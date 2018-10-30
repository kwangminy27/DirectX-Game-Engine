#include "DGClient_stdafx.h"
#include "start_scene.h"
#include "main_scene_component.h"

#include <Scene/scene_manager.h>
#include <Scene/scene.h>
#include <Scene/layer.h>
#include <object.h>
#include <Component/camera.h>
#include <Component/transform.h>
#include <Component/button_UI.h>

using namespace DG;

void StartScene::Initialize()
{
	_CreatePrototypes();

	auto const& camera = scene()->main_camera();
	auto const& camera_component = std::dynamic_pointer_cast<Camera>(camera->FindComponent(COMPONENT_TYPE::CAMERA));

	auto const& default_layer = scene()->FindLayer("Default");
	auto const& ui_layer = scene()->FindLayer("UI");

	auto start_button = Object::CreateObject("StartButton", ui_layer);
	auto button_UI_component = std::dynamic_pointer_cast<ButtonUI>(start_button->AddComponent<ButtonUI>("ButtonUI"));

	button_UI_component->set_callback([this](float _time) {
		_StartButtonCallback(_time);
	});
}

StartScene::StartScene(StartScene const& _other) : SceneComponent(_other)
{
}

StartScene::StartScene(StartScene&& _other) noexcept : SceneComponent(std::move(_other))
{
}

void StartScene::_Release()
{
}

std::unique_ptr<SceneComponent, std::function<void(SceneComponent*)>> StartScene::_Clone() const
{
	return std::unique_ptr<SceneComponent, std::function<void(SceneComponent*)>>{ new StartScene{ *this }, [](SceneComponent* _p) {
		dynamic_cast<StartScene*>(_p)->_Release();
		delete dynamic_cast<StartScene*>(_p);
	} };
}

void StartScene::_CreatePrototypes()
{
}

void StartScene::_StartButtonCallback(float _time)
{
	auto const& scene_manager = SceneManager::singleton();

	scene_manager->CreateNextScene("MainScene");
	scene_manager->AddSceneComponent<MainSceneComponent>("MainScene", true);
}
