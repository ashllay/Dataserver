#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"

#define MAX_DSF_START_HOUR_TYPE 25
#define MAX_DSF_ROUND 15
#define MAX_DSF_MONSTER_REGEN_INFO 200

#define MAX_DSF_USER 40
#define MAX_DSF_TEAM 20
#define MAX_DSF_TEAM_USER 2

#define MAX_DSF_GO_SEMIFINAL_PARTY 80
#define MAX_DSF_GO_FINAL_PARTY 20
#define MAX_DSF_WINNER_PARTY 1

#define DSF_MIN_USER_COUNT 4

/* 672 */
struct _stDSFGoFinalPartyInfo
{
	_stDSFGoFinalPartyInfo()
	{
		memset(this->szUserName1, 0, sizeof(this->szUserName1));
		memset(this->szUserName2, 0, sizeof(this->szUserName2));
		this->wServerCode1 = -1;
		this->wServerCode2 = -1;
		this->btRank = -1;
		this->btDSFType = -1;
		this->iPoint = -1;
		this->nEnterYear = -1;
		this->btEnterMonth = -1;
		this->btEnterDay = -1;
	}
	char szUserName1[MAX_IDSTRING + 1];
	char szUserName2[MAX_IDSTRING + 1];
	WORD wServerCode1;
	WORD wServerCode2;
	char btRank;
	char btDSFType;
	int iPoint;
	int nEnterYear;
	BYTE btEnterMonth;
	BYTE btEnterDay;
};

typedef struct PMSG_REQ_DSF_CAN_PARTY_ENTER
{
	PBMSG_HEAD2 h; // C1:FC:00 GS->DS
	int iUserIndex;
	char szAccountID1[MAX_IDSTRING + 1];
	char szUserName1[MAX_IDSTRING + 1];
	char szAccountID2[MAX_IDSTRING + 1];
	char szUserName2[MAX_IDSTRING + 1];
	BYTE btDSFType;
	int iEnterYear;
	BYTE btEnterMonth;
	BYTE btEnterDay;
} *LPPMSG_REQ_DSF_CAN_PARTY_ENTER;

/* 1094 */
struct PMSG_ANS_DSF_CAN_PARTY_ENTER
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char btCount;
	char btResult;
};

/* 1095 */
struct PMSG_REQ_SAVE_DSF_USERPOINT
{
	PBMSG_HEAD2 h;
	char UserName[MAX_IDSTRING + 1];
	char GName[9];
	int nPoint;
	int Type;
	int nEnterCount;
	int nWin;
};

/* 1096 */
struct PMSG_REQ_SAVE_DSF_PARTYPOINT
{
	PBMSG_HEAD2 h;
	char szAccountID1[MAX_IDSTRING + 1];
	char szUserName1[MAX_IDSTRING + 1];
	int nUser1Level;
	char szAccountID2[MAX_IDSTRING + 1];
	char szUserName2[MAX_IDSTRING + 1];
	int nUser2Level;
	int nDSFType;
	int nPoint;
	char btEnterCnt;
	int nEnterYear;
	BYTE btEnterMonth;
	BYTE btEnterDay;
};

/* 1097 */
struct PMSG_REQ_DSF_PARTYRANKRENEW
{
	PBMSG_HEAD2 h;
	char btDSFType;
	int nEnterYear;
	BYTE btEnterMonth;
	BYTE btEnterDay;
};

/* 1098 */
typedef struct PMSG_ANS_DSF_PARTYRANKRENEW
{
	PBMSG_HEAD2 h; // C1:FC:03 DS->GS
	BYTE btResult;
} *LPPMSG_ANS_DSF_PARTYRANKRENEW;

/* 1099 */
struct PMSG_REQ_DSF_TODAY_PARTYRANK
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char btDSFType;
	int nEnterYear;
	BYTE btEnterMonth;
	BYTE btEnterDay;
};

/* 1100 */
struct PMSG_ANS_DSF_TODAY_PARTYRANK
{
	PWMSG_HEAD2 h;
	int iUserIndex;
	char btPartyCnt;
};

/* 1101 */
struct PMSG_REQ_DSF_GO_FINAL_PARTY
{
	PBMSG_HEAD2 h;
	char btDSFType;
	int nEnterYear;
	BYTE btEnterMonth;
	BYTE btEnterDay;
};

/* 1102 */
struct PMSG_ANS_DSF_GO_FINAL_PARTY
{
	PWMSG_HEAD2 h;
	char btPartyCnt;
	char btDSFType;
};

/* 1103 */
struct PMSG_REQ_SAVE_DSF_REWARD_USER
{
	PBMSG_HEAD2 h;
	char szAccountID[MAX_IDSTRING + 1];
	char szUserName[MAX_IDSTRING + 1];
	int iClass;
	char btDSFType;
	int nRewardYear;
	char btRewardMonth;
	char btRewardStartDay;
	char btRewardEndDay;
};

/* 1104 */
struct PMSG_REQ_GET_DSF_REWARD
{
	PBMSG_HEAD2 h;
	char szAccountID[MAX_IDSTRING + 1];
	char szUserName[MAX_IDSTRING + 1];
	int nServerCode;
	int nUserIndex;
	int nRewardYear;
	char btRewardMonth;
	char btRewardDay;
};

/* 1105 */
struct PMSG_ANS_GET_DSF_REWARD
{
	PBMSG_HEAD2 h;
	int nUserIndex;
	char btResult;
};

/* 1106 */
struct _tagPMSG_ANS_DSF_REWARDLIST
{
	PWMSG_HEAD2 h;
	char byCnt;
};

/* 1107 */
struct _stDSFRewardList
{
	char byRank;
	char szCharName[MAX_IDSTRING + 1];
	char szGuildName[MAX_GUILDNAMESTRING + 1];
	char byEnterCount;
	char byPoint;
	char byGotReward;
};

class CDevilSquareFinalDBSet : public CDBConBase
{
public:

	CDevilSquareFinalDBSet();
	virtual ~CDevilSquareFinalDBSet();

	int Connect();
	void ReqCanPartyEnter(char *AccountID1, char *UserName1, char *AccountID2, char *UserName2, char btDSFType, int iEnterYear, BYTE btEnterMonth, BYTE btEnterDay, int *nEnterCount, int *nResult); // idb
	void UpdateDSFUserPoint(char *UserName, char *Gname, int DSFtype, int nPoint, int nEnterCount, int nWin); // idb
	void SaveDSFPartyPoint(char *szAccountID1, char *szUserName1, int nUser1Level, char *szAccountID2, char *szUserName2, int nUser2Level, int nType, int nPoint, char btEnterCount, int nEnterYear, char btEnterMonth, char btEnterDay); // idb
	void RenewDSFPartyRank(char btDSFType, int nYear, int nMonth, int nDay); // idb
	int TodayDSFPartyRank(_stDSFPartyRankInfo *DSFRank, char *btCount, char btDSFType, int nYear, int nMonth, int nDay); // idb
	int DSFGoFinalParty(_stDSFGoFinalPartyInfo* DSFRank, unsigned char& btCount, unsigned char btDSFType, int nYear, int nMonth, int nDay);
	void InsertRewardUser(char *szAccountID, char *szUserName, int iClass, int nDSFType, int nRewardYear, char btRewardMonth, char btRewardStartDay, char btRewardEndDay); // idb
	int GetReward(char *szAccountID, char *szUserName, int nServerCode, int nRewardYear, char btRewardMonth, char btRewardDay); // idb

};