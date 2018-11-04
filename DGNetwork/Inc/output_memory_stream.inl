#pragma once

using namespace DG;

template <typename T>
void OutputMemoryStream::Write(T const& _data)
{
	// arithmetic�̳� enum�� ��츸 ó��
	static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value, "OutputMemoryStream::Write");
	
	// ������ ��Ʋ�����, ��Ʈ��ũ�� �򿣵�� -> �����ʿ�
	T swapped_data = ByteSwap(_data);
	Write(&swapped_data, sizeof(swapped_data));
}