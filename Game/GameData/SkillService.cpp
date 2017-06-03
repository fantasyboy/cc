#include "stdafx.h"
#include "SkillService.h"


CSkillService::CSkillService(DWORD dwObjectBase):m_dwObjectBase(dwObjectBase)
{
}


CSkillService::~CSkillService()
{
}

void CSkillService::travse()
{
	m_skillList.clear();

	auto Base_SkillTravseOffset1 = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillTravseOffset1;
	auto Base_SkillTravseOffset2 = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillTravseOffset2;
	auto dwBase = m_dwObjectBase + Base_SkillTravseOffset1 + Base_SkillTravseOffset2;

	for (auto i = 0 ; i != 0x3f ; i++)
	{
		auto skillBase = utils::GetInstance()->read<DWORD>(dwBase + i * 4);
		if (!skillBase || !utils::GetInstance()->read<DWORD>(skillBase + CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillOffset_Object))
		{
			continue;
		}

		m_skillList.push_back(std::shared_ptr<skill>(new skill(i, skillBase)));
	}

}

std::shared_ptr<skill> CSkillService::GetSkillByIndex(DWORD index)
{
	travse();
	if (index >= m_skillList.size())
	{
		return m_skillList.at(0);
	}
	return m_skillList.at(index);
}
