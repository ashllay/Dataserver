// MasterLevelSystemDBSet.cpp: implementation of the CMasterLevelSystemDBSet class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#ifdef MASTER_LEVEL_UP_SYSTEM_20070912
#include "MasterLevelSystemDBSet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMasterLevelSystemDBSet::CMasterLevelSystemDBSet()
{

}

CMasterLevelSystemDBSet::~CMasterLevelSystemDBSet()
{

}

BOOL CMasterLevelSystemDBSet::Connect()
{
	return this->CDBConBase::Connect(szDbConnectID, szDbConnectPass);
}

BOOL CMasterLevelSystemDBSet::DSDB_QueryMasterLevelSystemLoad(char* szCharName, LPMLP_ANS_MASTERLEVEL_INFO lpReqInfo)
{
	char szId[MAX_IDSTRING+1];
	szId[MAX_IDSTRING] = '\0';
	memcpy(szId, szCharName, MAX_IDSTRING);

	int len = strlen(szId);

	if(len <= 0 || len > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED,"%s] 저장 에러 %s %d", szId, __FILE__, __LINE__);
		return TRUE;
	}

	CString szQuery;

	szQuery.Format("EXEC WZ_MLS_InfoLoad '%s'", szId);

	if(this->m_DBQuery.Exec(szQuery) == FALSE)
	{
		this->m_DBQuery.Clear();
		return TRUE;
	}

	if(this->m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		this->m_DBQuery.Clear();
		return TRUE;
	}

	lpReqInfo->nMLevel = this->m_DBQuery.GetInt("MASTER_LEVEL");
	lpReqInfo->i64MLExp = this->m_DBQuery.GetInt64("ML_EXP");
	lpReqInfo->i64NextMLExp = this->m_DBQuery.GetInt64("ML_NEXTEXP");
	lpReqInfo->nMLPoint = this->m_DBQuery.GetInt("ML_POINT");

	this->m_DBQuery.Clear();
	return FALSE;
}

BOOL CMasterLevelSystemDBSet::DSDB_QueryMasterLevelSystemSave(LPMLP_REQ_MASTERLEVEL_INFOSAVE lpRecv)
{
	char szId[MAX_IDSTRING+1];
	szId[MAX_IDSTRING] = '\0';
	memcpy(szId, lpRecv->szCharName, MAX_IDSTRING);

	int len = strlen(szId);

	if(len <= 0 || len > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED,"%s] 저장 에러 %s %d", szId, __FILE__, __LINE__);
		return TRUE;
	}

	CString szQuery;
	szQuery.Format("EXEC WZ_MLS_InfoSave '%s', %d, %I64d, %I64d, %d", szId, lpRecv->nMLevel, lpRecv->i64MLExp, lpRecv->i64NextMLExp, lpRecv->nMLPoint);

	if(this->m_DBQuery.Exec(szQuery) == FALSE)
	{
		this->m_DBQuery.Clear();
		return TRUE;
	}

	this->m_DBQuery.Clear();
	return FALSE;
}
#endif