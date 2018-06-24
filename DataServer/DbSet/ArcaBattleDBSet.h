#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"


class CArcaBattleDBSet : public CDBConBase
{
public:

	CArcaBattleDBSet();
	virtual ~CArcaBattleDBSet();

	int Connect();
	int DBSelectArcaBattleGuildJoin(char *szName, int *iResult); // idb
	int DBInsertArcaBattleGuildJoin(char *szName, char *szGuildName, unsigned int dwGuild, int *iResult); // idb
	int DBInsertArcaBattleGuildMemberJoin(char *szName, char *szGuildName, unsigned int dwGuild, int *iResult); // idb
	int DBInsertArcaBattleWinGuild(_stABWinGuildInfoDS *pABWinGuildInfoDS, int iGuildCnt); // idb
	int DBSelectArcaBattleWinGuild(_stABWinGuildInfoDS *pABGuildInfo, int *iGuildCnt); // idb
	int DBIsArcaBattleEnter(char *szName, int *iResult); // idb
	int DBSelectArcaBattleGuildGroupNum(char *szName, int *iGroupNum); // idb
	int DBDeleteArcaBattleInfo(); // idb
	int DBSelectArcaBattleJoinMemberUnder(_stGuildUnderMember *pGuildMemberCnt, char *btGuildCnt); // idb
	int DBInsertArcaBattleProc(int iABProc); // idb
	int DBSelectArcaBattleProc(int *iABProc); // idb
	int DBSelectArcaBattleCancelGuild(_stCancelGuildNames *pstCancelGuildNames, int iMinGuildMemNum, char *btGuildCnt); // idb
	int DBDeleteArcaBattleCancelGuild(_stCancelGuildNames *pstCancelGuildNames, int iGuildCnt); // idb
	int DBSelectABRegisteredMemberCnt(unsigned int dwGuild, char *btRegMemCnt); // idb
	int DBSelectArcaBattleIsTopRank(unsigned int dwGuildNumber); // idb
	int DBSelectArcaBattleMarkCnt(unsigned int dwGuildNumber); // idb
	int DBInsertArcaBattleRegMark(char *szGuildName, unsigned int dwGuildNum, char *szGuildMaster, unsigned int dwMarkCnt); // idb
	int DBSelectArcaBattleTopRank(_stArcaBattleMarkTopRank *pArcaBattleMarkTopRank, char *btGuildCnt); // idb
	int DBSelectArcaBattleMyGuildRank(unsigned int dwGuildNumber, char *btMyGuildRank, unsigned int *dwMarkCnt); // idb
	int DBDeleteArcaBattleMarkReg(unsigned int dwGuildNumber); // idb
	void DBDeleteAllArcaBattleGuildReg(); // idb
	void DBDeleteArcaBattleGuildReg(); // idb
	void DBUpdateArcaBattleGuildReg(BYTE *lpRecv, int aIndex); // idb
	void DBSelectArcaBattleAllGuildMark(_stABAllGuildMark *pABAllGuildMark, int *iGuildCnt); // idb
	int DBSelectABAllJoinUser(_stABJoinUserInfoDS *pABJoinUserInfo, char *btUserCnt); // idb

};