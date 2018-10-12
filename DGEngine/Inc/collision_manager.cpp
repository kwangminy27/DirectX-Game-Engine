#include "DGEngine_stdafx.h"
#include "collision_manager.h"

using namespace DG;

std::shared_ptr<CollisionGroup> CollisionManager::collision_group_nullptr_{};

void CollisionManager::Initialize()
{
	try
	{
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

std::shared_ptr<CollisionGroup> const& CollisionManager::FindCollisionGroup(std::string const& _tag) const
{
	auto iter = collision_group_map_.find(_tag);

	if (iter == collision_group_map_.end())
		return collision_group_nullptr_;
	
	return iter->second;
}

void CollisionManager::_Release()
{
}

void CollisionManager::_CreateGroup(
	std::string const& _tag,
	int _x_count,
	int _y_count,
	int _z_count,
	int _total_count,
	Math::Vector3 const& _min,
	Math::Vector3 const& _max)
{
}
