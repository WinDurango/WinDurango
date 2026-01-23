//Here lies some structs used in some of the Kernelx
//functions. All the code is based on XWine1's SlimEra
//Repo (https://github.com/XWine1/SlimEra). All credits
//to XWine1 and DaZombieKiller.
#pragma once
#include <Windows.h>

typedef struct _SYSTEMOSVERSIONINFO
{
    BYTE MajorVersion;
    BYTE MinorVersion;
    WORD BuildNumber;
    WORD Revision;
} SYSTEMOSVERSIONINFO, * PSYSTEMOSVERSIONINFO, * LPSYSTEMOSVERSIONINFO;

typedef enum _CONSOLE_TYPE
{
    CONSOLE_TYPE_UNKNOWN,
    CONSOLE_TYPE_XBOX_ONE,
    CONSOLE_TYPE_XBOX_ONE_S,
    CONSOLE_TYPE_XBOX_ONE_X,
    CONSOLE_TYPE_XBOX_ONE_X_DEVKIT,
} CONSOLE_TYPE, * PCONSOLE_TYPE, * LPCONSOLE_TYPE;

typedef struct _PROCESSOR_SCHEDULING_STATISTICS
{
	ULONGLONG RunningTime;
	ULONGLONG IdleTime;
	ULONGLONG GlobalTime;
} PROCESSOR_SCHEDULING_STATISTICS, * PPROCESSOR_SCHEDULING_STATISTICS, * LPPROCESSOR_SCHEDULING_STATISTICS;

typedef struct _PROCESSOR_SCHEDULING_STATISTICS
{
    ULONGLONG RunningTime;
    ULONGLONG IdleTime;
    ULONGLONG GlobalTime;
} PROCESSOR_SCHEDULING_STATISTICS, * PPROCESSOR_SCHEDULING_STATISTICS, * LPPROCESSOR_SCHEDULING_STATISTICS;