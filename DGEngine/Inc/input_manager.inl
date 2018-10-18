#pragma once

template<typename T, typename ... Types>
void InputManager::_AddKey(T const& _element, Types ... _Args)
{
	if (!key_buffer_)
		key_buffer_ = std::make_unique<KeyInfo>();

	key_buffer_->element.push_back(_element);

	_AddKey(_Args...);
}

template<typename ... Types>
void InputManager::_AddKey(std::string const& _tag, Types ... _Args)
{
	if (!key_buffer_)
		key_buffer_ = std::make_unique<KeyInfo>();

	key_tag_buffer_ = _tag;

	_AddKey(_Args...);
}