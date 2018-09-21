#include "DGEngine_stdafx.h"
#include "layer.h"

#include "object.h"

using namespace std;
using namespace DG;

void Layer::AddObject(shared_ptr<Object> const& _object)
{
	_object->set_scene(scene());
	_object->set_layer(shared_from_this());

	object_list_.push_back(_object);
}

int Layer::z_order() const
{
	return z_order_;
}

shared_ptr<Scene> Layer::scene() const
{
	return scene_.lock();
}

void Layer::set_z_order(int _z_order)
{
	z_order_ = _z_order;
}

void Layer::set_scene(shared_ptr<Scene> const& _scene)
{
	scene_ = _scene;
}

Layer::Layer(Layer const& _other) : Tag(_other)
{
	z_order_ = _other.z_order_;
	scene_ = _other.scene_;
}

Layer::Layer(Layer&& _other) noexcept : Tag(move(_other))
{
	z_order_ = move(_other.z_order_);
	scene_ = move(_other.scene_);
}

void Layer::_Release()
{
}

void Layer::_Initialize()
{
}

void Layer::_Input(float _time)
{
	for (auto iter = object_list_.begin(); iter != object_list_.end();)
	{
		if (!(*iter)->activation())
			iter = object_list_.erase(iter);
		else if (!(*iter)->enablement())
			++iter;
		else
		{
			(*iter)->_Input(_time);
			++iter;
		}
	}
}

void Layer::_Update(float _time)
{
	for (auto iter = object_list_.begin(); iter != object_list_.end();)
	{
		if (!(*iter)->activation())
			iter = object_list_.erase(iter);
		else if (!(*iter)->enablement())
			++iter;
		else
		{
			(*iter)->_Update(_time);
			++iter;
		}
	}
}

void Layer::_LateUpdate(float _time)
{
	for (auto iter = object_list_.begin(); iter != object_list_.end();)
	{
		if (!(*iter)->activation())
			iter = object_list_.erase(iter);
		else if (!(*iter)->enablement())
			++iter;
		else
		{
			(*iter)->_LateUpdate(_time);
			++iter;
		}
	}
}

void Layer::_Collision(float _time)
{
	for (auto iter = object_list_.begin(); iter != object_list_.end();)
	{
		if (!(*iter)->activation())
			iter = object_list_.erase(iter);
		else if (!(*iter)->enablement())
			++iter;
		else
		{
			(*iter)->_Collision(_time);
			++iter;
		}
	}
}

void Layer::_Render(float _time)
{
	for (auto iter = object_list_.begin(); iter != object_list_.end();)
	{
		if (!(*iter)->activation())
			iter = object_list_.erase(iter);
		else if (!(*iter)->enablement())
			++iter;
		else
		{
			(*iter)->_Render(_time);
			++iter;
		}
	}
}
