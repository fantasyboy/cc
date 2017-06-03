#pragma once
#include "monster.h"
#include "BufferService.h"
#include "SkillService.h"
class person :
	public monster
{
public:
	person(DWORD dwNodeBase);
	~person();

	//获取玩家普攻距离
	float GetAttackDistance()const;
	//获取玩家攻击速度
	float GetAttackSpeed()const;
	//获取移动速度
	float GetMoveSpeed()const;
	//获取玩家攻击力
	float GetAggressivity()const;

	std::shared_ptr<CSkillService> GetSkillService();

private:
	std::shared_ptr<CSkillService> m_skillService;
};

