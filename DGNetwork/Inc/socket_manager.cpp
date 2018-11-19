#include "DGNetwork_stdafx.h"
#include "socket_manager.h"

#include "UDP_socket.h"
#include "TCP_socket.h"

using namespace DG;

void SocketManager::Initialize()
{
}

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

std::shared_ptr<TCPSocket> SocketManager::CreateOverlappedTCPSocket(int _address_family)
{
	SOCKET s = WSASocket(_address_family, SOCK_STREAM, IPPROTO_TCP, nullptr, NULL, WSA_FLAG_OVERLAPPED);

	if(s == INVALID_SOCKET)
		throw std::exception{ "SocketManager::CreateOverlappedTCPSocket" };

	return std::shared_ptr<TCPSocket>{ new TCPSocket{ s } };
}

fd_set* SocketManager::FillSetFromVector(fd_set& _set, std::vector<std::shared_ptr<TCPSocket>> const* _sockets)
{
	if (_sockets)
	{
		FD_ZERO(&_set);

		for (std::shared_ptr<TCPSocket> const& _socket : *_sockets)
			FD_SET(_socket->socket_, &_set);

		return &_set;
	}

	return nullptr;
}

void SocketManager::FillVectorFromSet(
	std::vector<std::shared_ptr<TCPSocket>> const* _in_sockets,
	std::vector<std::shared_ptr<TCPSocket>>* _out_sockets,
	fd_set const& _in_set)
{
	if (_in_sockets && _out_sockets)
	{
		_out_sockets->clear();

		for (std::shared_ptr<TCPSocket> const& _socket : *_in_sockets)
		{
			if (FD_ISSET(_socket->socket_, &_in_set))
				_out_sockets->push_back(_socket);
		}
	}
}

int SocketManager::Select(
	std::vector<std::shared_ptr<TCPSocket>> const* _in_read_sockets,
	std::vector<std::shared_ptr<TCPSocket>>* _out_read_sockets,
	std::vector<std::shared_ptr<TCPSocket>> const* _in_write_sockets,
	std::vector<std::shared_ptr<TCPSocket>>* _out_write_sockets,
	std::vector<std::shared_ptr<TCPSocket>> const* _in_except_sockets,
	std::vector<std::shared_ptr<TCPSocket>>* _out_except_sockets)
{
	fd_set read{}, write{}, except{};
	fd_set* read_ptr = FillSetFromVector(read, _in_read_sockets);
	fd_set* write_ptr = FillSetFromVector(write, _in_write_sockets);
	fd_set* except_ptr = FillSetFromVector(except, _in_except_sockets);

	timeval time{0, 1}; // 0초 + 1마이크로초
	int count = select(0, read_ptr, write_ptr, except_ptr, &time);

	if (count > 0)
	{
		FillVectorFromSet(_in_read_sockets, _out_read_sockets, read);
		FillVectorFromSet(_in_write_sockets, _out_write_sockets, write);
		FillVectorFromSet(_in_except_sockets, _out_except_sockets, except);
	}

	return count;
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
