#pragma once

#include "component.h"

namespace DG
{
	class DG_ENGINE_DLL UserComponent : public Component
	{
	public:
		virtual void Initialize() = 0;
		virtual void Input(float _time);
		virtual void Update(float _time);
		virtual void LateUpdate(float _time);
		virtual void Collision(float _time);
		virtual void Render(float _time);
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const = 0;

	protected:
		UserComponent() = default;
		UserComponent(UserComponent const& _other);
		UserComponent(UserComponent&& _other) noexcept;
		UserComponent& operator=(UserComponent const&) = default;
		UserComponent& operator=(UserComponent&&) noexcept = default;

		virtual void _Release() override;
	};
}
