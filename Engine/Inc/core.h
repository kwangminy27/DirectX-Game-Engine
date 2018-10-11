#pragma once

#include "singleton.h"

namespace DG
{
	class Timer;

	class DG_ENGINE_DLL Core final : public Singleton<Core>
	{
		friend class Singleton<Core>;
	public:
		void Initialize(std::wstring const& _class_name, std::wstring const& _window_name, HINSTANCE _instance, int _icon, GAME_MODE _mode);
		void Run();

		void SetDefaultState(GAME_MODE _mode);

	private:
		Core() = default;
		Core(Core const&) = delete;
		Core(Core&&) noexcept = delete;
		Core& operator=(Core const&) = delete;
		Core& operator=(Core&&) noexcept = delete;

		virtual void _Release() override;

		static LRESULT CALLBACK _WindowProc(HWND _window, UINT _message, WPARAM _w_param, LPARAM _l_param);

		void _RegisterClass(std::wstring const& _class_name, int _icon);
		void _CreateWindow(std::wstring const& _class_name, std::wstring const& _window_name);

		void _CreateTimer();

		void _Logic();
		void _Input(float _time);
		void _Update(float _time);
		void _LateUpdate(float _time);
		void _Collision(float _time);
		void _Render(float _time);

		static MESSAGE_LOOP state_;

		HINSTANCE instance_{};
		HWND window_{};

		std::unique_ptr<Timer, std::function<void(Timer*)>> timer_{};
		float time_scale_{};
	};
}