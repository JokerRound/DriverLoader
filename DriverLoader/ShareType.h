//******************************************************************************
// License:     MIT
// Author:      Hoffman
// GitHub:      https://github.com/JokerRound
// Create Time: 2019-01-23
// Description: 
//      The type for share in this project.
//
// Modify Log:
//      2019-01-23    Hoffman
//      Info: a. Add below type.
//              a.1. enum tagDriverTypeTabControlItem;
//              a.2. enum tagServiceTypeItem;
//              a.3.
//******************************************************************************

#pragma once
#ifndef SHARETYPE_H_
#define SHARETYPE_H_

typedef enum tagDriverTypeTabControlItem
{
    DTTCI_NT = 0,

    TOTAL_DTTCI_NUMBER
} DRIVERTYPETABCONTROLITEM, *PDRIVERTYPETABCONTROLITEM;

typedef enum tagServiceTypeItem
{
    SERVTI_KERNEL = 0,
    SERVTI_FILE_SYSTEM,

    TOTAL_SERVTI_NUMBER
} SERVICETYPEITEM, *PSERVICETYPEITEM;

typedef enum tagErrorControlItem
{
    ECI_IGNORE = 0,
    ECI_NORMAL,
    ECI_SEVERE,
    ECI_CRITICAL,

    TOTAL_ECI_NUMBER
} ERRORCONTROLITEM, *PERRORCONTROLITEM;

typedef enum tagStartTypeItem
{
    STARTCI_BOOT = 0,
    STARTCI_SYSTEM,
    STARTCI_AUTO,
    STARTCI_DEMAND,
    STARTCI_DISABLE,

    TOTAL_STARTCI_NUMBER,
} STARTTYPEITEM, *PSTARTTYPEITEM;

#endif // !SHARETYPE_H_
