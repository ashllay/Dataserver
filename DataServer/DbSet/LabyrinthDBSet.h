#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"

class LabyrinthDBSet : public CDBConBase
{
public:

	LabyrinthDBSet();
	virtual ~LabyrinthDBSet();

	int Connect();
	int LoadLabyrinthInfo(char *szAccountID, char *szName, int nUserIndex, char *Buffer, int *nBufferLen); // idb
	int SaveLabyrinthInfo(BYTE *aRecv); // idb
	__int64 UpdateLabyrinthInfo(SDHP_REQ_LABYRINTH_INFO_UPDATE *aRecv);
	int UpdateLabyrinthMission(SDHP_REQ_LABYRINTH_MISSION_UPDATE *aRecv); // idb
	int DeleteLabyrinthMission(char *szAccountID, char *szName); // idb
	int EndUpdateLabyrinthInfo(char *szAccountID, char *szName, int nClearCnt, char btClearState); // idb
	int UpdateLabyrinthRewardState(char *szAccountID, char *szName, char btIsMainMission, char btRewardCheckState); // idb
	int SaveLabyrinthClearLog(char *szAccountID, char *szName, int nDimensionLevel); // idb
};