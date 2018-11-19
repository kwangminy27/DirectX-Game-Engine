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
	std::cout << "Ŭ���̾�Ʈ ����" << std::endl;
}

void ProcessDataFromClient(std::shared_ptr<TCPSocket> const& _socket, void* _segment, int _data_received)
{
	std::cout << static_cast<char*>(_segment) << std::endl;
}

// global variable
int const kGoodSegmentSize = 1000;

void ServerManager::Initialize()
{
	WSADATA WSA_data{};
	WSAStartup(MAKEWORD(2, 2), &WSA_data);
}

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
		if (GetAsyncKeyState(VK_F12) & 0x8000)
		{
			for (auto const& _socket : read_block_sockets)
				_socket->ShutDown();

			break;
		}

		// �۾� ������ socket�� ���� ��� continue
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
		// WSAWaitForMultipleEvents���� ��� �ɷ��� �ٸ��� ó���ؾ���
		if (GetAsyncKeyState('Q') & 0x8000)
		{
			for (int i = 0; i < WSA_MAXIMUM_WAIT_EVENTS; ++i)
				WSACloseEvent(event_array[i]);

			break;
		}

		int result = WSAWaitForMultipleEvents(idx, event_array, false, WSA_INFINITE, false); // last parameter is a flag for IO Completion Routine Execution.
		int smallest_idx = result - WSA_WAIT_EVENT_0; // �ñ׳� ���°� �� ���� ó�� �ε���

		// ���� �� ó��
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

			// listen socket �̺�Ʈ�� �߻��ߴٸ�
			if (network_events.lNetworkEvents & FD_ACCEPT)
			{
				// accept�� ������ �ִٸ�
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
				// read�� ������ �ִٸ�
				if (network_events.iErrorCode[FD_READ_BIT] != 0)
					break;

				char segment[kGoodSegmentSize];
				int data_received = socket_array[i]->Receive(segment, kGoodSegmentSize);

				if (data_received > 0)
					ProcessDataFromClient(socket_array[i], segment, data_received);
			}
			else if (network_events.lNetworkEvents & FD_CLOSE)
			{
				// read�� ������ �ִٸ�
				if (network_events.iErrorCode[FD_CLOSE_BIT] != 0)
					break;

				socket_array[i] = nullptr;
			}
		}
	}
}

void ServerManager::ExcuteTCPIOCPLoop()
{
	iocp_ = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, NULL, 0);

	for (auto i = 0; i < clients_.size(); ++i)
	{
		clients_[i].receive_overlapped_ex.operation = IO_OPERATION::RECV;
		clients_[i].receive_overlapped_ex.wsa_buffer.buf = reinterpret_cast<char*>(clients_[i].receive_overlapped_ex.buffer);
		clients_[i].receive_overlapped_ex.wsa_buffer.len = 1024;
	}

	std::vector<std::unique_ptr<std::thread>> worker_thread_vector{};

	for (int i = 0; i < 6; ++i)
		worker_thread_vector.push_back(std::make_unique<thread>(WorkerThreadFunc));

	std::unique_ptr<std::thread> accept_thread = std::make_unique<thread>(AcceptThreadFunc);

	while (true)
	{
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			break;

		std::this_thread::sleep_for(1s);
	}

	accept_thread->join();

	for (auto const& _worker_thread : worker_thread_vector)
		_worker_thread->join();
}

void ServerManager::ProcessPacket()
{
	auto const& server_manager = ServerManager::singleton();
	auto& clients = server_manager->clients();
}

HANDLE ServerManager::iocp()
{
	return iocp_;
}

std::array<Client, 100>& ServerManager::clients()
{
	return clients_;
}

void ServerManager::_Release()
{
	WSACleanup();
}

void DG::WorkerThreadFunc()
{
	auto const& server_manager = ServerManager::singleton();
	auto& clients = server_manager->clients();

	DWORD io_size{};
	ULONG_PTR key{};
	OverlappedEx* overlapped_ex{};
	bool result{};

	while (true)
	{
		result = GetQueuedCompletionStatus(server_manager->iocp(), &io_size, &key, reinterpret_cast<LPOVERLAPPED*>(&overlapped_ex), INFINITE);

		if (result == false)
			throw std::exception{ "WorkerThreadFunc" };

		if (io_size == 0)
		{
			std::cout << "Ŭ���̾�Ʈ " << clients.at(key).id << " ����" << std::endl;

			clients.at(key).tcp_socket = nullptr;
			clients.at(key).packet_size = 0;
			clients.at(key).previous_data = 0;
			clients.at(key).is_connected = false;

			continue;
		}

		switch (overlapped_ex->operation)
		{
		case IO_OPERATION::RECV:
		{
			unsigned char* buffer = overlapped_ex->buffer;
			int remained = io_size;

			while (remained > 0)
			{
				if (clients.at(key).packet_size == 0)
					clients.at(key).packet_size = buffer[0];

				int required = clients.at(key).packet_size - clients.at(key).previous_data;

				if (remained >= required)
				{
					memcpy_s(clients.at(key).packet_buffer + clients.at(key).previous_data, required, buffer, required);

					server_manager->ProcessPacket();

					buffer += required;
					remained -= required;
					clients.at(key).packet_size = 0;
					clients.at(key).previous_data = 0;
				}
				else
				{
					memcpy_s(clients.at(key).packet_buffer + clients.at(key).previous_data, remained, buffer, remained);

					clients.at(key).previous_data += remained;
					remained = 0;
				}
			}

			DWORD flags{};
			result = WSARecv(
				clients.at(key).tcp_socket->socket(),
				&clients.at(key).receive_overlapped_ex.wsa_buffer,
				1,
				nullptr,
				&flags,
				&clients.at(key).receive_overlapped_ex.overlapped,
				nullptr
			);

			if (result != 0)
			{
				if (WSAGetLastError() != WSA_IO_PENDING)
					throw std::exception{ "WorkerThreadFunc" };
			}
			break;
		}
		case IO_OPERATION::SEND:
			delete overlapped_ex; // Send�� �Ź� �����Ҵ��ؼ� ����. ����, �Ϸ�� ��� ���� ����� ��.
			break;

		default:
			throw std::exception{ "WorkerThreadFunc" };
			break;
		}
	}
}

void DG::AcceptThreadFunc()
{
	auto const& server_manager = ServerManager::singleton();
	auto const& socket_manager = SocketManager::singleton();

	auto& clients = server_manager->clients();
	auto listen_socket = socket_manager->CreateOverlappedTCPSocket(AF_INET);

	SocketAddress server_address(INADDR_ANY, 666);
	listen_socket->Bind(server_address);
	listen_socket->Listen(10);
	
	while (true)
	{
		SocketAddress new_client_address{};
		auto new_socket = listen_socket->Accept(new_client_address);

		int new_id = -1;
		for (auto i = 0; i < clients.size(); ++i)
		{
			if (clients.at(i).is_connected == false)
			{
				new_id = i;
				break;
			}
		}

		if (new_id == -1)
		{
			std::cout << "������ ���� ������ �ο��� �ʰ��߽��ϴ�." << std::endl;
			continue;
		}

		HANDLE result = CreateIoCompletionPort(
			reinterpret_cast<HANDLE>(new_socket->socket()),
			server_manager->iocp(),
			new_id,
			NULL
		);

		if (result == NULL)
			throw std::exception{ "AcceptThreadFunc" };

		clients.at(new_id).tcp_socket = new_socket;
		clients.at(new_id).id = new_id;
		clients.at(new_id).is_connected = true;

		std::cout << "Ŭ���̾�Ʈ " << new_id << " ����" << endl;

		DWORD flags{};
		int result_2 = WSARecv(
			clients.at(new_id).tcp_socket->socket(),
			&clients.at(new_id).receive_overlapped_ex.wsa_buffer,
			1,
			nullptr,
			&flags,
			&clients.at(new_id).receive_overlapped_ex.overlapped,
			nullptr
		);

		if (result_2 != 0)
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
				throw std::exception{ "AcceptThreadFunc" };
		}
	}
}
