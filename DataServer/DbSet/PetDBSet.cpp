// PetDBSet.cpp: implementation of the CPetDBSet class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PetDBSet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPetDBSet::CPetDBSet()
{

}

CPetDBSet::~CPetDBSet()
{

}

BOOL CPetDBSet::Connect()
{
	return this->CDBConBase::Connect(szDbConnectID, szDbConnectPass);
}

BOOL CPetDBSet::LoadPetInfo(DWORD number, int& Level, int& Exp)
{
	CString qSQL;

	qSQL.Format("SELECT Pet_Level, Pet_Exp FROM T_PetItem_Info WHERE ItemSerial=%u", number);

	if(this->m_DBQuery.Exec(qSQL) == FALSE)
	{
		return FALSE;
	}

	if(this->m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		this->m_DBQuery.Clear();
		this->CreatePetItemInfo(number, 1, 0);
		return FALSE;
	}

	Level = this->m_DBQuery.GetInt("Pet_Level");
	Exp = this->m_DBQuery.GetInt("Pet_Exp");

	this->m_DBQuery.Clear();

	if(Level < 0)
	{
		Level = 1;
	}

	if(Exp < 0)
	{
		Exp = 0;
	}

	return TRUE;
}

BOOL CPetDBSet::SavePetInfo(DWORD number, int Level, int Exp)
{
	CString qSQL;

	qSQL.Format("UPDATE T_PetItem_Info SET Pet_Level=%d, Pet_Exp=%d WHERE ItemSerial=%u", Level, Exp, number);

	if(this->m_DBQuery.Exec(qSQL) == FALSE)
	{
		return FALSE;
	}

	this->m_DBQuery.Clear();

	return TRUE;
}

BOOL CPetDBSet::CreatePetItemInfo(DWORD serial, int Level, __int64 Exp)
{
	CString qSQL;

	qSQL.Format("INSERT INTO T_PetItem_Info (ItemSerial,Pet_Level,Pet_Exp) VALUES(%u,%d,%I64d)", serial, Level, Exp);

	if(this->m_DBQuery.Exec(qSQL) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPetDBSet::UBFCopyPetInfo(unsigned int number, unsigned __int16 ServerCode)
{
	int result;
	int iResult;
	CString qSql;

	iResult = 0;
	qSql.Format("WZ_UnityBattleFieldPetInfoCopy_r %u, %d",
		number,
		ServerCode);
	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		LogAddTD("Error-L3 [PetDBSet][WZ_UnityBattleFieldPetInfoCopy_r] PetSerial:%d ", number);
		this->m_DBQuery.Clear();
		result = 0;
	}
	return result;
}

//----- (00448F60) --------------------------------------------------------
BOOL CPetDBSet::LoadPetInfoForUBF(unsigned int number, int *Level, __int64 *Exp, unsigned __int16 SeverCode)
{
	int result;
	__int64 *v8;
	__int16 sqlReturn;
	CString qSql;
	bool v7;

	qSql.Format("EXEC WZ_UnityBattleFieldPetInfoLoad_r %u, %d",
		number,
		SeverCode);
	if (this->m_DBQuery.Exec(qSql))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != 100 && sqlReturn != -1)
		{
			*Level = this->m_DBQuery.GetInt("Pet_Level");
			*Exp = this->m_DBQuery.GetInt64("Pet_Exp");
			this->m_DBQuery.Clear();
			if (*Level < 0)
				*Level = 1;
			v8 = Exp;
			if (*(Exp + 1) <= 0)
			{
				if (*(Exp + 1) < 0)
					*Exp = 0i64;
				else
					v7 = *v8 == 0;
			}
			result = 1;
		}
		else
		{
			LogAddTD(
				"Error-L3 [CPetDBSet][WZ_UnityBattleFieldPetInfoLoad_r] PetSerial:%d Return %d,%s,%d ",
				number,
				sqlReturn, __FILE__, __LINE__);
			this->m_DBQuery.Clear();
			result = 0;
		}
	}
	else
	{
		LogAddTD("Error-L3 [PetDBSet][WZ_UnityBattleFieldPetInfoLoad_r] PetSerial:%d", number);
		this->m_DBQuery.Clear();
		result = 0;
	}
	return result;
}
// 5CDFD4: using guessed type int `CPetDBSet::LoadPetInfoForUBF'::`2'::__LINE__Var;

//----- (004491A0) --------------------------------------------------------
BOOL CPetDBSet::SavePetInfoForUBF(unsigned int number, int Level, __int64 Exp, unsigned __int16 SeverCode)
{
	int result;
	CString qSql;

	qSql.Format("EXEC WZ_UnityBattleFieldPetInfoSave_r %d, %I64d, %u, %d ",
		Level,
		Exp,
		number,
		SeverCode);
	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		LogAddTD("Error-L3 [PetDBSet][WZ_UnityBattleFieldPetInfoSave_r] PetSerial:%d SeverCode:%d", number, SeverCode);
		this->m_DBQuery.Clear();
		result = 0;
	}
	return result;
}