// QuestMonKillDBSet.cpp: implementation of the CQuestMonKillDBSet class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QuestMonKillDBSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQuestMonKillDBSet::CQuestMonKillDBSet()
{

}

CQuestMonKillDBSet::~CQuestMonKillDBSet()
{

}

BOOL CQuestMonKillDBSet::Connect()
{
	return this->CDBConBase::Connect(szDbConnectID, szDbConnectPass);
}

BOOL CQuestMonKillDBSet::DSDB_QueryQuestMonKillInfoLoad(char* szCharName, LPSDHP_QUEST_MONSTER_KILL_INFO lpReqInfo)
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

	szQuery.Format("EXEC WZ_QMK_InfoLoad '%s'", szId);

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

	lpReqInfo->btQuestDBIndex = this->m_DBQuery.GetInt("QUEST_INDEX");

	lpReqInfo->iQuestMonIndex1 = this->m_DBQuery.GetInt("MON_INDEX_1");
	lpReqInfo->iKillCount1 = this->m_DBQuery.GetInt("KILL_COUNT_1");

	lpReqInfo->iQuestMonIndex2 = this->m_DBQuery.GetInt("MON_INDEX_2");
	lpReqInfo->iKillCount2 = this->m_DBQuery.GetInt("KILL_COUNT_2");

	lpReqInfo->iQuestMonIndex3 = this->m_DBQuery.GetInt("MON_INDEX_3");
	lpReqInfo->iKillCount3 = this->m_DBQuery.GetInt("KILL_COUNT_3");

	lpReqInfo->iQuestMonIndex4 = this->m_DBQuery.GetInt("MON_INDEX_4");
	lpReqInfo->iKillCount4 = this->m_DBQuery.GetInt("KILL_COUNT_4");

	lpReqInfo->iQuestMonIndex5 = this->m_DBQuery.GetInt("MON_INDEX_5");
	lpReqInfo->iKillCount5 = this->m_DBQuery.GetInt("KILL_COUNT_5");

	this->m_DBQuery.Clear();

	return FALSE;
}

BOOL CQuestMonKillDBSet::DSDB_QueryQuestMonKillInfoSave(LPSDHP_QUEST_MONSTER_KILL_INFO lpRecv)
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

	szQuery.Format("EXEC WZ_QMK_InfoSave '%s', %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", szId, lpRecv->btQuestDBIndex, 
		lpRecv->iQuestMonIndex1, lpRecv->iKillCount1, 
		lpRecv->iQuestMonIndex2, lpRecv->iKillCount2, 
		lpRecv->iQuestMonIndex3, lpRecv->iKillCount3, 
		lpRecv->iQuestMonIndex4, lpRecv->iKillCount4,
		lpRecv->iQuestMonIndex5, lpRecv->iKillCount5);

	if(this->m_DBQuery.Exec(szQuery) == FALSE)
	{
		this->m_DBQuery.Clear();
		return TRUE;
	}

	this->m_DBQuery.Clear();

	return FALSE;
}