#pragma once

#include <DGEngine_stdafx.h>
#include <Scene/scene_component.h>

namespace DG
{
	class MainSceneComponent final : public SceneComponent
	{
		friend class Scene;
	public:
		virtual void Initialize() override;

	private:
		MainSceneComponent() = default;
		MainSceneComponent(MainSceneComponent const& _other);
		MainSceneComponent(MainSceneComponent&& _other) noexcept;
		MainSceneComponent& operator=(MainSceneComponent const&) = default;
		MainSceneComponent& operator=(MainSceneComponent&&) noexcept = default;

		virtual void _Release() override;

		virtual std::unique_ptr<SceneComponent, std::function<void(SceneComponent*)>> _Clone() const override;
	};
}
