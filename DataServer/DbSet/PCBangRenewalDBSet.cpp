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

//----- (00445840) --------------------------------------------------------
int CPCBangRenewalDBSet::DSDB_GetPCBangPlayTimeInfo(char *szAccountID, char *btCompleteGrade, char *btRecvGrade, unsigned int *dwPCBangPlayTime)
{
	int result; // eax
	__int16 sqlReturn; // [esp+F8h] [ebp-2Ch]
	CString QueryStr; // [esp+104h] [ebp-20h]
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
// 5CDE94: using guessed type int `CPCBangRenewalDBSet::DSDB_GetPCBangPlayTimeInfo'::`2'::__LINE__Var;

//----- (00445A60) --------------------------------------------------------
int CPCBangRenewalDBSet::DSDB_SetPCBangPlayTimeInfo(char *szAccountID, char btCompleteGrade, char btRecvGrade, unsigned int dwPCBangPlayTime)
{
	int result; // eax
	CString QueryStr; // [esp+ECh] [ebp-20h]


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