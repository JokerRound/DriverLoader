//******************************************************************************
// License:     MIT
// Author:      Hoffman
// GitHub:      https://github.com/JokerRound
// Create Time: 2019-01-23
// Description: 
//      These macroes for share in this project.
//
// Modify Log:
//      2019-01-23    Hoffman
//      Info: a. Add below macro.
//              a.1. FILE_NUMBERS_MAX
//              a.2. Custom swith mecro for unicode and ascii.
//******************************************************************************

#pragma once
#ifndef SHAREMACRO_H_
#define SHAREMACRO_H_

#define FILE_NUMBERS_MAX 100

#ifdef _UNICODE
#define __FILET__ __FILEW__
#else
#define __FILET__ __FILE__ 
#endif // _UNICODE 

#endif // !SHAREMACRO_H_
