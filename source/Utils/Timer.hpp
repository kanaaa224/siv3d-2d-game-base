# pragma once

# include <Siv3D.hpp>
# include <chrono>
# include <functional>

namespace TimerUtils
{
	using std::chrono::milliseconds;
	using std::chrono::duration_cast;

	struct Task
	{
		bool repeat = false;
		bool done   = false;

		double delayTime = 0.0;
		double lastTime  = 0.0;

		std::function<void()> func;
	};

	inline Array<Task>& GetTasks()
	{
		static Array<Task> tasks;

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

	inline void Update()
	{
		auto& runningTime = GetRunningTime();

		runningTime += Scene::DeltaTime();

		for (auto& task : GetTasks())
		{
			if (!task.done && (runningTime - task.lastTime) >= task.delayTime)
			{
				task.lastTime = runningTime;

				task.func();

				if (!task.repeat) task.done = true;
			}
		}

		GetTasks().remove_if([](const Task& t) { return t.done; });
	}

	template<typename Func>
	inline void SetTimeout(Func&& func, milliseconds delay)
	{
		GetTasks().push_back({
			.repeat = false,
			.done   = false,

			.delayTime = delay.count() / 1000.0,
			.lastTime  = GetRunningTime(),

			.func = std::forward<Func>(func)
		});
	}

	template<typename Func>
	inline void SetInterval(Func&& func, milliseconds interval)
	{
		GetTasks().push_back({
			.repeat = true,
			.done   = false,

			.delayTime = interval.count() / 1000.0,
			.lastTime  = GetRunningTime(),

			.func = std::forward<Func>(func)
		});
	}

	template<typename Func>
	inline void WaitTimeout(Func&& func, milliseconds delay)
	{
		System::Sleep(delay.count());

		func();
	}
}
