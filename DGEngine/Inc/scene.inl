#pragma once

using namespace std;
using namespace DG;

template <typename T>
void Scene::_AddSceneComponent(string const& _tag)
{
	auto scene_component = shared_ptr<SceneComponent>{ new T, [](SceneComponent* _p) {
		_p->_Release();
		delete _p;
	} };

	scene_component->set_tag(_tag);
	scene_component->set_scene(shared_from_this());

	scene_component->_Initialize();

	scene_component_list_.push_back(move(scene_component));
}
