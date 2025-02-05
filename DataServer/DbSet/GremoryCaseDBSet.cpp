#include "stdafx.h"
#include "GremoryCaseDBSet.h"
#include "..\MainFrm.h"

CGremoryCaseSerial gGremoryCaseSerial;

CGremoryCaseDBSet::CGremoryCaseDBSet()
{
}

CGremoryCaseDBSet::~CGremoryCaseDBSet()
{
}

BOOL CGremoryCaseDBSet::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass) == FALSE)
	{
		MsgBox("CGremoryCaseDBSet ODBC Connect Fail");
		return FALSE;
	}

	return TRUE;
}

int CGremoryCaseDBSet::GetItemSerial(DWORD &sirial_number, int MakeSeiralCount)
{
	CString strQuery;

	sirial_number = 0;
	strQuery.Format("WZ_GremoryCaseSerial '%d'", MakeSeiralCount);
	this->m_DBQuery.Exec(strQuery);
	if (this->m_DBQuery.Fetch() == SQL_NO_DATA)
	{
		this->m_DBQuery.Clear();
		return 0;
	}
	sirial_number = this->m_DBQuery.GetInt64(1);
	LogAdd("[GetGremoriCaseSerial] Get Last Item Serial from DB : %u", sirial_number);
	this->m_DBQuery.Clear();
	return 1;
}

int CGremoryCaseDBSet::InsertGremoryCase(char* szAccountID, char* szName, char btGCType, char btGiveType, char btItemType, WORD wItemIndex, char btLevel, char btDur, char btSkill, char btLuck, char btOpt, char btSetOpt, WORD wNewOpt, char btBonusSocketOpt, BYTE* btSocketOpt, unsigned int dwReceiptExpireDuration, unsigned int dwItemDuration, int lRecvDate, int lRecvExpireDate, int lItemExpireDate, unsigned int* dwSerial)
{
	char Ret;
	CString QueryStr;

	*dwSerial = gGremoryCaseSerial.GetSerial();

	QueryStr.Format("EXEC WZ_GremoryCaseInsert %d,%d, '%s','%s', %d,%d,%d,%d,%d,%d,%d,%d,%d, %d,%d,%d,%d,%d,%d, %u, %u,%u, %u,%u,%u", btGCType, btGiveType, szAccountID, szName, btItemType, wItemIndex, btLevel, btDur, btSkill, btLuck, btOpt, btSetOpt, wNewOpt, btBonusSocketOpt, *btSocketOpt, btSocketOpt[1], btSocketOpt[2], btSocketOpt[3], btSocketOpt[4], *dwSerial, dwReceiptExpireDuration, dwItemDuration, lRecvDate, lRecvExpireDate, lItemExpireDate);

	if (this->m_DBQuery.Exec(QueryStr))
	{
		if (this->m_DBQuery.Fetch() == SQL_NO_DATA)
		{
			this->m_DBQuery.Clear();
			return 0;
		}
		else
		{
			Ret = this->m_DBQuery.GetInt(1);
			this->m_DBQuery.Clear();
			return Ret;
		}
	}
	this->m_DBQuery.Clear();
	LogAddTD("error-L3 : [GremoryCase] InsertGremoryCase #1 [%s][%s] %s %d", szAccountID, szName, __FILE__, __LINE__);
	return 0;
}
// 5CDB04: using guessed type int `CGremoryCaseDBSet::InsertGremoryCase'::`2'::__LINE__Var;

int CGremoryCaseDBSet::SelectGremoryCase(char* szAccountID, char* szName, _stGremoryCaseList* pGCList, char* btListCnt)
{
	__int16 sqlRetrun;
	int iGC_ChCnt;
	int iGC_AcCnt;
	CString QueryStr;

	QueryStr.Format("EXEC WZ_GremoryCaseChkLimitedCnt '%s', '%s', %d", szAccountID, szName, 1);

	if (this->m_DBQuery.Exec(QueryStr))
	{
		this->m_DBQuery.Clear();

		QueryStr.Format("EXEC WZ_GremoryCaseChkLimitedCnt '%s', '%s', %d", szAccountID, szName, 2);

		if (this->m_DBQuery.Exec(QueryStr))
		{
			this->m_DBQuery.Clear();

			QueryStr.Format("EXEC WZ_GremoryCaseSelect '%s', '%s', %d", szAccountID, szName, 1);

			if (this->m_DBQuery.Exec(QueryStr))
			{
				iGC_AcCnt = 0;
				iGC_ChCnt = 0;
				for (sqlRetrun = this->m_DBQuery.Fetch();
					sqlRetrun != SQL_NO_DATA && sqlRetrun != SQL_NULL_DATA;
					sqlRetrun = this->m_DBQuery.Fetch())
				{
					if (++iGC_AcCnt > 50)
					{
						this->m_DBQuery.Clear();
						LogAddTD("error-L3 : [GremoryCase] higher than MAX_GC_ACCOUNT [%s][%s] %s %d", szAccountID, szName, __FILE__, __LINE__);
						break;
					}
					pGCList[*btListCnt].btGCType = this->m_DBQuery.GetInt("GCType");
					pGCList[*btListCnt].btGiveType = this->m_DBQuery.GetInt("GiveType");
					pGCList[*btListCnt].btItemType = this->m_DBQuery.GetInt("ItemType");
					pGCList[*btListCnt].wItemIndex = this->m_DBQuery.GetInt("ItemIndex");
					pGCList[*btListCnt].btLevel = this->m_DBQuery.GetInt("Level");
					pGCList[*btListCnt].btDur = this->m_DBQuery.GetInt("ItemDur");
					pGCList[*btListCnt].btSkill = this->m_DBQuery.GetInt("Skill");
					pGCList[*btListCnt].btLuck = this->m_DBQuery.GetInt("Luck");
					pGCList[*btListCnt].btOpt = this->m_DBQuery.GetInt("Opt");
					pGCList[*btListCnt].btSetOpt = this->m_DBQuery.GetInt("SetOpt");
					pGCList[*btListCnt].wNewOpt = this->m_DBQuery.GetInt("NewOpt");
					pGCList[*btListCnt].btBonusSocketOpt = this->m_DBQuery.GetInt("BonusSocketOpt");
					pGCList[*btListCnt].btSocketOpt[0] = this->m_DBQuery.GetInt("SocketOpt1");
					pGCList[*btListCnt].btSocketOpt[1] = this->m_DBQuery.GetInt("SocketOpt2");
					pGCList[*btListCnt].btSocketOpt[2] = this->m_DBQuery.GetInt("SocketOpt3");
					pGCList[*btListCnt].btSocketOpt[3] = this->m_DBQuery.GetInt("SocketOpt4");
					pGCList[*btListCnt].btSocketOpt[4] = this->m_DBQuery.GetInt("SocketOpt5");
					pGCList[*btListCnt].dwSerial = this->m_DBQuery.GetInt64("Serial");
					pGCList[*btListCnt].lRecvDate = this->m_DBQuery.GetInt("RecvDateConvert");
					pGCList[*btListCnt].lRecvExpireDate = this->m_DBQuery.GetInt("RecvExpireDateConvert");
					pGCList[(*btListCnt)++].lItemExpireDate = this->m_DBQuery.GetInt("ItemExpireDateConvert");
				}
				this->m_DBQuery.Clear();

				QueryStr.Format("EXEC WZ_GremoryCaseSelect '%s', '%s', %d", szAccountID, szName, 2);

				if (this->m_DBQuery.Exec(QueryStr))
				{
					for (sqlRetrun = this->m_DBQuery.Fetch();
						sqlRetrun != SQL_NO_DATA && sqlRetrun != SQL_NULL_DATA;
						sqlRetrun = this->m_DBQuery.Fetch())
					{
						if (++iGC_ChCnt > 50)
						{
							this->m_DBQuery.Clear();
							LogAddTD("error-L3 : [GremoryCase] higher than MAX_GC_CHAR [%s][%s] %s %d", szAccountID, szName, __FILE__, __LINE__);
							break;
						}
						pGCList[*btListCnt].btGCType = this->m_DBQuery.GetInt("GCType");
						pGCList[*btListCnt].btGiveType = this->m_DBQuery.GetInt("GiveType");
						pGCList[*btListCnt].btItemType = this->m_DBQuery.GetInt("ItemType");
						pGCList[*btListCnt].wItemIndex = this->m_DBQuery.GetInt("ItemIndex");
						pGCList[*btListCnt].btLevel = this->m_DBQuery.GetInt("Level");
						pGCList[*btListCnt].btDur = this->m_DBQuery.GetInt("ItemDur");
						pGCList[*btListCnt].btSkill = this->m_DBQuery.GetInt("Skill");
						pGCList[*btListCnt].btLuck = this->m_DBQuery.GetInt("Luck");
						pGCList[*btListCnt].btOpt = this->m_DBQuery.GetInt("Opt");
						pGCList[*btListCnt].btSetOpt = this->m_DBQuery.GetInt("SetOpt");
						pGCList[*btListCnt].wNewOpt = this->m_DBQuery.GetInt("NewOpt");
						pGCList[*btListCnt].btBonusSocketOpt = this->m_DBQuery.GetInt("BonusSocketOpt");
						pGCList[*btListCnt].btSocketOpt[0] = this->m_DBQuery.GetInt("SocketOpt1");
						pGCList[*btListCnt].btSocketOpt[1] = this->m_DBQuery.GetInt("SocketOpt2");
						pGCList[*btListCnt].btSocketOpt[2] = this->m_DBQuery.GetInt("SocketOpt3");
						pGCList[*btListCnt].btSocketOpt[3] = this->m_DBQuery.GetInt("SocketOpt4");
						pGCList[*btListCnt].btSocketOpt[4] = this->m_DBQuery.GetInt("SocketOpt5");
						pGCList[*btListCnt].dwSerial = this->m_DBQuery.GetInt64("Serial");
						pGCList[*btListCnt].lRecvDate = this->m_DBQuery.GetInt("RecvDateConvert");
						pGCList[*btListCnt].lRecvExpireDate = this->m_DBQuery.GetInt("RecvExpireDateConvert");
						pGCList[(*btListCnt)++].lItemExpireDate = this->m_DBQuery.GetInt("ItemExpireDateConvert");
					}
					this->m_DBQuery.Clear();
					return 1;
				}
				else
				{
					this->m_DBQuery.Clear();
					LogAddTD("error-L3 : [GremoryCase] SelectGremoryCase #4 [%s][%s] %s %d", szAccountID, szName, __FILE__, __LINE__);
					return 0;
				}
			}
			else
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [GremoryCase] SelectGremoryCase #3 [%s][%s] %s %d", szAccountID, szName, __FILE__, __LINE__);
				return 0;
			}
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [GremoryCase] SelectGremoryCase #2 [%s][%s] %s %d", szAccountID, szName, __FILE__, __LINE__);
			return 0;
		}
	}
	this->m_DBQuery.Clear();
	LogAddTD("error-L3 : [GremoryCase] SelectGremoryCase #1 [%s][%s] %s %d", szAccountID, szName, __FILE__, __LINE__);
	return 0;
}
// 5CDB08: using guessed type int `CGremoryCaseDBSet::SelectGremoryCase'::`2'::__LINE__Var;

int CGremoryCaseDBSet::UpdateGremoryCase(char* szAccountID, char* szName, char btGCType, char btItemType, WORD wItemIndex, char btLevel, unsigned int dwSerial, int lRecvDate, char btUsedInfo)
{
	char Ret;
	CString QueryStr;

	QueryStr.Format("EXEC WZ_GremoryCaseDelete %d, '%s','%s', %d,%d,%d, %u,%u, %d", btGCType, szAccountID, szName, btItemType, wItemIndex, btLevel, dwSerial, lRecvDate, btUsedInfo);

	if (this->m_DBQuery.Exec(QueryStr))
	{
		if (this->m_DBQuery.Fetch() == SQL_NO_DATA)
		{
			this->m_DBQuery.Clear();
			return 0;
		}
		else
		{
			Ret = this->m_DBQuery.GetInt(1);
			this->m_DBQuery.Clear();
			return Ret;
		}
	}
	this->m_DBQuery.Clear();
	LogAddTD("error-L3 : [GremoryCase] UpdateGremoryCase #1 [%s][%s] %s %d", szAccountID, szName, __FILE__, __LINE__);
	return 0;
}
// 5CDB0C: using guessed type int `CGremoryCaseDBSet::UpdateGremoryCase'::`2'::__LINE__Var;

int CGremoryCaseDBSet::UpdateGremoryCaseItemRecv(char* szAccountID, char* szName, char btGCType, char btItemType, WORD wItemIndex, char btLevel, unsigned int dwSerial, int lRecvDate, char btUsedInfo)
{
	char Ret;
	CString QueryStr;

	QueryStr.Format("EXEC WZ_GremoryCaseItemRecv %d, '%s','%s', %d,%d,%d, %u,%u, %d", btGCType, szAccountID, szName, btItemType, wItemIndex, btLevel, dwSerial, lRecvDate, btUsedInfo);

	if (this->m_DBQuery.Exec(QueryStr))
	{
		if (this->m_DBQuery.Fetch() == SQL_NO_DATA)
		{
			this->m_DBQuery.Clear();
			return 0;
		}
		else
		{
			Ret = this->m_DBQuery.GetInt(1);
			this->m_DBQuery.Clear();
			return Ret;
		}
	}
	this->m_DBQuery.Clear();
	LogAddTD("error-L3 : [GremoryCase] UpdateGremoryCaseItemRecv #1 [%s][%s] %s %d", szAccountID, szName, __FILE__, __LINE__);
	return 0;
}

CGremoryCaseSerial::CGremoryCaseSerial()
{
	this->m_dwGCItemSerial = 0;
	this->m_dwGCLastSerial = 0;
	InitializeCriticalSection(&this->m_csGCItemSerial);
}

CGremoryCaseSerial::~CGremoryCaseSerial()
{
	DeleteCriticalSection(&this->m_csGCItemSerial);
}

int CGremoryCaseSerial::MakeSerial()
{
	if (!g_CGremoryCaseDBSet.GetItemSerial(this->m_dwGCItemSerial, 3000))
	{
		return 0;
	}
	this->m_dwGCLastSerial = this->m_dwGCItemSerial + 3000;
	return 1;
}

//----- (0043B360) --------------------------------------------------------
unsigned int CGremoryCaseSerial::GetSerial()
{
	unsigned int retserial;

	EnterCriticalSection(&this->m_csGCItemSerial);
	if (this->m_dwGCItemSerial >= this->m_dwGCLastSerial)
	{
		MakeSerial();
	}

	retserial = this->m_dwGCItemSerial++;
	LeaveCriticalSection(&this->m_csGCItemSerial);
	return retserial;
}
