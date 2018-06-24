#include "StdAfx.h"
#include "SPServerDBSet.h"

CSPServerDBSet::CSPServerDBSet()
{
}

CSPServerDBSet::~CSPServerDBSet()
{
}

BOOL CSPServerDBSet::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("CSPServerDBSet ODBC Connect Fail");
	return 0;
}

int CSPServerDBSet::getSPServerPlayTime(char *AccoundID, unsigned int *dwPlayTimeNormal, unsigned int *dwPlayTimePCRoom, unsigned int *dwCloseDateTime)
{
	int result;
	char v8;
	__int16 sqlReturn;
	CString QueryStr;

	memset(&v8, 0xCCu, 0x108u);

	QueryStr.Format("WZ_GET_SPSERVER_PLAY_TIME '%s'",AccoundID);

	if (this->m_DBQuery.Exec(QueryStr))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != 100 && sqlReturn != -1)
		{
			*dwPlayTimeNormal = this->m_DBQuery.GetInt(1);
			*dwPlayTimePCRoom = this->m_DBQuery.GetInt( 2);
			*dwCloseDateTime = this->m_DBQuery.GetInt( 3);
			this->m_DBQuery.Clear();
			result = 1;
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [CSPServerDBSet] getSPServerPlayTime #2 %d %s %d",sqlReturn, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [CSPServerDBSet] getSPServerPlayTime #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


int CSPServerDBSet::setSPServerPlayTime(char *AccoundID, unsigned int dwPlayTimeNormal, unsigned int dwPlayTimePCRoom, unsigned int dwCloseDateTime)
{
	int result;
	char v8; 
	CString QueryStr;

	memset(&v8, 0xCCu, 0xF0u);

	QueryStr.Format("WZ_SET_SPSERVER_PLAY_TIME '%s', %d, %d, %d ",
		AccoundID,
		dwPlayTimeNormal,
		dwPlayTimePCRoom,
		dwCloseDateTime);

	if (this->m_DBQuery.Exec(QueryStr))
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [CSPServerDBSet] setSPServerPlayTime #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}