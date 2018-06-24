// QuestExpDBSet.h: interface for the CQuestExpDBSet class.
//
//////////////////////////////////////////////////////////////////////

//#if 0
#if !defined(AFX_QUESTEXPDBSET_H__2E2B4157_4EDA_4522_8330_AE2C67318E1E__INCLUDED_)
#define AFX_QUESTEXPDBSET_H__2E2B4157_4EDA_4522_8330_AE2C67318E1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Include\Sprodef.h"

#include "DBConBase.h"

//typedef struct
//{
//	PWMSG_HEAD h;
//	BYTE btQuestCnt;
//	char szCharName[MAX_IDSTRING+1];
//}_PMSG_QUESTEXP_INFO, *LP_PMSG_QUESTEXP_INFO;

//#pragma pack(1)
//typedef struct
//{
//	PWMSG_HEAD head;
//	BYTE btQuestCnt;
//	int iUserIndex;
//}PMSG_ANS_QUESTEXP_INFO, *LPPMSG_ANS_QUESTEXP_INFO;
//#pragma pack()

class CQuestExpDBSet  : public CDBConBase
{
public:
	CQuestExpDBSet();
	virtual ~CQuestExpDBSet();

	BOOL Connect();
	BOOL DSDB_QueryQuestInfoSave(_PMSG_QUESTEXP_INFO *lpRecv);
	BOOL DSDB_QueryQuestInfoLoad(char* szCharName, _QUESTEXP_INFO *pQuestInfo, PMSG_ANS_QUESTEXP_INFO *pMsg);

};

#endif // !defined(AFX_QUESTEXPDBSET_H__2E2B4157_4EDA_4522_8330_AE2C67318E1E__INCLUDED_)
//#endif