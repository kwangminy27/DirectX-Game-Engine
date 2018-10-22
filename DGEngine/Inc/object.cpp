#include "DGEngine_stdafx.h"
#include "object.h"

#include "Scene/scene_manager.h"
#include "Scene/scene.h"
#include "Scene/layer.h"
#include "Component/component.h"
#include "collision_manager.h"

using namespace DG;

std::shared_ptr<Component> Object::component_nullptr_{};
std::shared_ptr<Object> Object::prototype_nullptr_{};
std::unordered_map<std::string, std::unordered_map<std::string, std::shared_ptr<Object>>> Object::prototype_map_{};

std::shared_ptr<Object> Object::CreatePrototype(std::string const& _tag, bool _current_flag)
{
	auto const& scene_manager = SceneManager::singleton();

	std::shared_ptr<Scene> scene{};

	if (_current_flag)
		scene = scene_manager->scene();
	else
		scene = scene_manager->next_scene();

	if (FindPrototype(_tag, scene->tag()))
		throw exception{ "Object::CreatePrototype" };

	auto iter = prototype_map_.find(scene->tag());

	if (iter == prototype_map_.end())
	{
		prototype_map_.insert(make_pair(scene->tag(), std::unordered_map<std::string, std::shared_ptr<Object>>{}));

		iter = prototype_map_.find(scene->tag());
	}

	auto prototype = std::shared_ptr<Object>{ new Object, [](Object* _p) {
		_p->_Release();
		delete _p;
	} };

	prototype->tag_ = _tag;
	prototype->scene_ = scene;

	prototype->_Initialize();

	iter->second.insert(make_pair(_tag, prototype));

	return prototype;
}

std::shared_ptr<Object> Object::CreateClone(std::string const& _tag, std::string const& _prototype_tag, std::shared_ptr<Layer> const& _layer, bool _current_flag)
{
	auto const& scene_manager = SceneManager::singleton();

	std::shared_ptr<Scene> scene{};

	if (_current_flag)
		scene = scene_manager->scene();
	else
		scene = scene_manager->next_scene();

	auto prototype = FindPrototype(scene->tag(), _prototype_tag);

	auto object = std::shared_ptr<Object>{ prototype->Clone() };

	if (!_layer)
		throw std::exception{ "Object::CreateClone" };

	_layer->AddCloneObject(object);

	return object;
}

std::shared_ptr<Object> Object::CreateObject(std::string const& _tag, std::shared_ptr<Layer> const& _layer)
{
	auto object = std::shared_ptr<Object>{ new Object, [](Object* _p) {
		_p->_Release();
		delete _p;
	} };

	object->tag_ = _tag;
	object->_Initialize();

	if (_layer)
		_layer->AddObject(object);

	return object;
}

std::shared_ptr<Object> Object::FindPrototype(std::string const& _scene_tag, std::string const& _tag)
{
	auto prototype_map_iter = prototype_map_.find(_scene_tag);

	if (prototype_map_iter == prototype_map_.end())
		return prototype_nullptr_;

	auto iter = prototype_map_iter->second.find(_tag);

	if (iter == prototype_map_iter->second.end())
		return prototype_nullptr_;

	return iter->second;
}

std::shared_ptr<Object> Object::FindObject(std::string const& _tag)
{
	return SceneManager::singleton()->FindObject(_tag);
}

void Object::DestroyPrototype()
{
	prototype_map_.clear();
}

void Object::DestroyPrototype(std::string const& _scene_tag)
{
	auto iter = prototype_map_.find(_scene_tag);

	if (iter == prototype_map_.end())
		return;

	prototype_map_.erase(iter);
}

void Object::DestroyPrototype(std::string const& _scene_tag, std::string const& _tag)
{
	auto prototype_map_iter = prototype_map_.find(_scene_tag);

	if (prototype_map_iter == prototype_map_.end())
		return;

	auto iter = prototype_map_iter->second.find(_tag);

	if (iter == prototype_map_iter->second.end())
		return;

	prototype_map_iter->second.erase(iter);
}

std::shared_ptr<Component> const& Object::FindComponent(std::string const& _tag) const
{
	auto iter = find_if(component_list_.begin(), component_list_.end(), [&_tag](std::shared_ptr<Component> const& _p) {
		return _p->tag() == _tag;
	});

	if (iter == component_list_.end())
		return component_nullptr_;

	return *iter;
}

std::shared_ptr<Component> const& Object::FindComponent(COMPONENT_TYPE _type) const
{
	auto iter = find_if(component_list_.begin(), component_list_.end(), [&_type](std::shared_ptr<Component> const& _p) {
		return _p->type() == _type;
	});

	if (iter == component_list_.end())
		return component_nullptr_;

	return *iter;
}

std::list<std::shared_ptr<Component>> const& Object::FindComponents(COMPONENT_TYPE _type) const
{
	static std::list<std::shared_ptr<Component>> component_list_buffer{};

	component_list_buffer.clear();

	for (auto const& _component : component_list_)
	{
		if (_component->type() == _type)
			component_list_buffer.push_back(_component);
	}

	return component_list_buffer;
}

bool Object::IsComponent(COMPONENT_TYPE _type) const
{
	for (auto iter = component_list_.begin(); iter != component_list_.end(); ++iter)
	{
		if ((*iter)->type() == _type)
			return true;
	}

	return false;
}

void Object::Test(std::shared_ptr<Scene> const& _scene, std::shared_ptr<Layer> const& _layer, std::shared_ptr<Object> const& _object)
{
	for (auto iter = component_list_.begin(); iter != component_list_.end(); ++iter)
	{
		(*iter)->set_scene(_scene);
		(*iter)->set_layer(_layer);
		(*iter)->set_object(_object);
	}
}

std::shared_ptr<Scene> Object::scene() const
{
	return scene_.lock();
}

std::shared_ptr<Layer> Object::layer() const
{
	return layer_.lock();
}

void Object::set_scene(std::shared_ptr<Scene> const& _scene)
{
	scene_ = _scene;
}

void Object::set_layer(std::shared_ptr<Layer> const& _layer)
{
	layer_ = _layer;
}

Object::Object(Object const& _other) : Tag(_other)
{
	scene_ = _other.scene_;
	layer_ = _other.layer_;

	component_list_.clear();

	for (auto const& _component : _other.component_list_)
		component_list_.push_back(_component->_Clone());
}

Object::Object(Object&& _other) noexcept : Tag(move(_other))
{
	scene_ = move(_other.scene_);
	layer_ = move(_other.layer_);

	component_list_ = std::move(_other.component_list_);
}

void Object::_Release()
{
}

void Object::_Initialize()
{
}

void Object::_Input(float _time)
{
	for (auto iter = component_list_.begin(); iter != component_list_.end();)
	{
		if (!(*iter)->active_flag())
			iter = component_list_.erase(iter);
		else if (!(*iter)->enable_flag())
			++iter;
		else
		{
			(*iter)->_Input(_time);
			++iter;
		}
	}
}

void Object::_Update(float _time)
{
	for (auto iter = component_list_.begin(); iter != component_list_.end();)
	{
		if (!(*iter)->active_flag())
			iter = component_list_.erase(iter);
		else if (!(*iter)->enable_flag())
			++iter;
		else
		{
			(*iter)->_Update(_time);
			++iter;
		}
	}
}

void Object::_LateUpdate(float _time)
{
	for (auto iter = component_list_.begin(); iter != component_list_.end();)
	{
		if (!(*iter)->active_flag())
			iter = component_list_.erase(iter);
		else if (!(*iter)->enable_flag())
			++iter;
		else
		{
			(*iter)->_LateUpdate(_time);
			++iter;
		}
	}
}

void Object::_Collision(float _time)
{
	// CollisionManager가 대체함

	/*for (auto iter = component_list_.begin(); iter != component_list_.end();)
	{
		if (!(*iter)->active_flag())
			iter = component_list_.erase(iter);
		else if (!(*iter)->enable_flag())
			++iter;
		else
		{
			(*iter)->_Collision(_time);
			++iter;
		}
	}*/
}

void Object::_Render(float _time)
{
	for (auto iter = component_list_.begin(); iter != component_list_.end();)
	{
		if (!(*iter)->active_flag())
			iter = component_list_.erase(iter);
		else if (!(*iter)->enable_flag())
			++iter;
		else
		{
			(*iter)->_Render(_time);
			++iter;
		}
	}
}

std::unique_ptr<Object, std::function<void(Object*)>> Object::Clone()
{
	return std::unique_ptr<Object, std::function<void(Object*)>>{ new Object{ *this }, [](Object* _p) {
		_p->_Release();
		delete _p;
	} };
}
