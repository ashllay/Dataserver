// CharPreviewDBSet.cpp: implementation of the CCharPreviewDBSet class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CharPreviewDBSet.h"
//#include "..\common\winutil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCharPreviewDBSet::CCharPreviewDBSet()
{

}

CCharPreviewDBSet::~CCharPreviewDBSet()
{

}

BOOL CCharPreviewDBSet::Conenect()
{
	if( m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass) == FALSE )
	{
		MsgBox("CharPreviewDBSet ODBC Connect Fail");
		return FALSE;
	}

	return TRUE;
}
int CCharPreviewDBSet::GetChar(char *Name, char *AccountId, int& _level, int& _class, BYTE *Inventory, BYTE& _ctlcode, BYTE& _dbverstion, char &_pkLevel, BYTE& _btGuildStatus)
{
	int nRet;
	int dbverstion;
	int ctlcode;
	CString qSql;

	if (!SQLSyntexCheck(Name))
	{
		return 0;
	}
	qSql.Format("SELECT Name, cLevel, Class, PkLevel, CtlCode, DbVersion FROM Character WHERE Name='%s'", Name);
	if (!this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		return 0;
	}
	if (this->m_DBQuery.Fetch() == 100)
	{
		this->m_DBQuery.Clear();
		return 0;
	}
	this->m_DBQuery.GetStr("Name", Name);
	_level = this->m_DBQuery.GetInt("cLevel");
	_class = this->m_DBQuery.GetInt("Class");
	_pkLevel = this->m_DBQuery.GetInt("PkLevel");
	//ctlcode = this->m_DBQuery.GetInt("CtlCode");
	//if (ctlcode < 0)
	//	LOBYTE(ctlcode) = 0;
	//*_ctlcode = ctlcode;
	ctlcode = m_DBQuery.GetInt("CtlCode");

	if (ctlcode < 0)
	{
		ctlcode = 0;
	}
	/*dbverstion = this->m_DBQuery.GetInt("DbVersion");
	if (dbverstion < 0)
		LOBYTE(dbverstion) = 0;
	*_dbverstion = dbverstion;*/
	dbverstion = m_DBQuery.GetInt("DbVersion");

	if (dbverstion < 0)
	{
		dbverstion = 0;
	}
	this->m_DBQuery.Clear();
	qSql.Format("WZ_GetLoadInventory '%s', '%s'", AccountId, Name);
	nRet = this->m_DBQuery.ReadBlob(qSql, Inventory);
	if (nRet)
	{
		if (nRet == -1)
		{
			return 0;
		}
	}
	else
	{
		memset(Inventory, 255, 0x78u);
	}
	this->m_DBQuery.Clear();
	qSql.Format("SELECT G_Status FROM GuildMember WHERE Name='%s'", Name);

	_btGuildStatus = 0xFF;

	if (m_DBQuery.Exec(qSql) == TRUE)
	{
		if (m_DBQuery.Fetch() == SQL_NO_DATA)
		{
		}
		else
		{
			_btGuildStatus = m_DBQuery.GetInt("G_Status");
		}
	}

	m_DBQuery.Clear();
	return 1;
}
//BOOL CCharPreviewDBSet::GetChar(char* Name, /*char *AccountId, */int& _level, int& _class, BYTE* Inventory, BYTE& _ctlcode, BYTE& _dbverstion, BYTE& _btGuildStatus)
//{
//	CString qSql;
//
//	if(SQLSyntexCheck(Name) == FALSE)
//	{
//		return FALSE;
//	}
//
//	qSql.Format("SELECT Name, cLevel, Class, CtlCode, DbVersion FROM vCharacterPreview WHERE Name='%s'", Name);
//
//	if(m_DBQuery.Exec(qSql) == FALSE)
//	{
//		m_DBQuery.Clear();
//		return FALSE;
//	}
//
//	if(m_DBQuery.Fetch() == SQL_NO_DATA)
//	{
//		m_DBQuery.Clear();
//		return FALSE;
//	}
//
//	m_DBQuery.GetStr("Name", Name);
//
//	_level = m_DBQuery.GetInt("cLevel");
//	_class = m_DBQuery.GetInt("Class");
//
//	int ctlcode = m_DBQuery.GetInt("CtlCode");
//
//	if(ctlcode < 0)
//	{
//		ctlcode = 0;
//	}
//
//	_ctlcode = ctlcode;
//
//	int dbverstion = m_DBQuery.GetInt("DbVersion");
//
//	if(dbverstion < 0)
//	{
//		dbverstion = 0;
//	}
//
//	_dbverstion = dbverstion;
//
//	/*qSql.Format("WZ_GetLoadInventory '%s', '%s'",AccountId,Name);
//
//	m_DBQuery.ReadBlob(qSql, Inventory);*/
//
//	m_DBQuery.Clear();
//
//	qSql.Format("SELECT Inventory FROM Character WHERE Name='%s'", Name);
//	int nRet = m_DBQuery.ReadBlob(qSql, Inventory);
//
//	if(nRet == 0)
//	{
//		memset(Inventory, 0xFF, 120);
//	}
//	else if(nRet == -1)
//	{
//		return FALSE;
//	}
//
//	m_DBQuery.Clear();
//	
//#ifdef ADD_CHARACTERLIST_GUILD_STATUS_01_20050126
//	qSql.Format("SELECT G_Status FROM GuildMember WHERE Name='%s'", Name);
//
//	_btGuildStatus = 0xFF;
//
//	if(m_DBQuery.Exec(qSql) == TRUE)
//	{
//		if(m_DBQuery.Fetch() == SQL_NO_DATA)
//		{
//		}
//		else
//		{
//			_btGuildStatus = m_DBQuery.GetInt("G_Status");
//		}
//	}
//
//	m_DBQuery.Clear();
//#endif
//
//	return TRUE;
//}

BOOL CCharPreviewDBSet::GetRealNameAndServerCode(char *szUBFName, char *szRealName, int *ServerCode, int IsUBFServer)
{
	int result;
	__int16 sqlReturn;
	CString qSql;
	char szCahrUBFName[11];


	if (this->m_DBQuery.IsConnected())
	{
		szCahrUBFName[10] = 0;
		memcpy(szCahrUBFName, szUBFName, 0xAu);
		//strlen(szCahrUBFName);
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
					LogAddTD("Error-L3 [ChaosCastleFinalDBSet][WZ_UnityBattleFieldGetRealName_r] [%s] Return %d,%s,%d ",szCahrUBFName,sqlReturn, __FILE__, __LINE__);
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
		LogAddTD("[UBF] CQuery::IsConnected: FALSE");
		result = 0;
	}
	return result;
}