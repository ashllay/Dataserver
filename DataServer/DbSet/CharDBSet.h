// CharDBSet.h: interface for the CCharDBSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARDBSET_H__BED5C4C4_EA0B_4126_A05F_9584C5F0E889__INCLUDED_)
#define AFX_CHARDBSET_H__BED5C4C4_EA0B_4126_A05F_9584C5F0E889__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

typedef struct
{
	/*int registry;
	char AccountID[11];
	char Name[11];
	char Class;
	int Level;
	int LevelUpPoint;
	int Experience;
	int NextExperience;
	int Money;
	__int16 Strength;
	__int16 Dexterity;
	__int16 Vitality;
	__int16 Energy;
	__int16 Leadership;
	unsigned __int16 ChatLitmitTime;
	float Life;
	float MaxLife;
	float Mana;
	float MaxMana;
	int PkCount;
	int PkLevel;
	int PkTime;
	BYTE dbInventory[3792];
	BYTE dbMagicList[450];
	BYTE dbQuest[50];
	char MapNumber;
	char MapX;
	char MapY;
	char Dir;
	char CtlCode;
	char DbVersion;
	int FruitPoint;
	char btExtendedInvenCount;
	char btExtendedWarehouseCount;
	int iUserGuid;*/
	int registry;
	char AccountID[MAX_IDSTRING+1];
	char Name[MAX_IDSTRING+1];
	BYTE Class;
	int Level;
	int LevelUpPoint;
	int Experience;
	int NextExperience;
	int Money;
	WORD Strength;
	WORD Dexterity;
	WORD Vitality;
	WORD Energy;
	WORD Leadership;
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
}CharacterInfo_Struct, *LPCharacterInfo_Struct;

class CCharDBSet  
{
public:
	CCharDBSet();
	virtual ~CCharDBSet();

	BOOL Connect();//
	BOOL GetCharacter(char *name);//
	int DeleteCharacter(char* AccoundID, char* CharacterID);//
	int DeleteCharacter_DregInfo(char* CharacterID);//
	int CreateCharacter(CString accountId, CString Name, BYTE Class);//
	__int64 DefaultCharacterCreate(BYTE classskin);
	void SetSP_WZ_CreateCharacterGetVersion(int version);//
	BOOL CheckSP_WZ_CreateCharacterGetVersion();//
	BOOL DefaultCreateCharacterAllDelete();//
	BOOL DefaultCreateCharacterInsert(LPCharacterInfo_Struct lpObj);//
	BYTE CurCharNameSave(char *Name);//
	BYTE SaveCharacter(char *Name, LPCharacterInfo_Struct lpObj);//
	BOOL GetCharacter(char *szAccountID, char *Name, LPCharacterInfo_Struct lpObj);//
	void SaveMacroInfo(char *szAccountID, char* Name, BYTE* lpMacroInfo);//
	BOOL LoadMacroInfo(char *szAccountID, char* Name, BYTE* lpMacroInfo);//
	BOOL SaveItem(char *Name, BYTE* ItemBuf, char *AccountId);//
	int CharServerMove(char *Name);//
	int ChangeName(char* AccountId, char* OldName, char* NewName);//
	int GetCharacterID(char* chName, char* chUserID);//
	DWORD GetCharacterClass(char *chName);//
	void SaveUserSetting(char *szAccountID, BYTE *lpSaveData);//
	int LoadUserSetting(char *szAccountID, BYTE *lpSaveData);//
	BOOL DeleteUserSetting(char *szAccountID);
	void SaveSnsInfo(char *szAccountID, char *Name, BYTE *lpSnsInfo);
	BOOL LoadSnsInfo(char *szAccountID, char *Name, BYTE *lpSnsInfo);
	BOOL DeleteSnsInfo(char *szAccountID, char *szName);
	__int64 SaveEventInvenItem(char *Name, BYTE *ItemBuf, char *AccountId);
	int LoadEventInvenItem(char *Name, BYTE *ItemBuf, char *AccountId, int *DbVersion);
	void RuudToken_Update(char *AccountID, char *Name, unsigned int dwRuudCnt);
	void RuudToken_LoadCount(char *AccountID, char *Name, int *nRuudCnt);
	int CreateCharacterMoneyUpdate(CString Name);
	BOOL RestoreJumpingPkLevel(char *Name, BYTE btPkLevel);
	void RewardJumpingItem(char* Name, BYTE* JumpingInventoryBuf);
public:
	int m_CreateCharacterVer;
	CQuery m_DBQuery;
};

#endif // !defined(AFX_CHARDBSET_H__BED5C4C4_EA0B_4126_A05F_9584C5F0E889__INCLUDED_)
