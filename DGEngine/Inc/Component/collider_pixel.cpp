#include "DGEngine_stdafx.h"
#include "collider_pixel.h"

#include "Resource/resource_manager.h"
#include "Resource/mesh.h"
#include "Rendering/rendering_manager.h"
#include "Scene/scene.h"
#include "object.h"
#include "Component/transform.h"
#include "Component/camera.h"
#include "Component/collider_point.h"
#include "Component/collider_rect.h"
#include "Component/collider_circle.h"
#include "Component/collider_OOBB.h"

using namespace DG;

void ColliderPixel::Initialize()
{
	Collider::Initialize();

	collider_type_ = COLLIDER_TYPE::PIXEL;
}

bool ColliderPixel::Collision(Collider* _dest, float _time)
{
	switch (_dest->collider_type())
	{
	case COLLIDER_TYPE::POINT:
		break;

	case COLLIDER_TYPE::RECT:
		return _CollisionPixelToRect(final_info_, dynamic_cast<ColliderRect*>(_dest)->final_info());

	case COLLIDER_TYPE::CIRCLE:
		break;

	case COLLIDER_TYPE::OOBB:
		break;

	case COLLIDER_TYPE::PIXEL:
		break;
	}

	return false;
}

PixelInfo const& ColliderPixel::final_info() const
{
	return final_info_;
}

void ColliderPixel::set_relative_info(std::string const& _tag, Math::Vector3 const& _min, Math::Vector3 const& _max)
{
	relative_info_.tag = _tag;
	relative_info_.rect_info.min = _min;
	relative_info_.rect_info.max = _max;
	relative_info_.rect_info.diagonal = _max - _min;

	final_info_.tag = _tag;
}

ColliderPixel::ColliderPixel(ColliderPixel const& _other) : Collider(_other)
{
	relative_info_ = _other.relative_info_;
	final_info_ = _other.final_info_;
}

ColliderPixel::ColliderPixel(ColliderPixel&& _other) noexcept : Collider(std::move(_other))
{
	relative_info_ = std::move(_other.relative_info_);
	final_info_ = std::move(_other.final_info_);
}

void ColliderPixel::_Release()
{
	Collider::_Release();
}

void ColliderPixel::_LateUpdate(float _time)
{
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	auto const& mesh = ResourceManager::singleton()->FindMesh(mesh_tag_);
	Math::Vector3 object_position = transform->GetWorldPosition() - mesh->diagonal() * transform->GetWorldScale() * transform->pivot();

	final_info_.rect_info.min = object_position + relative_info_.rect_info.min;
	final_info_.rect_info.max = object_position + relative_info_.rect_info.max;
	final_info_.rect_info.diagonal = relative_info_.rect_info.diagonal;	 

	collider_min_ = final_info_.rect_info.min;
	collider_max_ = final_info_.rect_info.max;
}

void ColliderPixel::_Render(float _time)
{
#ifdef _DEBUG
	auto const& main_camera = scene()->main_camera();
	auto const& camera_component = std::dynamic_pointer_cast<Camera>(main_camera->FindComponent(COMPONENT_TYPE::CAMERA));
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	Math::Matrix view = Math::Matrix::Identity;

	if (collision_group_tag_ != "UI")
		view = camera_component->view();

	TransformConstantBuffer transform_constant_buffer{};
	transform_constant_buffer.world = Math::Matrix::CreateScale(transform->GetWorldScale()) * Math::Matrix::CreateTranslation(final_info_.rect_info.min);
	transform_constant_buffer.view = view;
	transform_constant_buffer.projection = camera_component->projection();
	transform_constant_buffer.WVP = transform_constant_buffer.world * transform_constant_buffer.view * transform_constant_buffer.projection;
	transform_constant_buffer.pivot = pivot_;

	auto const& mesh = ResourceManager::singleton()->FindMesh(mesh_tag_);
	transform_constant_buffer.diagonal = mesh->diagonal();

	transform_constant_buffer.world = transform_constant_buffer.world.Transpose();
	transform_constant_buffer.view = transform_constant_buffer.view.Transpose();
	transform_constant_buffer.projection = transform_constant_buffer.projection.Transpose();
	transform_constant_buffer.WVP = transform_constant_buffer.WVP.Transpose();

	RenderingManager::singleton()->UpdateConstantBuffer("Transform", &transform_constant_buffer);

	Collider::_Render(_time);
#endif
}

std::unique_ptr<Component, std::function<void(Component*)>> ColliderPixel::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new ColliderPixel{ *this }, [](Component* _p) {
		dynamic_cast<ColliderPixel*>(_p)->_Release();
		delete dynamic_cast<ColliderPixel*>(_p);
	} };
}
