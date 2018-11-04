#pragma once

using namespace DG;

template <typename T>
void InputMemoryStream::Read(T& _data)
{
	static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value, "InputMemoryStream::Read");

	// ������ ��Ʋ�����, ��Ʈ��ũ�� �򿣵�� -> �����ʿ�
	T swapped_data = ByteSwap(_data);
	Read(&swapped_data, sizeof(swapped_data));
}