#pragma once

template <typename T>
void MemoryStream::Serialize(T& _data)
{
	static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value, "MemoryStream::Serialize(T& _data)");

	uint32_t platform_endianess = 0x12345678;
	uint32_t network_endianess = htonl(platform_endianess);

	if (platform_endianess == network_endianess)
		Serialize(&_data, sizeof(T));
	else
	{
		if (IsInput())
		{
			T data{};
			Serialize(&data, sizeof(T));
			_data = ByteSwap(data);
		}
		else
		{
			T swapped_data = ByteSwap(_data);
			Serialize(&swapped_data, sizeof(T));
		}
	}
}