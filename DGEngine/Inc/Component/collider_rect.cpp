#include "DGEngine_stdafx.h"
#include "collider_rect.h"

#include "Resource/resource_manager.h"
#include "Resource/mesh.h"
#include "Rendering/rendering_manager.h"
#include "Scene/scene.h"
#include "object.h"
#include "Component/transform.h"
#include "Component/camera.h"
#include "Component/collider_point.h"
#include "Component/collider_OOBB.h"

using namespace DG;

void ColliderRect::Initialize()
{
	collider_type_ = COLLIDER_TYPE::RECT;

	Collider::Initialize();
}

bool ColliderRect::Collision(Collider* _dest, float _time)
{
	switch (_dest->collider_type())
	{
	case COLLIDER_TYPE::POINT:
		return _CollisionRectToPoint(final_info_, dynamic_cast<ColliderPoint*>(_dest)->final_info());

	case COLLIDER_TYPE::RECT:
		return _CollisionRectToRect(final_info_, dynamic_cast<ColliderRect*>(_dest)->final_info_);

	case COLLIDER_TYPE::OOBB:
		return _CollisionOOBBToRect(dynamic_cast<ColliderOOBB*>(_dest)->final_info(), final_info_);
	}

	return false;
}

RectInfo const& ColliderRect::final_info() const
{
	return final_info_;
}

void ColliderRect::set_relative_info(Math::Vector3 const& _min, Math::Vector3 const& _max)
{
	relative_info_.min = _min;
	relative_info_.max = _max;
	relative_info_.diagonal = _max - _min;
}

ColliderRect::ColliderRect(ColliderRect const& _other) : Collider(_other)
{
	relative_info_ = _other.relative_info_;
}

ColliderRect::ColliderRect(ColliderRect&& _other) noexcept : Collider(std::move(_other))
{
	relative_info_ = std::move(_other.relative_info_);
}

void ColliderRect::_Release()
{
	Collider::_Release();
}

void ColliderRect::_LateUpdate(float _time)
{
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	auto const& mesh = ResourceManager::singleton()->FindMesh(mesh_tag_);
	Math::Vector3 object_position = transform->GetLocalPosition() - mesh->diagonal() * transform->scale_vector() * transform->pivot();

	final_info_.min = object_position + relative_info_.min;
	final_info_.max = object_position + relative_info_.max;
	final_info_.diagonal = relative_info_.diagonal;

	collider_min_ = final_info_.min;
	collider_max_ = final_info_.max;
}

void ColliderRect::_Render(float _time)
{
#ifdef _DEBUG
	auto const& main_camera = scene()->main_camera();
	auto const& camera_component = std::dynamic_pointer_cast<Camera>(main_camera->FindComponent(COMPONENT_TYPE::CAMERA));
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	Math::Matrix view = Math::Matrix::Identity;

	if (collision_group_tag_ != "UI")
		view = camera_component->view();

	TransformConstantBuffer transform_constant_buffer{};
	transform_constant_buffer.world = Math::Matrix::CreateScale(transform->scale_vector()) * Math::Matrix::CreateTranslation(final_info_.min);
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

std::unique_ptr<Component, std::function<void(Component*)>> ColliderRect::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new ColliderRect{ *this }, [](Component* _p) {
		dynamic_cast<ColliderRect*>(_p)->_Release();
		delete dynamic_cast<ColliderRect*>(_p);
	} };
}
