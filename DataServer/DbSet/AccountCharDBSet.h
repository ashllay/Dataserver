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
	char AccountId[MAX_IDSTRING+1];
	char GameID1[MAX_IDSTRING+1];
	char GameID2[MAX_IDSTRING+1];
	char GameID3[MAX_IDSTRING+1];
	char GameID4[MAX_IDSTRING+1];
	char GameID5[MAX_IDSTRING+1];
	BYTE CtlCode;
	BYTE MoveCnt;
}AccountCharacterInfo, *LPAccountCharacterInfo;


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
	BOOL GetSummonerCardInfo(char* Id);
	BOOL SetSummonerCardInfo(char* Id);
	BOOL SetCharacterExGameServerCode(char* Name, short sExGameServerCode);
	BOOL SetCharacterExtendedInvenCountAdd(char* Name, BYTE btAddExtendedInvenCount);
	BOOL SetCharacterExtendedInvenCountReplace(char* Name, BYTE btReplaceExtendedInvenCount);
	BOOL GetCharacterExtendedInvenCount(char* Name, char* btAddExtendedInvenCount);
	BOOL SetCharacterExtendedWarehouseCountAdd(char* Name, BYTE btAddExtendedWarehouseCount);
	BOOL SetCharacterExtendedWarehouseCountReplace(char* Name, BYTE btReplaceExtendedWarehouseCount);
	BOOL GetCharacterExtendedWarehouseCount(char* Name, BYTE* btAddExtendedWarehouseCount);
	//S12
	BOOL SetCharacterSlotCount(char *Name, BYTE btAddSlotCount);
	BOOL GetCharacterSlotCount(char *Name, BYTE *btSlotCount);
public:
	CQuery m_DBQuery;
};

#endif // !defined(AFX_ACCOUNTCHARDBSET_H__01C748D6_E836_4267_AF43_66BD9D34C7DC__INCLUDED_)
