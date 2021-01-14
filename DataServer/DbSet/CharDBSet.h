#ifndef __CHARDBSET_H__
#define __CHARDBSET_H__
#pragma once

#include "..\Include\Sprodef.h"

typedef struct CharacterInfo_Struct
{
	int registry;
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	BYTE Class;
	int Level;
	int LevelUpPoint;
	int Experience;
	int NextExperience;
	int Money;
	short Strength;
	short Dexterity;
	short Vitality;
	short Energy;
	short Leadership;
	WORD ChatLitmitTime;
	float Life;
	float MaxLife;
	float Mana;
	float MaxMana;
	int PkCount;
	int PkLevel;
	int PkTime;
	BYTE dbInventory[MAX_DBINVENTORY];
	BYTE dbMagicList[MAX_DBMAGIC];
	BYTE dbQuest[MAX_DBQUEST];
	BYTE MapNumber;
	BYTE MapX;
	BYTE MapY;
	BYTE Dir;
	BYTE CtlCode;
	BYTE DbVersion;
	int FruitPoint;
	BYTE btExtendedInvenCount;
	BYTE btExtendedWarehouseCount;
	int iUserGuid;
} *LPCharacterInfo_Struct;

class CCharDBSet
{
public:
	CCharDBSet();
	virtual ~CCharDBSet();

	BOOL Connect();

	BOOL GetCharacter(char* name);
	int DeleteCharacter(char* AccoundID, char* CharacterID);
	int DeleteCharacter_DregInfo(char* CharacterID);
	int CreateCharacter(CString accountId, CString Name, BYTE Class);

	BOOL DefaultCharacterCreate(BYTE classskin);
	void SetSP_WZ_CreateCharacterGetVersion(int version);
	BOOL CheckSP_WZ_CreateCharacterGetVersion();
	BOOL DefaultCreateCharacterAllDelete();
	BOOL DefaultCreateCharacterInsert(LPCharacterInfo_Struct lpObj);

	BYTE CurCharNameSave(char* Name);

	BYTE SaveCharacter(char* Name, LPCharacterInfo_Struct lpObj);
	BOOL GetCharacter(char* szAccountID, char* Name, LPCharacterInfo_Struct lpObj);

	void SaveMacroInfo(char* szAccountID, char* Name, LPBYTE lpMacroInfo);
	BOOL LoadMacroInfo(char* szAccountID, char* Name, LPBYTE lpMacroInfo);

	BOOL SaveItem(char* Name, LPBYTE ItemBuf, char* AccountId);

	BOOL CharServerMove(char* Name);

	int ChangeName(char* AccountId, char* OldName, char* NewName);

	int GetCharacterID(char* chName, char* chUserID);
	DWORD GetCharacterClass(char* chName);

	void SaveUserSetting(char* szAccountID, LPBYTE lpSaveData);
	BOOL LoadUserSetting(char* szAccountID, LPBYTE lpSaveData);
	BOOL DeleteUserSetting(char* szAccountID);

	void SaveSnsInfo(char* szAccountID, char* Name, LPBYTE lpSnsInfo);
	BOOL LoadSnsInfo(char* szAccountID, char* Name, LPBYTE lpSnsInfo);
	BOOL DeleteSnsInfo(char* szAccountID, char* szName);

	BOOL SaveEventInvenItem(char* Name, LPBYTE ItemBuf, char* AccountId);
	BOOL LoadEventInvenItem(char* Name, char* ItemBuf, char* AccountId, int& DbVersion);

	void RuudToken_Update(char* AccountID, char* Name, DWORD dwRuudCnt);
	void RuudToken_LoadCount(char* AccountID, char* Name, int& nRuudCnt);

	BOOL CreateCharacterMoneyUpdate(CString Name);
	BOOL RestoreJumpingPkLevel(char* Name, BYTE btPkLevel);
	void RewardJumpingItem(char* Name, LPBYTE JumpingInventoryBuf);

public:
	int m_CreateCharacterVer;
	CQuery m_DBQuery;
};

#endif
