
// Console.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Console.h"
#include "ConsoleDlg.h"
#include <string>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CConsoleApp

BEGIN_MESSAGE_MAP(CConsoleApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CConsoleApp 构造

CConsoleApp::CConsoleApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CConsoleApp 对象

CConsoleApp theApp;


// CConsoleApp 初始化

BOOL CConsoleApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));


	// TODO: 自己的工作

	//判断是否多开
	if (BMoreOpen())
		return FALSE;

	//释放资源到指定的目录 并且注册资源
	if (!ReleaseResoureToFilePath())
	{
		AfxMessageBox("释放资源到指定目录失败！");
		return FALSE;
	}

	::CoInitialize(NULL);
	pAuth.CreateInstance(__uuidof(CurrencyAuth));

	//内存加载VNC文件
	if (!LoadVNCFromMemory())
	{
		AfxMessageBox("从内存加载通信文件失败！");
		return FALSE;
	}

	auto result = pAuth->Initialize("{C1E14188-7629-4B10-B2B5-E03B523C90E6}");//验证组件初始化

	if (result == -1)
	{
		pAuth.Release();
		::CoUninitialize();
		return FALSE;
	}



	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CConsoleDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

bool CConsoleApp::BMoreOpen()
{
	auto temp = ::CreateMutex(NULL, FALSE, "Console_hxl");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(temp);
		return true;
	}
	return false;
}

bool CConsoleApp::ReleaseResoureToFilePath()
{
	HRSRC HIdrDllAllP = ::FindResource(NULL, MAKEINTRESOURCE(IDR_DLL_ALLP), "dll");
	if (!HIdrDllAllP)
	{
		return false;
	}

	auto IdrSize = SizeofResource(NULL, HIdrDllAllP);
	if (!IdrSize)
	{
		return false;
	}

	HGLOBAL hGlobal = LoadResource(NULL, HIdrDllAllP);
	if (!hGlobal)
	{
		return false;
	}

	LPVOID pBuffer = LockResource(hGlobal);
	if (!pBuffer)
	{
		return false;
	}

	auto hFile =  CreateFile("c:\\AllpurAuthentic.dll", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (!hFile)
		return false;
	DWORD dwWriteSize;
	WriteFile(hFile, hGlobal, IdrSize, &dwWriteSize, NULL);
	CloseHandle(hFile);

	WinExec("regsvr32  \"c:\\AllpurAuthentic.dll\" ", SW_HIDE);

	return true;
}

bool CConsoleApp::LoadVNCFromMemory()
{
	HRSRC hRsrc = ::FindResource(NULL, MAKEINTRESOURCE(IDR_VNC_VSGROUP), "vnc");
	if (!hRsrc)
	{
		return FALSE;
	}
	DWORD dwSize = SizeofResource(NULL, hRsrc);
	if (!dwSize)
	{
		return FALSE;
	}
	HGLOBAL hGlobal = LoadResource(NULL, hRsrc);
	if (!hGlobal)
	{
		return FALSE;
	}
	LPVOID pBuffer = LockResource(hGlobal);
	if (NULL == pBuffer)
		return FALSE;

	pAuth->InputVNC((int)pBuffer, dwSize);
	return true;
}

