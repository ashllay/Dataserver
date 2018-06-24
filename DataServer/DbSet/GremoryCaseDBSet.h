#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"


class CGremoryCaseDBSet : public CDBConBase
{
public:

	CGremoryCaseDBSet();
	virtual ~CGremoryCaseDBSet();

	int Connect();
	int GetItemSerial(unsigned int *sirial_number, int MakeSeiralCount); // idb
	int InsertGremoryCase(char *szAccountID, char *szName, char btGCType, char btGiveType, char btItemType, unsigned __int16 wItemIndex, char btLevel, char btDur, char btSkill, char btLuck, char btOpt, char btSetOpt, unsigned __int16 wNewOpt, char btBonusSocketOpt, char *btSocketOpt, unsigned int dwReceiptExpireDuration, unsigned int dwItemDuration, int lRecvDate, int lRecvExpireDate, int lItemExpireDate, unsigned int *dwSerial); // idb
	int SelectGremoryCase(char *szAccountID, char *szName, _stGremoryCaseList *pGCList, char *btListCnt); // idb
	int UpdateGremoryCase(char *szAccountID, char *szName, char btGCType, char btItemType, unsigned __int16 wItemIndex, char btLevel, unsigned int dwSerial, int lRecvDate, char btUsedInfo); // idb
	int UpdateGremoryCaseItemRecv(char *szAccountID, char *szName, char btGCType, char btItemType, unsigned __int16 wItemIndex, char btLevel, unsigned int dwSerial, int lRecvDate, char btUsedInfo); // idb

};

class CGremoryCaseSerial
{
public:

	CGremoryCaseSerial();
	virtual ~CGremoryCaseSerial();

	int MakeSerial(); // idb
	unsigned int GetSerial(); // idb

	unsigned int m_dwGCItemSerial;
	unsigned int m_dwGCLastSerial;
	_RTL_CRITICAL_SECTION m_csGCItemSerial;
};
