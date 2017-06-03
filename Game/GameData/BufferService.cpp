#include "stdafx.h"
#include "BufferService.h"


CBufferService::CBufferService(DWORD dwObjectBase): m_dwObjectBase(dwObjectBase)
{
}


CBufferService::~CBufferService()
{
}

void CBufferService::travse()
{
	m_bufferList.clear();

	//±éÀúbuff
	auto Base_BufferOffset = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_BufferOffset;

	auto startAddr = utils::GetInstance()->read<DWORD>(m_dwObjectBase + Base_BufferOffset + 0x10);
	auto endAddr = utils::GetInstance()->read<DWORD>(m_dwObjectBase + Base_BufferOffset + 0x14);
	for (auto i = 0; i != ((endAddr - startAddr) >> 3); i++)
	{
		auto tempObj = utils::GetInstance()->read<DWORD>(startAddr + 8 * i);
		if (utils::GetInstance()->read<DWORD>(tempObj) == 0xFFFFFFFF)
		{
			continue;
		}

		m_bufferList.push_back(std::shared_ptr<buffer>(new buffer(tempObj)));
	}

}

std::vector<std::shared_ptr<buffer>> CBufferService::GetBufferList()
{
	travse();
	return m_bufferList;
}
