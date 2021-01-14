#ifndef __CASTLEDBSET_H__
#define __CASTLEDBSET_H__
#pragma once

#include "..\Include\Sprodef.h"
#include "DBConBase.h"

typedef struct CASTLE_DATA
{
	WORD wStartYear;
	BYTE btStartMonth;
	BYTE btStartDay;
	WORD wEndYear;
	BYTE btEndMonth;
	BYTE btEndDay;
	BYTE btIsSiegeGuildList;
	BYTE btIsSiegeEnded;
	BYTE btIsCastleOccupied;
	char szCastleOwnGuild[MAX_GUILDNAMESTRING + 1];
	__int64 i64CastleMoney;
	int iTaxRateChaos;
	int iTaxRateStore;
	int iTaxHuntZone;
	int iFirstCreate;
} *LPCASTLE_DATA;

class CCastleDBSet : public CDBConBase
{
public:
	CCastleDBSet();
	virtual ~CCastleDBSet();

	BOOL Connect();
	BOOL DSDB_QueryCastleTotalInfo(int iMapSvrGroup, int iCastleEventCycle, LPCASTLE_DATA lpCastleData);
	BOOL DSDB_QueryOwnerGuildMaster(int iMapSvrGroup, LPCSP_ANS_OWNERGUILDMASTER lpOwnerGuildMaster);
	BOOL DSDB_QueryCastleNpcBuy(int iMapSvrGroup, LPCSP_REQ_NPCBUY lpNpcBuy, int* lpiResult);
	BOOL DSDB_QueryCastleNpcRepair(int iMapSvrGroup, LPCSP_REQ_NPCREPAIR lpNpcRepair, LPCSP_ANS_NPCREPAIR lpNpcRepairResult, int* lpiResult);
	BOOL DSDB_QueryCastleNpcUpgrade(int iMapSvrGroup, LPCSP_REQ_NPCUPGRADE lpNpcUpgrade);
	BOOL DSDB_QueryTaxInfo(int iMapSvrGroup, LPCSP_ANS_TAXINFO lpTaxInfo);
	BOOL DSDB_QueryTaxRateChange(int iMapSvrGroup, int iTaxType, int iTaxRate, LPCSP_ANS_TAXRATECHANGE lpTaxRateChange, int* lpiResult);
	BOOL DSDB_QueryCastleMoneyChange(int iMapSvrGroup, int iMoneyChange, __int64* i64ResultMoney, int* lpiResult);
	BOOL DSDB_QuerySiegeDateChange(int iMapSvrGroup, LPCSP_REQ_SDEDCHANGE lpSdEdChange, int* lpiResult);
	BOOL DSDB_QueryGuildMarkRegInfo(int iMapSvrGroup, char* lpszGuildName, LPCSP_ANS_GUILDREGINFO lpGuildRegInfo, int* lpiResult);
	BOOL DSDB_QuerySiegeEndedChange(int iMapSvrGroup, BOOL bIsCastleSiegeEnded, int* lpiResult);
	BOOL DSDB_QueryCastleOwnerChange(int iMapSvrGroup, LPCSP_REQ_CASTLEOWNERCHANGE lpCastleOwnerInfo, LPCSP_ANS_CASTLEOWNERCHANGE lpCastleOwnerInfoResult, int* lpiResult);
	BOOL DSDB_QueryRegAttackGuild(int iMapSvrGroup, LPCSP_REQ_REGATTACKGUILD lpRegAttackGuild, LPCSP_ANS_REGATTACKGUILD lpRegAttackGuildResult, int* lpiResult);
	BOOL DSDB_QueryRestartCastleState(int iMapSvrGroup, LPCSP_REQ_CASTLESIEGEEND lpCastleSiegeEnd, int* lpiResult);
	BOOL DSDB_QueryGuildMarkRegMark(int iMapSvrGroup, char* lpszGuildName, LPCSP_ANS_GUILDREGMARK lpGuildRegMark, int* lpiResult);
	BOOL DSDB_QueryGuildMarkReset(int iMapSvrGroup, char* lpszGuildName, LPCSP_ANS_GUILDRESETMARK lpGuildResetMark);
	BOOL DSDB_QueryGuildSetGiveUp(int iMapSvrGroup, char* lpszGuildName, BOOL bIsGiveUp, LPCSP_ANS_GUILDSETGIVEUP lpGuildSetGiveUp);
	BOOL DSDB_QueryCastleNpcRemove(int iMapSvrGroup, LPCSP_REQ_NPCREMOVE lpNpcRemove, int* lpiResult);
	BOOL DSDB_QueryResetCastleTaxInfo(int iMapSvrGroup, int* lpiResult);
	BOOL DSDB_QueryResetSiegeGuildInfo(int iMapSvrGroup, int* lpiResult);
	BOOL DSDB_QueryResetRegSiegeInfo(int iMapSvrGroup, int* lpiResult);
	BOOL DSDB_QueryCastleNpcInfo(int iMapSvrGroup, LPCSP_NPCDATA lpNpcData, int* lpiCount);
	BOOL DSDB_QueryAllGuildMarkRegInfo(int iMapSvrGroup, LPCSP_GUILDREGINFO lpGuildRegInfo, int* lpiCount);
	BOOL DSDB_QueryFirstCreateNPC(int iMapSvrGroup, LPCSP_REQ_NPCSAVEDATA lpNpcSaveData);
	BOOL DSDB_QueryCalcRegGuildList(int iMapSvrGroup, LPCSP_CALCREGGUILDLIST lpCalcRegGuildList, int* lpiCount);
	BOOL DSDB_QueryCsGuildUnionInfo(int iMapSvrGroup, char* lpszGuildName, int iCsGuildID, LPCSP_CSGUILDUNIONINFO lpCsGuildUnionInfo, int* lpiCount);
	BOOL DSDB_QueryCsClearTotalGuildInfo(int iMapSvrGroup);
	BOOL DSDB_QueryCsSaveTotalGuildInfo(int iMapSvrGroup, char* lpszGuildName, int iCsGuildID, int iCsGuildInvolved, int iCsGuildScore);
	BOOL DSDB_QueryCsSaveTotalGuildOK(int iMapSvrGroup, int* lpiResult);
	BOOL DSDB_QueryCsLoadTotalGuildInfo(int iMapSvrGroup, LPCSP_CSLOADTOTALGUILDINFO lpLoadTotalGuildInfo, int* lpiCount);
	BOOL DSDB_QueryCastleNpcUpdate(int iMapSvrGroup, LPCSP_REQ_NPCUPDATEDATA lpNpcSaveData);
};

#endif
