#include "DGNetwork_stdafx.h"
#include "output_memory_stream.h"

using namespace DG;

OutputMemoryStream::~OutputMemoryStream()
{
	std::free(buffer_);
}

char const* OutputMemoryStream::GetBufferPtr() const
{
	return buffer_;
}

uint32_t OutputMemoryStream::GetLength() const
{
	return head_;
}

void OutputMemoryStream::Write(void const* _data, size_t _byte_count)
{
	uint32_t result_head = head_ + static_cast<uint32_t>(_byte_count);

	if (result_head > capacity_)
		_ReallocBuffer(std::max(capacity_ * 2, result_head));

	memcpy_s(buffer_ + head_, _byte_count, _data, _byte_count);

	head_ = result_head;
}

void OutputMemoryStream::_ReallocBuffer(uint32_t _length)
{
	buffer_ = static_cast<char*>(std::realloc(buffer_, _length));

	capacity_ = _length;
}
