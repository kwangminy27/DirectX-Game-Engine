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
	local_ *= Math::Matrix::CreateScale(_v);

	update_flag_ = true;
}

void Transform::RotationX(float _radians)
{
	local_ *= Math::Matrix::CreateRotationX(_radians);

	update_flag_ = true;
}

void Transform::RotationY(float _radians)
{
	local_ *= Math::Matrix::CreateRotationY(_radians);

	update_flag_ = true;
}

void Transform::RotationZ(float _radians)
{
	local_ *= Math::Matrix::CreateRotationZ(_radians);

	update_flag_ = true;
}

void Transform::RotationRollPitchYaw(float _pitch, float _yaw, float _roll)
{
	local_ *= Math::Matrix::CreateFromRollPitchYaw(_pitch, _yaw, _roll);

	update_flag_ = true;
}

void Transform::RotationAxis(Math::Vector3 const& _axis, float _radians)
{
	local_ *= Math::Matrix::CreateFromAxisAngle(_axis, _radians);

	update_flag_ = true;
}

void Transform::Translation(Math::Vector3 const& _v)
{
	local_ *= Math::Matrix::CreateTranslation(_v);

	update_flag_ = true;
}

Math::Vector3 Transform::GetLocalRight() const
{
	return Math::Vector3{ local_._11, local_._12, local_._13 };
}

Math::Vector3 Transform::GetLocalUp() const
{
	return Math::Vector3{ local_._21, local_._22, local_._23 };
}

Math::Vector3 Transform::GetLocalLook() const
{
	return Math::Vector3{ local_._31, local_._32, local_._33 };
}

Math::Vector3 Transform::GetWorldRight() const
{
	return Math::Vector3{ world_._11, world_._12, world_._13 };
}

Math::Vector3 Transform::GetWorldUp() const
{
	return Math::Vector3{ world_._21, world_._22, world_._23 };
}

Math::Vector3 Transform::GetWorldLook() const
{
	return Math::Vector3{ world_._31, world_._32, world_._33 };
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

Transform::Transform(Transform const& _other) : Component(_other)
{
	update_flag_ = _other.update_flag_;
	static_flag_ = _other.static_flag_;
	local_ = _other.local_;
	parent_ = _other.parent_;
	world_ = _other.world_;
}

Transform::Transform(Transform&& _other) noexcept : Component(std::move(_other))
{
	update_flag_ = std::move(_other.update_flag_);
	static_flag_ = std::move(_other.static_flag_);
	local_ = std::move(_other.local_);
	parent_ = std::move(_other.parent_);
	world_ = std::move(_other.world_);
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
