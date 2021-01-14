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
	if (m_Query.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass) == FALSE)
	{
		MsgBox("CArcaBattleDBSet ODBC Connect Fail");
		return FALSE;
	}

	return TRUE;
}

BOOL CArcaBattleDBSet::DBSelectArcaBattleGuildJoin(char* szName, int& iResult)
{
	int iReturnCode = 0;
	int iItemCount = 0;

	CString QueryStr;
	QueryStr.Format("WZ_ArcaBattleGuildSelect '%s'", szName);

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildSelect #1 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildSelect #2 %d %s %d", sqlReturn, __FILE__, __LINE__);
		return FALSE;
	}

	iResult = m_Query.GetInt(1);

	if (iResult == -1)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildInsert #3 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	m_Query.Clear();
	return TRUE;
}

BOOL CArcaBattleDBSet::DBInsertArcaBattleGuildJoin(char* szName, char* szGuildName, DWORD dwGuild, int& iResult)
{
	int iItemCount = 0;
	int iReturnCode = 0;

	CString QueryStr;
	QueryStr.Format("WZ_ArcaBattleGuildInsert '%s', '%s', %d ", szGuildName, szName, dwGuild);

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildInsert #1 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildInsert #2 %d %s %d", sqlReturn, __FILE__, __LINE__);
		return FALSE;
	}

	iResult = m_Query.GetInt(1);

	if (iResult == -1)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildInsert #3 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	m_Query.Clear();
	return TRUE;
}

BOOL CArcaBattleDBSet::DBInsertArcaBattleGuildMemberJoin(char* szName, char* szGuildName, DWORD dwGuild, int& iResult)
{
	int iItemCount = 0;
	int iReturnCode = 0;

	CString QueryStr;
	QueryStr.Format("WZ_ArcaBattleGuildMemberInsert '%s', '%s', %d ", szGuildName, szName, dwGuild);

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildMemberInsert #1 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	SQLRETURN sqlReturn = this->m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildMemberInsert #2 %d %s %d", sqlReturn, __FILE__, __LINE__);
		return FALSE;
	}

	iResult = m_Query.GetInt(1);

	if (iResult == -1)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildMemberInsert #3 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	m_Query.Clear();
	return TRUE;
}

BOOL CArcaBattleDBSet::DBInsertArcaBattleWinGuild(_stABWinGuildInfoDS* pABWinGuildInfoDS, int iGuildCnt)
{
	int iItemCount = 0;
	int iReturnCode = 0;

	CString QueryStr;

	for (int i = 0; i < iGuildCnt; i++)
	{
		QueryStr.Format("WZ_ArcaBattleWinGuildInsert '%s', %d, %d, %d, %d", pABWinGuildInfoDS[i].szGuildName, pABWinGuildInfoDS[i].dwGuild, pABWinGuildInfoDS[i].wOccupyObelisk, pABWinGuildInfoDS[i].wObeliskGroup, 100);

		if (m_Query.Exec(QueryStr) == FALSE)
		{
			m_Query.Clear();
			LogAddTD("error-L3 : [ArcaBattle] WZ_ArcaBattleWinGuildInsert #1 %s %d", __FILE__, __LINE__);
			return FALSE;
		}

		m_Query.Clear();
	}

	m_Query.Clear();
	return TRUE;
}

BOOL CArcaBattleDBSet::DBSelectArcaBattleWinGuild(_stABWinGuildInfoDS* pABGuildInfo, int& iGuildCnt)
{
	int iItemCount = 0;
	int iReturnCode = 0;
	int iCnt = 0;

	CString QueryStr;
	QueryStr.Format("WZ_ArcaBattleWinGuildSelect");

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] WZ_ArcaBattleWinGuildSelect #1 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	while (sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
	{
		m_Query.GetStr("G_Name", pABGuildInfo[iCnt].szGuildName);
		pABGuildInfo[iCnt].wOccupyObelisk = m_Query.GetInt("OuccupyObelisk");
		pABGuildInfo[iCnt].wObeliskGroup = m_Query.GetInt("ObeliskGroup");
		iCnt++;

		if (iCnt >= MAX_AB_OBELISK_INFO)
		{
			break;
		}

		sqlReturn = m_Query.Fetch();
	}

	iGuildCnt = iCnt;
	m_Query.Clear();
	return TRUE;
}


BOOL CArcaBattleDBSet::DBIsArcaBattleEnter(char* szName, int& iResult)
{
	int iItemCount = 0;
	int iReturnCode = 0;

	CString QueryStr;
	QueryStr.Format("WZ_ArcaBattleMemberSelect '%s'", szName);

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBIsArcaBattleEnter #1 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBIsArcaBattleEnter #2 %d %s %d", sqlReturn, __FILE__, __LINE__);
		return FALSE;
	}

	iResult = m_Query.GetInt(1);

	if (iResult == -1)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBIsArcaBattleEnter #3 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	m_Query.Clear();
	return TRUE;
}

BOOL CArcaBattleDBSet::DBSelectArcaBattleGuildGroupNum(char* szName, int& iGroupNum)
{
	int iItemCount = 0;
	int iReturnCode = 0;

	CString QueryStr;
	QueryStr.Format("WZ_ArcaBattleGuildGroupNumSelect '%s'", szName);

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleGuildGroupNum #1 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA)
	{
		m_Query.Clear();
		return 2;
	}

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleGuildGroupNum #2 %d %s %d", sqlReturn, __FILE__, __LINE__);
		return FALSE;
	}

	iGroupNum = m_Query.GetInt(1);
	m_Query.Clear();
	return TRUE;
}


BOOL CArcaBattleDBSet::DBDeleteArcaBattleInfo()
{
	int iItemCount = 0;
	int iReturnCode = 0;

	CString QueryStr;
	QueryStr.Format("WZ_ArcaBattleInfoDelete");

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleInfo #1 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	if (m_Query.Fetch() == SQL_NO_DATA)
	{
		m_Query.Clear();
		return -1;
	}

	iReturnCode = m_Query.GetInt(1);
	m_Query.Clear();
	return TRUE;
}


BOOL CArcaBattleDBSet::DBSelectArcaBattleJoinMemberUnder(_stGuildUnderMember* pGuildMemberCnt, BYTE& btGuildCnt)
{
	int iItemCount = 0;
	int iReturnCode = 0;
	CString QueryStr;
	int iCnt = 0;

	QueryStr.Format("WZ_ArcaBattleGuildNamesSelect");

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleJoinMemberUnder #1 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	while (sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
	{
		m_Query.GetStr("G_Name", pGuildMemberCnt[iCnt].szGuildNames);
		iCnt++;

		if (iCnt >= 6)
		{
			break;
		}

		sqlReturn = m_Query.Fetch();
	}

	btGuildCnt = iCnt;
	m_Query.Clear();

	for (int i = 0; i < iCnt; i++)
	{
		QueryStr.Format("WZ_ArcaBattleMemberUnderSelect '%s'", pGuildMemberCnt[i].szGuildNames);

		if (m_Query.Exec(QueryStr) == FALSE)
		{
			m_Query.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleJoinMemberUnder #2 %s %d", __FILE__, __LINE__);
			return FALSE;
		}

		SQLRETURN sqlReturn = m_Query.Fetch();

		if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
		{
			m_Query.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleJoinMemberUnder #3 %d %s %d", sqlReturn, __FILE__, __LINE__);
			return FALSE;
		}

		pGuildMemberCnt[i].btGuildMemberCnt = m_Query.GetInt(1);
		m_Query.Clear();
	}

	m_Query.Clear();
	return TRUE;
}

BOOL CArcaBattleDBSet::DBInsertArcaBattleProc(int iABProc)
{
	CString QueryStr;
	QueryStr.Format("WZ_ArcaBattleProcInsert %d", iABProc);

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBInsertArcaBattleProc #1 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBInsertArcaBattleProc #2 %d %s %d", sqlReturn, __FILE__, __LINE__);
		return FALSE;
	}

	m_Query.Clear();
	return TRUE;
}

BOOL CArcaBattleDBSet::DBSelectArcaBattleProc(int& iABProc)
{
	CString QueryStr;
	QueryStr.Format("WZ_ArcaBattleProcSelect");

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleProc #1 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA)
	{
		m_Query.Clear();
		return FALSE;
	}

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleProc #2 %d %s %d", sqlReturn, __FILE__, __LINE__);
		return FALSE;
	}

	iABProc = m_Query.GetInt(1);
	m_Query.Clear();
	return TRUE;
}

BOOL CArcaBattleDBSet::DBSelectArcaBattleCancelGuild(_stCancelGuildNames* pstCancelGuildNames, int iMinGuildMemNum, BYTE& btGuildCnt)
{
	CString QueryStr;
	int iCnt = 0;
	int iCancelGuildCnt = 0;

	QueryStr.Format("WZ_ArcaBattleGuildNamesSelect");

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleCancelGuild #1 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	_stCancelGuildNames CancelGuildNames[6];
	SQLRETURN sqlReturn = m_Query.Fetch();

	while (sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
	{
		m_Query.GetStr("G_Name", CancelGuildNames[iCnt].szGuildNames);
		iCnt++;

		if (iCnt >= 6)
		{
			break;
		}

		sqlReturn = m_Query.Fetch();
	}

	m_Query.Clear();

	for (int i = 0; i < iCnt; i++)
	{
		QueryStr.Format("WZ_ArcaBattleMinGuildSelect '%s', %d", CancelGuildNames[i].szGuildNames, iMinGuildMemNum);

		if (m_Query.Exec(QueryStr) == FALSE)
		{
			m_Query.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleCancelGuild #2 %s %d", __FILE__, __LINE__);
			return FALSE;
		}

		SQLRETURN sqlReturn = m_Query.Fetch();

		if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
		{
			m_Query.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleCancelGuild #3 %d %s %d", sqlReturn, __FILE__, __LINE__);
			return FALSE;
		}

		int iResult = m_Query.GetInt(1);

		if (iResult < 0)
		{
			memcpy(pstCancelGuildNames[iCancelGuildCnt].szGuildNames, CancelGuildNames[i].szGuildNames, MAX_GUILDNAMESTRING);
			pstCancelGuildNames[iCancelGuildCnt].szGuildNames[MAX_GUILDNAMESTRING] = '\0';
			iCancelGuildCnt++;
		}

		m_Query.Clear();
	}

	BOOL bCancelGuild = DBDeleteArcaBattleCancelGuild(pstCancelGuildNames, iCancelGuildCnt);
	
	if (bCancelGuild == FALSE)
	{
		return FALSE;
	}

	btGuildCnt = iCancelGuildCnt;
	return TRUE;
}

BOOL CArcaBattleDBSet::DBDeleteArcaBattleCancelGuild(_stCancelGuildNames* pstCancelGuildNames, int iGuildCnt)
{
	CString QueryStr;
	int iReturnCode = 0;

	for (int i = 0; i < iGuildCnt; i++)
	{
		QueryStr.Format("WZ_ArcaBattleMinGuildDelete '%s'", pstCancelGuildNames[i].szGuildNames);
		
		if (m_Query.Exec(QueryStr) == FALSE)
		{
			m_Query.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleCancelGuild #1 %s %d", __FILE__, __LINE__);
			return FALSE;
		}

		if (m_Query.Fetch() == SQL_NO_DATA)
		{
			m_Query.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleCancelGuild #2 %s %d", __FILE__, __LINE__);
			return FALSE;
		}

		iReturnCode = m_Query.GetInt(1);
		m_Query.Clear();
	}

	return TRUE;
}

BOOL CArcaBattleDBSet::DBSelectABRegisteredMemberCnt(DWORD dwGuild, BYTE& btRegMemCnt)
{
	CString QueryStr;
	int iReturnCode = 0;

	QueryStr.Format("WZ_ArcaBattleGuildMemberSelect %d", dwGuild);

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildMemberSelect #1 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildMemberSelect #2 %d %s %d", sqlReturn, __FILE__, __LINE__);
		return FALSE;
	}

	iReturnCode = m_Query.GetInt(1);

	if (iReturnCode == -1)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildMemberSelect #3 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	btRegMemCnt = iReturnCode;
	m_Query.Clear();
	return TRUE;
}

BOOL CArcaBattleDBSet::DBSelectArcaBattleIsTopRank(DWORD dwGuildNumber)
{
	CString QueryStr;
	QueryStr.Format("WZ_ArcaBattleMarkRankSelect %d", dwGuildNumber);

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleIsTopRank #1 %s %d", __FILE__, __LINE__);
		return -1;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA)
	{
		m_Query.Clear();
		return -1;
	}

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleIsTopRank #2 %d %s %d", sqlReturn, __FILE__, __LINE__);
		return -1;
	}

	int iResult = m_Query.GetInt(1);

	if (iResult <= 6 && iResult > 0)
	{
		iResult = 0;
	}

	else
	{
		iResult = 6;
	}

	m_Query.Clear();
	return iResult;
}

BOOL CArcaBattleDBSet::DBSelectArcaBattleMarkCnt(DWORD dwGuildNumber)
{
	CString QueryStr;
	QueryStr.Format("WZ_ArcaBattleMarkCntSelect %d", dwGuildNumber);

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleMarkCnt #1 %s %d", __FILE__, __LINE__);
		return -2;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA)
	{
		m_Query.Clear();
		return -2;
	}

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleMarkCnt #2 %d %s %d", sqlReturn, __FILE__, __LINE__);
		return -2;
	}

	int iResult = m_Query.GetInt(1);
	m_Query.Clear();
	return iResult;
}

BOOL CArcaBattleDBSet::DBInsertArcaBattleRegMark(char* szGuildName, DWORD dwGuildNum, char* szGuildMaster, DWORD dwMarkCnt)
{
	CString QueryStr;
	QueryStr.Format("WZ_ArcaBattleMarkInsert '%s', %d, '%s', %u", szGuildName, dwGuildNum, szGuildMaster, dwMarkCnt);

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBInsertArcaBattleRegMark #1 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBInsertArcaBattleRegMark #2 %d %s %d", sqlReturn, __FILE__, __LINE__);
		return FALSE;
	}

	m_Query.Clear();
	return TRUE;
}

BOOL CArcaBattleDBSet::DBSelectArcaBattleTopRank(_stArcaBattleMarkTopRank* pArcaBattleMarkTopRank, BYTE& btGuildCnt)
{
	CString QueryStr;
	QueryStr.Format("WZ_ArcaBattleTopRankSelect");

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleTopRank #1 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA)
	{
		m_Query.Clear();
		return FALSE;
	}

	int iCnt = 0;

	while (sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
	{
		m_Query.GetStr("G_Name", pArcaBattleMarkTopRank[iCnt].szGuildNames);
		pArcaBattleMarkTopRank[iCnt].dwMarkCnt = m_Query.GetInt64("MarkCnt");
		pArcaBattleMarkTopRank[iCnt].btRank = iCnt + 1;
		iCnt++;

		if (iCnt >= 6)
		{
			break;
		}

		sqlReturn = m_Query.Fetch();
	}

	btGuildCnt = iCnt;
	m_Query.Clear();
	return TRUE;
}

BOOL CArcaBattleDBSet::DBSelectArcaBattleMyGuildRank(DWORD dwGuildNumber, BYTE& btMyGuildRank, DWORD& dwMarkCnt)
{
	CString QueryStr;
	QueryStr.Format("WZ_ArcaBattleMarkRankSelect %d", dwGuildNumber);

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleMarkCnt #1 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA)
	{
		m_Query.Clear();
		return FALSE;
	}

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleMarkCnt #2 %d %s %d", sqlReturn, __FILE__, __LINE__);
		return FALSE;
	}

	btMyGuildRank = m_Query.GetInt(1);
	dwMarkCnt = m_Query.GetInt64(2);
	m_Query.Clear();
	return TRUE;
}

BOOL CArcaBattleDBSet::DBDeleteArcaBattleMarkReg(DWORD dwGuildNumber)
{
	CString QueryStr;
	QueryStr.Format("WZ_ArcaBattleMarkRegDel %d", dwGuildNumber);

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleMarkReg #1 %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleMarkReg #2 %d %s %d", sqlReturn, __FILE__, __LINE__);
		return FALSE;
	}

	int iResult = m_Query.GetInt(1);

	if (iResult == -1)
	{
		LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleMarkReg #3 %d %s %d", sqlReturn, __FILE__, __LINE__);
	}

	m_Query.Clear();
	return TRUE;
}

void CArcaBattleDBSet::DBDeleteAllArcaBattleGuildReg()
{
	CString QueryStr;
	QueryStr.Format("WZ_ArcaBattleGuildMarkInfoAllDel");
	
	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBDeleteAllArcaBattleGuildReg %s %d", __FILE__, __LINE__);
		return;
	}

	m_Query.Clear();
}

void CArcaBattleDBSet::DBDeleteArcaBattleGuildReg()
{
	CString QueryStr;
	QueryStr.Format("delete T_ARCA_BATTLE_MEMBER_JOIN_INFO");
	
	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleGuildReg #1 %s %d", __FILE__, __LINE__);
		return;
	}

	m_Query.Clear();
	QueryStr.Format("delete T_ARCA_BATTLE_GUILD_JOIN_INFO");

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleGuildReg #2 %s %d", __FILE__, __LINE__);
		return;
	}

	m_Query.Clear();
	QueryStr.Format("delete T_ARCA_BATTLE_GUILDMARK_REG");

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleGuildReg #3 %s %d", __FILE__, __LINE__);
		return;
	}
			
	m_Query.Clear();
}

void CArcaBattleDBSet::DBUpdateArcaBattleGuildReg(LPBYTE lpRecv, int aIndex)
{
	LPPMSG_REQ_AB_MARK_REG_UPDATE_DS lpMsg = (LPPMSG_REQ_AB_MARK_REG_UPDATE_DS)lpRecv;

	CString QueryStr;
	QueryStr.Format("UPDATE T_ARCA_BATTLE_GUILDMARK_REG SET MarkCnt = %d WHERE G_Number = %d", lpMsg->dwMarkCnt, lpMsg->dwGuildNum);

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleGuildReg #1 %s %d", __FILE__, __LINE__);
		return;
	}

	m_Query.Clear();
}

void CArcaBattleDBSet::DBSelectArcaBattleAllGuildMark(_stABAllGuildMark* pABAllGuildMark, int& iGuildCnt)
{
	_stABAllGuildMark _stABAllGuildMark[250];

	CString QueryStr;
	QueryStr.Format("WZ_ArcaBattleAllMarkCntSelect");

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		LogAddC(LOGC_RED, "Error WZ_ArcaBattleAllMarkCntSelect m_Query.Exec %s %d", __FILE__, __LINE__);
		m_Query.Clear();
		return;
	}

	int iCnt = 0;

	SQLRETURN sqlReturn = m_Query.Fetch();

	while (sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
	{
		m_Query.GetStr("G_Name", pABAllGuildMark[iCnt].szGuildName);
		pABAllGuildMark[iCnt].dwMarkCnt = m_Query.GetInt("MarkCnt");
		iCnt++;

		if (iCnt >= 250)
		{
			break;
		}

		sqlReturn = m_Query.Fetch();
	}

	iGuildCnt = iCnt;
	m_Query.Clear();
}

BOOL CArcaBattleDBSet::DBSelectABAllJoinUser(_stABJoinUserInfoDS* pABJoinUserInfo, BYTE& btUserCnt)
{
	int iCnt = 0;

	CString szQuery;
	szQuery.Format("WZ_ArcaBattleAllJoinUserSelect");

	if (m_Query.Exec(szQuery) == FALSE)
	{
		LogAddC(LOGC_RED, "Error WZ_ArcaBattleAllJoinUserSelect m_Query.Exec %s %d", __FILE__, __LINE__);
		m_Query.Clear();
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	while (sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
	{
		m_Query.GetStr("G_Name", pABJoinUserInfo[iCnt].szGuildName);
		pABJoinUserInfo[iCnt].dwGuild = m_Query.GetInt("Number");
		m_Query.GetStr("CharName", pABJoinUserInfo[iCnt].szUserName);
		iCnt++;

		if (iCnt >= 200)
		{
			break;
		}

		sqlReturn = m_Query.Fetch();
	}

	btUserCnt = iCnt;
	m_Query.Clear();
	return TRUE;
}