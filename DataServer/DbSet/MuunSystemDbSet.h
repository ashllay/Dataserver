#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"
#define MAX_DBMUUNINVENTORY			1632
#define MAX_MUUN_INVENTORY_SLOT		102

/* 665 */
struct _stMuunPeriodInfoList
{
	_stMuunPeriodInfoList()
	{
		this->wItemType = 0;
		this->dwSerial = 0;
		this->lItemExpireDate = 0;
	}
	unsigned __int16 wItemType;
	unsigned int dwSerial;
	int lItemExpireDate;
};
/* 666 */
struct _stMuunConditionInfoList
{
	_stMuunConditionInfoList()
	{
		this->btConditionType = -1;
		this->btSlotIndex = -1;
		this->wValue = 0;
	}
	BYTE btConditionType;
	BYTE btSlotIndex;
	WORD wValue;
};

/* 1076 */
struct _tagSDHP_ANS_MUUN_CONDITION_INFO_LOAD
{
	PBMSG_HEAD2 h;
	short aIndex;
	_stMuunConditionInfoList MuunConditionInfoList[2];
};

/* 1065 */
struct _tagSDHP_REQ_DBMUUN_INVEN_SAVE
{
	PWMSG_HEAD h;
	char AccountID[11];
	char Name[11];
	BYTE dbInventory[MAX_DBMUUNINVENTORY];
};

/* 1066 */
struct SDHP_REQ_DBMUUN_INVEN_LOAD
{
	PBMSG_HEAD h;
	char AccountID[11];
	char Name[11];
	__int16 aIndex;
};

/* 1067 */
struct _tagSDHP_ANS_DBMUUN_INVEN_LOAD
{
	_tagSDHP_ANS_DBMUUN_INVEN_LOAD()
	{
		memset(this->dbItems, 0xFF, MAX_DBMUUNINVENTORY);
		this->DbVersion = 0;
		this->SubEquip = 0;
		this->aIndex = 0;
	}
	PWMSG_HEAD h;
	BYTE dbItems[MAX_DBMUUNINVENTORY];
	char DbVersion;
	char SubEquip;
	short aIndex;
};
/* 1068 */
struct SDHP_REQ_DBMUUN_INVEN_SUB_EQUIP_OPEN
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Name[11];
	short aIndex;
};

/* 1070 */
struct _tagSDHP_REQ_MUUN_PERIOD_INFO_SELECT
{
	PBMSG_HEAD2 h;
	char Name[11];
	short aIndex;
};
/* 1072 */
struct _tagSDHP_REQ_MUUN_PERIOD_INFO_INSERT
{
	PBMSG_HEAD2 h;
	__int16 aIndex;
	char Name[11];
	unsigned __int16 wItemType;
	unsigned int dwSerial;
	unsigned int dwItemDuration;
	int lItemExpireDate;
};

/* 1073 */
struct _tagSDHP_REQ_MUUN_PERIOD_INFO_UPDATE
{
	PBMSG_HEAD2 h;
	char Name[11];
	__int16 aIndex;
	unsigned __int16 wItemType;
	DWORD dwSerial;
	BYTE btUsedInfo;
};

struct _tagSDHP_REQ_MUUN_CONDITION_INFO_SAVE
{
	PBMSG_HEAD2 h;
	char Name[11];
	_stMuunConditionInfoList MuunConditionInfoList[2];
};
/* 1075 */
struct _tagSDHP_REQ_MUUN_CONDITION_INFO_LOAD
{
	PBMSG_HEAD2 h;
	char Name[11];
	short aIndex;
};

/* 1077 */
struct _tagSDHP_REQ_MUUN_CONDITION_INFO_DEL
{
	PBMSG_HEAD2 h;
	char Name[11];
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