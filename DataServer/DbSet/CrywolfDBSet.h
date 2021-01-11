#ifndef __CRYWOLFDBSET_H__
#define __CRYWOLFDBSET_H__
#pragma once

#include "..\Include\Sprodef.h"
#include "DBConBase.h"

class CCrywolfDBSet  : public CDBConBase
{
public:
	CCrywolfDBSet();
	virtual ~CCrywolfDBSet();

	BOOL Connect();
	BOOL DSDB_QueryCrywolfStateUpdate();
	BOOL DSDB_QueryCrywolfInfoLoad(int iMapSvrGroup, LPCWP_ANS_CRYWOLFINFOLOAD lpAnsMsg);
	BOOL DSDB_QueryCrywolfInfoSave( int iMapSvrGroup, LPCWP_REQ_CRYWOLFINFOSAVE lpReqMsg);
};

#endif