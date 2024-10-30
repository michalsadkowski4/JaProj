#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <functional>
#include <thread>

class ThreadPool {
	void SubmitTask(std::function<void()> task);
	void SetThreadCount(int count);
	void Shutdown();
};
#endif // THREAD_POOL_H