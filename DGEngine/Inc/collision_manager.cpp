#include "DGEngine_stdafx.h"
#include "collision_manager.h"

#include "object.h"
#include "Component/collider.h"

using namespace DG;

std::shared_ptr<CollisionGroup> CollisionManager::collision_group_nullptr_{};

void CollisionManager::Initialize()
{
	try
	{
		_CreateGroup(
			"Default",
			COLLISION_GROUP_TYPE::_2D,
			10, 10, 1,
			Math::Vector3{ 0.f, 0.f, 0.f }, Math::Vector3{ 5000.f, 5000.f, 0.f }
		);

		_CreateGroup(
			"UI",
			COLLISION_GROUP_TYPE::_2D,
			4, 4, 1,
			Math::Vector3{ 0.f, 0.f, 0.f }, Math::Vector3{ static_cast<float>(RESOLUTION::WIDTH), static_cast<float>(RESOLUTION::HEIGHT), 0.f }
		);
	}
	catch (std::exception const& _e)
	{
		std::cerr << _e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "CollisionManager::Initialize()" << std::endl;
	}
}

void CollisionManager::Collision(float _time)
{
	for (auto const& _collision_group : collision_group_map_)
	{
		for (int i = 0; i < _collision_group.second->total_count; ++i)
		{
			auto section = &(_collision_group.second->section_3d[i]);

			if (section->size < 2)
			{
				for (int j = 0; j < section->size; ++j)
					section->collider_dynamic_array[j]->_UpdateCollidedCollider(_time);

				section->size = 0;

				continue;
			}

			for(int j = 0; j < section->size; ++j)
				section->collider_dynamic_array[j]->_UpdateCollidedCollider(_time);

			// bubble sort, 나중에 개선하자
			for (int j = 0; j < section->size - 1; ++j)
			{
				for (int k = j + 1; k < section->size; ++k)
				{
					std::shared_ptr<Object> src = section->collider_dynamic_array[j]->object();
					std::shared_ptr<Object> dest = section->collider_dynamic_array[k]->object();

					if (src == dest)
						continue;

					Collider* src_collider = section->collider_dynamic_array[j];
					Collider* dest_collider = section->collider_dynamic_array[k];

					// 충돌처리
					if (src_collider->Collision(dest_collider, _time))
					{
						if (!src_collider->_IsCollidedCollider(dest_collider))
						{
							src_collider->_AddCollidedCollider(dest_collider);
							dest_collider->_AddCollidedCollider(src_collider);

							src_collider->_OnCollisionEnter(dest_collider, _time);
							dest_collider->_OnCollisionEnter(src_collider, _time);
						}
						else
						{
							src_collider->_OnCollision(dest_collider, _time);
							dest_collider->_OnCollision(src_collider, _time);
						}
					}
					else
					{
						if (src_collider->_IsCollidedCollider(dest_collider))
						{
							src_collider->_EraseCollidedCollider(dest_collider);
							dest_collider->_EraseCollidedCollider(src_collider);

							src_collider->_OnCollisionLeave(dest_collider, _time);
							dest_collider->_OnCollisionLeave(src_collider, _time);
						}
					}
				}
			}

			section->size = 0;
		}
	}
}

void CollisionManager::ClearCollisionGroup()
{
	collision_group_map_.clear();
}

void CollisionManager::AddColliders(std::shared_ptr<Object> const& _object)
{
	if (!_object->IsComponent(COMPONENT_TYPE::COLLIDER))
		return;

	// const&로 안 받게 일단 해놨는데, 나중에 인터페이스 통일시키자.
	auto collider_list = _object->FindComponents(COMPONENT_TYPE::COLLIDER);

	for (auto iter = collider_list.begin(); iter != collider_list.end(); ++iter)
	{
		std::dynamic_pointer_cast<Collider>(*iter)->_ClearSection();

		auto const& collision_group = FindCollisionGroup(std::dynamic_pointer_cast<Collider>(*iter)->collision_group_tag());

		if (!collision_group)
			return;

		Math::Vector3 collider_min = std::dynamic_pointer_cast<Collider>(*iter)->collider_min();
		Math::Vector3 collider_max = std::dynamic_pointer_cast<Collider>(*iter)->collider_max();

		Math::Vector3 section_length = collision_group->section_length;

		int x_min_idx = static_cast<int>(collider_min.x - collision_group->min.x) / static_cast<int>(section_length.x);
		int x_max_idx = static_cast<int>(collider_max.x - collision_group->min.x) / static_cast<int>(section_length.x);
		int y_min_idx = static_cast<int>(collider_min.y - collision_group->min.y) / static_cast<int>(section_length.y);
		int y_max_idx = static_cast<int>(collider_max.y - collision_group->min.y) / static_cast<int>(section_length.y);
		int z_min_idx{};
		int z_max_idx{};

		if (section_length.z != 0.f)
		{
			z_min_idx = static_cast<int>(collider_min.z - collision_group->min.z) / static_cast<int>(section_length.z);
			z_max_idx = static_cast<int>(collider_max.z - collision_group->min.z) / static_cast<int>(section_length.z);
		}

		for (int z = z_min_idx; z <= z_max_idx; ++z)
		{
			if (z < 0 || z >= collision_group->z_count)
				continue;

			for (int y = y_min_idx; y <= y_max_idx; ++y)
			{
				if (y < 0 || y >= collision_group->y_count)
					continue;

				for (int x = x_min_idx; x <= x_max_idx; ++x)
				{
					if (x < 0 || x >= collision_group->x_count)
						continue;

					int idx = (collision_group->x_count * collision_group->y_count * z) + (collision_group->x_count * y) + x;

					std::dynamic_pointer_cast<Collider>(*iter)->_AddSection(idx);

					auto section = &(collision_group->section_3d[idx]);

					if (section->capacity == section->size)
					{
						section->capacity = static_cast<int>(section->capacity * 1.5f);

						auto temp = std::unique_ptr<Collider*[], std::function<void(Collider**)>>{ new Collider*[section->capacity], [](Collider** _p) {
							delete[] _p;
						} };

						memcpy_s(temp.get(), sizeof(Collider*) * section->size, section->collider_dynamic_array.get(), sizeof(Collider*) * section->size);

						section->collider_dynamic_array = std::move(temp);
					}

					section->collider_dynamic_array[section->size] = reinterpret_cast<Collider*>((*iter).get());
					++section->size;
				}
			}
		}
	}
}

std::shared_ptr<CollisionGroup> const& CollisionManager::FindCollisionGroup(std::string const& _tag) const
{
	auto iter = collision_group_map_.find(_tag);

	if (iter == collision_group_map_.end())
		return collision_group_nullptr_;
	
	return iter->second;
}

void CollisionManager::SetGroupType(std::string const& _tag, COLLISION_GROUP_TYPE _type)
{
	auto iter = collision_group_map_.find(_tag);

	if (iter == collision_group_map_.end())
		return;

	iter->second->type = _type;
}

void CollisionManager::_Release()
{
}

void CollisionManager::_CreateGroup(
	std::string const& _tag,
	COLLISION_GROUP_TYPE _type,
	int _x_count,
	int _y_count,
	int _z_count,
	Math::Vector3 const& _min,
	Math::Vector3 const& _max)
{
	if (FindCollisionGroup(_tag))
		throw std::exception{ "CollisionManager::_CreateGroup" };

	auto collision_group = std::shared_ptr<CollisionGroup>{ new CollisionGroup, [](CollisionGroup* _p) {
		delete _p;
	} };

	collision_group->type = _type;
	collision_group->x_count = _x_count;
	collision_group->y_count = _y_count;
	collision_group->z_count = _z_count;
	collision_group->total_count = _x_count * _y_count * _z_count;
	collision_group->min = _min;
	collision_group->max = _max;

	collision_group->section_3d = std::unique_ptr<CollisionSection[], std::function<void(CollisionSection*)>>{ new CollisionSection[collision_group->total_count], [](CollisionSection* _p) {
		delete[] _p;
	} };

	for (int i = 0; i < collision_group->total_count; ++i)
	{
		collision_group->section_3d[i].capacity = 5;
		collision_group->section_3d[i].size = 0;

		collision_group->section_3d[i].collider_dynamic_array = std::unique_ptr<Collider*[], std::function<void(Collider**)>>{
			new Collider*[collision_group->section_3d[i].capacity], [](Collider** _p) { delete[] _p; }
		};
	}

	collision_group->length = _max - _min;
	collision_group->section_length = collision_group->length / Math::Vector3(static_cast<float>(_x_count), static_cast<float>(_y_count), static_cast<float>(_z_count));

	collision_group_map_.insert(make_pair(_tag, std::move(collision_group)));
}
