#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"


class CPentagramDBSet : public CDBConBase
{
public:

	CPentagramDBSet();
	virtual ~CPentagramDBSet();

	int Connect();
	BOOL GetPentagramJewel(int iUserGuid, char *szAccountID, char *Name, PENTAGRAMJEWEL_INFO *pPentagramJewelInfo, PMSG_ANS_PENTAGRAMJEWEL *pMsg, BYTE iReqType); // idb
	BOOL SetPentagramJewel(PMSG_PENTAGRAMJEWEL_INFO *lpRecv); // idb
	int DelPentagramJewel(PMSG_DEL_PENTAGRAMJEWEL *lpRecv); // idb
	int InsertPentagramJewel(PMSG_INSERT_PENTAGRAMJEWEL *lpRecv); // idb
};

class CPentagramLogDBSet : public CDBConBase
{
public:
	CPentagramLogDBSet();
	virtual ~CPentagramLogDBSet();
	int Connect(); // idb
	int InsertJewelUpgradeInfo(_tagPMSG_REQ_JEWEL_UPGRADE_INFO_INSERT_DS *lpMsg); // idb
};