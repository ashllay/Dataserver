#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"

typedef struct _stCCFRankingInfo
{
	_stCCFRankingInfo()
	{
		memset(szCharName, 0, sizeof(szCharName));
		byRank = 0;
		nPoint = 0;
	}

	char szCharName[MAX_IDSTRING + 1];
	BYTE byRank;
	int nPoint;
};

typedef struct
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	int iServerCode;
	BYTE btServerKind;
	BYTE btContentsType;
	char szName[MAX_IDSTRING + 1];
} PMSG_REQ_UBF_GET_REWARD, * LPPMSG_REQ_UBF_GET_REWARD;

typedef struct
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	BYTE btResult;
	BYTE btContentsType;
	BYTE btArrayCCF_Reward[4];
	BYTE btArrayDSF_Reward[4];
	BYTE btArrayCCN_Reward[2];
	BYTE btArrayDSN_Reward[14];
} PMSG_ANS_UBF_GET_REWARD, * LPPMSG_ANS_UBF_GET_REWARD;

typedef struct
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char szUBFName[MAX_IDSTRING + 1];
} PMSG_REQ_GET_UBF_REAL_NAME, * LPPMSG_REQ_GET_UBF_REAL_NAME;

typedef struct
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char szUBFName[MAX_IDSTRING + 1];
	char szRealName[MAX_IDSTRING + 1];
	int iServerCode;
	BYTE btRetrun;
} PMSG_ANS_GET_UBF_REAL_NAME, * LPPMSG_ANS_GET_UBF_REAL_NAME;

typedef struct
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char szAccountID[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	int iServerCode;
	BOOL IsUnityBattleFieldServer;
	BYTE btObserverMode;
} PMSG_REQ_UBF_ACCOUNT_USERINFO, * LPPMSG_REQ_UBF_ACCOUNT_USERINFO;

typedef struct
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	BYTE btResult;
	BYTE btRegisterState;
	BYTE btRegisterMonth;
	BYTE btRegisterDay;
	BYTE btObserverMode;
} PMSG_ANS_UBF_ACCOUNT_USERINFO, * LPPMSG_ANS_UBF_ACCOUNT_USERINFO;

typedef struct PMSG_NOTICE
{
	PBMSG_HEAD h; // C1:0D GS->C
	BYTE type;
	BYTE btCount;
	WORD wDelay;
	DWORD dwColor;
	BYTE btSpeed;
	char Notice[256];
} *LPPMSG_NOTICE;

typedef struct _tagCHAOS_CASTLE_NOTICE
{
	PBMSG_HEAD2 h; // C1:EE:00 GS->DS / DS->GS
	BYTE btState;
	PMSG_NOTICE pNotice;
} *LPSDHP_CHAOS_CASTLE_NOTICE;


typedef struct _tagREQCHAOS_CASTLE_USER_GS
{
	PBMSG_HEAD2 h; // C1:EE:01 GS->DS
	int userIndex;
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	bool bPCBangFree;
	BYTE btEnterLevel;
} *LPSDHP_REQ_CHACOS_CASTLE_USER_COUNT_GS;

typedef struct _tagREQCHAOS_CASTLE_USER_DS
{
	PBMSG_HEAD2 h; // C1:EE:01 DS->GS
	int serverIndex;
	int userIndex;
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	bool bPCBangFree;
	BYTE btEnterLevel;
} *LPSDHP_REQ_CHACOS_CASTLE_USER_COUNT_DS;

typedef struct _tagANSCHAOS_CASTLE_USER_GS
{
	PBMSG_HEAD2 h; // C1:EE:02 GS->DS
	int serverIndex;
	int userIndex;
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	bool bPCBangFree;
	BYTE btEnterLevel;
	BYTE btCount;
	WORD wRemainTime;
} *LPSDHP_ANS_CHACOS_CASTLE_USER_COUNT_GS;

typedef struct _tagANSCHAOS_CASTLE_USER_DS
{
	PBMSG_HEAD2 h; // C1:EE:02 DS->GS
	int userIndex;
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	bool bPCBangFree;
	BYTE btEnterLevel;
	BYTE btCount;
	WORD wRemainTime;
} *LPSDHP_ANS_CHACOS_CASTLE_USER_COUNT_DS;

typedef struct _tagREQGETSPECIALIZEDSERVERINFO
{
	PBMSG_HEAD2 h; // C1:EE:03 GS->DS
	int userIndex;
	BYTE btJoinResult;
	char AccountID[MAX_IDSTRING + 1];
} *LPSDHP_REQ_GET_SPECIALIZED_SERVER_INFO;

typedef struct _tagANSGETSPECIALIZEDSERVERINFO
{
	PBMSG_HEAD2 h; // C1:EE:03 DS->GS
	int userIndex;
	BYTE btJoinResult;
	char AccountID[MAX_IDSTRING + 1];
	DWORD dwPlayTime_Normal;
	DWORD dwPlayTime_PCRoom;
	DWORD dwCloseDateTime;
} *LPSDHP_ANS_GET_SPECIALIZED_SERVER_INFO;

typedef struct _tagREQSETSPECIALIZEDSERVERINFO
{
	PBMSG_HEAD2 h; // C1:EE:04 GS->DS
	int userIndex;
	char AccountID[MAX_IDSTRING + 1];
	DWORD dwPlayTime_Normal;
	DWORD dwPlayTime_PCRoom;
	DWORD dwCloseDateTime;
} *LPSDHP_REQ_SET_SPECIALIZED_SERVER_INFO;

typedef struct _tagREQSETRUUDTOKENLOG
{
	PBMSG_HEAD2 h; // C1:EE:05 GS->DS
	int userIndex;
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	DWORD dwRuudTotal;
	DWORD dwRuudValue;
	BYTE byFlag;
} *LPSDHP_REQ_SET_RUUD_TOKEN_LOG;

typedef struct
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	BYTE btServerKind;
	char szAccountID[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	short ServerCode;
	BYTE btContentsType;
	BYTE btSubContentsType;
	int iItemCode;
	BYTE btItemCount;
	BYTE btTookState;
} PMSG_REQ_UBF_SET_REWARD_INFORMATION, * LPPMSG_REQ_UBF_SET_REWARD_INFORMATION;

typedef struct PMSG_ANS_UBF_SET_REWARD_INFORMATION
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	BYTE btReturn;
	BYTE btContentsType;
	BYTE btSubContentsType;
	int iItemCode;
	BYTE btItemCount;
} PMSG_ANS_UBF_SET_REWARD_INFORMATION, * LPPMSG_ANS_UBF_SET_REWARD_INFORMATION;

//protocol
typedef struct
{
	PBMSG_HEAD2 h;
	BYTE btDummy;
	char szAccountID[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	char szBattleFieldName[MAX_IDSTRING + 1];
	int iUserIndex;
	short ServerCode;
	BYTE btRegisterState;
	BYTE btRegisterMonth;
	BYTE btRegisterDay;
} PMSG_UBF_REGISTER_ACCOUNT_USER, * LPPMSG_UBF_REGISTER_ACCOUNT_USER;

typedef struct
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	BYTE btResult;
	WORD nLeftSec;
} PMSG_UBF_REGISTER_ACCOUNT_USER_RESULT, * LPPMSG_UBF_REGISTER_ACCOUNT_USER_RESULT;

typedef struct
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char szAccountID[MAX_IDSTRING + 1];
	BYTE btDumy1;
	char szName[MAX_IDSTRING + 1];
	BYTE btDumy2;
	short ServerCode;
	BYTE btPromotionMode;
} PMSG_UBF_ACCOUNT_USER_COPY, * LPPMSG_UBF_ACCOUNT_USER_COPY;

typedef struct
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	BYTE btResult;
	BYTE btSubResult;
} PMSG_UBF_ACCOUNT_USER_COPY_RESULT, * LPPMSG_UBF_ACCOUNT_USER_COPY_RESULT;

typedef struct
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	int iServerCode;
	char szName[MAX_IDSTRING + 1];
	BYTE btReceivedReward;
} PMSG_REQ_UBF_SET_RECEIVED_REWARD, * LPPMSG_REQ_UBF_SET_RECEIVED_REWARD;

typedef struct
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	BYTE btReturn;
	BYTE btSubReturn;
} PMSG_ANS_UBF_SET_RECEIVED_REWARD, * LPPMSG_ANS_UBF_SET_RECEIVED_REWARD;

typedef struct
{
	PBMSG_HEAD2 h;
	BYTE btDummy;
	char szAccountID[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	int iUserIndex;
	short ServerCode;
	BYTE btCanceled;
} PMSG_UBF_REQ_CANCEL_REGISTER_USER, * LPPMSG_UBF_REQ_CANCEL_REGISTER_USER;

typedef struct
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	BYTE btCanceledResult;
	BYTE btDeletedResult;
} PMSG_UBF_ANS_CANCEL_REGISTER_USER, * LPPMSG_UBF_ANS_CANCEL_REGISTER_USER;

class ChaosCastleFinalDBSet : public CDBConBase
{
public:

	ChaosCastleFinalDBSet();
	virtual ~ChaosCastleFinalDBSet();

	int Connect();
	int ReqCCFRanking(_stCCFRankingInfo* CCFRankingInfo, int nCCFtype, char* btUserCount, int nServerCategory); // idb
	void Save_CCF_Point(char* Name, int nPoint, int nCCFType); // idb
	int CCFRankRenew(char byCCFType); // idb
	void GetPermission(char* Name, int nCCFType, int* nReturn); // idb
	int Save_ChaosCastle_KillPoint(char* szName, int nPoint, int CastleIndex, int* SubResult, int* CurrntPoint, int* TotalPoint); // idb
	int GetUBFAccountUserInfo(char* szAccountID, char* szName, int nServerCode, int IsUnityBattleFieldServer, PMSG_ANS_UBF_ACCOUNT_USERINFO* pMsg); // idb
	int RegisterUBFAccountUser(char* mAccountID, char* mCharName, char* mUBFName, int ServerCode, int RegisterState, int RegisterMonth, int RegisterDay, BYTE* Result, WORD* LeftSecond);
	int CopyUBFAccountUser(char* szAccountID, char* szName, short GameServerCode, BYTE* subResult); // idb
	int CopyUBFAccountUserPromotionMode(char* szAccountID, char* szName, short GameServerCode, BYTE* subResult); // idb
	int GetWinAllRewardInfoOfUBF(char* szCharName, int nServerCode, char btServerKind, char btContentsType, PMSG_ANS_UBF_GET_REWARD* pMsg); // idb
	int SetReceivedWinnerItemOfUBF(char* szCharName, int nServerCode, char btReceived, char* SubResult); // idb
	int SetCancelToJionUnityBattlefiled(char* szAccountID, char* szName, short GameServerCode, char* subResult); // idb
	char DeleteCharacterUnityBattlefiled(char* szAccountID, char* szName, short GameServerCode); // idb
	int GetRealNameAndServerCode(char* szUBFName, PMSG_ANS_GET_UBF_REAL_NAME* pMsg); // idb
	int GetRealNameAndServerCode(char* szUBFName, char* szRealName, int* ServerCode, int IsUBFServer); // idb
	int SetRewardInfoOfUnityBattleField(char* btResult, char btServerKind, char* szAccountID, char* szName, short wServerCode, char btContentsType, char btSubContentsType, int iItemCode, char btItemCount, char btTakeState); // idb

};