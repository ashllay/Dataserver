#include "StdAfx.h"
#include "ArcaBattleDBSet.h"

CArcaBattleDBSet::CArcaBattleDBSet()
{
}

CArcaBattleDBSet::~CArcaBattleDBSet()
{
}

BOOL CArcaBattleDBSet::Connect()
{
	//return this->CDBConBase::Connect(szDbConnectID, szDbConnectPass);
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("CArcaBattleDBSet ODBC Connect Fail");
	return 0;
}

int CArcaBattleDBSet::DBSelectArcaBattleGuildJoin(char *szName, int *iResult)
{
	int result;
	__int16 sqlReturn;
	CString QueryStr;
	int iReturnCode = 0;
	int iItemCount = 0;

	QueryStr.Format(
		"WZ_ArcaBattleGuildSelect '%s'",
		szName);
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != 100 && sqlReturn != -1)
		{
			*iResult = this->m_DBQuery.GetInt(1);
			if (*iResult == -1)
			{
				this->m_DBQuery.Clear();
				LogAddTD(
					"error-L3 : [ArcaBattle] GuildInsert #3 %s %d", __FILE__, __LINE__);
				result = 0;
			}
			else
			{
				this->m_DBQuery.Clear();
				result = 1;
			}
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD(
				"error-L3 : [ArcaBattle] GuildSelect #2 %d %s %d",
				sqlReturn, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD(
			"error-L3 : [ArcaBattle] GuildSelect #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}
// 5CD7B4: using guessed type int `CArcaBattleDBSet::DBSelectArcaBattleGuildJoin'::`2'::__LINE__Var;

//----- (00429310) --------------------------------------------------------
int CArcaBattleDBSet::DBInsertArcaBattleGuildJoin(char *szName, char *szGuildName, unsigned int dwGuild, int *iResult)
{
	int result; // eax
	__int16 sqlReturn; // [esp+104h] [ebp-44h]
	CString QueryStr; // [esp+110h] [ebp-38h]
	int iReturnCode; // [esp+11Ch] [ebp-2Ch]
	int iItemCount; // [esp+128h] [ebp-20h]

	iItemCount = 0;
	iReturnCode = 0;

	QueryStr.Format("WZ_ArcaBattleGuildInsert '%s', '%s', %d ",szGuildName,szName,dwGuild);
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != 100 && sqlReturn != -1)
		{
			*iResult = this->m_DBQuery.GetInt(1);
			if (*iResult == -1)
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [ArcaBattle] GuildInsert #3 %s %d", __FILE__, __LINE__);
				result = 0;
			}
			else
			{
				this->m_DBQuery.Clear();
				result = 1;
			}
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] GuildInsert #2 %d %s %d",sqlReturn, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildInsert #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}
// 5CD7B8: using guessed type int `CArcaBattleDBSet::DBInsertArcaBattleGuildJoin'::`2'::__LINE__Var;

//----- (00429570) --------------------------------------------------------
int CArcaBattleDBSet::DBInsertArcaBattleGuildMemberJoin(char *szName, char *szGuildName, unsigned int dwGuild, int *iResult)
{
	int result; 
	__int16 sqlReturn;
	CString QueryStr;
	int iReturnCode;
	int iItemCount;

	iItemCount = 0;
	iReturnCode = 0;

	QueryStr.Format("WZ_ArcaBattleGuildMemberInsert '%s', '%s', %d ",szGuildName,szName,dwGuild);
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != 100 && sqlReturn != -1)
		{
			*iResult = this->m_DBQuery.GetInt(1);
			if (*iResult == -1)
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [ArcaBattle] GuildMemberInsert #3 %s %d", __FILE__, __LINE__);
				result = 0;
			}
			else
			{
				this->m_DBQuery.Clear();
				result = 1;
			}
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] GuildMemberInsert #2 %d %s %d",sqlReturn, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildMemberInsert #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


int CArcaBattleDBSet::DBInsertArcaBattleWinGuild(_stABWinGuildInfoDS *pABWinGuildInfoDS, int iGuildCnt)
{
	CString QueryStr;
	int iReturnCode;
	int iItemCount;

	iItemCount = 0;
	iReturnCode = 0;

	for (int i = 0; i < iGuildCnt; ++i)
	{
		QueryStr.Format("WZ_ArcaBattleWinGuildInsert '%s', %d, %d, %d, %d",
			&pABWinGuildInfoDS[i],
			pABWinGuildInfoDS[i].dwGuild,
			pABWinGuildInfoDS[i].wOccupyObelisk,
			pABWinGuildInfoDS[i].wObeliskGroup,
			100);
		
		if (!this->m_DBQuery.Exec(QueryStr))
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] WZ_ArcaBattleWinGuildInsert #1 %s %d", __FILE__, __LINE__);
			return 0;
		}
		this->m_DBQuery.Clear();
	}
	this->m_DBQuery.Clear();
	return 1;
}


int CArcaBattleDBSet::DBSelectArcaBattleWinGuild(_stABWinGuildInfoDS *pABGuildInfo, int *iGuildCnt)
{
	int result;
	__int16 sqlReturn;
	CString QueryStr;
	int iCnt;
	int iReturnCode;
	int iItemCount; 

	iItemCount = 0;
	iReturnCode = 0;
	iCnt = 0;

	QueryStr.Format("WZ_ArcaBattleWinGuildSelect");
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		for (sqlReturn = this->m_DBQuery.Fetch(); sqlReturn != 100; sqlReturn = this->m_DBQuery.Fetch())
		{
			if (sqlReturn == -1)
				break;
			this->m_DBQuery.GetStr("G_Name", pABGuildInfo[iCnt].szGuildName);
			pABGuildInfo[iCnt].wOccupyObelisk = this->m_DBQuery.GetInt("OuccupyObelisk");
			pABGuildInfo[iCnt++].wObeliskGroup = this->m_DBQuery.GetInt("ObeliskGroup");
			if (iCnt >= 5)
				break;
		}
		*iGuildCnt = iCnt;
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] WZ_ArcaBattleWinGuildSelect #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


int CArcaBattleDBSet::DBIsArcaBattleEnter(char *szName, int *iResult)
{
	int result;
	__int16 sqlReturn;
	CString QueryStr;
	int iReturnCode;
	int iItemCount;

	iItemCount = 0;
	iReturnCode = 0;

	QueryStr.Format("WZ_ArcaBattleMemberSelect '%s'",szName);
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != 100 && sqlReturn != -1)
		{
			*iResult = this->m_DBQuery.GetInt(1);
			if (*iResult == -1)
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [ArcaBattle] DBIsArcaBattleEnter #3 %s %d", __FILE__, __LINE__);
				result = 0;
			}
			else
			{
				this->m_DBQuery.Clear();
				result = 1;
			}
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBIsArcaBattleEnter #2 %d %s %d",sqlReturn, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBIsArcaBattleEnter #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


int CArcaBattleDBSet::DBSelectArcaBattleGuildGroupNum(char *szName, int *iGroupNum)
{
	int result; 
	__int16 sqlReturn;
	CString QueryStr;
	int iReturnCode;
	int iItemCount;

	iItemCount = 0;
	iReturnCode = 0;

	QueryStr.Format("WZ_ArcaBattleGuildGroupNumSelect '%s'",szName);
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn == 100)
		{
			this->m_DBQuery.Clear();
			result = 2;
		}
		else if (sqlReturn != 100 && sqlReturn != -1)
		{
			*iGroupNum = this->m_DBQuery.GetInt(1);
			this->m_DBQuery.Clear();
			result = 1;
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleGuildGroupNum #2 %d %s %d",sqlReturn, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleGuildGroupNum #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


int CArcaBattleDBSet::DBDeleteArcaBattleInfo()
{
	int result; // eax
	CString QueryStr; // [esp+F8h] [ebp-38h]
	int iReturnCode; // [esp+104h] [ebp-2Ch]
	int iItemCount; 

	iItemCount = 0;
	iReturnCode = 0;

	QueryStr.Format("WZ_ArcaBattleInfoDelete");
	if (this->m_DBQuery.Exec(QueryStr))
	{
		if (this->m_DBQuery.Fetch() == 100)
		{
			this->m_DBQuery.Clear();
			result = -1;
		}
		else
		{
			iReturnCode = this->m_DBQuery.GetInt(1);
			this->m_DBQuery.Clear();
			result = 1;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleInfo #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


int CArcaBattleDBSet::DBSelectArcaBattleJoinMemberUnder(_stGuildUnderMember *pGuildMemberCnt, char *btGuildCnt)
{
	int result; // eax
	__int16 sqlReturn; // [esp+11Ch] [ebp-50h]
	int iCnt; // [esp+128h] [ebp-44h]
	CString QueryStr; // [esp+134h] [ebp-38h]
	int iReturnCode; // [esp+140h] [ebp-2Ch]
	int iItemCount; // [esp+14Ch] [ebp-20h]
					// [esp+158h] [ebp-14h]
	int v17; // [esp+168h] [ebp-4h]


	iItemCount = 0;
	iReturnCode = 0;

	v17 = 0;
	iCnt = 0;
	QueryStr.Format("WZ_ArcaBattleGuildNamesSelect");
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		for (sqlReturn = this->m_DBQuery.Fetch(); sqlReturn != 100; sqlReturn = this->m_DBQuery.Fetch())
		{
			if (sqlReturn == -1)
				break;
			this->m_DBQuery.GetStr("G_Name", pGuildMemberCnt[iCnt++].szGuildNames);
			if (iCnt >= 6)
				break;
		}
		*btGuildCnt = iCnt;
		this->m_DBQuery.Clear();
		for (int i = 0; i < iCnt; ++i)
		{
			QueryStr.Format("WZ_ArcaBattleMemberUnderSelect '%s'",
				pGuildMemberCnt[i].szGuildNames);
			
			if (!this->m_DBQuery.Exec(QueryStr))
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleJoinMemberUnder #2 %s %d",__FILE__, __LINE__);
				return 0;
			}
			sqlReturn = this->m_DBQuery.Fetch();
			if (sqlReturn == 100 || sqlReturn == -1)
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleJoinMemberUnder #3 %d %s %d", sqlReturn, __FILE__, __LINE__);
				return 0;
			}
			pGuildMemberCnt[i].btGuildMemberCnt = this->m_DBQuery.GetInt(1);
			this->m_DBQuery.Clear();
		}
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleJoinMemberUnder #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


int CArcaBattleDBSet::DBInsertArcaBattleProc(int iABProc)
{
	int result; 
	__int16 sqlReturn;
	CString QueryStr;

	QueryStr.Format("WZ_ArcaBattleProcInsert %d", iABProc);
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != 100 && sqlReturn != -1)
		{
			this->m_DBQuery.Clear();
			result = 1;
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBInsertArcaBattleProc #2 %d %s %d",sqlReturn, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBInsertArcaBattleProc #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


int CArcaBattleDBSet::DBSelectArcaBattleProc(int *iABProc)
{
	int result;
	__int16 sqlReturn;
	CString QueryStr; 

	QueryStr.Format("WZ_ArcaBattleProcSelect");
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn == 100)
		{
			this->m_DBQuery.Clear();
			result = 0;
		}
		else if (sqlReturn != 100 && sqlReturn != -1)
		{
			*iABProc = this->m_DBQuery.GetInt(1);
			this->m_DBQuery.Clear();
			result = 1;
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleProc #2 %d %s %d",sqlReturn, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleProc #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


int CArcaBattleDBSet::DBSelectArcaBattleCancelGuild(_stCancelGuildNames *pstCancelGuildNames, int iMinGuildMemNum, char *btGuildCnt)
{
	int result;
	int iResult;
	__int16 sqlReturn;
	_stCancelGuildNames CancelGuildNames[6];
	int iCancelGuildCnt;
	int iCnt;
	CString QueryStr;

	iCnt = 0;
	iCancelGuildCnt = 0;
	QueryStr.Format("WZ_ArcaBattleGuildNamesSelect");

	if (this->m_DBQuery.Exec(QueryStr))
	{
		for (sqlReturn = this->m_DBQuery.Fetch(); sqlReturn != 100; sqlReturn = this->m_DBQuery.Fetch())
		{
			if (sqlReturn == -1)
				break;
			this->m_DBQuery.GetStr("G_Name", CancelGuildNames[iCnt++].szGuildNames);
			if (iCnt >= 6)
				break;
		}
		this->m_DBQuery.Clear();
		for (int i = 0; i < iCnt; ++i)
		{
			QueryStr.Format("WZ_ArcaBattleMinGuildSelect '%s', %d",
				&CancelGuildNames[i],
				iMinGuildMemNum);
			if (!this->m_DBQuery.Exec(QueryStr))
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleCancelGuild #2 %s %d", __FILE__, __LINE__);
				return 0;
			}
			sqlReturn = this->m_DBQuery.Fetch();
			if (sqlReturn == 100 || sqlReturn == -1)
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleCancelGuild #3 %d %s %d", sqlReturn, __FILE__, __LINE__);
				return 0;
			}
			iResult = this->m_DBQuery.GetInt(1);
			if (iResult < 0)
			{
				memcpy(pstCancelGuildNames[iCancelGuildCnt].szGuildNames, CancelGuildNames[i].szGuildNames, 8u);
				pstCancelGuildNames[iCancelGuildCnt++].szGuildNames[8] = 0;
			}
			this->m_DBQuery.Clear();
		}
		if (DBDeleteArcaBattleCancelGuild(pstCancelGuildNames, iCancelGuildCnt))
		{
			*btGuildCnt = iCancelGuildCnt;
			result = 1;
		}
		else
		{
			result = 0;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleCancelGuild #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


int CArcaBattleDBSet::DBDeleteArcaBattleCancelGuild(_stCancelGuildNames *pstCancelGuildNames, int iGuildCnt)
{
	int iReturnCode;
	CString QueryStr;

	iReturnCode = 0;
	for (int i = 0; i < iGuildCnt; ++i)
	{
		QueryStr.Format(
			"WZ_ArcaBattleMinGuildDelete '%s'",&pstCancelGuildNames[i]);
		
		if (!this->m_DBQuery.Exec(QueryStr))
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleCancelGuild #1 %s %d", __FILE__, __LINE__);
			return 0;
		}
		if (this->m_DBQuery.Fetch() == 100)
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleCancelGuild #2 %s %d", __FILE__, __LINE__);
			return 0;
		}
		iReturnCode = this->m_DBQuery.GetInt(1);
		this->m_DBQuery.Clear();
	}
	return 1;
}


int CArcaBattleDBSet::DBSelectABRegisteredMemberCnt(unsigned int dwGuild, char *btRegMemCnt)
{
	int result; // eax
	__int16 sqlReturn;
	int iReturnCode;
	CString QueryStr;

	iReturnCode = 0;
	QueryStr.Format("WZ_ArcaBattleGuildMemberSelect %d",dwGuild);
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != 100 && sqlReturn != -1)
		{
			iReturnCode = this->m_DBQuery.GetInt(1);
			if (iReturnCode == -1)
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [ArcaBattle] GuildMemberSelect #3 %s %d", __FILE__, __LINE__);
				result = 0;
			}
			else
			{
				*btRegMemCnt = iReturnCode;
				this->m_DBQuery.Clear();
				result = 1;
			}
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] GuildMemberSelect #2 %d %s %d",sqlReturn, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildMemberSelect #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


int CArcaBattleDBSet::DBSelectArcaBattleIsTopRank(unsigned int dwGuildNumber)
{
	int result;
	int iResult;
	__int16 sqlReturn;
	CString QueryStr; 

	QueryStr.Format("WZ_ArcaBattleMarkRankSelect %d",dwGuildNumber);
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn == 100)
		{
			this->m_DBQuery.Clear();
			result = -1;
		}
		else if (sqlReturn != 100 && sqlReturn != -1)
		{
			iResult = this->m_DBQuery.GetInt(1);
			if (iResult > 6 || iResult <= 0)
				iResult = 6;
			else
				iResult = 0;
			this->m_DBQuery.Clear();
			result = iResult;
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleIsTopRank #2 %d %s %d",sqlReturn, __FILE__, __LINE__);
			result = -1;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleIsTopRank #1 %s %d", __FILE__, __LINE__);
		result = -1;
	}
	return result;
}


int CArcaBattleDBSet::DBSelectArcaBattleMarkCnt(unsigned int dwGuildNumber)
{
	int result;
	int iResult;
	__int16 sqlReturn;
	CString QueryStr;

	QueryStr.Format("WZ_ArcaBattleMarkCntSelect %d",dwGuildNumber);
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn == 100)
		{
			this->m_DBQuery.Clear();
			result = -2;
		}
		else if (sqlReturn != 100 && sqlReturn != -1)
		{
			iResult = this->m_DBQuery.GetInt(1);
			this->m_DBQuery.Clear();
			result = iResult;
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleMarkCnt #2 %d %s %d",sqlReturn, __FILE__, __LINE__);
			result = -2;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleMarkCnt #1 %s %d", __FILE__, __LINE__);
		result = -2;
	}
	return result;
}


int CArcaBattleDBSet::DBInsertArcaBattleRegMark(char *szGuildName, unsigned int dwGuildNum, char *szGuildMaster, unsigned int dwMarkCnt)
{
	int result;
	__int16 sqlReturn;
	CString QueryStr; 

	QueryStr.Format("WZ_ArcaBattleMarkInsert '%s', %d, '%s', %u",
		szGuildName,dwGuildNum,szGuildMaster,dwMarkCnt);
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != 100 && sqlReturn != -1)
		{
			this->m_DBQuery.Clear();
			result = 1;
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBInsertArcaBattleRegMark #2 %d %s %d",sqlReturn, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBInsertArcaBattleRegMark #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


int CArcaBattleDBSet::DBSelectArcaBattleTopRank(_stArcaBattleMarkTopRank *pArcaBattleMarkTopRank, char *btGuildCnt)
{
	int result;
	__int16 sqlReturn;
	CString QueryStr;

	QueryStr.Format("WZ_ArcaBattleTopRankSelect");
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn == 100)
		{
			this->m_DBQuery.Clear();
			result = 0;
		}
		else
		{
			int iCnt = 0;
			while (sqlReturn != 100)
			{
				if (sqlReturn == -1)
					break;
				this->m_DBQuery.GetStr("G_Name", pArcaBattleMarkTopRank[iCnt].szGuildNames);
				pArcaBattleMarkTopRank[iCnt].dwMarkCnt = this->m_DBQuery.GetInt64("MarkCnt");
				pArcaBattleMarkTopRank[iCnt].btRank = iCnt + 1;
				if (++iCnt >= 6)
					break;
				sqlReturn = this->m_DBQuery.Fetch();
			}
			*btGuildCnt = iCnt;
			this->m_DBQuery.Clear();
			result = 1;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleTopRank #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}
// 5CD7F8: using guessed type int `CArcaBattleDBSet::DBSelectArcaBattleTopRank'::`2'::__LINE__Var;

//----- (0042BAA0) --------------------------------------------------------
int CArcaBattleDBSet::DBSelectArcaBattleMyGuildRank(unsigned int dwGuildNumber, char *btMyGuildRank, unsigned int *dwMarkCnt)
{
	char *v4; // eax
	int result; // eax
	int v6; // [esp+14h] [ebp-11Ch]
	int v7; // [esp+2Ch] [ebp-104h]
	__int16 sqlReturn; // [esp+104h] [ebp-2Ch]
	CString QueryStr; // [esp+110h] [ebp-20h]
					  // [esp+11Ch] [ebp-14h]
	int v11; // [esp+12Ch] [ebp-4h]



	v11 = 0;
	QueryStr.Format(
		"WZ_ArcaBattleMarkRankSelect %d",
		dwGuildNumber);
	if (this->m_DBQuery.Exec(QueryStr))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn == 100)
		{
			this->m_DBQuery.Clear();
			v11 = -1;
			result = 0;
		}
		else if (sqlReturn != 100 && sqlReturn != -1)
		{
			*btMyGuildRank = this->m_DBQuery.GetInt(1);
			*dwMarkCnt = this->m_DBQuery.GetInt64(2);
			this->m_DBQuery.Clear();
			v11 = -1;
			result = 1;
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD(
				"error-L3 : [ArcaBattle] DBSelectArcaBattleMarkCnt #2 %d %s %d",
				sqlReturn, __FILE__, __LINE__);
			v7 = 0;
			v11 = -1;
			result = v7;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD(
			"error-L3 : [ArcaBattle] DBSelectArcaBattleMarkCnt #1 %s %d", __FILE__, __LINE__);
		v6 = 0;
		v11 = -1;
		result = v6;
	}
	return result;
}
// 5CD7FC: using guessed type int `CArcaBattleDBSet::DBSelectArcaBattleMyGuildRank'::`2'::__LINE__Var;

//----- (0042BCE0) --------------------------------------------------------
int CArcaBattleDBSet::DBDeleteArcaBattleMarkReg(unsigned int dwGuildNumber)
{
	int result;
	int iResult;
	__int16 sqlReturn;
	CString QueryStr;

	QueryStr.Format("WZ_ArcaBattleMarkRegDel %d",dwGuildNumber);
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != 100 && sqlReturn != -1)
		{
			iResult = this->m_DBQuery.GetInt(1);
			if (iResult == -1)
				LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleMarkReg #3 %d %s %d",
					sqlReturn, __FILE__, __LINE__);
			this->m_DBQuery.Clear();
			result = 1;
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleMarkReg #2 %d %s %d",
				sqlReturn, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleMarkReg #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


void CArcaBattleDBSet::DBDeleteAllArcaBattleGuildReg()
{
	CString QueryStr;
	int v4;
	v4 = 0;
	QueryStr.Format("WZ_ArcaBattleGuildMarkInfoAllDel");
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		this->m_DBQuery.Clear();
		v4 = -1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBDeleteAllArcaBattleGuildReg %s %d", __FILE__, __LINE__);
		v4 = -1;
	}
}


void CArcaBattleDBSet::DBDeleteArcaBattleGuildReg()
{
	CString QueryStr;

	QueryStr.Format("delete T_ARCA_BATTLE_MEMBER_JOIN_INFO");
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		this->m_DBQuery.Clear();
		QueryStr.Format(
			"delete T_ARCA_BATTLE_GUILD_JOIN_INFO");
		
		if (this->m_DBQuery.Exec(QueryStr))
		{
			this->m_DBQuery.Clear();
			QueryStr.Format("delete T_ARCA_BATTLE_GUILDMARK_REG");
			
			if (this->m_DBQuery.Exec(QueryStr))
			{
				this->m_DBQuery.Clear();
			}
			else
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleGuildReg #3 %s %d", __FILE__, __LINE__);
			}
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleGuildReg #2 %s %d", __FILE__, __LINE__);
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleGuildReg #1 %s %d", __FILE__, __LINE__);
	}
}


void CArcaBattleDBSet::DBUpdateArcaBattleGuildReg(BYTE *lpRecv, int aIndex)
{
	CString QueryStr;
	_tagPMSG_REQ_AB_MARK_REG_UPDATE_DS *lpMsg;
	lpMsg = (_tagPMSG_REQ_AB_MARK_REG_UPDATE_DS *)lpRecv;


	QueryStr.Format("UPDATE T_ARCA_BATTLE_GUILDMARK_REG SET MarkCnt = %d WHERE G_Number = %d",lpMsg->dwMarkCnt,lpMsg->dwGuildNum);
	
	if (this->m_DBQuery.Exec(QueryStr))
	{
		this->m_DBQuery.Clear();
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleGuildReg #1 %s %d", __FILE__, __LINE__);
	}
}


void CArcaBattleDBSet::DBSelectArcaBattleAllGuildMark(_stABAllGuildMark *pABAllGuildMark, int *iGuildCnt)
{
	SQLRETURN i; // [esp+D4h] [ebp-FE4h]
	CString QueryStr;
	_stABAllGuildMark _stABAllGuildMark[250];

	QueryStr.Format("WZ_ArcaBattleAllMarkCntSelect");

	if (this->m_DBQuery.Exec(QueryStr))
	{
		int wGuildCnt = 0;
		for (i = this->m_DBQuery.Fetch(); i != 100; i = this->m_DBQuery.Fetch())
		{
			if (i == -1)
				break;
			this->m_DBQuery.GetStr("G_Name", pABAllGuildMark[wGuildCnt].szGuildName);
			pABAllGuildMark[wGuildCnt++].dwMarkCnt = this->m_DBQuery.GetInt("MarkCnt");
			if (wGuildCnt >= 250)
				break;
		}
		*iGuildCnt = wGuildCnt;
		this->m_DBQuery.Clear();
	}
	else
	{
		LogAddC(2,"Error WZ_ArcaBattleAllMarkCntSelect m_DBQuery.Exec %s %d", __FILE__, __LINE__);
		this->m_DBQuery.Clear();
	}
}

int CArcaBattleDBSet::DBSelectABAllJoinUser(_stABJoinUserInfoDS *pABJoinUserInfo, char *btUserCnt)
{
	int result;
	SQLRETURN sqlRet;
	CString szQuery;
	int iCnt = 0;
	
	szQuery.Format("WZ_ArcaBattleAllJoinUserSelect");
	if (this->m_DBQuery.Exec(szQuery))
	{
		for (sqlRet = this->m_DBQuery.Fetch(); sqlRet != 100; sqlRet = this->m_DBQuery.Fetch())
		{
			if (sqlRet == SQL_NULL_DATA)
				break;
			this->m_DBQuery.GetStr("G_Name", pABJoinUserInfo[iCnt].szGuildName);
			pABJoinUserInfo[iCnt].dwGuild = this->m_DBQuery.GetInt("Number");
			this->m_DBQuery.GetStr("CharName", pABJoinUserInfo[iCnt++].szUserName);
			if (iCnt >= 200)
				break;
		}
		*btUserCnt = iCnt;
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		LogAddC(2,"Error WZ_ArcaBattleAllJoinUserSelect m_DBQuery.Exec %s %d", __FILE__, __LINE__);
		this->m_DBQuery.Clear();
		result = 0;
	}
	return result;
}