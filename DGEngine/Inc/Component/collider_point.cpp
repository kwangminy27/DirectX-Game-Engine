#include "DGEngine_stdafx.h"
#include "collider_point.h"

#include "Rendering/rendering_manager.h"
#include "Scene/scene.h"
#include "object.h"
#include "Component/transform.h"
#include "Component/camera.h"
#include "Component/collider_rect.h"
#include "Component/collider_circle.h"
#include "Component/collider_OOBB.h"

using namespace DG;

void ColliderPoint::Initialize()
{
	Collider::Initialize();

	collider_type_ = COLLIDER_TYPE::POINT;
}

bool ColliderPoint::Collision(Collider* _dest, float _time)
{
	switch (_dest->collider_type())
	{
	case COLLIDER_TYPE::POINT:
		return _CollisionPointToPoint(final_info_, dynamic_cast<ColliderPoint*>(_dest)->final_info_);

	case COLLIDER_TYPE::RECT:
		return _CollisionRectToPoint(dynamic_cast<ColliderRect*>(_dest)->final_info(), final_info_);

	case COLLIDER_TYPE::CIRCLE:
		return _CollisionCircleToPoint(dynamic_cast<ColliderCircle*>(_dest)->final_info(), final_info_);

	case COLLIDER_TYPE::OOBB:
		return _CollisionOOBBToPoint(dynamic_cast<ColliderOOBB*>(_dest)->final_info(), final_info_);
	}

	return false;
}

Math::Vector3 const& ColliderPoint::final_info() const
{
	return final_info_;
}

void ColliderPoint::set_relative_info(Math::Vector3 const& _info)
{
	relative_info_ = _info;
}

ColliderPoint::ColliderPoint(ColliderPoint const& _other) : Collider(_other)
{
	relative_info_ = _other.relative_info_;
	final_info_ = _other.final_info_;
}

ColliderPoint::ColliderPoint(ColliderPoint&& _other) noexcept : Collider(std::move(_other))
{
	relative_info_ = std::move(_other.relative_info_);
	final_info_ = std::move(_other.final_info_);
}

void ColliderPoint::_Release()
{
	Collider::_Release();
}

void ColliderPoint::_LateUpdate(float _time)
{
	Math::Vector3 object_position = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM))->GetLocalPosition();

	final_info_ = object_position + relative_info_;

	collider_min_ = final_info_;
	collider_max_ = final_info_;
}

void ColliderPoint::_Render(float _time)
{
#ifdef _DEBUG
	auto const& main_camera = scene()->main_camera();
	auto const& camera_component = std::dynamic_pointer_cast<Camera>(main_camera->FindComponent(COMPONENT_TYPE::CAMERA));
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	Math::Matrix view = Math::Matrix::Identity;

	if (collision_group_tag_ != "UI")
		view = camera_component->view();

	TransformConstantBuffer transform_constant_buffer{};
	transform_constant_buffer.world = Math::Matrix::CreateScale(Math::Vector3{ 3.f, 3.f, 1.f }) * Math::Matrix::CreateTranslation(final_info_);
	transform_constant_buffer.view = view;
	transform_constant_buffer.projection = camera_component->projection();
	transform_constant_buffer.WVP = transform_constant_buffer.world * transform_constant_buffer.view * transform_constant_buffer.projection;

	transform_constant_buffer.world = transform_constant_buffer.world.Transpose();
	transform_constant_buffer.view = transform_constant_buffer.view.Transpose();
	transform_constant_buffer.projection = transform_constant_buffer.projection.Transpose();
	transform_constant_buffer.WVP = transform_constant_buffer.WVP.Transpose();

	RenderingManager::singleton()->UpdateConstantBuffer("Transform", &transform_constant_buffer);

	Collider::_Render(_time);
#endif
}

std::unique_ptr<Component, std::function<void(Component*)>> ColliderPoint::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new ColliderPoint{ *this }, [](Component* _p) {
		dynamic_cast<ColliderPoint*>(_p)->_Release();
		delete dynamic_cast<ColliderPoint*>(_p);
	} };
}
