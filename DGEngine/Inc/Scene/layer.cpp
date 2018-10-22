#include "DGEngine_stdafx.h"
#include "layer.h"

#include "object.h"
#include "collision_manager.h"

using namespace DG;

std::shared_ptr<Object> Layer::object_nullptr_{};

void Layer::AddObject(std::shared_ptr<Object> const& _object)
{
	_object->set_scene(scene());
	_object->set_layer(shared_from_this());

	object_list_.push_back(_object);
}

void Layer::AddCloneObject(std::shared_ptr<Object> const& _object)
{
	// prototype으로부터 생성된 object와 component는 scene만 세팅되어 있음. 때문에, 각각 layer 추가해줘야 한다.
	// 또한, component는 object를 추가해줘야 한다. 그 이유는 component는 공유의 개념을 적용시키지 않을 것이기 때문에, object가 달라야 한다.
	// 따라서, 복사생성자에서 object를 복사하지 않기 때문에 여기서 컴포넌트마다 직접 추가해줘야 한다.

	_object->set_layer(shared_from_this());

	for (auto const& _component : _object->component_list_)
	{
		_component->set_layer(shared_from_this());
		_component->set_object(_object);
	}

	object_list_.push_back(_object);
}

std::shared_ptr<Object> const& Layer::FindObject(std::string const& _tag) const
{
	auto iter = std::find_if(object_list_.begin(), object_list_.end(), [&_tag](std::shared_ptr<Object> const& _object) {
		return _object->tag() == _tag;
	});

	if (iter == object_list_.end())
		return object_nullptr_;

	return *iter;
}

int Layer::z_order() const
{
	return z_order_;
}

std::shared_ptr<Scene> Layer::scene() const
{
	return scene_.lock();
}

void Layer::set_z_order(int _z_order)
{
	z_order_ = _z_order;
}

void Layer::set_scene(std::shared_ptr<Scene> const& _scene)
{
	scene_ = _scene;
}

Layer::Layer(Layer const& _other) : Tag(_other)
{
	z_order_ = _other.z_order_;
	scene_ = _other.scene_;
}

Layer::Layer(Layer&& _other) noexcept : Tag(std::move(_other))
{
	z_order_ = std::move(_other.z_order_);
	scene_ = std::move(_other.scene_);
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
		if (!(*iter)->active_flag())
			iter = object_list_.erase(iter);
		else if (!(*iter)->enable_flag())
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
		if (!(*iter)->active_flag())
			iter = object_list_.erase(iter);
		else if (!(*iter)->enable_flag())
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
		if (!(*iter)->active_flag())
			iter = object_list_.erase(iter);
		else if (!(*iter)->enable_flag())
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
		if (!(*iter)->active_flag())
			iter = object_list_.erase(iter);
		else if (!(*iter)->enable_flag())
			++iter;
		else
		{
			//(*iter)->_Collision(_time);
			CollisionManager::singleton()->AddColliders(*iter);
			++iter;
		}
	}
}

void Layer::_Render(float _time)
{
	for (auto iter = object_list_.begin(); iter != object_list_.end();)
	{
		if (!(*iter)->active_flag())
			iter = object_list_.erase(iter);
		else if (!(*iter)->enable_flag())
			++iter;
		else
		{
			(*iter)->_Render(_time);
			++iter;
		}
	}
}
