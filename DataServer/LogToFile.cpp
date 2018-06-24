// LogToFile.cpp: implementation of the CLogToFile class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dataserver.h"
#include "LogToFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogToFile::CLogToFile(LPSTR LogFileName, LPSTR LogDirectoryName, BOOL bWithDate)
{
	if (strcmp(LogFileName, "") == 0)
	{
		strcpy(this->m_szLogFileName , "LOGDATA");
	}
	else
	{
		strcpy(this->m_szLogFileName , LogFileName);
	}
	
	if (!strcmp(LogDirectoryName, ""))
	{
		strcpy(this->m_szLogDirectoryName , "LOG");
	}
	else
	{
		strcpy(this->m_szLogDirectoryName  , LogDirectoryName);
	}
	
	this->m_bWithDate  = bWithDate;	

	CreateDirectory(LogDirectoryName, NULL);

	InitializeCriticalSection(&this->m_critLogToFile );
}

CLogToFile::~CLogToFile()
{
	DeleteCriticalSection(&this->m_critLogToFile );
}

void __cdecl CLogToFile::Output( LPSTR fmt, ...)
{
	va_list argptr;
	int iChrWritten;
	char szLogFileName[260];

	SYSTEMTIME strSystime;
	
	EnterCriticalSection(&this->m_critLogToFile );

	va_start(argptr, fmt);
	iChrWritten=vsprintf(this->m_cBUFFER , fmt, argptr);
	va_end(argptr);

	GetLocalTime(&strSystime);

	wsprintf(szLogFileName, "%s\\%s %04d-%02d-%02d.txt",
		this->m_szLogDirectoryName, this->m_szLogFileName, 
		strSystime.wYear, strSystime.wMonth, strSystime.wDay);

	if ( (this->m_fLogFile = fopen(szLogFileName, "a+"))==0)
	{
		LeaveCriticalSection(&this->m_critLogToFile ); //wz fix :)
		return;
	}

	if (this->m_bWithDate ==0)
	{
		fprintf(this->m_fLogFile , "%s\n", this->m_cBUFFER);
	}
	else
	{
		fprintf(this->m_fLogFile , "%d:%d:%d  %s\n", 
			strSystime.wHour, strSystime.wMinute, 
			strSystime.wSecond, this->m_cBUFFER);
	}

	fclose(this->m_fLogFile );

	LeaveCriticalSection(&this->m_critLogToFile );
}