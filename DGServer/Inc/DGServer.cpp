#include <DGNetwork_stdafx.h>
#include <thread_manager.h>
#include <socket_manager.h>
#include <socket_address.h>
#include <UDP_socket.h>
#include <TCP_socket.h>

int const kGoodSegmentSize = 1000;

void ProcessNewClient(std::shared_ptr<TCPSocket> const& _socket, SocketAddress const& _address)
{
	std::cout << "클라이언트 접속" << std::endl;
}

void ProcessDataFromClient(std::shared_ptr<TCPSocket> const& _socket, void* _segment, int _data_received)
{
	std::cout << static_cast<char*>(_segment) << std::endl;
}

void DoTCPLoop()
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

int main()
{
	try
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		WSADATA WSA_data{};
		WSAStartup(MAKEWORD(2, 2), &WSA_data);

		auto const& thread_manager = ThreadManager::singleton();
		thread_manager->CreateThread("DoTCPLoop", [](void* _p) {
			DoTCPLoop();
		}, nullptr);

		while (true)
		{
			if (GetAsyncKeyState('Q') & 0x8000)
				break;
		}

		WSACleanup();
	}
	catch (std::exception const& _e)
	{
		std::cout << _e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "main" << std::endl;
	}

	return 0;
}