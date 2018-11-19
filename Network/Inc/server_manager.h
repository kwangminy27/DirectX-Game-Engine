#pragma once

#include "singleton_temp.h"

namespace DG
{
	class TCPSocket;

	enum class IO_OPERATION
	{
		RECV = 1 << 0,
		SEND = 1 << 1,
		MAX
	};

	struct OverlappedEx
	{
		WSAOVERLAPPED overlapped;
		IO_OPERATION operation;
		WSABUF wsa_buffer;
		unsigned char buffer[1024];
	};

	struct Client
	{
		std::shared_ptr<TCPSocket> tcp_socket;
		int id;
		OverlappedEx receive_overlapped_ex;
		unsigned char packet_buffer[1024];
		unsigned int packet_size;
		unsigned int previous_data;
		bool is_connected;
	};

	void WorkerThreadFunc();
	void AcceptThreadFunc();

	class DG_NETWORK_DLL ServerManager final : public Singleton_Temp<ServerManager>
	{
		friend class Singleton_Temp<ServerManager>;
	public:
		void Initialize() override;

		void ExcuteTCPSelectLoop();
		void ExcuteTCPEventSelectLoop();
		void ExcuteTCPIOCPLoop();

		void ProcessPacket();

		HANDLE iocp();
		std::array<Client, 100>& clients();

	private:
		ServerManager() = default;
		ServerManager(ServerManager const&) = delete;
		ServerManager(ServerManager&&) noexcept = delete;
		ServerManager& operator=(ServerManager const&) = delete;
		ServerManager& operator=(ServerManager&&) noexcept = delete;

		virtual void _Release() override;

		HANDLE iocp_{};
		std::array<Client, 100> clients_{};
	};
}
