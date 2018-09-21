#pragma once

#include "tag.h"

namespace DG
{
	class Scene;

	class SceneComponent : public Tag
	{
		friend class Scene;
	public:
		std::shared_ptr<Scene> scene() const;

		void set_scene(std::shared_ptr<Scene> const& _scene);

	protected:
		SceneComponent() = default;
		SceneComponent(SceneComponent const& _other);
		SceneComponent(SceneComponent&& _other) noexcept;
		SceneComponent& operator=(SceneComponent const&) = default;
		SceneComponent& operator=(SceneComponent&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Initialize() = 0;
		virtual void _Input(float _time);
		virtual void _Update(float _time);
		virtual void _LateUpdate(float _time);
		virtual void _Collision(float _time);
		virtual void _Render(float _time);

		std::weak_ptr<Scene> scene_{};
	};
}
