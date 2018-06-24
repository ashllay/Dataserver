#include "StdAfx.h"
#include "RestoreItemDBSet.h"

CRestoreItemDBSet::CRestoreItemDBSet()
{
}

CRestoreItemDBSet::~CRestoreItemDBSet()
{
}

BOOL CRestoreItemDBSet::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("CRestoreItemDBSet ODBC Connect Fail");
	return 0;
}

//----- (0044BCC0) --------------------------------------------------------
int CRestoreItemDBSet::DSDB_SelectRestoreItem(char *AccountID, char *Name, int userIndex, _SDHP_ANS_RESTORE_ITEM_LIST *lpSendMsg)
{
	int result;
	int nRet;
	CString QueryStr;
	
	QueryStr.Format("EXEC WZ_GetLoadRestoreInventory '%s', '%s'",AccountID,Name);
	lpSendMsg->userIndex = userIndex;

	nRet = this->m_DBQuery.ReadBlob(QueryStr, lpSendMsg->dbRestoreItemData);
	if (nRet == -1)
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [RestoreItem] - SelectRestoreItem #1 [%s][%s] %s %d",AccountID,Name,__FILE__, __LINE__);
		lpSendMsg->result = 1;
		result = 0;
	}
	else
	{
		this->m_DBQuery.Clear();
		QueryStr.Format("SELECT DbVersion FROM T_RestoreItem_Inventory WHERE AccountID='%s' AND [Name]='%s'",AccountID,Name);
		if (this->m_DBQuery.Exec(QueryStr))
		{
			if (this->m_DBQuery.Fetch() == 100)
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [RestoreItem] - SelectRestoreItem #5 [%s][%s] %s %d",AccountID,Name,__FILE__, __LINE__);lpSendMsg->result = 5;
				result = 0;
			}
			else
			{
				lpSendMsg->dbVersion = this->m_DBQuery.GetInt(1);
				lpSendMsg->result = 0;
				this->m_DBQuery.Clear();
				result = 1;
			}
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [RestoreItem] - SelectRestoreItem #4 [%s][%s] %s %d",AccountID,Name,__FILE__, __LINE__);
			lpSendMsg->result = 4;
			result = 0;
		}
	}
	return result;
}

//----- (0044BF70) --------------------------------------------------------
__int64 CRestoreItemDBSet::DSDB_UpdateRestoreItem(char *AccountID, char *Name, char *RestoreInventoryBuf)
{
	CString QueryStr;

	QueryStr.Format("EXEC dbo.WZ_SetSaveRestoreInventory '%s', '%s', ?",AccountID,Name);
	this->m_DBQuery.WriteBlob(QueryStr, RestoreInventoryBuf, 150);
	this->m_DBQuery.Clear();
	return TRUE;
}