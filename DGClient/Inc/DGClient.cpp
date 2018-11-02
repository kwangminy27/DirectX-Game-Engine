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
