#include "stdafx.h"
#include "skill.h"
#include "ShareMemoryService.h"
#include "GameCall.h"
skill::skill(DWORD dwIndex, DWORD dwNodeBase): base(dwNodeBase), m_index(dwIndex)
{

}

skill::~skill()
{
}

char* skill::GetName() const
{
	__try {
		auto Base_SkillOffset_Object = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillOffset_Object;
		auto temp = utils::GetInstance()->read<DWORD>(GetNodeBase() + Base_SkillOffset_Object);
		if (temp)
		{
			//读取名字指针，或者名字对象
			if (utils::GetInstance()->read<DWORD>(temp + 0x2c) <= 0x10)
			{
				return (char*)(temp + 0x18);
			}
			else
			{
				return (char*)(utils::GetInstance()->read<DWORD>(temp + 0x18));
			}
		}
	}
	__except (1)
	{
		utils::GetInstance()->log("HXL: skill::GetName()出现异常！");
	}
	return nullptr;
}

DWORD skill::GetLevel() const
{
	__try {
		return utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x10);
	}
	__except (1)
	{
		utils::GetInstance()->log("HXL: skill::GetLevel()出现异常！");
	}
	return 0;
}

bool skill::BCoolDown() const
{
	__try {
		return (GameCall::GetInstance()->GetClientTickTime() > utils::GetInstance()->read<float>(GetNodeBase() + 0x18));
	}
	__except (1)
	{
		utils::GetInstance()->log("HXL: skill::BCoolDown()出现异常！");
	}
	return false;
}

float skill::GetExpendMp() const
{
	__try {
		auto Base_SkillOffset_Object = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillOffset_Object;
		auto temp = utils::GetInstance()->read<DWORD>(GetNodeBase() + Base_SkillOffset_Object);
		if (temp)
		{
			auto temp2 = utils::GetInstance()->read<DWORD>(temp + 0x34);
			if (temp2)
			{
				auto Base_SkillOffset_MP = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillOffset_MP;
				return utils::GetInstance()->read<float>(temp2 + Base_SkillOffset_MP + (GetLevel() - 1) * 4);
			}
		}
	}
	__except (1)
	{
		utils::GetInstance()->log("HXL: skill::GetExpendMp()出现异常！");
	}
	return 0;
}

float skill::GetSkillRange() const
{
	if (GetSkillType() > 0)
	{
		return GetSkillType()+ 10.0;
	}

	if (GetSkillRange2() > 0)
	{
		return GetSkillRange2() +10.0;
	}

	if (GetSkillRange1() > 0)
	{
		return GetSkillRange1() +10.0;
	}

	return 0;
}

float skill::GetSkillRange1() const
{
	__try {
		//非锁定技能距离判断
		auto Base_SkillOffset_Object = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillOffset_Object;
		auto temp = utils::GetInstance()->read<DWORD>(GetNodeBase() + Base_SkillOffset_Object);
		if (temp)
		{
			auto temp2 = utils::GetInstance()->read<DWORD>(temp + 0x34);
			if (temp2)
			{
				auto Base_SkillOffset_Range1 = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillOffset_Range1;
				return utils::GetInstance()->read<float>(temp2 + Base_SkillOffset_Range1 + 4 * GetLevel());
			}
		}
	}
	__except (1) {
		utils::GetInstance()->log("ERROR: skill::GetSkillRange1()出现异常！\n");
		return 0;
	}
	return 0;
}

float skill::GetSkillRange2() const
{
	__try {
		//非锁定技能距离判断
		auto Base_SkillOffset_Object = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillOffset_Object;
		auto temp = utils::GetInstance()->read<DWORD>(GetNodeBase() + Base_SkillOffset_Object);
		if (temp)
		{
			auto temp2 = utils::GetInstance()->read<DWORD>(temp + 0x34);
			if (temp2)
			{
				auto Base_SkillOffset_Range1 = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillOffset_Range1;
				return utils::GetInstance()->read<float>(temp2 + Base_SkillOffset_Range1 + 0x20 + 4 * GetLevel());
			}
		}
	}
	__except (1) {
		utils::GetInstance()->log("ERROR: skill::GetSkillRange2()出现异常！\n");
		return 0;
	}
	return 0;
}

DWORD skill::GetIndex() const
{
	return m_index;
}

float skill::GetSkillType() const
{
	__try {
		return utils::GetInstance()->read<float>(GetNodeBase() + 0x4C);
	}
	__except (1)
	{
		utils::GetInstance()->log("ERROR: skill::GetSkillType()出现异常！\n");
	}
	return 0;
}

float skill::GetSkillGetAggressivity() const
{
	__try {
		//非锁定技能距离判断
		auto Base_SkillOffset_Object = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillOffset_Object;
		auto temp = utils::GetInstance()->read<DWORD>(GetNodeBase() + Base_SkillOffset_Object);
		if (temp)
		{
			auto temp2 = utils::GetInstance()->read<DWORD>(temp + 0x34);
			if (temp2)
			{
				auto Base_SkillOffset_Range1 = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillOffset_Range1;
				return utils::GetInstance()->read<float>(temp2 + 0x0b8 + 4 * GetLevel());
			}
		}
	}
	__except (1) {
		utils::GetInstance()->log("ERROR: skill::GetSkillRange2()出现异常！\n");
		return 0;
	}
	return 0;
}

float skill::GetSkillPlusProportion() const
{
	__try {
		auto Base_SkillOffset_Object = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillOffset_Object;
		auto temp = utils::GetInstance()->read<DWORD>(GetNodeBase() + Base_SkillOffset_Object);
		if (temp)
		{
			auto temp2 = utils::GetInstance()->read<DWORD>(temp + 0x34);
			if (temp2)
			{
				auto Base_SkillOffset_Range1 = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillOffset_Range1;
				return utils::GetInstance()->read<float>(temp2 + 0x1d0);
			}
		}
	}
	__except (1) {
		utils::GetInstance()->log("ERROR: skill::GetSkillRange2()出现异常！\n");
		return 0;
	}
	return 0;
}

