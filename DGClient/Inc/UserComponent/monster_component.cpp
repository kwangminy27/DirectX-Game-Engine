#include "DGClient_stdafx.h"
#include "monster_component.h"

#include <Resource/resource_manager.h>
#include <Resource/mesh.h>
#include <object.h>
#include <Component/transform.h>
#include <Component/renderer.h>
#include <Component/material.h>
#include <Component/collider_rect.h>

using namespace DG;

void MonsterComponent::Initialize()
{
	type_ = static_cast<COMPONENT_TYPE>(USER_COMPONENT_TYPE::MONSTER);

	auto transform = std::dynamic_pointer_cast<Transform>(object()->AddComponent<Transform>("Transform"));

	transform->Scaling(Math::Vector3{ 100.f, 100.f, 1.f });
	transform->Translation(Math::Vector3{ 400.f, 300.f, 0.f });
	transform->set_pivot(Math::Vector3{ 0.5f, 0.5f, 0.f });

	auto renderer = std::dynamic_pointer_cast<Renderer>(object()->AddComponent<Renderer>("Renderer"));

	renderer->set_shader_tag(BASIC_SHADER);
	renderer->set_mesh_tag("ColorTri");

	auto material = std::dynamic_pointer_cast<Material>(object()->AddComponent<Material>("Material"));

	MaterialConstantBuffer material_constant_buffer{};
	material_constant_buffer.diffuse = DirectX::Colors::White.v;

	material->SetMaterialConstantBuffer(material_constant_buffer, 0, 0);

	auto collider_rect = std::dynamic_pointer_cast<ColliderRect>(object()->AddComponent<ColliderRect>("MonsterBody"));

	auto const& mesh = ResourceManager::singleton()->FindMesh("ColorTri");
	collider_rect->set_relative_info(Math::Vector3::Zero, (mesh->max() - mesh->min()) * transform->scale_vector());
}

std::shared_ptr<Object> MonsterComponent::target()
{
	return target_.lock();
}

void MonsterComponent::set_target(std::shared_ptr<Object> const& _target)
{
	target_ = _target;
}

MonsterComponent::MonsterComponent(MonsterComponent const& _other) : UserComponent(_other)
{
	target_ = _other.target_;
}

MonsterComponent::MonsterComponent(MonsterComponent&& _other) noexcept : UserComponent(std::move(_other))
{
	target_ = std::move(_other.target_);
}

void MonsterComponent::_Release()
{
}

void MonsterComponent::_Update(float _time)
{
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));
	auto const& target_transform = std::dynamic_pointer_cast<Transform>(target()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	if (Math::Vector3::Distance(transform->GetLocalPosition(), target_transform->GetLocalPosition()) <= 400.f)
		transform->LookAt(target_transform->GetLocalPosition());
}

std::unique_ptr<Component, std::function<void(Component*)>> MonsterComponent::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new MonsterComponent{ *this }, [](Component* _p) {
		dynamic_cast<MonsterComponent*>(_p)->_Release();
		delete dynamic_cast<MonsterComponent*>(_p);
	} };
}
