//******************************************************************************
// License:     MIT
// Author:      Hoffman
// GitHub:      https://github.com/JokerRound
// Create Time: 2018-10-29
// Description: 
//      The declare of assist functions.
//
// Modify Log:
//      2018-10-29    Hoffman
//      Info: a. Add below functions.
//              a.1. Byte2HexString();
//              a.2. Word2HexString();
//              a.3. Dword2HexString();
//******************************************************************************

#pragma once
#ifndef ASSISTFUNC_H_
#define ASSISTFUNC_H_
#include <string>
#include "ShareMacro.h"

void OutputDebugStringWithInfo(_In_ const CString csOuput,
                               _In_ const CString csFileNmae,
                               _In_ DWORD dwFileLine);


void GetErrorMessage(_In_ DWORD dwError,
                     _In_ CString &ref_csMessage);


std::basic_string<TCHAR> Byte2HexString(_In_ const BYTE bytTarget);
std::basic_string<TCHAR> Word2HexString(_In_ const WORD wTarget);
std::basic_string<TCHAR> Dword2HexString(_In_ const DWORD dwTarget);

#endif // !ASSISTFUNC_H_
