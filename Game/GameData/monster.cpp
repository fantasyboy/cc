#include "stdafx.h"
#include "monster.h"


monster::monster(DWORD dwNodeBase): base(dwNodeBase)
{
	m_bufferService = std::shared_ptr<CBufferService>(new CBufferService(GetNodeBase()));
}


monster::~monster()
{
}

char* monster::GetName() const
{
	__try {
		if (utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x30) < 0x10)
		{
			return (char*)(GetNodeBase() + 0x20);
		}
		else
		{
			return (char*)(utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x20));
		}
	}
	__except (1) {
		utils::GetInstance()->log("HXL: monster::GetName()出现异常！");
	}
	return nullptr;
}

float monster::GetCurrentHealth() const
{
	__try {
		return utils::GetInstance()->read<float>(GetNodeBase() + CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_MonsterCurrentHpOffset);
	}
	__except (1) {
		utils::GetInstance()->log("HXL: monster::GetCurrentHealth() 出现异常！");
	}
	return 0;
}

float monster::GetMaxHealth() const
{
	__try {
		return utils::GetInstance()->read<float>(GetNodeBase() + CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_MonsterCurrentHpOffset + 0x10);
	}
	__except (1) {
		utils::GetInstance()->log("HXL: monster::GetMaxHealth() 出现异常！");
	}
	return 0;
}

float monster::GetCurrentMagic() const
{
	__try {
		return utils::GetInstance()->read<float>(GetNodeBase() + CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_MonsterCurrentMpOffset);
	}
	__except (1) {
		utils::GetInstance()->log("HXL: monster::GetCurrentMagic()出现异常！");
	}
	return 0;
}

float monster::GetMaxMagic() const
{
	__try {
		return utils::GetInstance()->read<float>(GetNodeBase() + CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_MonsterCurrentMpOffset + 0x10);
	}
	__except (1) {
		utils::GetInstance()->log("HXL: monster::GetMaxMagic()出现异常！");
	}
	return 0;
}

PEM_POINT_3D monster::GetPoint() const
{
	__try {
		return (PEM_POINT_3D)(GetNodeBase() + 0x50);
	}
	__except (1)
	{
		utils::GetInstance()->log("HXL: monster::GetPoint()出现异常！");
	}
	return nullptr;
}

DWORD monster::GetCamp() const
{
	__try {
		return utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x14);
	}
	__except (1) {
		utils::GetInstance()->log("HXL: monster::GetCamp()出现异常！");
	}
	return 0;
}

DWORD monster::GetType() const
{
	__try {
		return utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x18);
	}
	__except (1) {
		utils::GetInstance()->log("HXL: monster::GetType()出现异常！");
	}
	return 0;
}

bool monster::BVisableSee() const
{
	__try {
		auto temp = utils::GetInstance()->read<DWORD>(GetNodeBase() + CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_MonsterBVisableOffset);
		if (temp)
		{
			return utils::GetInstance()->read<bool>(temp + 0x18);
		}
	}
	__except (1)
	{
		utils::GetInstance()->log("HXL: monster::BVisableSee()出现异常！");
	}
	return false;
}

bool monster::BDead() const
{
	__try {
		return utils::GetInstance()->read<bool>(GetNodeBase() + 0x10c) || GetCurrentHealth() < 2;
	}
	__except (1) {
		utils::GetInstance()->log("HXL: monster::BDead()出现异常！");
	}
	return true;
}

float monster::GetDistance(PEM_POINT_3D mons)
{
	return sqrt((GetPoint()->x - mons->x)* (GetPoint()->x - mons->x) + (GetPoint()->y - mons->y)* (GetPoint()->y - mons->y));
}

PEM_POINT_3D monster::GetMonsterOrientation() const
{
	__try {
		return (PEM_POINT_3D)(GetNodeBase() + CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_MonsterOrientationXOffset);
	}
	__except (1) {
		utils::GetInstance()->log("HXL: monster::GetMonsterOrientation()出现异常！");
	}
	return nullptr;
}

bool monster::BMoving() const
{
	__try {
		return utils::GetInstance()->read<bool>(GetNodeBase() + CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_MonsterBMovingOffset);
	}
	__except (1) {
		utils::GetInstance()->log("HXL: monster::BMoving()出现异常！");
	}
	return false;
}

std::shared_ptr<CBufferService> monster::GetBuffService()
{
	
	return m_bufferService;

}
