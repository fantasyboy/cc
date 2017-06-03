#include "stdafx.h"
#include "MonsterService.h"
#include "ShareMemoryService.h"

CMonsterService::CMonsterService()
{
}


CMonsterService::~CMonsterService()
{
}



void CMonsterService::travse(const monster& role)
{
	m_personList.clear();
	m_monsterList.clear();

	auto startAddr = utils::GetInstance()->read<DWORD>(CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_MonsterArrayAddr);
	auto endAddr = utils::GetInstance()->read<DWORD>(CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_MonsterArrayAddr + 0x4);
	for (auto i = startAddr; i != endAddr ; i += 4)
	{
		auto temp = utils::GetInstance()->read<DWORD>(i);
		if (!temp)
		{
			continue;
		}

		std::shared_ptr<person> tempObj(new person(temp));
		//玩家以及怪物列表
		if (role.GetCamp() != tempObj->GetCamp() && !tempObj->BDead())
		{
			if (tempObj->GetType() == 0x1401) {
				m_personList.push_back(tempObj);
			}
			if (tempObj->GetType() == 0xc01 && tempObj->BVisableSee() && tempObj->GetDistance(role.GetPoint()) < 1500)
			{
				m_monsterList.push_back(tempObj);
			}
		}
	}
	//utils::GetInstance()->log("HXL: 当前敌人玩家个数： %d 小兵个数： %d", m_personList.size(), m_monsterList.size());
	for (auto temp : m_monsterList)
	{
		utils::GetInstance()->log("HXL: %x ： name =  %s (%f,%f,%f) camp = %x type = %x HP= %f MP= %f",temp->GetNodeBase() ,
			temp->GetName(),
			temp->GetPoint()->x , temp->GetPoint()->z , temp->GetPoint()->y ,
			temp->GetCamp() , temp->GetType(), 
			temp->GetCurrentHealth(),
			temp->GetCurrentMagic());
	}
}

std::shared_ptr<person> CMonsterService::GetNearleastPerson(const monster& role, float distance)
{
	float minDistance = FLT_MAX;
	std::shared_ptr<person>  minDisObj= nullptr;
	for (auto temp : m_personList)
	{
		auto tempDis = temp->GetDistance(role.GetPoint());
		if (tempDis < minDistance && tempDis < distance && !temp->BDead() && temp->BVisableSee())
		{
			minDistance = tempDis;
			minDisObj = temp;
		}
	}
	return minDisObj;
}

std::shared_ptr<person> CMonsterService::GetHealthLeastPerson(const monster& role, float distance)
{
	float minHealth = FLT_MAX;
	std::shared_ptr<person> tempObj = nullptr;
	for (auto temp : m_personList)
	{
		if (temp->GetCurrentHealth() < minHealth
			&& !temp->BDead()
			&& temp->BVisableSee()
			&& temp->GetDistance(role.GetPoint()) < distance)
		{
			minHealth = temp->GetCurrentHealth();
			tempObj = temp;
		}
	}
	return tempObj;
}

std::shared_ptr<monster> CMonsterService::GetNearleastMonster(const monster& role, float distance)
{
	float minDistance = FLT_MAX;
	std::shared_ptr<monster> tempObj = nullptr;
	for (auto temp : m_monsterList)
	{
		auto tempDis = temp->GetDistance(role.GetPoint());
		if (tempDis < minDistance && tempDis < distance && !temp->BDead() && temp->BVisableSee())
		{
			minDistance = tempDis;
			tempObj = temp;
		}
	}
	return tempObj;
}

std::shared_ptr<monster> CMonsterService::GetHealthleastMonster(const monster& role, float distance)
{
	float maxHealth = FLT_MAX;
	std::shared_ptr<monster> tempObj = nullptr;
	for (auto temp : m_monsterList)
	{
		if (temp->GetCurrentHealth() < maxHealth
			&& !temp->BDead()
			&& temp->BVisableSee()
			&& temp->GetDistance(role.GetPoint()) < distance)
		{
			maxHealth = temp->GetCurrentHealth();
			tempObj = temp;
		}
	}
	return tempObj;
}

std::vector<std::shared_ptr<person>> CMonsterService::GetHeroListInRange(const monster& role, float distance)
{
	std::vector<std::shared_ptr<person>> personList;
	for (auto temp : m_personList)
	{
		if (!temp->BDead()
			&& temp->BVisableSee()
			&& temp->GetDistance(role.GetPoint()) < distance)
		{
			personList.push_back(temp);
		}
	}

	return personList;
}

std::vector<std::shared_ptr<monster>> CMonsterService::GetMonsterListInRange(const monster& role, float distance)
{
	std::vector<std::shared_ptr<monster>> monsterList;
	for (auto temp : m_monsterList)
	{
		if (!temp->BDead()
			&& temp->BVisableSee()
			&& temp->GetDistance(role.GetPoint()) < distance)
		{
			monsterList.push_back(temp);
		}
	}

	return monsterList;
}


