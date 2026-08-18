#include "StdAfx.h"
#include "PCBangRenewalDBSet.h"

CPCBangRenewalDBSet::CPCBangRenewalDBSet()
{
}

CPCBangRenewalDBSet::~CPCBangRenewalDBSet()
{
}

BOOL CPCBangRenewalDBSet::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("PCBangRenewalDBSet ODBC Connect Fail");
	return 0;
}

int CPCBangRenewalDBSet::DSDB_GetPCBangPlayTimeInfo(char *szAccountID, char *btCompleteGrade, char *btRecvGrade, unsigned int *dwPCBangPlayTime)
{
	int result;
	__int16 sqlReturn;
	CString QueryStr;
	QueryStr.Format("WZ_PCBangEventPlayTimeLoad '%s'",szAccountID);
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != SQL_NO_DATA && sqlReturn != -1)
		{
			*btCompleteGrade = this->m_DBQuery.GetInt(1);
			*btRecvGrade = this->m_DBQuery.GetInt(2);
			*dwPCBangPlayTime = this->m_DBQuery.GetInt(3);
			this->m_DBQuery.Clear();
			result = 1;
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD(
				"error-L3 : [CPCBangRenewalDBSet] DSDB_GetPCBangPlayTimeInfo #2 %d %s %d",
				sqlReturn, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD(
			"error-L3 : [CPCBangRenewalDBSet] DSDB_GetPCBangPlayTimeInfo #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}

int CPCBangRenewalDBSet::DSDB_SetPCBangPlayTimeInfo(char *szAccountID, char btCompleteGrade, char btRecvGrade, unsigned int dwPCBangPlayTime)
{
	int result;
	CString QueryStr;

	QueryStr.Format(
		"WZ_PCBangEventPlayTimeSave '%s', %d, %d, %d",
		szAccountID,
		btCompleteGrade,
		btRecvGrade,
		dwPCBangPlayTime);
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		this->m_DBQuery.Clear();
		
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD(
			"error-L3 : [CPCBangRenewalDBSet] DSDB_SetPCBangPlayTimeInfo #1 %s %d", __FILE__, __LINE__);
		
		result = 0;
	}
	return result;
}