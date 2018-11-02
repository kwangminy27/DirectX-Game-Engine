#pragma once

namespace DG
{
	class SocketAddress;

	class DG_NETWORK_DLL UDPSocket
	{
		friend class SocketManager;
	public:
		~UDPSocket();
		void Bind(SocketAddress const& _address);
		int SendTo(void const* _data, int _len, SocketAddress const& _address);
		int ReceiveFrom(void* _buffer, int _len, SocketAddress& _address);
		
		void SetNonBlockingMode(bool _non_blocking_mode_flag);

	private:
		UDPSocket(SOCKET _socket);

		SOCKET socket_{};
	};
}
