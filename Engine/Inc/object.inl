#pragma once

#include "Component/component.h"

using namespace DG;

template <typename T>
std::shared_ptr<Component> Object::AddComponent(std::string const& _tag)
{
	auto component = std::shared_ptr<Component>{ new T, [](T* _p) {
		_p->_Release();
		delete _p;
	} };

	component->set_tag(_tag);
	component->set_scene(scene());
	component->set_layer(layer());
	component->set_object(shared_from_this());

	component->Initialize();

	component_list_.push_back(component);

	return component;
}
