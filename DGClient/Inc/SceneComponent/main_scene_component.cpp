#include "DGClient_stdafx.h"
#include "SceneComponent/main_scene_component.h"
#include "UserComponent/player_component.h"
#include "UserComponent/monster_component.h"
#include "UserComponent/missile_component.h"

#include <Scene/scene.h>
#include <Scene/layer.h>
#include <object.h>
#include <Component/component.h>
#include <Component/transform.h>
#include <Component/renderer.h>

// Test
#include <Component/material.h>
#include <Component/collider_pixel.h>
#include <Resource/resource_manager.h>
#include <Resource/mesh.h>

// Bar
#include <Component/bar_UI.h>

using namespace DG;

void MainSceneComponent::Initialize()
{
	_CreatePrototypes();

	auto const& default_layer = scene()->FindLayer("Default");
	auto const& ui_layer = scene()->FindLayer("UI");

	auto monster = Object::CreateObject("Monster", default_layer);
	auto monster_component = std::dynamic_pointer_cast<MonsterComponent>(monster->AddComponent<MonsterComponent>("Monster"));

	auto player = Object::CreateObject("Player", default_layer);
	auto player_component = player->AddComponent<PlayerComponent>("Player");

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
