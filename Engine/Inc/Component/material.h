#pragma once

#include "component.h"

namespace DG
{
	class Texture;
	class Sampler;

	struct DG_ENGINE_DLL SubsetMaterial
	{ // ����Ǵ� ��쿡�� Set�ϵ��� �����غ���.
		std::vector<std::shared_ptr<Texture>> texture_vector;
		std::vector<std::shared_ptr<Sampler>> sampler_vector;
		MaterialConstantBuffer material_constant_buffer;
	};

	class DG_ENGINE_DLL Material final : public Component
	{
		friend class Object;
	public:
		virtual void Initialize() override;

		void SetToShader(int _container_idx, int _subset_idx);
		void SetTexture(std::string const& _tag, int _slot, int _container_idx, int _subset_idx);
		void SetSampler(std::string const& _tag, int _slot, int _container_idx, int _subset_idx);
		void SetMaterialConstantBuffer(MaterialConstantBuffer const& _material_constant_buffer, int _container_idx, int _subset_idx);

	private:
		Material() = default;
		Material(Material const& _other);
		Material(Material&& _other) noexcept;
		Material& operator=(Material const&) = default;
		Material& operator=(Material&&) noexcept = default;

		virtual void _Release() override;

		virtual std::unique_ptr<Component, std::function<void(Component*)>> _Clone() const override;

		std::vector<std::vector<std::shared_ptr<SubsetMaterial>>> material_container_vector_{};
	};
}
