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
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass) == FALSE)
	{
		MsgBox("CBlockChatUserDbSet ODBC Connect Fail");
		return FALSE;
	}

	return TRUE;
}

BOOL CBlockChatUserDBSet::DSDB_SelectBlockChatUser(char* Name, LPSDHP_ANS_BLOCK_CHAT_USER_INFO lpSendMsg)
{
	CString QueryStr;
	int nCnt = 0;
	BYTE btSlotNum = 0;

	QueryStr.Format("WZ_ChattingBlockUserLoad '%s'", Name);

	if (m_DBQuery.Exec(QueryStr) == FALSE)
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [BlockChatUser] DSDB_SelectBlockChatUser #1 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	SQLRETURN sqlReturn = m_DBQuery.Fetch();

	while (sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
	{
		btSlotNum = m_DBQuery.GetInt("SlotNum");
		lpSendMsg->BlockCharList[btSlotNum].bIsUsed = true;
		lpSendMsg->BlockCharList[btSlotNum].btSlotNum = btSlotNum;
		m_DBQuery.GetStr("BlockUser", lpSendMsg->BlockCharList[btSlotNum].szCharName);
		lpSendMsg->BlockCharList[btSlotNum].szCharName[MAX_IDSTRING] = '\0';
		nCnt++;

		if (nCnt >= 20)
		{
			break;
		}
	}

	lpSendMsg->btUserCnt = nCnt;
	m_DBQuery.Clear();
	return TRUE;
}

BOOL CBlockChatUserDBSet::DSDB_AddBlockChatUser(LPSDHP_REQ_ADD_BLOCK_CHAT_USER_INFO lpRecv)
{
	CString qSql;
	qSql.Format("EXEC WZ_ChattingBlockUserInsert '%s', %d ,'%s'", lpRecv->szCharName, lpRecv->szBlockChar.btSlotNum, lpRecv->szBlockChar.szCharName);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [BlockChatUser] DSDB_AddBlockChatUser [%s] %s %d", lpRecv->szCharName, __FILE__, __LINE__);
		return FALSE;
	}

	m_DBQuery.Clear();
	return TRUE;
}

BOOL CBlockChatUserDBSet::DSDB_DelBlockChatUser(LPSDHP_REQ_DEL_BLOCK_CHAT_USER_INFO lpRecv)
{
	CString qSql;
	qSql.Format("EXEC WZ_ChattingBlockUserDel '%s' ,'%s'", lpRecv->szCharName, lpRecv->szBlockChar.szCharName);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [BlockChatUser] DSDB_DelBlockChatUser [%s] %s %d", lpRecv->szCharName, __FILE__, __LINE__);
		return FALSE;
	}

	m_DBQuery.Clear();
	return TRUE;
}