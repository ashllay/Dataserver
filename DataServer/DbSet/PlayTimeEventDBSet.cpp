#include "StdAfx.h"
#include "PlayTimeEventDBSet.h"

CPlayTimeEventDBSet::CPlayTimeEventDBSet()
{
}

CPlayTimeEventDBSet::~CPlayTimeEventDBSet()
{
}

BOOL CPlayTimeEventDBSet::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("CPlayTimeEventDBSet ODBC Connect Fail");
	return 0;
}

int CPlayTimeEventDBSet::getPlayTimeEventInfo(char *szAccountID, char *btGrade, unsigned int *dwPCBangPlayTime)
{
	int result;
	__int16 sqlReturn;
	CString QueryStr;
	QueryStr.Format("WZ_PlayTimeEventLoad '%s'",szAccountID);

	if (this->m_DBQuery.Exec(QueryStr))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != 100 && sqlReturn != -1)
		{
			*btGrade = this->m_DBQuery.GetInt(1);
			*dwPCBangPlayTime = this->m_DBQuery.GetInt( 2);
			this->m_DBQuery.Clear();
			result = 1;
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [CPlayTimeEventDBSet] getPlayTimeEventInfo #2 %d %s %d",sqlReturn, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [CPlayTimeEventDBSet] getPlayTimeEventInfo #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


int CPlayTimeEventDBSet::setPlayTimeEventInfo(char *szAccountID, char btGrade, unsigned int dwPCBangPlayTime)
{
	int result;
	CString QueryStr;

	QueryStr.Format("WZ_PlayTimeEventSave '%s', %d, %d",szAccountID,btGrade,dwPCBangPlayTime);
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		this->m_DBQuery.Clear();		
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [CPlayTimeEventDBSet] setPlayTimeEventInfo #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}