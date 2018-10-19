#include "DGEngine_stdafx.h"
#include "collider.h"

#include "device.h"
#include "Resource/resource_manager.h"
#include "Resource/mesh.h"
#include "Rendering/rendering_manager.h"
#include "Rendering/shader.h"
#include "collision_manager.h"

using namespace DG;

void Collider::Initialize()
{
	type_ = COMPONENT_TYPE::COLLIDER;

	collision_group_tag_ = "Default";

#ifdef _DEBUG
	mesh_tag_ = "ColliderRect";
	shader_tag_ = COLLIDER_SHADER;
	color_ = DirectX::Colors::Green.v;
#endif
}

void Collider::AddCallback(std::function<void(Collider*, Collider*, float)> const& _function, COLLISION_CALLBACK_TYPE _type)
{
	collision_callback_list_array_.at(static_cast<int>(_type)).push_back(_function);
}

COLLIDER_TYPE Collider::collider_type() const
{
	return collider_type_;
}

std::string const& Collider::collision_group_tag() const
{
	return collision_group_tag_;
}

bool Collider::update_flag() const
{
	return update_flag_;
}

Math::Vector3 const& Collider::collider_min() const
{
	return collider_min_;
}

Math::Vector3 const& Collider::collider_max() const
{
	return collider_max_;
}

std::list<int> const& Collider::section_idx_list() const
{
	return section_idx_list_;
}

void Collider::set_collision_group_tag(std::string const& _tag)
{
	collision_group_tag_ = _tag;
}

void Collider::set_pivot(Math::Vector3 const& _pivot)
{
	pivot_ = _pivot;
}

#ifdef _DEBUG
void Collider::set_mesh_tag(std::string const& _tag)
{
	mesh_tag_ = _tag;
}

void Collider::set_shader_tag(std::string const& _tag)
{
	shader_tag_ = _tag;
}

void Collider::set_color(Math::Vector4 const& _color)
{
	color_ = _color;
}
#endif

Collider::Collider(Collider const& _other) : Component(_other)
{
	collider_type_ = _other.collider_type_;
	collision_group_tag_ = _other.collision_group_tag_;
	update_flag_ = _other.update_flag_;
	pivot_ = _other.pivot_;

	collider_min_ = _other.collider_min_;
	collider_max_ = _other.collider_max_;
	
	section_idx_list_ = _other.section_idx_list_;
	collided_collider_list_ = _other.collided_collider_list_;
	collision_callback_list_array_ = _other.collision_callback_list_array_;

#ifdef _DEBUG
	mesh_tag_ = _other.mesh_tag_;
	shader_tag_ = _other.shader_tag_;
	color_ = _other.color_;
#endif
}

Collider::Collider(Collider&& _other) noexcept : Component(std::move(_other))
{
	collider_type_ = std::move(_other.collider_type_);
	collision_group_tag_ = std::move(_other.collision_group_tag_);
	update_flag_ = std::move(_other.update_flag_);
	pivot_ = std::move(_other.pivot_);

	collider_min_ = std::move(_other.collider_min_);
	collider_max_ = std::move(_other.collider_max_);

	section_idx_list_ = std::move(_other.section_idx_list_);
	collided_collider_list_ = std::move(_other.collided_collider_list_);
	collision_callback_list_array_ = std::move(_other.collision_callback_list_array_);

#ifdef _DEBUG
	mesh_tag_ = std::move(_other.mesh_tag_);
	shader_tag_ = std::move(_other.shader_tag_);
	color_ = std::move(_other.color_);
#endif
}

void Collider::_Release()
{
	for (auto iter = collided_collider_list_.begin(); iter != collided_collider_list_.end(); ++iter)
	{
		_OnCollisionLeave(*iter, 0.f);

		(*iter)->_OnCollisionLeave(this, 0.f);
		(*iter)->_EraseCollidedCollider(this);
	}
}

void Collider::_Render(float _time)
{
#ifdef _DEBUG
	if (collided_collider_list_.empty())
		color_ = DirectX::Colors::Green.v;
	else
		color_ = DirectX::Colors::Red.v;

	RenderingManager::singleton()->UpdateConstantBuffer("Collider", &color_);

	auto const& shader = RenderingManager::singleton()->FindShader(shader_tag_);
	auto const& mesh = ResourceManager::singleton()->FindMesh(mesh_tag_);

	shader->SetShader();
	mesh->Render();
#endif
}

void Collider::_ClearSection()
{
	section_idx_list_.clear();
}

void Collider::_AddSection(int _idx)
{
	section_idx_list_.push_back(_idx);
}

void Collider::_AddCollidedCollider(Collider* _dest)
{
	collided_collider_list_.push_back(_dest);
}

void Collider::_UpdateCollidedCollider(float _time)
{
	for (auto iter = collided_collider_list_.begin(); iter != collided_collider_list_.end();)
	{
		if (collision_group_tag_ != (*iter)->collision_group_tag_)
		{
			_OnCollisionLeave(*iter, _time);
			(*iter)->_OnCollisionLeave(this, _time);

			(*iter)->_EraseCollidedCollider(this);
			iter = collided_collider_list_.erase(iter);

			continue;
		}

		bool is_overlapped = false;
		for (auto src_iter = section_idx_list_.begin(); src_iter != section_idx_list_.end(); ++src_iter)
		{
			for (auto dest_iter = (*iter)->section_idx_list_.begin(); dest_iter != (*iter)->section_idx_list_.end(); ++dest_iter)
			{
				if ((*src_iter) == (*dest_iter))
				{
					is_overlapped = true;

					break;
				}
			}

			if (is_overlapped)
				break;
		}

		if (!is_overlapped)
		{
			_OnCollisionLeave(*iter, _time);
			(*iter)->_OnCollisionLeave(this, _time);

			(*iter)->_EraseCollidedCollider(this);
			iter = collided_collider_list_.erase(iter);

			continue;
		}

		++iter;
	}
}

bool Collider::_IsCollidedCollider(Collider* _dest)
{
	for (auto const& _collider : collided_collider_list_)
	{
		if (_collider == _dest)
			return true;
	}

	return false;
}

void Collider::_EraseCollidedCollider(Collider* _dest)
{
	for (auto iter = collided_collider_list_.begin(); iter != collided_collider_list_.end();)
	{

		if (*iter == _dest)
		{
			iter = collided_collider_list_.erase(iter);
			continue;
		}

		++iter;
	}
}

void Collider::_OnCollisionEnter(Collider* _dest, float _time)
{
	for (auto const& _callback : collision_callback_list_array_.at(static_cast<int>(COLLISION_CALLBACK_TYPE::ENTER)))
		_callback(this, _dest, _time);
}

void Collider::_OnCollision(Collider* _dest, float _time)
{
	for (auto const& _callback : collision_callback_list_array_.at(static_cast<int>(COLLISION_CALLBACK_TYPE::STAY)))
		_callback(this, _dest, _time);
}

void Collider::_OnCollisionLeave(Collider* _dest, float _time)
{
	for (auto const& _callback : collision_callback_list_array_.at(static_cast<int>(COLLISION_CALLBACK_TYPE::LEAVE)))
		_callback(this, _dest, _time);
}

bool Collider::_CollisionRectToRect(RectInfo const& _src, RectInfo const& _dest)
{
	if (_src.min.x > _dest.max.x)
		return false;

	else if (_src.max.x < _dest.min.x)
		return false;

	else if (_src.min.y > _dest.max.y)
		return false;

	else if (_src.max.y < _dest.min.y)
		return false;

	return true;
}

bool Collider::_CollisionRectToPoint(RectInfo const& _src, Math::Vector3 const& _dest)
{
	if (_dest.x < _src.min.x)
		return false;

	else if (_dest.x > _src.max.x)
		return false;

	else if (_dest.y < _src.min.y)
		return false;

	else if (_dest.y > _src.max.y)
		return false;

	return true;
}
