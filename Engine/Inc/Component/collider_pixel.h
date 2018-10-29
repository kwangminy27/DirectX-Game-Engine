#pragma once

#include "collider.h"

namespace DG
{
	class DG_ENGINE_DLL ColliderPixel final : public Collider
	{
	public:
		friend class Object;
		friend class CollisionManager;
	public:
		virtual void Initialize() override;

		virtual bool Collision(Collider* _dest, float _time) override;

		PixelInfo const& final_info() const;
		void set_relative_info(std::string const& _tag, Math::Vector3 const& _min, Math::Vector3 const& _max);

	private:
		ColliderPixel() = default;
		ColliderPixel(ColliderPixel const& _other);
		ColliderPixel(ColliderPixel&& _other) noexcept;
		ColliderPixel& operator=(ColliderPixel const&) = default;
		ColliderPixel& operator=(ColliderPixel&&) noexcept = default;

		virtual void _Release() override;

		virtual void _LateUpdate(float _time) override;
		virtual void _Render(float _time) override;
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;

		PixelInfo relative_info_{};
		PixelInfo final_info_{};
	};
}
