#include "DGNetwork_stdafx.h"
#include "socket_address.h"

using namespace DG;

SocketAddress::SocketAddress(uint32_t _address, uint16_t _port)
{
	_GetAsSockAddrIn()->sin_family = AF_INET;
	_GetAsSockAddrIn()->sin_addr.S_un.S_addr = htonl(_address);
	_GetAsSockAddrIn()->sin_port = htons(_port);
}

SocketAddress::SocketAddress(sockaddr const& _sockaddr)
{
	memcpy_s(&sockaddr_, sizeof(sockaddr), &_sockaddr, sizeof(sockaddr));
}

int SocketAddress::GetSize() const
{
	return static_cast<int>(sizeof(sockaddr_));
}

sockaddr_in* SocketAddress::_GetAsSockAddrIn()
{
	return reinterpret_cast<sockaddr_in*>(&sockaddr_);
}

std::shared_ptr<SocketAddress> SocketAddressFactory::CreateIPv4FromString(std::string const& _str)
{
	auto pos = _str.find_last_of(':');

	std::string host{}, service{};

	if (pos != std::string::npos)
	{
		host = _str.substr(0, pos);
		service = _str.substr(pos + 1);
	}
	else
		host = _str;

	addrinfo hints{};
	hints.ai_family = AF_INET;

	addrinfo* result{};
	int error = getaddrinfo(host.c_str(), service.c_str(), &hints, &result);
	addrinfo* init_result = result;

	// getaddrinfo()가 실패하면서 result에 무언가 있는 상황
	if (error == 0 && !result)
	{
		freeaddrinfo(init_result);
		return nullptr;
	}

	// result에 addr가 없지만 next가 남아있는 상황
	while (!result->ai_addr && result->ai_next)
		result = result->ai_next;

	// 최종 노드에도 addr가 없는 상황
	if (!result->ai_addr)
	{
		freeaddrinfo(init_result);
		return nullptr;
	}

	// DNS query를 통해 올바른 addr을 얻어온 상황
	auto return_value = std::shared_ptr<SocketAddress>{ new SocketAddress{ *result->ai_addr } };

	freeaddrinfo(init_result);

	return return_value;
}
