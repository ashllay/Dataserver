#include "StdAfx.h"
#include "MuunSystemDBSet.h"

CMuunSystemDBSet::CMuunSystemDBSet()
{
}

CMuunSystemDBSet::~CMuunSystemDBSet()
{
}

BOOL CMuunSystemDBSet::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("CMuunSystemDBSet ODBC Connect Fail");
	return 0;
}

BOOL CMuunSystemDBSet::LoadMuunInvenItem(char *Name, BYTE *ItemBuf, char *AccountId, int *SubEquip, int *DbVersion)
{
	int result;
	CString qSql; 
	qSql.Format("EXEC WZ_GetLoadMuunInventory '%s', '%s'",AccountId,Name);
	
	if (this->m_DBQuery.ReadBlob(qSql, ItemBuf) == -1)
	{
		this->m_DBQuery.Clear();
		result = 0;
	}
	else
	{
		qSql.Format("EXEC WZ_GetMuunSubEquip '%s', '%s'",AccountId,Name);
		if (this->m_DBQuery.Exec(qSql))
		{
			if (this->m_DBQuery.Fetch() == 100)
			{
				this->m_DBQuery.Clear();
				result = 0;
			}
			else
			{
				*DbVersion = this->m_DBQuery.GetInt(1);
				*SubEquip = this->m_DBQuery.GetInt(2);
				this->m_DBQuery.Clear();
				result = 1;
			}
		}
		else
		{
			this->m_DBQuery.Clear();
			result = 0;
		}
	}
	return result;
}


__int64 CMuunSystemDBSet::SaveMuunInvenItem(char *Name, BYTE *ItemBuf, char *AccountId)
{

	CString qSql; // [esp+E0h] [ebp-20h]

	qSql.Format("EXEC WZ_SetSaveMuunInventory '%s', '%s', ?",AccountId,Name);
	this->m_DBQuery.WriteBlob(qSql, ItemBuf, 1632);
	this->m_DBQuery.Clear();
	return TRUE;
}


BOOL CMuunSystemDBSet::MuunInvenSubEquipOpen(char *AccountId, char *Name)
{
	char result;
	CString qSql;

	qSql.Format("EXEC WZ_UpdateMuunInventorySubEquip '%s', '%s'",AccountId,Name);
	
	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		result = 0;
	}
	else
	{
		LogAddTD("error-L3 : [MuunSystem] MuunInvenSubEquipOpen #1 [%s][%s] %s %d",AccountId,Name, __FILE__, __LINE__);
		this->m_DBQuery.Clear();
		result = 1;
	}
	return result;
}


BOOL CMuunSystemDBSet::SelectMuunPeriodInfo(char *szName, _stMuunPeriodInfoList *MuunPeriodInfoList, BYTE *btListCnt)
{
	int result;
	__int16 sqlRetrun;
	CString QueryStr; 

	QueryStr.Format("EXEC WZ_MuunPeriodSelect '%s'",szName);
	if (this->m_DBQuery.Exec(QueryStr))
	{
		int iCnt = 0;
		for (sqlRetrun = this->m_DBQuery.Fetch();
			sqlRetrun != 100 && sqlRetrun != -1;
			sqlRetrun = this->m_DBQuery.Fetch())
		{
			if (iCnt > 101)
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [MuunSystem] higher than MAX_MUUN_INVENTORY [%s] %s %d",szName, __FILE__, __LINE__);
				break;
			}
			MuunPeriodInfoList[iCnt].wItemType = this->m_DBQuery.GetInt("ItemType");
			MuunPeriodInfoList[iCnt].dwSerial = this->m_DBQuery.GetInt64("Serial");
			MuunPeriodInfoList[iCnt++].lItemExpireDate = this->m_DBQuery.GetInt("ExpireDateConvert");
		}
		*btListCnt = iCnt;
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [MuunSystem] SelectMuunPeriodInfo #1 [%s] %s %d",szName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


BOOL CMuunSystemDBSet::InsertMuunPeriodInfo(char *szName, unsigned __int16 wItemType, unsigned int dwSerial, unsigned int dwItemDur, long lExpireDate)
{
	int result;
	CString QueryStr;

	QueryStr.Format("EXEC WZ_MuunPeriodInsert '%s', %d, %u, %d, %u",szName,wItemType,dwSerial,dwItemDur,lExpireDate);
	if (this->m_DBQuery.Exec(QueryStr))
	{
		if (this->m_DBQuery.Fetch() == 100)
		{
			this->m_DBQuery.Clear();
			result = 2;
		}
		else
		{
			int Ret = this->m_DBQuery.GetInt(1);
			this->m_DBQuery.Clear();
			result = Ret;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [MuunSystem] InsertMuunPeriodInfo #1 [%s] %s %d",szName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}

BOOL CMuunSystemDBSet::UpdateMuunPeriodInfo(char *szName, unsigned __int16 wItemType, DWORD dwSerial, BYTE btUsedInfo)
{
	int result; 
	CString QueryStr;

	QueryStr.Format("EXEC WZ_MuunPeriodUpdate '%s', %d, %u, %d",szName,wItemType,dwSerial,btUsedInfo);

	if (this->m_DBQuery.Exec(QueryStr))
	{
		if (this->m_DBQuery.Fetch() == 100)
		{
			this->m_DBQuery.Clear();
			result = 2;
		}
		else
		{
			int Ret = this->m_DBQuery.GetInt(1);
			this->m_DBQuery.Clear();
			result = Ret;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [MuunSystem] UpdateMuunPeriodInfo #1 [%s] %s %d",szName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


BOOL CMuunSystemDBSet::LoadMuunConditionInfo(char *szName, _stMuunConditionInfoList *MuunConditionInfoList)
{
	int result;
	__int16 sqlRetrun;
	CString QueryStr;

	QueryStr.Format("EXEC WZ_MuunConditionInfoGetLoad '%s'",szName);

	if (this->m_DBQuery.Exec(QueryStr))
	{
		int iCnt = 0;
		for (sqlRetrun = this->m_DBQuery.Fetch();
			sqlRetrun != 100 && sqlRetrun != -1;
			sqlRetrun = this->m_DBQuery.Fetch())
		{
			if (iCnt > 1)
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [MuunSystem] LoadMuunConditionInfo #2 higher than 2 [%s] %s %d",
					szName, __FILE__, __LINE__);
				break;
			}
			MuunConditionInfoList[iCnt].btConditionType = this->m_DBQuery.GetInt("ConditionType");
			MuunConditionInfoList[iCnt].btSlotIndex = this->m_DBQuery.GetInt("SlotIndex");
			MuunConditionInfoList[iCnt++].wValue = this->m_DBQuery.GetInt("Value");
		}
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [MuunSystem] LoadMuunConditionInfo #1 [%s] %s %d",szName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


BOOL CMuunSystemDBSet::SaveMuunConditionInfo(char *szName, BYTE btConditionType, char btSlotIndex, WORD wValue)
{
	int result;
	CString QueryStr;

	QueryStr.Format("EXEC WZ_MuunConditionInfoSetSave '%s', %d, %d, %d",szName,btSlotIndex,btConditionType,wValue);
	if (this->m_DBQuery.Exec(QueryStr))
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [MuunSystem] SaveMuunConditionInfo #1 [%s] %s %d",szName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


BOOL CMuunSystemDBSet::DelMuunConditionInfo(char *szName)
{
	int result;
	CString QueryStr;

	QueryStr.Format("EXEC WZ_MuunConditionInfoDel '%s'",szName);
	if (this->m_DBQuery.Exec(QueryStr))
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [MuunSystem] DelMuunConditionInfo #1 [%s] %s %d",
			szName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}