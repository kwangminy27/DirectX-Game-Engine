#pragma once

#include "singleton.h"

namespace DG
{
	class Scene;
	class Object;

	class DG_ENGINE_DLL SceneManager final : public Singleton<SceneManager>
	{
		friend class Singleton<SceneManager>;
	public:
		void Initialize();
		void Input(float _time);
		void Update(float _time);
		void LateUpdate(float _time);
		void Collision(float _time);
		void Render(float _time);

		template <typename T> void AddSceneComponent(std::string const& _tag);
		std::shared_ptr<Object> const& FindObject(std::string const& _tag) const;

		std::shared_ptr<Scene> scene() const;
		std::shared_ptr<Scene> next_scene() const;

	private:
		SceneManager() = default;
		SceneManager(SceneManager const&) = delete;
		SceneManager(SceneManager&&) noexcept = delete;
		SceneManager& operator=(SceneManager const&) = delete;
		SceneManager& operator=(SceneManager&&) noexcept = delete;

		virtual void _Release() override;

		std::shared_ptr<Scene> _CreateScene(std::string const& _tag);

		std::shared_ptr<Scene> scene_{};
		std::shared_ptr<Scene> next_scene_{};
	};
}

#include "scene_manager.inl"
