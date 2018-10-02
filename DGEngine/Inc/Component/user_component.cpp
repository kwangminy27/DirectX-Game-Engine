#include "DGEngine_stdafx.h"
#include "user_component.h"

using namespace DG;

UserComponent::UserComponent(UserComponent const& _other) : Component(_other)
{
}

UserComponent::UserComponent(UserComponent&& _other) noexcept : Component(std::move(_other))
{
}

void UserComponent::_Release()
{
}

void UserComponent::_Input(float _time)
{
}

void UserComponent::_Update(float _time)
{
}

void UserComponent::_LateUpdate(float _time)
{
}

void UserComponent::_Collision(float _time)
{
}

void UserComponent::_Render(float _time)
{
}
