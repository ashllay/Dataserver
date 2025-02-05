// MuRummyDBSet.h: interface for the CMuRummyDBSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MURUMMYDBSET_H__BED5C4C4_EA0B_4126_A05F_9584C5F0E889__INCLUDED_)
#define AFX_MURUMMYDBSET_H__BED5C4C4_EA0B_4126_A05F_9584C5F0E889__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBConBase.h"

#define MAX_MURUMMY_CARD_INFO 24
#define MAX_MURUMMY_SLOT_CARD 8
#define MAX_MURUMMY_OUTCARD_INFO 5

#define MAX_MURUMMY_SPECIALCARD_INFO 3
#define MAX_MURUMMY_SLOT_SPECIALCARD 2
#define MAX_MURUMMY_OUTSPECIALCARD_INFO 1

#define MAX_MURUMMYCARDCOLOR 3
#define MAX_MURUMMYCARDNUMBER 8

struct _tagMuRummyCardInfoDS
{
	_tagMuRummyCardInfoDS()
	{
		btColor = -1;
		btNumber = -1;
		btSlotNum = -1;
		btSeq = -1;
		btStatus = -1;
	}
	BYTE btColor;
	BYTE btNumber;
	BYTE btSlotNum;
	BYTE btSeq;
	BYTE btStatus;
};

typedef struct _tagMuRummyCardUpdateDS
{
	_tagMuRummyCardUpdateDS()
	{
		btSlotNum = -1;
		btSeq = -1;
		btStatus = -1;
	}
	BYTE btSlotNum;
	BYTE btSeq;
	BYTE btStatus;
} *LPMuRummyCardUpdateDS;


struct _tagPMSG_REQ_MURUMMY_SELECT_DS
{
	PBMSG_HEAD2 h; // C1:E8:00 GS->DS
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	WORD aIndex;
};

struct _tagPMSG_ANS_MURUMMY_SELECT_DS
{
	PBMSG_HEAD2 h; // C1:E8:00 DS->GS
	WORD aIndex;
	WORD wScore;
	BYTE btResult;
	BYTE btGameType;
	BYTE btSpecialCardDeckCnt;
	_tagMuRummyCardInfoDS stMuRummyCardInfoDS[MAX_MURUMMY_CARD_INFO + MAX_MURUMMY_SPECIALCARD_INFO];
};

struct _tagPMSG_REQ_MURUMMY_INSERT_DS
{
	PBMSG_HEAD2 h; // C1:E8:01 GS->DS
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	WORD aIndex;
	BYTE btGameType;
	BYTE btSpecialCardDeckCnt;
	_tagMuRummyCardInfoDS stMuRummyCardInfoDS[MAX_MURUMMY_CARD_INFO + MAX_MURUMMY_SPECIALCARD_INFO];
};

typedef struct _tagPMSG_REQ_MURUMMY_SCORE_UPDATE_DS
{
	PBMSG_HEAD2 h; // C1:E8:02 GS->DS
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	WORD wScore;
	BYTE btGameType;
	BYTE btSpecialCardDeckCnt;
	BYTE btMatchType;
	_tagMuRummyCardUpdateDS stCardUpdateDS[4];
} *LPPMSG_REQ_MURUMMY_SCORE_UPDATE_DS;
struct _tagPMSG_REQ_MURUMMY_UPDATE_DS
{
	PBMSG_HEAD2 h;
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	char btSlotNum;
	char btStatus;
	char btSequence;
};

struct _tagPMSG_REQ_MURUMMY_DELETE_DS
{
	PBMSG_HEAD2 h;
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
};

typedef struct _tagPMSG_REQ_MURUMMY_SLOTUPDATE_DS
{
	PBMSG_HEAD2 h; // C1:E8:05 GS->DS
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	_tagMuRummyCardUpdateDS stCardUpdateDS;
} *LPPMSG_REQ_MURUMMY_SLOTUPDATE_DS;

typedef struct _tagPMSG_REQ_MURUMMY_INFO_UPDATE_DS
{
	PBMSG_HEAD2 h; // C1:E8:06 GS->DS
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	WORD wScore;
	BYTE btGameType;
	BYTE btSpecialCardCnt;
	_tagMuRummyCardUpdateDS stMuRummyCardUpdateDS[MAX_MURUMMY_CARD_INFO + MAX_MURUMMY_SPECIALCARD_INFO];
} *LPPMSG_REQ_MURUMMY_INFO_UPDATE_DS;

struct _tagPMSG_REQ_MURUMMY_LOG_INSERT_DS
{
	PBMSG_HEAD2 h; // C1:E8:07 GS->DS
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	WORD wScore;
};

class CMuRummyDBSet : public CDBConBase
{
public:

	CMuRummyDBSet();
	virtual ~CMuRummyDBSet();

	BOOL Connect();
	BOOL DBSelectMuRummyCardInfo(char* szAccountID, char* szName, _tagMuRummyCardInfoDS* stOutMuRummyCardInfoDS, WORD* wOutScore, BYTE* btGameType, BYTE* btSpecialCardDeckCnt); // idb
	BOOL DBInsertMuRummyCardInfo(char* szAccountID, char* szName, _tagMuRummyCardInfoDS* stMuRummyCardInfoDS, BYTE btGameType, BYTE btSpecialCardDeckCnt); // idb
	BOOL DBUpdateMuRummyCardInfo(char* szAccountID, char* szName, int iSlotNum, int iStatus, int iSequence); // idb
	BOOL DBUpdateMuRummyScore(char* szAccountID, char* szName, WORD wScore, _tagMuRummyCardUpdateDS* stCardUpdateDS, BYTE btGameType, BYTE btSpecialCardDeckCnt, BYTE btMatchType); // idb
	BOOL DBDeleteMuRummyCardInfo(char* szAccountID, char* szName); // idb
	BOOL DBUpdateMuRummyCardSlotInfo(char* szAccountID, char* szName, _tagMuRummyCardUpdateDS stCardUpdateDS); // idb
	BOOL DBUpdateMuRummyInfo(char* szAccountID, char* szName, WORD wScore, _tagMuRummyCardUpdateDS* stCardUpdateDS, BYTE btGameType, BYTE btSpecialDeckCnt); // idb
	BOOL DBInsertMuRummyLog(char* szAccountID, char* szName, WORD wScore); // idb
};

#endif // !defined(AFX_MURUMMYDBSET_H__BED5C4C4_EA0B_4126_A05F_9584C5F0E889__INCLUDED_)
