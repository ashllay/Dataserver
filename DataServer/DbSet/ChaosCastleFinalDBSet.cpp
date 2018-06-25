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

int ChaosCastleFinalDBSet::ReqCCFRanking(_stCCFRankingInfo *CCFRankingInfo, int nCCFtype, char *btUserCount, int nServerCategory)
{
	int result;
	__int16 sqlRetrun;
	CString szquery;
	int iCnt = 0;

	if (this->m_DBQuery.IsConnected())
	{
		if (nServerCategory == 1)
			szquery.Format("WZ_ChaosCastleFinal_GetRank_r %d",nCCFtype);
		else
			szquery.Format("WZ_ChaosCastleFinal_GetRank %d",nCCFtype);
		if (this->m_DBQuery.Exec(szquery))
		{
			for (sqlRetrun = this->m_DBQuery.Fetch(); sqlRetrun != 100; sqlRetrun = this->m_DBQuery.Fetch())
			{
				if (sqlRetrun == -1)
					break;

				CCFRankingInfo[iCnt].byRank = this->m_DBQuery.GetInt("mRank");
				this->m_DBQuery.GetStr("mName", CCFRankingInfo[iCnt].szCharName);
				CCFRankingInfo[iCnt++].nPoint = this->m_DBQuery.GetInt("mPoint");
				if (iCnt >= 50)
					break;
			}
			*btUserCount = iCnt;
			this->m_DBQuery.Clear();
			result = 0;
		}
		else
		{
			LogAddC(2,"Error WZ_CCF_GET_RANKLIST m_DBQuery.Exec %s %d", __FILE__, __LINE__);
			this->m_DBQuery.Clear();
			result = -1;
		}
	}
	else
	{
		LogAddTD("[UBF] this->m_DBQuery.IsConnected: FALSE");
		result = -1;
	}
	return result;
}


void ChaosCastleFinalDBSet::Save_CCF_Point(char *Name, int nPoint, int nCCFType)
{
	__int16 sqlReturn;
	CString qSql;

	if (this->m_DBQuery.IsConnected())
	{

		qSql.Format("WZ_ChaosCastleFinal_Save '%s', %d, %d",Name,nPoint,nCCFType);
		if (!this->m_DBQuery.Exec(qSql))
			LogAddTD("Error-L1 [ChaosCastleFinal] [WZ_ChaosCastleFinal_Save] NAME:%s, Point:%d ,CCFType:%d ",Name,nPoint,nCCFType);
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn == 100 || sqlReturn == -1)
			LogAddTD("Error-L2 [ChaosCastleFinal] [WZ_ChaosCastleFinal_Save] %d, %s , %d",sqlReturn, __FILE__, __LINE__);
		this->m_DBQuery.Clear();
	}
	else
	{
		LogAddTD("[UBF] this->m_DBQuery.IsConnected: FALSE");
	}
}


int ChaosCastleFinalDBSet::CCFRankRenew(char byCCFType)
{
	int result;
	CString q;

	if (this->m_DBQuery.IsConnected())
	{
		q.Format("WZ_ChaosCastleFinal_Renew %d", byCCFType);
		if (this->m_DBQuery.Exec(q))
		{
			this->m_DBQuery.Clear();
			result = 0;
		}
		else
		{
			LogAddTD("Error-L1 [ChaosCastleFinalDBSet][WZ_ChaosCastleFinal_Renew]");
			result = -1;
		}
	}
	else
	{
		LogAddTD("[UBF] this->m_DBQuery.IsConnected: FALSE");
		result = -1;
	}
	return result;
}


void ChaosCastleFinalDBSet::GetPermission(char *Name, int nCCFType, int *nReturn)
{
	__int16 sqlReturn;
	CString qSql;

	if (this->m_DBQuery.IsConnected())
	{
		qSql.Format("WZ_ChaosCastleFinal_GetPermission  '%s' , %d",Name,nCCFType);
		if (this->m_DBQuery.Exec(qSql))
		{
			sqlReturn = this->m_DBQuery.Fetch();
			if (sqlReturn != 100 && sqlReturn != -1)
			{
				*nReturn = this->m_DBQuery.GetInt(1);
				if (*nReturn == -1)
					LogAddTD("error-L3 : [ChaosCastleFinalDBSet] WZ_ChaosCastleFinal_GetPermission #3 %d %s %d",
						sqlReturn, __FILE__, __LINE__);
				this->m_DBQuery.Clear();
			}
			else
			{
				this->m_DBQuery.Clear();
				LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_ChaosCastleFinal_GetPermission][A2] %s %d Return %d,%s,%d ",
					Name,nCCFType,sqlReturn, __FILE__, __LINE__);
			}
		}
		else
		{
			LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_ChaosCastleFinal_GetPermission][A1] %s %d ", Name, nCCFType);
		}
	}
	else
	{
		LogAddTD("[UBF] this->m_DBQuery.IsConnected: FALSE");
		*nReturn = 1;
	}
}


int ChaosCastleFinalDBSet::Save_ChaosCastle_KillPoint(char *szName, int nPoint, int CastleIndex, int *SubResult, int *CurrntPoint, int *TotalPoint)
{
	int result;
	__int16 sqlReturn; 
	CString qSql;
	char szCharName[11];

	if (this->m_DBQuery.IsConnected())
	{
		szCharName[10] = 0;
		memcpy(szCharName, szName, 0xAu);

		if (strlen(szCharName) && (strlen(szCharName) <= 0xA))
		{
			qSql.Format("EXEC WZ_ChaosCastle_SaveKillPoint '%s', %d ,%d ",szName,nPoint,CastleIndex);

			if (this->m_DBQuery.Exec(qSql))
			{
				sqlReturn = this->m_DBQuery.Fetch();
				if (sqlReturn != 100 && sqlReturn != -1)
				{
					*SubResult = this->m_DBQuery.GetInt("Result");
					*CurrntPoint = this->m_DBQuery.GetInt("CurrentPoint");
					*TotalPoint = this->m_DBQuery.GetInt("TotalPoint");
					this->m_DBQuery.Clear();
					result = 1;
				}
				else
				{
					LogAddTD("Error-L3 [ChaosCastleFinalDBSet][Save_ChaosCastle_KillPoint] [%s] nPoint:%d CastleIndex: %d Return %d,%s,%d ",
						szName,nPoint,CastleIndex,sqlReturn, __FILE__, __LINE__);
					this->m_DBQuery.Clear();

					result = 0;
				}
			}
			else
			{
				LogAddTD("Error-L3 [ChaosCastleFinalDBSet][Save_ChaosCastle_KillPoint] [%s] KillPoint:%d CastleIndex :%d ",
					szCharName,nPoint,CastleIndex);
				this->m_DBQuery.Clear();
				result = 0;
			}
		}
		else
		{
			LogAddC(2,"%s] ؎֥ ߡׯ %s %d",szCharName, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		LogAddTD("[UBF] this->m_DBQuery.IsConnected: FALSE");
		*SubResult = -1;
		*CurrntPoint = 0;
		*TotalPoint = 0;
		result = 0;
	}
	return result;
}


int ChaosCastleFinalDBSet::GetUBFAccountUserInfo(char *szAccountID, char *szName, int nServerCode, int IsUnityBattleFieldServer, PMSG_ANS_UBF_ACCOUNT_USERINFO *pMsg)
{
	int result; // eax
	__int16 sqlReturn;
	CString qSql;
	char szCharName[11]; 
	char szId[11];


	if (this->m_DBQuery.IsConnected())
	{
		szId[10] = 0;
		memcpy(szId, szAccountID, 0xAu);

		if (strlen(szId) && (strlen(szId) <= 0xA))
		{
			szCharName[10] = 0;
			memcpy(szCharName, szName, 0xAu);
			if (strlen(szCharName) && (strlen(szCharName) <= 0xA))
			{
				qSql.Format("EXEC WZ_UnityBattleFieldAccountUserInfoSelect_r '%s', '%s', %d, %d",
					szAccountID,szName,nServerCode,IsUnityBattleFieldServer);
				if (this->m_DBQuery.Exec(qSql))
				{
					sqlReturn = this->m_DBQuery.Fetch();
					if (sqlReturn == 100)
					{
						LogAddTD("[CCF][WZ_UnityBattleFieldAccountUserInfoSelect_r] No Result Not Error [%s][%s]ServerCode:%d Return %d,%s,%d ",
							szId,szName,nServerCode,sqlReturn, __FILE__, __LINE__);
						this->m_DBQuery.Clear();
						result = 0;
					}
					else if (sqlReturn == -1)
					{
						LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldAccountUserInfoSelect_r] [%s][%s]ServerCode:%d Return %d,%s,%d ",
							szId,szName,nServerCode,sqlReturn, __FILE__, __LINE__);
						this->m_DBQuery.Clear();
						result = 0;
					}
					else
					{
						pMsg->btRegisterState = this->m_DBQuery.GetInt("RegisterState");
						pMsg->btRegisterMonth = this->m_DBQuery.GetInt("RegisterMonth");
						pMsg->btRegisterDay = this->m_DBQuery.GetInt("RegisterDay");
						this->m_DBQuery.Clear();
						result = 1;
					}
				}
				else
				{
					LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldAccountUserInfoSelect_r] [%s][%s] ServerCode:%d, ServerType:%d ",
						szId,szCharName,nServerCode,IsUnityBattleFieldServer);
					this->m_DBQuery.Clear();
					result = 0;
				}
			}
			else
			{
				LogAddC(2,"%s] ؎֥ ߡׯ %s %d",szCharName, __FILE__, __LINE__);
				result = 0;
			}
		}
		else
		{
			LogAddC(2,"%s] ؎֥ ߡׯ %s %d",szId, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		LogAddTD("[UBF] this->m_DBQuery.IsConnected: FALSE");
		pMsg->btRegisterState = 0;
		pMsg->btRegisterMonth = 0;
		pMsg->btRegisterDay = 0;
		result = 0;
	}
	return result;
}


int ChaosCastleFinalDBSet::RegisterUBFAccountUser(char *szAccountID, char *szName, char *szBattleName, int nServerCode, int nRegisterState, int nRegisterMonth, int nRegisterDay, char *nResult, unsigned __int16 *nLeftSec)
{
	int result;
	__int16 sqlReturn;
	CString qSql;
	char szUBFName[11];
	char szCharName[11];
	char szId[11];


	if (this->m_DBQuery.IsConnected())
	{
		szId[10] = 0;
		memcpy(szId, szAccountID, 0xAu);

		if (strlen(szId) && (strlen(szId) <= 0xA))
		{
			szCharName[10] = 0;
			memcpy(szCharName, szName, 0xAu);
			strlen(szCharName);
			if (strlen(szCharName) && (strlen(szCharName) <= 0xA))
			{
				szUBFName[10] = 0;
				memcpy(szUBFName, szBattleName, 0xAu);
				strlen(szUBFName);
				if (strlen(szUBFName) && (strlen(szUBFName) <= 0xA))
				{

					qSql.Format("EXEC WZ_UnityBattleFieldAccountUserAdd_r '%s', '%s', %d, %d, %d, %d",
						szId,szCharName,nServerCode,nRegisterState,nRegisterMonth,nRegisterDay);
					if (this->m_DBQuery.Exec(qSql))
					{
						sqlReturn = this->m_DBQuery.Fetch();
						if (sqlReturn != 100 && sqlReturn != -1)
						{
							*nResult = this->m_DBQuery.GetInt("Result");
							*nLeftSec = this->m_DBQuery.GetInt("Left_Second");
							this->m_DBQuery.Clear();
							result = 1;
						}
						else
						{
							LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldAccountUserAdd_r] [%s][%s] sqlReturn:%d,%s,%d ",
								szId,szCharName,sqlReturn, __FILE__, __LINE__);
							this->m_DBQuery.Clear();
							result = 0;
						}
					}
					else
					{
						LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldAccountUserAdd_r] '%s', '%s', %d, %d, %d, %d ",
							szId,szCharName,nServerCode,nRegisterState,nRegisterMonth,nRegisterDay);
						this->m_DBQuery.Clear();
						result = 0;
					}
				}
				else
				{
					LogAddC(2,"%s] ؎֥ ߡׯ %s %d",szUBFName, __FILE__, __LINE__);
					result = 0;
				}
			}
			else
			{
				LogAddC(2, "%s] ؎֥ ߡׯ %s %d",szCharName, __FILE__, __LINE__);
				result = 0;
			}
		}
		else
		{
			LogAddC(2,"%s] ؎֥ ߡׯ %s %d",szId, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		LogAddTD("[UBF] this->m_DBQuery.IsConnected: FALSE");
		*nResult = -1;
		*nLeftSec = 0;
		result = 0;
	}
	return result;
}


bool ChaosCastleFinalDBSet::CopyUBFAccountUser(char *szAccountID, char *szName, __int16 GameServerCode, BYTE* subResult)
{
	int result;
	__int16 sqlReturn;
	CString qSql; 
	char szCharName[11];
	char szId[11];

	if (this->m_DBQuery.IsConnected())
	{
		szId[10] = 0;
		memcpy(szId, szAccountID, 0xAu);
		if (strlen(szId) && (strlen(szId) <= 0xA))
		{
			szCharName[10] = 0;
			memcpy(szCharName, szName, 0xAu);
			if (strlen(szCharName) && (strlen(szCharName) <= 0xA))
			{

				qSql.Format("EXEC WZ_UnityBattleFieldAccountUserDataCopy_r '%s', '%s',%d",
					szId,szCharName,GameServerCode);
				if (this->m_DBQuery.Exec(qSql))
				{
					sqlReturn = this->m_DBQuery.Fetch();
					if (sqlReturn != 100 && sqlReturn != -1)
					{
						*subResult = this->m_DBQuery.GetInt(1);
						this->m_DBQuery.Clear();
						result = 1;
					}
					else
					{
						this->m_DBQuery.Clear();
						LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldAccountUserDataCopy] [%s][%s] sqlReturn:%d,%s,%d ",
							szId,szCharName,sqlReturn, __FILE__, __LINE__);
						result = 0;
					}
				}
				else
				{
					LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldAccountUserDataCopy_r] '%s', '%s'",
						szId,szCharName);
					this->m_DBQuery.Clear();
					result = 0;
				}
			}
			else
			{
				LogAddC(2,"%s] ؎֥ ߡׯ %s %d",szCharName, __FILE__, __LINE__);
				result = 0;
			}
		}
		else
		{
			LogAddC(2, "%s] ؎֥ ߡׯ %s %d",szId, __FILE__, __LINE__);
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


bool ChaosCastleFinalDBSet::CopyUBFAccountUserPromotionMode(char *szAccountID, char *szName, __int16 GameServerCode, BYTE *subResult)
{
	int result;
	__int16 sqlReturn;
	CString qSql;
	char szCharName[11];
	char szId[11];


	if (this->m_DBQuery.IsConnected())
	{
		szId[10] = 0;
		memcpy(szId, szAccountID, 0xAu);

		if (strlen(szId) && (strlen(szId) <= 0xA))
		{
			szCharName[10] = 0;
			memcpy(szCharName, szName, 0xAu);

			if (strlen(szCharName) && (strlen(szCharName) <= 0xA))
			{
				qSql.Format("EXEC WZ_UnityBattleFieldAccountUserDataCopy_Promotion '%s', '%s',%d",
					szId,szCharName,GameServerCode);
				if (this->m_DBQuery.Exec(qSql))
				{
					sqlReturn = this->m_DBQuery.Fetch();
					if (sqlReturn != 100 && sqlReturn != -1)
					{
						*subResult = this->m_DBQuery.GetInt(1);
						this->m_DBQuery.Clear();
						result = 1;
					}
					else
					{
						this->m_DBQuery.Clear();
						LogAddTD("Error-L3 [CCFDBSet][WZ_UnityBattleFieldAccountUserDataCopy_Promotion] [%s][%s] sqlReturn:%d,%s,%d ",
							szId,szCharName,sqlReturn, __FILE__, __LINE__);
						result = 0;
					}
				}
				else
				{
					LogAddTD("Error-L3 [CCFDBSet][WZ_UnityBattleFieldAccountUserDataCopy_Promotion] '%s', '%s'", szId, szCharName);
					this->m_DBQuery.Clear();

					result = 0;
				}
			}
			else
			{
				LogAddC(2,"%s] ؎֥ ߡׯ %s %d",szCharName, __FILE__, __LINE__);
				result = 0;
			}
		}
		else
		{
			LogAddC(2,"%s] ؎֥ ߡׯ %s %d",szId, __FILE__, __LINE__);
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


int ChaosCastleFinalDBSet::GetWinAllRewardInfoOfUBF(char *szCharName, int nServerCode, char btServerKind, char btContentsType, PMSG_ANS_UBF_GET_REWARD *pMsg)
{
	int result; // eax
	__int16 sqlReturn; // [esp+F8h] [ebp-44h]
	CString qSql; // [esp+104h] [ebp-38h]
	char szName[11]; // [esp+110h] [ebp-2Ch]

	szName[10] = 0;
	memcpy(szName, szCharName, 0xAu);

	if (strlen(szName) && (strlen(szName) <= 0xA))
	{
		qSql.Format("EXEC WZ_All_GetAndUpdate_RewardInfoOfUnityBattleField %d, '%s', %d, %d ",
			btServerKind,
			szName,
			nServerCode,
			btContentsType);
		if (this->m_DBQuery.Exec(qSql))
		{
			sqlReturn = this->m_DBQuery.Fetch();
			if (sqlReturn != 100 && sqlReturn != -1)
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
					szName,nServerCode,sqlReturn, __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				result = 0;
			}
		}
		else
		{
			LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_All_GetAndUpdate_RewardInfoOfUnityBattleField] [ServerKind:%d][%s][%d][%d]",
				btServerKind,szName,nServerCode,btContentsType);
			this->m_DBQuery.Clear();
			result = 0;
		}
	}
	else
	{
		LogAddC(2,"%s] ؎֥ ߡׯ %s %d",szName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


int ChaosCastleFinalDBSet::SetReceivedWinnerItemOfUBF(char *szCharName, int nServerCode, char btReceived, char *SubResult)
{
	int result; // eax
	__int16 sqlReturn; // [esp+F8h] [ebp-44h]
	CString qSql; // [esp+104h] [ebp-38h]
	char szName[11]; // [esp+110h] [ebp-2Ch]

	if (this->m_DBQuery.IsConnected())
	{
		szName[10] = 0;
		memcpy(szName, szCharName, 0xAu);

		if (strlen(szName) && (strlen(szName) <= 0xA))
		{
			qSql.Format("EXEC WZ_UnityBattleField_SetReceivedWinnerItem_r '%s', %d, %d",
				szName,nServerCode,btReceived);
			if (this->m_DBQuery.Exec(qSql))
			{
				sqlReturn = this->m_DBQuery.Fetch();
				if (sqlReturn != 100 && sqlReturn != -1)
				{
					*SubResult = this->m_DBQuery.GetInt(1);
					this->m_DBQuery.Clear();
					result = 1;
				}
				else
				{
					LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleField_SetReceivedWinnerItem_r] [%s][%d] Return %d,%s,%d ",
						szName,nServerCode,sqlReturn, __FILE__, __LINE__);
					this->m_DBQuery.Clear();
					result = 0;
				}
			}
			else
			{
				LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleField_SetReceivedWinnerItem_r] [%s][%d][%d]",
					szName,nServerCode,btReceived);
				this->m_DBQuery.Clear();
				result = 0;
			}
		}
		else
		{
			LogAddC(2,"%s] ؎֥ ߡׯ %s %d",szName, __FILE__, __LINE__);
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


int ChaosCastleFinalDBSet::SetCancelToJionUnityBattlefiled(char *szAccountID, char *szName, __int16 GameServerCode, char *subResult)
{
	int result;
	__int16 sqlReturn;
	CString qSql;
	char Return;
	char szCharName[11];
	char szId[11];


	if (this->m_DBQuery.IsConnected())
	{
		szId[10] = 0;
		memcpy(szId, szAccountID, 0xAu);
		szCharName[10] = 0;
		memcpy(szCharName, szName, 0xAu);
		Return = 0;

		if (strlen(szId) && (strlen(szId) <= 0xA))
		{

			if (strlen(szCharName) && (strlen(szCharName) <= 0xA))
			{

				qSql.Format("EXEC WZ_UnityBattleFieldCancelToJoin_r '%s','%s',%d",
					szId,szCharName,GameServerCode);
				if (this->m_DBQuery.Exec(qSql))
				{
					sqlReturn = this->m_DBQuery.Fetch();
					if (sqlReturn != 100 && sqlReturn != -1)
					{
						*subResult = this->m_DBQuery.GetInt(1);
						this->m_DBQuery.Clear();
						result = 1;
					}
					else
					{
						LogAddTD("Error-L3 [ChaosCastleFinalDBSet][SetCancelToJionUnityBattlefiled] [%s][%d] Return %d,%s,%d ",
							szName,GameServerCode,sqlReturn, __FILE__, __LINE__);
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
				LogAddC(2,"%s] ؎֥ ߡׯ %s %d",szId, __FILE__, __LINE__);
				result = 0;
			}
		}
		else
		{
			LogAddC(2, "%s] ؎֥ ߡׯ %s %d",szId, __FILE__, __LINE__);
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


char ChaosCastleFinalDBSet::DeleteCharacterUnityBattlefiled(char *szAccountID, char *szName, __int16 GameServerCode)
{
	char result; 
	__int16 sqlReturn;
	CString qSql;
	char Return;
	char szCharName[11];
	char szId[11];

	if (this->m_DBQuery.IsConnected())
	{
		szId[10] = 0;
		memcpy(szId, szAccountID, 0xAu);
		szCharName[10] = 0;
		memcpy(szCharName, szName, 0xAu);
		Return = 0;

		if (strlen(szId) && (strlen(szId) <= 0xA))
		{
			if (strlen(szCharName) && (strlen(szCharName) <= 0xA))
			{
				qSql.Format("EXEC WZ_UnityBattleFieldDeleteCharacter_r '%s','%s',%d",
					szId,szCharName,GameServerCode);
				if (this->m_DBQuery.Exec(qSql))
				{
					sqlReturn = this->m_DBQuery.Fetch();
					if (sqlReturn != 100 && sqlReturn != -1)
					{
						Return = this->m_DBQuery.GetInt(1);
						this->m_DBQuery.Clear();
						result = Return;
					}
					else
					{
						LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldDeleteCharacter_r] [%s] Return %d,%s,%d ",
							szCharName,sqlReturn, __FILE__, __LINE__);
						this->m_DBQuery.Clear();
						result = 0;
					}
				}
				else
				{
					this->m_DBQuery.Clear();
					LogAddTD("Error-L3 [UBF][WZ_UnityBattleFieldDeleteCharacter_r] [%s][%s][%d]",
						szId,szCharName,GameServerCode);
					result = 2;
				}
			}
			else
			{
				LogAddC(2, "%s] ؎֥ ߡׯ %s %d",szId, __FILE__, __LINE__);
				result = 0;
			}
		}
		else
		{
			LogAddC(2,"%s] ؎֥ ߡׯ %s %d",szId, __FILE__, __LINE__);
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


int ChaosCastleFinalDBSet::GetRealNameAndServerCode(char *szUBFName, PMSG_ANS_GET_UBF_REAL_NAME *pMsg)
{
	int result;
	__int16 sqlReturn;
	CString qSql;
	char szCahrUBFName[11];


	if (this->m_DBQuery.IsConnected())
	{
		szCahrUBFName[10] = 0;
		memcpy(szCahrUBFName, szUBFName, 0xAu);
		if (strlen(szCahrUBFName) && (strlen(szCahrUBFName) <= 0xA))
		{
			qSql.Format("EXEC WZ_UnityBattleFieldGetRealName_r '%s'",
				szCahrUBFName);
			if (this->m_DBQuery.Exec(qSql))
			{
				sqlReturn = this->m_DBQuery.Fetch();
				if (sqlReturn != 100 && sqlReturn != -1)
				{
					this->m_DBQuery.GetStr("Name", pMsg->szRealName);
					pMsg->iServerCode = this->m_DBQuery.GetInt("ServerCode");
					memcpy(pMsg->szUBFName, szCahrUBFName, 0xAu);
					this->m_DBQuery.Clear();
					result = 1;
				}
				else
				{
					LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldGetRealName_r] [%s] Return %d,%s,%d ",
						szCahrUBFName,sqlReturn, __FILE__, __LINE__);
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
			LogAddC(2,"%s] ؎֥ ߡׯ %s %d",szUBFName, __FILE__, __LINE__);
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


int ChaosCastleFinalDBSet::GetRealNameAndServerCode(char *szUBFName, char *szRealName, int *ServerCode, int IsUBFServer)
{
	int result;
	__int16 sqlReturn;
	CString qSql;
	char szCahrUBFName[11]; 

	if (this->m_DBQuery.IsConnected())
	{
		szCahrUBFName[10] = 0;
		memcpy(szCahrUBFName, szUBFName, 0xAu);
		strlen(szCahrUBFName);
		if (strlen(szCahrUBFName) && (strlen(szCahrUBFName) <= 0xA))
		{
			qSql.Format("EXEC WZ_UnityBattleFieldGetRealName_r '%s'",szCahrUBFName);
			if (this->m_DBQuery.Exec(qSql))
			{
				sqlReturn = this->m_DBQuery.Fetch();
				if (sqlReturn != 100 && sqlReturn != -1)
				{
					this->m_DBQuery.GetStr("Name", szRealName);
					*ServerCode = this->m_DBQuery.GetInt("ServerCode");
					this->m_DBQuery.Clear();
					result = 1;
				}
				else
				{
					LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldGetRealName_r] [%s] Return %d,%s,%d ",
						szCahrUBFName,sqlReturn, __FILE__, __LINE__);
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
			LogAddC(2, "%s] ؎֥ ߡׯ %s %d",szUBFName, __FILE__, __LINE__);
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


int ChaosCastleFinalDBSet::SetRewardInfoOfUnityBattleField(char *btResult, char btServerKind, char *szAccountID, char *szName, __int16 wServerCode, char btContentsType, char btSubContentsType, int iItemCode, char btItemCount, char btTakeState)
{
	int result;
	__int16 sqlReturn; 
	CString qSql;
	char szCahrName[11];
	char szId[11];

	szId[10] = 0;
	memcpy(szId, szAccountID, 0xAu);
	szCahrName[10] = 0;
	memcpy(szCahrName, szName, 0xAu);

	if (strlen(szCahrName) && (strlen(szCahrName) <= 0xA) &&
		(strlen(szId)) && (strlen(szId) <= 0xA))
#pragma message ("check this!!!")
	{
		qSql.Format("EXEC WZ_Set_RewardInfoOfUnityBattleField %d, '%s','%s', %d, %d, %d,% d, %d, %d ",
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
			if (sqlReturn != 100 && sqlReturn != -1)
			{
				*btResult = this->m_DBQuery.GetInt("Result");
				this->m_DBQuery.Clear();
				result = 1;
			}
			else
			{
				LogAddTD(
					"Error-L3 [ChaosCastleFinalDBSet][WZ_Set_RewardInfoOfUnityBattleField] [%s][%s][%d][%d] Return %d,%s,%d ",
					szId,
					szCahrName,
					btContentsType,
					btTakeState,
					sqlReturn, __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				result = 0;
			}
		}
		else
		{
			LogAddTD("Error-L3 [UBF][WZ_Set_RewardInfoOfUnityBattleField] [%s][%s][%d][%d]",
				szId,
				szCahrName,
				btContentsType,
				btTakeState);
			this->m_DBQuery.Clear();
			result = 0;
		}
	}
	else
	{
		LogAddC(2,"%s] ؎֥ ߡׯ %s %d",szCahrName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}