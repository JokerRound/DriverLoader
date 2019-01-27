//******************************************************************************
// License:     MIT
// Author:      Hoffman
// GitHub:      https://github.com/JokerRound
// Create Time: 2019-01-24
// Description: 
//      The header file of class CProppageNT.
//
// Modify Log:
//      2019-01-24    Hoffman
//      Info: a. Add below member variables.
//              a.1. m_editFilePath;
//              a.2. m_editServiceName;
//              a.2. m_editDisplayName;
//              a.2. m_cmbServiceType;
//              a.2. m_cmbStartType;
//              a.2. m_cmbErrorControl;
//
//      2019-01-26    Hoffman
//      Info: a. Add below member variables.
//              a.1. m_acsServiceType;
//              a.2. m_adwServiceType;
//              a.3. m_acsErrorControl;
//              a.4. m_adwErrorControl;
//              a.5. m_acsStartType;
//              a.6. m_adwStartType;
//            b. Add below member methods.
//              b.1. OnBnClickedBtnSearchfile();
//              b.1. OnInitDialog();
//******************************************************************************

#pragma once

#include "ShareType.h"
// CProppageNT 对话框

class CProppageNT : public CDialogEx
{
	DECLARE_DYNAMIC(CProppageNT)

public:
	CProppageNT(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CProppageNT();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_NTDRIVER };
#endif

    CString m_acsServiceType[TOTAL_SERVTI_NUMBER] = {
        _T("Kernel"),
        _T("File system")
    };

    DWORD m_adwServiceType[TOTAL_SERVTI_NUMBER] = {
        SERVICE_KERNEL_DRIVER,
        SERVICE_FILE_SYSTEM_DRIVER
    };

    CString m_acsErrorControl[TOTAL_ECI_NUMBER] = {
        _T("Ignore"),
        _T("Normal"),
        _T("Severe"),
        _T("Critical")
    };
    DWORD m_adwErrorControl[TOTAL_ECI_NUMBER] = {
        SERVICE_ERROR_IGNORE,
        SERVICE_ERROR_NORMAL,
        SERVICE_ERROR_SEVERE,
        SERVICE_ERROR_CRITICAL
    };

    CString m_acsStartType[TOTAL_STARTCI_NUMBER] = {
        _T("Boot"),
        _T("System"),
        _T("Auto"),
        _T("Demand"),
        _T("Disabled")
    };

    DWORD m_adwStartType[TOTAL_STARTCI_NUMBER] = {
        SERVICE_BOOT_START,
        SERVICE_SYSTEM_START,
        SERVICE_AUTO_START,
        SERVICE_DEMAND_START,
        SERVICE_DISABLED
    };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedBtnSearchfile();
    CEdit m_editFilePath;
    CEdit m_editServiceName;
    CEdit m_editDisplayName;
    CComboBox m_cmbServiceType;
    CComboBox m_cmbStartType;
    CComboBox m_cmbErrorControl;
    virtual BOOL OnInitDialog();
};
