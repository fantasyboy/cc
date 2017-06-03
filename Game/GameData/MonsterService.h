#pragma once
#include <memory>
#include <vector>
#include "person.h"
class CMonsterService
{
public:
	CMonsterService();
	~CMonsterService();
	void travse(const monster& role);

	//获取距离范围内最近的敌人玩家
	std::shared_ptr<person> GetNearleastPerson(const monster& role, float distance);
	//获取距离范围内血量最低的玩家
	std::shared_ptr<person> GetHealthLeastPerson(const monster& role, float distance);
	//获取距离范围内最近的敌人怪物
	std::shared_ptr<monster> GetNearleastMonster(const monster& role, float distance);
	//获取距离范围内最低血量的怪物
	std::shared_ptr<monster> GetHealthleastMonster(const monster& role, float distance);
	//获取范围内的英雄数组
	std::vector<std::shared_ptr<person>> GetHeroListInRange(const monster& role, float distance);
	//获取范围内的小兵数组
	std::vector<std::shared_ptr<monster>> GetMonsterListInRange(const monster& role, float distance);
private:
	//人物列表
	std::vector<std::shared_ptr<person>> m_personList;
	//怪物列表
	std::vector<std::shared_ptr<monster>> m_monsterList;
};

