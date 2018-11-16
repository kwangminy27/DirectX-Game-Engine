#pragma once

#include "component.h"

namespace DG
{
	class DG_ENGINE_DLL Camera final : public Component
	{
		friend class Scene;
		friend class Object;
	public:
		virtual void Initialize() override;

		Math::Matrix const& view() const;
		Math::Matrix const& projection() const;

		void set_camera_info(CAMERA_TYPE _type, float _angle, float _width, float _height, float _near, float _far);
		void set_camera_type(CAMERA_TYPE _type);
		void set_fov_angle(float _angle);
		void set_width(float _width);
		void set_height(float _height);
		void set_near(float _near);
		void set_far(float _far);
		void set_target(std::shared_ptr<Object> const& _target);

	private:
		Camera() = default;
		Camera(Camera const& _other);
		Camera(Camera&& _other) noexcept;
		Camera& operator=(Camera const&) = default;
		Camera& operator=(Camera&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Update(float _time) override;
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;

		void _CreateProjectionMatrix(CAMERA_TYPE _type);

		CAMERA_TYPE camera_type_{};
		Math::Matrix view_{ Math::Matrix::Identity };
		Math::Matrix projection_{};
		float fov_angle_{};
		float width_{};
		float height_{};
		float near_{};
		float far_{};
		std::weak_ptr<Object> target_{};
	};
}
