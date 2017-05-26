// MainDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Console.h"
#include "MainDialog.h"
#include "afxdialogex.h"
#include "ShareMemoryService.h"

// CMainDialog 对话框

IMPLEMENT_DYNAMIC(CMainDialog, CDialogEx)

CMainDialog::CMainDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MAIN, pParent)
{

}

CMainDialog::~CMainDialog()
{
}

void CMainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainDialog, CDialogEx)
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


BOOL CMainDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  添加自己的初始化代码


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
