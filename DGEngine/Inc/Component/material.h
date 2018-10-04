#pragma once

#include "component.h"

namespace DG
{
	class Texture;
	class Sampler;

	struct DG_ENGINE_DLL SubsetMaterial
	{ // 변경되는 경우에만 Set하도록 수정해보자.
		std::shared_ptr<Texture> texture;
		int texture_slot;
		std::shared_ptr<Sampler> sampler;
		int sampler_slot;
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
