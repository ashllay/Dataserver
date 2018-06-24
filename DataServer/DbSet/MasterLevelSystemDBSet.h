// MasterLevelSystemDBSet.h: interface for the CMasterLevelSystemDBSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MASTERLEVELSYSTEMDBSET_H__C2AB5642_4ACC_4340_969D_8AA74198B503__INCLUDED_) && defined(MASTER_LEVEL_UP_SYSTEM_20070912)
#define AFX_MASTERLEVELSYSTEMDBSET_H__C2AB5642_4ACC_4340_969D_8AA74198B503__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"

class CMasterLevelSystemDBSet  : public CDBConBase
{
public:
	CMasterLevelSystemDBSet();
	virtual ~CMasterLevelSystemDBSet();

	BOOL Connect();
	BOOL DSDB_QueryMasterLevelSystemLoad(char* szCharName, LPMLP_ANS_MASTERLEVEL_INFO lpReqInfo);
	BOOL DSDB_QueryMasterLevelSystemSave(LPMLP_REQ_MASTERLEVEL_INFOSAVE lpRecv);

};

#endif // !defined(AFX_MASTERLEVELSYSTEMDBSET_H__C2AB5642_4ACC_4340_969D_8AA74198B503__INCLUDED_)
