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
		virtual void Initialize() override;

		std::shared_ptr<UDPSocket> CreateUDPSocket(int _address_family);
		std::shared_ptr<TCPSocket> CreateTCPSocket(int _address_family);
		std::shared_ptr<TCPSocket> CreateOverlappedTCPSocket(int _address_family);

		fd_set* FillSetFromVector(fd_set& _out_set, std::vector<std::shared_ptr<TCPSocket>> const* _in_sockets);
		void FillVectorFromSet(
			std::vector<std::shared_ptr<TCPSocket>> const* _in_sockets,
			std::vector<std::shared_ptr<TCPSocket>>* _out_sockets,
			fd_set const& _in_set);
		int Select(
			std::vector<std::shared_ptr<TCPSocket>> const* _in_read_sockets,
			std::vector<std::shared_ptr<TCPSocket>>* _out_read_sockets,
			std::vector<std::shared_ptr<TCPSocket>> const* _in_write_sockets,
			std::vector<std::shared_ptr<TCPSocket>>* _out_write_sockets,
			std::vector<std::shared_ptr<TCPSocket>> const* _in_except_sockets,
			std::vector<std::shared_ptr<TCPSocket>>* _out_except_sockets);

	private:
		SocketManager() = default;
		SocketManager(SocketManager const& _other);
		SocketManager(SocketManager&& _other) noexcept;
		SocketManager& operator=(SocketManager const&) = default;
		SocketManager& operator=(SocketManager&&) noexcept = default;

		virtual void _Release() override;
	};
}
