#include "DGEngine_stdafx.h"
#include "depth_stencil_state.h"

#include "device.h"

using namespace DG;

void DepthStencilState::Initialize()
{
	type_ = RENDER_STATE_TYPE::DEPTH_STENCIL;
}

DepthStencilState::DepthStencilState(DepthStencilState const& _other) : RenderState(_other)
{
	stencil_ref_ = _other.stencil_ref_;
	old_stencil_ref_ = _other.old_stencil_ref_;
}

DepthStencilState::DepthStencilState(DepthStencilState&& _other) noexcept : RenderState(std::move(_other))
{
	stencil_ref_ = std::move(_other.stencil_ref_);
	old_stencil_ref_ = std::move(_other.old_stencil_ref_);
}

void DepthStencilState::_Release()
{
}

void DepthStencilState::_SetState()
{
	auto const& context = Device::singleton()->context();

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_stencil_state{};

	context->OMGetDepthStencilState(&depth_stencil_state, &old_stencil_ref_);

	if (depth_stencil_state)
		ThrowIfFailed(depth_stencil_state.As(&old_state_));

	context->OMSetDepthStencilState(static_cast<ID3D11DepthStencilState*>(state_.Get()), stencil_ref_);
}

void DepthStencilState::_SetBackState()
{
	Device::singleton()->context()->OMSetDepthStencilState(static_cast<ID3D11DepthStencilState*>(old_state_.Get()), old_stencil_ref_);
}

void DepthStencilState::_CreateState(
	BOOL _depth_enable,
	D3D11_DEPTH_WRITE_MASK _depth_write_mask,
	D3D11_COMPARISON_FUNC _depth_func,
	BOOL _stencil_enable,
	UINT8 _stencil_read_mask,
	UINT8 _stencil_write_mask,
	D3D11_DEPTH_STENCILOP_DESC const& _front_face,
	D3D11_DEPTH_STENCILOP_DESC const& _back_face)
{
	auto const& device = Device::singleton()->device();

	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc{};
	depth_stencil_desc.DepthEnable = _depth_enable;
	depth_stencil_desc.DepthWriteMask = _depth_write_mask;
	depth_stencil_desc.DepthFunc = _depth_func;
	depth_stencil_desc.StencilEnable = _stencil_enable;
	depth_stencil_desc.StencilReadMask = _stencil_read_mask;
	depth_stencil_desc.StencilWriteMask = _stencil_write_mask;
	depth_stencil_desc.FrontFace = _front_face;
	depth_stencil_desc.BackFace = _back_face;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_stencil_state{};
	device->CreateDepthStencilState(&depth_stencil_desc, &depth_stencil_state);
	ThrowIfFailed(depth_stencil_state.As(&state_));
}
