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
	//if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
	//	return 1;
	//MsgBox("CMineSystemDBSet ODBC Connect Fail");
	//return 0;
}

int CMineSystemDBSet::DSDB_QueryInsertUPTUserInfo(char *szCharName, unsigned __int16 wTwinkleType, int iCurrentStage)
{
	int result;
	CString qSql;
		
	int v8;

	v8 = 0;
	qSql.Format("exec WZ_MineSystem_Insert_UPTUserInfo '%s', %d, %d",szCharName,wTwinkleType,iCurrentStage);
	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		v8 = -1;
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		v8 = -1;
		
		result = 0;
	}
	return result;
}

//----- (00442790) --------------------------------------------------------
int CMineSystemDBSet::DSDB_QueryDeleteUPTUserInfo(char *szCharName)
{
	char *v2; // eax
	int result; // eax
	CString qSql; // [esp+ECh] [ebp-20h]
	int v6; // [esp+108h] [ebp-4h]

	v6 = 0;
	qSql.Format("exec WZ_MineSystem_Delete_UPTUserInfo '%s'",szCharName);

	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		v6 = -1;
		
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		v6 = -1;
		
		result = 0;
	}
	return result;
}

//----- (004428C0) --------------------------------------------------------
int CMineSystemDBSet::DSDB_QuerySelectUPTUserInfo(char *szCharName, SDHP_ANS_LOAD_MINESYSTEM_UPT_USERINFO *pMsgSend)
{
	char *v3; // eax
	int result; // eax
	CString qSql; // [esp+F8h] [ebp-20h]
	int v7; // [esp+114h] [ebp-4h]

	v7 = 0;
	qSql.Format("exec WZ_MineSystem_Select_UPTUserInfo '%s'",szCharName);
	if (this->m_DBQuery.Exec(qSql))
	{
		if (this->m_DBQuery.Fetch() == 100)
		{
			pMsgSend->byResult = 0;
			this->m_DBQuery.Clear();
			v7 = -1;
			
			result = 0;
		}
		else
		{
			this->m_DBQuery.GetStr("CharacterName", pMsgSend->szCharName);
			pMsgSend->wTwinkleType = this->m_DBQuery.GetInt(2);
			pMsgSend->iCurrentStage = this->m_DBQuery.GetInt(3);
			pMsgSend->byResult = 1;
			this->m_DBQuery.Clear();
			v7 = -1;
			
			result = 1;
		}
	}
	else
	{
		pMsgSend->byResult = -1;
		this->m_DBQuery.Clear();
		v7 = -1;
		
		result = 0;
	}
	return result;
}