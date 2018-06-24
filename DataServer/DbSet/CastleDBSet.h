// CastleDBSet.h: interface for the CCastleDBSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CASTLEDBSET_H__866EE47E_B854_4D47_8664_64C3026FFE59__INCLUDED_) && defined(MU_CASTLESIEGE_DS_PROTOCOL_20041105)
#define AFX_CASTLEDBSET_H__866EE47E_B854_4D47_8664_64C3026FFE59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"

struct CASTLE_DATA 
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
	char szCastleOwnGuild[MAX_GUILDNAMESTRING+1];
	__int64 i64CastleMoney;
	int iTaxRateChaos;
	int iTaxRateStore;
	int iTaxHuntZone;
	int iFirstCreate;
};

class CCastleDBSet  : public CDBConBase
{
public:
	CCastleDBSet();
	virtual ~CCastleDBSet();
	
	BOOL Connect();
	BOOL DSDB_QueryCastleTotalInfo(int iMapSvrGroup, int iCastleEventCycle, CASTLE_DATA* lpCastleData);
	BOOL DSDB_QueryOwnerGuildMaster(int iMapSvrGroup, CSP_ANS_OWNERGUILDMASTER* lpOwnerGuildMaster);
	BOOL DSDB_QueryCastleNpcBuy(int iMapSvrGroup, CSP_REQ_NPCBUY* lpNpcBuy, int* lpiResult);
	BOOL DSDB_QueryCastleNpcRepair(int iMapSvrGroup, CSP_REQ_NPCREPAIR* lpNpcRepair, CSP_ANS_NPCREPAIR* lpNpcRepairResult,  int* lpiResult);
	BOOL DSDB_QueryCastleNpcUpgrade(int iMapSvrGroup, CSP_REQ_NPCUPGRADE* lpNpcUpgrade);
	BOOL DSDB_QueryTaxInfo(int iMapSvrGroup, CSP_ANS_TAXINFO* lpTaxInfo);
	BOOL DSDB_QueryTaxRateChange(int iMapSvrGroup, int iTaxType, int iTaxRate,  CSP_ANS_TAXRATECHANGE* lpTaxRateChange, int* lpiResult);
	BOOL DSDB_QueryCastleMoneyChange(int iMapSvrGroup, int iMoneyChange, __int64* i64ResultMoney,  int* lpiResult);
	BOOL DSDB_QuerySiegeDateChange(int iMapSvrGroup, CSP_REQ_SDEDCHANGE* lpSdEdChange, int* lpiResult);
	BOOL DSDB_QueryGuildMarkRegInfo(int iMapSvrGroup, char* lpszGuildName, CSP_ANS_GUILDREGINFO* lpGuildRegInfo,  int* lpiResult);
	BOOL DSDB_QuerySiegeEndedChange(int iMapSvrGroup, int bIsCastleSiegeEnded, int* lpiResult);
	BOOL DSDB_QueryCastleOwnerChange(int iMapSvrGroup, CSP_REQ_CASTLEOWNERCHANGE* lpCastleOwnerInfo, CSP_ANS_CASTLEOWNERCHANGE* lpCastleOwnerInfoResult,  int* lpiResult);
	BOOL DSDB_QueryRegAttackGuild(int iMapSvrGroup, CSP_REQ_REGATTACKGUILD* lpRegAttackGuild, CSP_ANS_REGATTACKGUILD* lpRegAttackGuildResult,  int* lpiResult);
	BOOL DSDB_QueryRestartCastleState(int iMapSvrGroup, CSP_REQ_CASTLESIEGEEND* lpCastleSiegeEnd, int* lpiResult);
	BOOL DSDB_QueryGuildMarkRegMark(int iMapSvrGroup, char* lpszGuildName, CSP_ANS_GUILDREGMARK* lpGuildRegMark,  int* lpiResult);
	BOOL DSDB_QueryGuildMarkReset(int iMapSvrGroup, char* lpszGuildName, CSP_ANS_GUILDRESETMARK* lpGuildResetMark);
	BOOL DSDB_QueryGuildSetGiveUp(int iMapSvrGroup, char* lpszGuildName, int bIsGiveUp,  CSP_ANS_GUILDSETGIVEUP* lpGuildSetGiveUp);
	BOOL DSDB_QueryCastleNpcRemove(int iMapSvrGroup, CSP_REQ_NPCREMOVE* lpNpcRemove, int* lpiResult);
	BOOL DSDB_QueryResetCastleTaxInfo(int iMapSvrGroup, int* lpiResult);
	BOOL DSDB_QueryResetSiegeGuildInfo(int iMapSvrGroup, int* lpiResult);
	BOOL DSDB_QueryResetRegSiegeInfo(int iMapSvrGroup, int* lpiResult);
	BOOL DSDB_QueryCastleNpcInfo(int iMapSvrGroup, CSP_NPCDATA* lpNpcData, int* lpiCount);
	BOOL DSDB_QueryAllGuildMarkRegInfo(int iMapSvrGroup, CSP_GUILDREGINFO* lpGuildRegInfo, int* lpiCount);
	BOOL DSDB_QueryFirstCreateNPC(int iMapSvrGroup, CSP_REQ_NPCSAVEDATA* lpNpcSaveData);
	BOOL DSDB_QueryCalcRegGuildList(int iMapSvrGroup, CSP_CALCREGGUILDLIST* lpCalcRegGuildList, int* lpiCount);
	BOOL DSDB_QueryCsGuildUnionInfo(int iMapSvrGroup, char* lpszGuildName, int iCsGuildID,  CSP_CSGUILDUNIONINFO* lpCsGuildUnionInfo, int* lpiCount);
	BOOL DSDB_QueryCsClearTotalGuildInfo(int iMapSvrGroup);
#ifdef ADD_CASTLE_TOTAL_GUILD_SCORE_20061123
	BOOL DSDB_QueryCsSaveTotalGuildInfo(int iMapSvrGroup, char* lpszGuildName, int iCsGuildID,  int iCsGuildInvolved, int iCsGuildScore);
#else
	BOOL DSDB_QueryCsSaveTotalGuildInfo(int iMapSvrGroup, char* lpszGuildName, int iCsGuildID,  int iCsGuildInvolved);
#endif
	BOOL DSDB_QueryCsSaveTotalGuildOK(int iMapSvrGroup, int* lpiResult);
	BOOL DSDB_QueryCsLoadTotalGuildInfo(int iMapSvrGroup, CSP_CSLOADTOTALGUILDINFO* lpLoadTotalGuildInfo, int* lpiCount);
	BOOL DSDB_QueryCastleNpcUpdate(int iMapSvrGroup, CSP_REQ_NPCUPDATEDATA* lpNpcSaveData);
};

#endif // !defined(AFX_CASTLEDBSET_H__866EE47E_B854_4D47_8664_64C3026FFE59__INCLUDED_)
