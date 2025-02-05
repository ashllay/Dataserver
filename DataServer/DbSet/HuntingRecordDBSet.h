#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"

#define MAX_HUNTING_RECORD_MAP_LIST 60
#define MAX_HUNTING_RECORD_EXCEPT_MONSTER_LIST 100
#define MAX_HUNTING_RECORD_USER_DATA MAX_HUNTING_RECORD_MAP_LIST

#pragma pack (1)
typedef struct HUNTING_RECORD_INFO
{
	BYTE btMapIndex;
	int iYear;
	BYTE btMonth;
	BYTE btDay;
	int iCurrentLevel;
	int iHuntingAccrueSecond;
	__int64 i64NormalAccrueDamage;
	__int64 i64PentagramAccrueDamage;
	int iHealAccrueValue;
	int iMonsterKillCount;
	__int64 i64AccrueExp;
	int iClass;
	int iMaxNormalDamage;
	int iMinNormalDamage;
	int iMaxPentagramDamage;
	int iMinPentagramDamage;
	int iGetNormalAccrueDamage;
	int iGetPentagramAccrueDamage;
} *LPHUNTING_RECORD_INFO;
#pragma pack ()

typedef struct SDHP_ANS_HUNTING_RECORD_COUNT
{
	PWMSG_HEAD2 head; // C2:BC:10 DS->GS
	BYTE btResult;
	BYTE btListCnt;
	BYTE btMapIndex;
	BYTE btCallType;
	BYTE btAnotherUser;
	int iUserIndex;
} *LPSDHP_ANS_HUNTING_RECORD_COUNT;

typedef struct SDHP_ANS_HUNTING_RECORD_INFO_USER_OPEN
{
	PBMSG_HEAD2 h; // C1:BC:12 DS->GS
	BYTE btResult;
	int iUserIndex;
	BYTE btOpen;
} *LPSDHP_ANS_HUNTING_RECORD_INFO_USER_OPEN;

#pragma pack (1)
typedef struct SDHP_ANS_HUNTING_RECORD_INFO_CURRENT
{
	PWMSG_HEAD2 h; // C2:BC:14 DS->GS
	int iUserIndex;
	BYTE btCallType;
	BYTE btListCnt;
	BYTE btMapIndex;
	int iYear;
	BYTE btMonth;
	BYTE btDay;
	int iCurrentLevel;
	int iHuntingAccrueSecond;
	__int64 i64NormalAccrueDamage;
	__int64 i64PentagramAccrueDamage;
	int iHealAccrueValue;
	int iMonsterKillCount;
	__int64 i64AccrueExp;
	int iClass;
	int iMaxNormalDamage;
	int iMinNormalDamage;
	int iMaxPentagramDamage;
	int iMinPentagramDamage;
	int iGetNormalAccrueDamage;
	int iGetPentagramAccrueDamage;
} *LPSDHP_ANS_HUNTING_RECORD_INFO_CURRENT;
#pragma pack ()

typedef struct SDHP_REQ_HUNTING_RECORD_INFO_SAVE
{
	PWMSG_HEAD2 h; // C2:BC:11 GS->DS
	BYTE btListCnt;
	char AccountId[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
} *LPSDHP_REQ_HUNTING_RECORD_INFO_SAVE;


typedef struct SDHP_REQ_HUNTING_RECORD_INFO_USER_OPEN_SAVE
{
	PBMSG_HEAD2 h; // C1:BC:13 GS->DS
	char AccountId[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	int iUserIndex;
	BYTE btOpen;
} *LPSDHP_REQ_HUNTING_RECORD_INFO_USER_OPEN_SAVE;

typedef struct SDHP_REQ_HUNTING_RECORD_INFO
{
	PBMSG_HEAD2 h; // C1:BC:10 GS->DS
	char AccountId[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	int iUserIndex;
	BYTE btMapIndex;
	BYTE btCallType;
	BYTE btAnotherUser;
} *LPSDHP_REQ_HUNTING_RECORD_INFO;

struct SDHP_REQ_HUNTING_RECORD_INFO_USER_OPEN
{
	PBMSG_HEAD2 h;
	char AccountId[11];
	char szName[11];
	int iUserIndex;
};

typedef struct SDHP_REQ_HUNTING_RECORD_INFO_CURRENT
{
	PBMSG_HEAD2 h; // C1:BC:14 GS->DS
	char AccountId[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	int iUserIndex;
	BYTE btMapIndex;
	int iYear;
	BYTE btMonth;
	BYTE btDay;
	BYTE btCallType;
} *LPSDHP_REQ_HUNTING_RECORD_INFO_CURRENT;

typedef struct SDHP_REQ_DELETE_HUNTING_RECORD_INFO
{
	PBMSG_HEAD2 h; // C1:BC:15 GS->DS
	char AccountId[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	int iUserIndex;
	BYTE btMapIndex;
	int iYear;
	BYTE btMonth;
	BYTE btDay;
} *LPSDHP_REQ_DELETE_HUNTING_RECORD_INFO;

class CHuntingRecordDBSet : public CDBConBase
{
public:

	CHuntingRecordDBSet();
	virtual ~CHuntingRecordDBSet();

	int Connect();
	int LoadHuntingRecordInfo(char* szAccountID, char* Name, HUNTING_RECORD_INFO* pHuntingRecordInfo, SDHP_ANS_HUNTING_RECORD_COUNT* pMsg, int iMapIndex);
	int HuntingRecordInfoSave(SDHP_REQ_HUNTING_RECORD_INFO_SAVE* lpRecv);
	int LoadHuntingRecordInfoUserOpen(char* szAccountID, char* Name, SDHP_ANS_HUNTING_RECORD_INFO_USER_OPEN* pMsg);
	int HuntingRecordInfoUserOpenSave(SDHP_REQ_HUNTING_RECORD_INFO_USER_OPEN_SAVE* lpRecv);
	int LoadHuntingRecordInfo_Current(char* szAccountID, char* Name, SDHP_ANS_HUNTING_RECORD_INFO_CURRENT* pMsg, int iMapIndex, int iYear, char btMonth, char btDay);
	int DeleteHuntingRecordInfo(char* szAccountID, char* Name, int iMapIndex, int iYear, char btMonth, char btDay);
};