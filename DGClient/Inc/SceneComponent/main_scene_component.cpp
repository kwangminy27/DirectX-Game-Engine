#include "DGClient_stdafx.h"
#include "SceneComponent/main_scene_component.h"
#include "UserComponent/player_component.h"
#include "UserComponent/monster_component.h"
#include "UserComponent/missile_component.h"

#include <Scene/scene.h>
#include <Scene/layer.h>
#include <object.h>
#include <Component/component.h>
#include <Component/transform.h>
#include <Component/renderer.h>

using namespace DG;

void MainSceneComponent::Initialize()
{
	_CreatePrototypes();

	auto const& default_layer = scene()->FindLayer("Default");

	auto monster = Object::CreateObject("Monster", default_layer);
	auto monster_component = std::dynamic_pointer_cast<MonsterComponent>(monster->AddComponent<MonsterComponent>("Monster"));

	auto player = Object::CreateObject("Player", default_layer);
	auto player_component = player->AddComponent<PlayerComponent>("Player");

	monster_component->set_target(player);
}

MainSceneComponent::MainSceneComponent(MainSceneComponent const& _other) : SceneComponent(_other)
{
}

MainSceneComponent::MainSceneComponent(MainSceneComponent&& _other) noexcept : SceneComponent(std::move(_other))
{
}

void MainSceneComponent::_Release()
{
}

std::unique_ptr<SceneComponent, std::function<void(SceneComponent*)>> MainSceneComponent::_Clone() const
{
	return std::unique_ptr<SceneComponent, std::function<void(SceneComponent*)>>{ new MainSceneComponent{ *this }, [](SceneComponent* _p) {
		dynamic_cast<MainSceneComponent*>(_p)->_Release();
		delete dynamic_cast<MainSceneComponent*>(_p);
	} };
}

void MainSceneComponent::_CreatePrototypes()
{
	auto const& default_layer = scene()->FindLayer("Default");

	auto missile_prototype = Object::CreatePrototype("Missile", true);
	auto missile_component = missile_prototype->AddComponent<MissileComponent>("Missile");
}
