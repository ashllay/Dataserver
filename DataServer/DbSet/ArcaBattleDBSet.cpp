// ArcaBattleDBSet.cpp: implementation of the CArcaBattleDBSet class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ArcaBattleDBSet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArcaBattleDBSet::CArcaBattleDBSet()
{

}

CArcaBattleDBSet::~CArcaBattleDBSet()
{

}

BOOL CArcaBattleDBSet::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass) == FALSE)
	{
		MsgBox("CArcaBattleDBSet ODBC Connect Fail");
		return FALSE;
	}

	return TRUE;
}

void CArcaBattleDBSet::DBDeleteAllArcaBattleGuildReg()
{

	CString qSQL;
	qSQL.Format("WZ_ArcaBattleGuildMarkInfoAllDel");
	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		m_DBQuery.Clear();
	}

	m_DBQuery.Clear();
	LogAddTD("error-L3 : [ArcaBattle] DBDeleteAllArcaBattleGuildReg %s %d", __FILE__, __LINE__);
}

int CArcaBattleDBSet::DBDeleteArcaBattleCancelGuild(_stCancelGuildNames GNames[20], int GCount)
{
	CString qSQL;

	for (int i = 0; i < GCount; i++)
	{
		qSQL.Format("WZ_ArcaBattleMinGuildDelete '%s'", GNames[i].szGuildNames);

		if (m_DBQuery.Exec(qSQL) == FALSE)
		{
			m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleCancelGuild #1 %s %d", __FILE__, __LINE__);
			return FALSE;
		}
		if (m_DBQuery.Fetch() == SQL_NO_DATA)
		{
			m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleCancelGuild #2 %s %d", __FILE__, __LINE__);
			return FALSE;
		}
		int Result = m_DBQuery.GetInt(1);
		m_DBQuery.Clear();
	}
	return TRUE;
}

void CArcaBattleDBSet::DBDeleteArcaBattleGuildReg()
{
	CString qSQL;

	qSQL.Format("delete T_ARCA_BATTLE_MEMBER_JOIN_INFO");

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		m_DBQuery.Clear();
		qSQL.Format("delete T_ARCA_BATTLE_GUILD_JOIN_INFO");
		if (m_DBQuery.Exec(qSQL) == TRUE)
		{
			m_DBQuery.Clear();
			qSQL.Format("delete T_ARCA_BATTLE_GUILDMARK_REG");
			if (m_DBQuery.Exec(qSQL) == TRUE)
			{
				m_DBQuery.Clear();
			}
			else
			{
				m_DBQuery.Clear();
				LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleGuildReg #3 %s %d", __FILE__, __LINE__);
			}
		}
		else
		{
			m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleGuildReg #2 %s %d", __FILE__, __LINE__);
		}
	}
	else
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleGuildReg #1 %s %d", __FILE__, __LINE__);
	}
}

int CArcaBattleDBSet::DBDeleteArcaBattleInfo()
{
	CString qSQL;

	qSQL.Format("WZ_ArcaBattleInfoDelete");

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		if (m_DBQuery.Fetch() == SQL_NO_DATA)
		{
			m_DBQuery.Clear();
			return -1;
		}
		else
		{
			int Result = m_DBQuery.GetInt(1);
			m_DBQuery.Clear();
			return 1;
		}
	}
	else
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleInfo #1 %s %d", __FILE__, __LINE__);
		return 0;
	}
}

int CArcaBattleDBSet::DBDeleteArcaBattleMarkReg(DWORD G_Number)
{
	int result;
	SHORT sqlReturn;

	CString qSQL;

	qSQL.Format("WZ_ArcaBattleMarkRegDel %d", G_Number);

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		sqlReturn = m_DBQuery.Fetch();
		if (sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
		{
			result = m_DBQuery.GetInt(1);
			if (result == -1)
				LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleMarkReg #3 %d %s %d", sqlReturn, __FILE__, __LINE__);

			m_DBQuery.Clear();
			return 1;
		}
		else
		{
			m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleMarkReg #2 %d %s %d", sqlReturn, __FILE__, __LINE__);
			return 0;
		}
	}
	else
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleMarkReg #1 %s %d", __FILE__, __LINE__);
		return 0;
	}
}

int CArcaBattleDBSet::DBInsertArcaBattleGuildJoin(char* CharName, char* GName, unsigned int Number, int* Result)
{
	if (!Result)
		return 0;

	CString qSQL;
	qSQL.Format("WZ_ArcaBattleGuildInsert '%s', '%s', %d ", GName, CharName, Number);

	if (!m_DBQuery.Exec(qSQL))
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildInsert #1 %s %d", __FILE__, __LINE__);
		*Result = -1;
		return 0;
	}

	int sqlReturn = m_DBQuery.Fetch();

	// Match IDA: (100 || -1) ¡æ failure
	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildInsert #2 %d %s %d", sqlReturn, __FILE__, __LINE__);
		*Result = -1;
		return 0;
	}

	*Result = m_DBQuery.GetInt(1);

	if (*Result == -1)
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildInsert #3 %s %d", __FILE__, __LINE__);
		return 0;
	}

	m_DBQuery.Clear();
	return 1;
}

int CArcaBattleDBSet::DBInsertArcaBattleGuildMemberJoin(char* CharName, char* GName, DWORD Number, char* Result)
{
	__int16 sqlReturn;

	CString qSQL;

	qSQL.Format("WZ_ArcaBattleGuildMemberInsert '%s', '%s', %d ", GName, CharName, Number);

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		sqlReturn = m_DBQuery.Fetch();
		if (sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
		{
			*Result = m_DBQuery.GetInt(1);
			if (*Result == -1)
			{
				m_DBQuery.Clear();
				LogAddTD("error-L3 : [ArcaBattle] GuildMemberInsert #3 %s %d", __FILE__, __LINE__);
				return 0;
			}
			else
			{
				m_DBQuery.Clear();
				return 1;
			}
		}
		else
		{
			m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] GuildMemberInsert #2 %d %s %d", sqlReturn, __FILE__, __LINE__);
			return 0;
		}
	}
	else
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildMemberInsert #1 %s %d", __FILE__, __LINE__);
		return 0;
	}
}

int CArcaBattleDBSet::DBInsertArcaBattleProc(int ProcState)
{
	__int16 nRet;

	CString qSQL;

	qSQL.Format("WZ_ArcaBattleProcInsert %d", ProcState);

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		nRet = m_DBQuery.Fetch();
		if (nRet != SQL_NO_DATA && nRet != SQL_NULL_DATA)
		{
			m_DBQuery.Clear();
			return 1;
		}
		else
		{
			m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBInsertArcaBattleProc #2 %d %s %d", nRet, __FILE__, __LINE__);
			return 0;
		}
	}
	else
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBInsertArcaBattleProc #1 %s %d", __FILE__, __LINE__);
		return 0;
	}
}

int CArcaBattleDBSet::DBInsertArcaBattleRegMark(char* GName, DWORD GNumber, char* GMaster, DWORD MarkCnt)
{
	__int16 nRet;

	CString qSQL;

	qSQL.Format("WZ_ArcaBattleMarkInsert '%s', %d, '%s', %u", GName, GNumber, GMaster, MarkCnt);

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		nRet = m_DBQuery.Fetch();
		if (nRet != SQL_NO_DATA && nRet != SQL_NULL_DATA)
		{
			m_DBQuery.Clear();
			return 1;
		}
		else
		{
			m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBInsertArcaBattleRegMark #2 %d %s %d", nRet, __FILE__, __LINE__);
			return 0;
		}
	}
	else
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBInsertArcaBattleRegMark #1 %s %d", __FILE__, __LINE__);
		return 0;
	}
}

int CArcaBattleDBSet::DBInsertArcaBattleWinGuild(_stABWinGuildInfoDS GuildInfo[5], int btGuildCnt)
{
	CString qSQL;

	for (int i = 0; i < btGuildCnt; ++i)
	{
		qSQL.Format("WZ_ArcaBattleWinGuildInsert '%s', %d, %d, %d, %d", GuildInfo[i].szGuildName, GuildInfo[i].dwGuild, GuildInfo[i].wOccupyObelisk, GuildInfo[i].wObeliskGroup, 100);

		if (m_DBQuery.Exec(qSQL) == FALSE)
		{
			m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] WZ_ArcaBattleWinGuildInsert #1 %s %d", __FILE__, __LINE__);
			return 0;
		}
		m_DBQuery.Clear();
	}
	m_DBQuery.Clear();
	return 1;
}

int CArcaBattleDBSet::DBIsArcaBattleEnter(char* CharName, int* Result)
{
	__int16 sqlReturn;

	CString qSQL;

	qSQL.Format("WZ_ArcaBattleMemberSelect '%s'", CharName);

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		sqlReturn = m_DBQuery.Fetch();
		if (sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
		{
			*Result = m_DBQuery.GetInt(1);
			if (*Result == -1)
			{
				m_DBQuery.Clear();
				LogAddTD("error-L3 : [ArcaBattle] DBIsArcaBattleEnter #3 %s %d", __FILE__, __LINE__);
				return 0;
			}
			else
			{
				m_DBQuery.Clear();
				return 1;
			}
		}
		else
		{
			m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBIsArcaBattleEnter #2 %d %s %d", sqlReturn, __FILE__, __LINE__);
			return 0;
		}
	}
	else
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBIsArcaBattleEnter #1 %s %d", __FILE__, __LINE__);
		return 0;
	}
}

int CArcaBattleDBSet::DBSelectABAllJoinUser(_stABJoinUserInfoDS pABJoinUserInfo[200], int* GCount)
{
	__int16 nRet;
	int Count = 0;

	CString qSQL;

	qSQL.Format("WZ_ArcaBattleAllJoinUserSelect");

	if (m_DBQuery.Exec(qSQL))
	{
		nRet = m_DBQuery.Fetch();

		while (nRet != SQL_NO_DATA)
		{
			if (nRet == SQL_NULL_DATA)
				break;

			m_DBQuery.GetStr("G_Name", pABJoinUserInfo[Count].szGuildName);
			pABJoinUserInfo[Count].dwGuild = m_DBQuery.GetInt("Number");
			m_DBQuery.GetStr("CharName", pABJoinUserInfo[Count].szUserName);
			Count++;

			if (Count >= 200)
			{
				break;
			}

			nRet = m_DBQuery.Fetch();
		}

		*GCount = Count;
		m_DBQuery.Clear();
		return 1;
	}
	else
	{
		bool bReConnect = false;
		m_DBQuery.PrintDiag(bReConnect);
		LogAddC(LOGC_RED, "Error WZ_ArcaBattleAllJoinUserSelect m_DBQuery.Exec %s %d", __FILE__, __LINE__);
		m_DBQuery.Clear();
		return 0;
	}
}

int CArcaBattleDBSet::DBSelectABRegisteredMemberCnt(DWORD G_Number, BYTE* Result)
{
	__int16 sqlReturn;
	int nRet;
	CString qSQL;

	qSQL.Format("WZ_ArcaBattleGuildMemberSelect %d", G_Number);

	if (m_DBQuery.Exec(qSQL))
	{
		sqlReturn = m_DBQuery.Fetch();
		if (sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
		{
			nRet = m_DBQuery.GetInt(1);
			if (nRet == -1)
			{
				m_DBQuery.Clear();
				LogAddTD("error-L3 : [ArcaBattle] GuildMemberSelect #3 %s %d", __FILE__, __LINE__);
				return 0;
			}
			else
			{
				*Result = nRet;
				m_DBQuery.Clear();
				return 1;
			}
		}
		else
		{
			m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] GuildMemberSelect #2 %d %s %d", sqlReturn, __FILE__, __LINE__);
			return 0;
		}
	}
	else
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildMemberSelect #1 %s %d", __FILE__, __LINE__);
		return 0;
	}
}

void CArcaBattleDBSet::DBSelectArcaBattleAllGuildMark(_stABAllGuildMark a2[250], int* GCount)
{
	int Count = 0;
	int nRet;

	CString qSQL;

	qSQL.Format("WZ_ArcaBattleAllMarkCntSelect");

	if (m_DBQuery.Exec(qSQL))
	{
		nRet = m_DBQuery.Fetch();

		while (nRet != SQL_NO_DATA)
		{
			if (nRet == SQL_NULL_DATA)
				break;

			m_DBQuery.GetStr("G_Name", a2[Count].szGuildName);
			a2[Count].dwMarkCnt = m_DBQuery.GetInt("MarkCnt");

			Count++;

			if (Count >= 250)
			{
				break;
			}

			nRet = m_DBQuery.Fetch();
		}

		*GCount = Count;
		m_DBQuery.Clear();
	}
	else
	{
		bool bReConnect = false;
		m_DBQuery.PrintDiag(bReConnect);
		LogAddC(LOGC_RED, "Error WZ_ArcaBattleAllMarkCntSelect m_DBQuery.Exec %s %d", __FILE__, __LINE__);
		m_DBQuery.Clear();
	}
}


int  CArcaBattleDBSet::DBSelectArcaBattleCancelGuild(_stCancelGuildNames* pstCancelGuildNames, int iMinGuildMemNum, BYTE* btGuildCnt)
{
	int nRet;
	int i;
	__int16 sqlReturn;
	_stCancelGuildNames CancelGuildNames[6];
	int iCancelGuildCnt;
	int iCnt;
	CString QueryStr;

	iCnt = 0;
	iCancelGuildCnt = 0;
	QueryStr.Format("WZ_ArcaBattleGuildNamesSelect");

	if (m_DBQuery.Exec(QueryStr))
	{
		for (sqlReturn = m_DBQuery.Fetch(); sqlReturn != SQL_NO_DATA; sqlReturn = m_DBQuery.Fetch())
		{
			if (sqlReturn == SQL_NULL_DATA)
				break;
			m_DBQuery.GetStr("G_Name", CancelGuildNames[iCnt++].szGuildNames);
			if (iCnt >= 6)
				break;
		}
		m_DBQuery.Clear();
		for (i = 0; i < iCnt; ++i)
		{
			QueryStr.Format("WZ_ArcaBattleMinGuildSelect '%s', %d",
				CancelGuildNames[i].szGuildNames,
				iMinGuildMemNum);

			if (!m_DBQuery.Exec(QueryStr))
			{
				m_DBQuery.Clear();
				LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleCancelGuild #2 %s %d",
					__FILE__,
					__LINE__);

				return 0;
			}

			nRet = m_DBQuery.Fetch();

			if (nRet == SQL_NO_DATA || nRet == SQL_NULL_DATA)
			{
				m_DBQuery.Clear();
				LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleCancelGuild #3 %d %s %d",
					nRet,
					__FILE__,
					__LINE__);

				return 0;
			}
			if (m_DBQuery.GetInt(1) < 0)
			{
				memcpy(&pstCancelGuildNames[iCancelGuildCnt], &CancelGuildNames[i], 8);
				pstCancelGuildNames[iCancelGuildCnt++].szGuildNames[8] = 0;
			}
			m_DBQuery.Clear();
		}
		if (DBDeleteArcaBattleCancelGuild(pstCancelGuildNames, iCancelGuildCnt))
		{
			*btGuildCnt = iCancelGuildCnt;

			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleCancelGuild #1 %s %d",
			__FILE__,
			__LINE__);
		return 0;
	}
}

int CArcaBattleDBSet::DBSelectArcaBattleGuildGroupNum(char* CharName, int* GroupNum)
{
	__int16 nRet;
	CString qSQL;

	qSQL.Format("WZ_ArcaBattleGuildGroupNumSelect '%s'", CharName);

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		nRet = m_DBQuery.Fetch();
		if (nRet == SQL_NO_DATA)
		{
			m_DBQuery.Clear();
			return 2;
		}
		else if (nRet != SQL_NO_DATA && nRet != SQL_NULL_DATA)
		{
			*GroupNum = m_DBQuery.GetInt(1);
			m_DBQuery.Clear();
			return 1;
		}
		else
		{
			m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleGuildGroupNum #2 %d %s %d", nRet, __FILE__, __LINE__);
			return 0;
		}
	}
	else
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleGuildGroupNum #1 %s %d", __FILE__, __LINE__);
		return 0;
	}
}

int CArcaBattleDBSet::DBSelectArcaBattleGuildJoin(char* CharName, BYTE* GuildNum)
{

	__int16 nRet;
	CString qSQL;

	qSQL.Format("WZ_ArcaBattleGuildSelect '%s'", CharName);

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		nRet = m_DBQuery.Fetch();
		if (nRet != SQL_NO_DATA && nRet != SQL_NULL_DATA)
		{
			*GuildNum = m_DBQuery.GetInt(1);
			if (*GuildNum == -1)
			{
				m_DBQuery.Clear();
				LogAddTD("error-L3 : [ArcaBattle] GuildInsert #3 %s %d", __FILE__, __LINE__);
				return 0;
			}
			else
			{
				m_DBQuery.Clear();
				return 1;
			}
		}
		else
		{
			m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] GuildSelect #2 %d %s %d", nRet, __FILE__, __LINE__);
			return 0;
		}
	}
	else
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildSelect #1 %s %d", __FILE__, __LINE__);
		return 0;
	}
}

int CArcaBattleDBSet::DBSelectArcaBattleIsTopRank(DWORD G_Number)
{
	int mRank;
	__int16 nRet;
	CString qSQL;

	qSQL.Format("WZ_ArcaBattleMarkRankSelect %d", G_Number);

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		nRet = m_DBQuery.Fetch();
		if (nRet == SQL_NO_DATA)
		{
			m_DBQuery.Clear();
			return -1;
		}
		else if (nRet != SQL_NO_DATA && nRet != SQL_NULL_DATA)
		{
			mRank = m_DBQuery.GetInt(1);
			if (mRank > 6 || mRank <= 0)
			{
				return 6;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleIsTopRank #2 %d %s %d", nRet, __FILE__, __LINE__);
			return -1;
		}
	}
	else
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleIsTopRank #1 %s %d", __FILE__, __LINE__);
		return -1;
	}
}

int CArcaBattleDBSet::DBSelectArcaBattleJoinMemberUnder(_stGuildUnderMember G_Memb[6], BYTE* MembCount)
{
	int nRet;
	int Count = 0;
	int nGCount = 0;
	CString qSQL;

	qSQL.Format("WZ_ArcaBattleGuildNamesSelect");

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{

		nRet = m_DBQuery.Fetch();

		while (nRet != SQL_NO_DATA)
		{
			if (nRet == SQL_NULL_DATA)
				break;

			m_DBQuery.GetStr("G_Name", G_Memb[Count].szGuildNames);

			Count++;

			if (Count >= 6)
			{
				break;
			}

			nRet = m_DBQuery.Fetch();
		}

		*MembCount = Count;
		m_DBQuery.Clear();
		for (int j = 0; j < Count; ++j)
		{
			qSQL.Format("WZ_ArcaBattleMemberUnderSelect '%s'", G_Memb[j].szGuildNames);

			if (m_DBQuery.Exec(qSQL) == FALSE)
			{
				m_DBQuery.Clear();
				LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleJoinMemberUnder #2 %s %d", __FILE__, __LINE__);
				return 0;
			}
			nRet = m_DBQuery.Fetch();
			if (nRet != SQL_NO_DATA && nRet != SQL_NULL_DATA)
			{
				m_DBQuery.Clear();
				LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleJoinMemberUnder #3 %d %s %d", nRet, __FILE__, __LINE__);
				return 0;
			}
			G_Memb[j].btGuildMemberCnt = m_DBQuery.GetInt(1);
			m_DBQuery.Clear();
		}
		m_DBQuery.Clear();
		return 1;
	}
	else
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleJoinMemberUnder #1 %s %d", __FILE__, __LINE__);
		return 0;
	}
}

int CArcaBattleDBSet::DBSelectArcaBattleMarkCnt(DWORD G_Number)
{
	int nRet;
	CString qSQL;

	qSQL.Format("WZ_ArcaBattleMarkCntSelect %d", G_Number);

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		nRet = m_DBQuery.Fetch();
		if (nRet == SQL_NO_DATA)
		{
			m_DBQuery.Clear();
			return -2;
		}
		else if (nRet != SQL_NO_DATA && nRet != SQL_NULL_DATA)
		{
			int MarkCnt = m_DBQuery.GetInt(1);
			m_DBQuery.Clear();
			return MarkCnt;
		}
		else
		{
			m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleMarkCnt #2 %d %s %d", nRet, __FILE__, __LINE__);
			return -2;
		}
	}
	else
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleMarkCnt #1 %s %d", __FILE__, __LINE__);
		return -2;
	}
}

int CArcaBattleDBSet::DBSelectArcaBattleMyGuildRank(DWORD G_Number, BYTE* mRank, DWORD* mMarkCnt)
{
	int nRet;
	CString qSQL;

	qSQL.Format("WZ_ArcaBattleMarkRankSelect %d", G_Number);

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		nRet = m_DBQuery.Fetch();
		if (nRet == SQL_NO_DATA)
		{
			m_DBQuery.Clear();
			return 0;
		}
		else if (nRet != SQL_NO_DATA && nRet != SQL_NULL_DATA)
		{
			*mRank = m_DBQuery.GetInt(1);
			*mMarkCnt = m_DBQuery.GetInt64(2);
			m_DBQuery.Clear();
			return 1;
		}
		else
		{
			m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleMarkCnt #2 %d %s %d", nRet, __FILE__, __LINE__);
			return 0;
		}
	}
	else
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleMarkCnt #1 %s %d", __FILE__, __LINE__);
		return 0;
	}
}

int CArcaBattleDBSet::DBSelectArcaBattleProc(char* ProcState)
{
	int nRet;
	CString qSQL;

	qSQL.Format("WZ_ArcaBattleProcSelect");

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		nRet = m_DBQuery.Fetch();
		if (nRet == SQL_NO_DATA)
		{
			m_DBQuery.Clear();
			return 0;
		}
		else if (nRet != SQL_NO_DATA && nRet != SQL_NULL_DATA)
		{

			*ProcState = m_DBQuery.GetInt(1);
			m_DBQuery.Clear();
			return 1;
		}
		else
		{
			m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleProc #2 %d %s %d", nRet, __FILE__, __LINE__);
			return 0;
		}
	}
	else
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleProc #1 %s %d", __FILE__, __LINE__);
		return 0;
	}
}

int CArcaBattleDBSet::DBSelectArcaBattleTopRank(_stArcaBattleMarkTopRank MarkTopRank[6], BYTE* MarkTopCount)
{
	int nRet;
	int Count;
	CString qSQL;

	qSQL.Format("WZ_ArcaBattleTopRankSelect");

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		nRet = m_DBQuery.Fetch();
		if (nRet == SQL_NO_DATA)
		{
			m_DBQuery.Clear();
			return 0;
		}
		else
		{
			Count = 0;

			while (nRet != SQL_NO_DATA)
			{
				if (nRet == SQL_NULL_DATA)
					break;

				m_DBQuery.GetStr("G_Name", MarkTopRank[Count].szGuildNames);
				MarkTopRank[Count].dwMarkCnt = m_DBQuery.GetInt64("MarkCnt");
				MarkTopRank[Count].btRank = Count + 1;

				Count++;

				if (Count >= 6)
				{
					break;
				}

				nRet = m_DBQuery.Fetch();
			}

			*MarkTopCount = Count;
			m_DBQuery.Clear();
			return 1;
		}
	}
	else
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleTopRank #1 %s %d", __FILE__, __LINE__);
		return 0;
	}
}

int CArcaBattleDBSet::DBSelectArcaBattleWinGuild(_stABWinGuildInfoDS GuildInfo[5], int* GuildInfoCount)
{
	int nRet;
	int Count = 0;
	CString qSQL;

	qSQL.Format("WZ_ArcaBattleWinGuildSelect");

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{

		nRet = m_DBQuery.Fetch();

		while (nRet != SQL_NO_DATA)
		{
			if (nRet == SQL_NULL_DATA)
				break;

			m_DBQuery.GetStr("G_Name", GuildInfo[Count].szGuildName);
			GuildInfo[Count].dwGuild = m_DBQuery.GetInt64("G_Number");
			GuildInfo[Count].wOccupyObelisk = m_DBQuery.GetInt64("OuccupyObelisk");
			GuildInfo[Count].wObeliskGroup = m_DBQuery.GetInt64("ObeliskGroup");

			Count++;

			if (Count >= 5)
			{
				break;
			}

			nRet = m_DBQuery.Fetch();
		}

		*GuildInfoCount = Count;
		m_DBQuery.Clear();
		return 1;
	}
	else
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] WZ_ArcaBattleWinGuildSelect #1 %s %d", __FILE__, __LINE__);
		return 0;
	}
}

void CArcaBattleDBSet::DBUpdateArcaBattleGuildReg(_tagPMSG_REQ_AB_MARK_REG_UPDATE_DS* lpMsg)
{
	CString qSQL;

	qSQL.Format("UPDATE T_ARCA_BATTLE_GUILDMARK_REG SET MarkCnt = %d WHERE G_Number = %d", lpMsg->dwMarkCnt, lpMsg->dwGuildNum);

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		m_DBQuery.Clear();
	}
	else
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] DBUpdateArcaBattleGuildReg #1 %s %d", __FILE__, __LINE__);
	}
}

void CArcaBattleDBSet::DBUpdateArcaBattleGuildReg(BYTE* lpRecv, int aIndex)
{
	CString QueryStr;
	_tagPMSG_REQ_AB_MARK_REG_UPDATE_DS* lpMsg;

	lpMsg = (_tagPMSG_REQ_AB_MARK_REG_UPDATE_DS*)lpRecv;

	QueryStr.Format("UPDATE T_ARCA_BATTLE_GUILDMARK_REG SET MarkCnt = %d WHERE G_Number = %d", lpMsg->dwMarkCnt, lpMsg->dwGuildNum);

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