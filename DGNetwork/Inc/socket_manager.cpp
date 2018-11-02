#include "DGNetwork_stdafx.h"
#include "socket_manager.h"

#include "UDP_socket.h"
#include "TCP_socket.h"

using namespace DG;

std::shared_ptr<UDPSocket> SocketManager::CreateUDPSocket(int _address_family)
{
	SOCKET s = socket(_address_family, SOCK_DGRAM, IPPROTO_UDP);

	if (s == INVALID_SOCKET)
		throw std::exception{ "SocketManager::CreateUDPSocket" };

	return std::shared_ptr<UDPSocket>{ new UDPSocket{ s } };
}

std::shared_ptr<TCPSocket> SocketManager::CreateTCPSocket(int _address_family)
{
	SOCKET s = socket(_address_family, SOCK_STREAM, IPPROTO_TCP);

	if (s == INVALID_SOCKET)
		throw std::exception{ "SocketManager::CreateTCPSocket" };

	return std::shared_ptr<TCPSocket>{ new TCPSocket{ s } };
}

SocketManager::SocketManager(SocketManager const& _other)
{
}

SocketManager::SocketManager(SocketManager&& _other) noexcept
{
}

void SocketManager::_Release()
{
}
