#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"

class CRestoreItemDBSet : public CDBConBase
{
public:

	CRestoreItemDBSet();
	virtual ~CRestoreItemDBSet();

	int Connect();
	int DSDB_SelectRestoreItem(char *AccountID, char *Name, int userIndex, _SDHP_ANS_RESTORE_ITEM_LIST *lpSendMsg); // idb
	__int64 DSDB_UpdateRestoreItem(char *AccountID, char *Name, char *RestoreInventoryBuf);
};