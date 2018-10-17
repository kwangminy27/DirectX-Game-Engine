#include "DGEngine_stdafx.h"
#include "collider_rect.h"

#include "Resource/resource_manager.h"
#include "Resource/mesh.h"
#include "Rendering/rendering_manager.h"
#include "Scene/scene.h"
#include "object.h"
#include "Component/transform.h"
#include "Component/camera.h"

using namespace DG;

void ColliderRect::Initialize()
{
	collider_type_ = COLLIDER_TYPE::RECT;

	Collider::Initialize();
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

	relative_info_.min.z = 0.f;
	relative_info_.max.z = 0.f;
	relative_info_.diagonal.z = 1.f; // 왜 1.f 이어야하지?
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
}

void ColliderRect::_LateUpdate(float _time)
{
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));

	auto const& mesh = ResourceManager::singleton()->FindMesh(mesh_tag_);
	Math::Vector3 object_position = transform->GetLocalPosition() - mesh->diagonal() * transform->pivot();

	final_info_.min = object_position + relative_info_.min - pivot_ * relative_info_.diagonal;
	final_info_.max = object_position + relative_info_.max - pivot_ * relative_info_.diagonal;
	final_info_.diagonal = relative_info_.diagonal;

	// 이 정보 자체가 사각형의 영역을 판단할 데이터로 사용된다.
	collider_min_ = final_info_.min;
	collider_max_ = final_info_.max;
}

bool ColliderRect::Collision(Collider* _dest, float _time)
{
	switch (_dest->collider_type())
	{
	case COLLIDER_TYPE::RECT:
		return _CollisionRectToRect(final_info_, dynamic_cast<ColliderRect*>(_dest)->final_info_);
	}

	return false;
}

void ColliderRect::_Render(float _time)
{
#ifdef _DEBUG
	auto const& main_camera = scene()->main_camera();
	auto const& camera_component = std::dynamic_pointer_cast<Camera>(main_camera->FindComponent(COMPONENT_TYPE::CAMERA));

	TransformConstantBuffer transform_constant_buffer{};
	transform_constant_buffer.world = Math::Matrix::CreateTranslation(final_info_.min);
	transform_constant_buffer.view = camera_component->view();
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
