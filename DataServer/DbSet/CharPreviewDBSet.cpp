#include "stdafx.h"
#include "CharPreviewDBSet.h"

CCharPreviewDBSet::CCharPreviewDBSet()
{
}

CCharPreviewDBSet::~CCharPreviewDBSet()
{
}

BOOL CCharPreviewDBSet::Conenect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass) == FALSE)
	{
		MsgBox("CharPreviewDBSet ODBC Connect Fail");
		return FALSE;
	}

	return TRUE;
}

BOOL CCharPreviewDBSet::GetChar(char* Name, char* AccountId, int& _level, int& _class, LPBYTE Inventory, BYTE& _ctlcode, BYTE& _dbverstion, BYTE& _pkLevel, BYTE& _btGuildStatus)
{
	CString qSql;

	if (SQLSyntexCheck(Name) == FALSE)
	{
		return FALSE;
	}

	qSql.Format("SELECT Name, cLevel, Class, PkLevel, CtlCode, DbVersion FROM Character WHERE Name='%s'", Name);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	if (m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	m_DBQuery.GetStr("Name", Name);
	_level = m_DBQuery.GetInt("cLevel");
	_class = m_DBQuery.GetInt("Class");
	_pkLevel = m_DBQuery.GetInt("PkLevel");

	int ctlcode = m_DBQuery.GetInt("CtlCode");

	if (ctlcode < 0)
	{
		ctlcode = 0;
	}

	int dbverstion = m_DBQuery.GetInt("DbVersion");

	if (dbverstion < 0)
	{
		dbverstion = 0;
	}

	m_DBQuery.Clear();

	qSql.Format("WZ_GetLoadInventory '%s', '%s'", AccountId, Name);
	int nRet = m_DBQuery.ReadBlob(qSql, Inventory);

	if (nRet == 0)
	{
		memset(Inventory, 0xFF, 120);
	}

	else if (nRet == -1)
	{
		return FALSE;
	}

	m_DBQuery.Clear();

	qSql.Format("SELECT G_Status FROM GuildMember WHERE Name='%s'", Name);
	_btGuildStatus = 0xFF;

	if (m_DBQuery.Exec(qSql) == TRUE)
	{
		if (m_DBQuery.Fetch() != SQL_NO_DATA)
		{
			_btGuildStatus = m_DBQuery.GetInt("G_Status");
		}
	}

	m_DBQuery.Clear();
	return TRUE;
}

BOOL CCharPreviewDBSet::GetRealNameAndServerCode(char* szUBFName, char* szRealName, int* ServerCode, BOOL IsUBFServer)
{
	if (m_DBQuery.IsConnected() == FALSE)
	{
		LogAddTD("[UBF] CQuery::IsConnected: FALSE");
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

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L3 [UBF][WZ_UnityBattleFieldGetRealName_r] [%s]", szCahrUBFName);
		m_DBQuery.Clear();
		return FALSE;
	}

	SQLRETURN sqlReturn = m_DBQuery.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldGetRealName_r] [%s] Return %d,%s,%d ", szCahrUBFName, sqlReturn, __FILE__, __LINE__);
		m_DBQuery.Clear();
		return FALSE;
	}

	m_DBQuery.GetStr("Name", szRealName);
	*ServerCode = m_DBQuery.GetInt("ServerCode");
	
	m_DBQuery.Clear();
	return TRUE;
}