#pragma once

#include <DGEngine_stdafx.h>
#include <Scene/scene_component.h>

namespace DG
{
	class StartScene final : public SceneComponent
	{
		friend class Scene;
	public:
		virtual void Initialize() override;

	private:
		StartScene() = default;
		StartScene(StartScene const& _other);
		StartScene(StartScene&& _other) noexcept;
		StartScene& operator=(StartScene const&) = default;
		StartScene& operator=(StartScene&&) noexcept = default;

		virtual void _Release() override;

		virtual std::unique_ptr<SceneComponent, std::function<void(SceneComponent*)>> _Clone() const override;

		void _CreatePrototypes();

		void _StartButtonCallback(float _time);
	};
}