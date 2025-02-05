#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"


typedef struct _tagSDHP_REQ_EVENT_MONSTER_KILL_INFO_SAVE
{
	_tagSDHP_REQ_EVENT_MONSTER_KILL_INFO_SAVE()
	{
		iUserIndex = -1;
		memset(AccountID, 0, sizeof(AccountID));
		memset(CharName, 0, sizeof(CharName));
		MonsterIndex1 = -1;
		MonsterLevel1 = 0;
		KillCount1 = 0;
		MonsterIndex2 = -1;
		MonsterLevel2 = 0;
		KillCount2 = 0;
		MonsterIndex3 = -1;
		MonsterLevel3 = 0;
		KillCount3 = 0;
		MonsterIndex4 = -1;
		MonsterLevel4 = 0;
		KillCount4 = 0;
		MonsterIndex4 = -1;
		MonsterLevel4 = 0;
		KillCount4 = 0;
		MonsterIndex5 = -1;
		MonsterLevel5 = 0;
		KillCount5 = 0;
		DamageScore = 0;
	}

	PBMSG_HEAD2 h; // C1:3E:02 GS->DS
	int iUserIndex;
	char AccountID[MAX_IDSTRING + 1];
	char CharName[MAX_IDSTRING + 1];
	short MonsterIndex1;
	WORD MonsterLevel1;
	int KillCount1;
	short MonsterIndex2;
	WORD MonsterLevel2;
	int KillCount2;
	short MonsterIndex3;
	WORD MonsterLevel3;
	int KillCount3;
	short MonsterIndex4;
	WORD MonsterLevel4;
	int KillCount4;
	short MonsterIndex5;
	WORD MonsterLevel5;
	int KillCount5;
	__int64 DamageScore;
} *LPSDHP_REQ_EVENT_MONSTER_KILL_INFO_SAVE;


struct _tagSDHP_REQ_EVENT_MONSTER_KILL_INFO
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char AccountID[MAX_IDSTRING + 1];
	char CharName[MAX_IDSTRING + 1];
};

typedef struct _tagSDHP_ANS_EVENT_MONSTER_KILL_INFO
{
	PBMSG_HEAD2 h; // C1:3E:01 DS->GS
	int iUserIndex;
	short MonsterIndex1;
	WORD MonsterLevel1;
	int KillCount1;
	short MonsterIndex2;
	WORD MonsterLevel2;
	int KillCount2;
	short MonsterIndex3;
	WORD MonsterLevel3;
	int KillCount3;
	short MonsterIndex4;
	WORD MonsterLevel4;
	int KillCount4;
	short MonsterIndex5;
	WORD MonsterLevel5;
	int KillCount5;
	__int64 DamageScore;
	BYTE btResult;
} *LPSDHP_ANS_EVENT_MONSTER_KILL_INFO;


struct SDHP_ANS_EVENT_MONSTER_KILL_INFO_SAVE
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	BYTE btResult;
};

class CMonsterKillInfoDbSet : public CDBConBase
{
public:
	
	CMonsterKillInfoDbSet();
	virtual ~CMonsterKillInfoDbSet();

	BOOL Connect();
	int DSDB_SelectMonsterKillInfo(char *szAccountID, char *szCharName, _tagSDHP_ANS_EVENT_MONSTER_KILL_INFO *pMsgSend);
	int DSDB_UpdateMonsterKillInfo(_tagSDHP_REQ_EVENT_MONSTER_KILL_INFO_SAVE *pMsgRecv);
};