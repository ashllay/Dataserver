#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"


class CHuntingRecordDBSet : public CDBConBase
{
public:

	CHuntingRecordDBSet();
	virtual ~CHuntingRecordDBSet();

	int Connect();
	int LoadHuntingRecordInfo(char *szAccountID, char *Name, HUNTING_RECORD_INFO *pHuntingRecordInfo, SDHP_ANS_HUNTING_RECORD_COUNT *pMsg, int iMapIndex); // idb
	int HuntingRecordInfoSave(SDHP_REQ_HUNTING_RECORD_INFO_SAVE *lpRecv); // idb
	int LoadHuntingRecordInfoUserOpen(char *szAccountID, char *Name, SDHP_ANS_HUNTING_RECORD_INFO_USER_OPEN *pMsg); // idb
	int HuntingRecordInfoUserOpenSave(SDHP_REQ_HUNTING_RECORD_INFO_USER_OPEN_SAVE *lpRecv); // idb
	int LoadHuntingRecordInfo_Current(char *szAccountID, char *Name, SDHP_ANS_HUNTING_RECORD_INFO_CURRENT *pMsg, int iMapIndex, int iYear, char btMonth, char btDay); // idb
	int DeleteHuntingRecordInfo(char *szAccountID, char *Name, int iMapIndex, int iYear, char btMonth, char btDay); // idb
};