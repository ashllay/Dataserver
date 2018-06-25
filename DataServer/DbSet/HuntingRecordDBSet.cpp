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
	//return this->CDBConBase::Connect(szDbConnectID, szDbConnectPass);
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("CHuntingRecordDBSet ODBC Connect Fail");
	return 0;
}

int CHuntingRecordDBSet::LoadHuntingRecordInfo(char *szAccountID, char *Name, HUNTING_RECORD_INFO *pHuntingRecordInfo, SDHP_ANS_HUNTING_RECORD_COUNT *pMsg, int iMapIndex)
{
	int result; // eax
	__int16 sqlRet;
	char szTemp[2048];
	CString szQuery;
	char szName[11]; 
	char szId[11];

	szId[10] = 0;
	memcpy(szId, szAccountID, 0xAu);
	/*strlen(szId)*/;
	if (strlen(szId) && (strlen(szId) <= 0xA))
	{
		szName[10] = 0;
		memcpy(szName, Name, 0xAu);
		//strlen(szName);
		if (strlen(szName) && (strlen(szName) <= 0xA))
		{
			int iCnt = 0;
			szTemp[0] = 0;
			memset(&szTemp[1], 0, 0x7FFu);
			szQuery.Format("WZ_HuntingRecordLoad '%s', '%s', %d",szAccountID,Name,iMapIndex);
			if (this->m_DBQuery.Exec(szQuery))
			{
				for (sqlRet = this->m_DBQuery.Fetch(); sqlRet != 100; sqlRet = this->m_DBQuery.Fetch())
				{
					if (sqlRet == -1)
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
					pHuntingRecordInfo[iCnt++].iGetPentagramAccrueDamage = this->m_DBQuery.GetInt("GetPentagramAccrueDamage");
					if (iCnt >= 60)
						break;
				}
				pMsg->btListCnt = iCnt;
				this->m_DBQuery.Clear();
				result = 0;
			}
			else
			{
				LogAddC(2,"LoadHuntingRecordInfo Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				result = 1;
			}
		}
		else
		{
			LogAddC(2,"%s] ¿+¡’ +Ì¿ª %s %d",szName, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(2,"%s] ¿+¡’ +Ì¿ª %s %d",szId, __FILE__, __LINE__);
		result = 1;
	}
	return result;
}


int CHuntingRecordDBSet::HuntingRecordInfoSave(SDHP_REQ_HUNTING_RECORD_INFO_SAVE *lpRecv)
{
	int v2; // eax
	unsigned int v3; // eax
	int result; // eax
	int v5; // eax
	unsigned int v6; // eax
	BOOL v8; // [esp+10h] [ebp-13C4h]
	int v9; // [esp+18h] [ebp-13BCh]
	int v10; // [esp+E4h] [ebp-12F0h]
	int v11; // [esp+F0h] [ebp-12E4h]
	int v12; // [esp+FCh] [ebp-12D8h]
	int v13; // [esp+108h] [ebp-12CCh]
	int v14; // [esp+114h] [ebp-12C0h]
	int v15; // [esp+120h] [ebp-12B4h]
	int v16; // [esp+12Ch] [ebp-12A8h]
	int v17; // [esp+138h] [ebp-129Ch]
	int v18; // [esp+13Ch] [ebp-1298h]
	int v19; // [esp+148h] [ebp-128Ch]
	int v20; // [esp+154h] [ebp-1280h]
	int v21; // [esp+160h] [ebp-1274h]
	int v22; // [esp+164h] [ebp-1270h]
	int v23; // [esp+170h] [ebp-1264h]
	int v24; // [esp+174h] [ebp-1260h]
	int v25; // [esp+180h] [ebp-1254h]
	int v26; // [esp+18Ch] [ebp-1248h]
	int v27; // [esp+198h] [ebp-123Ch]
	int v28; // [esp+1A4h] [ebp-1230h]
	int v29; // [esp+1B0h] [ebp-1224h]
	int v30; // [esp+1BCh] [ebp-1218h]
	int i; // [esp+1C8h] [ebp-120Ch]
	int v32; // [esp+1D4h] [ebp-1200h]
	CString szQuery; // [esp+1E0h] [ebp-11F4h]
	char v34; // [esp+1ECh] [ebp-11E8h]
	int v35; // [esp+1EDh] [ebp-11E7h]
	char v36; // [esp+1F1h] [ebp-11E3h]
	char v37; // [esp+1F2h] [ebp-11E2h]
	int v38; // [esp+1F3h] [ebp-11E1h]
	int v39; // [esp+1F7h] [ebp-11DDh]
	int v40; // [esp+1FBh] [ebp-11D9h]
	int v41; // [esp+1FFh] [ebp-11D5h]
	int v42; // [esp+203h] [ebp-11D1h]
	int v43; // [esp+207h] [ebp-11CDh]
	int v44; // [esp+20Bh] [ebp-11C9h]
	int v45; // [esp+20Fh] [ebp-11C5h]
	int v46; // [esp+213h] [ebp-11C1h]
	int v47; // [esp+217h] [ebp-11BDh]
	int v48; // [esp+21Bh] [ebp-11B9h]
	int v49; // [esp+21Fh] [ebp-11B5h]
	int v50; // [esp+223h] [ebp-11B1h]
	int v51; // [esp+227h] [ebp-11ADh]
	int v52; // [esp+22Bh] [ebp-11A9h]
	int v53; // [esp+22Fh] [ebp-11A5h]
	int v54; // [esp+233h] [ebp-11A1h]
	int v55; // [esp+1388h] [ebp-4Ch]
	char buf; // [esp+1394h] [ebp-40h]
	char v57; // [esp+139Eh] [ebp-36h]
	char dst; // [esp+13A8h] [ebp-2Ch]
	char v59; // [esp+13B2h] [ebp-22h]
	CHuntingRecordDBSet *v60; // [esp+13BCh] [ebp-18h]
	int v61; // [esp+13D0h] [ebp-4h]

	v60 = this;
	v59 = 0;
	memcpy(&dst, lpRecv->AccountId, 0xAu);
	//strlen(&dst);
	if (strlen(&dst) && (strlen(&dst) <= 0xA))
	{
		v57 = 0;
		memcpy(&buf, lpRecv->szName, 0xAu);
		//strlen(&buf);
		if (strlen(&buf) && (strlen(&buf) <= 0xA))
		{
			v55 = lpRecv->btListCnt;
			if (v55 >= 0)
				v8 = v55 <= 59;
			else
				v8 = 0;
			if (v8)
			{
				memcpy(&v34, &lpRecv[1].h.c, 75 * v55);
				v61 = 0;
				v32 = 0;
				for (i = 0; i < v55; ++i)
				{
					v30 = *(&v34 + 75 * i);
					v29 = *(&v35 + 75 * i);
					v28 = *(&v36 + 75 * i);
					v27 = *(&v37 + 75 * i);
					v26 = *(&v38 + 75 * i);
					v25 = *(&v39 + 75 * i);
					v23 = *(&v40 + 75 * i);
					v24 = *(&v41 + 75 * i);
					v21 = *(&v42 + 75 * i);
					v22 = *(&v43 + 75 * i);
					v20 = *(&v44 + 75 * i);
					v19 = *(&v45 + 75 * i);
					v17 = *(&v46 + 75 * i);
					v18 = *(&v47 + 75 * i);
					v16 = *(&v48 + 75 * i);
					v15 = *(&v49 + 75 * i);
					v14 = *(&v50 + 75 * i);
					v13 = *(&v51 + 75 * i);
					v12 = *(&v52 + 75 * i);
					v11 = *(&v53 + 75 * i);
					v10 = *(&v54 + 75 * i);
					//pHuntingRecordInfo[iCnt].btMapIndex = this->m_DBQuery.GetInt("MapIndex");
					//pHuntingRecordInfo[iCnt].iYear = this->m_DBQuery.GetInt("mYear");
					//pHuntingRecordInfo[iCnt].btMonth = this->m_DBQuery.GetInt("mMonth");
					//pHuntingRecordInfo[iCnt].btDay = this->m_DBQuery.GetInt("mDay");
					//pHuntingRecordInfo[iCnt].iCurrentLevel = this->m_DBQuery.GetInt("CurrentLevel");
					//pHuntingRecordInfo[iCnt].iHuntingAccrueSecond = this->m_DBQuery.GetInt("HuntingAccrueSecond");
					//pHuntingRecordInfo[iCnt].i64NormalAccrueDamage = this->m_DBQuery.GetInt64("NormalAccrueDamage");
					//pHuntingRecordInfo[iCnt].i64PentagramAccrueDamage = this->m_DBQuery.GetInt64("PentagramAccrueDamage");
					//pHuntingRecordInfo[iCnt].iHealAccrueValue = this->m_DBQuery.GetInt("HealAccrueValue");
					//pHuntingRecordInfo[iCnt].iMonsterKillCount = this->m_DBQuery.GetInt("MonsterKillCount");
					//pHuntingRecordInfo[iCnt].i64AccrueExp = this->m_DBQuery.GetInt64("AccrueExp");
					//pHuntingRecordInfo[iCnt].iClass = this->m_DBQuery.GetInt("Class");
					//pHuntingRecordInfo[iCnt].iMaxNormalDamage = this->m_DBQuery.GetInt("MaxNormalDamage");
					//pHuntingRecordInfo[iCnt].iMinNormalDamage = this->m_DBQuery.GetInt("MinNormalDamage");
					//pHuntingRecordInfo[iCnt].iMaxPentagramDamage = this->m_DBQuery.GetInt("MaxPentagramDamage");
					//pHuntingRecordInfo[iCnt].iMinPentagramDamage = this->m_DBQuery.GetInt("MinPentagramDamage");
					//pHuntingRecordInfo[iCnt].iGetNormalAccrueDamage = this->m_DBQuery.GetInt("GetNormalAccrueDamage");
					//pHuntingRecordInfo[iCnt++].iGetPentagramAccrueDamage = this->m_DBQuery.GetInt("GetPentagramAccrueDamage");
					szQuery.Format(
						"WZ_HuntingRecordInfoSave '%s', '%s', %d, %d, %d, %d, %d, %d, %I64d, %I64d, %d, %d, %I64d, %d, %d, %d, %d, %d, %d, %d",
						&dst,
						&buf,
						v30,
						v29,
						v28,
						v27,
						v26,
						v25,
						v23,
						v24,
						v21,
						v22,
						v20,
						v19,
						v17,
						v18,
						v16,
						v15,
						v14,
						v13,
						v12,
						v11,
						v10);
					if (!this->m_DBQuery.Exec(szQuery))
					{
						LogAddC(2,"Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
						this->m_DBQuery.Clear();
						v32 = 1;
						break;
					}
					this->m_DBQuery.Clear();
				}
				v9 = v32;
				v61 = -1;

				result = v9;
			}
			else
			{
				LogAddC(2,"%s] HuntingRecordInfoSave error! (List Count) %s %d",&dst, __FILE__, __LINE__);
				result = 1;
			}
		}
		else
		{
			LogAddC(2,"%s] +∑+’ +Ì¿ª %s %d",&buf, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(2,"%s] +∑+’ +Ì¿ª %s %d",&dst, __FILE__, __LINE__);
		result = 1;
	}
	return result;
}
// 5CDC14: using guessed type int `CHuntingRecordDBSet::HuntingRecordInfoSave'::`2'::__LINE__Var;

//----- (0043E180) --------------------------------------------------------
int CHuntingRecordDBSet::LoadHuntingRecordInfoUserOpen(char *szAccountID, char *Name, SDHP_ANS_HUNTING_RECORD_INFO_USER_OPEN *pMsg)
{
	int result; // eax
	CString szQuery; // [esp+F8h] [ebp-4Ch]
	char szName[11]; // [esp+104h] [ebp-40h]
	char szId[11]; // [esp+118h] [ebp-2Ch]

	szId[10] = 0;
	memcpy(szId, szAccountID, 0xAu);
	//strlen(szId);
	if (strlen(szId) && (strlen(szId) <= 0xA))
	{
		szName[10] = 0;
		memcpy(szName, Name, 0xAu);
		/*strlen(szName);*/
		if (strlen(szName) && (strlen(szName) <= 0xA))
		{
			//v16 = 0;
			szQuery.Format("WZ_HuntingRecordInfoUserOpenLoad '%s', '%s'", szAccountID, Name);
			if (this->m_DBQuery.Exec(szQuery))
			{
				if (this->m_DBQuery.Fetch() == 100)
				{
					LogAddTD("[CHuntingRecordDBSet][Load] HuntingRecordInfoUserOpen Load Error : Fetch() Error");
					this->m_DBQuery.Clear();
					result = 1;
				}
				else
				{
					pMsg->btOpen = this->m_DBQuery.GetInt("UserOpen");
					this->m_DBQuery.Clear();
					result = 0;
				}
			}
			else
			{
				LogAddTD("[CHuntingRecordDBSet][Load] HuntingRecordInfoUserOpen Load Error : Exec(szQuery) Error");
				this->m_DBQuery.Clear();
				result = 1;
			}
		}
		else
		{
			LogAddC(
				2,
				"%s] ¿+¡’ +Ì¿ª %s %d",
				szName, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(
			2,
			"%s] ¿+¡’ +Ì¿ª %s %d",
			szId, __FILE__, __LINE__);
		result = 1;
	}
	return result;
}
// 5CDC18: using guessed type int `CHuntingRecordDBSet::LoadHuntingRecordInfoUserOpen'::`2'::__LINE__Var;

//----- (0043E440) --------------------------------------------------------
int CHuntingRecordDBSet::HuntingRecordInfoUserOpenSave(SDHP_REQ_HUNTING_RECORD_INFO_USER_OPEN_SAVE *lpRecv)
{
	int v2; // eax
	unsigned int v3; // eax
	int result; // eax
	int v5; // eax
	unsigned int v6; // eax
	char *v7; // eax
	int v8; // [esp+14h] [ebp-124h]
	int iReturnValue; // [esp+E0h] [ebp-58h]
	CString szQuery; // [esp+ECh] [ebp-4Ch]
	char szName[11]; // [esp+F8h] [ebp-40h]
	char szId[11]; // [esp+10Ch] [ebp-2Ch]
	int v14; // [esp+134h] [ebp-4h]


	szId[10] = 0;
	memcpy(szId, lpRecv->AccountId, 0xAu);
	//strlen(szId);
	if (strlen(szId) && (strlen(szId), v3 <= 0xA))
	{
		szName[10] = 0;
		memcpy(szName, lpRecv->szName, 0xAu);
		//strlen(szName);
		if (strlen(szName) && (strlen(szName) <= 0xA))
		{
			v14 = 0;
			iReturnValue = 0;
			szQuery.Format(
				"WZ_HuntingRecordInfoUserOpenSave '%s', '%s', %d",
				szId,
				szName,
				lpRecv->btOpen);
			if (!this->m_DBQuery.Exec(szQuery))
			{
				LogAddC(
					2,
					"Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				iReturnValue = 1;
			}
			this->m_DBQuery.Clear();
			v14 = -1;
			result = iReturnValue;
		}
		else
		{
			LogAddC(
				2,
				"%s] +∑+’ +Ì¿ª %s %d",
				szName, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(
			2,
			"%s] +∑+’ +Ì¿ª %s %d",
			szId, __FILE__, __LINE__);
		result = 1;
	}
	return result;
}
// 5CDC1C: using guessed type int `CHuntingRecordDBSet::HuntingRecordInfoUserOpenSave'::`2'::__LINE__Var;

//----- (0043E690) --------------------------------------------------------
int CHuntingRecordDBSet::LoadHuntingRecordInfo_Current(char *szAccountID, char *Name, SDHP_ANS_HUNTING_RECORD_INFO_CURRENT *pMsg, int iMapIndex, int iYear, char btMonth, char btDay)
{
	int v8; // eax
	unsigned int v9; // eax
	int result; // eax
	int v11; // eax
	unsigned int v12; // eax
	char *v13; // eax
	int v14; // [esp+14h] [ebp-944h]
	__int16 sqlRet; // [esp+ECh] [ebp-86Ch]
	char szTemp[2048]; // [esp+F8h] [ebp-860h]
	CString szQuery; // [esp+900h] [ebp-58h]
	int iCnt; // [esp+90Ch] [ebp-4Ch]
	char szName[11]; // [esp+918h] [ebp-40h]
	char szId[11]; // [esp+92Ch] [ebp-2Ch]
	int v22; // [esp+954h] [ebp-4h]


	szId[10] = 0;
	memcpy(szId, szAccountID, 0xAu);
	//strlen(szId);
	if (strlen(szId) && (strlen(szId) <= 0xA))
	{
		szName[10] = 0;
		memcpy(szName, Name, 0xAu);
		//strlen(szName);
		if (strlen(szName) && (strlen(szName) <= 0xA))
		{
			iCnt = 0;

			v22 = 0;
			szTemp[0] = 0;
			memset(&szTemp[1], 0, 0x7FFu);
			szQuery.Format(
				"WZ_HuntingRecordLoad_Current '%s', '%s', %d, %d, %d, %d",
				szId,
				szName,
				iMapIndex,
				iYear,
				btMonth,
				btDay);
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
					if (++iCnt >= 60)
						break;
				}
				pMsg->btListCnt = iCnt;
				this->m_DBQuery.Clear();
				v22 = -1;

				result = 0;
			}
			else
			{
				LogAddC(
					2,
					"LoadHuntingRecordInfo_Current Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				v14 = 1;
				v22 = -1;

				result = v14;
			}
		}
		else
		{
			LogAddC(
				2,
				"%s] ¿+¡’ +Ì¿ª %s %d",
				szName, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(
			2,
			"%s] ¿+¡’ +Ì¿ª %s %d",
			szId, __FILE__, __LINE__);
		result = 1;
	}
	return result;
}
// 5CDC20: using guessed type int `CHuntingRecordDBSet::LoadHuntingRecordInfo_Current'::`2'::__LINE__Var;

//----- (0043EB30) --------------------------------------------------------
int CHuntingRecordDBSet::DeleteHuntingRecordInfo(char *szAccountID, char *Name, int iMapIndex, int iYear, char btMonth, char btDay)
{
	int v7; // eax
	unsigned int v8; // eax
	int result; // eax
	int v10; // eax
	unsigned int v11; // eax
	char *v12; // eax
	int v13; // [esp+14h] [ebp-938h]
	char szTemp[2048]; // [esp+ECh] [ebp-860h]
	CString szQuery; // [esp+8F4h] [ebp-58h]
	int iCnt; // [esp+900h] [ebp-4Ch]
	char szName[11]; // [esp+90Ch] [ebp-40h]
	char szId[11]; // [esp+920h] [ebp-2Ch]
	int v20; // [esp+948h] [ebp-4h]


	szId[10] = 0;
	memcpy(szId, szAccountID, 0xAu);
	strlen(szId);
	if (strlen(szId) && (strlen(szId) <= 0xA))
	{
		szName[10] = 0;
		memcpy(szName, Name, 0xAu);
		strlen(szName);
		if (strlen(szName) && (strlen(szName) <= 0xA))
		{
			iCnt = 0;

			v20 = 0;
			szTemp[0] = 0;
			memset(&szTemp[1], 0, 0x7FFu);
			if (iYear)
				szQuery.Format(
					"WZ_HuntingRecordDelete '%s', '%s', %d, %d, %d, %d",
					szId,
					szName,
					iMapIndex,
					iYear,
					btMonth,
					btDay);
			else
				szQuery.Format(
					"WZ_HuntingRecordDeleteMapAll '%s', '%s', %d",
					szId,
					szName,
					iMapIndex);
			if (this->m_DBQuery.Exec(szQuery))
			{
				this->m_DBQuery.Clear();
				v20 = -1;

				result = 0;
			}
			else
			{
				LogAddC(
					2,
					"DeleteHuntingRecordInfo Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				v20 = -1;

				result = 1;
			}
		}
		else
		{
			LogAddC(
				2,
				"%s] ¿+¡’ +Ì¿ª %s %d",
				szName, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(
			2,
			"%s] ¿+¡’ +Ì¿ª %s %d",
			szId, __FILE__, __LINE__);
		result = 1;
	}
	return result;
}