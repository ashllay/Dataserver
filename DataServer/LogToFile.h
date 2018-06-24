// LogToFile.h: interface for the CLogToFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGTOFILE_H__971EB894_9D72_4918_8637_EDD0178FC8CC__INCLUDED_)
#define AFX_LOGTOFILE_H__971EB894_9D72_4918_8637_EDD0178FC8CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLogToFile  
{
public:
	CLogToFile(LPSTR LogFileName, LPSTR LogDirectoryName, BOOL bWithDate);
	~CLogToFile();

	void __cdecl Output(LPSTR fmt, ...);
public:
	FILE* m_fLogFile;
	char m_szLogFileName[260];
	char m_szLogDirectoryName[260];
	char m_cBUFFER[65536];
	int m_bWithDate;
	CRITICAL_SECTION m_critLogToFile;
};

#endif // !defined(AFX_LOGTOFILE_H__971EB894_9D72_4918_8637_EDD0178FC8CC__INCLUDED_)
