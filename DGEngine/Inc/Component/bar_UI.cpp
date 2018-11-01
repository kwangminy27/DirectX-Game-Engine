#include "DGEngine_stdafx.h"
#include "bar_UI.h"

#include "Resource/resource_manager.h"
#include "Resource/mesh.h"
#include "object.h"
#include "Component/transform.h"
#include "Component/renderer.h"
#include "Component/material.h"
#include "Component/collider_rect.h"
#include "input_manager.h"

using namespace DG;

void BarUI::Initialize()
{
	try
	{
		UI::Initialize();

		auto transform = std::dynamic_pointer_cast<Transform>(object()->AddComponent<Transform>("Transform"));

		transform->Scaling({ 200.f, 30.f, 0.f });
		transform->Translation({ 100.f, 500.f, 0.f });

		transform->set_pivot({ 0.5f, 0.5f, 0.f });

		auto renderer = std::dynamic_pointer_cast<Renderer>(object()->AddComponent<Renderer>("Renderer"));

		renderer->set_shader_tag(BASIC_TEX_SHADER);
		renderer->set_mesh_tag("TexRect");

		auto material = std::dynamic_pointer_cast<Material>(object()->AddComponent<Material>("Material"));

		MaterialConstantBuffer material_constant_buffer{};
		material_constant_buffer.diffuse = DirectX::Colors::White.v;

		material->SetMaterialConstantBuffer(material_constant_buffer, 0, 0);
		material->SetTexture("HPBar", 0, 0, 0);
		material->SetSampler(LINEAR_SAMPLER, 0, 0, 0);

		auto collider_rect = std::dynamic_pointer_cast<ColliderRect>(object()->AddComponent<ColliderRect>("CheckboxBody"));
		auto const& mesh = ResourceManager::singleton()->FindMesh("TexRect");
		auto extent = (mesh->max() - mesh->min()) * 0.5f * transform->GetLocalScale();

		collider_rect->set_collision_group_tag("UI");
		collider_rect->set_relative_info(Math::Vector3::Zero, extent * 2.f);

		set_direction(CUTTING_DIR::RIGHT_TO_LEFT);
		set_range(0.f, 100.f);
		set_value(100.f);
		set_scale_vector(transform->GetLocalScale());
	}
	catch (std::exception const& _e)
	{
		std::cout << _e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "BarUI::Initialize()" << std::endl;
	}
}

void BarUI::UpdateConstantBuffer()
{
}

void BarUI::AddValue(float _value)
{
	value_ += _value;

	value_ = std::clamp(value_, range_.first, range_.second);
}

void BarUI::set_direction(CUTTING_DIR _direction)
{
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	direction_ = _direction;

	switch (_direction)
	{
	case CUTTING_DIR::BOTTOM_TO_TOP:
		transform->set_pivot({ 0.f, 1.f, 0.f });
		transform->Translation({ 0.f, transform->GetLocalScale().y, 0.f });
		break;
	case CUTTING_DIR::LEFT_TO_RIGHT:
		transform->set_pivot({ 1.f, 0.f, 0.f });
		transform->Translation({ transform->GetLocalScale().x, 0.f, 0.f });
		break;
	case CUTTING_DIR::RIGHT_TO_LEFT:
		transform->set_pivot({ 0.f, 0.f, 0.f });
		break;
	case CUTTING_DIR::TOP_TO_BOTTOM:
		transform->set_pivot({ 0.f, 0.f, 0.f });
		break;
	}
}

void BarUI::set_range(float _min, float _max)
{
	range_.first = _min;
	range_.second = _max;

	value_ = std::clamp(value_, _min, _max);
}

void BarUI::set_value(float _value)
{
	value_ = std::clamp(_value, range_.first, range_.second);
}

void BarUI::set_scale_vector(Math::Vector3 const& _scale_vector)
{
	scale_vector_ = _scale_vector;
}

BarUI::BarUI(BarUI const& _other) : UI(_other)
{
	direction_ = _other.direction_;
	range_ = _other.range_;
	value_ = _other.value_;
	scale_vector_ = _other.scale_vector_;
}

BarUI::BarUI(BarUI&& _other) noexcept : UI(std::move(_other))
{
	direction_ = std::move(_other.direction_);
	range_ = std::move(_other.range_);
	value_ = std::move(_other.value_);
	scale_vector_ = std::move(_other.scale_vector_);
}

void BarUI::_Release()
{
}

void BarUI::_Input(float _time)
{
	auto const& input_manager = InputManager::singleton();

	if (input_manager->KeyPressed("Z"))
		AddValue(-50.f * _time);
	if (input_manager->KeyPressed("X"))
		AddValue(50.f * _time);
}

void BarUI::_Update(float _time)
{
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	auto percent = (value_ - range_.first) / (range_.second - range_.first);
	auto scale_vector = scale_vector_;

	switch (direction_)
	{
	case CUTTING_DIR::BOTTOM_TO_TOP:
		scale_vector.y *= percent;
		break;
	case CUTTING_DIR::LEFT_TO_RIGHT:
		scale_vector.x *= percent;
		break;
	case CUTTING_DIR::RIGHT_TO_LEFT:
		scale_vector.x *= percent;
		break;
	case CUTTING_DIR::TOP_TO_BOTTOM:
		scale_vector.y *= percent;
		break;
	}

	transform->Scaling(scale_vector);
}

void BarUI::_LateUpdate(float _time)
{
}

void BarUI::_Collision(float _time)
{
}

void BarUI::_Render(float _time)
{
}

std::unique_ptr<Component, std::function<void(Component*)>> BarUI::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new BarUI{ *this }, [](Component* _p) {
		dynamic_cast<BarUI*>(_p)->_Release();
		delete dynamic_cast<BarUI*>(_p);
	} };
}

void BarUI::_AfterClone()
{
}
