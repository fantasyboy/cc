#include "stdafx.h"
#include "HookToMainThread.h"
#include "utils.h"
#include "ShareMemoryService.h"
#include "GameCall.h"
std::mutex CHookToMainThread::m_mutex;
CHookToMainThread* CHookToMainThread::m_pInstance = nullptr;
DWORD CHookToMainThread::m_msgCode = RegisterWindowMessage("MyMsgCodeEx");;
HHOOK CHookToMainThread::m_hHook;
HHOOK CHookToMainThread::m_msgHook;
LONG CHookToMainThread::m_hWndHook;
CHookToMainThread::CHookToMainThread()
{
}


CHookToMainThread::CHookToMainThread(const CHookToMainThread& ct)
{

}

void CHookToMainThread::operator=(const CHookToMainThread& ct)
{

}

CHookToMainThread::~CHookToMainThread()
{
	UnHook();
}

CHookToMainThread* CHookToMainThread::GetInstance()
{
	if (nullptr == m_pInstance)
	{
		m_mutex.lock();
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CHookToMainThread;
		}
		m_mutex.unlock();
	}
	return m_pInstance;
}

bool CHookToMainThread::Hook()
{
	auto hwnd = GetGameHwnd();
	if (!hwnd)
	{
		return false;
	}
	auto threadId = GetWindowThreadProcessId(hwnd, NULL);
	if (!threadId)
	{
		return false;
	}

	m_hHook = SetWindowsHookEx(WH_CALLWNDPROC, CallWndProc, NULL, threadId);
	//m_hWndHook = SetWindowLong(hwnd, GWL_WNDPROC, (LONG)WindowProc);
	//m_msgHook = SetWindowsHookEx(WH_GETMESSAGE, GetMsgProc, NULL, threadId);
	if (!m_hHook)
		return false;
	return true;
}

bool CHookToMainThread::UnHook()
{
	return UnhookWindowsHookEx(m_hHook);
}

void CHookToMainThread::SendMessageToGame(MESSAGE msg, LPARAM lParam)
{
	::SendMessage(GetGameHwnd(), m_msgCode, msg, lParam);
}

HWND CHookToMainThread::GetGameHwnd() const
{
	__try {
		return (HWND)(utils::GetInstance()->read<DWORD>(CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_GameWndHwndAddr));
	}
	__except (1)
	{
		utils::GetInstance()->log("HXL: CHookToMainThread::GetGameHwnd()出现异常！");
	}

	return 0;
}

LRESULT CALLBACK CallWndProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	//获取参数结构体
	CWPSTRUCT *pArg = (CWPSTRUCT*)lParam;

	if (nCode == HC_ACTION)
	{
		//如果是自定义消息
		if (pArg->message == CHookToMainThread::m_msgCode)
		{
			//根据消息ID来处理消息
			switch (pArg->wParam)
			{
			case MESSAGE::MSG_USESKILL : {
				SKILL_TO_MONS p = *(SKILL_TO_MONS*)pArg->lParam;
				utils::GetInstance()->log("HXL: index = %d monsObj = %x", p.index, p.monsObj);
				GameCall::GetInstance()->UserSkill(p.index, p.monsObj);
				break;
			}
			case MESSAGE::MSG_ATTACKCALL:
			{
				SKILL_TO_MONS p = *(SKILL_TO_MONS*)pArg->lParam;
				GameCall::GetInstance()->HeroAttack(p.monsObj);
				break;
			}
			case MESSAGE::MSG_FINDWAY:
			{
				auto pnt = GameCall::GetInstance()->GetMousePnt();
				GameCall::GetInstance()->FindWay(pnt);
				
				break;
			}
			}//switch 结束

			return 1;
		}//自定义消息结束，不传递消息

	}

	//传递给系统默认消息
	return CallNextHookEx(CHookToMainThread::m_hHook, nCode, wParam, lParam);
}

LRESULT CALLBACK GetMsgProc(_In_ int code, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	if (code == HC_ACTION)
	{
		PMSG msg = (PMSG)(lParam);
		
		if (msg->wParam == 'Q' || msg->wParam == 'q')
		{
			utils::GetInstance()->log("HXL:%d %d %d", msg->message, msg->lParam, msg->wParam);
			return 0;
		}
	}
	
	return CallNextHookEx(CHookToMainThread::m_msgHook, code, wParam, lParam);
}

LRESULT CALLBACK WindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	if (wParam == 'Q' || wParam == 'q')
	{
		return 1;
	}

	return CallWindowProc((WNDPROC)CHookToMainThread::m_hWndHook, hwnd, uMsg, wParam, lParam);
}
