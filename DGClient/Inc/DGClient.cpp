#include "DGClient_stdafx.h"
#include "resource.h"

#include "SceneComponent/main_scene_component.h"
#include "SceneComponent/start_scene.h"

#include <DGEngine_stdafx.h>
#include <core.h>
#include <Scene/scene_manager.h>

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

using namespace DG;

int WINAPI wWinMain(HINSTANCE _instance, HINSTANCE _prev_instance, PWSTR _cmd_line, int _cmd_show)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto const& core = Core::singleton();

	core->Initialize(L"DirectX Game Engine", L"DirectX Game Engine", _instance, IDI_ICON1, GAME_MODE::_2D);

	SceneManager::singleton()->AddSceneComponent<StartScene>("StartScene", false);

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

	core->Run();

	Core::singleton().reset();

	return 0;
}
