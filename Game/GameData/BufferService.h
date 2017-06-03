#pragma once
#include <memory>
#include <vector>
#include "buffer.h"
class CBufferService
{
public:
	CBufferService(DWORD dwObjectBase);
	~CBufferService();
	void travse();
	std::vector<std::shared_ptr<buffer>> GetBufferList();
private:
	std::vector<std::shared_ptr<buffer>> m_bufferList;
	DWORD m_dwObjectBase;
};

