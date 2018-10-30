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
#include <Component/checkbox_UI.h>

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

	auto checkbox = Object::CreateObject("Checkbox", ui_layer);
	auto checkbox_ui_component = std::dynamic_pointer_cast<CheckboxUI>(checkbox->AddComponent<CheckboxUI>("CheckboxUI"));

	auto checkbox1 = Object::CreateObject("Checkbox", ui_layer);
	auto checkbox_ui_component1 = std::dynamic_pointer_cast<CheckboxUI>(checkbox1->AddComponent<CheckboxUI>("CheckboxUI"));

	auto checkbox1_transform = std::dynamic_pointer_cast<Transform>(checkbox1->FindComponent(COMPONENT_TYPE::TRANSFORM));
	checkbox1_transform->Translation({ -50.f, 0.f, 0.f });
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
