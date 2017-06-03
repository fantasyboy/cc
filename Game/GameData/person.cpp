#include "stdafx.h"
#include "person.h"


person::person(DWORD dwNodeBase):monster(dwNodeBase)
{
	m_skillService = std::shared_ptr<CSkillService>(new CSkillService(GetNodeBase()));;
}


person::~person()
{

}

float person::GetAttackDistance() const
{
	__try {
		auto dwBase = utils::GetInstance()->read<DWORD>(CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_BufferAddr);
		if (dwBase)
		{
			auto dwOffset1 = utils::GetInstance()->read<DWORD>(dwBase + 0x20);
			if (dwOffset1)
			{
				auto dwOffset2 = utils::GetInstance()->read<DWORD>(dwOffset1 + 0x4);
				if (dwOffset2)
				{
					auto dwOffset3 = utils::GetInstance()->read<DWORD>(dwOffset2 + 0x10);
					if (dwOffset3)
					{
						//加个模型的宽度
						return (utils::GetInstance()->read<float>(dwOffset3 + 0x68) + (float)20.0);
					}
				}
			}
		}
	}
	__except (1) {
		utils::GetInstance()->log("ERROR: person::GetAttackRange() 出现异常！\n");
		return 0;
	}
	return 0;
}

float person::GetAttackSpeed() const
{
	__try {
		auto dwBase = utils::GetInstance()->read<DWORD>(CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_BufferAddr);
		if (dwBase)
		{
			auto dwOffset1 = utils::GetInstance()->read<DWORD>(dwBase + 0x20);
			if (dwOffset1)
			{
				auto dwOffset2 = utils::GetInstance()->read<DWORD>(dwOffset1 + 0x4);
				if (dwOffset2)
				{
					auto dwOffset3 = utils::GetInstance()->read<DWORD>(dwOffset2 + 0x10);
					if (dwOffset3)
					{
						return utils::GetInstance()->read<float>(dwOffset3 + 0x18);
					}
				}
			}
		}
	}
	__except (1)
	{
		utils::GetInstance()->log("ERROR: person::GetAttackSpeed()　出现异常！\n");
		return 0;
	}
	return 0;
}

float person::GetMoveSpeed() const
{
	__try {
		auto dwBase = utils::GetInstance()->read<DWORD>(CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_BufferAddr);
		if (dwBase)
		{
			auto dwOffset1 = utils::GetInstance()->read<DWORD>(dwBase + 0x20);
			if (dwOffset1)
			{
				auto dwOffset2 = utils::GetInstance()->read<DWORD>(dwOffset1 + 0x4);
				if (dwOffset2)
				{
					auto dwOffset3 = utils::GetInstance()->read<DWORD>(dwOffset2 + 0x10);
					if (dwOffset3)
					{
						return utils::GetInstance()->read<float>(dwOffset3 + 0x28);
					}
				}
			}
		}
	}
	__except (1)
	{
		utils::GetInstance()->log("ERROR: person::GetMoveSpeed()出现异常！\n");
	}
	return 0;
}

float person::GetAggressivity() const
{
	__try {
		auto dwBase = utils::GetInstance()->read<DWORD>(CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_BufferAddr);
		if (dwBase)
		{
			auto dwOffset1 = utils::GetInstance()->read<DWORD>(dwBase + 0x20);
			if (dwOffset1)
			{
				auto dwOffset2 = utils::GetInstance()->read<DWORD>(dwOffset1 + 0x4);
				if (dwOffset2)
				{
					auto dwOffset3 = utils::GetInstance()->read<DWORD>(dwOffset2 + 0x10);
					if (dwOffset3)
					{
						return utils::GetInstance()->read<float>(dwOffset3 + 0x10);
					}
				}
			}
		}
	}
	__except (1)
	{
		utils::GetInstance()->log("ERROR: person::GetAggressivity()出现异常！\n");
	}
	return 0;
}

std::shared_ptr<CSkillService> person::GetSkillService()
{
	return m_skillService;
}
