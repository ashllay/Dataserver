#include "StdAfx.h"
#include "LabyrinthDBSet.h"

LabyrinthDBSet::LabyrinthDBSet()
{
}

LabyrinthDBSet::~LabyrinthDBSet()
{
}

BOOL LabyrinthDBSet::Connect()
{
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("LabyrinthDBSet ODBC Connect Fail");
	return 0;
}
int LabyrinthDBSet::LoadLabyrinthInfo(char *szAccountID, char *szName, int nUserIndex, char *Buffer, int *nBufferLen)
{
	int result; // eax
	int v10; // [esp+14h] [ebp-290h]
	int v11; // [esp+20h] [ebp-284h]
	int v12; // [esp+2Ch] [ebp-278h]
	int v13; // [esp+38h] [ebp-26Ch]
	int v14; // [esp+44h] [ebp-260h]
	int v15; // [esp+50h] [ebp-254h]
	int v16; // [esp+5Ch] [ebp-248h]
	MISSION_INFO stMissionInfo; // [esp+128h] [ebp-17Ch]
	int nMissionCnt; // [esp+150h] [ebp-154h]
	int nOfs; // [esp+15Ch] [ebp-148h]
	int nRet; // [esp+168h] [ebp-13Ch]
	__int16 sqlRet; // [esp+174h] [ebp-130h]
	CString qSql; // [esp+180h] [ebp-124h]
	SDHP_ANS_LABYRINTH_INFO pMsg; // [esp+18Ch] [ebp-118h]
	__int64 v24; // [esp+274h] [ebp-30h]
	int v25; // [esp+27Ch] [ebp-28h]
	unsigned __int8 v26; // [esp+280h] [ebp-24h]
	char v27; // [esp+281h] [ebp-23h]
	const char *v8;
	int v29; // [esp+2A0h] [ebp-4h]

	//PWMSG_HEAD2::set(&pMsg.h.c, 119, 0, 248);
	pMsg.nUserIndex = nUserIndex;
	pMsg.btResult = 2;

	qSql.Format("EXEC WZ_Labyrinth_Info_Load '%s', '%s'",
		szAccountID,
		szName);

	if (this->m_DBQuery.Exec(qSql))
	{
		sqlRet = this->m_DBQuery.Fetch();
		if (sqlRet == -1)
		{
			this->m_DBQuery.Clear();
			LogAddTD(
				"error-L3 : [LABYRINTH] LoadLabyrinthInfo #2, Fail Fetch %s %d", __FILE__, __LINE__);
			pMsg.btResult = 2;
			memcpy_s(Buffer, 0x1B58u, &pMsg, 0xF8u);
			*nBufferLen = 248;
			v11 = pMsg.btResult;
			v29 = -1;
			result = v11;
		}
		else if (sqlRet == 100)
		{
			this->m_DBQuery.Clear();
			LogAddTD("[LABYRINTH] LoadLabyrinthInfo, Empty user data. (%s)(%s)", szAccountID, szName);
			pMsg.btResult = 1;
			memcpy_s(Buffer, 0x1B58u, &pMsg, 0xF8u);
			*nBufferLen = 248;
			v12 = pMsg.btResult;
			v29 = -1;
			result = v12;
		}
		else
		{
			pMsg.btDimensionLevel = this->m_DBQuery.GetInt("DimensionLevel");
			pMsg.wConfigNum = this->m_DBQuery.GetInt("ConfigNum");
			pMsg.btCurrentZone = this->m_DBQuery.GetInt("CurrentZone");
			*(&pMsg.btCurrentZone + 1) = this->m_DBQuery.GetInt("VisitedCnt");
			*&pMsg.btVisitedList[199] = this->m_DBQuery.GetInt64("EntireExp");
			v24 = this->m_DBQuery.GetInt64("EntireMonKillCnt");
			v25 = this->m_DBQuery.GetInt("ClearCnt");
			v26 = this->m_DBQuery.GetInt("ClearState");
			this->m_DBQuery.Clear();
			qSql.Format("EXEC WZ_Labyrinth_Path_Load '%s', '%s'",
				szAccountID,
				szName);
			nRet = this->m_DBQuery.ReadBlob(v8, &pMsg.btCurrentZone + 2);
			this->m_DBQuery.Clear();
			qSql.Format(
				"EXEC WZ_Labyrinth_Mission_Load '%s', '%s'",
				szAccountID,
				szName);
			if (this->m_DBQuery.Exec(qSql))
			{
				sqlRet = this->m_DBQuery.Fetch();
				if (sqlRet == -1)
				{
					this->m_DBQuery.Clear();
					LogAddTD(
						"error-L3 : [LABYRINTH] LoadLabyrinthInfo #4, Fail Fetch Mission. %s %d", __FILE__, __LINE__);
					pMsg.btResult = 2;
					memcpy_s(Buffer, 0x1B58u, &pMsg, 0xF8u);
					*nBufferLen = 248;
					v14 = pMsg.btResult;
					v29 = -1;
					result = v14;
				}
				else if (sqlRet == 100)
				{
					this->m_DBQuery.Clear();
					LogAddTD("[LABYRINTH] LoadLabyrinthInfo, Empty user Mission data. (%s)(%s)", szAccountID, szName);
					pMsg.btResult = v26 < 1;
					v27 = 0;
					memcpy_s(Buffer, 0x1B58u, &pMsg, 0xF8u);
					*nBufferLen = 248;
					v15 = pMsg.btResult;
					v29 = -1;
					result = v15;
				}
				else
				{
					nOfs = 248;
					nMissionCnt = 0;
					while (sqlRet != 100 && sqlRet != -1)
					{
						stMissionInfo.btZoneNumber = this->m_DBQuery.GetInt("ZoneNumber");
						stMissionInfo.btMissionType = this->m_DBQuery.GetInt("MissionType");
						stMissionInfo.nMissionValue = this->m_DBQuery.GetInt("MissionValue");
						stMissionInfo.nAcquisionValue = this->m_DBQuery.GetInt("AcquisitionValue");
						stMissionInfo.btMissionState = this->m_DBQuery.GetInt("MissionState");
						stMissionInfo.btIsMainMission = this->m_DBQuery.GetInt("IsMainMission");
						stMissionInfo.btMainMissionOrder = this->m_DBQuery.GetInt("MainMissionOrder");
						stMissionInfo.nRewardItemType = this->m_DBQuery.GetInt("RewardItemType");
						stMissionInfo.nRewardItemIndex = this->m_DBQuery.GetInt("RewardItemIndex");
						stMissionInfo.nRewardValue = this->m_DBQuery.GetInt("RewardValue");
						stMissionInfo.btRewardCheckState = this->m_DBQuery.GetInt("RewardCheckState");
						v27 = ++nMissionCnt;
						memcpy_s(&Buffer[nOfs], 0x1B58u, &stMissionInfo, 0x20u);
						nOfs += 32;
						sqlRet = this->m_DBQuery.Fetch();
					}
					pMsg.h.sizeH = HIBYTE(nOfs);
					pMsg.h.sizeL = nOfs;
					pMsg.btResult = 0;
					memcpy_s(Buffer, 0x1B58u, &pMsg, 0xF8u);
					*nBufferLen = nOfs;
					this->m_DBQuery.Clear();
					v16 = pMsg.btResult;
					v29 = -1;
					result = v16;
				}
			}
			else
			{
				this->m_DBQuery.Clear();
				LogAddTD(
					"error-L3 : [LABYRINTH] LoadLabyrinthInfo #3, Fail Exec Mission. %s %d", __FILE__, __LINE__);
				pMsg.btResult = 2;
				memcpy_s(Buffer, 0x1B58u, &pMsg, 0xF8u);
				*nBufferLen = 248;
				v13 = pMsg.btResult;
				v29 = -1;
				result = v13;
			}
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD(
			"error-L3 : [LABYRINTH] LoadLabyrinthInfo #1, Fail Exec %s %d", __FILE__, __LINE__);
		pMsg.btResult = 2;
		memcpy_s(Buffer, 0x1B58u, &pMsg, 0xF8u);
		*nBufferLen = 248;
		v10 = pMsg.btResult;
		v29 = -1;
		result = v10;
	}
	return result;
}

int LabyrinthDBSet::SaveLabyrinthInfo(BYTE *aRecv)
{
	int result;
	MISSION_INFO *RecvBuf;
	int nOfs;
	SDHP_REQ_LABYRINTH_INFO_SAVE *lpRecv; 
	CString qSql;

	qSql.Format("EXEC WZ_Labyrinth_Info_Save '%s', '%s', %d, %d, %d, %d, ?, %I64d, %I64d, %d, %d",
		lpRecv + 5,
		aRecv + 16,
		aRecv[32],
		*(aRecv + 17),
		aRecv[36],
		aRecv[37],
		*(aRecv + 60),
		*(aRecv + 61),
		*(aRecv + 62),
		*(aRecv + 63),
		*(aRecv + 64),
		aRecv[260]);
	this->m_DBQuery.WriteBlob(qSql, aRecv + 38, 200);
	this->m_DBQuery.Clear();
	if (aRecv[261])
	{
		nOfs = 264;
		for (int i = 0; i < lpRecv->btMissionCount; ++i)
		{
			RecvBuf = (MISSION_INFO *)&aRecv[nOfs];
			qSql.Format("EXEC WZ_Labyrinth_Mission_Insert '%s', '%s', %d, %d, %d, %d, %d",
				lpRecv->szAccountID,
				lpRecv->szName,
				aRecv[nOfs],
				aRecv[nOfs + 1],
				*&aRecv[nOfs + 4],
				aRecv[nOfs + 13],
				aRecv[nOfs + 14]);
			if (!this->m_DBQuery.Exec(qSql))
			{
				this->m_DBQuery.Clear();
				LogAddTD(
					"error-L3 : [LABYRINTH] SaveLabyrinthInfo, Fail Mission Insert Exec. %s %d", __FILE__, __LINE__);
				return 1;
			}
			this->m_DBQuery.Clear();
			nOfs += 32;
		}
		
		result = 0;
	}
	else
	{
		result = 0;
	}
	return result;
}

//----- (00441690) --------------------------------------------------------
__int64 LabyrinthDBSet::UpdateLabyrinthInfo(SDHP_REQ_LABYRINTH_INFO_UPDATE *aRecv)
{
	CString qSql;

	qSql.Format("EXEC WZ_Labyrinth_Info_Update '%s', '%s', %d, %d, %d, %d, ?, %I64d, %I64d",
		aRecv->szAccountID,
		aRecv->szName,
		aRecv->btDimensionLevel,
		aRecv->wConfigNum,
		aRecv->btCurrentZone,
		aRecv->btVisitedCnt,
		LODWORD(aRecv->nEntireExp),
		HIDWORD(aRecv->nEntireExp),
		LODWORD(aRecv->nEntireMonKillCnt),
		HIDWORD(aRecv->nEntireMonKillCnt));
	this->m_DBQuery.WriteBlob(qSql,aRecv->btVisitedList, 200);
	this->m_DBQuery.Clear();
	
	return TRUE;
}

//----- (004417E0) --------------------------------------------------------
int LabyrinthDBSet::UpdateLabyrinthMission(SDHP_REQ_LABYRINTH_MISSION_UPDATE *aRecv)
{
	int result;
	CString qSql;
	int v9;

	v9 = 0;
	qSql.Format(
		
		"EXEC WZ_Labyrinth_Mission_Update '%s', '%s', %d, %d, %d, %d, %d, %d",
		aRecv->szAccountID,
		aRecv->szName,
		aRecv->btZoneNumber,
		aRecv->btMissionType,
		aRecv->nAcquisionValue,
		aRecv->btMissionState,
		aRecv->btIsMainMission,
		aRecv->btMainMissionOrder);
	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		qSql.Format(
			
			"EXEC WZ_Labyrinth_Reward_Update '%s', '%s', %d, %d, %d, %d, %d, %d, %d",
			aRecv->szAccountID,
			aRecv->szName,
			aRecv->btZoneNumber,
			aRecv->btIsMainMission,
			aRecv->btMainMissionOrder,
			aRecv->nRewardItemType,
			aRecv->nRewardItemIndex,
			aRecv->nRewardValue,
			aRecv->btRewardCheckState);

		if (this->m_DBQuery.Exec(qSql))
		{
			this->m_DBQuery.Clear();
			v9 = -1;
			
			result = 0;
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD(
				"error-L3 : [LABYRINTH] UpdateLabyrinthMission #2, Fail Exec. %s %d",__FILE__,__LINE__);
			v9 = -1;
			
			result = 1;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD(
			"error-L3 : [LABYRINTH] UpdateLabyrinthMission #1, Fail Exec. %s %d", __FILE__, __LINE__);
		v9 = -1;
		
		result = 1;
	}
	return result;
}

//----- (00441A30) --------------------------------------------------------
int LabyrinthDBSet::DeleteLabyrinthMission(char *szAccountID, char *szName)
{
	int result;
	CString qSql;
	int v8;
	v8 = 0;
	qSql.Format("EXEC WZ_Labyrinth_Mission_Delete '%s', '%s'",szAccountID,szName);
	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		v8 = -1;
		result = 0;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [LABYRINTH] DeleteLabyrinthMission, Fail Exec. %s %d", __FILE__, __LINE__);
		v8 = -1;
		result = 1;
	}
	return result;
}
// 5CDD20: using guessed type int `LabyrinthDBSet::DeleteLabyrinthMission'::`2'::__LINE__Var;

//----- (00441B80) --------------------------------------------------------
int LabyrinthDBSet::EndUpdateLabyrinthInfo(char *szAccountID, char *szName, int nClearCnt, char btClearState)
{
	int result;
	CString qSql;
	int v10;

	v10 = 0;
	qSql.Format(
		
		"EXEC WZ_Labyrinth_End_Update '%s', '%s', %d, %d",
		szAccountID,
		szName,
		nClearCnt,
		btClearState);
	
	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		v10 = -1;
		result = 0;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [LABYRINTH] EndUpdateLabyrinthInfom, Fail Exec %s %d", __FILE__, __LINE__);
		v10 = -1;
		result = 1;
	}
	return result;
}

//----- (00441CE0) --------------------------------------------------------
int LabyrinthDBSet::UpdateLabyrinthRewardState(char *szAccountID, char *szName, char btIsMainMission, char btRewardCheckState)
{
	int result;
	CString qSql; 
	int v10;
	v10 = 0;

	qSql.Format("EXEC WZ_Labyrinth_Reward_Complete_Update '%s', '%s', %d, %d",szAccountID,szName,btIsMainMission,btRewardCheckState);

	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		v10 = -1;
		result = 0;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [LABYRINTH] UpdateLabyrinthRewardState, Fail Exec %s %d", __FILE__, __LINE__);
		v10 = -1;
		result = 1;
	}
	return result;
}


//----- (00441E40) --------------------------------------------------------
int LabyrinthDBSet::SaveLabyrinthClearLog(char *szAccountID, char *szName, int nDimensionLevel)
{
	int result;
	CString qSql;
	int v9;

	v9 = 0;
	qSql.Format("EXEC WZ_LabyrinthClearLogSetSave '%s', '%s', %d",szAccountID,szName,nDimensionLevel);
	
	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		v9 = -1;
		result = 0;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [LABYRINTH] SaveLabyrinthClearLog, Fail Exec %s %d", __FILE__, __LINE__);
		v9 = -1;
		result = 1;
	}
	return result;
}