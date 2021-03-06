#pragma once

#include "singleton.h"

namespace DG
{
	class DG_ENGINE_DLL Device final : public Singleton<Device>
	{
		friend class Singleton<Device>;
	public:
		void Initialize(HWND _window);
		void Clear();
		void Present();
		void ReportLiveObjects();

		Microsoft::WRL::ComPtr<ID3D11Device> const& device() const;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> const& context() const;

		Microsoft::WRL::ComPtr<ID2D1RenderTarget> const& d2d_render_target() const;

	private:
		Device() = default;
		Device(Device const&) = delete;
		Device(Device&&) noexcept = delete;
		Device& operator=(Device const&) = delete;
		Device& operator=(Device&&) noexcept = delete;

		virtual void _Release() override;

		// Direct3D
		HMODULE DXGIDebug_{};
		Microsoft::WRL::ComPtr<IDXGIDebug> debug_{};
		Microsoft::WRL::ComPtr<ID3D11Device> device_{};
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> context_{};
		Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain_{};
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RTV_{};
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DSV_{};

		// Direct2D
		Microsoft::WRL::ComPtr<ID2D1RenderTarget> d2d_render_target_{};
		Microsoft::WRL::ComPtr<ID2D1Factory> d2d_factory_{};
	};
}