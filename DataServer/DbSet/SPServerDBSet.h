#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"


class CSPServerDBSet : public CDBConBase
{
public:

	CSPServerDBSet();
	virtual ~CSPServerDBSet();

	int Connect();
	int getSPServerPlayTime(char *AccoundID, unsigned int *dwPlayTimeNormal, unsigned int *dwPlayTimePCRoom, unsigned int *dwCloseDateTime); // idb
	int setSPServerPlayTime(char *AccoundID, unsigned int dwPlayTimeNormal, unsigned int dwPlayTimePCRoom, unsigned int dwCloseDateTime); // idb

};