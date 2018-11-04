#include "DGNetwork_stdafx.h"
#include "thread_manager.h"

#include "thread.h"

using namespace DG;

std::unique_ptr<Thread, std::function<void(Thread*)>> ThreadManager::thread_nullptr_{};

void ThreadManager::Initialize()
{
}

std::unique_ptr<Thread, std::function<void(Thread*)>> const& ThreadManager::FindThread(std::string const& _tag) const
{
	auto iter = thread_map_.find(_tag);

	if (iter == thread_map_.end())
		return thread_nullptr_;

	return iter->second;
}

void ThreadManager::CreateThread(std::string const& _tag, std::function<void(void*)> const& _function, void* _argument)
{
	auto const& iter = FindThread(_tag);

	Task task{};
	task.function = _function;
	task.argument = _argument;

	if (iter)
	{
		iter->_AddTask(task);
		iter->_Run();
	}
	else
	{
		auto new_thread = std::unique_ptr<Thread, std::function<void(Thread*)>>{ new Thread, [](Thread* _p) {
			_p->_Release();
			delete _p;
		} };

		new_thread->_AddTask(task);
		new_thread->_Run();

		thread_map_.insert(std::make_pair(_tag, std::move(new_thread)));
	}
}

std::mutex& ThreadManager::debug_mutex()
{
	return debug_mutex_;
}

std::queue<std::string>& ThreadManager::debug_message_queue()
{
	return debug_message_queue_;
}

void ThreadManager::_Release()
{
	for (auto const& _thread : thread_map_)
		_thread.second->thread_.join();
}
