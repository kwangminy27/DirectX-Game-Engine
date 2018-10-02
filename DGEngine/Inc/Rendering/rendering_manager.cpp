#include "DGEngine_stdafx.h"
#include "rendering_manager.h"

#include "shader_manager.h"

using namespace DG;

void RenderingManager::Initialize()
{
	ShaderManager::singleton()->Initialize();
}

void RenderingManager::UpdateConstantBuffer(std::string const& _tag, void* _data)
{
	return ShaderManager::singleton()->_UpdateConstantBuffer(_tag, _data);
}

std::shared_ptr<Shader> RenderingManager::FindShader(std::string const& _tag)
{
	return ShaderManager::singleton()->FindShader(_tag);
}

void RenderingManager::_Release()
{
	ShaderManager::singleton().reset();
}
