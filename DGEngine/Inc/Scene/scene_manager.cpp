#include "DGEngine_stdafx.h"
#include "scene_manager.h"

#include "scene.h"

using namespace DG;

void SceneManager::Initialize()
{
	try
	{
		scene_ = _CreateScene("BasicScene");
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
	return scene_->FindObject(_tag);
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
