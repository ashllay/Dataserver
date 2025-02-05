#include "StdAfx.h"
#include "DevilSquareFinalDBSet.h"

CDevilSquareFinalDBSet::CDevilSquareFinalDBSet()
{
}

CDevilSquareFinalDBSet::~CDevilSquareFinalDBSet()
{
}

BOOL CDevilSquareFinalDBSet::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("CDevilSquareFinalDBSet ODBC Connect Fail");
	return 0;
}

void CDevilSquareFinalDBSet::ReqCanPartyEnter(char *AccountID1, char *UserName1, char *AccountID2, char *UserName2, char btDSFType, int iEnterYear, BYTE btEnterMonth, BYTE btEnterDay, int *nEnterCount, int *nResult)
{
	__int16 sqlreturn; // [esp+D4h] [ebp-2Ch]
	CString qSql; // [esp+E0h] [ebp-20h]

	qSql.Format("WZ_DSF_CanPartyEnter '%s', '%s', '%s', '%s', %d, %d, %d, %d",
		AccountID1,
		UserName1,
		AccountID2,
		UserName2,
		btDSFType,
		iEnterYear,
		btEnterMonth,
		btEnterDay);
	if (this->m_DBQuery.Exec(qSql))
	{
		sqlreturn = this->m_DBQuery.Fetch();
		if (sqlreturn != 100 && sqlreturn != -1)
		{
			*nResult = this->m_DBQuery.GetInt("QueryResult");
			*nEnterCount = this->m_DBQuery.GetInt("mEnterCount");
			LogAddTD(
				"[DSF] AccountID1:%s, UserName1:%s, AccountID2:%s, UserName2:%s, Month/Day:%d/%d, EnterCount:%d",
				AccountID1,
				UserName1,
				AccountID2,
				UserName2,
				btEnterMonth,
				btEnterDay,
				*nEnterCount);
			this->m_DBQuery.Clear();
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD(
				"Error-L3 [WZ_DSF_CanPartyEnter]  %d Return %s,%d ",
				sqlreturn, __FILE__, __LINE__);
		}
	}
	else
	{
		LogAddC(
			2,
			"Error WZ_DSF_CanPartyEnter m_DBQuery.Exec %s %d", __FILE__, __LINE__);
		this->m_DBQuery.Clear();
	}
}
// 5CDA4C: using guessed type int `CDevilSquareFinalDBSet::ReqCanPartyEnter'::`2'::__LINE__Var;


void CDevilSquareFinalDBSet::UpdateDSFUserPoint(char *UserName, char *Gname, int DSFtype, int nPoint, int nEnterCount, int nWin)
{
	__int16 sqlReturn; 
	CString qSql;

	qSql.Format("WZ_DSF_UpdateUserPoint '%s', '%s', %d, %d, %d, %d",UserName,Gname,DSFtype,nPoint,nEnterCount,nWin);
	if (this->m_DBQuery.Exec(qSql))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != 100 && sqlReturn != -1)
		{
			this->m_DBQuery.Clear();
		}
		else
		{
			LogAddTD("Error-L2 [DevilSquareFinal] [WZ_DSF_UpdateUserPoint] %d, %s , %d",
				sqlReturn, __FILE__, __LINE__);
			this->m_DBQuery.Clear();
		}
	}
	else
	{
		LogAddTD("Error-L1 [DevilSquareFinal][WZ_DSF_UpdateUserPoint] NAME:%s,G.Name:%s,Point:%d,DSFType:%d,EnterCount:%d",
			UserName,Gname,nPoint,DSFtype,nEnterCount);
		this->m_DBQuery.Clear();
	}
}
// 5CDA50: using guessed type int `CDevilSquareFinalDBSet::UpdateDSFUserPoint'::`2'::__LINE__Var;

//----- (00439810) --------------------------------------------------------
void CDevilSquareFinalDBSet::SaveDSFPartyPoint(char *szAccountID1, char *szUserName1, int nUser1Level, char *szAccountID2, char *szUserName2, int nUser2Level, int nType, int nPoint, char btEnterCount, int nEnterYear, char btEnterMonth, char btEnterDay)
{
	__int16 sqlReturn;
	CString qSql; 

	qSql.Format("WZ_DSF_UpdatePartyPoint '%s', '%s', %d, '%s', '%s', %d, %d, %d, %d, %d, %d, %d",
		szAccountID1,
		szUserName1,
		nUser1Level,
		szAccountID2,
		szUserName2,
		nUser2Level,
		nType,
		nPoint,
		btEnterCount,
		nEnterYear,
		btEnterMonth,
		btEnterDay);
	if (this->m_DBQuery.Exec(qSql))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != 100 && sqlReturn != -1)
		{
			this->m_DBQuery.Clear();
		}
		else
		{
			LogAddTD(
				"Error-L2 [DevilSquareFinal] [WZ_DSF_UpdateGuildPoint] %d, %s, %d",
				sqlReturn, __FILE__, __LINE__);
			this->m_DBQuery.Clear();
		}
	}
	else
	{
		LogAddTD(
			"Error-L1[DevilSquareFinal][WZ_DSF_UpdateGuildPoint] AccountID1:[%s], UserName1:[%s], User1Level:[%d], AccountID2:["
			"%s], UserName2:[%s], User2Level:[%d], DSFType:[%d], Point:[%d]",
			szAccountID1,
			szUserName1,
			nUser1Level,
			szAccountID2,
			szUserName2,
			nUser2Level,
			nType,
			nPoint);
		this->m_DBQuery.Clear();
	}
}
// 5CDA54: using guessed type int `CDevilSquareFinalDBSet::SaveDSFPartyPoint'::`2'::__LINE__Var;


void CDevilSquareFinalDBSet::RenewDSFPartyRank(char btDSFType, int nYear, int nMonth, int nDay)
{
	CString qSql; // [esp+D4h] [ebp-20h]

	qSql.Format("WZ_DSF_RenewPartyRank %d, %d, %d, %d",btDSFType,nYear,nMonth,nDay);
	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
	}
	else
	{
		LogAddTD("Error-L1 [DevilSquareFinal][WZ_DSF_RenewPartyRank %d, %d, %d, %d]", btDSFType, nYear, nMonth, nDay);
		this->m_DBQuery.Clear();
	}
}

//----- (00439B40) --------------------------------------------------------
int CDevilSquareFinalDBSet::TodayDSFPartyRank(_stDSFPartyRankInfo *DSFRank, char *btCount, char btDSFType, int nYear, int nMonth, int nDay)
{
	int result;
	__int16 sqlRetrun;
	int nRank =0 ;
	char btPartyCount = 0;
	CString qSql; 
	qSql.Format("WZ_DSF_GetTodayGuildRank %d, %d, %d, %d",btDSFType,nYear,nMonth,nDay);
	if (this->m_DBQuery.Exec(qSql))
	{
		for (sqlRetrun = this->m_DBQuery.Fetch(); sqlRetrun != 100; sqlRetrun = this->m_DBQuery.Fetch())
		{
			if (sqlRetrun == -1)
				break;
			++nRank;
			DSFRank[btPartyCount].btRank = this->m_DBQuery.GetInt("mRank");
			this->m_DBQuery.GetStr("mUserName1", DSFRank[btPartyCount].szUserName1);
			this->m_DBQuery.GetStr("mUserName2", DSFRank[btPartyCount].szUserName2);
			DSFRank[btPartyCount].btDSFType = btDSFType;
			DSFRank[btPartyCount++].iPoint = this->m_DBQuery.GetInt("mPoint");
			if (btPartyCount >= 20)
				break;
		}
		*btCount = btPartyCount;
		this->m_DBQuery.Clear();
		result = 0;
	}
	else
	{
		LogAddC(2,"Error WZ_DSF_GetTodayPartyRank m_DBQuery.Exec %s %d", __FILE__, __LINE__);
		this->m_DBQuery.Clear();
		result = -1;
	}
	return result;
}
// 5CDA58: using guessed type int `CDevilSquareFinalDBSet::TodayDSFPartyRank'::`2'::__LINE__Var;


int CDevilSquareFinalDBSet::DSFGoFinalParty(_stDSFGoFinalPartyInfo* DSFRank, unsigned char& btCount, unsigned char btDSFType, int nYear, int nMonth, int nDay)
{
	int result; 
	__int16 sqlRetrun;
	int nRank = 0;
	char btPartyCount = 0;
	CString qSql;

	qSql.Format("WZ_DSF_GetFinalPartyList %d, %d, %d, %d",btDSFType,nYear,nMonth,nDay);
	if (this->m_DBQuery.Exec(qSql))
	{
		for (sqlRetrun = this->m_DBQuery.Fetch();
			sqlRetrun != 100 && sqlRetrun != -1;
			sqlRetrun = this->m_DBQuery.Fetch())
		{
			++nRank;
			DSFRank[btPartyCount].btRank = this->m_DBQuery.GetInt("mRank");
			this->m_DBQuery.GetStr("mUserName1", DSFRank[btPartyCount].szUserName1);
			this->m_DBQuery.GetStr("mUserName2", DSFRank[btPartyCount].szUserName2);
			DSFRank[btPartyCount].wServerCode1 = this->m_DBQuery.GetInt("mServerCode1");
			DSFRank[btPartyCount].wServerCode2 = this->m_DBQuery.GetInt("mServerCode2");
			DSFRank[btPartyCount].btDSFType = btDSFType;
			DSFRank[btPartyCount].iPoint = this->m_DBQuery.GetInt("mPoint");
			DSFRank[btPartyCount].nEnterYear = this->m_DBQuery.GetInt("mEnterYear");
			DSFRank[btPartyCount].btEnterMonth = this->m_DBQuery.GetInt("mEnterMonth");
			DSFRank[btPartyCount++].btEnterDay = this->m_DBQuery.GetInt("mEnterDay");
		}
		btCount = btPartyCount;
		this->m_DBQuery.Clear();
		result = 0;
	}
	else
	{
		LogAddC(2,"Error WZ_DSF_GetFinalPartyList m_DBQuery.Exec %s %d", __FILE__, __LINE__);
		this->m_DBQuery.Clear();
		result = -1;
	}
	return result;
}
// 5CDA5C: using guessed type int `CDevilSquareFinalDBSet::DSFGoFinalParty'::`2'::__LINE__Var;


void CDevilSquareFinalDBSet::InsertRewardUser(char *szAccountID, char *szUserName, int iClass, int nDSFType, int nRewardYear, char btRewardMonth, char btRewardStartDay, char btRewardEndDay)
{
	__int16 sqlReturn;
	CString qSql;

	qSql.Format("WZ_DSF_InsertRewardUser '%s', '%s', %d, %d, %d, %d, %d, %d",
		szAccountID,
		szUserName,
		iClass,
		nDSFType,
		nRewardYear,
		btRewardMonth,
		btRewardStartDay,
		btRewardEndDay);
	if (this->m_DBQuery.Exec(qSql))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != 100 && sqlReturn != -1)
		{
			this->m_DBQuery.Clear();
		}
		else
		{
			LogAddTD(
				"Error-L2 [DevilSquareFinal][WZ_DSF_InsertRewardUser] %d, %s, %d",
				sqlReturn, __FILE__, __LINE__);
			this->m_DBQuery.Clear();
		}
	}
	else
	{
		LogAddTD(
			"Error-L1[DevilSquareFinal][WZ_DSF_InsertRewardUser] AccountID:[%s], UserName:[%s], UserClass:[%d], DSFType:[%d]",
			szAccountID,
			szUserName,
			iClass,
			nDSFType);
		this->m_DBQuery.Clear();
	}
}
// 5CDA60: using guessed type int `CDevilSquareFinalDBSet::InsertRewardUser'::`2'::__LINE__Var;

//----- (0043A280) --------------------------------------------------------
int CDevilSquareFinalDBSet::GetReward(char *szAccountID, char *szUserName, int nServerCode, int nRewardYear, char btRewardMonth, char btRewardDay)
{
	int result;
	__int16 sqlReturn;
	int nRetrun;
	char btPartyCount = 0; 
	CString qSql;
	qSql.Format("WZ_DSF_GetReward '%s', '%s', %d, %d, %d, %d",szAccountID,szUserName,nServerCode,nRewardYear,btRewardMonth,btRewardDay);
	if (this->m_DBQuery.Exec(qSql))
	{
		nRetrun = -1;
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn != 100 && sqlReturn != -1)
		{
			nRetrun = this->m_DBQuery.GetInt(1);
			this->m_DBQuery.Clear();
			result = nRetrun;
		}
		else
		{
			LogAddTD("Error-L2 [DevilSquareFinal] [WZ_DSF_GetReward] %d, %s, %d",sqlReturn, __FILE__, __LINE__);
			this->m_DBQuery.Clear();
			result = nRetrun;
		}
	}
	else
	{
		LogAddC(2,"Error WZ_DSF_GetReward m_DBQuery.Exec %s %d", __FILE__, __LINE__);
		this->m_DBQuery.Clear();
		result = -1;
	}
	return result;
}