#include "DGEngine_stdafx.h"
#include "scene_component.h"

using namespace std;
using namespace DG;

shared_ptr<Scene> SceneComponent::scene() const
{
	return scene_.lock();
}

void SceneComponent::set_scene(shared_ptr<Scene> const& _scene)
{
	scene_ = _scene;
}

SceneComponent::SceneComponent(SceneComponent const& _other) : Tag(_other)
{
	scene_ = _other.scene_;
}

SceneComponent::SceneComponent(SceneComponent&& _other) noexcept : Tag(move(_other))
{
	scene_ = move(_other.scene_);
}

void SceneComponent::_Release()
{
}

void SceneComponent::_Input(float _time)
{
}

void SceneComponent::_Update(float _time)
{
}

void SceneComponent::_LateUpdate(float _time)
{
}

void SceneComponent::_Collision(float _time)
{
}

void SceneComponent::_Render(float _time)
{
}
