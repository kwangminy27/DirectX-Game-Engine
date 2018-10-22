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

std::string const& Component::object_tag() const
{
	return object_tag_;
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

void Component::set_object_tag(std::string const& _tag)
{
	object_tag_ = _tag;
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
	set_object_tag(_object->tag());
	object_ = _object;
}

Component::Component(Component const& _other) : Tag(_other)
{
	type_ = _other.type_;

	scene_ = _other.scene_;
	layer_ = _other.layer_;

	// component는 공유하는 개념이 아님 따로 추가해 줘야 함, unique로 만들어야 했네
	// object_tag_ = _other.object_tag_;
	// object_ = _other.object_;
}

Component::Component(Component&& _other) noexcept : Tag(std::move(_other))
{
	type_ = std::move(_other.type_);

	object_tag_ = std::move(_other.object_tag_);

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