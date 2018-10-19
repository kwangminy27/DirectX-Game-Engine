#pragma once

#include <DGEngine_stdafx.h>
#include <Component/user_component.h>

namespace DG
{
	class Object;
	class Collider;

	class MissileComponent final : public UserComponent
	{
		friend class Object;
	public:
		virtual void Initialize() override;

	private:
		MissileComponent() = default;
		MissileComponent(MissileComponent const& _other);
		MissileComponent(MissileComponent&& _other) noexcept;
		MissileComponent& operator=(MissileComponent const&) = default;
		MissileComponent& operator=(MissileComponent&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Update(float _time);
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;

		void _MissileHit(Collider* _target);

		float speed_{};
		float range_{};
	};
}
