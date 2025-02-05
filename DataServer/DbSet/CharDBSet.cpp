// CharDBSet.cpp: implementation of the CCharDBSet class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CharDBSet.h"
#include "..\MainFrm.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCharDBSet::CCharDBSet()
{

}

CCharDBSet::~CCharDBSet()
{

}

BOOL CCharDBSet::Connect()
{
	if( m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass) == FALSE )
	{
		MsgBox("Character DB Connect Fail");
		return FALSE;
	}

	if(this->CheckSP_WZ_CreateCharacterGetVersion() == FALSE)
	{
		MsgBox("Error : WZ_CreateChracter Stored Procedure Version : %d", this->m_CreateCharacterVer);
		return FALSE;
	}

	this->DefaultCreateCharacterAllDelete();

	this->DefaultCharacterCreate(DB_CLASS_TYPE_WIZARD);
	this->DefaultCharacterCreate(DB_CLASS_TYPE_KNIGHT);
	this->DefaultCharacterCreate(DB_CLASS_TYPE_ELF);
	this->DefaultCharacterCreate(DB_CLASS_TYPE_MAGUMSA);
	this->DefaultCharacterCreate(DB_CLASS_TYPE_DARKLORD);
	this->DefaultCharacterCreate(DB_CLASS_TYPE_SUMMONER);
	this->DefaultCharacterCreate(DB_CLASS_TYPE_MONK);
	this->DefaultCharacterCreate(DB_CLASS_TYPE_LANCER);
	return TRUE;
}

BOOL CCharDBSet::GetCharacter(char *name)
{
	CString qSQL;
	char buffer[256];

	qSQL.Format("SELECT Name FROM Character WHERE Name='%s'", name);

	if(m_DBQuery.ExecGetStr(qSQL, buffer) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

int CCharDBSet::DeleteCharacter(char* AccoundID, char* CharacterID)
{
	if( strlen(CharacterID) < 1)
	{
		return 3;
	}

	CString qSql;

	qSql.Format("DELETE FROM Character WHERE AccountID='%s' AND Name='%s' ", AccoundID, CharacterID);

	if(m_DBQuery.Exec(qSql) == FALSE)
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

	if(m_DBQuery.Exec(qSql) == FALSE)
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

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		if (gbIsJumpingServer)
		{
			this->CreateCharacterMoneyUpdate(Name);
		}
		return result;
	}

	if(m_DBQuery.Fetch() != SQL_NO_DATA)
	{
		result = m_DBQuery.GetInt(1);
	}

	m_DBQuery.Clear();

	return result;
}

__int64 CCharDBSet::DefaultCharacterCreate(BYTE classskin)
{
	CharacterInfo_Struct tCharInfo;
	BYTE defclass;
	int n;

	defclass = classskin >> 4;

	if(defclass > MAX_CLASSTYPE-1)
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

#ifdef PERSONAL_SHOP_20040113
	for (n = 0; n < MAX_INVENTORY_EXTEND; n++)
	{
		memset(&tCharInfo.dbInventory[MAX_ITEMDBBYTE * n], 0xFF, MAX_ITEMDBBYTE);
	}
#else
	for (n = 0; n < MAX_INVENTORY; n++)
	{
		memset(&tCharInfo.dbInventory[MAX_ITEMDBBYTE * n], 0xFF, MAX_ITEMDBBYTE);
	}
#endif

	for ( n = 0; n < MAX_MAGIC; n++ )
	{
		tCharInfo.dbMagicList[3 * n] = 0xFF;
		tCharInfo.dbMagicList[3 * n + 1] = 0;
		tCharInfo.dbMagicList[3 * n + 2] = 0;
	}
	
	for ( n = 0; n < MAX_DBQUEST; n++ )
	{
		tCharInfo.dbQuest[n] = 0xFF;
	}

	if(defclass == CLASS_WIZARD)
	{
		tCharInfo.dbMagicList[0] = AT_SKILL_ENERGYBALL;
	}

	if(defclass == CLASS_DARKLORD)
	{
		tCharInfo.dbMagicList[0] = AT_SKILL_SPEAR;
	}

	ItemByteConvert16(tCharInfo.dbInventory, DCInfo.DefClass[defclass].Equipment, MAX_EQUIPMENT+2);

	this->DefaultCreateCharacterInsert(&tCharInfo);
	return TRUE;
}

void CCharDBSet::SetSP_WZ_CreateCharacterGetVersion(int version)
{
	this->m_CreateCharacterVer = version;
}

BOOL CCharDBSet::CheckSP_WZ_CreateCharacterGetVersion()
{
	CString qSql;
	int version = 0;

	qSql.Format("exec WZ_CreateCharacter_GetVersion");

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		return FALSE;
	}

	if(m_DBQuery.Fetch() != SQL_NO_DATA)
	{
		version = m_DBQuery.GetInt(1);

		if(version == this->m_CreateCharacterVer)
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
	if(m_DBQuery.Exec("DELETE FROM DefaultClassType") == FALSE)
	{
		LogAddTD("error-L3 : DELETE FROM DefaultClassType %s %d", __FILE__, __LINE__);
		return FALSE;
	}
	return TRUE;
}

BOOL CCharDBSet::DefaultCreateCharacterInsert(LPCharacterInfo_Struct lpObj)
{
	CString qSql;
	//			"INSERT INTO DefaultClassType (Level, Class, Strength, Dexterity, Vitality, Energy, Life, MaxLife, Mana, MaxMana, MapNumber, MapPosX, MapPosY, DbVersion, LevelUpPoint,Leadership)  VALUES (%d,%d,%d,%d,%d, %d, %f,%f,%f,%f, %d,%d,%d, %d, %d, %d)",
	qSql.Format("INSERT INTO DefaultClassType (Level, Class, Strength, Dexterity, Vitality, Energy, Life, MaxLife, Mana, MaxMana, MapNumber, MapPosX, MapPosY, DbVersion, LevelUpPoint,Leadership)  VALUES (%d,%d,%d,%d,%d, %d, %f,%f,%f,%f, %d,%d,%d, %d, %d, %d)",
		lpObj->Level, lpObj->Class, lpObj->Strength, lpObj->Dexterity, lpObj->Vitality, lpObj->Energy, lpObj->Life, lpObj->MaxLife, lpObj->Mana, lpObj->MaxMana, lpObj->MapNumber, lpObj->MapX, lpObj->MapY, 3, lpObj->LevelUpPoint, lpObj->Leadership);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		return FALSE;
	}

	//qSql.Format("UPDATE DefaultClassType SET Inventory=? where Class=%d", lpObj->Class);
	qSql.Format("WZ_SetDefaultCharacter %d, ?",lpObj->Class);
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

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		return 0x00;
	}

	return 0x01;
}

BYTE CCharDBSet::SaveCharacter(char* Name, LPCharacterInfo_Struct lpObj)
{
	int sresult;
	char chBuffer[512];
	char result;
	CString qSql;

	result = 1;
	strcpy(chBuffer, "UPDATE Character SET cLevel=%d, Class=%d, LevelUpPoint=%d, Experience=%d, Strength=%d, Dexterity=%d, Vitality=%d, En"
		"ergy=%d, Money=%d, Life=%f, MaxLife=%f, Mana=%f, MaxMana=%f, MapNumber=%d, MapPosX=%d, MapPosY=%d, MapDir=%d, PkCount=%d, ");
	memset(&chBuffer[239], 0, 0x111u);
	strcat(chBuffer, " PkLevel=%d, ");
	strcat(chBuffer, " PkTime=%d,  ");
	strcat(chBuffer, " DbVersion=3, ");
	strcat(chBuffer, " Leadership=%d, ");
	strcat(chBuffer, " ChatLimitTime=%d, ");
	strcat(chBuffer, " FruitPoint=%d, ");
	strcat(chBuffer, " LDate = getdate() ");
	strcat(chBuffer, " where Name = '%s' ");

	qSql.Format(chBuffer,
		lpObj->Level,
		lpObj->Class,
		lpObj->LevelUpPoint,
		lpObj->Experience,
		lpObj->Strength,
		lpObj->Dexterity,
		lpObj->Vitality,
		lpObj->Energy,
		lpObj->Money,
		lpObj->Life,
		lpObj->MaxLife,
		lpObj->Mana,
		lpObj->MaxMana,
		lpObj->MapNumber,
		lpObj->MapX,
		lpObj->MapY,
		lpObj->Dir,
		lpObj->PkCount,
		lpObj->PkLevel,
		lpObj->PkTime,
		lpObj->Leadership,
		lpObj->ChatLitmitTime,
		lpObj->FruitPoint,
		Name);
	if (this->m_DBQuery.Exec(qSql))
	{
		qSql.Format("WZ_SetSaveItem '%s', '%s', ?", lpObj->AccountID, Name);
		this->m_DBQuery.WriteBlob(qSql, lpObj->dbInventory, 3792);
		qSql.Format("UPDATE Character SET MagicList=? where Name='%s'", Name);
		this->m_DBQuery.WriteBlob(qSql, lpObj->dbMagicList, 450);
		qSql.Format("UPDATE Character SET Quest=? where Name='%s'", Name);

		this->m_DBQuery.WriteBlob(qSql, lpObj->dbQuest, 50);
		sresult = 1;
	}
	else
	{
		sresult = 0;
	}
	return sresult;

	return 0x01;
}
//#define OLD_GETCHAR
#ifdef OLD_GETCHAR
BOOL CCharDBSet::GetCharacter(char* szAccountID, char* Name, LPCharacterInfo_Struct lpObj)
{
	CString qSql;

	char chBuffer[512] = "SELECT AccountID, cLevel, Class, LevelUpPoint, Experience, Strength, Dexterity, Vitality, Energy, Money, Life, MaxLife, Mana, MaxMana, MapNumber, MapPosX, MapPosY, MapDir, PkCount, PkLevel, PkTime, CtlCode,";
	
	strcat(chBuffer, " Leadership, ");

	strcat(chBuffer, " ChatLimitTime, ");
	strcat(chBuffer, " FruitPoint, ");
	strcat(chBuffer, " ExGameServerCode, ");
	strcat(chBuffer, " ExtendedInvenCount, ");
	strcat(chBuffer, " DbVersion ");
	strcat(chBuffer, " FROM Character where Name = '%s' ");

	qSql.Format(chBuffer, Name);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	if(m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	m_DBQuery.GetStr("AccountID", lpObj->AccountID);

	if( strcmp(lpObj->AccountID, szAccountID) != 0)
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

	if(ctlcode < 0)
	{
		ctlcode = 0;
	}

	lpObj->CtlCode = ctlcode;

	int dbversion = m_DBQuery.GetInt("DbVersion");

	if(dbversion < 0)
	{
		dbversion = 0;
	}

	lpObj->DbVersion = dbversion;

	int leadership = m_DBQuery.GetInt("Leadership");

	if(leadership < 0)
	{
		leadership = 0;
	}

	int ChatLitmitTime = m_DBQuery.GetInt("ChatLimitTime");

	if(ChatLitmitTime < 0)
	{
		ChatLitmitTime = 0;
	}

	lpObj->Leadership = leadership;
	lpObj->ChatLitmitTime = ChatLitmitTime;

	int iFruitPoint = m_DBQuery.GetInt("FruitPoint");

	if(iFruitPoint < 0)
	{
		lpObj->FruitPoint = 0;
		LogAddC(LOGC_RED, "[Fruit System] [%s][%s] Fruit ÄÃ·³ %d -> 0 À¸·Î ¼öÁ¤ ", lpObj->AccountID, Name, iFruitPoint);
	}
	else
	{
		lpObj->FruitPoint = iFruitPoint;
	}

	lpObj->btExtendedInvenCount = m_DBQuery.GetInt("ExtendedInvenCount");
	//lpObj->sExGameServerCode = m_DBQuery.GetInt("ExGameServerCode");

	m_DBQuery.Clear();
	///////////////////////////////////
	qSql.Format("SELECT ExtendedWarehouseCount from AccountCharacter where Id='%s'", szAccountID);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	if(m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return FALSE;
	}

	lpObj->btExtendedWarehouseCount = m_DBQuery.GetInt("ExtendedWarehouseCount");
	m_DBQuery.Clear();
	///////////////////////////////////

	///////////////////////////////////
	qSql.Format("SELECT Inventory from Character where Name='%s'", Name);

	int nRet = m_DBQuery.ReadBlob(qSql, lpObj->dbInventory);

	if(nRet == 0)
	{
		for(int n = 0; n < MAX_DBINVENTORY; n++)
		{
			lpObj->dbInventory[n] = 0xFF;
		}
	}
	else if(nRet == -1)
	{
		return FALSE;
	}
	else if(nRet == 760)
	{
		for(int n = 760; n < MAX_DBINVENTORY; n++)
		{
			lpObj->dbInventory[n] = 0xFF;
		}
	}
	else if(nRet > 0 && nRet < MAX_DBINVENTORY)
	{
		for(int n = nRet; n < MAX_DBINVENTORY; n++)
		{
			lpObj->dbInventory[n] = 0xFF;
		}
	}
	///////////////////////////////////

	///////////////////////////////////
	qSql.Format("SELECT MagicList from Character where Name='%s'", Name);
	nRet = m_DBQuery.ReadBlob(qSql, lpObj->dbMagicList);

	if(nRet == 0)
	{
		for (int n = 0; n < MAX_MAGIC; n++ )
		{
			lpObj->dbMagicList[3 * n] = 0xFF;
			lpObj->dbMagicList[3 * n + 1] = 0;
			lpObj->dbMagicList[3 * n + 2] = 0;
		}
	}
	else if(nRet == -1)
	{
		return FALSE;
	}
	else if(nRet > 0 && nRet < MAX_DBMAGIC)
	{
		int n = nRet;

		while(n < MAX_DBMAGIC)
		{
			lpObj->dbMagicList[n] = 0xFF;
			lpObj->dbMagicList[n + 1] = 0;
			lpObj->dbMagicList[n + 2] = 0;
			n += 3;
		}
	}
	///////////////////////////////////

	///////////////////////////////////
	qSql.Format("SELECT Quest from Character where Name='%s'", Name);
	nRet = m_DBQuery.ReadBlob(qSql, lpObj->dbQuest);

	if(nRet == 0)
	{
		for (int n = 0; n < MAX_DBQUEST; n++ )
		{
			lpObj->dbQuest[n] = 0xFF;
		}
	}
	else if(nRet == -1)
	{
		return FALSE;
	}
	///////////////////////////////////
	
	return TRUE;
}
#else
int CCharDBSet::GetCharacter(char *szAccountID, char *Name, CharacterInfo_Struct *lpObj)
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

	if (!this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		return 0;
	}
	if (this->m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		this->m_DBQuery.Clear();
		return 0;
	}
	this->m_DBQuery.GetStr("AccountID", lpObj->AccountID);

	if (strcmp(lpObj->AccountID, szAccountID) != 0)
	{
		LogAddC(LOGC_RED, "error-L1 :Ä³¸¯ÅÍÀÇ °èÁ¤°ú ¿äÃ»ÇÑ °èÁ¤ÀÌ ¸ÂÁö¾Ê´Ù.%s %s", lpObj->AccountID, szAccountID);
		this->m_DBQuery.Clear();
		return 0;
	}
	lpObj->Level = this->m_DBQuery.GetInt("cLevel");
	lpObj->Class = this->m_DBQuery.GetInt("Class");
	lpObj->LevelUpPoint = this->m_DBQuery.GetInt("LevelUpPoint");
	lpObj->Experience = this->m_DBQuery.GetInt("Experience");
	lpObj->Strength = this->m_DBQuery.GetInt("Strength");
	lpObj->Dexterity = this->m_DBQuery.GetInt("Dexterity");
	lpObj->Vitality = this->m_DBQuery.GetInt("Vitality");
	lpObj->Energy = this->m_DBQuery.GetInt("Energy");
	lpObj->Money = this->m_DBQuery.GetInt("Money");
	lpObj->Life = this->m_DBQuery.GetFloat("Life");
	lpObj->MaxLife = this->m_DBQuery.GetFloat("MaxLife");
	lpObj->Mana = this->m_DBQuery.GetFloat("Mana");
	lpObj->MaxMana = this->m_DBQuery.GetFloat("MaxMana");
	lpObj->MapNumber = this->m_DBQuery.GetInt("MapNumber");
	lpObj->MapX = this->m_DBQuery.GetInt("MapPosX");
	lpObj->MapY = this->m_DBQuery.GetInt("MapPosY");
	lpObj->Dir = this->m_DBQuery.GetInt("MapDir");
	lpObj->PkCount = this->m_DBQuery.GetInt("PkCount");
	lpObj->PkLevel = this->m_DBQuery.GetInt("PkLevel");
	lpObj->PkTime = this->m_DBQuery.GetInt("PkTime");
	int ctlcode = this->m_DBQuery.GetInt("CtlCode");

	if (ctlcode < 0)
		ctlcode = 0;
	lpObj->CtlCode = ctlcode;
	int  dbversion = this->m_DBQuery.GetInt("DbVersion");
	if (dbversion < 0)
		dbversion = 0;
	lpObj->DbVersion = dbversion;
	int  leadership = this->m_DBQuery.GetInt("Leadership");
	if (leadership < 0)
		leadership = 0;
	int  ChatLitmitTime = this->m_DBQuery.GetInt("ChatLimitTime");
	if (ChatLitmitTime < 0)
		ChatLitmitTime = 0;
	lpObj->Leadership = leadership;
	lpObj->ChatLitmitTime = ChatLitmitTime;
	int iFruitPoint = this->m_DBQuery.GetInt("FruitPoint");
	if (iFruitPoint >= 0)
	{
		lpObj->FruitPoint = iFruitPoint;
	}
	else
	{
		lpObj->FruitPoint = 0;
		LogAddC(LOGC_RED, "[Fruit System] [%s][%s] Fruit ÄÃ·³ %d -> 0 À¸·Î ¼öÁ¤ ", lpObj->AccountID, Name, iFruitPoint);
	}
	lpObj->btExtendedInvenCount = this->m_DBQuery.GetInt("ExtendedInvenCount");
	this->m_DBQuery.Clear();
	qSql.Format("SELECT ExtendedWarehouseCount from AccountCharacter where Id='%s'", szAccountID);

	if (!this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		return 0;
	}
	if (this->m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		this->m_DBQuery.Clear();
		return 0;
	}
	lpObj->btExtendedWarehouseCount = this->m_DBQuery.GetInt("ExtendedWarehouseCount");
	this->m_DBQuery.Clear();

	qSql.Format("WZ_GetLoadInventory '%s', '%s'", szAccountID, Name);

	int nRet = this->m_DBQuery.ReadBlob(qSql, lpObj->dbInventory);
	if (nRet)
	{
		if (nRet == -1)
		{
			return 0;
		}
		if (nRet == 760)
		{
			for (int j = 760; j < MAX_DBINVENTORY; ++j)
				lpObj->dbInventory[j] = 0xFF;
		}
		else if (nRet > 0 && nRet < MAX_DBINVENTORY)
		{
			for (int k = nRet; k < MAX_DBINVENTORY; ++k)
				lpObj->dbInventory[k] = 0xFF;
		}
	}
	else
	{
		for (int i = 0; i < MAX_DBINVENTORY; ++i)
			lpObj->dbInventory[i] = 0xFF;
	}
	qSql.Format("SELECT MagicList from Character where Name='%s'", Name);

	nRet = this->m_DBQuery.ReadBlob(qSql, lpObj->dbMagicList);
	if (nRet)
	{
		if (nRet == -1)
		{
			return 0;
		}
		if (nRet > 0 && nRet < MAX_MAGIC)
		{
			for (int l = nRet; l < MAX_MAGIC; l += 3)
			{
				lpObj->dbMagicList[l] = 0xFF;
				lpObj->dbMagicList[l + 1] = 0;
				lpObj->dbMagicList[l + 2] = 0;
			}
		}
	}
	else
	{
		for (int n = 0; n < MAX_MAGIC; ++n)
		{
			lpObj->dbMagicList[3 * n] = 0xFF;
			lpObj->dbMagicList[3 * n + 1] = 0;
			lpObj->dbMagicList[3 * n + 2] = 0;
		}
	}
	qSql.Format("SELECT Quest from Character where Name='%s'", Name);
	nRet = this->m_DBQuery.ReadBlob(qSql, lpObj->dbQuest);
	if (nRet)
	{
		if (nRet == -1)
		{
			return 0;
		}
	}
	else
	{
		for (int m = 0; m < MAX_DBQUEST; ++m)
			lpObj->dbQuest[m] = 0xFF;
	}
	///////////////////////////////////

	return TRUE;
}
#endif
void CCharDBSet::SaveMacroInfo(char* szAccountID, char* Name, BYTE* lpMacroInfo)
{
	CString qSql;

	qSql.Format("EXEC WZ_MACROINFO_SAVE '%s', '%s', ?", szAccountID, Name);
	m_DBQuery.WriteBlob(qSql, lpMacroInfo, MAX_MACRO_DATA);
}

BOOL CCharDBSet::LoadMacroInfo(char* szAccountID, char* Name, BYTE* lpMacroInfo)
{
	CString qSql;

	qSql.Format("EXEC WZ_MACROINFO_LOAD '%s', '%s'", szAccountID, Name);
	int nRet = m_DBQuery.ReadBlob(qSql, lpMacroInfo);


	if (nRet)
	{
		if (nRet == -1)
		{
			m_DBQuery.Clear();
			return 0;
		}
	}
	else
	{
		for (int i = 0; i < MAX_MACRO_DATA; i++)
		{
			lpMacroInfo[i] = -1;
		}
	}

	return TRUE;
}

BOOL CCharDBSet::SaveItem(char *Name, BYTE* ItemBuf, char *AccountId)//changed
{
	CString qSql;
	int result;

	qSql.Format("UPDATE Character SET DbVersion=3 where Name = '%s'", Name);
	if (this->m_DBQuery.Exec(qSql))
	{
		qSql.Format("WZ_SetSaveItem '%s', '%s', ?", AccountId, Name);
		m_DBQuery.WriteBlob(qSql, ItemBuf, MAX_DBINVENTORY);
		result = 1;
}
	else
	{
		result = 0;
	}
	return result;
	//	CString qSql;
	//	
	//#ifdef ITEM_DBSIZE_EXTEND_20050706
	//	qSql.Format("UPDATE Character SET DbVersion=3 where Name = '%s'", Name);
	//#elif defined(PERSONAL_SHOP_20040113)
	//	qSql.Format("UPDATE Character SET DbVersion=2 where Name = '%s'", Name);
	//#else
	//	qSql.Format("UPDATE Character SET DbVersion=1 where Name = '%s'", Name);
	//#endif
	//	
	//	if(m_DBQuery.Exec(qSql) == FALSE)
	//	{
	//		return FALSE;
	//	}
	//
	//	qSql.Format("UPDATE Character SET Inventory=? where Name='%s'", Name);
	//	m_DBQuery.WriteBlob(qSql, ItemBuf, MAX_DBINVENTORY);
	//
	//	return TRUE;
}

int CCharDBSet::CharServerMove(char* Name)
{
	CString qSql;

	qSql.Format("SP_CHARACTER_TRANSFER '%s'", Name);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		LogAddC(LOGC_BLUE,"SP_CHARACTER_TRANSFER error return #1");
		return 1;
	}

	if(m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		LogAddC(LOGC_BLUE,"SP_CHARACTER_TRANSFER error return #2");
		m_DBQuery.Clear();
		return 1;
	}

	int error = m_DBQuery.GetInt(1);

	m_DBQuery.Clear();

	LogAddC(LOGC_BLUE,"SP_CHARACTER_TRANSFER result %d", error);

	if(error != 0)
	{
		return error;
	}

	return 0;
}

int CCharDBSet::ChangeName(char* AccountId, char* OldName, char* NewName)
{
	int result = 0;
	CString qSql;

	qSql.Format("WZ_ChangeCharacterName '%s', '%s', '%s'", AccountId, OldName, NewName);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return 5;
	}

	if(m_DBQuery.Fetch() != SQL_NO_DATA)
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

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return 1;
	}

	if(m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return 2;
	}

	char chBuffer[MAX_IDSTRING+1];

	m_DBQuery.GetStr(1, chBuffer);

	memcpy(chUserID, chBuffer, MAX_IDSTRING+1);

	m_DBQuery.Clear();

	return 0;
}

DWORD CCharDBSet::GetCharacterClass(char* chName)
{
	CString qSql;
	DWORD dwReturn = 0;

	qSql.Format("SELECT Class FROM Character WHERE Name = '%s'", chName);

	if(m_DBQuery.Exec(qSql) == FALSE)
	{
		m_DBQuery.Clear();
		return -1;
	}

	if(m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		m_DBQuery.Clear();
		return -2;
	}

	dwReturn = m_DBQuery.GetInt(1);

	m_DBQuery.Clear();

	return dwReturn;
}

//Season 12+
void CCharDBSet::RuudToken_Update(char *AccountID, char *Name, unsigned int dwRuudCnt)
{
	int nRetrun;
	__int16 sqlReturn;
	CString sql;
	char szCahrName[MAX_IDSTRING + 1];
	char szId[MAX_IDSTRING + 1];

	szId[MAX_IDSTRING] = 0;
	memcpy(szId, AccountID, MAX_IDSTRING);
	szCahrName[MAX_IDSTRING] = 0;
	memcpy(szCahrName, Name, MAX_IDSTRING);

	if (strlen(szCahrName) && (strlen(szCahrName) <= 0xA) &&
		(strlen(szId)) && (strlen(szId) <= 0xA))
	{
		
		sql.Format("WZ_RuudTokenUpdate '%s','%s', %d",
			szId,
			szCahrName,
			dwRuudCnt);
		if (m_DBQuery.Exec(sql))
		{
			sqlReturn = m_DBQuery.Fetch();
			if (sqlReturn != SQL_NO_DATA || sqlReturn != -1)
			{
				nRetrun = m_DBQuery.GetInt(1);
				if (nRetrun)
				{
					LogAddTD("RuudToken_Update return %d ACC:%s , Name:%s, ruud :%d ", nRetrun, szId, szCahrName, dwRuudCnt);
					LogAddTD("RuudToken_Update -1 == UpdateFail, -2 == InsertFail");
				}
				m_DBQuery.Clear();
			}
			else
			{
				LogAddTD(
					"Error-L2 [CAccountCharDBSet] [RuudToken_Update] %d, %s , %d",
					sqlReturn,__FILE__,__LINE__);
				m_DBQuery.Clear();
			}
		}
		else
		{
			LogAddTD("Error-L1 [CAccountCharDBSet][RuudToken_Update] ACC:%s NAME:%s, Ruud:%d ", szId, szCahrName, dwRuudCnt);
			m_DBQuery.Clear();
		}
	}
	else
	{
		LogAddC(2,"%s] 로드 에러 %s %d",szCahrName,__FILE__, __LINE__);
	}
}

BOOL CCharDBSet::LoadSnsInfo(char *szAccountID, char *Name, BYTE *lpSnsInfo)
{
	int result;
	CString qSql;

	qSql.Format("EXEC WZ_SnsInfo_Load '%s', '%s'",szAccountID,Name);
	int nRet = m_DBQuery.ReadBlob(qSql, lpSnsInfo);
	if (nRet)
	{
		if (nRet == -1)
		{
			result = 2;
		}
		else
		{
			result = 0;
		}
	}
	else
	{
		for (int i = 0; i < 255; ++i)
			lpSnsInfo[i] = -1;
		result = 1;
	}
	return result;
}

int CCharDBSet::DeleteSnsInfo(char *szAccountID, char *szName)
{

	int result;
	CString qSql;

	qSql.Format("exec WZ_DeleteSnsInfo '%s', '%s'",szAccountID,szName);

	if (this->m_DBQuery.Exec(qSql) == 1)
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		result = 0;
	}
	return result;
}

void CCharDBSet::SaveSnsInfo(char *szAccountID, char *Name, BYTE *lpSnsInfo)
{
	CString qSql;

	qSql.Format("EXEC WZ_SnsInfo_Save '%s', '%s', ?",szAccountID,Name);
	m_DBQuery.WriteBlob(qSql, lpSnsInfo, 255);
}

//----- (00437040) --------------------------------------------------------
void CCharDBSet::SaveUserSetting(char *szAccountID, BYTE *lpSaveData)
{
	CString qSql;

	qSql.Format("EXEC WZ_UserSettingInfo_Save '%s', ?",szAccountID);
	m_DBQuery.WriteBlob(qSql, lpSaveData, 255);
}

//----- (00437120) --------------------------------------------------------
int CCharDBSet::LoadUserSetting(char *szAccountID, BYTE *lpSaveData)
{
	int result;
	CString qSql;

	qSql.Format("EXEC WZ_UserSettingInfo_Load '%s'",szAccountID);
	int nRet = m_DBQuery.ReadBlob(qSql, lpSaveData);
	if (nRet)
	{
		if (nRet == -1)
		{
			result = 2;
		}
		else
		{
			result = 0;
		}
	}
	else
	{
		for (int i = 0; i < 255; ++i)
			lpSaveData[i] = -1;
		result = 1;
	}
	return result;
}

BOOL CCharDBSet::DeleteUserSetting(char *szAccountID)
{
	int result;
	CString qSql;
	
	qSql.Format("exec WZ_DeleteUserSettingInfo '%s', '%s'",szAccountID);

	if (this->m_DBQuery.Exec(qSql) == 1)
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		result = 0;
	}
	return result;
}

__int64 CCharDBSet::SaveEventInvenItem(char *Name, BYTE *ItemBuf, char *AccountId)
{
	CString qSql;
	qSql.Format("WZ_SetSaveEventInventory '%s', '%s', ?", AccountId, Name);
	this->m_DBQuery.WriteBlob(qSql, ItemBuf, 512);
	this->m_DBQuery.Clear();
	return TRUE;
}

int CCharDBSet::LoadEventInvenItem(char *Name, BYTE *ItemBuf, char *AccountId, int *DbVersion)
{
	int result;
	CString qSql;

	qSql.Format("WZ_GetLoadEventInventory '%s', '%s'",AccountId,Name);
	
	if (this->m_DBQuery.ReadBlob(qSql, ItemBuf) == -1)
	{
		this->m_DBQuery.Clear();
		result = 0;
	}
	else
	{
		qSql.Format("SELECT DbVersion from T_Event_Inventory where AccountID='%s'",AccountId);
		if (this->m_DBQuery.Exec(qSql))
		{
			if (this->m_DBQuery.Fetch() == SQL_NO_DATA)
			{
				this->m_DBQuery.Clear();
				result = 0;
			}
			else
			{
				*DbVersion = this->m_DBQuery.GetInt(1);
				this->m_DBQuery.Clear();
				result = 1;
			}
		}
		else
		{
			this->m_DBQuery.Clear();
			result = 0;
		}
	}
	return result;
}

int CCharDBSet::CreateCharacterMoneyUpdate(CString Name)
{
	int result;
	CString qSql;

	qSql.Format("UPDATE Character SET Money = 1000000000 WHERE Name = '%s'",Name);
	
	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		result = 0;
	}
	return result;
}

BOOL CCharDBSet::RestoreJumpingPkLevel(char *Name, BYTE btPkLevel)
{
	int result;
	CString qSql;

	qSql.Format("UPDATE Character SET PkLevel = %d WHERE Name = '%s'",
		btPkLevel,
		Name);

	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		result = 0;
	}
	return result;
}

void CCharDBSet::RuudToken_LoadCount(char *AccountID, char *Name, int *nRuudCnt)
{
	__int16 sqlReturn;
	CString qSql;
	char szCahrName[11];
	char szId[MAX_IDSTRING + 1];

	szId[10] = 0;
	memcpy(szId, AccountID, 0xAu);
	szCahrName[10] = 0;
	memcpy(szCahrName, Name, 0xAu);

	if (strlen(szCahrName) && (strlen(szCahrName) <= 0xA) && (strlen(szId)) && (strlen(szId) <= 0xA))
	{
		*nRuudCnt = 0;
		qSql.Format("WZ_RuudTokenLoad '%s','%s'",szId,szCahrName);
		if (this->m_DBQuery.Exec(qSql))
		{
			sqlReturn = this->m_DBQuery.Fetch();
			if (sqlReturn != 100 && sqlReturn != -1)
			{
				*nRuudCnt = this->m_DBQuery.GetInt(1);
				LogAddTD("[RuudToken_LoadCount]Acc:%s,Name:%s,Ruud:%d", szId, szCahrName, *nRuudCnt);
				if (*nRuudCnt == -1)
					*nRuudCnt = 0;
				this->m_DBQuery.Clear();
			}
			else
			{
				this->m_DBQuery.Clear();
				LogAddTD("Error-L3 [CAccountCharDBSet][WZ_RuudTokenLoad][A2] ACC:%s,NAME:%s sqlReturn:%d File %s Line %d ",
					szId,szCahrName,sqlReturn, __FILE__, __LINE__);
			}
		}
		else
		{
			LogAddTD("Error-L3 [CAccountCharDBSet][WZ_RuudTokenLoad][A1] %s %s", szId, szCahrName);
		}
	}
	else
	{
		LogAddC(2,"%s",szCahrName, __FILE__, __LINE__);
	}
}


void CCharDBSet::RewardJumpingItem(char *Name, BYTE *JumpingInventoryBuf)
{

	CString qSql; // [esp+D4h] [ebp-20h]
	qSql.Format("UPDATE Character SET Inventory=? where Name='%s'",Name);
	this->m_DBQuery.WriteBlob(qSql, JumpingInventoryBuf, 3776);
	this->m_DBQuery.Clear();
}

