#include "DGEngine_stdafx.h"
#include "render_state.h"

using namespace DG;

RENDER_STATE_TYPE RenderState::type() const
{
	return type_;
}

RenderState::RenderState(RenderState const& _other) : Tag(_other)
{
	state_ = _other.state_;
	old_state_ = _other.old_state_;
	type_ = _other.type_;
}

RenderState::RenderState(RenderState&& _other) noexcept : Tag(std::move(_other))
{
	state_ = std::move(_other.state_);
	old_state_ = std::move(_other.old_state_);
	type_ = std::move(_other.type_);
}

void RenderState::_Release()
{
}
