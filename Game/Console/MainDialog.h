#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMainDialog 对话框

class CMainDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDialog)

public:
	CMainDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAIN };
#endif
	HANDLE m_threadHanle;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void PreInitDialog();
	void InitGameStruct();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	CButton m_bLockQCheckBox;
	CButton m_bLockWCheckBox;
	CButton m_bLockECheckBox;
	CButton m_bLockRCheckBox;
	CEdit m_hotKeyQ;
	CEdit m_hotKeyW;
	CEdit m_hotKeyE;
	CEdit m_hotKeyR;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	CButton m_bZouA2PerCheckBox;
	CButton m_bZouA2MonsCheckBox;
	CEdit m_hotKeyZouAPer;
	CEdit m_hotKeyZouA2Mons;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_zouActl;
	DWORD m_zouAMsShow;
	CButton m_bAutoHuaBanE;
	afx_msg void OnBnClickedCheck7();
	CButton m_bAutoEMons;
	afx_msg void OnBnClickedCheck8();
	CButton m_bAutoEPer;
	afx_msg void OnBnClickedCheck9();
	CSliderCtrl m_zouKanQianYao;
	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	DWORD m_zouKanShow;
};
DWORD WINAPI ThreadProcA(_In_ LPVOID lpParameter);