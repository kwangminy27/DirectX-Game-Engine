#include "DGNetwork_stdafx.h"
#include "server_manager.h"

#include "socket_manager.h"
#include "socket_address.h"
#include "UDP_socket.h"
#include "TCP_socket.h"

using namespace DG;

// global function
void ProcessNewClient(std::shared_ptr<TCPSocket> const& _socket, SocketAddress const& _address)
{
	std::cout << "클라이언트 접속" << std::endl;
}

void ProcessDataFromClient(std::shared_ptr<TCPSocket> const& _socket, void* _segment, int _data_received)
{
	std::cout << static_cast<char*>(_segment) << std::endl;
}

// global variable
int const kGoodSegmentSize = 1000;

void ServerManager::ExcuteTCPSelectLoop()
{
	auto const& socket_manager = SocketManager::singleton();

	auto listen_socket = socket_manager->CreateTCPSocket(AF_INET);

	SocketAddress server_address(INADDR_ANY, 666);
	listen_socket->Bind(server_address);
	listen_socket->Listen(3);

	std::vector<std::shared_ptr<TCPSocket>> read_block_sockets{};
	read_block_sockets.push_back(listen_socket);
	std::vector<std::shared_ptr<TCPSocket>> readable_sockets{};

	while (true)
	{
		if (GetAsyncKeyState('Q') & 0x8000)
		{
			for (auto const& _socket : read_block_sockets)
				_socket->ShutDown();

			break;
		}

		// 작업 가능한 socket이 없는 경우 continue
		if (!socket_manager->Select(&read_block_sockets, &readable_sockets, nullptr, nullptr, nullptr, nullptr))
			continue;

		for (auto const& _socket : readable_sockets)
		{
			if (_socket == listen_socket)
			{
				SocketAddress new_client_address{};
				auto new_socket = listen_socket->Accept(new_client_address);

				read_block_sockets.push_back(new_socket);

				ProcessNewClient(new_socket, new_client_address);
			}
			else
			{
				char segment[kGoodSegmentSize];
				int data_received = _socket->Receive(segment, kGoodSegmentSize);

				if (data_received > 0)
					ProcessDataFromClient(_socket, segment, data_received);
			}
		}
	}
}

void ServerManager::ExcuteTCPEventSelectLoop()
{
	auto const& socket_manager = SocketManager::singleton();

	auto listen_socket = socket_manager->CreateTCPSocket(AF_INET);

	SocketAddress server_address(INADDR_ANY, 666);
	listen_socket->Bind(server_address);
	listen_socket->Listen(3);

	WSAEVENT event = WSACreateEvent();
	WSAEventSelect(listen_socket->socket(), event, FD_ACCEPT);

	WSAEVENT event_array[WSA_MAXIMUM_WAIT_EVENTS]{};
	std::shared_ptr<TCPSocket> socket_array[WSA_MAXIMUM_WAIT_EVENTS]{};
	int idx{};

	event_array[idx] = event;
	socket_array[idx] = listen_socket;
	++idx;

	while (true)
	{
		if (GetAsyncKeyState('Q') & 0x8000)
		{
			for (int i = 0; i < WSA_MAXIMUM_WAIT_EVENTS; ++i)
				WSACloseEvent(event_array[i]);

			break;
		}

		int result = WSAWaitForMultipleEvents(idx, event_array, false, WSA_INFINITE, false); // last parameter is a flag for IO Completion Routine Execution.
		int smallest_idx = result - WSA_WAIT_EVENT_0; // 시그널 상태가 된 가장 처음 인덱스

		// 실패 시 처리
		if (result == WSA_WAIT_TIMEOUT) {}

		for (int i = smallest_idx; i < idx; ++i)
		{
			int result_2 = WSAWaitForMultipleEvents(1, &event_array[i], true, 0, false);

			if (result_2 == WSA_WAIT_FAILED || result_2 == WSA_WAIT_TIMEOUT)
				continue;

			if (!socket_array[i])
				continue;

			WSANETWORKEVENTS network_events{};
			WSAEnumNetworkEvents(socket_array[i]->socket(), event_array[i], &network_events);

			// listen socket 이벤트가 발생했다면
			if (network_events.lNetworkEvents & FD_ACCEPT)
			{
				// accept에 문제가 있다면
				if (network_events.iErrorCode[FD_ACCEPT_BIT] != 0)
					break;

				SocketAddress new_client_address{};
				auto new_socket = listen_socket->Accept(new_client_address);

				event = WSACreateEvent();
				WSAEventSelect(new_socket->socket(), event, FD_READ | FD_CLOSE);

				event_array[idx] = event;
				socket_array[idx] = new_socket;
				++idx;

				ProcessNewClient(new_socket, new_client_address);
			}
			else if (network_events.lNetworkEvents & FD_READ)
			{
				// read에 문제가 있다면
				if (network_events.iErrorCode[FD_READ_BIT] != 0)
					break;

				char segment[kGoodSegmentSize];
				int data_received = socket_array[i]->Receive(segment, kGoodSegmentSize);

				if (data_received > 0)
					ProcessDataFromClient(socket_array[i], segment, data_received);
			}
			else if (network_events.lNetworkEvents & FD_CLOSE)
			{
				// read에 문제가 있다면
				if (network_events.iErrorCode[FD_CLOSE_BIT] != 0)
					break;

				socket_array[i] = nullptr;
			}
		}
	}
}

void ServerManager::_Release()
{
}
