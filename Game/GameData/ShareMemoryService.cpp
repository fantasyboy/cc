#include "stdafx.h"
#include "ShareMemoryService.h"

std::mutex CShareMemoryService::m_mutex;
CShareMemoryService* CShareMemoryService::m_pInstance = nullptr;
CShareMemoryService::CShareMemoryService()
{
}


CShareMemoryService::CShareMemoryService(const CShareMemoryService& cs)
{

}

void CShareMemoryService::operator=(const CShareMemoryService& cs)
{

}

CShareMemoryService::~CShareMemoryService()
{
	if (m_pShareMemoryPointer)
	{
		DestoryShareMemory();
	}
}

CShareMemoryService* CShareMemoryService::GetInstance()
{
	if (nullptr == m_pInstance)
	{
		m_mutex.lock();
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CShareMemoryService;
		}
		m_mutex.unlock();
	}
	return m_pInstance;
}

bool CShareMemoryService::OpenShareMemory()
{
	m_hMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, false, US_MAP_NAME);
	if (!m_hMapping)
	{
		return false;
	}

	m_pShareMemoryPointer = (PSHARED_MEMORY_DATA)(MapViewOfFile(m_hMapping, FILE_MAP_ALL_ACCESS, NULL, NULL, NULL));

	if (m_pShareMemoryPointer)
	{
		return true;
	}

	return false;
}


bool CShareMemoryService::DestoryShareMemory()
{
	if (m_pShareMemoryPointer)
	{
		UnmapViewOfFile(m_pShareMemoryPointer);
		m_pShareMemoryPointer = nullptr;
	}

	if (m_hMapping)
		CloseHandle(m_hMapping);

	return true;
}

PSHARED_MEMORY_DATA CShareMemoryService::GetShareMemoryPointer()
{
	return m_pShareMemoryPointer;
}
