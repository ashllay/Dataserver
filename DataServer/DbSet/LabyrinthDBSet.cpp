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
	MISSION_INFO stMissionInfo;
	int nMissionCnt;
	int nOfs;
	int nRet;
	__int16 sqlRet;
	CString qSql;
	SDHP_ANS_LABYRINTH_INFO pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0x77, 0, sizeof(pMsg));

	pMsg.nUserIndex = nUserIndex;
	pMsg.btResult = 2;

	qSql.Format("EXEC WZ_Labyrinth_Info_Load '%s', '%s'", szAccountID, szName);

	if (this->m_DBQuery.Exec(qSql))
	{
		sqlRet = this->m_DBQuery.Fetch();
		if (sqlRet == SQL_NULL_DATA)
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [LABYRINTH] LoadLabyrinthInfo #2, Fail Fetch %s %d", __FILE__, __LINE__);
			pMsg.btResult = 2;
			memcpy_s(Buffer, 7000, &pMsg, sizeof(pMsg));
			*nBufferLen = sizeof(pMsg);
			return pMsg.btResult;
		}
		else if (sqlRet == SQL_NO_DATA)
		{
			this->m_DBQuery.Clear();
			LogAddTD("[LABYRINTH] LoadLabyrinthInfo, Empty user data. (%s)(%s)", szAccountID, szName);
			pMsg.btResult = 1;
			memcpy_s(Buffer, 7000, &pMsg, sizeof(pMsg));
			*nBufferLen = sizeof(pMsg);
			return pMsg.btResult;
		}
		else
		{
			pMsg.btDimensionLevel = this->m_DBQuery.GetInt("DimensionLevel");
			pMsg.wConfigNum = this->m_DBQuery.GetInt("ConfigNum");
			pMsg.btCurrentZone = this->m_DBQuery.GetInt("CurrentZone");
			pMsg.btVisitedCnt = this->m_DBQuery.GetInt("VisitedCnt");
			pMsg.nEntireExp = this->m_DBQuery.GetInt64("EntireExp");
			pMsg.nEntireMonKillCnt = this->m_DBQuery.GetInt64("EntireMonKillCnt");
			pMsg.nClearCnt = this->m_DBQuery.GetInt("ClearCnt");
			pMsg.btClearState = this->m_DBQuery.GetInt("ClearState");

			this->m_DBQuery.Clear();

			qSql.Format("EXEC WZ_Labyrinth_Path_Load '%s', '%s'", szAccountID, szName);

			nRet = this->m_DBQuery.ReadBlob(qSql, pMsg.btVisitedList);

			this->m_DBQuery.Clear();

			qSql.Format("EXEC WZ_Labyrinth_Mission_Load '%s', '%s'", szAccountID, szName);

			if (this->m_DBQuery.Exec(qSql))
			{
				sqlRet = this->m_DBQuery.Fetch();

				if (sqlRet == SQL_NULL_DATA)
				{
					this->m_DBQuery.Clear();
					LogAddTD("error-L3 : [LABYRINTH] LoadLabyrinthInfo #4, Fail Fetch Mission. %s %d", __FILE__, __LINE__);
					pMsg.btResult = 2;
					memcpy_s(Buffer, 7000, &pMsg, sizeof(pMsg));
					*nBufferLen = sizeof(pMsg);
					return pMsg.btResult;
				}
				else if (sqlRet == SQL_NO_DATA)
				{
					this->m_DBQuery.Clear();
					LogAddTD("[LABYRINTH] LoadLabyrinthInfo, Empty user Mission data. (%s)(%s)", szAccountID, szName);
					pMsg.btResult = pMsg.btClearState < 1;
					memcpy_s(Buffer, 7000, &pMsg, sizeof(pMsg));
					*nBufferLen = sizeof(pMsg);
					return pMsg.btResult;
				}
				else
				{
					nOfs = sizeof(pMsg);
					nMissionCnt = 0;
					while (sqlRet != SQL_NO_DATA && sqlRet != -SQL_NULL_DATA)
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
						++nMissionCnt;
						memcpy_s(&Buffer[nOfs], 7000, &stMissionInfo, sizeof(MISSION_INFO));
						nOfs += sizeof(MISSION_INFO);
						sqlRet = this->m_DBQuery.Fetch();
					}
					pMsg.h.sizeH = HIBYTE(nOfs);
					pMsg.h.sizeL = LOBYTE(nOfs);
					pMsg.btResult = 0;
					memcpy_s(Buffer, 7000, &pMsg, sizeof(pMsg));
					*nBufferLen = nOfs;
					this->m_DBQuery.Clear();
					return pMsg.btResult;
				}
			}
			else
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [LABYRINTH] LoadLabyrinthInfo #3, Fail Exec Mission. %s %d", __FILE__, __LINE__);
				pMsg.btResult = 2;
				memcpy_s(Buffer, 7000, &pMsg, sizeof(pMsg));
				*nBufferLen = sizeof(pMsg);
				return pMsg.btResult;
			}
		}
	}

	this->m_DBQuery.Clear();
	LogAddTD("error-L3 : [LABYRINTH] LoadLabyrinthInfo #1, Fail Exec %s %d", __FILE__, __LINE__);
	pMsg.btResult = 2;
	memcpy_s(Buffer, 7000, &pMsg, sizeof(pMsg));
	*nBufferLen = sizeof(pMsg);
	return pMsg.btResult;
}

int LabyrinthDBSet::SaveLabyrinthInfo(SDHP_REQ_LABYRINTH_INFO_SAVE*aRecv)
{
	int result;
	MISSION_INFO *RecvBuf;
	int nOfs;
	SDHP_REQ_LABYRINTH_INFO_SAVE *lpRecv; 
	CString qSql;

	qSql.Format("EXEC WZ_Labyrinth_Info_Save '%s', '%s', %d, %d, %d, %d, ?, %I64d, %I64d, %d, %d",
		aRecv->szAccountID[11],
		aRecv->szName[11],
		aRecv->btDimensionLevel,
		aRecv->wConfigNum,
		aRecv->btCurrentZone,
		aRecv->btVisitedCnt,
		aRecv->btVisitedList[200],
		aRecv->nEntireExp,
		aRecv->nEntireMonKillCnt,
		aRecv->nClearCnt,
		aRecv->btClearState);
	this->m_DBQuery.WriteBlob(qSql, aRecv + 38, 200);
	this->m_DBQuery.Clear();
	if (lpRecv->btMissionCount)
	{
		nOfs = sizeof(SDHP_REQ_LABYRINTH_INFO_SAVE);
		for (int i = 0; i < lpRecv->btMissionCount; ++i)
		{
			RecvBuf = (MISSION_INFO *)&aRecv[nOfs];
			qSql.Format("EXEC WZ_Labyrinth_Mission_Insert '%s', '%s', %d, %d, %d, %d, %d",
				lpRecv->szAccountID, lpRecv->szName,
				RecvBuf->btZoneNumber, RecvBuf->btMissionType,
				RecvBuf->nMissionValue, RecvBuf->btIsMainMission,
				RecvBuf->btMainMissionOrder);
			if (!this->m_DBQuery.Exec(qSql))
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [LABYRINTH] SaveLabyrinthInfo, Fail Mission Insert Exec. %s %d", __FILE__, __LINE__);
				return 1;
			}
			this->m_DBQuery.Clear();
			nOfs += sizeof(MISSION_INFO);
		}
		
		result = 0;
	}
	else
	{
		result = 0;
	}
	return result;
}

int LabyrinthDBSet::SaveLabyrinthInfo(BYTE* aRecv)
{
	int nOfs;
	MISSION_INFO* RecvBuf;
	SDHP_REQ_LABYRINTH_INFO_SAVE* lpRecv;
	CString qSql;

	lpRecv = (SDHP_REQ_LABYRINTH_INFO_SAVE*)aRecv;

	qSql.Format(
		"EXEC WZ_Labyrinth_Info_Save '%s', '%s', %d, %d, %d, %d, ?, %I64d, %I64d, %d, %d",
		lpRecv->szAccountID,
		lpRecv->szName,
		lpRecv->btDimensionLevel,
		lpRecv->wConfigNum,
		lpRecv->btCurrentZone,
		lpRecv->btVisitedCnt,
		lpRecv->btVisitedList,
		lpRecv->nEntireExp,
		lpRecv->nEntireMonKillCnt,
		lpRecv->nClearCnt,
		lpRecv->btClearState);

	this->m_DBQuery.WriteBlob(qSql, lpRecv->btVisitedList, sizeof(lpRecv->btVisitedList));
	this->m_DBQuery.Clear();

	if (lpRecv->btMissionCount)
	{
		nOfs = sizeof(SDHP_REQ_LABYRINTH_INFO_SAVE);
		for (int i = 0; i < lpRecv->btMissionCount; ++i)
		{
			RecvBuf = (MISSION_INFO*)&aRecv[nOfs];

			qSql.Format("EXEC WZ_Labyrinth_Mission_Insert '%s', '%s', %d, %d, %d, %d, %d", lpRecv->szAccountID, lpRecv->szName, RecvBuf->btZoneNumber, RecvBuf->btMissionType, RecvBuf->nMissionValue, RecvBuf->btIsMainMission, RecvBuf->btMainMissionOrder);

			if (!this->m_DBQuery.Exec(qSql))
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [LABYRINTH] SaveLabyrinthInfo, Fail Mission Insert Exec. %s %d", __FILE__, __LINE__);
				return 1;
			}
			this->m_DBQuery.Clear();
			nOfs += sizeof(MISSION_INFO);
		}
	}
	return 0;
}

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
	this->m_DBQuery.WriteBlob(qSql,aRecv->btVisitedList, sizeof(aRecv->btVisitedList));
	this->m_DBQuery.Clear();
	
	return TRUE;
}

//----- (004417E0) --------------------------------------------------------
int LabyrinthDBSet::UpdateLabyrinthMission(SDHP_REQ_LABYRINTH_MISSION_UPDATE *aRecv)
{
	int result;
	CString qSql;

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
			result = 0;
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD(
				"error-L3 : [LABYRINTH] UpdateLabyrinthMission #2, Fail Exec. %s %d",__FILE__,__LINE__);
			
			result = 1;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [LABYRINTH] UpdateLabyrinthMission #1, Fail Exec. %s %d", __FILE__, __LINE__);
		result = 1;
	}
	return result;
}


int LabyrinthDBSet::DeleteLabyrinthMission(char *szAccountID, char *szName)
{
	int result;
	CString qSql;

	qSql.Format("EXEC WZ_Labyrinth_Mission_Delete '%s', '%s'",szAccountID,szName);
	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		result = 0;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [LABYRINTH] DeleteLabyrinthMission, Fail Exec. %s %d", __FILE__, __LINE__);
		result = 1;
	}
	return result;
}
// 5CDD20: using guessed type int `LabyrinthDBSet::DeleteLabyrinthMission'::`2'::__LINE__Var;


int LabyrinthDBSet::EndUpdateLabyrinthInfo(char *szAccountID, char *szName, int nClearCnt, char btClearState)
{
	int result;
	CString qSql;

	qSql.Format(
		
		"EXEC WZ_Labyrinth_End_Update '%s', '%s', %d, %d",
		szAccountID,
		szName,
		nClearCnt,
		btClearState);
	
	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		result = 0;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [LABYRINTH] EndUpdateLabyrinthInfom, Fail Exec %s %d", __FILE__, __LINE__);
		result = 1;
	}
	return result;
}

//----- (00441CE0) --------------------------------------------------------
int LabyrinthDBSet::UpdateLabyrinthRewardState(char *szAccountID, char *szName, char btIsMainMission, char btRewardCheckState)
{
	int result;
	CString qSql; 

	qSql.Format("EXEC WZ_Labyrinth_Reward_Complete_Update '%s', '%s', %d, %d",szAccountID,szName,btIsMainMission,btRewardCheckState);

	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		result = 0;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [LABYRINTH] UpdateLabyrinthRewardState, Fail Exec %s %d", __FILE__, __LINE__);
		result = 1;
	}
	return result;
}



int LabyrinthDBSet::SaveLabyrinthClearLog(char *szAccountID, char *szName, int nDimensionLevel)
{
	int result;
	CString qSql;

	qSql.Format("EXEC WZ_LabyrinthClearLogSetSave '%s', '%s', %d",szAccountID,szName,nDimensionLevel);
	
	if (this->m_DBQuery.Exec(qSql))
	{
		this->m_DBQuery.Clear();
		result = 0;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [LABYRINTH] SaveLabyrinthClearLog, Fail Exec %s %d", __FILE__, __LINE__);
		result = 1;
	}
	return result;
}