#include "StdAfx.h"
#include "HuntingRecordDBSet.h"

CHuntingRecordDBSet::CHuntingRecordDBSet()
{
}

CHuntingRecordDBSet::~CHuntingRecordDBSet()
{
}

BOOL CHuntingRecordDBSet::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass) == FALSE)
	{
		MsgBox("CHuntingRecordDBSet ODBC Connect Fail");
		return FALSE;
	}
	return TRUE;
}

int CHuntingRecordDBSet::LoadHuntingRecordInfo(char* szAccountID, char* Name, HUNTING_RECORD_INFO* pHuntingRecordInfo, SDHP_ANS_HUNTING_RECORD_COUNT* pMsg, int iMapIndex)
{
	__int16 sqlRet;
	CString szQuery;
	char szName[MAX_IDSTRING+1];
	char szId[MAX_IDSTRING+1];

	szId[MAX_IDSTRING] = 0;
	memcpy(szId, szAccountID, MAX_IDSTRING);

	if (strlen(szId) && (strlen(szId) <= MAX_IDSTRING))
	{
		szName[MAX_IDSTRING] = 0;
		memcpy(szName, Name, MAX_IDSTRING);

		if (strlen(szName) && (strlen(szName) <= MAX_IDSTRING))
		{
			int iCnt = 0;

			szQuery.Format("WZ_HuntingRecordLoad '%s', '%s', %d", szAccountID, Name, iMapIndex);

			if (this->m_DBQuery.Exec(szQuery))
			{
				for (sqlRet = this->m_DBQuery.Fetch(); sqlRet != SQL_NO_DATA; sqlRet = this->m_DBQuery.Fetch())
				{
					if (sqlRet == SQL_NULL_DATA)
						break;
					pHuntingRecordInfo[iCnt].btMapIndex = this->m_DBQuery.GetInt("MapIndex");
					pHuntingRecordInfo[iCnt].iYear = this->m_DBQuery.GetInt("mYear");
					pHuntingRecordInfo[iCnt].btMonth = this->m_DBQuery.GetInt("mMonth");
					pHuntingRecordInfo[iCnt].btDay = this->m_DBQuery.GetInt("mDay");
					pHuntingRecordInfo[iCnt].iCurrentLevel = this->m_DBQuery.GetInt("CurrentLevel");
					pHuntingRecordInfo[iCnt].iHuntingAccrueSecond = this->m_DBQuery.GetInt("HuntingAccrueSecond");
					pHuntingRecordInfo[iCnt].i64NormalAccrueDamage = this->m_DBQuery.GetInt64("NormalAccrueDamage");
					pHuntingRecordInfo[iCnt].i64PentagramAccrueDamage = this->m_DBQuery.GetInt64("PentagramAccrueDamage");
					pHuntingRecordInfo[iCnt].iHealAccrueValue = this->m_DBQuery.GetInt("HealAccrueValue");
					pHuntingRecordInfo[iCnt].iMonsterKillCount = this->m_DBQuery.GetInt("MonsterKillCount");
					pHuntingRecordInfo[iCnt].i64AccrueExp = this->m_DBQuery.GetInt64("AccrueExp");
					pHuntingRecordInfo[iCnt].iClass = this->m_DBQuery.GetInt("Class");
					pHuntingRecordInfo[iCnt].iMaxNormalDamage = this->m_DBQuery.GetInt("MaxNormalDamage");
					pHuntingRecordInfo[iCnt].iMinNormalDamage = this->m_DBQuery.GetInt("MinNormalDamage");
					pHuntingRecordInfo[iCnt].iMaxPentagramDamage = this->m_DBQuery.GetInt("MaxPentagramDamage");
					pHuntingRecordInfo[iCnt].iMinPentagramDamage = this->m_DBQuery.GetInt("MinPentagramDamage");
					pHuntingRecordInfo[iCnt].iGetNormalAccrueDamage = this->m_DBQuery.GetInt("GetNormalAccrueDamage");
					pHuntingRecordInfo[iCnt].iGetPentagramAccrueDamage = this->m_DBQuery.GetInt("GetPentagramAccrueDamage");

					if (++iCnt >= MAX_HUNTING_RECORD_MAP_LIST)
						break;
				}
				pMsg->btListCnt = iCnt;
				this->m_DBQuery.Clear();
				return 0;
			}
			else
			{
				LogAddC(2, "LoadHuntingRecordInfo Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				return 1;
			}
		}
		else
		{
			LogAddC(2, "%s] ?มี +ํภ?%s %d", szName, __FILE__, __LINE__);
			return 1;
		}
	}
	LogAddC(2, "%s] ?มี +ํภ?%s %d", szId, __FILE__, __LINE__);
	return 1;
}


int CHuntingRecordDBSet::HuntingRecordInfoSave(SDHP_REQ_HUNTING_RECORD_INFO_SAVE *lpRecv)
{
	int nOfs = sizeof(SDHP_REQ_HUNTING_RECORD_INFO_SAVE);
	char szName[MAX_IDSTRING + 1] = { 0 };
	char szId[MAX_IDSTRING + 1] = { 0 };

	if (strlen(lpRecv->AccountId) > MAX_IDSTRING || strlen(lpRecv->szName) > MAX_IDSTRING)
	{
		LogAddC(2, "Invalid AccountId or Name length");
		return 1;
	}

	memcpy(szId, lpRecv->AccountId, MAX_IDSTRING);
	memcpy(szName, lpRecv->szName, MAX_IDSTRING);

	if (lpRecv->btListCnt <= 0 || lpRecv->btListCnt > MAX_HUNTING_RECORD_MAP_LIST)
	{
		LogAddC(2, "Invalid btListCnt=%d for AccountId=%s, Name=%s", lpRecv->btListCnt, szId, szName);
		return 1;
	}

	BYTE* lpBuffer = (BYTE*)lpRecv;
	HUNTING_RECORD_INFO* RecvBuf = (HUNTING_RECORD_INFO*)(lpBuffer + nOfs);

	for (int i = 0; i < lpRecv->btListCnt; ++i)
	{
#ifdef _DEBUG
		LogAddC(3, "Saving record %d: MapIndex=%d, Year=%d, Damage=%lld",
			i, RecvBuf[i].btMapIndex, RecvBuf[i].iYear, RecvBuf[i].i64NormalAccrueDamage);
#endif
		CString szQuery;
		szQuery.Format("WZ_HuntingRecordInfoSave '%s', '%s', %d, %d, %d, %d, %d, %d, %I64d, %I64d, %d, %d, %I64d, %d, %d, %d, %d, %d, %d, %d",
			szId, szName, RecvBuf[i].btMapIndex, RecvBuf[i].iYear, RecvBuf[i].btMonth, RecvBuf[i].btDay,
			RecvBuf[i].iCurrentLevel, RecvBuf[i].iHuntingAccrueSecond, RecvBuf[i].i64NormalAccrueDamage,
			RecvBuf[i].i64PentagramAccrueDamage, RecvBuf[i].iHealAccrueValue, RecvBuf[i].iMonsterKillCount,
			RecvBuf[i].i64AccrueExp, RecvBuf[i].iClass, RecvBuf[i].iMaxNormalDamage, RecvBuf[i].iMinNormalDamage,
			RecvBuf[i].iMaxPentagramDamage, RecvBuf[i].iMinPentagramDamage, RecvBuf[i].iGetNormalAccrueDamage,
			RecvBuf[i].iGetPentagramAccrueDamage);

		if (!this->m_DBQuery.Exec(szQuery))
		{
			LogAddC(2, "SQL Query Failed: %s", szQuery);
			this->m_DBQuery.Clear();
			return 1;
		}
		this->m_DBQuery.Clear();
	}

	return 0;
}
// 5CDC14: using guessed type int `CHuntingRecordDBSet::HuntingRecordInfoSave'::`2'::__LINE__Var;


int CHuntingRecordDBSet::LoadHuntingRecordInfoUserOpen(char* szAccountID, char* Name, SDHP_ANS_HUNTING_RECORD_INFO_USER_OPEN* pMsg)
{
	CString szQuery;
	char szName[MAX_IDSTRING + 1];
	char szId[MAX_IDSTRING + 1];

	szId[MAX_IDSTRING] = 0;
	memcpy(szId, szAccountID, MAX_IDSTRING);

	if (strlen(szId) && (strlen(szId) <= MAX_IDSTRING))
	{
		szName[MAX_IDSTRING] = 0;
		memcpy(szName, Name, MAX_IDSTRING);

		if (strlen(szName) && (strlen(szName) <= MAX_IDSTRING))
		{
			szQuery.Format("WZ_HuntingRecordInfoUserOpenLoad '%s', '%s'", szAccountID, Name);
			if (this->m_DBQuery.Exec(szQuery))
			{
				if (this->m_DBQuery.Fetch() == SQL_NO_DATA)
				{
					LogAddTD("[CHuntingRecordDBSet][Load] HuntingRecordInfoUserOpen Load Error : Fetch() Error");
					this->m_DBQuery.Clear();
					return 1;
				}
				else
				{
					pMsg->btOpen = this->m_DBQuery.GetInt("UserOpen");
					this->m_DBQuery.Clear();
					return 0;
				}
			}
			else
			{
				LogAddTD("[CHuntingRecordDBSet][Load] HuntingRecordInfoUserOpen Load Error : Exec(szQuery) Error");
				this->m_DBQuery.Clear();
				return 1;
			}
		}
		else
		{
			LogAddC(2, "%s] ?มี +ํภ?%s %d", szName, __FILE__, __LINE__);
			return 1;
		}
	}
	LogAddC(2, "%s] ?มี +ํภ?%s %d", szId, __FILE__, __LINE__);
	return 1;
}
// 5CDC18: using guessed type int `CHuntingRecordDBSet::LoadHuntingRecordInfoUserOpen'::`2'::__LINE__Var;

int CHuntingRecordDBSet::HuntingRecordInfoUserOpenSave(SDHP_REQ_HUNTING_RECORD_INFO_USER_OPEN_SAVE* lpRecv)
{
	int iReturnValue;
	CString szQuery;
	char szName[MAX_IDSTRING + 1];
	char szId[MAX_IDSTRING + 1];

	szId[MAX_IDSTRING] = 0;
	memcpy(szId, lpRecv->AccountId, MAX_IDSTRING);

	if (strlen(szId) && (strlen(szId) <= MAX_IDSTRING))
	{
		szName[MAX_IDSTRING] = 0;
		memcpy(szName, lpRecv->szName, MAX_IDSTRING);

		if (strlen(szName) && (strlen(szName) <= MAX_IDSTRING))
		{
			iReturnValue = 0;
			szQuery.Format("WZ_HuntingRecordInfoUserOpenSave '%s', '%s', %d", szId, szName, lpRecv->btOpen);
			if (!this->m_DBQuery.Exec(szQuery))
			{
				LogAddC(2, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				iReturnValue = 1;
			}
			this->m_DBQuery.Clear();
			return iReturnValue;
		}
		else
		{
			LogAddC(2, "%s] +??+ํภ?%s %d", szName, __FILE__, __LINE__);
			return 1;
		}
	}
	LogAddC(2, "%s] +??+ํภ?%s %d", szId, __FILE__, __LINE__);
	return 1;
}
// 5CDC1C: using guessed type int `CHuntingRecordDBSet::HuntingRecordInfoUserOpenSave'::`2'::__LINE__Var;

int CHuntingRecordDBSet::LoadHuntingRecordInfo_Current(char* szAccountID, char* Name, SDHP_ANS_HUNTING_RECORD_INFO_CURRENT* pMsg, int iMapIndex, int iYear, char btMonth, char btDay)
{
	__int16 sqlRet;
	CString szQuery;
	int iCnt;
	char szName[MAX_IDSTRING + 1];
	char szId[MAX_IDSTRING + 1];


	szId[MAX_IDSTRING] = 0;
	memcpy(szId, szAccountID, MAX_IDSTRING);

	if (strlen(szId) && (strlen(szId) <= MAX_IDSTRING))
	{
		szName[MAX_IDSTRING] = 0;
		memcpy(szName, Name, MAX_IDSTRING);

		if (strlen(szName) && (strlen(szName) <= MAX_IDSTRING))
		{
			iCnt = 0;

			szQuery.Format("WZ_HuntingRecordLoad_Current '%s', '%s', %d, %d, %d, %d", szId, szName, iMapIndex, iYear, btMonth, btDay);

			if (this->m_DBQuery.Exec(szQuery))
			{
				for (sqlRet = this->m_DBQuery.Fetch(); sqlRet != 100; sqlRet = this->m_DBQuery.Fetch())
				{
					if (sqlRet == -1)
						break;
					pMsg->btMapIndex = this->m_DBQuery.GetInt("MapIndex");
					pMsg->iYear = this->m_DBQuery.GetInt("mYear");
					pMsg->btMonth = this->m_DBQuery.GetInt("mMonth");
					pMsg->btDay = this->m_DBQuery.GetInt("mDay");
					pMsg->iCurrentLevel = this->m_DBQuery.GetInt("CurrentLevel");
					pMsg->iHuntingAccrueSecond = this->m_DBQuery.GetInt("HuntingAccrueSecond");
					pMsg->i64NormalAccrueDamage = this->m_DBQuery.GetInt64("NormalAccrueDamage");
					pMsg->i64PentagramAccrueDamage = this->m_DBQuery.GetInt64("PentagramAccrueDamage");
					pMsg->iHealAccrueValue = this->m_DBQuery.GetInt("HealAccrueValue");
					pMsg->iMonsterKillCount = this->m_DBQuery.GetInt("MonsterKillCount");
					pMsg->i64AccrueExp = this->m_DBQuery.GetInt64("AccrueExp");
					pMsg->iClass = this->m_DBQuery.GetInt("Class");
					pMsg->iMaxNormalDamage = this->m_DBQuery.GetInt("MaxNormalDamage");
					pMsg->iMinNormalDamage = this->m_DBQuery.GetInt("MinNormalDamage");
					pMsg->iMaxPentagramDamage = this->m_DBQuery.GetInt("MaxPentagramDamage");
					pMsg->iMinPentagramDamage = this->m_DBQuery.GetInt("MinPentagramDamage");
					pMsg->iGetNormalAccrueDamage = this->m_DBQuery.GetInt("GetNormalAccrueDamage");
					pMsg->iGetPentagramAccrueDamage = this->m_DBQuery.GetInt("GetPentagramAccrueDamage");

					if (++iCnt >= MAX_HUNTING_RECORD_MAP_LIST)
						break;
				}
				pMsg->btListCnt = iCnt;
				this->m_DBQuery.Clear();

				return 0;
			}
			else
			{
				LogAddC(2, "LoadHuntingRecordInfo_Current Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				return 1;
			}
		}
		else
		{
			LogAddC(2, "%s] ?มี +ํภ?%s %d", szName, __FILE__, __LINE__);
			return 1;
		}
	}
	LogAddC(2, "%s] ?มี +ํภ?%s %d", szId, __FILE__, __LINE__);
	return 1;
}
// 5CDC20: using guessed type int `CHuntingRecordDBSet::LoadHuntingRecordInfo_Current'::`2'::__LINE__Var;

int CHuntingRecordDBSet::DeleteHuntingRecordInfo(char* szAccountID, char* Name, int iMapIndex, int iYear, char btMonth, char btDay)
{
	CString szQuery;
	char szName[MAX_IDSTRING + 1];
	char szId[MAX_IDSTRING + 1];

	szId[MAX_IDSTRING] = 0;
	memcpy(szId, szAccountID, MAX_IDSTRING);

	if (strlen(szId) && (strlen(szId) <= MAX_IDSTRING))
	{
		szName[MAX_IDSTRING] = 0;
		memcpy(szName, Name, MAX_IDSTRING);

		if (strlen(szName) && (strlen(szName) <= MAX_IDSTRING))
		{

			if (iYear)
			{
				szQuery.Format("WZ_HuntingRecordDelete '%s', '%s', %d, %d, %d, %d", szId, szName, iMapIndex, iYear, btMonth, btDay);
			}
			else
			{
				szQuery.Format("WZ_HuntingRecordDeleteMapAll '%s', '%s', %d", szId, szName, iMapIndex);
			}

			if (this->m_DBQuery.Exec(szQuery))
			{
				this->m_DBQuery.Clear();
				return 0;
			}
			else
			{
				LogAddC(2, "DeleteHuntingRecordInfo Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				return 1;
			}
		}
		else
		{
			LogAddC(2, "%s] ?มี +ํภ?%s %d", szName, __FILE__, __LINE__);
			return 1;
		}
	}
	LogAddC(2, "%s] ?มี +ํภ?%s %d", szId, __FILE__, __LINE__);
	return 1;
}