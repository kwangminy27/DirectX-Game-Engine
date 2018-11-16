#pragma once

#include "singleton_temp.h"

namespace DG
{
	class Object;

	class DG_NETWORK_DLL ReplicationManager final : public Singleton_Temp<ReplicationManager>
	{
		friend class Singleton_Temp<ReplicationManager>;
	public:
		virtual void Initialize() override;

		// ����
		void ReplicationWorldState(std::vector<Object*> const& _all_object);
		void ReplicateIntoStream(Object* _object);

		// Ŭ��
		void ReceiveWorld();
		void ReceiveReplicatedObject();

	protected:
		ReplicationManager() = default;
		ReplicationManager(ReplicationManager const&) = delete;
		ReplicationManager(ReplicationManager&&) noexcept = delete;
		ReplicationManager& operator=(ReplicationManager const&) = delete;
		ReplicationManager& operator=(ReplicationManager&&) noexcept = delete;

		virtual void _Release() override;
	};

	enum ReplicationAction
	{
		CREATE,
		UPDATE,
		DESTROY,
		MAX
	};

	class ReplicationHeader
	{
	public:
		ReplicationHeader() = default;
		~ReplicationHeader() = default;

		void Create();
		void Update();
		void Destory();
		void ProcessReplicationAction();

	private:
		ReplicationAction replication_action_{};
		uint32_t network_id_{};
		uint32_t class_id_{};
	};
}

// ��ü ���� ������Ʈ��

// ���� ����ȭ ���
// 1. ���� ��ü ����ȭ
// 2. ��Ÿ ����ȭ

// ��ü ���� �κ� ���÷����̼�

// RPC
