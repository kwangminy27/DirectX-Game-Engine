#include "DGEngine_stdafx.h"
#include "icon_UI.h"

#include "Resource/resource_manager.h"
#include "Resource/mesh.h"
#include "object.h"
#include "Component/transform.h"
#include "Component/renderer.h"
#include "Component/material.h"
#include "Component/collider_rect.h"
#include "input_manager.h"

using namespace DG;

void IconUI::Initialize()
{
	try
	{
		UI::Initialize();

		button_state_ = BUTTON_STATE::NORMAL;

		auto transform = std::dynamic_pointer_cast<Transform>(object()->AddComponent<Transform>("Transform"));

		transform->Scaling({ 36.f, 36.f, 1.f });

		auto renderer = std::dynamic_pointer_cast<Renderer>(object()->AddComponent<Renderer>("Renderer"));

		renderer->set_shader_tag(BASIC_TEX_SHADER);
		renderer->set_mesh_tag("TexRect");
		renderer->set_render_state(ALPHA_BLEND);

		auto material = std::dynamic_pointer_cast<Material>(object()->AddComponent<Material>("Material"));

		MaterialConstantBuffer material_constant_buffer{};
		material_constant_buffer.diffuse = DirectX::Colors::White.v;

		material->SetMaterialConstantBuffer(material_constant_buffer, 0, 0);
		material->SetTexture("Apple", 0, 0, 0);
		material->SetSampler(LINEAR_SAMPLER, 0, 0, 0);

		set_callback([this](float _time) {
			set_drag_flag(true);
		});

		auto collider_rect = std::dynamic_pointer_cast<ColliderRect>(object()->AddComponent<ColliderRect>("IconBody"));
		auto const& mesh = ResourceManager::singleton()->FindMesh("TexRect");
		auto extent = (mesh->max() - mesh->min()) * 0.5f * transform->GetLocalScale();

		collider_rect->set_collision_group_tag("UI");
		collider_rect->set_relative_info(Math::Vector3::Zero, extent * 2.f);
		collider_rect->AddSkipTag("SlotBody");

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
		std::cout << "IconUI::Initialize" << std::endl;
	}
}

void IconUI::AddSlot(std::shared_ptr<Object> const& _slot)
{
	slot_list_.push_back(_slot);
}

std::shared_ptr<Object> IconUI::current_slot() const
{
	return current_slot_.lock();
}

void IconUI::set_current_slot(std::weak_ptr<Object> const& _slot)
{
	current_slot_ = _slot;
}

bool IconUI::drag_flag() const
{
	return drag_flag_;
}

void IconUI::set_drag_flag(bool _flag)
{
	drag_flag_ = _flag;
}

IconUI::IconUI(IconUI const& _other) : ButtonUI(_other)
{
	slot_list_ = _other.slot_list_;
	drag_flag_ = _other.drag_flag_;
	current_slot_ = _other.current_slot_;
}


IconUI::IconUI(IconUI&& _other) noexcept : ButtonUI(std::move(_other))
{
	slot_list_ = std::move(_other.slot_list_);
	drag_flag_ = std::move(_other.drag_flag_);
	current_slot_ = std::move(_other.current_slot_);
}

void IconUI::_Release()
{	 
}	 
	 
void IconUI::_Input(float _time)
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
			if(!drag_flag_)
				callback_(_time);
			else
			{
				auto const& mouse_client_position = InputManager::singleton()->mouse_client_position();

				for (auto iter = slot_list_.begin(); iter != slot_list_.end(); ++iter)
				{
					auto const& slot_transform = std::dynamic_pointer_cast<Transform>((*iter).lock()->FindComponent(COMPONENT_TYPE::TRANSFORM));
					auto const& slot_position = slot_transform->GetLocalPosition();
					auto const& slot_scale = slot_transform->GetLocalScale();

					if (mouse_client_position.x < slot_position.x || mouse_client_position.x > slot_position.x + slot_scale.x)
						continue;
					if (mouse_client_position.y < slot_position.y || mouse_client_position.y > slot_position.y + slot_scale.y)
						continue;

					set_current_slot(*iter);
					button_state_ = BUTTON_STATE::MOUSEON;
					drag_flag_ = false;

					break;
				}
			}
		}

		break;
	}
}
	 
void IconUI::_Update(float _time)
{
	if (current_slot_.expired())
		object()->set_active_flag(false);

	auto const& input_manager = InputManager::singleton();
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));
	auto const& slot_transform = std::dynamic_pointer_cast<Transform>(current_slot()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	if (drag_flag_)
		transform->Translation(input_manager->mouse_displacement());
	else
		transform->SetLocalPosition(slot_transform->GetLocalPosition());
}	 
	 
void IconUI::_LateUpdate(float _time)
{	 
}	 
	 
void IconUI::_Collision(float _time)
{	 
}	 
	 
void IconUI::_Render(float _time)
{
}

std::unique_ptr<Component, std::function<void(Component*)>> IconUI::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new IconUI{ *this }, [](Component* _p) {
		dynamic_cast<IconUI*>(_p)->_Release();
		delete dynamic_cast<IconUI*>(_p);
	} };
}

void IconUI::_AfterClone()
{
}
