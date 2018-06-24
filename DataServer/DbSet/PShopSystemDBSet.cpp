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
	//return this->CDBConBase::Connect(szDbConnectID, szDbConnectPass);
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("CPShopSystemDBSet ODBC Connect Fail");
	return 0;
}

int CPShopSystemDBSet::LoadPShopItemValueInfo(char *szAccountID, char *Name, PMSG_PSHOPITEMVALUE_INFO *pPShopItemValueInfo, PMSG_ANS_PSHOPITEMVALUE_INFO *pMsg)
{
	int result;
	unsigned int v9;
	__int16 sqlRet;
	char szTemp[2048];
	CString szQuery;
	char szName[11];
	char szId[11];


	szId[10] = 0;
	memcpy(szId, szAccountID, 0xAu);
	if (strlen(szId) && (strlen(szId) <= 0xA))
	{
		szName[10] = 0;
		memcpy(szName, Name, 0xAu);
		if (strlen(szName) && (strlen(szName)<= 0xA))
		{
			int iCnt = 0;
			szTemp[0] = 0;
			memset(&szTemp[1], 0, 0x7FFu);

			szQuery.Format("WZ_PShopItemValueInfoLoad '%s', '%s'", szAccountID, Name);

			if (this->m_DBQuery.Exec(szQuery))
			{
				for (sqlRet = this->m_DBQuery.Fetch(); sqlRet != 100; sqlRet = this->m_DBQuery.Fetch())
				{
					if (sqlRet == -1)
						break;
					pPShopItemValueInfo[iCnt].nPShopItemInvenNum = this->m_DBQuery.GetInt("ItemInvenNum");
					pPShopItemValueInfo[iCnt].wItemSerial = this->m_DBQuery.GetInt64("ItemSerial");
					pPShopItemValueInfo[iCnt].nMoney = this->m_DBQuery.GetInt("Money");
					pPShopItemValueInfo[iCnt].sBlessJewelValue = this->m_DBQuery.GetInt("BlessJewelValue");
					pPShopItemValueInfo[iCnt].sSoulJewelValue = this->m_DBQuery.GetInt("SoulJewelValue");
					pPShopItemValueInfo[iCnt++].sChaosJewelValue = this->m_DBQuery.GetInt("ChaosJewelValue");
					if (iCnt >= 32)
						break;
				}
				pMsg->btItemCnt = iCnt;
				this->m_DBQuery.Clear();
				result = 0;
			}
			else
			{
				LogAddC(2, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				result = 1;
			}
		}
		else
		{
			LogAddC(2, "%s] ؎֥ ߡׯ %s %d", szName, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(2, "%s] ؎֥ ߡׯ %s %d", szId, __FILE__, __LINE__);
		result = 1;
	}
	return result;
}


int CPShopSystemDBSet::SavePShopItemValueInfo(PMSG_UPDATE_PSHOPITEMVALUE_INFO *lpRecv)
{
	int result;
	BOOL v8;
	int sChaosJewelValue;
	int sSoulJewelValue;
	int sBlessJewelValue;
	int nMoney;
	unsigned int wItemSerial;
	CString szQuery;
	PMSG_PSHOPITEMVALUE_INFO PShopItemValueInfo[32];
	int iItemCnt;
	char szName[11];
	char szId[11];

	szId[10] = 0;
	memcpy(szId, lpRecv->AccountId, 0xAu);
	
	if (strlen(szId) && (strlen(szId) <= 0xA))
	{
		szName[10] = 0;
		memcpy(szName, lpRecv->szName, 0xAu);
		//strlen(szName);
		if (strlen(szId) && (strlen(szName) <= 0xA))
		{
			iItemCnt = lpRecv->btItemCnt;
			if (iItemCnt > 0)
				v8 = iItemCnt <= 32;
			else
				v8 = 0;
			if (v8)
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
							LogAddC(2, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
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
				LogAddC(2, "%s] ze ߡׯ(гNܳa ߆Lƛ) %s %d", szId, __FILE__, __LINE__);
				result = 1;
			}
		}
		else
		{
			LogAddC(2, "%s] ze ߡׯ %s %d", szName, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(2, "%s] ze ߡׯ %s %d", szId, __FILE__, __LINE__);
		result = 1;
	}
	return result;
}


int CPShopSystemDBSet::DelPShopItemValueInfo(PMSG_DEL_PSHOPITEM *lpRecv)
{
	int result;
	int iReturnValue;
	CString szQuery;
	char szName[11];
	char szId[11];


	szId[10] = 0;
	memcpy(szId, lpRecv->AccountId, 0xAu);
	//strlen(szId);
	if (strlen(szId) && (strlen(szId) <= 0xA))
	{
		szName[10] = 0;
		memcpy(szName, lpRecv->szName, 0xAu);
		//strlen(szName);
		if (strlen(szName) && (strlen(szName) <= 0xA))
		{
			iReturnValue = 0;
			szQuery.Format("WZ_PShopItemValueInfoDel '%s', '%s', %d",
				szId,
				szName,
				lpRecv->nPShopItemInvenNum);
			if (!this->m_DBQuery.Exec(szQuery))
			{
				LogAddC(2, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				iReturnValue = 1;
			}
			this->m_DBQuery.Clear();
			result = iReturnValue;
		}
		else
		{
			LogAddC(2, "%s] ze ߡׯ %s %d", szName, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(2, "%s] ze ߡׯ %s %d", szId, __FILE__, __LINE__);
		result = 1;
	}
	return result;
}


int CPShopSystemDBSet::MovePShopItem(PMSG_MOVE_PSHOPITEM *lpRecv)
{
	int result;
	int iReturnValue;
	CString szQuery;
	char szName[11];
	char szId[11]; 
	int v14;


	szId[10] = 0;
	memcpy(szId, lpRecv->AccountId, 0xAu);
	/*strlen(szId);*/
	if (strlen(szId) && (strlen(szId) <= 0xA))
	{
		szName[10] = 0;
		memcpy(szName, lpRecv->szName, 0xAu);
		/*strlen(szName)*/;
		if (strlen(szName) && (strlen(szName) <= 0xA))
		{
			iReturnValue = 0;
			szQuery.Format("WZ_PShopItemMove '%s', '%s', %d, %d",
				szId,szName,lpRecv->nOldPShopItemInvenNum,lpRecv->nNewPShopItemInvenNum);
			if (!this->m_DBQuery.Exec(szQuery))
			{
				LogAddC(2, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
				this->m_DBQuery.Clear();
				iReturnValue = 1;
			}
			this->m_DBQuery.Clear();
			result = iReturnValue;
		}
		else
		{
			LogAddC(2, "%s] ze ߡׯ %s %d", szName, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(2, "%s] ze ߡׯ %s %d", szId, __FILE__, __LINE__);
		result = 1;
	}
	return result;
}