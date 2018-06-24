#include "StdAfx.h"
#include "PentagramDBSet.h"

CPentagramDBSet::CPentagramDBSet()
{
}

CPentagramDBSet::~CPentagramDBSet()
{
}

BOOL CPentagramDBSet::Connect()
{
	//return this->CDBConBase::Connect(szDbConnectID, szDbConnectPass);
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("CPentagramDBSet ODBC Connect Fail");
	return 0;
}

//----- (00445D40) --------------------------------------------------------
int CPentagramDBSet::GetPentagramJewel(int iUserGuid, char *szAccountID, char *Name, PENTAGRAMJEWEL_INFO *pPentagramJewelInfo, PMSG_ANS_PENTAGRAMJEWEL *pMsg, BYTE iReqType)
{
	int result; // eax
	__int16 sqlRet;
	char szTemp[2048];
	CString szQuery;
	char szName[11];
	char szId[11];

	szId[10] = 0;
	memcpy(szId, szAccountID, 0xA);
	//strlen(szId);
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

			szQuery.Format("WZ_PentagramInfoSelect %d, '%s', '%s', %d", iUserGuid, szId, szName, iReqType);

			if (this->m_DBQuery.Exec(szQuery))
			{
				for (sqlRet = this->m_DBQuery.Fetch(); sqlRet != 100; sqlRet = this->m_DBQuery.Fetch())
				{
					if (sqlRet == -1)
						break;
					pPentagramJewelInfo[iCnt].btJewelPos = iReqType;
					pPentagramJewelInfo[iCnt].btJewelIndex = this->m_DBQuery.GetInt("JewelIndex");
					pPentagramJewelInfo[iCnt].btItemType = this->m_DBQuery.GetInt("ItemType");
					pPentagramJewelInfo[iCnt].wItemIndex = this->m_DBQuery.GetInt("ItemIndex");
					pPentagramJewelInfo[iCnt].btMainAttribute = this->m_DBQuery.GetInt("MainAttribute");
					pPentagramJewelInfo[iCnt].btLevel = this->m_DBQuery.GetInt("JewelLevel");
					pPentagramJewelInfo[iCnt].btRank1OptionNum = this->m_DBQuery.GetInt("Rank1");
					pPentagramJewelInfo[iCnt].btRank1Level = this->m_DBQuery.GetInt("Rank1Level");
					pPentagramJewelInfo[iCnt].btRank2OptionNum = this->m_DBQuery.GetInt("Rank2");
					pPentagramJewelInfo[iCnt].btRank2Level = this->m_DBQuery.GetInt("Rank2Level");
					pPentagramJewelInfo[iCnt].btRank3OptionNum = this->m_DBQuery.GetInt("Rank3");
					pPentagramJewelInfo[iCnt].btRank3Level = this->m_DBQuery.GetInt("Rank3Level");
					pPentagramJewelInfo[iCnt].btRank4OptionNum = this->m_DBQuery.GetInt("Rank4");
					pPentagramJewelInfo[iCnt].btRank4Level = this->m_DBQuery.GetInt("Rank4Level");
					pPentagramJewelInfo[iCnt].btRank5OptionNum = this->m_DBQuery.GetInt("Rank5");
					pPentagramJewelInfo[iCnt++].btRank5Level = this->m_DBQuery.GetInt("Rank5Level");
					if (iCnt >= 250)
						break;
				}
				pMsg->btJewelCnt = iCnt;
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
			LogAddC(2, "%s] À+ÁÕ +íÀ» %s %d", szName, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(2, "%s] À+ÁÕ +íÀ» %s %d", szId, __FILE__, __LINE__);
		result = 1;
	}
	return result;
}
// 5CDF20: using guessed type int `CPentagramDBSet::GetPentagramJewel'::`2'::__LINE__Var;

BOOL CPentagramDBSet::SetPentagramJewel(PMSG_PENTAGRAMJEWEL_INFO *lpRecv)
{
	void *v2;
	int result;
	int v6;
	char bTmp;
	CString szQuery;
	PENTAGRAMJEWEL_INFO PentagramJewelInfo[250];
	char szName[10];
	char szId[10];

	v2 = alloca(4444);
	memcpy(szId, lpRecv->AccountId, 0xAu);
	if (strlen(szId) && strlen(szId) <= 0xA)
	{
		memcpy(szName, lpRecv->szName, 0xAu);
		if (strlen(szName) && strlen(szName) <= 0xA)
		{
			int iUserGuid = lpRecv->iUserGuid;
			BYTE iJewelCnt = lpRecv->btJewelCnt;
			BYTE iJewelPos = lpRecv->btJewelPos;
			if (iJewelCnt >= 0)
				v6 = iJewelCnt <= 249;
			else
				v6 = 0;
			if (v6)
			{
				memcpy(PentagramJewelInfo, &lpRecv[1], 17 * iJewelCnt);
				int iReturnValue = 0;
				for (int i = 0; i < iJewelCnt; ++i)
				{
					//WZ_PentagramInfoUpdate 8, 'test4', 'RagF', 0, 0, 0,  976, 0,  73, 0,  122, 56, 79, 119, 56, -67, 9, -63, -12 //not work
					//WZ_PentagramInfoUpdate 8, 'test4', 'RagF', 0, 0, 12, 252, 21, 0,  14, 0,   15, 15, 15,  15,  15, 15, 15,  15 //works
					BYTE iJewelPos = PentagramJewelInfo[i].btJewelPos;
					BYTE iJewelIndex = PentagramJewelInfo[i].btJewelIndex;
					BYTE iItemType = PentagramJewelInfo[i].btItemType;
					WORD wItemIndex = PentagramJewelInfo[i].wItemIndex;
					BYTE iMainAttribute = PentagramJewelInfo[i].btMainAttribute;
					BYTE iJewelLevel = PentagramJewelInfo[i].btLevel;
					BYTE iRank1OptionNum = PentagramJewelInfo[i].btRank1OptionNum;
					BYTE iRank1Level = PentagramJewelInfo[i].btRank1Level;
					BYTE iRank2OptionNum = PentagramJewelInfo[i].btRank2OptionNum;
					BYTE iRank2Level = PentagramJewelInfo[i].btRank2Level;
					BYTE iRank3OptionNum = PentagramJewelInfo[i].btRank3OptionNum;
					BYTE iRank3Level = PentagramJewelInfo[i].btRank3Level;
					BYTE iRank4OptionNum = PentagramJewelInfo[i].btRank4OptionNum;
					BYTE iRank4Level = PentagramJewelInfo[i].btRank4Level;
					BYTE iRank5OptionNum = PentagramJewelInfo[i].btRank5OptionNum;
					BYTE iRank5Level = PentagramJewelInfo[i].btRank5Level;
					szQuery.Format("WZ_PentagramInfoUpdate %d, '%s', '%s', %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", iUserGuid, szId, szName,
						iJewelPos,
						iJewelIndex,
						iItemType,
						wItemIndex,
						iMainAttribute,
						iJewelLevel,
						iRank1OptionNum,
						iRank1Level,
						iRank2OptionNum,
						iRank2Level,
						iRank3OptionNum,
						iRank3Level,
						iRank4OptionNum,
						iRank4Level,
						iRank5OptionNum,
						iRank5Level);
					if (!this->m_DBQuery.Exec(szQuery))
					{
						//bTmp = 0;
						//this->m_DBQuery.PrintDiag(bTmp);
						LogAddC(2u, "Error m_DBQuery.Exec %s %d", __FILE__, __LINE__);
						this->m_DBQuery.Clear();
						iReturnValue = 1;
						break;
					}
					this->m_DBQuery.Clear();
				}
				// CString::_CString(&szQuery);
				result = iReturnValue;
			}
			else
			{
				LogAddC(2u, "%s] ", szId, __FILE__, __LINE__);
				result = 1;
			}
		}
		else
		{
			LogAddC(2u, "%s] ", szName, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(2u, "%s] ", szId, __FILE__, __LINE__);
		result = 1;
	}
	return result;
}



int CPentagramDBSet::DelPentagramJewel(PMSG_DEL_PENTAGRAMJEWEL *lpRecv)
{
	int result;
	CString szQuery;
	char szName[11];
	char szId[11];

	szId[10] = 0;
	memcpy(szId, lpRecv->AccountId, 0xAu);
	if (strlen(szId) && (strlen(szId) <= 0xA))
	{
		szName[10] = 0;
		memcpy(szName, lpRecv->szName, 0xAu);
		if (strlen(szName) && (strlen(szName) <= 0xA))
		{
			int iUserGuid = lpRecv->iUserGuid;
			BYTE iJewelPos = lpRecv->btJewelPos;
			BYTE iJewelIndex = lpRecv->btJewelIndex;

			int iReturnValue = 0;
			szQuery.Format("WZ_PentagramInfoDelete %d, '%s', '%s', %d, %d",
				iUserGuid, szId, szName, iJewelPos, iJewelIndex);
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
			LogAddC(2, "%s] +Þ-ª +íÀ» %s %d", szName, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(2, "%s] +Þ-ª +íÀ» %s %d", szId, __FILE__, __LINE__);
		result = 1;
	}
	return result;
}



int CPentagramDBSet::InsertPentagramJewel(PMSG_INSERT_PENTAGRAMJEWEL *lpRecv)
{
	int result;
	int iReturnValue;
	CString szQuery;
	char szName[11];
	char szId[11];

	szId[10] = 0;
	memcpy(szId, lpRecv->AccountId, 0xAu);

	if (strlen(szId) && (strlen(szId) <= 0xA))
	{
		szName[10] = 0;
		memcpy(szName, lpRecv->szName, 0xAu);

		if (strlen(szName) && (strlen(szName) <= 0xA))
		{
			int		iUserGuid = lpRecv->iUserGuid;
			BYTE	iJewelPos = lpRecv->btJewelPos;
			BYTE	iJewelIndex = lpRecv->btJewelIndex;
			BYTE	iItemType = lpRecv->btItemType;
			WORD	iItemIndex = lpRecv->iItemIndex;
			BYTE	iMainAttribute = lpRecv->btMainAttribute;
			BYTE	iJewelLevel = lpRecv->btLevel;
			BYTE	iRank1OptionNum = lpRecv->btRank1OptionNum;
			BYTE	iRank1Level = lpRecv->btRank1Level;
			BYTE	iRank2OptionNum = lpRecv->btRank2OptionNum;
			BYTE	iRank2Level = lpRecv->btRank2Level;
			BYTE	iRank3OptionNum = lpRecv->btRank3OptionNum;
			BYTE	iRank3Level = lpRecv->btRank3Level;
			BYTE	iRank4OptionNum = lpRecv->btRank4OptionNum;
			BYTE	iRank4Level = lpRecv->btRank4Level;
			BYTE	iRank5OptionNum = lpRecv->btRank5OptionNum;
			BYTE	iRank5Level = lpRecv->btRank5Level;

			iReturnValue = 0;
			szQuery.Format("WZ_PentagramInfoUpdate %d, '%s', '%s', %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
				iUserGuid,
				szId,
				szName,
				iJewelPos,
				iJewelIndex,
				iItemType,
				iItemIndex,
				iMainAttribute,
				iJewelLevel,
				iRank1OptionNum,
				iRank1Level,
				iRank2OptionNum,
				iRank2Level,
				iRank3OptionNum,
				iRank3Level,
				iRank4OptionNum,
				iRank4Level,
				iRank5OptionNum,
				iRank5Level);
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
			LogAddC(2, "%s] Insert +íÀ» %s %d", szName, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(2, "%s] Insert +íÀ» %s %d", szId, __FILE__, __LINE__);
		result = 1;
	}
	return result;
}

CPentagramLogDBSet::CPentagramLogDBSet()
{
}

CPentagramLogDBSet::~CPentagramLogDBSet()
{
}

int CPentagramLogDBSet::Connect()
{

	if (this->m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox(" CPentagramDBSet DB set connect fail.");
	return 0;
}

int CPentagramLogDBSet::InsertJewelUpgradeInfo(_tagPMSG_REQ_JEWEL_UPGRADE_INFO_INSERT_DS *lpMsg)
{
	int result;
	int iReturnValue;
	CString szQuery;
	int iSuccess;
	int iUpgradeType;
	int iJewelIndex;
	int iJewelType;
	char szName[11];
	char szId[11];

	szId[10] = 0;
	memcpy(szId, lpMsg->AccountID, 0xAu);

	if (strlen(szId) && (strlen(szId) <= 0xA))
	{
		szName[10] = 0;
		memcpy(szName, lpMsg->Name, 0xAu);

		if (strlen(szName) && (strlen(szName) <= 0xA))
		{
			iJewelType = lpMsg->iJewelType;
			iJewelIndex = lpMsg->iJewelIndex;
			iUpgradeType = lpMsg->iUpgradeType;
			iSuccess = lpMsg->iSuccess;

			iReturnValue = 0;
			szQuery.Format("WZ_PentagramJewelUpgradeInfoInsert '%s', '%s', %d, %d, %d, %d",
				szId, szName, iJewelType, iJewelIndex, iUpgradeType, iSuccess);
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
			LogAddC(2, "%s] Insert ߡׯ %s %d", szName, __FILE__, __LINE__);
			result = 1;
		}
	}
	else
	{
		LogAddC(2, "%s] Insert ߡׯ %s %d", szId, __FILE__, __LINE__);
		result = 1;
	}
	return result;
}