#include "DGNetwork_stdafx.h"
#include "replication_manager.h"

#include "linking_context.h"
#include "output_memory_stream.h"

using namespace DG;

void ReplicationManager::Initialize()
{
}

void ReplicationManager::ReplicationWorldState(std::vector<Object*> const & _all_object)
{
	// 1. Packet::Replication ǥ��
	// 2. ��ü ���� ReplicationIntoStream ȣ��
}

void ReplicationManager::ReplicateIntoStream(Object* _object)
{
	// 1. Network Id ���
	// 2. Class Id ���
	// 3. Object Data ���
}

void ReplicationManager::ReceiveWorld()
{
	// 1. �ϴ� ��� ��ü�� �� ����
	// 2. ������ ��� �ִ� ��ü�� ���ؼ� ������ ��ü�� �ִٸ� �� ��ü ����
	// 3. 2�� ����� ����ִ� ��ü�鿡 ���ؼ� �����͸� �о����.
}

void ReplicationManager::ReceiveReplicatedObject()
{
	uint32_t network_id{};
	uint32_t class_id{};
}

void ReplicationManager::_Release()
{
}

void DG::ReplicationHeader::Create()
{
}

void DG::ReplicationHeader::Update()
{
}

void DG::ReplicationHeader::Destory()
{
}

void DG::ReplicationHeader::ProcessReplicationAction()
{
}
