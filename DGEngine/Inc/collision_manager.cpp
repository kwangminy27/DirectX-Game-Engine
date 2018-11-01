#include "DGEngine_stdafx.h"
#include "collision_manager.h"

#include "path_manager.h"
#include "object.h"
#include "Component/collider.h"
#include "Component/collider_point.h"
#include "input_manager.h"

using namespace DG;

std::unique_ptr<_PixelInfo, std::function<void(_PixelInfo*)>> CollisionManager::pixel_collider_nullptr_{};
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

		_CreatePixelCollider("PixelCollider", L"PixelCollider.bmp", TEXTURE_PATH);
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
	if (!CollisionBetweenMouseWithUI(_time))
		CollisionBetweenMouseWithObjects(_time);

	for (auto const& _collision_group : collision_group_map_)
	{
		for (int i = 0; i < _collision_group.second->total_count; ++i)
		{
			auto& section = _collision_group.second->section_3d[i];

			if (section.size < 2)
			{
				for (int j = 0; j < section.size; ++j)
					section.collider_dynamic_array[j]->_UpdateCollidedCollider(_time);

				section.size = 0; // 여기서 0으로 만들기 때문에 AddCollider에서는 따로 0으로 안 만들어줘도 됨

				continue;
			}

			for (int j = 0; j < section.size; ++j)
				section.collider_dynamic_array[j]->_UpdateCollidedCollider(_time);

			for (int j = 0; j < section.size - 1; ++j)
			{
				for (int k = j + 1; k < section.size; ++k)
				{
					Collider* src_collider = section.collider_dynamic_array[j];
					Collider* dest_collider = section.collider_dynamic_array[k];

					if (src_collider->object_tag() == dest_collider->object_tag())
						continue;

					if (!src_collider->active_flag() || !src_collider->enable_flag())
						continue;

					if (!dest_collider->active_flag() || !dest_collider->enable_flag())
						continue;

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

			section.size = 0;
		}
	}
}

bool CollisionManager::CollisionBetweenMouseWithUI(float _time)
{
	// 마우스와 오브젝트간 충돌처리
	auto const& mouse_object = InputManager::singleton()->mouse();
	Collider* mouse_ui_collider = std::dynamic_pointer_cast<ColliderPoint>(mouse_object->FindComponent("MouseUICollider")).get();

	mouse_ui_collider->_ClearSection();

	auto const& ui_collision_group = FindCollisionGroup("UI");
	auto const& mouse_position = dynamic_cast<ColliderPoint*>(mouse_ui_collider)->final_info();

	int mouse_ui_section_x_idx = static_cast<int>(mouse_position.x / ui_collision_group->section_length.x);
	int mouse_ui_section_y_idx = static_cast<int>(mouse_position.y / ui_collision_group->section_length.y);
	// 2D 게임이라 z는 아직 보류

	bool is_ui_collided = false;
	if (mouse_ui_section_x_idx >= 0 && mouse_ui_section_x_idx < ui_collision_group->x_count &&
		mouse_ui_section_y_idx >= 0 && mouse_ui_section_y_idx < ui_collision_group->y_count)
	{ // 인덱스가 유효하다면
		int mouse_section_idx = ui_collision_group->x_count * mouse_ui_section_y_idx + mouse_ui_section_x_idx;

		mouse_ui_collider->_AddSection(mouse_section_idx);

		auto const& section = ui_collision_group->section_3d[mouse_section_idx];

		// UI 오픈 순서에 따라 정렬, 일단 보류하고 나중에 구현
		for (int i = 0; i < section.size; ++i)
		{
			Collider* dest = section.collider_dynamic_array[i];

			if (!dest->active_flag() || !dest->enable_flag())
				continue;

			if (mouse_ui_collider->Collision(dest, _time))
			{
				if (!mouse_ui_collider->_IsCollidedCollider(dest))
				{
					mouse_ui_collider->_AddCollidedCollider(dest);
					dest->_AddCollidedCollider(mouse_ui_collider);

					mouse_ui_collider->_OnCollisionEnter(dest, _time);
					dest->_OnCollisionEnter(mouse_ui_collider, _time);

					is_ui_collided = true;

					break;
				}
				else
				{
					mouse_ui_collider->_OnCollision(dest, _time);
					dest->_OnCollision(mouse_ui_collider, _time);

					is_ui_collided = true;

					break;
				}
			}
			else
			{
				if (mouse_ui_collider->_IsCollidedCollider(dest))
				{
					mouse_ui_collider->_EraseCollidedCollider(dest);
					dest->_EraseCollidedCollider(mouse_ui_collider);

					mouse_ui_collider->_OnCollisionLeave(dest, _time);
					dest->_OnCollisionLeave(mouse_ui_collider, _time);
				}
			}
		}
	}

	// ui와 충돌이 발생한 경우 mouse_world_collider와 관련있는 collider들을 싹 제거해준다.
	if (is_ui_collided)
	{
		Collider* mouse_world_collider = std::dynamic_pointer_cast<ColliderPoint>(mouse_object->FindComponent("MouseWorldCollider")).get();

		for (auto iter = mouse_world_collider->collided_collider_list_.begin(); iter != mouse_world_collider->collided_collider_list_.end(); ++iter)
		{
			mouse_world_collider->_OnCollisionLeave(*iter, _time);

			(*iter)->_OnCollisionLeave(mouse_world_collider, _time);
			(*iter)->_EraseCollidedCollider(mouse_world_collider);
		}

		mouse_world_collider->collided_collider_list_.clear();
	}


	return is_ui_collided;
}

void CollisionManager::CollisionBetweenMouseWithObjects(float _time)
{
	auto const& mouse_object = InputManager::singleton()->mouse();
	Collider* mouse_world_collider = std::dynamic_pointer_cast<ColliderPoint>(mouse_object->FindComponent("MouseWorldCollider")).get();

	mouse_world_collider->_ClearSection();

	for (auto iter = collision_group_map_.begin(); iter != collision_group_map_.end(); ++iter)
	{
		if (iter->first == "UI")
			continue;

		auto const& mouse_position = dynamic_cast<ColliderPoint*>(mouse_world_collider)->final_info();

		int mouse_world_section_x_idx = static_cast<int>(mouse_position.x / iter->second->section_length.x);
		int mouse_world_section_y_idx = static_cast<int>(mouse_position.y / iter->second->section_length.y);

		if (mouse_world_section_x_idx >= 0 && mouse_world_section_x_idx < iter->second->x_count &&
			mouse_world_section_y_idx >= 0 && mouse_world_section_y_idx < iter->second->y_count)
		{
			int mouse_world_section_idx = iter->second->x_count * mouse_world_section_y_idx + mouse_world_section_x_idx;

			mouse_world_collider->_AddSection(mouse_world_section_idx);

			auto const& section = iter->second->section_3d[mouse_world_section_idx];

			// Objects 정렬(맨 앞에 있는 오브젝트가 선택되도록 하기 위함), 일단 보류하고 나중에 구현
			bool is_world_collided = false;
			for (int i = 0; i < section.size; ++i)
			{
				Collider* dest = section.collider_dynamic_array[i];

				if (!dest->active_flag() || !dest->enable_flag())
					continue;

				if (is_world_collided)
				{ // 이미 충돌이 되었다면 나머지는 충돌목록에서 제거한다. 1개만 선택되도록
					if (mouse_world_collider->_IsCollidedCollider(dest))
					{
						mouse_world_collider->_EraseCollidedCollider(dest);
						dest->_EraseCollidedCollider(mouse_world_collider);

						mouse_world_collider->_OnCollisionLeave(dest, _time);
						dest->_OnCollisionLeave(mouse_world_collider, _time);
					}

					continue;
				}

				if (mouse_world_collider->Collision(dest, _time))
				{
					if (!mouse_world_collider->_IsCollidedCollider(dest))
					{
						mouse_world_collider->_AddCollidedCollider(dest);
						dest->_AddCollidedCollider(mouse_world_collider);

						mouse_world_collider->_OnCollisionEnter(dest, _time);
						dest->_OnCollisionEnter(mouse_world_collider, _time);

						is_world_collided = true;
					}
					else
					{
						mouse_world_collider->_OnCollision(dest, _time);
						dest->_OnCollision(mouse_world_collider, _time);

						is_world_collided = true;
					}
				}
				else
				{
					if (mouse_world_collider->_IsCollidedCollider(dest))
					{
						mouse_world_collider->_EraseCollidedCollider(dest);
						dest->_EraseCollidedCollider(mouse_world_collider);

						mouse_world_collider->_OnCollisionLeave(dest, _time);
						dest->_OnCollisionLeave(mouse_world_collider, _time);
					}
				}
			}
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
	auto const& collider_list = _object->FindComponents(COMPONENT_TYPE::COLLIDER);

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

					// 모든 section이 들고 있는 collider는 의미가 있다는 것이 보장 됨.
					// 그 이유는, 충돌이 발생해서 active flag를 false로 설정하더라도 모든 충돌검사가 종료된 후에 object가 제거되기 때문.
					section->collider_dynamic_array[section->size] = reinterpret_cast<Collider*>((*iter).get());
					++section->size;
				}
			}
		}
	}
}

std::unique_ptr<_PixelInfo, std::function<void(_PixelInfo*)>> const& CollisionManager::FindPixelCollider(std::string const& _tag) const
{
	auto iter = pixel_collider_map_.find(_tag);

	if (iter == pixel_collider_map_.end())
		return pixel_collider_nullptr_;

	return iter->second;
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

void CollisionManager::EraseExpiredCollider(Collider* _collider)
{
	auto section_idx_list = _collider->section_idx_list();

	for (auto const& _section_idx : section_idx_list)
	{
		for (int i = 0; i < collision_group_map_[_collider->collision_group_tag()]->section_3d[_section_idx].size; ++i)
		{
			if (collision_group_map_[_collider->collision_group_tag()]->section_3d[_section_idx].collider_dynamic_array[i] == _collider)
				collision_group_map_[_collider->collision_group_tag()]->section_3d[_section_idx].collider_dynamic_array[i] = nullptr;		}
	}
}

void CollisionManager::_Release()
{
}

void CollisionManager::_CreatePixelCollider(std::string const& _tag, std::wstring const& _file_name, std::string const& _path_tag)
{
	auto const& path_buffer = PathManager::singleton()->FindPath(_path_tag);

	if (path_buffer.empty())
		throw std::exception{ "CollisionManager::_CreatePixel" };

	std::wstring full_path = path_buffer.wstring() + _file_name;

	std::ifstream file{ full_path, std::ios::binary };

	if(file.fail())
		throw std::exception{ "CollisionManager::_CreatePixel" };

	BITMAPFILEHEADER bitmap_file_header{};
	BITMAPINFOHEADER bitmap_info_header{};

	file.read(reinterpret_cast<char*>(&bitmap_file_header), sizeof(BITMAPFILEHEADER));
	file.read(reinterpret_cast<char*>(&bitmap_info_header), sizeof(BITMAPINFOHEADER));

	auto pixel = std::unique_ptr<_PixelInfo, std::function<void(_PixelInfo*)>>{ new _PixelInfo, [](_PixelInfo* _p) {
		delete[] _p->pixel_collection;
		delete _p;
	} };

	pixel->width = bitmap_info_header.biWidth;
	pixel->height = bitmap_info_header.biHeight;
	pixel->pixel_collection = new Pixel24[pixel->width * pixel->height];

	file.read(reinterpret_cast<char*>(pixel->pixel_collection), sizeof(Pixel24) * pixel->width * pixel->height);

	pixel_collider_map_.insert(make_pair(_tag, move(pixel)));
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
