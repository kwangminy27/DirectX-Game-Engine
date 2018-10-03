#include "DGEngine_stdafx.h"
#include "camera.h"

#include "object.h"
#include "Component/transform.h"

using namespace DG;

void Camera::Initialize()
{
	type_ = COMPONENT_TYPE::CAMERA;
}

Math::Matrix const& Camera::view() const
{
	return view_;
}

Math::Matrix const& Camera::projection() const
{
	return projection_;
}

void Camera::set_camera_info(CAMERA_TYPE _type, float _angle, float _width, float _height, float _near, float _far)
{
	camera_type_ = _type;
	fov_angle_ = _angle;
	width_ = _width;
	height_ = _height;
	near_ = _near;
	far_ = _far;

	_CreateProjectionMatrix(camera_type_);
}

void Camera::set_camera_type(CAMERA_TYPE _type)
{
	camera_type_ = _type;

	_CreateProjectionMatrix(camera_type_);
}

void Camera::set_fov_angle(float _angle)
{
	fov_angle_ = _angle;

	_CreateProjectionMatrix(camera_type_);
}

void Camera::set_width(float _width)
{
	width_ = _width;

	_CreateProjectionMatrix(camera_type_);
}

void Camera::set_height(float _height)
{
	height_ = _height;

	_CreateProjectionMatrix(camera_type_);
}

void Camera::set_near(float _near)
{
	near_ = _near;

	_CreateProjectionMatrix(camera_type_);
}

void Camera::set_far(float _far)
{
	far_ = _far;

	_CreateProjectionMatrix(camera_type_);
}

Camera::Camera(Camera const& _other) : Component(_other)
{
	camera_type_ = _other.camera_type_;
	view_ = _other.view_;
	projection_ = _other.projection_;
	fov_angle_ = _other.fov_angle_;
	width_ = _other.width_;
	height_ = _other.height_;
	near_ = _other.near_;
	far_ = _other.far_;
}

Camera::Camera(Camera&& _other) noexcept : Component(std::move(_other))
{
	camera_type_ = std::move(_other.camera_type_);
	view_ = std::move(_other.view_);
	projection_ = std::move(_other.projection_);
	fov_angle_ = std::move(_other.fov_angle_);
	width_ = std::move(_other.width_);
	height_ = std::move(_other.height_);
	near_ = std::move(_other.near_);
	far_ = std::move(_other.far_);
}

void Camera::_Release()
{
}

void Camera::_Update(float _time)
{
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	memcpy_s(&view_._41, sizeof(Math::Vector3), &transform->local()._41, sizeof(Math::Vector3));
	view_._41 *= -1.f;
	view_._42 *= -1.f;
	view_._43 *= -1.f;
}

std::unique_ptr<Component, std::function<void(Component*)>> Camera::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new Camera{ *this }, [](Component* _p) {
		dynamic_cast<Camera*>(_p)->_Release();
		delete dynamic_cast<Camera*>(_p);
	}};
}

void Camera::_CreateProjectionMatrix(CAMERA_TYPE _type)
{
	switch (_type)
	{
	case CAMERA_TYPE::PERSPECTIVE:
		projection_ = DirectX::XMMatrixPerspectiveFovLH(fov_angle_, width_ / height_, near_, far_);
		break;

	case CAMERA_TYPE::ORTHOGONAL:
		projection_ = DirectX::XMMatrixOrthographicOffCenterLH(0.f, width_, 0.f, height_, near_, far_);
		break;
	}
}
