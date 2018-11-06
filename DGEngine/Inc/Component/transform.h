#pragma once

#include "component.h"

namespace DG
{
	class DG_ENGINE_DLL Transform final : public Component
	{
		friend class Object;
		friend class InputManager;
	public:
		virtual void Initialize() override;

		void Scaling(Math::Vector3 const& _v);
		void RotationX(float _radians);
		void RotationY(float _radians);
		void RotationZ(float _radians);
		void RotationRollPitchYaw(float _pitch, float _yaw, float _roll);
		void RotationAxis(Math::Vector3 const& _axis, float _radians);
		void Translation(Math::Vector3 const& _v);

		Math::Vector3 GetLocalScale() const;
		Math::Vector3 GetLocalRight() const;
		Math::Vector3 GetLocalUp() const;
		Math::Vector3 GetLocalLook() const;
		Math::Vector3 GetLocalPosition() const;

		Math::Vector3 GetWorldScale() const;
		Math::Vector3 GetWorldRight() const;
		Math::Vector3 GetWorldUp() const;
		Math::Vector3 GetWorldLook() const;
		Math::Vector3 GetWorldPosition() const;

		void SetLocalRight(Math::Vector3 const& _right);
		void SetLocalUp(Math::Vector3 const& _up);
		void SetLocalLook(Math::Vector3 const& _look);
		void SetLocalPosition(Math::Vector3 const& _position);

		void LookAt(Math::Vector3 const& _position);

		bool update_flag() const;
		bool static_flag() const;
		int transform_flag() const;
		Math::Matrix const& local_scale() const;
		Math::Matrix const& local_rotate() const;
		Math::Matrix const& local_translate() const;
		Math::Matrix const& local() const;
		Math::Matrix const& parent_scale() const;
		Math::Matrix const& parent_rotate() const;
		Math::Matrix const& parent_translate() const;
		Math::Matrix const& parent() const;
		Math::Matrix const& world() const;
		Math::Vector3 const& pivot() const;

		void set_update_flag(bool _flag);
		void set_static_flag(bool _flag);
		void set_transform_flag(int _flag);
		void set_parent_scale(Math::Matrix const& _scale);
		void set_parent_rotate(Math::Matrix const& _rotate);
		void set_parent_translate(Math::Matrix const& _translate);
		void set_pivot(Math::Vector3 const& _pivot);

	private:
		Transform() = default;
		Transform(Transform const& _other);
		Transform(Transform&& _other) noexcept;
		Transform& operator=(Transform const&) = default;
		Transform& operator=(Transform&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Update(float _time) override;
		virtual void _LateUpdate(float _time) override;
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;

		bool update_flag_{ true };
		bool static_flag_{};
		int transform_flag_{};
		Math::Matrix local_scale_{ Math::Matrix::Identity };
		Math::Matrix local_rotate_{ Math::Matrix::Identity };
		Math::Matrix local_translate_{ Math::Matrix::Identity };
		Math::Matrix local_{ Math::Matrix::Identity };
		Math::Matrix parent_scale_{ Math::Matrix::Identity };
		Math::Matrix parent_rotate_{ Math::Matrix::Identity };
		Math::Matrix parent_translate_{ Math::Matrix::Identity };
		Math::Matrix parent_{ Math::Matrix::Identity };
		Math::Matrix world_scale_{ Math::Matrix::Identity };
		Math::Matrix world_rotate_{ Math::Matrix::Identity };
		Math::Matrix world_translate_{ Math::Matrix::Identity };
		Math::Matrix world_{ Math::Matrix::Identity };
		Math::Vector3 pivot_{};
	};
}
