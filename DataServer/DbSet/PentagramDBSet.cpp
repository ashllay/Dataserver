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
	char CharName[11] = { 0 };
	char AccountId[11] = { 0 };

	CString qSql;

	memcpy(&AccountId, lpRecv->szName, 0xAu);
	if (strlen(AccountId) > 0 && strlen(AccountId) <= 0xA)
	{

		memcpy(&CharName, lpRecv->szName, 0xAu);
		if (strlen(CharName) > 0 && strlen(CharName) <= 0xA)
		{
			UserGuid = lpRecv->iUserGuid;
			JewelPos = lpRecv->btJewelPos;
			JewelIndex = lpRecv->btJewelIndex;

			qSql.Format("WZ_PentagramInfoDelete %d, '%s', '%s', %d, %d", UserGuid, AccountId, CharName, JewelPos, JewelIndex);
			if (m_DBQuery.Exec(qSql) == FALSE)
			{
				bool bReConnect = false;
				m_DBQuery.PrintDiag(bReConnect);

				LogAddC(2, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				m_DBQuery.Clear();
				return 1;
			}
			m_DBQuery.Clear();
			return 0;
		}
		else
		{
			LogAddC(2, "%s] +Þ-ª +íÀ» %s %d", &CharName, __FILE__, __LINE__);
			return 1;
		}
	}
	else
	{
		LogAddC(2, "%s] +Þ-ª +íÀ» %s %d", &AccountId, __FILE__, __LINE__);
		return 1;
	}
	return 0;
}


int CPentagramDBSet::GetPentagramJewel(int UserGuid, char* Id, char* Char, PENTAGRAMJEWEL_INFO PentaGramInfo[250], PMSG_ANS_PENTAGRAMJEWEL* lpMsg, int JewelPos)
{
	int result;
	char CharName[11] = { 0 };
	char AccountId[11] = { 0 };

	CString qSql;
	int iReturnCode = 0;
	int iItemCount = 0;

	memcpy(&AccountId, Id, 0xAu);
	if (strlen(AccountId) && strlen(AccountId) <= 0xA)
	{
		memcpy(&CharName, Char, 0xAu);
		if (strlen(CharName) && strlen(CharName) <= 0xA)
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

					PentaGramInfo[iItemCount].btJewelPos = JewelPos;
					PentaGramInfo[iItemCount].btJewelIndex = m_DBQuery.GetInt("JewelIndex");
					PentaGramInfo[iItemCount].btItemType = m_DBQuery.GetInt("ItemType");
					PentaGramInfo[iItemCount].wItemIndex = m_DBQuery.GetInt("ItemIndex");
					PentaGramInfo[iItemCount].btMainAttribute = m_DBQuery.GetInt("MainAttribute");
					PentaGramInfo[iItemCount].btLevel = m_DBQuery.GetInt("JewelLevel");
					PentaGramInfo[iItemCount].btRank1OptionNum = m_DBQuery.GetInt("Rank1");
					PentaGramInfo[iItemCount].btRank1Level = m_DBQuery.GetInt("Rank1Level");
					PentaGramInfo[iItemCount].btRank2OptionNum = m_DBQuery.GetInt("Rank2");
					PentaGramInfo[iItemCount].btRank2Level = m_DBQuery.GetInt("Rank2Level");
					PentaGramInfo[iItemCount].btRank3OptionNum = m_DBQuery.GetInt("Rank3");
					PentaGramInfo[iItemCount].btRank3Level = m_DBQuery.GetInt("Rank3Level");
					PentaGramInfo[iItemCount].btRank4OptionNum = m_DBQuery.GetInt("Rank4");
					PentaGramInfo[iItemCount].btRank4Level = m_DBQuery.GetInt("Rank4Level");
					PentaGramInfo[iItemCount].btRank5OptionNum = m_DBQuery.GetInt("Rank5");
					PentaGramInfo[iItemCount].btRank5Level = m_DBQuery.GetInt("Rank5Level");
					iItemCount++;

					if (iItemCount >= 250)
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
				LogAddC(2, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				m_DBQuery.Clear();

				result = 1;
			}
		}
		else
		{
			LogAddC(2, "%s] 로드 에러 %s %d", &CharName, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(2, "%s] 로드 에러 %s %d", &AccountId, __FILE__, __LINE__);
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
				LogAddC(2, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				m_DBQuery.Clear();
				return 1;
			}
			m_DBQuery.Clear();
			return 1;
		}
		else
		{
			LogAddC(2, "%s] +Þ-ª +íÀ» %s %d", &CharName, __FILE__, __LINE__);
			return 1;
		}
	}
	else
	{
		LogAddC(2, "%s] +Þ-ª +íÀ» %s %d", &AccountID, __FILE__, __LINE__);
		return 1;
	}
}
*/

int CPentagramDBSet::InsertPentagramJewel(PMSG_INSERT_PENTAGRAMJEWEL* lpMsg)
{
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
				LogAddC(2, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				m_DBQuery.Clear();
				return 1;
			}
			m_DBQuery.Clear();
			return 1;
		}
		else
		{
			LogAddC(2, "%s] +Þ-ª +íÀ» %s %d", &CharName, __FILE__, __LINE__);
			return 1;
		}
	}
	else
	{
		LogAddC(2, "%s] +Þ-ª +íÀ» %s %d", &AccountID, __FILE__, __LINE__);
		return 1;
	}
}

int CPentagramDBSet::SetPentagramJewel(PMSG_PENTAGRAMJEWEL_INFO* src)
{
	int iItemCount;


	char CharName[11] = { 0 };
	char AccountID[11] = { 0 };

	CString qSql;

	memcpy(AccountID, src->AccountId, 0xAu);
	if (strlen(AccountID) && strlen(AccountID) <= 0xA)
	{

		memcpy(&CharName, src->szName, 0xAu);
		if (strlen(CharName) && strlen(CharName) <= 0xA)
		{

			iItemCount = src->btJewelCnt;
			if (iItemCount >= 0 && iItemCount <= 249)
			{

				for (int i = 0; i < iItemCount; ++i)
				{

					qSql.Format(
						"WZ_PentagramInfoUpdate %d, '%s', '%s', %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
						src->iUserGuid,
						AccountID,
						CharName,
						src->btJewelPos,
						src->PentaGramInfo[i].btJewelIndex,
						src->PentaGramInfo[i].btItemType,
						src->PentaGramInfo[i].wItemIndex,
						src->PentaGramInfo[i].btMainAttribute,
						src->PentaGramInfo[i].btLevel,
						src->PentaGramInfo[i].btRank1OptionNum,
						src->PentaGramInfo[i].btRank1Level,
						src->PentaGramInfo[i].btRank2OptionNum,
						src->PentaGramInfo[i].btRank2Level,
						src->PentaGramInfo[i].btRank3OptionNum,
						src->PentaGramInfo[i].btRank3Level,
						src->PentaGramInfo[i].btRank4OptionNum,
						src->PentaGramInfo[i].btRank4Level,
						src->PentaGramInfo[i].btRank5OptionNum,
						src->PentaGramInfo[i].btRank5Level
					);

					if (!m_DBQuery.Exec(qSql))
					{
						bool bReConnect = false;
						m_DBQuery.PrintDiag(bReConnect);
						LogAddC(2, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
						m_DBQuery.Clear();
						return 1;
						break;
					}
					m_DBQuery.Clear();
				}
				return 1;
			}
			else
			{
				LogAddC(2, "%s] +·+Õ +íÀ»(+Ë+¦¦©+« ¦¦+÷) %s %d", AccountID, __FILE__, __LINE__);
				return 1;
			}
		}
		else
		{
			LogAddC(2, "%s] +·+Õ +íÀ» %s %d", CharName, __FILE__, __LINE__);
			return 1;
		}
	}
	else
	{
		LogAddC(2, "%s] +·+Õ +íÀ» %s %d", AccountID, __FILE__, __LINE__);
		return 1;
	}
	return 1;
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
	char szName[11];
	char szId[11];

	szId[10] = 0;
	memcpy(szId, lpMsg->AccountID, 0xAu);

	if (strlen(szId) && (strlen(szId) <= 0xA))
	{
		szName[10] = 0;
		memcpy(szName, lpMsg->Name, 0xAu);

		if (strlen(szName) && (strlen(szName) <= 0xA))
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
				LogAddC(2, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				iReturnValue = 1;
			}
			this->m_DBQuery.Clear();
			return iReturnValue;
		}
		else
		{
			//LogAddC(2, "%s] Insert ߡׯ %s %d", szName, __FILE__, __LINE__);
			LogAddC(2, "%s] Insert %s %d", szName, __FILE__, __LINE__);
			return 1;
		}
	}
	//LogAddC(2, "%s] Insert ߡׯ %s %d", szId, __FILE__, __LINE__);
	LogAddC(2, "%s] Insert %s %d", szId, __FILE__, __LINE__);
	return 1;
}