#include "DGNetwork_stdafx.h"
#include "TCP_socket.h"

#include "socket_address.h"

using namespace DG;

TCPSocket::~TCPSocket()
{
	closesocket(socket_);
}

void TCPSocket::Bind(SocketAddress const& _address)
{
	int error = bind(socket_, &_address.sockaddr_, _address.GetSize());

	if (error == SOCKET_ERROR)
		throw std::exception{ "TCPSocket::Bind" };
}

void TCPSocket::Listen(int _backlog)
{
	int error = listen(socket_, _backlog);

	if (error == SOCKET_ERROR)
		throw std::exception{ "TCPSocket::Listen" };
}

std::shared_ptr<TCPSocket> TCPSocket::Accept(SocketAddress& _address)
{
	int length{};
	SOCKET new_socket = accept(socket_, &_address.sockaddr_, &length);

	if (new_socket == INVALID_SOCKET)
		throw std::exception{ "TCPSocket::Accept" };

	return std::shared_ptr<TCPSocket>{ new TCPSocket{ new_socket } };
}

void TCPSocket::Connect(SocketAddress const& _address)
{
	int error = connect(socket_, &_address.sockaddr_, _address.GetSize());

	if (error == SOCKET_ERROR)
		throw std::exception{ "TCPSocket::Connect" };
}

int TCPSocket::Send(void const* _data, int _len)
{
	int bytes_sent_count = send(socket_, static_cast<char const*>(_data), _len, 0);

	if (bytes_sent_count == SOCKET_ERROR)
		throw std::exception{ "TCPSocket::Send" };

	return bytes_sent_count;
}

int TCPSocket::Receive(void* _buffer, int _len)
{
	int bytes_received_count = recv(socket_, static_cast<char*>(_buffer), _len, 0);

	if (bytes_received_count == SOCKET_ERROR)
		throw std::exception{ "TCPSocket::Receive" };

	return bytes_received_count;
}

TCPSocket::TCPSocket(SOCKET _socket)
{
	socket_ = _socket;
}
