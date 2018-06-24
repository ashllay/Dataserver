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
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("CRuudLogDbSet ODBC Connect Fail");
	return 0;
}

int CGremoryCaseDBSet::GetItemSerial(unsigned int *sirial_number, int MakeSeiralCount)
{
	char *v3; // eax
	int result; // eax
	int v5; // [esp+20h] [ebp-ECh]
	CString strQuery; // [esp+ECh] [ebp-20h]
	int v8; // [esp+108h] [ebp-4h]

	*sirial_number = 0;
	strQuery.Format("WZ_GremoryCaseSerial '%d'",MakeSeiralCount);
	this->m_DBQuery.Exec(strQuery);
	if (this->m_DBQuery.Fetch() == 100)
	{
		this->m_DBQuery.Clear();
		result = 0;
	}
	else
	{
		*sirial_number = this->m_DBQuery.GetInt64(1);
		LogAdd("[GetGremoriCaseSerial] Get Last Item Serial from DB : %u", *sirial_number);
		this->m_DBQuery.Clear();
		result = 1;
	}
	return result;
}

//----- (0043B780) --------------------------------------------------------
int CGremoryCaseDBSet::InsertGremoryCase(char *szAccountID, char *szName, char btGCType, char btGiveType, char btItemType, unsigned __int16 wItemIndex, char btLevel, char btDur, char btSkill, char btLuck, char btOpt, char btSetOpt, unsigned __int16 wNewOpt, char btBonusSocketOpt, char *btSocketOpt, unsigned int dwReceiptExpireDuration, unsigned int dwItemDuration, int lRecvDate, int lRecvExpireDate, int lItemExpireDate, unsigned int *dwSerial)
{
	char *v22; // eax
	int result; // eax
	int v24; // [esp+14h] [ebp-11Ch]
	char Ret; // [esp+FBh] [ebp-35h]
	CString QueryStr; // [esp+110h] [ebp-20h]
	int v28; // [esp+12Ch] [ebp-4h]

	v28 = 0;
	*dwSerial = gGremoryCaseSerial.GetSerial();
	QueryStr.Format("EXEC WZ_GremoryCaseInsert %d,%d, '%s','%s', %d,%d,%d,%d,%d,%d,%d,%d,%d, %d,%d,%d,%d,%d,%d, %u, %u,%u, %u,%u,%u",
		btGCType,
		btGiveType,
		szAccountID,
		szName,
		btItemType,
		wItemIndex,
		btLevel,
		btDur,
		btSkill,
		btLuck,
		btOpt,
		btSetOpt,
		wNewOpt,
		btBonusSocketOpt,
		*btSocketOpt,
		btSocketOpt[1],
		btSocketOpt[2],
		btSocketOpt[3],
		btSocketOpt[4],
		*dwSerial,
		dwReceiptExpireDuration,
		dwItemDuration,
		lRecvDate,
		lRecvExpireDate,
		lItemExpireDate);
	if (this->m_DBQuery.Exec(v22))
	{
		if (this->m_DBQuery.Fetch() == 100)
		{
			this->m_DBQuery.Clear();
			v28 = -1;
			result = 0;
		}
		else
		{
			Ret = this->m_DBQuery.GetInt(1);
			this->m_DBQuery.Clear();
			v28 = -1;
			result = Ret;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD(
			"error-L3 : [GremoryCase] InsertGremoryCase #1 [%s][%s] %s %d",
			szAccountID,
			szName, __FILE__, __LINE__);
		v24 = 0;
		v28 = -1;
		result = v24;
	}
	return result;
}
// 5CDB04: using guessed type int `CGremoryCaseDBSet::InsertGremoryCase'::`2'::__LINE__Var;

//----- (0043B9D0) --------------------------------------------------------
int CGremoryCaseDBSet::SelectGremoryCase(char *szAccountID, char *szName, _stGremoryCaseList *pGCList, char *btListCnt)
{
	char *v5; // eax
	int result; // eax
	char *v7; // eax
	char *v8; // eax
	char *v9; // eax
	int v10; // [esp+14h] [ebp-140h]
	int v11; // [esp+20h] [ebp-134h]
	int v12; // [esp+2Ch] [ebp-128h]
	int v13; // [esp+38h] [ebp-11Ch]
	int v14; // [esp+44h] [ebp-110h]
	__int16 sqlRetrun; // [esp+110h] [ebp-44h]
	int iGC_ChCnt; // [esp+11Ch] [ebp-38h]
	int iGC_AcCnt; // [esp+128h] [ebp-2Ch]
	CString QueryStr; // [esp+134h] [ebp-20h]
	int v20; // [esp+150h] [ebp-4h]

	v20 = 0;
	QueryStr.Format("EXEC WZ_GremoryCaseChkLimitedCnt '%s', '%s', %d",
		szAccountID,
		szName,
		1);
	if (this->m_DBQuery.Exec(v5))
	{
		this->m_DBQuery.Clear();
		QueryStr.Format(
			"EXEC WZ_GremoryCaseChkLimitedCnt '%s', '%s', %d",
			szAccountID,
			szName,
			2);
		if (this->m_DBQuery.Exec(v7))
		{
			this->m_DBQuery.Clear();
			QueryStr.Format("EXEC WZ_GremoryCaseSelect '%s', '%s', %d",
				szAccountID,
				szName,
				1);
			if (this->m_DBQuery.Exec(v8))
			{
				iGC_AcCnt = 0;
				iGC_ChCnt = 0;
				for (sqlRetrun = this->m_DBQuery.Fetch();
					sqlRetrun != 100 && sqlRetrun != -1;
					sqlRetrun = this->m_DBQuery.Fetch())
				{
					if (++iGC_AcCnt > 50)
					{
						this->m_DBQuery.Clear();
						LogAddTD(
							"error-L3 : [GremoryCase] higher than MAX_GC_ACCOUNT [%s][%s] %s %d",
							szAccountID,
							szName, __FILE__, __LINE__);
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
				QueryStr.Format(
					"EXEC WZ_GremoryCaseSelect '%s', '%s', %d",
					szAccountID,
					szName,
					2);
				if (this->m_DBQuery.Exec(v9))
				{
					for (sqlRetrun = this->m_DBQuery.Fetch();
						sqlRetrun != 100 && sqlRetrun != -1;
						sqlRetrun = this->m_DBQuery.Fetch())
					{
						if (++iGC_ChCnt > 50)
						{
							this->m_DBQuery.Clear();
							LogAddTD(
								"error-L3 : [GremoryCase] higher than MAX_GC_CHAR [%s][%s] %s %d",
								szAccountID,
								szName, __FILE__, __LINE__);
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
					v14 = 1;
					v20 = -1;
					result = v14;
				}
				else
				{
					this->m_DBQuery.Clear();
					LogAddTD(
						"error-L3 : [GremoryCase] SelectGremoryCase #4 [%s][%s] %s %d",
						szAccountID,
						szName, __FILE__, __LINE__);
					v13 = 0;
					v20 = -1;
					result = v13;
				}
			}
			else
			{
				this->m_DBQuery.Clear();
				LogAddTD(
					"error-L3 : [GremoryCase] SelectGremoryCase #3 [%s][%s] %s %d",
					szAccountID,
					szName, __FILE__, __LINE__);
				v12 = 0;
				v20 = -1;
				result = v12;
			}
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD(
				"error-L3 : [GremoryCase] SelectGremoryCase #2 [%s][%s] %s %d",
				szAccountID,
				szName, __FILE__, __LINE__);
			v11 = 0;
			v20 = -1;
			result = v11;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD(
			"error-L3 : [GremoryCase] SelectGremoryCase #1 [%s][%s] %s %d",
			szAccountID,
			szName, __FILE__, __LINE__);
		v10 = 0;
		v20 = -1;
		result = v10;
	}
	return result;
}
// 5CDB08: using guessed type int `CGremoryCaseDBSet::SelectGremoryCase'::`2'::__LINE__Var;

//----- (0043C430) --------------------------------------------------------
int CGremoryCaseDBSet::UpdateGremoryCase(char *szAccountID, char *szName, char btGCType, char btItemType, unsigned __int16 wItemIndex, char btLevel, unsigned int dwSerial, int lRecvDate, char btUsedInfo)
{
	char *v10; // eax
	int result; // eax
	int v12; // [esp+14h] [ebp-11Ch]
	char Ret; // [esp+FBh] [ebp-35h]
	CString QueryStr; // [esp+110h] [ebp-20h]
	int v16; // [esp+12Ch] [ebp-4h]

	v16 = 0;
	QueryStr.Format("EXEC WZ_GremoryCaseDelete %d, '%s','%s', %d,%d,%d, %u,%u, %d",
		btGCType,
		szAccountID,
		szName,
		btItemType,
		wItemIndex,
		btLevel,
		dwSerial,
		lRecvDate,
		btUsedInfo);
	if (this->m_DBQuery.Exec(v10))
	{
		if (this->m_DBQuery.Fetch() == 100)
		{
			this->m_DBQuery.Clear();
			v16 = -1;
			result = 0;
		}
		else
		{
			Ret = this->m_DBQuery.GetInt(1);
			this->m_DBQuery.Clear();
			v16 = -1;
			result = Ret;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD(
			"error-L3 : [GremoryCase] UpdateGremoryCase #1 [%s][%s] %s %d",
			szAccountID,
			szName, __FILE__, __LINE__);
		v12 = 0;
		v16 = -1;
		result = v12;
	}
	return result;
}
// 5CDB0C: using guessed type int `CGremoryCaseDBSet::UpdateGremoryCase'::`2'::__LINE__Var;

//----- (0043C620) --------------------------------------------------------
int CGremoryCaseDBSet::UpdateGremoryCaseItemRecv(char *szAccountID, char *szName, char btGCType, char btItemType, unsigned __int16 wItemIndex, char btLevel, unsigned int dwSerial, int lRecvDate, char btUsedInfo)
{
	char *v10; // eax
	int result; // eax
	int v12; // [esp+14h] [ebp-11Ch]
	char Ret; // [esp+FBh] [ebp-35h]
	CString QueryStr; // [esp+110h] [ebp-20h]
	int v16; // [esp+12Ch] [ebp-4h]

	v16 = 0;
	QueryStr.Format("EXEC WZ_GremoryCaseItemRecv %d, '%s','%s', %d,%d,%d, %u,%u, %d",
		btGCType,
		szAccountID,
		szName,
		btItemType,
		wItemIndex,
		btLevel,
		dwSerial,
		lRecvDate,
		btUsedInfo);
	if (this->m_DBQuery.Exec(v10))
	{
		if (this->m_DBQuery.Fetch() == 100)
		{
			this->m_DBQuery.Clear();
			v16 = -1;
			result = 0;
		}
		else
		{
			Ret = this->m_DBQuery.GetInt(1);
			this->m_DBQuery.Clear();
			v16 = -1;
			result = Ret;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD(
			"error-L3 : [GremoryCase] UpdateGremoryCaseItemRecv #1 [%s][%s] %s %d",
			szAccountID,
			szName, __FILE__, __LINE__);
		v12 = 0;
		v16 = -1;
		result = v12;
	}
	return result;
}

CGremoryCaseSerial::CGremoryCaseSerial()
{
		this->m_dwGCItemSerial = 0;
	this->m_dwGCLastSerial = 0;
	InitializeCriticalSection(&this->m_csGCItemSerial);
}

CGremoryCaseSerial::~CGremoryCaseSerial()
{
	//this->vfptr = &CGremoryCaseSerial::`vftable';
		DeleteCriticalSection(&this->m_csGCItemSerial);
}

int CGremoryCaseSerial::MakeSerial()
{
	if (!g_CGremoryCaseDBSet.GetItemSerial(&this->m_dwGCItemSerial, 3000))
		return 0;
	this->m_dwGCLastSerial = this->m_dwGCItemSerial + 3000;
	return 1;
}

//----- (0043B360) --------------------------------------------------------
unsigned int CGremoryCaseSerial::GetSerial()
{
	unsigned int retserial; // STD4_4
	EnterCriticalSection(&this->m_csGCItemSerial);
	if (this->m_dwGCItemSerial >= this->m_dwGCLastSerial)
		MakeSerial();
	retserial = this->m_dwGCItemSerial++;
	LeaveCriticalSection(&this->m_csGCItemSerial);
	return retserial;
}
