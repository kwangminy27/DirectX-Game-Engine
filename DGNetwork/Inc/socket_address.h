#pragma once

namespace DG
{
	// sockaddr wrapper class
	class DG_NETWORK_DLL SocketAddress
	{
		friend class UDPSocket;
		friend class TCPSocket;
	public:
		SocketAddress(uint32_t _address, uint16_t _port);
		SocketAddress(sockaddr const& _sockaddr);

		int GetSize() const;

	private:
		sockaddr_in* _GetAsSockAddrIn();

		sockaddr sockaddr_{};
	};

	class DG_NETWORK_DLL SocketAddressFactory
	{
	public:
		static std::shared_ptr<SocketAddress> CreateIPv4FromString(std::string const& _str);
	};
}
