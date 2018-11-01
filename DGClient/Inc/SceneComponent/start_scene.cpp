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
#include <Component/radio_button_UI.h>
#include <Component/collider_rect.h>

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

	auto checkbox = Object::CreateObject("CheckboxObj", ui_layer);
	auto checkbox_ui_component = std::dynamic_pointer_cast<CheckboxUI>(checkbox->AddComponent<CheckboxUI>("CheckboxUI"));

	auto checkbox1 = Object::CreateObject("Checkbox", ui_layer);
	auto checkbox_ui_component1 = std::dynamic_pointer_cast<CheckboxUI>(checkbox1->AddComponent<CheckboxUI>("CheckboxUI"));

	auto checkbox1_transform = std::dynamic_pointer_cast<Transform>(checkbox1->FindComponent(COMPONENT_TYPE::TRANSFORM));
	checkbox1_transform->Translation({ -50.f, 0.f, 0.f });

	// RadioButton
	auto rb_0 = Object::CreateObject("RadioButtonObj", ui_layer);
	auto rb_0_com = std::dynamic_pointer_cast<RadioButtonUI>(rb_0->AddComponent<RadioButtonUI>("RadioButtonUI"));
	auto const& radio_button_transform_component = std::dynamic_pointer_cast<Transform>(rb_0->FindComponent(COMPONENT_TYPE::TRANSFORM));

	auto rb_1 = Object::CreateObject("RadioButtonObj", ui_layer);
	auto rb_1_com = std::dynamic_pointer_cast<RadioButtonUI>(rb_1->AddComponent<RadioButtonUI>("RadioButtonUI"));
	auto const& radio_button_transform_component1 = std::dynamic_pointer_cast<Transform>(rb_1->FindComponent(COMPONENT_TYPE::TRANSFORM));
	radio_button_transform_component1->Translation({ -50.f, 0.f, 0.f });

	auto rb_2 = Object::CreateObject("RadioButtonObj", ui_layer);
	auto rb_2_com = std::dynamic_pointer_cast<RadioButtonUI>(rb_2->AddComponent<RadioButtonUI>("RadioButtonUI"));
	auto const& radio_button_transform_component2 = std::dynamic_pointer_cast<Transform>(rb_2->FindComponent(COMPONENT_TYPE::TRANSFORM));
	radio_button_transform_component2->Translation({ 50.f, 0.f, 0.f });
	
	// RadioButton Grouping
	rb_0_com->set_callback([_p = rb_0_com.get(), _p1 = rb_1_com.get(), _p2 = rb_2_com.get()](float _time) {
		_p->set_checkbox_state(CHECKBOX_STATE::CHECKED);
		_p1->set_checkbox_state(CHECKBOX_STATE::NORMAL);
		_p2->set_checkbox_state(CHECKBOX_STATE::NORMAL);
	});

	rb_1_com->set_callback([_p = rb_0_com.get(), _p1 = rb_1_com.get(), _p2 = rb_2_com.get()](float _time) {
		_p->set_checkbox_state(CHECKBOX_STATE::NORMAL);
		_p1->set_checkbox_state(CHECKBOX_STATE::CHECKED);
		_p2->set_checkbox_state(CHECKBOX_STATE::NORMAL);
	});

	rb_2_com->set_callback([_p = rb_0_com.get(), _p1 = rb_1_com.get(), _p2 = rb_2_com.get()](float _time) {
		_p->set_checkbox_state(CHECKBOX_STATE::NORMAL);
		_p1->set_checkbox_state(CHECKBOX_STATE::NORMAL);
		_p2->set_checkbox_state(CHECKBOX_STATE::CHECKED);
	});

	// TitleBar
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
