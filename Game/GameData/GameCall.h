#pragma once
#include <mutex>
#include "monster.h"
class GameCall
{
public:
	~GameCall();
	static GameCall* GetInstance();
	//获取游戏时间
	float GetClientTickTime()const;
	//普通攻击
	bool HeroAttack(DWORD dwNodeBase);
	//使用技能
	bool UserSkill(DWORD _index, const DWORD& mons);
	//HOOK技能CALL
	bool HookUseSkill();
	PEM_POINT_3D GetMousePnt()const;
	bool FindWay(PEM_POINT_3D pnt);
private:
	static std::mutex m_mutex;
	static GameCall* m_pInstance;
private:
	GameCall();
	GameCall(const GameCall& cg);
	void operator= (const GameCall& cg);
};

void __stdcall SkillHookStub(const DWORD& skillObj, PFLOAT xyz, PDWORD monsObj);
void skillCall(DWORD skillObj, DWORD xyz, DWORD mons);