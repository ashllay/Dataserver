#include "StdAfx.h"
#include "BlockChatUserDBSet.h"

CBlockChatUserDBSet::CBlockChatUserDBSet()
{
}

CBlockChatUserDBSet::~CBlockChatUserDBSet()
{
}

BOOL CBlockChatUserDBSet::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("CBlockChatUserDbSet ODBC Connect Fail");
	return 0;
}


//----- (0042CA60) --------------------------------------------------------
int CBlockChatUserDBSet::DSDB_SelectBlockChatUser(char *Name, SDHP_ANS_BLOCK_CHAT_USER_INFO *lpSendMsg)
{
	char *v3; // eax
	int result; // eax
	int v5; // [esp+14h] [ebp-11Ch]
	__int16 sqlReturn; // [esp+ECh] [ebp-44h]
	char btSlotNum; // [esp+FBh] [ebp-35h]
	int nCnt; // [esp+104h] [ebp-2Ch]
	CString QueryStr;
	int v11; // [esp+12Ch] [ebp-4h]

	v11 = 0;
	nCnt = 0;
	btSlotNum = 0;
	QueryStr.Format("WZ_ChattingBlockUserLoad '%s'", Name);
	if (this->m_DBQuery.Exec(QueryStr))
	{
		for (sqlReturn = this->m_DBQuery.Fetch(); sqlReturn != SQL_NO_DATA; sqlReturn = this->m_DBQuery.Fetch())
		{
			if (sqlReturn == -1)
				break;
			btSlotNum = this->m_DBQuery.GetInt("SlotNum");
			lpSendMsg->BlockCharList[btSlotNum].bIsUsed = 1;
			lpSendMsg->BlockCharList[btSlotNum].btSlotNum = btSlotNum;
			this->m_DBQuery.GetStr("BlockUser", lpSendMsg->BlockCharList[btSlotNum].szCharName);
			lpSendMsg->BlockCharList[btSlotNum].szCharName[10] = 0;
			if (++nCnt >= 20)
				break;
		}
		lpSendMsg->btUserCnt = nCnt;
		this->m_DBQuery.Clear();
		v11 = -1;
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [BlockChatUser] DSDB_SelectBlockChatUser #1 %s %d",__FILE__,__LINE__);
		v5 = 0;
		v11 = -1;
		result = v5;
	}
	return result;
}

//----- (0042CC80) --------------------------------------------------------
int CBlockChatUserDBSet::DSDB_AddBlockChatUser(SDHP_REQ_ADD_BLOCK_CHAT_USER_INFO *lpRecv)
{
	char *v2; // eax
	int result; // eax
	int v4; // [esp+14h] [ebp-F8h]
	CString qSql; // [esp+ECh] [ebp-20h]
	int v7;

	v7 = 0;
	qSql.Format("EXEC WZ_ChattingBlockUserInsert '%s', %d ,'%s'",lpRecv->szCharName,lpRecv->szBlockChar.btSlotNum,lpRecv->szBlockChar.szCharName);

	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		v7 = -1;
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [BlockChatUser] DSDB_AddBlockChatUser [%s] %s %d",
			lpRecv->szCharName, __FILE__, __LINE__);
		v7 = -1;
		result = 0;
	}
	return result;
}



int CBlockChatUserDBSet::DSDB_DelBlockChatUser(SDHP_REQ_DEL_BLOCK_CHAT_USER_INFO *lpRecv)
{
	char *v2;
	int result;
	int v4;
	CString qSql;
	int v7;

	qSql.Format("EXEC WZ_ChattingBlockUserDel '%s' ,'%s'",
		lpRecv->szCharName,
		lpRecv->szBlockChar.szCharName);
	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		v7 = -1;
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [BlockChatUser] DSDB_DelBlockChatUser [%s] %s %d",
			lpRecv->szCharName, __FILE__, __LINE__);
		v7 = -1;
		result = 0;
	}
	return result;
}