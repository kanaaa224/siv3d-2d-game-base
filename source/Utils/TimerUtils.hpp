# pragma once

# include <chrono>
# include <functional>
# include <vector>
# include <algorithm>

namespace TimerUtils
{
	using std::chrono::milliseconds;
	using std::chrono::steady_clock;
	using namespace std::chrono_literals;

	struct Task
	{
		size_t id = 0;

		bool repeat = false;
		bool done   = false;

		double delayTime = 0.0;
		double lastTime  = 0.0;

		std::function<void()> func;
	};

	inline std::vector<Task>& GetTasks()
	{
		static std::vector<Task> tasks;

		return tasks;
	}

	inline void ClearTasks()
	{
		GetTasks().clear();
	}

	inline double& GetRunningTime()
	{
		static double runningTime = 0.0;

		return runningTime;
	}

	inline steady_clock::time_point& GetLastClock()
	{
		static auto lastClock = steady_clock::now();

		return lastClock;
	}

	inline size_t GenerateTaskID()
	{
		static std::atomic_size_t counter = 1;

		return counter++;
	}

	inline void Update()
	{
		auto  now  = steady_clock::now();
		auto& last = GetLastClock();

		double delta = std::chrono::duration<double>(now - last).count();

		last = now;

		auto& runningTime = GetRunningTime();

		runningTime += delta;

		std::vector<std::function<void()>> pendingCalls;

		for (auto& task : GetTasks())
		{
			if (!task.done && (runningTime - task.lastTime) >= task.delayTime)
			{
				task.lastTime = runningTime;

				pendingCalls.push_back(task.func);

				if (!task.repeat) task.done = true;
			}
		}

		for (const auto& func : pendingCalls) func();

		auto& tasks = GetTasks();

		tasks.erase(std::remove_if(tasks.begin(), tasks.end(), [](const Task& t) { return t.done; }), tasks.end());
	}

	template<typename Func>
	inline size_t SetTimeout(Func&& func, milliseconds delay = 0s)
	{
		size_t id = GenerateTaskID();

		GetTasks().push_back({
			id, false, false,

			delay.count() / 1000.0,

			GetRunningTime(),

			std::forward<Func>(func)
		});

		return id;
	}

	template<typename Func>
	inline size_t SetInterval(Func&& func, milliseconds interval = 0s)
	{
		size_t id = GenerateTaskID();

		GetTasks().push_back({
			id, true, false,

			interval.count() / 1000.0,

			GetRunningTime(),

			std::forward<Func>(func)
		});

		return id;
	}

	inline void CancelTask(size_t id)
	{
		auto& tasks = GetTasks();

		for (auto& task : tasks)
		{
			if (task.id == id)
			{
				task.done = true;

				break;
			}
		}
	}

#ifdef _DEBUG
#include <thread>
	template<typename Func>
	inline void WaitTimeout(Func&& func, milliseconds delay = 0s)
	{
		std::this_thread::sleep_for(delay);

		func();
	}
#endif
}
