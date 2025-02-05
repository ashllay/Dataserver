#include "StdAfx.h"
#include "ChaosCastleFinalDBSet.h"

ChaosCastleFinalDBSet::ChaosCastleFinalDBSet()
{
}

ChaosCastleFinalDBSet::~ChaosCastleFinalDBSet()
{
}

BOOL ChaosCastleFinalDBSet::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("ChaosCastleFinalDBSet ODBC Connect Fail");
	return 0;
}

int ChaosCastleFinalDBSet::ReqCCFRanking(_stCCFRankingInfo RankingInfo[50], int CCFType, char* rCount, int RankType)
{
	CString qSql;
	int Count = 0;
	//int nRet = 0;

	if (RankType == 1)
	{
		qSql.Format("WZ_ChaosCastleFinal_GetRank_r %d", CCFType);
	}
	else
	{
		qSql.Format("WZ_ChaosCastleFinal_GetRank %d", CCFType);
	}

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		bool bReConnect = false;
		m_DBQuery.PrintDiag(bReConnect);
		LogAddC(2, "Error WZ_CCF_GET_RANKLIST m_DBQuery.Exec %s %d", __FILE__, __LINE__);
		m_DBQuery.Clear();
		return -1;
	}

	while (SQL_VALID_DATA(m_DBQuery.Fetch()) == TRUE)
	{
		RankingInfo[Count].byRank = m_DBQuery.GetInt("mRank");
		m_DBQuery.GetStr("mName", RankingInfo[Count].szCharName);
		RankingInfo[Count].nPoint = m_DBQuery.GetInt("mPoint");

		Count++;

		if (Count >= 50)
		{
			break;
		}
	}

	*rCount = Count;
	m_DBQuery.Clear();
	return 0;
}

void ChaosCastleFinalDBSet::Save_CCF_Point(char* Name, int nPoint, int nCCFType)
{
	CString qSql;

	qSql.Format("WZ_ChaosCastleFinal_Save '%s', %d, %d", Name, nPoint, nCCFType);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L1 [ChaosCastleFinal] [WZ_ChaosCastleFinal_Save] NAME:%s, Point:%d ,CCFType:%d ", Name, nPoint, nCCFType);
	}

	short sqlRet = m_DBQuery.Fetch();

	if (sqlRet == SQL_NO_DATA || sqlRet == SQL_NULL_DATA)
	{
		LogAddTD("Error-L2 [ChaosCastleFinal] [WZ_ChaosCastleFinal_Save] %d, %s , %d", sqlRet, __FILE__, __LINE__);
	}

	m_DBQuery.Clear();
}


int ChaosCastleFinalDBSet::CCFRankRenew(char byCCFType)
{
	CString qSql;

	if (this->m_DBQuery.IsConnected())
	{
		qSql.Format("WZ_ChaosCastleFinal_Renew %d", byCCFType);
		if (this->m_DBQuery.Exec(qSql))
		{
			this->m_DBQuery.Clear();
			return 0;
		}
		LogAddTD("Error-L1 [ChaosCastleFinalDBSet][WZ_ChaosCastleFinal_Renew]");
		return -1;
	}
	LogAddTD("[UBF] this->m_DBQuery.IsConnected: FALSE");
	return -1;
}


void ChaosCastleFinalDBSet::GetPermission(char* Name, int nCCFType, int* nReturn)
{
	CString qSql;

	qSql.Format("WZ_ChaosCastleFinal_GetPermission  '%s' , %d", Name, nCCFType);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_ChaosCastleFinal_GetPermission][A1] %s %d ", Name, nCCFType);
		return;
	}

	short sqlRet = m_DBQuery.Fetch();

	if (sqlRet == SQL_NO_DATA || sqlRet == SQL_NULL_DATA)
	{
		m_DBQuery.Clear();
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_ChaosCastleFinal_GetPermission][A2] %s %d Return %d,%s,%d ", Name, nCCFType, sqlRet, __FILE__, __LINE__);
		return;
	}

	*nReturn = m_DBQuery.GetInt(1);

	if (*nReturn == -1)
	{
		LogAddTD("error-L3 : [ChaosCastleFinalDBSet] WZ_ChaosCastleFinal_GetPermission #3 %d %s %d", sqlRet, __FILE__, __LINE__);
	}

	m_DBQuery.Clear();
}


int ChaosCastleFinalDBSet::Save_ChaosCastle_KillPoint(char* CharName, int nPoint, int CastleIndex, int* Result, int* CurrentPoint, int* TotalPoint)
{
	char mCharName[MAX_IDSTRING + 1] = { 0 };

	CString qSql;

	memcpy(mCharName, CharName, MAX_IDSTRING);
	if (strlen(mCharName) <= 0 || strlen(mCharName) > MAX_IDSTRING)
	{
		LogAddC(2, "%s] 로드 에러 %s %d", mCharName, __FILE__, __LINE__);
		return 0;
	}

	qSql.Format("EXEC WZ_ChaosCastle_SaveKillPoint '%s', %d ,%d ", CharName, nPoint, CastleIndex);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][Save_ChaosCastle_KillPoint] [%s] KillPoint:%d CastleIndex :%d ", mCharName, nPoint, CastleIndex);
		m_DBQuery.Clear();
		return 0;
	}

	short sqlRet = m_DBQuery.Fetch();

	if (sqlRet == SQL_NO_DATA || sqlRet == SQL_NULL_DATA)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][Save_ChaosCastle_KillPoint] [%s] nPoint:%d CastleIndex: %d Return %d,%s,%d ", CharName, nPoint, CastleIndex, sqlRet, __FILE__, __LINE__);
		m_DBQuery.Clear();
		return 0;
	}

	*Result = m_DBQuery.GetInt("Result");
	*CurrentPoint = m_DBQuery.GetInt("CurrentPoint");
	*TotalPoint = m_DBQuery.GetInt("TotalPoint");
	m_DBQuery.Clear();
	return 1;
}

int ChaosCastleFinalDBSet::GetUBFAccountUserInfo(char* mAccountID, char* mCharName, int ServerCode, int ServerType, PMSG_ANS_UBF_ACCOUNT_USERINFO* lpMsg)
{

	char CharName[MAX_IDSTRING + 1] = { 0 };
	char AccountID[MAX_IDSTRING + 1] = { 0 };

	CString qSql;

	memcpy(AccountID, mAccountID, MAX_IDSTRING);
	if (strlen(AccountID) <= 0 || strlen(AccountID) > MAX_IDSTRING)
	{
		LogAddC(2, "%s] 로드 에러 %s %d", AccountID, __FILE__, __LINE__);
		return 0;
	}

	memcpy(CharName, mCharName, MAX_IDSTRING);
	if (strlen(CharName) <= 0 || strlen(CharName) > MAX_IDSTRING)
	{
		LogAddC(2, "%s] 로드 에러 %s %d", CharName, __FILE__, __LINE__);
		return 0;
	}

	qSql.Format("EXEC WZ_UnityBattleFieldAccountUserInfoSelect_r '%s', '%s', %d, %d",
		AccountID,
		CharName,
		ServerCode,
		ServerType);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldAccountUserInfoSelect_r] [%s][%s] ServerCode:%d, ServerType:%d ", AccountID, CharName, ServerCode, ServerType);
		m_DBQuery.Clear();
		return 0;
	}

	short sqlRet = m_DBQuery.Fetch();

	if (sqlRet == SQL_NO_DATA)
	{
		LogAddTD("[CCF][WZ_UnityBattleFieldAccountUserInfoSelect_r] No Result Not Error [%s][%s]ServerCode:%d Return %d,%s,%d ", AccountID, mCharName, ServerCode, sqlRet, __FILE__, __LINE__);
		m_DBQuery.Clear();
		return 0;
	}

	if (sqlRet == SQL_NULL_DATA)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldAccountUserInfoSelect_r] [%s][%s]ServerCode:%d Return %d,%s,%d ", AccountID, mCharName, ServerCode, sqlRet, __FILE__, __LINE__);
		m_DBQuery.Clear();
		return 0;
	}

	lpMsg->btRegisterState = m_DBQuery.GetInt("RegisterState");
	lpMsg->btRegisterMonth = m_DBQuery.GetInt("RegisterMonth");
	lpMsg->btRegisterDay = m_DBQuery.GetInt("RegisterDay");
	m_DBQuery.Clear();
	return 1;
}



int ChaosCastleFinalDBSet::RegisterUBFAccountUser(char* mAccountID, char* mCharName, char* mUBFName, int ServerCode, int RegisterState, int RegisterMonth, int RegisterDay, BYTE* Result, WORD* LeftSecond)
{
	char UBFName[MAX_IDSTRING + 1] = { 0 };
	char CharName[MAX_IDSTRING + 1] = { 0 };
	char AccountID[MAX_IDSTRING + 1] = { 0 };

	CString qSql;

	memcpy(AccountID, mAccountID, MAX_IDSTRING);
	if (strlen(AccountID) <= 0 || strlen(AccountID) > MAX_IDSTRING)
	{
		LogAddC(2, "%s] 로드 에러 %s %d", AccountID, __FILE__, __LINE__);
		return 0;
	}

	memcpy(CharName, mCharName, MAX_IDSTRING);
	if (strlen(CharName) <= 0 || strlen(CharName) > MAX_IDSTRING)
	{
		LogAddC(2, "%s] 로드 에러 %s %d", __FILE__, __LINE__);
		return 0;
	}

	memcpy(UBFName, mUBFName, MAX_IDSTRING);
	if (strlen(UBFName) <= 0 || strlen(UBFName) > MAX_IDSTRING)
	{
		LogAddC(2, "%s] 로드 에러 %s %d", UBFName, __FILE__, __LINE__);
		return 0;
	}

	qSql.Format(
		"EXEC WZ_UnityBattleFieldAccountUserAdd_r '%s', '%s', %d, %d, %d, %d",
		AccountID,
		CharName,
		ServerCode,
		RegisterState,
		RegisterMonth,
		RegisterDay
	);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldAccountUserAdd_r] '%s', '%s', %d, %d, %d, %d ", AccountID, CharName, ServerCode, RegisterState, RegisterMonth, RegisterDay);
		m_DBQuery.Clear();
		return 0;
	}

	short sqlRet = m_DBQuery.Fetch();

	if (sqlRet == SQL_NO_DATA || sqlRet == SQL_NULL_DATA)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldAccountUserAdd_r] [%s][%s] sqlReturn:%d,%s,%d ", AccountID, CharName, sqlRet, __FILE__, __LINE__);
		m_DBQuery.Clear();
		return 0;
	}

	*Result = m_DBQuery.GetInt("Result");
	*LeftSecond = m_DBQuery.GetInt("Left_Second");
	m_DBQuery.Clear();
	return 1;

}


int ChaosCastleFinalDBSet::CopyUBFAccountUser(char* szAccountID, char* szName, short GameServerCode, BYTE* subResult)
{
	char CharName[MAX_IDSTRING + 1] = { 0 };
	char AccountID[MAX_IDSTRING + 1] = { 0 };

	CString qSql;

	memcpy(AccountID, szAccountID, MAX_IDSTRING);
	if (strlen(AccountID) <= 0 || strlen(AccountID) > MAX_IDSTRING)
	{
		LogAddC(2, "%s] 로드 에러 %s %d", AccountID, __FILE__, __LINE__);
		return 0;
	}

	memcpy(CharName, szAccountID, MAX_IDSTRING);
	if (strlen(CharName) <= 0 || strlen(CharName) > MAX_IDSTRING)
	{
		LogAddC(2, "%s] 로드 에러 %s %d", CharName, __FILE__, __LINE__);
		return 0;
	}

	qSql.Format("EXEC WZ_UnityBattleFieldAccountUserDataCopy_r '%s', '%s',%d", AccountID, CharName, GameServerCode);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldAccountUserDataCopy_r] '%s', '%s'", AccountID, CharName);
		m_DBQuery.Clear();
		return 0;
	}

	short sqlRet = m_DBQuery.Fetch();

	if (sqlRet == SQL_NO_DATA || sqlRet == SQL_NULL_DATA)
	{
		m_DBQuery.Clear();
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldAccountUserDataCopy] [%s][%s] sqlReturn:%d,%s,%d ", AccountID, CharName, sqlRet, __FILE__, __LINE__);
		return 0;
	}

	*subResult = m_DBQuery.GetInt(1);
	m_DBQuery.Clear();
	return 1;
}


int ChaosCastleFinalDBSet::CopyUBFAccountUserPromotionMode(char* szAccountID, char* szName, short GameServerCode, BYTE* subResult)
{
	char CharName[MAX_IDSTRING + 1] = { 0 };
	char AccountID[MAX_IDSTRING + 1] = { 0 };

	CString qSql;

	memcpy(AccountID, szAccountID, MAX_IDSTRING);
	if (strlen(AccountID) <= 0 || strlen(AccountID) > MAX_IDSTRING)
	{
		LogAddC(2, "%s] 로드 에러 %s %d", AccountID, __FILE__, __LINE__);
		return 0;
	}

	memcpy(CharName, szName, MAX_IDSTRING);
	if (strlen(CharName) <= 0 || strlen(CharName) > MAX_IDSTRING)
	{
		LogAddC(2, "%s] 로드 에러 %s %d", CharName, __FILE__, __LINE__);
		return 0;
	}

	qSql.Format("EXEC WZ_UnityBattleFieldAccountUserDataCopy_Promotion '%s', '%s',%d",
		AccountID,
		CharName,
		GameServerCode);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L3 [CCFDBSet][WZ_UnityBattleFieldAccountUserDataCopy_Promotion] '%s', '%s'", AccountID, CharName);
		m_DBQuery.Clear();
		return 0;
	}

	short sqlRet = m_DBQuery.Fetch();

	if (sqlRet == SQL_NO_DATA || sqlRet == SQL_NULL_DATA)
	{
		m_DBQuery.Clear();
		LogAddTD("Error-L3 [CCFDBSet][WZ_UnityBattleFieldAccountUserDataCopy_Promotion] [%s][%s] sqlReturn:%d,%s,%d ", AccountID, CharName, sqlRet, __FILE__, __LINE__);
		return 0;
	}

	*subResult = m_DBQuery.GetInt(1);
	m_DBQuery.Clear();
	return 1;
}


int ChaosCastleFinalDBSet::GetWinAllRewardInfoOfUBF(char* szCharName, int nServerCode, char btServerKind, char btContentsType, PMSG_ANS_UBF_GET_REWARD* pMsg)
{
	int result;
	short sqlReturn;
	CString qSql;
	char szName[MAX_IDSTRING + 1] = { 0 };

	memcpy(szName, szCharName, MAX_IDSTRING);

	if (strlen(szName) && (strlen(szName) <= MAX_IDSTRING))
	{
		qSql.Format("EXEC WZ_All_GetAndUpdate_RewardInfoOfUnityBattleField %d, '%s', %d, %d ", btServerKind, szName, nServerCode, btContentsType);
		if (this->m_DBQuery.Exec(qSql))
		{
			sqlReturn = this->m_DBQuery.Fetch();
			if (sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
			{
				pMsg->btResult = this->m_DBQuery.GetInt("Result");
				pMsg->btContentsType = this->m_DBQuery.GetInt("ContentsType");
				pMsg->btArrayCCF_Reward[0] = this->m_DBQuery.GetInt("CCF_Reward_PreLeague");
				pMsg->btArrayCCF_Reward[1] = this->m_DBQuery.GetInt("CCF_Reward_SemiLeague");
				pMsg->btArrayCCF_Reward[2] = this->m_DBQuery.GetInt("CCF_Reward_FinalLeague");
				pMsg->btArrayCCF_Reward[3] = this->m_DBQuery.GetInt("CCF_Reward_LastWinner");
				pMsg->btArrayDSF_Reward[0] = this->m_DBQuery.GetInt("DSF_Reward_PreLeague");
				pMsg->btArrayDSF_Reward[1] = this->m_DBQuery.GetInt("DSF_Reward_SemiLeague");
				pMsg->btArrayDSF_Reward[2] = this->m_DBQuery.GetInt("DSF_Reward_FinalLeague");
				pMsg->btArrayDSF_Reward[3] = this->m_DBQuery.GetInt("DSF_Reward_LastWinner");
				pMsg->btArrayCCN_Reward[0] = this->m_DBQuery.GetInt("CC_Reward_General");
				pMsg->btArrayCCN_Reward[1] = this->m_DBQuery.GetInt("CC_Reward_LastWinner");
				pMsg->btArrayDSN_Reward[0] = this->m_DBQuery.GetInt("DSN_Reward_Type_1");
				pMsg->btArrayDSN_Reward[1] = this->m_DBQuery.GetInt("DSN_Reward_Type_2");
				pMsg->btArrayDSN_Reward[2] = this->m_DBQuery.GetInt("DSN_Reward_Type_3");
				pMsg->btArrayDSN_Reward[3] = this->m_DBQuery.GetInt("DSN_Reward_Type_4");
				pMsg->btArrayDSN_Reward[4] = this->m_DBQuery.GetInt("DSN_Reward_Type_5");
				pMsg->btArrayDSN_Reward[5] = this->m_DBQuery.GetInt("DSN_Reward_Type_6");
				pMsg->btArrayDSN_Reward[6] = this->m_DBQuery.GetInt("DSN_Reward_Type_7");
				pMsg->btArrayDSN_Reward[7] = this->m_DBQuery.GetInt("DSN_Reward_Type_8");
				pMsg->btArrayDSN_Reward[8] = this->m_DBQuery.GetInt("DSN_Reward_Type_9");
				pMsg->btArrayDSN_Reward[9] = this->m_DBQuery.GetInt("DSN_Reward_Type_10");
				pMsg->btArrayDSN_Reward[10] = this->m_DBQuery.GetInt("DSN_Reward_Type_11");
				pMsg->btArrayDSN_Reward[11] = this->m_DBQuery.GetInt("DSN_Reward_Type_12");
				pMsg->btArrayDSN_Reward[12] = this->m_DBQuery.GetInt("DSN_Reward_Type_13");
				pMsg->btArrayDSN_Reward[13] = this->m_DBQuery.GetInt("DSN_Reward_Type_14");
				this->m_DBQuery.Clear();
				result = 1;
			}
			else
			{
				LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_All_GetAndUpdate_RewardInfoOfUnityBattleField] [%s][%d] Return %d,%s,%d ",
					szName, nServerCode, sqlReturn, __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				result = 0;
			}
		}
		else
		{
			LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_All_GetAndUpdate_RewardInfoOfUnityBattleField] [ServerKind:%d][%s][%d][%d]",
				btServerKind, szName, nServerCode, btContentsType);
			this->m_DBQuery.Clear();
			result = 0;
		}
	}
	else
	{
		LogAddC(2, "%s] 로드 에러 %s %d", szName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


int ChaosCastleFinalDBSet::SetReceivedWinnerItemOfUBF(char* szCharName, int nServerCode, char btReceived, char* SubResult)
{
	int result; // eax
	short sqlReturn;
	CString qSql;
	char szName[MAX_IDSTRING + 1] = { 0 };

	if (this->m_DBQuery.IsConnected())
	{
		memcpy(szName, szCharName, MAX_IDSTRING);
		if (strlen(szName) && (strlen(szName) <= MAX_IDSTRING))
		{
			qSql.Format("EXEC WZ_UnityBattleField_SetReceivedWinnerItem_r '%s', %d, %d", szName, nServerCode, btReceived);
			if (this->m_DBQuery.Exec(qSql))
			{
				sqlReturn = this->m_DBQuery.Fetch();
				if (sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
				{
					*SubResult = this->m_DBQuery.GetInt(1);
					this->m_DBQuery.Clear();
					result = 1;
				}
				else
				{
					LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleField_SetReceivedWinnerItem_r] [%s][%d] Return %d,%s,%d ",
						szName, nServerCode, sqlReturn, __FILE__, __LINE__);
					this->m_DBQuery.Clear();
					result = 0;
				}
			}
			else
			{
				LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleField_SetReceivedWinnerItem_r] [%s][%d][%d]", szName, nServerCode, btReceived);
				this->m_DBQuery.Clear();
				result = 0;
			}
		}
		else
		{
			LogAddC(2, "%s] 로드 에러 %s %d", szName, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		LogAddTD("[UBF] this->m_DBQuery.IsConnected: FALSE");
		*SubResult = 0;
		result = 0;
	}
	return result;
}


int ChaosCastleFinalDBSet::SetCancelToJionUnityBattlefiled(char* szAccountID, char* szName, short GameServerCode, char* subResult)
{
	int result;
	short sqlReturn;
	CString qSql;
	char szCharName[MAX_IDSTRING + 1] = { 0 };
	char szId[MAX_IDSTRING + 1] = { 0 };


	if (this->m_DBQuery.IsConnected())
	{
		memcpy(szId, szAccountID, MAX_IDSTRING);
		memcpy(szCharName, szName, MAX_IDSTRING);

		if (strlen(szId) && (strlen(szId) <= 0xA))
		{
			if (strlen(szCharName) && (strlen(szCharName) <= 0xA))
			{
				qSql.Format("EXEC WZ_UnityBattleFieldCancelToJoin_r '%s','%s',%d", szId, szCharName, GameServerCode);
				if (this->m_DBQuery.Exec(qSql))
				{
					sqlReturn = this->m_DBQuery.Fetch();
					if (sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
					{
						*subResult = this->m_DBQuery.GetInt(1);
						this->m_DBQuery.Clear();
						result = 1;
					}
					else
					{
						LogAddTD("Error-L3 [ChaosCastleFinalDBSet][SetCancelToJionUnityBattlefiled] [%s][%d] Return %d,%s,%d ",
							szName, GameServerCode, sqlReturn, __FILE__, __LINE__);
						this->m_DBQuery.Clear();
						result = 0;
					}
				}
				else
				{
					LogAddTD("Error-L3 [UBF][WZ_UnityBattleFieldCancelToJoin_r] [%s][%s][%d]", szId, szCharName, GameServerCode);
					this->m_DBQuery.Clear();
					result = 0;
				}
			}
			else
			{
				LogAddC(2, "%s] 로드 에러 %s %d", szId, __FILE__, __LINE__);
				result = 0;
			}
		}
		else
		{
			LogAddC(2, "%s] 로드 에러 %s %d", szId, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		LogAddTD("[UBF] this->m_DBQuery.IsConnected: FALSE");
		*subResult = 0;
		result = 0;
	}
	return result;
}


char ChaosCastleFinalDBSet::DeleteCharacterUnityBattlefiled(char* szAccountID, char* szName, short GameServerCode)
{
	char CharName[MAX_IDSTRING + 1] = { 0 };
	char AccountID[MAX_IDSTRING + 1] = { 0 };

	CString qSql;

	memcpy(AccountID, szAccountID, MAX_IDSTRING);
	if (strlen(AccountID) <= 0 || strlen(AccountID) > MAX_IDSTRING)
	{
		LogAddC(2, "%s] 로드 에러 %s %d", AccountID, __FILE__, __LINE__);
		return 0;
	}

	memcpy(CharName, szName, MAX_IDSTRING);
	if (strlen(CharName) <= 0 || strlen(CharName) > MAX_IDSTRING)
	{
		LogAddC(2, "%s] 로드 에러 %s %d", AccountID, __FILE__, __LINE__);
		return 0;
	}

	qSql.Format("EXEC WZ_UnityBattleFieldCancelToJoin_r '%s','%s',%d", AccountID, CharName, GameServerCode);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L3 [UBF][WZ_UnityBattleFieldCancelToJoin_r] [%s][%s][%d]", AccountID, CharName, GameServerCode);
		m_DBQuery.Clear();
		return 0;
	}

	short sqlRet = m_DBQuery.Fetch();

	if (sqlRet == SQL_NO_DATA || sqlRet == SQL_NULL_DATA)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][SetCancelToJionUnityBattlefiled] [%s][%d] Return %d,%s,%d ", szName, GameServerCode, sqlRet, __FILE__, __LINE__);
		m_DBQuery.Clear();
		return 0;
	}

	char Result = m_DBQuery.GetInt(1);
	m_DBQuery.Clear();
	return Result;
}

int ChaosCastleFinalDBSet::GetRealNameAndServerCode(char* szUBFName, PMSG_ANS_GET_UBF_REAL_NAME* pMsg)
{
	int result;
	short sqlReturn;
	CString qSql;
	char szCahrUBFName[MAX_IDSTRING + 1] = { 0 };

	if (this->m_DBQuery.IsConnected())
	{
		memcpy(szCahrUBFName, szUBFName, MAX_IDSTRING);
		if (strlen(szCahrUBFName) && (strlen(szCahrUBFName) <= MAX_IDSTRING))
		{
			qSql.Format("EXEC WZ_UnityBattleFieldGetRealName_r '%s'",
				szCahrUBFName);
			if (this->m_DBQuery.Exec(qSql))
			{
				sqlReturn = this->m_DBQuery.Fetch();
				if (sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
				{
					this->m_DBQuery.GetStr("Name", pMsg->szRealName);
					pMsg->iServerCode = this->m_DBQuery.GetInt("ServerCode");
					memcpy(pMsg->szUBFName, szCahrUBFName, MAX_IDSTRING);
					this->m_DBQuery.Clear();
					result = 1;
				}
				else
				{
					LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldGetRealName_r] [%s] Return %d,%s,%d ", szCahrUBFName, sqlReturn, __FILE__, __LINE__);
					this->m_DBQuery.Clear();
					result = 0;
				}
			}
			else
			{
				LogAddTD("Error-L3 [UBF][WZ_UnityBattleFieldGetRealName_r] [%s]", szCahrUBFName);
				this->m_DBQuery.Clear();
				result = 0;
			}
		}
		else
		{
			LogAddC(2, "%s] 로드 에러 %s %d", szUBFName, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		LogAddTD("[UBF] this->m_DBQuery.IsConnected: FALSE");
		result = 0;
	}
	return result;
}

int ChaosCastleFinalDBSet::GetRealNameAndServerCode(char* szUBFName, char* szRealName, int* ServerCode, int IsUBFServer)
{
	int result;
	short sqlReturn;
	CString qSql;
	char szCahrUBFName[MAX_IDSTRING + 1] = { 0 };


	if (this->m_DBQuery.IsConnected())
	{
		memcpy(szCahrUBFName, szUBFName, MAX_IDSTRING);
		if (strlen(szCahrUBFName) && (strlen(szCahrUBFName) <= MAX_IDSTRING))
		{
			qSql.Format("EXEC WZ_UnityBattleFieldGetRealName_r '%s'",
				szCahrUBFName);
			if (this->m_DBQuery.Exec(qSql))
			{
				sqlReturn = this->m_DBQuery.Fetch();
				if (sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
				{
					this->m_DBQuery.GetStr("Name", szRealName);
					*ServerCode = this->m_DBQuery.GetInt("ServerCode");
					this->m_DBQuery.Clear();
					result = 1;
				}
				else
				{
					LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldGetRealName_r] [%s] Return %d,%s,%d ",
						szCahrUBFName, sqlReturn, __FILE__, __LINE__);
					this->m_DBQuery.Clear();
					result = 0;
				}
			}
			else
			{
				LogAddTD("Error-L3 [UBF][WZ_UnityBattleFieldGetRealName_r] [%s]", szCahrUBFName);
				this->m_DBQuery.Clear();
				result = 0;
			}
		}
		else
		{
			LogAddC(2, "%s] 로드 에러 %s %d", szUBFName, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		LogAddTD("[UBF] this->m_DBQuery.IsConnected: FALSE");
		result = 0;
	}
	return result;
}


int ChaosCastleFinalDBSet::SetRewardInfoOfUnityBattleField(char* btResult, char btServerKind, char* szAccountID, char* szName, short wServerCode, char btContentsType, char btSubContentsType, int iItemCode, char btItemCount, char btTakeState)
{
	__int16 sqlReturn;
	CString qSql;

	char szId[MAX_IDSTRING + 1] = { 0 };
	char szCahrName[MAX_IDSTRING + 1] = { 0 };

	szId[10] = 0;
	memcpy(szId, szAccountID, MAX_IDSTRING);
	szCahrName[10] = 0;
	memcpy(szCahrName, szName, MAX_IDSTRING);
	strlen(szCahrName);

	if (strlen(szCahrName) && strlen(szCahrName) <= MAX_IDSTRING && strlen(szId) && strlen(szId) <= MAX_IDSTRING)
	{
		qSql.Format(
			"EXEC WZ_Set_RewardInfoOfUnityBattleField %d, '%s','%s', %d, %d, %d,% d, %d, %d ",
			btServerKind,
			szId,
			szCahrName,
			wServerCode,
			btContentsType,
			btSubContentsType,
			iItemCode,
			btItemCount,
			btTakeState);

		if (this->m_DBQuery.Exec(qSql))
		{
			sqlReturn = this->m_DBQuery.Fetch();
			if (sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
			{
				*btResult = this->m_DBQuery.GetInt("Result");
				this->m_DBQuery.Clear();
				return 1;
			}
			else
			{
				LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_Set_RewardInfoOfUnityBattleField] [%s][%s][%d][%d] Return %d,%s,%d ", szId, szCahrName, btContentsType, btTakeState, sqlReturn, __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				return 0;
			}
		}
		else
		{
			LogAddTD("Error-L3 [UBF][WZ_Set_RewardInfoOfUnityBattleField] [%s][%s][%d][%d]", szId, szCahrName, btContentsType, btTakeState);
			this->m_DBQuery.Clear();
			return 0;
		}
	}
	LogAddC(2, "%s] 로드 에러 %s %d", szCahrName, __FILE__, __LINE__);
	return 0;
}