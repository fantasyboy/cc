#include "stdafx.h"
#include "GameCall.h"
#include "utils.h"
#include "ShareMemoryService.h"
#include "skill.h"
#include "monster.h"
std::mutex GameCall::m_mutex;
GameCall* GameCall::m_pInstance = nullptr;
DWORD g_hookCallAddr = 0;
std::mutex g_mutex;
DWORD g_currentMonObj = 0;
GameCall::GameCall()
{
}


GameCall::GameCall(const GameCall& cg)
{

}

void GameCall::operator=(const GameCall& cg)
{

}

GameCall::~GameCall()
{
}

GameCall* GameCall::GetInstance()
{
	if (nullptr == m_pInstance)
	{
		m_mutex.lock();
		if (nullptr == m_pInstance)
		{
			m_pInstance = new GameCall;
		}
		m_mutex.unlock();
	}
	return m_pInstance;
}

float GameCall::GetClientTickTime() const
{
	__try {
		auto Base_GameStartTime = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_GameStartTime;
		return utils::GetInstance()->read<float>(Base_GameStartTime + 0x30);
	}
	__except (1) {
		utils::GetInstance()->log("HXL: GameCall::GetClientTickTime()出现异常！\n");
	}
	return 0;
}

bool GameCall::HeroAttack(DWORD dwNodeBase)
{
	__try {

		static DWORD timeSec = 0;
		if (GetTickCount() - timeSec < 400)
		{
			return true;
		}
		timeSec = GetTickCount();

		static float fTargetPointArray[3] = { 0 };
		memcpy(fTargetPointArray, (void*)(dwNodeBase + 0x50), sizeof(float) * 3);
		DWORD  Base_RoleSelfAddr = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_RoleSelfAddr;
		DWORD Base_AttackHeroCallAddr = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_AttackHeroCallAddr;
		utils::GetInstance()->log("HXL: 普攻怪物 = %x", dwNodeBase);
		__asm
		{
			pushad;
			push 1;
			push 0;
			push 0;
			mov esi, dwNodeBase;
			push esi;
			lea eax, fTargetPointArray;
			push eax;
			push 3;
			mov EDX, Base_RoleSelfAddr;
			mov EDX, [EDX];
			mov ecx, edx;
			mov eax, Base_AttackHeroCallAddr;
			call eax;
			popad;
		}

		return true;
	}
	__except (1)
	{
		utils::GetInstance()->log("HXL: GameCall::HeroAttack()出现异常！\n");
	}
	return false;
}

bool GameCall::UserSkill( DWORD dwIndex, const DWORD& mons)
{
	__try {

		if (!g_currentMonObj)
		{
			g_mutex.lock();
			g_currentMonObj = mons;
			g_mutex.unlock();
		}
		DWORD Base_SkillCallEcxAddr =CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillCallEcxAddr;
		DWORD Base_SkillCallAddr = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillCallAddr;
		utils::GetInstance()->log("HXL: Base_SkillCallEcxAddr = %x Base_SkillCallAddr = %x", Base_SkillCallEcxAddr, Base_SkillCallAddr);
		__asm
		{
			pushad;
			mov     ecx, Base_SkillCallEcxAddr;
			mov     ecx, dword ptr[ecx];
			mov     ecx, dword ptr[ecx + 0x30];
			push    0;
			push    2;
			push    dwIndex;
			mov     eax, Base_SkillCallAddr;
			call    eax;
			popad;
		}

		return true;
	}
	__except (1)
	{
		utils::GetInstance()->log("HXL: GameCall::UserSkill()出现异常！\n");
	}
	return false;
}

bool GameCall::HookUseSkill()
{
	VMProtectBegin("HookUseSkill");
	DWORD HookAddr = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillCallHookAddr;
	//保存CALL地址
	g_hookCallAddr = utils::GetInstance()->read<DWORD>(HookAddr + 0x1) + HookAddr + 5;
	char hookData[5] = { 0xe8, 0x0, 0x0, 0x0, 0x0 };
	*(DWORD*)(&hookData[1]) = (DWORD)(&SkillHookStub) - HookAddr - 0x5;
	DWORD oldProtected = 0;
	VirtualProtect((LPVOID)HookAddr, 5, PAGE_READWRITE, &oldProtected);
	memcpy((void*)HookAddr, (void*)hookData, 5);
	VirtualProtect((LPVOID)HookAddr, 5, oldProtected, &oldProtected);
	VMProtectEnd();
	return true;
}

PEM_POINT_3D GameCall::GetMousePnt() const
{
	__try {
		auto dwBase = utils::GetInstance()->read<DWORD>(CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_MousePointAddr);
		if (dwBase)
		{
			auto offset1 = utils::GetInstance()->read<DWORD>(dwBase + 0x10);
			if (offset1)
			{
				return (PEM_POINT_3D)(offset1 + 0x10);
			}
		}
		
	}
	__except (1) {
		utils::GetInstance()->log("HXL: GameCall::GetMousePnt()出现异常！");
	}
	return nullptr;
}

bool GameCall::FindWay(PEM_POINT_3D pnt)
{
	__try
	{
		static float fArray[32] = { 0 };
		fArray[0] = pnt->x;
		fArray[1] = pnt->z;
		fArray[2] = pnt->y;
		fArray[3] = pnt->x;
		fArray[4] = pnt->z;
		fArray[5] = pnt->y;

		DWORD Base_RoleSelfAddr = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_RoleSelfAddr;
		DWORD Base_FindWayCallAddr = CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_FindWayCallAddr;
		__asm
		{
			PUSHAD;
			PUSH 1;
			PUSH 0;
			PUSH 0;
			PUSH 0;
			LEA EAX, fArray;
			PUSH EAX;
			PUSH 2;
			MOV ECX, Base_RoleSelfAddr;
			MOV ECX, DWORD PTR DS : [ECX];
			MOV EAX, Base_FindWayCallAddr;
			CALL EAX;
			POPAD;
		}
	}
	__except (1)
	{
		utils::GetInstance()->log("HXL: 寻路出现异常！\n");
		return false;
	}
	return TRUE;
}



void __stdcall SkillHookStub(const DWORD& skillObj, PFLOAT xyz, PDWORD monsObj)
{
	try {
		//判断是否有对象存在，如果有就调用自己的逻辑，没有的酒调用默认逻辑
		g_mutex.lock();
		auto mons = g_currentMonObj;
		g_currentMonObj = NULL;
		g_mutex.unlock();
		if (mons)
		{
			std::shared_ptr<monster> tempMons(new monster(mons));
			if (!tempMons->BDead())
			{
				std::shared_ptr<skill> tempSkill(new skill(0, skillObj));
				//如果怪物活着
				if (tempMons->BMoving() &&(DWORD)tempSkill->GetSkillType() == 0)
				{
					if (tempSkill->GetSkillRange2() > 0)
					{
						//调用预判逻辑
						EM_POINT_3D pnt = { 0 };
						pnt.x = tempMons->GetPoint()->x + tempMons->GetMonsterOrientation()->x * (float)(200.0);
						pnt.z = tempMons->GetPoint()->z + tempMons->GetMonsterOrientation()->z * (float)(200.0);
						pnt.y = tempMons->GetPoint()->y + tempMons->GetMonsterOrientation()->y * (float)(200.0);

						memcpy(xyz, &pnt, 0xc);
					}
					else
					{
						//锁定逻辑
						*monsObj = tempMons->GetNodeBase();
					}
				}
				else
				{
					memcpy(xyz, tempMons->GetPoint(), 0xc);
					*monsObj = tempMons->GetNodeBase();
				}
			}
			else
			{
				//如果怪物死亡
				*monsObj = 0;
			}
			return;
		}
		__asm {
			push monsObj;
			push xyz;
			push skillObj;
			mov eax, g_hookCallAddr;
			call eax;
		}
	}
	catch (...)
	{

	}

}

void skillCall(DWORD skillObj, DWORD _xyz, DWORD mons)
{
	PDWORD monsObj = &mons;
	PFLOAT xyz = (PFLOAT)(_xyz);
	__asm {
		push monsObj;
		push xyz;
		push skillObj;
		mov eax, 0x00A16330;
		call eax;
	}
}
