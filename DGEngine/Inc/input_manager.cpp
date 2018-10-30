#include "DGEngine_stdafx.h"
#include "input_manager.h"

#include "core.h"
#include "Scene/scene_manager.h"
#include "object.h"
#include "collision_manager.h"
#include "Component/transform.h"
#include "Component/renderer.h"
#include "Component/material.h"
#include "Component/collider_point.h"

using namespace DG;

std::unique_ptr<KeyInfo> InputManager::key_nullptr_;

void InputManager::Initialize()
{
	try
	{
		_AddKey("MoveUp"s, 'W');
		_AddKey("MoveDown"s, 'S');
		_AddKey("MoveLeft"s, 'A');
		_AddKey("MoveRight"s, 'D');

		_AddKey("LButton"s, VK_LBUTTON);

		_AddKey("Space"s, VK_SPACE);

		_AddKey("Pause"s, VK_F1);

		mouse_ = Object::CreateObject("Mouse", nullptr);

		auto transform = std::dynamic_pointer_cast<Transform>(mouse_->AddComponent<Transform>("Transform"));

		transform->Scaling(Math::Vector3{ 32.f, 31.f, 1.f });
		transform->set_pivot(Math::Vector3{ 0.f, 1.f, 0.f });

		auto renderer = std::dynamic_pointer_cast<Renderer>(mouse_->AddComponent<Renderer>("Renderer"));

		renderer->set_shader_tag(BASIC_TEX_SHADER);
		renderer->set_mesh_tag("TexRect");
		renderer->set_render_state(ALPHA_BLEND);

		auto material = std::dynamic_pointer_cast<Material>(mouse_->AddComponent<Material>("Material"));

		MaterialConstantBuffer material_constant_buffer{};
		material_constant_buffer.diffuse = DirectX::Colors::White.v;

		material->SetMaterialConstantBuffer(material_constant_buffer, 0, 0);
		material->SetTexture("Mouse", 0, 0, 0);
		material->SetSampler(LINEAR_SAMPLER, 0, 0, 0);

		auto mouse_ui_collider = std::dynamic_pointer_cast<ColliderPoint>(mouse_->AddComponent<ColliderPoint>("MouseUICollider"));
		mouse_ui_collider->set_collision_group_tag("UI");

		auto mouse_world_collider = mouse_->AddComponent<ColliderPoint>("MouseWorldCollider");

		auto scene = SceneManager::singleton()->scene();

		mouse_->set_scene(scene);
		for (auto const& _component : mouse_->component_list_)
			_component->set_scene(scene);

		ShowCursor(false);
	}
	catch (std::exception const& _e)
	{
		cout << _e.what() << endl;
	}
	catch (...)
	{
		cout << "InputManager::Initialize()" << endl;
	}
}

void InputManager::Update()
{
	// Keyboard
	for (auto const& key : key_map_)
	{
		int count{};
		for (auto const& value : key.second->element)
		{
			if (GetAsyncKeyState(value) & 0x8000)
				++count;
		}

		if (count == key.second->element.size())
		{
			if (!key.second->pressed)
			{
				key.second->push = true;
				key.second->pressed = true;
			}
			else
				key.second->push = false;
		}
		else if (key.second->pressed)
		{
			key.second->push = false;
			key.second->pressed = false;
			key.second->up = true;
		}
		else if (key.second->up)
			key.second->up = false;
	}

	// Mouse
	POINT position{};
	GetCursorPos(&position);
	ScreenToClient(Core::singleton()->window(), &position);

	RECT rc{};
	GetClientRect(Core::singleton()->window(), &rc);

	position.y = rc.bottom - position.y; // 원점을 좌상단에서 좌하단으로

	mouse_displacement_.x = static_cast<float>(position.x) - mouse_client_position_.x;
	mouse_displacement_.y = static_cast<float>(position.y) - mouse_client_position_.y;

	Math::Vector3 client_to_game_resolution_ratio{ static_cast<float>(RESOLUTION::WIDTH) / rc.right, static_cast<float>(RESOLUTION::HEIGHT) / rc.bottom, 1.f };

	mouse_client_position_ = Math::Vector3{ static_cast<float>(position.x), static_cast<float>(position.y), 1.f } * client_to_game_resolution_ratio;
	
	auto const& camera = SceneManager::singleton()->scene()->main_camera();
	mouse_world_position_ = mouse_client_position_ + std::dynamic_pointer_cast<Transform>(camera->FindComponent(COMPONENT_TYPE::TRANSFORM))->GetWorldPosition();

	auto const& mouse_transform = std::dynamic_pointer_cast<Transform>(mouse_->FindComponent(COMPONENT_TYPE::TRANSFORM));
	mouse_transform->SetLocalPosition(mouse_client_position_);

	if (!mouse_cursor_show_state_ && mouse_client_position_.x <= 0.f && mouse_client_position_.x >= static_cast<float>(RESOLUTION::WIDTH) && mouse_client_position_.y <= 0.f && mouse_client_position_.y >= static_cast<float>(RESOLUTION::HEIGHT))
	{
		mouse_cursor_show_state_ = true;
		ShowCursor(true);
	}
	else if (mouse_cursor_show_state_ && mouse_client_position_.x > 0.f && mouse_client_position_.x < static_cast<float>(RESOLUTION::WIDTH) && mouse_client_position_.y > 0.f && mouse_client_position_.y < static_cast<float>(RESOLUTION::HEIGHT))
	{
		mouse_cursor_show_state_ = false;
		ShowCursor(false);
	}
}

void InputManager::LateUpdate(float _time)
{
	auto const& mouse_ui_collider = std::dynamic_pointer_cast<ColliderPoint>(mouse_->FindComponent("MouseUICollider"));
	auto const& mouse_world_collider = std::dynamic_pointer_cast<ColliderPoint>(mouse_->FindComponent("MouseWorldCollider"));

	mouse_ui_collider->_LateUpdate(_time);
	mouse_world_collider->_LateUpdate(_time);
}

void InputManager::Render(float _time)
{
	auto mouse_transform = std::dynamic_pointer_cast<Transform>(mouse_->FindComponent(COMPONENT_TYPE::TRANSFORM));
	mouse_transform->_Update(_time);

	mouse_->_Render(_time);
}

void InputManager::UpdateMouseColliderPosition()
{
	auto const& camera_transform = std::dynamic_pointer_cast<Transform>(SceneManager::singleton()->scene()->main_camera()->FindComponent(COMPONENT_TYPE::TRANSFORM));
	auto const& mouse_world_collider = std::dynamic_pointer_cast<ColliderPoint>(mouse_->FindComponent("MouseWorldCollider"));

	mouse_world_collider->set_relative_info(camera_transform->GetLocalPosition());
}

bool InputManager::KeyPush(std::string const& _tag) const
{
	return _FindKey(_tag)->push;
}

bool InputManager::KeyPressed(std::string const& _tag) const
{
	return _FindKey(_tag)->pressed;
}

bool InputManager::KeyUp(std::string const& _tag) const
{
	return _FindKey(_tag)->up;
}

std::shared_ptr<Object> const& InputManager::mouse() const
{
	return mouse_;
}

Math::Vector3 const& InputManager::mouse_client_position() const
{
	return mouse_client_position_;
}

Math::Vector3 const& InputManager::mouse_world_position() const
{
	return mouse_world_position_;
}

Math::Vector3 const& InputManager::mouse_displacement() const
{
	return mouse_displacement_;
}

void InputManager::_Release()
{
}

void InputManager::_AddKey()
{
	key_map_.insert(make_pair(move(key_tag_buffer_), move(key_buffer_)));
}

std::unique_ptr<KeyInfo> const& InputManager::_FindKey(std::string const& _tag) const
{
	auto iter = key_map_.find(_tag);

	if (iter == key_map_.end())
		return key_nullptr_;

	return iter->second;
}
