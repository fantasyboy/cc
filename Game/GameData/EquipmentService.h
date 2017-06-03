#pragma once
#include <memory>
#include <vector>
#include "equipment.h"
class CEquipmentService
{
public:
	CEquipmentService(DWORD dwObjectBase);
	~CEquipmentService();
	void travse();
private:
	DWORD m_dwObjectBase;
	std::vector<std::shared_ptr<equipment>> m_equipmentList;
};

