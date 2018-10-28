#include "DGNetwork_stdafx.h"
#include "thread.h"

using namespace DG;

void Thread::_Release()
{
}

void Thread::_AddTask(Task const& _task)
{
	mutex_.lock();

	task_list_.push_back(_task);

	mutex_.unlock();
}

void Thread::_Run()
{
	mutex_.lock();

	for (auto const& _task : task_list_)
		thread_ = std::thread{ _task.function, _task.argument };

	mutex_.unlock();
}

size_t Thread::_GetTaskCount()
{
	return task_list_.size();
}
