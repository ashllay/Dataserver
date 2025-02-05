#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"

#define BOMB_HUNT_GAME_WIDTH 8
#define BOMB_HUNT_GAME_HEIGHT 6
#define BOMB_HUNT_GAME_BOMBCARD 11

#define MAX_BOMB_HUNT_RECUSIVE_CNT 385

/* 1037 */
typedef struct _tagPMSG_REQ_BOMB_HUNT_SELECT_DS
{
	PBMSG_HEAD2 h; // C1:E8:20 GS->DS
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	WORD aIndex;
} *LPPMSG_REQ_BOMB_HUNT_SELECT_DS;

/* 1038 */
typedef struct _tagPMSG_ANS_BOMB_HUNT_SELECT_DS
{
	PBMSG_HEAD2 h; // C1:E8:20 DS->GS
	WORD aIndex;
	BYTE btResult;
	WORD wScore;
	BYTE btGameState;
	BYTE szTileState[BOMB_HUNT_GAME_WIDTH * BOMB_HUNT_GAME_HEIGHT + 1];
} *LPPMSG_ANS_BOMB_HUNT_SELECT_DS;

/* 1039 */
typedef struct _tagPMSG_REQ_BOMB_HUNT_INSERT_DS
{
	PBMSG_HEAD2 h; // C1:E8:21 GS->DS
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	WORD aIndex;
	WORD wScore;
	BYTE btGameState;
	BYTE szTileState[BOMB_HUNT_GAME_WIDTH * BOMB_HUNT_GAME_HEIGHT + 1];
} *LPPMSG_REQ_BOMB_HUNT_INSERT_DS;

/* 1040 */
typedef struct _tagPMSG_REQ_BOMB_HUNT_DELETE_DS
{
	PBMSG_HEAD2 h; // C1:E8:22 GS->DS
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	WORD aIndex;
} *LPPMSG_REQ_BOMB_HUNT_DELETE_DS;

/* 1041 */
typedef struct _tagPMSG_REQ_BOMB_HUNT_LOG_INSERT_DS
{
	PBMSG_HEAD2 h; // C1:E8:23 GS->DS
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	WORD wScore;
	BYTE btClear;
} *LPPMSG_REQ_BOMB_HUNT_LOG_INSERT_DS;

class CBombHuntDBSet : public CDBConBase
{
public:

	CBombHuntDBSet();
	virtual ~CBombHuntDBSet();

	int Connect();
	int DBSelectBombHunt(char *szAccountID, char *szName, BYTE*wOutScore, char *btOutGameState, char *szOutTileState); // idb
	int DBInsertBombHunt(char *szAccountID, char *szName, BYTE wScore, BYTE wGameState, BYTE*szTileState); // idb
	int DBDeleteBombHunt(char *szAccountID, char *szName); // idb
	int DBInsertBombHuntLog(char *szAccountID, char *szName, BYTE wScore, char btClear); // idb
};