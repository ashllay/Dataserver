#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"
#define MAX_LAB_MISSION_TRAIT 6
#define MAX_LAB_GATE 4
#define MAX_LAB_ZONE 100
#define MAX_LAB_VISITED_LIST 200
#define MAX_LAB_MAIN_MISSION 5

/* 6304 */
struct SDHP_REQ_LABYRINTH_INFO_UPDATE
{
	PWMSG_HEAD2 h;
	char szAccountID[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	int nUserIndex;
	char btDimensionLevel;
	unsigned __int16 wConfigNum;
	char btCurrentZone;
	char btVisitedCnt;
	char btVisitedList[MAX_LAB_VISITED_LIST];
	__int64 nEntireExp;
	__int64 nEntireMonKillCnt;
};

/* 6305 */
struct  SDHP_REQ_LABYRINTH_MISSION_UPDATE
{
	PWMSG_HEAD2 h;
	char szAccountID[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	int nUserIndex;
	char btZoneNumber;
	char btMissionType;
	int nMissionValue;
	int nAcquisionValue;
	char btMissionState;
	char btIsMainMission;
	char btMainMissionOrder;
	int nRewardItemType;
	int nRewardItemIndex;
	int nRewardValue;
	char btRewardCheckState;
};
/* 6306 */
struct SDHP_REQ_LABYRINTH_INFO
{
	PWMSG_HEAD2 h;
	char szAccountID[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	int nUserIndex;
};

/* 6307 */
struct SDHP_REQ_LABYRINTH_MISSION_DELETE
{
	PWMSG_HEAD2 h;
	char szAccountID[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	int nUserIndex;
};

/* 6308 */
struct SDHP_REQ_LABYRINTH_END_UPDATE
{
	PWMSG_HEAD2 h;
	char szAccountID[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	int nUserIndex;
	int nClearCnt;
	char btClearState;
};
/* 6309 */
struct  SDHP_ANS_LABYRINTH_INFO
{
	PWMSG_HEAD2 h;
	int nUserIndex;
	char btResult;
	char btDimensionLevel;
	unsigned __int16 wConfigNum;
	char btCurrentZone;
	char btVisitedCnt;
	char btVisitedList[200];
	__int64 nEntireExp;
	__int64 nEntireMonKillCnt;
	int nClearCnt;
	char btClearState;
	char btMissionCount;
};

/* 6310 */
struct MISSION_INFO
{
	char btZoneNumber;
	char btMissionType;
	int nMissionValue;
	int nAcquisionValue;
	char btMissionState;
	char btIsMainMission;
	char btMainMissionOrder;
	int nRewardItemType;
	int nRewardItemIndex;
	int nRewardValue;
	char btRewardCheckState;
};
/* 63MAX_IDSTRING + 1 */
struct SDHP_REQ_LABYRINTH_INFO_SAVE
{
	PWMSG_HEAD2 h;
	char szAccountID[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	int nUserIndex;
	char btDimensionLevel;
	unsigned __int16 wConfigNum;
	char btCurrentZone;
	char btVisitedCnt;
	char btVisitedList[MAX_LAB_VISITED_LIST];
	__int64 nEntireExp;
	__int64 nEntireMonKillCnt;
	int nClearCnt;
	char btClearState;
	char btMissionCount;
};

/* 6312 */
struct SDHP_REQ_LABYRINTH_REWARD_COMPLETE
{
	PWMSG_HEAD2 h;
	char szAccountID[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	int nUserIndex;
	char btIsMainMission;
	char btRewardCheckState;
};

/* 6313 */
struct SDHP_REQ_LABYRINTH_CLEAR_LOG_SET_SAVE
{
	PWMSG_HEAD2 h;
	char szAccountID[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	int nUserIndex;
	int nDimensionLevel;
};

class LabyrinthDBSet : public CDBConBase
{
public:

	LabyrinthDBSet();
	virtual ~LabyrinthDBSet();

	int Connect();
	int LoadLabyrinthInfo(char *szAccountID, char *szName, int nUserIndex, char *Buffer, int *nBufferLen); // idb
	int SaveLabyrinthInfo(SDHP_REQ_LABYRINTH_INFO_SAVE* aRecv);
	int SaveLabyrinthInfo(BYTE* aRecv);
	__int64 UpdateLabyrinthInfo(SDHP_REQ_LABYRINTH_INFO_UPDATE *aRecv);
	int UpdateLabyrinthMission(SDHP_REQ_LABYRINTH_MISSION_UPDATE *aRecv); // idb
	int DeleteLabyrinthMission(char *szAccountID, char *szName); // idb
	int EndUpdateLabyrinthInfo(char *szAccountID, char *szName, int nClearCnt, char btClearState); // idb
	int UpdateLabyrinthRewardState(char *szAccountID, char *szName, char btIsMainMission, char btRewardCheckState); // idb
	int SaveLabyrinthClearLog(char *szAccountID, char *szName, int nDimensionLevel); // idb
};