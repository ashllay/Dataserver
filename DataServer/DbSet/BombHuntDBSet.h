#ifndef __BOMBHUNTDBSET_H__
#define __BOMBHUNTDBSET_H__
#pragma once

#include "..\Include\Sprodef.h"
#include "DBConBase.h"

class CBombHuntDBSet : public CDBConBase
{
public:

	CBombHuntDBSet();
	virtual ~CBombHuntDBSet();

	BOOL Connect();

	BOOL DBSelectBombHunt(char *szAccountID, char *szName, WORD& wOutScore, BYTE& btOutGameState, char *szOutTileState);
	BOOL DBInsertBombHunt(char *szAccountID, char *szName, WORD wScore, WORD wGameState, char *szTileState);
	BOOL DBDeleteBombHunt(char *szAccountID, char *szName);
	BOOL DBInsertBombHuntLog(char *szAccountID, char *szName, WORD wScore, BYTE btClear);

public:
	CQuery m_Query;
};

#endif