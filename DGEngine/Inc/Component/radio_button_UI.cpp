#include "DGEngine_stdafx.h"
#include "radio_button_UI.h"

#include "Resource/resource_manager.h"
#include "Resource/mesh.h"
#include "Rendering/shader_manager.h"
#include "Rendering/rendering_manager.h"
#include "Scene/scene.h"
#include "object.h"
#include "Component/transform.h"
#include "Component/renderer.h"
#include "Component/material.h"
#include "Component/collider_rect.h"
#include "Component/camera.h"
#include "input_manager.h"

using namespace DG;

void RadioButtonUI::Initialize()
{
	try
	{
		UI::Initialize();

		auto transform = std::dynamic_pointer_cast<Transform>(object()->AddComponent<Transform>("Transform"));

		transform->Scaling({ 16.f, 16.f, 0.f });
		transform->Translation({ 400.f, 500.f, 0.f });

		transform->set_pivot({ 0.5f, 0.5f, 0.f });

		auto renderer = std::dynamic_pointer_cast<Renderer>(object()->AddComponent<Renderer>("Renderer"));

		renderer->set_shader_tag(RADIO_BUTTON_SHADER);
		renderer->set_mesh_tag("TexRect");

		auto material = std::dynamic_pointer_cast<Material>(object()->AddComponent<Material>("Material"));

		MaterialConstantBuffer material_constant_buffer{};
		material_constant_buffer.diffuse = DirectX::Colors::White.v;

		material->SetMaterialConstantBuffer(material_constant_buffer, 0, 0);
		material->SetTexture("RadioButton", 0, 0, 0);
		material->SetSampler(LINEAR_SAMPLER, 0, 0, 0);

		auto collider_rect = std::dynamic_pointer_cast<ColliderRect>(object()->AddComponent<ColliderRect>("RadioButtonUIBody"));
		auto const& mesh = ResourceManager::singleton()->FindMesh("TexRect");
		auto extent = (mesh->max() - mesh->min()) * 0.5f * transform->GetLocalScale();

		collider_rect->set_collision_group_tag("UI");
		collider_rect->set_relative_info(Math::Vector3::Zero, extent * 2.f);
		collider_rect->AddCallback([this](Collider* _src, Collider* _dest, float _time) {
			_MouseOn(_src, _dest, _time);
		}, COLLISION_CALLBACK_TYPE::ENTER);
		collider_rect->AddCallback([this](Collider* _src, Collider* _dest, float _time) {
			_MouseOff(_src, _dest, _time);
		}, COLLISION_CALLBACK_TYPE::LEAVE);
	}
	catch (std::exception const& _e)
	{
		std::cout << _e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "RadioButtonUI::Initialize()" << std::endl;
	}
}

void RadioButtonUI::UpdateConstantBuffer()
{
	ButtonConstantBuffer button_constant_buffer{};
	button_constant_buffer.color = DirectX::Colors::White.v;
	button_constant_buffer.checkbox_state = static_cast<int>(checkbox_state_);

	RenderingManager::singleton()->UpdateConstantBuffer("Button", &button_constant_buffer);
}

int RadioButtonUI::group() const
{
	return group_;
}

Math::Vector3 const& RadioButtonUI::offset() const
{
	return offset_;
}

void RadioButtonUI::set_group(int _group)
{
	group_ = _group;
}

void RadioButtonUI::set_offset(Math::Vector3 const& _offset)
{
	offset_ = _offset;
}

RadioButtonUI::RadioButtonUI(RadioButtonUI const& _other) : CheckboxUI(_other)
{
	group_ = _other.group_;
	offset_ = _other.offset_;
}

RadioButtonUI::RadioButtonUI(RadioButtonUI&& _other) noexcept : CheckboxUI(std::move(_other))
{
	group_ = std::move(_other.group_);
	offset_ = std::move(_other.offset_);
}

void RadioButtonUI::_Release()
{
}

void RadioButtonUI::_Input(float _time)
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
		{
			if (callback_)
				callback_(_time);
		}

		break;
	}
}

void RadioButtonUI::_Update(float _time)
{
	
}

void RadioButtonUI::_LateUpdate(float _time)
{
}

void RadioButtonUI::_Collision(float _time)
{
}

void RadioButtonUI::_Render(float _time)
{
}

std::unique_ptr<Component, std::function<void(Component*)>> RadioButtonUI::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new RadioButtonUI{ *this }, [](Component* _p) {
		dynamic_cast<RadioButtonUI*>(_p)->_Release();
		delete dynamic_cast<RadioButtonUI*>(_p);
	} };
}

void RadioButtonUI::_AfterClone()
{
}
