// ArcaBattleDBSet.h: interface for the CArcaBattleDBSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARCABATTLEDBSET_H__01C748D6_E836_4267_AF43_66BD9D34C7DC__INCLUDED_)
#define AFX_ARCABATTLEDBSET_H__01C748D6_E836_4267_AF43_66BD9D34C7DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Include\Sprodef.h"

typedef struct _tagPMSG_REQ_AB_MARK_REG_UPDATE_DS
{
	_tagPMSG_REQ_AB_MARK_REG_UPDATE_DS()
	{
		dwGuildNum = 0;
		dwMarkCnt = 0;
	}

	PBMSG_HEAD2 h; // C1:F8:FD GS->DS
	DWORD dwGuildNum;
	DWORD dwMarkCnt;
} *LPPMSG_REQ_AB_MARK_REG_UPDATE_DS;

struct _stCancelGuildNames
{
	char szGuildNames[MAX_GUILDNAMESTRING + 1];
};

struct _stGuildUnderMember
{
	BYTE btGuildMemberCnt;
	char szGuildNames[MAX_GUILDNAMESTRING + 1];
};

typedef struct _stABWinGuildInfoDS
{
	_stABWinGuildInfoDS()
	{
		memset(szGuildName, 0, MAX_GUILDNAMESTRING + 1);
		dwGuild = 0;
		wOccupyObelisk = 0;
		wObeliskGroup = 0;
	}

	char szGuildName[MAX_GUILDNAMESTRING + 1];
	DWORD dwGuild;
	WORD wOccupyObelisk;
	WORD wObeliskGroup;
};


struct _stABJoinUserInfoDS
{
	_stABJoinUserInfoDS()
	{
		memset(szGuildName, 0, MAX_GUILDNAMESTRING + 1);
		dwGuild = 0;
		memset(szUserName, 0, MAX_IDSTRING + 1);
	}

	char szGuildName[MAX_GUILDNAMESTRING + 1];
	DWORD dwGuild;
	char szUserName[MAX_IDSTRING + 1];
};


typedef struct _stABAllGuildMark
{
	_stABAllGuildMark()
	{
		dwMarkCnt = 0;
		memset(szGuildName, 0, sizeof(szGuildName));
	}

	char szGuildName[MAX_GUILDNAMESTRING + 1];
	DWORD dwMarkCnt;
};

typedef struct _stArcaBattleMarkTopRank
{
	char btRank;
	char szGuildNames[MAX_GUILDNAMESTRING + 1];
	DWORD dwMarkCnt;
};

struct _tagPMSG_REQ_AB_GUILD_JOIN_SELECT_DS
{
	PBMSG_HEAD2 h;
	char szGuildMaster[MAX_IDSTRING + 1];
	WORD wNumber;
};

struct _tagPMSG_ANS_ARCA_BATTLE_GUILD_JOIN_DS
{
	_tagPMSG_ANS_ARCA_BATTLE_GUILD_JOIN_DS()
	{
		this->btResult = 0;
		this->wNumber = 0;
	}
	PBMSG_HEAD2 h;
	char btResult;
	WORD wNumber;
};

struct _tagPMSG_REQ_ARCA_BATTLE_GUILD_JOIN_DS
{
	PBMSG_HEAD2 h;
	char szGuildMaster[MAX_IDSTRING + 1];
	char szGuildName[MAX_GUILDNAMESTRING + 1];
	DWORD dwGuild;
	WORD wNumber;
};

struct _tagPMSG_REQ_ARCA_BATTLE_GUILD_MEMBER_JOIN_DS
{
	PBMSG_HEAD2 h;
	char szCharName[MAX_IDSTRING + 1];
	char szGuildName[MAX_GUILDNAMESTRING + 1];
	DWORD dwGuild;
	WORD wNumber;
};

struct _tagPMSG_ANS_ARCA_BATTLE_GUILD_MEMBER_JOIN_DS
{
	_tagPMSG_ANS_ARCA_BATTLE_GUILD_MEMBER_JOIN_DS()
	{
		this->btResult = 0;
		this->wNumber = 0;
	}
	PBMSG_HEAD2 h;
	char btResult;
	WORD wNumber;
};

struct _tagPMSG_REQ_ARCA_BATTLE_ENTER_DS
{
	PBMSG_HEAD2 h;
	char szCharName[MAX_IDSTRING + 1];
	char btEnterSeq;
	WORD wNumber;
};

struct _tagPMSG_ANS_ARCA_BATTLE_ENTER_DS
{
	_tagPMSG_ANS_ARCA_BATTLE_ENTER_DS()
	{
		this->btResult = 0;
		this->wNumber = 0;
	}
	PBMSG_HEAD2 h;
	char btResult;
	char btEnterSeq;
	WORD wNumber;
};

struct _tagPMSG_REQ_AB_WIN_GUILD_INFO_INSERT_DS
{
	PBMSG_HEAD2 h;
	char btGuildCnt;
	WORD wMapSvrNum;
	_stABWinGuildInfoDS m_stABWinGuildInfoDS[5];
};

struct _tagPMSG_ANS_AB_WIN_GUILD_INFO_DS
{
	_tagPMSG_ANS_AB_WIN_GUILD_INFO_DS()
	{
		this->btGuildCnt = 0;
	}
	PBMSG_HEAD2 h;
	char btGuildCnt;
	_stABWinGuildInfoDS m_stABWinGuildInfoDS[5];
};

struct _tagPMSG_REQ_AB_WIN_GUILD_INFO_DS
{
	PBMSG_HEAD2 h;
	WORD wNumber;
};

struct _tagPMSG_REQ_ARCA_BATTLE_GROUP_NUM_DS
{
	PBMSG_HEAD2 h;
	char szCharName[MAX_IDSTRING + 1];
	WORD wNumber;
};

struct _tagPMSG_ANS_ARCA_BATTLE_GROUP_NUM_DS
{
	_tagPMSG_ANS_ARCA_BATTLE_GROUP_NUM_DS()
	{
		this->wGroupNum = 0;
		this->wNumber = 0;
	}
	PBMSG_HEAD2 h;
	WORD wGroupNum;
	WORD wNumber;
};

struct _tagPMSG_REQ_ARCA_BATTLE_PROC_STATE_DS
{
	PBMSG_HEAD2 h;
	char btProcState;//#Eder Adicionado por Min
};

struct _tagPMSG_ANS_ARCA_BATTLE_PROC_STATE_DS
{
	PBMSG_HEAD2 h;
	char btProcState;
};

struct __declspec(align(2)) _tagPMSG_REQ_AB_PROC_INSERT_DS
{
	PBMSG_HEAD2 h;
	unsigned __int16 wMapSvrNum;
	char btProcState;
};
typedef _tagPMSG_REQ_AB_PROC_INSERT_DS* LPPMSG_REQ_AB_PROC_INSERT_DS;


struct _tagPMSG_REQ_AB_JOIN_MEMBER_UNDER_DS
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;
};

struct _tagPMSG_ANS_AB_JOIN_MEMBER_UNDER_DS
{
	PBMSG_HEAD2 h;
	char btGuildCnt;
	_stGuildUnderMember GuildMemberCnt[6];
};

struct _tagPMSG_REQ_AB_JOIN_CANCEL_DS
{
	PBMSG_HEAD2 h;
	char btMinGuildMemNum;
	WORD wMapSvrNum;
};

struct _tagPMSG_ANS_AB_JOIN_CANCEL_DS
{
	PBMSG_HEAD2 h;
	char btGuildCnt;
	_stCancelGuildNames CancelGuildNames[6];
};

struct _tagPMSG_REQ_AB_REG_MEMBER_CNT_DS
{
	PBMSG_HEAD2 h;
	WORD wNumber;
	DWORD dwGuild;
};

struct _tagPMSG_ANS_AB_REG_MEMBER_CNT_DS
{
	PBMSG_HEAD2 h; // C1:F8:46 DS->GS
	WORD wNumber;
	BYTE btRegMemCnt;
};

struct _tagPMSG_REQ_REMOVE_ALL_GUILD_BUFF_DS
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;
};

struct _tagPMSG_ANS_REMOVE_ALL_GUILD_BUFF_DS
{
	PBMSG_HEAD2 h;
};

struct _tagPMSG_REQ_REMOVE_GUILD_BUFF_DS
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;
	char szGuildName[MAX_GUILDNAMESTRING + 1];
};

struct _tagPMSG_ANS_REMOVE_GUILD_BUFF_DS
{
	PBMSG_HEAD2 h;
	char szGuildName[MAX_GUILDNAMESTRING + 1];
};

struct _tagPMSG_REQ_AE_PLAY_DS
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;
	char btPlay;
};
struct _tagPMSG_ANS_AE_PLAY_DS
{
	_tagPMSG_ANS_AE_PLAY_DS()
	{
		this->btPlay = 0;
	}
	PBMSG_HEAD2 h;
	char btPlay;
};

struct _tagPMSG_REQ_ARCA_BATTLE_MARK_CNT_DS
{
	PBMSG_HEAD2 h;
	WORD wNumber;
	DWORD dwGuildNum;
};

struct _tagPMSG_ANS_ARCA_BATTLE_MARK_CNT_DS
{
	_tagPMSG_ANS_ARCA_BATTLE_MARK_CNT_DS()
	{
		this->btResult = 0;
		this->wNumber = 0;
		this->dwMarkCnt = 0;
	}
	PBMSG_HEAD2 h;
	char btResult;
	WORD wNumber;
	DWORD dwMarkCnt;
};

struct _tagPMSG_REQ_ARCA_BATTLE_MARK_REG_DS
{
	PBMSG_HEAD2 h;
	WORD wNumber;
	char szGuildMaster[MAX_IDSTRING + 1];
	char szGuildName[MAX_GUILDNAMESTRING + 1];
	DWORD dwMarkCnt;
	DWORD dwGuildNum;
};

struct _tagPMSG_ANS_ARCA_BATTLE_MARK_REG_DS
{
	_tagPMSG_ANS_ARCA_BATTLE_MARK_REG_DS()
	{
		this->wNumber = 0;
		this->btResult = 0;
	}
	PBMSG_HEAD2 h;
	WORD wNumber;
	char btResult;
};

struct _tagPMSG_REQ_ARCA_BATTLE_MARK_RANK_DS
{
	PBMSG_HEAD2 h;
	WORD wNumber;
	DWORD dwGuildNum;
};

struct _tagPMSG_ANS_ARCA_BATTLE_MARK_RANK_DS
{
	_tagPMSG_ANS_ARCA_BATTLE_MARK_RANK_DS()
	{
		this->wNumber = 0;
		this->dwMarkCnt = 0;
		this->btRank = 0;
		this->btGuildCnt = 0;
	}
	PBMSG_HEAD2 h;
	WORD wNumber;
	char btRank;
	DWORD dwMarkCnt;
	char btGuildCnt;
	_stArcaBattleMarkTopRank ArcaBattleMarkTopRank[6];
};

struct _tagPMSG_REQ_ARCA_BATTLE_MARK_REG_DEL_DS
{
	PBMSG_HEAD2 h;
	WORD wNumber;
	DWORD dwGuildNum;
};

struct _tagPMSG_REQ_ARCA_BATTLE_IS_TOP_RANK
{
	PBMSG_HEAD2 h;
	unsigned __int16 wNumber;
	unsigned int dwGuildNum;
};

typedef struct _tagPMSG_ANS_AB_ALL_JOIN_USER_DS
{
	PWMSG_HEAD h; // C1:E5 DS->GS
	BYTE btUserCnt;
} *LPPMSG_ANS_AB_ALL_JOIN_USER_DS;

class CArcaBattleDBSet
{
public:
	CArcaBattleDBSet();
	virtual ~CArcaBattleDBSet();

	BOOL Connect();
	void DBDeleteAllArcaBattleGuildReg();
	int DBDeleteArcaBattleCancelGuild(_stCancelGuildNames GNames[20], int GCount);
	int DBDeleteArcaBattleMarkReg(unsigned __int32 G_Number);
	void DBDeleteArcaBattleGuildReg();
	int DBDeleteArcaBattleInfo();
	int DBInsertArcaBattleGuildJoin(char* CharName, char* GName, unsigned __int32 Number, char* Result);
	int DBInsertArcaBattleGuildMemberJoin(char* CharName, char* GName, unsigned __int32 Number, char* Result);
	int DBInsertArcaBattleProc(int ProcState);
	int DBInsertArcaBattleRegMark(char* GName, unsigned __int32 GNumber, char* GMaster, unsigned __int32 MarkCnt);
	int DBInsertArcaBattleWinGuild(_stABWinGuildInfoDS a2[5], int a3);
	int DBIsArcaBattleEnter(char* CharName, int* Result);
	int DBSelectABAllJoinUser(_stABJoinUserInfoDS a2[200], int* GCount);
	int DBSelectABRegisteredMemberCnt(unsigned __int32 G_Number, BYTE* Result);
	void DBSelectArcaBattleAllGuildMark(_stABAllGuildMark a2[250], int* GCount);
	int DBSelectArcaBattleCancelGuild(struct _stCancelGuildNames GNames[6], int GuildMemCnt, unsigned __int8* GCount);
	int DBSelectArcaBattleGuildGroupNum(char* CharName, int* GroupNum);
	int DBSelectArcaBattleGuildJoin(char* CharName, BYTE* GuildNum);
	int DBSelectArcaBattleIsTopRank(unsigned __int32 G_Number);
	int DBSelectArcaBattleJoinMemberUnder(_stGuildUnderMember G_Memb[6], unsigned __int8* MembCount);
	int DBSelectArcaBattleMarkCnt(unsigned __int32 G_Number);
	int DBSelectArcaBattleMyGuildRank(unsigned __int32 G_Number, unsigned __int8* mRank, unsigned __int32* mMarkCnt);
	int DBSelectArcaBattleProc(char* ProcState);
	int DBSelectArcaBattleTopRank(_stArcaBattleMarkTopRank MarkTopRank[6], BYTE* MarkTopCount);
	int DBSelectArcaBattleWinGuild(_stABWinGuildInfoDS GuildInfo[5], int* GuildInfoCount);
	void DBUpdateArcaBattleGuildReg(_tagPMSG_REQ_AB_MARK_REG_UPDATE_DS* lpMsg);
	void DBUpdateArcaBattleGuildReg(BYTE* lpRecv, int aIndex);



public:
	CQuery m_DBQuery;
};

#endif // !defined(AFX_ARCABATTLEDBSET_H__01C748D6_E836_4267_AF43_66BD9D34C7DC__INCLUDED_)
