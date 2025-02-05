// ArcaBattleDBSet.cpp: implementation of the CArcaBattleDBSet class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
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
// 5CD7B4: using guessed type int `CArcaBattleDBSet::DBSelectArcaBattleGuildJoin'::`2'::__LINE__Var;

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
// 5CD7B8: using guessed type int `CArcaBattleDBSet::DBInsertArcaBattleGuildJoin'::`2'::__LINE__Var;

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

int CArcaBattleDBSet::DBDeleteArcaBattleMarkReg(unsigned __int32 G_Number)
{
	int result;
	SHORT v9;

	CString qSQL;

	qSQL.Format("WZ_ArcaBattleMarkRegDel %d", G_Number);

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		v9 = m_DBQuery.Fetch();
		if (v9 != SQL_NO_DATA && v9 != SQL_NULL_DATA)
		{
			result = m_DBQuery.GetInt(1);
			if (result == -1)
				LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleMarkReg #3 %d %s %d", v9, __FILE__, __LINE__);

			m_DBQuery.Clear();
			return 1;
		}
		else
		{
			m_DBQuery.Clear();
			LogAddTD("error-L3 : [ArcaBattle] DBDeleteArcaBattleMarkReg #2 %d %s %d", v9, __FILE__, __LINE__);
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

int CArcaBattleDBSet::DBInsertArcaBattleGuildJoin(char* CharName, char* GName, unsigned __int32 Number, char* Result)
{
	__int16 v12;

	CString qSQL;

	qSQL.Format("WZ_ArcaBattleGuildInsert '%s', '%s', %d ", GName, CharName, Number);

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		v12 = m_DBQuery.Fetch();
		if (v12 != SQL_NO_DATA && v12 != SQL_NULL_DATA)
		{
			*Result = m_DBQuery.GetInt(1);
			if (*Result == -1)
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
			LogAddTD("error-L3 : [ArcaBattle] GuildInsert #2 %d %s %d", v12, __FILE__, __LINE__);
			return 0;
		}
	}
	else
	{
		m_DBQuery.Clear();
		LogAddTD("error-L3 : [ArcaBattle] GuildInsert #1 %s %d", __FILE__, __LINE__);
		return 0;
	}
}

int CArcaBattleDBSet::DBInsertArcaBattleGuildMemberJoin(char* CharName, char* GName, unsigned __int32 Number, char* Result)
{
	__int16 v12;

	CString qSQL;

	qSQL.Format("WZ_ArcaBattleGuildMemberInsert '%s', '%s', %d ", GName, CharName, Number);

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		v12 = m_DBQuery.Fetch();
		if (v12 != SQL_NO_DATA && v12 != SQL_NULL_DATA)
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
			LogAddTD("error-L3 : [ArcaBattle] GuildMemberInsert #2 %d %s %d", v12, __FILE__, __LINE__);
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

int CArcaBattleDBSet::DBInsertArcaBattleRegMark(char* GName, unsigned __int32 GNumber, char* GMaster, unsigned __int32 MarkCnt)
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
	__int16 v10;

	CString qSQL;

	qSQL.Format("WZ_ArcaBattleMemberSelect '%s'", CharName);

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{
		v10 = m_DBQuery.Fetch();
		if (v10 != SQL_NO_DATA && v10 != SQL_NULL_DATA)
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
			LogAddTD("error-L3 : [ArcaBattle] DBIsArcaBattleEnter #2 %d %s %d", v10, __FILE__, __LINE__);
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

int CArcaBattleDBSet::DBSelectABAllJoinUser(_stABJoinUserInfoDS a2[200], int* GCount)
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

			m_DBQuery.GetStr("G_Name", a2[Count].szGuildName);
			a2[Count].dwGuild = m_DBQuery.GetInt("Number");
			m_DBQuery.GetStr("CharName", a2[Count].szUserName);
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
		LogAddC(2, "Error WZ_ArcaBattleAllJoinUserSelect m_DBQuery.Exec %s %d", __FILE__, __LINE__);
		m_DBQuery.Clear();
		return 0;
	}
}

int CArcaBattleDBSet::DBSelectABRegisteredMemberCnt(unsigned __int32 G_Number, unsigned __int8* Result)
{

	__int16 v10;

	int nRet;

	CString qSQL;

	qSQL.Format("WZ_ArcaBattleGuildMemberSelect %d", G_Number);

	if (m_DBQuery.Exec(qSQL))
	{
		v10 = m_DBQuery.Fetch();
		if (v10 != SQL_NO_DATA && v10 != SQL_NULL_DATA)
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
			LogAddTD("error-L3 : [ArcaBattle] GuildMemberSelect #2 %d %s %d", v10, __FILE__, __LINE__);
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
		LogAddC(2, "Error WZ_ArcaBattleAllMarkCntSelect m_DBQuery.Exec %s %d", __FILE__, __LINE__);
		m_DBQuery.Clear();
	}
}

int CArcaBattleDBSet::DBSelectArcaBattleCancelGuild(_stCancelGuildNames GNames[6], int GuildMemCnt, unsigned __int8* GCount)
{

	int nRet;
	int Count = 0;
	int Count2 = 0;
	int nGCount = 0;

	CString qSQL;

	char* src[9 * 6] = { 0 };

	qSQL.Format("WZ_ArcaBattleGuildNamesSelect");

	if (m_DBQuery.Exec(qSQL) == TRUE)
	{

		nRet = m_DBQuery.Fetch();

		while (nRet != SQL_NO_DATA)
		{
			if (nRet == SQL_NULL_DATA)
				break;

			m_DBQuery.GetStr("G_Name", src[9 * Count]);

			Count++;

			if (Count >= 6)
			{
				break;
			}

			nRet = m_DBQuery.Fetch();
		}

		m_DBQuery.Clear();
		for (int j = 0; j < Count; ++j)
		{
			qSQL.Format("WZ_ArcaBattleMinGuildSelect '%s', %d", &src[9 * j], GuildMemCnt);

			if (m_DBQuery.Exec(qSQL) == FALSE)
			{
				m_DBQuery.Clear();
				LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleCancelGuild #2 %s %d", __FILE__, __LINE__);
				return 0;
			}
			nRet = m_DBQuery.Fetch();
			if (nRet == SQL_NO_DATA || nRet == SQL_NULL_DATA)
			{
				m_DBQuery.Clear();
				LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleCancelGuild #3 %d %s %d", nRet, __FILE__, __LINE__);
				return 0;
			}

			if (m_DBQuery.GetInt(1) < 0)
			{

				memcpy(GNames[Count2].szGuildNames, &src[9 * j], 8);
				//a2[Count2]->szGuildNames[9] = 0;
				Count2++;
			}
			m_DBQuery.Clear();
		}
		if (this->DBDeleteArcaBattleCancelGuild((_stCancelGuildNames*)GNames, nGCount) == TRUE)
		{
			*GCount = nGCount;
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
		LogAddTD("error-L3 : [ArcaBattle] DBSelectArcaBattleCancelGuild #1 %s %d", __FILE__, __LINE__);
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

int CArcaBattleDBSet::DBSelectArcaBattleIsTopRank(unsigned __int32 G_Number)
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

int CArcaBattleDBSet::DBSelectArcaBattleJoinMemberUnder(_stGuildUnderMember G_Memb[6], unsigned __int8* MembCount)
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

int CArcaBattleDBSet::DBSelectArcaBattleMarkCnt(unsigned __int32 G_Number)
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

int CArcaBattleDBSet::DBSelectArcaBattleMyGuildRank(unsigned __int32 G_Number, unsigned __int8* mRank, unsigned __int32* mMarkCnt)
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
// 5CD7F8: using guessed type int `CArcaBattleDBSet::DBSelectArcaBattleTopRank'::`2'::__LINE__Var;

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
// 5CD7FC: using guessed type int `CArcaBattleDBSet::DBSelectArcaBattleMyGuildRank'::`2'::__LINE__Var;

int CArcaBattleDBSet::DBSelectArcaBattleTopRank(_stArcaBattleMarkTopRank MarkTopRank[6], unsigned __int8* MarkTopCount)
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