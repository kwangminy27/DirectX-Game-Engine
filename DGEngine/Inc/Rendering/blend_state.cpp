#include "DGEngine_stdafx.h"
#include "blend_state.h"

using namespace DG;

BlendState::BlendState(BlendState const& _other) : RenderState(_other)
{
}

BlendState::BlendState(BlendState&& _other) noexcept : RenderState(std::move(_other))
{
}

void BlendState::_Release()
{
}
