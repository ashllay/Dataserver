#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"

class CPlayTimeEventDBSet : public CDBConBase
{
public:

	CPlayTimeEventDBSet();
	virtual ~CPlayTimeEventDBSet();

	int Connect();
	int getPlayTimeEventInfo(char *szAccountID, char *btGrade, unsigned int *dwPCBangPlayTime); // idb
	int setPlayTimeEventInfo(char *szAccountID, char btGrade, unsigned int dwPCBangPlayTime); // idb
};