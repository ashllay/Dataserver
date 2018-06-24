#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"

class CPCBangRenewalDBSet : public CDBConBase
{
public:

	CPCBangRenewalDBSet();
	virtual ~CPCBangRenewalDBSet();

	int Connect();
	int DSDB_GetPCBangPlayTimeInfo(char *szAccountID, char *btCompleteGrade, char *btRecvGrade, unsigned int *dwPCBangPlayTime); // idb
	int DSDB_SetPCBangPlayTimeInfo(char *szAccountID, char btCompleteGrade, char btRecvGrade, unsigned int dwPCBangPlayTime); // idb
};