#pragma once

#include "component.h"

namespace DG
{
	class Mesh;
	class Shader;

	class DG_ENGINE_DLL Collider : public Component
	{
		friend class Object;
		friend class CollisionManager;
	public:
		virtual void Initialize() override;

		virtual bool Collision(Collider* _dest, float _time) = 0;

		void AddCallback(std::function<void(Collider*, Collider*, float)> const& _function, COLLISION_CALLBACK_TYPE _type);

		COLLIDER_TYPE collider_type() const;
		std::string const& collision_group_tag() const;
		bool update_flag() const;
		Math::Vector3 const& collider_min() const;
		Math::Vector3 const& collider_max() const;
		std::list<int> const& section_idx_list() const;

		void set_collision_group_tag(std::string const& _tag);
		void set_pivot(Math::Vector3 const& _pivot);

		void set_mesh_tag(std::string const& _tag);
		void set_shader_tag(std::string const& _tag);
		void set_color(Math::Vector4 const& _color);

	protected:
		Collider() = default;
		Collider(Collider const& _other);
		Collider(Collider&& _other) noexcept;
		Collider& operator=(Collider const&) = default;
		Collider& operator=(Collider&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Render(float _time) override;
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const = 0;

		void _AddSection(int _idx);
		void _ClearSection();

		void _AddCollidedCollider(Collider* _dest);
		void _UpdateCollidedCollider(float _time); // 이전 프레임에 충돌했던 충돌체들 갱신
		bool _IsCollidedCollider(Collider* _dest);
		void _EraseCollidedCollider(Collider* _dest);

		void _OnCollisionEnter(Collider* _dest, float _time);
		void _OnCollision(Collider* _dest, float _time);
		void _OnCollisionLeave(Collider* _dest, float _time);

		bool _CollisionOOBBToOOBB(OOBBInfo const& _src, OOBBInfo const& _dest);
		bool _CollisionOOBBToCircle(OOBBInfo const& _src, CircleInfo const& _dest);
		bool _CollisionOOBBToRect(OOBBInfo const& _src, RectInfo const& _dest);
		bool _CollisionOOBBToPoint(OOBBInfo const& _src, Math::Vector3 const& _dest);

		bool _CollisionCircleToCircle(CircleInfo const& _src, CircleInfo const& _dest);
		bool _CollisionCircleToRect(CircleInfo const& _src, RectInfo const& _dest);
		bool _CollisionCircleToPoint(CircleInfo const& _src, Math::Vector3 const& _dest);

		bool _CollisionRectToRect(RectInfo const& _src, RectInfo const& _dest);
		bool _CollisionRectToPoint(RectInfo const& _src, Math::Vector3 const& _dest);

		bool _CollisionPointToPoint(Math::Vector3 const& _src, Math::Vector3 const& _dest);

		COLLIDER_TYPE collider_type_{};
		std::string collision_group_tag_{};
		bool update_flag_{};
		Math::Vector3 pivot_{};
		// collider min·max는 충돌체가 속할 section의 idx를 구할 때 사용된다.
		Math::Vector3 collider_min_{};
		Math::Vector3 collider_max_{};
		std::list<int> section_idx_list_{};
		std::list<Collider*> collided_collider_list_{};
		std::array<std::list<std::function<void(Collider*, Collider*, float)>>, static_cast<int>(COLLISION_CALLBACK_TYPE::END)> collision_callback_list_array_{};

		std::string mesh_tag_{};
		std::string shader_tag_{};
		Math::Vector4 color_{};
	};
}
