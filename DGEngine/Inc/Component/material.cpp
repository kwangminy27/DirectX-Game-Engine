#include "DGEngine_stdafx.h"
#include "material.h"

#include "Resource/resource_manager.h"
#include "Resource/texture.h"
#include "Resource/sampler.h"
#include "Rendering/rendering_manager.h"

using namespace DG;

void Material::Initialize()
{
	type_ = COMPONENT_TYPE::MATERIAL;
}

void Material::SetToShader(int _container_idx, int _subset_idx)
{
	auto const& subset_material = material_container_vector_.at(_container_idx).at(_subset_idx); // Player aniamtion_enable 1�� �Ǿ��ϴµ� ��� 0��
	auto const& texture = subset_material->texture;
	auto const& sampler = subset_material->sampler;

	if (texture)
		texture->SetToShader(subset_material->texture_slot);

	if (sampler)
		sampler->SetToShader(subset_material->sampler_slot);

	RenderingManager::singleton()->UpdateConstantBuffer("Material", &subset_material->material_constant_buffer);
}

void Material::SetTexture(std::string const& _tag, int _slot, int _container_idx, int _subset_idx)
{
	if (_container_idx >= material_container_vector_.size())
		material_container_vector_.resize(_container_idx + 1);

	if (_subset_idx >= material_container_vector_.at(_container_idx).size())
		material_container_vector_.at(_container_idx).resize(_subset_idx + 1);

	if (!material_container_vector_.at(_container_idx).at(_subset_idx))
	{
		material_container_vector_.at(_container_idx).at(_subset_idx) = std::shared_ptr<SubsetMaterial>{ new SubsetMaterial, [](SubsetMaterial* _p) {
			delete _p;
		} };
	}

	auto const& subset_material = material_container_vector_.at(_container_idx).at(_subset_idx);
	subset_material->texture = ResourceManager::singleton()->FindTexture(_tag);
	subset_material->texture_slot = _slot;
}

void Material::SetSampler(std::string const& _tag, int _slot, int _container_idx, int _subset_idx)
{
	if (_container_idx >= material_container_vector_.size())
		material_container_vector_.resize(_container_idx + 1);

	if (_subset_idx >= material_container_vector_.at(_container_idx).size())
		material_container_vector_.at(_container_idx).resize(_subset_idx + 1);

	if (!material_container_vector_.at(_container_idx).at(_subset_idx))
	{
		material_container_vector_.at(_container_idx).at(_subset_idx) = std::shared_ptr<SubsetMaterial>{ new SubsetMaterial, [](SubsetMaterial* _p) {
			delete _p;
		} };
	}

	auto const& subset_material = material_container_vector_.at(_container_idx).at(_subset_idx);
	subset_material->sampler = ResourceManager::singleton()->FindSampler(_tag);
	subset_material->sampler_slot = _slot;
}

void Material::SetMaterialConstantBuffer(MaterialConstantBuffer const& _material_constant_buffer, int _container_idx, int _subset_idx)
{
	if (_container_idx >= material_container_vector_.size())
		material_container_vector_.resize(_container_idx + 1);

	if (_subset_idx >= material_container_vector_.at(_container_idx).size())
		material_container_vector_.at(_container_idx).resize(_subset_idx + 1);

	if (!material_container_vector_.at(_container_idx).at(_subset_idx))
	{
		material_container_vector_.at(_container_idx).at(_subset_idx) = std::shared_ptr<SubsetMaterial>{ new SubsetMaterial, [](SubsetMaterial* _p) {
			delete _p;
		} };
	}

	material_container_vector_.at(_container_idx).at(_subset_idx)->material_constant_buffer = _material_constant_buffer;
}

Material::Material(Material const& _other) : Component(_other)
{
	material_container_vector_ = _other.material_container_vector_;
}

Material::Material(Material&& _other) noexcept : Component(std::move(_other))
{
	material_container_vector_ = std::move(_other.material_container_vector_);
}

void Material::_Release()
{
}

std::unique_ptr<Component, std::function<void(Component*)>> Material::_Clone() const
{
	return std::unique_ptr<Component, std::function<void(Component*)>>{ new Material{ *this }, [](Component* _p) {
		dynamic_cast<Material*>(_p)->_Release();
		delete dynamic_cast<Material*>(_p);
	} };
}
