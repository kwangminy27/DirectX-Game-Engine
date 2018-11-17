#include "DGEngine_stdafx.h"
#include "stage.h"

#include "device.h"
#include "Resource/resource_manager.h"
#include "Resource/mesh.h"
#include "Rendering/rendering_manager.h"
#include "Rendering/shader.h"
#include "Rendering/render_state.h"
#include "Scene/scene.h"
#include "object.h"
#include "tile.h"
#include "transform.h"
#include "Component/material.h"

using namespace DG;

void Stage::Initialize()
{
	try
	{
		type_ = COMPONENT_TYPE::STAGE;

		auto transform = object()->AddComponent<Transform>("Transform");
	}
	catch (std::exception const& _e)
	{
		std::cout << _e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Stage::Initialize" << std::endl;
	}
}

void Stage::CreateTile(STAGE_TYPE _stage_type, int _idx_width, int _idx_height, Math::Vector2 const& _tile_size)
{
	stage_type_ = _stage_type;

	tile_vector_2d_.resize(_idx_height);
	tile_graph_.resize(_idx_height);

	for (int i = 0; i < _idx_height; ++i)
	{
		tile_vector_2d_.at(i).resize(_idx_width);
		tile_graph_.at(i).resize(_idx_width);
	}

	stage_size_ = _tile_size * Math::Vector2{ static_cast<float>(_idx_width), static_cast<float>(_idx_height) };
	tile_size_ = _tile_size;

	switch (_stage_type)
	{
	case STAGE_TYPE::RECT:
		_CreateRectTile();
		break;

	case STAGE_TYPE::ISOMETRIC:
		_CreateIsometricTile();
		break;

	case STAGE_TYPE::HONEY:
		break;
	}
}

std::pair<int, int> Stage::GetTileIdx(Math::Vector3 const& _position)
{
	switch (stage_type_)
	{
	case STAGE_TYPE::RECT:
		return _GetRectTileIdx(_position);

	case STAGE_TYPE::ISOMETRIC:
		return _GetIsometricTileIdx(_position);

	case STAGE_TYPE::HONEY:
		break;
	}

	return std::pair<int, int>{};
}

Math::Vector3 Stage::GetTileCenterPosition(std::pair<int, int> const& _idx_pair) const
{
	auto const& tile_transform = std::dynamic_pointer_cast<Transform>(tile_vector_2d_.at(_idx_pair.second).at(_idx_pair.first)->FindComponent(COMPONENT_TYPE::TRANSFORM));
	
	return tile_transform->GetWorldPosition() + tile_transform->GetWorldScale() * 0.5f;
}

std::list<std::pair<int, int>> const& Stage::GetTileAdjacencyList(std::pair<int, int> const& _idx_pair) const
{
	return tile_graph_.at(_idx_pair.second).at(_idx_pair.first);
}

STAGE_TYPE Stage::stage_type() const
{
	return stage_type_;
}

TILE_OPTION Stage::tile_option(int _x_idx, int _y_idx) const
{
	if (_x_idx < 0 || _x_idx >= tile_vector_2d_.at(0).size())
		return TILE_OPTION::MAX;

	if (_y_idx < 0 || _y_idx >= tile_vector_2d_.size())
		return TILE_OPTION::MAX;

	auto const& tile_component = std::dynamic_pointer_cast<Tile>(tile_vector_2d_.at(_y_idx).at(_x_idx)->FindComponent(COMPONENT_TYPE::TILE));

	return tile_component->tile_option();
}

void Stage::set_tile_option(int _x_idx, int _y_idx, TILE_OPTION _option)
{
	if (_x_idx < 0 || _x_idx >= tile_vector_2d_.at(0).size())
		return;

	if (_y_idx < 0 || _y_idx >= tile_vector_2d_.size())
		return;

	auto const& tile_component = std::dynamic_pointer_cast<Tile>(tile_vector_2d_.at(_y_idx).at(_x_idx)->FindComponent(COMPONENT_TYPE::TILE));

	tile_component->set_tile_option(_option);
}

Stage::Stage(Stage const& _other) : Component(_other)
{
	stage_type_ = _other.stage_type_;
	tile_vector_2d_ = _other.tile_vector_2d_;
	stage_size_ = _other.stage_size_;
	tile_size_ = _other.tile_size_;
	view_range_idx_x_ = _other.view_range_idx_x_;
	view_range_idx_y_ = _other.view_range_idx_y_;
	tile_graph_ = _other.tile_graph_;
}

Stage::Stage(Stage&& _other) noexcept : Component(std::move(_other))
{
	stage_type_ = std::move(_other.stage_type_);
	tile_vector_2d_ = std::move(_other.tile_vector_2d_);
	stage_size_ = std::move(_other.stage_size_);
	tile_size_ = std::move(_other.tile_size_);
	view_range_idx_x_ = std::move(_other.view_range_idx_x_);
	view_range_idx_y_ = std::move(_other.view_range_idx_y_);
	tile_graph_ = std::move(_other.tile_graph_);
}

void Stage::_Release()
{
}

void Stage::_Input(float _time)
{
	auto const& camera = scene()->main_camera();
	auto const& camera_transform = std::dynamic_pointer_cast<Transform>(camera->FindComponent(COMPONENT_TYPE::TRANSFORM));

	auto const& camera_view_start = camera_transform->GetWorldPosition();
	auto const& camera_view_end = camera_view_start + Math::Vector3{ static_cast<float>(RESOLUTION::WIDTH), static_cast<float>(RESOLUTION::HEIGHT), 0.f };

	switch (stage_type_)
	{
	case STAGE_TYPE::RECT:
		break;

	case STAGE_TYPE::ISOMETRIC:
	{
		auto LB = _GetIsometricTileIdx(camera_view_start);
		auto LT = _GetIsometricTileIdx(camera_view_start + Math::Vector3{ 0.f, static_cast<float>(RESOLUTION::HEIGHT), 0.f });
		auto RT = _GetIsometricTileIdx(camera_view_end);
		auto RB = _GetIsometricTileIdx(camera_view_start + Math::Vector3{ static_cast<float>(RESOLUTION::WIDTH), 0.f, 0.f });

		view_range_idx_x_ = { LB.first, RT.first};
		view_range_idx_y_ = { RB.second, LT.second};
	}
	break;

	case STAGE_TYPE::HONEY:
		break;
	}

	for (int i = view_range_idx_y_.first; i <= view_range_idx_y_.second; ++i)
		for (int j = view_range_idx_x_.first; j <= view_range_idx_x_.second; ++j)
			tile_vector_2d_.at(i).at(j)->_Input(_time);
}

void Stage::_Update(float _time)
{
	for (int i = view_range_idx_y_.first; i <= view_range_idx_y_.second; ++i)
		for (int j = view_range_idx_x_.first; j <= view_range_idx_x_.second; ++j)
			tile_vector_2d_.at(i).at(j)->_Update(_time);
}

void Stage::_LateUpdate(float _time)
{
	for (int i = view_range_idx_y_.first; i <= view_range_idx_y_.second; ++i)
		for (int j = view_range_idx_x_.first; j <= view_range_idx_x_.second; ++j)
			tile_vector_2d_.at(i).at(j)->_LateUpdate(_time);
}

void Stage::_Collision(float _time)
{
	for (int i = view_range_idx_y_.first; i <= view_range_idx_y_.second; ++i)
		for (int j = view_range_idx_x_.first; j <= view_range_idx_x_.second; ++j)
			tile_vector_2d_.at(i).at(j)->_Collision(_time);
}

void Stage::_Render(float _time)
{
	auto const& resource_manager = ResourceManager::singleton();
	auto const& rendering_manager = RenderingManager::singleton();

	std::vector<Math::Matrix> matrix_vector{};
	for (int i = view_range_idx_y_.first; i <= view_range_idx_y_.second; ++i)
	{
		for (int j = view_range_idx_x_.first; j <= view_range_idx_x_.second; ++j)
		{
			auto const& tile_transform = std::static_pointer_cast<Transform>(tile_vector_2d_.at(i).at(j)->FindComponent(COMPONENT_TYPE::TRANSFORM));
			auto tile_world = tile_transform->world();

			tile_world = tile_world.Transpose();

			matrix_vector.push_back(std::move(tile_world));
		}
	}

	auto const& context = Device::singleton()->context();
	auto const& instance_buffer = resource_manager->FindMesh("InstanceTexRect")->GetInstanceBuffer(0, 0);

	D3D11_MAPPED_SUBRESOURCE mapped_resource{};
	context->Map(instance_buffer.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);

	int visible_object_count = static_cast<int>(matrix_vector.size());
	memcpy_s(mapped_resource.pData, sizeof(Math::Matrix) * visible_object_count, matrix_vector.data(), sizeof(Math::Matrix) * visible_object_count);

	context->Unmap(instance_buffer.Get(), 0);

	auto const& mesh = resource_manager->FindMesh("InstanceTexRect");
	auto const& shader = rendering_manager->FindShader(INSTANCE_TEX_SHADER);
	auto const& render_state = rendering_manager->FindRenderState(ALPHA_BLEND);
	auto const& material = std::static_pointer_cast<Material>(tile_vector_2d_.at(0).at(0)->FindComponent(COMPONENT_TYPE::MATERIAL));

	shader->SetShader();

	render_state->_SetState();

	material->SetToShader(0, 0);

	mesh->SetInstanceCount(visible_object_count, 0, 0);
	mesh->Render();

	render_state->_SetBackState();
}

std::unique_ptr<Component, std::function<void(Component*)>> Stage::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new Stage{ *this }, [](Component* _p) {
		dynamic_cast<Stage*>(_p)->_Release();
		delete dynamic_cast<Stage*>(_p);
	} };
}

void Stage::_AfterClone()
{
}

void Stage::_CreateRectTile()
{
}

void Stage::_CreateIsometricTile()
{
	auto start_position = Math::Vector3{ stage_size_.x * 0.5f, 0.f, 0.f };
	auto tile_size_div_2 = tile_size_ * 0.5f;

	for (auto i = 0; i < tile_vector_2d_.size(); ++i)
	{
		for (auto j = 0; j < tile_vector_2d_.at(0).size(); ++j)
		{
			auto tile = Object::CreateObject("Tile", nullptr);
			tile->set_scene(scene());
			tile->set_layer(layer());

			auto tile_component = tile->AddComponent<Tile>("TileComponent");
			tile_component->set_scene(scene());
			tile_component->set_layer(layer());

			auto const& tile_transform = std::dynamic_pointer_cast<Transform>(tile->FindComponent(COMPONENT_TYPE::TRANSFORM));

			tile_transform->Translation({ start_position.x + tile_size_div_2.x * (j - i - 1), start_position.y + tile_size_div_2.y * (j + i), 0.f });
			tile_transform->Scaling({ tile_size_.x, tile_size_.y, 1.f });

			tile_vector_2d_.at(i).at(j) = std::move(tile);
		}
	}

	for (auto i = 0; i < tile_vector_2d_.size(); ++i)
	{
		for (auto j = 0; j < tile_vector_2d_.at(0).size(); ++j)
		{
			if (tile_option(j - 1, i - 1) == TILE_OPTION::NORMAL)
				tile_graph_.at(i).at(j).push_back({ j - 1, i - 1 });
			if (tile_option(j, i - 1) == TILE_OPTION::NORMAL)
				tile_graph_.at(i).at(j).push_back({ j, i - 1 });
			if (tile_option(j + 1, i - 1) == TILE_OPTION::NORMAL)
				tile_graph_.at(i).at(j).push_back({ j + 1, i - 1 });

			if (tile_option(j - 1, i) == TILE_OPTION::NORMAL)
				tile_graph_.at(i).at(j).push_back({ j - 1, i });
			if (tile_option(j + 1, i) == TILE_OPTION::NORMAL)
				tile_graph_.at(i).at(j).push_back({ j + 1, i });

			if (tile_option(j - 1, i + 1) == TILE_OPTION::NORMAL)
				tile_graph_.at(i).at(j).push_back({ j - 1, i + 1 });
			if (tile_option(j, i + 1) == TILE_OPTION::NORMAL)
				tile_graph_.at(i).at(j).push_back({ j, i + 1 });
			if (tile_option(j + 1, i + 1) == TILE_OPTION::NORMAL)
				tile_graph_.at(i).at(j).push_back({ j + 1, i + 1 });
		}
	}
}

std::pair<int, int> Stage::_GetRectTileIdx(Math::Vector3 const& _position)
{
	return std::pair<int, int>{};
}

std::pair<int, int> Stage::_GetIsometricTileIdx(Math::Vector3 const& _position)
{
	std::pair<int, int> isometric_index{};

	auto y_intercept_for_iso_x_idx = static_cast<int>(std::clamp(_position.y + (_position.x * 0.5f) - (stage_size_.y * 0.5f), 0.f, stage_size_.y * (1.f - std::numeric_limits<float>::epsilon())));
	auto y_intercept_for_iso_y_idx = static_cast<int>(std::clamp(_position.y - (_position.x * 0.5f) + (stage_size_.y * 0.5f), 0.f, stage_size_.y * (1.f - std::numeric_limits<float>::epsilon())));

	isometric_index.first = static_cast<int>(y_intercept_for_iso_x_idx / tile_size_.y);
	isometric_index.second = static_cast<int>(y_intercept_for_iso_y_idx / tile_size_.y);

	return isometric_index;
}
