#pragma once

namespace DG
{
	class Timer
	{
		friend class Core;
	public:
		void Initialize();
		void Update();

		float delta_time() const;
		int frame_per_second() const;

	private:
		Timer() = default;
		Timer(Timer const&) = delete;
		Timer(Timer&&) noexcept = delete;
		Timer& operator=(Timer const&) = delete;
		Timer& operator=(Timer&&) noexcept = delete;

		std::chrono::time_point<std::chrono::high_resolution_clock> last_time_point_{};
		float delta_time_{};
		int frame_per_second_{};
	};
}