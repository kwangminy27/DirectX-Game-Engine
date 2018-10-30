#include "DGEngine_stdafx.h"
#include "checkbox_UI.h"

#include "object.h"
#include "Component/transform.h"
#include "Component/renderer.h"
#include "Component/material.h"
#include "Component/collider_rect.h"
#include "Resource/resource_manager.h"
#include "Resource/mesh.h"
#include "input_manager.h"
#include "Rendering/rendering_manager.h"

using namespace DG;

void CheckboxUI::Initialize()
{
	try
	{
		UI::Initialize();

		auto transform = std::dynamic_pointer_cast<Transform>(object()->AddComponent<Transform>("Transform"));
		
		transform->Scaling({ 16.f, 16.f, 0.f });
		transform->Translation({ 100.f, 500.f, 0.f });
		
		transform->set_pivot({ 0.5f, 0.5f, 0.f });

		auto renderer = std::dynamic_pointer_cast<Renderer>(object()->AddComponent<Renderer>("Renderer"));

		renderer->set_shader_tag(CHECKBOX_SHADER);
		renderer->set_mesh_tag("TexRect");

		auto material = std::dynamic_pointer_cast<Material>(object()->AddComponent<Material>("Material"));

		MaterialConstantBuffer material_constant_buffer{};
		material_constant_buffer.diffuse = DirectX::Colors::White.v;

		material->SetMaterialConstantBuffer(material_constant_buffer, 0, 0);
		material->SetTexture("Checkbox", 0, 0, 0);
		material->SetSampler(LINEAR_SAMPLER, 0, 0, 0);

		auto collider_rect = std::dynamic_pointer_cast<ColliderRect>(object()->AddComponent<ColliderRect>("CheckboxBody"));
		auto const& mesh = ResourceManager::singleton()->FindMesh("TexRect");
		auto extent = (mesh->max() - mesh->min()) * 0.5f * transform->scale_vector();

		collider_rect->set_collision_group_tag("UI");
		collider_rect->set_relative_info(Math::Vector3::Zero, extent * 2.f);
		collider_rect->AddCallback([this](Collider* _src, Collider* _dest, float _time) {
			_Hit(_src, _dest, _time);
		}, COLLISION_CALLBACK_TYPE::ENTER);
		collider_rect->AddCallback([this](Collider* _src, Collider* _dest, float _time) {
			_MouseOut(_src, _dest, _time);
		}, COLLISION_CALLBACK_TYPE::LEAVE);

	}
	catch (std::exception const& _e)
	{
		std::cout << _e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "CheckboxUI::Initialize()" << std::endl;
	}
}

void CheckboxUI::UpdateConstantBuffer()
{
	ButtonConstantBuffer button_constant_buffer{};
	button_constant_buffer.color = DirectX::Colors::White.v;
	button_constant_buffer.checkbox_state = static_cast<int>(checkbox_state_);

	RenderingManager::singleton()->UpdateConstantBuffer("Button", &button_constant_buffer);
}

CHECKBOX_STATE CheckboxUI::checkbox_state() const
{
	return checkbox_state_;
}

void CheckboxUI::set_checkbox_state(CHECKBOX_STATE _state)
{
	checkbox_state_ = _state;
}

CheckboxUI::CheckboxUI(CheckboxUI const& _other) : ButtonUI(_other)
{
	checkbox_state_ = _other.checkbox_state_;
}

CheckboxUI::CheckboxUI(CheckboxUI&& _other) noexcept : ButtonUI(std::move(_other))
{
	checkbox_state_ = std::move(_other.checkbox_state_);
}

void CheckboxUI::_Release()
{
}

void CheckboxUI::_Input(float _time)
{
	auto const& input_manager = InputManager::singleton();

	switch (button_state_)
	{
	case BUTTON_STATE::MOUSEON:
		if (input_manager->KeyPush("LButton"))
			checkbox_state_ = checkbox_state_ == CHECKBOX_STATE::NORMAL ? CHECKBOX_STATE::CHECKED : CHECKBOX_STATE::NORMAL;

		break;
	}
}

void CheckboxUI::_Update(float _time)
{
}

void CheckboxUI::_LateUpdate(float _time)
{
}

void CheckboxUI::_Collision(float _time)
{
}

void CheckboxUI::_Render(float _time)
{
}

std::unique_ptr<Component, std::function<void(Component*)>> CheckboxUI::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new CheckboxUI{ *this }, [](Component* _p) {
		dynamic_cast<CheckboxUI*>(_p)->_Release();
		delete dynamic_cast<CheckboxUI*>(_p);
	} };
}

void CheckboxUI::_AfterClone()
{
}
