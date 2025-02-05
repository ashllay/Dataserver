#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"

typedef struct _SDHP_REQ_RESTORE_ITEM_LIST
{
	PWMSG_HEAD2 h;
	int userIndex;
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
} *LPSDHP_REQ_RESTORE_ITEM_LIST;

typedef struct _SDHP_ANS_RESTORE_ITEM_LIST
{
	PWMSG_HEAD2 h;
	int userIndex;
	BYTE result;
	BYTE dbRestoreItemData[150];
	BYTE dbVersion;
} *LPSDHP_ANS_RESTORE_ITEM_LIST;

typedef struct _SDHP_REQ_RESTORE_ITEM_LIST_SAVE
{
	PWMSG_HEAD2 h;
	int userIndex;
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	BYTE dbRestoreItemData[150];
} *LPSDHP_REQ_RESTORE_ITEM_LIST_SAVE;

class CRestoreItemDBSet : public CDBConBase
{
public:

	CRestoreItemDBSet();
	virtual ~CRestoreItemDBSet();

	int Connect();
	int DSDB_SelectRestoreItem(char *AccountID, char *Name, int userIndex, _SDHP_ANS_RESTORE_ITEM_LIST *lpSendMsg); // idb
	__int64 DSDB_UpdateRestoreItem(char *AccountID, char *Name, LPBYTE RestoreInventoryBuf);
};