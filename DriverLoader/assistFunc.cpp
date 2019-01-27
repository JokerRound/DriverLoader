//******************************************************************************
// License:     MIT
// Author:      Hoffman
// Create Time: 2018-10-29
// Description: 
//      The achieve of assist functions.
//
// Modify Log:
//      2018-10-29    Hoffman
//      Info: a. Add achieve of below functions.
//              a.1. OutputDebugStringWithInfo();
//              a.2. GetErrorMessage();
//              a.3. HexString2Decimal();
//              a.4. Byte2HexString();
//              a.5. Word2HexString();
//              a.6. Dword2HexString();
//******************************************************************************

#include "stdafx.h"
#include "assistFunc.h"

// To get finally info with file name, file line and info output,
// Then call OutputDebugString.
void OutputDebugStringWithInfo(const CString csOuput,
                               const CString csFileNmae,
                               DWORD dwFileLine)
{
    CString csFinallyInfo;
    csFinallyInfo.Format(_T("%s (%d): %s"),
                         csFileNmae.GetString(),
                         dwFileLine,
                         csOuput.GetString());

    OutputDebugString(csFinallyInfo);
} //! OutputDebugStringWithInfo END


// 
void GetErrorMessage(DWORD dwError, CString &csMessage)
{
    // Get default system locale.
    DWORD dwSystemLocal = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);

    // Buffer that gets the error message.
    HLOCAL hLocal = NULL;

    // Get description of error meesage.
    BOOL bRet = FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dwError,
        dwSystemLocal,
        (LPTSTR)&hLocal,
        0,
        NULL);
    if (!bRet)
    {
        // Failed.
        // Try to get message from netmsg.dll.
        HMODULE hDll = LoadLibraryEx(_T("netmsg.dll"),
                                     NULL,
                                     DONT_RESOLVE_DLL_REFERENCES);
        if (NULL != hDll)
        {
            bRet = 
                FormatMessage(
                    FORMAT_MESSAGE_ALLOCATE_BUFFER
                    | FORMAT_MESSAGE_FROM_HMODULE 
                    | FORMAT_MESSAGE_IGNORE_INSERTS,
                    hDll,
                    dwError,
                    dwSystemLocal,
                    (LPTSTR)&hLocal,
                    0,
                    NULL
                );

            FreeLibrary(hDll);
        }
    }

    if (bRet && (NULL != hLocal))
    {
        csMessage = (LPTSTR)LocalLock(hLocal);
    }
    else
    {
#ifdef DEBUG
        OutputDebugStringWithInfo(_T("Can't find the error message."), 
                                  __FILET__, 
                                  __LINE__);
#endif // DEBUG
    }

    LocalFree(hLocal);
} //! GetErrorMessage END

// Hex string to qword
QWORD HexString2Decimal(const CString &ref_csTarget)
{
    QWORD aliNum[16] = { 0 };
    QWORD liBaseNum = 1;
    QWORD liResult = 0;

    for (int cntI = (int)ref_csTarget.GetLength() - 1;
         cntI >= 0;
         --cntI)
    {
        if (ref_csTarget[cntI] >= '0' && ref_csTarget[cntI] <= '9')
        {
            aliNum[cntI] = ref_csTarget[cntI] - '0';
        }
        else if (ref_csTarget[cntI] >= 'a' && ref_csTarget[cntI] <= 'f')
        {
            aliNum[cntI] = ref_csTarget[cntI] - 'a' + 10;
        }
        else if (ref_csTarget[cntI] >= 'A' && ref_csTarget[cntI] <= 'F')
        {
            aliNum[cntI] = ref_csTarget[cntI] - 'A' + 10;
        }
        else
        {
            aliNum[cntI] = 0;
        }

        liResult = liResult + aliNum[cntI] * liBaseNum;
        liBaseNum *= 16;
    }

    return liResult;
} //! HexString2Decimal END

std::basic_string<TCHAR> Byte2HexString(const BYTE bytTarget)
{
    TCHAR szByte[2 + 1] = { 0 };
    _stprintf_s(szByte,
                sizeof(szByte) / sizeof(TCHAR),
                _T("%02X"),
                bytTarget);
    return szByte;
}

std::basic_string<TCHAR> Word2HexString(const WORD wTarget)
{
    TCHAR szWord[4 + 1] = { 0 };
    _stprintf_s(szWord,
                sizeof(szWord) / sizeof(TCHAR),
                _T("%04X"),
                wTarget);
    return szWord;
}

std::basic_string<TCHAR> Dword2HexString(const DWORD dwTarget)
{
    TCHAR szDword[8 + 1] = { 0 };
    _stprintf_s(szDword,
                sizeof(szDword) / sizeof(TCHAR),
                _T("%08X"),
                dwTarget);
    return szDword;
} //! Dword2HexString() END 