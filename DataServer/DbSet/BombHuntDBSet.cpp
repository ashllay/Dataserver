#include "StdAfx.h"
#include "bombhuntdbset.h"

CBombHuntDBSet::CBombHuntDBSet()
{
}

CBombHuntDBSet::~CBombHuntDBSet()
{
}

BOOL CBombHuntDBSet::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("CBombHuntDBSet ODBC Connect Fail");
	return 0;
}

int CBombHuntDBSet::DBSelectBombHunt(char *szAccountID, char *szName, BYTE *wOutScore, char *btOutGameState, char *szOutTileState)
{
	int result;
	CString QueryStr;

	int iItemCount = 0;
	int iReturnCode = 0;


	QueryStr.Format("EXEC WZ_BombHuntSetSelect '%s', '%s'", szAccountID, szName);

	if (this->m_DBQuery.Exec(QueryStr))
	{
		if (this->m_DBQuery.Fetch() == SQL_NO_DATA)
		{
			this->m_DBQuery.Clear();
			result = 0;
		}
		else
		{
			*wOutScore = this->m_DBQuery.GetInt("Score");
			*btOutGameState = this->m_DBQuery.GetInt("GameState");
			this->m_DBQuery.GetStr("TileState", szOutTileState);
			this->m_DBQuery.Clear();
			result = 1;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [BombHuntDBSet] DBSelectBombHuntInfo #1 [%s][%s] %s %d", szAccountID, szName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}

int CBombHuntDBSet::DBInsertBombHunt(char *szAccountID, char *szName, BYTE wScore, BYTE wGameState, BYTE *szTileState)
{
	int result;
	CString QueryStr;

	QueryStr.Format("EXEC WZ_BombHuntSetSave '%s', '%s', %d, %d, '%s'", szAccountID, szName, wGameState, wScore, szTileState);

	if (this->m_DBQuery.Exec(QueryStr))
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [BombHunt] DBInsertBombHunt #1 [%s][%s] %s %d", szAccountID, szName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}

int CBombHuntDBSet::DBDeleteBombHunt(char *szAccountID, char *szName)
{
	int result;
	CString QueryStr;

	QueryStr.Format(
		"EXEC WZ_BombHuntSetDelete '%s', '%s'",
		szAccountID,
		szName);
	if (this->m_DBQuery.Exec(QueryStr))
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD(
			"error-L3 : [BombHunt] DBDeleteBombHunt #1 [%s][%s] %s %d",
			szAccountID,
			szName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}

int CBombHuntDBSet::DBInsertBombHuntLog(char *szAccountID, char *szName, BYTE wScore, char btClear)
{
	int result;
	CString QueryStr;

	QueryStr.Format("EXEC WZ_BombHuntLogSetSave  '%s', '%s', %d, %d", szAccountID, szName, wScore, btClear);

	if (this->m_DBQuery.Exec(QueryStr))
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [MuRummy] DBInsertBombHuntLog #1 [%s][%s] %s %d", szAccountID, szName, __FILE__, __LINE__);

		result = 0;
	}
	return result;
}