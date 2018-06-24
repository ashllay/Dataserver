#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"


class EventMapEnterCount : public CDBConBase
{
public:

	EventMapEnterCount();
	virtual ~EventMapEnterCount();

	int Connect();
	int GetEventMapEnterCount(char *CharName, char *BloodCastle, char *ChaosCastle, char *DevilSquare, char *DoppelGanger, char *ImperialGuardian_Weekdays, char *IllusionTempleRenewal); // idb
	int SetEventMapEnterCount(char *CharName, char BloodCastle, char ChaosCastle, char DevilSquare, char DoppelGanger, char ImperialGuardian_Weekdays, char IllusionTempleRenewal); // idb

};