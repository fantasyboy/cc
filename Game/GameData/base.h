#pragma once
#include "utils.h"
#include "ShareMemoryService.h"
class base
{
public:
	base(DWORD dwNodeBase);
	~base();
	DWORD GetNodeBase() const;
	virtual char* GetName() const;
private:
	DWORD m_dwNodeBase;
};

