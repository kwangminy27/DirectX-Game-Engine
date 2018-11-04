#include <DGNetwork_stdafx.h>
#include <server_manager.h>
//#include <socket_manager.h>
//#include <socket_address.h>
//#include <UDP_socket.h>
//#include <TCP_socket.h>

int main()
{
	try
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		WSADATA WSA_data{};
		WSAStartup(MAKEWORD(2, 2), &WSA_data);

		auto const& server_manager = ServerManager::singleton();
		server_manager->ExcuteTCPEventSelectLoop();

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