// QuestMonKillDBSet.h: interface for the CQuestMonKillDBSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUESTMONKILLDBSET_H__E7865BB5_E1E0_42CE_B1B8_5B8F17DC6285__INCLUDED_)
#define AFX_QUESTMONKILLDBSET_H__E7865BB5_E1E0_42CE_B1B8_5B8F17DC6285__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Include\Sprodef.h"

#include "DBConBase.h"

class CQuestMonKillDBSet  : public CDBConBase
{
public:
	CQuestMonKillDBSet();
	virtual ~CQuestMonKillDBSet();

	BOOL Connect();

	BOOL DSDB_QueryQuestMonKillInfoLoad(char* szCharName, LPSDHP_QUEST_MONSTER_KILL_INFO lpReqInfo);
	BOOL DSDB_QueryQuestMonKillInfoSave(LPSDHP_QUEST_MONSTER_KILL_INFO lpRecv);
};

#endif // !defined(AFX_QUESTMONKILLDBSET_H__E7865BB5_E1E0_42CE_B1B8_5B8F17DC6285__INCLUDED_)
