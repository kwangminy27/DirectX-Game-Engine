#include "DGClient_stdafx.h"
#include "resource.h"

#include "SceneComponent/main_scene_component.h"
#include "SceneComponent/start_scene.h"

#include <DGEngine_stdafx.h>
#include <core.h>
#include <Scene/scene_manager.h>

using namespace DG;

int WINAPI wWinMain(HINSTANCE _instance, HINSTANCE _prev_instance, PWSTR _cmd_line, int _cmd_show)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto const& core = Core::singleton();

	core->Initialize(L"DirectX Game Engine", L"DirectX Game Engine", _instance, IDI_ICON1, GAME_MODE::_2D);

	SceneManager::singleton()->AddSceneComponent<StartScene>("StartScene", false);

	core->Run();

	Core::singleton().reset();

	return 0;
}

#pragma region test
//#include <DGNetwork_stdafx.h>
//#include <thread_manager.h>
//
//void Test(void* _argument)
//{
//	int* argument = reinterpret_cast<int*>(_argument);
//
//	auto& thread_manager = ThreadManager::singleton();
//
//	std::string message{ "thread id: " };
//	message += to_string(*argument) + "\n"s;
//
//	thread_manager->debug_mutex().lock();
//	thread_manager->debug_message_queue().push(message);
//	thread_manager->debug_mutex().unlock();
//}

//// ########## Network Test #########
//#include <DGNetwork_stdafx.h>
//#include <socket_manager.h>
//#include <socket_address.h>
//#include <UDP_socket.h>
//#include <TCP_socket.h>

	//for (int i = 0; i < 10; ++i)
	//{
	//	ThreadManager::singleton()->CreateThread(
	//		"Test"s + to_string(i),
	//		[](void* _t) { Test(_t); },
	//		&i
	//	);
	//}

	//auto& message_queue = ThreadManager::singleton()->debug_message_queue();

	//while (message_queue.size() != 0)
	//{
	//	std::cout << message_queue.front() << std::endl;
	//	message_queue.pop();
	//}

	//ThreadManager::singleton().reset();

	/*WSADATA WSA_data{};
	WSAStartup(MAKEWORD(2, 2), &WSA_data);

	auto const& socket_manager = SocketManager::singleton();*/

	// ########## UDP Socket Test ##########
	//auto UDP_socket = socket_manager->CreateUDPSocket(AF_INET);

	//sockaddr_in my_addr{};
	//my_addr.sin_family = AF_INET;
	//my_addr.sin_port = htons(50000);
	//InetPton(AF_INET, L"192.168.1.119", &my_addr.sin_addr);

	//SocketAddress my_addr_wrapper{ *(reinterpret_cast<sockaddr*>(&my_addr)) };

	//UDP_socket->Bind(my_addr_wrapper);

	//char buffer[128] = "Hello";

	//sockaddr_in server_addr{};
	//server_addr.sin_family = AF_INET;
	//server_addr.sin_port = htons(666);
	//InetPton(AF_INET, L"192.168.1.119", &server_addr.sin_addr);

	//SocketAddress server_addr_wrapper{ *(reinterpret_cast<sockaddr*>(&server_addr)) };

	//UDP_socket->SendTo(buffer, 128, server_addr_wrapper);
	// ########## UDP Socket Test ##########

	// ########## TCP Socket Test ##########
	//auto TCP_socket = socket_manager->CreateTCPSocket(AF_INET);

	//sockaddr_in my_addr{};
	//my_addr.sin_family = AF_INET;
	//my_addr.sin_port = htons(0);
	//InetPton(AF_INET, L"192.168.1.119", &my_addr.sin_addr);

	//SocketAddress my_addr_wrapper{ *(reinterpret_cast<sockaddr*>(&my_addr)) };
	//TCP_socket->Bind(my_addr_wrapper);

	//sockaddr_in server_addr{};
	//server_addr.sin_family = AF_INET;
	//server_addr.sin_port = htons(666);
	//InetPton(AF_INET, L"192.168.1.119", &server_addr.sin_addr);

	//SocketAddress server_addr_wrapper{ *(reinterpret_cast<sockaddr*>(&server_addr)) };
	//TCP_socket->Connect(server_addr_wrapper);

	//char buffer[128] = "Hello I'm TCP";
	//TCP_socket->Send(buffer, 128);
	//// ########## TCP Socket Test ##########

	//system("pause");

	//WSACleanup();
#pragma endregion 