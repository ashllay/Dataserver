// CrywolfDBSet.h: interface for the CCrywolfDBSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYWOLFDBSET_H__DE77448E_DEA3_4B5A_83A0_9F0B04EFF3DE__INCLUDED_) && defined(MU_CRYWOLF_DS_PROTOCOL_20050505)
#define AFX_CRYWOLFDBSET_H__DE77448E_DEA3_4B5A_83A0_9F0B04EFF3DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "Include\ProDef.h"
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

#endif // !defined(AFX_CRYWOLFDBSET_H__DE77448E_DEA3_4B5A_83A0_9F0B04EFF3DE__INCLUDED_)
