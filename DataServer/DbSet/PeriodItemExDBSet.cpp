// PeriodItemExDBSet.cpp: implementation of the CPeriodItemExDBSet class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PeriodItemExDBSet.h"
//#include "..\common\winutil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPeriodItemExDBSet::CPeriodItemExDBSet()
{

}

CPeriodItemExDBSet::~CPeriodItemExDBSet()
{

}

BOOL CPeriodItemExDBSet::Connect()
{
	if( m_Query.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass) == FALSE )
	{
		MsgBox("PeriodtemExDBSet ODBC Connect Fail");
		return FALSE;
	}

	return TRUE;
}

int CPeriodItemExDBSet::Insert(DWORD dwUserGUID, char* pchCharacterName, BYTE btItemType, WORD wItemCode, BYTE btEffectCategory, BYTE btEffectType1, BYTE btEffectType2, DWORD dwSerial, DWORD dwDuration, long lBuyDate, long lExpireDate)
{
	int iReturnCode = 0;

	CString QuerySql;

	QuerySql.Format("EXEC WZ_PeriodItemInsertEx %d, '%s', %d, %d, %d, %d, %d, %u, %d, %d, %d",
		dwUserGUID, pchCharacterName, btItemType, wItemCode, btEffectCategory, btEffectType1, btEffectType2, dwSerial, dwDuration, lBuyDate, lExpireDate);

	if( m_Query.Exec(QuerySql) == FALSE)
	{
		m_Query.Clear();
		return -1;
	}

	if( m_Query.Fetch() != SQL_NO_DATA)
	{
		iReturnCode = m_Query.GetInt(1);
	}
	else
	{
		m_Query.Clear();
		return -1;
	}

	m_Query.Clear();

	return iReturnCode;
}

int CPeriodItemExDBSet::Delete(DWORD dwUserGUID, char* pchCharacterName, WORD wItemCode, BYTE btItemType, DWORD dwSerial)
{
	CString QuerySql;

	if(SQLSyntexCheck(pchCharacterName) == FALSE)
	{
		return 2;
	}

	QuerySql.Format("EXEC WZ_PeriodItemDeleteEx %d, '%s', %d, %d, %u", dwUserGUID, pchCharacterName, wItemCode, btItemType, dwSerial);

	if( m_Query.Exec(QuerySql) == FALSE)
	{
		m_Query.Clear();
		return 2;
	}

	if( m_Query.Fetch() == SQL_NO_DATA)
	{
		m_Query.Clear();
		return 1;
	}

	m_Query.Clear();

	return 0;
}

int CPeriodItemExDBSet::Select(LPPERIOD_ITEMLIST lpPeriodItemList)
{
	int iReturnCode = 0;
	int iItemCount = 0;

	CString QuerySql;

	QuerySql.Format("EXEC WZ_PeriodItemSelectEx %d, '%s'", lpPeriodItemList->dwUserGuid, lpPeriodItemList->chCharacterName);

	if( m_Query.Exec(QuerySql) == FALSE)
	{
		m_Query.Clear();
		return -3;
	}

	short i = m_Query.Fetch();

	while(i != SQL_NO_DATA && i != SQL_NULL_DATA)
	{
		iReturnCode = m_Query.GetInt(1);

		if(iReturnCode < 0)
		{
			break;
		}

		lpPeriodItemList->ItemData[iItemCount].btUsedInfo = 1;
		lpPeriodItemList->ItemData[iItemCount].wItemCode = m_Query.GetInt("ItemCode");
		lpPeriodItemList->ItemData[iItemCount].btItemType = m_Query.GetInt("ItemType");
		lpPeriodItemList->ItemData[iItemCount].btEffectType1 = m_Query.GetInt("EffectType1");
		lpPeriodItemList->ItemData[iItemCount].btEffectType2 = m_Query.GetInt("EffectType2");
		lpPeriodItemList->ItemData[iItemCount].btEffectCategory = m_Query.GetInt("OptionType");
		lpPeriodItemList->ItemData[iItemCount].dwSerial = (DWORD)m_Query.GetInt64("SerialCode");
		lpPeriodItemList->ItemData[iItemCount].lItemBuyDate = m_Query.GetInt("BuyDateConvert");
		lpPeriodItemList->ItemData[iItemCount].lItemExpireDate = m_Query.GetInt("ExpireDateConvert");
		iItemCount++;

		if(iItemCount >= 100)
		{
			LogAddTD("[PeriodItemEx][Select] Period Item List Count Over %d, User Id : %s(%d)", 100, lpPeriodItemList->chCharacterName, lpPeriodItemList->dwUserGuid);
			break;
		}

		i = m_Query.Fetch();
	}

	m_Query.Clear();
	lpPeriodItemList->btItemCount = iItemCount;

	return iReturnCode;
}

int CPeriodItemExDBSet::Update()
{
	int iReturnCode = 0;

	return iReturnCode;
}

int CPeriodItemExDBSet::SelectExpiredItemList(DWORD dwUserGuid, char* pchCharacterName, LPPERIOD_EXPIRED_ITEMLIST lpExpiredItemList)
{
	int iReturnCode = 0;
	int iItemCount = 0;
	
	CString QueryStr;
	QueryStr.Format("EXEC WZ_PeriodItemExpiredItemSelectEx %d, '%s'", dwUserGuid, pchCharacterName);

	if( m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		return -3;
	}

	short sqlReturn = m_Query.Fetch();

	while(sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
	{
		lpExpiredItemList->ExpiredItem[iItemCount].wItemCode = m_Query.GetInt("ItemCode");
		lpExpiredItemList->ExpiredItem[iItemCount].dwSerial = (DWORD)m_Query.GetInt64("SerialCode");
		iItemCount++;

		sqlReturn = m_Query.Fetch();

		if(iItemCount >= 30)
		{
			break;
		}
	}

	m_Query.Clear();

	lpExpiredItemList->btItemCount = iItemCount;

	return iItemCount; //wz bug
}

LuckyItemDBSet::LuckyItemDBSet()
{

}

LuckyItemDBSet::~LuckyItemDBSet()
{

}

BOOL LuckyItemDBSet::Connect()
{
	if( m_Query.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass) == FALSE )
	{
		MsgBox("LuckyItemDBSet ODBC Connect Fail");
		return FALSE;
	}

	return TRUE;
}

int LuckyItemDBSet::Insert(DWORD dwUserGuid, char* szCharName, WORD wItemCode, DWORD dwSerial, WORD wDurabilitySmall)
{
	int iReturnCode = 0;

	CString QuerySql;
	QuerySql.Format("EXEC WZ_LuckyItemInsert %d, '%s', %d, %u, %d", dwUserGuid, szCharName, wItemCode, dwSerial, wDurabilitySmall);

	if( m_Query.Exec(QuerySql) == FALSE)
	{
		m_Query.Clear();
		return -1;
	}

	if( m_Query.Fetch() != SQL_NO_DATA)
	{
		iReturnCode = m_Query.GetInt(1);
	}
	else
	{
		m_Query.Clear();
		return -1;
	}

	m_Query.Clear();

	return iReturnCode;
}

int LuckyItemDBSet::Delete(char* szCharName, WORD wItemCode, DWORD dwSerial)
{
	int iReturnCode = 0;

	CString QuerySql;
	QuerySql.Format("WZ_LuckyItemDelete '%s', %d, %u", szCharName, wItemCode, dwSerial);

	if( m_Query.Exec(QuerySql) == FALSE)
	{
		m_Query.Clear();
		return -1;
	}

	if( m_Query.Fetch() != SQL_NO_DATA)
	{
		iReturnCode = m_Query.GetInt(1);
	}
	else
	{
		m_Query.Clear();
		return -1;
	}

	m_Query.Clear();

	return iReturnCode;
}

int LuckyItemDBSet::SelectLuckyItemList(char* szCharName, LPPMSG_LUCKYITME_DB_INFO pLuckyItemInfo)
{
	int iItemCount = 0;
	int iReturnCode = 0;

	CString QueryStr;

	QueryStr.Format("WZ_LuckyItemSelect '%s'", szCharName);

	if( m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		return -3;
	}

	short sqlReturn = m_Query.Fetch();

	while(sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
	{
		pLuckyItemInfo[iItemCount].wItemCode = m_Query.GetInt("ItemCode");
		pLuckyItemInfo[iItemCount].dwSerial = (DWORD)m_Query.GetInt64("ItemSerial");
		pLuckyItemInfo[iItemCount].wDurabilitySmall = (WORD)m_Query.GetInt64("DurabilitySmall");
		iItemCount++;

		sqlReturn = m_Query.Fetch();

		if(iItemCount >= 45)
		{
			break;
		}
	}

	m_Query.Clear();

	return iItemCount; //wz bug
}


CPeriodBuffDBSet::CPeriodBuffDBSet()
{
}

CPeriodBuffDBSet::~CPeriodBuffDBSet()
{
}

BOOL CPeriodBuffDBSet::Connect()
{
	if (m_Query.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass) == FALSE)
	{
		MsgBox("CPeriodBuffDBSet ODBC Connect Fail");
		return FALSE;
	}
	return TRUE;
}

int CPeriodBuffDBSet::Insert(char *szCharacterName, unsigned __int16 wBuffIndex, char btEffectType1, char btEffectType2, unsigned int dwDuration, int lExpireDate)
{
	int result;
	CString QuerySql;
	int iReturnCode;
	int v13;

	iReturnCode = 0;
	v13 = 0;
	QuerySql.Format("EXEC WZ_PeriodBuffInsert '%s', %d, %d, %d, %d, %d",
		szCharacterName,
		wBuffIndex,
		btEffectType1,
		btEffectType2,
		dwDuration,
		lExpireDate);
	if (this->m_Query.Exec(QuerySql))
	{
		if (this->m_Query.Fetch() == 100)
		{
			this->m_Query.Clear();
			v13 = -1;
			result = -1;
		}
		else
		{
			iReturnCode = this->m_Query.GetInt(1);
			this->m_Query.Clear();
			v13 = -1;
			result = iReturnCode;
		}
	}
	else
	{
		this->m_Query.Clear();
		v13 = -1;
		result = -1;
	}
	return result;
}

//----- (00448490) --------------------------------------------------------
int CPeriodBuffDBSet::Delete(char *szCharacterName, unsigned __int16 wBuffIndex)
{
	
	int result; // eax
	CString QuerySql; // [esp+F8h] [ebp-2Ch]
	int iReturnCode; // [esp+104h] [ebp-20h]
	int v9;

	
	iReturnCode = 0;

	v9 = 0;
	QuerySql.Format("WZ_PeriodBuffDelete '%s', %d",
		szCharacterName,
		wBuffIndex);
	
	if (this->m_Query.Exec(QuerySql))
	{
		if (this->m_Query.Fetch() == 100)
		{
			this->m_Query.Clear();
			v9 = -1;
			result = -1;
		}
		else
		{
			iReturnCode = this->m_Query.GetInt(1);
			this->m_Query.Clear();
			v9 = -1;
			result = iReturnCode;
		}
	}
	else
	{
		this->m_Query.Clear();
		v9 = -1;
		
		result = -1;
	}
	return result;
}

//----- (00448610) --------------------------------------------------------
int CPeriodBuffDBSet::Select(char *szCharacterName, _tagPeriodBuffInfo *lpPeriodBuff, int *iBuffCnt)
{
	int result; // eax
	__int16 sqlReturn;
	CString QueryStr;
	int iBuffCount;
	int iReturnCode;
	int v16;
	iReturnCode = 0;
	iBuffCount = 0;
	
	v16 = 0;
	QueryStr.Format("EXEC WZ_PeriodBuffSelect '%s'",szCharacterName);
	if (this->m_Query.Exec(QueryStr))
	{
		sqlReturn = this->m_Query.Fetch();
		if (sqlReturn == 100)
		{
			this->m_Query.Clear();
			v16 = -1;
			result = -2;
		}
		else
		{
			while (sqlReturn != 100)
			{
				if (sqlReturn == -1)
					break;
				iReturnCode = this->m_Query.GetInt(1);
				if (iReturnCode < 0)
					break;
				lpPeriodBuff[iBuffCount].wBuffIndex = this->m_Query.GetInt("BuffIndex");
				lpPeriodBuff[iBuffCount].btEffectType1 = this->m_Query.GetInt("EffectType1");
				lpPeriodBuff[iBuffCount].btEffectType2 = this->m_Query.GetInt("EffectType2");
				lpPeriodBuff[iBuffCount++].lExpireDate = this->m_Query.GetInt("ExpireDateConvert");
				if (iBuffCount >= 10)
				{
					LogAddTD("[CPeriodBuff][Select] Period Item List Count Over %d, User Id : %s", 10, szCharacterName);
					break;
				}
				sqlReturn = this->m_Query.Fetch();
			}
			*iBuffCnt = iBuffCount;
			this->m_Query.Clear();
			v16 = -1;
			result = iReturnCode;
		}
	}
	else
	{
		this->m_Query.Clear();
		v16 = -1;
		result = -3;
	}
	return result;
}