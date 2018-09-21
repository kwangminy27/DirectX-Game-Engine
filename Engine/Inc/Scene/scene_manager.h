#pragma once

#include "singleton.h"

namespace DG
{
	class Scene;

	class SceneManager final : public Singleton<SceneManager>
	{
		friend class Singleton<SceneManager>;
	public:
		void Initialize();
		void Input(float _time);
		void Update(float _time);
		void LateUpdate(float _time);
		void Collision(float _time);
		void Render(float _time);

	private:
		SceneManager() = default;
		SceneManager(SceneManager const&) = delete;
		SceneManager(SceneManager&&) noexcept = delete;
		SceneManager& operator=(SceneManager const&) = delete;
		SceneManager& operator=(SceneManager&&) noexcept = delete;

		virtual void _Release() override;

		std::shared_ptr<Scene> scene_{};
		std::shared_ptr<Scene> next_scene_{};
	};
}
