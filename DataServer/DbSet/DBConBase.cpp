#include "stdafx.h"
#include "..\Dataserver.h"
#include "DBConBase.h"

CDBConBase::CDBConBase()
{
}

CDBConBase::~CDBConBase()
{
}

BOOL CDBConBase::Connect(char* szConID, char* szConPass)
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szConID, szConPass) == FALSE)
	{
		MsgBox("%s DB Connect Fail", szDbConnectDsn);
		return FALSE;
	}

	return TRUE;
}