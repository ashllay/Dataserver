// OptionDbSet.cpp: implementation of the COptionDbSet class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OptionDbSet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COptionDbSet::COptionDbSet()
{

}

COptionDbSet::~COptionDbSet()
{

}

BOOL COptionDbSet::Connect()
{
	if(m_DBQuery.Connect(3,szDbConnectDsn,szDbConnectID,szDbConnectPass) == FALSE)
	{
		MsgBox("可记沥焊 DB 立加 角菩");
		return FALSE;
	}

	return TRUE;
}

BOOL COptionDbSet::Load(char* name, BYTE* KeyBuffer, BYTE& GO, BYTE& QK, BYTE& WK, BYTE& EK, BYTE& CW, BYTE& RK, int& QWERLevel, BYTE& EnableChangeMode, short &PlayGuideLv, BYTE& PlayGuideCheck)
{
	int nRet;
	int result;
	CString qSql;
	qSql.Format("EXEC WZ_OptionData_UI_Load '%s'", name);

	if (this->m_DBQuery.Exec(qSql))
	{
		if (this->m_DBQuery.Fetch() == SQL_NO_DATA)
		{
			LogAddTD("[COptionDbSet][Load] Game UserOptinData Load Error : Fetch() Error");
			result = 0;
		}
		else
		{
			GO = this->m_DBQuery.GetInt("GameOption");
			QK = this->m_DBQuery.GetInt("Qkey");
			WK = this->m_DBQuery.GetInt("Wkey");
			EK = this->m_DBQuery.GetInt("Ekey");
			CW = this->m_DBQuery.GetInt("ChatWindow");
			RK = this->m_DBQuery.GetInt("RKey");
			QWERLevel = this->m_DBQuery.GetInt("QWERLevel");
			EnableChangeMode = this->m_DBQuery.GetInt("EnableChangeMode");
			PlayGuideLv = this->m_DBQuery.GetInt("PlayGuideLv");
			PlayGuideCheck = this->m_DBQuery.GetInt("PlayGuideCK");
			this->m_DBQuery.Clear();
			qSql.Format("EXEC WZ_OptionData_SkillKey_Load '%s'", name);

			nRet = this->m_DBQuery.ReadBlob(qSql, KeyBuffer);
			if (nRet == 0xFF)
				LogAddTD("[COptionDbSet][Load] Game UserOptinData Load Error : ReadBlob() Error");
			this->m_DBQuery.Clear();
			result = nRet;
		}
	}
	else
	{
		LogAddTD("[COptionDbSet][Load] Game UserOptinData Load Error : Exec(Sql) Error");
		this->m_DBQuery.Clear();
		result = 0;
	}
	return result;
//	int nRet;
//	CString qSql;
//
//	qSql.Format("SELECT * FROM OptionData WHERE Name='%s'", name);
//
//	if(m_DBQuery.Exec(qSql) == FALSE)
//	{
//		return FALSE;
//	}
//
//	if(m_DBQuery.Fetch() == SQL_NO_DATA)
//	{
//		m_DBQuery.Clear();
//		return FALSE;
//	}
//
//	int GameOption = m_DBQuery.GetInt("GameOption");
//
//	if(GameOption >= 0)
//	{
//		GO = GameOption;
//	}
//	
//	int Qkey, Wkey, Ekey, Rkey, QWERL, ChatWindow;
//
//	Qkey = m_DBQuery.GetInt("Qkey");
//
//	if(Qkey >= 0)
//	{
//		QK = Qkey;
//	}
//	
//	Wkey = m_DBQuery.GetInt("Wkey");
//
//	if(Wkey >= 0)
//	{
//		WK = Wkey;
//	}
//
//	Ekey = m_DBQuery.GetInt("Ekey");
//
//	if(Ekey >= 0)
//	{
//		EK = Ekey;
//	}
//
//#ifdef VER_CHATWINDOW_OPTION
//	ChatWindow = m_DBQuery.GetInt("ChatWindow");
//
//	if(ChatWindow >= 0)
//	{
//		CW = ChatWindow;
//	}
//	else
//	{
//		CW = 0xFF;
//	}
//#endif
//	
//#ifdef ADD_SEASON_3_NEW_UI_20071122
//	Rkey = m_DBQuery.GetInt("Rkey");
//
//	if(Rkey >= 0)
//	{
//		RK = Rkey;
//	}
//#endif
//
//#ifdef UPDATE_OPTIONKEY_LEVEL_20080116
//	QWERL = m_DBQuery.GetInt("QWERLevel");
//
//	if(QWERL >= 0)
//	{
//		QWERLevel = QWERL;
//	}
//#endif
//
//	m_DBQuery.Clear();
//
//	qSql.Format("SELECT SkillKey from OptionData where Name='%s'", name);
//	nRet = m_DBQuery.ReadBlob(qSql, KeyBuffer);
//
//	return nRet;
}

BOOL COptionDbSet::IsUser(char* name)
{
	CString qSQL;

	qSQL.Format("SELECT Name FROM OptionData WHERE Name='%s'", name);

	char buffer[256];

	if(m_DBQuery.ExecGetStr(qSQL, buffer) == FALSE)
	{
		return FALSE;
	}

	if( strcmp(name, buffer) != 0)
	{
		return FALSE;
	}

	return TRUE;
}


void COptionDbSet::Save(char* name, BYTE* KeyBuffer, BYTE GO, BYTE QK, BYTE WK, BYTE EK, BYTE CW, BYTE RK, int QWERLevel, BYTE EnableChangeMode, short PlayGuideLv, BYTE PlayGuideCheck)
{
	CString qSql;

	qSql.Format("EXEC WZ_OptionData_Save '%s', %d, %d, %d, %d, %d, %d, %d, %d, ?, %d, %d",
		name,
		GO,
		QK,
		WK,
		EK,
		CW,
		RK,
		QWERLevel,
		EnableChangeMode,
		PlayGuideLv,
		PlayGuideCheck);
	m_DBQuery.WriteBlob(qSql, KeyBuffer, 20);
	this->m_DBQuery.Clear();
//	CString qSql;
//
//	if(this->IsUser(name) == FALSE)
//	{
//#ifdef UPDATE_OPTIONKEY_LEVEL_20080116
//		qSql.Format("INSERT INTO OptionData (Name, GameOption, Qkey, Wkey, Ekey, ChatWindow, RKey, QWERLevel) VALUES ('%s', %d, %d, %d, %d, %d, %d, %d)",
//			name, GO, QK, WK, EK, CW, RK, QWERLevel);
//#elif defined(ADD_SEASON_3_NEW_UI_20071122)
//		qSql.Format("INSERT INTO OptionData (Name, GameOption, Qkey, Wkey, Ekey, ChatWindow, RKey) VALUES ('%s', %d, %d, %d, %d, %d, %d)",
//			name, GO, QK, WK, EK, CW, RK);
//#elif defined(VER_CHATWINDOW_OPTION)
//		qSql.Format("INSERT INTO OptionData (Name, GameOption, Qkey, Wkey, Ekey, ChatWindow) VALUES ('%s', %d, %d, %d, %d, %d)",
//			name, GO, QK, WK, EK, CW);
//#else
//		qSql.Format("INSERT INTO OptionData (Name, GameOption, Qkey, Wkey, Ekey) VALUES ('%s', %d, %d, %d, %d)",
//			name, GO, QK, WK, EK);
//#endif
//
//		if(m_DBQuery.Exec(qSql) == FALSE)
//		{
//			return;
//		}
//		return;
//	}
//
//#ifdef UPDATE_OPTIONKEY_LEVEL_20080116
//	qSql.Format("UPDATE OptionData SET GameOption=%d, Qkey=%d, Wkey=%d, Ekey=%d, ChatWindow=%d, RKey=%d, QWERLevel=%d where Name='%s'",
//		GO, QK, WK, EK, CW, RK, QWERLevel, name);
//#elif defined(ADD_SEASON_3_NEW_UI_20071122)
//	qSql.Format("UPDATE OptionData SET GameOption=%d, Qkey=%d, Wkey=%d, Ekey=%d, ChatWindow=%d, RKey=%d where Name='%s'",
//		GO, QK, WK, EK, CW, RK, name);
//#elif defined(VER_CHATWINDOW_OPTION)
//	qSql.Format("UPDATE OptionData SET GameOption=%d, Qkey=%d, Wkey=%d, Ekey=%d, ChatWindow=%d where Name='%s'",
//		GO, QK, WK, EK, CW, name);
//#else
//	qSql.Format("UPDATE OptionData SET GameOption=%d, Qkey=%d, Wkey=%d, Ekey=%d where Name='%s'",
//		GO, QK, WK, EK, name);
//#endif
//
//	if(m_DBQuery.Exec(qSql) == FALSE)
//	{
//		return;
//	}
//
//	qSql.Format("UPDATE OptionData SET SkillKey=? where Name='%s'", name);
//#ifdef UPDATE_SKILLKEY_EXPAND_20080804
//	m_DBQuery.WriteBlob(qSql, KeyBuffer, 20);
//#else
//	m_DBQuery.WriteBlob(qSql, KeyBuffer, 10);
//#endif
}