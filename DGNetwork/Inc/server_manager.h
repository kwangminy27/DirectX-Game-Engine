#pragma once

#include "singleton_temp.h"

namespace DG
{
	struct OverlapEx
	{
		WSAOVERLAPPED overlapped;
		WSABUF wsa_buffer;
		unsigned char receive_buffer[1500];
		int operation;
	};

	class DG_NETWORK_DLL ServerManager final : public Singleton_Temp<ServerManager>
	{
		friend class Singleton_Temp<ServerManager>;
	public:
		void Initialize() override;

		void ExcuteTCPSelectLoop();
		void ExcuteTCPEventSelectLoop();
		//void ExcuteTCPIOCPLoop();

		//static void WorkFunc(HANDLE _iocp);
		//static void AcceptFunc();

	private:
		ServerManager() = default;
		ServerManager(ServerManager const&) = delete;
		ServerManager(ServerManager&&) noexcept = delete;
		ServerManager& operator=(ServerManager const&) = delete;
		ServerManager& operator=(ServerManager&&) noexcept = delete;

		virtual void _Release() override;
	};
}
