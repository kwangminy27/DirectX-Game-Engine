#pragma once

#include "component.h"

namespace DG
{
	class DG_ENGINE_DLL UserComponent : public Component
	{
	public:
		virtual void Initialize() = 0;

	protected:
		UserComponent() = default;
		UserComponent(UserComponent const& _other);
		UserComponent(UserComponent&& _other) noexcept;
		UserComponent& operator=(UserComponent const&) = default;
		UserComponent& operator=(UserComponent&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Input(float _time);
		virtual void _Update(float _time);
		virtual void _LateUpdate(float _time);
		virtual void _Collision(float _time);
		virtual void _Render(float _time);
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const = 0;
	};
}
