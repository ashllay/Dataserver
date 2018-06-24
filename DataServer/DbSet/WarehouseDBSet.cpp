// WarehouseDBSet.cpp: implementation of the CWarehouseDBSet class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WarehouseDBSet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWarehouseDBSet::CWarehouseDBSet()
{

}

CWarehouseDBSet::~CWarehouseDBSet()
{

}

BOOL CWarehouseDBSet::Connect()
{
	if( m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass) == FALSE )
	{
		LogAdd("Warehouse database connect fail.");
		return FALSE;
	}

	return TRUE;
}
BOOL CWarehouseDBSet::Get(char* AccountID)
{
	CString qSQL;
	
	char buffer[50];

	qSQL.Format("SELECT AccountID FROM T_WareHouseInfo WHERE AccountID='%s'", AccountID);
	
	if (m_DBQuery.ExecGetStr(qSQL,buffer) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CWarehouseDBSet::Create(char* AccountID)
{
	CString qSQL;
	
	qSQL.Format("INSERT INTO T_WareHouseInfo (AccountID, Money, EndUseDate, DbVersion) VALUES ('%s',0, getdate(), 3)", AccountID);

	if (m_DBQuery.Exec(qSQL) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

DWORD CWarehouseDBSet::Save(char* AccountID, BYTE* itembuf, int money, int pw)
{
	CString qSql;

	qSql.Format("UPDATE T_WareHouseInfo SET Money=%d, pw=%d, DbVersion=3 where AccountID='%s'", money, pw, AccountID);

	if (!this->m_DBQuery.Exec(qSql))
		LogAdd("Money Set error [%d] %s", money, AccountID);

	qSql.Format("EXEC WZ_SetWarehouseItem ? , '%s'", AccountID);

	this->m_DBQuery.WriteBlob(qSql, itembuf, MAX_WAREHOUSEDBSIZE);

	return TRUE;
//	CString qSQL;
//	
//#ifdef ITEM_DBSIZE_EXTEND_20050706
//	qSQL.Format("UPDATE warehouse SET Money=%d, pw=%d, DbVersion=3 where AccountID='%s'", money, pw, AccountID);
//#elif defined(PERSONAL_SHOP_20040113)
//	qSQL.Format("UPDATE warehouse SET Money=%d, pw=%d, DbVersion=2 where AccountID='%s'", money, pw, AccountID);
//#else
//	qSQL.Format("UPDATE warehouse SET Money=%d, pw=%d, DbVersion=1 where AccountID='%s'", money, pw, AccountID);
//#endif
//	
//	if (m_DBQuery.Exec(qSQL) == FALSE)
//	{
//		LogAdd("Money Set error [%d] %s",money,AccountID);
//	}
//
//	qSQL.Format("UPDATE warehouse SET Items=? where AccountID='%s'", AccountID);
//	
//	m_DBQuery.WriteBlob(qSQL, itembuf, MAX_WAREHOUSEDBSIZE);
//
//	return TRUE;
}

BOOL CWarehouseDBSet::Load(char *AccountID, BYTE* itembuf, int& money, BYTE& _dbversion, short& pw)
{
	CString qSql; // [esp+11Ch] [ebp-20h]
	int dbversion = 0;
	qSql.Format("SELECT Money, DbVersion, pw from T_WareHouseInfo where AccountID='%s'", AccountID);

	if (this->m_DBQuery.Exec(qSql) == 1)
	{
		if (this->m_DBQuery.Fetch() == 100)
		{
			money = 0;
			LogAdd("CWarehouseDBSet::Load : get money error %s", AccountID);
		}
		else
		{
			money = this->m_DBQuery.GetInt("Money");
			if (money < 0)
				money = 0;
			dbversion = this->m_DBQuery.GetInt("DbVersion");
			if (dbversion < 0)
				dbversion = 0;
			pw = this->m_DBQuery.GetInt("pw");
			if (pw < 0)
				pw = 0;
		}
		this->m_DBQuery.Clear();
	}
	else
	{
		money = 0;
		LogAdd("CWarehouseDBSet::Load : [%s] %s", AccountID, qSql);
	}
	_dbversion = dbversion;

	qSql.Format("SELECT Items from T_WareHouseInfo where AccountID='%s'",AccountID);
	int nRet = this->m_DBQuery.ReadBlob(qSql, itembuf);
	if (nRet)
	{
		if (nRet == -1)
		{
			return 0;
		}
		if (nRet > 0 && nRet < MAX_WAREHOUSEDBSIZE)
		{
			for (int  j = nRet; j < MAX_WAREHOUSEDBSIZE; ++j)
				itembuf[j] = 0xFF;
		}
	}
	else
	{
		for (int i = 0; i < MAX_WAREHOUSEDBSIZE; ++i)
			itembuf[i] = 0xFF;
	}
	return TRUE;
}

//BOOL CWarehouseDBSet::Load(char* AccountID, BYTE* itembuf, int& money, BYTE& _dbversion, short& pw)
//{
//	CString qSQL;
//
//	int dbversion = 0;
//	
//	qSQL.Format("SELECT Money, DbVersion, pw from T_WareHouseInfo where AccountID='%s'", AccountID);
//	
//	if (m_DBQuery.Exec(qSQL) == TRUE)
//	{
//		if (m_DBQuery.Fetch() != SQL_NO_DATA)
//		{
//			money = m_DBQuery.GetInt("Money");
//			
//			if (money < 0)
//			{
//				money = 0;
//			}
//			
//			dbversion = m_DBQuery.GetInt("DbVersion");
//			
//			if (dbversion < 0)
//			{
//				dbversion = 0;
//			}
//			
//			pw = m_DBQuery.GetInt("pw");
//			
//			if (pw == NULL)
//			{
//				pw = 0;
//			}
//		}
//		else
//		{
//			money = 0;
//			LogAdd("error-L2 : get money error %s", AccountID);
//		}
//
//		m_DBQuery.Clear();
//	}
//	else
//	{
//		money = 0;
//		LogAdd("error-L2 : [%s] %s", AccountID, qSQL);
//	}
//
//	_dbversion = dbversion;
//	
//	qSQL.Format("SELECT Items from T_WareHouseInfo where AccountID='%s'", AccountID);
//	
//	int nRet = m_DBQuery.ReadBlob(qSQL,itembuf);
//
//	if (nRet == 0)
//	{
//		for (int i = 0; i < MAX_WAREHOUSEDBSIZE; i++)
//		{
//			itembuf[i] = 0xFF;
//		}
//	}
//	else if (nRet == -1)
//	{
//		return FALSE;
//	}
//	else if (nRet > 0 && nRet < MAX_WAREHOUSEDBSIZE)
//	{
//		for (int i = nRet; i < MAX_WAREHOUSEDBSIZE; i++)
//		{
//			itembuf[i] = 0xFF;
//		}
//	}
//
//	return TRUE;
//}

DWORD CWarehouseDBSet::MoneyUpdate(char* AccountID, int money)
{
	CString qSQL;
	
	qSQL.Format("UPDATE T_WareHouseInfo SET Money=%d where AccountID='%s'", money, AccountID);
	
	if (m_DBQuery.Exec(qSQL) == FALSE)
	{	
		LogAdd("Money Set error [%d] %s", money, AccountID);
	}

	return TRUE;
}

DWORD CWarehouseDBSet::GetWareHouseMoney(char *AccountID)
{
	int money =0 ;
	CString qSql;

	qSql.Format("SELECT Money from T_WareHouseInfo where AccountID='%s'",AccountID);

	if (this->m_DBQuery.Exec(qSql) == TRUE)
	{
		if (this->m_DBQuery.Fetch() == SQL_NO_DATA)
		{
			money = 0;
			LogAdd("GetWareHouseMoney : get money error %s", AccountID);
		}
		else
		{
			money = this->m_DBQuery.GetInt("Money");
			if (money < 0)
				money = 0;
		}
		this->m_DBQuery.Clear();
	}
	else
	{
		money = 0;
		LogAdd("GetWareHouseMoney : [%s] %s", AccountID, qSql);
	}

	return money;
}