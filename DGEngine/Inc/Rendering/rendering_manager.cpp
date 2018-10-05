#include "DGEngine_stdafx.h"
#include "rendering_manager.h"

#include "shader_manager.h"
#include "render_state.h"
#include "blend_state.h"

using namespace DG;

std::shared_ptr<RenderState> RenderingManager::render_state_nullptr_{};

void RenderingManager::Initialize()
{
	try
	{
		ShaderManager::singleton()->Initialize();

		AddRenderTargetBlendDesc(true);
		CreateBlendState("AlphaBlend", false, false);
	}
	catch (std::exception const& _e)
	{
		std::cerr << _e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "RenderingManager::Initialize()" << std::endl;
	}
}

void RenderingManager::AddRenderTargetBlendDesc(
	bool _blend_enable,
	D3D11_BLEND _src_blend,
	D3D11_BLEND _dest_blend,
	D3D11_BLEND_OP _blend_op,
	D3D11_BLEND _src_blend_alpha,
	D3D11_BLEND _dest_blend_alpha,
	D3D11_BLEND_OP _blend_op_alpha,
	UINT8 render_target_write_mask)
{
	if (!render_state_nullptr_)
	{
		render_state_nullptr_ = std::shared_ptr<RenderState>{ new BlendState, [](BlendState* _p) {
			_p->_Release();
			delete _p;
		} };
	}

	std::dynamic_pointer_cast<BlendState>(render_state_nullptr_)->_AddRenderTargetBlendDesc(
		_blend_enable,
		_src_blend,
		_dest_blend,
		_blend_op,
		_src_blend_alpha,
		_dest_blend_alpha,
		_blend_op_alpha,
		render_target_write_mask
	);
}

void RenderingManager::CreateBlendState(std::string const& _tag, bool _alpha_to_coverage_enable, bool _independent_blend_enable)
{
	if (!render_state_nullptr_)
		throw std::exception{ "RenderingManager::CreateBlendState" };

	std::dynamic_pointer_cast<BlendState>(render_state_nullptr_)->_CreateBlendState(_alpha_to_coverage_enable, _independent_blend_enable);
	render_state_map_.insert(std::make_pair(_tag, move(render_state_nullptr_)));
}

std::shared_ptr<Shader> const& RenderingManager::FindShader(std::string const& _tag) const
{
	return ShaderManager::singleton()->FindShader(_tag);
}

std::shared_ptr<RenderState> const& RenderingManager::FindRenderState(std::string const& _tag) const
{
	auto iter = render_state_map_.find(_tag);

	if (iter == render_state_map_.end())
		return render_state_nullptr_;

	return iter->second;
}

void RenderingManager::UpdateConstantBuffer(std::string const& _tag, void* _data)
{
	return ShaderManager::singleton()->_UpdateConstantBuffer(_tag, _data);
}

void RenderingManager::_Release()
{
	ShaderManager::singleton().reset();
}
