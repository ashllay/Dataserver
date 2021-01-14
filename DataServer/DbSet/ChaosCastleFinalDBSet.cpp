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
	if (m_Query.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass) == FALSE)
	{
		MsgBox("ChaosCastleFinalDBSet ODBC Connect Fail");
		return FALSE;
	}
		
	return TRUE;
}

BOOL ChaosCastleFinalDBSet::ReqCCFRanking(_stCCFRankingInfo* CCFRankingInfo, int nCCFtype, BYTE& btUserCount, int nServerCategory)
{
	int iCnt = 0;

	if (m_Query.IsConnected() == FALSE)
	{
		LogAddTD("[UBF] m_Query.IsConnected: FALSE");
		return -1;
	}

	CString szquery;

	if (nServerCategory == 1)
	{
		szquery.Format("WZ_ChaosCastleFinal_GetRank_r %d", nCCFtype);
	}

	else
	{
		szquery.Format("WZ_ChaosCastleFinal_GetRank %d", nCCFtype);
	}

	if (m_Query.Exec(szquery) == FALSE)
	{
		LogAddC(LOGC_RED, "Error WZ_CCF_GET_RANKLIST m_Query.Exec %s %d", __FILE__, __LINE__);
		m_Query.Clear();
		return -1;
	}

	SQLRETURN sqlRetrun = m_Query.Fetch();

	while (sqlRetrun != SQL_NO_DATA && sqlRetrun != SQL_NULL_DATA)
	{
		CCFRankingInfo[iCnt].byRank = m_Query.GetInt("mRank");
		m_Query.GetStr("mName", CCFRankingInfo[iCnt].szCharName);
		CCFRankingInfo[iCnt].nPoint = m_Query.GetInt("mPoint");
		iCnt++;

		if (iCnt >= 50)
		{
			break;
		}

		sqlRetrun = m_Query.Fetch();
	}

	btUserCount = iCnt;
	m_Query.Clear();
	return FALSE;
}

void ChaosCastleFinalDBSet::Save_CCF_Point(char *Name, int nPoint, int nCCFType)
{
	if (m_Query.IsConnected() == FALSE)
	{
		LogAddTD("[UBF] m_Query.IsConnected: FALSE");
		return;
	}

	CString qSql;
	qSql.Format("WZ_ChaosCastleFinal_Save '%s', %d, %d",Name,nPoint,nCCFType);

	if (m_Query.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L1 [ChaosCastleFinal] [WZ_ChaosCastleFinal_Save] NAME:%s, Point:%d ,CCFType:%d ", Name, nPoint, nCCFType);
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		LogAddTD("Error-L2 [ChaosCastleFinal] [WZ_ChaosCastleFinal_Save] %d, %s , %d", sqlReturn, __FILE__, __LINE__);
	}

	m_Query.Clear();
}

BOOL ChaosCastleFinalDBSet::CCFRankRenew(BYTE byCCFType)
{
	int result;
	CString q;

	if (m_Query.IsConnected() == FALSE)
	{
		LogAddTD("[UBF] m_Query.IsConnected: FALSE");
		return -1;
	}

	CString q;
	q.Format("WZ_ChaosCastleFinal_Renew %d", byCCFType);

	if (m_Query.Exec(q) == FALSE)
	{
		LogAddTD("Error-L1 [ChaosCastleFinalDBSet][WZ_ChaosCastleFinal_Renew]");
		return -1;
	}

	m_Query.Clear();
	return FALSE;
}

void ChaosCastleFinalDBSet::GetPermission(char* Name, int nCCFType, int& nReturn)
{
	if (m_Query.IsConnected() == FALSE)
	{
		LogAddTD("[UBF] m_Query.IsConnected: FALSE");
		nReturn = 1;
		return;
	}

	CString qSql;
	qSql.Format("WZ_ChaosCastleFinal_GetPermission  '%s' , %d", Name, nCCFType);

	if (m_Query.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_ChaosCastleFinal_GetPermission][A1] %s %d ", Name, nCCFType);
		return;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		m_Query.Clear();
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_ChaosCastleFinal_GetPermission][A2] %s %d Return %d,%s,%d ", Name, nCCFType, sqlReturn, __FILE__, __LINE__);
		return;
	}

	nReturn = m_Query.GetInt(1);

	if (nReturn == -1)
	{
		LogAddTD("error-L3 : [ChaosCastleFinalDBSet] WZ_ChaosCastleFinal_GetPermission #3 %d %s %d", sqlReturn, __FILE__, __LINE__);
	}

	m_Query.Clear();
}


BOOL ChaosCastleFinalDBSet::Save_ChaosCastle_KillPoint(char* szName, int nPoint, int CastleIndex, int& SubResult, int& CurrntPoint, int& TotalPoint)
{
	if (m_Query.IsConnected() == FALSE)
	{
		LogAddTD("[UBF] m_Query.IsConnected: FALSE");
		SubResult = -1;
		CurrntPoint = 0;
		TotalPoint = 0;
		return FALSE;
	}

	char szCharName[MAX_IDSTRING + 1];
	szCharName[MAX_IDSTRING] = '\0';
	memcpy(szCharName, szName, MAX_IDSTRING);

	if (strlen(szCharName) == 0 || strlen(szCharName) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szCharName, __FILE__, __LINE__);
		return FALSE;
	}

	CString qSql;
	qSql.Format("EXEC WZ_ChaosCastle_SaveKillPoint '%s', %d ,%d ", szName, nPoint, CastleIndex);

	if (m_Query.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][Save_ChaosCastle_KillPoint] [%s] KillPoint:%d CastleIndex :%d ", szCharName, nPoint, CastleIndex);
		m_Query.Clear();
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][Save_ChaosCastle_KillPoint] [%s] nPoint:%d CastleIndex: %d Return %d,%s,%d ", szName, nPoint, CastleIndex, sqlReturn, __FILE__, __LINE__);
		m_Query.Clear();
		return FALSE;
	}

	SubResult = m_Query.GetInt("Result");
	CurrntPoint = m_Query.GetInt("CurrentPoint");
	TotalPoint = m_Query.GetInt("TotalPoint");
	
	m_Query.Clear();
	return TRUE;
}

BOOL ChaosCastleFinalDBSet::GetUBFAccountUserInfo(char* szAccountID, char* szName, int nServerCode, BOOL IsUnityBattleFieldServer, LPPMSG_ANS_UBF_ACCOUNT_USERINFO pMsg)
{
	if (m_Query.IsConnected() == FALSE)
	{
		LogAddTD("[UBF] m_Query.IsConnected: FALSE");
		pMsg->btRegisterState = 0;
		pMsg->btRegisterMonth = 0;
		pMsg->btRegisterDay = 0;
		return FALSE;
	}

	char szId[MAX_IDSTRING + 1];
	szId[MAX_IDSTRING] = '\0';
	memcpy(szId, szAccountID, MAX_IDSTRING);

	if (strlen(szId) == 0 || strlen(szId) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szId, __FILE__, __LINE__);
		return FALSE;
	}

	char szCharName[MAX_IDSTRING + 1];
	szCharName[MAX_IDSTRING] = '\0';
	memcpy(szCharName, szName, MAX_IDSTRING);

	if (strlen(szCharName) == 0 || strlen(szCharName) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szCharName, __FILE__, __LINE__);
		return FALSE;
	}

	CString qSql;
	qSql.Format("EXEC WZ_UnityBattleFieldAccountUserInfoSelect_r '%s', '%s', %d, %d", szAccountID, szName, nServerCode, IsUnityBattleFieldServer);

	if (m_Query.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldAccountUserInfoSelect_r] [%s][%s] ServerCode:%d, ServerType:%d ", szId, szCharName, nServerCode, IsUnityBattleFieldServer);
		m_Query.Clear();
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA)
	{
		LogAddTD("[CCF][WZ_UnityBattleFieldAccountUserInfoSelect_r] No Result Not Error [%s][%s]ServerCode:%d Return %d,%s,%d ", szId, szName, nServerCode, sqlReturn, __FILE__, __LINE__);
		m_Query.Clear();
		return FALSE;
	}

	if (sqlReturn == SQL_NULL_DATA)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldAccountUserInfoSelect_r] [%s][%s]ServerCode:%d Return %d,%s,%d ", szId, szName, nServerCode, sqlReturn, __FILE__, __LINE__);
		m_Query.Clear();
		return FALSE;
	}

	pMsg->btRegisterState = m_Query.GetInt("RegisterState");
	pMsg->btRegisterMonth = m_Query.GetInt("RegisterMonth");
	pMsg->btRegisterDay = m_Query.GetInt("RegisterDay");
	
	m_Query.Clear();
	return TRUE;
}

BOOL ChaosCastleFinalDBSet::RegisterUBFAccountUser(char* szAccountID, char* szName, char* szBattleName, int nServerCode, int nRegisterState, int nRegisterMonth, int nRegisterDay, BYTE& nResult, WORD& nLeftSec)
{
	if (m_Query.IsConnected() == FALSE)
	{
		LogAddTD("[UBF] m_Query.IsConnected: FALSE");
		nResult = -1;
		nLeftSec = 0;
		return FALSE;
	}

	char szId[MAX_IDSTRING + 1];
	szId[MAX_IDSTRING] = '\0';
	memcpy(szId, szAccountID, MAX_IDSTRING);

	if (strlen(szId) == 0 || strlen(szId) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szId, __FILE__, __LINE__);
		return FALSE;
	}

	char szCharName[MAX_IDSTRING + 1];
	szCharName[MAX_IDSTRING] = '\0';
	memcpy(szCharName, szName, MAX_IDSTRING);

	if (strlen(szCharName) == 0 || strlen(szCharName) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szCharName, __FILE__, __LINE__);
		return FALSE;
	}

	char szUBFName[MAX_IDSTRING + 1];
	szUBFName[MAX_IDSTRING] = '\0';
	memcpy(szUBFName, szBattleName, MAX_IDSTRING);

	if (strlen(szUBFName) == 0 || strlen(szUBFName) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szUBFName, __FILE__, __LINE__);
		return FALSE;
	}

	CString qSql;
	qSql.Format("EXEC WZ_UnityBattleFieldAccountUserAdd_r '%s', '%s', %d, %d, %d, %d", szId, szCharName, nServerCode, nRegisterState, nRegisterMonth, nRegisterDay);

	if (m_Query.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldAccountUserAdd_r] '%s', '%s', %d, %d, %d, %d ", szId, szCharName, nServerCode, nRegisterState, nRegisterMonth, nRegisterDay);
		m_Query.Clear();
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldAccountUserAdd_r] [%s][%s] sqlReturn:%d,%s,%d ", szId, szCharName, sqlReturn, __FILE__, __LINE__);
		m_Query.Clear();
		return FALSE;
	}

	nResult = m_Query.GetInt("Result");
	nLeftSec = m_Query.GetInt("Left_Second");
	
	m_Query.Clear();
	return TRUE;
}

BOOL ChaosCastleFinalDBSet::CopyUBFAccountUser(char* szAccountID, char* szName, WORD GameServerCode, BYTE& subResult)
{
	if (m_Query.IsConnected() == FALSE)
	{
		LogAddTD("[UBF] m_Query.IsConnected: FALSE");
		subResult = 0;
		return FALSE;
	}

	char szId[MAX_IDSTRING + 1];
	szId[MAX_IDSTRING] = '\0';
	memcpy(szId, szAccountID, MAX_IDSTRING);

	if (strlen(szId) == 0 || strlen(szId) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szId, __FILE__, __LINE__);
		return FALSE;
	}

	char szCharName[MAX_IDSTRING + 1];
	szCharName[MAX_IDSTRING] = '\0';
	memcpy(szCharName, szName, MAX_IDSTRING);

	if (strlen(szCharName) == 0 || strlen(szCharName) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szCharName, __FILE__, __LINE__);
		return FALSE;
	}

	CString qSql;
	qSql.Format("EXEC WZ_UnityBattleFieldAccountUserDataCopy_r '%s', '%s',%d", szId, szCharName, GameServerCode);

	if (m_Query.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldAccountUserDataCopy_r] '%s', '%s'", szId, szCharName);
		m_Query.Clear();
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		m_Query.Clear();
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldAccountUserDataCopy] [%s][%s] sqlReturn:%d,%s,%d ", szId, szCharName, sqlReturn, __FILE__, __LINE__);
		return FALSE;
	}

	subResult = m_Query.GetInt(1);
	
	m_Query.Clear();
	return TRUE;
}

BOOL ChaosCastleFinalDBSet::CopyUBFAccountUserPromotionMode(char* szAccountID, char* szName, WORD GameServerCode, BYTE& subResult)
{
	if (m_Query.IsConnected() == FALSE)
	{
		LogAddTD("[UBF] m_Query.IsConnected: FALSE");
		subResult = 0;
		return FALSE;
	}

	char szId[MAX_IDSTRING + 1];
	szId[MAX_IDSTRING] = '\0';
	memcpy(szId, szAccountID, MAX_IDSTRING);

	if (strlen(szId) == 0 || strlen(szId) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szId, __FILE__, __LINE__);
		return FALSE;
	}

	char szCharName[MAX_IDSTRING + 1];
	szCharName[MAX_IDSTRING] = '\0';
	memcpy(szCharName, szName, MAX_IDSTRING);

	if (strlen(szCharName) == 0 || strlen(szCharName) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szCharName, __FILE__, __LINE__);
		return FALSE;
	}

	CString qSql;
	qSql.Format("EXEC WZ_UnityBattleFieldAccountUserDataCopy_Promotion '%s', '%s',%d", szId, szCharName, GameServerCode);

	if (m_Query.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L3 [CCFDBSet][WZ_UnityBattleFieldAccountUserDataCopy_Promotion] '%s', '%s'", szId, szCharName);
		m_Query.Clear();
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		m_Query.Clear();
		LogAddTD("Error-L3 [CCFDBSet][WZ_UnityBattleFieldAccountUserDataCopy_Promotion] [%s][%s] sqlReturn:%d,%s,%d ", szId, szCharName, sqlReturn, __FILE__, __LINE__);
		return FALSE;
	}

	subResult = m_Query.GetInt(1);

	m_Query.Clear();
	return TRUE;
}

BOOL ChaosCastleFinalDBSet::GetWinAllRewardInfoOfUBF(char* szCharName, int nServerCode, BYTE btServerKind, BYTE btContentsType, LPPMSG_ANS_UBF_GET_REWARD pMsg)
{
	char szName[MAX_IDSTRING + 1];
	szName[MAX_IDSTRING] = '\0';
	memcpy(szName, szCharName, MAX_IDSTRING);

	if (strlen(szName) == 0 || strlen(szName) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szName, __FILE__, __LINE__);
		return FALSE;
	}

	CString qSql;
	qSql.Format("EXEC WZ_All_GetAndUpdate_RewardInfoOfUnityBattleField %d, '%s', %d, %d ", btServerKind, szName, nServerCode, btContentsType);

	if (m_Query.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_All_GetAndUpdate_RewardInfoOfUnityBattleField] [ServerKind:%d][%s][%d][%d]", btServerKind, szName, nServerCode, btContentsType);
		m_Query.Clear();
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_All_GetAndUpdate_RewardInfoOfUnityBattleField] [%s][%d] Return %d,%s,%d ", szName, nServerCode, sqlReturn, __FILE__, __LINE__);
		m_Query.Clear();
		return FALSE;
	}

	enum
	{
		REWARD_TYPE_1 = 0x0,
		REWARD_TYPE_2 = 0x1,
		REWARD_TYPE_3 = 0x2,
		REWARD_TYPE_4 = 0x3,
		REWARD_TYPE_5 = 0x4,
		REWARD_TYPE_6 = 0x5,
		REWARD_TYPE_7 = 0x6,
		REWARD_TYPE_8 = 0x7,
		REWARD_TYPE_9 = 0x8,
		REWARD_TYPE_10 = 0x9,
		REWARD_TYPE_11 = 0xA,
		REWARD_TYPE_12 = 0xB,
		REWARD_TYPE_13 = 0xC,
		REWARD_TYPE_14 = 0xD,
	};


	pMsg->btResult = m_Query.GetInt("Result");
	pMsg->btContentsType = m_Query.GetInt("ContentsType");

	pMsg->btArrayCCF_Reward[REWARD_TYPE_1] = m_Query.GetInt("CCF_Reward_PreLeague");
	pMsg->btArrayCCF_Reward[REWARD_TYPE_2] = m_Query.GetInt("CCF_Reward_SemiLeague");
	pMsg->btArrayCCF_Reward[REWARD_TYPE_3] = m_Query.GetInt("CCF_Reward_FinalLeague");
	pMsg->btArrayCCF_Reward[REWARD_TYPE_4] = m_Query.GetInt("CCF_Reward_LastWinner");
	pMsg->btArrayDSF_Reward[REWARD_TYPE_1] = m_Query.GetInt("DSF_Reward_PreLeague");
	pMsg->btArrayDSF_Reward[REWARD_TYPE_2] = m_Query.GetInt("DSF_Reward_SemiLeague");
	pMsg->btArrayDSF_Reward[REWARD_TYPE_3] = m_Query.GetInt("DSF_Reward_FinalLeague");
	pMsg->btArrayDSF_Reward[REWARD_TYPE_4] = m_Query.GetInt("DSF_Reward_LastWinner");
	pMsg->btArrayCCN_Reward[REWARD_TYPE_1] = m_Query.GetInt("CC_Reward_General");
	pMsg->btArrayCCN_Reward[REWARD_TYPE_2] = m_Query.GetInt("CC_Reward_LastWinner");
	pMsg->btArrayDSN_Reward[REWARD_TYPE_1] = m_Query.GetInt("DSN_Reward_Type_1");
	pMsg->btArrayDSN_Reward[REWARD_TYPE_2] = m_Query.GetInt("DSN_Reward_Type_2");
	pMsg->btArrayDSN_Reward[REWARD_TYPE_3] = m_Query.GetInt("DSN_Reward_Type_3");
	pMsg->btArrayDSN_Reward[REWARD_TYPE_4] = m_Query.GetInt("DSN_Reward_Type_4");
	pMsg->btArrayDSN_Reward[REWARD_TYPE_5] = m_Query.GetInt("DSN_Reward_Type_5");
	pMsg->btArrayDSN_Reward[REWARD_TYPE_6] = m_Query.GetInt("DSN_Reward_Type_6");
	pMsg->btArrayDSN_Reward[REWARD_TYPE_7] = m_Query.GetInt("DSN_Reward_Type_7");
	pMsg->btArrayDSN_Reward[REWARD_TYPE_8] = m_Query.GetInt("DSN_Reward_Type_8");
	pMsg->btArrayDSN_Reward[REWARD_TYPE_9] = m_Query.GetInt("DSN_Reward_Type_9");
	pMsg->btArrayDSN_Reward[REWARD_TYPE_10] = m_Query.GetInt("DSN_Reward_Type_10");
	pMsg->btArrayDSN_Reward[REWARD_TYPE_11] = m_Query.GetInt("DSN_Reward_Type_11");
	pMsg->btArrayDSN_Reward[REWARD_TYPE_12] = m_Query.GetInt("DSN_Reward_Type_12");
	pMsg->btArrayDSN_Reward[REWARD_TYPE_13] = m_Query.GetInt("DSN_Reward_Type_13");
	pMsg->btArrayDSN_Reward[REWARD_TYPE_14] = m_Query.GetInt("DSN_Reward_Type_14");

	m_Query.Clear();
	return TRUE;
}

BOOL ChaosCastleFinalDBSet::SetReceivedWinnerItemOfUBF(char* szCharName, int nServerCode, BYTE btReceived, BYTE& SubResult)
{
	if (m_Query.IsConnected() == FALSE)
	{
		LogAddTD("[UBF] m_Query.IsConnected: FALSE");
		SubResult = 0;
		return FALSE;
	}

	char szName[MAX_IDSTRING + 1];
	szName[MAX_IDSTRING] = '\0';
	memcpy(szName, szCharName, MAX_IDSTRING);

	if (strlen(szName) == 0 || strlen(szName) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szName, __FILE__, __LINE__);
		return FALSE;
	}

	CString qSql;
	qSql.Format("EXEC WZ_UnityBattleField_SetReceivedWinnerItem_r '%s', %d, %d", szName, nServerCode, btReceived);

	if (m_Query.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleField_SetReceivedWinnerItem_r] [%s][%d][%d]", szName, nServerCode, btReceived);
		m_Query.Clear();
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleField_SetReceivedWinnerItem_r] [%s][%d] Return %d,%s,%d ", szName, nServerCode, sqlReturn, __FILE__, __LINE__);
		m_Query.Clear();
		return FALSE;
	}
	
	SubResult = m_Query.GetInt(1);
	
	m_Query.Clear();
	return TRUE;
}

BOOL ChaosCastleFinalDBSet::SetCancelToJionUnityBattlefiled(char* szAccountID, char* szName, WORD GameServerCode, BYTE& subResult)
{
	if (m_Query.IsConnected() == FALSE)
	{
		LogAddTD("[UBF] m_Query.IsConnected: FALSE");
		subResult = 0;
		return FALSE;
	}

	char szId[MAX_IDSTRING + 1];
	szId[MAX_IDSTRING] = '\0';
	memcpy(szId, szAccountID, MAX_IDSTRING);

	char szCharName[MAX_IDSTRING + 1];
	szCharName[MAX_IDSTRING] = '\0';
	memcpy(szCharName, szName, MAX_IDSTRING);

	BYTE Return = 0;

	if (strlen(szId) == 0 || strlen(szId) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szId, __FILE__, __LINE__);
		return FALSE;
	}

	if (strlen(szCharName) == 0 || strlen(szCharName) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szId, __FILE__, __LINE__);
		return FALSE;
	}

	CString qSql;
	qSql.Format("EXEC WZ_UnityBattleFieldCancelToJoin_r '%s','%s',%d", szId, szCharName, GameServerCode);

	if (m_Query.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L3 [UBF][WZ_UnityBattleFieldCancelToJoin_r] [%s][%s][%d]", szId, szCharName, GameServerCode);
		m_Query.Clear();
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][SetCancelToJionUnityBattlefiled] [%s][%d] Return %d,%s,%d ", szName, GameServerCode, sqlReturn, __FILE__, __LINE__);
		m_Query.Clear();
		return FALSE;
	}

	subResult = m_Query.GetInt(1);

	m_Query.Clear();
	return TRUE;
}

BYTE ChaosCastleFinalDBSet::DeleteCharacterUnityBattlefiled(char* szAccountID, char* szName, WORD GameServerCode)
{
	if (m_Query.IsConnected() == FALSE)
	{
		LogAddTD("[UBF] m_Query.IsConnected: FALSE");
		return FALSE;
	}

	char szId[MAX_IDSTRING + 1];
	szId[MAX_IDSTRING] = '\0';
	memcpy(szId, szAccountID, MAX_IDSTRING);

	char szCharName[MAX_IDSTRING + 1];
	szCharName[MAX_IDSTRING] = '\0';
	memcpy(szCharName, szName, MAX_IDSTRING);

	BYTE Return = 0;

	if (strlen(szId) == 0 || strlen(szId) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szId, __FILE__, __LINE__);
		return FALSE;
	}

	if (strlen(szCharName) == 0 || strlen(szCharName) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szId, __FILE__, __LINE__);
		return FALSE;
	}

	CString qSql;
	qSql.Format("EXEC WZ_UnityBattleFieldDeleteCharacter_r '%s','%s',%d", szId, szCharName, GameServerCode);

	if (m_Query.Exec(qSql) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("Error-L3 [UBF][WZ_UnityBattleFieldDeleteCharacter_r] [%s][%s][%d]", szId, szCharName, GameServerCode);
		return 2;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldDeleteCharacter_r] [%s] Return %d,%s,%d ", szCharName, sqlReturn, __FILE__, __LINE__);
		m_Query.Clear();
		return FALSE;
	}

	Return = m_Query.GetInt(1);
		
	m_Query.Clear();
	return Return;
}

BOOL ChaosCastleFinalDBSet::GetRealNameAndServerCode(char* szUBFName, LPPMSG_ANS_GET_UBF_REAL_NAME pMsg)
{
	if (m_Query.IsConnected() == FALSE)
	{
		LogAddTD("[UBF] m_Query.IsConnected: FALSE");
		return FALSE;
	}

	char szCahrUBFName[MAX_IDSTRING + 1];
	szCahrUBFName[MAX_IDSTRING] = '\0';
	memcpy(szCahrUBFName, szUBFName, MAX_IDSTRING);

	if (strlen(szCahrUBFName) == 0 || strlen(szCahrUBFName) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szUBFName, __FILE__, __LINE__);
		return FALSE;
	}

	CString qSql;
	qSql.Format("EXEC WZ_UnityBattleFieldGetRealName_r '%s'", szCahrUBFName);

	if (m_Query.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L3 [UBF][WZ_UnityBattleFieldGetRealName_r] [%s]", szCahrUBFName);
		m_Query.Clear();
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldGetRealName_r] [%s] Return %d,%s,%d ", szCahrUBFName, sqlReturn, __FILE__, __LINE__);
		m_Query.Clear();
		return FALSE;
	}

	m_Query.GetStr("Name", pMsg->szRealName);
	pMsg->iServerCode = m_Query.GetInt("ServerCode");
	memcpy(pMsg->szUBFName, szCahrUBFName, MAX_IDSTRING);

	m_Query.Clear();
	return TRUE;
}

BOOL ChaosCastleFinalDBSet::GetRealNameAndServerCode(char* szUBFName, char* szRealName, int* ServerCode, BOOL IsUBFServer)
{
	if (m_Query.IsConnected() == FALSE)
	{
		LogAddTD("[UBF] m_Query.IsConnected: FALSE");
		return FALSE;
	}

	char szCahrUBFName[MAX_IDSTRING + 1];
	szCahrUBFName[MAX_IDSTRING] = '\0';
	memcpy(szCahrUBFName, szUBFName, MAX_IDSTRING);

	if (strlen(szCahrUBFName) == 0 || strlen(szCahrUBFName) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szUBFName, __FILE__, __LINE__);
		return FALSE;
	}

	CString qSql;
	qSql.Format("EXEC WZ_UnityBattleFieldGetRealName_r '%s'", szCahrUBFName);

	if (m_Query.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L3 [UBF][WZ_UnityBattleFieldGetRealName_r] [%s]", szCahrUBFName);
		m_Query.Clear();
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldGetRealName_r] [%s] Return %d,%s,%d ", szCahrUBFName, sqlReturn, __FILE__, __LINE__);
		m_Query.Clear();
		return FALSE;
	}

	m_Query.GetStr("Name", szRealName);
	*ServerCode = m_Query.GetInt("ServerCode");

	m_Query.Clear();
	return TRUE;
}

BOOL ChaosCastleFinalDBSet::SetRewardInfoOfUnityBattleField(BYTE& btResult, BYTE btServerKind, char* szAccountID, char* szName, WORD wServerCode, BYTE btContentsType, BYTE btSubContentsType, int iItemCode, BYTE btItemCount, BYTE btTakeState)
{
	char szId[MAX_IDSTRING + 1];
	szId[MAX_IDSTRING] = '\0';
	memcpy(szId, szAccountID, MAX_IDSTRING);

	char szCahrName[MAX_IDSTRING + 1];
	szCahrName[MAX_IDSTRING] = '\0';
	memcpy(szCahrName, szName, MAX_IDSTRING);

	if (strlen(szCahrName) == 0 || strlen(szCahrName) > MAX_IDSTRING || strlen(szId) == 0 || strlen(szId) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szCahrName, __FILE__, __LINE__);
		return FALSE;
	}

	CString qSql;
	qSql.Format("EXEC WZ_Set_RewardInfoOfUnityBattleField %d, '%s','%s', %d, %d, %d, %d, %d, %d ", btServerKind, szId, szCahrName, wServerCode, btContentsType, btSubContentsType, iItemCode, btItemCount, btTakeState);

	if (m_Query.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L3 [UBF][WZ_Set_RewardInfoOfUnityBattleField] [%s][%s][%d][%d]", szId, szCahrName, btContentsType, btTakeState);
		m_Query.Clear();
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_Set_RewardInfoOfUnityBattleField] [%s][%s][%d][%d] Return %d,%s,%d ", szId, szCahrName, btContentsType, btTakeState, sqlReturn, __FILE__, __LINE__);
		m_Query.Clear();
		return FALSE;
	}

	btResult = m_Query.GetInt("Result");
		
	m_Query.Clear();
	return TRUE;
}