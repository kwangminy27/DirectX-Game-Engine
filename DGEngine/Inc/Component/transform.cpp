#include "DGEngine_stdafx.h"
#include "transform.h"

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
	scale_vector_ = _v;
	local_ *= Math::Matrix::CreateScale(_v);

	update_flag_ = true;
}

void Transform::RotationX(float _radians)
{
	Math::Vector3 position = GetLocalPosition();

	memset(&local_._41, 0, sizeof(Math::Vector3));

	local_ *= Math::Matrix::CreateRotationX(_radians);

	memcpy_s(&local_._41, sizeof(Math::Vector3), &position, sizeof(Math::Vector3));

	update_flag_ = true;
}

void Transform::RotationY(float _radians)
{
	Math::Vector3 position = GetLocalPosition();

	memset(&local_._41, 0, sizeof(Math::Vector3));

	local_ *= Math::Matrix::CreateRotationY(_radians);

	memcpy_s(&local_._41, sizeof(Math::Vector3), &position, sizeof(Math::Vector3));

	update_flag_ = true;
}

void Transform::RotationZ(float _radians)
{
	Math::Vector3 position = GetLocalPosition();

	memset(&local_._41, 0, sizeof(Math::Vector3));

	local_ *= Math::Matrix::CreateRotationZ(_radians);

	memcpy_s(&local_._41, sizeof(Math::Vector3), &position, sizeof(Math::Vector3));

	update_flag_ = true;
}

void Transform::RotationRollPitchYaw(float _pitch, float _yaw, float _roll)
{
	Math::Vector3 position = GetLocalPosition();

	memset(&local_._41, 0, sizeof(Math::Vector3));

	local_ *= Math::Matrix::CreateFromRollPitchYaw(_pitch, _yaw, _roll);

	memcpy_s(&local_._41, sizeof(Math::Vector3), &position, sizeof(Math::Vector3));

	update_flag_ = true;
}

void Transform::RotationAxis(Math::Vector3 const& _axis, float _radians)
{
	Math::Vector3 position = GetLocalPosition();

	memset(&local_._41, 0, sizeof(Math::Vector3));

	local_ *= Math::Matrix::CreateFromAxisAngle(_axis, _radians);

	memcpy_s(&local_._41, sizeof(Math::Vector3), &position, sizeof(Math::Vector3));

	update_flag_ = true;
}

void Transform::Translation(Math::Vector3 const& _v)
{
	local_ *= Math::Matrix::CreateTranslation(_v);

	update_flag_ = true;
}

Math::Vector3 Transform::scale_vector() const
{
	return scale_vector_;
}

Math::Vector3 Transform::GetLocalRight() const
{
	auto R = Math::Vector3{ local_._11, local_._12, local_._13 };

	R.Normalize();

	return R;
}

Math::Vector3 Transform::GetLocalUp() const
{
	auto R = Math::Vector3{ local_._21, local_._22, local_._23 };

	R.Normalize();

	return R;
}

Math::Vector3 Transform::GetLocalLook() const
{
	auto R = Math::Vector3{ local_._31, local_._32, local_._33 };

	R.Normalize();

	return R;
}

Math::Vector3 Transform::GetLocalPosition() const
{
	return Math::Vector3{ local_._41, local_._42, local_._43 };
}

Math::Vector3 Transform::GetWorldRight() const
{
	auto R = Math::Vector3{ world_._11, world_._12, world_._13 };

	R.Normalize();

	return R;
}

Math::Vector3 Transform::GetWorldUp() const
{
	auto R = Math::Vector3{ world_._21, world_._22, world_._23 };

	R.Normalize();

	return R;
}

Math::Vector3 Transform::GetWorldLook() const
{
	auto R = Math::Vector3{ world_._31, world_._32, world_._33 };

	R.Normalize();

	return R;
}

Math::Vector3 Transform::GetWorldPosition() const
{
	return Math::Vector3{ world_._41, world_._42, world_._43 };
}

void Transform::SetLocalRight(Math::Vector3 const& _right)
{
	auto right = _right * scale_vector_;
	memcpy_s(&local_._11, sizeof(Math::Vector3), &right, sizeof(Math::Vector3));

	update_flag_ = true;
}

void Transform::SetLocalUp(Math::Vector3 const& _up)
{
	auto up = _up * scale_vector_;
	memcpy_s(&local_._21, sizeof(Math::Vector3), &up, sizeof(Math::Vector3));

	update_flag_ = true;
}

void Transform::SetLocalLook(Math::Vector3 const& _look)
{
	auto look = _look * scale_vector_;
	memcpy_s(&local_._31, sizeof(Math::Vector3), &look, sizeof(Math::Vector3));

	update_flag_ = true;
}

void Transform::SetLocalPosition(Math::Vector3 const& _position)
{
	memcpy_s(&local_._41, sizeof(Math::Vector3), &_position, sizeof(Math::Vector3));

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

Math::Matrix const& Transform::local() const
{
	return local_;
}

Math::Matrix const& Transform::parent() const
{
	return parent_;
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

void Transform::set_local(Math::Matrix const& _local)
{
	local_ = _local;
}

void Transform::set_parent(Math::Matrix const& _parent)
{
	parent_ = _parent;
}

void Transform::set_pivot(Math::Vector3 const& _pivot)
{
	pivot_ = _pivot;
}

Transform::Transform(Transform const& _other) : Component(_other)
{
	update_flag_ = _other.update_flag_;
	static_flag_ = _other.static_flag_;
	scale_vector_ = _other.scale_vector_;
	local_ = _other.local_;
	parent_ = _other.parent_;
	world_ = _other.world_;
	pivot_ = _other.pivot_;
}

Transform::Transform(Transform&& _other) noexcept : Component(std::move(_other))
{
	update_flag_ = std::move(_other.update_flag_);
	static_flag_ = std::move(_other.static_flag_);
	scale_vector_ = std::move(_other.scale_vector_);
	local_ = std::move(_other.local_);
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

	world_ = local_ * parent_;

	update_flag_ = false;
}

void Transform::_LateUpdate(float _time)
{
	if (static_flag_)
		return;

	if (!update_flag_)
		return;

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
