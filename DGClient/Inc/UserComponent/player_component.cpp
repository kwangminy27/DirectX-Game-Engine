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

PlayerComponent::PlayerComponent(PlayerComponent const& _other) : UserComponent(_other)
{
}

PlayerComponent::PlayerComponent(PlayerComponent&& _other) noexcept : UserComponent(std::move(_other))
{
}

void PlayerComponent::_Release()
{
}

void PlayerComponent::_Input(float _time)
{
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	if (GetAsyncKeyState('A') & 0x8000)
		transform->RotationZ(DirectX::XMConvertToRadians(180.f * _time));
	if (GetAsyncKeyState('D') & 0x8000)
		transform->RotationZ(DirectX::XMConvertToRadians(-180.f * _time));
	if (GetAsyncKeyState('S') & 0x8000)
		transform->Translation(transform->GetLocalUp() * -20.f * _time);
	if (GetAsyncKeyState('W') & 0x8000)
		transform->Translation(transform->GetLocalUp() * 20.f * _time);
}

std::unique_ptr<Component, std::function<void(Component*)>> PlayerComponent::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new PlayerComponent{ *this }, [](Component* _p) {
		dynamic_cast<PlayerComponent*>(_p)->_Release();
		delete dynamic_cast<PlayerComponent*>(_p);
	} };
}
