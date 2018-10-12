#include "DGEngine_stdafx.h"
#include "collider.h"

using namespace DG;

void Collider::Initialize()
{
}

Collider::Collider(Collider const& _other) : Component(_other)
{
}

Collider::Collider(Collider&& _other) noexcept : Component(std::move(_other))
{
}

void Collider::_Release()
{
}

std::unique_ptr<Component, std::function<void(Component*)>> Collider::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new Collider{ *this }, [](Component* _p) {
		dynamic_cast<Collider*>(_p)->_Release();
		delete dynamic_cast<Collider*>(_p);
	} };
}
