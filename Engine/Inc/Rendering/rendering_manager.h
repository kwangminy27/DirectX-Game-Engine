#pragma once

#include "singleton.h"

namespace DG
{
	class RenderingManager final : public Singleton<RenderingManager>
	{
		friend class Singleton<RenderingManager>;
	public:
		void Initialize();

	private:
		RenderingManager() = default;
		RenderingManager(RenderingManager const&) = delete;
		RenderingManager(RenderingManager&&) noexcept = delete;
		RenderingManager& operator=(RenderingManager const&) = delete;
		RenderingManager& operator=(RenderingManager&&) noexcept = delete;

		virtual void _Release() override;
	};
}
