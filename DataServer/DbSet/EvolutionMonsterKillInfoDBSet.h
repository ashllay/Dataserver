#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"

class CMonsterKillInfoDbSet : public CDBConBase
{
public:
	
	CMonsterKillInfoDbSet();
	virtual ~CMonsterKillInfoDbSet();

	BOOL Connect();
	int DSDB_SelectMonsterKillInfo(char *szAccountID, char *szCharName, _tagSDHP_ANS_EVENT_MONSTER_KILL_INFO *pMsgSend);
	int DSDB_UpdateMonsterKillInfo(_tagSDHP_REQ_EVENT_MONSTER_KILL_INFO_SAVE *pMsgRecv);
};