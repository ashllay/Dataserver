#include "StdAfx.h"
#include "MineSystemDBSet.h"

CMineSystemDBSet::CMineSystemDBSet()
{
}

CMineSystemDBSet::~CMineSystemDBSet()
{
}

BOOL CMineSystemDBSet::Connect()
{
	return this->CDBConBase::Connect(szDbConnectID, szDbConnectPass);
}

int CMineSystemDBSet::DSDB_QueryInsertUPTUserInfo(char *szCharName, unsigned __int16 wTwinkleType, int iCurrentStage)
{
	int result;
	CString qSql;

	qSql.Format("exec WZ_MineSystem_Insert_UPTUserInfo '%s', %d, %d",szCharName,wTwinkleType,iCurrentStage);
	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		result = 0;
	}
	return result;
}


int CMineSystemDBSet::DSDB_QueryDeleteUPTUserInfo(char *szCharName)
{
	int result;
	CString qSql;

	qSql.Format("exec WZ_MineSystem_Delete_UPTUserInfo '%s'",szCharName);

	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		result = 0;
	}
	return result;
}


int CMineSystemDBSet::DSDB_QuerySelectUPTUserInfo(char *szCharName, SDHP_ANS_LOAD_MINESYSTEM_UPT_USERINFO *pMsgSend)
{
	int result; 
	CString qSql; 

	qSql.Format("exec WZ_MineSystem_Select_UPTUserInfo '%s'",szCharName);
	if (this->m_DBQuery.Exec(qSql))
	{
		if (this->m_DBQuery.Fetch() == SQL_NO_DATA)
		{
			pMsgSend->byResult = 0;
			this->m_DBQuery.Clear();
			result = 0;
		}
		else
		{
			this->m_DBQuery.GetStr("CharacterName", pMsgSend->szCharName);
			pMsgSend->wTwinkleType = this->m_DBQuery.GetInt(2);
			pMsgSend->iCurrentStage = this->m_DBQuery.GetInt(3);
			pMsgSend->byResult = 1;
			this->m_DBQuery.Clear();
			result = 1;
		}
	}
	else
	{
		pMsgSend->byResult = -1;
		this->m_DBQuery.Clear();
		result = 0;
	}
	return result;
}