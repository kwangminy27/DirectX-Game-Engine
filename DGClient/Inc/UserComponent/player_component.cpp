#include "DGClient_stdafx.h"
#include "player_component.h"

#include <Scene/scene.h>
#include <object.h>
#include <Resource/resource_manager.h>
#include <Resource/texture.h>
#include <Component/transform.h>
#include <Component/renderer.h>
#include <Component/material.h>
#include <Component/animation_2d.h>
#include <Component/collider_rect.h>

using namespace DG;

void PlayerComponent::Initialize()
{
	type_ = static_cast<COMPONENT_TYPE>(USER_COMPONENT_TYPE::PLAYER);

	auto transform = std::dynamic_pointer_cast<Transform>(object()->AddComponent<Transform>("Transform"));

	transform->set_pivot(Math::Vector3{ 0.5f, 0.f, 0.f });

	auto renderer = std::dynamic_pointer_cast<Renderer>(object()->AddComponent<Renderer>("Renderer"));

	renderer->set_shader_tag(BASIC_ANIMATION_2D_SHADER);
	renderer->set_mesh_tag("TexRect");
	renderer->set_render_state(ALPHA_BLEND);

	auto material = std::dynamic_pointer_cast<Material>(object()->AddComponent<Material>("Material"));

	MaterialConstantBuffer material_constant_buffer{};
	material_constant_buffer.diffuse = DirectX::Colors::White.v;

	material->SetMaterialConstantBuffer(material_constant_buffer, 0, 0);
	material->SetTexture("Player", 0, 0, 0);
	material->SetSampler(LINEAR_SAMPLER, 0, 0, 0);

	auto animation_2d = std::dynamic_pointer_cast<Animation2D>(object()->AddComponent<Animation2D>("Animation2D"));

	animation_2d->AddClip("Player");

	auto collider_rect = std::dynamic_pointer_cast<ColliderRect>(object()->AddComponent<ColliderRect>("ColliderRect"));

	collider_rect->set_relative_info(Math::Vector3{ 0.f, 0.f, 0.f }, Math::Vector3{ 100.f, 100.f, 0.f });
}

PlayerComponent::PlayerComponent(PlayerComponent const& _other) : UserComponent(_other)
{
}

PlayerComponent::PlayerComponent(PlayerComponent&& _other) noexcept : UserComponent(std::move(_other))
{ 
}

void PlayerComponent::_Release()
{
}

void PlayerComponent::_Input(float _time)
{
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	if (GetAsyncKeyState('A') & 0x8000)
		transform->RotationZ(DirectX::XMConvertToRadians(180.f * _time));
	if (GetAsyncKeyState('D') & 0x8000)
		transform->RotationZ(DirectX::XMConvertToRadians(-180.f * _time));
	if (GetAsyncKeyState('S') & 0x8000)
		transform->Translation(transform->GetLocalUp() * -400.f * _time);
	if (GetAsyncKeyState('W') & 0x8000)
		transform->Translation(transform->GetLocalUp() * 400.f * _time);

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		auto const& default_layer = scene()->FindLayer("Default");
		auto missile = Object::CreateClone("Missile", "Missile", default_layer, true);
		auto const& missile_transform = std::dynamic_pointer_cast<Transform>(missile->FindComponent(COMPONENT_TYPE::TRANSFORM));

		missile_transform->set_local(transform->local());
	}
}

std::unique_ptr<Component, std::function<void(Component*)>> PlayerComponent::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new PlayerComponent{ *this }, [](Component* _p) {
		dynamic_cast<PlayerComponent*>(_p)->_Release();
		delete dynamic_cast<PlayerComponent*>(_p);
	} };
}
