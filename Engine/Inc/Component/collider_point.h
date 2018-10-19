#pragma once

#include "collider.h"

namespace DG
{
	class DG_ENGINE_DLL ColliderPoint final : public Collider
	{
		friend class Object;
		friend class CollisionManager;
		friend class InputManager;
	public:
		virtual void Initialize() override;

		virtual bool Collision(Collider* _dest, float _time) override;

		Math::Vector3 const& final_info() const;
		void set_relative_info(Math::Vector3 const& _info);

	private:
		ColliderPoint() = default;
		ColliderPoint(ColliderPoint const& _other);
		ColliderPoint(ColliderPoint&& _other) noexcept;
		ColliderPoint& operator=(ColliderPoint const&) = default;
		ColliderPoint& operator=(ColliderPoint&&) noexcept = default;

		virtual void _Release() override;

		virtual void _LateUpdate(float _time) override;
		virtual void _Render(float _time) override;
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;

		Math::Vector3 relative_info_{};
		Math::Vector3 final_info_{};
	};
}
