#include "DGEngine_stdafx.h"
#include "user_component.h"

using namespace DG;

void UserComponent::Input(float _time)
{
}

void UserComponent::Update(float _time)
{
}

void UserComponent::LateUpdate(float _time)
{
}

void UserComponent::Collision(float _time)
{
}

void UserComponent::Render(float _time)
{
}

UserComponent::UserComponent(UserComponent const& _other) : Component(_other)
{
}

UserComponent::UserComponent(UserComponent&& _other) noexcept : Component(std::move(_other))
{
}

void UserComponent::_Release()
{
}
