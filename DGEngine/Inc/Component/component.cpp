#include "DGEngine_stdafx.h"
#include "component.h"

#include "Scene/scene.h"
#include "Scene/layer.h"
#include "object.h"

using namespace DG;

COMPONENT_TYPE Component::type() const
{
	return type_;
}

std::shared_ptr<Scene> Component::scene() const
{
	return scene_.lock();
}

std::shared_ptr<Layer> Component::layer() const
{
	return layer_.lock();
}

std::shared_ptr<Object> Component::object() const
{
	return object_.lock();
}

void Component::set_type(COMPONENT_TYPE _type)
{
	type_ = _type;
}

void Component::set_scene(std::shared_ptr<Scene> const& _scene)
{
	scene_ = _scene;
}

void Component::set_layer(std::shared_ptr<Layer> const& _layer)
{
	layer_ = _layer;
}

void Component::set_object(std::shared_ptr<Object> const& _object)
{
	object_ = _object;
}

Component::Component(Component const& _other) : Tag(_other)
{
	type_ = _other.type_;
	scene_ = _other.scene_;
	layer_ = _other.layer_;
	//object_ = _other.object_;
}

Component::Component(Component&& _other) noexcept : Tag(std::move(_other))
{
	type_ = std::move(_other.type_);
	scene_ = std::move(_other.scene_);
	layer_ = std::move(_other.layer_);
	object_ = std::move(_other.object_);
}

void Component::_Release()
{
}

void Component::_Input(float _time)
{
}

void Component::_Update(float _time)
{
}

void Component::_LateUpdate(float _time)
{
}

void Component::_Collision(float _time)
{
}

void Component::_Render(float _time)
{
}