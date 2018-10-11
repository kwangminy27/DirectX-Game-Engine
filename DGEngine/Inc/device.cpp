#include "DGEngine_stdafx.h"
#include "device.h"

using namespace std;
using namespace DirectX::Colors;
using namespace DG;

using Microsoft::WRL::ComPtr;

void Device::Initialize(HWND _window)
{
	try
	{
		UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
		flags |= D3D11_CREATE_DEVICE_DEBUG;

		DXGIDebug_ = LoadLibrary(L"DXGIDebug.dll");
		ThrowIfFailed(reinterpret_cast<HRESULT(*)(REFIID, void**)>(GetProcAddress(DXGIDebug_, "DXGIGetDebugInterface"))(__uuidof(IDXGIDebug), &debug_));
#endif
		std::array<D3D_FEATURE_LEVEL, 1> d3d_feature_levels{ D3D_FEATURE_LEVEL_11_0 };
		ThrowIfFailed(D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			flags,
			d3d_feature_levels.data(),
			static_cast<UINT>(d3d_feature_levels.size()),
			D3D11_SDK_VERSION,
			&device_,
			nullptr,
			&context_
		));

		ComPtr<IDXGIDevice> device{};
		ComPtr<IDXGIAdapter> adapter{};
		ComPtr<IDXGIFactory> factory{};
		ThrowIfFailed(device_.As(&device));
		ThrowIfFailed(device->GetAdapter(&adapter));
		ThrowIfFailed((adapter->GetParent(__uuidof(IDXGIFactory), &factory)));

		DXGI_SWAP_CHAIN_DESC swap_chain_desc{};
		swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		swap_chain_desc.SampleDesc.Count = 1;
		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.BufferCount = 2;
		swap_chain_desc.OutputWindow = _window;
		swap_chain_desc.Windowed = true;
		swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		ThrowIfFailed((factory->CreateSwapChain(device_.Get(), &swap_chain_desc, &swap_chain_)));

		ComPtr<ID3D11Texture2D> buffer{};
		ThrowIfFailed(swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), &buffer));
		ThrowIfFailed(device_->CreateRenderTargetView(buffer.Get(), nullptr, &RTV_));

		D3D11_TEXTURE2D_DESC depth_stencil_buffer_desc{};
		depth_stencil_buffer_desc.Width = static_cast<UINT>(RESOLUTION::WIDTH);
		depth_stencil_buffer_desc.Height = static_cast<UINT>(RESOLUTION::HEIGHT);
		depth_stencil_buffer_desc.MipLevels = 1;
		depth_stencil_buffer_desc.ArraySize = 1;
		depth_stencil_buffer_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_stencil_buffer_desc.SampleDesc.Count = 1;
		depth_stencil_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		depth_stencil_buffer_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		ThrowIfFailed(device_->CreateTexture2D(&depth_stencil_buffer_desc, nullptr, &buffer));

		D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc{};
		depth_stencil_view_desc.Format = depth_stencil_buffer_desc.Format;
		depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		ThrowIfFailed(device_->CreateDepthStencilView(buffer.Get(), &depth_stencil_view_desc, &DSV_));

		D3D11_VIEWPORT viewport{};
		viewport.Width = static_cast<int>(RESOLUTION::WIDTH);
		viewport.Height = static_cast<int>(RESOLUTION::HEIGHT);
		viewport.MaxDepth = 1.f;

		context_->RSSetViewports(1, &viewport);
		context_->OMSetRenderTargets(1, RTV_.GetAddressOf(), DSV_.Get());
	}
	catch (exception const& _e)
	{
		cerr << _e.what() << endl;
	}
	catch (...)
	{
		cerr << "Device::Initialize" << endl;
	}
}

void Device::Clear()
{
	context_->ClearRenderTargetView(RTV_.Get(), PaleGreen);
	context_->ClearDepthStencilView(DSV_.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void Device::Present()
{
	swap_chain_->Present(0, NULL);

	// SWAP_EFFECT_FLIP_DISCARD
	context_->OMSetRenderTargets(0, nullptr, nullptr);
	context_->OMSetRenderTargets(1, RTV_.GetAddressOf(), DSV_.Get());
}

void Device::ReportLiveObjects()
{
#ifdef _DEBUG
	try
	{
		ThrowIfFailed(debug_->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_DETAIL));
	}
	catch (exception const& _e)
	{
		cerr << _e.what() << endl;
	}
	catch (...)
	{
		cerr << "Device::ReportLiveObjects" << endl;
	}
#endif
}

ComPtr<ID3D11Device> const& Device::device() const
{
	return device_;
}

ComPtr<ID3D11DeviceContext> const& Device::context() const
{
	return context_;
}

void Device::_Release()
{
#ifdef _DEBUG
	FreeLibrary(DXGIDebug_);
#endif
	context_->ClearState();
}