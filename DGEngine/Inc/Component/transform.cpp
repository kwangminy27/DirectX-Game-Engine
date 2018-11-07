#include "DGEngine_stdafx.h"
#include "transform.h"

#include "object.h"

using namespace DG;

void Transform::Initialize()
{
	try
	{
		type_ = COMPONENT_TYPE::TRANSFORM;
	}
	catch (std::exception const& _e)
	{
		std::cerr << _e.what() << std::endl;
	}
}

void Transform::Scaling(Math::Vector3 const& _v)
{
	local_scale_ = Math::Matrix::CreateScale(_v);

	update_flag_ = true;
}

void Transform::RotationX(float _radians)
{
	local_rotate_ *= Math::Matrix::CreateRotationX(_radians);

	update_flag_ = true;
}

void Transform::RotationY(float _radians)
{
	local_rotate_ *= Math::Matrix::CreateRotationY(_radians);

	update_flag_ = true;
}

void Transform::RotationZ(float _radians)
{
	local_rotate_ *= Math::Matrix::CreateRotationZ(_radians);

	update_flag_ = true;
}

void Transform::RotationRollPitchYaw(float _pitch, float _yaw, float _roll)
{
	local_rotate_ *= Math::Matrix::CreateFromRollPitchYaw(_pitch, _yaw, _roll);

	update_flag_ = true;
}

void Transform::RotationAxis(Math::Vector3 const& _axis, float _radians)
{
	local_rotate_ *= Math::Matrix::CreateFromAxisAngle(_axis, _radians);

	update_flag_ = true;
}

void Transform::Translation(Math::Vector3 const& _v)
{
	local_translate_ *= Math::Matrix::CreateTranslation(_v);

	update_flag_ = true;
}

Math::Vector3 Transform::GetLocalScale() const
{
	return Math::Vector3{ local_scale_._11, local_scale_._22, local_scale_._33 };
}

Math::Vector3 Transform::GetLocalRight() const
{
	return Math::Vector3{ local_rotate_._11, local_rotate_._12, local_rotate_._13 };
}

Math::Vector3 Transform::GetLocalUp() const
{
	return Math::Vector3{ local_rotate_._21, local_rotate_._22, local_rotate_._23 };
}

Math::Vector3 Transform::GetLocalLook() const
{
	return Math::Vector3{ local_rotate_._31, local_rotate_._32, local_rotate_._33 };
}

Math::Vector3 Transform::GetLocalTranslate() const
{
	return Math::Vector3{ local_translate_._41, local_translate_._42, local_translate_._43 };
}

Math::Vector3 Transform::GetLocalPosition() const
{
	return Math::Vector3{ local_._41, local_._42, local_._43 };
}

Math::Vector3 Transform::GetWorldScale() const
{
	return Math::Vector3{ world_scale_._11, world_scale_._22, world_scale_._33 };
}

Math::Vector3 Transform::GetWorldRight() const
{
	return Math::Vector3{ world_rotate_._11, world_rotate_._12, world_rotate_._13 };
}

Math::Vector3 Transform::GetWorldUp() const
{
	return Math::Vector3{ world_rotate_._21, world_rotate_._22, world_rotate_._23 };
}

Math::Vector3 Transform::GetWorldLook() const
{
	return Math::Vector3{ world_rotate_._31, world_rotate_._32, world_rotate_._33 };
}

Math::Vector3 DG::Transform::GetWorldTranslate() const
{
	return Math::Vector3{ world_translate_._41, world_translate_._42, world_translate_._43 };
}

Math::Vector3 Transform::GetWorldPosition() const
{
	return Math::Vector3{ world_._41, world_._42, world_._43 };
}

void Transform::SetLocalRight(Math::Vector3 const& _right)
{
	memcpy_s(&local_rotate_._11, sizeof(Math::Vector3), &_right, sizeof(Math::Vector3));

	update_flag_ = true;
}

void Transform::SetLocalUp(Math::Vector3 const& _up)
{
	memcpy_s(&local_rotate_._21, sizeof(Math::Vector3), &_up, sizeof(Math::Vector3));

	update_flag_ = true;
}

void Transform::SetLocalLook(Math::Vector3 const& _look)
{
	memcpy_s(&local_rotate_._31, sizeof(Math::Vector3), &_look, sizeof(Math::Vector3));

	update_flag_ = true;
}

void Transform::SetLocalPosition(Math::Vector3 const& _position)
{
	memcpy_s(&local_translate_._41, sizeof(Math::Vector3), &_position, sizeof(Math::Vector3));

	update_flag_ = true;
}

void Transform::LookAt(Math::Vector3 const& _position)
{
	auto direction_vector = _position - GetLocalPosition();
	direction_vector.Normalize();

	auto angle = acosf(GetLocalUp().Dot(direction_vector));
	Math::Vector3 axis = GetLocalUp().Cross(direction_vector);
	axis.Normalize();

	// 외적 연산시 문제 발생 가능 -> IsNan으로 예외처리 하거나 각도로 예외처리
	if (DirectX::XMConvertToDegrees(angle) > 0.01f)
		RotationAxis(axis, angle);
	else
		return;

	update_flag_ = true;
}

bool Transform::update_flag() const
{
	return update_flag_;
}

bool Transform::static_flag() const
{
	return static_flag_;
}

int Transform::transform_flag() const
{
	return transform_flag_;
}

Math::Matrix const& Transform::local_scale() const
{
	return local_scale_;
}

Math::Matrix const& Transform::local_rotate() const
{
	return local_rotate_;
}

Math::Matrix const& Transform::local_translate() const
{
	return local_translate_;
}

Math::Matrix const& Transform::local() const
{
	return local_;
}

Math::Matrix const& Transform::parent_scale() const
{
	return parent_scale_;
}

Math::Matrix const& Transform::parent_rotate() const
{
	return parent_rotate_;
}

Math::Matrix const& Transform::parent_translate() const
{
	return parent_translate_;
}

Math::Matrix const& Transform::parent() const
{
	return parent_;
}

Math::Matrix const& Transform::world_scale() const
{
	return world_scale_;
}

Math::Matrix const& Transform::world_rotate() const
{
	return world_rotate_;
}

Math::Matrix const& Transform::world_translate() const
{
	return world_translate_;
}

Math::Matrix const& Transform::world() const
{
	return world_;
}

Math::Vector3 const& Transform::pivot() const
{
	return pivot_;
}

void Transform::set_update_flag(bool _flag)
{
	update_flag_ = _flag;
}

void Transform::set_static_flag(bool _flag)
{
	static_flag_ = _flag;
}

void Transform::set_transform_flag(int _flag)
{
	transform_flag_ = _flag;
}

void Transform::set_parent_scale(Math::Matrix const& _scale)
{
	parent_scale_ = _scale;
}

void Transform::set_parent_rotate(Math::Matrix const& _rotate)
{
	parent_rotate_ = _rotate;
}

void Transform::set_parent_translate(Math::Matrix const& _translate)
{
	parent_translate_ = _translate;
}

void Transform::set_pivot(Math::Vector3 const& _pivot)
{
	pivot_ = _pivot;
}

Transform::Transform(Transform const& _other) : Component(_other)
{
	update_flag_ = _other.update_flag_;
	static_flag_ = _other.static_flag_;
	transform_flag_ = _other.transform_flag_;
	local_scale_ = _other.local_scale_;
	local_rotate_ = _other.local_rotate_;
	local_translate_ = _other.local_translate_;
	local_ = _other.local_;
	parent_scale_ = _other.parent_scale_;
	parent_rotate_ = _other.parent_rotate_;
	parent_translate_ = _other.parent_translate_;
	parent_ = _other.parent_;
	world_ = _other.world_;
	pivot_ = _other.pivot_;
}

Transform::Transform(Transform&& _other) noexcept : Component(std::move(_other))
{
	update_flag_ = std::move(_other.update_flag_);
	static_flag_ = std::move(_other.static_flag_);
	transform_flag_ = std::move(_other.transform_flag_);
	local_scale_ = std::move(_other.local_scale_);
	local_rotate_ = std::move(_other.local_rotate_);
	local_translate_ = std::move(_other.local_translate_);
	local_ = std::move(_other.local_);
	parent_scale_ = std::move(_other.parent_scale_);
	parent_rotate_ = std::move(_other.parent_rotate_);
	parent_translate_ = std::move(_other.parent_translate_);
	parent_ = std::move(_other.parent_);
	world_ = std::move(_other.world_);
	pivot_ = std::move(_other.pivot_);
}

void Transform::_Release()
{
}

void Transform::_Update(float _time)
{
	if (static_flag_)
		return;

	if (!update_flag_)
		return;

	local_ = local_scale_ * local_rotate_ * local_translate_;

	parent_ = Math::Matrix::Identity;

	world_scale_ = local_scale_;
	world_rotate_ = local_rotate_;
	world_translate_ = local_translate_;

	if ((transform_flag_ & static_cast<int>(TRANSFORM_FLAG::SCALE)))
	{
		world_scale_ *= parent_scale_;
		parent_ *= parent_scale_;
	}
	if ((transform_flag_ & static_cast<int>(TRANSFORM_FLAG::ROTATE)))
	{
		world_rotate_ *= parent_rotate_;
		parent_ *= parent_rotate_;
	}
	if ((transform_flag_ & static_cast<int>(TRANSFORM_FLAG::TRANSLATE)))
	{
		world_translate_ *= parent_translate_;
		parent_ *= parent_translate_;
	}

	world_ = local_ * parent_;

	update_flag_ = false;
}

void Transform::_LateUpdate(float _time)
{
	if (static_flag_)
		return;

	if (!update_flag_)
		return;

	local_ = local_scale_ * local_rotate_ * local_translate_;

	parent_ = Math::Matrix::Identity;

	world_scale_ = local_scale_;
	world_rotate_ = local_rotate_;
	world_translate_ = local_translate_;

	if ((transform_flag_ & static_cast<int>(TRANSFORM_FLAG::SCALE)))
	{
		world_scale_ *= parent_scale_;
		parent_ *= parent_scale_;
	}
	if ((transform_flag_ & static_cast<int>(TRANSFORM_FLAG::ROTATE)))
	{
		world_rotate_ *= parent_rotate_;
		parent_ *= parent_rotate_;
	}
	if ((transform_flag_ & static_cast<int>(TRANSFORM_FLAG::TRANSLATE)))
	{
		world_translate_ *= parent_translate_;
		parent_ *= parent_translate_;
	}

	world_ = local_ * parent_;

	update_flag_ = false;
}

std::unique_ptr<Component, std::function<void(Component*)>> Transform::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new Transform(*this), [](Component* _p) {
		dynamic_cast<Transform*>(_p)->_Release();
		delete dynamic_cast<Transform*>(_p);
	} };
}
