#include "DGEngine_stdafx.h"
#include "scene_manager.h"

#include "scene.h"
#include "object.h"
#include "input_manager.h"

using namespace DG;

void SceneManager::Initialize()
{
	try
	{
		scene_ = _CreateScene("StartScene");
	}
	catch (exception const& _e)
	{
		cerr << _e.what() << endl;
	}
	catch (...)
	{
		cerr << "SceneManager::Initialize" << endl;
	}
}

void SceneManager::Input(float _time)
{
	scene_->_Input(_time);
}

void SceneManager::Update(float _time)
{
	scene_->_Update(_time);
}

void SceneManager::LateUpdate(float _time)
{
	scene_->_LateUpdate(_time);
}

void SceneManager::Collision(float _time)
{
	scene_->_Collision(_time);
}

void SceneManager::Render(float _time)
{
	scene_->_Render(_time);
}

std::shared_ptr<Object> const& SceneManager::FindObject(std::string const& _tag) const
{
	auto const& object = scene_->FindObject(_tag);

	if (object)
		return object;

	return next_scene_->FindObject(_tag);
}


void SceneManager::CreateNextScene(std::string const& _tag)
{
	next_scene_ = _CreateScene(_tag);
}

void SceneManager::TrySceneChange()
{
	if (!next_scene_)
		return;

	scene_ = std::move(next_scene_);

	auto const& mouse = InputManager::singleton()->mouse();

	mouse->set_scene(scene_);
	for (auto const& _component : mouse->component_list_)
		_component->set_scene(scene_);
}

std::shared_ptr<Scene> SceneManager::scene() const
{
	return scene_;
}

std::shared_ptr<Scene> SceneManager::next_scene() const
{
	return next_scene_;
}

void SceneManager::_Release()
{
}

shared_ptr<Scene> SceneManager::_CreateScene(string const& _tag)
{
	auto scene = shared_ptr<Scene>{ new Scene, [](Scene* _p) {
		_p->_Release();
		delete _p;
	} };

	scene->tag_ = _tag;

	scene->_Initialize();

	return scene;
}
