#include "StdAfx.h"
#include "IllusionTempleLeagueDBSet.h"

IllusionTempleLeagueDBSet::IllusionTempleLeagueDBSet()
{
}

IllusionTempleLeagueDBSet::~IllusionTempleLeagueDBSet()
{
}

BOOL IllusionTempleLeagueDBSet::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("IllusionTempleLeague ODBC Connect Fail");
	return 0;
}

void IllusionTempleLeagueDBSet::SaveITLGuildCount(char *GName, BYTE byCount)
{
	__int16 sqlReturn;
	CString qSql;

	qSql.Format("WZ_ITL_UpdateGuildEnterCount '%s',%d ",
		GName,
		byCount);
	if (this->m_DBQuery.Exec(qSql))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != SQL_NO_DATA || sqlReturn != -1)
		{
			this->m_DBQuery.Clear();
		}
		else
		{
			LogAddTD(
				"Error-L2 [IllusionTempleLeague] [WZ_SaveITLGuildPoint] %d, %s , %d",
				sqlReturn, __FILE__, __LINE__);
			this->m_DBQuery.Clear();
		}
	}
	else
	{
		LogAddTD("Error-L1 [IllusionTempleLeague][WZ_ITL_UpdateGuildEnterCount] G.NAME:%s,Count:%d", GName, byCount);
		this->m_DBQuery.Clear();
	}
}


void IllusionTempleLeagueDBSet::SaveITLGuildPoint(char *szGuildName, int nType, BYTE byWin, BYTE byLose, BYTE byOccupiedCnt, BYTE byEnterCount)
{
	__int16 sqlReturn;
	CString qSql;
	qSql.Format("WZ_ITL_UpdateGuildPoint '%s',%d,%d,%d,%d,%d",
		szGuildName,
		nType,
		byWin,
		byLose,
		byOccupiedCnt,
		byEnterCount);
	if (this->m_DBQuery.Exec(qSql))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != SQL_NO_DATA || sqlReturn != -1)
		{
			this->m_DBQuery.Clear();
		}
		else
		{
			LogAddTD(
				"Error-L2 [IllusionTempleLeague] [WZ_SaveITLGuildPoint] %d, %s , %d",
				sqlReturn, __FILE__, __LINE__);
			this->m_DBQuery.Clear();
		}
	}
	else
	{
		LogAddTD(
			"Error-L1[IllusionTempleLeague][WZ_ITL_UpdateGuildPoint]G.NAME:%s,Point:%d,Type:%d,Win:%d,Lose:%d,OccCnt:%d,EnterCnt:%d",
			szGuildName,
			nType,
			byWin,
			byLose,
			byOccupiedCnt,
			byEnterCount);
		this->m_DBQuery.Clear();
	}
}


void IllusionTempleLeagueDBSet::UpdateITL_RewardReceived(char *CharName)
{
	int nRetrun;
	__int16 sqlReturn;
	CString qSql;

	qSql.Format("WZ_ITL_GiveReward '%s'", CharName);
	if (this->m_DBQuery.Exec(qSql))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != SQL_NO_DATA || sqlReturn != -1)
		{
			nRetrun = this->m_DBQuery.GetInt(1);
			if (nRetrun)
			{
				LogAddTD("WZ_ITL_GiveReward return %d", nRetrun);
				LogAddTD("WZ_ITL_GiveReward 1==NoChar,2==AlreadyReward");
			}
			this->m_DBQuery.Clear();
		}
		else
		{
			LogAddTD(
				"Error-L2 [IllusionTempleLeague] [WZ_ITL_GiveReward] %d, %s , %d",
				sqlReturn, __FILE__, __LINE__);
			this->m_DBQuery.Clear();
		}
	}
	else
	{
		LogAddTD("Error-L1 [IllusionTempleLeague][WZ_ITL_GiveReward] NAME:%s", CharName);
		this->m_DBQuery.Clear();
	}
}


void IllusionTempleLeagueDBSet::UpdateITLUserPoint(char *UserName, char *Gname, int ITLtype, int nOccupiedCount, int nKillP, int nInvalidationCount, int nEnterCount, int nWin)
{
	int nRetrun; 
	__int16 sqlReturn;
	CString qSql;

	qSql.Format("WZ_ITL_UpdateUserPoint '%s','%s', %d , %d , %d , %d, %d , %d",
		UserName,
		Gname,
		ITLtype,
		nOccupiedCount,
		nKillP,
		nInvalidationCount,
		nEnterCount,
		nWin);
	if (this->m_DBQuery.Exec(qSql))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != SQL_NO_DATA || sqlReturn != -1)
		{
			nRetrun = this->m_DBQuery.GetInt(1);
			if (nRetrun)
			{
				LogAddTD("WZ_ITL_UpdateUserPoint return %d", nRetrun);
				LogAddTD("WZ_ITL_UpdateUserPoint -1==UpdateFail, -2==InsertFail");
			}
			this->m_DBQuery.Clear();
		}
		else
		{
			LogAddTD(
				"Error-L2 [IllusionTempleLeague] [WZ_SaveITLUserPoint] %d, %s , %d",
				sqlReturn, __FILE__, __LINE__);
			this->m_DBQuery.Clear();
		}
	}
	else
	{
		LogAddTD(
			"Error-L1 [IllusionTempleLeague][WZ_ITL_UpdateUserPoint] NAME:%s,G.Name:%s,nOccupiedCount:%d,nInvalidationCount:%d,EnterCount:%d",
			UserName,
			Gname,
			nOccupiedCount,
			nKillP,
			ITLtype,
			nInvalidationCount,
			nEnterCount);
		this->m_DBQuery.Clear();
	}
}


void IllusionTempleLeagueDBSet::Renew_ITLRewardList()
{
	CString qSql; 

	qSql.Format("WZ_ITL_UserRewardRenew");
	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
	}
	else
	{
		LogAddTD("Error-L1 [Renew_ITLRewardList][WZ_ITL_UserRewardRenew]");
		this->m_DBQuery.Clear();
	}
}

void IllusionTempleLeagueDBSet::RenewITLGuildRank(BYTE byITLType)
{
	CString qSql;

	qSql.Format("WZ_ITL_RenewGuildRank %d", byITLType);
	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
	}
	else
	{
		LogAddTD("Error-L1 [RenewITLGuildRank][WZ_ITL_RenewGuildRank %d]", byITLType);
		this->m_DBQuery.Clear();
	}
}

int IllusionTempleLeagueDBSet::LoadITLGuildRank(_stITLRankingInfo *ITLRankInfo, int *btGuildCount)
{
	int result;
	__int16 sqlRetrun;
	CString qSql;
	char byCount;
	byCount = 0;

	qSql.Format("WZ_ITL_GetGuildRank");
	if (this->m_DBQuery.Exec(qSql))
	{
		for (sqlRetrun = this->m_DBQuery.Fetch(); sqlRetrun != SQL_NO_DATA; sqlRetrun = this->m_DBQuery.Fetch())
		{
			if (sqlRetrun == -1)
				break;
			ITLRankInfo[byCount].byRank = this->m_DBQuery.GetInt("mRank");
			this->m_DBQuery.GetStr("mGuildName", ITLRankInfo[byCount].szGuildName);
			ITLRankInfo[byCount].byWin = this->m_DBQuery.GetInt("mWin");
			ITLRankInfo[byCount++].byLose = this->m_DBQuery.GetInt("mLose");
			if (byCount >= 56)
				break;
		}
		*btGuildCount = byCount;
		this->m_DBQuery.Clear();
		result = 0;
	}
	else
	{
		LogAddC(
			2,
			"Error WZ_ITL_GetGuildRank m_DBQuery.Exec %s %d", __FILE__, __LINE__);
		this->m_DBQuery.Clear();
		result = -1;
	}
	return result;
}


int IllusionTempleLeagueDBSet::LoadITLRewardList(_stITLRewardList* itlRewardList, BYTE* byCount)
{
	CString qSql;

	qSql.Format("WZ_ITL_GetUserRewardList");

	if (!this->m_DBQuery.Exec(qSql))
	{
		LogAddC(LOGC_RED,"Error WZ_ITL_GetUserRewardList m_DBQuery.Exec %s %d", __FILE__, __LINE__);

		this->m_DBQuery.Clear();
		return -1;
	}

	for (short sqlReturn = this->m_DBQuery.Fetch();
		sqlReturn != SQL_NO_DATA;
		sqlReturn = this->m_DBQuery.Fetch())
	{
		if (sqlReturn == -1)
			break;

		int index = *byCount;

		itlRewardList[index].byRank = this->m_DBQuery.GetInt("mRank");
		this->m_DBQuery.GetStr("mUserName",itlRewardList[index].szCharName);
		this->m_DBQuery.GetStr("mGuildName",itlRewardList[index].szGuildName);
		itlRewardList[index].byEnterCount =this->m_DBQuery.GetInt("mEnterCount");
		itlRewardList[index].byPoint =this->m_DBQuery.GetInt("mPoint");
		itlRewardList[index].byGotReward =this->m_DBQuery.GetInt("mGotReward");

		LogAddTD(
			"[ITL][REWARD LIST] NAME:[%s], G.NAME:[%s], Enter:[%d], Point:[%d], Rank:[%d]",
			itlRewardList[index].szCharName,
			itlRewardList[index].szGuildName,
			itlRewardList[index].byEnterCount,
			itlRewardList[index].byPoint,
			itlRewardList[index].byRank);

		++(*byCount);

		if (*byCount >= 6)
			break;
	}

	this->m_DBQuery.Clear();

	return 0;
}

int IllusionTempleLeagueDBSet::LoadITLTournament(_stITLRankingInfo *ITLRanking, char *btCount, BYTE byITLType)
{
	int result;
	__int16 sqlRetrun;
	CString qSql;
	char byCount;
	byCount = 0;

	qSql.Format("WZ_ITL_GetTournament %d", byITLType);
	if (this->m_DBQuery.Exec(qSql))
	{
		for (sqlRetrun = this->m_DBQuery.Fetch(); sqlRetrun != SQL_NO_DATA; sqlRetrun = this->m_DBQuery.Fetch())
		{
			if (sqlRetrun == -1)
				break;
			ITLRanking[byCount].byRank = this->m_DBQuery.GetInt("mRank");
			this->m_DBQuery.GetStr("mGuildName", ITLRanking[byCount].szGuildName);
			ITLRanking[byCount].byITLType = this->m_DBQuery.GetInt("mITLType");
			ITLRanking[byCount].byWin = this->m_DBQuery.GetInt("mWin");
			ITLRanking[byCount].byLose = this->m_DBQuery.GetInt("mLose");
			LogAddTD(" ITL TORNA INFO RANK : %d, TYPE :%d, WIN :%d  LOSE : %d G.NAME : %s ",
				ITLRanking[byCount].byRank,
				ITLRanking[byCount].byITLType,
				ITLRanking[byCount].byWin,
				ITLRanking[byCount].byLose,
				&ITLRanking[byCount]);
			if (++byCount >= 6)
				break;
		}
		*btCount = byCount;
		LogAddTD("LoadITLTournament COunt :%d ", *btCount);
		this->m_DBQuery.Clear();
		result = 0;
	}
	else
	{
		LogAddC(LOGC_RED, "Error WZ_ITL_GetTournament m_DBQuery.Exec %s %d", __FILE__, __LINE__);
		this->m_DBQuery.Clear();
		result = -1;
	}
	return result;
}


void IllusionTempleLeagueDBSet::ReqGuildCount(char *GuildName, int *nEnterCount)
{
	__int16 sqlreturn; 
	CString qSql; 

	qSql.Format("WZ_ITL_GetGuildCnt '%s'", GuildName);
	if (this->m_DBQuery.Exec(qSql))
	{
		sqlreturn = this->m_DBQuery.Fetch();
		if (sqlreturn != SQL_NO_DATA || sqlreturn != -1)
		{
			*nEnterCount = this->m_DBQuery.GetInt("mEnterCount");
			LogAddTD("[ ITL ] GuildName :%s, Count:%d", GuildName, *nEnterCount);
			this->m_DBQuery.Clear();
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD("Error-L3 [WZ_ITL_GetGuildCnt][A2]  %d Return %s,%d ", sqlreturn, __FILE__, __LINE__);
		}
	}
	else
	{
		LogAddC(LOGC_RED, "Error WZ_ITL_GetGuildCnt m_DBQuery.Exec %s %d", __FILE__, __LINE__);
		this->m_DBQuery.Clear();
	}
}


void IllusionTempleLeagueDBSet::ReqUserItlEnterCount(char *UserName, int *nEnterCount)
{
	__int16 sqlReturn;
	CString qSql;

	qSql.Format("WZ_ITL_GetUserEnterCnt '%s'", UserName);
	if (this->m_DBQuery.Exec(qSql))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != 100 || sqlReturn != -1)
		{
			*nEnterCount = this->m_DBQuery.GetInt(1);
			this->m_DBQuery.Clear();
		}
		else
		{
			LogAddTD(
				"Error-L2 [IllusionTempleLeague] [WZ_ITL_GetUserEnterCnt] %d, %s , %d",
				sqlReturn, __FILE__, __LINE__);
			this->m_DBQuery.Clear();
		}
	}
	else
	{
		LogAddTD("Error-L1 [IllusionTempleLeague][WZ_ITL_GetUserEnterCnt] NAME:%s", UserName);
		this->m_DBQuery.Clear();
	}
}