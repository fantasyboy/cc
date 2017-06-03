#pragma once
#include "CShareStruct.h"
#include <mutex>
class CShareMemoryService
{
public:
	
	~CShareMemoryService();
	static CShareMemoryService* GetInstance();

	//打开共享内存
	bool OpenShareMemory();
	//销毁共享内存
	bool DestoryShareMemory();
	//获取共享内存指针
	PSHARED_MEMORY_DATA GetShareMemoryPointer();
private:
	static std::mutex m_mutex;
	static CShareMemoryService* m_pInstance;
	PSHARED_MEMORY_DATA m_pShareMemoryPointer;
	HANDLE m_hMapping;
private:
	CShareMemoryService();
	CShareMemoryService(const CShareMemoryService& cs);
	void operator= (const CShareMemoryService& cs);
};

