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

	// getaddrinfo()�� �����ϸ鼭 result�� ���� �ִ� ��Ȳ
	if (error == 0 && !result)
	{
		freeaddrinfo(init_result);
		return nullptr;
	}

	// result�� addr�� ������ next�� �����ִ� ��Ȳ
	while (!result->ai_addr && result->ai_next)
		result = result->ai_next;

	// ���� ��忡�� addr�� ���� ��Ȳ
	if (!result->ai_addr)
	{
		freeaddrinfo(init_result);
		return nullptr;
	}

	// DNS query�� ���� �ùٸ� addr�� ���� ��Ȳ
	auto return_value = std::shared_ptr<SocketAddress>{ new SocketAddress{ *result->ai_addr } };

	freeaddrinfo(init_result);

	return return_value;
}
