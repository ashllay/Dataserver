#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"


class CBombHuntDBSet : public CDBConBase
{
public:

	CBombHuntDBSet();
	virtual ~CBombHuntDBSet();

	int Connect();
	int DBSelectBombHunt(char *szAccountID, char *szName, unsigned __int16 *wOutScore, char *btOutGameState, char *szOutTileState); // idb
	int DBInsertBombHunt(char *szAccountID, char *szName, unsigned __int16 wScore, unsigned __int16 wGameState, char *szTileState); // idb
	int DBDeleteBombHunt(char *szAccountID, char *szName); // idb
	int DBInsertBombHuntLog(char *szAccountID, char *szName, unsigned __int16 wScore, char btClear); // idb
};