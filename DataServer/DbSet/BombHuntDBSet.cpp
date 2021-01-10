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
	if (m_Query.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass) == FALSE)
	{
		MsgBox("CBombHuntDBSet ODBC Connect Fail");
		return FALSE;
	}

	return TRUE;
}

BOOL CBombHuntDBSet::DBSelectBombHunt(char* szAccountID, char* szName, WORD& wOutScore, BYTE& btOutGameState, char* szOutTileState)
{
	int iItemCount = 0;
	int iReturnCode = 0;

	CString QueryStr;
	QueryStr.Format("EXEC WZ_BombHuntSetSelect '%s', '%s'", szAccountID, szName);

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [BombHuntDBSet] DBSelectBombHuntInfo #1 [%s][%s] %s %d", szAccountID, szName, __FILE__, __LINE__);
		return FALSE;
	}

	SQLRETURN sqlReturn = m_Query.Fetch();

	if (sqlReturn == SQL_NO_DATA)
	{
		m_Query.Clear();
		return FALSE;
	}

	wOutScore = m_Query.GetInt("Score");
	btOutGameState = m_Query.GetInt("GameState");
	m_Query.GetStr("TileState", szOutTileState);
	m_Query.Clear();
	return TRUE;
}

BOOL CBombHuntDBSet::DBInsertBombHunt(char *szAccountID, char *szName, WORD wScore, WORD wGameState, char *szTileState)
{
	int iItemCount = 0;
	int iReturnCode = 0;

	CString QueryStr;
	QueryStr.Format("EXEC WZ_BombHuntSetSave '%s', '%s', %d, %d, '%s'", szAccountID, szName, wGameState, wScore, szTileState);

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [BombHunt] DBInsertBombHunt #1 [%s][%s] %s %d", szAccountID, szName, __FILE__, __LINE__);
		return FALSE;
	}

	m_Query.Clear();
	return TRUE;
}

BOOL CBombHuntDBSet::DBDeleteBombHunt(char *szAccountID, char *szName)
{
	CString QueryStr;
	QueryStr.Format("EXEC WZ_BombHuntSetDelete '%s', '%s'", szAccountID, szName);

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [BombHunt] DBDeleteBombHunt #1 [%s][%s] %s %d", szAccountID, szName, __FILE__, __LINE__);
		return FALSE;
	}

	m_Query.Clear();
	return TRUE;
}

BOOL CBombHuntDBSet::DBInsertBombHuntLog(char *szAccountID, char *szName, WORD wScore, BYTE btClear)
{
	CString QueryStr;
	QueryStr.Format("EXEC WZ_BombHuntLogSetSave  '%s', '%s', %d, %d", szAccountID, szName, wScore, btClear);

	if (m_Query.Exec(QueryStr) == FALSE)
	{
		m_Query.Clear();
		LogAddTD("error-L3 : [MuRummy] DBInsertBombHuntLog #1 [%s][%s] %s %d", szAccountID, szName, __FILE__, __LINE__);
		return FALSE;
	}

	m_Query.Clear();
	return TRUE;
}