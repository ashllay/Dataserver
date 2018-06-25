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
bool CBlockChatUserDBSet::DSDB_SelectBlockChatUser(char *Name, SDHP_ANS_BLOCK_CHAT_USER_INFO *lpSendMsg)
{
	int result;
	__int16 sqlReturn;
	char btSlotNum;
	int nCnt;
	CString QueryStr;

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
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [BlockChatUser] DSDB_SelectBlockChatUser #1 %s %d",__FILE__,__LINE__);
		result = 0;
	}
	return result;
}



int CBlockChatUserDBSet::DSDB_AddBlockChatUser(SDHP_REQ_ADD_BLOCK_CHAT_USER_INFO *lpRecv)
{
	int result;
	CString qSql;

	qSql.Format("EXEC WZ_ChattingBlockUserInsert '%s', %d ,'%s'",lpRecv->szCharName,lpRecv->szBlockChar.btSlotNum,lpRecv->szBlockChar.szCharName);

	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [BlockChatUser] DSDB_AddBlockChatUser [%s] %s %d",lpRecv->szCharName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}



int CBlockChatUserDBSet::DSDB_DelBlockChatUser(SDHP_REQ_DEL_BLOCK_CHAT_USER_INFO *lpRecv)
{
	int result;
	CString qSql;

	qSql.Format("EXEC WZ_ChattingBlockUserDel '%s' ,'%s'",
		lpRecv->szCharName,lpRecv->szBlockChar.szCharName);
	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [BlockChatUser] DSDB_DelBlockChatUser [%s] %s %d",
			lpRecv->szCharName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}