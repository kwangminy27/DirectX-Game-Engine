#pragma once

#include "collider.h"

namespace DG
{
	class DG_ENGINE_DLL ColliderCircle final : public Collider
	{
		friend class Object;
		friend class CollisionManager;
	public:
		virtual void Initialize() override;

		virtual bool Collision(Collider* _dest, float _time) override;

		CircleInfo const& final_info() const;
		void set_relative_info(Math::Vector3 const& _center, float _radius);

	private:
		ColliderCircle() = default;
		ColliderCircle(ColliderCircle const& _other);
		ColliderCircle(ColliderCircle&& _other) noexcept;
		ColliderCircle& operator=(ColliderCircle const&) = default;
		ColliderCircle& operator=(ColliderCircle&&) noexcept = default;

		virtual void _Release() override;

		virtual void _LateUpdate(float _time) override;
		virtual void _Render(float _time) override;
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;

		CircleInfo relative_info_{};
		CircleInfo final_info_{};
	};
}		
