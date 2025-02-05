// AccountCharDBSet.h: interface for the CAccountCharDBSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCOUNTCHARDBSET_H__01C748D6_E836_4267_AF43_66BD9D34C7DC__INCLUDED_)
#define AFX_ACCOUNTCHARDBSET_H__01C748D6_E836_4267_AF43_66BD9D34C7DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "Include\ProDef.h"
#include "..\include\Sprodef.h"

typedef struct
{
	int DBNumber;
	char AccountId[MAX_IDSTRING + 1];
	char GameID1[MAX_IDSTRING + 1];
	char GameID2[MAX_IDSTRING + 1];
	char GameID3[MAX_IDSTRING + 1];
	char GameID4[MAX_IDSTRING + 1];
	char GameID5[MAX_IDSTRING + 1];
	BYTE CtlCode;
	BYTE MoveCnt;
}AccountCharacterInfo, * LPAccountCharacterInfo;

struct SDHP_ANS_SETACCOUNTINFO
{
	PBMSG_HEAD h;
	char AccountId[MAX_IDSTRING + 1];
	short Number;
	BYTE Result;
};

struct SDHP_ANS_SET_EXTENDEDINVEN_COUNT
{
	PBMSG_HEAD h;
	WORD Number;
	BYTE Result;
	BYTE ExtendedInvenCount;
	DWORD EventIndex;
	int ItemPos;
	BYTE BuyAtInGameShop;
	BYTE IsReplace;
};

struct SDHP_ANS_SET_EXTENDEDWAREHOUSE_COUNT
{
	PBMSG_HEAD h;
	WORD Number;
	BYTE Result;
	BYTE ExtendedWarehouseCount;
	DWORD EventIndex;
	int ItemPos;
	BYTE BuyAtInGameShop;
	BYTE IsReplace;
};

class CAccountCharDBSet
{
public:
	CAccountCharDBSet();
	virtual ~CAccountCharDBSet();

	BOOL Connect();
	BOOL CreateAccountCharacter(char* id);
	BOOL SaveAccountCharacter(char* id, int pos, char* GameID);
	BOOL SaveAccountCharacter(char* id, char* GameID1, char* GameID2, char* GameID3, char* GameID4, char* GameID5);
	int DeleteAccountCharacter(char* id, char* gameid);
	BOOL GetAccountId(char* Id);
	BOOL GetAccountInfo(char* Id, LPAccountCharacterInfo lpACInfo);
	int GetAccountCharBlank(char* Id);
	BOOL CurAccountCharacterSet(char* id, char* GameID);
	BYTE GetAccountCharCtlCode(char* Id);

	BYTE GetSummonerCardInfo(char* Id);
	BYTE SetSummonerCardInfo(char* Id, int Value);

	int GetCharacterExtendedInvenCount(char* id, BYTE& ExtendedInvenCount);
	int SetCharacterExtendedInvenCountAdd(char* id, BYTE ExtendedInvenCount);
	int SetCharacterExtendedInvenCountReplace(char* id, BYTE ExtendedInvenCount);

	BOOL CAccountCharDBSet::GetCharacterExtendedWarehouseCount(char* Name, BYTE* btAddExtendedWarehouseCount);
	int SetCharacterExtendedWarehouseCountAdd(char* id, BYTE& ExtendedWarehouseCount);
	int SetCharacterExtendedWarehouseCountReplace(char* id, BYTE ExtendedWarehouseCount);

	BOOL GetCharacterSlotCount(char* Name, BYTE* btSlotCount);
	BOOL SetCharacterSlotCount(char* Name, BYTE btAddSlotCount);

public:
	CQuery m_DBQuery;
};

#endif // !defined(AFX_ACCOUNTCHARDBSET_H__01C748D6_E836_4267_AF43_66BD9D34C7DC__INCLUDED_)
