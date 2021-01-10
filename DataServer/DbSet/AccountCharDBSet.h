#ifndef __ACCOUNTCHARSETDB_H__
#define __ACCOUNTCHARSETDB_H__
#pragma once

#include "..\include\Sprodef.h"

typedef struct AccountCharacterInfo
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
} *LPAccountCharacterInfo;


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
	BYTE SetSummonerCardInfo(char* Id, BYTE btCharacterCardInfo);

	BOOL SetCharacterSlotCount(char* Name, BYTE btAddSlotCount);
	BOOL GetCharacterSlotCount(char* Name, BYTE& btSlotCount);

	BOOL SetCharacterExtendedInvenCountAdd(char* Name, BYTE btAddExtendedInvenCount);
	BOOL GetCharacterExtendedInvenCount(char* Name, LPBYTE btAddExtendedInvenCount);
	BOOL SetCharacterExtendedInvenCountReplace(char* Name, BYTE btReplaceExtendedInvenCount);

	BOOL SetCharacterExtendedWarehouseCountAdd(char* Name, BYTE btAddExtendedWarehouseCount);
	BOOL SetCharacterExtendedWarehouseCountReplace(char* Name, BYTE btReplaceExtendedWarehouseCount);
	BOOL GetCharacterExtendedWarehouseCount(char* Name, LPBYTE btAddExtendedWarehouseCount);

public:
	CQuery m_DBQuery;
};

#endif