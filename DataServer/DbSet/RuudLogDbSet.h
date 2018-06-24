#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"


class CRuudLogDbSet : public CDBConBase
{
public:

	CRuudLogDbSet();
	virtual ~CRuudLogDbSet();

	int Connect();
	int setRuudTokenLog(char *AccoundID, char *Name, unsigned int dwRuudTotal, unsigned int dwRuudValue, char byFlag); // idb
};