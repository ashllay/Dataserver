#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"


class IllusionTempleLeagueDBSet : public CDBConBase
{
public:

	IllusionTempleLeagueDBSet();
	virtual ~IllusionTempleLeagueDBSet();

	int Connect();
	void SaveITLGuildCount(char *GName, char byCount); // idb
	void SaveITLGuildPoint(char *szGuildName, int nType, char byWin, char byLose, char byOccupiedCnt, char byEnterCount); // idb
	void UpdateITL_RewardReceived(char *CharName); // idb
	void UpdateITLUserPoint(char *UserName, char *Gname, int ITLtype, int nOccupiedCount, int nKillP, int nInvalidationCount, int nEnterCount, int nWin); // idb
	void Renew_ITLRewardList(); // idb
	void RenewITLGuildRank(char byITLType); // idb
	int LoadITLGuildRank(_stITLRankingInfo *ITLRankInfo, char *btGuildCount); // idb
	int LoadITLRewardList(_stITLRewardList *itlRewardList, char *byCount); // idb
	int LoadITLTournament(_stITLRankingInfo *ITLRanking, char *btCount, char byITLType); // idb
	void ReqGuildCount(char *GuildName, int *nEnterCount); // idb
	void ReqUserItlEnterCount(char *UserName, int *nEnterCount); // idb
};