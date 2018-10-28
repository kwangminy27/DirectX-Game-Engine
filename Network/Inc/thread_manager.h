#pragma once

#include "singleton.h"

namespace DG
{
	class DG_NETWORK_DLL ThreadManager : public Singleton<ThreadManager>
	{
		friend class Singleton<ThreadManager>;
	private:
		ThreadManager() = default;
		ThreadManager(ThreadManager const&) = delete;
		ThreadManager(ThreadManager&&) noexcept = delete;
		ThreadManager& operator=(ThreadManager const&) = delete;
		ThreadManager& operator=(ThreadManager&&) noexcept = delete;

		virtual void _Release() override;
	};
}
