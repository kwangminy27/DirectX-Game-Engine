#pragma once

#include "scene.h"

using namespace DG;

template <typename T>
void SceneManager::AddSceneComponent(std::string const& _tag, bool _next_scene_flag)
{
	if(!_next_scene_flag)
		scene_->_AddSceneComponent<T>(_tag);
	else
		next_scene_->_AddSceneComponent<T>(_tag);
}
