// ActiveMng.cpp: implementation of the CActiveMng class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dataserver.h"
#include "ActiveMng.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CActiveMng::CActiveMng()
{
	InitializeCriticalSection(&this->m_critSect);
	this->SetMode(AM_NONE);
	this->m_running = 0;
}

CActiveMng::~CActiveMng()
{
	DeleteCriticalSection(&this->m_critSect);
}

void CActiveMng::SetMode(DWORD mode)
{
	EnterCriticalSection(&this->m_critSect);

	this->m_dwStateMode = mode;
	this->m_dwTime = GetTickCount();

	LeaveCriticalSection(&this->m_critSect);
}

DWORD CActiveMng::GetMode()
{
	return this->m_dwStateMode;
}

void CActiveMng::CheckTime(DWORD chTime)
{
	if(this->m_dwStateMode == AM_STANDBY)
	{
		return;
	}

	if(GetTickCount() - this->m_dwTime > chTime)
	{
		this->m_dwStateMode = AM_STANDBY;
		LogAdd("StateMode Change %d", this->m_dwStateMode);
	}
}

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	CActiveMng* pThis = (CActiveMng *)lpParameter;

	EnterCriticalSection(&pThis->m_critSect);

	pThis->m_running = 1;

	LeaveCriticalSection(&pThis->m_critSect);

	while ( true )
	{
		EnterCriticalSection(&pThis->m_critSect);
		pThis->CheckTime(30000);
		LeaveCriticalSection(&pThis->m_critSect);
		Sleep(1000);
	}

	return FALSE;
}

void CActiveMng::StartThread()
{
	EnterCriticalSection(&this->m_critSect);

	this->m_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, this, 0, &this->m_threadId);

	LeaveCriticalSection(&this->m_critSect);
}

void CActiveMng::StopThread()
{
	EnterCriticalSection(&this->m_critSect);

	this->m_running = 0;

	if(this->m_thread != NULL)
	{
		int result = WaitForSingleObject(this->m_thread, 10000);

		if (result == PST_TCPIP_TELNET )
		{
			TerminateThread(this->m_thread, 0);
		}
		
		CloseHandle(this->m_thread);
		this->m_thread = 0;
	}

	LeaveCriticalSection(&this->m_critSect);
}