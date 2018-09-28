#include "DGClient_stdafx.h"
#include "player_component.h"

#include <object.h>
#include <Component/transform.h>
#include <Component/renderer.h>

using namespace DG;

void PlayerComponent::Initialize()
{
	auto transform = object()->AddComponent<Transform>("Transform");
	auto renderer = std::dynamic_pointer_cast<Renderer>(object()->AddComponent<Renderer>("Renderer"));

	renderer->set_shader("BasicShader");
	renderer->set_mesh("ColorTri");
}

void PlayerComponent::Input(float _time)
{
}

std::unique_ptr<Component, std::function<void(Component*)>> PlayerComponent::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new PlayerComponent{ *this }, [](Component* _p) {
		dynamic_cast<PlayerComponent*>(_p)->_Release();
		delete dynamic_cast<PlayerComponent*>(_p);
	} };
}

PlayerComponent::PlayerComponent(PlayerComponent const& _other) : UserComponent(_other)
{
}

PlayerComponent::PlayerComponent(PlayerComponent&& _other) noexcept : UserComponent(std::move(_other))
{
}

void PlayerComponent::_Release()
{
}
