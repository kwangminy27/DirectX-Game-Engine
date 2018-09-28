#include "DGEngine_stdafx.h"
#include "rendering_manager.h"

#include "shader_manager.h"

void DG::RenderingManager::Initialize()
{
	DG::ShaderManager::singleton()->Initialize();
}

std::shared_ptr<Shader> DG::RenderingManager::FindShader(std::string const& _tag)
{
	return DG::ShaderManager::singleton()->FindShader(_tag);
}

void DG::RenderingManager::_Release()
{
	DG::ShaderManager::singleton().reset();
}
