//******************************************************************************
// License:     MIT
// Author:      Hoffman
// GitHub:      https://github.com/JokerRound
// Create Time: 2019-01-24
// Description: 
//      The achieve file of class CProppageNT.
//
// Modify Log:
//      2019-01-26    Hoffman
//      Info: a. Add below member methods.
//              a.1. OnBnClickedBtnSearchfile();
//              a.1. OnInitDialog();
//******************************************************************************


#include "stdafx.h"
#include "DriverLoader.h"
#include "ProppageNT.h"
#include "afxdialogex.h"
#include "ShareMacro.h"


// CProppageNT 对话框

IMPLEMENT_DYNAMIC(CProppageNT, CDialogEx)

CProppageNT::CProppageNT(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROPPAGE_NTDRIVER, pParent)
{

}

CProppageNT::~CProppageNT()
{
}

void CProppageNT::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_DRIVERFILEPATH, m_editFilePath);
    DDX_Control(pDX, IDC_EDIT_SERVICE_NAME, m_editServiceName);
    DDX_Control(pDX, IDC_EDIT_DISPLAYNAME, m_editDisplayName);
    DDX_Control(pDX, IDC_COMBO_SERVICETYPE, m_cmbServiceType);
    DDX_Control(pDX, IDC_COMBO_STARTMODE, m_cmbStartType);
    DDX_Control(pDX, IDC_COMBO_ERRORCONTROL, m_cmbErrorControl);
}


BEGIN_MESSAGE_MAP(CProppageNT, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_SEARCHFILE, &CProppageNT::OnBnClickedBtnSearchfile)
END_MESSAGE_MAP()


//******************************************************************************
// Author:              Hoffman
// Create Time:         2019-01-26
// Last Time:           2019-01-26
// Logical Descrition:  
//      Popup a search file dialog.
//******************************************************************************
void CProppageNT::OnBnClickedBtnSearchfile()
{
    CFileDialog dlgSearchFile(TRUE);
    CString csFilePath;

    // Set buffer.
    const int kcntBuffSize = (FILE_NUMBERS_MAX * (MAX_PATH + 1)) + 1;
    dlgSearchFile.GetOFN().lpstrFile =
        csFilePath.GetBufferSetLength(kcntBuffSize);
    dlgSearchFile.GetOFN().nMaxFile = FILE_NUMBERS_MAX;

    // Popup the page.
    DWORD dwRet = dlgSearchFile.DoModal();
    csFilePath.ReleaseBuffer();

    if (dwRet == IDOK)
    {
        m_editFilePath.SetWindowText(csFilePath);

        CPath pathFileName = csFilePath;
        pathFileName.StripPath();
        pathFileName.RemoveExtension();
        
        m_editServiceName.SetWindowText(pathFileName.m_strPath);
        m_editDisplayName.SetWindowText(pathFileName.m_strPath);

        m_cmbErrorControl.SetCurSel(ECI_NORMAL);
        m_cmbServiceType.SetCurSel(SERVTI_KERNEL);
        m_cmbStartType.SetCurSel(STARTCI_DEMAND);
    }
} //! OnBnClickedBtnSearchfile() END

//******************************************************************************
// Author:              Hoffman
// Create Time:         2019-01-26
// Last Time:           2019-01-26
// Logical Descrition:  
//      Add initialize for combo box control.
//******************************************************************************
BOOL CProppageNT::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    for (size_t cntI = 0; cntI < TOTAL_ECI_NUMBER; cntI++)
    {
        m_cmbErrorControl.AddString(m_acsErrorControl[cntI]);
    }

    for (size_t cntI = 0; cntI < TOTAL_SERVTI_NUMBER; cntI++)
    {
        m_cmbServiceType.AddString(m_acsServiceType[cntI]);
    }

    for (size_t cntI = 0; cntI < TOTAL_STARTCI_NUMBER; cntI++)
    {
        m_cmbStartType.AddString(m_acsStartType[cntI]);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // 异常: OCX 属性页应返回 FALSE
} //! m_acsServiceType() END
