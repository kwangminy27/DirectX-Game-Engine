#pragma once

#include "component.h"

namespace DG
{
	class DG_ENGINE_DLL Collider : public Component
	{
		friend class Object;
	public:
		virtual void Initialize() override;

	protected:
		Collider() = default;
		Collider(Collider const& _other);
		Collider(Collider&& _other) noexcept;
		Collider& operator=(Collider const&) = default;
		Collider& operator=(Collider&&) noexcept = default;

		virtual void _Release() override;

		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;
	};
}
