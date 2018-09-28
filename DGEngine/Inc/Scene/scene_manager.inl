#pragma once

#include "scene.h"

using namespace DG;

template <typename T>
void SceneManager::AddSceneComponent(std::string const& _tag)
{
	scene_->_AddSceneComponent<T>(_tag);
}
