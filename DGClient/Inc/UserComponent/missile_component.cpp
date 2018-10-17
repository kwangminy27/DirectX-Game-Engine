#include "DGClient_stdafx.h"
#include "missile_component.h"

#include <object.h>
#include <Component/transform.h>
#include <Component/renderer.h>
#include <Component/material.h>

using namespace DG;

void MissileComponent::Initialize()
{
	type_ = static_cast<COMPONENT_TYPE>(USER_COMPONENT_TYPE::MISSILE);

	auto transform = std::dynamic_pointer_cast<Transform>(object()->AddComponent<Transform>("Transform"));

	transform->set_pivot(Math::Vector3{ 0.5f, 0.f, 0.f });

	auto renderer = std::dynamic_pointer_cast<Renderer>(object()->AddComponent<Renderer>("Renderer"));

	renderer->set_shader(BASIC_SHADER);
	renderer->set_mesh("ColorTri");

	auto const& material = std::dynamic_pointer_cast<Material>(object()->FindComponent(COMPONENT_TYPE::MATERIAL));

	MaterialConstantBuffer material_constant_buffer{};
	material_constant_buffer.diffuse = DirectX::Colors::White.v;

	material->SetMaterialConstantBuffer(material_constant_buffer, 0, 0);

	range_ = 1000.f;
}

MissileComponent::MissileComponent(MissileComponent const& _other) : UserComponent(_other)
{
	range_ = _other.range_;
}

MissileComponent::MissileComponent(MissileComponent&& _other) noexcept : UserComponent(std::move(_other))
{
	range_ = std::move(_other.range_);
}

void MissileComponent::_Release()
{
}

void MissileComponent::_Update(float _time)
{
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	auto displacement = 1000.f * _time;

	transform->Translation(transform->GetLocalUp() * displacement);

	range_ -= displacement;

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
