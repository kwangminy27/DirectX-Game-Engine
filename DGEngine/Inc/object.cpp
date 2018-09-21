#include "DGEngine_stdafx.h"
#include "object.h"

using namespace std;
using namespace DG;

shared_ptr<Scene> Object::scene() const
{
	return scene_.lock();
}

shared_ptr<Layer> Object::layer() const
{
	return layer_.lock();
}

shared_ptr<Transform> Object::transform() const
{
	return transform_;
}

void Object::set_scene(shared_ptr<Scene> const& _scene)
{
	scene_ = _scene;
}

void Object::set_layer(shared_ptr<Layer> const& _layer)
{
	layer_ = _layer;
}

Object::Object(Object const& _other) : Tag(_other)
{
	scene_ = _other.scene_;
	layer_ = _other.layer_;
}

Object::Object(Object&& _other) noexcept : Tag(move(_other))
{
	scene_ = move(_other.scene_);
	layer_ = move(_other.layer_);
}

void Object::_Release()
{
}

void Object::_Initialize()
{
}

void Object::_Input(float _time)
{
}

void Object::_Update(float _time)
{
}

void Object::_LateUpdate(float _time)
{
}

void Object::_Collision(float _time)
{
}

void Object::_Render(float _time)
{
}

unique_ptr<Object, function<void(Object*)>> Object::Clone()
{
	return unique_ptr<Object, function<void(Object*)>>{ new Object(*this), [](Object* _p) {
		_p->_Release();
		delete _p;
	} };
}
