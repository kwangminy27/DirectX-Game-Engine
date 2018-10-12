#pragma once

#include "singleton.h"

namespace DG
{
	class Collider;

	struct DG_ENGINE_DLL CollisionSection
	{
		Collider** collider_list;
		int size;
		int capacity;
		Math::Vector3 min;
		Math::Vector3 max;
	};

	struct DG_ENGINE_DLL CollisionGroup
	{
		std::unique_ptr<CollisionSection, std::function<void(CollisionSection*)>> section_3d;
		int x_count;
		int y_count;
		int z_count;
		int total_count;
		Math::Vector3 min;
		Math::Vector3 max;
	};

	class DG_ENGINE_DLL CollisionManager final : public Singleton<CollisionManager>
	{
		friend class Singleton<CollisionManager>;
	public:
		void Initialize();

		std::shared_ptr<CollisionGroup> const& FindCollisionGroup(std::string const& _tag) const;

	private:
		CollisionManager() = default;
		CollisionManager(CollisionManager const&) = delete;
		CollisionManager(CollisionManager&&) noexcept = delete;
		CollisionManager& operator=(CollisionManager const&) = delete;
		CollisionManager& operator=(CollisionManager&&) noexcept = delete;

		virtual void _Release() override;

		void _CreateGroup(
			std::string const& _tag,
			int _x_count,
			int _y_count,
			int _z_count,
			int _total_count,
			Math::Vector3 const& _min,
			Math::Vector3 const& _max);

		static std::shared_ptr<CollisionGroup> collision_group_nullptr_;
		std::unordered_map<std::string, std::shared_ptr<CollisionGroup>> collision_group_map_{};
	};
}
