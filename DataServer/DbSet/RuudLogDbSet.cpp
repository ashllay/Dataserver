#include "StdAfx.h"
#include "RuudLogDbSet.h"

CRuudLogDbSet::CRuudLogDbSet()
{
}

CRuudLogDbSet::~CRuudLogDbSet()
{
}

BOOL CRuudLogDbSet::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("CRuudLogDbSet ODBC Connect Fail");
	return 0;
}

int CRuudLogDbSet::setRuudTokenLog(char *AccoundID, char *Name, unsigned int dwRuudTotal, unsigned int dwRuudValue, char byFlag)
{
	int result; // eax
	CString QueryStr; // [esp+ECh] [ebp-20h]

	QueryStr.Format(
		"WZ_SET_RUUD_TOKEN_LOG '%s', '%s', %d, %d, %d ",
		AccoundID,
		Name,
		dwRuudTotal,
		dwRuudValue,
		byFlag);
	if (this->m_DBQuery.Exec(QueryStr))
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [CSPServerDBSet] setRuudTokenLog #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}