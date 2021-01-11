#include "stdafx.h"
#include "CharDBSet.h"
#include "..\MainFrm.h"

CCharDBSet::CCharDBSet()
{
}

CCharDBSet::~CCharDBSet()
{
}

BOOL CCharDBSet::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass) == FALSE)
	{
		MsgBox("Character DB Connect Fail");
		return FALSE;
	}

	if (CheckSP_WZ_CreateCharacterGetVersion() == FALSE)
	{
		MsgBox("Error : WZ_CreateChracter Stored Procedure Version : %d", m_CreateCharacterVer);
		return FALSE;
	}

	DefaultCreateCharacterAllDelete();
	DefaultCharacterCreate(DB_CLASS_TYPE_WIZARD);
	DefaultCharacterCreate(DB_CLASS_TYPE_KNIGHT);
	DefaultCharacterCreate(DB_CLASS_TYPE_ELF);
	DefaultCharacterCreate(DB_CLASS_TYPE_MAGUMSA);
	DefaultCharacterCreate(DB_CLASS_TYPE_DARKLORD);
	DefaultCharacterCreate(DB_CLASS_TYPE_SUMMONER);
	DefaultCharacterCreate(DB_CLASS_TYPE_MONK);
	DefaultCharacterCreate(DB_CLASS_TYPE_GROWLANCER);

	return TRUE;
}

BOOL CCharDBSet::GetCharacter(char* name)
{
	CString qSQL;
	char buffer[256];

	qSQL.Format("SELECT Name FROM Character WHERE Name='%s'", name);

	if (m_DBQuery.ExecGetStr(qSQL, buffer) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

int CCharDBSet::DeleteCharacter(char* AccoundID, char* CharacterID)
{
	if (strlen(CharacterID) < 1)
	{
		return 3;
	}

	CString qSql;
	qSql.Format("DELETE FROM Character WHERE AccountID='%s' AND Name='%s' ", AccoundID, CharacterID);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return 2;
	}

	m_DBQuery.Clear();
	return 1;
}

int CCharDBSet::DeleteCharacter_DregInfo(char* CharacterID)
{
	CString qSql;
	qSql.Format("EXEC WZ_Delete_C_DregInfo '%s'", CharacterID);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return 2;
	}

	m_DBQuery.Clear();
	return 1;
}

int CCharDBSet::CreateCharacter(CString accountId, CString Name, BYTE Class)
{
	CString qSql;
	int result = 3;

	qSql.Format("WZ_CreateCharacter '%s', '%s', '%d'", accountId, Name, Class);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return result;
	}

	if (m_DBQuery.Fetch() != SQL_NO_DATA)
	{
		result = m_DBQuery.GetInt(1);
	}

	m_DBQuery.Clear();

	if (gbIsJumpingServer != FALSE)
	{
		CreateCharacterMoneyUpdate(Name);
	}

	return result;
}

BOOL CCharDBSet::DefaultCharacterCreate(BYTE classskin)
{
	CharacterInfo_Struct tCharInfo;
	BYTE defclass;
	int n;

	defclass = classskin >> 4;

	if (defclass > MAX_CLASSTYPE - 1)
	{
		MsgBox("error-L3 : Class over value %s %d", __FILE__, __LINE__);
		defclass = CLASS_KNIGHT;
	}

	tCharInfo.Level = 1;
	tCharInfo.LevelUpPoint = 0;
	tCharInfo.Leadership = DCInfo.DefClass[defclass].Leadership;
	tCharInfo.Class = classskin;
	tCharInfo.Experience = DCInfo.DefClass[defclass].Experience;
	tCharInfo.Strength = DCInfo.DefClass[defclass].Strength;
	tCharInfo.Dexterity = DCInfo.DefClass[defclass].Dexterity;
	tCharInfo.Vitality = DCInfo.DefClass[defclass].Vitality;
	tCharInfo.Energy = DCInfo.DefClass[defclass].Energy;
	tCharInfo.Money = 0;
	tCharInfo.Life = DCInfo.DefClass[defclass].Life;
	tCharInfo.MaxLife = DCInfo.DefClass[defclass].MaxLife;
	tCharInfo.Mana = DCInfo.DefClass[defclass].Mana;
	tCharInfo.MaxMana = DCInfo.DefClass[defclass].MaxMana;
	tCharInfo.MapNumber = 0;
	tCharInfo.MapX = 182;
	tCharInfo.MapY = 128;
	tCharInfo.PkCount = 0;
	tCharInfo.PkLevel = PK_LEVEL_DEFAULT;
	tCharInfo.PkTime = 0;

	for (n = 0; n < MAX_INVENTORY; n++)
	{
		memset(&tCharInfo.dbInventory[MAX_ITEMDBBYTE * n], 0xFF, MAX_ITEMDBBYTE);
	}

	for (n = 0; n < MAX_MAGIC; n++)
	{
		tCharInfo.dbMagicList[3 * n] = 0xFF;
		tCharInfo.dbMagicList[3 * n + 1] = 0;
		tCharInfo.dbMagicList[3 * n + 2] = 0;
	}

	for (n = 0; n < MAX_DBQUEST; n++)
	{
		tCharInfo.dbQuest[n] = 0xFF;
	}

	if (defclass == CLASS_WIZARD)
	{
		tCharInfo.dbMagicList[0] = AT_SKILL_ENERGYBALL;
	}

	if (defclass == CLASS_DARKLORD)
	{
		tCharInfo.dbMagicList[0] = AT_SKILL_SPEAR;
	}

	ItemByteConvert16(tCharInfo.dbInventory, DCInfo.DefClass[defclass].Equipment, MAX_EQUIPMENT + 3);
	DefaultCreateCharacterInsert(&tCharInfo);
	return TRUE;
}

void CCharDBSet::SetSP_WZ_CreateCharacterGetVersion(int version)
{
	m_CreateCharacterVer = version;
}

BOOL CCharDBSet::CheckSP_WZ_CreateCharacterGetVersion()
{
	CString qSql;
	int version = 0;

	qSql.Format("exec WZ_CreateCharacter_GetVersion");

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		return FALSE;
	}

	if (m_DBQuery.Fetch() != SQL_NO_DATA)
	{
		version = m_DBQuery.GetInt(1);

		if (version == m_CreateCharacterVer)
		{
			m_DBQuery.Clear();
			return TRUE;
		}
	}

	m_DBQuery.Clear();
	return FALSE;
}

BOOL CCharDBSet::DefaultCreateCharacterAllDelete()
{
	if (m_DBQuery.Exec("DELETE FROM DefaultClassType") == FALSE)
	{
		LogAddTD("error-L3 : DELETE FROM DefaultClassType %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	return TRUE;
}

BOOL CCharDBSet::DefaultCreateCharacterInsert(LPCharacterInfo_Struct lpObj)
{
	CString qSql;
	qSql.Format("INSERT INTO DefaultClassType (Level, Class, Strength, Dexterity, Vitality, Energy, Life, MaxLife, Mana, MaxMana, MapNumber, MapPosX, MapPosY, DbVersion, LevelUpPoint,Leadership)  VALUES (%d,%d,%d,%d,%d, %d, %f,%f,%f,%f, %d,%d,%d, %d, %d, %d)",
		lpObj->Level, lpObj->Class, lpObj->Strength, lpObj->Dexterity, lpObj->Vitality, lpObj->Energy, lpObj->Life, lpObj->MaxLife, lpObj->Mana, lpObj->MaxMana, lpObj->MapNumber, lpObj->MapX, lpObj->MapY, 3, lpObj->LevelUpPoint, lpObj->Leadership);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		return FALSE;
	}

	qSql.Format("WZ_SetDefaultCharacter %d, ?", lpObj->Class);
	m_DBQuery.WriteBlob(qSql, lpObj->dbInventory, MAX_DBINVENTORY);

	qSql.Format("UPDATE DefaultClassType SET MagicList=? where Class=%d", lpObj->Class);
	m_DBQuery.WriteBlob(qSql, lpObj->dbMagicList, MAX_DBMAGIC);

	qSql.Format("UPDATE DefaultClassType SET Quest=? where Class=%d", lpObj->Class);
	m_DBQuery.WriteBlob(qSql, lpObj->dbQuest, MAX_DBQUEST);

	return TRUE;
}

BYTE CCharDBSet::CurCharNameSave(char* Name)
{
	CString qSql;
	qSql.Format("INSERT INTO T_CurCharName (Name) VALUES('%s')", Name);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		return 0x00;
	}

	return 0x01;
}

BYTE CCharDBSet::SaveCharacter(char* Name, LPCharacterInfo_Struct lpObj)
{
	BYTE result = 1;
	CString qSql;

	char chBuffer[512] = "UPDATE Character SET cLevel=%d, Class=%d, LevelUpPoint=%d, Experience=%d, Strength=%d, Dexterity=%d, Vitality=%d, Energy=%d, Money=%d, Life=%f, MaxLife=%f, Mana=%f, MaxMana=%f, MapNumber=%d, MapPosX=%d, MapPosY=%d, MapDir=%d, PkCount=%d, ";
	strcat(chBuffer, " PkLevel=%d, ");
	strcat(chBuffer, " PkTime=%d,  ");
	strcat(chBuffer, " DbVersion=3, ");
	strcat(chBuffer, " Leadership=%d, ");
	strcat(chBuffer, " ChatLimitTime=%d, ");
	strcat(chBuffer, " FruitPoint=%d, ");
	strcat(chBuffer, " LDate = getdate() ");
	strcat(chBuffer, " where Name = '%s' ");

	qSql.Format(chBuffer, lpObj->Level, lpObj->Class, lpObj->LevelUpPoint, lpObj->Experience, lpObj->Strength, lpObj->Dexterity, lpObj->Vitality, lpObj->Energy, lpObj->Money, lpObj->Life, lpObj->MaxLife, lpObj->Mana, lpObj->MaxMana, lpObj->MapNumber, lpObj->MapX, lpObj->MapY, lpObj->Dir, lpObj->PkCount, lpObj->PkLevel, lpObj->PkTime, lpObj->Leadership, lpObj->ChatLitmitTime, lpObj->FruitPoint, Name);
	
	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		return 0;
	}

	qSql.Format("WZ_SetSaveItem '%s', '%s', ?", lpObj->AccountID, Name);
	m_DBQuery.WriteBlob(qSql, lpObj->dbInventory, MAX_DBINVENTORY);
	
	qSql.Format("UPDATE Character SET MagicList=? where Name='%s'", Name);
	m_DBQuery.WriteBlob(qSql, lpObj->dbMagicList, MAX_DBMAGIC);

	qSql.Format("UPDATE Character SET Quest=? where Name='%s'", Name);
	m_DBQuery.WriteBlob(qSql, lpObj->dbQuest, MAX_DBQUEST);

	return 1;
}

BOOL CCharDBSet::GetCharacter(char* szAccountID, char* Name, LPCharacterInfo_Struct lpObj)
{
	CString qSql;

	char chBuffer[512] = "SELECT AccountID, cLevel, Class, LevelUpPoint, Experience, Strength, Dexterity, Vitality, Energy, Money, Life, MaxLife, Mana, MaxMana, MapNumber, MapPosX, MapPosY, MapDir, PkCount, PkLevel, PkTime, CtlCode,";
	strcat(chBuffer, " Leadership, ");
	strcat(chBuffer, " ChatLimitTime, ");
	strcat(chBuffer, " FruitPoint, ");
	strcat(chBuffer, " ExtendedInvenCount, ");
	strcat(chBuffer, " DbVersion ");
	strcat(chBuffer, " FROM Character where Name = '%s' ");

	qSql.Format(chBuffer, Name);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	if (m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	m_DBQuery.GetStr("AccountID", lpObj->AccountID);

	if (strcmp(lpObj->AccountID, szAccountID) != 0)
	{
		LogAddC(LOGC_RED, "error-L1 :Ä³¸¯ÅÍÀÇ °èÁ¤°ú ¿äÃ»ÇÑ °èÁ¤ÀÌ ¸ÂÁö¾Ê´Ù.%s %s", lpObj->AccountID, szAccountID);
		m_DBQuery.Clear();
		return FALSE;
	}

	lpObj->Level = m_DBQuery.GetInt("cLevel");
	lpObj->Class = m_DBQuery.GetInt("Class");
	lpObj->LevelUpPoint = m_DBQuery.GetInt("LevelUpPoint");
	lpObj->Experience = m_DBQuery.GetInt("Experience");
	lpObj->Strength = m_DBQuery.GetInt("Strength");
	lpObj->Dexterity = m_DBQuery.GetInt("Dexterity");
	lpObj->Vitality = m_DBQuery.GetInt("Vitality");
	lpObj->Energy = m_DBQuery.GetInt("Energy");
	lpObj->Money = m_DBQuery.GetInt("Money");
	lpObj->Life = m_DBQuery.GetFloat("Life");
	lpObj->MaxLife = m_DBQuery.GetFloat("MaxLife");
	lpObj->Mana = m_DBQuery.GetFloat("Mana");
	lpObj->MaxMana = m_DBQuery.GetFloat("MaxMana");
	lpObj->MapNumber = m_DBQuery.GetInt("MapNumber");
	lpObj->MapX = m_DBQuery.GetInt("MapPosX");
	lpObj->MapY = m_DBQuery.GetInt("MapPosY");
	lpObj->Dir = m_DBQuery.GetInt("MapDir");
	lpObj->PkCount = m_DBQuery.GetInt("PkCount");
	lpObj->PkLevel = m_DBQuery.GetInt("PkLevel");
	lpObj->PkTime = m_DBQuery.GetInt("PkTime");

	int ctlcode = m_DBQuery.GetInt("CtlCode");

	if (ctlcode < 0)
	{
		ctlcode = 0;
	}

	lpObj->CtlCode = ctlcode;
	
	int dbversion = m_DBQuery.GetInt("DbVersion");
	
	if (dbversion < 0)
	{
		dbversion = 0;
	}

	lpObj->DbVersion = dbversion;
	
	int leadership = m_DBQuery.GetInt("Leadership");

	if (leadership < 0)
	{
		leadership = 0;
	}

	int ChatLitmitTime = m_DBQuery.GetInt("ChatLimitTime");
	
	if (ChatLitmitTime < 0)
	{
		ChatLitmitTime = 0;
	}

	lpObj->Leadership = leadership;
	lpObj->ChatLitmitTime = ChatLitmitTime;
	
	int iFruitPoint = m_DBQuery.GetInt("FruitPoint");

	if (iFruitPoint < 0)
	{
		lpObj->FruitPoint = 0;
		LogAddC(LOGC_RED, "[Fruit System] [%s][%s] Fruit ÄÃ·³ %d -> 0 À¸·Î ¼öÁ¤ ", lpObj->AccountID, Name, iFruitPoint);
	}

	else
	{
		lpObj->FruitPoint = iFruitPoint;
	}

	lpObj->btExtendedInvenCount = m_DBQuery.GetInt("ExtendedInvenCount");
	m_DBQuery.Clear();

	qSql.Format("SELECT ExtendedWarehouseCount from AccountCharacter where Id='%s'", szAccountID);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	if (m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	lpObj->btExtendedWarehouseCount = m_DBQuery.GetInt("ExtendedWarehouseCount");
	m_DBQuery.Clear();

	qSql.Format("WZ_GetLoadInventory '%s', '%s'", szAccountID, Name);
	int nRet = m_DBQuery.ReadBlob(qSql, lpObj->dbInventory);

	if (nRet == 0)
	{
		for (int i = 0; i < MAX_DBINVENTORY; i++)
		{
			lpObj->dbInventory[i] = 0xFF;
		}
	}

	else if (nRet == -1)
	{
		return FALSE;
	}

	else if (nRet == 760)
	{
		for (int i = 760; i < MAX_DBINVENTORY; i++)
		{
			lpObj->dbInventory[i] = 0xFF;
		}
	}

	else if (nRet > 0 && nRet < MAX_DBINVENTORY)
	{
		for (int i = nRet; i < MAX_DBINVENTORY; i++)
		{
			lpObj->dbInventory[i] = 0xFF;
		}
	}

	qSql.Format("SELECT MagicList from Character where Name='%s'", Name);
	nRet = m_DBQuery.ReadBlob(qSql, lpObj->dbMagicList);

	if (nRet == 0)
	{
		for (int n = 0; n < MAX_MAGIC; n++)
		{
			lpObj->dbMagicList[3 * n] = 0xFF;
			lpObj->dbMagicList[3 * n + 1] = 0;
			lpObj->dbMagicList[3 * n + 2] = 0;
		}
	}

	else if (nRet == -1)
	{
		return FALSE;
	}

	else if (nRet > 0 && nRet < MAX_MAGIC)
	{
		for (int i = nRet; i < MAX_MAGIC; i += 3)
		{
			lpObj->dbMagicList[i] = 0xFF;
			lpObj->dbMagicList[i + 1] = 0;
			lpObj->dbMagicList[i + 2] = 0;
		}
	}

	qSql.Format("SELECT Quest from Character where Name='%s'", Name);
	nRet = m_DBQuery.ReadBlob(qSql, lpObj->dbQuest);

	if (nRet == 0)
	{
		for (int i = 0; i < MAX_DBQUEST; i++)
		{
			lpObj->dbQuest[i] = 0xFF;
		}
	}

	else if (nRet == -1)
	{
		return FALSE;
	}

	return TRUE;
}

void CCharDBSet::SaveMacroInfo(char* szAccountID, char* Name, LPBYTE lpMacroInfo)
{
	CString qSql;

	qSql.Format("EXEC WZ_MACROINFO_SAVE '%s', '%s', ?", szAccountID, Name);
	m_DBQuery.WriteBlob(qSql, lpMacroInfo, 511);
}

BOOL CCharDBSet::LoadMacroInfo(char* szAccountID, char* Name, LPBYTE lpMacroInfo)
{
	CString qSql;

	qSql.Format("EXEC WZ_MACROINFO_LOAD '%s', '%s'", szAccountID, Name);
	int nRet = m_DBQuery.ReadBlob(qSql, lpMacroInfo);

	if (nRet == 0)
	{
		for (int n = 0; n < 511; n++)
		{
			lpMacroInfo[n] = 0xFF;
		}
	}

	else if (nRet == -1)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharDBSet::SaveItem(char *Name, LPBYTE ItemBuf, char *AccountId)
{
	CString qSql;
	qSql.Format("UPDATE Character SET DbVersion=3 where Name = '%s'", Name);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		return FALSE;
	}

	qSql.Format("WZ_SetSaveItem '%s', '%s', ?", AccountId, Name);
	m_DBQuery.WriteBlob(qSql, ItemBuf, MAX_DBINVENTORY);

	return TRUE;
}

BOOL CCharDBSet::CharServerMove(char* Name)
{
	CString qSql;
	qSql.Format("SP_CHARACTER_TRANSFER '%s'", Name);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		LogAddC(LOGC_BLUE, "SP_CHARACTER_TRANSFER error return #1");
		return TRUE;
	}

	if (m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		LogAddC(LOGC_BLUE, "SP_CHARACTER_TRANSFER error return #2");
		m_DBQuery.Clear();
		return TRUE;
	}

	int error = m_DBQuery.GetInt(1);
	m_DBQuery.Clear();

	LogAddC(LOGC_BLUE, "SP_CHARACTER_TRANSFER result %d", error);

	if (error != 0)
	{
		return error;
	}

	return FALSE;
}

int CCharDBSet::ChangeName(char* AccountId, char* OldName, char* NewName)
{
	int result = 0;
	CString qSql;

	qSql.Format("WZ_ChangeCharacterName '%s', '%s', '%s'", AccountId, OldName, NewName);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return 5;
	}

	if (m_DBQuery.Fetch() != SQL_NO_DATA)
	{
		result = m_DBQuery.GetInt(1);
	}

	m_DBQuery.Clear();
	return result;
}

int CCharDBSet::GetCharacterID(char* chName, char* chUserID)
{
	CString qSql;
	qSql.Format("SELECT AccountID FROM Character WHERE Name = '%s'", chName);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return 1;
	}

	if (m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return 2;
	}

	char chBuffer[MAX_IDSTRING + 1];
	m_DBQuery.GetStr(1, chBuffer);
	memcpy(chUserID, chBuffer, sizeof(chBuffer));

	m_DBQuery.Clear();
	return 0;
}

DWORD CCharDBSet::GetCharacterClass(char* chName)
{
	CString qSql;
	DWORD dwReturn = 0;

	qSql.Format("SELECT Class FROM Character WHERE Name = '%s'", chName);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return -1;
	}

	if (m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return -2;
	}

	dwReturn = m_DBQuery.GetInt(1);

	m_DBQuery.Clear();
	return dwReturn;
}

void CCharDBSet::SaveUserSetting(char* szAccountID, LPBYTE lpSaveData)
{
	CString qSql;
	qSql.Format("EXEC WZ_UserSettingInfo_Save '%s', ?", szAccountID);

	m_DBQuery.WriteBlob(qSql, lpSaveData, 255);
}

BOOL CCharDBSet::LoadUserSetting(char* szAccountID, LPBYTE lpSaveData)
{
	CString qSql;
	qSql.Format("EXEC WZ_UserSettingInfo_Load '%s'", szAccountID);

	int nRet = m_DBQuery.ReadBlob(qSql, lpSaveData);

	if (nRet == 0)
	{
		for (int i = 0; i < 255; i++)
		{
			lpSaveData[i] = 0xFF;
		}

		return TRUE;
	}

	if (nRet == -1)
	{
		return 2;
	}

	return FALSE;
}

BOOL CCharDBSet::DeleteUserSetting(char* szAccountID)
{
	CString qSql;
	qSql.Format("exec WZ_DeleteUserSettingInfo '%s', '%s'", szAccountID);

	if (m_DBQuery.Exec(qSql) == TRUE)
	{
		m_DBQuery.Clear();
		return TRUE;
	}

	m_DBQuery.Clear();
	return FALSE;
}

void CCharDBSet::SaveSnsInfo(char* szAccountID, char* Name, LPBYTE lpSnsInfo)
{
	CString qSql;
	qSql.Format("EXEC WZ_SnsInfo_Save '%s', '%s', ?", szAccountID, Name);

	m_DBQuery.WriteBlob(qSql, lpSnsInfo, 255);
}

BOOL CCharDBSet::LoadSnsInfo(char* szAccountID, char* Name, LPBYTE lpSnsInfo)
{
	CString qSql;
	qSql.Format("EXEC WZ_SnsInfo_Load '%s', '%s'", szAccountID, Name);

	int nRet = m_DBQuery.ReadBlob(qSql, lpSnsInfo);

	if (nRet == 0)
	{
		for (int i = 0; i < 255; i++)
		{
			lpSnsInfo[i] = 0xFF;
		}

		return TRUE;
	}
		
	if (nRet == -1)
	{
		return 2;
	}

	return FALSE;
}

BOOL CCharDBSet::DeleteSnsInfo(char* szAccountID, char* szName)
{
	CString qSql;
	qSql.Format("exec WZ_DeleteSnsInfo '%s', '%s'", szAccountID, szName);

	if (m_DBQuery.Exec(qSql) == TRUE)
	{
		m_DBQuery.Clear();
		return TRUE;
	}

	m_DBQuery.Clear();
	return FALSE;
}

BOOL CCharDBSet::SaveEventInvenItem(char* Name, LPBYTE ItemBuf, char* AccountId)
{
	CString qSql;
	qSql.Format("WZ_SetSaveEventInventory '%s', '%s', ?", AccountId, Name);
	m_DBQuery.WriteBlob(qSql, ItemBuf, MAX_DBEVENTINVENTORY);

	m_DBQuery.Clear();
	return TRUE;
}

BOOL CCharDBSet::LoadEventInvenItem(char* Name, char* ItemBuf, char* AccountId, int& DbVersion)
{
	CString qSql;
	qSql.Format("WZ_GetLoadEventInventory '%s', '%s'", AccountId, Name);

	int nRet = m_DBQuery.ReadBlob(qSql, ItemBuf);

	if (nRet == -1)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	qSql.Format("SELECT DbVersion from T_Event_Inventory where AccountID='%s'", AccountId);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	if (m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	DbVersion = m_DBQuery.GetInt(1);

	m_DBQuery.Clear();
	return TRUE;
}

void CCharDBSet::RuudToken_Update(char* AccountID, char* Name, DWORD dwRuudCnt)
{
	char szId[MAX_IDSTRING + 1];
	szId[MAX_IDSTRING] = '\0';
	memcpy(szId, AccountID, MAX_IDSTRING);

	char szCahrName[MAX_IDSTRING + 1];
	szCahrName[MAX_IDSTRING] = '\0';
	memcpy(szCahrName, Name, MAX_IDSTRING);

	if (strlen(szCahrName) == 0 || strlen(szCahrName) > MAX_IDSTRING || strlen(szId) == 0 || strlen(szId) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szCahrName, __FILE__, __LINE__);
		return;
	}

	CString qSql;
	qSql.Format("WZ_RuudTokenUpdate '%s','%s', %d", szId, szCahrName, dwRuudCnt);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		LogAddTD("Error-L1 [CAccountCharDBSet][RuudToken_Update] ACC:%s NAME:%s, Ruud:%d ", szId, szCahrName, dwRuudCnt);
		m_DBQuery.Clear();
		return;
	}

	SQLRETURN sqlReturn = m_DBQuery.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		LogAddTD("Error-L2 [CAccountCharDBSet] [RuudToken_Update] %d, %s , %d", sqlReturn, __FILE__, __LINE__);
		m_DBQuery.Clear();
		return;
	}

	int nRetrun = m_DBQuery.GetInt(1);
	
	if (nRetrun != 0)
	{
		LogAddTD("RuudToken_Update return %d ACC:%s , Name:%s, ruud :%d ", nRetrun, szId, szCahrName, dwRuudCnt);
		LogAddTD("RuudToken_Update -1 == UpdateFail, -2 == InsertFail");
	}

	m_DBQuery.Clear();
}

void CCharDBSet::RuudToken_LoadCount(char* AccountID, char* Name, int& nRuudCnt)
{
	char szId[MAX_IDSTRING + 1];
	szId[MAX_IDSTRING] = '\0';
	memcpy(szId, AccountID, MAX_IDSTRING);

	char szCahrName[MAX_IDSTRING + 1];
	szCahrName[MAX_IDSTRING] = '\0';
	memcpy(szCahrName, Name, MAX_IDSTRING);

	if (strlen(szCahrName) == 0 || strlen(szCahrName) > MAX_IDSTRING || strlen(szId) == 0 || strlen(szId) > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ؎֥ ߡׯ %s %d", szCahrName, __FILE__, __LINE__);
		return;
	}

	CString q;
	nRuudCnt = 0;

	q.Format("WZ_RuudTokenLoad '%s','%s'", szId, szCahrName);

	if (m_DBQuery.Exec(q) == FALSE)
	{
		LogAddTD("Error-L3 [CAccountCharDBSet][WZ_RuudTokenLoad][A1] %s %s", szId, szCahrName);
		return;
	}
		
	SQLRETURN sqlReturn = m_DBQuery.Fetch();

	if (sqlReturn == SQL_NO_DATA || sqlReturn == SQL_NULL_DATA)
	{
		m_DBQuery.Clear();
		LogAddTD("Error-L3 [CAccountCharDBSet][WZ_RuudTokenLoad][A2] ACC:%s,NAME:%s sqlReturn:%d File %s Line %d ", szId, szCahrName, sqlReturn, __FILE__, __LINE__);
		return;
	}

	nRuudCnt = m_DBQuery.GetInt(1);
	LogAddTD("[RuudToken_LoadCount]Acc:%s,Name:%s,Ruud:%d", szId, szCahrName, nRuudCnt);

	if (nRuudCnt == -1)
	{
		nRuudCnt = 0;
	}

	m_DBQuery.Clear();
}

BOOL CCharDBSet::CreateCharacterMoneyUpdate(CString Name)
{
	CString qSql;
	qSql.Format("UPDATE Character SET Money = 1000000000 WHERE Name = '%s'",Name);
	
	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	m_DBQuery.Clear();
	return TRUE;
}

BOOL CCharDBSet::RestoreJumpingPkLevel(char* Name, BYTE btPkLevel)
{
	CString qSql;
	qSql.Format("UPDATE Character SET PkLevel = %d WHERE Name = '%s'", btPkLevel, Name);

	if (m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	m_DBQuery.Clear();
	return TRUE;
}

void CCharDBSet::RewardJumpingItem(char* Name, LPBYTE JumpingInventoryBuf)
{
	CString qSql;
	qSql.Format("UPDATE Character SET Inventory=? where Name='%s'", Name);

	m_DBQuery.WriteBlob(qSql, JumpingInventoryBuf, MAX_DBINVENTORY - MAX_ITEMDBBYTE);
	m_DBQuery.Clear();
}

