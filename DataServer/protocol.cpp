#include "stdafx.h"
#include "protocol.h"
#include "Include\sprodef.h"
//#include "Include\ProDef.h"
#include "MainFrm.h"
#include "ServerPrc.h"
#include "common\winutil.h"
#include "BadSyntaxChk.h"
#include "WzItemSerial.h"
#include "LogToFile.h"

CLogToFile ITEM_SERIAL_LOG("ITEM_SERIAL_LOG", ".\\ITEM_SERIAL_LOG", TRUE);

void GetJoinInfo(LPSDHP_SERVERINFO lpMsg, short aIndex);
void GJPCharacterListRequestCS(LPSDHP_GETCHARLIST lpCLMsg, int aIndex);
void GDCharacterClose(LPSDHP_USERCLOSE lpMsg, short aIndex);
void GJPCharacterCreate(LPSDHP_CREATECHAR lpMsg, short aIndex);
void GJPCharacterDelete(LPSDHP_CHARDELETE lpMsg, short aIndex);
void GDPGetWarehouse(LPSDHP_GETWAREHOUSEDB lpMsg, int aIndex);
void GDPWarehouseNoItemSend(int aIndex, int userindex, char *szId);
void GDPSetWarehouse(LPSDHP_GETWAREHOUSEDB_SAVE lpMsg, int aIndex);
void GDPSetWarehouseMoney(LPSDHP_WAREHOUSEMONEY_SAVE lpMsg, int aIndex);
void GJPGetCharacterInfo(LPSDHP_DBCHARINFOREQUEST lpMsg, short aIndex);
void GJPSetCharacterInfo(LPSDHP_DBCHAR_INFOSAVE lpMsg, short aIndex);
void GJPSetItemSave(LPSDHP_DBCHAR_ITEMSAVE lpMsg, short aIndex);
void GDReqQuestMonKillInfo(BYTE*lpRecv, int aIndex);
void DGSendQuestMonKillInfo(char *szCharName, int iUserIndex, int aIndex);
void GDReqQuestMonKillInfoSave(BYTE*lpRecv, int aIndex);
void GetGameServerInfo(LPSDHP_GAMESERVERINFO lpMsg, short aIndex);
void DSSendResultSend(int aIndex, BYTE headcode, BYTE result);
void GDLoadMedalInfo(LPSDHP_LOAD_MEDALINFO lpMsg, int aIndex);
#ifdef MASTER_LEVEL_UP_SYSTEM_20070912
void GDReqMasterLevelInfo(LPMLP_REQ_MASTERLEVEL_INFO lpMsg, int aIndex);
void GDReqMasterLevelInfoSave(LPMLP_REQ_MASTERLEVEL_INFOSAVE lpMsg, int aIndex);
#endif
void GDSkillKeyDataRecv(LPSDHP_SKILLKEYDATA lpMsg);
void GDSkillKeyDataSend(char *name, int userindex, int aIndex);
void GDZenSave(LPSDHP_ZENSAVE lpMsg, int aIndex);
void GDItemCreate(SDHP_ITEMCREATE *lpMsg, int aIndex);
void GDPropertyItemCreate(LPSDHP_PROPERTY_ITEMCREATE lpMsg, int aIndex);
//void GDDeleteTempUserInfo(LPSDHP_DELETE_TEMPUSERINFO lpMsg);
void GDCharacterTransfer(LPSDHP_CHARACTER_TRANSFER lpMsg, int aIndex);
#ifdef DARKLORD_WORK
void GDPetItemCreate(LPSDHP_PET_ITEMCREATE lpMsg, int aIndex);
void DGGetPetItemInfo(BYTE *lpRecv, int aIndex);
void DGSetPetItemInfo(BYTE *lpRecv, int aIndex);
#endif
#ifdef MU_CASTLESIEGE_DS_PROTOCOL_20041105
void DS_GDReqCastleTotalInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqOwnerGuildMaster(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleNpcBuy(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleNpcRepair(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleNpcUpgrade(BYTE *lpRecv, int aIndex);
void DS_GDReqTaxInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqTaxRateChange(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleMoneyChange(BYTE *lpRecv, int aIndex);
void DS_GDReqSiegeDateChange(BYTE *lpRecv, int aIndex);
void DS_GDReqGuildMarkRegInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqSiegeEndedChange(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleOwnerChange(BYTE *lpRecv, int aIndex);
void DS_GDReqRegAttackGuild(BYTE *lpRecv, int aIndex);
void DS_GDReqRestartCastleState(BYTE *lpRecv, int aIndex);
void DS_GDReqMapSvrMsgMultiCast(BYTE *lpRecv, int aIndex);
void DS_GDReqRegGuildMark(BYTE *lpRecv, int aIndex);
void DS_GDReqGuildMarkReset(BYTE *lpRecv, int aIndex);
void DS_GDReqGuildSetGiveUp(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleNpcRemove(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleStateSync(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleTributeMoney(BYTE *lpRecv, int aIndex);
void DS_GDReqResetCastleTaxInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqResetSiegeGuildInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqResetRegSiegeInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleInitData(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleNpcInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqAllGuildMarkRegInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqFirstCreateNPC(BYTE *lpRecv, int aIndex);
void DS_GDReqCalcRegGuildList(BYTE *lpRecv, int aIndex);
void DS_GDReqCsGuildUnionInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqCsSaveTotalGuildInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqCsLoadTotalGuildInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleNpcUpdate(BYTE *lpRecv, int aIndex);
#endif
#ifdef MU_CRYWOLF_DS_PROTOCOL_20050505
void GDReqCrywolfSync(BYTE *lpRecv, int aIndex);
void GDReqCrywolfInfoLoad(BYTE *lpRecv, int aIndex);
void GDReqCrywolfInfoSave(BYTE *lpRecv, int aIndex);
#endif
void GDReqPeriodItemExInsert(BYTE *lpRecv, int aIndex);
void GDReqPeriodItemExDelete(BYTE *lpRecv, int aIndex);
void GDReqPeriodItemExSelect(BYTE *lpRecv, int aIndex);
void GDReqUserID(BYTE *lpRecv, int aIndex);
void DGChangeName(LPSDHP_CHANGE_NAME lpMsg, int aIndex);
#ifdef ADD_CHARCARD_SUMMONER_20080313
void GJPSetAccountInfo(LPSDHP_REQ_SETACCOUNTINFO lpMsg, int aIndex);
#endif
void GDReqQuestExpInfoSave(_PMSG_QUESTEXP_INFO *lpMsg);
void GDReqQuestExpInfoLoad(PMSG_REQ_QUESTEXP_INFO *lpMsg, int aIndex);
void GDReqLuckyItemInsert(BYTE *lpRecv, int aIndex);
void GDReqLuckyItemInsert2nd(BYTE *lpRecv, int aIndex);
void GDReqLuckyItemDelete(BYTE *lpRecv, int aIndex);
void GDReqLuckyItemSelect(BYTE *lpRecv, int aIndex);
//void GDSetExGameServerCode(LPSDHP_REQ_SET_EXGAMESERVERCODE lpMsg, int aIndex);
void GDSetExtendedInvenCount(SDHP_REQ_SET_EXTENDEDINVEN_COUNT *lpMsg, int aIndex);
void GDSetExtendedWarehouseCount(SDHP_REQ_SET_EXTENDEDWAREHOUSE_COUNT *lpMsg, int aIndex);
void GDMacroLoad(SDHP_MACRODATA *lpMsg, int aIndex);
void GDMacroSave(LPSDHP_MACRODATA lpMsg, int aIndex);
//void GDBroadcastPostMessage(BYTE *lpRecv, int aIndex);
//void DGShellExecution(LPBYTE pMsg, int aIndex);
//void DGRequestVip(LPPMSG_REQ_VIP pMsg, int aIndex);
//void DGRequestUpdateResetInfo(LPPMSG_REQ_SAVE_CHARACTER_RESET pMsg, int aIndex);
//void DGRequestResetInfo(LPPMSG_CHARACTER_RESET pMsg, int aIndex);

//season 12+
void GD_RuudTokenUpdate(SDHP_RUUDTOKENUPDATE *lpRecv);
void GDSnsLoad(SDHP_SNSDATA *lpMsg, int aIndex);
void GDSnsSave(SDHP_SNSDATA *lpMsg);
void GDUserSettingSave(SDHP_USERSETTING_SAVEDATA *lpMsg);
void GDUserSettingLoad(SDHP_USERSETTING_SAVEDATA *lpMsg, int aIndex);
void GDReqLoadMonsterKillInfo(_tagSDHP_REQ_EVENT_MONSTER_KILL_INFO *lpRecv, int aIndex);
void GDReqAddBlockChattingUser(SDHP_REQ_ADD_BLOCK_CHAT_USER_INFO *lpRecv);
void GDReqDelBlockChattingUser(SDHP_REQ_DEL_BLOCK_CHAT_USER_INFO *lpRecv);
void GDReqLoadBlockChattingUser(SDHP_REQ_BLOCK_CHAT_USER_INFO *lpRecv, int aIndex);
void GDReqSaveRestoreItemList(_SDHP_REQ_RESTORE_ITEM_LIST_SAVE *lpRecv);
void GDReqLoadRestoreItemList(_SDHP_REQ_RESTORE_ITEM_LIST *lpRecv, int aIndex);
void GDReqLabyrinthInfo(SDHP_REQ_LABYRINTH_INFO *lpRecv, int aIndex);
void GDReqLabyrinthInfoSave(BYTE *lpRecv);
void GDReqLabyrinthInfoUpdate(SDHP_REQ_LABYRINTH_INFO_UPDATE *lpRecv);
void GDReqLabyrinthMissionUpdate(SDHP_REQ_LABYRINTH_MISSION_UPDATE *lpRecv);
void GDReqLabyrinthMissionDelete(SDHP_REQ_LABYRINTH_MISSION_DELETE *lpRecv);
void GDReqLabyrinthEndUpdate(SDHP_REQ_LABYRINTH_END_UPDATE *lpRecv);
void GDReqLabyrinthRewardComplete(SDHP_REQ_LABYRINTH_REWARD_COMPLETE *lpRecv);
void GDReqLabyrinthSaveClearLog(SDHP_REQ_LABYRINTH_CLEAR_LOG_SET_SAVE *lpRecv);
void GDReqGetPCBangPlayTime(SDHP_REQ_GET_PCBANG_PLAYTIME_INFO *lpRecv, int aIndex);
void GDReqSetPCBangPlayTime(SDHP_REQ_SET_PCBANG_PLAYTIME_INFO *lpRecv);
void GDReqLoadPlayTimeEventInfo(SDHP_REQ_LOAD_PLAYTIME_EVENT_INFO *lpRecv, int aIndex);
void GDReqSavePlayTimeEventInfo(SDHP_REQ_SAVE_PLAYTIME_EVENT_INFO *lpRecv);
void GDReqSaveMonsterKillInfo(_tagSDHP_REQ_EVENT_MONSTER_KILL_INFO_SAVE *lpRecv, int aIndex);
void GDReqLoadMineSystemUPTInfo(SDHP_REQ_LOAD_MINESYSTEM_UPT_USERINFO *lpMsg, int aIndex);
void GDReqModifyMineSystemUPTInfo(SDHP_REQ_MINESYSTEM_UPT_USERINFO *lpMsg, int aIndex);
void GDReqMuunInvenSubEquipOpen(SDHP_REQ_DBMUUN_INVEN_SUB_EQUIP_OPEN *lpMsg, short aIndex);
void GDReqMuunPeriodInfoInsert(_tagSDHP_REQ_MUUN_PERIOD_INFO_INSERT *lpMsg);
void GDReqMuunPeriodInfoExpire(_tagSDHP_REQ_MUUN_PERIOD_INFO_UPDATE *lpMsg);
void GDReqMuunConditonInfoSave(_tagSDHP_REQ_MUUN_CONDITION_INFO_SAVE *lpMsg);
void GDReqMuunConditonInfoLoad(_tagSDHP_REQ_MUUN_CONDITION_INFO_LOAD *lpMsg, short aIndex);
void GDReqMuunConditonInfoDel(_tagSDHP_REQ_MUUN_CONDITION_INFO_DEL *lpMsg);
void GDSetCharacterSlotCount(SDHP_REQ_SET_CHARACTER_SLOT_COUNT *lpMsg, int aIndex);
void GDReqHuntingRecordInfo(SDHP_REQ_HUNTING_RECORD_INFO *lpRecv, int aIndex);
void GDReqHuntingRecordInfoSave(SDHP_REQ_HUNTING_RECORD_INFO_SAVE *lpRecv);
void GDReqHuntingRecordInfoUserOpen(SDHP_REQ_HUNTING_RECORD_INFO_USER_OPEN *lpRecv, int aIndex);
void GDReqHuntingRecordInfoUserOpenSave(SDHP_REQ_HUNTING_RECORD_INFO_USER_OPEN_SAVE *lpRecv);
void GDReqHuntingRecordInfo_Current(SDHP_REQ_HUNTING_RECORD_INFO_CURRENT *lpRecv, int aIndex);
void GDReqHuntingRecordInfoDelete(SDHP_REQ_DELETE_HUNTING_RECORD_INFO *lpRecv);
void GDReqGetPentagramJewel(PMSG_REQ_PENTAGRAMJEWEL *lpMsg, int aIndex);
void GDReqDelPentagramJewel(PMSG_DEL_PENTAGRAMJEWEL *lpMsg);
void GDReqSetPentagramJewel(PMSG_PENTAGRAMJEWEL_INFO *lpMsg);
void GDReqInsertPentagramJewel(PMSG_INSERT_PENTAGRAMJEWEL *lpMsg);
void GDReqInsertJewelUpgradeInfo(_tagPMSG_REQ_JEWEL_UPGRADE_INFO_INSERT_DS *lpMsg);
void GDReqPeriodBuffInsert(BYTE *lpRecv);
void GDReqPeriodBuffDelete(BYTE *lpRecv);
void GDReqPeriodBuffSelect(BYTE *lpRecv, int aIndex);
void GDReqArcaBattleMarkCnt(BYTE *lpRecv, int aIndex);
void GDReqArcaBattleAllJoinUser(_tagPMSG_REQ_AB_ALL_JOIN_USER_DS *lpMsg, int aIndex);
void GDReqEventInvenItemLoad(SDHP_REQ_DBEVENT_INVEN_LOAD *lpMsg, __int16 aIndex);
void GDReqEventInvenItemSave(_tagSDHP_REQ_DBEVENT_INVEN_SAVE *lpMsg);
void GDReqMuRummyCardSelect(_tagPMSG_REQ_MURUMMY_SELECT_DS *lpRecv, int aIndex);
void GDReqMuRummyCardInsert(_tagPMSG_REQ_MURUMMY_INSERT_DS *lpRecv);
void GDReqMuRummyScoreUpdate(_tagPMSG_REQ_MURUMMY_SCORE_UPDATE_DS *lpRecv);
void GDReqMuRummyCardUpdate(_tagPMSG_REQ_MURUMMY_UPDATE_DS *lpRecv);
void GDReqMuRummyCardDelete(_tagPMSG_REQ_MURUMMY_DELETE_DS *lpRecv);
void GDReqMuRummyCardSlotInfoUpdate(_tagPMSG_REQ_MURUMMY_SLOTUPDATE_DS *lpRecv);
void GDReqMuRummyInfoUpdate(_tagPMSG_REQ_MURUMMY_INFO_UPDATE_DS *lpRecv);
void GDReqMuRummyLogInsert(_tagPMSG_REQ_MURUMMY_LOG_INSERT_DS *lpRecv);
void GDReqBombHuntSelect(_tagPMSG_REQ_BOMB_HUNT_SELECT_DS *lpRecv, int aIndex);
void GDReqBombHuntInsert(_tagPMSG_REQ_BOMB_HUNT_INSERT_DS *lpRecv);
void GDReqBombHuntDelete(_tagPMSG_REQ_BOMB_HUNT_DELETE_DS *lpRecv);
void GDReqBombLogInsert(_tagPMSG_REQ_BOMB_HUNT_LOG_INSERT_DS *lpRecv);
void GDRequestPShopItemValue(PMSG_REQ_PSHOPITEMVALUE_INFO *lpRecv, int aIndex);
void GDUpdatePShopItemValue();
void GDAllSavePShopItemValue(PMSG_UPDATE_PSHOPITEMVALUE_INFO *lpRecv);
void GDDelPShopItemValue(PMSG_DEL_PSHOPITEM *lpRecv);
void GDMovePShopItem(PMSG_MOVE_PSHOPITEM *lpRecv);
void GD_ChaosCastleNotice(_tagCHAOS_CASTLE_NOTICE *lpRecv);
void GD_ReqChaosCastleUserCount(_tagREQCHAOS_CASTLE_USER_GS *lpRecv, int aIndex);
void GD_AnsChaosCastleUserCount(_tagANSCHAOS_CASTLE_USER_GS *lpRecv);
void GD_ReqGetSpecializedServerInfo(_tagREQGETSPECIALIZEDSERVERINFO *lpRecv, int aIndex);
void GD_ReqSetSpecializedServerInfo(_tagREQSETSPECIALIZEDSERVERINFO *lpRecv);
void GD_ReqSetRuudTokenLog(_tagREQSETRUUDTOKENLOG *lpRecv);
void GD_ITL_SaveGuildCount(SDHP_REQ_SAVE_ITL_GUILDCOUNT *lpRecv);
void GD_ITL_SaveGuildPoint(SDHP_REQ_SAVE_ITL_GUILDPOINT *lpRecv);
void GD_ITL_SaveUserPoint(SDHP_REQ_SAVE_ITL_USERPOINT *lpRecv);
void GD_ITL_LoadGuildEnterCount(_tagPMSG_REQ_ITL_GUILDCOUNTREQ *lpRecv, int aIndex);
void GD_ITL_LoadUserEnterCount(_tagPMSG_REQ_ITL_USERCOUNTREQ *lpRecv, int aIndex);
void GD_ITL_GuildTournamentGet(PMSG_REQ_ITL_TOURNAMENT *lpRecv, int aIndex);
void GD_ITL_RewardRenew(PMSG_REQ_ITL_RENEW_REWARD *lpRecv);
void GD_ITL_UpdaterewardReceived(PMSG_REQ_ITL_REWARDRECEIVED *lpRecv);
void GD_ITL_GetRewardList(PMSG_REQ_ITL_GET_REWARDLIST *lpRecv, int aIndex);
void GD_ITL_GuildRankGet(_tagPMSG_REQ_GUILDRANK_GET *lpRecv, int aIndex);
void GD_ITL_LeagueRankRenew(_tagPMSG_REQ_LEAGUERANK_RENEW *lpRecv);
void GDReqMuunInvenItemLoad(SDHP_REQ_DBMUUN_INVEN_LOAD *lpMsg, __int16 aIndex);
void GDReqMuunInvenItemSave(_tagSDHP_REQ_DBMUUN_INVEN_SAVE *lpMsg);
void GDReqMuunPeriodInfoSelect(_tagSDHP_REQ_MUUN_PERIOD_INFO_SELECT *lpMsg, __int16 aIndex);
void GDReqGremoryCaseItemInsert(_tagSDHP_REQ_GREMORY_CASE_INSERT *lpMsg, __int16 aIndex);
void GDReqGremoryCaseItemSelect(_tagSDHP_REQ_GREMORY_CASE_SELECT *lpMsg, __int16 aIndex);
void GDReqGremoryCaseItemExpire(_tagSDHP_REQ_GC_UPDATE *lpMsg, __int16 aIndex);
void GDReqGremoryCaseItemDelete(_tagSDHP_REQ_GC_UPDATE *lpMsg, __int16 aIndex);
void GDReqGremoryCaseItemRecv(_tagSDHP_REQ_GC_UPDATE *lpMsg, __int16 aIndex);
void GDReqGremoryCaseItemUpdateAndInsert(_tagSDHP_REQ_GC_UPDATE_INSERT *lpMsg, __int16 aIndex);
void GDReqArcaBattleGuildJoinSelect(_tagPMSG_REQ_AB_GUILD_JOIN_SELECT_DS *lpMsg, int aIndex);
void GDReqArcaBattleGuildJoin(_tagPMSG_REQ_ARCA_BATTLE_GUILD_JOIN_DS *lpMsg, int aIndex);
void GDReqArcaBattleGuildMemberJoin(_tagPMSG_REQ_ARCA_BATTLE_GUILD_MEMBER_JOIN_DS *lpMsg, int aIndex);
void GDReqInsertArcaBattleWinGuild(_tagPMSG_REQ_AB_WIN_GUILD_INFO_INSERT_DS *lpMsg);
void GDReqSelectArcaBattleWinGuildInfo(_tagPMSG_REQ_AB_WIN_GUILD_INFO_DS *lpMsg, int aIndex);
void GDReqArcaBattleEnter(_tagPMSG_REQ_ARCA_BATTLE_ENTER_DS *lpMsg, int aIndex);
void GDReqArcaBattleGuildGroupNum(_tagPMSG_REQ_ARCA_BATTLE_GROUP_NUM_DS *lpMsg, int aIndex);
void GDReqArcaBattleInfoDelete();
void GDReqSelectArcaBattleProc(_tagPMSG_REQ_ARCA_BATTLE_PROC_STATE_DS *lpMsg, int aIndex);
void GDReqArcaBattleJoinMemberUnder(_tagPMSG_REQ_AB_JOIN_MEMBER_UNDER_DS *lpMsg);
void GDReqABLessGuildMemberCancel(_tagPMSG_REQ_AB_JOIN_CANCEL_DS *lpMsg);
void GDReqRegisteredMemberCnt(_tagPMSG_REQ_AB_REG_MEMBER_CNT_DS *lpMsg, int aIndex);
void GDReqRemoveAllGuildBuffMultiCast(_tagPMSG_REQ_REMOVE_ALL_GUILD_BUFF_DS *lpMsg);
void GDReqRemoveGuildBuffMultiCast(_tagPMSG_REQ_REMOVE_GUILD_BUFF_DS *lpMsg);
void GDReqArcaBattleMarkReg(BYTE *lpRecv, int aIndex);
void GDReqArcaBattleRank(BYTE *lpRecv, int aIndex);
void GDReqArcaBattleMarkRegDel(BYTE *lpRecv);
void GDReqArcaBattleIsTopRank(BYTE *lpRecv, int aIndex);
void GDReqArcaBattleAllGuildMarkCnt(int aIndex);
void GDReqInsertArcaBattleProc(BYTE *lpRecv);
void GDReqAcheronPlayProc(BYTE *lpRecv);
void GD_Save_ChaosCastle_KillPoint(_tagPMSG_REQ_SAVE_CHAOSCASTLE_KILLPOINT *lpRecv, int aIndex);
void GD_CCF_Point_Save(SDHP_REQ_CCF_RESULT *lpRecv);
void GD_CCF_RankigReq(SDHP_REQ_CCF_RANKING_REQ *lpRecv, int aIndex);
void GD_CCFRankRenew(SDHP_RENEW_RANKING *lpRecv);
void GD_CCF_Info_AllSend(SDHP_SEND_CCF_INFO *lpRecv);
void GD_CCF_GetPermission(SDHP_REQ_CCF_GETPERMISSION *lpRecv, int aIndex);
void GDReqUBFAccountUserInfo(PMSG_REQ_UBF_ACCOUNT_USERINFO *lpRecv, int aIndex);
void GDReqUBFAccountUserRegister(PMSG_UBF_REGISTER_ACCOUNT_USER *lpRecv, int aIndex);
void GDReqUBFAccountUserCopy(PMSG_UBF_ACCOUNT_USER_COPY *lpRecv, int aIndex);
void GDReqUBFCopyPetItemInfo(BYTE *lpRecv);
void GDReqUBFWinInfo(PMSG_REQ_UBF_GET_REWARD *lpRecv, int aIndex);
void GDReqSetReceivedWinnerItem(PMSG_REQ_UBF_SET_RECEIVED_REWARD *lpRecv, int aIndex);
void GDReqUBFCancel(PMSG_UBF_REQ_CANCEL_REGISTER_USER *lpRecv, int aIndex);
void GDReqGetRealNameAndServerCode(PMSG_REQ_GET_UBF_REAL_NAME *lpRecv, int aIndex);
void GDReqSaveRewardInfoOfUnityBattleField(PMSG_REQ_UBF_SET_REWARD_INFORMATION *lpRecv, int aIndex);
void GD_DSF_CanPartyEnter(PMSG_REQ_DSF_CAN_PARTY_ENTER *lpRecv, int aIndex);
void GD_DSF_SaveUserPoint(PMSG_REQ_SAVE_DSF_USERPOINT *lpRecv);
void GD_DSF_SavePartyPoint(PMSG_REQ_SAVE_DSF_PARTYPOINT *lpRecv);
void GD_DSF_PartyRankRenew(PMSG_REQ_DSF_PARTYRANKRENEW *lpRecv, int aIndex);
void GD_DSF_TodayPartyRank(PMSG_REQ_DSF_TODAY_PARTYRANK *lpRecv, int aIndex);
void GD_DSF_GoFinalParty(PMSG_REQ_DSF_GO_FINAL_PARTY *lpRecv, int aIndex);
void GD_DSF_InsertRewardUser(PMSG_REQ_SAVE_DSF_REWARD_USER *lpRecv);
void GD_DSF_ReqGetReward(PMSG_REQ_GET_DSF_REWARD *lpRecv, int aIndex);
void GD_Req_Get_EventMapEnterCount(SDHP_GET_EVENTMAPENTERCOUNT *lpRecv, int aIndex);
void GD_Req_Set_EventMapEnterCount(SDHP_SET_EVENTMAPENTERCOUNT *lpRecv);
void GD_ReqEventMapIntegration_AllNotify(SDHP_SEND_EVENTMAP_INFO_ALL_SVR *lpRecv);

//--
struct PMSG_DEFAULT
{
	PBMSG_HEAD h;
	BYTE subcode;
};

void ProtocolCore(BYTE protoNum, BYTE *aRecv, int aLen, short aIndex)
{
	if (protoNum > 0)
	{
		cAM.SetMode(AM_ACTIVE);
	}
	LogAdd("Protocol:0x%x", protoNum);
	switch (protoNum)
	{
	case 0:
		GetJoinInfo((SDHP_SERVERINFO *)aRecv, aIndex);
		break;
	case 1:
		GJPCharacterListRequestCS((SDHP_GETCHARLIST *)aRecv, aIndex);//fuckin fucked
		break;
	case 2:
		GDCharacterClose((SDHP_USERCLOSE *)aRecv, aIndex);
		break;
	case 4:
		GJPCharacterCreate((SDHP_CREATECHAR *)aRecv, aIndex);
		break;
	case 5:
		GJPCharacterDelete((SDHP_CHARDELETE *)aRecv, aIndex);
		break;
	case 6:
		GJPGetCharacterInfo((SDHP_DBCHARINFOREQUEST *)aRecv, aIndex);
		break;
	case 7:
		GJPSetCharacterInfo((SDHP_DBCHAR_INFOSAVE *)aRecv, aIndex);
		break;
	case 8:
		GDPGetWarehouse((SDHP_GETWAREHOUSEDB *)aRecv, aIndex);
		break;
	case 9:
		GDPSetWarehouse((SDHP_GETWAREHOUSEDB_SAVE *)aRecv, aIndex);
		break;
	case 0x11:
		GJPSetItemSave((SDHP_DBCHAR_ITEMSAVE *)aRecv, aIndex);
		break;
	case 0x12:
		GDPSetWarehouseMoney((SDHP_WAREHOUSEMONEY_SAVE *)aRecv, aIndex);
		break;
	case 0x13:
		GDReqQuestMonKillInfo(aRecv, aIndex);
		break;
	case 0x14:
		GDReqQuestMonKillInfoSave(aRecv, aIndex);
		break;
	case 0x16:
		DGChangeName((SDHP_CHANGE_NAME *)aRecv, aIndex);
		break;
	case 0x17:
		GDMacroLoad((SDHP_MACRODATA *)aRecv, aIndex);
		break;
	case 0x18:
		GDMacroSave((SDHP_MACRODATA *)aRecv, aIndex);
		break;
		//s12
	case 0x19:
		GD_RuudTokenUpdate((SDHP_RUUDTOKENUPDATE *)aRecv);
		break;
	case 0x20:
		GetGameServerInfo((SDHP_GAMESERVERINFO *)aRecv, aIndex);
		break;
		//S12
	case 0x21:
		GDSnsLoad((SDHP_SNSDATA *)aRecv, aIndex);
		break;
	case 0x22:
		GDSnsSave((SDHP_SNSDATA *)aRecv);
		break;
	case 0x23:
		GDUserSettingLoad((SDHP_USERSETTING_SAVEDATA *)aRecv, aIndex);
		break;
	case 0x24:
		GDUserSettingSave((SDHP_USERSETTING_SAVEDATA *)aRecv);
		break;
	case 0x2D:
		GDLoadMedalInfo((SDHP_LOAD_MEDALINFO *)aRecv, aIndex);
		break;
#ifdef MASTER_LEVEL_UP_SYSTEM_20070912
	case 0x30:
		GDReqMasterLevelInfo((MLP_REQ_MASTERLEVEL_INFO *)aRecv, aIndex);
		break;
	case 0x31:
		GDReqMasterLevelInfoSave((MLP_REQ_MASTERLEVEL_INFOSAVE *)aRecv, aIndex);
		break;
#endif
		//season12
	case 0x3E:
	{
		PMSG_DEFAULT * lpDef = (PMSG_DEFAULT*)aRecv;
		if (lpDef->subcode == 1)
		{
			GDReqLoadMonsterKillInfo((_tagSDHP_REQ_EVENT_MONSTER_KILL_INFO *)aRecv, aIndex);
		}
		else if (lpDef->subcode == 2)
		{
			GDReqSaveMonsterKillInfo((_tagSDHP_REQ_EVENT_MONSTER_KILL_INFO_SAVE *)aRecv, aIndex);
		}
		break;
	}
	case 0x4C:
	{
		PMSG_DEFAULT * lpDef = (PMSG_DEFAULT*)aRecv;
		if (lpDef->subcode)
		{
			if (lpDef->subcode == 1)
				GDReqLoadMineSystemUPTInfo((SDHP_REQ_LOAD_MINESYSTEM_UPT_USERINFO *)aRecv, aIndex);
		}
		else
		{
			GDReqModifyMineSystemUPTInfo((SDHP_REQ_MINESYSTEM_UPT_USERINFO *)aRecv, aIndex);
		}
		break;
	}
	case 0x4E:
	{
		PMSG_DEFAULT * lpDef = (PMSG_DEFAULT*)aRecv;
		switch (lpDef->subcode)
		{
		case 0:
			GDReqMuunInvenSubEquipOpen((SDHP_REQ_DBMUUN_INVEN_SUB_EQUIP_OPEN *)aRecv, aIndex);
			LogAddC(2, "GDReqMuunInvenSubEquipOpen");
			break;
		case 0x20:
			GDReqMuunPeriodInfoSelect((_tagSDHP_REQ_MUUN_PERIOD_INFO_SELECT *)aRecv, aIndex);
			LogAddC(2, "GDReqMuunPeriodInfoSelect");
			break;
		case 0x21:
			GDReqMuunPeriodInfoInsert((_tagSDHP_REQ_MUUN_PERIOD_INFO_INSERT *)aRecv);
			LogAddC(2, "GDReqMuunPeriodInfoInsert");
			break;
		case 0x22:
			GDReqMuunPeriodInfoExpire((_tagSDHP_REQ_MUUN_PERIOD_INFO_UPDATE *)aRecv);
			LogAddC(2, "GDReqMuunPeriodInfoExpire");
			break;
		case 0x23:
			GDReqMuunConditonInfoSave((_tagSDHP_REQ_MUUN_CONDITION_INFO_SAVE *)aRecv);
			LogAddC(2, "GDReqMuunConditonInfoSave");
			break;
		case 0x24:
			GDReqMuunConditonInfoLoad((_tagSDHP_REQ_MUUN_CONDITION_INFO_LOAD *)aRecv, aIndex);
			LogAddC(2, "GDReqMuunConditonInfoLoad");
			break;
		case 0x25:
			GDReqMuunConditonInfoDel((_tagSDHP_REQ_MUUN_CONDITION_INFO_DEL *)aRecv);
			LogAddC(2, "GDReqMuunConditonInfoDel");
			break;
		default:
			return;
		}
		break;
	}
	//--
	case 0x52:
		GDItemCreate((SDHP_ITEMCREATE *)aRecv, aIndex);
		break;
	case 0x54:
		GDPropertyItemCreate((SDHP_PROPERTY_ITEMCREATE *)aRecv, aIndex);
		break;
#ifdef DARKLORD_WORK
	case 0x55:
		GDPetItemCreate((SDHP_PET_ITEMCREATE *)aRecv, aIndex);
		break;
	case 0x56:
		DGGetPetItemInfo(aRecv, aIndex);
		break;
	case 0x57:
		DGSetPetItemInfo(aRecv, aIndex);
		break;
#endif
	case 0x60:
		GDSkillKeyDataRecv((SDHP_SKILLKEYDATA *)aRecv);
		break;
		//season12
	case 0x6E:
	{
		PMSG_DEFAULT * lpDef = (PMSG_DEFAULT*)aRecv;
		if (lpDef->subcode)
		{
			if (lpDef->subcode == 1)
			{
				GDReqAddBlockChattingUser((SDHP_REQ_ADD_BLOCK_CHAT_USER_INFO *)aRecv);
			}
			else if (lpDef->subcode == 2)
			{
				GDReqDelBlockChattingUser((SDHP_REQ_DEL_BLOCK_CHAT_USER_INFO *)aRecv);
			}
		}
		else
		{
			GDReqLoadBlockChattingUser((SDHP_REQ_BLOCK_CHAT_USER_INFO *)aRecv, aIndex);
		}
		break;
	}
	case 0x6F:
	{
		PMSG_DEFAULT * lpDef = (PMSG_DEFAULT*)aRecv;
		if (lpDef->subcode)
		{
			if (lpDef->subcode == 1)
				GDReqSaveRestoreItemList((_SDHP_REQ_RESTORE_ITEM_LIST_SAVE *)aRecv);
		}
		else
		{
			GDReqLoadRestoreItemList((_SDHP_REQ_RESTORE_ITEM_LIST *)aRecv, aIndex);
		}
		break;
	}
	case 0x77:
	{
		PMSG_DEFAULT * lpDef = (PMSG_DEFAULT*)aRecv;

		switch (lpDef->subcode)
		{
		case 0:
			GDReqLabyrinthInfo((SDHP_REQ_LABYRINTH_INFO *)aRecv, aIndex);
			break;
		case 1:
			GDReqLabyrinthInfoSave(aRecv);
			break;
		case 2:
			GDReqLabyrinthInfoUpdate((SDHP_REQ_LABYRINTH_INFO_UPDATE *)aRecv);
			break;
		case 3:
			GDReqLabyrinthMissionUpdate((SDHP_REQ_LABYRINTH_MISSION_UPDATE *)aRecv);
			break;
		case 4:
			GDReqLabyrinthMissionDelete((SDHP_REQ_LABYRINTH_MISSION_DELETE *)aRecv);
			break;
		case 5:
			GDReqLabyrinthEndUpdate((SDHP_REQ_LABYRINTH_END_UPDATE *)aRecv);
			break;
		case 6:
			GDReqLabyrinthRewardComplete((SDHP_REQ_LABYRINTH_REWARD_COMPLETE *)aRecv);
			break;
		case 7:
			GDReqLabyrinthSaveClearLog((SDHP_REQ_LABYRINTH_CLEAR_LOG_SET_SAVE *)aRecv);
			break;
		default:
			return;
		}
		break;
	}
	case 0x79:
	{
		PMSG_DEFAULT * lpDef = (PMSG_DEFAULT*)aRecv;

		switch (lpDef->subcode)
		{
		case 1:
			GDReqGetPCBangPlayTime((SDHP_REQ_GET_PCBANG_PLAYTIME_INFO *)aRecv, aIndex);
			break;
		case 2:
			GDReqSetPCBangPlayTime((SDHP_REQ_SET_PCBANG_PLAYTIME_INFO *)aRecv);
			break;
		case 3:
			GDReqLoadPlayTimeEventInfo((SDHP_REQ_LOAD_PLAYTIME_EVENT_INFO *)aRecv, aIndex);
			break;
		case 4:
			GDReqSavePlayTimeEventInfo((SDHP_REQ_SAVE_PLAYTIME_EVENT_INFO *)aRecv);
			break;
		default:
			return;
		}
		break;
	}
#ifdef MU_CASTLESIEGE_DS_PROTOCOL_20041105
	case 0x80:
	{
		PMSG_DEFAULT* lpDef = (PMSG_DEFAULT*)aRecv;

		switch (lpDef->subcode)
		{
		case 0:
			DS_GDReqCastleTotalInfo(aRecv, aIndex);
			break;
		case 1:
			DS_GDReqOwnerGuildMaster(aRecv, aIndex);
			break;
		case 3:
			DS_GDReqCastleNpcBuy(aRecv, aIndex);
			break;
		case 4:
			DS_GDReqCastleNpcRepair(aRecv, aIndex);
			break;
		case 5:
			DS_GDReqCastleNpcUpgrade(aRecv, aIndex);
			break;
		case 6:
			DS_GDReqTaxInfo(aRecv, aIndex);
			break;
		case 7:
			DS_GDReqTaxRateChange(aRecv, aIndex);
			break;
		case 8:
			DS_GDReqCastleMoneyChange(aRecv, aIndex);
			break;
		case 9:
			DS_GDReqSiegeDateChange(aRecv, aIndex);
			break;
		case 0xA:
			DS_GDReqGuildMarkRegInfo(aRecv, aIndex);
			break;
		case 0xB:
			DS_GDReqSiegeEndedChange(aRecv, aIndex);
			break;
		case 0xC:
			DS_GDReqCastleOwnerChange(aRecv, aIndex);
			break;
		case 0xD:
			DS_GDReqRegAttackGuild(aRecv, aIndex);
			break;
		case 0xE:
			DS_GDReqRestartCastleState(aRecv, aIndex);
			break;
		case 0xF:
			DS_GDReqMapSvrMsgMultiCast(aRecv, aIndex);
			break;
		case 0x10:
			DS_GDReqRegGuildMark(aRecv, aIndex);
			break;
		case 0x11:
			DS_GDReqGuildMarkReset(aRecv, aIndex);
			break;
		case 0x12:
			DS_GDReqGuildSetGiveUp(aRecv, aIndex);
			break;
		case 0x16:
			DS_GDReqCastleNpcRemove(aRecv, aIndex);
			break;
		case 0x17:
			DS_GDReqCastleStateSync(aRecv, aIndex);
			break;
		case 0x18:
			DS_GDReqCastleTributeMoney(aRecv, aIndex);
			break;
		case 0x19:
			DS_GDReqResetCastleTaxInfo(aRecv, aIndex);
			break;
		case 0x1A:
			DS_GDReqResetSiegeGuildInfo(aRecv, aIndex);
			break;
		case 0x1B:
			DS_GDReqResetRegSiegeInfo(aRecv, aIndex);
			break;
		}
	}
	break;
	case 0x81:
		DS_GDReqCastleInitData(aRecv, aIndex);
		break;
	case 0x82:
		DS_GDReqCastleNpcInfo(aRecv, aIndex);
		break;
	case 0x83:
		DS_GDReqAllGuildMarkRegInfo(aRecv, aIndex);
		break;
	case 0x84:
		DS_GDReqFirstCreateNPC(aRecv, aIndex);
		break;
	case 0x85:
		DS_GDReqCalcRegGuildList(aRecv, aIndex);
		break;
	case 0x86:
		DS_GDReqCsGuildUnionInfo(aRecv, aIndex);
		break;
	case 0x87:
		DS_GDReqCsSaveTotalGuildInfo(aRecv, aIndex);
		break;
	case 0x88:
		DS_GDReqCsLoadTotalGuildInfo(aRecv, aIndex);
		break;
	case 0x89:
		DS_GDReqCastleNpcUpdate(aRecv, aIndex);
		break;

#ifdef ADD_CHARCARD_SUMMONER_20080313
	case 0xA2:
		GJPSetAccountInfo((SDHP_REQ_SETACCOUNTINFO *)aRecv, aIndex);
		break;
#endif
		//S12
	case 0xA5:
		GDSetCharacterSlotCount((SDHP_REQ_SET_CHARACTER_SLOT_COUNT *)aRecv, aIndex);
		break;
		//--
#endif
#ifdef MU_CRYWOLF_DS_PROTOCOL_20050505
	case 0xB0:
		GDReqCrywolfSync(aRecv, aIndex);
		break;
	case 0xB1:
		GDReqCrywolfInfoLoad(aRecv, aIndex);
		break;
	case 0xB2:
		GDReqCrywolfInfoSave(aRecv, aIndex);
		break;
#endif
	case 0xBC:
	{
		PMSG_DEFAULT * lpDef = (PMSG_DEFAULT*)aRecv;

		switch (lpDef->subcode)
		{
		case 0x10:
			GDReqHuntingRecordInfo((SDHP_REQ_HUNTING_RECORD_INFO *)aRecv, aIndex);
			break;
		case 0x12:
			GDReqHuntingRecordInfoUserOpen((SDHP_REQ_HUNTING_RECORD_INFO_USER_OPEN *)aRecv, aIndex);
			break;
		case 0x13:
			GDReqHuntingRecordInfoUserOpenSave((SDHP_REQ_HUNTING_RECORD_INFO_USER_OPEN_SAVE *)aRecv);
			break;
		case 0x14:
			GDReqHuntingRecordInfo_Current((SDHP_REQ_HUNTING_RECORD_INFO_CURRENT *)aRecv, aIndex);
			break;
		case 0x15:
			GDReqHuntingRecordInfoDelete((SDHP_REQ_DELETE_HUNTING_RECORD_INFO *)aRecv);
			break;
		default:
			if (lpDef->subcode == 17)
				GDReqHuntingRecordInfoSave((SDHP_REQ_HUNTING_RECORD_INFO_SAVE *)aRecv);
			break;
		}
		break;
	}
	case 0xCF:
		GDCharacterTransfer((SDHP_CHARACTER_TRANSFER *)aRecv, aIndex);
		break;
#if 0
	case 0xCE:
		GDDeleteTempUserInfo((SDHP_DELETE_TEMPUSERINFO *)aRecv);
		break;
#endif
	case 0xD1:
	{
		PMSG_DEFAULT* lpDef = (PMSG_DEFAULT*)aRecv;

		switch (lpDef->subcode)
		{
		case 1:
			GDReqPeriodItemExInsert(aRecv, aIndex);
			break;
		case 2:
			GDReqPeriodItemExDelete(aRecv, aIndex);
			break;
		case 3:
			GDReqPeriodItemExSelect(aRecv, aIndex);
			break;
		case 0x20:
			GDReqLuckyItemSelect(aRecv, aIndex);
			break;
		case 0x22:
			GDReqLuckyItemInsert(aRecv, aIndex);
			break;
		case 0x23:
			GDReqLuckyItemDelete(aRecv, aIndex);
			break;
		case 0x24:
			GDReqLuckyItemInsert2nd(aRecv, aIndex);
			break;
		}
	}
	break;
	case 0xD3:
	{
		PMSG_DEFAULT* lpDef = (PMSG_DEFAULT*)aRecv;

		switch (lpDef->subcode)
		{
		case 1:
			GDReqUserID(aRecv, aIndex);
			break;
		}
	}
	break;
	case 0xD5:
		GDSetExtendedInvenCount((SDHP_REQ_SET_EXTENDEDINVEN_COUNT *)aRecv, aIndex);
		break;
	case 0xD6:
		GDSetExtendedWarehouseCount((SDHP_REQ_SET_EXTENDEDWAREHOUSE_COUNT *)aRecv, aIndex);
		break;
	case 0xE0:
		GDReqGetPentagramJewel((PMSG_REQ_PENTAGRAMJEWEL *)aRecv, aIndex);
		break;
	case 0xE1:
		GDReqSetPentagramJewel((PMSG_PENTAGRAMJEWEL_INFO *)aRecv);
		break;
	case 0xE2:
		GDReqDelPentagramJewel((PMSG_DEL_PENTAGRAMJEWEL *)aRecv);
		break;
	case 0xE3:
		GDReqInsertPentagramJewel((PMSG_INSERT_PENTAGRAMJEWEL *)aRecv);
		break;
	case 0xE4:
	{
		PMSG_DEFAULT * lpDef = (PMSG_DEFAULT*)aRecv;

		switch (lpDef->subcode)
		{
		case 1:
			GDReqPeriodBuffInsert(aRecv);
			break;
		case 2:
			GDReqPeriodBuffDelete(aRecv);
			break;
		case 3:
			GDReqPeriodBuffSelect(aRecv, aIndex);
			break;
		}
		break;
	}
	case 0xE5:
		GDReqArcaBattleAllJoinUser((_tagPMSG_REQ_AB_ALL_JOIN_USER_DS *)aRecv, aIndex);
		break;
	case 0xE6:
		GDReqEventInvenItemLoad((SDHP_REQ_DBEVENT_INVEN_LOAD *)aRecv, aIndex);
		break;
	case 0xE7:
		GDReqEventInvenItemSave((_tagSDHP_REQ_DBEVENT_INVEN_SAVE *)aRecv);
		break;
	case 0xE8:
	{
		PMSG_DEFAULT * lpDef = (PMSG_DEFAULT*)aRecv;
		switch (lpDef->subcode)
		{
		case 0:
			GDReqMuRummyCardSelect((_tagPMSG_REQ_MURUMMY_SELECT_DS *)aRecv, aIndex);
			LogAddC(2, "GDReqMuRummyCardSelect");
			break;
		case 1:
			GDReqMuRummyCardInsert((_tagPMSG_REQ_MURUMMY_INSERT_DS *)aRecv);
			LogAddC(2, "GDReqMuRummyCardInsert");
			break;
		case 2:
			GDReqMuRummyScoreUpdate((_tagPMSG_REQ_MURUMMY_SCORE_UPDATE_DS *)aRecv);
			LogAddC(2, "GDReqMuRummyScoreUpdate");
			break;
		case 3:
			GDReqMuRummyCardUpdate((_tagPMSG_REQ_MURUMMY_UPDATE_DS *)aRecv);
			LogAddC(2, "GDReqMuRummyCardUpdate");
			break;
		case 4:
			GDReqMuRummyCardDelete((_tagPMSG_REQ_MURUMMY_DELETE_DS *)aRecv);
			LogAddC(2, "GDReqMuRummyCardDelete");
			break;
		case 5:
			GDReqMuRummyCardSlotInfoUpdate((_tagPMSG_REQ_MURUMMY_SLOTUPDATE_DS *)aRecv);
			LogAddC(2, "GDReqMuRummyCardSlotInfoUpdate");
			break;
		case 6:
			GDReqMuRummyInfoUpdate((_tagPMSG_REQ_MURUMMY_INFO_UPDATE_DS *)aRecv);
			LogAddC(2, "GDReqMuRummyInfoUpdate");
			break;
		case 7:
			GDReqMuRummyLogInsert((_tagPMSG_REQ_MURUMMY_LOG_INSERT_DS *)aRecv);
			LogAddC(2, "GDReqMuRummyLogInsert");
			break;
		case 0x20:
			GDReqBombHuntSelect((_tagPMSG_REQ_BOMB_HUNT_SELECT_DS *)aRecv, aIndex);
			LogAddC(2, "GDReqBombHuntSelect");
			break;
		case 0x21:
			GDReqBombHuntInsert((_tagPMSG_REQ_BOMB_HUNT_INSERT_DS *)aRecv);
			LogAddC(2, "GDReqBombHuntInsert");
			break;
		case 0x22:
			GDReqBombHuntDelete((_tagPMSG_REQ_BOMB_HUNT_DELETE_DS *)aRecv);
			LogAddC(2, "GDReqBombHuntDelete");
			break;
		case 0x23:
			GDReqBombLogInsert((_tagPMSG_REQ_BOMB_HUNT_LOG_INSERT_DS *)aRecv);
			LogAddC(2, "GDReqBombLogInsert");
			break;
		default:
			return;
		}
		break;
	}
	case 0xE9:
		GDRequestPShopItemValue((PMSG_REQ_PSHOPITEMVALUE_INFO *)aRecv, aIndex);
		break;
	case 0xEA:
		//GDUpdatePShopItemValue((PMSG_PSHOPITEMVALUE_INFO *)aRecv);
		break;
	case 0xEB:
		GDAllSavePShopItemValue((PMSG_UPDATE_PSHOPITEMVALUE_INFO *)aRecv);
		break;
	case 0xEC:
		GDDelPShopItemValue((PMSG_DEL_PSHOPITEM *)aRecv);
		break;
	case 0xED:
		GDMovePShopItem((PMSG_MOVE_PSHOPITEM *)aRecv);
		break;
	case 0xEE:
	{
		PMSG_DEFAULT * lpDef = (PMSG_DEFAULT*)aRecv;
		switch (lpDef->subcode)
		{
		case 0:
			GD_ChaosCastleNotice((_tagCHAOS_CASTLE_NOTICE *)aRecv);
			break;
		case 1:
			GD_ReqChaosCastleUserCount((_tagREQCHAOS_CASTLE_USER_GS *)aRecv, aIndex);
			break;
		case 2:
			GD_AnsChaosCastleUserCount((_tagANSCHAOS_CASTLE_USER_GS *)aRecv);
			break;
		case 3:
			GD_ReqGetSpecializedServerInfo((_tagREQGETSPECIALIZEDSERVERINFO *)aRecv, aIndex);
			break;
		case 4:
			GD_ReqSetSpecializedServerInfo((_tagREQSETSPECIALIZEDSERVERINFO *)aRecv);
			break;
		case 5:
			GD_ReqSetRuudTokenLog((_tagREQSETRUUDTOKENLOG *)aRecv);
			break;
		default:
			return;
		}
		break;
	}
	case 0xEF:
		GDReqInsertJewelUpgradeInfo((_tagPMSG_REQ_JEWEL_UPGRADE_INFO_INSERT_DS *)aRecv);
		break;
	case 0xF0:
	{
		PMSG_DEFAULT * lpDef = (PMSG_DEFAULT*)aRecv;
		switch (lpDef->subcode)
		{
		case 0xA1:
			GD_ITL_SaveGuildPoint((SDHP_REQ_SAVE_ITL_GUILDPOINT *)aRecv);
			break;
		case 0xA2:
			GD_ITL_SaveUserPoint((SDHP_REQ_SAVE_ITL_USERPOINT *)aRecv);
			break;
		case 0xA4:
			GD_ITL_SaveGuildCount((SDHP_REQ_SAVE_ITL_GUILDCOUNT *)aRecv);
			break;
		case 0xA5:
			GD_ITL_LeagueRankRenew((_tagPMSG_REQ_LEAGUERANK_RENEW *)aRecv);
			break;
		case 0xA6:
			GD_ITL_GuildRankGet((_tagPMSG_REQ_GUILDRANK_GET *)aRecv, aIndex);
			break;
		case 0xA7:
			GD_ITL_GuildTournamentGet((PMSG_REQ_ITL_TOURNAMENT *)aRecv, aIndex);
			break;
		case 0xA8:
			GD_ITL_RewardRenew((PMSG_REQ_ITL_RENEW_REWARD *)aRecv);
			break;
		case 0xA9:
			GD_ITL_GetRewardList((PMSG_REQ_ITL_GET_REWARDLIST *)aRecv, aIndex);
			break;
		case 0xAA:
			GD_ITL_UpdaterewardReceived((PMSG_REQ_ITL_REWARDRECEIVED *)aRecv);
			break;
		case 0xAB:
			GD_ITL_LoadGuildEnterCount((_tagPMSG_REQ_ITL_GUILDCOUNTREQ *)aRecv, aIndex);
			break;
		case 0xAC:
			GD_ITL_LoadUserEnterCount((_tagPMSG_REQ_ITL_USERCOUNTREQ *)aRecv, aIndex);
			break;
		default:
			return;
		}
		break;
	}
	case 0xF1:
		GDReqMuunInvenItemLoad((SDHP_REQ_DBMUUN_INVEN_LOAD *)aRecv, aIndex);
		break;
	case 0xF2:
		GDReqMuunInvenItemSave((_tagSDHP_REQ_DBMUUN_INVEN_SAVE *)aRecv);
		break;
	case 0xF3:
	{
		PMSG_DEFAULT * lpDef = (PMSG_DEFAULT*)aRecv;
		switch (lpDef->subcode)
		{
		case 0:
			GDReqGremoryCaseItemInsert((_tagSDHP_REQ_GREMORY_CASE_INSERT *)aRecv, aIndex);
			break;
		case 1:
			GDReqGremoryCaseItemExpire((_tagSDHP_REQ_GC_UPDATE *)aRecv, aIndex);
			break;
		case 2:
			GDReqGremoryCaseItemRecv((_tagSDHP_REQ_GC_UPDATE *)aRecv, aIndex);
			break;
		case 3:
			GDReqGremoryCaseItemUpdateAndInsert((_tagSDHP_REQ_GC_UPDATE_INSERT *)aRecv, aIndex);
			break;
		case 4:
			GDReqGremoryCaseItemDelete((_tagSDHP_REQ_GC_UPDATE *)aRecv, aIndex);
			break;
		case 0x10:
			GDReqGremoryCaseItemSelect((_tagSDHP_REQ_GREMORY_CASE_SELECT *)aRecv, aIndex);
			break;
		default:
			return;
		}
		break;
	}
	case 0xF6:
		GDReqQuestExpInfoSave((_PMSG_QUESTEXP_INFO *)aRecv);
		break;
	case 0xF7:
		GDReqQuestExpInfoLoad((PMSG_REQ_QUESTEXP_INFO *)aRecv, aIndex);
		break;
	case 0xF8:
	{
		PMSG_DEFAULT * lpDef = (PMSG_DEFAULT*)aRecv;
		switch (lpDef->subcode)
		{
		case 0x2A:
			GDReqArcaBattleGuildJoinSelect((_tagPMSG_REQ_AB_GUILD_JOIN_SELECT_DS *)aRecv, aIndex);
			break;
		case 0x30:
			GDReqArcaBattleGuildJoin((_tagPMSG_REQ_ARCA_BATTLE_GUILD_JOIN_DS *)aRecv, aIndex);
			break;
		case 0x32:
			GDReqArcaBattleGuildMemberJoin((_tagPMSG_REQ_ARCA_BATTLE_GUILD_MEMBER_JOIN_DS *)aRecv, aIndex);
			break;
		case 0x34:
			GDReqArcaBattleEnter((_tagPMSG_REQ_ARCA_BATTLE_ENTER_DS *)aRecv, aIndex);
			break;
		case 0x38:
			GDReqInsertArcaBattleWinGuild((_tagPMSG_REQ_AB_WIN_GUILD_INFO_INSERT_DS *)aRecv);
			break;
		case 0x39:
			GDReqSelectArcaBattleWinGuildInfo((_tagPMSG_REQ_AB_WIN_GUILD_INFO_DS *)aRecv, aIndex);
			break;
		case 0x3B:
			GDReqArcaBattleGuildGroupNum((_tagPMSG_REQ_ARCA_BATTLE_GROUP_NUM_DS *)aRecv, aIndex);
			break;
		case 0x3D:
			GDReqArcaBattleInfoDelete();
			break;
		case 0x3E:
			GDReqInsertArcaBattleProc(aRecv);
			break;
		case 0x3F:
			GDReqSelectArcaBattleProc((_tagPMSG_REQ_ARCA_BATTLE_PROC_STATE_DS *)aRecv, aIndex);
			break;
		case 0x41:
			GDReqArcaBattleJoinMemberUnder((_tagPMSG_REQ_AB_JOIN_MEMBER_UNDER_DS *)aRecv);
			break;
		case 0x43:
			GDReqABLessGuildMemberCancel((_tagPMSG_REQ_AB_JOIN_CANCEL_DS *)aRecv);
			break;
		case 0x45:
			GDReqRegisteredMemberCnt((_tagPMSG_REQ_AB_REG_MEMBER_CNT_DS *)aRecv, aIndex);
			break;
		case 0x47:
			GDReqRemoveAllGuildBuffMultiCast((_tagPMSG_REQ_REMOVE_ALL_GUILD_BUFF_DS *)aRecv);
			break;
		case 0x4B:
			GDReqRemoveGuildBuffMultiCast((_tagPMSG_REQ_REMOVE_GUILD_BUFF_DS *)aRecv);
			break;
		case 0x4D:
			GDReqArcaBattleMarkCnt(aRecv, aIndex);
			break;
		case 0x4F:
			GDReqArcaBattleMarkReg(aRecv, aIndex);
			break;
		case 0x51:
			GDReqArcaBattleRank(aRecv, aIndex);
			break;
		case 0x53:
			GDReqArcaBattleMarkRegDel(aRecv);
			break;
		case 0x54:
			GDReqArcaBattleIsTopRank(aRecv, aIndex);
			break;
		case 0x57:
			gCArcaBattleDBSet.DBDeleteAllArcaBattleGuildReg();
			break;
		case 0xF0:
			GDReqAcheronPlayProc(aRecv);
			break;
		case 0xFB:
			GDReqArcaBattleAllGuildMarkCnt(aIndex);
			break;
		case 0xFD:
			gCArcaBattleDBSet.DBUpdateArcaBattleGuildReg(aRecv, aIndex);
			break;
		case 0xFE:
			gCArcaBattleDBSet.DBDeleteArcaBattleGuildReg();
			break;
		default:
			return;
		}
		break;
	}
	case 0xF9:
	{
		PMSG_DEFAULT * lpDef = (PMSG_DEFAULT*)aRecv;
		switch (lpDef->subcode)
		{
		case 1:
			GD_Save_ChaosCastle_KillPoint((_tagPMSG_REQ_SAVE_CHAOSCASTLE_KILLPOINT *)aRecv, aIndex);
			break;
		case 0xA1:
			GD_CCF_Point_Save((SDHP_REQ_CCF_RESULT *)aRecv);
			break;
		case 0xA2:
			GD_CCF_GetPermission((SDHP_REQ_CCF_GETPERMISSION *)aRecv, aIndex);
			break;
		case 0xA3:
			GD_CCF_RankigReq((SDHP_REQ_CCF_RANKING_REQ *)aRecv, aIndex);
			break;
		case 0xA4:
			GD_CCFRankRenew((SDHP_RENEW_RANKING *)aRecv);
			break;
		case 0xA5:
			GD_CCF_Info_AllSend((SDHP_SEND_CCF_INFO *)aRecv);
			break;
		default:
			return;
		}
		break;
	}
	case 0xFA:
	{
		PMSG_DEFAULT * lpDef = (PMSG_DEFAULT*)aRecv;
		switch (lpDef->subcode)
		{
		case 1:
			GDReqUBFAccountUserInfo((PMSG_REQ_UBF_ACCOUNT_USERINFO *)aRecv, aIndex);
			break;
		case 2:
			GDReqUBFAccountUserRegister((PMSG_UBF_REGISTER_ACCOUNT_USER *)aRecv, aIndex);
			break;
		case 3:
			GDReqUBFAccountUserCopy((PMSG_UBF_ACCOUNT_USER_COPY *)aRecv, aIndex);
			break;
		case 5:
			GDReqSetReceivedWinnerItem((PMSG_REQ_UBF_SET_RECEIVED_REWARD *)aRecv, aIndex);
			break;
		case 6:
			GDReqUBFWinInfo((PMSG_REQ_UBF_GET_REWARD *)aRecv, aIndex);
			break;
		case 7:
			GDReqUBFCancel((PMSG_UBF_REQ_CANCEL_REGISTER_USER *)aRecv, aIndex);
			break;
		case 8:
			GDReqGetRealNameAndServerCode((PMSG_REQ_GET_UBF_REAL_NAME *)aRecv, aIndex);
			break;
		case 9:
			GDReqSaveRewardInfoOfUnityBattleField((PMSG_REQ_UBF_SET_REWARD_INFORMATION *)aRecv, aIndex);
			break;
		default:
			return;
		}
		break;
	}
	case 0xFB:
		GDReqUBFCopyPetItemInfo(aRecv);
		break;
	case 0xFC:
	{
		PMSG_DEFAULT * lpDef = (PMSG_DEFAULT*)aRecv;
		switch (lpDef->subcode)
		{
		case 0:
			GD_DSF_CanPartyEnter((PMSG_REQ_DSF_CAN_PARTY_ENTER *)aRecv, aIndex);
			break;
		case 1:
			GD_DSF_SaveUserPoint((PMSG_REQ_SAVE_DSF_USERPOINT *)aRecv);
			break;
		case 2:
			GD_DSF_SavePartyPoint((PMSG_REQ_SAVE_DSF_PARTYPOINT *)aRecv);
			break;
		case 3:
			GD_DSF_PartyRankRenew((PMSG_REQ_DSF_PARTYRANKRENEW *)aRecv, aIndex);
			break;
		case 4:
			GD_DSF_TodayPartyRank((PMSG_REQ_DSF_TODAY_PARTYRANK *)aRecv, aIndex);
			break;
		case 5:
			GD_DSF_GoFinalParty((PMSG_REQ_DSF_GO_FINAL_PARTY *)aRecv, aIndex);
			break;
		case 6:
			GD_DSF_InsertRewardUser((PMSG_REQ_SAVE_DSF_REWARD_USER *)aRecv);
			break;
		case 7:
			GD_DSF_ReqGetReward((PMSG_REQ_GET_DSF_REWARD *)aRecv, aIndex);
			break;
		default:
			return;
		}
		break;
	}
	case 0xFD:
	{
		PMSG_DEFAULT * lpDef = (PMSG_DEFAULT*)aRecv;
		switch (lpDef->subcode)
		{
		case (char)0xFB:
			GD_Req_Get_EventMapEnterCount((SDHP_GET_EVENTMAPENTERCOUNT *)aRecv, aIndex);
			break;
		case (char)0xFC:
			GD_Req_Set_EventMapEnterCount((SDHP_SET_EVENTMAPENTERCOUNT *)aRecv);
			break;
		case (char)0xFE:
			GD_ReqEventMapIntegration_AllNotify((SDHP_SEND_EVENTMAP_INFO_ALL_SVR *)aRecv);
			break;
		}
		break;
	}
	default:
		return;
	}
}

void GetJoinInfo(LPSDHP_SERVERINFO lpMsg, short aIndex)
{
	SDHP_RESULT pResult;

	pResult.h.c = PMHC_BYTE;
	pResult.h.headcode = 0;
	pResult.h.size = sizeof(SDHP_RESULT);
	pResult.Result = 1;
	pResult.ItemCount = gItemCount;

	if (gSObjSetInfo(aIndex, lpMsg->Port, lpMsg->Type, lpMsg->ServerName, lpMsg->ServerCode, lpMsg->btGameServerType) == FALSE)
	{
		pResult.Result = 0;
		LogAdd("Client Join Fail %s %d", __FILE__, __LINE__);
	}

	wsjServer.DataSend(aIndex, (char*)&pResult, pResult.h.size);
}
char GameID = '\0';

#define EX700CHS
#ifdef EX700CHS
//ex700chs
void GJPCharacterListRequestCS(SDHP_GETCHARLIST *lpCLMsg, int aIndex)
{
	BYTE Inventory[MAX_DBINVENTORY-1];

	AccountCharacterInfo ACInfo;
	CString strCharId[5];
	BYTE SendBuf[512];
	SDHP_CHARLIST pCharList;
	SDHP_CHARLISTCOUNT pCount;
	char szId[11];
	char characterName[11];
	SDHP_ANS_ACCOUNTINFO Result;
	CharacterInfo_Struct tCharInfo;
	MLP_ANS_MASTERLEVEL_INFO ReqInfo;

	memset(Result.AccountId, 0, 0xBu);
	memcpy(Result.AccountId, lpCLMsg->Id, 0xAu);
	Result.h.set((LPBYTE)&Result.h.c, 0xA1, 18);
	Result.Number = lpCLMsg->Number;
	Result.bSummoner = gACDbSet.GetSummonerCardInfo(Result.AccountId);
	Result.Result = 0;
	wsjServer.DataSend(aIndex, (char*)&Result.h.c, 18);

	int IsUBFServer = lpCLMsg->IsUnityBattleFiledServer;//s12

	BYTE result = 1;
	int listcount = 0;
	int lOfs = 0;
	int Count = 0;

	memset(&pCharList, 0, sizeof(SDHP_CHARLIST));
	memset(pCount.AccountId, 0, sizeof(pCount.AccountId));
	memset(szId, 0, MAX_IDSTRING + 1);
	memcpy(szId, lpCLMsg->Id, MAX_IDSTRING);
	memcpy(pCount.AccountId, lpCLMsg->Id, MAX_IDSTRING);
	memset(SendBuf, 0, 512);
	pCount.GenerableClass = 0;
	lOfs += sizeof(SDHP_CHARLISTCOUNT);
	if (result == 1)
	{
		if (gACDbSet.GetAccountId(szId) == 1)
		{
			result = 1;
		}
		else
		{
			result = 0;
			if (gACDbSet.CreateAccountCharacter(szId) == 1)
				result = 1;
		}
	}
	if (result == 1)
	{
		BYTE  btSlotCount = 0;
		if (gACDbSet.GetCharacterSlotCount(szId, &btSlotCount) == TRUE)
			pCount.CharacterSlotCount = btSlotCount;

		BYTE btExtendedWarehouseCount = 0;
		if (gACDbSet.GetCharacterExtendedWarehouseCount(szId, &btExtendedWarehouseCount) == 1)
			pCount.ExtendedWarehouseCount = btExtendedWarehouseCount;

		memset(&ACInfo, 0, sizeof(AccountCharacterInfo));
		if (gACDbSet.GetAccountInfo(szId, &ACInfo))
		{
			result = 1;
			strCharId[0] = ACInfo.GameID1;
			strCharId[1] = ACInfo.GameID2;
			strCharId[2] = ACInfo.GameID3;
			strCharId[3] = ACInfo.GameID4;
			strCharId[4] = ACInfo.GameID5;
			pCount.MoveCnt = ACInfo.MoveCnt;
			listcount = 0;
			for (int n = 0; n < 5; ++n)
			{
				//if (strCharId[n].GetLength() > 0 && strCharId[n].GetLength() <= MAX_IDSTRING)
				if (strCharId[n].GetLength() > 0)
				{
					if (strCharId[n].GetLength() <= MAX_IDSTRING)
					{
						memset(characterName, 0, MAX_IDSTRING + 1);
						strcpy(characterName, strCharId[n].GetBuffer(MAX_IDSTRING));
						
						int _level;
						int _class;

						BOOL bGetPrevChar = FALSE;
						BYTE _ctlcode = 0;
						BYTE _dbverstion = 0;
						char _pkLevel = 0;
						BYTE _btGuildStatus = 0xFF;
						bGetPrevChar = gCharPreDBSet.GetChar(
							characterName,
							szId,
							_level,
							_class,
							Inventory,
							_ctlcode,
							_dbverstion,
							_pkLevel,
							_btGuildStatus);
						if (bGetPrevChar == 1)
						{
							pCharList.Index = n;
							pCharList.Level = _level;
							pCharList.Class = _class;
							pCharList.CtlCode = _ctlcode;
							pCharList.DbVersion = _dbverstion;
							
							if (_pkLevel & 0x80)
							{
								_pkLevel &= 0x7Fu;
								int v17 = 0;
								int v16 = 0xFF;
								if (_level >= 400
									&& !MasterLevelSystemDBSet.DSDB_QueryMasterLevelSystemLoad(characterName, &ReqInfo))
								{
									v17 = ReqInfo.nMLevel;
								}
								//classdef pClassDef;
								v16 = DCInfo.GetCharacterClassByDBClass(_class);
								if (v16 != 255)
								{
									BYTE buf[3784];
									for (int j = 0; j < 236; ++j)
										memset(&buf[16 * j], 255, 0x10u);
									if (v17 + _level < 600)
									{
										if (v17 + _level < 500)
										{
											if (_level < 400)
											{
												if (_level < 380)
												{
													/*	`vector constructor iterator'(__t, 0xA8u, 13, CItem::CItem);
													for (k = 0; k < 13; ++k)
													CItem::Clear(&__t[168 * k]);
													type = ItemGetNumberMake(14, 286);
													CItem::Convert(&v12, type, 0, 0, 0, 0, 0, 3);
													ItemByteConvert16(buf, __t, 13);*/
												}
												else
												{
													ItemByteConvert16(buf, DCInfo.JumpingEquipment[v16 + 2], 204);
													//ItemByteConvert16(buf, DCInfo.DefClass[defclass].Equipment, 12);
												}
											}
											else
											{
												ItemByteConvert16(buf, DCInfo.JumpingEquipment[v16], 204);
											}
										}
										else
										{
											ItemByteConvert16(buf, DCInfo.JumpingEquipment[v16 + 1], 204);
										}
									}
									else
									{
										ItemByteConvert16(buf, DCInfo.JumpingEquipment[v16 + 3], 204);
									}
									gCharDbSet.RewardJumpingItem(characterName, buf);
								}
							}
							pCharList.PK_Level = _pkLevel;
							pCharList.btGuildStatus = _btGuildStatus;
							int v7 = 0;
							/*ServerCode = 0;
							if (IsUBFServer == 1)
							v7 = gCharPreDBSet.GetRealNameAndServerCode(characterName, &szRealName, &ServerCode, 1);
							if (IsUBFServer != 1 || v7 != 1)
							{
							memcpy(&v41, &GameID, 0xAu);*/
							pCharList.ServerCodeOfHomeWorld = 0;
							/*}
							else
							{
							memcpy(&v41, &szRealName, 0xAu);
							pCharList.ServerCodeOfHomeWorld = ServerCode;
							}
							memcpy(pCharList.Name, characterName, 0xAu);*/
							memcpy(pCharList.Name, characterName, MAX_IDSTRING);
							if (!(_ctlcode & 0x80) && _level >= 150)
							{
								if (_level < 400)
								{
									if (_level < 250)
									{
										if (_level < 220)
										{
											if (_level < 200)
											{
												if (pCount.GenerableClass < 2)
													pCount.GenerableClass = 1;
											}
											else if (pCount.GenerableClass < 3)
											{
												pCount.GenerableClass = 2;
											}
										}
										else if (pCount.GenerableClass < 4)
										{
											pCount.GenerableClass = 3;
										}
									}
									else if (pCount.GenerableClass < 5)
									{
										pCount.GenerableClass = 4;
									}
								}
								else
								{
									pCount.GenerableClass = 5;
								}
							}
							if (_dbverstion)
							{
								if (_dbverstion != 1 && _dbverstion != 2)
								{
									for (int j = 0; j < MAX_EQUIPMENT; ++j)
									{
										memcpy(&pCharList.dbInventory[4 * j], &Inventory[16 * j], 2u);
										pCharList.dbInventory[4 * j + 2] = Inventory[16 * j + 7];
										pCharList.dbInventory[4 * j + 3] = Inventory[16 * j + 9];
									}
								}
								else
								{
									for (int k = 0; k < MAX_EQUIPMENT; ++k)
									{
										memcpy(&pCharList.dbInventory[3 * k], &Inventory[10 * k], 2u);
										pCharList.dbInventory[3 * k + 2] = Inventory[10 * k + 7];
									}
								}
							}
							else
							{
								for (int i = 0; i < MAX_EQUIPMENT; ++i)
									memcpy(&pCharList.dbInventory[2 * i], &Inventory[7 * i], 2u);
							}
							memcpy(&SendBuf[lOfs], &pCharList, sizeof(SDHP_CHARLIST));
							lOfs += sizeof(SDHP_CHARLIST);
							++Count;
						}
					}
				}
			}
		}
		else
		{
			result = 0;
		}
	}
	pCount.h.c = PMHC_WORD;
	pCount.h.headcode = 1;
	pCount.Number = lpCLMsg->Number;
	pCount.Count = Count;
	pCount.h.sizeH = SET_NUMBERH(lOfs);
	pCount.h.sizeL = SET_NUMBERL(lOfs);
	memcpy(SendBuf, &pCount, sizeof(SDHP_CHARLISTCOUNT));
	wsjServer.DataSend(aIndex, (char*)SendBuf, lOfs);
}
#endif
#ifdef DEV

void GJPCharacterListRequestCS(SDHP_GETCHARLIST *lpCLMsg, int aIndex)
{
	SDHP_ANS_ACCOUNTINFO Result;

	char Name[MAX_IDSTRING + 1];
	char szRealName[MAX_IDSTRING + 1];
	char szId[MAX_IDSTRING + 1];

	MLP_ANS_MASTERLEVEL_INFO ReqInfo;
	AccountCharacterInfo ACInfo;

	int l;
	int m;
	int ServerCode;
	char v7;

	int type;
	int k;
	char __t[2016];
	CItem v12;
	int j;
	BYTE buf[3784];

	unsigned __int8 v16;
	int v17;
	BYTE Inventory[7];
	char v24[2];
	char v25[3791];
	int _class;
	int _level;

	char v40;
	char v41;
	char v46[2];
	char v47;
	char v48[45];

	int IsUBFServer;
	char v53;

	int i;

	int v74;

	memset(Result.AccountId, 0, MAX_IDSTRING + 1);
	memcpy(Result.AccountId, lpCLMsg->Id, MAX_IDSTRING);

	Result.h.set((LPBYTE)&Result, 0xA1, sizeof(SDHP_ANS_ACCOUNTINFO));

	Result.Number = lpCLMsg->Number;

	Result.bSummoner = gACDbSet.GetSummonerCardInfo(Result.AccountId);

	Result.Result = 0;

	wsjServer.DataSend(aIndex, (char*)&Result, sizeof(SDHP_ANS_ACCOUNTINFO));

	BYTE result = 1;
	int listcount = 0;

	int n;
	SDHP_CHARLISTCOUNT pCount;
	SDHP_CHARLIST pCharList;
	char SendBuf[512];

	IsUBFServer = lpCLMsg->IsUnityBattleFiledServer;
	int len = 0;
	int Count = 0;
	v74 = 0;

	CString strCharId[5];

	memset(&pCharList, 0, sizeof(SDHP_CHARLIST));
	memset(pCount.AccountId, 0, sizeof(pCount.AccountId));
	memset(szId, 0, MAX_IDSTRING + 1);

	memcpy(szId, lpCLMsg->Id, MAX_IDSTRING);
	memcpy(pCount.AccountId, lpCLMsg->Id, MAX_IDSTRING);

	memset(SendBuf, 0, 512);
	pCount.GenerableClass = 0;

	len += 28;

	if (result == 1)
	{
		if (gACDbSet.GetAccountId(szId) == 1)
		{
			result = 1;
		}
		else
		{
			result = 0;
			if (gACDbSet.CreateAccountCharacter(szId) == 1)
				result = 1;
		}
	}


	if (result == 1)
	{
		BYTE btSlotCount = 0;
		if (gACDbSet.GetCharacterSlotCount(szId, &btSlotCount) == 1)
			pCount.CharacterSlotCount = btSlotCount;
		BYTE btAddExtendedWarehouseCount = 0;
		if (gACDbSet.GetCharacterExtendedWarehouseCount(szId, &btAddExtendedWarehouseCount) == 1)
			pCount.ExtendedWarehouseCount = btAddExtendedWarehouseCount;
		memset((char *)&ACInfo, 0, sizeof(AccountCharacterInfo));
		if (gACDbSet.GetAccountInfo(szId, &ACInfo))
		{
			result = 1;

			strCharId[0] = ACInfo.GameID1;
			strCharId[1] = ACInfo.GameID2;
			strCharId[2] = ACInfo.GameID3;
			strCharId[3] = ACInfo.GameID4;
			strCharId[4] = ACInfo.GameID5;

			pCount.MoveCnt = ACInfo.MoveCnt;
			listcount = 0;

			for (i = 0; i < 5; ++i)
			{
				if (strCharId[i].GetLength() > 0
					&& strCharId[i].GetLength() <= MAX_IDSTRING
					//strCharId[n].GetLength() > 0 && strCharId[n].GetLength() <= MAX_IDSTRING
					)
				{
					memset(Name, 0, 0xBu);
					strcpy(Name, strCharId[i].GetBuffer(MAX_IDSTRING));
					BOOL bGetPrevChar = FALSE;
					BYTE _ctlcode = 0;
					BYTE _dbverstion = 0;
					char _pkLevel = 0;
					BYTE _btGuildStatus = 0xFF;

					bGetPrevChar = gCharPreDBSet.GetChar(
						Name,
						szId,
						_level,
						_class,
						Inventory,
						_ctlcode,
						_dbverstion,
						_pkLevel,
						_btGuildStatus);
					if (bGetPrevChar == 1)
					{
						pCharList.Index = i;
						pCharList.Level = _level;
						pCharList.Class = _class;
						pCharList.CtlCode = _ctlcode;
						pCharList.DbVersion = _dbverstion;
						//if (_pkLevel & 0x80)
						//{
						//	//LogAddTD(&byte_591B4C, &Id, &Name, _level);
						//	_pkLevel &= 0x7Fu;
						//	v17 = 0;
						//	v16 = -1;
						//	if (_level >= 400
						//		&& !MasterLevelSystemDBSet.DSDB_QueryMasterLevelSystemLoad(Name, &ReqInfo))
						//	{
						//		v17 = ReqInfo.nMLevel;
						//	}
						//	//v16 = 4 * classdef::GetCharacterClassByDBClass(&DCInfo, _class);
						//	v16 = DCInfo.GetCharacterClassByDBClass(_class);
						//	if (v16 != 255)
						//	{
						//		for (j = 0; j < 236; ++j)
						//			memset(&buf[16 * j], 255, 0x10u);
						//		if (v17 + _level < 600)
						//		{
						//			if (v17 + _level < 500)
						//			{
						//				if (_level < 400)
						//				{
						//					if (_level < 380)
						//					{
						//						/*`vector constructor iterator'(__t, 0xA8u, 13, (void *(__thiscall *)(void *))CItem::CItem);
						//							for (k = 0; k < 13; ++k)
						//								CItem::Clear((CItem *)&__t[168 * k]);
						//						type = ItemGetNumberMake(14, 286);
						//						CItem::Convert(&v12, type, 0, 0, 0, 0, 0, 3);
						//						ItemByteConvert16(buf, (CItem *)__t, 13);*/
						//					}
						//					else
						//					{
						//						ItemByteConvert16(buf, DCInfo.JumpingEquipment[v16 + 2], 204);
						//					}
						//				}
						//				else
						//				{
						//					ItemByteConvert16(buf, DCInfo.JumpingEquipment[v16], 204);
						//				}
						//			}
						//			else
						//			{
						//				ItemByteConvert16(buf, DCInfo.JumpingEquipment[v16 + 1], 204);
						//			}
						//		}
						//		else
						//		{
						//			ItemByteConvert16(buf, DCInfo.JumpingEquipment[v16 + 3], 204);
						//		}
						//		gCharDbSet.RewardJumpingItem(Name, buf);
						//	}
						//}
						pCharList.PK_Level = _pkLevel;
						pCharList.btGuildStatus = _btGuildStatus;
						v7 = 0;
						ServerCode = 0;
						if (IsUBFServer == 1)
							v7 = gCharPreDBSet.GetRealNameAndServerCode(Name, szRealName, &ServerCode, 1);
						if (IsUBFServer != 1 || v7 != 1)
						{
							memcpy(&v41, &GameID, 0xAu);
							pCharList.ServerCodeOfHomeWorld = 0;
						}
						else
						{
							memcpy(&v41, szRealName, 0xAu);
							pCharList.ServerCodeOfHomeWorld = ServerCode;
						}
						memcpy(&v40, Name, 0xAu);
						if (!(_ctlcode & 0x80) && _level >= 150)
						{
							if (_level < 400)
							{
								if (_level < 250)
								{
									if (_level < 220)
									{
										if (_level < 200)
										{
											if (pCount.GenerableClass < 2)
												pCount.GenerableClass = 1;
										}
										else if (pCount.GenerableClass < 3)
										{
											pCount.GenerableClass = 2;
										}
									}
									else if (pCount.GenerableClass < 4)
									{
										pCount.GenerableClass = 3;
									}
								}
								else if (pCount.GenerableClass < 5)
								{
									pCount.GenerableClass = 4;
								}
							}
							else
							{
								pCount.GenerableClass = 5;
							}
						}
						if (_dbverstion)
						{
							if (_dbverstion != 1 && _dbverstion != 2)
							{
								for (l = 0; l < 12; ++l)
								{
									memcpy(&v46[4 * l], &Inventory[16 * l], 2u);
									*(&v47 + 4 * l) = v24[16 * l];
									v48[4 * l] = v25[16 * l];
								}
							}
							else
							{
								for (m = 0; m < 12; ++m)
								{
									memcpy(&v46[3 * m], &Inventory[10 * m], 2u);
									*(&v47 + 3 * m) = v24[10 * m];
								}
							}
						}
						else
						{
							for (n = 0; n < 12; ++n)
								memcpy(&v46[2 * n], &Inventory[7 * n], 2u);
						}
						memcpy(&SendBuf[len], &pCharList, sizeof(SDHP_CHARLIST));
						len += sizeof(SDHP_CHARLIST);
						++Count;
					}
				}
			}
		}
		else
		{
			result = 0;
		}
	}
	pCount.h.c = PMHC_WORD;
	pCount.h.headcode = 0x01;
	pCount.Number = lpCLMsg->Number;
	pCount.Count = Count;
	pCount.h.sizeH = SET_NUMBERH(len);
	pCount.h.sizeL = SET_NUMBERL(len);
	memcpy(SendBuf, &pCount, sizeof(SDHP_CHARLISTCOUNT));

	wsjServer.DataSend(aIndex, (char*)SendBuf, len);
	//pCount.h.c = PMHC_WORD;
	//pCount.h.headcode = 1;
	//pCount.Number = lpCLMsg->Number;
	//pCount.Count = Count;
	//pCount.h.sizeH = SET_NUMBERH(len);
	//pCount.h.sizeL = SET_NUMBERL(len);
	//memcpy(SendBuf, &pCount, sizeof(SDHP_CHARLISTCOUNT));
	//wsjServer.DataSend(aIndex, SendBuf, len);
}
#endif

//void GJPCharacterListRequestCS(SDHP_GETCHARLIST *lpCLMsg, int aIndex)
//{
//	CharacterInfo_Struct tCharInfo;
//	MLP_ANS_MASTERLEVEL_INFO ReqInfo;
//	AccountCharacterInfo ACInfo;
//	CString strCharId[5];
//	char SendBuf[520];
//	SDHP_CHARLIST pCharList;
//
//	int IsUBFServer;
//	SDHP_CHARLISTCOUNT pCount;
//
//	SDHP_ANS_ACCOUNTINFO Result;
//
//	memset(Result.AccountId, 0, MAX_IDSTRING + 1);
//	memcpy(Result.AccountId, lpCLMsg->Id, MAX_IDSTRING);
//	Result.h.set((LPBYTE)&Result, 0xA1, sizeof(SDHP_ANS_ACCOUNTINFO));
//	Result.Number = lpCLMsg->Number;
//	Result.bSummoner = gACDbSet.GetSummonerCardInfo(Result.AccountId);
//	Result.Result = 0;
//	wsjServer.DataSend(aIndex, (char*)&Result, sizeof(SDHP_ANS_ACCOUNTINFO));
//
//	BYTE result = 1;
//	int listcount = 0;
//	IsUBFServer = lpCLMsg->IsUnityBattleFiledServer;
//	int lOfs = 0;
//	int Count = 0;
//	int v74 = 0;
//
//	char szId[MAX_IDSTRING + 1];
//	char characterName[MAX_IDSTRING + 1];
//
//	memset(&pCharList, 0, sizeof(SDHP_CHARLIST));
//	memset(pCount.AccountId, 0, MAX_IDSTRING + 1);
//	memset(szId, 0, MAX_IDSTRING + 1);
//
//	memcpy(szId, lpCLMsg->Id, MAX_IDSTRING);
//	memcpy(pCount.AccountId, lpCLMsg->Id, MAX_IDSTRING);
//
//	memset(SendBuf, 0, 512);
//	pCount.GenerableClass = 0;
//
//	lOfs += sizeof(SDHP_CHARLISTCOUNT);
//
//	if (result == 1)
//	{
//		if (gACDbSet.GetAccountId(szId) == 1)
//		{
//			result = 1;
//		}
//		else
//		{
//			result = 0;
//			if (gACDbSet.CreateAccountCharacter(szId) == 1)
//				result = 1;
//		}
//	}
//	if (result == 1)
//	{
//		BYTE btSlotCount = 0;
//		if (gACDbSet.GetCharacterSlotCount(szId, &btSlotCount) == 1)
//		{
//			pCount.CharacterSlotCount = btSlotCount;
//		}
//		BYTE btAddExtendedWarehouseCount = 0;
//		if (gACDbSet.GetCharacterExtendedWarehouseCount(szId, &btAddExtendedWarehouseCount) == 1)
//		{
//			pCount.ExtendedWarehouseCount = btAddExtendedWarehouseCount;
//		}
//		memset(&ACInfo, 0, sizeof(AccountCharacterInfo));
//
//		if (gACDbSet.GetAccountInfo(szId, &ACInfo))
//		{
//			result = 1;
//
//			strCharId[0] = ACInfo.GameID1;
//			strCharId[1] = ACInfo.GameID2;
//			strCharId[2] = ACInfo.GameID3;
//			strCharId[3] = ACInfo.GameID4;
//			strCharId[4] = ACInfo.GameID5;
//			pCount.MoveCnt = ACInfo.MoveCnt;
//
//			int listcount = 0;
//
//			for (int i = 0; i < 5; ++i)
//			{
//				int n;
//				if (strCharId[n].GetLength() > 0 && strCharId[n].GetLength() <= MAX_IDSTRING)
//				{
//					memset(characterName, 0, MAX_IDSTRING + 1);
//
//					strcpy(characterName, strCharId[n].GetBuffer(MAX_IDSTRING));
//
//					int _level;
//					int _class;
//
//					BYTE Inventory[MAX_DBINVENTORY];
//
//					BOOL bGetPrevChar = 0;
//					BYTE _ctlcode = 0;
//					BYTE _dbverstion = 0;
//					char _pkLevel = 0;
//					BYTE _btGuildStatus = 0xFF;
//					//(characterName, _level, _class, Inventory, _ctlcode, _dbverstion, _btGuildStatus);
//					bGetPrevChar = gCharPreDBSet.GetChar(characterName, szId, &_level, &_class, Inventory, _ctlcode, _dbverstion, &_pkLevel, _btGuildStatus);
//
//					if (bGetPrevChar == TRUE)
//					{
//						pCharList.Index = i;
//						pCharList.Level = _level;
//						pCharList.Class = _class;
//						pCharList.CtlCode = _ctlcode;
//						pCharList.DbVersion = _dbverstion;
//
//						if (_pkLevel & 0x80)
//						{
//							//LogAddTD(&byte_591B4C, szId, characterName, _level);
//							_pkLevel &= 0x7Fu;
//							int v17 = 0;
//							int v16 = 0xFF;
//							if (_level >= 400 && !MasterLevelSystemDBSet.DSDB_QueryMasterLevelSystemLoad(characterName, &ReqInfo))
//							{
//								v17 = ReqInfo.nMLevel;
//							}
//							classdef _classdef;
//							v16 = 4 * _classdef.GetCharacterClassByDBClass(_class);
//							if (v16 != 255)
//							{
//								for (int j = 0; j < 236; ++j)
//									memset(&tCharInfo.dbInventory[16 * j], 255, 0x10u);
//								if (v17 + _level < 600)
//								{
//									if (v17 + _level < 500)
//									{
//										if (_level < 400)
//										{
//											if (_level < 380)
//											{
//												//`vector constructor iterator'(__t, 0xA8u, 13, CItem::CItem);
//												/*	for (k = 0; k < 13; ++k)
//												Inventory.Clear([168 * k]);
//												type = ItemGetNumberMake(14, 286);
//												v12.Convert(type, 0, 0, 0, 0, 0, 3);
//												ItemByteConvert16(tCharInfo.dbInventory, Inventory, 13);*/
//											}
//											else
//											{
//												ItemByteConvert16(tCharInfo.dbInventory, DCInfo.JumpingEquipment[v16 + 2], 204);
//											}
//										}
//										else
//										{
//											ItemByteConvert16(tCharInfo.dbInventory, DCInfo.JumpingEquipment[v16], 204);
//										}
//									}
//									else
//									{
//										ItemByteConvert16(tCharInfo.dbInventory, DCInfo.JumpingEquipment[v16 + 1], 204);
//									}
//								}
//								else
//								{
//									//ItemByteConvert16(tCharInfo.dbInventory, DCInfo.DefClass[defclass].Equipment, MAX_EQUIPMENT + 2);
//									ItemByteConvert16(tCharInfo.dbInventory, DCInfo.JumpingEquipment[v16 + 3], 204);
//								}
//								gCharDbSet.RewardJumpingItem(characterName, tCharInfo.dbInventory);
//							}
//						}
//						pCharList.PK_Level = _pkLevel;
//						pCharList.btGuildStatus = _btGuildStatus;
//						int ServerCodeOfHomeWorld = 0;
//						int ServerCode = 0;
//						char szRealName;
//						if (IsUBFServer == 1)
//							
//							pCharList.ServerCodeOfHomeWorld = gCharPreDBSet.GetRealNameAndServerCode(characterName, &szRealName, &ServerCode, 1);
//						if (IsUBFServer != 1 || ServerCodeOfHomeWorld != 1)
//						{
//							//memcpy(&v41, &GameID, MAX_IDSTRING);
//							int ServerCodeOfHomeWorld = 0;
//						}
//						else
//						{
//							//memcpy(&v41, &szRealName, MAX_IDSTRING);
//							ServerCodeOfHomeWorld = ServerCode;
//						}
//						char v40;
//						memcpy(&v40, characterName, MAX_IDSTRING);
//						if (!(_ctlcode & 0x80) && _level >= 150)
//						{
//							if (_level < 400)
//							{
//								if (_level < 250)
//								{
//									if (_level < 220)
//									{
//										if (_level < 200)
//										{
//											if (pCount.GenerableClass < 2)
//												pCount.GenerableClass = 1;
//										}
//										else if (pCount.GenerableClass < 3)
//										{
//											pCount.GenerableClass = 2;
//										}
//									}
//									else if (pCount.GenerableClass < 4)
//									{
//										pCount.GenerableClass = 3;
//									}
//								}
//								else if (pCount.GenerableClass < 5)
//								{
//									pCount.GenerableClass = 4;
//								}
//							}
//							else
//							{
//								pCount.GenerableClass = 5;
//							}
//						}
//						if (_dbverstion)
//						{
//							if (_dbverstion != 1 && _dbverstion != 2)
//							{
//								for (int l = 0; l < MAX_EQUIPMENT; ++l)
//								{
//									memcpy(&pCharList.dbInventory[4 * l], &Inventory[16 * l], 2);
//									pCharList.dbInventory[4 * l + 2] = Inventory[16 * l + 7];
//									pCharList.dbInventory[4 * l + 3] = Inventory[16 * l + 9];
//								}
//							}
//							else
//							{
//								for (int k = 0; k < MAX_EQUIPMENT; ++k)
//								{
//									memcpy(&pCharList.dbInventory[3 * k], &Inventory[10 * k], 2);
//									pCharList.dbInventory[3 * k + 2] = Inventory[10 * k + 7];
//								}
//							}
//						}
//						else
//						{
//							for (int  n = 0; n < MAX_EQUIPMENT; ++n)
//								memcpy(&pCharList.dbInventory[2 * n], &Inventory[7 * n], 2);
//						}
//						memcpy(&SendBuf[lOfs], &pCharList, sizeof(SDHP_CHARLIST));
//						lOfs += sizeof(SDHP_CHARLIST);;
//						++Count;
//					}
//				}
//			}
//		}
//		else
//		{
//			result = 0;
//		}
//	}
//	pCount.h.c = PMHC_WORD;
//	pCount.h.headcode = 1;
//	pCount.Number = lpCLMsg->Number;
//	pCount.Count = Count;
//	pCount.h.sizeH = HIBYTE(lOfs);
//	pCount.h.sizeL = LOBYTE(lOfs);
//	memcpy(SendBuf, &pCount, sizeof(SDHP_CHARLISTCOUNT));
//	wsjServer.DataSend(aIndex, (char*)SendBuf, lOfs);
//}

#ifdef WORKIG_PREVIEW
void GJPCharacterListRequestCS(LPSDHP_GETCHARLIST lpCLMsg, int aIndex)
{
#ifdef ADD_CHARCARD_SUMMONER_20080313
	SDHP_ANS_ACCOUNTINFO Result;
#endif

	char characterName[MAX_IDSTRING + 1];
	char szId[MAX_IDSTRING + 1];

#ifdef ADD_CHARCARD_SUMMONER_20080313
	memset(Result.AccountId, 0, MAX_IDSTRING + 1);
	memcpy(Result.AccountId, lpCLMsg->Id, MAX_IDSTRING);

	Result.h.set((LPBYTE)&Result, 0xA1, sizeof(SDHP_ANS_ACCOUNTINFO));

	Result.Number = lpCLMsg->Number;

	Result.bSummoner = gACDbSet.GetSummonerCardInfo(Result.AccountId);

	Result.Result = 0;

	wsjServer.DataSend(aIndex, (char*)&Result, sizeof(SDHP_ANS_ACCOUNTINFO));
#endif

	int IsUBFServer = lpCLMsg->IsUnityBattleFiledServer;//s12
	BYTE result = 1;
	int listcount = 0;

	int n;
	SDHP_CHARLISTCOUNT pCount;
	SDHP_CHARLIST pCharList;
	char SendBuf[512];

	int lOfs = 0;
	int Count = 0;

	CString strCharId[5];

	memset(&pCharList, 0, sizeof(SDHP_CHARLIST));
	memset(pCount.AccountId, 0, sizeof(pCount.AccountId));
	memset(szId, 0, MAX_IDSTRING + 1);

	memcpy(szId, lpCLMsg->Id, MAX_IDSTRING);
	memcpy(pCount.AccountId, lpCLMsg->Id, MAX_IDSTRING);

	memset(SendBuf, 0, 512);
	pCount.GenerableClass = 0;

	lOfs += sizeof(SDHP_CHARLISTCOUNT);

	if (result == 1)
	{
		if (gACDbSet.GetAccountId(szId) == 1)
		{
			result = 1;
		}
		else
		{
			result = 0;

			if (gACDbSet.CreateAccountCharacter(szId) == 1)
			{
				result = 1;
			}
		}
	}

	AccountCharacterInfo ACInfo;

	if (result == 1)
	{
		BYTE  btSlotCount = 0;
		if (gACDbSet.GetCharacterSlotCount(szId, &btSlotCount) == TRUE)
			pCount.CharacterSlotCount = btSlotCount;

		BYTE btExtendedWarehouseCount = 0;
		if (gACDbSet.GetCharacterExtendedWarehouseCount(szId, &btExtendedWarehouseCount) == TRUE)
		{
			pCount.ExtendedWarehouseCount = btExtendedWarehouseCount;
		}

		memset(&ACInfo, 0, sizeof(AccountCharacterInfo));

		if (gACDbSet.GetAccountInfo(szId, &ACInfo) == FALSE)
		{
			result = 0;
		}
		else
		{
			result = 1;

			strCharId[0] = ACInfo.GameID1;
			strCharId[1] = ACInfo.GameID2;
			strCharId[2] = ACInfo.GameID3;
			strCharId[3] = ACInfo.GameID4;
			strCharId[4] = ACInfo.GameID5;
#ifdef CHARACTER_MOVE_20040810
			pCount.MoveCnt = ACInfo.MoveCnt;
#endif
			listcount = 0;

			for (n = 0; n < 5; n++)
			{
				if (strCharId[n].GetLength() > 0 && strCharId[n].GetLength() <= MAX_IDSTRING)
				{
					memset(characterName, 0, MAX_IDSTRING + 1);
					strcpy(characterName, strCharId[n].GetBuffer(MAX_IDSTRING));

					int _level;
					int _class;
					BYTE Inventory[MAX_DBINVENTORY];

					BOOL bGetPrevChar = FALSE;
					BYTE _ctlcode = 0;
					BYTE _dbverstion = 0;
					char _pkLevel = 0;
					BYTE _btGuildStatus = 0xFF;

					//bGetPrevChar = gCharPreDBSet.GetChar(characterName, _level, _class, Inventory, _ctlcode, _dbverstion, _btGuildStatus);
					bGetPrevChar = gCharPreDBSet.GetChar(
						characterName,
						szId,
						&_level,
						&_class,
						Inventory,
						_ctlcode,
						_dbverstion,
						&_pkLevel,
						_btGuildStatus);

					if (bGetPrevChar == TRUE)
					{
						pCharList.Index = n;
						pCharList.Level = _level;
						pCharList.Class = _class;
						
						pCharList.CtlCode = _ctlcode;
						pCharList.DbVersion = _dbverstion;
#ifdef ADD_CHARACTERLIST_GUILD_STATUS_01_20050126
						pCharList.btGuildStatus = _btGuildStatus;
#endif
						memcpy(pCharList.Name, characterName, MAX_IDSTRING);

						if ((_ctlcode & 0x80) == FALSE)
						{
							/*int v17 = 0;
							if (_level >= 400 && !MasterLevelSystemDBSet.DSDB_QueryMasterLevelSystemLoad(&Name, &ReqInfo))
							{
								v17 = ReqInfo.nMLevel;
							}*/
#ifdef ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912
							if (_level >= 150)
#else
							if (_level >= 220)
#endif
							{
#ifdef DARKLORD_WORK
#ifdef ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912
								if (_level >= 250)
								{
									pCount.GenerableClass = 3;
								}
								else
#endif
									if (_level >= 220)
									{
										if (pCount.GenerableClass < 2)
										{
											pCount.GenerableClass = 2;
										}
									}
									else if (pCount.GenerableClass < 2)
#endif
									{
										pCount.GenerableClass = 1;
									}
							}
						}

						if (_dbverstion == 0)
						{
							for (int i = 0; i < MAX_EQUIPMENT; i++)
							{
								memcpy(&pCharList.dbInventory[2 * i], &Inventory[7 * i], 2);
							}
						}
						else
#if GAME_VERSION >= G_V_S1_512
							if (_dbverstion == 1 || _dbverstion == 2)
#endif
							{
								for (int k = 0; k < MAX_EQUIPMENT; k++)
								{
									memcpy(&pCharList.dbInventory[3 * k], &Inventory[10 * k], 2);
									pCharList.dbInventory[3 * k + 2] = Inventory[10 * k + 7];
								}
							}
#if GAME_VERSION >= G_V_S1_512
							else
							{
								for (int j = 0; j < MAX_EQUIPMENT; j++)
								{
									memcpy(&pCharList.dbInventory[4 * j], &Inventory[16 * j], 2);
									pCharList.dbInventory[4 * j + 2] = Inventory[16 * j + 7];
									pCharList.dbInventory[4 * j + 3] = Inventory[16 * j + 9];
								}
							}
#endif

						memcpy(&SendBuf[lOfs], &pCharList, sizeof(SDHP_CHARLIST));
						lOfs += sizeof(SDHP_CHARLIST);
						Count++;
					}
				}
			}
		}
	}

	pCount.h.c = PMHC_WORD;
	pCount.h.headcode = 0x01;
	pCount.Number = lpCLMsg->Number;
	pCount.Count = Count;
	pCount.h.sizeH = HIBYTE(lOfs);
	pCount.h.sizeL = LOBYTE(lOfs);
	memcpy(SendBuf, &pCount, sizeof(SDHP_CHARLISTCOUNT));

	wsjServer.DataSend(aIndex, (char*)SendBuf, lOfs);
}
#endif

void GDCharacterClose(LPSDHP_USERCLOSE lpMsg, short aIndex)
{
	char szChar[MAX_IDSTRING + 1];
	char szGuildName[MAX_GUILDNAMESTRING + 1];

	memset(szChar, 0, MAX_IDSTRING + 1);
	memset(szGuildName, 0, MAX_GUILDNAMESTRING + 1);

	memcpy(szChar, lpMsg->CharName, MAX_IDSTRING);
	memcpy(szGuildName, lpMsg->GuildName, MAX_GUILDNAMESTRING);

	for (int n = 0; n < 100; n++)
	{
		if (gSObj[n].Connected != 0)
		{
			wsjServer.DataSend(n, (char*)lpMsg, lpMsg->h.size);
		}
	}
}

void GJPCharacterCreate(LPSDHP_CREATECHAR lpMsg, short aIndex)
{
	char szId[MAX_IDSTRING + 1];
	char accountId[MAX_IDSTRING + 1];
	BYTE defclass;
	int Result = 0;
	CharacterInfo_Struct tCharInfo;
	SDHP_CREATECHARRESULT pMsgResult;
	int CurCharCount;

	Result = 1;

	accountId[MAX_IDSTRING] = '\0';
	memcpy(accountId, lpMsg->AccountId, MAX_IDSTRING);

	CurCharCount = gACDbSet.GetAccountCharBlank(accountId);

	if (CurCharCount < 0)
	{
		LogAdd("error-L3 : Character Max Over :%d User(%s)", 5, accountId);
		Result = 2;
	}

	szId[MAX_IDSTRING] = 0;
	memcpy(szId, lpMsg->Name, MAX_IDSTRING);

	if (SQLSyntexCheck(szId) == FALSE)
	{
		Result = 0;
	}

	if (cBadStrChk.CmpString(szId) == TRUE)
	{
		Result = 0;
	}

	if (gMuName.CmpString(szId) == 1)
	{
		Result = 0;
	}

	pMsgResult.h.c = PMHC_BYTE;
	pMsgResult.h.size = sizeof(SDHP_CREATECHARRESULT);
	pMsgResult.h.headcode = 0x04;
	pMsgResult.Result = Result;
	pMsgResult.Number = lpMsg->Number;
	pMsgResult.ClassSkin = lpMsg->ClassSkin;
	pMsgResult.Pos = CurCharCount;

	memcpy(pMsgResult.AccountId, lpMsg->AccountId, MAX_IDSTRING);
	memcpy(pMsgResult.Name, lpMsg->Name, MAX_IDSTRING);

	if (Result == 1)
	{
		memset(&tCharInfo, 0, sizeof(CharacterInfo_Struct));
		defclass = lpMsg->ClassSkin >> 4;

		if (defclass > MAX_CLASSTYPE-1)
		{
			LogAdd("error-L3 : Class over value %s %d", __FILE__, __LINE__);
			defclass = 1;
		}

		strcpy(tCharInfo.Name, szId);
#ifdef ITEM_DBSIZE_EXTEND_20050706
		ItemByteConvert16(tCharInfo.dbInventory, DCInfo.DefClass[defclass].Equipment, MAX_EQUIPMENT);
#else
		ItemByteConvert10(tCharInfo.dbInventory, DCInfo.DefClass[defclass].Equipment, MAX_EQUIPMENT);
#endif

#ifdef ITEM_DBSIZE_EXTEND_20050706
		for (int n = 0; n < MAX_EQUIPMENT; n++)
		{
			pMsgResult.Equipment[2 * n] = tCharInfo.dbInventory[16 * n];
			pMsgResult.Equipment[2 * n + 1] = tCharInfo.dbInventory[16 * n + 1];
		}
#else
		for (int n = 0; n < MAX_EQUIPMENT; n++)
		{
			pMsgResult.Equipment[2 * n] = tCharInfo.dbInventory[10 * n];
			pMsgResult.Equipment[2 * n + 1] = tCharInfo.dbInventory[10 * n + 1];
		}
#endif

		pMsgResult.Result = gCharDbSet.CreateCharacter(accountId, szId, lpMsg->ClassSkin);

#ifdef DARKLORD_WORK
		pMsgResult.Level = 1;

		if (lpMsg->ClassSkin == DB_CLASS_TYPE_DARKLORD)
		{
			pMsgResult.Level = 1;
		}
#endif

		LogAddTD("Ä³¸¯ÅÍ »ý¼º %s %s %d", accountId, szId, lpMsg->ClassSkin);
	}

	if (pMsgResult.Result == 1)
	{
		gACDbSet.SaveAccountCharacter(accountId, CurCharCount, szId);
	}
	else
	{
		LogAddTD("[ERROR!!] CreateCharacter Fail Result : %d", pMsgResult.Result);
	}

	wsjServer.DataSend(aIndex, (char*)&pMsgResult, pMsgResult.h.size);
}

void GJPCharacterDelete(LPSDHP_CHARDELETE lpMsg, short aIndex)
{
	SDHP_CHARDELETERESULT pResult;
	char szAccountId[MAX_IDSTRING + 1];
	char szCharName[MAX_IDSTRING + 1];
	char szGuildName[MAX_GUILDNAMESTRING + 1];

	memset(szAccountId, 0, MAX_IDSTRING + 1);
	memset(szCharName, 0, MAX_IDSTRING + 1);
	memset(szGuildName, 0, MAX_GUILDNAMESTRING + 1);

	pResult.h.c = PMHC_BYTE;
	pResult.h.size = sizeof(SDHP_CHARDELETERESULT);
	pResult.h.headcode = 0x05;
	pResult.Result = 1;
	pResult.Number = lpMsg->Number;

	memcpy(pResult.AccountID, lpMsg->AccountID, MAX_IDSTRING);

	szAccountId[MAX_IDSTRING] = '\0';
	szCharName[MAX_IDSTRING] = '\0';
	szGuildName[MAX_GUILDNAMESTRING] = '\0';

	memcpy(szAccountId, lpMsg->AccountID, MAX_IDSTRING);
	memcpy(szCharName, lpMsg->Name, MAX_IDSTRING);
	memcpy(szGuildName, lpMsg->GuildName, MAX_GUILDNAMESTRING);

	if (SQLSyntexCheck(szAccountId) == FALSE || SQLSyntexCheck(szCharName) == FALSE)
	{
		pResult.Result = 0;
	}

	if (strlen(szAccountId) < 1)
	{
		pResult.Result = 0;
	}

	if (strlen(szCharName) < 1)
	{
		pResult.Result = 0;
	}

	if (pResult.Result == 1)
	{
		if (gCharDbSet.DeleteCharacter(szAccountId, szCharName) == FALSE)
		{
			pResult.Result = 0;
		}
		else
		{
			if (gACDbSet.DeleteAccountCharacter(szAccountId, szCharName) >= 0)
			{
				pResult.Result = 1;
			}
#if GAME_VERSION >= G_V_S4_6
			if (gCharDbSet.DeleteCharacter_DregInfo(szCharName) == 1)
			{
				LogAdd("Character Dreg Info Delete [%s]", szCharName);
			}
#endif
		}
	}

	wsjServer.DataSend(aIndex, (char*)&pResult, pResult.h.size);

	if (lpMsg->Guild == 1)
	{
		SDHP_GUILDDESTROY pgmsg;

		memcpy(pgmsg.GuildName, szGuildName, MAX_GUILDNAMESTRING);
		memcpy(pgmsg.Master, szCharName, MAX_IDSTRING);

		pgmsg.NumberH = HIBYTE(lpMsg->Number);
		pgmsg.NumberL = LOBYTE(lpMsg->Number);

		LogAdd("Character Delete... [%s] Guild Delete [%s] ", szCharName, szGuildName);
	}
	else if (lpMsg->Guild == 2)
	{
		SDHP_GUILDDESTROY pgmsg;

		memcpy(pgmsg.GuildName, szGuildName, MAX_GUILDNAMESTRING);
		memcpy(pgmsg.Master, szCharName, MAX_IDSTRING);

		pgmsg.NumberH = HIBYTE(lpMsg->Number);
		pgmsg.NumberL = LOBYTE(lpMsg->Number);
	}
}

void GDPGetWarehouse(LPSDHP_GETWAREHOUSEDB lpMsg, int aIndex)
{
	char szId[MAX_IDSTRING + 1];
	SDHP_GETWAREHOUSEDB_SAVE pMsg;

	int _dbversion = 0;

	szId[MAX_IDSTRING] = '\0';
	memcpy(szId, lpMsg->AccountID, MAX_IDSTRING);

	pMsg.h.c = PMHC_WORD;
	pMsg.h.headcode = 0x08;
	pMsg.h.sizeH = HIBYTE(sizeof(pMsg));
	pMsg.h.sizeL = LOBYTE(sizeof(pMsg));
	pMsg.aIndex = lpMsg->aIndex;
	pMsg.Money = 0;

	int len = strlen(szId);
	if (len > 0 && len <= MAX_IDSTRING)
	{
		if (CWhDBSet.Get(szId))
		{
			memcpy(pMsg.AccountID, szId, MAX_IDSTRING);
			CWhDBSet.Load(szId, pMsg.dbItems, pMsg.Money, pMsg.DbVersion, pMsg.pw);
			wsjServer.DataSend(aIndex, (char*)&pMsg, sizeof(SDHP_GETWAREHOUSEDB_SAVE));
		}
		else
		{
			CWhDBSet.Create(szId);
			GDPWarehouseNoItemSend(aIndex, pMsg.aIndex, szId);
		}
	}
	/*char szId[MAX_IDSTRING + 1];
	SDHP_GETWAREHOUSEDB_SAVE pMsg;

	int _dbversion = 0;

	szId[MAX_IDSTRING] = '\0';
	memcpy(szId, lpMsg->AccountID, MAX_IDSTRING);

	pMsg.h.c = PMHC_WORD;
	pMsg.h.headcode = 0x08;
	pMsg.h.sizeH = HIBYTE(sizeof(pMsg));
	pMsg.h.sizeL = LOBYTE(sizeof(pMsg));
	pMsg.aIndex = lpMsg->aIndex;
	pMsg.Money = 0;

	int len = strlen(szId);

	if (len <= 0 || len > MAX_IDSTRING)
	{
		return;
	}

	if (CWhDBSet.Get(szId) == FALSE)
	{
		CWhDBSet.Create(szId);
		GDPWarehouseNoItemSend(aIndex, pMsg.aIndex, szId);
		return;
	}

	memcpy(pMsg.AccountID, szId, MAX_IDSTRING);
	CWhDBSet.Load(szId, pMsg.dbItems, pMsg.Money, pMsg.DbVersion, pMsg.pw);

	wsjServer.DataSend(aIndex, (char*)&pMsg, sizeof(SDHP_GETWAREHOUSEDB_SAVE));*/
}

void GDPWarehouseNoItemSend(int aIndex, int userindex, char *szId)
{
	SDHP_GETWAREHOUSEDB_RESULT pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.headcode = 0x10;
	pMsg.h.size = sizeof(SDHP_GETWAREHOUSEDB_RESULT);
	pMsg.aIndex = userindex;
	memcpy(pMsg.AccountID, szId, MAX_IDSTRING);

	wsjServer.DataSend(aIndex, (char*)&pMsg, sizeof(SDHP_GETWAREHOUSEDB_RESULT));
}

void GDPSetWarehouse(LPSDHP_GETWAREHOUSEDB_SAVE lpMsg, int aIndex)
{
	char szId[MAX_IDSTRING + 1];
	szId[MAX_IDSTRING] = '\0';
	memcpy(szId, lpMsg->AccountID, MAX_IDSTRING);

	int len = strlen(szId);

	if (len <= 0 || len > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ÀúÀå ¿¡·¯ %s %d", szId, __FILE__, __LINE__);
		return;
	}
	CWhDBSet.Save(szId, lpMsg->dbItems, lpMsg->Money, lpMsg->pw);
}

void GDPSetWarehouseMoney(LPSDHP_WAREHOUSEMONEY_SAVE lpMsg, int aIndex)
{
	char szId[MAX_IDSTRING + 1];
	szId[MAX_IDSTRING] = '\0';
	memcpy(szId, lpMsg->AccountID, MAX_IDSTRING);

	int len = strlen(szId);

	if (len <= 0 || len > MAX_IDSTRING)
	{
		LogAddC(LOGC_RED, "%s] ÀúÀå ¿¡·¯ %s %d", szId, __FILE__, __LINE__);
		return;
	}
	CWhDBSet.MoneyUpdate(szId, lpMsg->Money);
}

void GJPGetCharacterInfo(LPSDHP_DBCHARINFOREQUEST lpMsg, short aIndex)
{
	SDHP_DBCHAR_INFORESULT pChar;
	CharacterInfo_Struct CharObj;
	char szAccountId[MAX_IDSTRING + 1];

	pChar.h.c = PMHC_WORD;
	pChar.h.headcode = 0x6;
	pChar.h.sizeH = HIBYTE(sizeof(SDHP_DBCHAR_INFORESULT));
	pChar.h.sizeL = LOBYTE(sizeof(SDHP_DBCHAR_INFORESULT));
	pChar.result = 0x1;
	pChar.Number = lpMsg->Number;
	szAccountId[MAX_IDSTRING] = '\0';
	pChar.Name[MAX_IDSTRING] = '\0';
	memcpy(pChar.Name, lpMsg->Name, MAX_IDSTRING);
	memcpy(szAccountId, lpMsg->AccountID, MAX_IDSTRING);
	memcpy(pChar.AccountID, szAccountId, MAX_IDSTRING);
	BuxConvert(pChar.Name, MAX_IDSTRING);
	if (SpaceSyntexCheck(pChar.Name) == 1)
	{
		if (!gCharDbSet.GetCharacter(szAccountId, pChar.Name, &CharObj))
			pChar.result = 0;
		if (pChar.result == 1)
		{
			LogAddC(2, "GJPGetCharacterInfo FUCKING CHARACTER NAME IS %s", pChar.Name);
			pChar.Class = CharObj.Class;
			pChar.Level = LOWORD(CharObj.Level);
			pChar.LevelUpPoint = CharObj.LevelUpPoint;
			pChar.Exp = CharObj.Experience;
			pChar.NextExp = CharObj.NextExperience;
			pChar.Money = CharObj.Money;
			pChar.Str = CharObj.Strength;
			pChar.Dex = CharObj.Dexterity;
			pChar.Vit = CharObj.Vitality;
			pChar.Energy = CharObj.Energy;
			pChar.Life = (WORD)(CharObj.Life * 10.0);
			pChar.MaxLife = (WORD)(CharObj.MaxLife * 10.0);
			pChar.Mana = (WORD)(CharObj.Mana * 10.0);
			pChar.MaxMana = (WORD)(CharObj.MaxMana * 10.0);
			pChar.MapNumber = CharObj.MapNumber;
			pChar.MapX = CharObj.MapX;
			pChar.MapY = CharObj.MapY;
			pChar.Dir = CharObj.Dir;
			pChar.PkCount = CharObj.PkCount;
			pChar.PkLevel = CharObj.PkLevel;
			pChar.PkTime = CharObj.PkTime;
			pChar.CtlCode = CharObj.CtlCode;
			pChar.DbVersion = CharObj.DbVersion;

			pChar.Leadership = CharObj.Leadership;
			pChar.ChatLitmitTime = CharObj.ChatLitmitTime;
			pChar.iFruitPoint = CharObj.FruitPoint;
			pChar.btExtendedInvenCount = CharObj.btExtendedInvenCount;
			pChar.btExtendedWarehouseCount = CharObj.btExtendedWarehouseCount;
			pChar.WareHouseMoney = CWhDBSet.GetWareHouseMoney(pChar.AccountID);
			memcpy(pChar.dbInventory, CharObj.dbInventory, MAX_DBINVENTORY);
			memcpy(pChar.dbMagicList, CharObj.dbMagicList, MAX_DBMAGIC);
			memcpy(pChar.dbQuest, CharObj.dbQuest, MAX_DBQUEST);
			gACDbSet.CurAccountCharacterSet(szAccountId, pChar.Name);
			int nRuudCnt = 0;
			gCharDbSet.RuudToken_LoadCount(szAccountId, pChar.Name, &nRuudCnt);
			pChar.dwRuudToken = nRuudCnt;
		}
	}
	else
	{
		pChar.result = 0;
	}
	wsjServer.DataSend(aIndex, (char*)&pChar, sizeof(SDHP_DBCHAR_INFORESULT));;
	if (pChar.result == 1)
		GDSkillKeyDataSend(pChar.Name, lpMsg->Number, aIndex);
//	SDHP_DBCHAR_INFORESULT pChar;
//	CharacterInfo_Struct CharObj;
//	char szAccountId[MAX_IDSTRING + 1];
//
//	pChar.h.c = PMHC_WORD;
//	pChar.h.headcode = 0x6;
//	pChar.h.sizeH = HIBYTE(sizeof(SDHP_DBCHAR_INFORESULT));
//	pChar.h.sizeL = LOBYTE(sizeof(SDHP_DBCHAR_INFORESULT));
//	pChar.result = 0x1;
//	pChar.Number = lpMsg->Number;
//
//	szAccountId[MAX_IDSTRING] = '\0';
//	pChar.Name[MAX_IDSTRING] = '\0';
//
//	memcpy(pChar.Name, lpMsg->Name, MAX_IDSTRING);
//	memcpy(szAccountId, lpMsg->AccountID, MAX_IDSTRING);
//	memcpy(pChar.AccountID, szAccountId, MAX_IDSTRING);
//	BuxConvert(pChar.Name, MAX_IDSTRING);
//
//	if (SpaceSyntexCheck(pChar.Name) == 1)
//	{
//		if (gCharDbSet.GetCharacter(szAccountId, pChar.Name, &CharObj) == FALSE)
//		{
//			pChar.result = 0;
//		}
//
//		if (pChar.result == 1)
//		{
//			LogAddC(2,"GJPGetCharacterInfo FUCKING CHARACTER NAME IS %S", pChar.Name);
//			pChar.Class = CharObj.Class;
//			pChar.Level = LOWORD(CharObj.Level);
//			pChar.LevelUpPoint = CharObj.LevelUpPoint;
//			pChar.Exp = CharObj.Experience;
//			pChar.NextExp = CharObj.NextExperience;
//			pChar.Money = CharObj.Money;
//			pChar.Str = CharObj.Strength;
//			pChar.Dex = CharObj.Dexterity;
//			pChar.Vit = CharObj.Vitality;
//			pChar.Energy = CharObj.Energy;
//			pChar.Life = (WORD)(CharObj.Life * 10.0);
//			pChar.MaxLife = (WORD)(CharObj.MaxLife * 10.0);
//			pChar.Mana = (WORD)(CharObj.Mana * 10.0);
//			pChar.MaxMana = (WORD)(CharObj.MaxMana * 10.0);
//			pChar.MapNumber = CharObj.MapNumber;
//			pChar.MapX = CharObj.MapX;
//			pChar.MapY = CharObj.MapY;
//			pChar.Dir = CharObj.Dir;
//			pChar.PkCount = CharObj.PkCount;
//			pChar.PkLevel = CharObj.PkLevel;
//			pChar.PkTime = CharObj.PkTime;
//			pChar.CtlCode = CharObj.CtlCode;
//			pChar.DbVersion = CharObj.DbVersion;
//#ifdef DARKLORD_WORK
//			pChar.Leadership = CharObj.Leadership;
//			pChar.ChatLitmitTime = CharObj.ChatLitmitTime;
//#endif
//#ifdef ADD_MINUS_STAT_SYSTEM_USING_FRUIT_20050712
//			pChar.iFruitPoint = CharObj.FruitPoint;
//#endif
//			pChar.btExtendedInvenCount = CharObj.btExtendedInvenCount;
//			pChar.btExtendedWarehouseCount = CharObj.btExtendedWarehouseCount;
//			pChar.WareHouseMoney = CWhDBSet.GetWareHouseMoney(pChar.Name);
//			//pChar.sExGameServerCode = CharObj.sExGameServerCode;
//			memcpy(pChar.dbInventory, CharObj.dbInventory, MAX_DBINVENTORY);
//			memcpy(pChar.dbMagicList, CharObj.dbMagicList, MAX_DBMAGIC);
//			memcpy(pChar.dbQuest, CharObj.dbQuest, MAX_DBQUEST);
//			gACDbSet.CurAccountCharacterSet(szAccountId, pChar.Name);
//			int nRuudCnt = 0;
//			gCharDbSet.RuudToken_LoadCount(szAccountId, pChar.Name, &nRuudCnt);
//			pChar.dwRuudToken = nRuudCnt;
//			//gACDbSet.RequestVipTime(szAccountId, pChar.AccountType, pChar.EndTime);
//		}
//	}
//	else
//	{
//		pChar.result = 0;
//	}
//
//	wsjServer.DataSend(aIndex, (char*)&pChar, sizeof(SDHP_DBCHAR_INFORESULT));
//
//	if (pChar.result == 1)
//	{
//		GDSkillKeyDataSend(pChar.Name, lpMsg->Number, aIndex);
//	}
}

void GJPSetCharacterInfo(LPSDHP_DBCHAR_INFOSAVE lpMsg, short aIndex)
{
	CharacterInfo_Struct CharObject;
	memset(&CharObject, 0, sizeof(CharacterInfo_Struct));

	if (strlen(lpMsg->Name) >= 1)
	{
		LogAddC(2, "GJPSetCharacterInfo FUCKING CHARACTER NAME IS %s", lpMsg->Name);
		CharObject.Name[MAX_IDSTRING] = '\0';
		memcpy(CharObject.Name, lpMsg->Name, MAX_IDSTRING);
		CharObject.Class = lpMsg->Class;
		CharObject.Level = lpMsg->Level;
		CharObject.LevelUpPoint = lpMsg->LevelUpPoint;
		CharObject.Experience = lpMsg->Exp;
		CharObject.NextExperience = lpMsg->NextExp;
		CharObject.Money = lpMsg->Money;
		CharObject.Strength = lpMsg->Str;
		CharObject.Dexterity = lpMsg->Dex;
		CharObject.Vitality = lpMsg->Vit;
		CharObject.Energy = lpMsg->Energy;

		if (lpMsg->Life != 0)
		{
			CharObject.Life = (float)lpMsg->Life;
			CharObject.Life /= 10.0f;
		}
		else
		{
			CharObject.Life = 0;
		}

		if (lpMsg->MaxLife != 0)
		{
			CharObject.MaxLife = (float)lpMsg->MaxLife;
			CharObject.MaxLife /= 10.0f;
		}
		else
		{
			CharObject.MaxLife = 0;
		}

		if (lpMsg->Mana != 0)
		{
			CharObject.Mana = (float)lpMsg->Mana;
			CharObject.Mana /= 10.0f;
		}
		else
		{
			CharObject.Mana = 0;
		}

		if (lpMsg->MaxMana != 0)
		{
			CharObject.MaxMana = (float)lpMsg->MaxMana;
			CharObject.MaxMana /= 10.0f;
		}
		else
		{
			CharObject.MaxMana = 0;
		}

		CharObject.MapNumber = lpMsg->MapNumber;
		CharObject.MapX = lpMsg->MapX;
		CharObject.MapY = lpMsg->MapY;
		CharObject.Dir = lpMsg->Dir;
		CharObject.PkCount = lpMsg->PkCount;
		CharObject.PkLevel = lpMsg->PkLevel;
		CharObject.PkTime = lpMsg->PkTime;
		CharObject.Leadership = lpMsg->Leadership;
		CharObject.ChatLitmitTime = lpMsg->ChatLitmitTime;
		CharObject.FruitPoint = lpMsg->iFruitPoint;
		memcpy(CharObject.dbInventory, lpMsg->dbInventory, MAX_DBINVENTORY);
		memcpy(CharObject.dbMagicList, lpMsg->dbMagicList, MAX_DBMAGIC);
		memcpy(CharObject.dbQuest, lpMsg->dbQuest, MAX_DBQUEST);
		memcpy(CharObject.AccountID, lpMsg->AccountId, MAX_IDSTRING);
		gCharDbSet.SaveCharacter(CharObject.Name, &CharObject);

		if (lpMsg->CharInfoSave == 1)
		{
			gCharDbSet.CurCharNameSave(CharObject.Name);
		}
	}
	else
	{
		LogAdd("error-L2 : Name is zero %s %d", __FILE__, __LINE__);
	}
	//CharacterInfo_Struct CharObject;
	//memset(&CharObject, 0, sizeof(CharacterInfo_Struct));
	//LogAddC(2, "GJPSetCharacterInfo FUCKING CHARACTER NAME IS %S", lpMsg->Name);
	//if (strlen(lpMsg->Name) < 1)
	//{
	//	LogAdd("error-L2 : Name is zero %s %d", __FILE__, __LINE__);
	//	return;
	//}

	//CharObject.Name[MAX_IDSTRING] = '\0';
	//memcpy(CharObject.Name, lpMsg->Name, MAX_IDSTRING);

	//CharObject.Class = lpMsg->Class;
	//CharObject.Level = lpMsg->Level;
	//CharObject.LevelUpPoint = lpMsg->LevelUpPoint;
	//CharObject.Experience = lpMsg->Exp;
	//CharObject.NextExperience = lpMsg->NextExp;
	//CharObject.Money = lpMsg->Money;
	//CharObject.Strength = lpMsg->Str;
	//CharObject.Dexterity = lpMsg->Dex;
	//CharObject.Vitality = lpMsg->Vit;
	//CharObject.Energy = lpMsg->Energy;

	//if (lpMsg->Life != 0)
	//{
	//	CharObject.Life = (float)lpMsg->Life;
	//	CharObject.Life /= 10.0f;
	//}
	//else
	//{
	//	CharObject.Life = 0;
	//}

	//if (lpMsg->MaxLife != 0)
	//{
	//	CharObject.MaxLife = (float)lpMsg->MaxLife;
	//	CharObject.MaxLife /= 10.0f;
	//}
	//else
	//{
	//	CharObject.MaxLife = 0;
	//}

	//if (lpMsg->Mana != 0)
	//{
	//	CharObject.Mana = (float)lpMsg->Mana;
	//	CharObject.Mana /= 10.0f;
	//}
	//else
	//{
	//	CharObject.Mana = 0;
	//}

	//if (lpMsg->MaxMana != 0)
	//{
	//	CharObject.MaxMana = (float)lpMsg->MaxMana;
	//	CharObject.MaxMana /= 10.0f;
	//}
	//else
	//{
	//	CharObject.MaxMana = 0;
	//}

	//CharObject.MapNumber = lpMsg->MapNumber;
	//CharObject.MapX = lpMsg->MapX;
	//CharObject.MapY = lpMsg->MapY;
	//CharObject.Dir = lpMsg->Dir;
	//CharObject.PkCount = lpMsg->PkCount;
	//CharObject.PkLevel = lpMsg->PkLevel;
	//CharObject.PkTime = lpMsg->PkTime;
	//CharObject.Leadership = lpMsg->Leadership;
	//CharObject.ChatLitmitTime = lpMsg->ChatLitmitTime;
	//CharObject.FruitPoint = lpMsg->iFruitPoint;

	////CharObject.sExGameServerCode = lpMsg->sExGameServerCode;
	//memcpy(CharObject.dbInventory, lpMsg->dbInventory, MAX_DBINVENTORY);
	//memcpy(CharObject.dbMagicList, lpMsg->dbMagicList, MAX_DBMAGIC);
	//memcpy(CharObject.dbQuest, lpMsg->dbQuest, MAX_DBQUEST);
	//gCharDbSet.SaveCharacter(CharObject.Name, &CharObject);
	//memcpy(CharObject.AccountID, lpMsg->AccountId, MAX_IDSTRING);
	////gACDbSet.UpdateVipTime(lpMsg->AccountID, lpMsg->DecreaseTime);

	//if (lpMsg->CharInfoSave == 1)
	//{
	//	gCharDbSet.CurCharNameSave(CharObject.Name);
	//}
}

void GJPSetItemSave(LPSDHP_DBCHAR_ITEMSAVE lpMsg, short aIndex)
{
	char szId[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];

	memset(szName, 0, MAX_IDSTRING + 1);
	memcpy(szName, lpMsg->Name, MAX_IDSTRING);
	if (strlen(szName))
	{
		szId[10] = 0;
		memcpy(szId, lpMsg->AccountID, MAX_IDSTRING);
		if (strlen(szId))
			gCharDbSet.SaveItem(szName, lpMsg->dbInventory, szId);
	}
	//char szName[MAX_IDSTRING + 1];
	//memset(szName, 0, MAX_IDSTRING + 1);
	//memcpy(szName, lpMsg->Name, MAX_IDSTRING);

	//if (strlen(szName) <= 0)
	//{
	//	return;
	//}

	//gCharDbSet.SaveItem(szName, lpMsg->dbInventory);
}

void GDReqQuestMonKillInfo(BYTE* lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	LPSDHP_REQ_QUEST_MONSTER_KILL lpMsg = (LPSDHP_REQ_QUEST_MONSTER_KILL)lpRecv;
	DGSendQuestMonKillInfo(lpMsg->szCharName, lpMsg->iUserIndex, aIndex);
}

void DGSendQuestMonKillInfo(char *szCharName, int iUserIndex, int aIndex)
{
	SDHP_QUEST_MONSTER_KILL_INFO pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x14, sizeof(SDHP_QUEST_MONSTER_KILL_INFO));
	pMsgSend.iUserIndex = iUserIndex;

	if (QuestMonKillDBSet.DSDB_QueryQuestMonKillInfoLoad(szCharName, &pMsgSend) == TRUE)
	{
		pMsgSend.btQuestDBIndex = -1;
		pMsgSend.iQuestMonIndex1 = -1;
		pMsgSend.iKillCount1 = -1;
		pMsgSend.iQuestMonIndex2 = -1;
		pMsgSend.iKillCount2 = -1;
		pMsgSend.iQuestMonIndex3 = -1;
		pMsgSend.iKillCount3 = -1;
		pMsgSend.iQuestMonIndex4 = -1;
		pMsgSend.iKillCount4 = -1;
		pMsgSend.iQuestMonIndex5 = -1;
		pMsgSend.iKillCount5 = -1;
	}

	memcpy(pMsgSend.szCharName, szCharName, MAX_IDSTRING);
	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(SDHP_QUEST_MONSTER_KILL_INFO));
}

void GDReqQuestMonKillInfoSave(BYTE*lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	QuestMonKillDBSet.DSDB_QueryQuestMonKillInfoSave((LPSDHP_QUEST_MONSTER_KILL_INFO)lpRecv);
}

void GetGameServerInfo(LPSDHP_GAMESERVERINFO lpMsg, short aIndex)
{
	gGSDbSet.SetCount(lpMsg->ItemCount);
}

void DSSendResultSend(int aIndex, BYTE headcode, BYTE result)
{
	SDHP_DEFAULT_RESULT pMsg;

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.headcode = headcode;
	pMsg.h.size = sizeof(SDHP_DEFAULT_RESULT);
	pMsg.Result = result;
	wsjServer.DataSend(aIndex, (char*)&pMsg, pMsg.h.size);
}

void GDLoadMedalInfo(LPSDHP_LOAD_MEDALINFO lpMsg, int aIndex)
{
	SDHP_LOAD_MEDALINFO_RESULT pMsg;

	memset(&pMsg, 0, sizeof(SDHP_LOAD_MEDALINFO_RESULT));
	pMsg.h.set((LPBYTE)&pMsg, 0x2D, sizeof(SDHP_LOAD_MEDALINFO_RESULT));

	pMsg.wIndex = lpMsg->wIndex;
	pMsg.dwItemSerial = lpMsg->dwItemSerial;
	pMsg.wItemIndex = lpMsg->wItemIndex;

	if (gGSDbSet.GetPropertyItemInfo(lpMsg->dwItemSerial, &pMsg) == 1)
	{
		wsjServer.DataSend(aIndex, (char*)&pMsg, pMsg.h.size);
	}
	else
	{
		LogAdd("error-L2 : GetPropertyItemInfo() serial:%u index: %d", lpMsg->dwItemSerial, lpMsg->wIndex);
	}
}

#ifdef MASTER_LEVEL_UP_SYSTEM_20070912
void GDReqMasterLevelInfo(LPMLP_REQ_MASTERLEVEL_INFO lpMsg, int aIndex)
{
	MLP_ANS_MASTERLEVEL_INFO pMsgSend;

	if (lpMsg == NULL)
	{
		return;
	}

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x30, sizeof(MLP_ANS_MASTERLEVEL_INFO));
	pMsgSend.iUserIndex = lpMsg->iUserIndex;
	pMsgSend.btResult = 1;

	if (MasterLevelSystemDBSet.DSDB_QueryMasterLevelSystemLoad(lpMsg->szCharName, &pMsgSend) == TRUE)
	{
		pMsgSend.btResult = 0;
	}

	memcpy(pMsgSend.szCharName, lpMsg->szCharName, MAX_IDSTRING);
	pMsgSend.szCharName[MAX_IDSTRING] = '\0';

	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(MLP_ANS_MASTERLEVEL_INFO));
}

void GDReqMasterLevelInfoSave(LPMLP_REQ_MASTERLEVEL_INFOSAVE lpMsg, int aIndex)
{
	if (lpMsg == NULL)
	{
		return;
	}

	MasterLevelSystemDBSet.DSDB_QueryMasterLevelSystemSave(lpMsg);
}
#endif

void GDSkillKeyDataRecv(LPSDHP_SKILLKEYDATA lpMsg)
{
	char szName[MAX_IDSTRING + 1];

	memset(szName, 0, MAX_IDSTRING + 1);
	memcpy(szName, lpMsg->Name, MAX_IDSTRING);
	gOptionDbSet.Save(
		szName,
		lpMsg->SkillKeyBuffer,
		lpMsg->GameOption,
		lpMsg->QkeyDefine,
		lpMsg->WkeyDefine,
		lpMsg->EkeyDefine,
		lpMsg->ChatWindow,
		lpMsg->RkeyDefine,
		lpMsg->QWERLevel,
		lpMsg->EnableTransfromMode,
		lpMsg->PlayGuideLv,
		lpMsg->PlayGuideCheck);
//	gOptionDbSet.Save(szName, lpMsg->SkillKeyBuffer, lpMsg->GameOption, lpMsg->QkeyDefine, lpMsg->WkeyDefine, lpMsg->EkeyDefine
//#ifdef VER_CHATWINDOW_OPTION
//		, lpMsg->ChatWindow
//#endif
//#ifdef ADD_SEASON_3_NEW_UI_20071122
//		, lpMsg->RkeyDefine
//#endif
//#ifdef UPDATE_OPTIONKEY_LEVEL_20080116
//		, lpMsg->QWERLevel
//#endif
	//);
}

void GDSkillKeyDataSend(char *name, int userindex, int aIndex)
{
	SDHP_SKILLKEYDATA_SEND pMsg;

#ifdef UPDATE_SKILLKEY_EXPAND_20080804
	BYTE KeyBuf[20];
#else
	BYTE KeyBuf[10];
#endif

	if (gOptionDbSet.Load(name, KeyBuf, pMsg.GameOption, pMsg.QkeyDefine, pMsg.WkeyDefine, pMsg.EkeyDefine
		, pMsg.ChatWindow
		, pMsg.RkeyDefine
		, pMsg.QWERLevel,
		pMsg.EnableTransfromMode,
		pMsg.PlayGuideLv,
		pMsg.PlayGuideCheck) < 1)
	{
		return;
	}

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.headcode = 0x60;
	pMsg.h.size = sizeof(SDHP_SKILLKEYDATA_SEND);

	memcpy(pMsg.Name, name, MAX_IDSTRING);
	memcpy(pMsg.SkillKeyBuffer, KeyBuf, sizeof(KeyBuf));

	pMsg.aIndex = userindex;

	wsjServer.DataSend(aIndex, (char*)&pMsg, pMsg.h.size);
}

void GDZenSave(LPSDHP_ZENSAVE lpMsg, int aIndex)
{
	char szId[MAX_IDSTRING + 1];

	SDHP_ZENLOAD pMsg;

	int Zen = lpMsg->Total;

	szId[MAX_IDSTRING] = '\0';
	memcpy(szId, lpMsg->AccountID, MAX_IDSTRING);

	CZenEvenDBSet.SetZen(szId, Zen);

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.headcode = 0x50;
	pMsg.h.size = sizeof(SDHP_ZENLOAD);
	memcpy(pMsg.AccountID, szId, MAX_IDSTRING);
	pMsg.Total = Zen;
	pMsg.Number = lpMsg->Number;

	wsjServer.DataSend(aIndex, (char*)&pMsg, pMsg.h.size);
}
void GDItemCreate(SDHP_ITEMCREATE *lpMsg, int aIndex)
{
	SDHP_ITEMCREATERECV pMsg;

	DWORD s_num = gWzItemSerial.GetSerial();
	pMsg.h.c = PMHC_BYTE;
	pMsg.h.headcode = 0x52;
	pMsg.h.size = sizeof(SDHP_ITEMCREATERECV);
	pMsg.Dur = lpMsg->Dur;
	pMsg.Level = lpMsg->Level;
	//pMsg.MapNumber = lpMsg->MapNumber;
	*(WORD *)(&pMsg.MapNumber + 1) = lpMsg->MapNumber;
	pMsg.Type = lpMsg->Type;
	pMsg.x = lpMsg->x;
	pMsg.y = lpMsg->y;
	pMsg.Op1 = lpMsg->Op1;
	pMsg.Op2 = lpMsg->Op2;
	pMsg.Op3 = lpMsg->Op3;
	pMsg.aIndex = lpMsg->aIndex;
	pMsg.NewOption = lpMsg->NewOption;
	pMsg.m_Number = s_num;
	pMsg.lootindex = lpMsg->lootindex;
	pMsg.SetOption = lpMsg->SetOption;
	pMsg.SocketSlotCount = lpMsg->SocketSlotCount;
	pMsg.lDuration = lpMsg->lDuration;
	pMsg.dwEventIndex = lpMsg->dwEventIndex;
	if (lpMsg != (SDHP_ITEMCREATE *)0xFFFFFFE0)
	{
		for (int i = 0; i < 5; ++i)
			pMsg.SocketOption[i] = lpMsg->SocketOption[i];
	}
	pMsg.MainAttribute = lpMsg->MainAttribute;
	wsjServer.DataSend(aIndex, (char*)&pMsg.h.c, pMsg.h.size);
	if (lpMsg->Type == ITEM_POTION + 13 ||
		lpMsg->Type == ITEM_POTION + 14 ||
		lpMsg->Type == ITEM_POTION + 16 ||
		lpMsg->Type == ITEM_POTION + 22 ||
		lpMsg->Type == ITEM_WING + 15 ||
		lpMsg->Type == ITEM_WING + 30 ||
		lpMsg->Type == ITEM_WING + 31 ||
		lpMsg->Type == ITEM_POTION + 31)
	{
		ITEM_SERIAL_LOG.Output("[Item Serial] [%s][%d] Type(%d) Serial(%u)",
			gSObj[aIndex].Ip, gSObj[aIndex].Port, lpMsg->Type, s_num);
	}
}
//void GDItemCreate(LPSDHP_ITEMCREATE lpMsg, int aIndex)
//{
//	SDHP_ITEMCREATERECV pMsg;
//
//	DWORD s_num = gWzItemSerial.GetSerial();
//
//	pMsg.h.c = PMHC_BYTE;
//	pMsg.h.headcode = 0x52;
//	pMsg.h.size = sizeof(SDHP_ITEMCREATERECV);
//	pMsg.Dur = lpMsg->Dur;
//	pMsg.Level = lpMsg->Level;
//	pMsg.MapNumber = lpMsg->MapNumber;
//	//*(WORD *)(&pMsg.MapNumber + 1) = lpMsg->MapNumber;
//	pMsg.Type = lpMsg->Type;
//	pMsg.x = lpMsg->x;
//	pMsg.y = lpMsg->y;
//	pMsg.Op1 = lpMsg->Op1;
//	pMsg.Op2 = lpMsg->Op2;
//	pMsg.Op3 = lpMsg->Op3;
//	pMsg.aIndex = lpMsg->aIndex;
//	pMsg.NewOption = lpMsg->NewOption;
//	pMsg.m_Number = s_num;
//	pMsg.lootindex = lpMsg->lootindex;
//	pMsg.SetOption = lpMsg->SetOption;
//	pMsg.SocketSlotCount = lpMsg->SocketSlotCount;
//	pMsg.lDuration = lpMsg->lDuration;
//	pMsg.dwEventIndex = lpMsg->dwEventIndex;
//	if (lpMsg != (SDHP_ITEMCREATE *)0xFFFFFFE0)
//	{
//		for (int i = 0; i < 5; ++i)
//			pMsg.SocketOption[i] = lpMsg->SocketOption[i];
//	}
//	pMsg.MainAttribute = lpMsg->MainAttribute;
//	wsjServer.DataSend(aIndex, (char*)&pMsg, pMsg.h.size);
//
//	if (lpMsg->Type == ITEM_POTION + 13 ||
//		lpMsg->Type == ITEM_POTION + 14 ||
//		lpMsg->Type == ITEM_POTION + 16 ||
//		lpMsg->Type == ITEM_POTION + 22 ||
//		lpMsg->Type == ITEM_WING + 15 ||
//		lpMsg->Type == ITEM_WING + 30 ||
//		lpMsg->Type == ITEM_WING + 31 ||
//		lpMsg->Type == ITEM_POTION + 31)
//	{
//		ITEM_SERIAL_LOG.Output("[Item Serial] [%s][%d] Type(%d) Serial(%u)",
//			gSObj[aIndex].Ip, gSObj[aIndex].Port, lpMsg->Type, s_num);
//	}
//}

void GDPropertyItemCreate(LPSDHP_PROPERTY_ITEMCREATE lpMsg, int aIndex)
{
	SDHP_PROPERTY_ITEMRECV pMsg;

	DWORD s_num = gWzItemSerial.GetSerial();

	pMsg.h.set((LPBYTE)&pMsg, 0x54, sizeof(SDHP_PROPERTY_ITEMRECV));

	if (gGSDbSet.CreatePropertyItemInfo(s_num, lpMsg) == FALSE)
	{
		LogAdd("error-L1 : CreatePropertyItemInfo %u ", s_num);
	}

	pMsg.Dur = lpMsg->Dur;
	pMsg.Level = lpMsg->Level;
	pMsg.MapNumber = lpMsg->MapNumber;
	pMsg.Type = lpMsg->Type;
	pMsg.x = lpMsg->x;
	pMsg.y = lpMsg->y;
	pMsg.Op1 = lpMsg->Op1;
	pMsg.Op2 = lpMsg->Op2;
	pMsg.Op3 = lpMsg->Op3;
	pMsg.aIndex = lpMsg->aIndex;
	pMsg.NewOption = lpMsg->NewOption;
	pMsg.m_Number = s_num;
	pMsg.lootindex = lpMsg->lootindex;
	pMsg.SetOption = lpMsg->SetOption;
	pMsg.dwTime = lpMsg->dwTime;

	memcpy(pMsg.szName, lpMsg->szName, MAX_IDSTRING);
	memcpy(pMsg.szName_T, lpMsg->szName_T, MAX_IDSTRING);
	pMsg.wLevel = lpMsg->wLevel;
	pMsg.wLevel_T = lpMsg->wLevel_T;
	pMsg.wItemIndex = lpMsg->wItemIndex;
	pMsg.wRemainTime = lpMsg->wRemainTime;

	wsjServer.DataSend(aIndex, (char*)&pMsg, pMsg.h.size);
}

void GDCharacterTransfer(LPSDHP_CHARACTER_TRANSFER lpMsg, int aIndex)
{
	SDHP_CHARACTER_TRANSFER_RESULT pMsg;

	char id[MAX_IDSTRING + 1];

	memset(id, 0, MAX_IDSTRING);
	memcpy(id, lpMsg->Account, MAX_IDSTRING);

	pMsg.Result = 1;

	if (strlen(id) > 1)
	{
		pMsg.Result = gCharDbSet.CharServerMove(id);
	}

	pMsg.h.c = PMHC_BYTE;
	pMsg.h.headcode = 0xCF;
	pMsg.h.size = sizeof(SDHP_CHARACTER_TRANSFER_RESULT);

	memcpy(pMsg.Account, lpMsg->Account, MAX_IDSTRING);

	pMsg.Number = lpMsg->Number;

	wsjServer.DataSend(aIndex, (char*)&pMsg, pMsg.h.size);
}

#ifdef DARKLORD_WORK
void GDPetItemCreate(LPSDHP_PET_ITEMCREATE lpMsg, int aIndex)
{
	SDHP_PET_ITEMCREATERECV pMsg;

	DWORD s_num = gWzItemSerial.GetSerial();

	pMsg.h.set((LPBYTE)&pMsg, 0x52, sizeof(SDHP_PET_ITEMCREATERECV));

	if (PetDBSet.CreatePetItemInfo(s_num, 1, 0) == FALSE)
	{
		LogAdd("error-L1 : CreatePetItemInfo %u ", s_num);
	}

	pMsg.Dur = lpMsg->Dur;
	pMsg.Level = lpMsg->Level;
	pMsg.MapNumber = lpMsg->MapNumber;
	pMsg.Type = lpMsg->Type;
	pMsg.x = lpMsg->x;
	pMsg.y = lpMsg->y;
	pMsg.Op1 = lpMsg->Op1;
	pMsg.Op2 = lpMsg->Op2;
	pMsg.Op3 = lpMsg->Op3;
	pMsg.aIndex = lpMsg->aIndex;
	pMsg.NewOption = lpMsg->NewOption;
	pMsg.m_Number = s_num;
	pMsg.lootindex = lpMsg->lootindex;
	pMsg.SetOption = lpMsg->SetOption;

	wsjServer.DataSend(aIndex, (char*)&pMsg, pMsg.h.size);
}

void DGGetPetItemInfo(BYTE *lpRecv, int aIndex)
{
	Recv_PetItem_Info pMsg; //10

	SDHP_RECV_PETITEM_INFO pHeader; //24

	SDHP_REQUEST_PETITEM_INFO* lpHeader; //28

	Request_PetItem_Info* lpItem; //2c

	BYTE lpMsgBuf[4096]; //102C

	int MsgOfs = 0;

	lpHeader = (SDHP_REQUEST_PETITEM_INFO*)lpRecv;

	if (lpHeader->nCount < 1)
	{
		return;
	}

	LogAdd("Æê ¾ÆÀÌÅÛ Á¤º¸ ¿äÃ» count %d", lpHeader->nCount);

	MsgOfs += sizeof(SDHP_REQUEST_PETITEM_INFO);

	lpItem = (Request_PetItem_Info*)(lpRecv + MsgOfs);

	int level = 0;
	int exp = 0;

	for (int n = 0; n < lpHeader->nCount; n++)
	{
		PetDBSet.LoadPetInfo(lpItem[n].nSerial, level, exp);
		pMsg.nPos = lpItem[n].nPos;
		pMsg.nSerial = lpItem[n].nSerial;
		pMsg.Level = level;
		pMsg.Exp = exp;
		memcpy(&lpMsgBuf[MsgOfs], &pMsg, sizeof(Recv_PetItem_Info));
		MsgOfs += sizeof(Recv_PetItem_Info);
		LogAdd("Æê ¾ÆÀÌÅÛ (Serial:%u) Level : %d Exp : %d", lpItem[n].nSerial, level, exp);
	}

	pHeader.h.set((LPBYTE)&pHeader, 0x56, MsgOfs);
	memcpy(pHeader.AccountID, lpHeader->AccountID, MAX_IDSTRING);
	pHeader.Number = lpHeader->Number;
	pHeader.InvenType = lpHeader->InvenType;
	pHeader.nCount = lpHeader->nCount;
	memcpy(lpMsgBuf, &pHeader, sizeof(SDHP_REQUEST_PETITEM_INFO));

	wsjServer.DataSend(aIndex, (char*)&lpMsgBuf, MsgOfs);
}

void DGSetPetItemInfo(BYTE *lpRecv, int aIndex)
{
	int n; // [esp+D0h] [ebp-20h]
	Save_PetItem_Info *lpMsg; // [esp+DCh] [ebp-14h]
	SDHP_SAVE_PETITEM_INFO *lpHeader; // [esp+E8h] [ebp-8h]

	lpHeader = (SDHP_SAVE_PETITEM_INFO *)lpRecv;
	if (lpRecv[4] >= 1)
	{
		LogAdd("Æê ¾ÆÀÌÅÛ Á¤º¸ ÀúÀå ¿äÃ» count %d", lpHeader->nCount);
		lpMsg = (CONTAINING_RECORD(lpRecv, Save_PetItem_Info, Level) + 14);
		for (n = 0; n < lpHeader->nCount; ++n)
		{
			if (lpHeader->ServerType == 1)
				PetDBSet.SavePetInfoForUBF(lpMsg[n].nSerial, lpMsg[n].Level, lpMsg[n].Exp, lpHeader->ServerCode);
			else
				PetDBSet.SavePetInfo(lpMsg[n].nSerial, lpMsg[n].Level, lpMsg[n].Exp);
			LogAdd("Æê ¾ÆÀÌÅÛ Á¤º¸ ÀúÀå (Serial : %u) Level : %d   Exp : %d", lpMsg[n].nSerial, lpMsg[n].Level, LODWORD(lpMsg[n].Exp), HIDWORD(lpMsg[n].Exp));
		}
	}
	/*SDHP_SAVE_PETITEM_INFO* lpHeader = (SDHP_SAVE_PETITEM_INFO*)lpRecv;

	if (lpHeader->nCount < 1)
	{
		return;
	}

	LogAdd("Æê ¾ÆÀÌÅÛ Á¤º¸ ÀúÀå ¿äÃ» count %d", lpHeader->nCount);
	Save_PetItem_Info* lpMsg = (Save_PetItem_Info*)&lpRecv[5];

	for (int n = 0; n < lpHeader->nCount; n++)
	{
		PetDBSet.SavePetInfo(lpMsg[n].nSerial, lpMsg[n].Level, lpMsg[n].Exp);
		LogAdd("Æê ¾ÆÀÌÅÛ Á¤º¸ ÀúÀå (Serial : %u) Level : %d   Exp : %d", lpMsg[n].nSerial, lpMsg[n].Level, lpMsg[n].Exp);
	}*/
}
#endif

#ifdef MU_CASTLESIEGE_DS_PROTOCOL_20041105
void DS_GDReqCastleTotalInfo(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_CASTLEDATA* lpMsg = (CSP_REQ_CASTLEDATA*)lpRecv;
	CASTLE_DATA pCastleData;
	CSP_ANS_CASTLEDATA pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x00, sizeof(CSP_ANS_CASTLEDATA));

	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;

	int iRES = CastleDBSet.DSDB_QueryCastleTotalInfo(lpMsg->wMapSvrNum, lpMsg->iCastleEventCycle, &pCastleData);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
		wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_CASTLEDATA));
	}
	else
	{
		pMsgSend.iResult = 1;
		pMsgSend.wStartYear = pCastleData.wStartYear;
		pMsgSend.btStartMonth = pCastleData.btStartMonth;
		pMsgSend.btStartDay = pCastleData.btStartDay;
		pMsgSend.wEndYear = pCastleData.wEndYear;
		pMsgSend.btEndMonth = pCastleData.btEndMonth;
		pMsgSend.btEndDay = pCastleData.btEndDay;
		pMsgSend.btIsSiegeGuildList = pCastleData.btIsSiegeGuildList;
		pMsgSend.btIsSiegeEnded = pCastleData.btIsSiegeEnded;
		pMsgSend.btIsCastleOccupied = pCastleData.btIsCastleOccupied;
		pMsgSend.i64CastleMoney = pCastleData.i64CastleMoney;
		pMsgSend.iTaxRateChaos = pCastleData.iTaxRateChaos;
		pMsgSend.iTaxRateStore = pCastleData.iTaxRateStore;
		pMsgSend.iTaxHuntZone = pCastleData.iTaxHuntZone;
		pMsgSend.iFirstCreate = pCastleData.iFirstCreate;

		memset(pMsgSend.szCastleOwnGuild, 0, MAX_GUILDNAMESTRING);
		memcpy(pMsgSend.szCastleOwnGuild, pCastleData.szCastleOwnGuild, MAX_GUILDNAMESTRING);

		wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_CASTLEDATA));
	}
}

void DS_GDReqOwnerGuildMaster(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_OWNERGUILDMASTER* lpMsg = (CSP_REQ_OWNERGUILDMASTER*)lpRecv;
	CSP_ANS_OWNERGUILDMASTER pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x01, sizeof(CSP_ANS_OWNERGUILDMASTER));

	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsgSend.iIndex = lpMsg->iIndex;

	int iRES = CastleDBSet.DSDB_QueryOwnerGuildMaster(lpMsg->wMapSvrNum, &pMsgSend);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
	}

	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_OWNERGUILDMASTER));
}

void DS_GDReqCastleNpcBuy(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_NPCBUY* lpMsg = (CSP_REQ_NPCBUY*)lpRecv;
	CSP_ANS_NPCBUY pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x03, sizeof(CSP_ANS_NPCBUY));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;

	pMsgSend.iIndex = lpMsg->iIndex;
	pMsgSend.iNpcNumber = lpMsg->iNpcNumber;
	pMsgSend.iNpcIndex = lpMsg->iNpcIndex;
	pMsgSend.iBuyCost = lpMsg->iBuyCost;

	int iQueryResult = 0;

	int iRES = CastleDBSet.DSDB_QueryCastleNpcBuy(lpMsg->wMapSvrNum, lpMsg, &iQueryResult);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
	}
	else
	{
		pMsgSend.iResult = iQueryResult;
	}

	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_NPCBUY));
}

void DS_GDReqCastleNpcRepair(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_NPCREPAIR* lpMsg = (CSP_REQ_NPCREPAIR*)lpRecv;
	CSP_ANS_NPCREPAIR pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x04, sizeof(CSP_ANS_NPCREPAIR));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsgSend.iIndex = lpMsg->iIndex;
	pMsgSend.iNpcNumber = lpMsg->iNpcNumber;
	pMsgSend.iNpcIndex = lpMsg->iNpcIndex;
	pMsgSend.iRepairCost = lpMsg->iRepairCost;

	int iQueryResult = 0;

	int iRES = CastleDBSet.DSDB_QueryCastleNpcRepair(lpMsg->wMapSvrNum, lpMsg, &pMsgSend, &iQueryResult);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
	}
	else
	{
		pMsgSend.iResult = iQueryResult;
	}

	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_NPCREPAIR));
}

void DS_GDReqCastleNpcUpgrade(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_NPCUPGRADE* lpMsg = (CSP_REQ_NPCUPGRADE*)lpRecv;
	CSP_ANS_NPCUPGRADE pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x05, sizeof(CSP_ANS_NPCUPGRADE));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsgSend.iIndex = lpMsg->iIndex;
	pMsgSend.iNpcNumber = lpMsg->iNpcNumber;
	pMsgSend.iNpcIndex = lpMsg->iNpcIndex;
	pMsgSend.iNpcUpType = lpMsg->iNpcUpType;
	pMsgSend.iNpcUpValue = lpMsg->iNpcUpValue;
	pMsgSend.iNpcUpIndex = lpMsg->iNpcUpIndex;

	int iRES = CastleDBSet.DSDB_QueryCastleNpcUpgrade(lpMsg->wMapSvrNum, lpMsg);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
	}
	else
	{
		pMsgSend.iResult = 1;
	}

	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_NPCUPGRADE));
}

void DS_GDReqTaxInfo(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}
	CSP_REQ_TAXINFO* lpMsg = (CSP_REQ_TAXINFO*)lpRecv;
	CSP_ANS_TAXINFO pMsgSend;
	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x06, sizeof(CSP_ANS_TAXINFO));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsgSend.iIndex = lpMsg->iIndex;

	int iRES = CastleDBSet.DSDB_QueryTaxInfo(lpMsg->wMapSvrNum, &pMsgSend);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
	}
	else
	{
		pMsgSend.iResult = 1;
	}

	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_TAXINFO));
}

void DS_GDReqTaxRateChange(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_TAXRATECHANGE* lpMsg = (CSP_REQ_TAXRATECHANGE*)lpRecv;
	CSP_ANS_TAXRATECHANGE pMsgSend;
	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x07, sizeof(CSP_ANS_TAXRATECHANGE));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsgSend.iIndex = lpMsg->iIndex;

	int iQueryResult = 0;

	int iRES = CastleDBSet.DSDB_QueryTaxRateChange(lpMsg->wMapSvrNum, lpMsg->iTaxKind, lpMsg->iTaxRate, &pMsgSend, &iQueryResult);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
	}
	else
	{
		pMsgSend.iResult = iQueryResult;
	}

	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_TAXRATECHANGE));
}

void DS_GDReqCastleMoneyChange(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_MONEYCHANGE* lpMsg = (CSP_REQ_MONEYCHANGE*)lpRecv;
	CSP_ANS_MONEYCHANGE pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x08, sizeof(CSP_ANS_MONEYCHANGE));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsgSend.iIndex = lpMsg->iIndex;
	pMsgSend.iMoneyChanged = lpMsg->iMoneyChanged;

	int iQueryResult = 0;
	__int64 i64MoneyResult = 0;

	int iRES = CastleDBSet.DSDB_QueryCastleMoneyChange(lpMsg->wMapSvrNum, lpMsg->iMoneyChanged, &i64MoneyResult, &iQueryResult);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
		wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_MONEYCHANGE));
	}
	else
	{
		pMsgSend.iResult = iQueryResult;
		pMsgSend.i64CastleMoney = i64MoneyResult;
		wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_MONEYCHANGE));
	}
}

void DS_GDReqSiegeDateChange(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}
	CSP_REQ_SDEDCHANGE* lpMsg = (CSP_REQ_SDEDCHANGE*)lpRecv;
	CSP_ANS_SDEDCHANGE pMsgSend;
	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x09, sizeof(CSP_ANS_SDEDCHANGE));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsgSend.iIndex = lpMsg->iIndex;

	int iQueryResult = 0;

	int iRES = CastleDBSet.DSDB_QuerySiegeDateChange(lpMsg->wMapSvrNum, lpMsg, &iQueryResult);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
		wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_SDEDCHANGE));
	}
	else
	{
		pMsgSend.iResult = iQueryResult;
		pMsgSend.wStartYear = lpMsg->wStartYear;
		pMsgSend.btStartMonth = lpMsg->btStartMonth;
		pMsgSend.btStartDay = lpMsg->btStartDay;
		pMsgSend.wEndYear = lpMsg->wEndYear;
		pMsgSend.btEndMonth = lpMsg->btEndMonth;
		pMsgSend.btEndDay = lpMsg->btEndDay;
		wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_SDEDCHANGE));
	}
}

void DS_GDReqGuildMarkRegInfo(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_GUILDREGINFO* lpMsg = (CSP_REQ_GUILDREGINFO*)lpRecv;

	int iQueryResult = 0;

	CSP_ANS_GUILDREGINFO pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0xA, sizeof(CSP_ANS_GUILDREGINFO));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsgSend.iIndex = lpMsg->iIndex;

	char szGuildName[MAX_GUILDNAMESTRING + 1] = { '\0' };
	memcpy(szGuildName, lpMsg->szGuildName, MAX_GUILDNAMESTRING);

	int iRES = CastleDBSet.DSDB_QueryGuildMarkRegInfo(lpMsg->wMapSvrNum, szGuildName, &pMsgSend, &iQueryResult);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
	}
	else
	{
		pMsgSend.iResult = iQueryResult;
	}

	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_GUILDREGINFO));
}

void DS_GDReqSiegeEndedChange(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_SIEGEENDCHANGE* lpMsg = (CSP_REQ_SIEGEENDCHANGE*)lpRecv;
	CSP_ANS_SIEGEENDCHANGE pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x0B, sizeof(CSP_ANS_SIEGEENDCHANGE));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;

	int iQueryResult = 0;

	int iRES = CastleDBSet.DSDB_QuerySiegeEndedChange(lpMsg->wMapSvrNum, lpMsg->bIsSiegeEnded, &iQueryResult);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
	}
	else
	{
		pMsgSend.iResult = iQueryResult;
	}

	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_SIEGEENDCHANGE));
}

void DS_GDReqCastleOwnerChange(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_CASTLEOWNERCHANGE* lpMsg = (CSP_REQ_CASTLEOWNERCHANGE*)lpRecv;
	CSP_ANS_CASTLEOWNERCHANGE pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x0C, sizeof(CSP_ANS_CASTLEOWNERCHANGE));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;

	int iQueryResult = 0;

	int iRES = CastleDBSet.DSDB_QueryCastleOwnerChange(lpMsg->wMapSvrNum, lpMsg, &pMsgSend, &iQueryResult);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
	}
	else
	{
		pMsgSend.iResult = iQueryResult;
	}

	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_CASTLEOWNERCHANGE));
}

void DS_GDReqRegAttackGuild(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_REGATTACKGUILD* lpMsg = (CSP_REQ_REGATTACKGUILD*)lpRecv;
	CSP_ANS_REGATTACKGUILD pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x0D, sizeof(CSP_ANS_REGATTACKGUILD));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsgSend.iIndex = lpMsg->iIndex;

	int iQueryResult = 0;

	int iRES = CastleDBSet.DSDB_QueryRegAttackGuild(lpMsg->wMapSvrNum, lpMsg, &pMsgSend, &iQueryResult);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
	}
	else
	{
		pMsgSend.iResult = iQueryResult;
	}

	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_REGATTACKGUILD));
}

void DS_GDReqRestartCastleState(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_CASTLESIEGEEND* lpMsg = (CSP_REQ_CASTLESIEGEEND*)lpRecv;
	CSP_ANS_CASTLESIEGEEND pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x0E, sizeof(CSP_ANS_CASTLESIEGEEND));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;

	int iQueryResult = 0;

	int iRES = CastleDBSet.DSDB_QueryRestartCastleState(lpMsg->wMapSvrNum, lpMsg, &iQueryResult);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
	}
	else
	{
		pMsgSend.iResult = iQueryResult;
	}

	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_CASTLESIEGEEND));
}

void DS_GDReqMapSvrMsgMultiCast(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_MAPSVRMULTICAST* lpMsg = (CSP_REQ_MAPSVRMULTICAST*)lpRecv;
	CSP_ANS_MAPSVRMULTICAST pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x0F, sizeof(CSP_ANS_MAPSVRMULTICAST));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;

	memcpy(pMsgSend.szMsgText, lpMsg->szMsgText, sizeof(lpMsg->szMsgText));

	for (int iIDX = 0; iIDX < MAX_SERVEROBJECT; iIDX++)
	{
		if (gSObj[iIDX].Connected != 0)
		{
			if (gSObj[iIDX].iMapSvrGroup == lpMsg->wMapSvrNum)
			{
				wsjServer.DataSend(iIDX, (char*)&pMsgSend, sizeof(CSP_ANS_MAPSVRMULTICAST));
			}
		}
	}
}

void DS_GDReqRegGuildMark(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_GUILDREGMARK* lpMsg = (CSP_REQ_GUILDREGMARK*)lpRecv;
	CSP_ANS_GUILDREGMARK pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x10, sizeof(CSP_ANS_GUILDREGMARK));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsgSend.iIndex = lpMsg->iIndex;
	pMsgSend.iItemPos = lpMsg->iItemPos;

	char szGuildName[MAX_GUILDNAMESTRING + 1] = { '\0' };
	memcpy(szGuildName, lpMsg->szGuildName, MAX_GUILDNAMESTRING);

	int iQueryResult = 0;

	int iRES = CastleDBSet.DSDB_QueryGuildMarkRegMark(lpMsg->wMapSvrNum, szGuildName, &pMsgSend, &iQueryResult);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
	}
	else
	{
		pMsgSend.iResult = iQueryResult;
	}

	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_GUILDREGMARK));
}

void DS_GDReqGuildMarkReset(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_GUILDRESETMARK* lpMsg = (CSP_REQ_GUILDRESETMARK*)lpRecv;
	CSP_ANS_GUILDRESETMARK pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x11, sizeof(CSP_ANS_GUILDRESETMARK));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;

	char szGuildName[MAX_GUILDNAMESTRING + 1] = { '\0' };
	memcpy(szGuildName, lpMsg->szGuildName, MAX_GUILDNAMESTRING);

	int iRES = CastleDBSet.DSDB_QueryGuildMarkReset(lpMsg->wMapSvrNum, szGuildName, &pMsgSend);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
	}

	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_GUILDRESETMARK));
}

void DS_GDReqGuildSetGiveUp(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_GUILDSETGIVEUP* lpMsg = (CSP_REQ_GUILDSETGIVEUP*)lpRecv;
	CSP_ANS_GUILDSETGIVEUP pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x12, sizeof(CSP_ANS_GUILDSETGIVEUP));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsgSend.iIndex = lpMsg->iIndex;

	char szGuildName[MAX_GUILDNAMESTRING + 1] = { '\0' };
	memcpy(szGuildName, lpMsg->szGuildName, MAX_GUILDNAMESTRING);

	int iRES = CastleDBSet.DSDB_QueryGuildSetGiveUp(lpMsg->wMapSvrNum, szGuildName, lpMsg->bIsGiveUp, &pMsgSend);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
	}

	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_GUILDSETGIVEUP));
}

void DS_GDReqCastleNpcRemove(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_NPCREMOVE* lpMsg = (CSP_REQ_NPCREMOVE*)lpRecv;
	CSP_ANS_NPCREMOVE pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x16, sizeof(CSP_ANS_NPCREMOVE));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsgSend.iNpcNumber = lpMsg->iNpcNumber;
	pMsgSend.iNpcIndex = lpMsg->iNpcIndex;

	int iQueryResult = 0;

	int iRES = CastleDBSet.DSDB_QueryCastleNpcRemove(lpMsg->wMapSvrNum, lpMsg, &iQueryResult);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
	}
	else
	{
		pMsgSend.iResult = iQueryResult;
	}

	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_NPCREMOVE));
}

void DS_GDReqCastleStateSync(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_CASTLESTATESYNC* lpMsg = (CSP_REQ_CASTLESTATESYNC*)lpRecv;
	CSP_ANS_CASTLESTATESYNC pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x17, sizeof(CSP_ANS_CASTLESTATESYNC));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;
	pMsgSend.iCastleState = lpMsg->iCastleState;
	pMsgSend.iTaxRateChaos = lpMsg->iTaxRateChaos;
	pMsgSend.iTaxRateStore = lpMsg->iTaxRateStore;
	pMsgSend.iTaxHuntZone = lpMsg->iTaxHuntZone;
	memcpy(pMsgSend.szOwnerGuildName, lpMsg->szOwnerGuildName, MAX_GUILDNAMESTRING);

	for (int iIDX = 0; iIDX < MAX_SERVEROBJECT; iIDX++)
	{
		if (gSObj[iIDX].Connected != 0)
		{
			if (gSObj[iIDX].iMapSvrGroup == lpMsg->wMapSvrNum)
			{
				wsjServer.DataSend(iIDX, (char*)&pMsgSend, sizeof(CSP_ANS_CASTLESTATESYNC));
			}
		}
	}
}

void DS_GDReqCastleTributeMoney(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_CASTLETRIBUTEMONEY* lpMsg = (CSP_REQ_CASTLETRIBUTEMONEY*)lpRecv;
	CSP_ANS_CASTLETRIBUTEMONEY pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x18, sizeof(CSP_ANS_CASTLETRIBUTEMONEY));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;

	int iQueryResult = 0;
	__int64 i64MoneyResult = 0;

	if (lpMsg->iCastleTributeMoney < 0)
	{
		pMsgSend.iResult = 0;
	}
	else
	{
		BOOL bResult = CastleDBSet.DSDB_QueryCastleMoneyChange(lpMsg->wMapSvrNum, lpMsg->iCastleTributeMoney, &i64MoneyResult, &iQueryResult);

		if (bResult != 0)
		{
			pMsgSend.iResult = 0;
			wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_CASTLESTATESYNC));//webzen's mistake
			return;
		}

		pMsgSend.iResult = iQueryResult;
	}

	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_CASTLETRIBUTEMONEY));
}

void DS_GDReqResetCastleTaxInfo(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_RESETCASTLETAXINFO* lpMsg = (CSP_REQ_RESETCASTLETAXINFO*)lpRecv;
	CSP_ANS_RESETCASTLETAXINFO pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x19, sizeof(CSP_ANS_RESETCASTLETAXINFO));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;

	int iQueryResult = 0;

	int iRES = CastleDBSet.DSDB_QueryResetCastleTaxInfo(lpMsg->wMapSvrNum, &iQueryResult);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
		wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_RESETCASTLETAXINFO));
	}
	else
	{
		pMsgSend.iResult = iQueryResult;
		wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_RESETCASTLETAXINFO));
	}
}

void DS_GDReqResetSiegeGuildInfo(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_RESETSIEGEGUILDINFO* lpMsg = (CSP_REQ_RESETSIEGEGUILDINFO*)lpRecv;
	CSP_ANS_RESETSIEGEGUILDINFO pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 0x1A, sizeof(CSP_ANS_RESETSIEGEGUILDINFO));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;

	int iQueryResult = 0;

	int iRES = CastleDBSet.DSDB_QueryResetSiegeGuildInfo(lpMsg->wMapSvrNum, &iQueryResult);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
		wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_RESETSIEGEGUILDINFO));
	}
	else
	{
		pMsgSend.iResult = iQueryResult;
		wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_RESETSIEGEGUILDINFO));
	}
}

void DS_GDReqResetRegSiegeInfo(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_RESETSIEGEGUILDINFO* lpMsg = (CSP_REQ_RESETSIEGEGUILDINFO*)lpRecv;
	CSP_ANS_RESETSIEGEGUILDINFO pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x80, 27, sizeof(CSP_ANS_RESETSIEGEGUILDINFO));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;

	int iQueryResult = 0;

	int iRES = CastleDBSet.DSDB_QueryResetRegSiegeInfo(lpMsg->wMapSvrNum, &iQueryResult);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
		wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_RESETSIEGEGUILDINFO));
	}
	else
	{
		pMsgSend.iResult = iQueryResult;
		wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_RESETSIEGEGUILDINFO));
	}
}

void DS_GDReqCastleInitData(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_CSINITDATA* lpMsg = (CSP_REQ_CSINITDATA*)lpRecv;
	CASTLE_DATA pCastleData;

	char cBUFFER[5920];

	CSP_ANS_CSINITDATA* lpMsgSend = (CSP_ANS_CSINITDATA*)cBUFFER;
	CSP_NPCDATA* lpMsgSendBody = (CSP_NPCDATA *)&cBUFFER[sizeof(CSP_ANS_CSINITDATA)];

	lpMsgSend->wMapSvrNum = lpMsg->wMapSvrNum;

	int iDataCount = 200;

	lpMsgSend->iCount = 0;

	int iRES = CastleDBSet.DSDB_QueryCastleTotalInfo(lpMsg->wMapSvrNum, lpMsg->iCastleEventCycle, &pCastleData);

	if (iRES != 0)
	{
		lpMsgSend->iResult = 0;
		lpMsgSend->h.set((LPBYTE)lpMsgSend, 0x81, (sizeof(CSP_NPCDATA) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSINITDATA));
		wsjServer.DataSend(aIndex, (char*)lpMsgSend, (sizeof(CSP_NPCDATA) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSINITDATA));
	}
	else
	{
		lpMsgSend->iResult = 0;
		lpMsgSend->wStartYear = pCastleData.wStartYear;
		lpMsgSend->btStartMonth = pCastleData.btStartMonth;
		lpMsgSend->btStartDay = pCastleData.btStartDay;
		lpMsgSend->wEndYear = pCastleData.wEndYear;
		lpMsgSend->btEndMonth = pCastleData.btEndMonth;
		lpMsgSend->btEndDay = pCastleData.btEndDay;
		lpMsgSend->btIsSiegeGuildList = pCastleData.btIsSiegeGuildList;
		lpMsgSend->btIsSiegeEnded = pCastleData.btIsSiegeEnded;
		lpMsgSend->btIsCastleOccupied = pCastleData.btIsCastleOccupied;
		lpMsgSend->i64CastleMoney = pCastleData.i64CastleMoney;
		lpMsgSend->iTaxRateChaos = pCastleData.iTaxRateChaos;
		lpMsgSend->iTaxRateStore = pCastleData.iTaxRateStore;
		lpMsgSend->iTaxHuntZone = pCastleData.iTaxHuntZone;
		lpMsgSend->iFirstCreate = pCastleData.iFirstCreate;

		memset(lpMsgSend->szCastleOwnGuild, 0, MAX_GUILDNAMESTRING);
		memcpy(lpMsgSend->szCastleOwnGuild, pCastleData.szCastleOwnGuild, MAX_GUILDNAMESTRING);

		iRES = CastleDBSet.DSDB_QueryCastleNpcInfo(lpMsg->wMapSvrNum, lpMsgSendBody, &iDataCount);

		if (iRES != 0)
		{
			lpMsgSend->iResult = 0;
			lpMsgSend->h.set((LPBYTE)lpMsgSend, 0x81, (sizeof(CSP_NPCDATA) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSINITDATA));
			wsjServer.DataSend(aIndex, (char*)lpMsgSend, (sizeof(CSP_NPCDATA) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSINITDATA));
		}
		else
		{
			lpMsgSend->iResult = 1;
			lpMsgSend->iCount = iDataCount;
			lpMsgSend->h.set((LPBYTE)lpMsgSend, 0x81, (sizeof(CSP_NPCDATA) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSINITDATA));
			wsjServer.DataSend(aIndex, (char*)lpMsgSend, (sizeof(CSP_NPCDATA) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSINITDATA));
		}
	}
}

void DS_GDReqCastleNpcInfo(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_NPCDATA* lpMsg = (CSP_REQ_NPCDATA*)lpRecv;

	char cBUFFER[5876];

	CSP_ANS_NPCDATA* lpMsgSend = (CSP_ANS_NPCDATA*)cBUFFER;
	CSP_NPCDATA* lpMsgSendBody = (CSP_NPCDATA *)&cBUFFER[20];

	lpMsgSend->wMapSvrNum = lpMsg->wMapSvrNum;

	int iDataCount = 200;

	lpMsgSend->iCount = 0;

	int iRES = CastleDBSet.DSDB_QueryCastleNpcInfo(lpMsg->wMapSvrNum, lpMsgSendBody, &iDataCount);

	if (iRES != 0)
	{
		lpMsgSend->iResult = 0;
		lpMsgSend->h.set((LPBYTE)lpMsgSend, 0x82, (sizeof(CSP_NPCDATA) * lpMsgSend->iCount) + sizeof(CSP_ANS_NPCDATA));
		wsjServer.DataSend(aIndex, (char*)lpMsgSend, (sizeof(CSP_NPCDATA) * lpMsgSend->iCount) + sizeof(CSP_ANS_NPCDATA));
	}
	else
	{
		lpMsgSend->iResult = 1;
		lpMsgSend->iCount = iDataCount;
		lpMsgSend->h.set((LPBYTE)lpMsgSend, 0x82, (sizeof(CSP_NPCDATA) * lpMsgSend->iCount) + sizeof(CSP_ANS_NPCDATA));
		wsjServer.DataSend(aIndex, (char*)lpMsgSend, (sizeof(CSP_NPCDATA) * lpMsgSend->iCount) + sizeof(CSP_ANS_NPCDATA));
	}
}

void DS_GDReqAllGuildMarkRegInfo(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_ALLGUILDREGINFO* lpMsg = (CSP_REQ_ALLGUILDREGINFO*)lpRecv;

	char cBUFFER[1876];

	CSP_ANS_ALLGUILDREGINFO* lpMsgSend = (CSP_ANS_ALLGUILDREGINFO*)cBUFFER;
	CSP_GUILDREGINFO* lpMsgSendBody = (CSP_GUILDREGINFO *)&cBUFFER[20];

	lpMsgSend->wMapSvrNum = lpMsg->wMapSvrNum;
	lpMsgSend->iIndex = lpMsg->iIndex;

	int iDataCount = 100;

	lpMsgSend->iCount = 0;

	int iRES = CastleDBSet.DSDB_QueryAllGuildMarkRegInfo(lpMsg->wMapSvrNum, lpMsgSendBody, &iDataCount);

	if (iRES != 0)
	{
		lpMsgSend->iResult = 0;
		lpMsgSend->h.set((LPBYTE)lpMsgSend, 0x83, (sizeof(CSP_GUILDREGINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_ALLGUILDREGINFO));
		wsjServer.DataSend(aIndex, (char*)lpMsgSend, (sizeof(CSP_GUILDREGINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_ALLGUILDREGINFO));
	}
	else
	{
		lpMsgSend->iResult = 1;
		lpMsgSend->iCount = iDataCount;
		lpMsgSend->h.set((LPBYTE)lpMsgSend, 0x83, (sizeof(CSP_GUILDREGINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_ALLGUILDREGINFO));
		wsjServer.DataSend(aIndex, (char*)lpMsgSend, (sizeof(CSP_GUILDREGINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_ALLGUILDREGINFO));
	}
}

void DS_GDReqFirstCreateNPC(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_NPCSAVEDATA* lpMsg = (CSP_REQ_NPCSAVEDATA*)lpRecv;
	CSP_NPCSAVEDATA* lpMsgBody = (CSP_NPCSAVEDATA*)&lpRecv[12];

	CSP_ANS_NPCSAVEDATA pMsgSend;
	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x84, sizeof(CSP_ANS_NPCSAVEDATA));
	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;

	int iRES = CastleDBSet.DSDB_QueryFirstCreateNPC(lpMsg->wMapSvrNum, lpMsg);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
		wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_NPCSAVEDATA));
	}
	else
	{
		pMsgSend.iResult = 1;
		wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_NPCSAVEDATA));
	}
}

void DS_GDReqCalcRegGuildList(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_CALCREGGUILDLIST* lpMsg = (CSP_REQ_CALCREGGUILDLIST*)lpRecv;

	char cBUFFER[2672];

	CSP_ANS_CALCREGGUILDLIST* lpMsgSend = (CSP_ANS_CALCREGGUILDLIST*)cBUFFER;
	CSP_CALCREGGUILDLIST* lpMsgSendBody = (CSP_CALCREGGUILDLIST *)&cBUFFER[16];

	lpMsgSend->wMapSvrNum = lpMsg->wMapSvrNum;

	int iDataCount = 100;

	lpMsgSend->iCount = 0;

	int iRES = CastleDBSet.DSDB_QueryCalcRegGuildList(lpMsg->wMapSvrNum, lpMsgSendBody, &iDataCount);

	if (iRES != 0)
	{
		lpMsgSend->iResult = 0;
		lpMsgSend->h.set((LPBYTE)lpMsgSend, 0x85, (sizeof(CSP_CALCREGGUILDLIST) * lpMsgSend->iCount) + sizeof(CSP_ANS_CALCREGGUILDLIST));
		wsjServer.DataSend(aIndex, (char*)lpMsgSend, (sizeof(CSP_CALCREGGUILDLIST) * lpMsgSend->iCount) + sizeof(CSP_ANS_CALCREGGUILDLIST));
	}
	else
	{
		lpMsgSend->iResult = 1;
		lpMsgSend->iCount = iDataCount;
		lpMsgSend->h.set((LPBYTE)lpMsgSend, 0x85, (sizeof(CSP_CALCREGGUILDLIST) * lpMsgSend->iCount) + sizeof(CSP_ANS_CALCREGGUILDLIST));
		wsjServer.DataSend(aIndex, (char*)lpMsgSend, (sizeof(CSP_CALCREGGUILDLIST) * lpMsgSend->iCount) + sizeof(CSP_ANS_CALCREGGUILDLIST));
	}
}

void DS_GDReqCsGuildUnionInfo(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_CSGUILDUNIONINFO* lpMsg = (CSP_REQ_CSGUILDUNIONINFO*)lpRecv;
	CSP_CSGUILDUNIONINFO* lpMsgBody = (CSP_CSGUILDUNIONINFO*)&lpRecv[12];

	char cBUFFER[1472];

	CSP_ANS_CSGUILDUNIONINFO* lpMsgSend = (CSP_ANS_CSGUILDUNIONINFO*)cBUFFER;
	CSP_CSGUILDUNIONINFO* lpMsgSendBody = (CSP_CSGUILDUNIONINFO *)&cBUFFER[16];

	lpMsgSend->wMapSvrNum = lpMsg->wMapSvrNum;

	if (lpMsg->iCount < 0)
	{
		lpMsg->iCount = 0;
	}

	int iRET_COUNT = 0;

	for (int iGCNT = 0; iGCNT < lpMsg->iCount; iGCNT++)
	{
		char szGuildName[MAX_GUILDNAMESTRING + 1] = { '\0' };
		memcpy(szGuildName, lpMsgBody[iGCNT].szGuildName, MAX_GUILDNAMESTRING);

		int iRES = CastleDBSet.DSDB_QueryCsGuildUnionInfo(lpMsg->wMapSvrNum, szGuildName, lpMsgBody[iGCNT].iCsGuildID, lpMsgSendBody, &iRET_COUNT);

		if (iRES != 0)
		{
			lpMsgSend->iResult = 0;
			lpMsgSend->iCount = 0;
			lpMsgSend->h.set((LPBYTE)lpMsgSend, 0x86, (sizeof(CSP_CSGUILDUNIONINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSGUILDUNIONINFO));
			wsjServer.DataSend(aIndex, (char*)lpMsgSend, (sizeof(CSP_CSGUILDUNIONINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSGUILDUNIONINFO));
			return;
		}
	}

	lpMsgSend->iResult = 1;
	lpMsgSend->iCount = iRET_COUNT;
	lpMsgSend->h.set((LPBYTE)lpMsgSend, 0x86, (sizeof(CSP_CSGUILDUNIONINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSGUILDUNIONINFO));
	wsjServer.DataSend(aIndex, (char*)lpMsgSend, (sizeof(CSP_CSGUILDUNIONINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSGUILDUNIONINFO));
}

void DS_GDReqCsSaveTotalGuildInfo(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_CSSAVETOTALGUILDINFO* lpMsg = (CSP_REQ_CSSAVETOTALGUILDINFO*)lpRecv;
	CSP_CSSAVETOTALGUILDINFO* lpMsgBody = (CSP_CSSAVETOTALGUILDINFO*)&lpRecv[12];

	CSP_ANS_CSSAVETOTALGUILDINFO pMsgSend;

	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;

	int iRES = CastleDBSet.DSDB_QueryCsClearTotalGuildInfo(lpMsg->wMapSvrNum);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
		pMsgSend.h.set((LPBYTE)&pMsgSend, 0x87, sizeof(CSP_ANS_CSSAVETOTALGUILDINFO));
		wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_CSSAVETOTALGUILDINFO));
	}
	else
	{
		for (int iGCNT = 0; iGCNT < lpMsg->iCount; iGCNT++)
		{
			char szGuildName[MAX_GUILDNAMESTRING + 1] = { '\0' };
			memcpy(szGuildName, lpMsgBody[iGCNT].szGuildName, MAX_GUILDNAMESTRING);

#ifdef ADD_CASTLE_TOTAL_GUILD_SCORE_20061123
			int iRES = CastleDBSet.DSDB_QueryCsSaveTotalGuildInfo(lpMsg->wMapSvrNum, szGuildName, lpMsgBody[iGCNT].iCsGuildID, lpMsgBody[iGCNT].iGuildInvolved, lpMsgBody[iGCNT].iGuildScore);
#else
			int iRES = CastleDBSet.DSDB_QueryCsSaveTotalGuildInfo(lpMsg->wMapSvrNum, szGuildName, lpMsgBody[iGCNT].iCsGuildID, lpMsgBody[iGCNT].iGuildInvolved);
#endif

			if (iRES != 0)
			{
				pMsgSend.iResult = 0;
				pMsgSend.h.set((LPBYTE)&pMsgSend, 0x87, sizeof(CSP_ANS_CSSAVETOTALGUILDINFO));
				wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_CSSAVETOTALGUILDINFO));
				return;
			}
		}

		int iQueryResult = 0;

		iRES = CastleDBSet.DSDB_QueryCsSaveTotalGuildOK(lpMsg->wMapSvrNum, &iQueryResult);

		if (iRES != 0)
		{
			pMsgSend.iResult = 0;
			pMsgSend.h.set((LPBYTE)&pMsgSend, 0x87, sizeof(CSP_ANS_CSSAVETOTALGUILDINFO));
			wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_CSSAVETOTALGUILDINFO));
		}
		else
		{
			pMsgSend.iResult = 1;
			pMsgSend.iResult = 1; //??
			pMsgSend.h.set((LPBYTE)&pMsgSend, 0x87, sizeof(CSP_ANS_CSSAVETOTALGUILDINFO));
			wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_CSSAVETOTALGUILDINFO));
		}
	}
}

void DS_GDReqCsLoadTotalGuildInfo(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_CSLOADTOTALGUILDINFO* lpMsg = (CSP_REQ_CSLOADTOTALGUILDINFO*)lpRecv;

	char cBUFFER[2272];

	CSP_ANS_CSLOADTOTALGUILDINFO* lpMsgSend = (CSP_ANS_CSLOADTOTALGUILDINFO*)cBUFFER;
	CSP_CSLOADTOTALGUILDINFO* lpMsgSendBody = (CSP_CSLOADTOTALGUILDINFO *)&cBUFFER[16];

	lpMsgSend->wMapSvrNum = lpMsg->wMapSvrNum;

	int iDataCount = 100;

	lpMsgSend->iCount = 0;

	int iRES = CastleDBSet.DSDB_QueryCsLoadTotalGuildInfo(lpMsg->wMapSvrNum, lpMsgSendBody, &iDataCount);

	if (iRES != 0)
	{
		lpMsgSend->iResult = 0;
		lpMsgSend->h.set((LPBYTE)lpMsgSend, 0x88, (sizeof(CSP_CSLOADTOTALGUILDINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSLOADTOTALGUILDINFO));
		wsjServer.DataSend(aIndex, (char*)lpMsgSend, (sizeof(CSP_CSLOADTOTALGUILDINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSLOADTOTALGUILDINFO));
	}
	else
	{
		lpMsgSend->iResult = 1;
		lpMsgSend->iCount = iDataCount;
		lpMsgSend->h.set((LPBYTE)lpMsgSend, 0x88, (sizeof(CSP_CSLOADTOTALGUILDINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSLOADTOTALGUILDINFO));
		wsjServer.DataSend(aIndex, (char*)lpMsgSend, (sizeof(CSP_CSLOADTOTALGUILDINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSLOADTOTALGUILDINFO));
	}
}

void DS_GDReqCastleNpcUpdate(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CSP_REQ_NPCUPDATEDATA* lpMsg = (CSP_REQ_NPCUPDATEDATA*)lpRecv;
	CSP_NPCUPDATEDATA* lpMsgBody = (CSP_NPCUPDATEDATA*)&lpRecv[12];

	CSP_ANS_NPCSAVEDATA pMsgSend;
	pMsgSend.h.set((LPBYTE)&pMsgSend, 0x89, sizeof(CSP_ANS_NPCSAVEDATA));

	pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;

	int iRES = CastleDBSet.DSDB_QueryCastleNpcUpdate(lpMsg->wMapSvrNum, lpMsg);

	if (iRES != 0)
	{
		pMsgSend.iResult = 0;
	}
	else
	{
		pMsgSend.iResult = 1;
	}

	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CSP_ANS_NPCSAVEDATA));
}
#endif

#ifdef MU_CRYWOLF_DS_PROTOCOL_20050505
void GDReqCrywolfSync(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CWP_REQ_CRYWOLFSYNC* lpMsg = (CWP_REQ_CRYWOLFSYNC*)lpRecv;
	CWP_ANS_CRYWOLFSYNC pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0xB0, sizeof(CWP_ANS_CRYWOLFSYNC));
	pMsgSend.iCrywolfState = lpMsg->iCrywolfState;
	pMsgSend.iOccupationState = lpMsg->iOccupationState;
	pMsgSend.btResult = 1;

	for (int iIDX = 0; iIDX < MAX_SERVEROBJECT; iIDX++)
	{
		if (gSObj[iIDX].Connected != 0)
		{
			if (gSObj[iIDX].iMapSvrGroup == lpMsg->wMapSvrNum)
			{
				wsjServer.DataSend(iIDX, (char*)&pMsgSend, sizeof(CWP_ANS_CRYWOLFSYNC));
			}
		}
	}
}

void GDReqCrywolfInfoLoad(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
	{
		return;
	}

	CWP_REQ_CRYWOLFINFOLOAD* lpMsg = (CWP_REQ_CRYWOLFINFOLOAD*)lpRecv;
	CWP_ANS_CRYWOLFINFOLOAD pMsgSend;

	pMsgSend.h.set((LPBYTE)&pMsgSend, 0xB1, sizeof(CWP_ANS_CRYWOLFINFOLOAD));
	pMsgSend.btResult = 0;

	int iResult = CrywolfDBSet.DSDB_QueryCrywolfInfoLoad(lpMsg->wMapSvrNum, &pMsgSend);

	if (iResult == 0)
	{
		pMsgSend.btResult = 1;
	}

	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CWP_ANS_CRYWOLFINFOLOAD));
}

void GDReqCrywolfInfoSave(BYTE *lpRecv, int aIndex)
{
	if (lpRecv == NULL)
		return;

	CWP_REQ_CRYWOLFINFOSAVE* lpMsg = (CWP_REQ_CRYWOLFINFOSAVE*)lpRecv;
	int iResult = CrywolfDBSet.DSDB_QueryCrywolfInfoSave(lpMsg->wMapSvrNum, lpMsg);


	CWP_ANS_CRYWOLFINFOSAVE pMsgSend;
	pMsgSend.h.set((LPBYTE)&pMsgSend, 0xB2, sizeof(CWP_ANS_CRYWOLFINFOSAVE));
	pMsgSend.btResult = 0;

	if (iResult == 0)
		pMsgSend.btResult = 1;

	wsjServer.DataSend(aIndex, (char*)&pMsgSend, sizeof(CWP_ANS_CRYWOLFINFOSAVE));
}
#endif

void GDReqPeriodItemExInsert(BYTE *lpRecv, int aIndex)
{
	LPPMSG_REQ_PERIODITEMEX_INSERT lpMsg = (LPPMSG_REQ_PERIODITEMEX_INSERT)lpRecv;

	PMSG_ANS_PERIODITEMEX_INSERT pMsg;
	pMsg.head.set((LPBYTE)&pMsg, 0xD1, 0x01, sizeof(PMSG_ANS_PERIODITEMEX_INSERT));
	pMsg.btResultCode = PeriodItemExDBSet.Insert(lpMsg->dwUserGuid, lpMsg->chCharacterName, lpMsg->btItemType, lpMsg->wItemCode, lpMsg->btOptionType, lpMsg->btEffectType1, lpMsg->btEffectType2, lpMsg->dwSerial, lpMsg->dwDuration, lpMsg->lBuyDate, lpMsg->lExpireDate);
	pMsg.dwUserGuid = lpMsg->dwUserGuid;
	pMsg.wUserIndex = lpMsg->wUserIndex;
	pMsg.btItemtype = lpMsg->btItemType;
	pMsg.wItemCode = lpMsg->wItemCode;
	pMsg.btOptionType = lpMsg->btOptionType;
	pMsg.btEffectType1 = lpMsg->btEffectType1;
	pMsg.btEffectType2 = lpMsg->btEffectType2;
	pMsg.dwSerial = lpMsg->dwSerial;
	pMsg.dwDuration = lpMsg->dwDuration;
	pMsg.lBuyDate = lpMsg->lBuyDate;
	pMsg.lExpireDate = lpMsg->lExpireDate;

	wsjServer.DataSend(aIndex, (char*)&pMsg, sizeof(PMSG_ANS_PERIODITEMEX_INSERT));
}

void GDReqPeriodItemExDelete(BYTE *lpRecv, int aIndex)
{
	LPPMSG_REQ_PERIODITEMEX_DELETE lpMsg = (LPPMSG_REQ_PERIODITEMEX_DELETE)lpRecv;

	PMSG_ANS_PERIODITEMEX_DELETE pMsg;
	pMsg.head.set((LPBYTE)&pMsg, 0xD1, 0x02, sizeof(PMSG_ANS_PERIODITEMEX_DELETE));

	pMsg.btResultCode = PeriodItemExDBSet.Delete(lpMsg->dwUserGuid, lpMsg->chCharacterName, lpMsg->wItemCode, lpMsg->btItemType, lpMsg->dwSerial);
	pMsg.dwUserGuid = lpMsg->dwUserGuid;
	pMsg.wUserIndex = lpMsg->wUserIndex;

	wsjServer.DataSend(aIndex, (char*)&pMsg, sizeof(PMSG_ANS_PERIODITEMEX_DELETE));
}

void GDReqPeriodItemExSelect(BYTE *lpRecv, int aIndex)
{
	LPPMSG_REQ_PERIODITEMEX_SELECT lpMsg = (LPPMSG_REQ_PERIODITEMEX_SELECT)lpRecv;

	PMSG_ANS_PERIODITEMEX_LIST_COUNT pListCount;
	PMSG_ANS_PERIODITEMEX_LIST pList;

	PMSG_ANS_PERIODITEMEX_EXPIRED_ITEMLIST pExpiredList = { 0 };
	PERIOD_EXPIRED_ITEMLIST ExpiredItemList;

	pList.head.set((LPBYTE)&pList, 0xD1, 0x05, sizeof(PMSG_ANS_PERIODITEMEX_LIST));
	pListCount.head.set((LPBYTE)&pListCount, 0xD1, 0x04, sizeof(PMSG_ANS_PERIODITEMEX_LIST_COUNT));
	pExpiredList.head.set((LPBYTE)&pExpiredList, 0xD1, 0x03, sizeof(PMSG_ANS_PERIODITEMEX_EXPIRED_ITEMLIST));

	int iReturnCode = 0;
	iReturnCode = PeriodItemExDBSet.SelectExpiredItemList(lpMsg->dwUserGuid, lpMsg->chCharacterName, &ExpiredItemList);

	if (iReturnCode < 0)
	{
		//do nothing :)
	}
	else
	{
		pExpiredList.wUserIndex = lpMsg->wUserIndex;
		pExpiredList.btExpiredItemCount = iReturnCode;

		for (int i = 0; i < pExpiredList.btExpiredItemCount; i++)
		{
			pExpiredList.wItemCode[i] = ExpiredItemList.ExpiredItem[i].wItemCode;
			pExpiredList.dwSerial[i] = ExpiredItemList.ExpiredItem[i].dwSerial;
		}

		wsjServer.DataSend(aIndex, (char*)&pExpiredList, pExpiredList.head.size);
	}

	PERIOD_ITEMLIST ItemData;
	ItemData.dwUserGuid = lpMsg->dwUserGuid;
	memcpy(ItemData.chCharacterName, lpMsg->chCharacterName, MAX_IDSTRING + 1);

	pListCount.btResult = PeriodItemExDBSet.Select(&ItemData);
	pListCount.btListCount = ItemData.btItemCount;
	pListCount.dwUserGuid = lpMsg->dwUserGuid;
	pListCount.wUserIndex = lpMsg->wUserIndex;

	for (int iItemCount = 0; iItemCount < pListCount.btListCount; iItemCount++)
	{
		pList.dwUserGuid = lpMsg->dwUserGuid;
		pList.wUserIndex = lpMsg->wUserIndex;
		pList.wItemCode = ItemData.ItemData[iItemCount].wItemCode;
		pList.btEffectCategory = ItemData.ItemData[iItemCount].btEffectCategory;
		pList.btEffectType1 = ItemData.ItemData[iItemCount].btEffectType1;
		pList.btEffectType2 = ItemData.ItemData[iItemCount].btEffectType2;
		pList.btItemType = ItemData.ItemData[iItemCount].btItemType;
		pList.btUsedInfo = ItemData.ItemData[iItemCount].btUsedInfo;
		pList.dwSerial = ItemData.ItemData[iItemCount].dwSerial;
		pList.lItemBuyDate = ItemData.ItemData[iItemCount].lItemBuyDate;
		pList.lItemExpireDate = ItemData.ItemData[iItemCount].lItemExpireDate;

		wsjServer.DataSend(aIndex, (char*)&pList, pList.head.size);
	}
	wsjServer.DataSend(aIndex, (char*)&pListCount, pListCount.head.size);
}


void GDReqUserID(BYTE *lpRecv, int aIndex)
{
	PMSG_REQ_USERID* lpMsg = (PMSG_REQ_USERID*)lpRecv;
	PMSG_ANS_USERID pMsg;

	char chBuffer[MAX_IDSTRING + 1];
	memset(chBuffer, 0, MAX_IDSTRING + 1);
	memcpy(chBuffer, lpMsg->chUserName, MAX_IDSTRING);
	chBuffer[MAX_IDSTRING] = '\0';

	pMsg.head.set((LPBYTE)&pMsg, 0xD3, 0x01, sizeof(PMSG_ANS_USERID));
	pMsg.dwKey = lpMsg->dwKey;
	pMsg.dwUserGUID = lpMsg->dwUserGUID;
	pMsg.btResult = gCharDbSet.GetCharacterID(lpMsg->chUserName, pMsg.chUserID);

	wsjServer.DataSend(aIndex, (char*)&pMsg, sizeof(PMSG_ANS_USERID));
}

void DGChangeName(LPSDHP_CHANGE_NAME lpMsg, int aIndex)
{
	int Result = 0;

	SDHP_CHANGE_NAME_RESULT pResult;

	char accountId[MAX_IDSTRING + 1];
	char OldName[MAX_IDSTRING + 1];
	char NewName[MAX_IDSTRING + 1];

	accountId[MAX_IDSTRING] = '\0';
	memcpy(accountId, lpMsg->AccountId, MAX_IDSTRING);

	OldName[MAX_IDSTRING] = '\0';
	NewName[MAX_IDSTRING] = '\0';

	memcpy(OldName, lpMsg->OldName, MAX_IDSTRING);
	memcpy(NewName, lpMsg->NewName, MAX_IDSTRING);

	if (SQLSyntexCheck(NewName) == FALSE)
		Result = 1;

	if (cBadStrChk.CmpString(NewName) == 1)
		Result = 1;

	if (gMuName.CmpString(NewName) == 1)
		Result = 1;

	if (Result == 0)
		Result = gCharDbSet.ChangeName(accountId, OldName, NewName);

	pResult.h.set((LPBYTE)&pResult, 0x16, sizeof(SDHP_CHANGE_NAME_RESULT));
	pResult.btResult = Result;
	pResult.aIndex = lpMsg->aIndex;

	memcpy(pResult.AccountId, lpMsg->AccountId, MAX_IDSTRING);
	memcpy(pResult.OldName, lpMsg->OldName, MAX_IDSTRING);
	memcpy(pResult.NewName, lpMsg->NewName, MAX_IDSTRING);

	wsjServer.DataSend(aIndex, (char*)&pResult, sizeof(PMSG_ANS_USERID));
}

#ifdef ADD_CHARCARD_SUMMONER_20080313
void GJPSetAccountInfo(LPSDHP_REQ_SETACCOUNTINFO lpMsg, int aIndex)
{
	SDHP_ANS_SETACCOUNTINFO Result;

	Result.Result = gACDbSet.SetSummonerCardInfo(lpMsg->AccountId);

	memset(Result.AccountId, 0, MAX_IDSTRING + 1);
	memcpy(Result.AccountId, lpMsg->AccountId, MAX_IDSTRING);

	Result.h.set((LPBYTE)&Result, 0xA2, sizeof(SDHP_ANS_SETACCOUNTINFO));
	Result.Number = lpMsg->Number;

	wsjServer.DataSend(aIndex, (char*)&Result, sizeof(SDHP_ANS_SETACCOUNTINFO));
}
#endif


void GDReqQuestExpInfoSave(_PMSG_QUESTEXP_INFO *lpMsg)
{
	g_QuestExpDBSet.DSDB_QueryQuestInfoSave(lpMsg);
}

void GDReqQuestExpInfoLoad(PMSG_REQ_QUESTEXP_INFO *lpMsg, int aIndex)
{
	_QUESTEXP_INFO QuestInfo[25];

	PMSG_ANS_QUESTEXP_INFO pMsg;

	BYTE sendbuf[2048] = { 0 };

	int lOfs = 0;
	lOfs = sizeof(PMSG_ANS_QUESTEXP_INFO);

	pMsg.iUserIndex = lpMsg->iUserIndex;

	bool iRet = 0;
	iRet = g_QuestExpDBSet.DSDB_QueryQuestInfoLoad(lpMsg->szCharName, QuestInfo, &pMsg);

	if (iRet != 0)
	{
		LogAddC(LOGC_RED, "[QuestExp Error - GDReqQuestExpInfoLoad] Ret:%d, CharName : %s, UserIndex : %d",
			iRet, lpMsg->szCharName, lpMsg->iUserIndex);
		return;
	}
	/*memcpy(&sendbuf[lOfs], QuestInfo, 29 * pMsg.btQuestCnt);
	lOfs += 29 * pMsg.btQuestCnt;
	PWMSG_HEAD::set(&pMsg.head, 246, lOfs);
	memcpy(sendbuf, &pMsg.head, 9u);
	CwsJoinServer::DataSend(aIndex, sendbuf, lOfs);*/

	memcpy(&sendbuf[lOfs], QuestInfo, sizeof(_QUESTEXP_INFO) * pMsg.btQuestCnt);
	pMsg.head.set((LPBYTE)&pMsg.head, 0xF6, lOfs);
	memcpy(sendbuf, &pMsg.head, lOfs);

	wsjServer.DataSend(aIndex, (char*)&sendbuf, lOfs);
}

void GDReqLuckyItemInsert(BYTE *lpRecv, int aIndex)
{
	LPPMSG_REQ_LUCKYITEM_INSERT lpMsg = (LPPMSG_REQ_LUCKYITEM_INSERT)lpRecv;
	g_LuckyItemDBSet.Insert(lpMsg->dwUserGuid, lpMsg->szCharName, lpMsg->LuckyItemDBInfo.wItemCode, lpMsg->LuckyItemDBInfo.dwSerial, lpMsg->LuckyItemDBInfo.wDurabilitySmall);
}

void GDReqLuckyItemInsert2nd(BYTE *lpRecv, int aIndex)
{
	LPPMSG_REQ_LUCKYITEM_INSERT_2ND lpMsg = (LPPMSG_REQ_LUCKYITEM_INSERT_2ND)lpRecv;

	int iItemCnt = lpMsg->btItemCnt;
	if (iItemCnt <= 0)
		return;

	for (int i = 0; i < iItemCnt; i++)
		g_LuckyItemDBSet.Insert(lpMsg->dwUserGuid, lpMsg->szCharName, lpMsg->LuckyItemDBInfo[i].wItemCode, lpMsg->LuckyItemDBInfo[i].dwSerial, lpMsg->LuckyItemDBInfo[i].wDurabilitySmall);
}

void GDReqLuckyItemDelete(BYTE *lpRecv, int aIndex)
{
	LPPMSG_REQ_LUCKYITEM_DELETE lpMsg = (LPPMSG_REQ_LUCKYITEM_DELETE)lpRecv;
	g_LuckyItemDBSet.Delete(lpMsg->szCharName, lpMsg->wItemCode, lpMsg->dwSerial);
}

void GDReqLuckyItemSelect(BYTE *lpRecv, int aIndex)
{
	char sendbuf[2048] = { 0 };
	int lOfs = 0;

	LPPMSG_REQ_LUCKYITEM_SELECT lpMsg = (LPPMSG_REQ_LUCKYITEM_SELECT)lpRecv;

	PMSG_LUCKYITME_DB_INFO LuckyItemInfo[45] = { 0 };

	int iResult = g_LuckyItemDBSet.SelectLuckyItemList(lpMsg->chCharacterName, LuckyItemInfo);
	if (iResult <= 0)
		return;

	lOfs = sizeof(PMSG_ANS_LUCKYITEM_SELECT);

	PMSG_ANS_LUCKYITEM_SELECT pMsg;
	pMsg.btItemCnt = iResult;
	pMsg.wUserIndex = lpMsg->wUserIndex;

	memcpy(&sendbuf[lOfs], LuckyItemInfo, pMsg.btItemCnt * sizeof(PMSG_REQ_LUCKYITEM_SELECT));
	lOfs += (pMsg.btItemCnt * sizeof(PMSG_REQ_LUCKYITEM_SELECT));

	pMsg.head.set((LPBYTE)&pMsg, 0xD4, lOfs);
	memcpy(sendbuf, &pMsg, sizeof(PMSG_ANS_LUCKYITEM_SELECT));
	wsjServer.DataSend(aIndex, (char*)&sendbuf, lOfs);
}

//void GDSetExGameServerCode(LPSDHP_REQ_SET_EXGAMESERVERCODE lpMsg, int aIndex)
//{
//	gACDbSet.SetCharacterExGameServerCode(lpMsg->szCharName, lpMsg->sExGameServerCode);
//}
void GDSetExtendedInvenCount(SDHP_REQ_SET_EXTENDEDINVEN_COUNT *lpMsg, int aIndex)
{
	SDHP_ANS_SET_EXTENDEDINVEN_COUNT pMsg; // [esp+D0h] [ebp-18h]

	//PBMSG_HEAD::set(&pMsg.h.c, 213, 20);
	pMsg.h.set((LPBYTE)&pMsg.h.c, 0xD5, 20);
	pMsg.Number = lpMsg->Number;
	pMsg.Result = 1;
	pMsg.ExtendedInvenCount = 0;
	pMsg.EventIndex = lpMsg->EventIndex;
	pMsg.ItemPos = lpMsg->ItemPos;
	pMsg.BuyAtInGameShop = lpMsg->BuyAtInGameShop;
	if (lpMsg->ItemPos <= 203 && lpMsg->ItemPos >= 0 || lpMsg->BuyAtInGameShop || lpMsg->IsReplace)
	{
		if (lpMsg->IsReplace == 1)
			pMsg.Result = gACDbSet.SetCharacterExtendedInvenCountReplace(lpMsg->szCharName,lpMsg->ExtendedInvenCount);
		else
			pMsg.Result = gACDbSet.SetCharacterExtendedInvenCountAdd(lpMsg->szCharName,lpMsg->ExtendedInvenCount);
		gACDbSet.GetCharacterExtendedInvenCount( lpMsg->szCharName, (char*)&pMsg.ExtendedInvenCount);
		wsjServer.DataSend(aIndex, (char*)&pMsg.h.c, 20);
	}
	else
	{
		pMsg.Result = 0;
		gACDbSet.GetCharacterExtendedInvenCount( lpMsg->szCharName, (char*)&pMsg.ExtendedInvenCount);
		wsjServer.DataSend(aIndex, (char*)&pMsg.h.c, 20);
	}
}
//void GDSetExtendedInvenCount(SDHP_REQ_SET_EXTENDEDINVEN_COUNT *lpMsg, int aIndex)
//{
//	SDHP_ANS_SET_EXTENDEDINVEN_COUNT pMsg;
//	pMsg.h.set((LPBYTE)&pMsg.h.c, 0xD5, sizeof(SDHP_ANS_SET_EXTENDEDINVEN_COUNT));
//
//	pMsg.Number = lpMsg->Number;
//	pMsg.Result = 0x01;
//	pMsg.ExtendedInvenCount = 0;
//	pMsg.EventIndex = lpMsg->EventIndex;
//	pMsg.ItemPos = lpMsg->ItemPos;
//	pMsg.BuyAtInGameShop = lpMsg->BuyAtInGameShop;
//
//	if (lpMsg->ItemPos <= 203 && lpMsg->ItemPos >= 0 || lpMsg->BuyAtInGameShop || lpMsg->IsReplace)
//	{
//		if (lpMsg->IsReplace == 1)
//			pMsg.Result = gACDbSet.SetCharacterExtendedInvenCountReplace(lpMsg->szCharName, lpMsg->ExtendedInvenCount);
//
//		else
//			pMsg.Result = gACDbSet.SetCharacterExtendedInvenCountAdd(lpMsg->szCharName, lpMsg->ExtendedInvenCount);
//
//		//gACDbSet.GetCharacterExtendedInvenCount(lpMsg->szCharName, pMsg.ExtendedInvenCount);
//		gACDbSet.GetCharacterExtendedInvenCount(lpMsg->szCharName, &pMsg.ExtendedInvenCount);
//		//wsjServer.DataSend(aIndex, &pMsg.h.c, 20);
//		wsjServer.DataSend(aIndex, (char*)&pMsg.h.c, sizeof(SDHP_ANS_SET_EXTENDEDINVEN_COUNT));
//	}
//	else
//	{
//		pMsg.Result = 0;
//		gACDbSet.GetCharacterExtendedInvenCount(lpMsg->szCharName, &pMsg.ExtendedInvenCount);
//		//wsjServer.DataSend(aIndex, &pMsg.h.c, 20);
//		wsjServer.DataSend(aIndex, (char*)&pMsg.h.c, sizeof(SDHP_ANS_SET_EXTENDEDINVEN_COUNT));
//	}
//	//if (lpMsg->ItemPos <= 203 && lpMsg->ItemPos >= 0 || lpMsg->BuyAtInGameShop || lpMsg->IsReplace)
//	//{
//	//	pMsg.Result = 0;
//	//	gACDbSet.GetCharacterExtendedInvenCount(lpMsg->szCharName, pMsg.ExtendedInvenCount);
//	//	wsjServer.DataSend(aIndex, (char*)&pMsg, sizeof(SDHP_ANS_SET_EXTENDEDINVEN_COUNT));
//	//	return;
//	//}
//
//	//if(lpMsg->IsReplace == 0x01)
//	//	pMsg.Result = gACDbSet.SetCharacterExtendedInvenCountReplace(lpMsg->szCharName, lpMsg->ExtendedInvenCount);
//	//else pMsg.Result = gACDbSet.SetCharacterExtendedInvenCountAdd(lpMsg->szCharName, lpMsg->ExtendedInvenCount);
//
//	//gACDbSet.GetCharacterExtendedInvenCount(lpMsg->szCharName, &pMsg.ExtendedInvenCount);
//	//wsjServer.DataSend(aIndex, (char*)&pMsg, sizeof(SDHP_ANS_SET_EXTENDEDINVEN_COUNT));
//}

void GDSetExtendedWarehouseCount(SDHP_REQ_SET_EXTENDEDWAREHOUSE_COUNT *lpMsg, int aIndex)
{
	SDHP_ANS_SET_EXTENDEDWAREHOUSE_COUNT pMsg; // [esp+D0h] [ebp-18h]

	//PBMSG_HEAD::set(&pMsg.h.c, 214, 20);
	pMsg.h.set((LPBYTE)&pMsg.h.c, 0xD6, 20);
	pMsg.Number = lpMsg->Number;
	pMsg.Result = 1;
	pMsg.ExtendedWarehouseCount = 0;
	pMsg.EventIndex = lpMsg->EventIndex;
	pMsg.ItemPos = lpMsg->ItemPos;
	pMsg.BuyAtInGameShop = lpMsg->BuyAtInGameShop;
	if (lpMsg->ItemPos <= 203 && lpMsg->ItemPos >= 0 || lpMsg->BuyAtInGameShop || lpMsg->IsReplace)
	{
		if (lpMsg->IsReplace == 1)
			pMsg.Result = gACDbSet.SetCharacterExtendedWarehouseCountReplace(lpMsg->AccountId,lpMsg->ExtendedWarehouseCount);
		else
			pMsg.Result = gACDbSet.SetCharacterExtendedWarehouseCountAdd(lpMsg->AccountId,lpMsg->ExtendedWarehouseCount);
		gACDbSet.GetCharacterExtendedWarehouseCount( lpMsg->AccountId, &pMsg.ExtendedWarehouseCount);
		wsjServer.DataSend(aIndex, (char*)&pMsg.h.c, 20);
	}
	else
	{
		pMsg.Result = 0;
		gACDbSet.GetCharacterExtendedWarehouseCount( lpMsg->AccountId, &pMsg.ExtendedWarehouseCount);
		wsjServer.DataSend(aIndex, (char*)&pMsg.h.c, 20);
		LogAddTD("Extend Warehouse fail %d %d", lpMsg->ItemPos, pMsg.ExtendedWarehouseCount);
	}
}
//void GDSetExtendedWarehouseCount(LPSDHP_REQ_SET_EXTENDEDWAREHOUSE_COUNT lpMsg, int aIndex)
//{
//	SDHP_ANS_SET_EXTENDEDWAREHOUSE_COUNT pMsg;
//	pMsg.h.set((LPBYTE)&pMsg.h.c, 0xD6, sizeof(SDHP_ANS_SET_EXTENDEDWAREHOUSE_COUNT));
//
//	pMsg.Number = lpMsg->Number;
//	pMsg.Result = 0x01;
//	pMsg.ExtendedWarehouseCount = 0x00;
//	pMsg.EventIndex = lpMsg->EventIndex;
//	pMsg.ItemPos = lpMsg->ItemPos;
//	pMsg.BuyAtInGameShop = lpMsg->BuyAtInGameShop;
//	//pMsg.IsReplace = lpMsg->IsReplace;
//
//	if ((lpMsg->ItemPos > 203 || lpMsg->ItemPos < 0) && lpMsg->BuyAtInGameShop == 0 && lpMsg->IsReplace == 0)
//	{
//		pMsg.Result = 0;
//		gACDbSet.GetCharacterExtendedWarehouseCount(lpMsg->AccountId, &pMsg.ExtendedWarehouseCount);
//		wsjServer.DataSend(aIndex, (char*)&pMsg.h.c, sizeof(SDHP_ANS_SET_EXTENDEDWAREHOUSE_COUNT));
//		LogAddTD("Extend Warehouse fail %d %d", lpMsg->ItemPos, pMsg.ExtendedWarehouseCount);
//		return;
//	}
//
//	if (lpMsg->IsReplace == 0x01)
//		pMsg.Result = gACDbSet.SetCharacterExtendedWarehouseCountReplace(lpMsg->AccountId, lpMsg->ExtendedWarehouseCount);
//	else
//		pMsg.Result = gACDbSet.SetCharacterExtendedWarehouseCountAdd(lpMsg->AccountId, lpMsg->ExtendedWarehouseCount);
//
//	gACDbSet.GetCharacterExtendedWarehouseCount(lpMsg->AccountId, &pMsg.ExtendedWarehouseCount);
//	wsjServer.DataSend(aIndex, (char*)&pMsg.h.c, sizeof(SDHP_ANS_SET_EXTENDEDWAREHOUSE_COUNT));
//}
void GDMacroLoad(SDHP_MACRODATA *lpMsg, int aIndex)
{
	SDHP_MACRODATA pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0x17, sizeof(SDHP_MACRODATA));
	pMsg.btResult = gCharDbSet.LoadSnsInfo(lpMsg->AccountID, lpMsg->Name, pMsg.btMacroData) == 0;
	memcpy(pMsg.AccountID, lpMsg->AccountID, 0xBu);
	memcpy(pMsg.Name, lpMsg->Name, 0xBu);
	pMsg.aIndex = lpMsg->aIndex;
	wsjServer.DataSend(aIndex, (char*)&pMsg, sizeof(SDHP_MACRODATA));
}
//void GDMacroLoad(LPSDHP_MACRODATA lpMsg, int aIndex)
//{
//	SDHP_MACRODATA pMsg;
//	pMsg.h.set((LPBYTE)&pMsg, 0x17, sizeof(SDHP_MACRODATA));
//
//	BOOL bFlag = gCharDbSet.LoadMacroInfo(lpMsg->AccountID, lpMsg->Name, pMsg.btMacroData);
//
//	if (bFlag)
//		pMsg.btResult = 0x00;
//	else pMsg.btResult = 0x01;
//
//	memcpy(pMsg.AccountID, lpMsg->AccountID, MAX_IDSTRING + 1);
//	memcpy(pMsg.Name, lpMsg->Name, MAX_IDSTRING + 1);
//	pMsg.aIndex = lpMsg->aIndex;
//
//	wsjServer.DataSend(aIndex, (char*)&pMsg, sizeof(SDHP_MACRODATA));
//}

void GDMacroSave(LPSDHP_MACRODATA lpMsg, int aIndex)
{
	//gCharDbSet.SaveMacroInfo(lpMsg->AccountID, lpMsg->Name, lpMsg->btMacroData);
	gCharDbSet.SaveMacroInfo( lpMsg->AccountID, lpMsg->Name, lpMsg->btMacroData);

}

//season 12+


void GD_RuudTokenUpdate(SDHP_RUUDTOKENUPDATE *lpRecv)
{
	if (lpRecv)
	{
		LogAddTD("[GD_RuudTokenUpdate]%s,%s,%d", lpRecv->AccountID, lpRecv->CharName, lpRecv->dwRuud);
		gCharDbSet.RuudToken_Update(lpRecv->AccountID, lpRecv->CharName, lpRecv->dwRuud);
	}
}

void GDSnsLoad(SDHP_SNSDATA *lpMsg, int aIndex)
{
	SDHP_SNSDATA pMsg; // [esp+DCh] [ebp-128h]

	//pMsg.head.set(&pMsg.h, 0x21, 0x120);
	pMsg.h.set((LPBYTE)&pMsg, 0x21, sizeof(pMsg));
	pMsg.btResult = gCharDbSet.LoadSnsInfo(lpMsg->AccountID, lpMsg->Name, pMsg.btSnsData);
	memcpy(pMsg.AccountID, lpMsg->AccountID, 0xBu);
	memcpy(pMsg.Name, lpMsg->Name, 0xBu);
	pMsg.aIndex = lpMsg->aIndex;
	//wsjServer.DataSend(aIndex, &pMsg.h, sizeof(SDHP_SNSDATA));
	wsjServer.DataSend(aIndex, (char*)&pMsg, sizeof(pMsg));
}

void GDSnsSave(SDHP_SNSDATA *lpMsg)
{
	gCharDbSet.SaveSnsInfo(lpMsg->AccountID, lpMsg->Name, lpMsg->btSnsData);
}

void GDUserSettingSave(SDHP_USERSETTING_SAVEDATA *lpMsg)
{
	gCharDbSet.SaveUserSetting(lpMsg->AccountID, lpMsg->btSaveData);
}

//----- (00457610) --------------------------------------------------------

void GDUserSettingLoad(SDHP_USERSETTING_SAVEDATA *lpMsg, int aIndex)
{
	SDHP_USERSETTING_SAVEDATA pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0x23, sizeof(SDHP_USERSETTING_SAVEDATA));
	pMsg.btResult = gCharDbSet.LoadUserSetting(lpMsg->AccountID, pMsg.btSaveData);
	memcpy(pMsg.AccountID, lpMsg->AccountID, 0xBu);
	pMsg.aIndex = lpMsg->aIndex;
	wsjServer.DataSend(aIndex, (char*)&pMsg, sizeof(SDHP_USERSETTING_SAVEDATA));
}

void GDReqLoadMonsterKillInfo(_tagSDHP_REQ_EVENT_MONSTER_KILL_INFO *lpRecv, int aIndex)
{
	_tagSDHP_ANS_EVENT_MONSTER_KILL_INFO pMsg;
	//LPSDHP_SHELL_EXEC lpMsg = (LPSDHP_SHELL_EXEC)pMsg;
	//_tagSDHP_ANS_EVENT_MONSTER_KILL_INFO lpMsg = (_tagSDHP_ANS_EVENT_MONSTER_KILL_INFO)pMsg;
	if (lpRecv)
	{
		g_MonsterKillInfoDbSet.DSDB_SelectMonsterKillInfo(lpRecv->AccountID, lpRecv->CharName, &pMsg);
		//PHeadSubSetB(&pMsg.h, 0x3E, 1, 0x40);
		PHeadSubSetB((LPBYTE)&pMsg, 0x3E, 0x40, sizeof(pMsg));
		pMsg.iUserIndex = lpRecv->iUserIndex;
		wsjServer.DataSend(aIndex, (char *)&pMsg.h, pMsg.h.size);
	}
	else
	{
		LogAddTD("Error - [EventMonster][GDReqLoadMonsterKillInfo] lpRecv is NULL");
	}
}

void GDReqAddBlockChattingUser(SDHP_REQ_ADD_BLOCK_CHAT_USER_INFO *lpRecv)
{
	if (lpRecv)
		g_BlockChatUserDBSet.DSDB_AddBlockChatUser(lpRecv);
	else
		LogAddTD("Error - [BlockCharUser][GDReqAddBlockChattingUser] lpRecv is NULL");
}

void GDReqDelBlockChattingUser(SDHP_REQ_DEL_BLOCK_CHAT_USER_INFO *lpRecv)
{
	if (lpRecv)
		g_BlockChatUserDBSet.DSDB_DelBlockChatUser(lpRecv);
	else
		LogAddTD("Error - [BlockCharUser][GDReqDelBlockChattingUser] lpRecv is NULL");
}


void GDReqLoadBlockChattingUser(SDHP_REQ_BLOCK_CHAT_USER_INFO *lpRecv, int aIndex)
{
	int Result; // [esp+D0h] [ebp-130h]
	SDHP_ANS_BLOCK_CHAT_USER_INFO pMsg; // [esp+DCh] [ebp-124h]

//	SDHP_ANS_BLOCK_CHAT_USER_INFO pMsg = (SDHP_ANS_BLOCK_CHAT_USER_INFO)pMsg;
	if (lpRecv)
	{
		Result = g_BlockChatUserDBSet.DSDB_SelectBlockChatUser(lpRecv->szCharName, &pMsg);
		PHeadSubSetW(&pMsg.h.c, 0x6E, 0, sizeof(pMsg));
		pMsg.nUserIndex = lpRecv->iUserIndex;
		if (!Result)
			pMsg.btUserCnt = 0;
		wsjServer.DataSend(aIndex, (char *)&pMsg.h.c, sizeof(pMsg));
	}
	else
	{
		LogAddTD("Error - [BlockCharUser][GDReqLoadBlockChattingUser] lpRecv is NULL");
	}
}


void GDReqSaveRestoreItemList(_SDHP_REQ_RESTORE_ITEM_LIST_SAVE *lpRecv)
{
	if (lpRecv)
		g_CRestoreItemDBSet.DSDB_UpdateRestoreItem(
			lpRecv->AccountID,
			lpRecv->Name,
			lpRecv->dbRestoreItemData);
	else
		LogAddTD("Error - [RestoreItem][GDReqSaveRestoreItemList] lpRecv is NULL");
}


void GDReqLoadRestoreItemList(_SDHP_REQ_RESTORE_ITEM_LIST *lpRecv, int aIndex)
{
	_SDHP_ANS_RESTORE_ITEM_LIST pMsg;

	if (lpRecv)
	{
		PHeadSubSetW(&pMsg.h.c, 0x6F, 0, sizeof(_SDHP_ANS_RESTORE_ITEM_LIST));
		pMsg.userIndex = lpRecv->userIndex;
		g_CRestoreItemDBSet.DSDB_SelectRestoreItem(lpRecv->AccountID, lpRecv->Name, lpRecv->userIndex, &pMsg);
		wsjServer.DataSend(aIndex, (char *)&pMsg.h.c, sizeof(_SDHP_ANS_RESTORE_ITEM_LIST));
		//wsjServer.DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
	}
	else
	{
		LogAddTD("Error - [RestoreItem][GDReqLoadRestoreItemList] lpRecv is NULL");
	}
}


void GDReqLabyrinthInfo(SDHP_REQ_LABYRINTH_INFO *lpRecv, int aIndex)
{
	int nBufferLen;
	char Buffer;
	char dst; 

	if (lpRecv)
	{
		Buffer = 0;
		memset(&dst, 0, 0x1B57u);
		nBufferLen = 0;
		int Ret = g_LabyrinthDBSet.LoadLabyrinthInfo(
			lpRecv->szAccountID,
			lpRecv->szName,
			lpRecv->nUserIndex,
			&Buffer,
			&nBufferLen);
		LogAddTD("[GDReqLabyrinthInfo] (Ret: %d)(Send size: %d)", Ret, nBufferLen);
		wsjServer.DataSend(aIndex, &Buffer, nBufferLen);
	}
	else
	{
		LogAddTD("Error - [GDReqLabyrinthInfo] lpRecv is NULL");
	}
}

void GDReqLabyrinthInfoSave(BYTE *lpRecv)
{
	if (lpRecv)
		g_LabyrinthDBSet.SaveLabyrinthInfo(lpRecv);
	else
		LogAddTD("Error - [GDReqLabyrinthInfoSave] lpRecv is NULL");
}

void GDReqLabyrinthInfoUpdate(SDHP_REQ_LABYRINTH_INFO_UPDATE *lpRecv)
{
	if (lpRecv)
		g_LabyrinthDBSet.UpdateLabyrinthInfo(lpRecv);
	else
		LogAddTD("Error - [GDReqLabyrinthInfoUpdate] lpRecv is NULL");
}

void GDReqLabyrinthMissionUpdate(SDHP_REQ_LABYRINTH_MISSION_UPDATE *lpRecv)
{
	if (lpRecv)
		g_LabyrinthDBSet.UpdateLabyrinthMission(lpRecv);
	else
		LogAddTD("Error - [GDReqLabyrinthMissionUpdate] lpRecv is NULL");
}


//----- (00461250) --------------------------------------------------------
void GDReqLabyrinthMissionDelete(SDHP_REQ_LABYRINTH_MISSION_DELETE *lpRecv)
{
	if (lpRecv)
		g_LabyrinthDBSet.DeleteLabyrinthMission(lpRecv->szAccountID, lpRecv->szName);
	else
		LogAddTD("Error - [GDReqLabyrinthMissionDelete] lpRecv is NULL");
}


//----- (004612C0) --------------------------------------------------------
void GDReqLabyrinthEndUpdate(SDHP_REQ_LABYRINTH_END_UPDATE *lpRecv)
{
	if (lpRecv)
		g_LabyrinthDBSet.EndUpdateLabyrinthInfo(lpRecv->szAccountID, lpRecv->szName, lpRecv->nClearCnt, lpRecv->btClearState);
	else
		LogAddTD("Error - [GDReqLabyrinthEndUpdate] lpRecv is NULL");
}

//----- (00461340) --------------------------------------------------------
void GDReqLabyrinthRewardComplete(SDHP_REQ_LABYRINTH_REWARD_COMPLETE *lpRecv)
{
	if (lpRecv)
		g_LabyrinthDBSet.UpdateLabyrinthRewardState(lpRecv->szAccountID, lpRecv->szName, lpRecv->btIsMainMission, lpRecv->btRewardCheckState);
	else
		LogAddTD("Error - [GDReqLabyrinthRewardComplete] lpRecv is NULL");
}


//----- (004613C0) --------------------------------------------------------
void GDReqLabyrinthSaveClearLog(SDHP_REQ_LABYRINTH_CLEAR_LOG_SET_SAVE *lpRecv)
{
	if (lpRecv)
		g_LabyrinthDBSet.SaveLabyrinthClearLog(lpRecv->szAccountID, lpRecv->szName, lpRecv->nDimensionLevel);
	else
		LogAddTD("Error - [GDReqLabyrinthSaveClearLog] lpRecv is NULL");
}

void GDReqGetPCBangPlayTime(SDHP_REQ_GET_PCBANG_PLAYTIME_INFO *lpRecv, int aIndex)
{
	int bResult;
	unsigned int dwPCBangPlayTime;
	char btRecvGrade;
	char btCompleteGrade;
	SDHP_ANS_GET_PCBANG_PLAYTIME_INFO pMsg;

	if (lpRecv)
	{

		//PBMSG_HEAD2::set(&pMsg.h, (char *)&pMsg.h, 0x79, 1, 0x1C);
		pMsg.h.set((LPBYTE)&pMsg, 0x79, 0x01, sizeof(pMsg));
		btCompleteGrade = 0;
		btRecvGrade = 0;
		dwPCBangPlayTime = 0;
		bResult = g_PCBangRenewalDBSet.DSDB_GetPCBangPlayTimeInfo(
			lpRecv->AccountID,
			&btCompleteGrade,
			&btRecvGrade,
			&dwPCBangPlayTime);
		if (bResult)
		{
			pMsg.userIndex = lpRecv->userIndex;
			memcpy(pMsg.AccountID, lpRecv->AccountID, 0xBu);
			pMsg.btCompleteGrade = btCompleteGrade;
			pMsg.btRecvGrade = btRecvGrade;
			pMsg.dwPCBangPlayTime = dwPCBangPlayTime;
			wsjServer.DataSend(aIndex, (char *)&pMsg.h, sizeof(pMsg));
		}
		else
		{
			LogAddTD("Error - [GDReqGetPCBangPlayTime] DSDB_GetPCBangPlayTimeInfo");
		}
	}
	else
	{
		LogAddTD("Error - [PCBangBenefit][GDReqGetPCBangPlayTime] lpRecv is NULL");
	}
}

void GDReqSetPCBangPlayTime(SDHP_REQ_SET_PCBANG_PLAYTIME_INFO *lpRecv)
{
	int bResult;

	if (lpRecv)
	{
		bResult = g_PCBangRenewalDBSet.DSDB_SetPCBangPlayTimeInfo(
			lpRecv->AccountID,
			lpRecv->btCompleteGrade,
			lpRecv->btRecvGrade,
			lpRecv->dwPCBangPlayTime);
		if (!bResult)
			LogAddTD("Error - [GDReqSetPCBangPlayTime] DSDB_SetPCBangPlayTimeInfo");
	}
	else
	{
		LogAddTD("Error - [GDReqSetPCBangPlayTime] lpRecv is NULL");
	}
}

void GDReqLoadPlayTimeEventInfo(SDHP_REQ_LOAD_PLAYTIME_EVENT_INFO *lpRecv, int aIndex)
{
	int bResult;
	unsigned int dwPlayTime;
	char btGrade;
	SDHP_RES_LOAD_PLAYTIME_EVENT_INFO pMsg;

	if (lpRecv)
	{
		//PBMSG_HEAD2::set(&pMsg.h, (char *)&pMsg.h, 0x79, 3, 0x1C);
		pMsg.h.set((LPBYTE)&pMsg, 0x79, 0x01, sizeof(SDHP_RES_LOAD_PLAYTIME_EVENT_INFO));
		btGrade = 0;
		dwPlayTime = 0;
		bResult = g_PlayTimeEventDBSet.getPlayTimeEventInfo(lpRecv->AccountID, &btGrade, &dwPlayTime);
		if (bResult)
		{
			pMsg.userIndex = lpRecv->userIndex;
			memcpy(pMsg.AccountID, lpRecv->AccountID, 0xBu);
			pMsg.btGrade = btGrade;
			pMsg.dwPlayTime = dwPlayTime;
			wsjServer.DataSend(aIndex, (char *)&pMsg.h, 0x1C);
		}
		else
		{
			LogAddTD("Error - [GDReqLoadPlayTimeEventInfo] getPlayTimeEventInfo ");
		}
	}
	else
	{
		LogAddTD("Error - [PlayTimeEvent][GDReqLoadPlayTimeEventInfo] lpRecv is NULL");
	}
}

void GDReqSavePlayTimeEventInfo(SDHP_REQ_SAVE_PLAYTIME_EVENT_INFO *lpRecv)
{
	int bResult; // [esp+D0h] [ebp-8h]

	if (lpRecv)
	{
		bResult = g_PlayTimeEventDBSet.setPlayTimeEventInfo(
			lpRecv->AccountID,
			lpRecv->btGrade,
			lpRecv->dwPlayTime);
		if (!bResult)
			LogAddTD("Error - [GDReqSavePlayTimeEventInfo] setPlayTimeEventInfo");
	}
	else
	{
		LogAddTD("Error - [GDReqSavePlayTimeEventInfo] lpRecv is NULL");
	}
}

void GDReqSaveMonsterKillInfo(_tagSDHP_REQ_EVENT_MONSTER_KILL_INFO_SAVE *lpRecv, int aIndex)
{
	SDHP_ANS_EVENT_MONSTER_KILL_INFO_SAVE pMsg; // [esp+D0h] [ebp-10h]

	if (lpRecv)
	{
		g_MonsterKillInfoDbSet.DSDB_UpdateMonsterKillInfo(lpRecv);
		memset((char *)&pMsg.h, 0, 0xC);
		//PHeadSubSetB((char *)&pMsg.h, 0x3E, 2, 0xC);
		PHeadSubSetB((LPBYTE)&pMsg.h, 0x3E, 2, sizeof(pMsg));
		pMsg.iUserIndex = lpRecv->iUserIndex;
		pMsg.btResult = 0;
		wsjServer.DataSend(aIndex, (char *)&pMsg.h, pMsg.h.size);
	}
	else
	{
		LogAddTD("Error - [EventMonster][GDReqSaveMonsterKillInfo] lpRecv is NULL");
	}
}

void GDReqLoadMineSystemUPTInfo(SDHP_REQ_LOAD_MINESYSTEM_UPT_USERINFO *lpMsg, int aIndex)
{
	SDHP_ANS_LOAD_MINESYSTEM_UPT_USERINFO pMsgSend; // [esp+DCh] [ebp-20h]

	memset((char *)&pMsgSend.h, 0, 0x18u);
	g_MineSystemDBSet.DSDB_QuerySelectUPTUserInfo(lpMsg->szCharName, &pMsgSend);
	//PHeadSubSetB((char *)&pMsgSend.h, 0x4C, 1, 0x18);
	PHeadSubSetB((LPBYTE)&pMsgSend.h, 0x4C, 1, sizeof(pMsgSend));
	pMsgSend.wUserIndex = lpMsg->wUserIndex;
	wsjServer.DataSend(aIndex, (char *)&pMsgSend.h, (unsigned __int8)pMsgSend.h.size);
}

void GDReqModifyMineSystemUPTInfo(SDHP_REQ_MINESYSTEM_UPT_USERINFO *lpMsg, int aIndex)
{
	char bResult; // [esp+D0h] [ebp-18h]
	SDHP_ANS_MINESYSTEM_UPT_USERINFO pMsgSend; // [esp+DCh] [ebp-Ch]

	memset((char *)&pMsgSend.h, 0, 8u);
	if (lpMsg->byRequestType)
	{
		if (lpMsg->byRequestType == 1)
			bResult = g_MineSystemDBSet.DSDB_QueryDeleteUPTUserInfo(lpMsg->szCharName);
		else
			bResult = -1;
	}
	else
	{
		bResult = g_MineSystemDBSet.DSDB_QueryInsertUPTUserInfo(
			lpMsg->szCharName,
			lpMsg->wTwinkleType,
			lpMsg->iCurrentStage);
	}
	//PHeadSubSetB((char *)&pMsgSend.h, 0x4C, 0, 8);
	PHeadSubSetB((LPBYTE)&pMsgSend.h, 0x4C, 0, sizeof(pMsgSend));
	pMsgSend.wUserIndex = lpMsg->wUserIndex;
	pMsgSend.byRequestType = lpMsg->byRequestType;
	pMsgSend.Result = bResult;
	wsjServer.DataSend(aIndex, (char *)&pMsgSend.h, (unsigned __int8)pMsgSend.h.size);
}

void GDReqMuunInvenSubEquipOpen(SDHP_REQ_DBMUUN_INVEN_SUB_EQUIP_OPEN *lpMsg, short aIndex)//ok
{
	SDHP_ANS_DBMUUN_INVEN_SUB_EQUIP_OPEN pMsg;

	//PHeadSubSetB((char *)&pMsg.h, 0x4E, 0, 8);
	PHeadSubSetB((LPBYTE)&pMsg.h, 0x4E, 0, sizeof(pMsg));
	pMsg.btResult = g_CMuunSystemDBSet.MuunInvenSubEquipOpen(lpMsg->AccountID, lpMsg->Name);
	pMsg.aIndex = lpMsg->aIndex;
	wsjServer.DataSend(aIndex, (char *)&pMsg.h, sizeof(pMsg));
}

void GDReqMuunPeriodInfoSelect(_tagSDHP_REQ_MUUN_PERIOD_INFO_SELECT *lpMsg, __int16 aIndex)//ok
{
	int size;
	BYTE dst; 
	dst = 0;
	_tagSDHP_ANS_MUUN_PERIOD_INFO_SELECT pMsg;
	BYTE btListCnt;
	_stMuunPeriodInfoList MuunPeriodItemList[102];
	btListCnt = 0;
	int bResult = g_CMuunSystemDBSet.SelectMuunPeriodInfo(lpMsg->Name, MuunPeriodItemList, &btListCnt);

	if (bResult)
	{
		memcpy((char *)&dst, &MuunPeriodItemList, 12 * btListCnt);
		size = 12 * btListCnt + 10;
		pMsg.btResult = bResult;
		pMsg.aIndex = lpMsg->aIndex;
		pMsg.btCnt = btListCnt;
		//pMsg.h.set((LPBYTE)&pMsg.h.c, 0x4E, 0x20, size);
		pMsg.h.set((LPBYTE)&pMsg,0x4E, 0x20, size);
		memcpy(&dst, &pMsg.h.c, 0xAu);
		wsjServer.DataSend(aIndex, (char *)&dst, size);
		//LogAddTD("[GDReqMuunPeriodInfoSelect][%s] %d %u %d %d", lpMsg->Name, MuunPeriodItemList->wItemType, MuunPeriodItemList->dwSerial, MuunPeriodItemList->lItemExpireDate, size);
	}
}

void GDReqMuunPeriodInfoInsert(_tagSDHP_REQ_MUUN_PERIOD_INFO_INSERT *lpMsg)//ok
{
	//LogAddTD("[GDReqMuunPeriodInfoInsert][%s] %d %u %u %u", lpMsg->Name, lpMsg->wItemType, lpMsg->dwSerial, lpMsg->dwItemDuration, lpMsg->lItemExpireDate);

	int iRet = g_CMuunSystemDBSet.InsertMuunPeriodInfo(lpMsg->Name,lpMsg->wItemType,lpMsg->dwSerial,lpMsg->dwItemDuration,lpMsg->lItemExpireDate);

	if (iRet)
		LogAddTD("[MuunSystem][Error][Insert][Result:%d] [%s] %d %u %u %u",iRet,lpMsg->Name,lpMsg->wItemType,lpMsg->dwSerial,lpMsg->dwItemDuration,lpMsg->lItemExpireDate);
}

void GDReqMuunPeriodInfoExpire(_tagSDHP_REQ_MUUN_PERIOD_INFO_UPDATE *lpMsg)//ok
{
	//LogAddTD("[GDReqMuunPeriodInfoExpire][%s] %d %u %d", lpMsg->Name, lpMsg->wItemType, lpMsg->dwSerial, lpMsg->btUsedInfo);
	int iRet = g_CMuunSystemDBSet.UpdateMuunPeriodInfo(lpMsg->Name, lpMsg->wItemType, lpMsg->dwSerial, lpMsg->btUsedInfo);
	
	if (iRet)
		LogAddTD("[MuunSystem][Error][Update][Result:%d] [%s] %d %u %d", iRet, lpMsg->Name, lpMsg->wItemType, lpMsg->dwSerial, lpMsg->btUsedInfo);
}

void GDReqMuunConditonInfoSave(_tagSDHP_REQ_MUUN_CONDITION_INFO_SAVE *lpMsg)
{
	for (int i = 0; i < 2 && g_CMuunSystemDBSet.SaveMuunConditionInfo(
			lpMsg->Name,
			lpMsg->MuunConditionInfoList[i].btConditionType,
			lpMsg->MuunConditionInfoList[i].btSlotIndex,
			lpMsg->MuunConditionInfoList[i].wValue);
		++i)
	{
		;
	}
}


void GDReqMuunConditonInfoLoad(_tagSDHP_REQ_MUUN_CONDITION_INFO_LOAD *lpMsg, short aIndex)//ok
{
	_tagSDHP_ANS_MUUN_CONDITION_INFO_LOAD pMsg;
	char btListCnt; 
	_stMuunConditionInfoList MuunConditionInfoList[2];

	int Result = g_CMuunSystemDBSet.LoadMuunConditionInfo(lpMsg->Name, MuunConditionInfoList);
	if (Result)
	{
		PHeadSubSetB((LPBYTE)&pMsg.h, 0x4E, 0x24, sizeof(pMsg));
		memcpy((char *)pMsg.MuunConditionInfoList, (char *)MuunConditionInfoList, 8);
		pMsg.aIndex = lpMsg->aIndex;
		wsjServer.DataSend(aIndex, (char *)&pMsg.h, sizeof(pMsg));
	}
}

void GDReqMuunConditonInfoDel(_tagSDHP_REQ_MUUN_CONDITION_INFO_DEL *lpMsg)
{
	g_CMuunSystemDBSet.DelMuunConditionInfo(lpMsg->Name);
}

void GDSetCharacterSlotCount(SDHP_REQ_SET_CHARACTER_SLOT_COUNT *lpMsg, int aIndex)
{
	SDHP_ANS_SET_CHARACTER_SLOT_COUNT pMsg; // [esp+D0h] [ebp-10h]

	//PBMSG_HEAD::set(&pMsg.h, &pMsg.h.c, 0xA5, 0xC);
	pMsg.h.set((LPBYTE)&pMsg.h.c, 0xA5, sizeof(pMsg));
	pMsg.Number = lpMsg->Number;
	pMsg.Result = 1;
	pMsg.EventIndex = lpMsg->EventIndex;
	if (!gACDbSet.SetCharacterSlotCount(lpMsg->AccountId, lpMsg->CharacterSlotCount))
		pMsg.Result = 0;
	//wsjServer.DataSend(aIndex, &pMsg.h.c, 0xC);
	wsjServer.DataSend(aIndex, (char*)&pMsg.h.c, sizeof(pMsg));
}

void GDReqHuntingRecordInfo(SDHP_REQ_HUNTING_RECORD_INFO *lpRecv, int aIndex)
{
	int v2; // [esp+D0h] [ebp-31D4h]
	int size; // [esp+DCh] [ebp-31C8h]
	char buf; // [esp+E8h] [ebp-31BCh]
	char dst; // [esp+E9h] [ebp-31BBh]
	SDHP_ANS_HUNTING_RECORD_COUNT pMsg; // [esp+20F0h] [ebp-11B4h]
	HUNTING_RECORD_INFO pHuntingRecordInfo; // [esp+2108h] [ebp-119Ch]

	if (lpRecv)
	{
		buf = 0;
		memset(&dst, 0, 0x1FFFu);
		size = 0x10;
		pMsg.btMapIndex = lpRecv->btMapIndex;
		pMsg.iUserIndex = lpRecv->iUserIndex;
		pMsg.btCallType = lpRecv->btCallType;
		pMsg.btAnotherUser = lpRecv->btAnotherUser;
		v2 = 0;
		v2 = g_HuntingRecordDBSet.LoadHuntingRecordInfo(lpRecv->AccountId, lpRecv->szName, &pHuntingRecordInfo, &pMsg,
			(unsigned __int8)lpRecv->btMapIndex);
		if (v2)
		{
			LogAddC(2, "[HuntingRecordInfo Error - GDReqHuntingRecordInfo] Ret : %d, AccountId : %s, CharName : %s",
				v2, lpRecv->AccountId, lpRecv->szName);
		}
		else
		{
			memcpy(&buf + size, &pHuntingRecordInfo.btMapIndex, 75 * (unsigned __int8)pMsg.btListCnt);
			size += 75 * (unsigned __int8)pMsg.btListCnt;
			//PWMSG_HEAD2::set(&pMsg.head, &pMsg.head.c, 0xBC, 0x10, size);
			pMsg.head.set((LPBYTE)&pMsg.head.c, 0xBC, 0x10, size);
			memcpy(&buf, &pMsg.head.c, 0x10u);
			wsjServer.DataSend(aIndex, &buf, size);
		}
	}
	else
	{
		LogAddTD("Error - [GDReqHuntingRecordInfo] lpRecv is NULL");
	}
}

void GDReqHuntingRecordInfoSave(SDHP_REQ_HUNTING_RECORD_INFO_SAVE *lpRecv)
{
	g_HuntingRecordDBSet.HuntingRecordInfoSave(lpRecv);
}

void GDReqHuntingRecordInfoUserOpen(SDHP_REQ_HUNTING_RECORD_INFO_USER_OPEN *lpRecv, int aIndex)
{
	int bResult; // [esp+D0h] [ebp-20h]
	SDHP_ANS_HUNTING_RECORD_INFO_USER_OPEN pMsg; // [esp+DCh] [ebp-14h]

	if (lpRecv)
	{
		//PBMSG_HEAD2::set(&pMsg.h, (char *)&pMsg.h, 0xBC, 0x12, 0x10);
		pMsg.h.set((LPBYTE)&pMsg.h, 0xBC, 0x12, sizeof(SDHP_ANS_HUNTING_RECORD_INFO_USER_OPEN));
		pMsg.iUserIndex = lpRecv->iUserIndex;
		bResult = g_HuntingRecordDBSet.LoadHuntingRecordInfoUserOpen(
			lpRecv->AccountId,
			lpRecv->szName,
			&pMsg);
		if (bResult)
		{
			LogAddTD(
				"Error - [GDReqHuntingRecordInfoUserOpen][%s][%s] Error... can't get HuntingRecordInfoUserOpen",
				lpRecv->AccountId,
				lpRecv->szName);
		}
		else
		{
			pMsg.btResult = 1;
			wsjServer.DataSend(aIndex, (char *)&pMsg.h, 0x10);
		}
	}
	else
	{
		LogAddTD("Error - [GDReqHuntingRecordInfoUserOpen] lpRecv is NULL");
	}
}

void GDReqHuntingRecordInfoUserOpenSave(SDHP_REQ_HUNTING_RECORD_INFO_USER_OPEN_SAVE *lpRecv)
{
	int bResult; // [esp+D0h] [ebp-8h]

	if (lpRecv)
	{
		bResult = g_HuntingRecordDBSet.HuntingRecordInfoUserOpenSave(lpRecv);
		if (bResult)
			LogAddTD(
				"Error - [GDReqHuntingRecordInfoUserOpenSave][%s][%s] Error... HuntingRecordInfoUserOpenSave",
				lpRecv->AccountId,
				lpRecv->szName);
	}
	else
	{
		LogAddTD("Error - [GDReqHuntingRecordInfoUserOpenSave] lpRecv is NULL");
	}
}

void GDReqHuntingRecordInfo_Current(SDHP_REQ_HUNTING_RECORD_INFO_CURRENT *lpRecv, int aIndex)
{
	int iRet; // [esp+D0h] [ebp-68h]
	SDHP_ANS_HUNTING_RECORD_INFO_CURRENT pMsg; // [esp+DCh] [ebp-5Ch]

	if (lpRecv)
	{
		pMsg.btMapIndex = lpRecv->btMapIndex;
		pMsg.iUserIndex = lpRecv->iUserIndex;
		pMsg.btCallType = lpRecv->btCallType;
		iRet = 0;
		iRet = g_HuntingRecordDBSet.LoadHuntingRecordInfo_Current(
			lpRecv->AccountId,
			lpRecv->szName,
			&pMsg,
			(unsigned __int8)lpRecv->btMapIndex,
			lpRecv->iYear,
			lpRecv->btMonth,
			lpRecv->btDay);
		if (iRet)
		{
			LogAddC(
				2,
				"[HuntingRecordInfo_Current Error - LoadHuntingRecordInfo_Current] Ret : %d, AccountId : %s, CharName : %s",
				iRet,
				lpRecv->AccountId,
				lpRecv->szName);
		}
		else
		{
			//PWMSG_HEAD2::set(&pMsg.h, &pMsg.h.c, 0xBC, 0x14, 0x56);
			pMsg.h.set((LPBYTE)&pMsg.h.c, 0xBC, 0x14, 0x56);
			//wsjServer.DataSend(aIndex, &pMsg.h.c, 0x56);
			wsjServer.DataSend(aIndex, (char*)&pMsg, sizeof(SDHP_ANS_HUNTING_RECORD_INFO_CURRENT));
		}
	}
	else
	{
		LogAddTD("Error - [GDReqHuntingRecordInfo_Current] lpRecv is NULL");
	}
}

void GDReqHuntingRecordInfoDelete(SDHP_REQ_DELETE_HUNTING_RECORD_INFO *lpRecv)
{
	int bResult; // [esp+D0h] [ebp-8h]

	if (lpRecv)
	{
		bResult = g_HuntingRecordDBSet.DeleteHuntingRecordInfo(
			lpRecv->AccountId,
			lpRecv->szName,
			(unsigned __int8)lpRecv->btMapIndex,
			lpRecv->iYear,
			lpRecv->btMonth,
			lpRecv->btDay);
		if (bResult)
			LogAddTD(
				"Error - [GDReqHuntingRecordInfoDelete][%s][%s] Error... ReqHuntingRecordInfoDelete",
				lpRecv->AccountId,
				lpRecv->szName);
	}
	else
	{
		LogAddTD("Error - [GDReqHuntingRecordInfoDelete] lpRecv is NULL");
	}
}


void GDReqGetPentagramJewel(PMSG_REQ_PENTAGRAMJEWEL *lpMsg, int aIndex)
{
	int size = 16;
	char buf = 0;
	char dst;
	PMSG_ANS_PENTAGRAMJEWEL pMsg;
	PENTAGRAMJEWEL_INFO pPentagramJewelInfo;

	//pMsg.iUserIndex = lpMsg->iUserIndex;
	//pMsg.iAnsType = lpMsg->btJewelPos;
	buf = 0;
	memset(&dst, 0, 0x7FFu);
	size = 16;
	pMsg.iUserIndex = lpMsg->iUserIndex;
	pMsg.iAnsType = (unsigned __int8)lpMsg->btJewelPos;

	int Ret = 0;
	Ret = g_PentagramDBSet.GetPentagramJewel(lpMsg->iUserGuid,lpMsg->AccountId,lpMsg->szName,&pPentagramJewelInfo,&pMsg,lpMsg->btJewelPos);

	if (Ret)
	{
		LogAddC(2,"[PentagramJewel Error - GDReqPentagramJewel] Ret : %d, CharName : %s, UserGuid : %d",
			Ret,lpMsg->szName,lpMsg->iUserGuid);
	}
	else
	{
		//memcpy(&buf + size, &pPentagramJewelInfo.btJewelPos, sizeof(PENTAGRAMJEWEL_INFO));
		//size += sizeof(PENTAGRAMJEWEL_INFO);
		////PWMSG_HEAD::set(&pMsg.head, (char *)&pMsg.head, 224, size);
		//pMsg.head.set((LPBYTE)&pMsg, 0xE0, size/* += (sizeof(PMSG_ANS_PENTAGRAMJEWEL) * pMsg.pPentagramJewelInfo)*/);
		//memcpy(&buf, (char *)&pMsg.head, 0x10);

		memcpy(&buf + size, &pPentagramJewelInfo.btJewelPos, 0x11 * (unsigned __int8)pMsg.btJewelCnt);
		size += 0x11 * (unsigned __int8)pMsg.btJewelCnt;
		//PWMSG_HEAD::set(&pMsg.head, (char *)&pMsg.head, 0xE0, size);

		pMsg.head.set((LPBYTE)&pMsg.head, 0xE0, size);
		memcpy(&buf, (char *)&pMsg.head, 0x10);
		//CwsJoinServer::DataSend(&wsjServer, aIndex, &buf, size);

		wsjServer.DataSend(aIndex, &buf, size);
	}
}
void GDReqDelPentagramJewel(PMSG_DEL_PENTAGRAMJEWEL *lpMsg)
{
	g_PentagramDBSet.DelPentagramJewel(lpMsg);
}

//----- (00457C30) --------------------------------------------------------
void GDReqSetPentagramJewel(PMSG_PENTAGRAMJEWEL_INFO *lpMsg)
{
	g_PentagramDBSet.SetPentagramJewel(lpMsg);
}

//----- (00457CB0) --------------------------------------------------------
void GDReqInsertPentagramJewel(PMSG_INSERT_PENTAGRAMJEWEL *lpMsg)
{
	g_PentagramDBSet.InsertPentagramJewel(lpMsg);
}

//----- (00457CF0) --------------------------------------------------------
void GDReqInsertJewelUpgradeInfo(_tagPMSG_REQ_JEWEL_UPGRADE_INFO_INSERT_DS *lpMsg)
{
	g_PentagramLogDBSet.InsertJewelUpgradeInfo(lpMsg);
}


void GDReqPeriodBuffInsert(BYTE *lpRecv)
{
	int iReturnCode;
	PMSG_REQ_PERIODBUFF_INSERT *lpMsg;

	//lpMsg = (PMSG_REQ_PERIODBUFF_INSERT *)lpRecv; 

	iReturnCode = g_PeriodBuffDBSet.Insert(//need to check
		//pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;
		lpMsg->szCharacterName,
		lpMsg->wBuffIndex,
		lpMsg->btEffectType1,
		lpMsg->btEffectType2,
		lpMsg->dwDuration,
		lpMsg->lExpireDate);
	//lpRecv + 6, *(lpRecv + 9), lpRecv[20], lpRecv[21], *(lpRecv + 6), *(lpRecv + 7));
	//lpRecv->szCharacterName, lpRecv->wBuffIndex, lpRecv->btEffectType1, lpRecv->btEffectType2, lpRecv->dwDuration, lpRecv->lExpireDate);
	if (iReturnCode < 0)
		LogAddTD("[PeriodBuff][Error] [Insert] Name[%s] BuffIndex[%d] ReturnCode[%d] ", lpMsg->szCharacterName, lpMsg->wBuffIndex, iReturnCode);
}

//----- (00459150) --------------------------------------------------------
void GDReqPeriodBuffDelete(BYTE *lpRecv)
{
	int iReturnCode; // [esp+D0h] [ebp-14h]
	PMSG_REQ_PERIODBUFF_DELETE *lpMsg; // [esp+DCh] [ebp-8h]

	lpMsg = (PMSG_REQ_PERIODBUFF_DELETE *)lpRecv;
	iReturnCode = g_PeriodBuffDBSet.Delete(lpMsg->szCharacterName, lpMsg->wBuffIndex);//need to check
	if (iReturnCode < 0)
		LogAddTD(
			"[PeriodBuff][Error] [Delete] Name[%s] BuffIndex[%d] ReturnCode[%d] ",
			lpMsg->szCharacterName,
			lpMsg->wBuffIndex,
			iReturnCode);
}

//----- (004591E0) --------------------------------------------------------
void GDReqPeriodBuffSelect(BYTE *lpRecv, int aIndex)
{
	int i; // [esp+D0h] [ebp-C4h]
	int iReturnCode; // [esp+DCh] [ebp-B8h]
	int iBuffCnt; // [esp+E8h] [ebp-ACh]
	_tagPeriodBuffInfo PeriodBuff[10]; // [esp+F4h] [ebp-A0h]
	PMSG_ANS_PERIODBUFF_SELECT pMsg; // [esp+174h] [ebp-20h]
	PMSG_REQ_PERIODBUFF_SELECT *lpMsg; // [esp+18Ch] [ebp-8h]

	lpMsg = (PMSG_REQ_PERIODBUFF_SELECT *)lpRecv;
	//PBMSG_HEAD2::set(&pMsg.head, 228, 3, 16);
	//pMsg.h.set((LPBYTE)&pMsg, 228, 3, sizeof(PMSG_REQ_PERIODBUFF_SELECT));
	PHeadSubSetB((LPBYTE)&pMsg.head, 0xE4, 0x03, sizeof(pMsg));
	iBuffCnt = 0;
	iReturnCode = g_PeriodBuffDBSet.Select(lpMsg->szCharacterName, PeriodBuff, &iBuffCnt);
	if (iReturnCode >= 0)
	{
		if (iBuffCnt <= 10)
		{
			for (i = 0; i < iBuffCnt; ++i)
			{
				pMsg.wBuffIndex = PeriodBuff[i].wBuffIndex;
				pMsg.btEffectType1 = PeriodBuff[i].btEffectType1;
				pMsg.btEffectType2 = PeriodBuff[i].btEffectType2;
				pMsg.lExpireDate = PeriodBuff[i].lExpireDate;
				pMsg.btResultCode = iReturnCode;
				pMsg.wUserIndex = lpMsg->wUserIndex;
				wsjServer.DataSend(aIndex, (char*)&pMsg.head, pMsg.head.size);
			}
		}
		else
		{
			LogAddTD("[PeriodBuff][Error] BuffCnt Over");
		}
	}
}

//----- (00459390) --------------------------------------------------------
void GDReqArcaBattleMarkCnt(BYTE *lpRecv, int aIndex)
{
	_tagPMSG_ANS_ARCA_BATTLE_MARK_CNT_DS pMsg; // [esp+D0h] [ebp-40h]
	int iResult; // [esp+E4h] [ebp-2Ch]
	int iMarkCnt; // [esp+F0h] [ebp-20h]
	unsigned int dwGuildNumber; // [esp+FCh] [ebp-14h]
	_tagPMSG_REQ_ARCA_BATTLE_MARK_CNT_DS *lpMsg; // [esp+108h] [ebp-8h]

	lpMsg = (_tagPMSG_REQ_ARCA_BATTLE_MARK_CNT_DS *)lpRecv;
	dwGuildNumber = *(lpRecv + 2);
	iMarkCnt = gCArcaBattleDBSet.DBSelectArcaBattleMarkCnt(dwGuildNumber);
	iResult = 0;
	if (iMarkCnt < 0)
	{
		iMarkCnt = 0;
		iResult = 1;
	}
	/*_tagPMSG_ANS_ARCA_BATTLE_MARK_CNT_DS::_tagPMSG_ANS_ARCA_BATTLE_MARK_CNT_DS(&pMsg);
	PBMSG_HEAD2::set(&pMsg.h, 248, 78, 12);*/
	PHeadSubSetB((LPBYTE)&pMsg.h, 0xF8, 0x4E, sizeof(pMsg));
	pMsg.wNumber = lpMsg->wNumber;
	pMsg.dwMarkCnt = iMarkCnt;
	pMsg.btResult = iResult;
	wsjServer.DataSend(aIndex, (char*)&pMsg, 12);
}
#pragma message ("GDReqArcaBattleAllJoinUser need some work here!!!")
void GDReqArcaBattleAllJoinUser(_tagPMSG_REQ_AB_ALL_JOIN_USER_DS *lpMsg, int aIndex)
{
	char v2; // [sp+Ch] [bp-36E8h]@1
	char btUserCnt; // [sp+DFh] [bp-3615h]@1
	int size; // [sp+E8h] [bp-360Ch]@1
	char buf; // [sp+F4h] [bp-3600h]@1
	char dst; // [sp+F5h] [bp-35FFh]@1
	_tagPMSG_ANS_AB_ALL_JOIN_USER_DS pMsg; // [sp+20FCh] [bp-15F8h]@1
	unsigned int v10; // [sp+36F0h] [bp-4h]@1
	int savedregs; // [sp+36F4h] [bp+0h]@1

	//memset(&v2, 0xCCu, 0x36E8u);
#pragma message ("FIX THIS FUCKIN VECTOR!!")
	/*v10 = (unsigned int)&savedregs ^ __security_cookie;
	`vector constructor iterator'(
		&__t,
		0x1Cu,
		200,
		(void *(__thiscall *)(void *))_stABJoinUserInfoDS::_stABJoinUserInfoDS);*/
		//_tagPMSG_ANS_AB_ALL_JOIN_USER_DS::_tagPMSG_ANS_AB_ALL_JOIN_USER_DS(&pMsg);
	_stABJoinUserInfoDS _stABJoinUserInfoDS[200];
	buf = 0;
	memset(&dst, 0, 0x1FFFu);
	btUserCnt = 0;
	size = 5;
	int nRet = 0;
	nRet = gCArcaBattleDBSet.DBSelectABAllJoinUser(_stABJoinUserInfoDS, &btUserCnt);
	if (nRet == 1)
	{
		LogAddTD("WZ_ArcaBattleAllJoinUserSelect Count %d", (unsigned __int8)btUserCnt);
		memcpy(&buf + size, &_stABJoinUserInfoDS, 28 * (unsigned __int8)btUserCnt);
		size += 28 * (unsigned __int8)btUserCnt;
		//PWMSG_HEAD::set((char *)&v8.h, -27, size);
		PHeadSetW((LPBYTE)&pMsg.h, 0xE5, size);
		pMsg.btUserCnt = btUserCnt;
		memcpy(&buf, (char *)&pMsg.h, 5u);
		wsjServer.DataSend(aIndex, &buf, size);
		LogAddTD("WZ_ArcaBattleAllJoinUserSelect DataSend size : %d", size);
	}
	else
	{
		LogAddC(2, "[ArcaBattle Error - GDReqArcaBattleAllJoinUser] Ret : %d", nRet);
	}
}

void GDReqEventInvenItemLoad(SDHP_REQ_DBEVENT_INVEN_LOAD *lpMsg, __int16 aIndex)
{
	int DbVersion; // [esp+DCh] [ebp-21Ch]
	_tagSDHP_ANS_DBEVENT_INVEN_LOAD pMsg; // [esp+E8h] [ebp-210h]

	//_tagSDHP_ANS_DBEVENT_INVEN_LOAD::_tagSDHP_ANS_DBEVENT_INVEN_LOAD(&pMsg);
	pMsg.h.c = 0xC2;
	pMsg.h.headcode = 0xE6;
	pMsg.h.sizeH = 2;
	pMsg.h.sizeL = 8;
	DbVersion = 0;
	if (gCharDbSet.LoadEventInvenItem(lpMsg->Name, pMsg.dbItems, lpMsg->AccountID, &DbVersion))
	{
		pMsg.DbVersion = DbVersion;
		pMsg.aIndex = lpMsg->aIndex;
		wsjServer.DataSend(aIndex, (char *)&pMsg.h, sizeof(pMsg));
	}
}


void GDReqEventInvenItemSave(_tagSDHP_REQ_DBEVENT_INVEN_SAVE *lpMsg)
{
	gCharDbSet.SaveEventInvenItem(lpMsg->Name, lpMsg->dbInventory, lpMsg->AccountID);
}

//----- (0045ABB0) --------------------------------------------------------
void GDReqMuRummyCardSelect(_tagPMSG_REQ_MURUMMY_SELECT_DS *lpRecv, int aIndex)
{
	char v2; 
	_tagMuRummyCardInfoDS stOutMuRummyCardInfoDS[27]; 
	int bRet = 0; 
	BYTE btSpecialCardDeckCnt;
	BYTE btGameType;
	unsigned __int16 wScore;
	_tagPMSG_ANS_MURUMMY_SELECT_DS pMsg; 

	memset(&v2, 0xCCu, 0x21Cu);

	pMsg.btResult = 0;
	pMsg.aIndex = lpRecv->aIndex;
	pMsg.btGameType = 0;
	pMsg.btSpecialCardDeckCnt = 0;
	wScore = 0;
	btGameType = 0;
	btSpecialCardDeckCnt = 0;

	bRet = g_CMuRummyDBSet.DBSelectMuRummyCardInfo(lpRecv->AccountID, lpRecv->Name, stOutMuRummyCardInfoDS, &wScore, &btGameType, &btSpecialCardDeckCnt);
	if (bRet == 1)
	{
		pMsg.btResult = 1;
		memcpy((char *)pMsg.stMuRummyCardInfoDS, (char *)stOutMuRummyCardInfoDS, 0x87u);
	}
	pMsg.wScore = wScore;
	pMsg.btGameType = btGameType;
	pMsg.btSpecialCardDeckCnt = btSpecialCardDeckCnt;
	//PHeadSubSetB((char *)&pMsg.h, -24, 0, 146);
	PHeadSubSetB((LPBYTE)&pMsg.h, 0xE8, 0x00, sizeof(pMsg));
	wsjServer.DataSend(aIndex, (char *)&pMsg.h, sizeof(pMsg));
}

void GDReqMuRummyCardInsert(_tagPMSG_REQ_MURUMMY_INSERT_DS *lpRecv)
{
	g_CMuRummyDBSet.DBInsertMuRummyCardInfo(lpRecv->AccountID,lpRecv->Name,lpRecv->stMuRummyCardInfoDS,
		lpRecv->btGameType,lpRecv->btSpecialCardDeckCnt);
}

//----- (0045AEB0) --------------------------------------------------------
void GDReqMuRummyScoreUpdate(_tagPMSG_REQ_MURUMMY_SCORE_UPDATE_DS *lpRecv)
{
	g_CMuRummyDBSet.DBUpdateMuRummyScore(lpRecv->AccountID,lpRecv->Name,lpRecv->wScore,lpRecv->stCardUpdateDS,
		lpRecv->btGameType,lpRecv->btSpecialCardDeckCnt,lpRecv->btMatchType);
}


void GDReqMuRummyCardUpdate(_tagPMSG_REQ_MURUMMY_UPDATE_DS *lpRecv)
{
	g_CMuRummyDBSet.DBUpdateMuRummyCardInfo(
		lpRecv->AccountID,
		lpRecv->Name,
		lpRecv->btSlotNum,
		lpRecv->btStatus,
		lpRecv->btSequence);
}


void GDReqMuRummyCardDelete(_tagPMSG_REQ_MURUMMY_DELETE_DS *lpRecv)
{
	g_CMuRummyDBSet.DBDeleteMuRummyCardInfo(lpRecv->AccountID, lpRecv->Name);
}


void GDReqMuRummyCardSlotInfoUpdate(_tagPMSG_REQ_MURUMMY_SLOTUPDATE_DS *lpRecv)
{
	_tagMuRummyCardUpdateDS pMsg;

	*&pMsg.btSlotNum = *&lpRecv->stCardUpdateDS.btSlotNum;
	pMsg.btStatus = lpRecv->stCardUpdateDS.btStatus;
	g_CMuRummyDBSet.DBUpdateMuRummyCardSlotInfo(lpRecv->AccountID, lpRecv->Name, pMsg);

}

//----- (0045B070) --------------------------------------------------------
void GDReqMuRummyInfoUpdate(_tagPMSG_REQ_MURUMMY_INFO_UPDATE_DS *lpRecv)
{
	g_CMuRummyDBSet.DBUpdateMuRummyInfo(

		lpRecv->AccountID,
		lpRecv->Name,
		lpRecv->wScore,
		lpRecv->stMuRummyCardUpdateDS,
		lpRecv->btGameType,
		lpRecv->btSpecialCardCnt);
}

//----- (0045B0F0) --------------------------------------------------------
void GDReqMuRummyLogInsert(_tagPMSG_REQ_MURUMMY_LOG_INSERT_DS *lpRecv)
{
	g_CMuRummyDBSet.DBInsertMuRummyLog(lpRecv->AccountID, lpRecv->Name, lpRecv->wScore);
}

//----- (0045B150) --------------------------------------------------------
void GDReqBombHuntSelect(_tagPMSG_REQ_BOMB_HUNT_SELECT_DS *lpRecv, int aIndex)
{
	_tagPMSG_ANS_BOMB_HUNT_SELECT_DS pMsg; // [esp+D0h] [ebp-A4h]
	int bRet; // [esp+114h] [ebp-60h]
	char szOutTileState[49]; // [esp+120h] [ebp-54h]
	char btOutGameState = 0; // [esp+15Fh] [ebp-15h]
	unsigned __int16 wOutScore = 0; // [esp+168h] [ebp-Ch]

	szOutTileState[0] = 0;
	memset(&szOutTileState[1], 0, 0x30u);
	bRet = g_BombHuntDBSet.DBSelectBombHunt(lpRecv->AccountID, lpRecv->Name, &wOutScore, &btOutGameState, szOutTileState);
	//_tagPMSG_ANS_BOMB_HUNT_SELECT_DS::_tagPMSG_ANS_BOMB_HUNT_SELECT_DS(&pMsg);
	//PHeadSubSetB(&pMsg.h, 0xE8, 0x20, 0x3C);
	PHeadSubSetB((LPBYTE)&pMsg.h, 0xE8, 0x00, sizeof(pMsg));
	pMsg.aIndex = lpRecv->aIndex;
	if (bRet)
	{
		szOutTileState[48] = 0;
		pMsg.btResult = 0;
		pMsg.wScore = wOutScore;
		pMsg.btGameState = btOutGameState;
		memcpy(pMsg.szTileState, szOutTileState, 0x30u);
	}
	else
	{
		pMsg.btResult = 1;
	}
	wsjServer.DataSend(aIndex, (char*)&pMsg, 60);
}

void GDReqBombHuntInsert(_tagPMSG_REQ_BOMB_HUNT_INSERT_DS *lpRecv)
{
	g_BombHuntDBSet.DBInsertBombHunt(

		lpRecv->AccountID,
		lpRecv->Name,
		lpRecv->wScore,
		lpRecv->btGameState,
		lpRecv->szTileState);
}

//----- (0045B3D0) --------------------------------------------------------
void GDReqBombHuntDelete(_tagPMSG_REQ_BOMB_HUNT_DELETE_DS *lpRecv)
{
	g_BombHuntDBSet.DBDeleteBombHunt(lpRecv->AccountID, lpRecv->Name);
}

//----- (0045B430) --------------------------------------------------------
void GDReqBombLogInsert(_tagPMSG_REQ_BOMB_HUNT_LOG_INSERT_DS *lpRecv)
{
	g_BombHuntDBSet.DBInsertBombHuntLog(

		lpRecv->AccountID,
		lpRecv->Name,
		lpRecv->wScore,
		lpRecv->btClear);
}
void GDRequestPShopItemValue(PMSG_REQ_PSHOPITEMVALUE_INFO *lpRecv, int aIndex)
{
	int iRet; // [esp+D0h] [ebp-A7Ch]
	int lOfs; // [esp+DCh] [ebp-A70h]
	char sendbuf[2048]; // [esp+E8h] [ebp-A64h]
	PMSG_ANS_PSHOPITEMVALUE_INFO pMsg; // [esp+8F0h] [ebp-25Ch]
	PMSG_PSHOPITEMVALUE_INFO PShopItemValueInfo[32]; // [esp+904h] [ebp-248h]

	sendbuf[0] = 0;
	memset(&sendbuf[1], 0, 0x7FFu);
	lOfs = 12;
	pMsg.iUserIndex = lpRecv->iUserIndex;
	iRet = g_PShopSystemDBSet.LoadPShopItemValueInfo(
		lpRecv->AccountId,
		lpRecv->szName,
		PShopItemValueInfo,
		&pMsg);
	if (iRet)
	{
		LogAddC(
			2,
			"[PShopItemValueInfo Error - GDRequestPShopItemValue] Ret : %d, AccountId : %d, CharName : %s",
			iRet,
			lpRecv->AccountId,
			lpRecv->szName);
	}
	else
	{
		/*memcpy(&sendbuf[lOfs], QuestInfo, 29 * pMsg.btQuestCnt);
		lOfs += 29 * pMsg.btQuestCnt;
		PWMSG_HEAD::set(&pMsg.head, 246, lOfs);
		memcpy(sendbuf, &pMsg.head, 9u);
		CwsJoinServer::DataSend(aIndex, sendbuf, lOfs);*/

		/*memcpy(&sendbuf[lOfs], QuestInfo, sizeof(_QUESTEXP_INFO) * pMsg.btQuestCnt);
		pMsg.head.set((LPBYTE)&pMsg, 0xF6, lOfs += (sizeof(_QUESTEXP_INFO) * pMsg.btQuestCnt));
		memcpy(sendbuf, &pMsg, sizeof(PMSG_ANS_QUESTEXP_INFO));*/

		memcpy(&sendbuf[lOfs], PShopItemValueInfo, 18 * pMsg.btItemCnt);
		//lOfs += 18 * pMsg.btItemCnt;
		//PWMSG_HEAD::set(&pMsg.head, 233, lOfs);
		pMsg.head.set((LPBYTE)&pMsg, 0xE9, lOfs += (sizeof(PMSG_PSHOPITEMVALUE_INFO) *pMsg.btItemCnt));
		memcpy(sendbuf, &pMsg.head, 0xCu);
		wsjServer.DataSend(aIndex, sendbuf, lOfs);
	}
}

void GDUpdatePShopItemValue()
{
	;
}

//----- (0045B6C0) --------------------------------------------------------
void GDAllSavePShopItemValue(PMSG_UPDATE_PSHOPITEMVALUE_INFO *lpRecv)
{
	g_PShopSystemDBSet.SavePShopItemValueInfo(lpRecv);
}

//----- (0045B700) --------------------------------------------------------
void GDDelPShopItemValue(PMSG_DEL_PSHOPITEM *lpRecv)
{
	g_PShopSystemDBSet.DelPShopItemValueInfo(lpRecv);
}

//----- (0045B740) --------------------------------------------------------
void GDMovePShopItem(PMSG_MOVE_PSHOPITEM *lpRecv)
{
	g_PShopSystemDBSet.MovePShopItem(lpRecv);
}

void GD_ChaosCastleNotice(_tagCHAOS_CASTLE_NOTICE *lpRecv)
{
	_tagCHAOS_CASTLE_NOTICE pMsg; // [sp+DCh] [bp-120h]@3
	if (lpRecv)
	{
		memcpy((char *)&pMsg.h, (char *)&lpRecv->h, lpRecv->h.size);
		for (int iIDX = 0; iIDX < 100; ++iIDX)
		{
			if (gSObj[iIDX].Connected)
				wsjServer.DataSend(iIDX, (char *)&pMsg.h, (unsigned __int8)pMsg.h.size);
		}
	}
	else
	{
		LogAddTD("Error - [GD_ChaosCastleNotice] lpRecv is NULL");
	}
}
// 68372C4: using guessed type void (*LogAddTD)(char *, ...);
// 6B90690: using guessed type struct ServerObject_Struct *gSObj;

//----- (0045F930) --------------------------------------------------------
void GD_ReqChaosCastleUserCount(_tagREQCHAOS_CASTLE_USER_GS *lpRecv, int aIndex)
{
	_tagREQCHAOS_CASTLE_USER_DS pMsg;

	if (lpRecv)
	{
		for (int iIDX = 0; iIDX < 100; ++iIDX)
		{
			if (gSObj[iIDX].Connected && gSObj[iIDX].btGameServerType == 2)
			{
				//PBMSG_HEAD2::set(&pMsg.h, 238, 1, 36);
				pMsg.h.set((LPBYTE)&pMsg, 0xEE, 0x01, sizeof(_tagREQCHAOS_CASTLE_USER_DS));
				pMsg.serverIndex = aIndex;
				pMsg.userIndex = lpRecv->userIndex;
				memcpy(pMsg.AccountID, lpRecv->AccountID, 0xBu);
				memcpy(pMsg.Name, lpRecv->Name, 0xDu);
				wsjServer.DataSend(iIDX, (char *)&pMsg.h, pMsg.h.size);
				return;
			}
		}
	}
	else
	{
		LogAddTD("Error - [GD_CaosCastleNotice] lpRecv is NULL");
	}
}


void GD_AnsChaosCastleUserCount(_tagANSCHAOS_CASTLE_USER_GS *lpRecv)
{
	_tagANSCHAOS_CASTLE_USER_DS pMsg;
	if (lpRecv)
	{
		//PBMSG_HEAD2::set(&pMsg.h, (char *)&pMsg.h, 0xEE, 2, 0x24);
		pMsg.h.set((LPBYTE)&pMsg.h, 0xEE, 2, sizeof(pMsg));
		pMsg.userIndex = lpRecv->userIndex;
		memcpy(pMsg.AccountID, lpRecv->AccountID, 0xBu);
		memcpy(pMsg.Name, lpRecv->Name, 0xEu);
		pMsg.wRemainTime = lpRecv->wRemainTime;
		wsjServer.DataSend(lpRecv->serverIndex, (char *)&pMsg.h, sizeof(pMsg));
	}
	else
	{
		LogAddTD("Error - [GD_ReqChaosCastleUserCount] lpRecv is NULL");
	}
}

void GD_ReqGetSpecializedServerInfo(_tagREQGETSPECIALIZEDSERVERINFO *lpRecv, int aIndex)
{
	int bResult; // [esp+D0h] [ebp-58h]
	unsigned int dwCloseDateTime; // [esp+DCh] [ebp-4Ch]
	unsigned int dwPlayTimePCRoom; // [esp+E8h] [ebp-40h]
	unsigned int dwPlayTimeNormal; // [esp+F4h] [ebp-34h]
	_tagANSGETSPECIALIZEDSERVERINFO pMsg; // [esp+100h] [ebp-28h]

	if (lpRecv)
	{
		//PBMSG_HEAD2::set(&pMsg.h, (char *)&pMsg.h, 0xEE, 3, 0x20);
		pMsg.h.set((LPBYTE)&pMsg.h, 0xEE, 0x03, sizeof(pMsg));
		dwPlayTimeNormal = 0;
		dwPlayTimePCRoom = 0;
		dwCloseDateTime = 0;
		bResult = g_SPServerDBSet.getSPServerPlayTime(

			lpRecv->AccountID,
			&dwPlayTimeNormal,
			&dwPlayTimePCRoom,
			&dwCloseDateTime);
		if (bResult)
		{
			pMsg.userIndex = lpRecv->userIndex;
			pMsg.btJoinResult = lpRecv->btJoinResult;
			memcpy(pMsg.AccountID, lpRecv->AccountID, 0xBu);
			pMsg.dwPlayTime_Normal = dwPlayTimeNormal;
			pMsg.dwPlayTime_PCRoom = dwPlayTimePCRoom;
			pMsg.dwCloseDateTime = dwCloseDateTime;
			wsjServer.DataSend(aIndex, (char *)&pMsg.h, sizeof(pMsg));
		}
		else
		{
			LogAddTD("Error - [GD_ReqGetSpecializedServerInfo] getSPServerPlayTime");
		}
	}
	else
	{
		LogAddTD("Error - [GD_ReqGetSpecializedServerInfo] lpRecv is NULL");
	}
}

void GD_ReqSetSpecializedServerInfo(_tagREQSETSPECIALIZEDSERVERINFO *lpRecv)
{
	if (lpRecv)
	{
		int bResult = g_SPServerDBSet.setSPServerPlayTime(

			lpRecv->AccountID,
			lpRecv->dwPlayTime_Normal,
			lpRecv->dwPlayTime_PCRoom,
			lpRecv->dwCloseDateTime);
		if (!bResult)
			LogAddTD("Error - [GD_ReqGetSpecializedServerInfo] setSPServerPlayTime");
	}
	else
	{
		LogAddTD("Error - [GD_ReqSetSpecializedServerInfo] lpRecv is NULL");
	}
}

void GD_ReqSetRuudTokenLog(_tagREQSETRUUDTOKENLOG *lpRecv)
{
	if (lpRecv)
	{
		int bResult = g_RuudLogDBSet.setRuudTokenLog(

			lpRecv->AccountID,
			lpRecv->Name,
			lpRecv->dwRuudTotal,
			lpRecv->dwRuudValue,
			lpRecv->byFlag);
		if (!bResult)
			LogAddTD("Error - [GD_ReqSetRuudTokenLog] GD_ReqSetRuudTokenLog");
	}
	else
	{
		LogAddTD("Error - [GD_ReqSetRuudTokenLog] lpRecv is NULL");
	}
}


void GD_ITL_SaveGuildCount(SDHP_REQ_SAVE_ITL_GUILDCOUNT *lpRecv)
{
	if (lpRecv)
	{
		g_ITLDBset.SaveITLGuildCount(lpRecv->GuildName, lpRecv->byCount);
		LogAddTD("[ITL][SaveITLGuildCount] GName : %s, Count : %d", lpRecv->GuildName, lpRecv->byCount);
	}
	else
	{
		LogAddTD("[ITL][SaveITLGuildCount] lpRecv is NULL");
	}
}

//----- (0045BD20) --------------------------------------------------------
void GD_ITL_SaveGuildPoint(SDHP_REQ_SAVE_ITL_GUILDPOINT *lpRecv)
{
	if (lpRecv)
	{
		g_ITLDBset.SaveITLGuildPoint(
			lpRecv->GuildName,
			lpRecv->nType,
			lpRecv->byWin,
			lpRecv->byLose,
			lpRecv->byOccupiedCnt,
			lpRecv->byEnterCnt);
		LogAddTD(
			"[ITL][SaveITLGuildPoint] G.Name : %s, Type:%d %d, Win:%d, Lose:%d, OccCnt:%d , EnterCnt:%d",
			lpRecv->GuildName,
			lpRecv->nType,
			lpRecv->byWin,
			lpRecv->byLose,
			lpRecv->byOccupiedCnt,
			lpRecv->byEnterCnt);
	}
	else
	{
		LogAddTD("[ITL][SaveITLGuildPoint] lpRecv is NULL");
	}
}

//----- (0045BDF0) --------------------------------------------------------
void GD_ITL_SaveUserPoint(SDHP_REQ_SAVE_ITL_USERPOINT *lpRecv)
{
	if (lpRecv)
	{
		g_ITLDBset.UpdateITLUserPoint(
			lpRecv->UserName,
			lpRecv->GName,
			lpRecv->Type,
			lpRecv->nOccupiedCount,
			lpRecv->nKillP,
			lpRecv->nInvalidationCount,
			lpRecv->EnterCount,
			lpRecv->Win);

		LogAddTD("[ITL][SaveITLUserPoint] PC.NAME:%s,G.NAME:%s,OccCnt:%d,Kill:%d,Type:%d,nInvalidationCount:%d,EnterCount:%d,Win:%d",
			lpRecv->UserName,
			lpRecv->GName,
			lpRecv->nOccupiedCount,
			lpRecv->nKillP,
			lpRecv->Type,
			lpRecv->nInvalidationCount,
			lpRecv->EnterCount,
			lpRecv->Win);
	}
	else
	{
		LogAddTD("[ITL][SaveITLUserPoint] lpRecv is NULL");
	}
}

//----- (0045BEE0) --------------------------------------------------------
void GD_ITL_LoadGuildEnterCount(_tagPMSG_REQ_ITL_GUILDCOUNTREQ *lpRecv, int aIndex)
{
	int nEnterCount; // [esp+D0h] [ebp-28h]
	_tagPMSG_ANS_ITL_GUILDCOUNTANS pMsg; // [esp+DCh] [ebp-1Ch]
	int nReturn; // [esp+F0h] [ebp-8h]

	if (lpRecv)
	{
		nReturn = -1;
		memset(&pMsg.h, 0, 0xCu);
		nEnterCount = 0;
		g_ITLDBset.ReqGuildCount(lpRecv->GuildName, &nEnterCount);
		//PHeadSubSetB(&pMsg.h, 0x7D, 4, 0xC);
		PHeadSubSetB((LPBYTE)&pMsg, 0x7D, 4, sizeof(pMsg));
		pMsg.byCount = nEnterCount;
		pMsg.nUserIndex = lpRecv->nUserIndex;
		wsjServer.DataSend(aIndex, (char*)&pMsg, pMsg.h.size);
	}
	else
	{
		LogAddTD("[ITL][GD_ITL_LoadGuildEnterCount] lpRecv is NULL");
	}
}

void GD_ITL_LoadUserEnterCount(_tagPMSG_REQ_ITL_USERCOUNTREQ *lpRecv, int aIndex)
{
	_tagPMSG_ANS_ITL_USERCOUNTANS pMsg;

	if (lpRecv)
	{
		int nReturn = -1;
		memset(&pMsg.h, 0, 0xCu);
		int nEnterCount = 0;
		g_ITLDBset.ReqUserItlEnterCount(lpRecv->UserName, &nEnterCount);
		//PHeadSubSetB((LPBYTE)&pMsg.h, 125, 5, 12);
		PHeadSubSetB((LPBYTE)&pMsg.h, 0x7D, 5, sizeof(pMsg));
		pMsg.byCount = nEnterCount;
		pMsg.nUserIndex = lpRecv->nUserIndex;
		wsjServer.DataSend(aIndex, (char*)&pMsg, pMsg.h.size);
	}
	else
	{
		LogAddTD("[ITL][GD_ITL_LoadUserEnterCount] lpRecv is NULL");
	}
}


void GD_ITL_GuildTournamentGet(PMSG_REQ_ITL_TOURNAMENT *lpRecv, int aIndex)
{
	char byCount; // [esp+DFh] [ebp-485h]
	int loffs; // [esp+E8h] [ebp-47Ch]
	char sendbuf[1024]; // [esp+F4h] [ebp-470h]
	_tagPMSG_ANS_ITL_RANKING pMsg; // [esp+4FCh] [ebp-68h]
	_stITLRankingInfo ITLRANK[6]; // [esp+50Ch] [ebp-58h]

	if (lpRecv)
	{
#pragma message ("FIX THIS FUCKIN VECTOR!!")
		/*`vector constructor iterator'(QuestInfo, 0x1Du, 25, _QUESTEXP_INFO::_QUESTEXP_INFO);
		_QUESTEXP_INFO QuestInfo[25];*/
		//`vector constructor iterator'(ITLRANK, 0xDu, 6, _stITLRankingInfo::_stITLRankingInfo);
		//	_tagPMSG_ANS_ITL_RANKING::_tagPMSG_ANS_ITL_RANKING(&pMsg);
		sendbuf[0] = 0;
		memset(&sendbuf[1], 0, 0x3FFu);
		byCount = 0;
		loffs = 6;
		if (!g_ITLDBset.LoadITLTournament(ITLRANK, &byCount, lpRecv->byITLType))
		{
			memcpy(&sendbuf[loffs], ITLRANK, 13 * byCount);
			loffs += 13 * byCount;
			//PWMSG_HEAD2::set(&pMsg.h.c, 125, 2, loffs);
			pMsg.h.set((LPBYTE)&pMsg.h.c, 0x7D, 2, loffs);

			pMsg.byGuildCnt = byCount;
			memcpy(sendbuf, &pMsg.h.c, 6u);
			wsjServer.DataSend(aIndex, sendbuf, loffs);
		}
	}
}
//----- (0045BFF0) --------------------------------------------------------
void GD_ITL_RewardRenew(PMSG_REQ_ITL_RENEW_REWARD *lpRecv)
{
	if (lpRecv)
	{
		g_ITLDBset.Renew_ITLRewardList();
		LogAddTD("[ITL][GD_ITL_RewardRenew]");
	}
	else
	{
		LogAddTD("[ITL][GD_ITL_RewardRenew] lpRecv is NULL");
	}
}

//----- (0045C070) --------------------------------------------------------
void GD_ITL_UpdaterewardReceived(PMSG_REQ_ITL_REWARDRECEIVED *lpRecv)
{
	if (lpRecv)
	{
		g_ITLDBset.UpdateITL_RewardReceived(lpRecv->szCharName);
		LogAddTD("UpdateITL_RewardReceived %s", lpRecv->szCharName);
	}
	else
	{
		LogAddTD("[ITL][GD_ITL_UpdaterewardReceived] lpRecv is NULL");
	}
}

//----- (0045C0F0) --------------------------------------------------------
void GD_ITL_GetRewardList(PMSG_REQ_ITL_GET_REWARDLIST *lpRecv, int aIndex)
{
	int nReturn; // [esp+D0h] [ebp-4BCh]
	char byCount; // [esp+DFh] [ebp-4ADh]
	int loffs; // [esp+E8h] [ebp-4A4h]
	char sendbuf[1024]; // [esp+F4h] [ebp-498h]
	_tagPMSG_ANS_ITL_REWARDLIST pMsg; // [esp+4FCh] [ebp-90h]
	_stITLRewardList ITLREWARD[5]; // [esp+50Ch] [ebp-80h]

	if (lpRecv)
	{
#pragma message ("FIX THIS FUCKIN VECTOR!!")
		//`vector constructor iterator'(ITLREWARD, 0x18u, 5, (void *(__thiscall *)(void *))_stITLRewardList::_stITLRewardList);
			//_tagPMSG_ANS_ITL_REWARDLIST::_tagPMSG_ANS_ITL_REWARDLIST(&pMsg);
		sendbuf[0] = 0;
		memset(&sendbuf[1], 0, 0x3FFu);
		byCount = 0;
		loffs = 6;
		nReturn = g_ITLDBset.LoadITLRewardList(ITLREWARD, &byCount);
		if (!nReturn)
		{
			memcpy(&sendbuf[loffs], ITLREWARD, 24 * byCount);
			loffs += 24 * byCount;
			//PWMSG_HEAD2::set(&pMsg.h.c, 125, 9, loffs);
			pMsg.h.set((LPBYTE)&pMsg.h.c, 0x7D, 9, loffs);
			pMsg.byCnt = byCount;
			memcpy(sendbuf, &pMsg.h.c, 6u);
			wsjServer.DataSend(aIndex, sendbuf, loffs);
			LogAddTD("[ITL][GD_ITL_GetRewardList]");
		}
	}
	else
	{
		LogAddTD("[ITL][GD_ITL_GetRewardList] lpRecv is NULL");
	}
}

void GD_ITL_GuildRankGet(_tagPMSG_REQ_GUILDRANK_GET *lpRecv, int aIndex)
{
	char byCount; // [esp+DFh] [ebp-70Dh]
	int loffs; // [esp+E8h] [ebp-704h]
	char sendbuf[1024]; // [esp+F4h] [ebp-6F8h]
	_tagPMSG_ANS_ITL_RANKING pMsg; // [esp+4FCh] [ebp-2F0h]
	_stITLRankingInfo ITLRANK[56]; // [esp+50Ch] [ebp-2E0h]

	if (lpRecv)
	{
		//`vector constructor iterator'(ITLRANK, 0xDu, 56, _stITLRankingInfo::_stITLRankingInfo);
			//_tagPMSG_ANS_ITL_RANKING::_tagPMSG_ANS_ITL_RANKING(&pMsg);
		sendbuf[0] = 0;
		memset(&sendbuf[1], 0, 0x3FFu);
		byCount = 0;
		loffs = 6;
		if (!g_ITLDBset.LoadITLGuildRank(ITLRANK, &byCount))
		{
			memcpy(&sendbuf[loffs], ITLRANK, 13 * byCount);
			loffs += 13 * byCount;
			//PWMSG_HEAD2::set(&pMsg.h.c, 125, 1, loffs);
			pMsg.h.set((LPBYTE)&pMsg.h.c, 0x7D, 1, loffs);
			pMsg.byGuildCnt = byCount;
			memcpy(sendbuf, &pMsg.h.c, 6u);
			wsjServer.DataSend(aIndex, sendbuf, loffs);
		}
	}
}

//----- (0045BC00) --------------------------------------------------------
void GD_ITL_LeagueRankRenew(_tagPMSG_REQ_LEAGUERANK_RENEW *lpRecv)
{
	if (lpRecv)
	{
		g_ITLDBset.RenewITLGuildRank(lpRecv->byITLType);
		LogAddTD("[ITL][RenewITLGuildRank]%d", lpRecv->byITLType);
	}
	else
	{
		LogAddTD("[ITL][GD_ITL_LeagueRankRenew] lpRecv is NULL");
	}
}


void GDReqMuunInvenItemLoad(SDHP_REQ_DBMUUN_INVEN_LOAD *lpMsg, __int16 aIndex)
{
	_tagSDHP_ANS_DBMUUN_INVEN_LOAD pMsg;

	pMsg.h.c = 0xC2;
	pMsg.h.headcode = 0xF1;
	pMsg.h.sizeH = 6;
	pMsg.h.sizeL = 0x68;
	int DbVersion = 0;
	int SubEquip = 0;
	int bRet = 0;
	bRet = g_CMuunSystemDBSet.LoadMuunInvenItem(lpMsg->Name, pMsg.dbItems, lpMsg->AccountID, &SubEquip, &DbVersion);

	if (bRet)
	{
		pMsg.SubEquip = SubEquip;
		pMsg.DbVersion = DbVersion;
		pMsg.aIndex = lpMsg->aIndex;
		wsjServer.DataSend(aIndex, (char*)&pMsg.h, sizeof(pMsg));
	}
}

void GDReqMuunInvenItemSave(_tagSDHP_REQ_DBMUUN_INVEN_SAVE *lpMsg)
{
	g_CMuunSystemDBSet.SaveMuunInvenItem(lpMsg->Name, lpMsg->dbInventory, lpMsg->AccountID);
}

void GDReqGremoryCaseItemInsert(_tagSDHP_REQ_GREMORY_CASE_INSERT *lpMsg, __int16 aIndex)
{
	_tagSDHP_ANS_GREMORY_CASE_INSERT pMsg;
	unsigned int dwSerial;
	int Result;

	Result = 0;
	dwSerial = 0;
	Result = g_CGremoryCaseDBSet.InsertGremoryCase(
		lpMsg->AccountID,
		lpMsg->Name,
		lpMsg->btGCType,
		lpMsg->btGiveType,
		lpMsg->btItemType,
		lpMsg->wItemIndex,
		lpMsg->btLevel,
		lpMsg->btDur,
		lpMsg->btSkill,
		lpMsg->btLuck,
		lpMsg->btOpt,
		lpMsg->btSetOpt,
		lpMsg->wNewOpt,
		lpMsg->btBonusSocketOpt,
		lpMsg->btSocketOpt,
		lpMsg->dwReceiptExpireDuration,
		lpMsg->dwItemDuration,
		lpMsg->lRecvDate,
		lpMsg->lRecvExpireDate,
		lpMsg->lItemExpireDate,
		&dwSerial);
	//_tagSDHP_ANS_GREMORY_CASE_INSERT::_tagSDHP_ANS_GREMORY_CASE_INSERT();
	//PBMSG_HEAD2::set(&pMsg.h, 243, 0, 44);
	pMsg.h.set((LPBYTE)&pMsg.h, 0xF3, 0x00, sizeof(_tagSDHP_ANS_GREMORY_CASE_INSERT));
	if (Result)
		LogAddTD(
			"[GremoryCase][Error][Insert][Result:%d] [%s][%s] %d %d %d %u %u",
			Result,
			lpMsg->AccountID,
			lpMsg->Name,
			lpMsg->btItemType,
			lpMsg->wItemIndex,
			lpMsg->btLevel,
			dwSerial,
			lpMsg->lRecvDate);
	pMsg.aIndex = lpMsg->aIndex;
	pMsg.btResult = Result;
	pMsg.btGCType = lpMsg->btGCType;
	pMsg.btGiveType = lpMsg->btGiveType;
	pMsg.btItemType = lpMsg->btItemType;
	pMsg.wItemIndex = lpMsg->wItemIndex;
	pMsg.btLevel = lpMsg->btLevel;
	pMsg.btDur = lpMsg->btDur;
	pMsg.btSkill = lpMsg->btSkill;
	pMsg.btLuck = lpMsg->btLuck;
	pMsg.btOpt = lpMsg->btOpt;
	pMsg.btSetOpt = lpMsg->btSetOpt;
	pMsg.wNewOpt = lpMsg->wNewOpt;
	pMsg.btBonusSocketOpt = lpMsg->btBonusSocketOpt;
	memcpy(pMsg.btSocketOpt, lpMsg->btSocketOpt, 5u);
	pMsg.dwSerial = dwSerial;
	pMsg.lRecvDate = lpMsg->lRecvDate;
	pMsg.lRecvExpireDate = lpMsg->lRecvExpireDate;
	pMsg.lItemExpireDate = lpMsg->lItemExpireDate;
	wsjServer.DataSend(aIndex, (char*)&pMsg.h, 0x2C);
}

void GDReqGremoryCaseItemSelect(_tagSDHP_REQ_GREMORY_CASE_SELECT *lpMsg, __int16 aIndex)
{
	int size; // [esp+D0h] [ebp-1E6Ch]
	char dst; // [esp+DCh] [ebp-1E60h]
	__int16 v4; // [esp+E6h] [ebp-1E56h]
	_tagSDHP_ANS_GREMORY_CASE_SELECT pMsg; // [esp+10E4h] [ebp-E58h]
	_tagSDHP_ANS_GREMORY_CASE_SELECT pMsgv2; // [esp+10F8h] [ebp-E44h]
	int Result; // [esp+110Ch] [ebp-E30h]
	char btListCnt; // [esp+111Bh] [ebp-E21h]
	_stGremoryCaseList __t; // [esp+1124h] [ebp-E18h]
#pragma message ("FIX THIS FUCKIN VECTOR!!")
	//`vector constructor iterator'(&__t, 0x24u, 100, _stGremoryCaseList::_stGremoryCaseList);
	btListCnt = 0;
	Result = g_CGremoryCaseDBSet.SelectGremoryCase(lpMsg->AccountID, lpMsg->Name, &__t, &btListCnt);
	if (Result)
	{
		//_tagSDHP_ANS_GREMORY_CASE_SELECT::_tagSDHP_ANS_GREMORY_CASE_SELECT();
		memcpy(&v4, &__t, 36 * btListCnt);
		size = 36 * btListCnt + 10;
		pMsg.btResult = Result;
		pMsg.aIndex = lpMsg->aIndex;
		pMsg.btCnt = btListCnt;
		//PWMSG_HEAD2::set(&v5.h.c, 243, 16, size);
		pMsg.h.set((LPBYTE)&pMsg.h.c, 0xF3, 0x10, size);
		memcpy(&dst, &pMsg.h.c, 0xAu);
		wsjServer.DataSend(aIndex, &dst, size);
	}
	else
	{
		//_tagSDHP_ANS_GREMORY_CASE_SELECT::_tagSDHP_ANS_GREMORY_CASE_SELECT();
		pMsgv2.aIndex = lpMsg->aIndex;
		pMsgv2.btCnt = 0;
		pMsgv2.btResult = 0;
		//PWMSG_HEAD2::set(&pMsg.h.c, 243, 16, 10);
		pMsgv2.h.set((LPBYTE)&pMsgv2.h.c, 0xF3, 0x10, sizeof(pMsg));
		//wsjServer.DataSend(aIndex, &pMsgv2.h.c, 10);
		wsjServer.DataSend(aIndex, (char*)&pMsgv2.h.c, 0xA);
		LogAddTD("[GremoryCase][Error][GDReqGremoryCaseItemSelect][Result:%d] [%s][%s]", Result, lpMsg->AccountID, lpMsg->Name);
	}
}

void GDReqGremoryCaseItemExpire(_tagSDHP_REQ_GC_UPDATE *lpMsg, __int16 aIndex)
{
	_tagSDHP_ANS_GC_UPDATE pMsg; // [esp+D0h] [ebp-24h]
	int Result; // [esp+ECh] [ebp-8h]

	Result = 0;
	Result = g_CGremoryCaseDBSet.UpdateGremoryCase(

		lpMsg->AccountID,
		lpMsg->Name,
		lpMsg->btGCType,
		lpMsg->btItemType,
		lpMsg->wItemIndex,
		lpMsg->btLevel,
		lpMsg->dwSerial,
		lpMsg->lRecvDate,
		lpMsg->btUsedInfo);
	//_tagSDHP_ANS_GC_UPDATE::_tagSDHP_ANS_GC_UPDATE();
	//PBMSG_HEAD2::set(&pMsg.h, 243, 1, 20);
	pMsg.h.set((LPBYTE)&pMsg.h, 0xF3, 0x01, sizeof(_tagSDHP_ANS_GC_UPDATE));
	if (Result)
		LogAddTD(
			"[GremoryCase][Error][Expire][Result:%d] [%s][%s] %d %d %d %u %u",
			Result,
			lpMsg->AccountID,
			lpMsg->Name,
			lpMsg->btItemType,
			lpMsg->wItemIndex,
			lpMsg->btLevel,
			lpMsg->dwSerial,
			lpMsg->lRecvDate);
	pMsg.btResult = Result;
	pMsg.aIndex = lpMsg->aIndex;
	pMsg.btItemType = lpMsg->btItemType;
	pMsg.wItemIndex = lpMsg->wItemIndex;
	pMsg.btLevel = lpMsg->btLevel;
	pMsg.dwSerial = lpMsg->dwSerial;
	pMsg.lRecvDate = lpMsg->lRecvDate;
	wsjServer.DataSend(aIndex, (char*)&pMsg, 0x14);
}

void GDReqGremoryCaseItemDelete(_tagSDHP_REQ_GC_UPDATE *lpMsg, __int16 aIndex)
{
	_tagSDHP_ANS_GC_UPDATE pMsg; // [esp+D0h] [ebp-24h]
	int Result; // [esp+ECh] [ebp-8h]

	Result = 0;
	Result = g_CGremoryCaseDBSet.UpdateGremoryCase(

		lpMsg->AccountID,
		lpMsg->Name,
		lpMsg->btGCType,
		lpMsg->btItemType,
		lpMsg->wItemIndex,
		lpMsg->btLevel,
		lpMsg->dwSerial,
		lpMsg->lRecvDate,
		lpMsg->btUsedInfo);
	//_tagSDHP_ANS_GC_UPDATE::_tagSDHP_ANS_GC_UPDATE();
	//PBMSG_HEAD2::set(&pMsg.h, 243, 4, 20);
	pMsg.h.set((LPBYTE)&pMsg.h, 0xF3, 0x04, sizeof(_tagSDHP_ANS_GC_UPDATE));
	if (Result)
		LogAddTD(
			"[GremoryCase][Error][Delete][Result:%d] [%s][%s] %d %d %d %u %u",
			Result,
			lpMsg->AccountID,
			lpMsg->Name,
			lpMsg->btItemType,
			lpMsg->wItemIndex,
			lpMsg->btLevel,
			lpMsg->dwSerial,
			lpMsg->lRecvDate);
	pMsg.btResult = Result;
	pMsg.aIndex = lpMsg->aIndex;
	pMsg.btItemType = lpMsg->btItemType;
	pMsg.wItemIndex = lpMsg->wItemIndex;
	pMsg.btLevel = lpMsg->btLevel;
	pMsg.dwSerial = lpMsg->dwSerial;
	pMsg.lRecvDate = lpMsg->lRecvDate;
	wsjServer.DataSend(aIndex, (char*)&pMsg, 0x14);
}

//----- (0045CD30) --------------------------------------------------------
void GDReqGremoryCaseItemRecv(_tagSDHP_REQ_GC_UPDATE *lpMsg, __int16 aIndex)
{
	_tagSDHP_ANS_GC_UPDATE pMsg; // [esp+D0h] [ebp-24h]
	int Result; // [esp+ECh] [ebp-8h]

	Result = 0;
	Result = g_CGremoryCaseDBSet.UpdateGremoryCaseItemRecv(

		lpMsg->AccountID,
		lpMsg->Name,
		lpMsg->btGCType,
		lpMsg->btItemType,
		lpMsg->wItemIndex,
		lpMsg->btLevel,
		lpMsg->dwSerial,
		lpMsg->lRecvDate,
		lpMsg->btUsedInfo);
	//_tagSDHP_ANS_GC_UPDATE::_tagSDHP_ANS_GC_UPDATE();
	//PBMSG_HEAD2::set(&pMsg.h, 243, 2, 20);
	pMsg.h.set((LPBYTE)&pMsg.h, 0xF3, 0x02, sizeof(_tagSDHP_ANS_GC_UPDATE));
	if (Result)
	{
		LogAddTD(
			"[GremoryCase][Error][ItemRecv][Result:%d] [%s][%s] %d %d %d %u %u",
			Result,
			lpMsg->AccountID,
			lpMsg->Name,
			lpMsg->btItemType,
			lpMsg->wItemIndex,
			lpMsg->btLevel,
			lpMsg->dwSerial,
			lpMsg->lRecvDate);
		pMsg.btResult = Result;
		pMsg.aIndex = lpMsg->aIndex;
		pMsg.btItemType = 0;
		pMsg.wItemIndex = 0;
		pMsg.btLevel = 0;
		pMsg.dwSerial = 0;
		pMsg.lRecvDate = 0;
		wsjServer.DataSend(aIndex, (char*)&pMsg, 20);
	}
	else
	{
		pMsg.btResult = 0;
		pMsg.aIndex = lpMsg->aIndex;
		pMsg.btItemType = lpMsg->btItemType;
		pMsg.wItemIndex = lpMsg->wItemIndex;
		pMsg.btLevel = lpMsg->btLevel;
		pMsg.dwSerial = lpMsg->dwSerial;
		pMsg.lRecvDate = lpMsg->lRecvDate;
		wsjServer.DataSend(aIndex, (char*)&pMsg, 20);
	}
}

//----- (0045CF00) --------------------------------------------------------
void GDReqGremoryCaseItemUpdateAndInsert(_tagSDHP_REQ_GC_UPDATE_INSERT *lpMsg, __int16 aIndex)
{
	_tagSDHP_ANS_GC_UPDATE_INSERT pMsg; // [esp+D0h] [ebp-58h]
	unsigned int dwSerial; // [esp+110h] [ebp-18h]
	int Result; // [esp+11Ch] [ebp-Ch]

	Result = 0;
	Result = g_CGremoryCaseDBSet.UpdateGremoryCase(

		lpMsg->AccountID,
		lpMsg->Name,
		lpMsg->btUpdate_GCType,
		lpMsg->btUpdate_ItemType,
		lpMsg->wUpdate_ItemIndex,
		lpMsg->btUpdate_Level,
		lpMsg->dwUpdate_Serial,
		lpMsg->lUpdate_RecvDate,
		lpMsg->btUpdate_UsedInfo);
	if (!Result)
	{
		dwSerial = 0;
		Result = g_CGremoryCaseDBSet.InsertGremoryCase(

			lpMsg->AccountID,
			lpMsg->Name,
			lpMsg->btGCType,
			lpMsg->btGiveType,
			lpMsg->btItemType,
			lpMsg->wItemIndex,
			lpMsg->btLevel,
			lpMsg->btDur,
			lpMsg->btSkill,
			lpMsg->btLuck,
			lpMsg->btOpt,
			lpMsg->btSetOpt,
			lpMsg->wNewOpt,
			lpMsg->btBonusSocketOpt,
			lpMsg->btSocketOpt,
			lpMsg->dwReceiptDuration,
			lpMsg->dwItemDuration,
			lpMsg->lRecvDate,
			lpMsg->lRecvExpireDate,
			lpMsg->lItemExpireDate,
			&dwSerial);
		if (!Result)
		{
			//_tagSDHP_ANS_GC_UPDATE_INSERT::_tagSDHP_ANS_GC_UPDATE_INSERT();
			//PBMSG_HEAD2::set(&pMsg.h, 243, 3, 56);
			pMsg.h.set((LPBYTE)&pMsg.h, 0xF3, 0x03, sizeof(_tagSDHP_ANS_GC_UPDATE_INSERT));
			pMsg.btUpdate_ItemType = lpMsg->btUpdate_ItemType;
			pMsg.wUpdate_ItemIndex = lpMsg->wUpdate_ItemIndex;
			pMsg.btUpdate_Level = lpMsg->btUpdate_Level;
			pMsg.dwUpdate_Serial = lpMsg->dwUpdate_Serial;
			pMsg.lUpdate_RecvDate = lpMsg->lUpdate_RecvDate;
			pMsg.aIndex = lpMsg->aIndex;
			pMsg.btGCType = lpMsg->btGCType;
			pMsg.btGiveType = lpMsg->btGiveType;
			pMsg.btItemType = lpMsg->btItemType;
			pMsg.wItemIndex = lpMsg->wItemIndex;
			pMsg.btLevel = lpMsg->btLevel;
			pMsg.btDur = lpMsg->btDur;
			pMsg.btSkill = lpMsg->btSkill;
			pMsg.btLuck = lpMsg->btLuck;
			pMsg.btOpt = lpMsg->btOpt;
			pMsg.btSetOpt = lpMsg->btSetOpt;
			pMsg.wNewOpt = lpMsg->wNewOpt;
			pMsg.btBonusSocketOpt = lpMsg->btBonusSocketOpt;
			memcpy(pMsg.btSocketOpt, lpMsg->btSocketOpt, 5u);
			pMsg.dwSerial = dwSerial;
			pMsg.lRecvDate = lpMsg->lRecvDate;
			pMsg.lRecvExpireDate = lpMsg->lRecvExpireDate;
			pMsg.lItemExpireDate = lpMsg->lItemExpireDate;
			wsjServer.DataSend(aIndex, (char*)&pMsg, 0x38);
		}
	}
}

void GDReqArcaBattleGuildJoinSelect(_tagPMSG_REQ_AB_GUILD_JOIN_SELECT_DS *lpMsg, int aIndex)
{
	_tagPMSG_ANS_ARCA_BATTLE_GUILD_JOIN_DS pMsg; // [esp+D0h] [ebp-24h]
	int bResult; // [esp+E0h] [ebp-14h]
	int iResult; // [esp+ECh] [ebp-8h]

	iResult = 0;
	bResult = gCArcaBattleDBSet.DBSelectArcaBattleGuildJoin(lpMsg->szGuildMaster, &iResult);
	if (bResult)
	{
		//_tagPMSG_ANS_ARCA_BATTLE_GUILD_JOIN_DS::_tagPMSG_ANS_ARCA_BATTLE_GUILD_JOIN_DS(&pMsg);
		//PBMSG_HEAD2::set(&pMsg.h, 248, 43, 8);
		pMsg.h.set((LPBYTE)&pMsg.h, 0xF8, 0x2B, sizeof(_tagPMSG_ANS_ARCA_BATTLE_GUILD_JOIN_DS));
		pMsg.btResult = iResult;
		pMsg.wNumber = lpMsg->wNumber;
		wsjServer.DataSend(aIndex, (char*)&pMsg, 8);
	}
	else
	{
		LogAddC(
			2,
			"[ArcaBattle] Error GDReqArcaBattleGuildJoinSelect() iResult : %d, CharName : %s, UserIndex : %d",
			iResult,
			lpMsg->szGuildMaster,
			lpMsg->wNumber);
	}
}

void GDReqArcaBattleGuildJoin(_tagPMSG_REQ_ARCA_BATTLE_GUILD_JOIN_DS *lpMsg, int aIndex)
{
	_tagPMSG_ANS_ARCA_BATTLE_GUILD_JOIN_DS pMsg; // [esp+D0h] [ebp-24h]
	int bResult; // [esp+E0h] [ebp-14h]
	int iResult; // [esp+ECh] [ebp-8h]

	iResult = 0;
	bResult = gCArcaBattleDBSet.DBInsertArcaBattleGuildJoin(

		lpMsg->szGuildMaster,
		lpMsg->szGuildName,
		lpMsg->dwGuild,
		&iResult);
	if (bResult)
	{
		//_tagPMSG_ANS_ARCA_BATTLE_GUILD_JOIN_DS::_tagPMSG_ANS_ARCA_BATTLE_GUILD_JOIN_DS(&pMsg);
		//PBMSG_HEAD2::set(&pMsg.h, 248, 49, 8);
		pMsg.h.set((LPBYTE)&pMsg.h, 0xF8, 0x31, sizeof(_tagPMSG_ANS_ARCA_BATTLE_GUILD_JOIN_DS));
		pMsg.btResult = iResult;
		pMsg.wNumber = lpMsg->wNumber;
		wsjServer.DataSend(aIndex, (char*)&pMsg, 8);
	}
	else
	{
		LogAddC(2, "[ArcaBattle] Error GDReqArcaBattleGuildJoin() iResult : %d, CharName : %s, UserIndex : %d",
			iResult,
			lpMsg->szGuildMaster,
			lpMsg->wNumber);
	}
}

//----- (00457FA0) --------------------------------------------------------
void GDReqArcaBattleGuildMemberJoin(_tagPMSG_REQ_ARCA_BATTLE_GUILD_MEMBER_JOIN_DS *lpMsg, int aIndex)
{
	_tagPMSG_ANS_ARCA_BATTLE_GUILD_MEMBER_JOIN_DS pMsg; // [esp+D0h] [ebp-24h]
	int bResult; // [esp+E0h] [ebp-14h]
	int iResult; // [esp+ECh] [ebp-8h]

	iResult = 0;
	bResult = gCArcaBattleDBSet.DBInsertArcaBattleGuildMemberJoin(

		lpMsg->szCharName,
		lpMsg->szGuildName,
		lpMsg->dwGuild,
		&iResult);
	if (bResult)
	{
		//_tagPMSG_ANS_ARCA_BATTLE_GUILD_MEMBER_JOIN_DS::_tagPMSG_ANS_ARCA_BATTLE_GUILD_MEMBER_JOIN_DS(&pMsg);
		//PBMSG_HEAD2::set(&pMsg.h, 248, 51, 8);
		pMsg.h.set((LPBYTE)&pMsg, 0xF8, 0x33, sizeof(_tagPMSG_ANS_ARCA_BATTLE_GUILD_MEMBER_JOIN_DS));
		pMsg.btResult = iResult;
		pMsg.wNumber = lpMsg->wNumber;
		wsjServer.DataSend(aIndex, (char*)&pMsg, 8);
	}
	else
	{
		LogAddC(2, "[ArcaBattle] Error GDReqArcaBattleGuildMemberJoin() iResult : %d, CharName : %s, UserIndex : %d",
			iResult,
			lpMsg->szCharName,
			lpMsg->wNumber);
	}
}

void GDReqInsertArcaBattleWinGuild(_tagPMSG_REQ_AB_WIN_GUILD_INFO_INSERT_DS *lpMsg)
{
	int iIDX; // [esp+D0h] [ebp-98h]
	int i; // [esp+DCh] [ebp-8Ch]
	_tagPMSG_ANS_AB_WIN_GUILD_INFO_DS pMsg; // [esp+E8h] [ebp-80h]
	int bResult; // [esp+15Ch] [ebp-Ch]

	bResult = gCArcaBattleDBSet.DBInsertArcaBattleWinGuild(

		lpMsg->m_stABWinGuildInfoDS,
		lpMsg->btGuildCnt);
	if (bResult)
	{
		//_tagPMSG_ANS_AB_WIN_GUILD_INFO_DS::_tagPMSG_ANS_AB_WIN_GUILD_INFO_DS(&pMsg);
		pMsg.btGuildCnt = lpMsg->btGuildCnt;
		for (i = 0; i < lpMsg->btGuildCnt; ++i)
		{
			memcpy(pMsg.m_stABWinGuildInfoDS[i].szGuildName, lpMsg->m_stABWinGuildInfoDS[i].szGuildName, 9u);
			pMsg.m_stABWinGuildInfoDS[i].dwGuild = lpMsg->m_stABWinGuildInfoDS[i].dwGuild;
			pMsg.m_stABWinGuildInfoDS[i].wObeliskGroup = lpMsg->m_stABWinGuildInfoDS[i].wObeliskGroup;
			pMsg.m_stABWinGuildInfoDS[i].wOccupyObelisk = lpMsg->m_stABWinGuildInfoDS[i].wOccupyObelisk;
		}
		//PBMSG_HEAD2::set(&pMsg.h, 248, 58, 108);
		pMsg.h.set((LPBYTE)&pMsg, 0xF8, 0x3A, sizeof(_tagPMSG_ANS_ARCA_BATTLE_GUILD_MEMBER_JOIN_DS));
		for (iIDX = 0; iIDX < 100; ++iIDX)
		{
			if (gSObj[iIDX].Connected)
			{
				if (gSObj[iIDX].iMapSvrGroup == lpMsg->wMapSvrNum)
					wsjServer.DataSend(iIDX, (char *)&pMsg.h, sizeof(_tagPMSG_ANS_ARCA_BATTLE_GUILD_MEMBER_JOIN_DS));
			}
		}
	}
	else
	{
		LogAddC(2, "[ArcaBattle] Error GDReqArcaBattleInfo()");
	}
}

void GDReqSelectArcaBattleWinGuildInfo(_tagPMSG_REQ_AB_WIN_GUILD_INFO_DS *lpMsg, int aIndex)
{
	_stABWinGuildInfoDS *v2; // ecx
	_stABWinGuildInfoDS *v3; // eax
	int i; // [esp+D0h] [ebp-128h]
	_tagPMSG_ANS_AB_WIN_GUILD_INFO_DS pMsg; // [esp+DCh] [ebp-11Ch]
	int bResult; // [esp+150h] [ebp-A8h]
	int iGuildCnt; // [esp+15Ch] [ebp-9Ch]
	_stABWinGuildInfoDS stABGuildInfo[5]; // [esp+168h] [ebp-90h]
	unsigned int dwDuration; // [esp+1D4h] [ebp-24h]
	unsigned __int16 wObeliskGroup; // [esp+1E0h] [ebp-18h]
	unsigned __int16 wObeliskAttr; // [esp+1ECh] [ebp-Ch]

	wObeliskAttr = 0;
	wObeliskGroup = 0;
	dwDuration = 0;
#pragma message ("FIX THIS FUCKIN VECTOR!!")
	//`vector constructor iterator'(stABGuildInfo, 0x14u, 5, _stABWinGuildInfoDS::_stABWinGuildInfoDS);
	iGuildCnt = 0;
	bResult = gCArcaBattleDBSet.DBSelectArcaBattleWinGuild(stABGuildInfo, &iGuildCnt);
	if (bResult && bResult != 2)
	{
		//_tagPMSG_ANS_AB_WIN_GUILD_INFO_DS::_tagPMSG_ANS_AB_WIN_GUILD_INFO_DS(&pMsg);
		for (i = 0; i < iGuildCnt; ++i)
		{
			v2 = &stABGuildInfo[i];
			v3 = &pMsg.m_stABWinGuildInfoDS[i];
			*v3->szGuildName = *v2->szGuildName;
			*&v3->szGuildName[4] = *&v2->szGuildName[4];
			*&v3->szGuildName[8] = *&v2->szGuildName[8];
			v3->dwGuild = v2->dwGuild;
			*&v3->wOccupyObelisk = *&v2->wOccupyObelisk;
		}
		pMsg.btGuildCnt = iGuildCnt;
		//PBMSG_HEAD2::set(&pMsg.h, 248, 58, 108);
		PHeadSubSetB((LPBYTE)&pMsg.h, 0xF8, 0x3A, sizeof(pMsg));
		wsjServer.DataSend(aIndex, (char*)&pMsg, 0x6C);
	}
}

//----- (00458590) --------------------------------------------------------
void GDReqArcaBattleEnter(_tagPMSG_REQ_ARCA_BATTLE_ENTER_DS *lpMsg, int aIndex)
{
	_tagPMSG_ANS_ARCA_BATTLE_ENTER_DS pMsg; // [esp+D0h] [ebp-24h]
	int bResult; // [esp+E0h] [ebp-14h]
	int iResult; // [esp+ECh] [ebp-8h]

	iResult = 0;
	bResult = gCArcaBattleDBSet.DBIsArcaBattleEnter(lpMsg->szCharName, &iResult);
	if (bResult)
	{
		//_tagPMSG_ANS_ARCA_BATTLE_ENTER_DS::_tagPMSG_ANS_ARCA_BATTLE_ENTER_DS(&pMsg);
		//PBMSG_HEAD2::set(&pMsg.h, 248, 53, 8);
		PHeadSubSetB((LPBYTE)&pMsg.h, 0xF8, 0x35, sizeof(pMsg));
		pMsg.btResult = iResult;
		pMsg.wNumber = lpMsg->wNumber;
		pMsg.btEnterSeq = lpMsg->btEnterSeq;
		wsjServer.DataSend(aIndex, (char*)&pMsg, 8);
	}
	else
	{
		LogAddC(
			2,
			"[ArcaBattle] Error GDReqArcaBattleEnter() iResult : %d, CharName : %s, UserIndex : %d",
			iResult,
			lpMsg->szCharName,
			lpMsg->wNumber);
	}
}
void GDReqArcaBattleGuildGroupNum(_tagPMSG_REQ_ARCA_BATTLE_GROUP_NUM_DS *lpMsg, int aIndex)
{
	_tagPMSG_ANS_ARCA_BATTLE_GROUP_NUM_DS pMsg; // [esp+D0h] [ebp-24h]
	int bResult; // [esp+E0h] [ebp-14h]
	int iResult; // [esp+ECh] [ebp-8h]

	iResult = 0;
	bResult = gCArcaBattleDBSet.DBSelectArcaBattleGuildGroupNum(lpMsg->szCharName, &iResult);
	if (bResult)
	{
		if (bResult != 2)
		{
			if (iResult)
			{
				//_tagPMSG_ANS_ARCA_BATTLE_GROUP_NUM_DS::_tagPMSG_ANS_ARCA_BATTLE_GROUP_NUM_DS(&pMsg);
				//PBMSG_HEAD2::set(&pMsg.h, 248, 60, 8);
				PHeadSubSetB((LPBYTE)&pMsg.h, 0xF8, 0x3C, sizeof(pMsg));
				pMsg.wGroupNum = iResult;
				pMsg.wNumber = lpMsg->wNumber;
				wsjServer.DataSend(aIndex, (char*)&pMsg, 8);
			}
			else
			{
				LogAddC(
					2,
					"[ArcaBattle] (iResult == 0) Error GDReqArcaBattleGuildGroupNum() GuildName : %s, UserIndex : %d",
					lpMsg->szCharName,
					lpMsg->wNumber);
			}
		}
	}
	else
	{
		LogAddC(
			2,
			"[ArcaBattle] Error GDReqArcaBattleGuildGroupNum() GuildName : %s, UserIndex : %d",
			lpMsg->szCharName,
			lpMsg->wNumber);
	}
}

void GDReqArcaBattleInfoDelete()
{
	int bResult; // [esp+D0h] [ebp-14h]
	int iResult; // [esp+DCh] [ebp-8h]

	iResult = 0;
	bResult = gCArcaBattleDBSet.DBDeleteArcaBattleInfo();
	if (!bResult)
		LogAddC(2, "[ArcaBattle] Error GDReqArcaBattleInfoDelete()");
}

//----- (004588E0) --------------------------------------------------------
void GDReqSelectArcaBattleProc(_tagPMSG_REQ_ARCA_BATTLE_PROC_STATE_DS *lpMsg, int aIndex)
{
	_tagPMSG_ANS_ARCA_BATTLE_PROC_STATE_DS pMsgSend; // [esp+D0h] [ebp-24h]
	int bResult; // [esp+E0h] [ebp-14h]
	int iProcState; // [esp+ECh] [ebp-8h]

	iProcState = 0;
	bResult = gCArcaBattleDBSet.DBSelectArcaBattleProc(&iProcState);
	if (bResult)
	{
		//PBMSG_HEAD2::set(&pMsgSend.h, 248, 64, 5);
		PHeadSubSetB((LPBYTE)&pMsgSend.h, 0xF8, 0x40, sizeof(pMsgSend));
		pMsgSend.btProcState = iProcState;
		wsjServer.DataSend(aIndex, (char*)&pMsgSend.h, 5);
	}
}

//----- (004589B0) --------------------------------------------------------
void GDReqArcaBattleJoinMemberUnder(_tagPMSG_REQ_AB_JOIN_MEMBER_UNDER_DS *lpMsg)
{
	_stGuildUnderMember *v1; // ecx
	_stGuildUnderMember *v2; // eax
	int iIDX; // [esp+D0h] [ebp-C0h]
	int i; // [esp+DCh] [ebp-B4h]
	int bResult; // [esp+E8h] [ebp-A8h]
	char btGuildCnt; // [esp+F7h] [ebp-99h]
	_stGuildUnderMember GuildMemberCnt[6]; // [esp+100h] [ebp-90h]
	_tagPMSG_ANS_AB_JOIN_MEMBER_UNDER_DS pMsgSend; // [esp+144h] [ebp-4Ch]

	//PBMSG_HEAD2::set(&pMsgSend.h, 248, 66, 65);
	PHeadSubSetB((LPBYTE)&pMsgSend.h, 0xF8, 0x42, sizeof(pMsgSend));
	btGuildCnt = 0;
	bResult = gCArcaBattleDBSet.DBSelectArcaBattleJoinMemberUnder(GuildMemberCnt, &btGuildCnt);
	if (bResult)
	{
		pMsgSend.btGuildCnt = btGuildCnt;
		for (i = 0; i < 6; ++i)
		{
			v1 = &GuildMemberCnt[i];
			v2 = &pMsgSend.GuildMemberCnt[i];
			*&v2->btGuildMemberCnt = *&v1->btGuildMemberCnt;
			*&v2->szGuildNames[3] = *&v1->szGuildNames[3];
			*&v2->szGuildNames[7] = *&v1->szGuildNames[7];
		}
		for (iIDX = 0; iIDX < 100; ++iIDX)
		{
			if (gSObj[iIDX].Connected)
			{
				if (gSObj[iIDX].iMapSvrGroup == lpMsg->wMapSvrNum)
					wsjServer.DataSend(iIDX, (char*)&pMsgSend.h, 0x41);
			}
		}
	}
	else
	{
		LogAddC(2, "[ArcaBattle] Error GDReqArcaBattleJoinMemberUnder()");
	}
}
// 6B906E4: using guessed type int dword_6B906E4[];

//----- (00458B80) --------------------------------------------------------
void GDReqABLessGuildMemberCancel(_tagPMSG_REQ_AB_JOIN_CANCEL_DS *lpMsg)
{
	int iIDX; // [esp+D0h] [ebp-68h]
	int bResult; // [esp+DCh] [ebp-5Ch]
	_tagPMSG_ANS_AB_JOIN_CANCEL_DS pMsg; // [esp+E8h] [ebp-50h]
	char btGuildCnt; // [esp+12Fh] [ebp-9h]

	btGuildCnt = 0;
	//PBMSG_HEAD2::set(&pMsg.h, 248, 68, 59);
	pMsg.h.set((LPBYTE)&pMsg, 0xF8, 0x44, sizeof(_tagPMSG_ANS_AB_JOIN_CANCEL_DS));
	bResult = gCArcaBattleDBSet.DBSelectArcaBattleCancelGuild(

		pMsg.CancelGuildNames,
		lpMsg->btMinGuildMemNum,
		&btGuildCnt);
	if (bResult)
	{
		pMsg.btGuildCnt = btGuildCnt;
		for (iIDX = 0; iIDX < 100; ++iIDX)
		{
			if (gSObj[iIDX].Connected)
			{
				if (gSObj[iIDX].iMapSvrGroup == lpMsg->wMapSvrNum)
					wsjServer.DataSend(iIDX, (char *)&pMsg.h, 0x3B);
			}
		}
	}
	else
	{
		LogAddC(2, "[ArcaBattle] Error GDReqABLessGuildMemberCancel()");
	}
}
// 6B906E4: using guessed type int dword_6B906E4[];

//----- (00458CC0) --------------------------------------------------------
void GDReqRegisteredMemberCnt(_tagPMSG_REQ_AB_REG_MEMBER_CNT_DS *lpMsg, int aIndex)
{
	int bResult; // [esp+D0h] [ebp-18h]
	_tagPMSG_ANS_AB_REG_MEMBER_CNT_DS pMsg; // [esp+DCh] [ebp-Ch]

	bResult = gCArcaBattleDBSet.DBSelectABRegisteredMemberCnt(lpMsg->dwGuild, &pMsg.btRegMemCnt);
	if (bResult)
	{
		pMsg.wNumber = lpMsg->wNumber;
		//PBMSG_HEAD2::set(&pMsg.h, 0xF8, 0x46, 8);
		pMsg.h.set((LPBYTE)&pMsg.h, 0xF8, 0x46, sizeof(_tagPMSG_ANS_AB_REG_MEMBER_CNT_DS));
		wsjServer.DataSend(aIndex, (char*)&pMsg, 8);
	}
	else
	{
		LogAddC(2, "[ArcaBattle] Error GDReqRegisteredMemberCnt()");
	}
}

//----- (00458D90) --------------------------------------------------------
void GDReqRemoveAllGuildBuffMultiCast(_tagPMSG_REQ_REMOVE_ALL_GUILD_BUFF_DS *lpMsg)
{
	int iIDX; // [esp+D0h] [ebp-24h]
	_tagPMSG_ANS_REMOVE_GUILD_BUFF_DS pMsgSend; // [esp+DCh] [ebp-18h]

	//PBMSG_HEAD2::set(&pMsgSend.h, 248, 72, 4);
	pMsgSend.h.set((LPBYTE)&pMsgSend.h, 0xF8, 0x48, sizeof(_tagPMSG_ANS_REMOVE_GUILD_BUFF_DS));
	for (iIDX = 0; iIDX < 100; ++iIDX)
	{
		if (gSObj[iIDX].Connected)
		{
			if (gSObj[iIDX].iMapSvrGroup == lpMsg->wMapSvrNum)
				wsjServer.DataSend(iIDX, (char*)&pMsgSend.h, 4);
		}
	}
}
// 6B906E4: using guessed type int dword_6B906E4[];

//----- (00458E70) --------------------------------------------------------
void GDReqRemoveGuildBuffMultiCast(_tagPMSG_REQ_REMOVE_GUILD_BUFF_DS *lpMsg)
{
	int iIDX; // [esp+D0h] [ebp-24h]
	_tagPMSG_ANS_REMOVE_GUILD_BUFF_DS pMsgSend; // [esp+DCh] [ebp-18h]

	pMsgSend.szGuildName[8] = 0;
	memcpy(pMsgSend.szGuildName, lpMsg->szGuildName, 8u);
	//PBMSG_HEAD2::set(&pMsgSend.h, 248, 76, 13);
	pMsgSend.h.set((LPBYTE)&pMsgSend.h, 0xF8, 0x4C, sizeof(_tagPMSG_ANS_REMOVE_GUILD_BUFF_DS));
	for (iIDX = 0; iIDX < 100; ++iIDX)
	{
		if (gSObj[iIDX].Connected)
		{
			if (gSObj[iIDX].iMapSvrGroup == lpMsg->wMapSvrNum)
				wsjServer.DataSend(iIDX, (char*)&pMsgSend.h, 13);
		}
	}
}

void GDReqArcaBattleMarkReg(BYTE *lpRecv, int aIndex)
{
	_tagPMSG_ANS_ARCA_BATTLE_MARK_REG_DS pMsg; // [esp+D0h] [ebp-24h]
	int bResult; // [esp+E0h] [ebp-14h]
	_tagPMSG_REQ_ARCA_BATTLE_MARK_REG_DS *lpMsg; // [esp+ECh] [ebp-8h]

	lpMsg = (_tagPMSG_REQ_ARCA_BATTLE_MARK_REG_DS *)lpRecv;
	bResult = gCArcaBattleDBSet.DBInsertArcaBattleRegMark(
		lpMsg->szGuildName,
		lpMsg->dwGuildNum,
		lpMsg->szGuildMaster,
		lpMsg->dwMarkCnt);
	if (!bResult)
	{
		LogAddC(2, "[ArcaBattle] Error GDReqArcaBattleMarkReg() GuildName[%s] GuildNum[%d] GuildMater[%s] MarkCnt[%d]",
			lpMsg->szGuildName,
			lpMsg->dwGuildNum,
			lpMsg->szGuildMaster,
			lpMsg->dwMarkCnt);
		//_tagPMSG_ANS_ARCA_BATTLE_MARK_REG_DS::_tagPMSG_ANS_ARCA_BATTLE_MARK_REG_DS(&pMsg);
		//PBMSG_HEAD2::set(&pMsg.h, 248, 80, 8);
		pMsg.h.set((LPBYTE)&pMsg.h, 0xF8, 0x50, sizeof(_tagPMSG_ANS_ARCA_BATTLE_MARK_REG_DS));
		pMsg.wNumber = lpMsg->wNumber;
		pMsg.btResult = bResult;
		wsjServer.DataSend(aIndex, (char*)&pMsg, 8);
	}
}

void GDReqArcaBattleRank(BYTE *lpRecv, int aIndex)
{
	int bTopRank; // [esp+DCh] [ebp-128h]
	_tagPMSG_ANS_ARCA_BATTLE_MARK_RANK_DS pMsg; // [esp+E8h] [ebp-11Ch]
	unsigned int dwMarkCnt; // [esp+160h] [ebp-A4h]
	unsigned int dwGuildNumber; // [esp+16Ch] [ebp-98h]
	char btMyGuildRank; // [esp+17Bh] [ebp-89h]
	char btGuildCnt; // [esp+187h] [ebp-7Dh]
	_stArcaBattleMarkTopRank ArcaBattleMarkTopRank[6]; // [esp+190h] [ebp-74h]
	_tagPMSG_REQ_ARCA_BATTLE_MARK_RANK_DS *lpMsg; // [esp+1F8h] [ebp-Ch]

	lpMsg = (_tagPMSG_REQ_ARCA_BATTLE_MARK_RANK_DS *)lpRecv;
#pragma message ("FIX THIS FUCKIN VECTOR!!")
	//`vector constructor iterator'(ArcaBattleMarkTopRank, 0x10u, 6, _stArcaBattleMarkTopRank::_stArcaBattleMarkTopRank);
	btGuildCnt = 0;
	btMyGuildRank = 0;
	dwGuildNumber = lpMsg->dwGuildNum;
	dwMarkCnt = 0;
	//_tagPMSG_ANS_ARCA_BATTLE_MARK_RANK_DS::_tagPMSG_ANS_ARCA_BATTLE_MARK_RANK_DS(&pMsg);
	bTopRank = gCArcaBattleDBSet.DBSelectArcaBattleTopRank(ArcaBattleMarkTopRank, &btGuildCnt);
	if (gCArcaBattleDBSet.DBSelectArcaBattleMyGuildRank(dwGuildNumber, &btMyGuildRank, &dwMarkCnt)
		&& bTopRank)
	{
		//PBMSG_HEAD2::set(&pMsg.h, 248, 82, 112);
		pMsg.h.set((LPBYTE)&pMsg.h, 0xF8, 0x52, sizeof(_tagPMSG_ANS_ARCA_BATTLE_MARK_RANK_DS));
		pMsg.wNumber = lpMsg->wNumber;
		pMsg.btRank = btMyGuildRank;
		pMsg.dwMarkCnt = dwMarkCnt;
		pMsg.btGuildCnt = btGuildCnt;
		memcpy(pMsg.ArcaBattleMarkTopRank, ArcaBattleMarkTopRank, 0x60u);
		wsjServer.DataSend(aIndex, (char*)&pMsg, 0x70);
	}
	else
	{
		//PBMSG_HEAD2::set(&pMsg.h, 248, 82, 112);
		pMsg.h.set((LPBYTE)&pMsg.h, 0xF8, 0x50, sizeof(_tagPMSG_ANS_ARCA_BATTLE_MARK_RANK_DS));
		pMsg.wNumber = lpMsg->wNumber;
		wsjServer.DataSend(aIndex, (char*)&pMsg, 0x70);
	}
}

void GDReqArcaBattleMarkRegDel(BYTE *lpRecv)
{
	int bResult; // [esp+D0h] [ebp-14h]
	_tagPMSG_REQ_ARCA_BATTLE_MARK_REG_DEL_DS *lpMsg; // [esp+DCh] [ebp-8h]

	lpMsg = (_tagPMSG_REQ_ARCA_BATTLE_MARK_REG_DEL_DS *)lpRecv;
	bResult = gCArcaBattleDBSet.DBDeleteArcaBattleMarkReg(*(lpRecv + 2));
	if (!bResult)
		LogAddC(2, "[ArcaBattle] Error GDReqArcaBattleMarkRegDel() User Index [%d]", lpMsg->wNumber);
}

void GDReqArcaBattleIsTopRank(BYTE *lpRecv, int aIndex)
{
	_tagPMSG_ANS_ARCA_BATTLE_GUILD_JOIN_DS pMsg; // [esp+D0h] [ebp-24h]
	int iResult; // [esp+E0h] [ebp-14h]
	_tagPMSG_REQ_ARCA_BATTLE_IS_TOP_RANK *lpMsg; // [esp+ECh] [ebp-8h]


	lpMsg = (_tagPMSG_REQ_ARCA_BATTLE_IS_TOP_RANK *)lpRecv;
	iResult = gCArcaBattleDBSet.DBSelectArcaBattleIsTopRank(*(lpRecv + 2));
	//_tagPMSG_ANS_ARCA_BATTLE_GUILD_JOIN_DS::_tagPMSG_ANS_ARCA_BATTLE_GUILD_JOIN_DS(&pMsg);
	//PBMSG_HEAD2::set(&pMsg.h, 248, 43, 8);
	pMsg.h.set((LPBYTE)&pMsg.h, 0xF8, 0x2B, sizeof(_tagPMSG_ANS_ARCA_BATTLE_GUILD_JOIN_DS));
	pMsg.btResult = iResult;
	pMsg.wNumber = lpMsg->wNumber;
	wsjServer.DataSend(aIndex, (char*)&pMsg, 8);
}

//----- (00459A70) --------------------------------------------------------
void GDReqArcaBattleAllGuildMarkCnt(int aIndex)
{
	_tagPMSG_ANS_ALL_GUILD_MARK_CNT_DS pMsg;
	int iGuildCnt;
	int size;
	char buf; 
	char dst;
	int v6; 
	_stABAllGuildMark stABGuildMark[250];

	buf = 0;
	memset(&dst, 0, 0x1067u);
	size = 0;
	iGuildCnt = 0;
	gCArcaBattleDBSet.DBSelectArcaBattleAllGuildMark(stABGuildMark, &iGuildCnt);
	size = 8;
	pMsg.wGuildCnt = iGuildCnt;
	memcpy(&v6, &stABGuildMark, 16 * iGuildCnt);
	size += 16 * iGuildCnt;
	//PWMSG_HEAD2::set(&pMsg.h.c, 248, 252, size);
	pMsg.h.set((LPBYTE)&pMsg.h.c, 0xF8, 0xFC, size);
	memcpy(&buf, &pMsg.h.c, 8u);
	wsjServer.DataSend(aIndex, &buf, size);
}

void GDReqInsertArcaBattleProc(BYTE *lpRecv)
{
	int iIDX; // [esp+D0h] [ebp-30h]
	_tagPMSG_ANS_ARCA_BATTLE_PROC_STATE_DS pMsgSend; // [esp+E8h] [ebp-18h]
	_tagPMSG_REQ_AB_PROC_INSERT_DS *lpMsg; // [esp+F8h] [ebp-8h]

	if (lpRecv)
	{
		lpMsg = (_tagPMSG_REQ_AB_PROC_INSERT_DS *)lpRecv;
		//PBMSG_HEAD2::set(&pMsgSend.h, 248, 64, 5);
		pMsgSend.h.set((LPBYTE)&pMsgSend.h, 0xF8, 0x40, sizeof(_tagPMSG_REQ_AB_PROC_INSERT_DS));
		pMsgSend.btProcState = lpMsg->btProcState;
		if (gCArcaBattleDBSet.DBInsertArcaBattleProc(pMsgSend.btProcState))
		{
			for (iIDX = 0; iIDX < 100; ++iIDX)
			{
				if (gSObj[iIDX].Connected)
				{
					if (gSObj[iIDX].iMapSvrGroup == lpMsg->wMapSvrNum)
						wsjServer.DataSend(iIDX, (char *)&pMsgSend.h, 5);
				}
			}
		}
	}
}

void GDReqAcheronPlayProc(BYTE *lpRecv)
{
	int iIDX; // [esp+D0h] [ebp-24h]
	_tagPMSG_ANS_AE_PLAY_DS pMsgSend; // [esp+DCh] [ebp-18h]
	_tagPMSG_REQ_AE_PLAY_DS *lpMsg; // [esp+ECh] [ebp-8h]

	if (lpRecv)
	{
		lpMsg = (_tagPMSG_REQ_AE_PLAY_DS *)lpRecv;
		/*_tagPMSG_ANS_AE_PLAY_DS::_tagPMSG_ANS_AE_PLAY_DS(&pMsgSend);
		PBMSG_HEAD2::set(&pMsgSend.h, 248, 241, 5);*/
		pMsgSend.h.set((LPBYTE)&pMsgSend.h, 0xF8, 0xF1, sizeof(_tagPMSG_ANS_AE_PLAY_DS));
		pMsgSend.btPlay = lpMsg->btPlay;
		for (iIDX = 0; iIDX < 100; ++iIDX)
		{
			if (gSObj[iIDX].Connected)
			{
				if (gSObj[iIDX].iMapSvrGroup == lpMsg->wMapSvrNum)
					wsjServer.DataSend(iIDX, (char *)&pMsgSend.h, 5);
			}
		}
	}
}

void GD_Save_ChaosCastle_KillPoint(_tagPMSG_REQ_SAVE_CHAOSCASTLE_KILLPOINT *lpRecv, int aIndex)
{
	int subResult; // [esp+DCh] [ebp-3Ch]
	int TotalPoint; // [esp+E8h] [ebp-30h]
	int CurrentPoint; // [esp+F4h] [ebp-24h]
	SDHP_ANS_KILLPOINT_RESULT pMsg; // [esp+100h] [ebp-18h]

	if (lpRecv)
	{
		memset(&pMsg.h, 0, 0x14u);
		CurrentPoint = 0;
		TotalPoint = 0;
		subResult = 0;
		g_CCFDbSet.Save_ChaosCastle_KillPoint(

			lpRecv->szCharName,
			lpRecv->nPoint,
			lpRecv->nCatleIndex,
			&subResult,
			&CurrentPoint,
			&TotalPoint);
		//PHeadSubSetB(&pMsg.h, 249, 1, 20);
		PHeadSubSetB((LPBYTE)&pMsg, 0xF9, 0x01, sizeof(pMsg));
		pMsg.nResult = subResult;
		pMsg.nIndex = lpRecv->nIndex;
		pMsg.nCurrentPoint = CurrentPoint;
		pMsg.nTotalPoint = TotalPoint;
		wsjServer.DataSend(aIndex, (char*)&pMsg, pMsg.h.size);
	}
}

void GD_CCF_Point_Save(SDHP_REQ_CCF_RESULT *lpRecv)
{
	if (lpRecv)
	{
		g_CCFDbSet.Save_CCF_Point(lpRecv->szCharName, lpRecv->nPoint, lpRecv->byCCFType);
		LogAddTD(
			"lpRecv->szCharName %s ,lpRecv->nPoint %d,lpRecv->byCCFType %d",
			lpRecv->szCharName,
			lpRecv->nPoint,
			lpRecv->byCCFType);
	}
}

//----- (0045A320) --------------------------------------------------------
void GD_CCF_RankigReq(SDHP_REQ_CCF_RANKING_REQ *lpRecv, int aIndex)
{
	char btUserCount; // [esp+DFh] [ebp-755h]
	int lOfs; // [esp+E8h] [ebp-74Ch]
	char sendbuf[1024]; // [esp+F4h] [ebp-740h]
	_tagPMSG_ANS_CCF_RANKING pAnsMsg; // [esp+4FCh] [ebp-338h]
	_stCCFRankingInfo CCFRankingInfo[50]; // [esp+50Ch] [ebp-328h]

	if (lpRecv)
	{
#pragma message ("FIX THIS FUCKIN VECTOR!!")
		//`vector constructor iterator'(CCFRankingInfo, 0x10u, 50, _stCCFRankingInfo::_stCCFRankingInfo);
			//_tagPMSG_ANS_CCF_RANKING::_tagPMSG_ANS_CCF_RANKING(&pAnsMsg);
		sendbuf[0] = 0;
		memset(&sendbuf[1], 0, 0x3FFu);
		btUserCount = 0;
		lOfs = 5;
		if (!g_CCFDbSet.ReqCCFRanking(

			CCFRankingInfo,
			lpRecv->byRankingType,
			&btUserCount,
			lpRecv->nServerCategory))
		{
			memcpy(&sendbuf[lOfs], CCFRankingInfo, 16 * btUserCount);
			lOfs += 16 * btUserCount;
			//PWMSG_HEAD::set(&pAnsMsg.h, 245, lOfs);
			pAnsMsg.h.set((LPBYTE)&pAnsMsg.h, 0xE9, lOfs);
			pAnsMsg.byUserCnt = btUserCount;
			memcpy(sendbuf, &pAnsMsg.h, 5u);
			wsjServer.DataSend(aIndex, sendbuf, lOfs);
		}
	}
}

//----- (0045A640) --------------------------------------------------------
void GD_CCF_Info_AllSend(SDHP_SEND_CCF_INFO *lpRecv)
{
	int i; // [esp+D0h] [ebp-20h]
	PMSG_CCF_SEND_ALL_INFO pMsg; // [esp+DCh] [ebp-14h]

	if (lpRecv)
	{
		memset(&pMsg.h, 0, 0x10u);
		//PHeadSubSetB(&pMsg.h, 249, 164, 16);
		PHeadSubSetB((LPBYTE)&pMsg, 0xF9, 0xA4, sizeof(pMsg));
		pMsg.nMin = lpRecv->nMin;
		pMsg.nType = lpRecv->nType;
		pMsg.wMapSvrNum = lpRecv->wMapSvrNum;
		LogAddTD(
			"[ChaosCastleFinal][GD_CCF_Info_AllSend] Min :%d, Type:%d ,MapSvr %d ",
			pMsg.nMin,
			pMsg.nType,
			pMsg.wMapSvrNum);
		for (i = 0; i < 100; ++i)
		{
			if (gSObj[i].Connected)
			{
				if (gSObj[i].iMapSvrGroup == pMsg.wMapSvrNum)
					wsjServer.DataSend(i, (char *)&pMsg.h, 16);
			}
		}
	}
}
// 6B906E4: using guessed type int dword_6B906E4[];

//----- (0045A770) --------------------------------------------------------
void GD_CCF_GetPermission(SDHP_REQ_CCF_GETPERMISSION *lpRecv, int aIndex)
{
	SDHP_ANS_CCF_GETPERMISSION pMsg; // [esp+D0h] [ebp-1Ch]
	int nReturn; // [esp+E4h] [ebp-8h]

	nReturn = -1;
	memset(&pMsg.h, 0, 0xCu);
	g_CCFDbSet.GetPermission(lpRecv->szCharName, lpRecv->byCCFType, &nReturn);
	//PHeadSubSetB(&pMsg.h, 249, 163, 12);
	PHeadSubSetB((LPBYTE)&pMsg, 0xF9, 0xA3, sizeof(pMsg));
	pMsg.nResult = nReturn;
	pMsg.nIndex = lpRecv->nIndex;
	wsjServer.DataSend(aIndex, (char*)&pMsg, pMsg.h.size);
}


void GD_CCFRankRenew(SDHP_RENEW_RANKING *lpRecv)
{
	int nReturn; // [esp+D0h] [ebp-8h]

	if (lpRecv)
	{
		nReturn = 0;
		nReturn = g_CCFDbSet.CCFRankRenew(lpRecv->byCCFType);
		LogAddTD(
			"[ChaosCastleFinal][Ranking][Renew] lpRecv->byCCFtype %d CCFRankRenew Retrun %d",
			lpRecv->byCCFType,
			nReturn);
	}
}

void GDReqUBFAccountUserInfo(PMSG_REQ_UBF_ACCOUNT_USERINFO *lpRecv, int aIndex)
{
	PMSG_ANS_UBF_ACCOUNT_USERINFO pMsg; // [esp+DCh] [ebp-14h]

	if (lpRecv)
	{
		memset(&pMsg.h, 0, 0x10u);
		pMsg.iUserIndex = lpRecv->iUserIndex;
		pMsg.btObserverMode = lpRecv->btObserverMode;
		pMsg.btResult = g_CCFDbSet.GetUBFAccountUserInfo(

			lpRecv->szAccountID,
			lpRecv->szName,
			lpRecv->iServerCode,
			lpRecv->IsUnityBattleFieldServer,
			&pMsg);
		//PHeadSubSetB(&pMsg.h, 250, 1, 16);
		PHeadSubSetB((LPBYTE)&pMsg, 0xFA, 1, sizeof(pMsg));
		wsjServer.DataSend(aIndex, (char*)&pMsg, sizeof(pMsg));
	}
}

//----- (0045DD50) --------------------------------------------------------
void GDReqUBFAccountUserRegister(PMSG_UBF_REGISTER_ACCOUNT_USER *lpRecv, int aIndex)
{
	PMSG_UBF_REGISTER_ACCOUNT_USER_RESULT pMsg; // [esp+D0h] [ebp-1Ch]
	char btRet; // [esp+E7h] [ebp-5h]

	if (lpRecv)
	{
		btRet = 0;
		memset(&pMsg.h, 0, 0xCu);
		pMsg.iUserIndex = lpRecv->iUserIndex;
		btRet = g_CCFDbSet.RegisterUBFAccountUser(

			lpRecv->szAccountID,
			lpRecv->szName,
			lpRecv->szBattleFieldName,
			lpRecv->ServerCode,
			lpRecv->btRegisterState,
			lpRecv->btRegisterMonth,
			lpRecv->btRegisterDay,
			&pMsg.btResult,
			&pMsg.nLeftSec);
		//PHeadSubSetB(&pMsg.h, 250, 2, 12);
		PHeadSubSetB((LPBYTE)&pMsg, 0xFA, 2, sizeof(pMsg));
		wsjServer.DataSend(aIndex, (char*)&pMsg, 12);
	}
}

//----- (0045DE50) --------------------------------------------------------
void GDReqUBFAccountUserCopy(PMSG_UBF_ACCOUNT_USER_COPY *lpRecv, int aIndex)
{
	PMSG_UBF_ACCOUNT_USER_COPY_RESULT pMsg; // [esp+D0h] [ebp-54h]
	char subResult; // [esp+E7h] [ebp-3Dh]
	int btRet; // [esp+F0h] [ebp-34h]
	char szCharName[11]; // [esp+FCh] [ebp-28h]
	char szId[11]; // [esp+110h] [ebp-14h]

	if (lpRecv)
	{
		szId[10] = 0;
		memcpy(szId, lpRecv->szAccountID, 0xAu);
		szCharName[10] = 0;
		memcpy(szCharName, lpRecv->szName, 0xAu);
		btRet = 0;
		subResult = 0;
		if (lpRecv->btPromotionMode == 1)
			btRet = g_CCFDbSet.CopyUBFAccountUserPromotionMode(

				szId,
				szCharName,
				lpRecv->ServerCode,
				&subResult);
		else
			btRet = g_CCFDbSet.CopyUBFAccountUser(szId, szCharName, lpRecv->ServerCode, &subResult);
		memset(&pMsg.h, 0, 0xCu);
		pMsg.iUserIndex = lpRecv->iUserIndex;
		pMsg.btResult = btRet;
		pMsg.btSubResult = subResult;
		//PHeadSubSetB(&pMsg.h, 250, 3, 12);
		PHeadSubSetB((LPBYTE)&pMsg, 0xFA, 2, sizeof(pMsg));
		wsjServer.DataSend(aIndex, (char*)&pMsg, sizeof(pMsg));
	}
}

//----- (0045DFF0) --------------------------------------------------------
void GDReqUBFCopyPetItemInfo(BYTE *lpRecv)
{
	unsigned int dwtemp; // [esp+D0h] [ebp-38h]
	int n; // [esp+DCh] [ebp-2Ch]
	int MsgOfs; // [esp+E8h] [ebp-20h]
	Request_PetItem_Info *lpItem; // [esp+F4h] [ebp-14h]
	SDHP_REQUEST_PETITEM_INFO *lpHeader; // [esp+100h] [ebp-8h]

	MsgOfs = 0;
	lpHeader = (SDHP_REQUEST_PETITEM_INFO *)lpRecv;
	if (lpRecv[19] >= 1)
	{
		LogAdd("Ǫ ߆Lƛ copy count %d", lpHeader->nCount);
		MsgOfs += 24;
		lpItem = (Request_PetItem_Info *)&lpRecv[MsgOfs];
		for (n = 0; n < lpHeader->nCount; ++n)
		{
			dwtemp = lpItem[n].nSerial;
			PetDBSet.UBFCopyPetInfo(lpItem[n].nSerial, lpHeader->ServerCode);
		}
	}
}

//----- (0045E0C0) --------------------------------------------------------
void GDReqUBFWinInfo(PMSG_REQ_UBF_GET_REWARD *lpRecv, int aIndex)
{
	PMSG_ANS_UBF_GET_REWARD pMsg; // [esp+DCh] [ebp-2Ch]

	if (lpRecv)
	{
		memset(&pMsg.h, 0, 0x24u);
		pMsg.iUserIndex = lpRecv->iUserIndex;
		g_CCFDbSet.GetWinAllRewardInfoOfUBF(

			lpRecv->szName,
			lpRecv->iServerCode,
			lpRecv->btServerKind,
			lpRecv->btContentsType,
			&pMsg);
		//PHeadSubSetB(&pMsg.h, 250, 6, 36);
		PHeadSubSetB((LPBYTE)&pMsg, 0xFA, 0x06, sizeof(pMsg));
		wsjServer.DataSend(aIndex, (char*)&pMsg, sizeof(pMsg));

	}
}

//----- (0045E1C0) --------------------------------------------------------
void GDReqSetReceivedWinnerItem(PMSG_REQ_UBF_SET_RECEIVED_REWARD *lpRecv, int aIndex)
{
	char btSubResult; // [esp+D3h] [ebp-25h]
	int bReturn; // [esp+DCh] [ebp-1Ch]
	PMSG_ANS_UBF_SET_RECEIVED_REWARD pMsg; // [esp+E8h] [ebp-10h]

	if (lpRecv)
	{
		memset(&pMsg.h, 0, 0xCu);
		pMsg.iUserIndex = lpRecv->iUserIndex;
		bReturn = g_CCFDbSet.SetReceivedWinnerItemOfUBF(

			lpRecv->szName,
			lpRecv->iServerCode,
			lpRecv->btReceivedReward,
			&btSubResult);
		pMsg.btReturn = bReturn;
		pMsg.btSubReturn = btSubResult;
		//PHeadSubSetB(&pMsg.h, 250, 5, 12);
		PHeadSubSetB((LPBYTE)&pMsg, 0xFA, 0x05, sizeof(pMsg));
		wsjServer.DataSend(aIndex, (char*)&pMsg, sizeof(pMsg));
	}
}

//----- (0045E2C0) --------------------------------------------------------
void GDReqUBFCancel(PMSG_UBF_REQ_CANCEL_REGISTER_USER *lpRecv, int aIndex)
{
	PMSG_UBF_ANS_CANCEL_REGISTER_USER pMsg; // [esp+D0h] [ebp-34h]
	char CanceledSubResult; // [esp+E7h] [ebp-1Dh]
	char DeletedResult; // [esp+F3h] [ebp-11h]
	int CanceledResult; // [esp+FCh] [ebp-8h]

	if (lpRecv)
	{
		CanceledResult = 0;
		DeletedResult = 0;
		CanceledSubResult = 0;
		memset(&pMsg.h, 0, 0xCu);
		CanceledResult = g_CCFDbSet.SetCancelToJionUnityBattlefiled(

			lpRecv->szAccountID,
			lpRecv->szName,
			lpRecv->ServerCode,
			&CanceledSubResult);
		if (CanceledSubResult != 1 || CanceledResult != 1)
			LogAddTD("[UBF][GDReqUBFCancel] No Info, Fail to Call DeleteCharacterUnityBattlefiled ");
		else
			DeletedResult = g_CCFDbSet.DeleteCharacterUnityBattlefiled(

				lpRecv->szAccountID,
				lpRecv->szName,
				lpRecv->ServerCode);
		pMsg.iUserIndex = lpRecv->iUserIndex;
		pMsg.btCanceledResult = CanceledSubResult;
		pMsg.btDeletedResult = DeletedResult;
		//PHeadSubSetB(&pMsg.h, 250, 7, 12);
		PHeadSubSetB((LPBYTE)&pMsg, 0xFA, 0x07, sizeof(pMsg));
		if (lpRecv->btCanceled == 1)
			wsjServer.DataSend(aIndex, (char*)&pMsg, sizeof(pMsg));
	}
}


//----- (0045E430) --------------------------------------------------------
void GDReqGetRealNameAndServerCode(PMSG_REQ_GET_UBF_REAL_NAME *lpRecv, int aIndex)
{
	PMSG_ANS_GET_UBF_REAL_NAME pMsg; // [esp+DCh] [ebp-30h]

	memset(&pMsg.h, 0, 0x28u);
	if (lpRecv)
	{
		pMsg.btRetrun = g_CCFDbSet.GetRealNameAndServerCode(lpRecv->szUBFName, &pMsg);
		pMsg.iUserIndex = lpRecv->iUserIndex;
		if (!pMsg.btRetrun)
		{
			memcpy(pMsg.szRealName, &GameID, 0xAu);
			memcpy(pMsg.szUBFName, &GameID, 0xAu);
		}
		//PHeadSubSetB(&pMsg.h, 250, 8, 40);
		PHeadSubSetB((LPBYTE)&pMsg, 0xFA, 0x08, sizeof(pMsg));
		wsjServer.DataSend(aIndex, (char*)&pMsg, sizeof(pMsg));
	}
}



void GDReqSaveRewardInfoOfUnityBattleField(PMSG_REQ_UBF_SET_REWARD_INFORMATION *lpRecv, int aIndex)
{
	char Result; // [esp+D3h] [ebp-2Dh]
	int bReturn; // [esp+DCh] [ebp-24h]
	PMSG_ANS_UBF_SET_REWARD_INFORMATION pMsg; // [esp+E8h] [ebp-18h]

	if (lpRecv)
	{
		memset(&pMsg.h, 0, 0x14u);
		//PHeadSubSetB(&pMsg.h, 250, 9, 20);
		PHeadSubSetB((LPBYTE)&pMsg, 0xFA, 0x09, sizeof(pMsg));
		bReturn = 0;
		Result = 0;
		bReturn = g_CCFDbSet.SetRewardInfoOfUnityBattleField(

			&Result,
			lpRecv->btServerKind,
			lpRecv->szAccountID,
			lpRecv->szName,
			lpRecv->ServerCode,
			lpRecv->btContentsType,
			lpRecv->btSubContentsType,
			lpRecv->iItemCode,
			lpRecv->btItemCount,
			lpRecv->btTookState);
		if (bReturn)
			pMsg.btReturn = Result;
		else
			pMsg.btReturn = 0;
		pMsg.iUserIndex = lpRecv->iUserIndex;
		pMsg.btContentsType = lpRecv->btContentsType;
		pMsg.btSubContentsType = lpRecv->btSubContentsType;
		pMsg.iItemCode = lpRecv->iItemCode;
		pMsg.btItemCount = lpRecv->btItemCount;
		wsjServer.DataSend(aIndex, (char*)&pMsg, pMsg.h.size);
	}
}


void GD_DSF_CanPartyEnter(PMSG_REQ_DSF_CAN_PARTY_ENTER *lpRecv, int aIndex)
{
	int nResult; // [esp+D0h] [ebp-34h]
	int nEnterCount; // [esp+DCh] [ebp-28h]
	PMSG_ANS_DSF_CAN_PARTY_ENTER pMsg; // [esp+E8h] [ebp-1Ch]
	int nReturn; // [esp+FCh] [ebp-8h]

	if (lpRecv)
	{
		nReturn = -1;
		memset(&pMsg.h, 0, 0xCu);
		nEnterCount = 0;
		nResult = 0;
		g_DSFDBset.ReqCanPartyEnter(

			lpRecv->szAccountID1,
			lpRecv->szUserName1,
			lpRecv->szAccountID2,
			lpRecv->szUserName2,
			lpRecv->btDSFType,
			lpRecv->iEnterYear,
			lpRecv->btEnterMonth,
			lpRecv->btEnterDay,
			&nEnterCount,
			&nResult);
		//PHeadSubSetB(&pMsg.h, 252, 0, 12);
		PHeadSubSetB((LPBYTE)&pMsg, 0xFC, 0x0, sizeof(pMsg));
		pMsg.iUserIndex = lpRecv->iUserIndex;
		pMsg.btCount = nEnterCount;
		pMsg.btResult = nResult;
		wsjServer.DataSend(aIndex, (char*)&pMsg, pMsg.h.size);
	}
	else
	{
		LogAddTD("[DSF][GD_DSF_CanPartyEnter] lpRecv is NULL");
	}
}

//----- (0045E810) --------------------------------------------------------
void GD_DSF_SaveUserPoint(PMSG_REQ_SAVE_DSF_USERPOINT *lpRecv)
{
	if (lpRecv)
	{
		g_DSFDBset.UpdateDSFUserPoint(

			lpRecv->UserName,
			lpRecv->GName,
			lpRecv->Type,
			lpRecv->nPoint,
			lpRecv->nEnterCount,
			lpRecv->nWin);
		LogAddTD(
			"[DSF][SaveDSFUserPoint] PC.NAME:%s,G.NAME:%s,Point:%d,Type:%d,EnterCount:%d,Win:%d",
			lpRecv->UserName,
			lpRecv->GName,
			lpRecv->nPoint,
			lpRecv->Type,
			lpRecv->nEnterCount,
			lpRecv->nWin);
	}
	else
	{
		LogAddTD("[DSF][SaveDSFUserPoint] lpRecv is NULL");
	}
}

//----- (0045E8E0) --------------------------------------------------------
void GD_DSF_SavePartyPoint(PMSG_REQ_SAVE_DSF_PARTYPOINT *lpRecv)
{
	if (lpRecv)
	{
		g_DSFDBset.SaveDSFPartyPoint(

			lpRecv->szAccountID1,
			lpRecv->szUserName1,
			lpRecv->nUser1Level,
			lpRecv->szAccountID2,
			lpRecv->szUserName2,
			lpRecv->nUser2Level,
			lpRecv->nDSFType,
			lpRecv->nPoint,
			lpRecv->btEnterCnt,
			lpRecv->nEnterYear,
			lpRecv->btEnterMonth,
			lpRecv->btEnterDay);
		LogAddTD(
			"[DSF][SaveDSFPartyPoint] AccountID1:[%s], UserName1:[%s], User1Level:[%d], AccountID2:[%s], UserName2:[%s], User2L"
			"evel:[%d], DSFType:[%d], Point:[%d]",
			lpRecv->szAccountID1,
			lpRecv->szUserName1,
			lpRecv->nUser1Level,
			lpRecv->szAccountID2,
			lpRecv->szUserName2,
			lpRecv->nUser2Level,
			lpRecv->nDSFType,
			lpRecv->nPoint);
	}
	else
	{
		LogAddTD("[DSF][SaveDSFPartyPoint] lpRecv is NULL");
	}
}

//----- (0045E9F0) --------------------------------------------------------
void GD_DSF_PartyRankRenew(PMSG_REQ_DSF_PARTYRANKRENEW *lpRecv, int aIndex)
{
	int nResult; // [esp+D0h] [ebp-24h]
	int nEnterCount; // [esp+DCh] [ebp-18h]
	PMSG_ANS_DSF_PARTYRANKRENEW pMsg; // [esp+E8h] [ebp-Ch]

	if (lpRecv)
	{
		memset(&pMsg.h, 0, 5u);
		nEnterCount = 0;
		nResult = 0;
		g_DSFDBset.RenewDSFPartyRank(

			lpRecv->btDSFType,
			lpRecv->nEnterYear,
			lpRecv->btEnterMonth,
			lpRecv->btEnterDay);
		//PHeadSubSetB(&pMsg.h, 252, 3, 5);
		PHeadSubSetB((LPBYTE)&pMsg, 0xFC, 0x03, sizeof(pMsg));
		pMsg.btResult = 1;
		wsjServer.DataSend(aIndex, (char*)&pMsg, pMsg.h.size);
		LogAddTD("[DSF][RenewDSFPartyRank]%d", lpRecv->btDSFType);
	}
	else
	{
		LogAddTD("[DSF][GD_DSF_PartyRankRenew] lpRecv is NULL");
	}
}

//----- (0045EB10) --------------------------------------------------------
void GD_DSF_TodayPartyRank(PMSG_REQ_DSF_TODAY_PARTYRANK *lpRecv, int aIndex)
{
	int nReturn; // [esp+D0h] [ebp-67Ch]
	char btCount; // [esp+DFh] [ebp-66Dh]
	int loffs; // [esp+E8h] [ebp-664h]
	char sendbuf[1024]; // [esp+F4h] [ebp-658h]
	PMSG_ANS_DSF_TODAY_PARTYRANK pMsg; // [esp+4FCh] [ebp-250h]
	_stDSFPartyRankInfo DSFRank[20]; // [esp+514h] [ebp-238h]

	if (lpRecv)
	{
#pragma message ("FIX THIS FUCKIN VECTOR!!")
		//`vector constructor iterator'(DSFRank, 0x1Cu, 20, _stDSFPartyRankInfo::_stDSFPartyRankInfo);
		sendbuf[0] = 0;
		memset(&sendbuf[1], 0, 0x3FFu);
		btCount = 0;
		loffs = 16;
		nReturn = 0;
		if (!g_DSFDBset.TodayDSFPartyRank(

			DSFRank,
			&btCount,
			lpRecv->btDSFType,
			lpRecv->nEnterYear,
			lpRecv->btEnterMonth,
			lpRecv->btEnterDay))
		{
			memcpy(&sendbuf[loffs], DSFRank, 28 * btCount);
			loffs += 28 * btCount;
			//PWMSG_HEAD2::set(&pMsg.h.c, 252, 4, loffs);
			pMsg.h.set((LPBYTE)&pMsg.h.c, 0xFC, 4, loffs);
			pMsg.btPartyCnt = btCount;
			memcpy(sendbuf, &pMsg.h.c, 0x10u);
			wsjServer.DataSend(aIndex, sendbuf, loffs);
		}
	}
	else
	{
		LogAddTD("[DSF][GD_DSF_TodayPartyRank] lpRecv is NULL");
	}
}

void GD_DSF_GoFinalParty(PMSG_REQ_DSF_GO_FINAL_PARTY *lpRecv, int aIndex)
{
	char v2;
	int v3;
	char btCount;
	int size;
	char buf;
	char dst;
	PWMSG_HEAD2 pMsg;
	char v9;
	char v10;
	_stDSFGoFinalPartyInfo v11;
	_stDSFGoFinalPartyInfo DSFRank;
	char __t;
	unsigned int v14;
	int savedregs;

	memset(&v2, 0xCCu, 0x23D8u);
	v14 = (unsigned int)&savedregs ^ __security_cookie;
	if (lpRecv)
	{
#pragma message ("FIX THIS FUCKIN VECTOR!!")
		/*`vector constructor iterator'(
			&__t,
			0x28u,
			80,
			(void *(__thiscall *)(void *))_stDSFGoFinalPartyInfo::_stDSFGoFinalPartyInfo);
			`vector constructor iterator'(
				&DSFRank,
				0x28u,
				20,
				(void *(__thiscall *)(void *))_stDSFGoFinalPartyInfo::_stDSFGoFinalPartyInfo);
				`vector constructor iterator'(
					&v11,
					0x28u,
					20,
					(void *(__thiscall *)(void *))_stDSFGoFinalPartyInfo::_stDSFGoFinalPartyInfo);*/
		buf = 0;
		memset(&dst, 0, 0xFFFu);
		btCount = 0;
		size = 7;
		v3 = 0;
		switch (lpRecv->btDSFType)
		{
		case 2:
			v3 = g_DSFDBset.DSFGoFinalParty(

				(_stDSFGoFinalPartyInfo *)&__t,
				&btCount,
				lpRecv->btDSFType,
				lpRecv->nEnterYear,
				lpRecv->btEnterMonth,
				lpRecv->btEnterDay);
			memcpy(&buf + size, &__t, 40 * (unsigned __int8)btCount);
			break;
		case 3:
			v3 = g_DSFDBset.DSFGoFinalParty(
				&DSFRank,
				&btCount,
				lpRecv->btDSFType,
				lpRecv->nEnterYear,
				lpRecv->btEnterMonth,
				lpRecv->btEnterDay);
			memcpy(&buf + size, DSFRank.szUserName1, 40 * (unsigned __int8)btCount);
			break;
		case 4:
			v3 = g_DSFDBset.DSFGoFinalParty(

				&v11,
				&btCount,
				lpRecv->btDSFType,
				lpRecv->nEnterYear,
				lpRecv->btEnterMonth,
				lpRecv->btEnterDay);
			memcpy(&buf + size, v11.szUserName1, 40 * (unsigned __int8)btCount);
			break;
		}
		if (!v3)
		{
			size += 40 * (unsigned __int8)btCount;
			//PWMSG_HEAD2::set(&pMsg.c, -4, 5, size);
			pMsg.set((LPBYTE)&pMsg.c, 0xFC, 4, size);
			v9 = btCount;
			v10 = lpRecv->btDSFType;
			memcpy(&buf, &pMsg.c, 7u);
			wsjServer.DataSend(aIndex, &buf, size);
		}
	}
	else
	{
		LogAddTD("[DSF][GD_DSF_GoFinalParty] lpRecv is NULL");
	}
}

void GD_DSF_InsertRewardUser(PMSG_REQ_SAVE_DSF_REWARD_USER *lpRecv)
{
	//char v1;

	//memset(&v1, 0xCCu, 0xC0u);
	if (lpRecv)
	{
		g_DSFDBset.InsertRewardUser(

			lpRecv->szAccountID,
			lpRecv->szUserName,
			lpRecv->iClass,
			lpRecv->btDSFType,
			lpRecv->nRewardYear,
			lpRecv->btRewardMonth,
			lpRecv->btRewardStartDay,
			lpRecv->btRewardEndDay);
		LogAddTD(
			"[DSF][GD_DSF_InsertRewardUser]AccountId:%s, Name:%s, DSFType:%d",
			lpRecv->szAccountID,
			lpRecv->szUserName,
			lpRecv->btDSFType);
	}
	else
	{
		LogAddTD("[DSF][GD_DSF_InsertRewardUser] lpRecv is NULL");
	}
}

void GD_DSF_ReqGetReward(PMSG_REQ_GET_DSF_REWARD *lpRecv, int aIndex)
{
	char v2;
	int nResult;
	int nEnterCount;
	PMSG_ANS_GET_DSF_REWARD pMsg;

	memset(&v2, 0xCCu, 0xECu);
	if (lpRecv)
	{
		memset((char *)&pMsg.h, 0, 0xCu);
		nEnterCount = 0;
		nResult = 0;
		nResult = g_DSFDBset.GetReward(

			lpRecv->szAccountID,
			lpRecv->szUserName,
			lpRecv->nServerCode,
			lpRecv->nRewardYear,
			lpRecv->btRewardMonth,
			lpRecv->btRewardDay);
		//PHeadSubSetB((char *)&pMsg.h, 0xFC, 7, 0xC);
		PHeadSubSetB((LPBYTE)&pMsg.h, 0xFC, 7, sizeof(pMsg));
		pMsg.nUserIndex = lpRecv->nUserIndex;
		pMsg.btResult = nResult;
		wsjServer.DataSend(aIndex, (char *)&pMsg.h, (unsigned __int8)pMsg.h.size);
		LogAddTD("[DSF][ReqGetReward]AccountId:%s, Name:%s, Result:%d", lpRecv->szAccountID, lpRecv->szUserName, nResult);
	}
	else
	{
		LogAddTD("[DSF][GD_DSF_ReqGetReward] lpRecv is NULL");
	}
}

void GD_Req_Get_EventMapEnterCount(SDHP_GET_EVENTMAPENTERCOUNT *lpRecv, int aIndex)
{
	int nReturn;
	char IllusionTemple;
	char IG_Weeks;
	char Doppel;
	char Chaos;
	char devil;
	char blood; 
	SDHP_ANS_EVENTMAPENTERCOUNT pMsg;

	if (lpRecv)
	{
		//PBMSG_HEAD2::set(&pMsg.h, (char *)&pMsg.h, 0xFD, 0xFB, 0x1C);
		pMsg.h.set((LPBYTE)&pMsg.h, 0xFD, 0xFB, sizeof(_tagPMSG_ANS_AE_PLAY_DS));
		blood = 0;
		devil = 0;
		Chaos = 0;
		Doppel = 0;
		IG_Weeks = 0;
		IllusionTemple = 0;
		nReturn = 0;
		nReturn = g_EventMapEnterCount.GetEventMapEnterCount(
			lpRecv->Name,
			&blood,
			&Chaos,
			&devil,
			&Doppel,
			&IG_Weeks,
			&IllusionTemple);
		if (nReturn)
		{
			LogAddTD("[GD_Req_Get_EventMapEnterCount] NAME:[%s] nReturn:%d", lpRecv->Name, nReturn);
		}
		else
		{
			memcpy(pMsg.Name, lpRecv->Name, 0xBu);
			pMsg.nUserIndex = lpRecv->userIndex;
			pMsg.BloodCastle = blood;
			pMsg.ChaosCastle = Chaos;
			pMsg.DevilSquare = devil;
			pMsg.DoppelGanger = Doppel;
			pMsg.ImperialGuardian = IG_Weeks;
			pMsg.IllusionTempleRenewal = IllusionTemple;
			wsjServer.DataSend(aIndex, (char *)&pMsg.h, 28);
		}
	}
	else
	{
		LogAddTD("Error - [GD_Req_Get_EventMapEnterCount] lpRecv is NULL");
	}
}
// 68372C4: using guessed type void (*LogAddTD)(char *, ...);

//----- (0045FDB0) --------------------------------------------------------
void GD_Req_Set_EventMapEnterCount(SDHP_SET_EVENTMAPENTERCOUNT *lpRecv)
{
	//char v1; // [sp+Ch] [bp-CCh]@1
	int bResult;

	//memset(&v1, 0xCCu, 0xCCu);
	if (lpRecv)
	{
		bResult = g_EventMapEnterCount.SetEventMapEnterCount(

			lpRecv->Name,
			lpRecv->BloodCastle,
			lpRecv->ChaosCastle,
			lpRecv->DevilSquare,
			lpRecv->DoppelGanger,
			lpRecv->ImperialGuardian,
			lpRecv->IllusionTempleRenewal);
		if (!bResult)
			LogAddTD("Error - [GD_Req_Set_EventMapEnterCount] SetEventMapEnterCount");
	}
	else
	{
		LogAddTD("Error - [GD_Req_Set_EventMapEnterCount] lpRecv is NULL");
	}
}

void GD_ReqEventMapIntegration_AllNotify(SDHP_SEND_EVENTMAP_INFO_ALL_SVR *lpRecv)
{
	//char v1; // [sp+Ch] [bp-DCh]@1
	SDHP_SEND_EVENTMAP_INFO_ALL_SVR pMsg; // [sp+DCh] [bp-Ch]@2

	//memset(&v1, 0xCCu, 0xDCu);
	if (lpRecv)
	{
		memset((char *)&pMsg.h, 0, 8);
		//PHeadSubSetB((char *)&pMsg.h, 0xFD, 0xFE, 8);
		PHeadSubSetB((LPBYTE)&pMsg.h, 0x4C, 0, sizeof(pMsg));
		pMsg.byBattleStatus = lpRecv->byBattleStatus;
		pMsg.byBattleType = lpRecv->byBattleType;
		pMsg.wMapSvrNum = lpRecv->wMapSvrNum;
		LogAddTD(
			"[EventMapIntegration][GD_ReqEventMapIntegration_AllNotify] byBattleType :%d ,BattleStatus %d",
			lpRecv->byBattleType,
			lpRecv->byBattleStatus);
		for (int i = 0; i < 100; ++i)
		{
			if (gSObj[i].Connected)
			{
				if (gSObj[1].iMapSvrGroup == pMsg.wMapSvrNum)
					wsjServer.DataSend(i, (char *)&pMsg.h, 8);
			}
		}
	}
}