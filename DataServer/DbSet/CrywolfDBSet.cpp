// CrywolfDBSet.cpp: implementation of the CCrywolfDBSet class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#ifdef MU_CRYWOLF_DS_PROTOCOL_20050505
#include "CrywolfDBSet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCrywolfDBSet::CCrywolfDBSet()
{

}

CCrywolfDBSet::~CCrywolfDBSet()
{

}

BOOL CCrywolfDBSet::Connect()
{
	return this->CDBConBase::Connect(szDbConnectID, szDbConnectPass);
}

BOOL CCrywolfDBSet::DSDB_QueryCrywolfStateUpdate()
{
	return FALSE;
}

BOOL CCrywolfDBSet::DSDB_QueryCrywolfInfoLoad(int iMapSvrGroup, LPCWP_ANS_CRYWOLFINFOLOAD lpAnsMsg)
{
	CString szQuery;

	szQuery.Format("EXEC WZ_CW_InfoLoad %d", iMapSvrGroup);

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

	lpAnsMsg->iOccupationState = this->m_DBQuery.GetInt("CRYWOLF_OCCUFY");
	lpAnsMsg->iCrywolfState = this->m_DBQuery.GetInt("CRYWOLF_STATE");

	this->m_DBQuery.Clear();

	return FALSE;
}

BOOL CCrywolfDBSet::DSDB_QueryCrywolfInfoSave(int iMapSvrGroup, LPCWP_REQ_CRYWOLFINFOSAVE lpReqMsg)
{
	CString szQuery;

	szQuery.Format("EXEC WZ_CW_InfoSave %d, %d, %d", iMapSvrGroup, lpReqMsg->iCrywolfState, lpReqMsg->iOccupationState);

	if(this->m_DBQuery.Exec(szQuery) == FALSE)
	{
		this->m_DBQuery.Clear();
		return TRUE;
	}

	this->m_DBQuery.Clear();

	return FALSE;
}
#endif