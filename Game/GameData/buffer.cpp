#include "stdafx.h"
#include "buffer.h"


buffer::buffer(DWORD dwNodeBase): base(dwNodeBase)
{

}


buffer::~buffer()
{
}

char* buffer::GetName() const
{
	__try
	{
		auto temp = utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x4);
		if (temp)
		{
			return (char*)(temp + 0xa);
		}
	}
	__except (1)
	{

	}
	return nullptr;
}

DWORD buffer::GetBufferCount() const
{
	__try
	{
		auto temp = utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x1c) - utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x18);
		if ((temp & 0xFFFFFFF8)< 0x10)
		{
			auto Base_BufferCountOffset = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_BufferCountOffset;
			return utils::GetInstance()->read<DWORD>(GetNodeBase() + Base_BufferCountOffset);
		}
		else
		{
			return (temp >> 3);
		}
	}
	__except (1) {

	}
	return 0;
}
