#include "DGEngine_stdafx.h"
#include "button_UI.h"

#include "Resource/resource_manager.h"
#include "Resource/mesh.h"
#include "Rendering/rendering_manager.h"
#include "object.h"
#include "Component/transform.h"
#include "Component/renderer.h"
#include "Component/material.h"
#include "Component/collider_rect.h"
#include "input_manager.h"
#include "Component/collider.h"

using namespace DG;

void ButtonUI::Initialize()
{
	try
	{
		UI::Initialize();

		button_state_ = BUTTON_STATE::NORMAL;
		color_array_.at(static_cast<int>(BUTTON_STATE::DISABLE)) = DirectX::Colors::Gray.v;
		color_array_.at(static_cast<int>(BUTTON_STATE::NORMAL)) = DirectX::Colors::Red.v;
		color_array_.at(static_cast<int>(BUTTON_STATE::MOUSEON)) = DirectX::Colors::Green.v;
		color_array_.at(static_cast<int>(BUTTON_STATE::CLICK)) = DirectX::Colors::Blue.v;

		// Component
		auto transform = std::dynamic_pointer_cast<Transform>(object()->AddComponent<Transform>("Transform"));

		transform->Scaling(Math::Vector3{ 120.f, 69.f, 1.f });
		transform->Translation({ static_cast<float>(RESOLUTION::WIDTH) * 0.5f, static_cast<float>(RESOLUTION::HEIGHT) * 0.5, 0.f });

		transform->set_pivot(Math::Vector3{ 0.5f, 0.5f, 0.f });

		auto renderer = std::dynamic_pointer_cast<Renderer>(object()->AddComponent<Renderer>("Renderer"));

		renderer->set_shader_tag(BUTTON_SHADER);
		renderer->set_mesh_tag("TexRect");
		renderer->set_render_state(ALPHA_BLEND);

		auto material = std::dynamic_pointer_cast<Material>(object()->AddComponent<Material>("Material"));

		MaterialConstantBuffer material_constant_buffer{};
		material_constant_buffer.diffuse = DirectX::Colors::White.v;

		material->SetMaterialConstantBuffer(material_constant_buffer, 0, 0);
		material->SetTexture("StartButton", 0, 0, 0);
		material->SetSampler(LINEAR_SAMPLER, 0, 0, 0);

		auto collider_rect = std::dynamic_pointer_cast<ColliderRect>(object()->AddComponent<ColliderRect>("ButtonBody"));
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
		std::cout << "ButtonUI::Initialize()" << std::endl;
	}
}

void ButtonUI::UpdateConstantBuffer()
{
	RenderingManager::singleton()->UpdateConstantBuffer("Button", &color_array_.at(static_cast<int>(button_state_)));
}

void ButtonUI::Enable()
{
	button_state_ = BUTTON_STATE::NORMAL;
}

void ButtonUI::Disable()
{
	button_state_ = BUTTON_STATE::DISABLE;
}

BUTTON_STATE ButtonUI::button_state() const
{
	return button_state_;
}

void ButtonUI::set_button_state(BUTTON_STATE _state)
{
	button_state_ = _state;
}

void ButtonUI::set_callback(std::function<void(float)> const& _function)
{
	callback_ = _function;
}

ButtonUI::ButtonUI(ButtonUI const& _other) : UI(_other)
{
	button_state_ = _other.button_state_;
	callback_ = _other.callback_;

	memcpy_s(color_array_.data(), sizeof(Math::Vector4) * color_array_.size(), _other.color_array_.data(), sizeof(Math::Vector4) * color_array_.size());
}

ButtonUI::ButtonUI(ButtonUI&& _other) noexcept : UI(std::move(_other))
{
	button_state_ = std::move(_other.button_state_);
	callback_ = std::move(_other.callback_);
	color_array_ = std::move(_other.color_array_);
}

void ButtonUI::_Release()
{
}

void ButtonUI::_Input(float _time)
{
	auto const& input_manager = InputManager::singleton();

	switch (button_state_)
	{
	case BUTTON_STATE::MOUSEON:
		if (input_manager->KeyPush("LButton"))
			button_state_ = BUTTON_STATE::CLICK;

		break;
	case BUTTON_STATE::CLICK:
		if (input_manager->KeyUp("LButton"))
			callback_(_time);

		break;
	}
}

void ButtonUI::_Update(float _time)
{
}

void ButtonUI::_LateUpdate(float _time)
{
}

void ButtonUI::_Collision(float _time)
{
}

void ButtonUI::_Render(float _time)
{
}

std::unique_ptr<Component, std::function<void(Component*)>> ButtonUI::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new ButtonUI{ *this }, [](Component* _p) {
		dynamic_cast<ButtonUI*>(_p)->_Release();
		delete dynamic_cast<ButtonUI*>(_p);
	} };
}

void ButtonUI::_AfterClone()
{
}

void ButtonUI::_Hit(Collider* _src, Collider* _dest, float _time)
{
	if (_dest->tag() == "MouseUICollider" || _src->tag() == "MouseUICollider")
		button_state_ = BUTTON_STATE::MOUSEON;
}

void ButtonUI::_MouseOut(Collider* _src, Collider* _dest, float _time)
{
	if (_dest->tag() == "MouseUICollider" || _src->tag() == "MouseUICollider")
		button_state_ = BUTTON_STATE::NORMAL;
}
