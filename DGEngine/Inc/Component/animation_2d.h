#pragma once

#include "component.h"

namespace DG
{
	class DG_ENGINE_DLL Animation2D final : public Component
	{
		friend class Object;
	public:
		virtual void Initialize() override;

		void AddClip(std::string const& _tag);
		std::shared_ptr<Animation2DClipDesc> const& FindAnimation2DClip(std::string const& _tag) const;
		void UpdateAnimation2DConstantBuffer(float _time);
		void SetDefaultClip(std::shared_ptr<Animation2DClipDesc> const& _animation_2d_clip);
		void ChangeClip(std::string const& _tag);

	protected:
		Animation2D() = default;
		Animation2D(Animation2D const& _other);
		Animation2D(Animation2D&& _other) noexcept;
		Animation2D& operator=(Animation2D const&) = default;
		Animation2D& operator=(Animation2D&&) noexcept = default;

		virtual void _Release() override;

		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;

		static std::shared_ptr<Animation2DClipDesc> animation_2d_clip_nullptr_;
		int frame_idx_{};
		float elapsed_time_{};
		std::unordered_map<std::string, std::shared_ptr<Animation2DClipDesc>> animation_2d_clip_map_{};
		std::shared_ptr<Animation2DClipDesc> current_clip_{};
		std::string default_clip_tag_{};
	};
}
