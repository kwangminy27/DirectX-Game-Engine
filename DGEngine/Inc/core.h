#pragma once

#include "singleton.h"

namespace DG
{
	class Core final : public Singleton<Core>
	{
		friend class Singleton<Core>;
	public:
		void DG_DLL Initialize(std::wstring const& _class_name, std::wstring const& _window_name, HINSTANCE _instance, int _icon);
		void DG_DLL Run();

	private:
		Core() = default;
		Core(Core const&) = delete;
		Core(Core&&) noexcept = delete;
		Core& operator=(Core const&) = delete;
		Core& operator=(Core&&) noexcept = delete;

		virtual void DG_DLL _Release() override;

		static LRESULT CALLBACK _WindowProc(HWND _window, UINT _message, WPARAM _w_param, LPARAM _l_param);
		void _RegisterClass(std::wstring const& _class_name, int _icon);
		void _CreateWindow(std::wstring const& _class_name, std::wstring const& _window_name);

		static MESSAGE_LOOP state_;
		HINSTANCE instance_{};
		HWND window_{};
	};
}