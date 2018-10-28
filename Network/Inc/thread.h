#pragma once

namespace DG
{
	struct Task
	{
		std::function<void(void*)> function;
		void* argument;
	};

	class Thread
	{
		friend class ThreadManager;
	private:
		Thread() = default;
		Thread(Thread const&) = delete;
		Thread(Thread&&) noexcept = delete;
		Thread& operator=(Thread const&) = delete;
		Thread& operator=(Thread&&) noexcept = delete;

		void _Release();

		void _AddTask(Task const& _task);
		void _Run();

		size_t _GetTaskCount();

		std::mutex mutex_{};
		std::thread thread_{};
		std::list<Task> task_list_{};
	};
}
