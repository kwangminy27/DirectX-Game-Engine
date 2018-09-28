#include "DGEngine_stdafx.h"
#include "renderer.h"

#include "Resource/resource_manager.h"
#include "Resource/mesh.h"
#include "Rendering/rendering_manager.h"
#include "Rendering/shader.h"

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

void Renderer::set_mesh(std::string const& _tag)
{
	mesh_ = ResourceManager::singleton()->FindMesh(_tag);
}

void Renderer::set_mesh(std::shared_ptr<Mesh> const& _mesh)
{
	mesh_ = _mesh;
}

void Renderer::set_shader(std::string const& _tag)
{
	shader_ = RenderingManager::singleton()->FindShader(_tag);
}

void Renderer::set_shader(std::shared_ptr<Shader> const& _shader)
{
	shader_ = _shader;
}

Renderer::Renderer(Renderer const& _other) : Component(_other)
{
	mesh_ = _other.mesh_;
	shader_ = _other.shader_;
}

Renderer::Renderer(Renderer&& _other) noexcept : Component(std::move(_other))
{
	mesh_ = std::move(_other.mesh_);
	shader_ = std::move(_other.shader_);
}

void Renderer::_Release()
{
}

void Renderer::_Render(float _time)
{
	shader_->SetShader();
	mesh_->Render();
}

std::unique_ptr<Component, std::function<void(Component*)>> Renderer::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new Renderer{ *this }, [](Component* _p) {
		dynamic_cast<Renderer*>(_p)->_Release();
		delete dynamic_cast<Renderer*>(_p);
	} };
}
