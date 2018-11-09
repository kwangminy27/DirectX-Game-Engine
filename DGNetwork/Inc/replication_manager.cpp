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
	// 1. Packet::Replication 표시
	// 2. 객체 마다 ReplicationIntoStream 호출
}

void ReplicationManager::ReplicateIntoStream(Object* _object)
{
	// 1. Network Id 기록
	// 2. Class Id 기록
	// 3. Object Data 기록
}

void ReplicationManager::ReceiveWorld()
{
	// 1. 일단 모든 객체를 다 받음
	// 2. 기존에 들고 있던 객체와 비교해서 누락된 객체가 있다면 그 객체 삭제
	// 3. 2의 결과인 살아있는 객체들에 대해서 데이터를 읽어들임.
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
