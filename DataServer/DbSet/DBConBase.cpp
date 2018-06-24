// DBConBase.cpp: implementation of the CDBConBase class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\Dataserver.h"
#include "DBConBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDBConBase::CDBConBase()
{

}

CDBConBase::~CDBConBase()
{

}

BOOL CDBConBase::Connect(char* szConID, char* szConPass)
{
	if(m_DBQuery.Connect(3, szDbConnectDsn, szConID, szConPass) == FALSE)
	{
		MsgBox("%s DB Connect Fail", szDbConnectDsn);
		return FALSE;
	}

	return TRUE;
}