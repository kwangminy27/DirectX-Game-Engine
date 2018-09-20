#include "DGEngine_stdafx.h"
#include "rendering_manager.h"

#include "shader_manager.h"

using namespace std;
using namespace DG;

void RenderingManager::Initialize()
{
	ShaderManager::singleton()->Initialize();
}

void RenderingManager::_Release()
{
	ShaderManager::singleton().reset();
}
