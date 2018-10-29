#pragma once

#include "singleton.h"

namespace DG
{
	class Object;
	class Collider;
	class ColliderPixel;

	struct DG_ENGINE_DLL CollisionSection
	{
		std::unique_ptr<Collider*[], std::function<void(Collider**)>> collider_dynamic_array;
		int size;
		int capacity;
	};

	struct DG_ENGINE_DLL CollisionGroup
	{
		COLLISION_GROUP_TYPE type;
		std::unique_ptr<CollisionSection[], std::function<void(CollisionSection*)>> section_3d;
		int x_count;
		int y_count;
		int z_count;
		int total_count;
		Math::Vector3 min;
		Math::Vector3 max;
		Math::Vector3 length;
		Math::Vector3 section_length;
	};

	class DG_ENGINE_DLL CollisionManager final : public Singleton<CollisionManager>
	{
		friend class Singleton<CollisionManager>;
	public:
		void Initialize();
		void Collision(float _time);
		bool CollisionBetweenMouseWithUI(float _time);
		void CollisionBetweenMouseWithObjects(float _time);
		void ClearCollisionGroup();

		void AddColliders(std::shared_ptr<Object> const& _object);
		std::unique_ptr<_PixelInfo, std::function<void(_PixelInfo*)>> const& FindPixelCollider(std::string const& _tag) const;
		std::shared_ptr<CollisionGroup> const& FindCollisionGroup(std::string const& _tag) const;
		void SetGroupType(std::string const& _tag, COLLISION_GROUP_TYPE _type);
		void EraseExpiredCollider(Collider* _collider);

	private:
		CollisionManager() = default;
		CollisionManager(CollisionManager const&) = delete;
		CollisionManager(CollisionManager&&) noexcept = delete;
		CollisionManager& operator=(CollisionManager const&) = delete;
		CollisionManager& operator=(CollisionManager&&) noexcept = delete;

		virtual void _Release() override;

		void _CreatePixelCollider(std::string const& _tag, std::wstring const& _file_name, std::string const& _path_tag);
		void _CreateGroup(
			std::string const& _tag,
			COLLISION_GROUP_TYPE _type,
			int _x_count,
			int _y_count,
			int _z_count,
			Math::Vector3 const& _min,
			Math::Vector3 const& _max);

		static std::unique_ptr<_PixelInfo, std::function<void(_PixelInfo*)>> pixel_collider_nullptr_;
		static std::shared_ptr<CollisionGroup> collision_group_nullptr_;

		std::unordered_map<std::string, std::unique_ptr<_PixelInfo, std::function<void(_PixelInfo*)>>> pixel_collider_map_{};
		std::unordered_map<std::string, std::shared_ptr<CollisionGroup>> collision_group_map_{};
	};
}
