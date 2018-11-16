#pragma once

#include "singleton_temp.h"

namespace DG
{
	class Object;

	class DG_NETWORK_DLL LinkingContext final : public Singleton_Temp<LinkingContext>
	{
		friend class Singleton_Temp<LinkingContext>;
	public:
		virtual void Initialize() override;

		uint32_t GetNetworkId(Object const* _object, bool _should_create_if_not_found);
		void AddObject(Object* _object, uint32_t _network_id);
		void RemoveObject(Object* _object);

	protected:
		LinkingContext() = default;
		LinkingContext(LinkingContext const&) = delete;
		LinkingContext(LinkingContext&&) noexcept = delete;
		LinkingContext& operator=(LinkingContext const&) = delete;
		LinkingContext& operator=(LinkingContext&&) noexcept = delete;

		virtual void _Release() override;

		std::unordered_map<uint32_t, Object*> network_id_to_object_map_{};
		std::unordered_map<Object const*, uint32_t> object_to_network_id_map_{};
		uint32_t next_network_id_{};
	};
}
