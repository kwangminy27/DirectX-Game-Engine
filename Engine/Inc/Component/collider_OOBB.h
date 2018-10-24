#pragma once

#include "collider.h"

namespace DG
{
	class DG_ENGINE_DLL ColliderOOBB final : public Collider
	{
		friend class Object;
		friend class CollisionManager;
	public:
		virtual void Initialize() override;
		virtual bool Collision(Collider* _dest, float _time) override;

		Math::Vector3 GetRight();
		Math::Vector3 GetUp();
		Math::Vector3 GetLook();

		OOBBInfo const& relative_info() const;
		OOBBInfo const& final_info() const;

		void set_relative_info(Math::Vector3 const& _center, Math::Vector3 const& _extent, Math::Matrix const& _rotation);

	private:
		ColliderOOBB() = default;
		ColliderOOBB(ColliderOOBB const& _other);
		ColliderOOBB(ColliderOOBB&& _other) noexcept;
		ColliderOOBB& operator=(ColliderOOBB const&) = default;
		ColliderOOBB& operator=(ColliderOOBB&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Update(float _time) override;
		virtual void _LateUpdate(float _time) override;
		virtual void _Render(float _time) override;
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;

		OOBBInfo relative_info_{};
		OOBBInfo final_info_{};
	};
}
