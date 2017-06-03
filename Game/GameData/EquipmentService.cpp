#include "stdafx.h"
#include "EquipmentService.h"
#include "ShareMemoryService.h"

CEquipmentService::CEquipmentService(DWORD dwObjectBase):m_dwObjectBase(dwObjectBase)
{
}


CEquipmentService::~CEquipmentService()
{
}

void CEquipmentService::travse()
{
	m_equipmentList.clear();
	auto NodeBase = m_dwObjectBase + CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_equipmentTravseOffset1 + CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_equipmentTravseOffset2;
	for (auto i = 0 ; i != 0x27 ; i++)
	{
		auto temp = utils::GetInstance()->read<DWORD>(NodeBase + 4 * i);
		if (!temp || !utils::GetInstance()->read<DWORD>(temp))
		{
			continue;
		}

		m_equipmentList.push_back(std::shared_ptr<equipment>(new equipment(temp)));
	}
}
