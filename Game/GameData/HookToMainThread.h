#pragma once
#include <mutex>

enum MESSAGE
{
	MSG_USESKILL = 100,
	MSG_ATTACKCALL,
	MSG_FINDWAY
};

struct SKILL_TO_MONS
{
	DWORD index;
	DWORD monsObj;
};
class CHookToMainThread
{
public:
	~CHookToMainThread();
	static CHookToMainThread* GetInstance();
	bool Hook();
	bool UnHook();
	void SendMessageToGame(MESSAGE msg, LPARAM lParam);
	HWND GetGameHwnd()const;
	static DWORD m_msgCode;
	static HHOOK m_hHook;
	static HHOOK m_msgHook;
	static LONG m_hWndHook;
private:
	
	static std::mutex m_mutex;
	static CHookToMainThread* m_pInstance;
private:
	CHookToMainThread();
	CHookToMainThread(const CHookToMainThread& ct);
	void operator= (const CHookToMainThread& ct);
};

LRESULT CALLBACK CallWndProc(
	_In_ int    nCode,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);
LRESULT CALLBACK GetMsgProc(
	_In_ int    code,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);
LRESULT CALLBACK WindowProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);
