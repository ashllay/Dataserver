#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"


class CPShopSystemDBSet : public CDBConBase
{
public:

	CPShopSystemDBSet();
	virtual ~CPShopSystemDBSet();

	int Connect();
	int LoadPShopItemValueInfo(char *szAccountID, char *Name, PMSG_PSHOPITEMVALUE_INFO *pPShopItemValueInfo, PMSG_ANS_PSHOPITEMVALUE_INFO *pMsg); // idb
	int SavePShopItemValueInfo(PMSG_UPDATE_PSHOPITEMVALUE_INFO *lpRecv); // idb
	int DelPShopItemValueInfo(PMSG_DEL_PSHOPITEM *lpRecv); // idb
	int MovePShopItem(PMSG_MOVE_PSHOPITEM *lpRecv); // idb
};