#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"

struct _stITLRewardList
{
	_stITLRewardList()
	{
		byRank = 0;
		memset(szCharName, 0, sizeof(szCharName));
		memset(szGuildName, 0, sizeof(szGuildName));
		byEnterCount = 0;
		byPoint = 0;
		byGotReward = 0;
	}

	BYTE byRank;
	char szCharName[MAX_IDSTRING + 1];
	char szGuildName[MAX_GUILDNAMESTRING + 1];
	BYTE byEnterCount;
	BYTE byPoint;
	BYTE byGotReward;
};

struct _stITLRankingInfo
{
	_stITLRankingInfo()
	{
		memset(szGuildName, 0, sizeof(szGuildName));
		this->byRank = 0;
		this->byITLType = 0;
		this->byWin = 0;
		this->byLose = 0;
	}
	char szGuildName[MAX_GUILDNAMESTRING + 1];
	BYTE byRank;
	BYTE byITLType;
	BYTE byWin;
	BYTE byLose;
};


struct SDHP_REQ_SAVE_ITL_GUILDPOINT
{
	PBMSG_HEAD2 h;
	char GuildName[MAX_GUILDNAMESTRING + 1];
	int nType;
	BYTE byWin;
	BYTE byLose;
	BYTE byOccupiedCnt;
	BYTE byEnterCnt;
};


struct SDHP_REQ_SAVE_ITL_GUILDCOUNT
{
	PBMSG_HEAD2 h;
	char GuildName[MAX_GUILDNAMESTRING + 1];
	BYTE byCount;
};


struct SDHP_REQ_SAVE_ITL_USERPOINT
{
	PBMSG_HEAD2 h;
	char UserName[MAX_IDSTRING + 1];
	char GName[MAX_GUILDNAMESTRING + 1];
	int nOccupiedCount;
	int nKillP;
	int nInvalidationCount;
	int Type;
	int EnterCount;
	int Win;
};


struct _tagPMSG_REQ_ITL_GUILDCOUNTREQ
{
	PBMSG_HEAD2 h;
	char GuildName[MAX_GUILDNAMESTRING + 1];
	int nUserIndex;
	WORD wMapSverNum;
};


struct _tagPMSG_ANS_ITL_GUILDCOUNTANS
{
	PBMSG_HEAD2 h;
	int nUserIndex;
	BYTE byCount;
};


struct _tagPMSG_ANS_ITL_RANKING
{
	_tagPMSG_ANS_ITL_RANKING()
	{
		this->byGuildCnt = 0;
	}
	PWMSG_HEAD2 h;
	char byGuildCnt;
};


struct _tagPMSG_ANS_ITL_GUILDCNT
{
	PWMSG_HEAD2 h;
	char byGuildCnt;
};


struct _tagPMSG_REQ_LEAGUERANK_RENEW
{
	PBMSG_HEAD2 h;
	char byITLType;
};


struct _tagPMSG_REQ_GUILDRANK_GET
{
	PBMSG_HEAD2 h;
};


struct PMSG_REQ_ITL_TOURNAMENT
{
	PBMSG_HEAD2 h;
	BYTE byITLType;
};


struct PMSG_REQ_ITL_RENEW_REWARD
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;
};


struct PMSG_REQ_ITL_GET_REWARDLIST
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;
};


struct PMSG_REQ_ITL_REWARDRECEIVED
{
	PBMSG_HEAD2 h;
	char szCharName[MAX_IDSTRING + 1];
};


struct _tagPMSG_ANS_ITL_REWARDLIST
{
	_tagPMSG_ANS_ITL_REWARDLIST()
	{
		this->byCnt = 0;
	}
	PWMSG_HEAD2 h;
	BYTE byCnt;
};


struct _tagPMSG_REQ_ITL_USERCOUNTREQ
{
	PBMSG_HEAD2 h;
	char UserName[MAX_IDSTRING + 1];
	int nUserIndex;
};


struct _tagPMSG_ANS_ITL_USERCOUNTANS
{
	PBMSG_HEAD2 h;
	int nUserIndex;
	BYTE byCount;
};

class IllusionTempleLeagueDBSet : public CDBConBase
{
public:

	IllusionTempleLeagueDBSet();
	virtual ~IllusionTempleLeagueDBSet();

	int Connect();
	void SaveITLGuildCount(char *GName, BYTE byCount); // idb
	void SaveITLGuildPoint(char *szGuildName, int nType, BYTE byWin, BYTE byLose, BYTE byOccupiedCnt, BYTE byEnterCount); // idb
	void UpdateITL_RewardReceived(char *CharName); // idb
	void UpdateITLUserPoint(char *UserName, char *Gname, int ITLtype, int nOccupiedCount, int nKillP, int nInvalidationCount, int nEnterCount, int nWin); // idb
	void Renew_ITLRewardList(); // idb
	void RenewITLGuildRank(BYTE byITLType); // idb
	int LoadITLGuildRank(_stITLRankingInfo *ITLRankInfo, int *btGuildCount); // idb
	int LoadITLRewardList(_stITLRewardList *itlRewardList, char*byCount); // idb
	int LoadITLTournament(_stITLRankingInfo *ITLRanking, char *btCount, BYTE byITLType); // idb
	void ReqGuildCount(char *GuildName, int *nEnterCount); // idb
	void ReqUserItlEnterCount(char *UserName, int *nEnterCount); // idb
};