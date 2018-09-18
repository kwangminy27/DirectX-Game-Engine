#pragma once

#include "singleton.h"

namespace DG
{
	class Device final : public Singleton<Device>
	{
		friend class Singleton<Device>;
	public:
		void DG_DLL Initialize(HWND _window);
		void DG_DLL Clear();
		void DG_DLL Present();
		void DG_DLL ReportLiveObjects();

	private:
		Device() = default;
		Device(Device const&) = delete;
		Device(Device&&) noexcept = delete;
		Device& operator=(Device const&) = delete;
		Device& operator=(Device&&) noexcept = delete;

		virtual void DG_DLL _Release() override;

		HMODULE DXGIDebug_{};
		Microsoft::WRL::ComPtr<IDXGIDebug> debug_{};
		Microsoft::WRL::ComPtr<ID3D11Device> device_{};
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> context_{};
		Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain_{};
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RTV_{};
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DSV_{};
	};
}