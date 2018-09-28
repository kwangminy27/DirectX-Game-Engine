#pragma once

#include "tag.h"

namespace DG
{
	class Scene;

	class DG_ENGINE_DLL SceneComponent : public Tag
	{
		friend class Scene;
	public:
		virtual void Initialize() = 0;

		std::shared_ptr<Scene> scene() const;

		void set_scene(std::shared_ptr<Scene> const& _scene);

	protected:
		SceneComponent() = default;
		SceneComponent(SceneComponent const& _other);
		SceneComponent(SceneComponent&& _other) noexcept;
		SceneComponent& operator=(SceneComponent const&) = default;
		SceneComponent& operator=(SceneComponent&&) noexcept = default;

		virtual void _Release() override;

		virtual void _Input(float _time);
		virtual void _Update(float _time);
		virtual void _LateUpdate(float _time);
		virtual void _Collision(float _time);
		virtual void _Render(float _time);
		virtual std::unique_ptr<SceneComponent, std::function<void(SceneComponent*)>> _Clone() const = 0;

		std::weak_ptr<Scene> scene_{};
	};
}
