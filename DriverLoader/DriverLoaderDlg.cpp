﻿//******************************************************************************
// License:     MIT
// Author:      Hoffman
// GitHub:      https://github.com/JokerRound
// Create Time: 2019-01-23
// Description: 
//      The achieve file of class CDriverLoaderDlg.
//
// Modify Log:
//      2019-01-26    Hoffman
//      Info: a. Modify below member method.
//              a.1. OnInitDialog();
//                  a.1.1. Add initialize for tab control.
//            b. Add below member methods.
//              b.1. OnBnClickedBtnLoaddriver();
//              b.2. OnDestroy();
//              b.3. StopAndDeleteService();
//              b.4. OnBnClickedBtnUnloaddriver();
//
//      2019-02-18    Hoffman
//      Info: a. Moidfy below member methods.
//              a.1. OnBnClickedBtnLoaddriver();
//                  a.1.1. Add other message info.
//                  a.1.2. Call GetDriverInfo.
//              a.2. OnBnClickedBtnUnloaddriver();
//                  a.2.1. Add other message info.
//                  a.2.2. Call GetDriverInfo.
//              a.3. StopAndDeleteService();
//                  a.3.1. Add SERIVCE_SOTPPED check.
//            b. Add below member methods.
//              b.1. GetDriverInfo();
//******************************************************************************

#include "stdafx.h"
#include "DriverLoader.h"
#include "DriverLoaderDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDriverLoaderDlg 对话框


CDriverLoaderDlg::CDriverLoaderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRIVERLOADER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDriverLoaderDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB_DRIVERTYPECONTROL, m_tabDriverType);
}

BEGIN_MESSAGE_MAP(CDriverLoaderDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(ID_BTN_LOADDRIVER, 
                  &CDriverLoaderDlg::OnBnClickedBtnLoaddriver)
    ON_WM_DESTROY()
    ON_BN_CLICKED(ID_BTN_UNLOADDRIVER, 
                  &CDriverLoaderDlg::OnBnClickedBtnUnloaddriver)
END_MESSAGE_MAP()


// CDriverLoaderDlg 消息处理程序

BOOL CDriverLoaderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

#ifdef DEBUG
    DWORD dwError = -1;
    CString csErrorMessage;
    DWORD dwLine = 0;
    BOOL bOutputErrMsg = FALSE;
#endif // DEBUG
    BOOL bRet = FALSE;
    CRect rctFeildToShow;
    m_tabDriverType.GetClientRect(&rctFeildToShow);
    rctFeildToShow.top += 25;
    rctFeildToShow.bottom -= 5;
    rctFeildToShow.left += 5;
    rctFeildToShow.right -= 5;
    
    for (int cntI = DTTCI_NT; cntI < TOTAL_DTTCI_NUMBER; cntI++)
    {
        // Insert title.
        m_tabDriverType.InsertItem(cntI, m_acsProppageTitle[cntI]);

        // Create page and point parent window.
        bRet = m_apProppage[cntI]->Create(m_adwProppageResource[cntI],
                                          &m_tabDriverType);
        if (!bRet)
        {
#ifdef DEBUG
            dwError = GetLastError();
            GetErrorMessage(dwError, csErrorMessage);
            OutputDebugStringWithInfo(csErrorMessage, __FILET__, __LINE__);
#endif // DEBUG 
        }
        
        // Move page to target postion, and take it hide.
        m_apProppage[cntI]->MoveWindow(rctFeildToShow);
        m_apProppage[cntI]->ShowWindow(SW_HIDE);
    }
    
    // Set the first page to show.
    m_iCurrentSelectPage = DTTCI_NT;
    m_tabDriverType.SetCurSel(DTTCI_NT);
    m_apProppage[DTTCI_NT]->ShowWindow(SW_NORMAL);

    // Open SCManager.
    do
    {
        if (NULL == m_hSCManager)
        {
            break;
        }
        
        m_hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
        if (NULL == m_hSCManager)
        {
#ifdef DEBUG
            dwError = GetLastError();
            GetErrorMessage(dwError, csErrorMessage);
            OutputDebugStringWithInfo(csErrorMessage, __FILET__, __LINE__);
#endif // DEBUG 
        }
    } while (FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDriverLoaderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, 
                    reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDriverLoaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//******************************************************************************
// Author:              Hoffman
// Create Time:         2019-01-26
// Last Time:           2019-02-18
// Logical Descrition:  
//      Deal with button unload driver is clicked.
//      Get information of service, then create it.
//      The message info is different, it accord with the different error 
//      occation. 
//******************************************************************************
void CDriverLoaderDlg::OnBnClickedBtnLoaddriver()
{
#ifdef DEBUG
    DWORD dwError = -1;
    CString csErrorMessage;
    DWORD dwLine = 0;
    BOOL bOutputErrMsg = FALSE;
#endif // DEBUG

    CString csMessageInfo = _T("");

    // Load NT Driver.
    if (DTTCI_NT == m_iCurrentSelectPage)
    {
        SC_HANDLE hService = NULL;
        BOOL bLoadSuccessful = FALSE;

        do
        {
            // Check SCManager handle.
            if (NULL == m_hSCManager)
            {
                m_hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
                if (NULL == m_hSCManager)
                {
#ifdef DEBUG
                    dwLine = __LINE__;
                    bOutputErrMsg = TRUE;
#endif // DEBUG 
                    break;
                }
            }

            if (!GetDriverInfo())
            {
#ifdef DEBUG
                OutputDebugStringWithInfo(
                    _T("Get driver info failed.\r\n"),
                    __FILET__,
                    __LINE__
                );
#endif // DEBUG
                break;
            }

            // Check serivce exist or not.
            if (!StopAndDeleteService())
            {
#ifdef DEBUG
                OutputDebugStringWithInfo(
                    _T("Stop and delete service failed.\r\n"),
                    __FILET__,
                    __LINE__
                );
#endif // DEBUG
                break;
            }

            // Create Serivce.
            hService = CreateService(
                m_hSCManager,
                m_csServiceName,
                m_csDisplayName,
                SERVICE_ALL_ACCESS,
                m_pageNT.m_adwServiceType[m_iServiceType],
                m_pageNT.m_adwStartType[m_iStartType],
                m_pageNT.m_adwErrorControl[m_iErrorControl],
                m_csBinaryPath,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL
            );
            if (NULL == hService)
            {
#ifdef DEBUG
                dwLine = __LINE__;
                bOutputErrMsg = TRUE;
#endif // DEBUG 
                csMessageInfo = _T("Create serivce for driver failed.\r\n");
                break;
            }

            // Start Serivce.
            BOOL bRet = StartService(hService, NULL, NULL);
            if (!bRet)
            {
#ifdef DEBUG
                dwLine = __LINE__;
                bOutputErrMsg = TRUE;
#endif // DEBUG 
                csMessageInfo = _T("Load successful, but start filed.\r\n");
                break;
            }

            bLoadSuccessful = TRUE;
            MessageBox(_T("NT Driver load successful!"), _T("OK"), MB_OK);
        } while (FALSE);

#ifdef DEBUG
        if (bOutputErrMsg && 0 != dwLine)
        {
            dwError = GetLastError();
            GetErrorMessage(dwError, csErrorMessage);
            OutputDebugStringWithInfo(csErrorMessage, __FILET__, dwLine);
        }
#endif // DEBUG 

        // Close service handle.
        if (NULL != hService)
        {
            CloseServiceHandle(hService);
            hService = NULL;
        }

        if (!bLoadSuccessful)
        {
            if (csMessageInfo.IsEmpty())
            {
                csMessageInfo = _T("NT driver load filed.\r\n");
            }

            MessageBox(csMessageInfo, _T("ERROR"), MB_OK);
        }
    } //! if 'Load NT Driver' END
} //! OnBnClickedBtnLoaddriver() END 

//******************************************************************************
// Author:              Hoffman
// Create Time:         2019-01-26
// Last Time:           2019-01-26
// Logical Descrition:  
//      Close the SCManager handle.
//******************************************************************************
void CDriverLoaderDlg::OnDestroy()
{
    CDialogEx::OnDestroy();

    // Close SCManager handle.
    if (NULL != m_hSCManager)
    {
        CloseServiceHandle(m_hSCManager);
        m_hSCManager = NULL;
    }
} //! OnDestroy() END

//******************************************************************************
// Author:              Hoffman
// Create Time:         2019-01-26
// Last Time:           2019-02-18
// Logical Descrition:  
//      Deal with the event that unload driver button is clicked.
//      Open service, then delete it.
//      The message info is different, it accord with the different error 
//      occation. 
//******************************************************************************
void CDriverLoaderDlg::OnBnClickedBtnUnloaddriver()
{
#ifdef DEBUG
    DWORD dwError = -1;
    CString csErrorMessage;
    DWORD dwLine = 0;
    BOOL bOutputErrMsg = FALSE;
#endif // DEBUG

    CString csMessageInfo = _T("");

    // Unload NT Driver.
    if (DTTCI_NT == m_iCurrentSelectPage)
    {
        SC_HANDLE hService = NULL;
        BOOL bUnloadSuccessful = FALSE;

        do
        {
            // Get service name.
            CString csServiceName;
            m_pageNT.m_editServiceName.GetWindowText(csServiceName);

            // Check SCManager handle.
            if (NULL == m_hSCManager)
            {
                m_hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
                if (NULL == m_hSCManager)
                {
#ifdef DEBUG
                    dwLine = __LINE__;
                    bOutputErrMsg = TRUE;
#endif // DEBUG 
                    break;
                }
            }

            if (!GetDriverInfo())
            {
#ifdef DEBUG
                OutputDebugStringWithInfo(
                    _T("Get driver info failed.\r\n"),
                    __FILET__,
                    __LINE__
                );
#endif // DEBUG
                break;
            }

            if (!StopAndDeleteService())
            {
#ifdef DEBUG
                OutputDebugStringWithInfo(
                    _T("Stop and delete service failed.\r\n"),
                    __FILET__,
                    __LINE__
                );
#endif // DEBUG
                break;
            }


            bUnloadSuccessful = TRUE;
            MessageBox(_T("NT Driver unload successful!"), _T("OK"), MB_OK);
        } while (FALSE);

#ifdef DEBUG
        if (bOutputErrMsg && 0 != dwLine)
        {
            dwError = GetLastError();
            GetErrorMessage(dwError, csErrorMessage);
            OutputDebugStringWithInfo(csErrorMessage, __FILET__, dwLine);
        }
#endif // DEBUG 

        // Close service handle.
        if (NULL != hService)
        {
            CloseServiceHandle(hService);
            hService = NULL;
        }

        if (!bUnloadSuccessful)
        {
            if (csMessageInfo.IsEmpty())
            {
                csMessageInfo = _T("NT driver unload failed.\r\n");
            }

            MessageBox(csMessageInfo, _T("ERROR"), MB_OK);
        }
    } //! if 'Unload NT Driver' END 
} //! OnBnClickedBtnUnloaddriver() END

//******************************************************************************
// Author:              Hoffman
// Create Time:         2019-01-26
// Last Time:           2019-02-18
// Logical Descrition:  
//      Stop a serivce, then delete it.
//******************************************************************************
BOOL CDriverLoaderDlg::StopAndDeleteService()
{
#ifdef DEBUG
    DWORD dwError = -1;
    CString csErrorMessage;
    DWORD dwLine = 0;
    BOOL bOutputErrMsg = FALSE;
#endif // DEBUG

    BOOL bRet = FALSE;
    SERVICE_STATUS stServiceStatus = { 0 };
    SC_HANDLE hService = NULL;

    do
    {
        if (NULL == m_hSCManager)
        {
            break;
        }

        // Get serivce handle.
        hService = OpenService(m_hSCManager,
                               m_csServiceName,
                               SERVICE_ALL_ACCESS);
        if (NULL == hService)
        {
            DWORD dwErrorCode = GetLastError();
            if (ERROR_SERVICE_DOES_NOT_EXIST == dwErrorCode)
            {
                bRet = TRUE;
            }

            break;
        }

        if (!ControlService(hService, SERVICE_CONTROL_STOP, &stServiceStatus))
        {
#ifdef DEBUG
            dwLine = __LINE__;
            bOutputErrMsg = TRUE;
#endif // DEBUG 

            if (SERVICE_STOPPED != stServiceStatus.dwCurrentState)
            {
                break;
            }
        }

        if (!DeleteService(hService))
        {
#ifdef DEBUG
            dwLine = __LINE__;
            bOutputErrMsg = TRUE;
#endif // DEBUG 
            break;
        }

        bRet = TRUE;
    } while (FALSE);

#ifdef DEBUG
    if (bOutputErrMsg && 0 != dwLine)
    {
        dwError = GetLastError();
        GetErrorMessage(dwError, csErrorMessage);
        OutputDebugStringWithInfo(csErrorMessage, __FILET__, dwLine);
    }
#endif // DEBUG 

    // Close service handle.
    if (NULL != hService)
    {
        CloseServiceHandle(hService);
        hService = NULL;
    }

    return bRet;
} //! StopAndDeleteService() END

//******************************************************************************
// Author:              Hoffman
// Create Time:         2019-02-18
// Last Time:           2019-02-18
// Logical Description:  
//      Get driver info from dialog.
//******************************************************************************
BOOL CDriverLoaderDlg::GetDriverInfo()
{
    do
    {
        // Get service name.
        m_pageNT.m_editServiceName.GetWindowText(m_csServiceName);
        if (m_csServiceName.IsEmpty())
        {
#ifdef DEBUG
            OutputDebugStringWithInfo(
                _T("The service name is null.\r\n"),
                __FILET__,
                __LINE__
            );
#endif // DEBUG
            break;
        }

        // Get display name.
        m_pageNT.m_editDisplayName.GetWindowText(m_csDisplayName);
        if (m_csDisplayName.IsEmpty())
        {
#ifdef DEBUG
            OutputDebugStringWithInfo(
                _T("The display name is null.\r\n"),
                __FILET__,
                __LINE__
            );
#endif // DEBUG
            break;
        }

        // Get binary path.
        m_pageNT.m_editFilePath.GetWindowText(m_csBinaryPath);
        if (m_csDisplayName.IsEmpty())
        {
#ifdef DEBUG
            OutputDebugStringWithInfo(
                _T("The binary path is null.\r\n"),
                __FILET__,
                __LINE__
            );
#endif // DEBUG
            break;
        }

        // Get service type.
        m_iServiceType = m_pageNT.m_cmbServiceType.GetCurSel();

        // Get start type.
        m_iStartType = m_pageNT.m_cmbStartType.GetCurSel();

        // Get error control.
        m_iErrorControl = m_pageNT.m_cmbErrorControl.GetCurSel();

        return TRUE;
    } while (FALSE);

    return FALSE;
} //! GetDriverInfo();