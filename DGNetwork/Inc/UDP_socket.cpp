#include "DGNetwork_stdafx.h"
#include "UDP_socket.h"

#include "socket_address.h"

using namespace DG;

UDPSocket::~UDPSocket()
{
	closesocket(socket_);
}

void UDPSocket::Bind(SocketAddress const& _address)
{
	int error = bind(socket_, &_address.sockaddr_, _address.GetSize());

	if (error == SOCKET_ERROR)
		throw std::exception{ "UDPSocket::Bind" };
}

int UDPSocket::SendTo(void const* _data, int _len, SocketAddress const& _address)
{
	// bytes_sent_count: 송신 대기열에 넣은 데이터의 길이
	int bytes_sent_count = sendto(socket_, static_cast<char const*>(_data), _len, 0, &_address.sockaddr_, _address.GetSize());

	if (bytes_sent_count == SOCKET_ERROR)
		throw std::exception{ "UDPSocket::SendTo" };

	return bytes_sent_count;
}

int UDPSocket::ReceiveFrom(void* _buffer, int _len, SocketAddress& _address)
{
	int length = _address.GetSize();
	int bytes_received_count = recvfrom(socket_, static_cast<char*>(_buffer), _len, 0, &_address.sockaddr_, &length);

	if (bytes_received_count == SOCKET_ERROR)
		throw std::exception{ "UDPSocket::ReceiveFrom" };

	return bytes_received_count;
}

void UDPSocket::SetNonBlockingMode(bool _non_blocking_mode_flag)
{
	u_long arg = _non_blocking_mode_flag ? 1 : 0;
	
	int error = ioctlsocket(socket_, FIONBIO, &arg);

	if (error == SOCKET_ERROR)
		throw std::exception{ "UDPSocket::SetNonBlockingMode" };
}

UDPSocket::UDPSocket(SOCKET _socket)
{
	socket_ = _socket;
}
