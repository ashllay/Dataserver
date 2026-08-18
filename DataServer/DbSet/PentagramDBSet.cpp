// PentagramDBSet.cpp: implementation of the CPentagramDBSet class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PentagramDBSet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPentagramDBSet::CPentagramDBSet()
{

}

CPentagramDBSet::~CPentagramDBSet()
{

}

BOOL CPentagramDBSet::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass) == FALSE)
	{
		MsgBox(" CPentagramDBSet DB set connect fail.");
		return FALSE;
	}

	return TRUE;
}

int CPentagramDBSet::DelPentagramJewel(PMSG_DEL_PENTAGRAMJEWEL* lpRecv)
{
	int JewelIndex;
	int JewelPos;
	int UserGuid;
	char CharName[MAX_IDSTRING+1] = { 0 };
	char AccountId[MAX_IDSTRING + 1] = { 0 };

	CString qSql;

	memcpy(&AccountId, lpRecv->szName, MAX_IDSTRING);
	if (strlen(AccountId) > 0 && strlen(AccountId) <= MAX_IDSTRING)
	{

		memcpy(&CharName, lpRecv->szName, MAX_IDSTRING);
		if (strlen(CharName) > 0 && strlen(CharName) <= MAX_IDSTRING)
		{
			UserGuid = lpRecv->iUserGuid;
			JewelPos = lpRecv->btJewelPos;
			JewelIndex = lpRecv->btJewelIndex;

			qSql.Format("WZ_PentagramInfoDelete %d, '%s', '%s', %d, %d", UserGuid, AccountId, CharName, JewelPos, JewelIndex);
			if (m_DBQuery.Exec(qSql) == FALSE)
			{
				bool bReConnect = false;
				m_DBQuery.PrintDiag(bReConnect);

				LogAddC(LOGC_RED, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				m_DBQuery.Clear();
				return 1;
			}
			m_DBQuery.Clear();
			return 0;
		}
		else
		{
			LogAddC(LOGC_RED, "%s] 삭제 에러 %s %d", &CharName, __FILE__, __LINE__);
			return 1;
		}
	}
	else
	{
		LogAddC(LOGC_RED, "%s] 삭제 에러 %s %d", &AccountId, __FILE__, __LINE__);
		return 1;
	}
	return 0;
}


int CPentagramDBSet::GetPentagramJewel(int UserGuid, char* Id, char* Char, PENTAGRAMJEWEL_INFO* pPentagramJewelInfo, PMSG_ANS_PENTAGRAMJEWEL* lpMsg, int JewelPos)
{
	int result;
	char CharName[MAX_IDSTRING+1] = { 0 };
	char AccountId[MAX_IDSTRING+1] = { 0 };

	CString qSql;
	int iReturnCode = 0;
	int iItemCount = 0;

	memcpy(&AccountId, Id, MAX_IDSTRING);
	if (strlen(AccountId) && strlen(AccountId) <= MAX_IDSTRING)
	{
		memcpy(&CharName, Char, MAX_IDSTRING);
		if (strlen(CharName) && strlen(CharName) <= MAX_IDSTRING)
		{
			qSql.Format("WZ_PentagramInfoSelect %d, '%s', '%s', %d", UserGuid, AccountId, CharName, JewelPos);

			if (m_DBQuery.Exec(qSql))
			{
				short i = m_DBQuery.Fetch();

				while (i != SQL_NO_DATA && i != SQL_NULL_DATA)
				{
					iReturnCode = m_DBQuery.GetInt(1);

					if (iReturnCode < 0)
					{
						break;
					}

					pPentagramJewelInfo[iItemCount].btJewelPos = JewelPos;
					pPentagramJewelInfo[iItemCount].btJewelIndex = m_DBQuery.GetInt("JewelIndex");
					pPentagramJewelInfo[iItemCount].btItemType = m_DBQuery.GetInt("ItemType");
					pPentagramJewelInfo[iItemCount].wItemIndex = m_DBQuery.GetInt("ItemIndex");
					pPentagramJewelInfo[iItemCount].btMainAttribute = m_DBQuery.GetInt("MainAttribute");
					pPentagramJewelInfo[iItemCount].btLevel = m_DBQuery.GetInt("JewelLevel");
					pPentagramJewelInfo[iItemCount].btRank1OptionNum = m_DBQuery.GetInt("Rank1");
					pPentagramJewelInfo[iItemCount].btRank1Level = m_DBQuery.GetInt("Rank1Level");
					pPentagramJewelInfo[iItemCount].btRank2OptionNum = m_DBQuery.GetInt("Rank2");
					pPentagramJewelInfo[iItemCount].btRank2Level = m_DBQuery.GetInt("Rank2Level");
					pPentagramJewelInfo[iItemCount].btRank3OptionNum = m_DBQuery.GetInt("Rank3");
					pPentagramJewelInfo[iItemCount].btRank3Level = m_DBQuery.GetInt("Rank3Level");
					pPentagramJewelInfo[iItemCount].btRank4OptionNum = m_DBQuery.GetInt("Rank4");
					pPentagramJewelInfo[iItemCount].btRank4Level = m_DBQuery.GetInt("Rank4Level");
					pPentagramJewelInfo[iItemCount].btRank5OptionNum = m_DBQuery.GetInt("Rank5");
					pPentagramJewelInfo[iItemCount].btRank5Level = m_DBQuery.GetInt("Rank5Level");
					iItemCount++;

					if (iItemCount >= MAX_PENTAGRAMJEWEL_INFO)
					{
						break;
					}

					i = m_DBQuery.Fetch();

				}

				lpMsg->btJewelCnt = iItemCount;
				m_DBQuery.Clear();
				result = 0;
			}
			else
			{
				bool bReConnect = false;
				m_DBQuery.PrintDiag(bReConnect);
				LogAddC(LOGC_RED, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				m_DBQuery.Clear();

				result = 1;
			}
		}
		else
		{
			LogAddC(LOGC_RED, "%s] 로드 에러 %s %d", &CharName, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(LOGC_RED, "%s] 로드 에러 %s %d", &AccountId, __FILE__, __LINE__);
		result = 1;
	}
	return result;
}

/*
int CPentagramDBSet::InsertPentagramJewel(PMSG_INSERT_PENTAGRAMJEWEL *lpMsg)
{
	int Rank5Level = lpMsg->btRank5Level;
	int Rank5 = lpMsg->btRank5OptionNum;
	int Rank4Level = lpMsg->btRank4Level;
	int Rank4 = lpMsg->btRank4OptionNum;
	int Rank3Level = lpMsg->btRank3Level;
	int Rank3 = lpMsg->btRank3OptionNum;
	int Rank2Level = lpMsg->btRank2Level;
	int Rank2 = lpMsg->btRank2OptionNum;
	int Rank1Level = lpMsg->btRank1Level;
	int Rank1 = lpMsg->btRank1OptionNum;
	int JewelLevel = lpMsg->btLevel;
	int MainAttribute = lpMsg->btMainAttribute;
	int ItemIndex = lpMsg->iItemIndex;
	int ItemType = lpMsg->btItemType;
	int JewelIndex = lpMsg->btJewelIndex;
	int JewelPos = lpMsg->btJewelPos;
	int UserGuid = lpMsg->iUserGuid;
	char CharName[11] = { 0 };
	char AccountID[11] = { 0 };


	CString qSql;

	memcpy(AccountID, lpMsg->AccountId, 0xAu);
	if (strlen(AccountID) && strlen(AccountID) <= 0xA)
	{

		memcpy(&CharName, lpMsg->szName, 0xAu);
		if (strlen(CharName) && strlen(CharName) <= 0xA)
		{
			qSql.Format(
				"WZ_PentagramInfoUpdate %d, '%s', '%s', %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
				UserGuid,
				AccountID,
				CharName,
				JewelPos,
				JewelIndex,
				ItemType,
				ItemIndex,
				MainAttribute,
				JewelLevel,
				Rank1,
				Rank1Level,
				Rank2,
				Rank2Level,
				Rank3,
				Rank3Level,
				Rank4,
				Rank4Level,
				Rank5,
				Rank5Level
				);


			if (!m_DBQuery.Exec(qSql))
			{
				bool bReConnect = false;
				m_DBQuery.PrintDiag(bReConnect);
				LogAddC(LOGC_RED, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				m_DBQuery.Clear();
				return 1;
			}
			m_DBQuery.Clear();
			return 1;
		}
		else
		{
			LogAddC(LOGC_RED, "%s] +Þ-ª +íÀ» %s %d", &CharName, __FILE__, __LINE__);
			return 1;
		}
	}
	else
	{
		LogAddC(LOGC_RED, "%s] +Þ-ª +íÀ» %s %d", &AccountID, __FILE__, __LINE__);
		return 1;
	}
}
*/

int CPentagramDBSet::InsertPentagramJewel(PMSG_INSERT_PENTAGRAMJEWEL* lpMsg)
{
	char CharName[MAX_IDSTRING + 1] = { 0 };
	char AccountID[MAX_IDSTRING + 1] = { 0 };

	CString qSql;

	memcpy(AccountID, lpMsg->AccountId, MAX_IDSTRING);
	if (strlen(AccountID) && strlen(AccountID) <= MAX_IDSTRING)
	{

		memcpy(&CharName, lpMsg->szName, MAX_IDSTRING);
		if (strlen(CharName) && strlen(CharName) <= MAX_IDSTRING)
		{
			qSql.Format(
				"WZ_PentagramInfoUpdate %d, '%s', '%s', %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
				lpMsg->iUserGuid,
				AccountID,
				CharName,
				lpMsg->btJewelPos,
				lpMsg->btJewelIndex,
				lpMsg->btItemType,
				lpMsg->iItemIndex,
				lpMsg->btMainAttribute,
				lpMsg->btLevel,
				lpMsg->btRank1OptionNum,
				lpMsg->btRank1Level,
				lpMsg->btRank2OptionNum,
				lpMsg->btRank2Level,
				lpMsg->btRank3OptionNum,
				lpMsg->btRank3Level,
				lpMsg->btRank4OptionNum,
				lpMsg->btRank4Level,
				lpMsg->btRank5OptionNum,
				lpMsg->btRank5Level
			);

			if (!m_DBQuery.Exec(qSql))
			{
				bool bReConnect = false;
				m_DBQuery.PrintDiag(bReConnect);
				LogAddC(LOGC_RED, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				m_DBQuery.Clear();
				return 1;
			}
			m_DBQuery.Clear();
			return 1;
		}
		else
		{
			LogAddC(LOGC_RED, "%s] Insert 에러 %s %d", &CharName, __FILE__, __LINE__);
			return 1;
		}
	}
	else
	{
		LogAddC(LOGC_RED, "%s] Insert 에러 %s %d", &AccountID, __FILE__, __LINE__);
		return 1;
	}
}

int CPentagramDBSet::SetPentagramJewel(PMSG_PENTAGRAMJEWEL_INFO* lpRecv)
{
	char AccountID[MAX_IDSTRING + 1] = { 0 };
	char CharName[MAX_IDSTRING + 1] = { 0 };

	memcpy(AccountID, lpRecv->AccountId, MAX_IDSTRING);
	memcpy(CharName, lpRecv->szName, MAX_IDSTRING);

	if (strlen(AccountID) == 0 || strlen(AccountID) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED,"%s] Account Error %s %d",AccountID,__FILE__,__LINE__);
		return 1;
	}

	if (strlen(CharName) == 0 || strlen(CharName) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED,"%s] Character Error %s %d",CharName,__FILE__,__LINE__);
		return 1;
	}

	int iUserGuid = lpRecv->iUserGuid;
	int btJewelCnt = lpRecv->btJewelCnt;
	int btJewelPos = lpRecv->btJewelPos;

	if (btJewelCnt < 0 || btJewelCnt > MAX_PENTAGRAMJEWEL_INFO-1)
	{
		LogAddC(LOGC_RED,"%s] Invalid Jewel Count %s %d",AccountID,__FILE__,__LINE__);

		return 1;
	}

	// EXACTLY LIKE ORIGINAL BINARY
	PENTAGRAMJEWEL_INFO* lpInfo = (PENTAGRAMJEWEL_INFO*)((BYTE*)lpRecv + sizeof(PMSG_PENTAGRAMJEWEL_INFO));

	CString qSql;

	for (int i = 0; i < btJewelCnt; i++)
	{
		PENTAGRAMJEWEL_INFO* lpJewel = &lpInfo[i];

		qSql.Format(
			"WZ_PentagramInfoUpdate %d, '%s', '%s', %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
			iUserGuid,
			AccountID,
			CharName,
			lpJewel->btJewelPos,
			lpJewel->btJewelIndex,
			lpJewel->btItemType,
			lpJewel->wItemIndex,
			lpJewel->btMainAttribute,
			lpJewel->btLevel,
			lpJewel->btRank1OptionNum,
			lpJewel->btRank1Level,
			lpJewel->btRank2OptionNum,
			lpJewel->btRank2Level,
			lpJewel->btRank3OptionNum,
			lpJewel->btRank3Level,
			lpJewel->btRank4OptionNum,
			lpJewel->btRank4Level,
			lpJewel->btRank5OptionNum,
			lpJewel->btRank5Level
		);

		//LogAddTD("%s", qSql);

		if (!m_DBQuery.Exec(qSql))
		{
			bool bReconnect = false;
			m_DBQuery.PrintDiag(bReconnect);
			LogAddC(LOGC_RED, "Error m_DBQuery.Exec %s %d" ,__FILE__, __LINE__);
			m_DBQuery.Clear();
			return 1;
		}

		m_DBQuery.Clear();
	}
	return 0;
}

CPentagramLogDBSet::CPentagramLogDBSet()
{
}

CPentagramLogDBSet::~CPentagramLogDBSet()
{
}

int CPentagramLogDBSet::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass) == FALSE)
	{
		MsgBox(" CPentagramLogDBSet DB set connect fail.");
		return FALSE;
	}

	return TRUE;
}

int CPentagramLogDBSet::InsertJewelUpgradeInfo(_tagPMSG_REQ_JEWEL_UPGRADE_INFO_INSERT_DS* lpMsg)
{
	int iReturnValue;
	CString szQuery;
	int iSuccess;
	int iUpgradeType;
	int iJewelIndex;
	int iJewelType;
	char szName[MAX_IDSTRING + 1];
	char szId[MAX_IDSTRING + 1];

	szId[MAX_IDSTRING] = 0;
	memcpy(szId, lpMsg->AccountID, MAX_IDSTRING);

	if (strlen(szId) && (strlen(szId) <= MAX_IDSTRING))
	{
		szName[MAX_IDSTRING] = 0;
		memcpy(szName, lpMsg->Name, MAX_IDSTRING);

		if (strlen(szName) && (strlen(szName) <= MAX_IDSTRING))
		{
			iJewelType = lpMsg->iJewelType;
			iJewelIndex = lpMsg->iJewelIndex;
			iUpgradeType = lpMsg->iUpgradeType;
			iSuccess = lpMsg->iSuccess;

			iReturnValue = 0;
			szQuery.Format("WZ_PentagramJewelUpgradeInfoInsert '%s', '%s', %d, %d, %d, %d",
				szId, szName, iJewelType, iJewelIndex, iUpgradeType, iSuccess);
			if (!this->m_DBQuery.Exec(szQuery))
			{
				LogAddC(LOGC_RED, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				iReturnValue = 1;
			}
			this->m_DBQuery.Clear();
			return iReturnValue;
		}
		else
		{
			LogAddC(LOGC_RED, "%s] Insert 에러 %s %d", szName, __FILE__, __LINE__);
			return 1;
		}
	}
	LogAddC(LOGC_RED, "%s] Insert 에러 %s %d", szId, __FILE__, __LINE__);
	return 1;
}