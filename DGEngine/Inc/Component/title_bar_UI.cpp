#include "DGEngine_stdafx.h"
#include "title_bar_UI.h"

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

void TitleBarUI::Initialize()
{
	try
	{
		UI::Initialize();

		auto transform = std::dynamic_pointer_cast<Transform>(object()->AddComponent<Transform>("Transform"));
		auto renderer = std::dynamic_pointer_cast<Renderer>(object()->AddComponent<Renderer>("Renderer"));

		renderer->set_shader_tag(BASIC_TEX_SHADER);
		renderer->set_mesh_tag("TexRect");

		auto material = std::dynamic_pointer_cast<Material>(object()->AddComponent<Material>("Material"));

		MaterialConstantBuffer material_constant_buffer{};
		material_constant_buffer.diffuse = DirectX::Colors::White.v;

		material->SetMaterialConstantBuffer(material_constant_buffer, 0, 0);
		material->SetTexture("Button", 0, 0, 0);
		material->SetSampler(LINEAR_SAMPLER, 0, 0, 0);

		auto collider_rect = std::dynamic_pointer_cast<ColliderRect>(object()->AddComponent<ColliderRect>("TitleBarBody"));
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
		std::cout << "TitleBarUI::Initialize()" << std::endl;
	}
}

std::shared_ptr<Object> TitleBarUI::owner() const
{
	return owner_.lock();
}

bool TitleBarUI::click_flag() const
{
	return click_flag_;
}

void TitleBarUI::set_owner(std::shared_ptr<Object> const& _owner)
{
	owner_ = _owner;

	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));
	auto const& owner_transform = std::dynamic_pointer_cast<Transform>(owner()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	auto owner_scale = owner_transform->GetLocalScale();
	owner_scale.y = 20.f;

	transform->Scaling(owner_scale);

	auto position = owner_transform->GetLocalPosition() - owner_transform->GetLocalScale() * owner_transform->pivot();
	position.y += owner_transform->GetLocalScale().y;

	transform->SetLocalPosition(position);

	auto const& collider_rect = std::dynamic_pointer_cast<ColliderRect>(object()->FindComponent(COMPONENT_TYPE::COLLIDER));
	auto const& mesh = ResourceManager::singleton()->FindMesh("TexRect");
	auto extent = (mesh->max() - mesh->min()) * 0.5f * transform->GetLocalScale();

	collider_rect->set_relative_info(Math::Vector3::Zero, extent * 2.f);
}

void TitleBarUI::set_click_flag(bool _flag)
{
	click_flag_ = _flag;
}

TitleBarUI::TitleBarUI(TitleBarUI const& _other) : ButtonUI(_other)
{
	owner_ = _other.owner_;
}

TitleBarUI::TitleBarUI(TitleBarUI&& _other) noexcept : ButtonUI(std::move(_other))
{
	owner_ = std::move(_other.owner_);
}

void TitleBarUI::_Release()
{
}

void TitleBarUI::_Input(float _time)
{
	auto const& input_manager = InputManager::singleton();

	switch (button_state_)
	{
	case BUTTON_STATE::MOUSEON:
		if (input_manager->KeyPush("LButton"))
			button_state_ = BUTTON_STATE::CLICK;

		break;
	case BUTTON_STATE::CLICK:
		if (input_manager->KeyPressed("LButton"))
			callback_(_time);

		break;
	}
}

void TitleBarUI::_Update(float _time)
{
	if (owner_.expired())
	{
		object()->set_active_flag(false);
		return;
	}

	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));
	auto const& owner_transform = std::dynamic_pointer_cast<Transform>(owner()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	auto position = owner_transform->GetLocalPosition() - owner_transform->GetLocalScale() * owner_transform->pivot();
	position.y += owner_transform->GetLocalScale().y;

	transform->SetLocalPosition(position);

	auto const& collider_rect = std::dynamic_pointer_cast<ColliderRect>(object()->FindComponent(COMPONENT_TYPE::COLLIDER));
	auto const& mesh = ResourceManager::singleton()->FindMesh("TexRect");
	auto extent = (mesh->max() - mesh->min()) * 0.5f * transform->GetLocalScale();

	collider_rect->set_relative_info(Math::Vector3::Zero, extent * 2.f);
}

void TitleBarUI::_LateUpdate(float _time)
{
}

void TitleBarUI::_Collision(float _time)
{
}

void TitleBarUI::_Render(float _time)
{
}

std::unique_ptr<Component, std::function<void(Component*)>> TitleBarUI::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new TitleBarUI{ *this }, [](Component* _p) {
		dynamic_cast<TitleBarUI*>(_p)->_Release();
		delete dynamic_cast<TitleBarUI*>(_p);
	} };
}

void TitleBarUI::_AfterClone()
{
}
