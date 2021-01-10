#ifndef __ARCABATTLEDBSET_H__
#define __ARCABATTLEDBSET_H__
#pragma once

#include "..\Include\Sprodef.h"
#include "DBConBase.h"

class CArcaBattleDBSet : public CDBConBase
{
public:
	CArcaBattleDBSet();
	virtual ~CArcaBattleDBSet();

	BOOL Connect();

	BOOL DBSelectArcaBattleGuildJoin(char* szName, int& iResult);
	BOOL DBInsertArcaBattleGuildJoin(char* szName, char* szGuildName, DWORD dwGuild, int& iResult);
	BOOL DBInsertArcaBattleGuildMemberJoin(char* szName, char* szGuildName, DWORD dwGuild, int& iResult);
	BOOL DBInsertArcaBattleWinGuild(_stABWinGuildInfoDS* pABWinGuildInfoDS, int iGuildCnt);
	BOOL DBSelectArcaBattleWinGuild(_stABWinGuildInfoDS* pABGuildInfo, int& iGuildCnt);

	BOOL DBIsArcaBattleEnter(char* szName, int& iResult);

	BOOL DBSelectArcaBattleGuildGroupNum(char* szName, int& iGroupNum);

	BOOL DBDeleteArcaBattleInfo();
	BOOL DBSelectArcaBattleJoinMemberUnder(_stGuildUnderMember* pGuildMemberCnt, BYTE& btGuildCnt);

	BOOL DBInsertArcaBattleProc(int iABProc);
	BOOL DBSelectArcaBattleProc(int& iABProc);

	BOOL DBSelectArcaBattleCancelGuild(_stCancelGuildNames* pstCancelGuildNames, int iMinGuildMemNum, BYTE& btGuildCnt);
	BOOL DBDeleteArcaBattleCancelGuild(_stCancelGuildNames* pstCancelGuildNames, int iGuildCnt);

	BOOL DBSelectABRegisteredMemberCnt(DWORD dwGuild, BYTE& btRegMemCnt);

	BOOL DBSelectArcaBattleIsTopRank(DWORD dwGuildNumber);
	BOOL DBSelectArcaBattleMarkCnt(DWORD dwGuildNumber);
	BOOL DBInsertArcaBattleRegMark(char* szGuildName, DWORD dwGuildNum, char* szGuildMaster, DWORD dwMarkCnt);
	BOOL DBSelectArcaBattleTopRank(_stArcaBattleMarkTopRank* pArcaBattleMarkTopRank, BYTE& btGuildCnt);
	BOOL DBSelectArcaBattleMyGuildRank(DWORD dwGuildNumber, BYTE& btMyGuildRank, DWORD& dwMarkCnt);
	BOOL DBDeleteArcaBattleMarkReg(DWORD dwGuildNumber);

	void DBDeleteAllArcaBattleGuildReg();
	void DBDeleteArcaBattleGuildReg();
	void DBUpdateArcaBattleGuildReg(LPBYTE lpRecv, int aIndex);

	void DBSelectArcaBattleAllGuildMark(_stABAllGuildMark* pABAllGuildMark, int& iGuildCnt);
	BOOL DBSelectABAllJoinUser(_stABJoinUserInfoDS* pABJoinUserInfo, BYTE& btUserCnt);

public:
	CQuery m_Query;
};

#endif