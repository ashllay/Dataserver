#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"


class CMineSystemDBSet : public CDBConBase
{
public:

	CMineSystemDBSet();
	virtual ~CMineSystemDBSet();

	int Connect();
	int DSDB_QueryInsertUPTUserInfo(char *szCharName, unsigned __int16 wTwinkleType, int iCurrentStage); // idb
	int DSDB_QueryDeleteUPTUserInfo(char *szCharName); // idb
	int DSDB_QuerySelectUPTUserInfo(char *szCharName, SDHP_ANS_LOAD_MINESYSTEM_UPT_USERINFO *pMsgSend); // idb
};