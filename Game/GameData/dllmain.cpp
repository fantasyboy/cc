// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "dllmain.h"
#include "ShareMemoryService.h"
#include "utils.h"
#include "GameCall.h"
#include "HookToMainThread.h"
#include "person.h"
#include "MonsterService.h"

void UseAttackAA2Mons(std::shared_ptr<monster> mons, person& ps);
void UseSkillByindex(std::shared_ptr<skill> sk, std::shared_ptr<monster> mons, person& ps);
void AutoEToHero(CMonsterService& cm, person& role);
void AutoEToMons(CMonsterService& cm, person& role);

void AutoEToMons(CMonsterService& cm, person& role)
{

	auto tempSkill = role.GetSkillService()->GetSkillByIndex(2);
	auto monserList = cm.GetMonsterListInRange(role, tempSkill->GetSkillRange());
	for (auto temp : monserList)
	{
		if (temp->BDead())
		{
			continue;
		}

		auto buffService = temp->GetBuffService()->GetBufferList();
		for (auto buff : buffService)
		{
			if (buff->GetName() == nullptr)
			{
				continue;
			}

			if (strstr(buff->GetName(), "marker") != NULL)
			{
				if (buff->GetBufferCount() > 0) {

					if (((buff->GetBufferCount() - 1)*(tempSkill->GetSkillGetAggressivity() + 0.1 * role.GetAggressivity())) + ((tempSkill->GetSkillGetAggressivity() + tempSkill->GetSkillPlusProportion() * role.GetAggressivity())) > (temp->GetCurrentHealth() + 30.0))
					{
						UseSkillByindex(tempSkill, temp, role);
					}
				}
				else
				{

					if (((tempSkill->GetSkillGetAggressivity() + tempSkill->GetSkillPlusProportion() * role.GetAggressivity())) > (temp->GetCurrentHealth() + 30.0))
					{
						UseSkillByindex(tempSkill, temp, role);
					}
				}
			}
		}
	}
}

void AutoEToHero(CMonsterService& cm, person& role)
{
	auto tempSkill = role.GetSkillService()->GetSkillByIndex(2);
	auto personList = cm.GetHeroListInRange(role, tempSkill->GetSkillRange());
	for (auto temp : personList)
	{
		if (temp->BDead())
		{
			continue;
		}

		auto buffService = temp->GetBuffService()->GetBufferList();
		for (auto buff : buffService)
		{
			if (buff->GetName() == nullptr)
			{
				continue;
			}

			if (strstr(buff->GetName(), "marker") != NULL)
			{
				if (buff->GetBufferCount() > 0) {

					if (((buff->GetBufferCount() - 1)*(tempSkill->GetSkillGetAggressivity() + 0.1 * role.GetAggressivity())) + ((tempSkill->GetSkillGetAggressivity() + tempSkill->GetSkillPlusProportion() * role.GetAggressivity())) > (temp->GetCurrentHealth() + 30.0))
					{
						UseSkillByindex(tempSkill, temp, role);
					}
				}
				else
				{

					if (((tempSkill->GetSkillGetAggressivity() + tempSkill->GetSkillPlusProportion() * role.GetAggressivity())) > (temp->GetCurrentHealth() + 30.0))
					{
						UseSkillByindex(tempSkill, temp, role);
					}
				}
			}
		}
	}
}

void UseSkillByindex(std::shared_ptr<skill> sk, std::shared_ptr<monster> mons, person& ps)
{
	static bool BUseSkill = false;
	if (
		sk->GetSkillRange() > mons->GetDistance(ps.GetPoint()) //技能范围 > 玩家距离
		&& sk->GetLevel() //技能等级 > 0
		&& sk->BCoolDown() //技能已经冷却
		&& ps.GetCurrentMagic() > sk->GetExpendMp() //玩家当前MP > 技能消耗的MP
		&& !mons->BDead()  //怪物活着
		&& !ps.BDead()    //玩家活着
		&& mons->BVisableSee() //怪物可见
		&& !BUseSkill
		)
	{
		utils::GetInstance()->log("TIPS: 开始使用技能 %x 攻击 %x", sk->GetIndex(), mons->GetNodeBase());
		SKILL_TO_MONS temp;
		temp.index = sk->GetIndex();
		temp.monsObj = mons->GetNodeBase();
		CHookToMainThread::GetInstance()->SendMessageToGame(MESSAGE::MSG_USESKILL, (LPARAM)(&temp));
		BUseSkill = true;
	}
	else
	{
		BUseSkill = false;
	}
	Sleep(1);
}

BOOL APIENTRY DllMain(HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		::CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(ThreadProc), NULL, NULL, NULL);
		break;
	}
	case DLL_THREAD_ATTACH:
	{

		break;
	}
	case DLL_THREAD_DETACH:
	{
		break;
	}
	case DLL_PROCESS_DETACH:
	{
		break;
	}

	}
	return TRUE;
}

DWORD WINAPI ThreadProc(_In_ LPVOID lpParameter)
{
	VMProtectBegin("ThreadProc");
	if (!CShareMemoryService::GetInstance()->OpenShareMemory())
	{
		utils::GetInstance()->log("HXL: CShareMemoryService::GetInstance()->OpenShareMemory()出现异常！");
		return 1;
	}
	auto pSharedMemoryPointer = CShareMemoryService::GetInstance()->GetShareMemoryPointer();
	//等待进入游戏
	while ((DWORD)GameCall::GetInstance()->GetClientTickTime() < 1 || utils::GetInstance()->read<DWORD>(pSharedMemoryPointer->game.Base_RoleSelfAddr) < 1)
	{
		utils::GetInstance()->log("HXL: 等待进入游戏中！");
		Sleep(3000);
	}

	if (!CHookToMainThread::GetInstance()->Hook())
	{
		utils::GetInstance()->log("HXL: CHookToMainThread::GetInstance()->Hook()出现异常！");
		return 1;
	}

	if (!GameCall::GetInstance()->HookUseSkill())
	{
		utils::GetInstance()->log("HXL: GameCall::GetInstance()->HookUseSkill()出现异常！");
		return 1;
	}
	VMProtectEnd();
	utils::GetInstance()->log("HXL: 开启成功！\n");

	auto tempRole = utils::GetInstance()->read<DWORD>(pSharedMemoryPointer->game.Base_RoleSelfAddr);
	if (!tempRole)
	{
		utils::GetInstance()->log("HXL: utils::GetInstance()->read<DWORD>(pSharedMemoryPointer->game.Base_RoleSelfAddr)出现异常！");
		return 1;
	}

	person role(tempRole);
	CMonsterService cm;
	while (true)
	{
		cm.travse(role);

		//预判技能Q
		if (CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.bLockQ)
		{
			if (GetAsyncKeyState(CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.VirtualKeyQ) & 0x8000)
			{
				auto tempSkill = role.GetSkillService()->GetSkillByIndex(0);
				auto mons = cm.GetHealthLeastPerson(role, tempSkill->GetSkillRange());
				if (mons)
				{
					UseSkillByindex(tempSkill, mons, role);
				}
			}
		}

		//预判W
		if (CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.bLockW)
		{
			if (GetAsyncKeyState(CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.VirtualKeyW) & 0x8000)
			{
				auto tempSkill = role.GetSkillService()->GetSkillByIndex(1);
				auto mons = cm.GetHealthLeastPerson(role, tempSkill->GetSkillRange());
				if (mons)
				{
					UseSkillByindex(tempSkill, mons, role);
				}
			}
		}



		//预判E
		if (CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.bLockE)
		{
			if (GetAsyncKeyState(CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.VirtualKeyE) & 0x8000)
			{
				auto tempSkill = role.GetSkillService()->GetSkillByIndex(2);
				auto mons = cm.GetHealthLeastPerson(role, tempSkill->GetSkillRange());
				if (mons)
				{
					UseSkillByindex(tempSkill, mons, role);
				}
			}
		}


		//预判R
		if (CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.bLockR)
		{
			if (GetAsyncKeyState(CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.VirtualKeyW) & 0x8000)
			{
				auto tempSkill = role.GetSkillService()->GetSkillByIndex(3);
				auto mons = cm.GetHealthLeastPerson(role, tempSkill->GetSkillRange());
				if (mons)
				{
					UseSkillByindex(tempSkill, mons, role);
				}
			}
		}
		//砍人 开始走A && 走A 热键被按下
		if (CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.bOpenAA && GetAsyncKeyState( CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.VirtualKeyAA) & 0x8000)
		{
			auto mons = cm.GetHealthLeastPerson(role, role.GetAttackDistance());
			UseAttackAA2Mons(mons, role);
		}
		//砍怪
		if (CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.bOpenClearAA && GetAsyncKeyState(CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.VirtualKeyOpenClear) & 0x8000)
		{
			auto mons = cm.GetHealthleastMonster(role, role.GetAttackDistance());
			UseAttackAA2Mons(mons, role);
		}

		if (CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.bAutoHuabanE)
		{
			//如果开启自定E英雄
			if (CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.bAutoEToHero)
			{
				AutoEToHero(cm, role);
				
			}
			//如果开启自动E小兵
			if (CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.bAutoEToMons)
			{
				AutoEToMons(cm, role);
			}
		}


		Sleep(15);
	}
	utils::GetInstance()->log("HXL: 线程被结束了！！");
	return 0;
}

void UseAttackAA2Mons(std::shared_ptr<monster> mons, person& ps)
{
	auto dwZouAms = (DWORD)(((float)(2.0) / ps.GetAttackSpeed())* ((float)(2.0) / ps.GetAttackSpeed()) * CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.dwZouAMs);
	static DWORD timeSec = 0;
	if (mons != nullptr
		&& mons->GetNodeBase()
		&& !ps.BDead()
		&& !mons->BDead()
		&& ps.GetAttackDistance() > ps.GetDistance(mons->GetPoint())
		&& mons->BVisableSee()
		&& GetTickCount() - timeSec > (CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.dwZouAMsNew / ps.GetAttackSpeed()))
	{
		utils::GetInstance()->log("HXL: 开始普攻逻辑！\n");
		SKILL_TO_MONS temp;
		temp.monsObj = mons->GetNodeBase();
		CHookToMainThread::GetInstance()->SendMessageToGame(MESSAGE::MSG_ATTACKCALL, (LPARAM)(&temp));
		timeSec = GetTickCount();
		Sleep(dwZouAms);
	}
	else
	{
		utils::GetInstance()->log("HXL: 走A寻路逻辑！\n");
		CHookToMainThread::GetInstance()->SendMessageToGame(MESSAGE::MSG_FINDWAY, NULL);
		
	}
}

