#include "StdAfx.h"
#include "EvolutionMonsterKillInfoDBSet.h"

CMonsterKillInfoDbSet::CMonsterKillInfoDbSet()
{
}

CMonsterKillInfoDbSet::~CMonsterKillInfoDbSet()
{
}

BOOL CMonsterKillInfoDbSet::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("CMonsterKillInfoDbSet ODBC Connect Fail");
	return 0;
}

//----- (0043AC60) --------------------------------------------------------
int CMonsterKillInfoDbSet::DSDB_SelectMonsterKillInfo(char *szAccountID, char *szCharName, _tagSDHP_ANS_EVENT_MONSTER_KILL_INFO *pMsgSend)
{
	int result; // eax
	CString qSql; // [esp+F8h] [ebp-20h]
	
	int v9;

	v9 = 0;
	qSql.Format("EXEC WZ_EvolutionMonsterInfoLoad '%s', '%s'",szAccountID,szCharName);

	if (m_DBQuery.Exec(qSql))
	{
		if (this->m_DBQuery.Fetch() == 100)
		{
			this->m_DBQuery.Clear();
			pMsgSend->btResult = 2;
			v9 = -1;
			result = 0;
		}
		else
		{
			pMsgSend->MonsterIndex1 = this->m_DBQuery.GetInt("MonsterIndex1");
			pMsgSend->MonsterLevel1 = this->m_DBQuery.GetInt("MonsterLevel1");
			pMsgSend->KillCount1 = this->m_DBQuery.GetInt("KillCount1");
			pMsgSend->MonsterIndex2 = this->m_DBQuery.GetInt("MonsterIndex2");
			pMsgSend->MonsterLevel2 = this->m_DBQuery.GetInt("MonsterLevel2");
			pMsgSend->KillCount2 = this->m_DBQuery.GetInt("KillCount2");
			pMsgSend->MonsterIndex3 = this->m_DBQuery.GetInt("MonsterIndex3");
			pMsgSend->MonsterLevel3 = this->m_DBQuery.GetInt("MonsterLevel3");
			pMsgSend->KillCount3 = this->m_DBQuery.GetInt("KillCount3");
			pMsgSend->MonsterIndex4 = this->m_DBQuery.GetInt("MonsterIndex4");
			pMsgSend->MonsterLevel4 = this->m_DBQuery.GetInt("MonsterLevel4");
			pMsgSend->KillCount4 = this->m_DBQuery.GetInt("KillCount4");
			pMsgSend->MonsterIndex5 = this->m_DBQuery.GetInt("MonsterIndex5");
			pMsgSend->MonsterLevel5 = this->m_DBQuery.GetInt("MonsterLevel5");
			pMsgSend->KillCount5 = this->m_DBQuery.GetInt("KillCount5");
			pMsgSend->DamageScore = this->m_DBQuery.GetInt64("AccumDmg");
			pMsgSend->btResult = 0;
			this->m_DBQuery.Clear();
			v9 = -1;
			result = 1;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD(
			"error-L3 : [EventMonster] DSDB_SelectMonsterKillInfo [%s][%s] %s %d",
			szAccountID,
			szCharName,__FILE__,__LINE__);
		pMsgSend->btResult = 1;
		v9 = -1;
		result = 0;
	}
	return result;
}

//----- (0043AFC0) --------------------------------------------------------
int CMonsterKillInfoDbSet::DSDB_UpdateMonsterKillInfo(_tagSDHP_REQ_EVENT_MONSTER_KILL_INFO_SAVE *pMsgRecv)
{
	char *v2;
	int result; 
	int iUserIndex;
	CString qSql;
	int v8;

	v8 = 0;
	iUserIndex = -1;
	iUserIndex = pMsgRecv->iUserIndex;
	qSql.Format(
		"EXEC WZ_EvolutionMonsterInfoSave '%s', '%s' ,%d, %d, %d, %d, %d, %d,  %d, %d, %d, %d, %d, %d, %d, %d, %d, %I64d",
		pMsgRecv->AccountID,
		pMsgRecv->CharName,
		pMsgRecv->MonsterIndex1,
		pMsgRecv->MonsterLevel1,
		pMsgRecv->KillCount1,
		pMsgRecv->MonsterIndex2,
		pMsgRecv->MonsterLevel2,
		pMsgRecv->KillCount2,
		pMsgRecv->MonsterIndex3,
		pMsgRecv->MonsterLevel3,
		pMsgRecv->KillCount3,
		pMsgRecv->MonsterIndex4,
		pMsgRecv->MonsterLevel4,
		pMsgRecv->KillCount4,
		pMsgRecv->MonsterIndex5,
		pMsgRecv->MonsterLevel5,
		pMsgRecv->KillCount5,
		LODWORD(pMsgRecv->DamageScore),
		HIDWORD(pMsgRecv->DamageScore));
	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		v8 = -1;
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [EventMonster] DSDB_SelectMonsterKillInfo [%s][%s] %s %d",
			pMsgRecv->AccountID,pMsgRecv->CharName, __FILE__, __LINE__);
		v8 = -1;
		result = 0;
	}
	return result;
}