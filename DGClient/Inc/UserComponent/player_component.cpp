#include "DGClient_stdafx.h"
#include "player_component.h"

#include <Scene/scene.h>
#include <object.h>
#include <Resource/resource_manager.h>
#include <Resource/mesh.h>
#include <Resource/texture.h>
#include <Component/transform.h>
#include <Component/renderer.h>
#include <Component/material.h>
#include <Component/animation_2d.h>
#include <Component/collider_rect.h>
#include <Component/collider_circle.h>
#include <Component/collider_OOBB.h>
#include <Component/camera.h>
#include <input_manager.h>

using namespace DG;

void PlayerComponent::Initialize()
{
	auto const& camera = scene()->main_camera();
	auto const& camera_component = std::dynamic_pointer_cast<Camera>(camera->FindComponent(COMPONENT_TYPE::CAMERA));
	camera_component->set_target(object());

	type_ = static_cast<COMPONENT_TYPE>(USER_COMPONENT_TYPE::PLAYER);

	auto transform = std::dynamic_pointer_cast<Transform>(object()->AddComponent<Transform>("Transform"));

	transform->Scaling(Math::Vector3{ 100.f, 100.f, 1.f });
	transform->Translation({ 200.f, 200.f, 0.f });
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

	auto collider_oobb = std::dynamic_pointer_cast<ColliderOOBB>(object()->AddComponent<ColliderOOBB>("PlayerBody"));
	auto const& mesh = ResourceManager::singleton()->FindMesh("TexRect");
	auto extent = (mesh->max() - mesh->min()) * 0.5f * transform->GetLocalScale();

	collider_oobb->set_pivot({ 0.5f, 0.5f, 0.f });
	collider_oobb->set_relative_info({ 0.f, extent.y, 0.f }, extent, Math::Matrix::Identity);

	//auto collider_rect = std::dynamic_pointer_cast<ColliderRect>(object()->AddComponent<ColliderRect>("PlayerBody"));
	//auto const& mesh = ResourceManager::singleton()->FindMesh("TexRect");
	//auto extent = (mesh->max() - mesh->min()) * 0.5f * transform->GetLocalScale();

	//collider_rect->set_relative_info(Math::Vector3::Zero, extent * 2.f);
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
	auto const& input_manager = InputManager::singleton();
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	if (input_manager->KeyPressed("MoveLeft"))
		transform->RotationZ(DirectX::XMConvertToRadians(180.f * _time));
	if (input_manager->KeyPressed("MoveRight"))
		transform->RotationZ(DirectX::XMConvertToRadians(-180.f * _time));
	if (input_manager->KeyPressed("MoveUp"))
		transform->Translation(transform->GetLocalUp() * 400.f * _time);
	if (input_manager->KeyPressed("MoveDown"))
		transform->Translation(transform->GetLocalUp() * -400.f * _time);

	if (input_manager->KeyPressed("Space"))
	{
		auto const& default_layer = scene()->FindLayer("Default");
		auto missile = Object::CreateClone("Missile", "Missile", default_layer, false);
		auto const& missile_transform = std::dynamic_pointer_cast<Transform>(missile->FindComponent(COMPONENT_TYPE::TRANSFORM));

		// scaling을 사용하고 있어서 각각 따로따로 세팅해 줌. GetRight·Up·Look은 normalize된 vector를 리턴해주도록 했음
		missile_transform->SetLocalRight(transform->GetLocalRight());
		missile_transform->SetLocalUp(transform->GetLocalUp());
		missile_transform->SetLocalLook(transform->GetLocalLook());
		missile_transform->SetLocalPosition(transform->GetLocalPosition());
	}
}

std::unique_ptr<Component, std::function<void(Component*)>> PlayerComponent::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new PlayerComponent{ *this }, [](Component* _p) {
		dynamic_cast<PlayerComponent*>(_p)->_Release();
		delete dynamic_cast<PlayerComponent*>(_p);
	} };
}
