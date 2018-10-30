#include "DGEngine_stdafx.h"
#include "renderer.h"

#include "Resource/resource_manager.h"
#include "Resource/mesh.h"
#include "Rendering/rendering_manager.h"
#include "Rendering/shader.h"
#include "Rendering/render_state.h"
#include "Scene/scene.h"
#include "object.h"
#include "Component/transform.h"
#include "Component/camera.h"
#include "Component/material.h"
#include "Component/animation_2d.h"
#include "Component/UI.h"

using namespace DG;

void Renderer::Initialize()
{
	try
	{
		type_ = COMPONENT_TYPE::RENDERER;
	}
	catch (std::exception const& _e)
	{
		std::cerr << _e.what() << std::endl;
	}
}

void Renderer::set_mesh_tag(std::string const& _tag)
{
	mesh_tag_ = _tag;
}

void Renderer::set_shader_tag(std::string const & _tag)
{
	shader_tag_ = _tag;
}

void Renderer::set_render_state(std::string const& _tag)
{
	auto const& state = RenderingManager::singleton()->FindRenderState(_tag);

	if (!state)
		throw std::exception{ "Renderer::set_render_state" };

	render_state_array_.at(static_cast<int>(state->type())) = state;
}

Renderer::Renderer(Renderer const& _other) : Component(_other)
{
	mesh_tag_ = _other.mesh_tag_;
	shader_tag_ = _other.shader_tag_;
	render_state_array_ = _other.render_state_array_;
}

Renderer::Renderer(Renderer&& _other) noexcept : Component(std::move(_other))
{
	mesh_tag_ = std::move(_other.mesh_tag_);
	shader_tag_ = std::move(_other.shader_tag_);
	render_state_array_ = std::move(_other.render_state_array_);
}

void Renderer::_Release()
{
}

void Renderer::_Render(float _time)
{
	auto const& material = std::dynamic_pointer_cast<Material>(object()->FindComponent(COMPONENT_TYPE::MATERIAL));
	auto const& shader = RenderingManager::singleton()->FindShader(shader_tag_);
	auto const& mesh = ResourceManager::singleton()->FindMesh(mesh_tag_);

	_UpdateConstantBuffers(_time);

	shader->SetShader();

	// SetRenderState
	for (auto const& _state : render_state_array_)
	{
		if(_state)
			_state->_SetState();
	}

	for (auto i = 0; i < mesh->GetContainerSize(); ++i)
	{
		for (auto j = 0; j < mesh->GetSubsetSize(i); ++j)
		{
			material->SetToShader(i, j);

			mesh->Render(i, j);
		}
	}

	// ResetRenderState
	for (auto const& _state : render_state_array_)
	{
		if (_state)
			_state->_SetBackState();
	}
}

std::unique_ptr<Component, std::function<void(Component*)>> Renderer::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new Renderer{ *this }, [](Component* _p) {
		dynamic_cast<Renderer*>(_p)->_Release();
		delete dynamic_cast<Renderer*>(_p);
	} };
}

void Renderer::_UpdateConstantBuffers(float _time)
{
	// Transform
	_UpdateTransform();

	// Animation2D
	if (auto const& animation_2d = std::dynamic_pointer_cast<Animation2D>(object()->FindComponent(COMPONENT_TYPE::ANIMATION_2D)))
		animation_2d->UpdateAnimation2DConstantBuffer(_time);

	// UI
	auto const& UIs = object()->FindComponents(COMPONENT_TYPE::UI);
	for (auto const& _UI : UIs)
		_UI->UpdateConstantBuffer();
}

void Renderer::_UpdateTransform()
{
	std::shared_ptr<Object> camera{};

	if (object()->IsComponent(COMPONENT_TYPE::UI))
		camera = scene()->ui_camera();
	else
		camera = scene()->main_camera();

	auto const& camera_component = dynamic_pointer_cast<Camera>(camera->FindComponent(camera->tag()));
	auto const& transform = std::dynamic_pointer_cast<Transform>(object()->FindComponent(COMPONENT_TYPE::TRANSFORM));
	auto const& mesh = ResourceManager::singleton()->FindMesh(mesh_tag_);

	TransformConstantBuffer transform_constant_buffer{};
	transform_constant_buffer.world = transform->world();
	transform_constant_buffer.view = camera_component->view();
	transform_constant_buffer.projection = camera_component->projection();
	transform_constant_buffer.WVP = transform_constant_buffer.world * transform_constant_buffer.view * transform_constant_buffer.projection;
	transform_constant_buffer.pivot = transform->pivot();
	transform_constant_buffer.diagonal = mesh->diagonal();

	transform_constant_buffer.world = transform_constant_buffer.world.Transpose();
	transform_constant_buffer.view = transform_constant_buffer.view.Transpose();
	transform_constant_buffer.projection = transform_constant_buffer.projection.Transpose();
	transform_constant_buffer.WVP = transform_constant_buffer.WVP.Transpose();

	RenderingManager::singleton()->UpdateConstantBuffer("Transform", &transform_constant_buffer);
}
