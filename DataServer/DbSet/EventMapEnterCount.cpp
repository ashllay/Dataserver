#include "StdAfx.h"
#include "EventMapEnterCount.h"

EventMapEnterCount::EventMapEnterCount()
{
}

EventMapEnterCount::~EventMapEnterCount()
{
}

BOOL EventMapEnterCount::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("IllusionTempleLeague ODBC Connect Fail");
	return 0;
}

int EventMapEnterCount::GetEventMapEnterCount(char *CharName, char *BloodCastle, char *ChaosCastle, char *DevilSquare, char *DoppelGanger, char *ImperialGuardian_Weekdays, char *IllusionTempleRenewal)
{
	int result; // eax
	__int16 sqlReturn; // [esp+F8h] [ebp-2Ch]
	CString QueryStr; // [esp+104h] [ebp-20h]

	QueryStr.Format(
		"WZ_EventMapEnterCount_Get '%s'",
		CharName);
	if (this->m_DBQuery.Exec(QueryStr))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != 100 && sqlReturn != -1)
		{
			*BloodCastle = this->m_DBQuery.GetInt(1);
			*ChaosCastle = this->m_DBQuery.GetInt(2);
			*DevilSquare = this->m_DBQuery.GetInt(3);
			*DoppelGanger = this->m_DBQuery.GetInt(4);
			*ImperialGuardian_Weekdays = this->m_DBQuery.GetInt(5);
			*IllusionTempleRenewal = this->m_DBQuery.GetInt(6);
			this->m_DBQuery.Clear();
			result = 0;
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD(
				"error-L3 : [EventMapEnterCount] WZ_EventMapEnterCount_Get #2 %d %s %d",
				sqlReturn, __FILE__, __LINE__);
			result = -2;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD(
			"error-L3 : [EventMapEnterCount] WZ_EventMapEnterCount_Get #1 %s %d", __FILE__, __LINE__);
		result = -1;
	}
	return result;
}
// 5CDA8C: using guessed type int `EventMapEnterCount::GetEventMapEnterCount'::`2'::__LINE__Var;

//----- (0043A8E0) --------------------------------------------------------
int EventMapEnterCount::SetEventMapEnterCount(char *CharName, char BloodCastle, char ChaosCastle, char DevilSquare, char DoppelGanger, char ImperialGuardian_Weekdays, char IllusionTempleRenewal)
{
	int result;
	CString QueryStr;

	QueryStr.Format(
		"WZ_EventMapEnterCount_Set '%s', %d, %d, %d ,%d ,%d ,%d ",
		CharName,
		BloodCastle,
		ChaosCastle,
		DevilSquare,
		DoppelGanger,
		ImperialGuardian_Weekdays,
		IllusionTempleRenewal);
	if (this->m_DBQuery.Exec(QueryStr))
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD(
			"error-L3 : [EventMapEnterCount] WZ_EventMapEnterCount_Set #1 %s %d", __FILE__, __LINE__);
		result = 0;
	}
	return result;
}