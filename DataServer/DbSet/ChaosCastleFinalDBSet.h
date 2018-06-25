#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"


class ChaosCastleFinalDBSet : public CDBConBase
{
public:

	ChaosCastleFinalDBSet();
	virtual ~ChaosCastleFinalDBSet();

	int Connect();
	int ReqCCFRanking(_stCCFRankingInfo *CCFRankingInfo, int nCCFtype, char *btUserCount, int nServerCategory); // idb
	void Save_CCF_Point(char *Name, int nPoint, int nCCFType); // idb
	int CCFRankRenew(char byCCFType); // idb
	void GetPermission(char *Name, int nCCFType, int *nReturn); // idb
	int Save_ChaosCastle_KillPoint(char *szName, int nPoint, int CastleIndex, int *SubResult, int *CurrntPoint, int *TotalPoint); // idb
	int GetUBFAccountUserInfo(char *szAccountID, char *szName, int nServerCode, int IsUnityBattleFieldServer, PMSG_ANS_UBF_ACCOUNT_USERINFO *pMsg); // idb
	int RegisterUBFAccountUser(char *szAccountID, char *szName, char *szBattleName, int nServerCode, int nRegisterState, int nRegisterMonth, int nRegisterDay, char *nResult, unsigned __int16 *nLeftSec); // idb
	bool CopyUBFAccountUser(char *szAccountID, char *szName, __int16 GameServerCode, BYTE* subResult); // idb
	bool CopyUBFAccountUserPromotionMode(char *szAccountID, char *szName, __int16 GameServerCode, BYTE* subResult); // idb
	int GetWinAllRewardInfoOfUBF(char *szCharName, int nServerCode, char btServerKind, char btContentsType, PMSG_ANS_UBF_GET_REWARD *pMsg); // idb
	int SetReceivedWinnerItemOfUBF(char *szCharName, int nServerCode, char btReceived, char *SubResult); // idb
	int SetCancelToJionUnityBattlefiled(char *szAccountID, char *szName, __int16 GameServerCode, char *subResult); // idb
	char DeleteCharacterUnityBattlefiled(char *szAccountID, char *szName, __int16 GameServerCode); // idb
	int GetRealNameAndServerCode(char *szUBFName, PMSG_ANS_GET_UBF_REAL_NAME *pMsg); // idb
	int GetRealNameAndServerCode(char *szUBFName, char *szRealName, int *ServerCode, int IsUBFServer); // idb
	int SetRewardInfoOfUnityBattleField(char *btResult, char btServerKind, char *szAccountID, char *szName, __int16 wServerCode, char btContentsType, char btSubContentsType, int iItemCode, char btItemCount, char btTakeState); // idb

};