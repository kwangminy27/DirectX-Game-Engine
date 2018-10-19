#include "DGClient_stdafx.h"
#include "missile_component.h"

#include <Resource/resource_manager.h>
#include <Resource/mesh.h>
#include <object.h>
#include <Component/transform.h>
#include <Component/renderer.h>
#include <Component/material.h>
#include <Component/collider.h>
#include <Component/collider_rect.h>

using namespace DG;

void MissileComponent::Initialize()
{
	type_ = static_cast<COMPONENT_TYPE>(USER_COMPONENT_TYPE::MISSILE);

	speed_ = 1200.f;
	range_ = 600.f;

	auto transform = std::dynamic_pointer_cast<Transform>(object()->AddComponent<Transform>("Transform"));

	transform->Scaling(Math::Vector3{ 0.5f, 0.5f, 1.f });
	transform->set_pivot(Math::Vector3{ 0.5f, 0.f, 0.f });

	auto renderer = std::dynamic_pointer_cast<Renderer>(object()->AddComponent<Renderer>("Renderer"));

	renderer->set_shader_tag(BASIC_SHADER);
	renderer->set_mesh_tag("ColorTri");

	auto material = std::dynamic_pointer_cast<Material>(object()->AddComponent<Material>("Material"));

	MaterialConstantBuffer material_constant_buffer{};
	material_constant_buffer.diffuse = DirectX::Colors::White.v;

	material->SetMaterialConstantBuffer(material_constant_buffer, 0, 0);

	auto collider_rect = std::dynamic_pointer_cast<ColliderRect>(object()->AddComponent<ColliderRect>("ColliderRect"));

//	auto const& mesh = ResourceManager::singleton()->FindMesh("ColorTri");
//	collider_rect->set_relative_info(Math::Vector3::Zero, (mesh->max() - mesh->min()) * transform->scale_vector());
	collider_rect->set_relative_info(Math::Vector3::Zero, Math::Vector3{ 100.f, 100.f, 0.f });
	collider_rect->AddCallback([this](Collider* _src, Collider* _dest, float _time) {
		_MissileHit(_dest);
	}, COLLISION_CALLBACK_TYPE::ENTER);
}

MissileComponent::MissileComponent(MissileComponent const& _other) : UserComponent(_other)
{
	speed_ = _other.speed_;
	range_ = _other.range_;
}

MissileComponent::MissileComponent(MissileComponent&& _other) noexcept : UserComponent(std::move(_other))
{
	speed_ = std::move(_other.speed_);
	range_ = std::move(_other.range_);
}

void MissileComponent::_Release()
{
}

void MissileComponent::_Update(float _time)
{
	range_ -= speed_ * _time;

	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	transform->Translation(transform->GetLocalUp() * speed_ * _time);

	if (range_ <= 0.f)
		object()->set_active_flag(false);
}

std::unique_ptr<Component, std::function<void(Component*)>> MissileComponent::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new MissileComponent{ *this }, [](Component* _p) {
		dynamic_cast<MissileComponent*>(_p)->_Release();
		delete dynamic_cast<MissileComponent*>(_p);
	} };
}

void MissileComponent::_MissileHit(Collider* _target)
{
	if (_target->tag() == "MonsterBody")
	{
		std::cout << "Monster Hit!" << std::endl;
		_target->object()->set_active_flag(false);
	}
}
