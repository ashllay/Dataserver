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
	int result; // eax
	char v7; // al
	int v8; // eax
	int v9; // [esp+14h] [ebp-11Ch]
	int v10; // [esp+20h] [ebp-110h]
	__int16 sqlRetrun; // [esp+F8h] [ebp-38h]
	CString szquery; // [esp+104h] [ebp-2Ch]
	int iCnt; // [esp+110h] [ebp-20h]
	int v15; // [esp+12Ch] [ebp-4h]


	iCnt = 0;
	v15 = 0;
	if (this->m_DBQuery.IsConnected())
	{
		if (nServerCategory == 1)
			szquery.Format("WZ_ChaosCastleFinal_GetRank_r %d",
				nCCFtype);
		else
			szquery.Format("WZ_ChaosCastleFinal_GetRank %d",
				nCCFtype);
		if (this->m_DBQuery.Exec(szquery))
		{
			for (sqlRetrun = this->m_DBQuery.Fetch(); sqlRetrun != 100; sqlRetrun = this->m_DBQuery.Fetch())
			{
				if (sqlRetrun == -1)
					break;
				v7 = this->m_DBQuery.GetInt("mRank");
				CCFRankingInfo[iCnt].byRank = v7;
				this->m_DBQuery.GetStr("mName", CCFRankingInfo[iCnt].szCharName);
				v8 = this->m_DBQuery.GetInt("mPoint");
				CCFRankingInfo[iCnt++].nPoint = v8;
				if (iCnt >= 50)
					break;
			}
			*btUserCount = iCnt;
			this->m_DBQuery.Clear();
			v15 = -1;
			result = 0;
		}
		else
		{
			LogAddC(
				2,
				"Error WZ_CCF_GET_RANKLIST m_DBQuery.Exec %s %d", __FILE__, __LINE__);
			this->m_DBQuery.Clear();
			v10 = -1;
			v15 = -1;
			result = v10;
		}
	}
	else
	{
		LogAddTD("[UBF] this->m_DBQuery.IsConnected: FALSE");
		v9 = -1;
		v15 = -1;
		result = v9;
	}
	return result;
}
// 5CD8B8: using guessed type int `ChaosCastleFinalDBSet::ReqCCFRanking'::`2'::__LINE__Var;

//----- (00431B80) --------------------------------------------------------
void ChaosCastleFinalDBSet::Save_CCF_Point(char *Name, int nPoint, int nCCFType)
{
	__int16 sqlReturn; // [esp+D4h] [ebp-2Ch]
	CString qSql; // [esp+E0h] [ebp-20h]
	int v8; // [esp+FCh] [ebp-4h]


	if (this->m_DBQuery.IsConnected())
	{
		v8 = 0;
		qSql.Format("WZ_ChaosCastleFinal_Save '%s', %d, %d",
			Name,
			nPoint,
			nCCFType);
		if (!this->m_DBQuery.Exec(qSql))
			LogAddTD(
				"Error-L1 [ChaosCastleFinal] [WZ_ChaosCastleFinal_Save] NAME:%s, Point:%d ,CCFType:%d ",
				Name,
				nPoint,
				nCCFType);
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn == 100 || sqlReturn == -1)
			LogAddTD(
				"Error-L2 [ChaosCastleFinal] [WZ_ChaosCastleFinal_Save] %d, %s , %d",
				sqlReturn, __FILE__, __LINE__);
		this->m_DBQuery.Clear();
		v8 = -1;
	}
	else
	{
		LogAddTD("[UBF] this->m_DBQuery.IsConnected: FALSE");
	}
}
// 5CD8BC: using guessed type int `ChaosCastleFinalDBSet::Save_CCF_Point'::`2'::__LINE__Var;

//----- (00431D20) --------------------------------------------------------
int ChaosCastleFinalDBSet::CCFRankRenew(char byCCFType)
{
	int result; // eax
	int v4; // [esp+14h] [ebp-F8h]
	CString q; // [esp+ECh] [ebp-20h]
	int v7; // [esp+108h] [ebp-4h]


	if (this->m_DBQuery.IsConnected())
	{
		v7 = 0;
		q.Format("WZ_ChaosCastleFinal_Renew %d", byCCFType);
		if (this->m_DBQuery.Exec(q))
		{
			this->m_DBQuery.Clear();
			v7 = -1;
			result = 0;
		}
		else
		{
			LogAddTD("Error-L1 [ChaosCastleFinalDBSet][WZ_ChaosCastleFinal_Renew]");
			v4 = -1;
			v7 = -1;
			result = v4;
		}
	}
	else
	{
		LogAddTD("[UBF] this->m_DBQuery.IsConnected: FALSE");
		result = -1;
	}
	return result;
}

//----- (00431E90) --------------------------------------------------------
void ChaosCastleFinalDBSet::GetPermission(char *Name, int nCCFType, int *nReturn)
{
	__int16 sqlReturn; // [esp+D4h] [ebp-2Ch]
	CString qSql; // [esp+E0h] [ebp-20h]
	int v8; // [esp+FCh] [ebp-4h]


	if (this->m_DBQuery.IsConnected())
	{
		v8 = 0;
		qSql.Format("WZ_ChaosCastleFinal_GetPermission  '%s' , %d",
			Name,
			nCCFType);
		if (this->m_DBQuery.Exec(qSql))
		{
			sqlReturn = this->m_DBQuery.Fetch();
			if (sqlReturn != 100 && sqlReturn != -1)
			{
				*nReturn = this->m_DBQuery.GetInt(1);
				if (*nReturn == -1)
					LogAddTD(
						"error-L3 : [ChaosCastleFinalDBSet] WZ_ChaosCastleFinal_GetPermission #3 %d %s %d",
						sqlReturn, __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				v8 = -1;
			}
			else
			{
				this->m_DBQuery.Clear();
				LogAddTD(
					"Error-L3 [ChaosCastleFinalDBSet][WZ_ChaosCastleFinal_GetPermission][A2] %s %d Return %d,%s,%d ",
					Name,
					nCCFType,
					sqlReturn, __FILE__, __LINE__);
				v8 = -1;
			}
		}
		else
		{
			LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_ChaosCastleFinal_GetPermission][A1] %s %d ", Name, nCCFType);
			v8 = -1;
		}
	}
	else
	{
		LogAddTD("[UBF] this->m_DBQuery.IsConnected: FALSE");
		*nReturn = 1;
	}
}
// 5CD8C0: using guessed type int `ChaosCastleFinalDBSet::GetPermission'::`2'::__LINE__Var;

//----- (004320B0) --------------------------------------------------------
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
// 5CD8C4: using guessed type int `ChaosCastleFinalDBSet::Save_ChaosCastle_KillPoint'::`2'::__LINE__Var;

//----- (004323B0) --------------------------------------------------------
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


int ChaosCastleFinalDBSet::CopyUBFAccountUser(char *szAccountID, char *szName, __int16 GameServerCode, char *subResult)
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


int ChaosCastleFinalDBSet::CopyUBFAccountUserPromotionMode(char *szAccountID, char *szName, __int16 GameServerCode, char *subResult)
{
	int result; // eax
	int v6; // eax
	unsigned int v7; // eax
	int v8; // eax
	unsigned int v9; // eax
	int v11; // [esp+14h] [ebp-13Ch]
	int v12; // [esp+20h] [ebp-130h]
	__int16 sqlReturn; // [esp+F8h] [ebp-58h]
	CString qSql; // [esp+104h] [ebp-4Ch]
	char szCharName[11]; // [esp+110h] [ebp-40h]
	char szId[11]; // [esp+124h] [ebp-2Ch]
	int v18; // [esp+14Ch] [ebp-4h]


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
				v18 = 0;
				qSql.Format("EXEC WZ_UnityBattleFieldAccountUserDataCopy_Promotion '%s', '%s',%d",
					szId,szCharName,GameServerCode);
				if (this->m_DBQuery.Exec(qSql))
				{
					sqlReturn = this->m_DBQuery.Fetch();
					if (sqlReturn != 100 && sqlReturn != -1)
					{
						*subResult = this->m_DBQuery.GetInt(1);
						this->m_DBQuery.Clear();
						v18 = -1;
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
	int v6; // eax
	unsigned int v7; // eax
	int result; // eax
	int v10; // [esp+14h] [ebp-128h]
	int v11; // [esp+20h] [ebp-11Ch]
	__int16 sqlReturn; // [esp+F8h] [ebp-44h]
	CString qSql; // [esp+104h] [ebp-38h]
	char szName[11]; // [esp+110h] [ebp-2Ch]
	int v16; // [esp+138h] [ebp-4h]


	szName[10] = 0;
	memcpy(szName, szCharName, 0xAu);
	//strlen(szName);
	if (strlen(szName) && (strlen(szName) <= 0xA))
	{
		v16 = 0;
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
				v16 = -1;
				result = 1;
			}
			else
			{
				LogAddTD(
					"Error-L3 [ChaosCastleFinalDBSet][WZ_All_GetAndUpdate_RewardInfoOfUnityBattleField] [%s][%d] Return %d,%s,%d ",
					szName,
					nServerCode,
					sqlReturn, __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				v11 = 0;
				v16 = -1;
				result = v11;
			}
		}
		else
		{
			LogAddTD(
				"Error-L3 [ChaosCastleFinalDBSet][WZ_All_GetAndUpdate_RewardInfoOfUnityBattleField] [ServerKind:%d][%s][%d][%d]",
				btServerKind,
				szName,
				nServerCode,
				btContentsType);
			this->m_DBQuery.Clear();
			v10 = 0;
			v16 = -1;
			result = v10;
		}
	}
	else
	{
		LogAddC(
			2,
			 "%s] ؎֥ ߡׯ %s %d",
			szName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}
// 5CD8D8: using guessed type int `ChaosCastleFinalDBSet::GetWinAllRewardInfoOfUBF'::`2'::__LINE__Var;

//----- (004336F0) --------------------------------------------------------
int ChaosCastleFinalDBSet::SetReceivedWinnerItemOfUBF(char *szCharName, int nServerCode, char btReceived, char *SubResult)
{
	int result; // eax
	int v6; // eax
	unsigned int v7; // eax
	int v9; // [esp+14h] [ebp-128h]
	int v10; // [esp+20h] [ebp-11Ch]
	__int16 sqlReturn; // [esp+F8h] [ebp-44h]
	CString qSql; // [esp+104h] [ebp-38h]
	char szName[11]; // [esp+110h] [ebp-2Ch]
	int v15; // [esp+138h] [ebp-4h]


	if (this->m_DBQuery.IsConnected())
	{
		szName[10] = 0;
		memcpy(szName, szCharName, 0xAu);
		//strlen(szName);
		if (strlen(szName) && (strlen(szName) <= 0xA))
		{
			v15 = 0;
			qSql.Format("EXEC WZ_UnityBattleField_SetReceivedWinnerItem_r '%s', %d, %d",
				szName,
				nServerCode,
				btReceived);
			if (this->m_DBQuery.Exec(qSql))
			{
				sqlReturn = this->m_DBQuery.Fetch();
				if (sqlReturn != 100 && sqlReturn != -1)
				{
					*SubResult = this->m_DBQuery.GetInt(1);
					this->m_DBQuery.Clear();
					v15 = -1;
					result = 1;
				}
				else
				{
					LogAddTD(
						"Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleField_SetReceivedWinnerItem_r] [%s][%d] Return %d,%s,%d ",
						szName,
						nServerCode,
						sqlReturn, __FILE__, __LINE__);
					this->m_DBQuery.Clear();
					v10 = 0;
					v15 = -1;
					result = v10;
				}
			}
			else
			{
				LogAddTD(
					"Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleField_SetReceivedWinnerItem_r] [%s][%d][%d]",
					szName,
					nServerCode,
					btReceived);
				this->m_DBQuery.Clear();
				v9 = 0;
				v15 = -1;
				result = v9;
			}
		}
		else
		{
			LogAddC(
				2,
				 "%s] ؎֥ ߡׯ %s %d",
				szName, __FILE__, __LINE__);
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
// 5CD8DC: using guessed type int `ChaosCastleFinalDBSet::SetReceivedWinnerItemOfUBF'::`2'::__LINE__Var;

//----- (004339B0) --------------------------------------------------------
int ChaosCastleFinalDBSet::SetCancelToJionUnityBattlefiled(char *szAccountID, char *szName, __int16 GameServerCode, char *subResult)
{
	int result; // eax
	int v6; // eax
	unsigned int v7; // eax
	int v8; // eax
	unsigned int v9; // eax
	int v11; // [esp+14h] [ebp-148h]
	int v12; // [esp+20h] [ebp-13Ch]
	__int16 sqlReturn; // [esp+F8h] [ebp-64h]
	CString qSql; // [esp+104h] [ebp-58h]
	char Return; // [esp+113h] [ebp-49h]
	char szCharName[11]; // [esp+11Ch] [ebp-40h]
	char szId[11]; // [esp+130h] [ebp-2Ch]
	int v19; // [esp+158h] [ebp-4h]


	if (this->m_DBQuery.IsConnected())
	{
		szId[10] = 0;
		memcpy(szId, szAccountID, 0xAu);
		szCharName[10] = 0;
		memcpy(szCharName, szName, 0xAu);
		Return = 0;
		/*strlen(szId)*/;
		if (strlen(szId) && (strlen(szId) <= 0xA))
		{
			/*strlen(szCharName)*/;
			if (strlen(szCharName) && (strlen(szCharName) <= 0xA))
			{
				v19 = 0;
				qSql.Format("EXEC WZ_UnityBattleFieldCancelToJoin_r '%s','%s',%d",
					szId,
					szCharName,
					GameServerCode);
				if (this->m_DBQuery.Exec(qSql))
				{
					sqlReturn = this->m_DBQuery.Fetch();
					if (sqlReturn != 100 && sqlReturn != -1)
					{
						*subResult = this->m_DBQuery.GetInt(1);
						this->m_DBQuery.Clear();
						v19 = -1;
						result = 1;
					}
					else
					{
						LogAddTD(
							"Error-L3 [ChaosCastleFinalDBSet][SetCancelToJionUnityBattlefiled] [%s][%d] Return %d,%s,%d ",
							szName,
							GameServerCode,
							sqlReturn, __FILE__, __LINE__);
						this->m_DBQuery.Clear();
						v12 = 0;
						v19 = -1;
						result = v12;
					}
				}
				else
				{
					LogAddTD("Error-L3 [UBF][WZ_UnityBattleFieldCancelToJoin_r] [%s][%s][%d]", szId, szCharName, GameServerCode);
					this->m_DBQuery.Clear();
					v11 = 0;
					v19 = -1;
					result = v11;
				}
			}
			else
			{
				LogAddC(
					2,
					 "%s] ؎֥ ߡׯ %s %d",
					szId, __FILE__, __LINE__);
				result = 0;
			}
		}
		else
		{
			LogAddC(
				2,
				 "%s] ؎֥ ߡׯ %s %d",
				szId, __FILE__, __LINE__);
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
// 5CD8E0: using guessed type int `ChaosCastleFinalDBSet::SetCancelToJionUnityBattlefiled'::`2'::__LINE__Var;

//----- (00433CF0) --------------------------------------------------------
char ChaosCastleFinalDBSet::DeleteCharacterUnityBattlefiled(char *szAccountID, char *szName, __int16 GameServerCode)
{
	char result; // al
	int v5; // eax
	unsigned int v6; // eax
	int v7; // eax
	unsigned int v8; // eax
	char v10; // [esp+17h] [ebp-145h]
	char v11; // [esp+23h] [ebp-139h]
	char v12; // [esp+2Fh] [ebp-12Dh]
	__int16 sqlReturn; // [esp+F8h] [ebp-64h]
	CString qSql; // [esp+104h] [ebp-58h]
	char Return; // [esp+113h] [ebp-49h]
	char szCharName[11]; // [esp+11Ch] [ebp-40h]
	char szId[11]; // [esp+130h] [ebp-2Ch]
	int v19; // [esp+158h] [ebp-4h]


	if (this->m_DBQuery.IsConnected())
	{
		szId[10] = 0;
		memcpy(szId, szAccountID, 0xAu);
		szCharName[10] = 0;
		memcpy(szCharName, szName, 0xAu);
		Return = 0;
		//strlen(szId);
		if (strlen(szId) && (strlen(szId), v6 <= 0xA))
		{
			//strlen(szCharName);
			if (strlen(szCharName) && (strlen(szCharName) <= 0xA))
			{
				v19 = 0;
				qSql.Format("EXEC WZ_UnityBattleFieldDeleteCharacter_r '%s','%s',%d",
					szId,
					szCharName,
					GameServerCode);
				if (this->m_DBQuery.Exec(qSql))
				{
					sqlReturn = this->m_DBQuery.Fetch();
					if (sqlReturn != 100 && sqlReturn != -1)
					{
						Return = this->m_DBQuery.GetInt(1);
						this->m_DBQuery.Clear();
						v12 = Return;
						v19 = -1;
						result = v12;
					}
					else
					{
						LogAddTD(
							"Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldDeleteCharacter_r] [%s] Return %d,%s,%d ",
							szCharName,
							sqlReturn, __FILE__, __LINE__);
						this->m_DBQuery.Clear();
						v11 = 0;
						v19 = -1;
						result = v11;
					}
				}
				else
				{
					this->m_DBQuery.Clear();
					LogAddTD(
						"Error-L3 [UBF][WZ_UnityBattleFieldDeleteCharacter_r] [%s][%s][%d]",
						szId,
						szCharName,
						GameServerCode);
					v10 = 2;
					v19 = -1;
					result = v10;
				}
			}
			else
			{
				LogAddC(
					2,
					 "%s] ؎֥ ߡׯ %s %d",
					szId, __FILE__, __LINE__);
				result = 0;
			}
		}
		else
		{
			LogAddC(
				2,
				 "%s] ؎֥ ߡׯ %s %d",
				szId, __FILE__, __LINE__);
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
// 5CD8E4: using guessed type int `ChaosCastleFinalDBSet::DeleteCharacterUnityBattlefiled'::`2'::__LINE__Var;

//----- (00434020) --------------------------------------------------------
int ChaosCastleFinalDBSet::GetRealNameAndServerCode(char *szUBFName, PMSG_ANS_GET_UBF_REAL_NAME *pMsg)
{
	int result; // eax
	int v4; // eax
	unsigned int v5; // eax
	int v7; // [esp+14h] [ebp-128h]
	int v8; // [esp+20h] [ebp-11Ch]
	__int16 sqlReturn; // [esp+F8h] [ebp-44h]
	CString qSql; // [esp+104h] [ebp-38h]
	char szCahrUBFName[11]; // [esp+110h] [ebp-2Ch]
	int v13; // [esp+138h] [ebp-4h]


	if (this->m_DBQuery.IsConnected())
	{
		szCahrUBFName[10] = 0;
		memcpy(szCahrUBFName, szUBFName, 0xAu);
		//strlen(szCahrUBFName);
		if (strlen(szCahrUBFName) && (strlen(szCahrUBFName) <= 0xA))
		{
			v13 = 0;
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
					v13 = -1;
					result = 1;
				}
				else
				{
					LogAddTD(
						"Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldGetRealName_r] [%s] Return %d,%s,%d ",
						szCahrUBFName,
						sqlReturn, __FILE__, __LINE__);
					this->m_DBQuery.Clear();
					v8 = 0;
					v13 = -1;
					result = v8;
				}
			}
			else
			{
				LogAddTD("Error-L3 [UBF][WZ_UnityBattleFieldGetRealName_r] [%s]", szCahrUBFName);
				this->m_DBQuery.Clear();
				v7 = 0;
				v13 = -1;
				result = v7;
			}
		}
		else
		{
			LogAddC(
				2,
				 "%s] ؎֥ ߡׯ %s %d",
				szUBFName, __FILE__, __LINE__);
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
// 5CD8E8: using guessed type int `ChaosCastleFinalDBSet::GetRealNameAndServerCode'::`2'::__LINE__Var;

//----- (004342F0) --------------------------------------------------------
int ChaosCastleFinalDBSet::GetRealNameAndServerCode(char *szUBFName, char *szRealName, int *ServerCode, int IsUBFServer)
{
	int result; // eax
	int v6; // eax
	unsigned int v7; // eax
	int v9; // [esp+14h] [ebp-128h]
	int v10; // [esp+20h] [ebp-11Ch]
	__int16 sqlReturn; // [esp+F8h] [ebp-44h]
	CString qSql; // [esp+104h] [ebp-38h]
	char szCahrUBFName[11]; // [esp+110h] [ebp-2Ch]
	int v15; // [esp+138h] [ebp-4h]


	if (this->m_DBQuery.IsConnected())
	{
		szCahrUBFName[10] = 0;
		memcpy(szCahrUBFName, szUBFName, 0xAu);
		strlen(szCahrUBFName);
		if (strlen(szCahrUBFName) && (strlen(szCahrUBFName) <= 0xA))
		{
			v15 = 0;
			qSql.Format("EXEC WZ_UnityBattleFieldGetRealName_r '%s'",
				szCahrUBFName);
			if (this->m_DBQuery.Exec(qSql))
			{
				sqlReturn = this->m_DBQuery.Fetch();
				if (sqlReturn != 100 && sqlReturn != -1)
				{
					this->m_DBQuery.GetStr("Name", szRealName);
					*ServerCode = this->m_DBQuery.GetInt("ServerCode");
					this->m_DBQuery.Clear();
					v15 = -1;
					result = 1;
				}
				else
				{
					LogAddTD(
						"Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldGetRealName_r] [%s] Return %d,%s,%d ",
						szCahrUBFName,
						sqlReturn, __FILE__, __LINE__);
					this->m_DBQuery.Clear();
					v10 = 0;
					v15 = -1;
					result = v10;
				}
			}
			else
			{
				LogAddTD("Error-L3 [UBF][WZ_UnityBattleFieldGetRealName_r] [%s]", szCahrUBFName);
				this->m_DBQuery.Clear();
				v9 = 0;
				v15 = -1;
				result = v9;
			}
		}
		else
		{
			LogAddC(
				2,
				 "%s] ؎֥ ߡׯ %s %d",
				szUBFName, __FILE__, __LINE__);
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
// 5CD8EC: using guessed type int `ChaosCastleFinalDBSet::GetRealNameAndServerCode'::`2'::__LINE__Var;

//----- (004345B0) --------------------------------------------------------
int ChaosCastleFinalDBSet::SetRewardInfoOfUnityBattleField(char *btResult, char btServerKind, char *szAccountID, char *szName, __int16 wServerCode, char btContentsType, char btSubContentsType, int iItemCode, char btItemCount, char btTakeState)
{
	int v11; // eax
	unsigned int v12; // eax
	int v13; // eax
	unsigned int v14; // eax
	int result; // eax
	int v17; // [esp+14h] [ebp-148h]
	int v18; // [esp+20h] [ebp-13Ch]
	__int16 sqlReturn; // [esp+104h] [ebp-58h]
	CString qSql; // [esp+110h] [ebp-4Ch]
	char szCahrName[11]; // [esp+11Ch] [ebp-40h]
	char szId[11]; // [esp+130h] [ebp-2Ch]
	int v24; // [esp+158h] [ebp-4h]


	szId[10] = 0;
	memcpy(szId, szAccountID, 0xAu);
	szCahrName[10] = 0;
	memcpy(szCahrName, szName, 0xAu);
	//strlen(szCahrName);
	if (strlen(szCahrName) && (strlen(szCahrName) <= 0xA) &&
		(strlen(szId)) && (strlen(szId) <= 0xA))
#pragma warning "check this!!!"
	{
		v24 = 0;
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
				v24 = -1;
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
				v18 = 0;
				v24 = -1;
				result = v18;
			}
		}
		else
		{
			LogAddTD(
				"Error-L3 [UBF][WZ_Set_RewardInfoOfUnityBattleField] [%s][%s][%d][%d]",
				szId,
				szCahrName,
				btContentsType,
				btTakeState);
			this->m_DBQuery.Clear();
			v17 = 0;
			v24 = -1;
			result = v17;
		}
	}
	else
	{
		LogAddC(
			2,
			 "%s] ؎֥ ߡׯ %s %d",
			szCahrName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}