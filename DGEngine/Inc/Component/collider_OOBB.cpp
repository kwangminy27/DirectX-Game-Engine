#include "DGEngine_stdafx.h"
#include "collider_OOBB.h"

#include "Resource/resource_manager.h"
#include "Resource/mesh.h"
#include "Rendering/rendering_manager.h"
#include "Scene/scene.h"
#include "object.h"
#include "Component/transform.h"
#include "Component/camera.h"
#include "Component/collider_point.h"
#include "Component/collider_rect.h"

using namespace DG;

void ColliderOOBB::Initialize()
{
	collider_type_ = COLLIDER_TYPE::OOBB;

	Collider::Initialize();
}

bool ColliderOOBB::Collision(Collider* _dest, float _time)
{
	switch (_dest->collider_type())
	{
	case COLLIDER_TYPE::POINT:
		return _CollisionOOBBToPoint(final_info_, dynamic_cast<ColliderPoint*>(_dest)->final_info());

	case COLLIDER_TYPE::RECT:
		return _CollisionOOBBToRect(final_info_, dynamic_cast<ColliderRect*>(_dest)->final_info());

	case COLLIDER_TYPE::OOBB:
		return _CollisionOOBBToOOBB(final_info_, dynamic_cast<ColliderOOBB*>(_dest)->final_info_);
	}

	return false;
}

Math::Vector3 ColliderOOBB::GetRight()
{
	return Math::Vector3{ relative_info_.rotation._11, relative_info_.rotation._12, relative_info_.rotation._13 };
}

Math::Vector3 ColliderOOBB::GetUp()
{
	return Math::Vector3{ relative_info_.rotation._21, relative_info_.rotation._22, relative_info_.rotation._23 };
}

Math::Vector3 ColliderOOBB::GetLook()
{
	return Math::Vector3{ relative_info_.rotation._31, relative_info_.rotation._32, relative_info_.rotation._33 };
}

OOBBInfo const& ColliderOOBB::relative_info() const
{
	return relative_info_;
}

OOBBInfo const& ColliderOOBB::final_info() const
{
	return final_info_;
}

void ColliderOOBB::set_relative_info(Math::Vector3 const& _center, Math::Vector3 const& _extent, Math::Matrix const& _rotation)
{
	relative_info_.center = _center;
	relative_info_.extent = _extent;
	relative_info_.rotation = _rotation;
}

ColliderOOBB::ColliderOOBB(ColliderOOBB const& _other) : Collider(_other)
{
	relative_info_ = _other.relative_info_;
	final_info_ = _other.final_info_;
}

ColliderOOBB::ColliderOOBB(ColliderOOBB&& _other) noexcept : Collider(std::move(_other))
{
	relative_info_ = std::move(_other.relative_info_);
	final_info_ = std::move(_other.final_info_);
}

void ColliderOOBB::_Release()
{
	Collider::_Release();
}

void ColliderOOBB::_Update(float _time)
{
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	memcpy_s(&relative_info_.rotation._11, sizeof(Math::Vector3), &(transform->GetLocalRight()), sizeof(Math::Vector3));
	memcpy_s(&relative_info_.rotation._21, sizeof(Math::Vector3), &(transform->GetLocalUp()), sizeof(Math::Vector3));
	memcpy_s(&relative_info_.rotation._31, sizeof(Math::Vector3), &(transform->GetLocalLook()), sizeof(Math::Vector3));
}

void ColliderOOBB::_LateUpdate(float _time)
{
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	auto rotated_center = DirectX::XMVector3TransformCoord(relative_info_.center, transform->GetLocalRotation());

	final_info_.center = transform->GetLocalPosition() + rotated_center;
	final_info_.extent = relative_info_.extent;
	final_info_.rotation = relative_info_.rotation;

	auto v0 = -GetRight() * relative_info_.extent.x + -GetUp() * relative_info_.extent.y;
	auto v1 = -GetRight() * relative_info_.extent.x + GetUp() * relative_info_.extent.y;
	auto v2 = GetRight() * relative_info_.extent.x + GetUp() * relative_info_.extent.y;
	auto v3 = GetRight() * relative_info_.extent.x + -GetUp() * relative_info_.extent.y;

	auto x_element_minmax = std::minmax({ v0.x, v1.x, v2.x, v3.x }, [](float const& _first, float const& _second) {
		return _first < _second;
	});

	auto y_element_minmax = std::minmax({ v0.y, v1.y, v2.y, v3.y }, [](float const& _first, float const& _second) {
		return _first < _second;
	});

	collider_min_ = final_info_.center + Math::Vector3{ x_element_minmax.first, y_element_minmax.first, 0.f };
	collider_max_ = final_info_.center + Math::Vector3{ x_element_minmax.second, y_element_minmax.second, 0.f };
}

void ColliderOOBB::_Render(float _time)
{
#ifdef _DEBUG
	auto const& main_camera = scene()->main_camera();
	auto const& camera_component = std::dynamic_pointer_cast<Camera>(main_camera->FindComponent(COMPONENT_TYPE::CAMERA));
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	Math::Matrix view = Math::Matrix::Identity;

	if (collision_group_tag_ != "UI")
		view = camera_component->view();

	TransformConstantBuffer transform_constant_buffer{};
	transform_constant_buffer.world = Math::Matrix::CreateScale(transform->scale_vector()) * final_info_.rotation * Math::Matrix::CreateTranslation(final_info_.center);
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

std::unique_ptr<Component, std::function<void(Component*)>> ColliderOOBB::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new ColliderOOBB{ *this }, [](Component* _p) {
		dynamic_cast<ColliderOOBB*>(_p)->_Release();
		delete dynamic_cast<ColliderOOBB*>(_p);
	} };
}
