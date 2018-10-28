#pragma once

#include "singleton_temp.h"

namespace DG
{
	class Thread;

	class DG_NETWORK_DLL ThreadManager : public Singleton_Temp<ThreadManager>
	{
		friend class Singleton_Temp<ThreadManager>;
	public:
		std::unique_ptr<Thread, std::function<void(Thread*)>> const& FindThread(std::string const& _tag) const;

		void CreateThread(std::string const& _tag, std::function<void(void*)> const& _function, void* _argument);

		std::mutex& debug_mutex();
		std::queue<std::string>& debug_message_queue();

	private:
		ThreadManager() = default;
		ThreadManager(ThreadManager const&) = delete;
		ThreadManager(ThreadManager&&) noexcept = delete;
		ThreadManager& operator=(ThreadManager const&) = delete;
		ThreadManager& operator=(ThreadManager&&) noexcept = delete;

		virtual void _Release() override;

		static std::unique_ptr<Thread, std::function<void(Thread*)>> thread_nullptr_;
		std::unordered_map<std::string, std::unique_ptr<Thread, std::function<void(Thread*)>>> thread_map_{};

		std::mutex debug_mutex_{};
		std::queue<std::string> debug_message_queue_{};
	};
}
