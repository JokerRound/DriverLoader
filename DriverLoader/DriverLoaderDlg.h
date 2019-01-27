//******************************************************************************
// License:     MIT
// Author:      Hoffman
// GitHub:      https://github.com/JokerRound
// Create Time: 2019-01-23
// Description: 
//      The header file of class CDriverLoaderDlg.
//
// Modify Log:
//      2019-01-23    Hoffman
//      Info: a. Add below member variables.
//              a.1.
//
//      2019-01-26    Hoffman
//      Info: a. Modify below member method.
//              a.1. OnInitDialog();
//                  a.1.1. Add initialize for tab control.
//            b. Add below member methods.
//              b.1. OnBnClickedBtnLoaddriver();
//              b.2. OnDestroy();
//              b.3. StopAndDeleteService();
//              b.4. OnBnClickedBtnUnloaddriver();
//******************************************************************************

#pragma once
#include "ProppageNT.h"
#include "ShareType.h"
#include "ShareMacro.h"

// CDriverLoaderDlg 对话框
class CDriverLoaderDlg : public CDialogEx
{
// 构造
public:
	CDriverLoaderDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRIVERLOADER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
private:
    CString m_acsProppageTitle[TOTAL_DTTCI_NUMBER] = {
        _T("NT")
    };

    DWORD m_adwProppageResource[TOTAL_DTTCI_NUMBER] = {
        IDD_PROPPAGE_NTDRIVER
    };

    CDialog *m_apProppage[TOTAL_DTTCI_NUMBER] = {
        &m_pageNT
    };

    int m_iCurrentSelectPage = 0;
    SC_HANDLE m_hSCManager = NULL;
public:
    CTabCtrl m_tabDriverType;
    CProppageNT m_pageNT;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnLoaddriver();
    afx_msg void OnDestroy();
    afx_msg void OnBnClickedBtnUnloaddriver();
    BOOL StopAndDeleteService(const CString kcsSeirvceName);
};
