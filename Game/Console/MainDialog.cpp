// MainDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Console.h"
#include "MainDialog.h"
#include "afxdialogex.h"
#include "ShareMemoryService.h"
#include "InjectDll.h"
#include "virtualKey.h"
// CMainDialog 对话框

IMPLEMENT_DYNAMIC(CMainDialog, CDialogEx)

CMainDialog::CMainDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MAIN, pParent)
	, m_zouAMsShow(0)
	, m_zouKanShow(0)
{

}

CMainDialog::~CMainDialog()
{
}

void CMainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_bLockQCheckBox);
	DDX_Control(pDX, IDC_CHECK2, m_bLockWCheckBox);
	DDX_Control(pDX, IDC_CHECK3, m_bLockECheckBox);
	DDX_Control(pDX, IDC_CHECK4, m_bLockRCheckBox);
	DDX_Control(pDX, IDC_EDIT1, m_hotKeyQ);
	DDX_Control(pDX, IDC_EDIT2, m_hotKeyW);
	DDX_Control(pDX, IDC_EDIT3, m_hotKeyE);
	DDX_Control(pDX, IDC_EDIT4, m_hotKeyR);
	DDX_Control(pDX, IDC_CHECK5, m_bZouA2PerCheckBox);
	DDX_Control(pDX, IDC_CHECK6, m_bZouA2MonsCheckBox);
	DDX_Control(pDX, IDC_EDIT6, m_hotKeyZouAPer);
	DDX_Control(pDX, IDC_EDIT7, m_hotKeyZouA2Mons);
	DDX_Control(pDX, IDC_SLIDER1, m_zouActl);
	DDX_Text(pDX, IDC_STATIC_ZOUKAN, m_zouAMsShow);
	DDX_Control(pDX, IDC_CHECK7, m_bAutoHuaBanE);
	DDX_Control(pDX, IDC_CHECK8, m_bAutoEMons);
	DDX_Control(pDX, IDC_CHECK9, m_bAutoEPer);
	DDX_Control(pDX, IDC_SLIDER2, m_zouKanQianYao);
	DDX_Text(pDX, IDC_STATIC_ZOUKAN2, m_zouKanShow);
}


BEGIN_MESSAGE_MAP(CMainDialog, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &CMainDialog::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CMainDialog::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CMainDialog::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CMainDialog::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CMainDialog::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &CMainDialog::OnBnClickedCheck6)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CMainDialog::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDC_CHECK7, &CMainDialog::OnBnClickedCheck7)
	ON_BN_CLICKED(IDC_CHECK8, &CMainDialog::OnBnClickedCheck8)
	ON_BN_CLICKED(IDC_CHECK9, &CMainDialog::OnBnClickedCheck9)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CMainDialog::OnNMCustomdrawSlider2)
END_MESSAGE_MAP()


// CMainDialog 消息处理程序


void CMainDialog::PreInitDialog()
{
	// TODO: 创建共享内存
	if (!CShareMemoryService::GetInstance()->CreateShareMemory()) {
		AfxMessageBox("通信失败，请联系作者更新程序，或者重启电脑！");
		return;
	}
		
	CDialogEx::PreInitDialog();
}


void CMainDialog::InitGameStruct()
{
	VMProtectBegin("InitGameStruct");
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_GameStartTime = 0x01AA2768;    //游戏开局时间     偏移:1    //OD地址:0x008DF27E
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_RoleSelfAddr = 0x01A9EA20;    //玩家基地址     偏移:2    //OD地址:0x005E0482
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_BufferAddr = 0x01A9C290;    //buff数组基地址     偏移:2    //OD地址:0x00BB4BEA
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_MonsterArrayAddr = 0x02AC8104;    //怪物数组基地址     偏移:2    //OD地址:0x00C688C2
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_GameWndHwndAddr = 0x01A9C508;    //游戏窗口基地址     偏移:2    //OD地址:0x008301D4
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillTravseOffset1 = 0x00002948;    //技能数组第一层偏移     偏移:1    //OD地址:0x0059478D
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillTravseOffset2 = 0x00000560;    //技能数组第二层偏移     偏移:2    //OD地址:0x007426C0
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillOffset_Object = 0x000000F4;    //技能对象偏移     偏移:2    //OD地址:0x005947A4
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillCallEcxAddr = 0x01A9D2FC;    //技能CALL ECX     偏移:2    //OD地址:0x00E55E48
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillCallAddr = 0x00BDB500;    //技能CALL     偏移:1    //OD地址:0x00E55E6F
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillCallHookAddr = 0x00B0236D;    //技能CALL Hook     偏移:1    //OD地址:0x00B0236D
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_AttackHeroCallAddr = 0x007E7560;    //普攻CALL     偏移:1    //OD地址:0x0076168E
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_FindWayCallAddr = 0x007E7560;    //寻路call     偏移:1    //OD地址:0x0062FC72
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_MonsterCurrentMpOffset = 0x000001F4;    //当前蓝量偏移     偏移:5    //OD地址:0x00C5F30F
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_MonsterCurrentHpOffset = 0x0000056C;    //当前血量偏移     偏移:4    //OD地址:0x007C43B7（已更新）
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_MonsterBVisableOffset = 0x00003A58;    //是否可见偏移     偏移:2    //OD地址:0x00A5BF03
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_equipmentTravseOffset1 = 0x000015D8;    //装备数组遍历偏移1     偏移:2    //OD地址:0x00C2227B
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_equipmentTravseOffset2 = 0x00000288;    //装备数组遍历偏移2     偏移:3    //OD地址:0x00C40349
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_MousePointAddr = 0x1A9D2FC;            //鼠标位置基地址（已更新）
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillOffset_Range1 = 0x3b0;		 //技能范围偏移（已更新）
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_SkillOffset_MP = 0x000005AC;    //技能蓝耗偏移     偏移:5    //OD地址:0x0077FBDB（已更新）
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_MonsterOrientationXOffset = 0x312C;  //玩家X朝向
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_MonsterBMovingOffset = 0x4C54; //玩家是否移动
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_BufferOffset = 0x2FD0;
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->game.Base_BufferCountOffset = 0x7C;
	VMProtectEnd();
}

BOOL CMainDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//初始化游戏数据
	InitGameStruct();

	//初始化界面设置相关
	m_hotKeyQ.SetWindowTextA(KeyNames[VK_SPACE].text);
	m_hotKeyW.SetWindowTextA(KeyNames[VK_SPACE].text);
	m_hotKeyE.SetWindowTextA(KeyNames[VK_SPACE].text);
	m_hotKeyR.SetWindowTextA(KeyNames[VK_SPACE].text);
	m_hotKeyZouAPer.SetWindowTextA(KeyNames[VK_SPACE].text);
	m_hotKeyZouA2Mons.SetWindowTextA(KeyNames['C'].text);
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.VirtualKeyQ = VK_SPACE;
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.VirtualKeyW = VK_SPACE;
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.VirtualKeyE = VK_SPACE;
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.VirtualKeyR = VK_SPACE;
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.VirtualKeyAA = VK_SPACE;
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.VirtualKeyOpenClear = 'C';

	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.dwZouAMs = 50;
	m_zouActl.SetPos(50);

	m_zouKanQianYao.SetRange(500, 1100);
	m_zouKanQianYao.SetPos(1000);
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.dwZouAMsNew = 1000;
	//注入线程
	m_threadHanle = ::CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(ThreadProcA), this, NULL, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CMainDialog::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.bLockQ = m_bLockQCheckBox.GetCheck() == BST_CHECKED ? true : false;
	m_hotKeyQ.EnableWindow((m_bLockQCheckBox.GetCheck() != BST_CHECKED));
}


void CMainDialog::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.bLockW = m_bLockWCheckBox.GetCheck() == BST_CHECKED ? true : false;
	m_hotKeyW.EnableWindow((m_bLockWCheckBox.GetCheck() != BST_CHECKED));
}


void CMainDialog::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.bLockE = m_bLockECheckBox.GetCheck() == BST_CHECKED ? true : false;
	m_hotKeyE.EnableWindow(m_bLockECheckBox.GetCheck() != BST_CHECKED);
}


void CMainDialog::OnBnClickedCheck4()
{
	// TODO: 在此添加控件通知处理程序代码
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.bLockR = m_bLockRCheckBox.GetCheck() == BST_CHECKED ? true : false;
	m_hotKeyR.EnableWindow(m_bLockRCheckBox.GetCheck() != BST_CHECKED);
}

DWORD WINAPI ThreadProcA(_In_ LPVOID lpParameter)
{
	//监视窗口的回调函数
	CInjectDll injectClass("GameData.dll");
	while (true)
	{

		auto hwnd = FindWindow("RiotWindowClass", NULL);
		if (hwnd)
		{
			//如果没有注入
			if (!injectClass.GetInject()) {
				injectClass.injectDll(hwnd);
			}
		}
		else
		{
			//如果游戏退出，设置成没有注入
			injectClass.SetInject(false);

		}
		Sleep(100);
	}
}


BOOL CMainDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
	{
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN)
	{
		//设置Q
		if (::GetFocus() == m_hotKeyQ.GetSafeHwnd())
		{
			m_hotKeyQ.SetWindowTextA(KeyNames[pMsg->wParam].text);
			CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.VirtualKeyQ = pMsg->wParam;
		}

		//设置W
		if (::GetFocus() == m_hotKeyW.GetSafeHwnd())
		{
			m_hotKeyW.SetWindowTextA(KeyNames[pMsg->wParam].text);
			CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.VirtualKeyW = pMsg->wParam;
		}

		//设置E
		if (::GetFocus() == m_hotKeyE.GetSafeHwnd())
		{
			m_hotKeyE.SetWindowTextA(KeyNames[pMsg->wParam].text);
			CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.VirtualKeyE = pMsg->wParam;
		}
		//设置R
		if (::GetFocus() == m_hotKeyR.GetSafeHwnd())
		{
			m_hotKeyR.SetWindowTextA(KeyNames[pMsg->wParam].text);
			CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.VirtualKeyR = pMsg->wParam;
		}
		//设置走A
		if (::GetFocus() == m_hotKeyZouAPer.GetSafeHwnd())
		{
			m_hotKeyZouAPer.SetWindowTextA(KeyNames[pMsg->wParam].text);
			CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.VirtualKeyAA = pMsg->wParam;
		}
		//设置清线
		if (::GetFocus() == m_hotKeyZouA2Mons.GetSafeHwnd())
		{
			m_hotKeyZouA2Mons.SetWindowTextA(KeyNames[pMsg->wParam].text);
			CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.VirtualKeyOpenClear = pMsg->wParam;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMainDialog::OnBnClickedCheck5()
{
	// TODO: 在此添加控件通知处理程序代码
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.bOpenAA = m_bZouA2PerCheckBox.GetCheck() == BST_CHECKED ? true : false;
	m_hotKeyZouAPer.EnableWindow(m_bZouA2PerCheckBox.GetCheck() != BST_CHECKED);
}


void CMainDialog::OnBnClickedCheck6()
{
	// TODO: 在此添加控件通知处理程序代码
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.bOpenClearAA = m_bZouA2MonsCheckBox.GetCheck() == BST_CHECKED ? true : false;
	m_hotKeyZouA2Mons.EnableWindow(m_bZouA2MonsCheckBox.GetCheck() != BST_CHECKED);
}


void CMainDialog::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.dwZouAMs = m_zouActl.GetPos();
	m_zouAMsShow = m_zouActl.GetPos();
	UpdateData(FALSE);
	*pResult = 0;
}


void CMainDialog::OnBnClickedCheck7()
{
	// TODO: 在此添加控件通知处理程序代码
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.bAutoHuabanE = m_bAutoHuaBanE.GetCheck() == BST_CHECKED ? true : false;
	//m_hotKeyZouAPer.EnableWindow(m_bZouA2PerCheckBox.GetCheck() != BST_CHECKED);
}

void CMainDialog::OnBnClickedCheck8()
{
	// TODO: 在此添加控件通知处理程序代码
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.bAutoEToMons = m_bAutoEMons.GetCheck() == BST_CHECKED ? true : false;
}


void CMainDialog::OnBnClickedCheck9()
{
	// TODO: 在此添加控件通知处理程序代码
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.bAutoEToHero = m_bAutoEPer.GetCheck() == BST_CHECKED ? true : false;
}


void CMainDialog::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CShareMemoryService::GetInstance()->GetShareMemoryPointer()->ui.dwZouAMsNew= m_zouKanQianYao.GetPos();
	m_zouKanShow = m_zouKanQianYao.GetPos();
	UpdateData(FALSE);
	*pResult = 0;
}
