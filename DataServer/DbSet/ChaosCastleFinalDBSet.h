#ifndef __CHAOSCASTLEFINALDBSET_H__
#define __CHAOSCASTLEFINALDBSET_H__
#pragma once

#include "..\Include\Sprodef.h"
#include "DBConBase.h"


class ChaosCastleFinalDBSet : public CDBConBase
{
public:
	ChaosCastleFinalDBSet();
	virtual ~ChaosCastleFinalDBSet();

	BOOL Connect();

	BOOL ReqCCFRanking(_stCCFRankingInfo* CCFRankingInfo, int nCCFtype, BYTE& btUserCount, int nServerCategory);
	void Save_CCF_Point(char* Name, int nPoint, int nCCFType);
	BOOL CCFRankRenew(BYTE byCCFType);
	void GetPermission(char* Name, int nCCFType, int& nReturn);

	BOOL Save_ChaosCastle_KillPoint(char* szName, int nPoint, int CastleIndex, int& SubResult, int& CurrntPoint, int& TotalPoint);

	BOOL GetUBFAccountUserInfo(char* szAccountID, char* szName, int nServerCode, BOOL IsUnityBattleFieldServer, LPPMSG_ANS_UBF_ACCOUNT_USERINFO pMsg);
	BOOL RegisterUBFAccountUser(char* szAccountID, char* szName, char* szBattleName, int nServerCode, int nRegisterState, int nRegisterMonth, int nRegisterDay, BYTE& nResult, WORD& nLeftSec);
	BOOL CopyUBFAccountUser(char* szAccountID, char* szName, WORD GameServerCode, BYTE& subResult);
	BOOL CopyUBFAccountUserPromotionMode(char* szAccountID, char* szName, WORD GameServerCode, BYTE& subResult);
	BOOL GetWinAllRewardInfoOfUBF(char* szCharName, int nServerCode, BYTE btServerKind, BYTE btContentsType, LPPMSG_ANS_UBF_GET_REWARD pMsg);
	BOOL SetReceivedWinnerItemOfUBF(char* szCharName, int nServerCode, BYTE btReceived, BYTE& SubResult);
	BOOL SetCancelToJionUnityBattlefiled(char* szAccountID, char* szName, WORD GameServerCode, BYTE& subResult);
	BYTE DeleteCharacterUnityBattlefiled(char* szAccountID, char* szName, WORD GameServerCode);
	BOOL GetRealNameAndServerCode(char* szUBFName, LPPMSG_ANS_GET_UBF_REAL_NAME pMsg);
	BOOL GetRealNameAndServerCode(char* szUBFName, char* szRealName, int* ServerCode, BOOL IsUBFServer);
	BOOL SetRewardInfoOfUnityBattleField(BYTE& btResult, BYTE btServerKind, char* szAccountID, char* szName, WORD wServerCode, BYTE btContentsType, BYTE btSubContentsType, int iItemCode, BYTE btItemCount, BYTE btTakeState);

public:
	CQuery m_Query;
};

#endif