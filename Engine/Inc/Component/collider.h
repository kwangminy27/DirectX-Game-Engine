#pragma once

#include "component.h"

namespace DG
{
#ifdef _DEBUG
	class Mesh;
	class Shader;
#endif

	class DG_ENGINE_DLL Collider : public Component, public std::enable_shared_from_this<Collider>
	{
		friend class Object;
		friend class CollisionManager;
	public:
		virtual void Initialize() override;

		virtual bool Collision(std::shared_ptr<Collider> const& _dest, float _time) = 0;

		COLLIDER_TYPE collider_type() const;
		std::string const& collision_group_tag() const;
		bool update_flag() const;
		Math::Vector3 const& collider_min() const;
		Math::Vector3 const& collider_max() const;
		std::list<int> const& section_idx_list() const;

		void set_collision_group_tag(std::string const& _tag);
		void set_pivot(Math::Vector3 const& _pivot);

#ifdef _DEBUG
		void set_mesh_tag(std::string const& _tag);
		void set_shader_tag(std::string const& _tag);
		void set_color(Math::Vector4 const& _color);
#endif

	protected:
		Collider() = default;
		Collider(Collider const& _other);
		Collider(Collider&& _other) noexcept;
		Collider& operator=(Collider const&) = default;
		Collider& operator=(Collider&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Render(float _time) override;
		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const = 0;

		void _AddCallback(std::function<void(std::shared_ptr<Collider> const&, std::shared_ptr<Collider> const&, float)> const& _function, COLLISION_CALLBACK_TYPE _type);

		void _AddSection(int _idx);
		void _ClearSection();

		void _AddCollidedCollider(std::shared_ptr<Collider> const& _dest);
		void _UpdateCollidedCollider(float _time); // 이전 프레임에 충돌했던 충돌체들과 그룹이나 섹션이 틀어지는 경우 처리.
		bool _IsCollidedCollider(std::shared_ptr<Collider> const& _dest);
		void _EraseCollidedCollider(std::shared_ptr<Collider> const& _dest);

		void _OnCollisionEnter(std::shared_ptr<Collider> const& _dest, float _time);
		void _OnCollision(std::shared_ptr<Collider> const& _dest, float _time);
		void _OnCollisionLeave(std::shared_ptr<Collider> const& _dest, float _time);

		bool _CollisionRectToRect(RectInfo const& _src, RectInfo const& _dest);

		COLLIDER_TYPE collider_type_{};
		std::string collision_group_tag_{};
		bool update_flag_{};
		Math::Vector3 pivot_{};
		Math::Vector3 collider_min_{};
		Math::Vector3 collider_max_{};
		std::list<int> section_idx_list_{};
		std::list<std::weak_ptr<Collider>> collided_collider_list_{};
		std::array<std::list<std::function<void(std::shared_ptr<Collider> const&, std::shared_ptr<Collider> const&, float)>>, static_cast<int>(COLLISION_CALLBACK_TYPE::END)> collision_callback_list_array_{};

#ifdef _DEBUG
		std::string mesh_tag_{};
		std::string shader_tag_{};
		Math::Vector4 color_{};
#endif
	};
}
