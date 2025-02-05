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

#define MAX_QUESTEXP_ASK_INFO				5
#define MAX_QUESTEXP_REWARD_INFO			5
#define MAX_QUESTEXP_EPISODE				25
#define MAX_QUESTEXP_SWITCH					255
#define MAX_QUESTEXP_INFO					MAX_QUESTEXP_EPISODE
#define MAX_QUESTEXP_USER_INFO				MAX_QUESTEXP_EPISODE
#define MAX_QUESTEXP_REWARDKIND_RANDOM		5
#define MAX_QUESTEXP_ACTIVE_QUEST			10
#define MAX_QUESTEXP_JOURNAL_UI_INFO		8

typedef struct
{
	PWMSG_HEAD h;
	BYTE btQuestCnt;
	char szCharName[MAX_IDSTRING + 1];
} _PMSG_QUESTEXP_INFO, *LPPMSG_QUESTEXP_INFO;


#pragma pack(push, 1)
typedef struct _QUESTEXP_INFO
{
	_QUESTEXP_INFO()
	{
		this->dwQuestIndexID = 0;
		this->wProgState = 0;
		this->lStartDate = 0;
		this->lEndDate = 0;
		memset(this->btAskIndex, 0, sizeof(btAskIndex));
		memset(this->btAskValue, 0, sizeof(btAskValue));
		memset(this->btAskState, 0, sizeof(btAskState));
	}

	DWORD dwQuestIndexID;
	WORD wProgState;
	BYTE btAskIndex[MAX_QUESTEXP_ASK_INFO];
	BYTE btAskValue[MAX_QUESTEXP_ASK_INFO];
	BYTE btAskState[MAX_QUESTEXP_ASK_INFO];
	long lStartDate;
	long lEndDate;
} *LPQUESTEXP_INFO;

typedef struct
{
	PWMSG_HEAD head;
	BYTE btQuestCnt;
	int iUserIndex;
} PMSG_ANS_QUESTEXP_INFO, *LPPMSG_ANS_QUESTEXP_INFO;
#pragma pack(pop)

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