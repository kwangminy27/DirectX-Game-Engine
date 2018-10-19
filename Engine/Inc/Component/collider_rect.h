#pragma once

#include "collider.h"

namespace DG
{
	class DG_ENGINE_DLL ColliderRect final : public Collider
	{
		friend class Object;
		friend class CollisionManager;
	public:
		virtual void Initialize() override;

		virtual bool Collision(Collider* _dest, float _time) override;

		RectInfo const& final_info() const;
		void set_relative_info(Math::Vector3 const& _min, Math::Vector3 const& _max);

	private:
		ColliderRect() = default;
		ColliderRect(ColliderRect const& _other);
		ColliderRect(ColliderRect&& _other) noexcept;
		ColliderRect& operator=(ColliderRect const&) = default;
		ColliderRect& operator=(ColliderRect&&) noexcept = default;

		virtual void _Release() override;

		virtual void _LateUpdate(float _time) override;
		virtual void _Render(float _time) override;
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;

		RectInfo relative_info_{};
		RectInfo final_info_{};
	};
}
