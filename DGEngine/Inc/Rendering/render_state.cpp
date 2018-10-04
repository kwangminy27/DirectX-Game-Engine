#include "DGEngine_stdafx.h"
#include "render_state.h"

using namespace DG;

RenderState::RenderState(RenderState const& _other) : Tag(_other)
{
	state_ = _other.state_;
}

RenderState::RenderState(RenderState&& _other) noexcept : Tag(std::move(_other))
{
	state_ = std::move(_other.state_);
}

void RenderState::_Release()
{
}
