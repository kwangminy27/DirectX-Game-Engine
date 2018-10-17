#pragma once

#include <DGEngine_stdafx.h>
#include <Component/user_component.h>

namespace DG
{
	class MissileComponent : public UserComponent
	{
		friend class Object;
	public:
		virtual void Initialize() override;

	protected:
		MissileComponent() = default;
		MissileComponent(MissileComponent const& _other);
		MissileComponent(MissileComponent&& _other) noexcept;
		MissileComponent& operator=(MissileComponent const&) = default;
		MissileComponent& operator=(MissileComponent&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Update(float _time) override;
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;

		float range_{};
	};
}
