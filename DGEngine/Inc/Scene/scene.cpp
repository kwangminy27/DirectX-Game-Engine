#include "DGEngine_stdafx.h"
#include "scene.h"

#include "scene_component.h"
#include "layer.h"

using namespace std;
using namespace DG;

shared_ptr<SceneComponent> const& Scene::FindSceneComponent(string const& _tag) const
{
	for (auto const& scene_component : scene_component_list_)
	{
		if (scene_component->tag() == _tag)
			return scene_component;
	}

	return scene_component_nullptr_;
}

shared_ptr<Layer> const& Scene::FindLayer(string const& _tag) const
{
	for (auto const& layer : layer_list_)
	{
		if (layer->tag() == _tag)
			return layer;
	}

	return layer_nullptr_;
}

Scene::Scene(Scene const& _other) : Tag(_other)
{
	scene_component_list_ = _other.scene_component_list_;
	layer_list_ = _other.layer_list_;
}

Scene::Scene(Scene&& _other) noexcept : Tag(move(_other))
{
	scene_component_list_ = move(_other.scene_component_list_);
	layer_list_ = move(_other.layer_list_);
}

void Scene::_Release()
{
}

void Scene::_AddLayer(string const& _tag, int _z_order)
{
	auto layer = shared_ptr<Layer>{ new Layer, [](Layer* _p) {
		_p->_Release();
		delete _p;
	} };

	layer->set_tag(_tag);
	layer->set_z_order(_z_order);
	layer->set_scene(shared_from_this());

	layer->_Initialize();

	layer_list_.push_back(move(layer));

	layer_list_.sort([](shared_ptr<Layer> const& _left, shared_ptr<Layer> const& _right) {
		return _left->z_order() < _right->z_order();
	});
}

void Scene::_Initialize()
{
	_AddLayer("Default", 0);
	_AddLayer("UI", numeric_limits<int>::max());
}

void Scene::_Input(float _time)
{
	for (auto iter = scene_component_list_.begin(); iter != scene_component_list_.end();)
	{
		if (!(*iter)->activation())
			iter = scene_component_list_.erase(iter);
		else if (!(*iter)->enablement())
			++iter;
		else
		{
			(*iter)->_Input(_time);
			++iter;
		}
	}

	for (auto iter = layer_list_.begin(); iter != layer_list_.end();)
	{
		if (!(*iter)->activation())
			iter = layer_list_.erase(iter);
		else if (!(*iter)->enablement())
			++iter;
		else
		{
			(*iter)->_Input(_time);
			++iter;
		}
	}
}

void Scene::_Update(float _time)
{
	for (auto iter = scene_component_list_.begin(); iter != scene_component_list_.end();)
	{
		if (!(*iter)->activation())
			iter = scene_component_list_.erase(iter);
		else if (!(*iter)->enablement())
			++iter;
		else
		{
			(*iter)->_Update(_time);
			++iter;
		}
	}

	for (auto iter = layer_list_.begin(); iter != layer_list_.end();)
	{
		if (!(*iter)->activation())
			iter = layer_list_.erase(iter);
		else if (!(*iter)->enablement())
			++iter;
		else
		{
			(*iter)->_Update(_time);
			++iter;
		}
	}
}

void Scene::_LateUpdate(float _time)
{
	for (auto iter = scene_component_list_.begin(); iter != scene_component_list_.end();)
	{
		if (!(*iter)->activation())
			iter = scene_component_list_.erase(iter);
		else if (!(*iter)->enablement())
			++iter;
		else
		{
			(*iter)->_LateUpdate(_time);
			++iter;
		}
	}

	for (auto iter = layer_list_.begin(); iter != layer_list_.end();)
	{
		if (!(*iter)->activation())
			iter = layer_list_.erase(iter);
		else if (!(*iter)->enablement())
			++iter;
		else
		{
			(*iter)->_LateUpdate(_time);
			++iter;
		}
	}
}

void Scene::_Collision(float _time)
{
	for (auto iter = scene_component_list_.begin(); iter != scene_component_list_.end();)
	{
		if (!(*iter)->activation())
			iter = scene_component_list_.erase(iter);
		else if (!(*iter)->enablement())
			++iter;
		else
		{
			(*iter)->_Collision(_time);
			++iter;
		}
	}

	for (auto iter = layer_list_.begin(); iter != layer_list_.end();)
	{
		if (!(*iter)->activation())
			iter = layer_list_.erase(iter);
		else if (!(*iter)->enablement())
			++iter;
		else
		{
			(*iter)->_Collision(_time);
			++iter;
		}
	}
}

void Scene::_Render(float _time)
{
	for (auto iter = scene_component_list_.begin(); iter != scene_component_list_.end();)
	{
		if (!(*iter)->activation())
			iter = scene_component_list_.erase(iter);
		else if (!(*iter)->enablement())
			++iter;
		else
		{
			(*iter)->_Render(_time);
			++iter;
		}
	}

	for (auto iter = layer_list_.begin(); iter != layer_list_.end();)
	{
		if (!(*iter)->activation())
			iter = layer_list_.erase(iter);
		else if (!(*iter)->enablement())
			++iter;
		else
		{
			(*iter)->_Render(_time);
			++iter;
		}
	}
}
