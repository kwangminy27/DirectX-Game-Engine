#include "DGNetwork_stdafx.h"
#include "input_memory_stream.h"

using namespace DG;

InputMemoryStream::~InputMemoryStream()
{
	std::free(buffer_);
}

uint32_t InputMemoryStream::GetRemainingDataSize() const
{
	return capacity_ - head_;
}

void InputMemoryStream::Read(void* _data, uint32_t _byte_size)
{
	uint32_t result_byte_size = std::max(GetRemainingDataSize(), _byte_size);

	memcpy_s(_data, result_byte_size, buffer_ + head_, result_byte_size);

	head_ += result_byte_size;
}
