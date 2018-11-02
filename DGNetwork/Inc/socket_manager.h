#pragma once

#include "singleton_temp.h"

namespace DG
{
	class UDPSocket;
	class TCPSocket;

	// UDP, TCP 家南 积己 淬寸
	class DG_NETWORK_DLL SocketManager final : public Singleton_Temp<SocketManager>
	{
		friend class Singleton_Temp<SocketManager>;
	public:
		std::shared_ptr<UDPSocket> CreateUDPSocket(int _address_family);
		std::shared_ptr<TCPSocket> CreateTCPSocket(int _address_family);

	private:
		SocketManager() = default;
		SocketManager(SocketManager const& _other);
		SocketManager(SocketManager&& _other) noexcept;
		SocketManager& operator=(SocketManager const&) = default;
		SocketManager& operator=(SocketManager&&) noexcept = default;

		virtual void _Release() override;
	};
}
