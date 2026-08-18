#include "StdAfx.h"
#include "PShopSystemDBSet.h"

CPShopSystemDBSet::CPShopSystemDBSet()
{
}

CPShopSystemDBSet::~CPShopSystemDBSet()
{
}

BOOL CPShopSystemDBSet::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("CPShopSystemDBSet ODBC Connect Fail");
	return 0;
}

int CPShopSystemDBSet::LoadPShopItemValueInfo(char *szAccountID, char *Name, PMSG_PSHOPITEMVALUE_INFO *pPShopItemValueInfo, PMSG_ANS_PSHOPITEMVALUE_INFO *pMsg)
{
	int result;
	__int16 sqlRet;
	char szTemp[2048];
	CString szQuery;
	char szName[MAX_IDSTRING+1];
	char szId[MAX_IDSTRING + 1];

	szId[MAX_IDSTRING] = 0;
	memcpy(szId, szAccountID, MAX_IDSTRING);
	if (strlen(szId) && (strlen(szId) <= MAX_IDSTRING))
	{
		szName[MAX_IDSTRING] = 0;
		memcpy(szName, Name, MAX_IDSTRING);
		if (strlen(szName) && (strlen(szName)<= MAX_IDSTRING))
		{
			int iCnt = 0;
			szTemp[0] = 0;
			memset(&szTemp[1], 0, sizeof(szTemp));

			szQuery.Format("WZ_PShopItemValueInfoLoad '%s', '%s'", szAccountID, Name);

			if (this->m_DBQuery.Exec(szQuery))
			{
				for (sqlRet = this->m_DBQuery.Fetch(); sqlRet != SQL_NO_DATA; sqlRet = this->m_DBQuery.Fetch())
				{
					if (sqlRet == -1)
						break;
					pPShopItemValueInfo[iCnt].nPShopItemInvenNum = this->m_DBQuery.GetInt("ItemInvenNum");
					pPShopItemValueInfo[iCnt].wItemSerial = this->m_DBQuery.GetInt64("ItemSerial");
					pPShopItemValueInfo[iCnt].nMoney = this->m_DBQuery.GetInt("Money");
					pPShopItemValueInfo[iCnt].sBlessJewelValue = this->m_DBQuery.GetInt("BlessJewelValue");
					pPShopItemValueInfo[iCnt].sSoulJewelValue = this->m_DBQuery.GetInt("SoulJewelValue");
					pPShopItemValueInfo[iCnt++].sChaosJewelValue = this->m_DBQuery.GetInt("ChaosJewelValue");
					if (iCnt >= MAX_PSHOPITEM)
						break;
				}
				pMsg->btItemCnt = iCnt;
				this->m_DBQuery.Clear();
				result = 0;
			}
			else
			{
				LogAddC(LOGC_RED, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				result = 1;
			}
		}
		else
		{
			LogAddC(LOGC_RED, "%s] 로드 에러 %s %d", szName, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(LOGC_RED, "%s] 로드 에러 %s %d", szId, __FILE__, __LINE__);
		result = 1;
	}
	return result;
}


int CPShopSystemDBSet::SavePShopItemValueInfo(PMSG_UPDATE_PSHOPITEMVALUE_INFO *lpRecv)
{
	int result;
	//BOOL v8;
	int sChaosJewelValue;
	int sSoulJewelValue;
	int sBlessJewelValue;
	int nMoney;
	unsigned int wItemSerial;
	CString szQuery;
	PMSG_PSHOPITEMVALUE_INFO PShopItemValueInfo[32];
	int iItemCnt;
	char szName[MAX_IDSTRING + 1];
	char szId[MAX_IDSTRING + 1];

	szId[MAX_IDSTRING] = 0;
	memcpy(szId, lpRecv->AccountId, MAX_IDSTRING);
	
	if (strlen(szId) && (strlen(szId) <= MAX_IDSTRING))
	{
		szName[MAX_IDSTRING] = 0;
		memcpy(szName, lpRecv->szName, MAX_IDSTRING);
		//strlen(szName);
		if (strlen(szId) && (strlen(szName) <= MAX_IDSTRING))
		{
			iItemCnt = lpRecv->btItemCnt;
			//if (iItemCnt > 0)
			//	v8 = iItemCnt <= 32;
			//else
			//	v8 = 0;
			if (iItemCnt > 0 && iItemCnt <= MAX_PSHOPITEM)
			{
				memcpy(PShopItemValueInfo, &lpRecv[1].h, 18 * iItemCnt);
				int iReturnValue = 0;
				for (int i = 0; i < iItemCnt; ++i)
				{
					int nPShopItemInvenNum = PShopItemValueInfo[i].nPShopItemInvenNum;
					wItemSerial = PShopItemValueInfo[i].wItemSerial;
					nMoney = PShopItemValueInfo[i].nMoney;
					sBlessJewelValue = PShopItemValueInfo[i].sBlessJewelValue;
					sSoulJewelValue = PShopItemValueInfo[i].sSoulJewelValue;
					sChaosJewelValue = PShopItemValueInfo[i].sChaosJewelValue;
					if (nPShopItemInvenNum)
					{
						szQuery.Format("WZ_PShopItemValueInfoSave '%s', '%s', %d, %d, %d, %d, %d, %d",
							szId,
							szName,
							nPShopItemInvenNum,
							wItemSerial,
							nMoney,
							sBlessJewelValue,
							sSoulJewelValue,
							sChaosJewelValue);
						if (!this->m_DBQuery.Exec(szQuery))
						{
							LogAddC(LOGC_RED, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
							this->m_DBQuery.Clear();
							iReturnValue = 1;
							break;
						}
						this->m_DBQuery.Clear();
					}
					else
					{
						LogAddTD("[SavePShopItemValueInfo] Inven position number Error %s %s", szId, szName);
					}
				}
				result = iReturnValue;
			}
			else
			{
				LogAddC(LOGC_RED, "%s] 저장 에러(개인상점 아이템) %s %d", szId, __FILE__, __LINE__);
				result = 1;
			}
		}
		else
		{
			LogAddC(LOGC_RED, "%s] 저장 에러 %s %d", szName, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(LOGC_RED, "%s] 저장 에러 %s %d", szId, __FILE__, __LINE__);
		result = 1;
	}
	return result;
}


int CPShopSystemDBSet::DelPShopItemValueInfo(PMSG_DEL_PSHOPITEM *lpRecv)
{
	int result;
	int iReturnValue;
	CString szQuery;
	char szName[MAX_IDSTRING+1];
	char szId[MAX_IDSTRING+1];


	szId[MAX_IDSTRING] = 0;
	memcpy(szId, lpRecv->AccountId, MAX_IDSTRING);
	//strlen(szId);
	if (strlen(szId) && (strlen(szId) <= MAX_IDSTRING))
	{
		szName[MAX_IDSTRING] = 0;
		memcpy(szName, lpRecv->szName, MAX_IDSTRING);
		//strlen(szName);
		if (strlen(szName) && (strlen(szName) <= MAX_IDSTRING))
		{
			iReturnValue = 0;
			szQuery.Format("WZ_PShopItemValueInfoDel '%s', '%s', %d",
				szId,
				szName,
				lpRecv->nPShopItemInvenNum);
			if (!this->m_DBQuery.Exec(szQuery))
			{
				LogAddC(LOGC_RED, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				iReturnValue = 1;
			}
			this->m_DBQuery.Clear();
			result = iReturnValue;
		}
		else
		{
			LogAddC(LOGC_RED, "%s] 저장 에러 %s %d", szName, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(LOGC_RED, "%s] 저장 에러 %s %d", szId, __FILE__, __LINE__);
		result = 1;
	}
	return result;
}


int CPShopSystemDBSet::MovePShopItem(PMSG_MOVE_PSHOPITEM *lpRecv)
{
	int result;
	int iReturnValue;
	CString szQuery;
	char szName[MAX_IDSTRING+1];
	char szId[MAX_IDSTRING+1];

	szId[MAX_IDSTRING] = 0;
	memcpy(szId, lpRecv->AccountId, MAX_IDSTRING);
	/*strlen(szId);*/
	if (strlen(szId) && (strlen(szId) <= MAX_IDSTRING))
	{
		szName[MAX_IDSTRING] = 0;
		memcpy(szName, lpRecv->szName, MAX_IDSTRING);
		/*strlen(szName)*/;
		if (strlen(szName) && (strlen(szName) <= MAX_IDSTRING))
		{
			iReturnValue = 0;
			szQuery.Format("WZ_PShopItemMove '%s', '%s', %d, %d",
				szId,szName,lpRecv->nOldPShopItemInvenNum,lpRecv->nNewPShopItemInvenNum);
			if (!this->m_DBQuery.Exec(szQuery))
			{
				LogAddC(LOGC_RED, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				iReturnValue = 1;
			}
			this->m_DBQuery.Clear();
			result = iReturnValue;
		}
		else
		{
			LogAddC(LOGC_RED, "%s] 저장 에러 %s %d", szName, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(LOGC_RED, "%s] 저장 에러 %s %d", szId, __FILE__, __LINE__);
		result = 1;
	}
	return result;
}