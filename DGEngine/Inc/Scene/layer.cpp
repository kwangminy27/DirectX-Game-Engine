#include "DGEngine_stdafx.h"
#include "layer.h"

using namespace std;
using namespace DG;

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
}

void Layer::_Update(float _time)
{
}

void Layer::_LateUpdate(float _time)
{
}

void Layer::_Collision(float _time)
{
}

void Layer::_Render(float _time)
{
}
