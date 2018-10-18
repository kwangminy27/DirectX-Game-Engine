#include "DGEngine_stdafx.h"
#include "input_manager.h"

#include "core.h"
#include "Scene/scene_manager.h"
#include "object.h"
#include "Component/transform.h"

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

		_AddKey("Space"s, VK_SPACE);

		mouse_ = Object::CreateObject("Mouse", nullptr);
		mouse_->AddComponent<Transform>("Transform");
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

	mouse_displacement_.x = static_cast<float>(position.x) - mouse_client_position_.x;
	mouse_displacement_.y = static_cast<float>(position.y) - mouse_client_position_.y;

	mouse_client_position_ = { static_cast<float>(position.x), static_cast<float>(position.y), 0.f };
	
	auto const& camera = SceneManager::singleton()->scene()->main_camera();
	mouse_world_position_ = mouse_client_position_ + std::dynamic_pointer_cast<Transform>(camera->FindComponent(COMPONENT_TYPE::TRANSFORM))->GetWorldPosition();

	auto const& mouse_transform = std::dynamic_pointer_cast<Transform>(mouse_->FindComponent(COMPONENT_TYPE::TRANSFORM));
	mouse_transform->Translation(mouse_client_position_);

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

void InputManager::Render(float _time)
{
	mouse_->_Render(_time);
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
