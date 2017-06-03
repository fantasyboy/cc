#pragma once
#include "base.h"
class skill :
	public base
{
public:
	skill(DWORD dwIndex , DWORD dwNodeBase);
	~skill();
	//获取技能名字
	virtual char* GetName() const;
	//获取技能等级
	DWORD GetLevel()const;
	//技能是否冷却
	bool BCoolDown()const;
	//获取技能蓝耗
	float GetExpendMp()const;
	//获取技能范围
	float GetSkillRange() const;
	//获取技能范围1
	float GetSkillRange1() const;
	//获取技能范围2
	float GetSkillRange2() const;
	//获取技能索引
	DWORD GetIndex()const;
	//获取玩家是否是锁定技能 如果是锁定技能，这里就是范围
	float GetSkillType()const;
	//获取技能基础攻击
	float GetSkillGetAggressivity()const;
	//获取技能攻击力加成比例
	float GetSkillPlusProportion()const;

private:
	DWORD m_index;

};

