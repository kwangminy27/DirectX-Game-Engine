#include "DGClient_stdafx.h"
#include "resource.h"

#include "SceneComponent/main_scene_component.h"

#include <DGEngine_stdafx.h>
#include <core.h>
#include <Scene/scene_manager.h>

using namespace DG;

int WINAPI wWinMain(HINSTANCE _instance, HINSTANCE _prev_instance, PWSTR _cmd_line, int _cmd_show)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto const& core = Core::singleton();

	core->Initialize(L"DirectX Game Engine", L"DirectX Game Engine", _instance, IDI_ICON1, GAME_MODE::_2D);

	SceneManager::singleton()->AddSceneComponent<MainSceneComponent>("MainSceneComponent");

	core->Run();

	Core::singleton().reset();

	return 0;
}