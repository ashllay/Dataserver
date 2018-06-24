#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"


class CMuRummyDBSet : public CDBConBase
{
public:

	CMuRummyDBSet();
	virtual ~CMuRummyDBSet();

	BOOL Connect();
	BOOL DBSelectMuRummyCardInfo(char *szAccountID, char *szName, _tagMuRummyCardInfoDS *stOutMuRummyCardInfoDS, unsigned __int16 *wOutScore, BYTE *btGameType, BYTE *btSpecialCardDeckCnt); // idb
	BOOL DBInsertMuRummyCardInfo(char *szAccountID, char *szName, _tagMuRummyCardInfoDS *stMuRummyCardInfoDS, BYTE btGameType, BYTE btSpecialCardDeckCnt); // idb
	BOOL DBUpdateMuRummyCardInfo(char *szAccountID, char *szName, int iSlotNum, int iStatus, int iSequence); // idb
	BOOL DBUpdateMuRummyScore(char *szAccountID, char *szName, unsigned __int16 wScore, _tagMuRummyCardUpdateDS *stCardUpdateDS, BYTE btGameType, BYTE btSpecialCardDeckCnt, BYTE btMatchType); // idb
	BOOL DBDeleteMuRummyCardInfo(char *szAccountID, char *szName); // idb
	BOOL DBUpdateMuRummyCardSlotInfo(char *szAccountID, char *szName, _tagMuRummyCardUpdateDS stCardUpdateDS); // idb
	BOOL DBUpdateMuRummyInfo(char *szAccountID, char *szName, unsigned __int16 wScore, _tagMuRummyCardUpdateDS *stCardUpdateDS, BYTE btGameType, BYTE btSpecialDeckCnt); // idb
	BOOL DBInsertMuRummyLog(char *szAccountID, char *szName, unsigned __int16 wScore); // idb
};