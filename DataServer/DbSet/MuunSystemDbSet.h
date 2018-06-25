#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"
#define MAX_MUUN_INVENTORY_SLOT	102

struct _stMuunPeriodInfoList
{
	_stMuunPeriodInfoList()
	{
		this->wItemType = 0;
		this->dwSerial = 0;
		this->lItemExpireDate = 0;
	}
	WORD wItemType;
	DWORD dwSerial;
	int lItemExpireDate;
};

class CMuunSystemDBSet : public CDBConBase
{
public:

	CMuunSystemDBSet();
	virtual ~CMuunSystemDBSet();

	int Connect();
	int LoadMuunInvenItem(char *Name, BYTE *ItemBuf, char *AccountId, int *SubEquip, int *DbVersion); // idb
	__int64 SaveMuunInvenItem(char *Name, BYTE *ItemBuf, char *AccountId);
	BOOL MuunInvenSubEquipOpen(char *AccountId, char *Name); // idb
	bool SelectMuunPeriodInfo(char *szName, _stMuunPeriodInfoList *MuunPeriodInfoList, BYTE *btListCnt); // idb
	BOOL InsertMuunPeriodInfo(char *szName, unsigned __int16 wItemType, unsigned int dwSerial, unsigned int dwItemDur, long lExpireDate); // idb
	BOOL UpdateMuunPeriodInfo(char *szName, unsigned __int16 wItemType, DWORD dwSerial, BYTE btUsedInfo); // idb
	BOOL LoadMuunConditionInfo(char *szName, _stMuunConditionInfoList *MuunConditionInfoList); // idb
	BOOL SaveMuunConditionInfo(char *szName, BYTE btConditionType, char btSlotIndex, WORD wValue); // idb
	BOOL DelMuunConditionInfo(char *szName); // idb
};