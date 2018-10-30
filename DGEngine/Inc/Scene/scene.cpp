#include "DGEngine_stdafx.h"
#include "scene.h"

#include "scene_component.h"
#include "layer.h"
#include "object.h"
#include "Component/transform.h"
#include "Component/camera.h"
#include "collision_manager.h"
#include "input_manager.h"

std::shared_ptr<SceneComponent> Scene::scene_component_nullptr_{};
std::shared_ptr<Layer> Scene::layer_nullptr_{};
std::shared_ptr<Object> Scene::camera_nullptr_{};

using namespace DG;

std::shared_ptr<SceneComponent> const& Scene::FindSceneComponent(std::string const& _tag) const
{
	for (auto const& scene_component : scene_component_list_)
	{
		if (scene_component->tag() == _tag)
			return scene_component;
	}

	return scene_component_nullptr_;
}

std::shared_ptr<Layer> const& Scene::FindLayer(std::string const& _tag) const
{
	for (auto const& layer : layer_list_)
	{
		if (layer->tag() == _tag)
			return layer;
	}

	return layer_nullptr_;
}

std::shared_ptr<Object> const& Scene::FindObject(std::string const& _tag) const
{
	for (auto layer : layer_list_)
	{
		auto const& object = layer->FindObject(_tag);

		if (object)
			return object;
	}

	return Layer::object_nullptr_;
}

std::shared_ptr<Object> const& Scene::FindCamera(std::string const& _tag) const
{
	auto iter = camera_map_.find(_tag);

	if (iter == camera_map_.end())
		return camera_nullptr_;
	
	return iter->second;
}

std::shared_ptr<Object> const& Scene::main_camera() const
{
	return main_camera_;
}

std::shared_ptr<Object> const& Scene::ui_camera() const
{
	return ui_camera_;
}

Scene::Scene(Scene const& _other) : Tag(_other)
{
	scene_component_list_ = _other.scene_component_list_;
	layer_list_ = _other.layer_list_;
	camera_map_ = _other.camera_map_;
	main_camera_ = _other.main_camera_;
}

Scene::Scene(Scene&& _other) noexcept : Tag(std::move(_other))
{
	scene_component_list_ = std::move(_other.scene_component_list_);
	layer_list_ = std::move(_other.layer_list_);
	camera_map_ = std::move(_other.camera_map_);
	main_camera_ = std::move(_other.main_camera_);
}

void Scene::_Release()
{
}

void Scene::_AddLayer(std::string const& _tag, int _z_order)
{
	auto layer = std::shared_ptr<Layer>{ new Layer, [](Layer* _p) {
		_p->_Release();
		delete _p;
	} };

	layer->tag_ = _tag;
	layer->set_z_order(_z_order);
	layer->set_scene(shared_from_this());

	layer->_Initialize();

	layer_list_.push_back(move(layer));

	layer_list_.sort([](std::shared_ptr<Layer> const& _left, std::shared_ptr<Layer> const& _right) {
		return _left->z_order() < _right->z_order();
	});
}

void Scene::_Initialize()
{
	_AddLayer("Default", 0);
	_AddLayer("UI", std::numeric_limits<int>::max());

	main_camera_ = _CreateCamera(
		"BasicCamera",
		Math::Vector3::Zero,
		CAMERA_TYPE::ORTHOGONAL ,
		DirectX::XM_PIDIV4,
		static_cast<float>(RESOLUTION::WIDTH),
		static_cast<float>(RESOLUTION::HEIGHT),
		0.f, // perspective인 경우에는 0.f 될 수 없음
		1000.f
	);

	ui_camera_ = _CreateCamera(
		"UICamera",
		Math::Vector3::Zero,
		CAMERA_TYPE::ORTHOGONAL,
		DirectX::XM_PIDIV4,
		static_cast<float>(RESOLUTION::WIDTH),
		static_cast<float>(RESOLUTION::HEIGHT),
		0.f,
		1000.f
	);
}

void Scene::_Input(float _time)
{
	for (auto iter = scene_component_list_.begin(); iter != scene_component_list_.end();)
	{
		if (!(*iter)->active_flag())
			iter = scene_component_list_.erase(iter);
		else if (!(*iter)->enable_flag())
			++iter;
		else
		{
			(*iter)->_Input(_time);
			++iter;
		}
	}

	for (auto iter = layer_list_.begin(); iter != layer_list_.end();)
	{
		if (!(*iter)->active_flag())
			iter = layer_list_.erase(iter);
		else if (!(*iter)->enable_flag())
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
		if (!(*iter)->active_flag())
			iter = scene_component_list_.erase(iter);
		else if (!(*iter)->enable_flag())
			++iter;
		else
		{
			(*iter)->_Update(_time);
			++iter;
		}
	}

	for (auto iter = layer_list_.begin(); iter != layer_list_.end();)
	{
		if (!(*iter)->active_flag())
			iter = layer_list_.erase(iter);
		else if (!(*iter)->enable_flag())
			++iter;
		else
		{
			(*iter)->_Update(_time);
			++iter;
		}
	}

	main_camera_->_Update(_time);
	InputManager::singleton()->UpdateMouseColliderPosition();
}

void Scene::_LateUpdate(float _time)
{
	for (auto iter = scene_component_list_.begin(); iter != scene_component_list_.end();)
	{
		if (!(*iter)->active_flag())
			iter = scene_component_list_.erase(iter);
		else if (!(*iter)->enable_flag())
			++iter;
		else
		{
			(*iter)->_LateUpdate(_time);
			++iter;
		}
	}

	for (auto iter = layer_list_.begin(); iter != layer_list_.end();)
	{
		if (!(*iter)->active_flag())
			iter = layer_list_.erase(iter);
		else if (!(*iter)->enable_flag())
			++iter;
		else
		{
			(*iter)->_LateUpdate(_time);
			++iter;
		}
	}

	InputManager::singleton()->LateUpdate(_time);
}

void Scene::_Collision(float _time)
{
	for (auto iter = scene_component_list_.begin(); iter != scene_component_list_.end();)
	{
		if (!(*iter)->active_flag())
			iter = scene_component_list_.erase(iter);
		else if (!(*iter)->enable_flag())
			++iter;
		else
		{
			(*iter)->_Collision(_time);
			++iter;
		}
	}

	for (auto iter = layer_list_.begin(); iter != layer_list_.end();)
	{
		if (!(*iter)->active_flag())
			iter = layer_list_.erase(iter);
		else if (!(*iter)->enable_flag())
			++iter;
		else
		{
			(*iter)->_Collision(_time);
			++iter;
		}
	}

	CollisionManager::singleton()->Collision(_time);
}

void Scene::_Render(float _time)
{
	for (auto iter = scene_component_list_.begin(); iter != scene_component_list_.end();)
	{
		if (!(*iter)->active_flag())
			iter = scene_component_list_.erase(iter);
		else if (!(*iter)->enable_flag())
			++iter;
		else
		{
			(*iter)->_Render(_time);
			++iter;
		}
	}

	for (auto iter = layer_list_.begin(); iter != layer_list_.end();)
	{
		if (!(*iter)->active_flag())
			iter = layer_list_.erase(iter);
		else if (!(*iter)->enable_flag())
			++iter;
		else
		{
			(*iter)->_Render(_time);
			++iter;
		}
	}
}

std::shared_ptr<Object> Scene::_CreateCamera(
	std::string const& _tag,
	Math::Vector3 const& _position,
	CAMERA_TYPE _type,
	float _fov_angle,
	float _width,
	float _height,
	float _near,
	float _far)
{
	if (FindCamera(_tag))
		throw std::exception{ "Scene::_CreateCamera" };

	auto camera = Object::CreateObject(_tag, layer_nullptr_);

	auto camera_transform = std::dynamic_pointer_cast<Transform>(camera->AddComponent<Transform>("Transform"));
	camera_transform->Translation(_position);

	auto camera_component = dynamic_pointer_cast<Camera>(camera->AddComponent<Camera>(_tag));
	camera_component->set_camera_info(_type, _fov_angle, _width, _height, _near, _far);

	camera_map_.insert(make_pair(_tag, camera));

	return camera;
}

void Scene::_ChangeCamera(std::string const& _tag)
{
	auto const& camera = FindCamera(_tag);

	if (!camera)
		return;

	main_camera_ = camera;
}
