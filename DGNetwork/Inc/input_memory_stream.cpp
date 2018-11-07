#include "DGNetwork_stdafx.h"
#include "input_memory_stream.h"

using namespace DG;

void InputMemoryStream::Initialize()
{
	buffer_ = static_cast<char*>(std::malloc(STREAM_BUFFER_DEFAULT_SIZE));
	head_ = 0;
	capacity_ = 1024;
}

void InputMemoryStream::PreProcess()
{
	head_ = 0;
}

char const* InputMemoryStream::GetBufferPtr() const
{
	return buffer_;
}

uint32_t InputMemoryStream::GetLength() const
{
	return head_;
}

uint32_t InputMemoryStream::GetRemainingDataSize() const
{
	return capacity_ - head_;
}

void InputMemoryStream::Read(void* _data, uint32_t _byte_size)
{
	uint32_t result_byte_size = std::max(GetRemainingDataSize(), _byte_size);

	if (result_byte_size + head_ >= capacity_)
		_ReallocBuffer(std::max(capacity_ * 2, result_byte_size + head_));

	memcpy_s(_data, result_byte_size, buffer_ + head_, result_byte_size);

	head_ += result_byte_size;
}

void InputMemoryStream::_Release()
{
	std::free(buffer_);
}

void InputMemoryStream::_ReallocBuffer(uint32_t _length)
{
	buffer_ = static_cast<char*>(std::realloc(buffer_, _length));

	capacity_ = _length;
}
