#include "DGEngine_stdafx.h"
#include "collider_circle.h"

#include "Resource/resource_manager.h"
#include "Resource/mesh.h"
#include "Rendering/rendering_manager.h"
#include "Scene/scene.h"
#include "object.h"
#include "Component/transform.h"
#include "Component/camera.h"
#include "Component/collider_point.h"
#include "Component/collider_rect.h"
#include "Component/collider_OOBB.h"

using namespace DG;

void ColliderCircle::Initialize()
{
	Collider::Initialize();

	collider_type_ = COLLIDER_TYPE::CIRCLE;

	mesh_tag_ = "ColliderCircle";
}

bool ColliderCircle::Collision(Collider* _dest, float _time)
{
	switch (_dest->collider_type())
	{
	case COLLIDER_TYPE::POINT:
		return _CollisionCircleToPoint(final_info_, dynamic_cast<ColliderPoint*>(_dest)->final_info());

	case COLLIDER_TYPE::RECT:
		return _CollisionCircleToRect(final_info_, dynamic_cast<ColliderRect*>(_dest)->final_info());

	case COLLIDER_TYPE::CIRCLE:
		return _CollisionCircleToCircle(final_info_, dynamic_cast<ColliderCircle*>(_dest)->final_info_);

	case COLLIDER_TYPE::OOBB:
		return _CollisionOOBBToCircle(dynamic_cast<ColliderOOBB*>(_dest)->final_info(), final_info_);
	}

	return false;
}

CircleInfo const& ColliderCircle::final_info() const
{
	return final_info_;
}

void ColliderCircle::set_relative_info(Math::Vector3 const& _center, float _radius)
{
	relative_info_.center = _center;
	relative_info_.radius = _radius;
	final_info_.radius = _radius;
}

ColliderCircle::ColliderCircle(ColliderCircle const& _other) : Collider(_other)
{
	relative_info_ = _other.relative_info_;
	final_info_ = _other.final_info_;
}

ColliderCircle::ColliderCircle(ColliderCircle&& _other) noexcept : Collider(std::move(_other))
{
	relative_info_ = std::move(_other.relative_info_);
	final_info_ = std::move(_other.final_info_);
}

void ColliderCircle::_Release()
{
	Collider::_Release();
}

void ColliderCircle::_LateUpdate(float _time)
{
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	auto const& mesh = ResourceManager::singleton()->FindMesh(mesh_tag_);
	Math::Vector3 object_position = transform->GetLocalPosition() - mesh->diagonal() * transform->scale_vector() * transform->pivot();

	final_info_.center = object_position + relative_info_.center;

	collider_min_ = final_info_.center - Math::Vector3{ final_info_.radius, final_info_.radius, 0.f };
	collider_max_ = final_info_.center + Math::Vector3{ final_info_.radius, final_info_.radius, 0.f };
}

void ColliderCircle::_Render(float _time)
{
#ifdef _DEBUG
	auto const& main_camera = scene()->main_camera();
	auto const& camera_component = std::dynamic_pointer_cast<Camera>(main_camera->FindComponent(COMPONENT_TYPE::CAMERA));
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	Math::Matrix view = Math::Matrix::Identity;

	if (collision_group_tag_ != "UI")
		view = camera_component->view();

	TransformConstantBuffer transform_constant_buffer{};
	transform_constant_buffer.world = Math::Matrix::CreateScale(transform->scale_vector()) * Math::Matrix::CreateTranslation(final_info_.center);
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

std::unique_ptr<Component, std::function<void(Component*)>> ColliderCircle::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new ColliderCircle{ *this }, [](Component* _p) {
		dynamic_cast<ColliderCircle*>(_p)->_Release();
		delete dynamic_cast<ColliderCircle*>(_p);
	} };
}
