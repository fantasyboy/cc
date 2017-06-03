#pragma once
#include <memory>
#include <vector>
#include "skill.h"
class CSkillService
{
public:
	CSkillService(DWORD dwObjectBase);
	~CSkillService();
	void travse();
	std::shared_ptr<skill> GetSkillByIndex(DWORD index);
private:
	std::vector<std::shared_ptr<skill>> m_skillList;
	DWORD m_dwObjectBase;
};

