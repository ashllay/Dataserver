#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"

typedef struct _stGremoryCaseList
{
	_stGremoryCaseList()
	{
		btGCType = 0;
		btGiveType = 0;
		btItemType = 0;
		wItemIndex = 0;
		btLevel = 0;
		btDur = 0;
		btSkill = 0;
		btLuck = 0;
		btOpt = 0;
		btSetOpt = 0;
		wNewOpt = 0;
		btBonusSocketOpt = 0;
		memset(btSocketOpt, 0xFF, sizeof(btSocketOpt));
		dwSerial = 0;
		lRecvDate = 0;
		lRecvExpireDate = 0;
		lItemExpireDate = 0;
	}

	BYTE btGCType;
	BYTE btGiveType;
	BYTE btItemType;
	WORD wItemIndex;
	BYTE btLevel;
	BYTE btDur;
	BYTE btSkill;
	BYTE btLuck;
	BYTE btOpt;
	BYTE btSetOpt;
	WORD wNewOpt;
	BYTE btBonusSocketOpt;
	BYTE btSocketOpt[5];
	DWORD dwSerial;
	long lRecvDate;
	long lRecvExpireDate;
	long lItemExpireDate;
};

typedef struct _tagSDHP_REQ_GREMORY_CASE_INSERT
{
	_tagSDHP_REQ_GREMORY_CASE_INSERT()
	{
		memset(AccountID, 0, sizeof(AccountID));
		memset(Name, 0, sizeof(Name));
	}

	PBMSG_HEAD2 h;
	short aIndex;
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	BYTE btGCType;
	BYTE btGiveType;
	BYTE btItemType;
	WORD wItemIndex;
	BYTE btLevel;
	BYTE btDur;
	BYTE btSkill;
	BYTE btLuck;
	BYTE btOpt;
	BYTE btSetOpt;
	WORD wNewOpt;
	BYTE btBonusSocketOpt;
	BYTE btSocketOpt[5];
	DWORD dwReceiptExpireDuration;
	DWORD dwItemDuration;
	long lRecvDate;
	long lRecvExpireDate;
	long lItemExpireDate;
} *LPSDHP_REQ_GREMORY_CASE_INSERT;

typedef struct _tagSDHP_ANS_GREMORY_CASE_INSERT
{
	_tagSDHP_ANS_GREMORY_CASE_INSERT()
	{
	}

	PBMSG_HEAD2 h;
	short aIndex;
	BYTE btResult;
	BYTE btGCType;
	BYTE btGiveType;
	BYTE btItemType;
	WORD wItemIndex;
	BYTE btLevel;
	BYTE btDur;
	BYTE btSkill;
	BYTE btLuck;
	BYTE btOpt;
	BYTE btSetOpt;
	WORD wNewOpt;
	BYTE btBonusSocketOpt;
	BYTE btSocketOpt[5];
	DWORD dwSerial;
	long lRecvDate;
	long lRecvExpireDate;
	long lItemExpireDate;
} *LPSDHP_ANS_GREMORY_CASE_INSERT;

typedef struct _tagSDHP_REQ_GC_UPDATE
{
	_tagSDHP_REQ_GC_UPDATE()
	{
		memset(AccountID, 0, sizeof(AccountID));
		memset(Name, 0, sizeof(Name));
	}

	PBMSG_HEAD2 h;
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	short aIndex;
	BYTE btGCType;
	BYTE btItemType;
	WORD wItemIndex;
	BYTE btLevel;
	DWORD dwSerial;
	int lRecvDate;
	BYTE btUsedInfo;
} *LPSDHP_REQ_GC_UPDATE;

typedef struct _tagSDHP_ANS_GC_UPDATE
{
	_tagSDHP_ANS_GC_UPDATE()
	{
	}

	PBMSG_HEAD2 h;
	short aIndex;
	BYTE btResult;
	BYTE btItemType;
	WORD wItemIndex;
	BYTE btLevel;
	DWORD dwSerial;
	long lRecvDate;
} *LPSDHP_ANS_GC_UPDATE;

struct _tagSDHP_REQ_GC_UPDATE_INSERT
{
	PBMSG_HEAD2 h;
	short aIndex;
	char btUpdate_GCType;
	char btUpdate_ItemType;
	WORD wUpdate_ItemIndex;
	char btUpdate_Level;
	DWORD dwUpdate_Serial;
	int lUpdate_RecvDate;
	char btUpdate_UsedInfo;
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	char btGCType;
	char btGiveType;
	char btItemType;
	WORD wItemIndex;
	char btLevel;
	char btDur;
	char btSkill;
	char btLuck;
	char btOpt;
	char btSetOpt;
	WORD wNewOpt;
	char btBonusSocketOpt;
	BYTE btSocketOpt[5];
	DWORD dwReceiptDuration;
	DWORD dwItemDuration;
	int lRecvDate;
	int lRecvExpireDate;
	int lItemExpireDate;
};

struct _tagSDHP_ANS_GC_UPDATE_INSERT
{
	PBMSG_HEAD2 h;
	short aIndex;
	char btUpdate_GCType;
	char btUpdate_ItemType;
	WORD wUpdate_ItemIndex;
	char btUpdate_Level;
	unsigned int dwUpdate_Serial;
	int lUpdate_RecvDate;
	char btUpdate_UsedInfo;
	char btGCType;
	char btGiveType;
	char btItemType;
	WORD wItemIndex;
	char btLevel;
	char btDur;
	char btSkill;
	char btLuck;
	char btOpt;
	char btSetOpt;
	WORD wNewOpt;
	char btBonusSocketOpt;
	BYTE btSocketOpt[5];
	unsigned int dwSerial;
	int lRecvDate;
	int lRecvExpireDate;
	int lItemExpireDate;
};

typedef struct _tagSDHP_REQ_GREMORY_CASE_SELECT
{
	_tagSDHP_REQ_GREMORY_CASE_SELECT()
	{
		memset(AccountID, 0, sizeof(AccountID));
		memset(Name, 0, sizeof(Name));
	}

	PBMSG_HEAD2 h;
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	short aIndex;
	BYTE btGCType;
} *LPSDHP_REQ_GREMORY_CASE_SELECT;

typedef struct _tagSDHP_ANS_GREMORY_CASE_SELECT
{
	_tagSDHP_ANS_GREMORY_CASE_SELECT()
	{
	}

	PWMSG_HEAD2 h;
	BYTE btResult;
	short aIndex;
	BYTE btCnt;
} *LPSDHP_ANS_GREMORY_CASE_SELECT;


class CGremoryCaseDBSet : public CDBConBase
{
public:

	CGremoryCaseDBSet();
	virtual ~CGremoryCaseDBSet();

	int Connect();
	int GetItemSerial(DWORD& sirial_number, int MakeSeiralCount);
	int InsertGremoryCase(char* szAccountID, char* szName, char btGCType, char btGiveType, char btItemType, WORD wItemIndex, char btLevel, char btDur, char btSkill, char btLuck, char btOpt, char btSetOpt, WORD wNewOpt, char btBonusSocketOpt, BYTE* btSocketOpt, unsigned int dwReceiptExpireDuration, unsigned int dwItemDuration, int lRecvDate, int lRecvExpireDate, int lItemExpireDate, unsigned int* dwSerial);
	int SelectGremoryCase(char* szAccountID, char* szName, _stGremoryCaseList* pGCList, char* btListCnt);
	int UpdateGremoryCase(char* szAccountID, char* szName, char btGCType, char btItemType, WORD wItemIndex, char btLevel, unsigned int dwSerial, int lRecvDate, char btUsedInfo);
	int UpdateGremoryCaseItemRecv(char* szAccountID, char* szName, char btGCType, char btItemType, WORD wItemIndex, char btLevel, unsigned int dwSerial, int lRecvDate, char btUsedInfo);

};

class CGremoryCaseSerial
{
public:

	CGremoryCaseSerial();
	virtual ~CGremoryCaseSerial();

	int MakeSerial();
	unsigned int GetSerial();

	DWORD m_dwGCItemSerial;
	DWORD m_dwGCLastSerial;
	_RTL_CRITICAL_SECTION m_csGCItemSerial;
};
