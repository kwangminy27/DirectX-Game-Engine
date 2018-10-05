#include "DGEngine_stdafx.h"
#include "blend_state.h"

#include "device.h"

using namespace DG;

void BlendState::Initialize()
{
	type_ = RENDER_STATE_TYPE::BLEND;
}

BlendState::BlendState(BlendState const& _other) : RenderState(_other)
{
	render_target_blend_desc_vector_buffer_ = _other.render_target_blend_desc_vector_buffer_;
}

BlendState::BlendState(BlendState&& _other) noexcept : RenderState(std::move(_other))
{
	render_target_blend_desc_vector_buffer_ = std::move(_other.render_target_blend_desc_vector_buffer_);
}

void BlendState::_Release()
{
}

void BlendState::_SetState()
{
	auto const& context = Device::singleton()->context();

	Microsoft::WRL::ComPtr<ID3D11BlendState> blend_state{};
	UINT sample_mask{ 0xffffffff };

	context->OMGetBlendState(&blend_state, nullptr, &sample_mask);

	if(blend_state)
		ThrowIfFailed(blend_state.As(&old_state_));

	context->OMSetBlendState(static_cast<ID3D11BlendState*>(state_.Get()), nullptr, 0xffffffff);
}

void BlendState::_SetBackState()
{
	Device::singleton()->context()->OMSetBlendState(static_cast<ID3D11BlendState*>(old_state_.Get()), nullptr, 0xffffffff);
}

void BlendState::_AddRenderTargetBlendDesc(
	bool _blend_enable,
	D3D11_BLEND _src_blend,
	D3D11_BLEND _dest_blend,
	D3D11_BLEND_OP _blend_op,
	D3D11_BLEND _src_blend_alpha,
	D3D11_BLEND _dest_blend_alpha,
	D3D11_BLEND_OP _blend_op_alpha,
	UINT8 render_target_write_mask)
{
	render_target_blend_desc_vector_buffer_.push_back(
		{ _blend_enable, _src_blend, _dest_blend, _blend_op, _src_blend_alpha, _dest_blend_alpha, _blend_op_alpha, render_target_write_mask }
	);
}

void BlendState::_CreateBlendState(bool _alpha_to_coverage_enable, bool _independent_blend_enable)
{
	auto const& device = Device::singleton()->device();

	D3D11_BLEND_DESC blend_desc{};
	blend_desc.AlphaToCoverageEnable = _alpha_to_coverage_enable;
	blend_desc.IndependentBlendEnable = _independent_blend_enable;

	auto size = sizeof(D3D11_RENDER_TARGET_BLEND_DESC) * render_target_blend_desc_vector_buffer_.size();
	memcpy_s(blend_desc.RenderTarget, size, render_target_blend_desc_vector_buffer_.data(), size);
	render_target_blend_desc_vector_buffer_.clear();

	Microsoft::WRL::ComPtr<ID3D11BlendState> state{};
	ThrowIfFailed(device->CreateBlendState(&blend_desc, &state));
	ThrowIfFailed(state.As(&state_));
}
