#pragma once

namespace DG
{
	class SocketAddress;
	class TCPSocket;

	class DG_NETWORK_DLL TCPSocket
	{
		friend class SocketManager;
	public:
		~TCPSocket();
		void Bind(SocketAddress const& _address);
		void Listen(int _backlog);
		std::shared_ptr<TCPSocket> Accept(SocketAddress& _address);
		void Connect(SocketAddress const& _address);
		int Send(void const* _data, int _len);
		int Receive(void* _buffer, int _len);
		void ShutDown();

	private:
		TCPSocket(SOCKET _socket);

		SOCKET socket_{};
	};
}
