# pragma once

# include <thread>
# include <chrono>
# include <type_traits>

namespace TimerUtils
{
	template<typename Func>
	inline void SetTimeout(Func&& func, std::chrono::milliseconds delay)
	{
		std::thread([func = std::forward<Func>(func), delay]() {
			std::this_thread::sleep_for(delay);
			func();
		}).detach();
	}

	template<typename Func>
	inline void SetInterval(Func&& func, std::chrono::milliseconds interval)
	{
		std::thread([func = std::forward<Func>(func), interval]() {
			while (true) {
				std::this_thread::sleep_for(interval);
				func();
			}
		}).detach();
	}

	template<typename Func>
	inline void WaitTimeout(Func&& func, std::chrono::milliseconds delay)
	{
		std::this_thread::sleep_for(delay);
		func();
	}
}
