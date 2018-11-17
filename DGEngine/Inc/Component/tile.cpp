#include "DGEngine_stdafx.h"
#include "tile.h"

#include "Resource/resource_manager.h"
#include "Resource/mesh.h"
#include "Rendering/rendering_manager.h"
#include "Rendering/shader.h"
#include "object.h"
#include "Component/transform.h"
#include "Component/material.h"
#include "collider_rect.h"

using namespace DG;

void Tile::Initialize()
{
	try
	{
		type_ = COMPONENT_TYPE::TILE;

		auto transform = object()->AddComponent<Transform>("Transform");

		auto material = std::static_pointer_cast<Material>(object()->AddComponent<Material>("Material"));

		MaterialConstantBuffer material_constant_buffer{};
		material_constant_buffer.diffuse = DirectX::Colors::White.v;

		material->SetMaterialConstantBuffer(material_constant_buffer, 0, 0);
		material->SetTexture("BaseTile", 0, 0, 0);
		material->SetSampler(LINEAR_SAMPLER, 0, 0, 0);
	}
	catch (std::exception const& _e)
	{
		std::cout << _e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Tile::Initialize" << std::endl;
	}
}

TILE_OPTION Tile::tile_option() const
{
	return tile_option_;
}

void Tile::set_tile_option(TILE_OPTION _option)
{
	tile_option_ = _option;
}

Tile::Tile(Tile const& _other) : Component(_other)
{
	tile_option_ = _other.tile_option_;
}

Tile::Tile(Tile&& _other) noexcept : Component(std::move(_other))
{
	tile_option_ = std::move(_other.tile_option_);
}

void Tile::_Release()
{
}

void Tile::_Input(float _time)
{
}

void Tile::_Update(float _time)
{
}

void Tile::_LateUpdate(float _time)
{
}

void Tile::_Collision(float _time)
{
}

void Tile::_Render(float _time)
{
}

std::unique_ptr<Component, std::function<void(Component*)>> Tile::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new Tile{ *this }, [](Component* _p) {
		dynamic_cast<Tile*>(_p)->_Release();
		delete dynamic_cast<Tile*>(_p);
	} };
}

void Tile::_AfterClone()
{
}
