#include "DGClient_stdafx.h"
#include "SceneComponent/main_scene_component.h"
#include "UserComponent/player_component.h"
#include "UserComponent/monster_component.h"
#include "UserComponent/missile_component.h"

#include <core.h>
#include <Scene/scene_manager.h>
#include <Scene/scene.h>
#include <Scene/layer.h>
#include <object.h>
#include <Component/component.h>
#include <Component/transform.h>
#include <Component/renderer.h>
#include <Component/icon_UI.h>
#include <Component/Slot_ui.h>
#include <Component/collider_rect.h>
#include <Component/text.h>
#include <audio_manager.h>

// Test
#include <Component/material.h>
#include <Component/collider_pixel.h>
#include <Resource/resource_manager.h>
#include <Resource/mesh.h>

// Bar
#include <Component/bar_UI.h>
#include <Component/title_bar_UI.h>

#include <input_manager.h>

// Stage
#include <Component/stage.h>

using namespace DG;

void MainSceneComponent::Initialize()
{
	_CreatePrototypes();

	// Layer
	auto const& default_layer = scene()->FindLayer("Default");
	auto const& ui_layer = scene()->FindLayer("UI");

	// Monster
	auto monster = Object::CreateObject("Monster", default_layer);
	auto monster_component = std::dynamic_pointer_cast<MonsterComponent>(monster->AddComponent<MonsterComponent>("Monster"));

	// TitleBar_0
	auto title_bar = Object::CreateObject("TitleBar", ui_layer);
	auto title_bar_component = std::dynamic_pointer_cast<TitleBarUI>(title_bar->AddComponent<TitleBarUI>("Bar"));

	title_bar_component->set_owner(monster);
	title_bar_component->set_callback([_p = title_bar_component.get()](float _time) {
		auto const& input_manager = InputManager::singleton();
		auto const& owner_transform = std::dynamic_pointer_cast<Transform>(_p->owner()->FindComponent(COMPONENT_TYPE::TRANSFORM));

		owner_transform->Translation(input_manager->mouse_displacement());
	});

	// Player
	auto player = Object::CreateObject("Player", default_layer);
	auto player_component = player->AddComponent<PlayerComponent>("Player");

	auto const& player_transform = std::static_pointer_cast<Transform>(player->FindComponent(COMPONENT_TYPE::TRANSFORM));
	player_transform->SetLocalPosition({ 8000.f, 4000.f, 0.f });

	// Child
	int transform_flag{};
	//transform_flag = static_cast<int>(TRANSFORM_FLAG::SCALE);
	transform_flag |= static_cast<int>(TRANSFORM_FLAG::ROTATE);
	transform_flag |= static_cast<int>(TRANSFORM_FLAG::TRANSLATE);

	//auto child = Object::CreateObject("Child", nullptr);
	//player->AddChild(child);
	//auto child_component = child->AddComponent<SlotUI>("Slot");

	//auto const& child_transform = std::dynamic_pointer_cast<Transform>(child->FindComponent(COMPONENT_TYPE::TRANSFORM));
	//child_transform->SetLocalPosition({ 150.f, 0.f, 0.f });
	//child_transform->set_transform_flag(transform_flag);

	//auto child_2 = Object::CreateObject("Child", nullptr);
	//player->AddChild(child_2);
	//auto child_2_component = child_2->AddComponent<SlotUI>("Slot");

	//auto const& child_2_transform = std::dynamic_pointer_cast<Transform>(child_2->FindComponent(COMPONENT_TYPE::TRANSFORM));
	//child_2_transform->SetLocalPosition({ 50.f, 0.f, 0.f });
	//child_2_transform->set_transform_flag(transform_flag);

	//// child's child
	//transform_flag = {};
	////transform_flag = static_cast<int>(TRANSFORM_FLAG::SCALE);
	////transform_flag |= static_cast<int>(TRANSFORM_FLAG::ROTATE);
	//transform_flag |= static_cast<int>(TRANSFORM_FLAG::TRANSLATE);

	//auto child_child = Object::CreateObject("Child", nullptr);
	//child->AddChild(child_child);
	//auto child_child_component = child_child->AddComponent<SlotUI>("Slot");

	//auto const& child_child_transform = std::dynamic_pointer_cast<Transform>(child_child->FindComponent(COMPONENT_TYPE::TRANSFORM));
	//child_child_transform->SetLocalPosition({ 100.f, 0.f, 0.f });
	//child_child_transform->set_transform_flag(transform_flag);

	//// TitleBar_1
	//auto title_bar1 = Object::CreateObject("TitleBar", ui_layer);
	//auto title_bar1_component = std::dynamic_pointer_cast<TitleBarUI>(title_bar1->AddComponent<TitleBarUI>("Bar"));

	//title_bar1_component->set_owner(player);
	//title_bar1_component->set_callback([_p = title_bar1_component.get()](float _time) {
	//	auto const& input_manager = InputManager::singleton();
	//	auto const& owner_transform = std::dynamic_pointer_cast<Transform>(_p->owner()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	//	owner_transform->Translation(input_manager->mouse_displacement());
	//});

	monster_component->set_target(player);

	// Pixel Collision Test
	auto pixel = Object::CreateObject("Pixel", default_layer);

	auto transform = std::dynamic_pointer_cast<Transform>(pixel->AddComponent<Transform>("Transform"));
	transform->Scaling({ 200.f, 50.f, 1.f });
	transform->Translation({ 500.f, 100.f, 0.f });

	auto renderer = dynamic_pointer_cast<Renderer>(pixel->AddComponent<Renderer>("Renderer"));
	renderer->set_shader_tag(BASIC_TEX_SHADER);
	renderer->set_mesh_tag("TexRect");

	auto material = dynamic_pointer_cast<Material>(pixel->AddComponent<Material>("Material"));

	MaterialConstantBuffer material_constant_buffer{};
	material_constant_buffer.diffuse = DirectX::Colors::White.v;

	material->SetMaterialConstantBuffer(material_constant_buffer, 0, 0);
	material->SetTexture("PixelCollider", 0, 0, 0);
	material->SetSampler(LINEAR_SAMPLER, 0, 0, 0);

	auto colider_pixel = dynamic_pointer_cast<ColliderPixel>(pixel->AddComponent<ColliderPixel>("ColliderPixel"));
	auto const& mesh = ResourceManager::singleton()->FindMesh("TexRect");
	auto extent = (mesh->max() - mesh->min()) * 0.5f * transform->GetLocalScale();

	colider_pixel->set_relative_info("PixelCollider", Math::Vector3::Zero, extent * 2.f);

	// Bar
	auto bar = Object::CreateObject("Bar", ui_layer);
	auto bar_component = bar->AddComponent<BarUI>("Bar");

	// Slot
	auto slot = Object::CreateObject("Slot", ui_layer);
	auto slot_component = std::dynamic_pointer_cast<SlotUI>(slot->AddComponent<SlotUI>("Slot"));

	auto slot_2 = Object::CreateObject("Slot", ui_layer);
	auto slot_2_component = std::dynamic_pointer_cast<SlotUI>(slot_2->AddComponent<SlotUI>("Slot"));
	auto const& slot_2_transform = std::dynamic_pointer_cast<Transform>(slot_2->FindComponent(COMPONENT_TYPE::TRANSFORM));
	slot_2_transform->Translation({ 37.f, 0.f, 0.f });

	auto slot_3 = Object::CreateObject("Slot", ui_layer);
	auto slot_3_component = std::dynamic_pointer_cast<SlotUI>(slot_3->AddComponent<SlotUI>("Slot"));
	auto const& slot_3_transform = std::dynamic_pointer_cast<Transform>(slot_3->FindComponent(COMPONENT_TYPE::TRANSFORM));
	slot_3_transform->Translation({ 74.f, 0.f, 0.f });

	// Icon
	auto icon = Object::CreateObject("Icon", ui_layer);
	auto icon_component = std::dynamic_pointer_cast<IconUI>(icon->AddComponent<IconUI>("Icon"));
	icon_component->AddSlot(slot);
	icon_component->AddSlot(slot_2);
	icon_component->AddSlot(slot_3);
	icon_component->set_current_slot(slot);

	auto icon_2 = Object::CreateObject("Icon", ui_layer);
	auto icon_2_component = std::dynamic_pointer_cast<IconUI>(icon_2->AddComponent<IconUI>("Icon"));
	auto const& icon_2_material = std::dynamic_pointer_cast<Material>(icon_2->FindComponent(COMPONENT_TYPE::MATERIAL));
	icon_2_material->SetTexture("Cake", 0, 0, 0);
	icon_2_component->AddSlot(slot);
	icon_2_component->AddSlot(slot_2);
	icon_2_component->AddSlot(slot_3);
	icon_2_component->set_current_slot(slot_2);

	// Text
	auto text = Object::CreateObject("FPSText", ui_layer);
	auto text_component = std::dynamic_pointer_cast<Text>(text->AddComponent<Text>("FPSTextComponent"));
	auto const& text_transform = std::dynamic_pointer_cast<Transform>(text->FindComponent(COMPONENT_TYPE::TRANSFORM));

	text_transform->Translation({ 0.f, 600.f, 0.f });

	text_component->set_text(L"Hello, world!");
	text_component->set_text_alignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	text_component->set_paragraph_alignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	text_component->set_ui_flag(true);
	text_component->set_shadow_flag(true);
	text_component->set_shadow_offset({ 5.f, -5.f, 0.f });
	text_component->set_text_format_tag("ÀÏ¹Ý");
	text_component->set_brush_color(DirectX::Colors::Gold.v);
	text_component->set_shadow_brush_color(DirectX::Colors::Black.v);
	text_component->set_text_area({ 0.f, 0.f, 200.f, 200.f });

	// Stage
	auto stage = Object::CreateObject("Stage", default_layer);
	auto stage_component = std::dynamic_pointer_cast<Stage>(stage->AddComponent<Stage>("StageComponent"));
	stage_component->CreateTile(STAGE_TYPE::ISOMETRIC, 200, 200, { 80.f, 40.f });
}

MainSceneComponent::MainSceneComponent(MainSceneComponent const& _other) : SceneComponent(_other)
{
}

MainSceneComponent::MainSceneComponent(MainSceneComponent&& _other) noexcept : SceneComponent(std::move(_other))
{
}

void MainSceneComponent::_Release()
{
}

void MainSceneComponent::_Input(float _time)
{
	if (GetAsyncKeyState(VK_F5) & 0x8000)
		AudioManager::singleton()->FindSoundEffect("town1")->Play();
	if (GetAsyncKeyState(VK_F6) & 0x8000)
		AudioManager::singleton()->Suspend();
	if (GetAsyncKeyState(VK_F7) & 0x8000)
		AudioManager::singleton()->Resume();
	if (GetAsyncKeyState(VK_F8) & 0x8000)
	{
		auto sound_effect_instance = AudioManager::singleton()->FindSoundEffect("town1")->CreateInstance();
		sound_effect_instance->Play(true);
		AudioManager::singleton()->AddSoundEffectInstance("town1_loop", sound_effect_instance);
	}
	if (GetAsyncKeyState(VK_F9) & 0x8000)
		AudioManager::singleton()->RemoveSoundEffectInstance("town1_loop");
}

void MainSceneComponent::_Update(float _time)
{
	auto const& text = SceneManager::singleton()->FindObject("FPSText");
	auto const& text_component = std::static_pointer_cast<Text>(text->FindComponent("FPSTextComponent"));

	auto FPS = Core::singleton()->GetFPS();

	text_component->set_text(to_wstring(FPS));
}

std::unique_ptr<SceneComponent, std::function<void(SceneComponent*)>> MainSceneComponent::_Clone() const
{
	return std::unique_ptr<SceneComponent, std::function<void(SceneComponent*)>>{ new MainSceneComponent{ *this }, [](SceneComponent* _p) {
		dynamic_cast<MainSceneComponent*>(_p)->_Release();
		delete dynamic_cast<MainSceneComponent*>(_p);
	} };
}

void MainSceneComponent::_CreatePrototypes()
{
	auto const& default_layer = scene()->FindLayer("Default");

	auto missile_prototype = Object::CreatePrototype("Missile", true);
	auto missile_component = missile_prototype->AddComponent<MissileComponent>("Missile");
}
