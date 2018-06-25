//----------------------------------------------------------------------------
// MU 서버프로젝트 전반에 걸쳐 정의되어 사용되어지는 것들..
//----------------------------------------------------------------------------
#ifndef __DEFINE_H__
#define __DEFINE_H__

#include "..\\Include\\Public.h"
//----------------------------------------------------------------------------

enum DB_CLASS_TYPE 
{
	DB_CLASS_TYPE_WIZARD = 0x0,
	DB_CLASS_TYPE_KNIGHT = 0x10,
	DB_CLASS_TYPE_ELF = 0x20,
	DB_CLASS_TYPE_MAGUMSA = 0x30,
	DB_CLASS_TYPE_DARKLORD = 0x40,
	DB_CLASS_TYPE_SUMMONER = 0x50,
	DB_CLASS_TYPE_MONK = 0x60,
	DB_CLASS_TYPE_LANCER = 0x70,
};

enum AMS 
{
	AM_NONE = 0x0,
	AM_STANDBY = 0x0,
	AM_ACTIVE = 0x1,
};


//----------------------------------------------------------------------------
// 컴파일시에 사용되는 것
//#define _DEBUG_PROTOCOL						// 프로토콜을 디버그 시에 사용 
#define LOG_PRINT			1					// 로그를 출력할것인가?
#define SPEEDHACK_CHECK		1					// 스피드핵을 체크할것인가?

#define TESTSERVER	 		0					// Service:0  테스트 서버인가..
#define LOCALCONNECT		0					// Service:0  사내에서만 접속 가능하게..
#define DATANOSAVE			0					// Service:0  데이터가 저장되지 않게 한다.

#define DBGUILDLOAD			1					// Service:1, DB서버에 접속해서 길드 정보를 가지고 오는가..

/*enum GAME_VERSION_ENUM
{
G_V_97D,
G_V_99B,
G_V_S1,
G_V_S2,
G_V_S2_2,
G_V_S3_E1,
G_V_S3_E2,
G_V_S4_5,
G_V_S4_6, //S4.5.1
};*/

#define G_V_97D		0
#define G_V_97_99	1
#define G_V_99B		2
#define G_V_S1		3
#define G_V_S1_512	4
#define G_V_S2		5
#define G_V_S2_2	6
#define G_V_S3_E1	7
#define G_V_S3_E2	8
#define G_V_S4_5	9
#define G_V_S4_6	10
#define CHARACTERDB_SERVER
#define GAME_VERSION	G_V_S4_6

//#define ADD_ANTI_HACK_01_20051027 //SpeedHack FIX! - BAD

#if GAME_VERSION >= G_V_S4_6
//#define KOREAN_S4_6
//#define GLOBAL_S4_6
#define JAPAN_S4_6
#endif

#if GAME_VERSION >= G_V_99B
#define EVENT_STONE
#define EVENT_RENA_20040909
#define EVENT_LOTTO
#define USER_ENTER_BLOODCASTLE7_WITH6_20040330
#define EVENT_FRIENDSHIP_20040204
#define EVENT_STONE_OF_FRIENDSHIP_20040206 
#define MODIFY_INVEN_CLEAR_MACRO_20071212
#endif



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








//#ifdef USA
#if GAME_VERSION >= G_V_S4_6
// 미국 버전 테스트를 위한 데이터로딩 검사.
//	#define	TEST_LOADING_STEP_20060211

// 1) 유저 인증 시 레벨 캡(현재 60 레벨) 적용을 위한 작업
// 2) 인증 서버에 존재하는 계정, 캐릭터, 레벨 정보 테이블의 무결성을 위한 작업
// 3) 캐릭터 삭제 시 인증서버에 알려 해당 테이블에서 삭제해준다. (apple)

// [업데이트] 캐릭터 리스트 중복요청금지(goni)
#define UPDATE_RESEND_GETCHARlIST_DISABLE_20090605

// [버그수정] 중국 접속 공격 차단 
#define MODIFY_CONNNECT_HACK_ATTACK_20090409
#ifdef MODIFY_CONNNECT_HACK_ATTACK_20090409
#define TEMPLOG_PRINT		0	// 1 이면 로그 파일을 따로 생성,출력 한다.
#endif

#define NOTIFY_CHARACTER_DELETE_FROM_GS_TO_JS_20060322

// MuLog 기록 값 변경
#define LOGINSERVER_MULOG

// 패스워드 길이 20바이트로 증가
#define PW_KUZIMO
#ifdef GLOBAL_S4_6
#define UPDATE_USERPASSWORD_LENGTH_20090424
#endif

// [업데이트] 통합빌링 추가(goni)
#define UPDATE_UNIFICATIONBILL_20090203

//#define MODIFY_HACKLOG_OF_ATTACK_20050714			// 공격 핵 로그 수정 (b4nfter)
//#define MODIFY_HACKLOG_OF_ATTACK_20050518           // 공격 핵 로그 수정 (u4us)
//#define CHECK_ATTACK_AREA

// [업데이트] 화이트엔젤 아이템 지급 이벤트 (RKFKA)
#define WHITEANGEL_GET_ITEM_EVENT_20060822

#endif

#if defined ( FOR_KOREA ) || defined ( EVENT_FRIENDSHIP_20040204 ) || defined ( EVENT_LOTTO )
#define ADD_ITEM_OF_FRIENDSHIP_EVENT_20040729		           
#endif

///////////////////////////////////////////////////////////////////////////////
// 이벤트 관련 설정 코드
//
// 주의: 두개 이상의 이벤트 실행시 버그 발생 확인 요망
///////////////////////////////////////////////////////////////////////////////

// EVENT_SERVER_OPEN_COMMEMORATION_20050510     // 서버 오픈 기념 이벤트 (u4us)
// EVENT_RENA_20040909                          // 레나 이벤트 (u4us)
// EVENT_LOTTO                                  // 복권 이벤트 (u4us)    

// EVENT_STONE_OF_FRIENDSHIP_20040206                       
// EVENT_RENA_FOR_CASTLE_SIEGE_20041116                     
// EVENT_FRIENDSHIP_20040204


///////////////////////////////////////////////////////////////////////////////

#if GAME_VERSION >= G_V_99B
#define DELETE_DARKLORD_PET_SERIAL_ZERO_20050617		// 일본 버그패치
#define DARKLORD_PET_INFO_FORCE_TO_SET_20050531			// 상점에서 다크로드 펫을 살 경우 기본정보를 강제로 세팅
#endif

#define APPLY_TESTSERVER					// 테스트 서버에만 적용중 또는 적용 예정 중인것들

// 테스트 서버에 적용되는 것들은 여기에 추가!!!!!
#ifdef APPLY_TESTSERVER

#if TESTSERVER == 1
// [업데이트] 3차 전직을 하여 마스터 레벨인 경우만 MasterLevelSystem 정보를 로딩하고 저장하도록 수정 2008-12-12 by riverstyx
// 현재 마스터레벨이 아닌유저도 MasterLevelSystem에 정보를 저장하고 로딩하는 불필요한 로직을 사용함
//#define MODIFY_3RDCHANGEUP_MASTERLEVEL
#endif

#ifndef FOR_KOREA

// EventItembag 번호 겹치는 문제(pelero)
#define MODIFY_FIRECRACKER_EVENTITEMBAG_NUMBER_CHANGE_20090930

// 해외 부분유료화 7차 업데이트 (pelero)	
#define ADD_PARTIALY_CHARGE_SYSTEM_07_20090915
#ifdef ADD_PARTIALY_CHARGE_SYSTEM_07_20090915
// 엘리트 SD 회복 물약 추가(pelero)
#define ADD_ELITE_SD_POTION_20090918
// 파티시 경험치 증가 스크롤 추가(pelero)
#define ADD_PARTY_EXP_INCREASE_SCROLL_20090916
// 오라 아이템 추가(pelero)
#define ADD_AURA_CASH_ITEM_20090915
// 유니콘 펫 추가(pelero)
#define ADD_UNICORN_PET_20090915
// 치명 마법 반지 추가(pelero)
#define ADD_CRITICAL_WIZARD_RING_20090915
#endif // ADD_PARTIALY_CHARGE_SYSTEM_07_20090915

// 크리스가 창고에 안 들어가는 버그(pelero)
#define MODIFY_KRIS_MOVE_WAREHOUSE_BUGFIX_20090904

// 캐쉬 아이템중 공격력, 방어력, 마나, 생명을 증가시켜주는 아이템 사용시
// 아이템 이펙트와 버프이펙트 중복 적용되는 버그 (musang33)
#define MODIFY_CASHITEM_EFFECT_REITERATION_APPLY_20090903

// 갬블링시에 엑설런트 장비에도 행운 옵션이 붙을 수 있도록 변경(pelero)
#define MODIFY_GAMBLING_ATTACH_LUCK_OPTION_20090901

// 환영 사원 종료 후 맵 이동시 아이템 삭제 버그(pelero)
#define MODIFY_ILLUSIONTEMPLE_MOVEGATE_ITEM_DELETE_BUGFIX_20090826

// 결투장에서 다크스피릿이 재착용해야 사용되는 버그(pelero)
#define MODIFY_PKFIELD_DARK_SPRIT_BUGFIX_20090804

// 벚꽃 이벤트 관련 NPC를 등록(pelero)
#define MODIFY_CHEREEY_NPC_REGISTER_NPC_GROUP_20090803

// 수호 부적과 보호 부적은 각각 중복으로 사용하지 못하도록 처리(pelero)
#define MODIFY_CHARM_GUARDIAN_CHARM_PROTECTITEM_NON_DUPLICATION_20090720

// 결투중 결투 종료 카운트 중에 또다시 결투 종료 요청시 카운트가 초기화 되는 버그(pelero)
#define MODIFY_NEWPVP_ENDING_COUNTDOWN_BUGFIX_20090715

// 불카누스에서 인장류가 검투사의 명예보다 우선 적용 되도록 수정(pelero)
#define MODIFY_PCS_MARKS_GLORYOFGLADIATOR_SEQUENCE_20090715

// 결투중 종료시에 초기화 문제(pelero)
#define MODIFY_NEWPVP_GAME_CLOSING_BUGFIX_20070715

// 눈사람 변신 반지, 팬더 변신 반지 버그 수정(pelero)
#define MODIFY_SNOW_MAN_PANDA_POLYMORPH_RING_BUGFIX_20090715

// 여름 불꽃놀이 이벤트(pelero)
#define ADD_SUMMER_FIRECRACKER_MONSTER_EVENT_20090610

// 황금 군단 이벤트 리뉴얼 20090311 (natinda)
//#define ADD_GOLDEN_EVENT_RENEWAL_20090311 DESACTIVADO POR 007JODEX

// 쿤둔&벚꽃 아이템백 리뉴얼 작업 by natinda
#define MODIFY_KUNDUN_EVENTBAG_RENEWAL_2009_02_04
#endif // FOR_KOREA

// [버그 수정] PathFind 버그수정(goni)
#define MODIFY_PATHFIND_BUGFIX_20090609
#if GAME_VERSION >= G_V_S4_6
// [보상 변경] 카오스 캐슬 보상 관련 변경 by natinda
#define MODIFY_CHAOSCASTLE_REWARD_20090608     
#endif

#if defined( FOR_KOREA ) && GAME_VERSION >= G_V_S4_6// 수리비 공식 국내만 적용
// [공식 수정] 자동 수리비 공식 관련 변경
#define MODIFY_AUTOREPAIR_CALC_20090608
#endif // FOR_KOREA

// [버그 수정] 전체 수리비용 관련 문제 (natinda)
#if GAME_VERSION >= G_V_S4_6
#define MODIFY_CALREPAIRRATE_20090528
#endif

#if GAME_VERSION >= G_V_S4_6
// [업데이트] EventItemBag 확장_addoption  값에 따라 옵션을 넣어줌.(goni)
#define UPDATE_PROBABILITYITEMBAG_ADDOPTION_VALUE_20090526

// 프리미엄아이템 추가(팬더변신반지, 팬더펫) 2009-04-30 by riverstyx
// #define PREMIUMITEM_20090106 활성화 되어있어야 함
#define ADD_PREMIUMITEM_PANDA

// [버그 수정] 무기 스킬을 강화한 후 무기를 장착 해제하면
// 스킬트리가 비정상적으로 표시 되는 버그(pelero)
#define MODIFY_WEAPONSKILL_STRENGTHEN_ICON_BUGFIX_2ND_20090514

// [설정수정] 이벤트맵 진입시 스킬 버프를 지우도록 수정(pelero)
#define ADD_EVENT_MAP_BUFF_EFFECT_DELETE_20090421
#endif

// [버그수정] 인피니티 에로우 시전시 +2화살의 마나감소 버그(pelero)
#define MODIFY_INFINITY_ARROW_USE_MANA_BUGFIX_20090416

#if GAME_VERSION >= G_V_S4_5
// [버그수정] 피의 환영사원 입장권(두루마리/피의두루마리)의 내구도가 0되어도 삭제 안되는 버그 수정
// 국내도 발생가능 TW_0074(riverstyx) - 국내로 옮겨옴 20090416
#define MODIFY_ILLUSIONTEMPLE_FREE_TICK_20080617

// [버그수정] 환영 사원에서 라이트닝 쇼크 사용시 버그(pelero)
#define MODIFY_LIGHTNINGSHOCK_ILLUSIONTEMPLE_BUGFIX_20090414

// [버그수정] 눈사람 변신 반지 장비창에서 창고로 넣을때 변신 안풀리는 버그(pelero)
#define MODIFY_SNOW_MAN_POLYMORPH_RING_BUGFIX_20090414
#endif

// [버그수정] 물건을 수리시 수리비용보다 소유젠이 많아야 수리되는 버그(pelero)
// 소유젠이 수리비와 같을 때도 수리되도록 수정
#define	MODIFY_ITEM_REPAIR_HIRE_BUGFIX_20090415

// [버그수정] 창고에서 물건을 찾을 때 사용료보다 소유젠이 많아야 찾아지는 버그(pelero)
// 소유젠이 사용료와 같을 때도 찾아지도록 수정
#define	MODIFY_WAREHOUSE_HIRE_BUGFIX_20090413

#if GAME_VERSION >= G_V_S4_5
// [버그수정] 피씨방버프 부분유료화 버프 처리 로직 개선 2008-04-08 by riverstyx
// 디파인으로 구분되어 처리되던 피씨방, 해외 부분 유료화 아이템 버프 처리 로직을 하나로 합친다.
// CheckItemOptForGetExpEx <- (CheckItemOptForGetExp, CPCBangPointSystem::CheckItemOptForGetExp, CNewPVP::CheckItemOptForGetExp) 통합
// 안정화되면 아래 디파인은 정리할 예정
// 기존 버프 처리 디파인은 제거
// MODIFY_MARKITEM_20080506 - 제거
// MODIFY_EVENTMAP_REWARD_BUGFIX_20080404 - 제거
// MODIFY_BUFF_SYSTEM_EXTENTION_CASHSHOP_20080318 - 버프 처리 로직에서 제거
// BUGFIX_BUFF_EFFECT_SYSTEM_FOR_PCBANG_ITEM_20071205 - 버프 처리 로직에서 제거
#define MODIFY_BUFF_EFFECT_SYSTEM_CHECKLOGIC
#endif


// 루아
//#define MODIFY_LUA_SCRIPT_20090430

// [버그수정] 공성전 시 공성전 참여길드인데도 PK카운트가 올라가는 현상 수정 2009-04-30 by riverstyx
#define MODIFY_CASTLESIEGE_STATENOTIFY_JOINGUILD_BUGFIX

// [업데이트] 해킹 툴 블록 기능을 전체 서버에 가능하도록 인증서버와의 연동 기능 추가 (hnine)
#define MODIFY_HACKTOOL_BLOCK_ALL_SESSION_20090422
#if GAME_VERSION >= G_V_S3_E1
// [버그수정] 3차날개 조합가격 버그수정(goni)
#define MODIFY_THIRD_WING_EXITEMMONEY_BUGFIX_20090423
#endif
// [버그수정] Movereq.txt 파일의 최대 맵 인덱스 제한 상승 40 -> 50 (hnine)
#define MODIFY_MOVEREQ_MAP_INDEX_LITMIT_20090421

#ifdef FOR_KOREA	// 현재는 국내만 적용
// [업데이트] 맵이동을 채팅 메시지가 아닌 맵 이동 요청 프로토콜로 변경 (hnine)
#if GAME_VERSION >= G_V_S4_6
//#define ADD_MAPMOVE_PROTOCOL_20090327 //TEST MOVE
#endif
#define USE_MAPMOVE_KEY_GENERATOR_SERVER_SIDE
#endif	// FOR_KOREA

// [업데이트] 해킹 툴 블록 기능을 단일 서버에만 적용되도록 임시 수정 (hnine)
#define MODIFY_HACKING_TOOL_BLOCK_SINGLE_SERVER_20090325

// [버그수정] 드래곤 어택 이벤트 몹에서 떨군 축석을 상점에 판매시 4억이 넘는 금액으로 팔리는 문제. by natinda 20090410
#define MODIFY_JEWELOFBLESS_SELL_BUGFIX

// [업데이트] 통합빌링 추가(goni)
#define UPDATE_UNIFICATIONBILL_20090203

// [버그수정] 파워 슬레쉬 거리 버그 수정 테스트 후 삭제(grooving)
#define MLS_POWERSLASH_DISTANCE_20090216
#if GAME_VERSION >= G_V_S4_5
// [업데이트] 아이로봇 및 해킹 툴 블록 기능 추가 (hnine)
#define ADD_HACKING_TOOL_BLOCK_20090311

// [버그수정] 크로스 실드 엑설런트 옵션 적용(pelero)
#define MODIFY_CROSS_SHIELD_EX_OPTION_APPLY_20090326
#endif

#if GAME_VERSION >= G_V_S4_5
// [버그수정] 벚꽃관련 아이템의 판매 가격에 갯수 적용(pelero)
#define MODIFY_CHERRYBLOSSOM_SELL_MONEY_BUGFIX_20090325
#endif

// [버그수정] 캐쉬샵 리스트가 없을경우(등록되지 않거나 샵서버와의 연결 문제로 못받았을경우) empty packet을 보내지 않도록 한다. by natinda 20090218
#define MODIFY_BUGFIX_CASHSHOP_OPEN_INTERFACE

// [업데이트] 이벤트 아이템 발급 로그에 발급된 아이템 정보 추가 2009-03-18 by riverstyx
#define ADD_COUPON_EVENTITEM_LOG

// [버그수정] Teleport 시 타켓 좌표 Y를 OBJECTSTRUCT.TX 에 입력하는 버그수정 2009-03-12 by riverstyx
#define MODIFY_TELEPORT_TARGETPOSITION_BUGFIX

// [버그수정] 카오스카드 조합 - 개인상점 오픈시 카오스 조합 불가 2009-03-12 by riverstyx
#define MODIFY_PCS_CHAOSMIX_PSHOP_BUGFIX

#if GAME_VERSION >= G_V_S4_6
// [업데이트] 불카누스, PK Field 2009-01-08 by riverstyx
#define	ADD_NEWPVP_PKFIELD

// [업데이트] 겜블링 시스템 업데이트(pelero)
#define ADD_GAMBLING_20090120
#endif

#ifdef ADD_NEWPVP_PKFIELD
// PKField 작업중에 셋트 Life 버그 발견 우선 PKField 반영시에 적용할 예정이다.
// [버그수정] Life 최대 값 감소시 현재 감소된 값 전송.아이템 효과 적용에서 분리 2009-02-02 by riverstyx
// 삭제예정
//#define MODIFY_LIFE_CHANGEMAXVALUE

// [버그수정] Life, Shield 백분율로 100%(Life > MaxLife + AddLife) 넘어가는 버그수정(NewPVP에서만 사용) 2009-04-17 by riverstyx
#define MODIFY_LIFE_CHANGEMAXVALUE_BUGFIX
// [업데이트] 벚꽃상자 불카누스에서만 드랍되도록 수정(pelero)
#define MODIFY_CHERRYBLOSSOM_DROP_VULCANUS_20090324
#endif // ADD_NEWPVP_PKFIELD

#ifdef ADD_GAMBLING_20090120
// [업데이트] 겜블링 시스템 보완
#define MODIFY_GAMBLING_COMPLEMENT_20090513
// [업데이트] 겜블링 진행여부 스크립트 적용
#define ADD_IS_ENABLED_GAMBLING_20090504
// [버그수정] 겜블링 시스템 1차 버그 수정(pelero)
#define MODIFY_GAMBLING_BUGFIX_1_20090323
// [업데이트] 스트라이커 셉터 처리 추가(pelero)
#define ADD_STRIKER_SCEPTER_20090317
// [업데이트] 에어린보우 추가(pelero)
#define ADD_AERINBOW_20090309
#endif // ADD_GAMBLING_20090120

#if GAME_VERSION >= G_V_S2_2
// 국내 프리미엄 아이템(카오스카드) 추가
#define ADD_PCS_LOTTERY_SYSTEM_20070117
#define MODIFY_PCS_CHAOSMIX_REFACTORING_20070903
#endif

#if GAME_VERSION >= G_V_S3_E2
// [버그수정] 마스터레벨 경험치 비율을 정수형으로 읽어오는 버그(pelero)
#define MODIFY_MASTER_LEVEL_ADD_EXPERIENCE_BUGFIX_20090304
#endif

#if GAME_VERSION >= G_V_S4_5
// [버그수정] 피씨방 이용자 경험치(Rate) 설정 2009-02-19 by riverstyx
#define UPDATE_PCBANGPOINTSYSTEM_BUGFIX
#endif

#if GAME_VERSION >= G_V_S4_6
// [업데이트] 수성측길드나 수성측연합길드인지 판단(goni)
#define UPDATE_CHECK_CASTLE_OWNERMEMBER_20090217
#endif

#if GAME_VERSION >= G_V_S4_5
// [업데이트] 피씨방 이용자 경험치(Rate) 설정 2009-02-16 by riverstyx
#define ADD_PCBANG_EXPRATE
#endif

#if GAME_VERSION >= G_V_S4_5
// [버그수정] 디비렉으로 인한 카오스 조합 복사 버그수정(goni)
#define MODIFY_CHAOS_ITEM_COPY_BUGFIX_20090211

// [버그수정] 서버에서 몬스터 리로드 옵션 기능 수행시 세루판이 바보가 된 채로 리젠(pelero)
#define MODIFY_SELUPAN_REGEN_MONSTER_RELOADING_BUGFIX_20090128
#endif

// [업데이트] GM 기능 강화 2008-12-16 by riverstyx
#define GMCOMMAND_EX
#if defined( GMCOMMAND_EX ) && GAME_VERSION >= G_V_S4_5
#define GMCOMMAND_EX_1ST_BUGFIX
#endif // GMCOMMAND_EX

#if GAME_VERSION >= G_V_99B
// [업데이트] GM 기능 강화 2009-01-14 by riverstyx
#define MODIFY_SETITEM_LEADERSHIP_BUGFIX
#endif

// [업데이트] 다크로드보완_카오틱디세이어 수정(goni)
#define UPDATE_CHAOTICDESAIR_SKILL_20090109

#if GAME_VERSION >= G_V_99B
// [업데이트] 다크로드 보완(다크스피릿, 다크호스 인벤수리가능)(goni)
#define UPDATE_DARKROAD_PET_ITEMREPAIR_20090109
#endif

#if GAME_VERSION >= G_V_S4_6
// [업데이트] 국내 프리미엄 아이템판매(grooving)
#define PREMIUMITEM_20090106
#endif 

#ifdef PREMIUMITEM_20090106
#define EVENT_LOTTO
// [업데이트] 쿠폰 이벤트 아이템 리스트(grooving)
#define COUPON_EVENT_ITEMLIST_20081022
// [업데이트] 카오스 부적. 카오스부적 실패시 소멸되는 아이템 보호(grooving)
#define	ADD_CHAOSMIXCHARM_ITEM_20080702
#endif

#if GAME_VERSION >= G_V_S4_5
// 국내에두 적용함
// [업데이트] 수호 아이템. 기존 수호천사 아이템 업그레이드 형태. //grooving
#define	ADD_SAFEGUARD_ITEM_20080702

// 쿨러틴이 데비아스에서 바보인 상태로 리젠되는 버그 수정(pelero)
#define MODIFY_REGEN_SELUPAN_SUMMON_MONSTER_IN_DEVIAS_BUGFIX_20081205

// [업데이트] 해외 크리스마스 이벤트 맵 추가 (riverstyx)
#define UPDATE_XMASEVENT_MAP_20080930
#endif

#ifdef UPDATE_XMASEVENT_MAP_20080930
// [업데이트] 해외 크리스마스  (grooving)
#define ADD_XMASEVENT_PET_20080930

// [업데이트] 해외 크리스마스 아이템 지급 관련 (natinda)
#define ADD_GIFTITEM_XMASEVENT_20081030

// [업데이트] 해외 크리스마스 산타클로스 군단
#define ADD_ITEM_ATTACK_XMASEVENT_20081014

// [업데이트] 해외 크리스마스 이벤트 Npc 추가
#define ADD_NPC_XMASEVENT_20080930

// [업데이트] 해외 크리스마스 이벤트 버프 추가
#define ADD_BUFF_XMASEVENT_20080930

// [업데이트] 해외 크리스마스 변신 반지 추가
#define ADD_XMASEVENT_POLYMORPH_RING_20080930

// [업데이트] 해외 크리스마스 아이템 지급 처리 추가 (riverstyx)
#define ADD_PAYITEM_20081030
// [업데이트] EventDB 확장 (riverstyx)
#define EVENTDB_PROTOCOLEX

// [버그수정] 15레벨 미만 사용자 산타의 마을 입장 레벨제한 설정 2008-12-17 by riverstyx
#define MODIFY_SANTACLAUSVILLAGE_VISITLEVEL

// [버그수정] 산타의 강화 마력도 +30 적용(소환술사-공방에 저주력추가) 되도록 변경 2008-12-17 by riverstyx
#define MDOFIY_BUFF_POWER_UP

// [업데이트] 산타의 마을 NPC 선물 설정 파일로 변경 2008-12-17 by riverstyx
#define ADD_XMASEVENT_LUCKNUMBER

// [버그수정] 산타의 마을 초대장이 수리되는 버그 수정 2008-12-18 by riverstyx
#define MODIFY_SANTACLAUSVILLAGE_INVITATION

// [버그수정] 루돌프펫, 눈사람 변신반지 전체수리 제외 2008-12-19 by riverstyx
#define MODIFY_XMASEVENTITEM_REPAIR
#endif // UPDATE_XMASEVENT_MAP_20080930

// [버그수정] 누적버그수정(goni)
#define MODIFY_BUGFIX_20081119

//[버그수정] 적대길드로 설정되있지 않은 유저에게도 데미지가 적용되는 버그(pelero)
#define MODIFY_FIRESCREAM_SPLASH_DAMAGE_BUGFIX_20081121

#if GAME_VERSION >= G_V_S4_6
// [버그수정] 같은 레벨의 다크스팅거가 엑알바트로스보우보다 데미지가 높은 버그(pelero)
#define MODIFY_DARKSTINGER_BUGFIX_20081119

// [버그수정] 스피드 핵 임시 처리 (riverstyx)
#define MODIFY_SPEEDHACK_20080605
#endif

#if GAME_VERSION >= G_V_99B
// [버그수정] 이벤트맵에서 이벤트가 종료되면 순간이동 스킬 사용 못하게..(pelero)
#define MODIFY_DONT_TELEPORT_EVNET_ENDING_IN_EVENTMAP_20081118
#endif

// [업데이트] 요정 +3 화살 추가(pelero)
#define UPDATE_ADD_ARROW_TYPE_PLUS_3_20081106

#if GAME_VERSION >= G_V_S4_5
// [업데이트] 신섭 추가로 변경된 정보를 적용 가능하게 설정 추가 2008-11-13 by riverstyx
#define ADD_NEWSERVER_20081113
#endif

#ifdef ADD_NEWSERVER_20081113
// [업데이트] 신섭 카오스캐슬 몬스터 사냥 시 드롭되는 보상 내역 추가 2008-11-13 by riverstyx
#ifndef MODIFY_CHAOSCASTLE_REWARD_20090608
#define ADD_NEWSERVER_CHAOSCASTLE_MONSTERITEMS_20081113
#endif
// [업데이트] 신섭 이벤트 Off
#define ADD_NEWSERVER_EVENTOFF_20081114
#endif // ADD_NEWSERVER_20081113

#if GAME_VERSION >= G_V_S4_6
// [업데이트] 상용화 7주년 이벤트(행운의 동전)(goni)
#define UPDATE_LUCKY_COIN_EVENT_20081029
#endif

// 인벤에서 수리할경우 마을서 수리할때 비해 3배요금 부과(goni)
#define UPDATE_INVEN_REPAIREMONEY_INC_20081112

#if GAME_VERSION >= G_V_S4_5
//[버그수정] 세루판 등장전 부화장 내에서 셔먼 스킬을 사용할 경우 파티원들이 바로 입구로 튕기는 버그 2008-11-07 by natinda
#define MODIFY_RECALLSKIL_BUGFIX_20081107
#endif

// [해킹] NPC에 보내지는 비정상적인 요청 차단(거래, 친구추가, 길드추가, 파티초대) - 2008-11-06 by riverstyx
#define MODIFY_REQUESTNPC_HACK

// [버그수정] 보석복사 버그수정 - riverstyx
// 유저간 거래상태에서 보석조합을(묶음) 요청 후 거래 취소를 요청하여 복사
#define MODIFY_JEWELMIXSYSTEM_BUGFIX_20081020

// [버그수정] 맵이동시시 이동 위치 버그수정(goni)
#define MODIFY_MAPMOVE_POSITION_SYNC_BUGFIX_200981024

#if GAME_VERSION >= G_V_S4_5
// [수치조정] 데몬과 정령의 내구도 감소율 조정(natinda)
#define MODIFY_DEMON_AND_SPRITE_DURABILITY_20081023
#endif

// [버그수정] 파이어스크림 강화시 스플래시 데미지가 적용 안되는 버그(pelero)
#define MODIFY_STRENGTHEN_FIRESCREAM_SPLASH_DAMAGE_BUGFIX_20081017

// [버그수정] 소켓조합 후 카오스박스 아이템 안내려오는 버그수정(goni)
#define MODIFY_SOCKET_CHAOSMIX_ITEM_MOVE_BUGFIX_200801021

// [버그수정] 포이즌 소뿔전사 변화 반지 착용시 체인 라이트닝 데미지가 이상적으로 증가하여 벨런스 붕괴 (일본/중국) 국내에도 적용해야 될 것으로 보임..(natinda)
#define MODIFY_CHAIN_LIGHTNING_BUGFIX_20081022

#ifdef CHAOS_MIX_UPGRADE
// [버그수정] 착용장비를 카오스 조합시 인벤토리가 풀일 경우 올라간 스탯 때문에 입지도 버리지도 못하는 문제 (natinda)
#define MODIFY_MIXSYSTEM_BUGFIX_20081016
#endif

// [버그수정] 마검스킬 보완및 수정(goni)
#define MODIFY_MAGUMSA_SKILL_BUGFIX_20081015

// [버그수정] GetBuffData 리턴값 NULL 검사(goni)
#define MODIFY_GETBUFFDATA_RETURNVALUE_NULLCHECK_BUGFIX_20080923

// [업데이트] 환영사원 랭킹서버 SendData 수정(goni)
#define UPDATE_ILLUTIONTEMPLE_RANKINGSERVER_SENDDATA_FIX_20080925

#if GAME_VERSION >= G_V_S3_E2
// 라이브 그룹 4차 버그수정
#define ADD_LIVE_GROUP_4TH_BUGFIX_20080908
#endif

#ifdef ADD_LIVE_GROUP_4TH_BUGFIX_20080908
// [업데이트] 이카루스 지역에서 다크로드 셔먼 스킬로 날개(3차 날개, 소환술사용, 다크호스)를
// 착용했는데도 소환이 안되는 버그(pelero) - WOPS번호:30852
#define MODIFY_RECALL_PARTY_SKILL_SUMMONER_BUGFIX_20080829
// [업데이트] 생명력 증가 버프가 있는 상황에서 스탯 부족으로
// 착용이 불가능한 아이템 착용시 생명력 증가 버프 효과가 2배로 
// 증가하는 버그(pelero) - WOPS번호:30867 
#define MODIFY_INCREASE_LIFE_AND_SETITEM_BUGFIX_20080829
// [업데이트] 마스터 레벨 캐릭터일 경우 엑설런트 옵션인 공격력증가+레벨/20 옵션이
// 접속 직후에는 레벨+마스터레벨/20이 적용이 안되는 버그(pelero) - WOPS번호:30853
#define MODIFY_MASTER_LEVEL_ATTACK20UP_BUGFIX_20080828
// [업데이트] 다크스피릿으로 공격시 엑설런트데미지, 더블데미지가
// 적용되지 않는 버그 (pelero) - WOPS번호:28829, 26208
//#define MODIFY_EX_DAMAGE_DARKSPRIT_BUGFIX_20080826
// [업데이트] 흑마법사 헬버스트 시전시 순간이동 스킬을 사용하여도
// 헬버스트 지속시간이 누적되는 버그(pelero) - WOPS번호:29010
#define MODIFY_TELEPORT_USING_HELLBURST_BUGFIX_20080822
// [업데이트] 환영사원에서 칼리마 마석이 생성되는 버그(pelero) - WOPS번호:27964
#define MODIFY_ILLUSION_TEMPLE_USE_KALIMA_GATE_BUGFIX_20080821
// [업데이트] 소환술사의 체인 라이트닝 스킬이 로스트타워 함정에 사용되는 버그(pelero) - WOPS번호:22175
#define MODIFY_CHAIN_LIGHTNING_USE_TRAP_BUGFIX_20080820
// [업데이트] 엘리트해골 변신 반지와 크리스마스 변신반지를 함께 착용할 경우
// 엘리트해골 변신 반지의 내구도만 감소하는 버그, 또한 (13, 10)의 변신반지(0~6)을
// 제외한 변신 반지들은 2중으로 내구도가 감소하고 있던 것을 수정(pelero) - WOPS번호:20886
#define MODIFY_CHANGE_RING_DURABILITY_BUGFIX_20080820
#endif // ADD_LIVE_GROUP_4TH_BUGFIX_20080908

// [버그수정] 마스터스킬 거리수정(goni)
#define MODIFY_MASTER_SKILL_DISTANCE_BUGFIX_20080909

// [버그수정] 플러스 조합시 날개 아이템을 일반 아이템 조합으로 설정 (hnine)
#define MODIFY_PLUS_ITEM_MIX_WING_SET_NORMAL_ITEM_20080916

// [버그수정] 시드스피어 조합 이후에 아이템 이동 불가 버그 수정 (hnine)
#define MODIFY_SOCKET_CHAOSMIX_ITEM_MOVE_BUGFIX_20080910

#ifdef MASTER_LEVEL_SKILL_SYSTEM_20071122
// [버그수정] 마스터스킬 방어력 증가값 수정(goni)
#define BUGFIX_MASTERSKILL_INC_DEFENSE_BUGFIX_20080917
#endif

// [업데이트] 열매공식 수정(goni)
#define UPDATE_FRUITPOINT_SUCCESSRATE_FIX_200809017

// [업데이트] 라클리온 보스존에서 로그인할 경우 무조건 안전지대로 이동(pelero)
#define MODIFY_RAKLION_BOSS_ZONE_BANISH_USER_2ND_20080917

// [업데이트] 라클리온 보스전 실패 후 보스 바로 삭제하도록 수정(pelero)
#define MODIFY_BATTLE_OF_SELUPAN_FAIL_DELETE_IMMEDIATELY_20080917

// [업데이트] 라클리온 보스전 참여 리스트에서 유저 삭제가 제대로 안되는 문제(pelero)
#define MODIFY_RAKLION_BATTLE_USER_DELETE_BUGFIX_20080916

// [업데이트] R단축키 저장이 제대로 안되는 버그(pelero)
#define MODIFY_R_HOTKEY_SAVE_BUGFIX_20080910

// [업데이트] 크라이울프에서 라클리온으로 이동되지 않는 버그(pelero)
#define MODIFY_CRYWOLF_MOVE_RAKLION_BUGFIX_20080910

#if GAME_VERSION >= G_V_S4_5
// [버그수정] 시즌4 신규스킬 보완 (goni)
#define MODIFY_SEASON4_NEWSKILL_20080909
#endif

#if GAME_VERSION >= G_V_S3_E1
// 라이브 그룹 3차 버그수정
#define ADD_LIVE_GROUP_3TH_BUGFIX_20080908
#endif

#ifdef ADD_LIVE_GROUP_3TH_BUGFIX_20080908
// [업데이트] 알바트로스 보우 사용시 내구도가 줄지 않는 버그(pelero) - WOPS번호:28574
#define MODIFY_ALBATROS_BOW_DURABILITY_BUGFIX_20080813
// [업데이트] 계정을 생성하고 처음으로 창고를 열경우
// 창고젠을 보내주지 않는 현상 수정(pelero) - WOPS번호:27340
#define MODIFY_NEW_ACCOUNT_WAREHOUSE_ZEN_BUGFIX_20080812
// [업데이트] 기사가 마스터 스킬중 액티브 스킬(회오리베기, 블로어, 분노의 일격)을
// 배운 상태에서 콤보를 사용할 경우 2번째 스킬과 3번째 스킬이 같아도
// 콤보가 발동 되는 버그 (pelero) - WOPS번호:27647
#define MODIFY_MASTER_LEVEL_COMBO_SKILL_BUGFIX_20080805
// [업데이트] 마스터레벨 액티브 스킬에 투자한 스킬을 슬롯에
// 저장하고 재접속하면 리셋되는 버그 (pelero) - WOPS번호:27127
#define MODIFY_MASTER_SKILL_HOTKEY_BUGFIX_20080804
// [업데이트] 내구도가 0인 문스톤 팬던트를 착용하고 있어도 효과가
// 적용되는 버그(즉사하지 않는 버그) (pelero) - WOPS번호:26919
#define MODIFY_BATTLE_OF_NIGHTMARE_MOONSTONE_PENDANT_BUGFIX_20080731
// [업데이트] 환영 사원에서도 쉐도우팬텀의 공방 버프가 유지되는 버그(pelero) - WOPS번호:26834
#define MODIFY_SHADOW_PHANTOM_BUFF_IN_ILLUSION_TEMPLE_BUGFIX_20080731
// [업데이트] 이카루스에서 펜릴을 장착했는데도 날개가 벗어지지 않는 버그(pelero)
// 다크호스만 착용했을때 이카루스로 이동하지 못하는 버그
#define MODIFY_SKYLAND_FENRIR_AND_WING_BUGFIX_20080730
// [업데이트]지팡이류에 민첩성 감소 옵션이 적용되지 않는 버그(pelero) - WOPS번호:26206
#define MODIFY_STAFF_DECREASE_DEXTERITY_BUGFIX_20080729
// [업데이트]이동불가 스킬에 당한 상태에서 스킬에 의한 밀림현상 수정(pelero) - WOPS번호:29691
#define MODIFY_BACK_SPRING_SKILL_BUGFIX_20080716
#endif // ADD_LIVE_GROUP_3TH_BUGFIX_20080908

// [버그수정] 플러스 아이템 조합에서 소켓 아이템이 380아이템으로 적용되는 버그를 수정 (hnine)
#define MODIFY_PLUSITEMMIX_SOCKET_ITEM_DIVISION_20080905

#ifdef ADD_MASTER_LEVEL_SKILL_SYSTEM_ACTIVE_20080107
// [업데이트] 공격시 안전지역이면 데미지 적용하지 않고 안전지대로 이동시킨다(pelero)
// 라클리온 이동 버그 관련하여 수정함
#define MODIFY_SAFEZONE_CHECK_ATTACK_20080903
#endif

// [업데이트] 고블린 카오스조합 아이템 레벨 성공확률 조정(goni)
#define UPDATE_CHAOSMIX_LEVELUP_RATE_20080904

// 뭉친패킷 처리(kuzimo)
#define HACKTOOL_KUZIMO

// [버그수정] 체인라이트닝 버그수정(goni)
#define MODIFY_CHAINLIGHTNING_BUGFIX_20080902

// [버그수정] 몬스터 걸치기 작업수정(goni)
#define MODIFY_MONSTER_ATTACK_BUGFIX_20080902

// [ 버그수정] 스피어 드럽 버그수정(goni)
//#define MODIFY_SPEAR_DROP_BUGFIX_20080901
#if GAME_VERSION >= G_V_S4_5
// [업데이트] 시즌4 추가 시세밸런스(goni)
#define UPDATE_SEASON4_MARKET_CONDITIONS_BALANCE_20080828

// [업데이트] 시즌 4 업데이트 - 소켓 아이템 드롭을 라클리온 맵으로 한정 (hnine)
#define MODIFY_LIMIT_SOCKET_ITEM_DROP_MAP_RAKLION_20080825

// [업데이트] 시즌 4 업데이트 - 로그추가 2차 (hnine)
#define ADD_SOCKET_OPTION_LOG_02_20080821		

// [업데이트] 시즌 4 업데이트 - 신규 소켓 옵션 추가 (hnine)
//#define MODIFY_SOCKET_ITEM_NEW_OPTION_20080818

// [업데이트] 시즌 4 업데이트 - 상점에서 판매되는 소켓 아이템에 소켓 슬롯 생성 추가 (hnine)
#define MODIFY_SEASON4_SHOP_SOCKET_ITEM_MAKE_SLOT_20080808
#endif

#ifdef MASTER_LEVEL_SKILL_SYSTEM_20071122
// [업데이트] 마스터스킬 추가 작업(goni)
#define UPDATE_MASTER_SKILL_4RANK_ADDITION_20080808
#endif

#if GAME_VERSION >= G_V_S4_5
// [업데이트] 이벤트맵 입장권 조합재료 가격 설정
#define UPDATE_EVENT_MAP_MIXiTEM_VALUE_200800808
#endif

// [업데이트] 젠 드랍율 축소(goni)
#define UPDATE_ZEN_DROP_DOWN_20080806

#if GAME_VERSION >= G_V_S4_5
//[버그수정] 무기스킬강화시 스킬 아이콘수정(goni)
#define MODIFY_WEAPONSKILL_STRENGTHEN_ICON_BUGFIX_20080807

// [업데이트] 스킬키 단축기 확장(goni)
#define UPDATE_SKILLKEY_EXPAND_20080804

// [버그수정] 시즌 4 업데이트 - 버그수정 2차 (hnine)
#define MODIFY_SEASON4_UPDATE_BUGFIX_02_20080804

// [버그수정] 콤보스킬 데이터구조체의 스킬값 확장(goni)
#define MODIFY_COMBOSKILLDATA_SKILLNUMBER_20080801
#endif

#if GAME_VERSION >= G_V_S4_5
// [버그수정] 재접속시 추가생명력 적용문제 수정(goni)
#define MODIFY_ADDLIFE_BUGFIX_20080730
#endif

// [업데이트] 시즌 4 업데이트 - 소켓 아이템 시스템 수정 (hnine)
#define MODIFY_SOCKET_OPTION_SYSTEM_20080725

// [버그수정] 맵서버이동시 인증부분 삭제 제거(goni)
#define MODIFY_GAMEGARD_AUTH_MAPSERVER_MOVE_20080723

// [업데이트]공성 성문, 석상 보완 작업(최대HP 값 증가) (pelero)
#define MODIFY_GATE_AND_STATUE_INCREASE_MAX_HP_20080718

#if GAME_VERSION >= G_V_S4_5
// [버그수정] 시즌 4 업데이트 - 버그수정 1차 (hnine)
#define MODIFY_SEASON4_UPDATE_BUGFIX_01_20080722

// [업데이트] 시즌 4 업데이트 - 소켓 아이템 버그 수정 5차 (hnine)
#define MODIFY_ITEM_SOCKET_OPTION_BUGFIX_05_20080715

// [업데이트] 시즌 4 업데이트 - 소켓 아이템 로그 추가 (hnine)
#define ADD_SOCKET_OPTION_LOG_20080715

// [업데이트] skill(kor).txt 스크립트 확장 - 스킬 타입(riverstyx)
// 일단 해외만 적용 국내도 적용해야함
#define ADD_EXPAND_SKILL_SCRIPT_FOR_SKILLTYPE_20080515

// [업데이트] 시즌 4 업데이트 - 소켓 아이템 버그 수정 4차 (hnine)
#define MODIFY_ITEM_SOCKET_OPTION_BUGFIX_04_20080710
#endif

// [버그수성] 타겟유저,소환몬인덱스 체크(goni)
#define MODIFY_TARGETNUMBER_RECALLMON_INDEX_BUFGIX_20080711

// [버그수정] 스킬 최종 요구에너지버그 수정(riverstyx)
#define MODIFY_SKILL_REQUIREENERGY_20080423

#if GAME_VERSION >= G_V_99B
// [버그수정] 유저 접속시 다크 스피릿 스킬 초기화 안되는 버그(pelero) - WOPS번호:20295
#define MODIFY_DARK_SPRIT_SKILL_INITIALIZE_BUGFIX_20080702
#endif

// [버그수정] 마검사가 가이온 세트 아이템 착용 후 힘스탯이 올라간 상태에서 블러드어택을 배우고
// 세트 아이템을 벗어 블러드어택 사용 가능 스탯이 아닌 상태에서도 블러드어택이 시전되는 버그(pelero) - WOPS번호:20674
#define MODIFY_BLOOD_ATTACK_AND_ADD_STRENGTH_BUGFIX_20080701

// [버그수정] 회오리베기 강화 스킬 습득시 스킬 범위가 줄어드는 버그(pelero) - WOPS번호:26969
#define MODIFY_ML_STRENGTHEN_WHEEL_RANGE_BUGFIX_20080630

// [버그수정] 칸투르 보스전 다크호스 버그(pelero) - WOPS번호:20444
#define MODIFY_KANTURU_ENTERANCE_DARKHORSE_BUGFIX_20080627

#if GAME_VERSION >= G_V_S4_5
// [버그수정] 다크로드 펫의 생명력 버그 수정(pelero) - WOPS번호:19787
#define MODIFY_DARKLORD_SEND_INFO_PROTOCOL_EXTEND_20080626
#endif

#ifdef MASTER_LEVEL_UP_SYSTEM_20070912
// [버그수정] 마스터 레벨끼리 악마의 광장에서 파티시 경험치 분배 버그 수정(pelero) - WOPS번호:29466
#define MODIFY_MASTER_LEVEL_DEVIL_SQUARE_PARTY_EXP_BUGFIX_20080625
#endif

// [버그수정] 3차 날개 옵션 5% 확률로 생명력 완전 회복 버그 수정(pelero) - WOPS번호:28215
#define MODIFY_THIRD_WING_OPTION_5_PERCENT_REFILL_ALL_BUGFIX_20080624

// [업데이트] GM 매크로 최대 확장 (hnine)
#define MODIFY_MAX_GMCMD_EXTEND_20080630

#if GAME_VERSION >= G_V_S4_5
// [업데이트] 시즌 4 업데이트 - 시즌 4 업데이트 추가 패치는 해당 디파인으로 On/off
#define ADD_SEASON_4_UPDATE_20080617
#endif

#ifdef ADD_SEASON_4_UPDATE_20080617
// [버그수정] 블러드캐슬 유저 인덱스 수정(goni)
#define MODIFY_BLOODCASTLE_USERINDEX_BUGFIX_20080709

// [업데이트] 시즌 4 업데이트 - 아이템 업그레이드/조합 수정 (hnine)
#define MODIFY_ITEM_UPGRADE_MIX_RATE_FIX_20080627
// [업데이트] 시즌 4 업데이트 - 마이너스 열매 공식 수정 (hnine)
#define MODIFY_MINUS_FRUIT_POINT_CALC_20080627

// [업데이트] 시즌4 블러드캐슬 스케줄 변경(goni)
#define UPDATE_BLOODECASTLE_SCADULE_20080624
// [업데이트] 시즌4 신규스킬 추가(goni)
#define ADD_SEASON4_NEW_SKILL_20080522
// [업데이트] 시즌4 신규캐릭터 환수스킬(Pollution)추가(goni)
#define UPDATE_ADD_SUMMONER_SKILL_POLLUTION_20080425
// [업데이트] 시즌 4 업데이트 - 소켓 아이템 시스템 (hnien)
//#define ADD_ITEM_SOCKET_OPTION_SYSTEM_20080415
// [업데이트] 시즌 4 업데이트 - 아이템 소켓 데이터 부분 확장 (hnine)
//#define ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
// [업데이트] 시즌 4 업데이트 - 소켓 아이템 조합 NPC (hnine)
#define ADD_ITEM_SOCKET_OPTION_MIX_20080415
// [업데이트] 시즌 4 업데이트 - 카오스 조합 프로토콜 확장 (hnine)
#define MODIFY_CHAOSMIX_PROTOCOL_EXTEND_20080526
// [업데이트] 라클리온 쿨러틴, 아이언 나이트 리젠시 좌표 버그(pelero)
#define MODIFY_RAKLION_COOLUTIN_AND_IRON_KNIGHT_REGEN_BUGFIX_20080828
// [업데이트] 부화장 폐쇄 후 유저의 처리(pelero)
#define MODIFY_RAKLION_BOSS_ZONE_BANISH_USER_20080818
// [업데이트] 세루판이 이동하면서 스킬을 사용하는 버그(pelero)
#define MODIFY_RAKLION_SELUPAN_MOVING_USE_SKILL_BUGFIX_20080813
// [업데이트]간혹 세루판이 나오지 않아서 라클리온 보스전의 전체 스케쥴이 멈추는 버그(pelero)
#define MODIFY_RAKLION_SELUPAN_NO_REGEN_BUGFIX_20080730
// [업데이트]세루판 등장 스킬 타겟 수정(pelero)
#define MODIFY_RAKLION_SELUPAN_FIRST_SKILL_BUGFIX_20080721
// [업데이트] 시즌4 이벤트용 로그 추가(pelero)
#define UPDATE_SEASON_4_EVENT_LOG_200800715
// [업데이트] 시즌4 업데이트 - 라클리온 보스전 버그 수정 2차(pelero)
#define MODIFY_RAKLION_BUGFIX_2ND_20080710
// [업데이트] 시즌4 업데이트 - 라클리온 보스전 버그 수정(pelero)
#define MODIFY_RAKLION_BUGFIX_20080707
// [업데이트] 신규맵 라클리온 추가(pelero)
#define	ADD_RAKLION_20080408
// [업데이트] 라클리온에서 사용하는 프로토콜(pelero)
#define RAKLION_PROTOCOL_20080625
// [업데이트] 세루판 관련 몬스터 스킬 갯수 추가 TSkillDefine.h (pelero)
#define UPDATE_MONSTER_SKILLUNIT_SLOT_EXTEND_20080514
// 시즌4 안정화 후에 삭제 바랍니다.
#define SEASON4_PATCH_GROOVING
#endif // ADD_SEASON_4_UPDATE_20080617

#ifdef ADD_ITEM_SOCKET_OPTION_SYSTEM_20080415
// [버그수정] 시드 추출 실패시 아이템의 레벨을 0~2 다운되도록 수정 (hnine)
#define MODIFY_SEED_EXTRACT_FAIL_RESULT_20080903

// [버그수정] 시드와 스피어의 드롭 확률을 설정 가능하도록 수정 (hnine)
#define MODIFY_SET_SEED_SPHERE_DROP_RATE_20080903
#endif

#ifdef ADD_ITEM_SOCKET_OPTION_SYSTEM_20080415
// [버그수정] 시즌 4 업데이트 - 소켓 아이템 드롭 기능 수정 (hnine)
#define MODIFY_SOCKET_ITEM_DROP_SYSTEM_FIX_20080828
#endif

#ifdef ADD_ITEM_SOCKET_OPTION_SYSTEM_20080415
// [업데이트] 시즌 4 업데이트 - 소켓 아이템 버그 수정 3차 (hnine)
#define MODIFY_ITEM_SOCKET_OPTION_BUGFIX_03_20080704

// [업데이트] 시즌 4 업데이트 - 소켓 아이템 버그 수정 2차 (hnine)
#define MODIFY_ITEM_SOCKET_OPTION_BUGFIX_02_20080630
#endif

// [버그수정] OBJECTSTRUCT생성시에 문제 가능성이 있어 재수정.테스트 요함.
#define MEM2_KUZIMO

// [버그수정] LNK4084 경고 메시지 제거를 위한 OBJECTSTRUCT gObj[MAX_OBJECT]의 Heap메모리 이동. 기타 버그 수정.
#define MEM_KUZIMO


#ifdef FOR_KOREA
// [업데이트] 시즌4 PC방 포인트 관련 수정
#ifdef PCBANG_POINT_SYSTEM_20070206
#define PCBANG_KUZIMO
#endif
// [보완작업] 패스워드 길이 12bytes로 수정(kuzimo)
//#define PW_KUZIMO
#endif // FOR_KOREA

// [버그수정] 악령 버그수정(goni)
#define MODIFY_EVIL_BUGFIX_20080618

#ifdef MASTER_LEVEL_SKILL_SYSTEM_20071122
// [버그수정] 몬스터 킬 시 SD, 마나 중첩 회복 버그수정(goni)
#define MODIFY_SKILL_ML_MONSTER_KILL_SD_BUGFIX_20080514
#endif

// [버그수정] AddMonster 수정(goni)
#define MODIFY_ADDMONSTER_BUGFIX_20080423

//[업데이트] 세트아이템 드랍 로그수정 (goni)
#define UPDATE_SET_ITEM_DROP_LOG_20080420

// [버그수정] 공성서버 진입 불가 관련 추적 로그 (hnine)
//#define MODIFY_CASTLE_MAP_MOVE_TRACE_LOG_20080418

#if GAME_VERSION >= G_V_S4_5
// [업데이트] 캐릭명 변경(goni)
#define UPDATE_CHANGE_CHARACTERNAME_20080410
#endif

#if GAME_VERSION >= G_V_S4_5
// [업데이트] NPC 레오 이벤트 아이템 백 셋트적용(goni)
#define UPDATE_NPC_REO_NEW_EVENTITEMBACK_20080408
#endif

//[버그수정] 아이템 겹치는 문제 수정(goni)
#define MODIFY_ITEMDURABILITY_BUGFIX_20080408

// [버그수정] 소환술사 위크니스, 이너베이션 PVP 적용시간 수정(goni)
#define MODIFY_SUMMONER_WEAKENESS_ENERVATION_PVPEFFECTTIME_BUGFIX_20080404

// [버그수정] 공성 직인등록시간 리셋수정(goni)
#define MODIFY_CASTLE_CROWN_ACCESS_TIME_CHECK_BUGFIX_20080403

#if GAME_VERSION >= G_V_S4_5
// [업데이트] 이벤트 아이템 백에 셋트아이템 추가(goni)
#define UPDATE_PROBABILITYiTEMBAG_ADD_SETITEM_20080329

// [업데이트] ItemSetOption(kor)에 소환술사 클래스 확장(goni)
#define UPDATE_SETOPTION_SCRIPT_ADD_CLASS_20080321

// [업데이트] 벚꽃놀이 이벤트(riverstyx)
#define ADD_EVENT_CHERRYBLOSSOM_20080312

// [업데이트] 각 이벤트맵 보상 경험치 배율 추가(pelero)
#define UPDATE_ADD_EVENT_MAP_EXP_RATE_20080320

// [업데이트] 마검사, 다크로드, 소환술사 파티 세트 경험치 추가(pelero)
#define UPDATE_ADD_NEW_PARTY_SET_EXP_20080325

// [업데이트] 아이템 시리얼 확장 (hnine)
#define MODIFY_ITEM_SERIAL_EXPAND_20080227
#endif

// [업데이트] 아이템 시리얼 중복체크 옵션 리로드 가능하도록 수정 (hnine)
#define MODIFY_SERIAL_CHECK_OPTION_RELOAD_20080212

//[버그수정] 스킬리스트 사이즈 수정(goni)
#define MODIFY_SKLL_LIST_SIZE_BUFFIX_20080221

// [업데이트] 쉐도운팬텀공방 최대레벨 스크립트로 변경(goni)
#define UPDATE_SHADOW_PHANTOM_MAX_LAVEL_LOAD_SCRIPT_20080220

// [업데이트] "/요청 off"시 적대관계 맺기/끊기 요청에대한 거부도 추가(goni)
#define UPDATE_REQUEST_OFF_ADD_RELATIONSHIP_20080219

#if GAME_VERSION >= G_V_S4_5
//해외로 빌드시 컴파일 에러가 발생하여 상위 디파인조건을 추가함 riverstyx
#ifdef FOR_KOREA
// [버그수정] 피씨방포인트상점 종료시 처리(goni)
#define MODIFY_PCBANGPOINTSHOP_CLOSEWINDOWS_BUGFIX_20080218
#endif // FOR_KOREA
#endif

//////////////////////////////////////////////////////////////////////////
// 시즌3plus 신규캐릭터 스킬추가
//////////////////////////////////////////////////////////////////////////
#if GAME_VERSION >= G_V_S2
// 380 아이템 엑 안떨어지게(goni)
#define MODIFY_380_EXCELENT_ITEM_DISABLE_20080212
#endif

// [버그수정] 슬립시킬 성공률 수정(goni)
#define MODIFY_SLEEP_SKILL_SUCCESSRATE_BUGFIX_20080125

// [업데이트] 로그추가(goni)
#define UPDATE_ADD_LOG_20080117

#if GAME_VERSION >= G_V_S4_5
// [업데이트] 옵션 키 레벨추가(goni)
#define UPDATE_OPTIONKEY_LEVEL_20080116

// [업데이트] 신규캐릭터 신규스킬 추가(goni)
#define UPDATE_SUMMONER_NEW_SKILL_20080111
#endif

// [버그수정] 신규캐릭터 summoner 3차날개 버그수정(goni)
#define MODIFY_SUMMONER_THIRD_WING_BUFGIX_20090109

#if GAME_VERSION >= G_V_S4_5
// [업데이트] 신규맵 평온의 늪 추가(goni)
#define UPDATE_NEWMAP_SWAMP_OF_CALMNESS_20080108
#endif
//////////////////////////////////////////////////////////////////////////

// [버그수정] 마라쥬 NPC 한테 말을 걸경우 상정 종료되 문제 수정(goni)
#define MODIFY_MIRAGE_NPC_ACT_CLOSESHOP_BUGFIX_20080123

#if GAME_VERSION >= G_V_S4_5
// [업데이트] 마스터레벨 입장 이벤트맵 입장권 재료 드롭확률 조정(goni)
#define UPDATE_MASTER_LEVEL_EVENTMAP_TICKET_METERIAL_DROPRATE_20080123
#endif

// [버그수정] 몬스터 생성시 락을 검(goni)
//	#define MODIFY_ADDMONSTER_ADDLOCK_20080117

// [버그수정] 버프 시스템 확장 7차 수정 (hnine)
#define MODIFY_BUFFSYSTEM_BUGFIX_07_20080109

// [버그수정] 이동제한 버그수정(goni)
#define MODIFY_MOVEMAP_BUGFIX_20080109

#ifdef DUEL_SYSTEM_20031028
//[버그수정] 상대방을 PK시 데미지 반사로 자신이 죽을경우 상데방이 PK적용 안되게 수정(goni)
#define MOIDFY_PK_DAMAGE_REFLECT_NOPK_BUGFIX_20081202
#endif

#if GAME_VERSION >= G_V_S3_E2
// [버그수정] 버프 시스템 확장 6차 수정 (hnine)
#define MODIFY_BUFFSYSTEM_BUGFIX_06_20080102
#endif

// [버그수정] 정당방위 시간 및 최대 인원수 수정(goni)
#define MODIFY_SELFDEFENSETIME_MAXSELFDEFIENSE_20071221
#if GAME_VERSION >= G_V_S3_E2
// [버그수정] 신규캐릭터 버그수정_1(goni)
#define MODIFY_SUMMONER_BUGFIX_1_20071221
#endif

#ifdef MODIFY_BUFF_SYSTEM_EXTENTION_20070917
// [버그수정] 버프 시스템 확장 5차 수정 (hnine)
#define MODIFY_BUFFSYSTEM_BUGFIX_05_20071220

// [버그수정] 버프 시스템 확장 4차 수정 (hnine)
#define MODIFY_BUFFSYSTEM_BUGFIX_04_20071216
#endif

#if GAME_VERSION >= G_V_S3_E2
// [버그수정] 공성시 공성 마크가 제대로 출력되지 않는 버그 수정 (hnine)
#define MODIFY_CASTLESIEGE_MARK_DISPLAY_20071216

// [버그수정] 신규캐릭터 장비 내구소 감소 버그수정(goni)
#define MODIFY_SUMMONER_ITEM_DURABILITY_DOWN_BUGFIX_20071213
#endif

// [업데이트] 해외 부분유료화 메크로 국내용으로 수정 (hnine)
#define MODIFY_INVEN_CLEAR_MACRO_20071212

#ifdef MODIFY_BUFF_SYSTEM_EXTENTION_20070917
// [업데이트] 버프 시스템 확장 3차 수정 (hnine)
#define MODIFY_BUFFSYSTEM_BUGFIX_03_20071211
#endif

// [로그추가] 일본 요청으로 경험치 출력 로그에 몬스터 인덱스와 이벤트 타입 추가(hnine)
#define MODIFY_EXP_LOG_MONSTER_EVENT_INDEX_20060906

// [버그수정] 클라이언트 접속시 끊기는 문제수정(goni)
#define MODIFY_JOIN_ERROR_BUGFIX_20071211

#ifdef MODIFY_BUFF_SYSTEM_EXTENTION_20070917
// [업데이트] 버프 시스템 확장 2차 수정 (hnine)
#define MODIFY_BUFFSYSTEM_BUGFIX_02_20071204
#endif

#if GAME_VERSION >= G_V_S3_E2
// [업데이트] 신규캐릭터 3차날개 조합생성( 차원의 날개 ) (goni)
#define ADD_SUMMONER_THIRD_WING_MIX_20071203

// [업데이트] 신규캐릭터 2차, 3차날개 (절망의 날개, 차원의 날개) (goni)
#define ADD_SUMMONER_SECOND_THIRD_WING_20071130
#endif

#ifdef MODIFY_BUFF_SYSTEM_EXTENTION_20070917
// [업데이트] 버프 시스템 확장 1차 수정 (hnine)
#define MODIFY_BUFFSYSTEM_BUGFIX_01_20071128
#endif

#if GAME_VERSION >= G_V_S3_E2
// [업데이트] 신규 UI 추가_단축키, 입장횟수(goni)
#define ADD_SEASON_3_NEW_UI_20071122

// [버그수정] 뷰포트 내의 유저들을 위한 버프 추가 삭제 프로토콜 변경 (hnine)
#define MODIFY_SEND_BUFFEFFECT_IN_VIEWPORT_20071121
#endif

// [버그수정] 카오스 조합시 조합 가격이 초과할 경우 확률이 마이너스 값을 가지는 버그 수정 (hnine)
#define MODIFY_CHAOSMIX_MONEY_OVER_MAX_FIX_RATE_20071114

#if GAME_VERSION >= G_V_S3_E2
// [업데이트] 시즌 3 신규 캐릭터 추가(goni)
#define ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912
#endif

// [버그수정] 인벤토리에서 같은 위치로 아이템 이동시 아이템 사라지는 문제(goni)
#define MODIFY_INVENTORY_ITEM_MOVE_BUGFIX_20071113

#if GAME_VERSION >= G_V_S3_E2
// [업데이트] 행운의 호박 드롭레벨 설정(goni)
#define UPDATE_PUMPKIN_OF_LUCK_DROP_LEVEL_20071026
#endif

// [버그수정] 파티시 정방설정 관련 버그수정(goni)
#define MODIFY_PARTY_SELFDEFENSE_BUG_FIX_20071022

// [업데이트] 타이틀바에 버전정보추가(goni)
#define UPDATE_TITLEBAR_VERSION_INFO_120071004

#if GAME_VERSION >= G_V_S3_E2
// [업데이트] 마스터레벨 시스템(RKFKA)
#define MASTER_LEVEL_SYSTEM_20070912	

// [업데이트] 버프 시스템 전면 수정 (hnine)
#define MODIFY_BUFF_SYSTEM_EXTENTION_20070917

// [업데이트] 버프 시스템 확장에 따른 기존 스킬 버프 효과 변경 (hnine)
#define MODIFY_OLD_BUFF_EFFECT_SYSTEM_20071004
#endif

#if GAME_VERSION >= G_V_S3_E1
// [업데이트] ItemAddOption에서 카테고리 별로 로드 하도록 설정 (hnine)
#define MODIFY_ITEMADDOPTION_LOAD_CATEGORY_20070712
#endif

#if GAME_VERSION >= G_V_S3_E2
// [업데이트] 시즌 3 신규 맵 엘베란드 추가(goni)
#define ADD_SEASON_3_NEW_MAP_20070910

// [버그수정] 공성전 사이클 조정 (RKFKA)
#define MODIFY_CASTLE_SIEGE_CYCLE_RESET_20071009
#endif

// [업데이트] 해외 부분유료화 on/off (hnine)
//#define ADD_PARTIALY_CHARGE_ON

// [업데이트] 해외 부분유료화 디파인 정리 (hnine)
#ifdef ADD_PARTIALY_CHARGE_ON
// [버그수정] 비약류 사용시 처리 순서 변경 (hnine)
//#define MODIFY_IMPROVE_POTION_CALC_PROCEDURE_20071023

// [업데이트] 부분유료화 : 환영사원 보상 경험치에 인장류 아이템 효과 설정 (hnine)
#define MODIFY_SET_MARK_EFFECT_AT_ILLUSIONTEMPLE_20071018
// [업데이트] 부분유료화 : 국내 아이템과 해외 아이템 중 인덱스가 겹치는 부분 수정 (hnine)
// 이동의 인장(13,52)->(13,59), 면죄부(13,53)->(13,60)
#define MODIFY_PCS_OVERLAP_ITEM_BUFF_INDEX_20071011

// [업데이트] 부분유료화 : 행운의 부적의 조합확률 적용을 환영사원 입장권과 3차날개 추가 (hnine)
#define MODIFY_PCS_LUCKY_CHARM_TICKET_3RD_WING_20071011

// [업데이트] 부분유료화 : 환영사원 자유 입장권 추가 (hnine)
#define ADD_PCS_ILLUSION_TEMPLE_FREE_TICKET_20071011

// 해외 부분유료화 1차 업데이트 (hnine)
#define ADD_PARTIALY_CHARGE_SYSTEM_01_20070110
// 해외 부분유료화 2차 업데이트 (hnine)
#define ADD_PARTIALY_CHARGE_SYSTEM_02_20070423
#if GAME_VERSION >= G_V_S3_E2
// 해외 부분유료화 3차 업데이트 (riverstyx, hnine)
#define ADD_PARTIALY_CHARGE_SYSTEM_03_20080407
// 해외 부분유료화 4차 업데이트 (riverstyx)
#define ADD_PARTIALY_CHARGE_SYSTEM_04_20080723
// 해외 부분유료화 5차 업데이트 (grooving)
#define ADD_PARTIALY_CHARGE_SYSTEM_05_20080930
// 해외 부분유료화 6차 업데이트 (natinda)	
#define ADD_PARTIALY_CHARGE_SYSTEM_06_20090129
// 해외 부분유료화 7차 업데이트 (pelero)	
//#define ADD_PARTIALY_CHARGE_SYSTEM_07_20090915
#endif

// 해외 부분유료화 2차는 1차 업데이트가 필요함.
#if defined ( ADD_PARTIALY_CHARGE_SYSTEM_02_20070423 ) && !defined ( ADD_PARTIALY_CHARGE_SYSTEM_01_20070110 )
#define ADD_PARTIALY_CHARGE_SYSTEM_01_20070110
#endif 
// [업데이트] 국내 시즌 2.5와 해외 부분유료화 통합시 발생 에러 수정 (hnine)
#define MODIFY_SEASON25_PCS_UNIFICATION_20070903
// [업데이트] 해외부분유료화 조합 관련 리팩토링 추가 (hnine)
#define MODIFY_PCS_CHAOSMIX_REFACTORING_20070903

// [버그수정] 환영사원 보상경험치 인장 혜택 삭제 (hnine)
// #define MODIFY_REMOVE_MARK_BENEFIT_ILLUSIONTEMPLE_REWARD_20071116

// [업데이트] 환영사원 메시지 로컬라이징 (hnine)
// #define MODIFY_ILLUSIONTEMPLE_MESSAGE_LOCALIZING_20071104
// -> MODIFY_ILLUSIONTEMPLE_MESSAGE_20080417

// [업데이트] 공성 물약 조합시 행운의 부적 사용 차단 (hnine)
#define MODIFY_LUCKYCHARM_BLOCK_USE_CASTLEPOTION_20071105

#if GAME_VERSION >= G_V_S3_E2
// [버그수정] 해외 블러드 캐슬 MasterLevel 입장 버그 수정(riverstyx)
#define MODIFY_MASTER_LEVEL_SYSTEM_20080414

// [버그수정] 해외 이동명령 버그 수정 (riverstyx)
#define MODIFY_MOVECOMMAND_20080415

// [업데이트] 환영사원 출력 메시지 업데이트 (riverstyx)
// 일단 해외만 적용
#define MODIFY_ILLUSIONTEMPLE_MESSAGE_20080417

// [업데이트] 마스터레벨을 0으로 설정할 수 있도록 수정(riverstyx)
#define MODIFY_MASTER_LEVEL_SYSTEM_COMMAND_20080417

// [버그수정] 10이하 유저 경험치 및 젠 손실 버그 수정(riverstyx)
// 국내도 있는 버그 일단 해외만 적용
#define MODIFY_MINLEVEL_EXPRATE_20080630

// [업데이트] 장착된 아이템은 못 팔도록 수정(riverstyx)
// 클라이언트 버그로 확인됨 디파인 삭제 예정 20081024 (riverstyx)
//#define ADD_NOT_SELL_EQUIPITEM_20080625

// [버그수정] 악마의 광장 확장된 맴에 종료 30초전 메시지 안가는 버그 수정 (riverstyx)
// 국내도 있는 버그 일단 해외만 적용
#define MODIFY_DEVILSQUARE_CLOSE_MSG_20080717

// 악마의 광장 조합 아이템 드랍 관련 - 해외만 적용(grooving)
#define DEVILSQARE_COMBINE_ITEM_DROP_20090114

// 전투축구 이벤트 일반 유저 명령어로 실행 불능 버그 수정 - 해외만 수정(grooving) 
#define BATTLESOCCERWAR_COMMAND_BUGFIX_20090310

// [버그수정] 세트 아이템 버그 수정(riverstyx)
//#define MODIFY_SETITEM_BUGFIX_20080731

// [버그수정] 공성서버 접속 사용자가 월드서버(사용자 MAX)로 이동시 발생하는 투명 버그 수정 
// 국내도 발생가능(riverstyx)
#define MODIFY_MOVECOMMAND_BUGFIX_20080806

// [버그수정] 장착된 아이템 내구도 체크 (riverstyx)
// 일단 EQUIPMENT_WEAPON_RIGHT, EQUIPMENT_WEAPON_LEFT 체크 - 국내도 있는 버그 일단 해외만 적용
#define MODIFY_EQUIPITEM_CHECKDURABILITY_20080811

// [버그수정] 아이템 구매/판매 시 구매(60) 판매(18) 제한에 걸린경우 처리함(riverstyx)
#define MODIFY_SELLBUYITEM_20080811

// [버그수정] 요정 세트 아이템 착용 후 힘스탯이 올라간 상태에서 아이스애로우를 배우고
// 세트 아이템을 벗어 아이스애로우 사용 가능 스탯이 아닌 상태에서도 시전되는 버그(riverstyx)
#define MODIFY_SKILL_ICEARROW_AND_ADD_DEXTERITY_BUGFIX_20080820
#endif

// 해외 부분유료화가 켜 있는 상태에서는 설정되면 안되는 디파인들
#else
#ifdef FOR_KOREA
#if GAME_VERSION >= G_V_S2_2
// [업데이트] 로그 추가 6차 (hnine)
#define EXTEND_LOG_SYSTEM_06_20070308
#endif
//////////////////////////////////////////////////////////////////////////
//	
// ** 아이템을 지급하는 NPC 정리(RKFKA)
// 루크(PC방 활성화): PC방에서 지급 / EventDB에 등록된 유저	/ 한 번			/ 아이템백에서 랜덤 지급
// 레오(화이트엔젤) : 접속하면 지급	/ EventDB에 등록된 유저	/ 한 번			/ 아이템백에서 랜덤 지급
// 앨런(레드이벤트)	: 접속하면 지급	/ 모든 유저				/ 하루에 한 번	/ 아이템백에서 랜덤 지급
//
//////////////////////////////////////////////////////////////////////////	
#if GAME_VERSION >= G_V_S3_E2
// [업데이트] 아이템지급 NPC 도우미 앨런 추가(RKFKA)
#define ADD_ITEM_GIVE_NPC_ALAN_20070823
#endif
#endif // FOR_KOREA
#endif // ADD_PARTIALY_CHARGE_ON

#if GAME_VERSION >= G_V_S4_5
// 해외 부부분유료화 아이템구매 요청결과 추가(goni)
#define UPDATE_BUY_CASHITEM_ERROR_CODE_20090410
#endif

// 해외 부분유료화 5차 업데이트 (grooving)
#ifdef ADD_PARTIALY_CHARGE_SYSTEM_05_20080930
// [업데이트] 5차 부분유료화 부활, 이동 부적 (grooving)
#define ADD_TELEPORT_CHARM_ITEM_20080930
#endif //ADD_PARTIALY_CHARGE_SYSTEM_05_20080930

// 부분유료화 4차 업데이트
#ifdef ADD_PARTIALY_CHARGE_SYSTEM_04_20080723
// [업데이트] 카오스 부적. 카오스부적 실패시 소멸되는 아이템 보호 //grooving
#define	ADD_CHAOSMIXCHARM_ITEM_20080702

// [업데이트] 4차 아이템 추가(치유의 인장, 신성의 인장) riverstyx
#define ADD_CASHITEM_4RD_MARK_20080723

// [업데이트] 4차 아이템 추가(전투의 스크롤, 강화의 스크롤) riverstyx
#define ADD_CASHITEM_4RD_SCROLL_20080723
#endif // ADD_PARTIALY_CHARGE_SYSTEM_04_20080723

// 부분유료화 3차 업데이트
#ifdef ADD_PARTIALY_CHARGE_SYSTEM_03_20080407
// [업데이트] 카오스카드 조합 시스템 확장 (hnine)
#define MODIFY_EXPEND_CHAOSCARD_SYSTEM_20080326

// [업데이트] 소환술사 캐릭터 카드 (riverstyx)
#define ADD_CHARCARD_SUMMONER_20080313

// [업데이트] 버프 아이템 캐쉬伺낯 
#define	MODIFY_BUFF_SYSTEM_EXTENTION_CASHSHOP_20080318

#ifdef MODIFY_BUFF_SYSTEM_EXTENTION_CASHSHOP_20080318
// [버그수정] 버프 아이템(비약) 사용만료 후 능력치 계산을 다시 하도록 수정(riverstyx)
#define MODIFY_BUFFITEM_MEDICINE_20080424
#endif // MODIFY_BUFF_SYSTEM_EXTENTION_CASHSHOP_20080318

// [버그수정] 버프 아이템(비약) 셋트 아이템 능력치 계산 부분 수정(riverstyx)
#define MODIFY_BUFFITEM_MEDICINE_SETITEM_20080424

// [버그수정] 버프 아이템(인장) 유지의 인장 사용시 블러드 캐슬 경험치가 증가되는 버그 수정(riverstyx)
#define MODIFY_MARKITEM_20080506

// [버그수정] 버프 아이템(비약) 셋트 아이템 능력치 계산 부분 수정(riverstyx)
#define MODIFY_BUFFITEM_MEDICINE_SETITEM_20080709
#endif // ADD_PARTIALY_CHARGE_SYSTEM_03_20080407

// [업데이트] 인장 아이템 추가 (hnine)
#define ADD_PCS_MARK_OF_EXP_20070205

#ifdef ADD_PARTIALY_CHARGE_SYSTEM_02_20070423
// [버그수정] 칼리마 자유 입장권 사용 실패 부분 처리 추가 (hnine)
#define MODIFY_KALIMA_FREETICKET_USE_RESULT_20070830

// [버그수정] 리셋열매 결과 코드 추가 (hnine)
#define MODIFY_RESET_FRUITS_RESULT_TYPE_20070821
// [버그수정] 엘도라도 이벤트의 옵션 로드 순서를 바꿈 (hnine)
#define MODIFY_ELDORADO_EVENT_OPTION_LOAD_SEQUEANCE_20070821

// [버그수정] ItemAddOption의 추가효과를 Add변수로 적용시키도록 변경 (hnine)
#define MODIFY_ITEMADDOPTION_VARIABLE_20070725
// [업데이트] 확장 열매 사용시 감소 스텟이 기본 스텟 이하일 경우 기본 스텟 까지만 초기화 되도록 수정 (hnine)
#define MODIFY_PCS_FRUITS_EX_DECREASE_POINT_SET_DEFAULT_20070806
// [버그수정] 캐쉬 아이템 이동 옵션에 희귀 아이템 티켓 6 추가 (hnine)
#define MODIFY_ADD_CASHITEM_MOVE_CHECK_ITEM_20070821
// [버그수정] ItemAddOption의 옵션은 할로윈 아이템과 부분유료화 아이템의 효과를 분리해서 적용시킨다.
#define MODIFY_ITEMADDOPTION_SET_EFFECT_20070801
// [업데이트] 아이탬 구매시 아이템의 최대 겹치기 갯수만큼 더해주도록 설정 (hnine)
#define MODIFY_OVERLAP_ITEM_DURATION_20070730
// [업데이트] ItemAddOption에서 카테고리 별로 로드 하도록 설정 (hnine)
#define MODIFY_ITEMADDOPTION_LOAD_CATEGORY_20070712
// [업데이트] 기간제 아이템 슬롯 확장 (hnine)
#define MODIFY_PERIODITEM_SLOT_EXTEND_20070423
// [업데이트] 캐쉬 아이템 리스트 우선 순위 추가 (hnine)
#define ADD_CASH_ITEMLIST_RATIO_20070430
// [업데이트] 엘리트 물약 (풀 회복 물약) 추가 (hnine)
#define ADD_FULL_RECOVERY_POTION_20070719
// [업데이트] 열매 시스템 확장 (hnine)
#define ADD_PCS_FRUITS_POINT_EXTENTION_20070430
// [업데이트] 면죄부 추가 (hnine)
#define ADD_PCS_INDULGENCE_20070504
// [업데이트] 100% 회복 물약 추가 (hnine)
#define ADD_PCS_FULL_RECOVERY_POTION_20070508
// [업데이트] 멥 이동 제한을 확인하는 상태 수정 (hnine)
#define MODIFY_MAPMOVEBOUNCE_CHECK_OPTION_20070521
// [업데이트] 강화의 비약 추가 (hnine)
#define ADD_PCS_IMPROVE_POTION_20070718
// [업데이트] 엘리트 스크롤 추가 (hnine)
#define ADD_ELITE_SCROLL_20070521
#endif // ADD_PARTIALY_CHARGE_SYSTEM_02_20070423

#ifdef ADD_PARTIALY_CHARGE_SYSTEM_01_20070110
// [버그수정] 개인 상점을 연 상태로 카오스 카도 조합을 할 수 없음. (hnine)
#define MODIFY_CHAOSCARD_MIX_BLOCK_PSHOP_USE_20070713

// [버그수정] 블러드캐슬 자유 입장권 관련 버그 수정 (hnine)
#define MODIFY_BLOODCASTLE_ENTER_ITEMCHECK_20070627

// [버그수정] 기간제 아이템 관리를 위한 크리티컬섹션 추가 (hnine)
//#define MODIFY_PERIOD_ITEM_SYSTEM_CRITICALSECTION_20070619

// [버그수정] 기간제 아이템 구입 시 DB에 이미 사용 중인 아이템이 있는지 확인 한다. (hnine) - 임시 삭제
//#define MODIFY_CHECK_PERIOD_ITEM_LIST_AT_ITEMBUY_20070619

#if GAME_VERSION >= G_V_S2_2
#ifndef FOR_JAPAN
// [업데이트] 인장 효과를 다른 유저에게도 보여준다. (hnine)
#define MODIFY_PERIODITEM_EFFECT_ADD_VIEWPORT_20070601
#endif // FOR_JAPAN

// [버그수정] 블러드 캐슬 자유 입장권 사용시 메시지 버그 수정 (hnine)
#define MODIFY_FREE_BLOODCASTLE_ENTER_CHECK_20070531

// [버그수정] 인장 효과 크라이울프 보상 적험치 적용 (hnine)
#define MODIFY_MARKITEM_EFFECT_USE_CRYWOLF_REWARD_20070502

// [버그수정] 유지의 인장 효과가 접속 종료 시간에 사라지는 버그 수정 (hnine)
#define MODIFY_PERIODITEM_EFFECT_DURING_CLOSETIME_20070416
#endif

// [버그수정] 플러스 아이템 조합시 로그 변경 (hnine)
#define MODIFY_PLUSITEM_CHAOSMIX_LOG_BUGFIX_20070330

#if GAME_VERSION >= G_V_S2_2
// [버그수정] 이벤트 맵에서의 인장 아이템 효과 삭제 - 유지의 인장 제외 (hnine)
#define MODIFY_MARKITEM_EFFECT_REMOVE_IN_EVENTMAP_20070328

// [버그수정] 행운의 부적 사용 범위에 날개 조합 추가 (hnine)
#define MODIFY_LUCKYCHARM_ADD_WINGMIX_20070328
#endif

// [버그수정] 게임 종료시 카오스 조합 아이템 리스트 저장 (hnine)
#define MODIFY_SAVE_CHAOSBOX_ITEMLIST_AT_LOGOUT_20070328

// [버그수정] 부분 유료화 기간제 시스템 1차 수정 (hnine)
#define MODIFY_PERIOD_ITEM_SYSTEM_BUGFIX_20070326

#if GAME_VERSION >= G_V_S2_2
// [버그수정] 잭 오 랜턴의 축복 물약 사용시 튕기는 버그 수정 (hnine)
#define MODIFY_JOL_BLESS_POTION_USE_EFFECT_20061030
// [업데이트] 할로윈 데이 이벤트 작업 (hnine)
#define HALLOWINDAY_JACK_O_LANTERN_EVENT_20061017
#endif

// [업데이트] 캐쉬 샵 시스템 추가 (hnine)
#define ADD_PARTIALY_CHARGE_CASH_SHOP_20070117
// [업데이트] 캐쉬 아이템 기간제 시스템 추가 (hnine)
#define ADD_PARTIALY_CHARGE_PERIOD_SYSTEM_20070205
// [업데이트] 복권 아이템 (hnine)
#define ADD_PCS_LOTTERY_SYSTEM_20070117
// [업데이트] 인장 아이템의 맵 이동 제한 (hnine)
#define ADD_PCS_MARKITEM_MAP_MOVE_BOUND_20070221
// [업데이트] 이벤트 맵 자유 입장권
#define ADD_PCS_EVENT_MAP_FREE_TICKET_20070110
// [업데이트] 조합률 상승 아이템
#define ADD_PCS_CHAOSMIX_SUCCESS_RATE_UPGRADE_CHARM_20070111
// [업데이트] 카오스 조합 확률 조정
#define MODIFY_CHAOSMIX_RATE_FIX_20070304
// 2차 업데이트 예정 컨텐츠
#endif // ADD_PARTIALY_CHARGE_SYSTEM_01_20070110

#if GAME_VERSION >= G_V_S2_2
// 부분 유료화 아이템 추가를 위해 필요한 디파인들.
// [업데이트] 캐쉬 아이템 효과 적용을 위한 ItemAddOption.h 추가
#define ITEM_ADD_OPTION_20061019
#endif

// [업데이트] 젠증가 옵션 추가(commonserver.cfg) (RKFKA)
#define ADD_ZEN_OPTION_20070903

#if GAME_VERSION >= G_V_S3_E1
// [업데이트] 이벤트 맵_환영 사원(goni)
#define ADD_EVENT_MAP_ILLUSION_TEMPLE_20070328
#endif

#ifdef ADD_EVENT_MAP_ILLUSION_TEMPLE_20070328
// [버그수정] 피의두루마리 조합재료 가격표시 오류 수정 (goni)
#define MODIFY_ILLUSIONTEMPLE_ITEMVALUE_BUFGIX_20070904 
#endif

// [버그수정] 개인이 개인 공격시 정방 안걸리는 버그 수정 (goni)
#define MODIFY_SELFDEFENSE_20070904

#if GAME_VERSION >= G_V_S3_E1
// [업데이트] 추석 몬스터 이벤트(RKFKA)
#define CHUSEOK_MONSTER_EVENT_20070823

// [업데이트] 공성 직인 등록중 실패시 누적시간 감소 패널티 삭제 (RKFKA)
#define MODIFY_CASTLE_CROWN_ACCESS_TIME_20070828
#endif

// [업데이트] 아이템 백을 읽을 때 기본으로 사용할 함수 설정 (RKFKA)
#define MODIFY_EVENTITEMBAG_BASIC_SET_20070823

// [버그수정[ 8 월 버그수정(goni)
#define MODIFY_0708_BUFFIX_20070820

#ifdef ADD_EVENT_MAP_ILLUSION_TEMPLE_20070328
// [버그수정] 환영사원 버그수정_6 (goni)
#define MODIFY_ILLUSIONTEMPLE_BUGFIX_6_200708013
#endif

#if GAME_VERSION >= G_V_S3_E1
// [업데이트] 로그 추가 8차 (hnine)
#define EXTEND_LOG_SYSTEM_08_20070810
#endif

// [버그수정] 시련의땅 입장 금액 조건확인 수정 (RKFKA)
#define MODIFY_CASTLE_HUNTZONE_TAX_BUGFIX_20070806

#ifdef ADD_EVENT_MAP_ILLUSION_TEMPLE_20070328
// [버그수정] 환영사원 버그수정_5(goni)
#define MODIFY_ILLUSIONTEMPLE_BUGFIX_5_20070807

// [버그수정] 환영사원 버그수정_4(goni)
#define MODIFY_ILLUSIONTEMPLE_BUGFIX_4_20070802
#endif

// [버그수정] PK 시스템 개선 버그수정_공성시 PK 유저 파티 패널티 제거(goni)
#define MODIFY_PK_SYSTEM_BUGFIX_2_20070731

#ifdef ADD_EVENT_MAP_ILLUSION_TEMPLE_20070328
// [버그수정] 환영사원 버그수정_3, MAX_OBJ증가(goni)
#define MODIFY_ILLUSIONTEMPLE_BUGFIX_3_20070731
#endif

#if GAME_VERSION >= G_V_S3_E1
// [로그수정] 3차전직 로그수정(RKFKA)
#define MODIFY_LOG_THIRD_CHANGEUP_20070801

// [로그추가] 환영사원 로그추가(goni)
#define ADD_LOG_ILLUSION_TEMPLE_1_20070727
#endif

#ifdef ADD_EVENT_MAP_ILLUSION_TEMPLE_20070328
// [버그수정] 환영사원 버그수정_2(goni)
#define MODIFY_ILLUSIONTEMPLE_BUGFIX_2_20070724

// [버그수정] 환영사원 버그수정_1(goni)
#define MODIFY_ILLUSIONTEMPLE_BUGFIX_1_20070723
#endif

// [버그수정] 최대 대미지 유저 검색시 버그수정(goni)
#define MODIFY_MAXHITUSER_BUG_FIX_20070711

#if GAME_VERSION >= G_V_S3_E1
// 환영사원 스크립트 보강( 보상경험치 증가율, 최소 Skill 사용 횟수 )(goni)
#define UPDATE_ILLUSION_TEMPLE_SCRIPT_20070710
#endif

#if GAME_VERSION >= G_V_S3_E1
// [버그수정] 블러드 캐슬 시작 시간 변경 버그 수정(goni)
#define MODIFY_BLOODECASTLE_SCADULE_BUGFIX_20070710
#endif

#if GAME_VERSION >= G_V_S3_E1
// [업데이트] 환영사원 비활성화시 수정(goni)
#define MODIFY_ILLUSION_TEMPLE_SCEDULE_20070703

// [업데이트] 환영 펜릴 추가(goni)
#define ADD_ILLUSION_FENRIR_20070703
#endif

#ifdef MODIFY_QUEST_SYSTEM_20070525
// [버그수정] 퀘스트 몬스터 킬카운트 정보 초기화 버그 수정 (RKFKA)
#define MODIFY_QUEST_MONSTER_KILL_COUNT_BUGFIX_20070704
#endif

#if GAME_VERSION >= G_V_S3_E1
// [업데이트] 블러드 캐슬 시작 시간대(짝수 홀수) 스크립트로 변경(goni)
#define UPDATE_BLOODECASTLE_SCADULE_20070702

// [업데이트] 환영사원 들어가기전 MAX_MAP 수정(goni)
#define UPDATE_BEFORE_ILLUSION_TEMPLE_MAX_MAP_20070702

// [버그수정] 환영사원 버그수정(goni)
#define MODIFY_ILLUSION_TEMPLE_20070629

// [업데이트]400레벨 달성시 파티원로그 추가(goni)
#define ADD_LOG_400LEVELUP_PARTY_20070628

// [업데이트] 3차 날개 추가 (RKFKA)
#define ADD_THIRD_WING_20070525
// [업데이트] 3차 전직 시스템 (RKFKA)
#define THIRD_CHANGEUP_SYSTEM_20070507

// [버그수정] 퀘스트 시스템 버그수정 및 보완 (RKFKA)
#define MODIFY_QUEST_SYSTEM_20070525

// [업데이트] 악마의 광장 시작시간 스케줄 추가(goni)
#define UPDATE_DEVIL_SQUARE_START_TIME_20070511
#endif

// [업데이트] 조합 시스템 개선 (RKFKA)
#define MODIFY_MIX_SYSTEM_20070518	

// [버그수정] 라이프스톤을 던지자마자 적용되는 버그(생성시간 이후에 적용되어야 함) (RKFKA)
#define MODIFY_LIFESTONE_BUGFIX_20070426


#if GAME_VERSION >= G_V_S3_E1
// [업데이트] Shop14 추가-> WzVersionManager, WzAuthGs, WzFsGate 같이 수정(RKFKA)
#define	ADD_SHOP_14_20070308
#endif

// [버그수정] 레알서버 고가품 등록아이템 드랍버그 수정(goni)
#define MODIFY_VALUABLE_ITME_BUGFIX_20070828

// [버그수정] 용사, 전사, 마법의 반지 거래 버그수정(goni)
#define MODIFY_MAGICIARINGRING_TRADE_BUGFIX_20070328

// [버그수정] PK 시스템 개선 버그 수정_2단계 이상 살인마와 파티중인 캐릭을 죽였을경우 살인마가 되는부분 수정(goni)
#define MODIFY_PK_SYSTEM_BUGFIX_20070323

#if GAME_VERSION >= G_V_S3_E1
// [업데이트] 로그 추가 7차 (hnine)
#define EXTEND_LOG_SYSTEM_07_20070320

// [업데이트] 블러드 캐슬 성문 생성 로그 추가(goni)
#define ADD_LOG_BLOODCASTLE_DOOR_20070321
#endif

// [버그수정] 카오 유저가 블러드 캐슬에 입장을 위해 천사와 대화시 메시지 수정(goni)
#define MODIFY_BLOODCASTLE_PK_USER_ENTER_MESSAGE_20070321

// [버그수정] 정당방위 종료시 종료 실패 메시지 추가(goni)
#define MODIFY_SELFDEFENSE_CLOSE_20070321

// [버그수정] 파티 경험치 획득 버그 2차 수정(goni)
#define MODIFY_PARTY_PLAY_EXPERIENCE_2_20070320

// [버그수정] 카오스캐슬 안전지대에서만 입장가능으로 수정(goni)
#define MODIFY_ENTER_CHOSCASTLE_BUGFIX_20070316

#if GAME_VERSION >= G_V_S3_E1
// [업데이트] 변신 반지 착용시 뷰포트 정보에 장비정보 추가(goni)
#define UPDATE_VIEWPORTCREATE_CHANGE_ADD_CHARSET_20070314

// [업데이트] 고가품 설정 아이템 추가 및 삭제(goni)
#define UPDATE_VALUABLE_ITEM_20070307

// [버그수정] 잃어버린표식 이동시 아이템 사라지는 버그수정(goni)
#define MODIFY_MOVE_KUNDUN_MARK_20070307

// [업데이트] 폭죽판매 NPC(goni)
#define ADD_FIRECRACKER_NPC_20070306

#if GAME_VERSION >= G_V_S4_6
// [업데이트] PK 시스템 개선(goni)
#define UPDATE_PK_SYSTEM_20070302
#endif

// [업데이트] 세도우 팬텀 공방 보완(goni)
#define UPDATE_SHADOW_PHANTOM_20070302

// [업데이트] GM 기능 추가: GM 선물상자추가, GM 소환지역 추가, GM 마크 활성화, GM 콘솔 기능 추가, GM 캐릭터 변신반지 추가(goni)
#define UPDATE_GM_FUNCTION_20070228

// [업데이트] 이벤트 아이템 상자 드롭엑설런트 아이템 로그 추가(goni)
#define ADD_LOG_EVENT_DROP_EXITEM_20070308
#endif

// [버그 수정] 상자 발 밑에 떨어지는 현상 수정(goni)
#define MODIFY_BOX_DROP_POSITION_20070308

// [버그수정] 공성전 시작시 시련의 땅에 있는 모든 유저를 로랜협곡 앞마당으로 보낸다.(RKFKA)
#define MODIFY_CASTLEHUNTZONE_USER_BUGFIX_20070223

// [소스수정] 데빌스퀘어에서 랭킹서버로 보내는 주기적인 메세지 삭제(RKFKA)
#define DELETE_DEVILSQURE_MESSAGE_TO_RANKINGSERVER_20070223

#if GAME_VERSION >= G_V_S3_E1
// [버그 수정] 변신반지 거래 버그(goni)
#define MODEFY_CHAGNE_RING_TRADE_INVENTORY_20070213

// [버그 수정] 잃어버린 지도를 수동으로 겹칠때 표식이 사라지지 않는 버그(goni)
#define MODIFY_CREATE_LOSTMAP_ITEM_20070209

// [버그 수정] 파티후 다른지역에서 사냥시 경험치 획득 버그_레벨차 200이상(goni)
#define MODIFY_PARTY_PLAY_EXPERIENCE_20070208

// [업데이트] 발렌타인데이 상자 드롭엑설런트 아이템 로그 추가(goni)
#define ADD_LOG_VALENTINES_DAY_DROP_EXITEM_20070212

// [버그 수정] 발렌타인데이 상자 발 밑에 떨어지는 현상 수정(goni)
#define MODIFY_VALENTINES_DAY_BOX_DROP_20070202

// [업데이트] 설날복주머니 추가(goni)
#define UPDATE_NEWYEAR_LUCKYBAG_MONSTER_20070131

// [업데이트] 카오스캐슬 시스템변경 - 시간이 끝나 유저가 1명 남으면 몬스터가 있어도 성공(RKFKA)->적용 보류
//#define MODIFY_CHAOSCASTLE_SYSTEM_CHANGE_SUCCESS_FLOW_20070129

// [업데이트] 물자보급관 파멜라, 안젤라 추가(goni)
#define UPDATE_QUARTERMASTER_NPC_20070122
#endif

// [업데이트] 확률 별 이벤트 아이템 가방 추가(goni)
#define UPDATE_EVENT_ITEM_BAG_EXTEND_20070131

// [업데이트] 카오스캐슬에서 몬스터 남은 수를 판단하는 루틴 변경(RKFKA)
#define MODIFY_CHOSCASTLE_MONSTER_COUNT_RECAL_20070119

// [버그수정] 법사 스킬 악령 서버판단으로 변경 (RKFKA) -> 적용보류
//#define MODIFY_SKILL_EVEIL_AT_SERVER_20070117

#if GAME_VERSION >= G_V_S3_E1
// [업데이트] 용사, 전사(우정의 돌)의 반지 추가/수정(goni)
#define UPDATE_LOWLEVEL_SUPPORT_RING_20070119

// [버그추적] 카오스캐슬에서 몬스터가 남아 실패한 경우 몬스터의 좌표를 로그로 남긴다.(RKFKA)
#define ADD_LOG_CHAOSCASTLE_LEFT_MONSTER_ATTR_20070118

// [업데이트] 방어력/공격력향상 스킬 적용시 이전보다 조건이 나쁘면 적용하지 않는다.(RKFKA)
#define MODIFY_ELF_DEFENCE_ATTACK_VALUE_UP_SKILL_20070110
#endif

// [버그수정] 알바트로스 보우 버그 수정 (goni)
#define MODIFY_ALBATROS_BOW_BUGFIX_20070105

#if GAME_VERSION >= G_V_S2_2
// [업데이트] 크리스마스의 별 아이템 추가 (RKFKA)
#define CHRISTMAS_STAR_20061211

// [업데이트] 크리스마스 이벤트 산타크로스 변신반지 (hnine)
#define CHRISTMAS_SANTA_POLYMORPH_RING_20061117

// [업데이트] 공성전 참여길드로 선정된 길드의 점수를 표기한다. (RKFKA)
#define ADD_CASTLE_TOTAL_GUILD_SCORE_20061123

// [업데이트] 로그 추가 5차 (hnine)
#define EXTEND_LOG_SYSTEM_05_20060823

// [버그수정] 행운의 호박이 드롭되는 버그 수정 (hnine)
#define MODIFY_BLOCK_PUMPKIN_OF_LUCK_DROP_20061120
#endif

// [버그수정] 카오스캐슬 버그 수정 2차 (RKFKA)
#define MODIFY_CHAOSCASTLE_BUGFIX2_20061026

#if GAME_VERSION >= G_V_S2_2
// [버그수정] 잭 오 랜턴의 축복 물약 사용시 튕기는 버그 수정 (hnine)
#define MODIFY_JOL_BLESS_POTION_USE_EFFECT_20061030

// [버그수정] 조화의 보석 옵션의 초기값이 FF로 저장되는 버그 수정 (hnine)
#define MODIFY_HARMONY_OPTION_INIT_VALUE_FIX_20061019

// [업데이트] 할로윈 데이 이벤트 작업 (hnine)
#define HALLOWINDAY_JACK_O_LANTERN_EVENT_20061017

// [업데이트] 할로윈 변신반지 작업 (hnine)
#define HALLOWINDAY_JACK_O_LANTERN_MORPH_RING_20061017
#endif

#if GAME_VERSION >= G_V_99B
// 카오스 캐슬
#define CHAOSCASTLE_SYSTEM_20040408						// 카오스 캐슬 이벤트	
#define CHAOSCASTLE_TIME_BUGFIX_20040508				// 카오스 캐슬 시간 버그 수정

// 반지의 제왕 이벤트 -> 반지 던지기 이벤트
#define RING_EVENT_ITEMBOX_20031124

// 내 친구 이벤트 관련  (b4nfter)
//#define FRIENDSHIP_STONE_EXCHANGE_20040206			// 우정의돌 환전 시 체크
#define FRIENDSHIP_EVENT_RING_BOX_20040211				// 전사의반지 이벤트
#endif

#ifdef CHAOSCASTLE_SYSTEM_20040408
// [버그수정] 카오스캐슬 버그 수정 (RKFKA)
#define MODIFY_CHAOSCASTLE_BUGFIX_20060919
#endif

#if GAME_VERSION >= G_V_S2_2
// [업데이트] 카오스캐슬 제도 보상을 삭제한다. (hnine)
#define MODIFY_DELETE_ZETTO_EVENT_20061121
#endif

#if GAME_VERSION >= G_V_S4_5
// [업데이트] PC방 미납자 메시지를 주기적으로 출력하도록 수정 (hnine)
#define MODIFY_PCBANG_DEFAULTER_MESSAGE_20061011
#endif

// [버그수정] 칸투르 나이트메어전 성공,실패 초기화 버그 수정(RKFKA)
#define MODIFY_KANTURU_NIGHTMARE_INIT_BUGFIX_20061010

#ifdef NEW_SKILL_FORSKYLAND
// [버그수정] 요정 아이스애로우스킬. 미스가 난 경우 아이스적용 안되도록 수정. ( hjlim )
#define MODIFY_ELF_ICEARROWSKILL_BUGFIX_20060914
#endif

// [버그수정] 다크로드 - 어스퀘이크 스킬. 필요에너지 버그 ( hjlim )
#define MODIFY_DARKLORD_EARTHQUAKE_REQENERGY_BUGFIX_20060914

// [버그수정] 380 아이템 드롭시 380옵션이 사라지는 버그 수정 (hnine)
#define MODIFY_380_ITEM_OPTION_DELETE_AT_DROP_20060919

// [버그추적] 카오스캐슬, 블러드캐슬 버그 추적 로그 추가(RKFKA)
#define ADD_LOG_FOR_CASTLE_BUG_20060911

// [업데이트] 해외 시즌 2 패치를 위한 수정 ( PC방 전용 이벤트의 에러를 처리를 위한 디파인)
#ifndef FOR_KOREA
#define MODIFY_SEASON_02_20060908
#endif

#if !defined( MODIFY_SEASON_02_20060908 ) && GAME_VERSION >= G_V_S4_5
// [업데이트] PC방 활성화 이벤트 (RKFKA) - PC방 쿠폰이벤트를 그대로 사용하되 아이템 드랍처리만 변경되었다.
#define PCBANG_REVITALIZATION_EVENT_20060830

// [업데이트] 화이트엔젤 아이템 지급 이벤트 (RKFKA)
#define WHITEANGEL_GET_ITEM_EVENT_20060822

// [버그수정] PC방 이벤트 카오스캐슬 무료 입장 - 버그 수정(RKFKA)
#define MODIFY_PCBANG_EVENT_FREE_CHAOSCASTLE_20060331

// [업데이트] PC방 이벤트 - 카오스캐슬 무료입장 (RKFKA)
#define PCBANG_EVENT_FREE_CHAOSCASTLE_20060307

// [업데이트] PC방 전용 이벤트 - 쿠폰발행 이벤트 (hnine)
#define PCBANG_COUPON_EVENT_20060124

// [업데이트] PC방 전용 이벤트 - 칼리마 무료이동 이벤트 (hnine)
#define PCBANG_FREE_KALIMA_EVENT_20060124
#endif

// [버그추적] 캐슬 몬스터 버그 추적 로그 추가 (RKFKA)
#define ADD_LOG_CASTLE_MONSTER_BUG_FIX_20060911

#ifdef ADD_NEW_SKILL_FOR_CASTLE_01_20041116
// [버그수정] 착용한 변신반지를 빼면 클라이언트에서 정보를 리셋함 - 킬카운트 정보를 보내준다.
#define MODIFY_KILL_COUNT_BUGFIX_20060908
#endif

#if GAME_VERSION >= G_V_S2_2
// [업데이트] 엘리트해골전사변신반지 추가(RKFKA)
#define ADD_ELITE_SKELETON_WORRIOR_CHANGE_RING_20060830
#endif

// [버그수정] AI Automata 딜레이 적용 버그 수정 ( hjlim )
#define MODIFY_MONSTERAI_AUTOMATA_DELAY_BUGFIX_20060907

#if GAME_VERSION >= G_V_S2_2
// [버그수정] 크라이울프 보스 몬스터는 경험치를 주지 않는다. - 발가스, 다크엘프, 발리스타 (hnine) 
#define MODIFY_NON_EXP_IN_CRYWOLF_MONSTER_20060530

// [버그수정] 맵 이동시 칼리마 게이트 채크 부분 수정 (hnine)
#define MODIFY_MAP_MOVE_LEVEL_MESSAGE_SEND_20060830

// [버그수정] 로그 시스템 확장 (2,3차) 내용 수정 (hnine)
#define MODIFY_LOG_SYSTEM_2_3_20060828

// [버그수정] 파이어스크림스크롤 드랍 가능하게 수정 - 시즌2 전용 (apple)
#define	MODIFY_ITEM_DROP_FIRESCREAMSCROLL_20060830
#endif

// [버그수정] 아이템 드랍 버그 수정 (apple)
// 1) Type 당 배정되어 있는 Index 의 최대값에 해당되는 아이템 드랍 안 되는 버그 수정
// 2) 법서의 드랍 가능 Index 최대 범위 수정
#define MODIFY_ITEM_DROP_MAXINDEX_20060830

// [버그수정] 크라이울프 HeroList 로그 버그 ( hjlim )
#define MODIFY_CRYWOLF_HEROLIST_LOG_BUGFIX_20060828

#if GAME_VERSION >= G_V_S2_2
// [업데이트] 로그 시스템 확장 - 3차 (hnine)
#define EXTEND_LOG_SYSTEM_04_20060823
#endif

// [업데이트] 칸투르 보스전 타임어택 이벤트 (RKFKA)	-	20061018 이벤트 종료로 삭제(RKFKA)
//#define KANTURU_TIMEATTACK_EVENT_20060822
#if GAME_VERSION >= G_V_99B
// [버그수정] 맵 서버 이동 시 캐릭터 저장 Flag 수정(중국적용 후 모두 적용) ( hjlim )
#define MODIFY_MAPSERVERMOVE_FLAG_BUGFIX_20060817
#endif

#if GAME_VERSION >= G_V_S2_2
// [업데이트] 조화의보석 메시지 WTF 추가 ( hjlim )
#define ADD_JEWEL_OF_HARMONY_WTFMESSAGE_20060818

// [업데이트] 로그 시스템 확장 - 2차 (hnine)
#define EXTEND_LOG_SYSTEM_03_20060816

// [버그수정] 380 추가 옵션 스크립트 타입 확장 ( hjlim )
#define MODIFY_380ITEM_SCRIPTTYPE_EXTEND_20060811

//[업데이트] PC방 전용 체험서버에서 접속시 이동 가능 맵 설정 (hnine)
#define MODIFY_KANTURU_MAPNUMBER_CHECK_20060807

// [업데이트] 타겟을 가지는 트랩을 위해 PMSG_ACTIONRESULT에 타겟 인덱스 추가(hnine)
#define ADD_TRAP_OBJECT_EXTEND_20060731

// [업데이트] 몬스터 AI & 스킬 수정 ( hjlim_RKFKA )
#define	MODIFY_NEW_MONSTER_AI_01_2006724 
#define MODIFY_NEW_MONSTER_SKILL_01_20060724
#endif

// [버그수정] 350 아이템 2차 버그 수정. 신규아이템추가 시 주의 ( hjlim )
#define MODIFY_350ITEM_BUGFIX2_20060823

// [버그수정] 몬스터 밀기 스킬 기본값 적용 / 독 딜레이 없이 즉시 처리 적용 ( hjlim )
#define MODIFY_MONSTERSKILL_SPRING_POISON_BUGFIX_20060817

//[버그수정] 350 아이템 추가 버그 수정 ( hjlim )
#define MODIFY_350ITEM_BUGFIX_20060811

// [버그수정] 맵이동 최소 레벨 체크 수정 ( hjlim )
#define MODIFY_CHECK_MOVELEVEL_20060731

#if !defined(GAMESERVER_TO_CASTLESIEGESERVER) && GAME_VERSION >= G_V_S2_2
// [업데이트] 칸투르 보스전 추가(RKFKA)
#define ADD_KANTURU_20060627
#endif


//[버그수정] 조화의보석/380아이템 DB버전 관련 버그 수정.매우 중요. ( hjlim )
#define MODIFY_JEWELOFHARMONY_380OPTION_DBVERSION_BUGFIX_20060727

#if GAME_VERSION >= G_V_S2_2
// [업데이트] 다크로드 스킬 파이어 스크림 추가(RKFKA)
#define ADD_SKILL_DARKLOAD_FIRESCREAM_20060601

// [업데이트] 마이너스 스탯 열매 개선 ( hjlim )
#define MODIFY_MINUS_FRUIT_POINT_20060622
#endif

// [버그수정] 유저 종료 시 귓말 캐시에서 캐릭터명 삭제하지 않는 버그 ( hjlim )
#define MODIFY_WHISPER_CASH_BUGFIX_20060704

#if GAME_VERSION >= G_V_S2_2
// [업데이트] 380 아이템 추가 옵션 시스템 ( hjlim )
//#define ADD_380ITEM_NEWOPTION_20060711

// [업데이트] 조화의 보석 시스템 (hjlim)
//#define ADD_JEWEL_OF_HARMONY_SYSTEM_20060530
#endif

#if GAME_VERSION >= G_V_99B
// [버그수정] 개인상점 오픈 후 공성서버->로랜시아 이동 시 
//				RegenMapNumber 초기화 안해서 생기는 위치 버그 수정(apple)
//				!!주의!! gObjMoveGate()에서 RegenMapNumber 가 초기화 된다
#define MODIFY_MOVEGATE_CHECK_PERSONALSHOP_OPEN_20060704
#endif

// [버그수정][ExDB] 서로 다른 서버에서 친구 추가 시 서버정보 오류 버그 ( hjlim )
#define MODIFY_RE_ADDFRIEND_BUG_20060623

// [버그수정][ExDB] 캐릭터 종료 시 길드인 경우 친구 종료처리 하지않는 버그 ( hjlim )
#define MODIFY_CHARCLOSE_BUG_20060623

// [버그수정] 스웰라이프 초기화 버그 재수정 ( hjlim )
#define MODIFY_SWELLLIFE_BUG_FIXAGIAN_20060628

// [버그수정] 익스플로젼 블레이드 추가 마력 반영 되지 않는 버그 ( hjlim )
#define MODIFY_EXPLOSION_BLADE_WEAPON_MAGICDAMAGE_BUG_20060623

// [버그수정] 엑설런트 엘리멘탈 방패 생증 옵션 버그 (hjlim)
#define	MODIFY_EXCELLENT_SHILED_BUG_20060615

#if GAME_VERSION >= G_V_S2_2
// [버그수정] 성문, 석상 업그레이드 할 때 수호보석을 삭제한 후 업그레이드를 실행한다. (RKFKA)
#define MODIFY_CASTLE_NPC_UPGRADE_PROCESS_20060619
#endif

// [버그수정] 주민번호를 제대로 체크하지 않는 버그 - USA 국가코드가 추가되면서 해당 처리가 빠졌음(RKFKA)
#define MODIFY_JOOMINCHECK_FOR_USA

// [버그수정] 수호석상 & 라이프 스톤 회복 - 최대 HP,MP,AG 버그 (hjlim)
#define MODIFY_GUARDIANSTATUE_LIFESTONE_REFILLBUG_FIX_20060609

// [버그수정] 공성 직책 스킬 - 투명 스킬 타겟 설정 버그 ( hjlim )
#define MODIFY_CLOAKING_TARGET_BUGFIX_20060608

// [버그수정] 연합길드 방출 시 생기는 버그 (hjlim)
#define MODIFY_UNIONGUILD_KICKOUT_BUGFIX_20060529

// [버그수정] 법사 순간 이동시 뷰포트 버그 재수정 (hjlim)
#define MODIFY_WIZARD_TELEPORT_VIEWPORT_20060526

// [버그수정] 결투 종료 후 다크스피릿 타겟 해제 (hjlim)
#define MODIFY_DARKSPIRTI_TARGETRELEASE_ON_DUEL_20060524

// [버그수정] 엑설런트 아이템 드랍시 내구도 버그 (hjlim)
#define MODIFY_EXCELLENT_DROP_DURATION_BUG_20060524

// [업데이트] 게임가드 2.5버전에서 맵 서버 이동시에는 인증을 하지 않는다. (hnine)
#ifdef NPROTECT_GAME_GAURD_FOR_SERVER_VERSION_25_20060123
#define MODIFY_GAMEGUARD_NOT_AUTH_MAPSERVER_MOVE_20060513
#endif

// [업데이트] 카오스 캐슬에서는 쉴드 파괴 이펙트를 출력하지 않는다. (hnine)
#define MODIFY_NO_SHOW_SHIELDBROKE_EFFECT_IN_CHAOSCASTLE_20060523

// [누적버그수정] 헬 버스트 스킬 시전 시간 문제 수정 (hnine)
#define MODIFY_HELLBURST_SKILL_TIME_20060522

// [버그수정] 아이템 최대 내구도 계산 버그 (0527삭제) (hjlim)
//#define MODIFY_CALC_DURABILITY_20060523

// [버그수정] 몬스터 저항력 100% 저항 설정 (hjlim)
#define MODIFY_MONSTER_RESISTANCE_IMMUNE_20060523

// [버그수정] 쿤둔 관련 뷰포트 버그 (hjlim)
#define MODIFY_KUNDUN_VIEWPORT_20060523

#if GAME_VERSION >= G_V_S2_2
// [버그수정] 펜릴 엑설런트 옵션 버그(젠증가/방성증가 버그) (hjlim)
// MODIFY_DESTRUCTION_FENRIR_GET_MONEY_20060515 삭제
#define MODIFY_FENRIR_EXOPTION_BUG_20060522
#endif

// [버그수정] 로랜협곡/크라이울프 맵에서 펜릴 공격시 상대 내구력 감소 하지 않는 버그 (hjlim)
#define MODIFY_CASTLEMAP_FENRIR_DURATION_20060522

// [버그수정] 쉴드/마나 최대 값 감소시 현재 감소된 값 전송.아이템 효과 적용에서 분리 ( hjlim )
#define MODIFY_SHIELD_MANA_CHANGEMAXVALUE_20060526

// [버그수정] 아이템 효과 적용 순서 변경. 엑설런트아이템/세트아이템 ( hjlim )
//#define MODIFY_ITEM_EFFECT_FLOW_20060519
//#define MODIFY_ITEM_EFFECT_FLOW_20060519_2

// [버그수정] 레벨업시 체력증가 옵션 적용안되는 버그 및 재접후 깍이는 버그(0527재수정) (hjlim)
#define MODIFY_LIFEANDMANA_BUG_LEVELUP_RELOGIN_20065018

#if GAME_VERSION >= G_V_S2_2
// [스킬보완] 인피니티 애로우 스킬 취소 적용 (RKFKA)
#define ADD_INFINITY_ARROW_CANCEL_20060516
#endif

#ifdef MAP_SERVER_WORK_20041030
// [버그수정] 맵 이동시 아이템 드롭으로 인한 아이템 복사 버그 수정 (hnine)
#define MODIFY_ITEM_DUPLICATION_USING_ITEMDROP_20060518
#endif

#if GAME_VERSION >= G_V_S2_2
// [버그수정] 드롭이 안되는 고가의 아이템 추가 (hnine)
#define ADD_NON_DROP_VALUABLE_ITEM_20060518
#endif

// [버그수정] 일본 스웰라이프 초기화 버그 수정 (hnine)
#define MODIFY_SWELLLIFE_INIT_BUGFIX_20060411

// [버그수정] 텔레포트 중 잔상 버그 수정 (삭제) (hnine)
//#define MODIFY_AFTERIMAGE_BUGFIX_20060215

// [버그수정] 일본 공성 서버 종료 시간 3초 버그 수정 (hnine)
#define MODIFY_SIEGE_END_DATE_BUG_FIX_20060116

#if GAME_VERSION >= G_V_S2_2
// [버그수정] 같은 맵으로 맵 이동시에 유저가 안 보이는 버그 수정 (hnine)
#define MODIFY_MOVEMAP_RESET_VIEWPORT_BUGFIX_20060511
#endif

// [버그수정] 축복의 물약, 영혼의 물약을 겹칠수 있는 최대 수 조정 160 ->250 (RKFKA)
#define MODIFY_SIEGE_POTION_OVERLAP_COUNT_20060511

// [버그수정] 해외 컴파일시 오류 부분 수정 (HAPPY_CAT으로 인한 버그 수정) (hnine)
// 해외 컴파일 시에만 켜 져야 함
#ifndef FOR_KOREA
#define MODIFY_SEASON_01_20060317
#endif

#if GAME_VERSION >= G_V_S2_2
// [업데이트] 로그 시스템 확장 (hnine)
#define EXTEND_LOG_SYSTEM_02_20060516
#endif

// [누적버그수정] 카오스 캐슬에서 쉴드 데미지 이상 버그 (hnine)
#define MODIFY_SHIELDDAMAGE_BUGFIX_IN_CHAOSCASTLE_20060516

// [누적버그수정] 로렌시아 강제 이동 버그  (hjlim)
#define MODIFY_FORCEMOVE_TO_LORENCIA_20060515

#if GAME_VERSION >= G_V_S2_2
// [누적버그수정] 마검사 볼케이노 세트 착용시 세트 방어력 추가 (hjlim)
#define MODIFY_MAGUMSA_VOLCANOSET_DEFENSE_20060515

// [누적버그수정] 군주의망토 업그레이드시 내구력 계산 버그 (hjlim)
#define MODIFY_UPGRADE_DARKLORDMANTLE_20060515
#endif

// [누적버그수정] 공성맵 입장 유저 리젠 좌표 재설정 수정 (RKFKA)
#define MODIFY_LOGINUSER_SET_REGEN_COORD_AT_CASTLE_MAP_20060511

// [누적버그수정] 수성 길드인 경우 길드 해체 불가 (RKFKA)
#define MODIFY_CASTLE_OWNER_GUILD_DESTROY_LIMIT_20060418

// [누적버그수정] 공성전 NPC 초기화 버그 수정 (RKFKA)
#define MODIFY_CASTLE_NPC_INITIALIZE_BUG_20060406

// [버그수정] 공성시에 유저를 텔레포트 시킬 수 있는 버그 수정 (hnine)
#define MODIFY_TELEPORT_SKILL_USING_PARTY_MEMBER_20060504

// [버그수정 베트남] - 메세지 전송시 문자열 길이 계산 버그 수정 (RKFKA)
#define MODIFY_VIETNAM_MEMCPY_BUG_20060502

// [업데이트] 쉴드 게이지 공식 변경 (hjlim)
#define UPDATE_SHIELD_CALCULATE_GAGE_20060428

#ifdef ADD_SHIELD_POINT_01_20060403
// [기능추가] 쉴드 시스템 콤보 적용 옵션 & 물약 조합 확률 (hjlim)
#define UPDATE_SHIELD_OPTION_20060427
#endif

#ifdef FOR_ONAIR
// [기능추가] 방송용 서버 설정 매크로 추가 (hnine)
#define ADD_MACRO_FOR_SETITEM_20060424
#endif

// [버그수정] 아이디 암호 임력 창에서 Connect 후 무한 대기 가능한 문제 해결 (apple)
#define MODIFY_CONNECTTIME_CHECK_20060424

#if GAME_VERSION >= G_V_S2_2
// [기능추가] 인피니티 애로우 스킬 사용시 추가 MP 소모량 조정 매크로 (RKFKA)
#define ADD_MACRO_INIFINITY_ARROW_CONTROL_20060410
// [업데이트] CSkillAdditionInfo 추가 (RKFKA)
#define ADD_SKILL_ADDITION_INFO_CLASS_20060407
// [업데이트] 뮤즈엘프 스킬 '인피니티 애로우' 추가 (RKFKA)
#define ADD_SKILL_MUSE_ELF_INFINITYARROW_20060406

// [업데이트] 칼리마 NPC 레이라 추가 (RKFKA)
#define ADD_SHOP_KALIMA_NPC_REIRA_20060403
#endif

// [업데이트] 카오유저 이벤트( 카오스캐슬, 데빌스퀘어, 블러드캐슬) 입장 금지 (RKFKA)
#define ADD_PK_USER_ENTER_LIMIT_EVENT_MAP_20060411

#if GAME_VERSION >= G_V_S2_2
// [공방보완] 공방전 성공시 아이템 보상 (RKFKA)
#define ADD_CRYWOLF_SUCCESS_REWARD_20060404		
// [공방보완] 제단에 계약하는 요정 캐릭터의 제한 레벨 350 -> 260 변경 (RKFKA)
#define MODIFY_CRYWOLF_ELF_ALTAR_LIMIT_LEVEL_CHANGE_20060404
// [공방보완] 크라이울프 몬스터 다크엘프, 발가스 아이템 드랍	(RKFKA)
#define ADD_CRYWOLF_MONSTER_ITEMDROP_20060404

// 쉴드 시스템 디버그 메시지 출력 (삭제) : 사내 개발서버에서만 활성화.
//#define SHIELD_POINT_DEBUGLOG

// [업데이트] 쉴드 시스템(포인트) 추가 (hnine)
#define ADD_SHIELD_POINT_01_20060403
#endif

// [버그수정] 스킬 공격 범위 체크 추가 보완 (hjlim)
#define MODIFY_SKILL_CHECK_DISTANCE_UPDATE_02_20060421

// [버그수정] 스킬 공격 범위 체크 수정 및 보완 (hjlim)
#define MODIFY_SKILL_CHECK_DISTANCE_UPDATE_20060417

// [버그수정] 스킬 공격 범위 체크 (hjlim)
#define MODIFY_SKILL_CHECK_DISTANCE_20060413

// [기능추가] 게임서버 정보 추가 (apple)
// 테스트/서비스 서버구분, 각종 서버들과의 연결 상태 정보 보여주기
#define ADD_SERVER_INFO_DISPLAY_EXTEND_01_20060313

// 맵 조인 프로토콜을 받았는지 체크 한다. (Server Dev.)
#define	BLOCK_INVALID_CHARACTER_DELETE_01_20060327

// [버그수정] 러브팡팡(러브러브) 이벤트와 인증서버와의 연결관계 제거 (apple)
#define REMOVE_LOVELOVE_EVENT_COUPLING_WITH_JOINSERVER_20060319

// [기능수정] 크라이울프 몬스터 체력하락 자동화 & 쿤둔 자생 제거 옵션화 (apple)
#define MODIFY_CRYWOLF_BENEFIT_01_20060315

// [버그감시] 카오스캐슬, 블러드캐슬 버그 추적 로그 ( RKFKA )
#define ADD_LOG_CHECK_CAHOSCASTLE_BLOODCASTLE_EVENT_20060314

// [기능추가] FSGate 연결 안 됐을때 Option Reload 방지 (apple)
//	#define ADD_SERVER_FUNC_OPTION_RELOAD_CHECK_01_20060313

#if GAME_VERSION >= G_V_S2_2
// [업데이트] 화이트데이 사탕상자 이벤트 ( RKFKA )
#define WHITEDAY_CANDY_BOX_EVENT_20060222

// [로그추가] 쿤둔 아이템 드랍 로그 추가( RKFKA )
// ADD_KUNDUN_ITEM_DROP_LOG_20060309
#endif

// [업데이트] 로컬라이징 데이터(.wtf) 추가
// 0.99.60 - 0.99.94
#define MODIFY_LOCALIZING_WTF_20060309

// [버그수정] 칼리마 이동 버그 수정 (hnine)
#define MODIFY_KALIMAMOVE_BUGFIX_20060221

// [버그수정] 마법사의 반지 내구력 버그 수정 (hnine)
#define MODIFY_MAGICIANRING_DURATION_BUGFIX_20060221

#ifdef ADD_KUNDUN_CONTROL_20040923
// 쿤둔 이벤트 관련 로그 저장 파일명 변경(임시) (hnine)
#define MODIFY_KUNDUN_EVENT_LOG_FILENAME_20060220
#endif

#if GAME_VERSION >= G_V_S2_2
// [업데이트] 로그 시스템 확장 20060202 (hnine)
#define EXTEND_LOG_SYSTEM_20060202

// [버그수정] 쿤둔 아이템이 칼리마가 아닌 맵에서 드랍되는 버그 수정 (RKFKA)
#define MODIFY_KUNDUN_ITEM_DROP_MAP_20060216
#endif

// [업데이트] 경험치 계산 방식 및 파티/셋트 경험치 수정 (hnine)
#define MODIFY_GETTING_EXP_RATE_20060214
// 경험치 공식 변경 관련 기존 MODIFY_GETTING_EXP_RATE_20060213 삭제 (hnine)
// MODIFY_GETTING_EXP_RATE_20060213 (RKFKA)
// [업데이트] 경험치 획득 증가 (apple)
//#define MODIFY_GETTING_EXP_RATE_20051116

// [로그수정] 1) 쿤둔 관련 로그 수정 KALIMA(6) -> KALIMA(7)	
//				2) 6칼리마에 있는 모든 유저정보 로그 부분 주석처리 (RKFKA)
// MODIFY_KUNDUN_LOG_20060201

// [버그감시] 유효하지 않은 영역으로 인해 로랜시아 이동 추적 로그 (apple)
#define ADD_LOG_CHECK_INVLIDE_X_Y_POSITION_20060131

// [버그감시] 경험치 획득 맵, 좌표 정보 추가 (apple)
#define ADD_LOG_GETTING_EXP_MAP_X_Y_INFO_20060131

#if GAME_VERSION >= G_V_S2_2
// [업데이트] 발렌타인데이 상자 이벤트 (RKFKA)
#define VALENTINES_DAY_BOX_EVENT_20060124

// [버그수정] 펜릴 젠으로 수리 되는 버그 수정 (apple)
#define	MODIFY_FENRIR_ZEN_REPAIR_20060124
#endif

#ifdef PERSONAL_SHOP_20040113
// [버그수정] 맵서버 이동 시 개인상점 아이템 복사 발생 (apple)
#define MODIFY_ITEM_DUPLICATION_IN_MAPSERVER_MOVING_20051219
#endif

// [버그수정] 공성 진행에 다른 연합은 SOMMON 되지 않는다. (apple)
#define MODIFY_DARKLORD_RECALL_IN_CASTLESIEGE_TIME_20051219

// [버그수정] 수호석상이 파괴 되지 않았으면, 직인 등록을 할 수 없다. (apple)
#define	MODIFY_CASTLE_CROWN_ACCESS_BY_CHECKING_STATUE_20051219

#if GAME_VERSION >= G_V_S2_2
// [업데이트] 크리스마스 리본상자 이벤트 (RKFKA)
#define CHRISTMAS_RIBBONBOX_EVENT_20051212	
#endif

// [업데이트] 저레벨 육성 관련 수정 (hnine)
#define UPDATE_LOWLEVEL_SUPPORT_1_20051215				

// [버그수정] 게임 중이 아니면 NPC와 이야기 할수 없다. (apple)
#define MODIFY_NPCTALK_REQUIREMENT_20051212

#if GAME_VERSION >= G_V_S2_2
// [업데이트] 신규 몬스터 AI 추가 (apple)
#define ADD_NEW_MONSTER_SYSTEM_02_20050725	// Monster AI

// ☆★ 크라이울프 (apple)
#ifdef GAMESERVER_TO_CRYWOLFSERVER
#define CRYWOLF_PRECEDENCE_PATCH_20050413
#define CRYWOLF_COMMON_PATCH_20050413
#define CRYWOLF_ONLY_PATCH_20050413
#else
#define CRYWOLF_PRECEDENCE_PATCH_20050413
#define CRYWOLF_COMMON_PATCH_20050413
#endif

// [업데이트] 신규 탈것 펜릴(Fenrir) 추가 (apple)
#define	ADD_ITEM_FENRIR_01_20051110
#endif

// [안티해킹] 시리얼 0 보석 생성 및 거래에 대한 처리 (apple)
#define ANTIHACKING_SERIAL_0_ITEM_20051202

// [버그수정] 몬스터 범위상에 랜덤 생성일 경우 Rand() -> GetLargeRand()로 변경 (apple)
#define MODIFY_MONSTER_RANDOM_POS_CREATION_20051202

// [버그수정] 맵상에서 캐릭삭제 가능으로 인한 복사 버그 수정 (apple)
#define MODIFY_CHARACTER_DELETE_IN_MAP_20051121

// [버그수정] (중국) 핵툴사용 117문자 채팅메세지 전송 시 팅 버그 방지 (apple)
#define PREVENT_117_CHATTING_MSG_BUG_20051114

// [로그추가] 공성전 시작, 종료 날짜 DB 업데이트 대한 로그 추가 (apple)
#define ADD_CASTLESIEGE_DATE_UPDATING_LOG_20051103

// [버그수정] 다크로드 소환 5초 카운트 시 유니리아 착용 가능 버그 수정 (apple)
#define MODIFY_DARKLORD_RECALL_BUGFIX_20051103 

// [버그수정] 공성서버에서 변신반지 착용시 공&수성 정보를 보낸다 (apple)
#define MODIFY_CASTLESIEGE_VIEWPORT_BY_CANGE_RING_20051103

// [버그수정] 공성서버에서 변신반지를 제거했을 때 자신의 뷰포트와 창/방패 정보를 보낸다.. (apple)
#define MODIFY_VIEWPORT_REMOVE_CHANGE_RING_20051013

// [파일수정] 로랜 협곡 이벤트 메세지를 wtf 파일로 수정 (apple)
#define MODIFY_CASTLEDEEP_EVENT_MESSAGE_20051013

// [공성보완] 직인 등록 시 왕관 스위치 등록자 정보를 검색하고 가능 여부 판단 (apple)
#define MODIFY_CASTLE_CROWN_ACCESS_ALLOWED_BY_CROWNSWITCH_20051102

// [공성보완] 공성시작 후 수호석상이 없을 경우 생성시키는 루틴 제거 (apple)
#define REMOVE_CASTLESIEGE_AUTO_REVIVE_GUARDIANSTATUE_20051101

// [공성보완] 다크호스를 착용하고 직인 등록 중인 길드 마스터는 밀려나지 않는다. (apple)
#define MODIFY_CASTLESIEGE_GUILDMASTER_BACKSPRING_20051018

// [공성보완] 왕관 스위치 등록자 정보를 알린다. (apple)
#define MODIFY_CASTLESIEGE_NOTIFY_CROWNSWITCH_USER_20051017

// [공성보완] 공성 물약 조합 결과 개수 5->10으로 변경, 지속 시간 확장 (apple)
#define MODIFY_CASTLE_POTION_20051017

// [공성보완] 직인 등록 시간 누적 시스템 (apple)
#define MODIFY_CASTLESIEGE_CALC_CROWN_ACCESSTIME_20051014

// [공성보완] 공성 길드간 구별을 위한 식별 시스템 (apple)
#define MODIFY_CASTLESIEGE_IDENTIFICATION_20051012




//----------------------------------------------------------------------------------------------------------
//
//	◆ OLD Style..
//
//----------------------------------------------------------------------------------------------------------


// T_CurCharName 에 캐릭터 정보를 쌓지 않는다 (apple)
#define REMOVE_CONNECTED_CHARACTER_NAME_INFO_20051004

// 뮤매니저 전체공지 발생 시 로그 기록 (apple)
#define	ADD_LOG_GM_TOOL_NOTICE_20051004

// 몬스터 응답이상 버그 : 아이스에로우와 같이 움직임을 멈추는 스킬 주의! (apple)
#define MODIFY_MONSTER_ACT_BY_ICEARROW_20050914

#if GAME_VERSION >= G_V_S2_2
// 숨겨진 보물상자 이벤트 (b4nfter)
#define HIDDEN_TREASUREBOX_EVENT_20050804

// 한국 공인 IP주소 변경 (b4nfter)
#define MODIFY_WEBZEN_PUBLIC_IPADDRESS_20050822

// 에로우바이퍼 등 활, 석궁 수치 적용 수정 (apple)
#define MODIFY_APPLYING_BOW_01_20050825

// 신규 아이템 추가 (apple)
#define ADD_NEW_ITEM_01_20050823

// 마이너스 스탯 열매 추가 (apple)
#define ADD_MINUS_STAT_SYSTEM_USING_FRUIT_20050712
#endif

#if GAME_VERSION >= G_V_99B
// item.txt 파일 확장 (apple)
// < 필요요구치 확장 >
//	힘,민첩,에너지 -> 레벨,힘,민첩,에너지,체력,통솔
#define EXPAND_ITEMSCRIPT_01_20050808
#endif

// 애로우바이퍼 화살 +2 작용시 데미지 적용 (apple)
#define MODIFY_ARROWVIPER_2PERCENT_DAMAGE_20050816

#if GAME_VERSION >= G_V_99B
// ExDB 친구 기능 ON/OFF 추가 (apple)
#define ADD_FRIEND_FUNCTION_ON_OFF_20050811

// 파란 복주머니 사용 후 '이동 칼리마' 명령 사용 적용 수정
#define MODIFY_KALIMAMOVE_COMMAND_FOR_BLUEPOUCH_20050811

// 아이템인덱스 확장으로 인한 드랍리스트 관리 (apple)
// 랜덤 범위를 한정 짓는다.
// 랜덤으로 세트아이템 만들기 수정
#define ADD_RANDOM_RANGE_OF_ITEMINDEX_20050808

#if GAME_VERSION >= G_V_S1_512
// 히든 칼리마 추가 (b4nfter)
#define HIDDEN_KALIMA_20050706
#endif

// 파티원 맺을 때 로그 오류 수정 (b4nfter)
#define	PARTY_ADD_LOGFIX_20050801

// 쿤둔은 경험치를 주지 않는다 (apple)
#define DISABLE_GETTING_EXP_FROM_KUNDUN_20070801
#endif

// 게임서버 파라메터 추가 (DataServerIp2, DataServerPort2, ExDbIp, ExDbPort) (b4nfter)
#define ADD_GAMESERVER_PARAMETER_20050728

#if GAME_VERSION >= G_V_S1_512
// 아이템 인덱스 확장 (b4nfter)
#define ITEM_INDEX_EXTEND_20050706

// DB크기 확장 (b4nfter)
#define ITEM_DBSIZE_EXTEND_20050706

// 아이다 맵 추가 (apple)
#define ADD_NEW_MAP_AIDA_20050617

// 새로운 몬스터 시스템 추가 (apple)
#define ADD_NEW_MONSTER_SYSTEM_01_20050714	// Monster SKILL

// EXDB에서 적대가 있는 상태에서는 다른 적대를 맺지 못하도록 함! (apple)
#define MODIFY_EXDB_RIVAL_CHECK
#endif

// 공성 운영자 명령 wtf 로 수정(apple)
#define MODIFY_CASTLESIEGE_GM_MESSAGE_20050722

// 배틀사커를 이용해 PK 안되게 하는 버그 수정 (apple)
#define MODIFY_BATTLESOCCER_PKCHECK_20050714

// 다크로드 최대 생성가능 스탯 버그 수정(apple)
#define MODIFY_DARKLORD_CREATION_MAXSTAT_USING_FRUIT_20050712

// 축복, 영혼의 물약 조합 핵톨 사용 가능 취약점 수정. (apple)
#define MODIFY_BLESS_SOUL_POTION_CREATION_BUG_20050711

#if GAME_VERSION >= G_V_S1_512
// 대천사의 절대 셉터 추가. item.txt 수정 필요(apple)
#define	ADD_WEAPON_OF_ARCHANGEL_SCEPTER_20050706

// 길드 채팅 / 연합 채팅을 서버그룹단위로 가능하게 한다. (apple)
// GS <-> ExDB <-> GS 간에 데이터 교환
#define ADD_SERVERGROUP_CHATTING_FOR_GUILD_UNION_01_20050706

// 길드전,배틀사커가 자신의 길드에 되는 버그 수정. (서버가 죽음 ㅠ_ㅠ) (apple)
#define MODIFY_GUILDWAR_REQUEST_PROCESS_20050704

// WhatsUp과 Console 화면 상에서 서버의 이상을 체크한다. (apple)
//	#define ADD_SERVER_ALERT_USING_WHATSUP_01_20050628

// 캐릭터 직책 스킬 보강. skill.txt 수정 필요(apple)
#define ADD_NEW_SKILL_FOR_CASTLE_02_20050531		

// 블러드 캐슬, 카오스 캐슬, 광장에서는 SHADOW PAHTOM의 기능을 없앤다(apple)
#define MODIFY_NPC_SHADOW_PAHTOM_20050628

// 몬스터의 아이템 드롭 최대 레벨 조정 (u4us)
#define MODIFY_DROP_MAX_ITEM_LEVEL_6_OF_MONSTER_20050624
// 반지 및 목걸이 레벨 5 이상 몬스터 드롭 방지 (u4us)
#define MODIFY_DROP_PREVENT_OF_RING_N_NECKLACE_LV_5_OVER_20050623
// 캐릭터 공격력 & 방어력 향상 제공 NPC Shadow Phantom 추가 (u4us)
#define ADD_NPC_SHADOW_PHANTOM_20050616
// 캐릭터 자동 회복 시스템 (u4us)
#define CHARACTER_AUTO_RECUPERATION_SYSTEM_20050614
// 사과 아이템 레벨 0 - 1 사용시 즉시 회복 (u4us)
#define IMMEDIATELY_HP_MP_AG_RECUPERATION_20050614
#endif

// [소스수정] Shop15번 파일 추가 삭제 -> ADD_SHOP_15_20050613 삭제(RKFKA)
// 공성전 맵에 상점추가 -> WzVersionManager, WzAuthGs, WzFsGate 같이 수정 (b4nfter)
//	#define	ADD_SHOP_15_20050613

// 최고 레벨이 되면 더이상 경험치를 얻지 못한다.
#define	MAX_LEVEL_BLOCK_GAIN_EXPERIENCE_20050613

// 에로힘과 쿤둔의 아이템 드랍이 몹이 존재하는 맵이 되도록 변경 (apple)
#define MODIFY_ITEM_DROP_MAP_OF_EROHIM_KUNDUN_20050610

// 이벤트 운영자(GM) 권한 추가 (u4us)
#define ADD_AUTHORITY_CODE_OF_EVENT_GM_20050602	

#if GAME_VERSION >= G_V_S1_512
// 데빌스퀘어 확장 -> 기존 4개에서 6개 (b4nfter)
#define DEVILSQUARE_EXTEND_20050221
#endif

// [누적버그수정 1차] 다크로드 PET 보상 경험치 적용 수정. (apple)
#define MODIFY_ACCUMULATED_BUG_DARKLORD_PET_EXP_01_20050603
// [누적버그수정 1차] 성주의 표식 판매가격 버그 수정. (apple)
#define MODIFY_ACCUMULATED_BUG_MARKOFLORD_SELL_VALUE_01_20050531
// [누적버그수정 1차] 캐논타워에 죽을 경우 경험치 하락 버그 수정. (apple)
#define MODIFY_ACCUMULATED_BUG_DEAD_BY_CANNONTOWER_01_20050531
// [누적버그수정 1차] 스웰라이프 파티 시 정상 적용 되도록 수정. (apple)
#define MODIFY_ACCUMULATED_BUG_SWELLLIFE_ON_PARTY_01_20050531
// [누적버그수정 1차] 기술목걸이, 마법의반지 자생 적용 제거. (apple)
#define MODIFY_ACCUMULATED_BUG_AMULETRING_WRONG_OPTION_01_20050531
// [누적버그수정 1차] 군주의 망또 +10~13 방어력 적용 수정. (apple)
#define MODIFY_ACCUMULATED_BUG_SLEEVEOFLORD_01_20050531


// 에로힘 아이템 루팅은 MAXHIT 유저로 한다. (apple)
// 에로힘 아이템 루팅은 LastHit 유저로 한다. (apple)
#define MODIFY_ITEM_LOOTING_FROM_EROHIM_20050610
#define MODIFY_ITEM_LOOTING_FROM_EROHIM_20050530

// 변신 캐릭터으로 부활시 자신의 뷰포트 정보 갱신 (u4us)
#define BUGFIX_UPDATE_VIEWPORT_INFO_FOR_SELF_20050510

#if GAME_VERSION >= G_V_S1_512
// 맵서버 관련 추가정보
#define	MAP_SERVER_ADDINFO_20050509
#endif

// 공성 사냥터의 보스몹인 에로힘은 경험치를 주지 않는다. (apple)
// 경험치 버그로 인해 수정 함.
#define DISABLE_GETTING_EXP_FROM_EROHIM_20050509

// NPC 대화창 금지 (클라이언트 요청) (b4nfter)
#define DISABLE_NPC_MESSAGE_20050506

#ifdef DARKLORD_WORK
// 다크로드의 팻을 위한 아이템 판매가격 버그 수정 (u4us)
#define BUGFIX_SELL_PRICE_OF_DARKLOAD_PETS_20050310            
#endif

// [공성보완] 성주 길드는 다른 길드에 연합 가입 할수 없다. (apple)
#define MODIFY_UNION_JOIN_CASTLE_OWNER_GUILD_20050502

// 카오스 조합 열매 & 날개 추가 (u4us)
#define ADD_FRUIT_N_WING_OF_CHAOS_MIX_20050502    

#if GAME_VERSION >= G_V_S1_512
// 보석 조합 시스템 (b4nfter)
#define JEWEL_MIX_SYSTEM_20050309

// [공성보완] 연합 길드마스터 길드 연합 방출 기능 추가 (apple)
#define ADD_ABILITY_OF_UNIONMASTER_TO_KICK_OUT_UNIONMEMBER_01_20050418

// [공성보완] 연합 길드 수 조정 (7->3) (apple)
#define MODIFY_MAX_UNION_MEMBER_01_20050418
#endif

// 개인상점 젠복사 버그 패치
#define	BUGFIX_PERSONALSHOP_ZENCOPY_20050426

// 운영 캐릭 명령어처리 로그 추가 수정. (apple)
// 명령 대상에 대한 정보 추가.
#define ADD_LOG_GM_COMMAND_20050426

// 레나 및 이벤트칩 복사 시도 방지 및 로그 기록 (u4us)
#define BUGFIX_EVENT_CHIP_DUPLICATE_PREVENT_20050422  

// MaxUser 수 Commonserver.cfg에서 조절 기능 추가. (apple)
// Commonserver.cfg 추가 내용 :
// 1) NumberOfMaxUser = 500		
// 2) NumberOfCastleSiegeMaxUser = 1500
#define ADD_CONTROL_MAXUSER_20050420

// X 주민등록번호 체크부 수정 (u4us)
#define BUGFIX_X_RESIDENT_REGISTRATION_OF_USER_20050419            

// 데스 블레이드 크리티컬 데미지 처리 추가 (u4us)
#define ADD_CRITICAL_DAMAGE_OF_DEATH_BLADE_20050419 

// Send Buffer 확장. (apple)
#define EXPAND_MAX_SENDBUFFER_20050413

// #LOGADD_CASTLESIEGE_20050404 (b4nfter)

// 길드이름 리셋 (b4nfter)
#define	GUILDNAME_MEMSET_20050410

// 아이템을 주을 때 생기는 논리적 오류 수정 (b4nfter)
#define ITEM_GET_BUGFIX_20050406

// 객체 삭제 시 서있던 위치의 속성을 리셋해줌 (b4nfter)
#define	CLEAR_STANDATTR_OBJDEL_20050325

// PK를 자유롭게 할 수 있도록 변경 (b4nfter) -> ServerInfo.dat 의 PkLimitFree = 1 이 되어야 적용
#define	ADD_PK_LIMIT_FREE_OPTION_20050324

// 개인상점 인벤토리 초기화 시 메모리 침범으로 발생혔던 오류수정 (b4nfter)
#define	PSHOP_INVENTORY_CLEAR_BUGFIX_20050321

// 종료 시 인벤토리가 사라지는 버그 수정 (b4nfter)
#define INVENTORY_CLEAR_BUGFIX_20050226

// 쿤둔 이벤트 종료에 따른 설정 변경 (apple)
// 1) 아이템 드랍 5->2개로 변경
// 2) 쿤둔 HP 메세지 삭제.
#define	CHANGE_KUNDUN_SETTING_01_20050221

// 특정 몹의 죽었다는 상태 Q 처리를 우선시한다. (apple)
#define ADD_QPROCESSING_STATE_OF_DEAD_20050221

// DB아이템 데이터에서 아이템이 없는 슬롯 체크방법 
// 단순히 배열 첫자리를 0xFF 경우 없는 것으로 할때 9비트 아이템타입 형식에서 0xFF (-> 7/31) 아이템을 만들었을 경우 문제 발생
#define INVENTORY_EMPTYSLOT_CHECK_20050217

// 블러드 캐슬, 데빌스퀘어 복사 버그 수정
// 한국에는 비활성화 되어 있던것을 활성화 시킴. (20050216) (apple)
#define BLOOD_DEVILSQUARE_TRADE_BUG_FIX

// 캐릭터 선택 창에서 캐릭터 삭제시 레벨을 알수 없으므로 해당 코드 삭제(apple)
#define DEL_CODE_LIMIT_OF_DEL_CHARACTER_LEVEL_20050215

// 친구 리스트 + 쪽지 리스트 요청 순서 변경.
// 맵서버 연결과 관련.	(b4nfter_apple)
#define MODIFY_ORDER_REQUEST_FRIENDLIST_20050205

#ifdef PERSONAL_SHOP_20040113
// 레벨 5 이하의 케릭터들의 경우 최초 접속 시 개인상점 영역을 초기화 하고 시작한다.
#define PERSONAL_SHOP_DELETE_UNDER_LV5_20050203
#endif

// EXDB DB 객체 동기화를 위한 수정. (apple)
// EXDB Server에만 적용됨.
// ExDB Server : 0.40.G에 적용됨.
#define MODIFY_EXDB_SYNC_01_20050128		

#if GAME_VERSION >= G_V_S1_512
// 캐릭터 리스트 정보에 길드 정보도 추가한다. (apple)
// Dataserver에도 적용된다. : 0.55.09T 부터 적용
// 공성용 Dataserver서버에만 적용!!
#define ADD_CHARACTERLIST_GUILD_STATUS_01_20050126
#endif

// 카오스 조합시 팝업 메세지 뜨지 않도록 메세지 제거 (apple)
#define REMOVE_CHAOSMIX_NPC_MESSAGE_20050125

#define ADD_OPTION_RELOAD_ITEM_TO_JOINSERVER

// 공성전에 따라 길드해체, 연합끊기 제한설정. (apple)
// ExDB Server에 적용됨.
// ExDB Server : 0.40.F 이상 적용
#define EXDB_APPLY_CASTLEUPDATE_01_20050111

// 이벤트 매니저 (전체 이벤트를 특정 시간으로 분할하여 순차적으로 실행시키고 싶을 경우 사용) (b4nfter_apple)
#define EVENT_MANAGEMENT_20040711

#if GAME_VERSION >= G_V_S1_512
// 캐릭생성시 Class 정보 보내기 (apple)
#define ADD_CLASSINFO_ON_CHARCTER_CREATION_20041224

// 연합 마크 얻기 (apple) - EXDB 수정 필요
//	#define ADD_UNION_GET_UNIONMARK_01_20041222

// 연합 이름 얻기 (apple)
#define ADD_UNION_GET_UNIONNAME_01_20041222
#endif

// 인증서버 종료 시 프로세스 종료가 아닌 1분 종료가 되도록 수정
//	#define	MODIFY_AUTHSERVER_CLOSE_20041207

// 액설런트 아이템 내구력 수정 (apple)
#define MODIFY_EXCELLENT_ITEM_DUR_01_20041202

// 몬스터 아이템 드롭 로그에 몬스터 이름을 추가한다. (b4nfter)
#define	MONSTER_ITEMDROP_LOG_ADD_NAME_20041202

#if GAME_VERSION >= G_V_S1_512
// 거래 시 관계 정보 초기화 보완. (apple)
#define MODIFY_NEW_UNION_02_20041201	

// 연합 채팅 기능 (apple)
#define ADD_UNION_CHATTING_01_20041201
#endif

#if GAME_VERSION >= G_V_99B
// 매니저에서 메일보내기 (foguy)
#define ADD_MANAGER_SENDMAIL

// 길드원이 다른 길드원 방출 할수 있는 것 수정 (apple)
#define ADD_NAMECHECK_DISMISS_GUILDMEMBER_20041129

// 마석은 카오스캐슬, 블러드캐슬, 악마의광장에서 열 수 없다. (apple)
#define ADD_MAPCHECK_OPEN_KALIMAGATE_20041129
#endif

// 카오스캐슬 입장시간 표시 오류 수정 (apple)
#define MODIFY_OPENTIME_CHAOS_CASTLE_20041129

// 로크의 깃털 가격 수정 (apple)	
#define MODIFY_PRICE_FEATHE_OF_LOCH_20041129

#if GAME_VERSION >= G_V_S1_512
// 맵서버 분할 작업 (b4nfter)
#define MAP_SERVER_WORK_20041030				
#endif

// 체크섬 파일의 정보를 캡션바에 보여서 보여준다.(apple)
#define ADD_DISPLAY_CHECKSUM_INFO_20041127

// GM 명령 User State 다크로드 추가 (apple)
// 20041127 message_kor.wtf 적용되어야 합니다~! 
//	#define MODIFY_GMCOMMAND_USERSTAT_20041127

// 대만 게임패스워드(창고비밀번호) 적용 (apple)
#define MODIFY_GAMEPASSWORD_20041126

// 직책 임명 오류 수정. (apple)
#define MODIFY_ASSIGN_GUILD_STATUS_20041123

// 데이터 파일 국가별 선택 방식 변경. (apple)
// DataServer, ExDB Server에 적용됨.
// !!주의 - Commonserver.cfg에 CountryCode 가 추가 되야함.
// !!주의 - 해외 통합버전에 적용됨. 
// !!주의 - DataServer : 0.55.07 ExDB Server : 0.40.B
#define MODIFY_LOAD_DATAFILE_FOR_DBSERVER_20041117

// 다크호스, 스피릿 조합 수정 (apple)
#define MODIFY_DARKLORD_PETITEM_CHAOS_MIX_20041117

#ifdef DARKLORD_WORK
// 다크로드 열매 버그 수정 (apple)
#define MODIFY_DARKLORD_ACQUIRING_EXTRA_POINT_20041117
#endif

#ifdef CASTLE_SIEGE_COMMON_PATCH_20041018
// 공성 준비 레나 이벤트(왕의직인 대신 일시적 이벤트) (apple)
#define ADD_RENAEVENT_FOR_CASTLE_SIEGE_20041116
#endif

#ifdef DARKLORD_WORK
// 마법 배우고 사용할 때 배울 수 있는 레벨인지 체크.. (apple)
#define ADD_CHECKING_LEVEL_TO_LEARN_MAGIC_20041115
#endif

#if GAME_VERSION >= G_V_S1
// 공성전 작업 (b4nfter)
#ifdef GAMESERVER_TO_CASTLESIEGESERVER
// 공성서버 모드
#define CASTLE_SIEGE_COMMON_PATCH_20041018		// 공성전 서버와 일반 서버간에 공통되는 패치부분
#define CASTLE_SIEGE_ONLY_PATCH_20041018		// 공성전 서버만 필요한 패치부분
#else
// 일반서버 모드
#define CASTLE_SIEGE_COMMON_PATCH_20041018		// 공성전 서버와 일반 서버간에 공통되는 패치부분
#endif
#endif

#if GAME_VERSION >= G_V_S1
// New Guild System	(apple)
// 해당 수정사항을 적용하기 위해서는 ExDB를 40.C 이상 버전으로 변경 해야 함.
// [C   <-> GS] 0xE0 ~ 부터 사용.
// [EDS <-> GS] 0xE0 ~ 부터 사용
#define MODIFY_NEW_UNION_01_20041122		// 거래 시 길드 정보 초기화 보완.

#define ADD_NEW_UNION_02_20041118	// 연합 조건
#define ADD_NEW_UNION_01_20041006	// 연합
#define ADD_NEW_GUILD_02_20040922	// 용병
#define ADD_NEW_GUILD_01_20040913	// 직책
#endif

// 월드 토너먼트 이벤트
//	#define WORLD_TOURNAMENT_EVENT_SETTING

// 망토 엑셀옵션 버그 수정(무조건 공증옵션이 들어가야 되는데 생증도 들어가는 버그)
#define SLEEVEOFLORD_OPTION_BUG_PATCH

// 중국 카오스 조합을 이용한 복사 버그 수정
#define CHAOS_BOX_ITEMCOPY_FIX_20041112_FOR_CHS

// 흑마법사 텔레포트 시 뷰포트에 맵이동한 케릭이 남아있는 현상 수정 (b4nfter)
#define BUGFIX_WIZARD_TELEPORT_MAGIC_20041018

// 공지 보낼때 버퍼복사방식 수정 (b4nfter)
//	#define MODIFY_SERVER_NOTICE_BUFFERCOPY_20041018

// WzJoinServerCli.cpp 에서 Send() 시 버퍼가 무한히 쌓이는 문제 수정 (그동안 DB소켓 등의 데이터 전송 문제의 원인으로 추정됨) (b4nfter)
//	#define	BUGFIX_WSJOINCLIENT_SENDLENGTH_20041011		

// GS -> DS 서버로 지속적인 LIVE신호 보냄
//	#define GS_DS_LIVECHECK_20041008

#if GAME_VERSION >= G_V_99B
// (1) 게임서버 업그레이드 (apple)
// : 몬스터 OBJ 경량화
#define UPGRADE_GAMESERVER_01_20041006

// 마석 사리지는 버그 수정 (b4nfter)
#define BUGFIX_KALIMAGATE_VANISHING_20041006		// 칼리마 게이트 사라지는 현상 수정

// #BUGFIX_DARKSPRITE_DINORANT_DAMAGE_20041005		// 다크스피릿 공격 시 디노란트 착용하면 추가 데미지가 들어가는 버그

// 쿤둔 피 조절 및 모니터링을 위한 명령어추가 등(apple)
#define	ADD_KUNDUN_CONTROL_20040923

// 몬스터 HP 회복 (쿤둔 이벤트를 위해 추가) (apple)
// HP가 20%이하일때 부하 몬스터 x 마리 소환!
#define ADD_ABILLITY_KUNDUN_01_20040920
#endif

#ifdef _NEW_EXDB_
// 길드 파괴 시 길드전 해제 않되던 점 수정 (b4nfter)
#define BUGFIX_GUILD_DESTROY_WAR_BLOCK_20040922
#endif

// 콤보 데미지도 PVP시 50% 데미지 감소 되도록 수정
#define MODIFY_CC_PVP_COMBO_DAMAGE_LOWER_50_20040917

// 마검사 아스릴세트 방어력. 방어률 적용 (apple)
#define MODIFY_10_11_12_13_SET_DEFENSE_20040916

#ifdef ADD_KUNDUN_CONTROL_20040923
// 쿤둔을 잡은 보상 수정 및 로그 추가 (apple)
#define MODIFY_KUNDUN_REWARD_01_20040915
#endif

// 특정 몬스터를 죽였을 때 보상으로 여러개의 아이템을 드랍한다. (apple)
#define ADD_MONSTER_DIE_REWARD_ITEMS_20040915 

// 몬스터 전체 공격 수정 (apple)
// 유저도 사용하는 CGBeattackRecv 사용으로 4개이상의 타겟에게 데미지 주지 못하는것 수정.
#define MODIFY_MONSTER_ENTIRE_ATTACK_20040915

// 특정 유저 이름이 영문 3글자인 경우 처리를 위해 길드가입, 길드생성 수정. (apple)
// ExDB BUG FIX로 추가. ExDB 40.B 이상 버전으로 변경 해야 함.
#define MODIFY_GUILDMEMBER_NAME_LIMIT_200040914

// DSProtocol 과 EDSProtocol 에 혼재해 있던 코드 정리 (apple)
// DSProtocol 주석처리. -> 삭제 요망.
#define	BLOCK_PREVIOUS_DSPROTOCOL_FOR_GUILD_20040913

#if GAME_VERSION >= G_V_99B
// 길드 Number 0x36(DB프로토콜) 부분 수정 : WORD -> INT (apple)
// ExDB DeadLock 해결
// 해당 수정사항을 적용하기 위해서는 ExDB를 40.A으로 변경 해야 함.
#define	MODIFY_GUILD_VIEWPORT_03_20040913
#endif

// 다크스피릿 "타겟지정" 공격 직접 타격 공격으로 변경 (apple)
#define MODIFY_DARKSPIRIT_TAGET_ATTACK_01_20040906

// 쿤둔의 표식 드랍 -> 각 표식 등급별로 처리하도록 변경 (apple)
#define MODIFY_KALIMA_KUNDUNMARK_DROP_01_20040906

// 다크로드 파티원 SOMMON 스킬 이동 구역 수정 (apple)
// DARKLORD_WORK <-- ON 되어 있어야 함.
#define MODIFY_DARKLORD_SKILL_RECALL_PARTY_20040831

#if GAME_VERSION >= G_V_99B
// 새로 길드 뷰포트 시스템 수정 (apple) 
// 기존 GuildNumber를 WORD로 인식했던 부분.(OLD 뷰포트 버전 역시 문제 있음)
#define	MODIFY_GUILD_VIEWPORT_02_20040830
#endif

// 아이템 복사방지 관련 수정 (b4nfter)
#define ITEM_DUPLICATE_PREVENT_PATCH_BUGFIX_20040825

// ConnectMember.txt의 계정개수 무제한 (b4nfter)
#define CONNECT_MEMBER_COUNT_INFINITE_20040823

#if GAME_VERSION >= G_V_99B
// 캐릭터이동..
#define CHARACTER_MOVE_20040810
#endif

#if GAME_VERSION >= G_V_99B
// 스킬에 물리/마법 속성 들어감 (b4nfter)
#define SKILL_ADD_PHYSICS_MAGIC_TYPE_20040812

// 다크로드의 마음 이벤트 (b4nfter)
#define DARK_LORD_HEART_EVENT_20040810
#endif

// 블러드캐슬에 대천사의 무기 드롭을 직접 하도록 수정 (b4nfter)
#define BLOODCASTLE_ITEMDROP_DIRECTLY_20040728

// 거래 버그 수정 (창닫히는 부분에 대한)
#define	TRADE_BUG_FIX_CLOSE_WINDOWS_20040727

// 새로운 형태의 NPC_A Type 추가 (apple)
//#define ADD_NPC_TYPE_A_01_20040708

// 아이템 복사 방지 패치 (b4nfter)
#define ITEM_DUPLICATE_PREVENT_PATCH_20040719

// 데빌스퀘어 하루 입장수 제한 (b4nfter)
//#define DEVILSQUARE_CHECK_ENTERCOUNT_20040715
#if GAME_VERSION >= G_V_S1
// Guild Viewport 작업 (apple)
#define MODIFY_GUILD_VIEWPORT_01_20040701
#endif

#if GAME_VERSION >= G_V_99B
// 지속 마법 핵 방지 (apple)
#define APPLY_DURATION_MAGIC_HACK_CLEANER_20040504

// 신규맵 - 칼리마 (b4nfter)
#define ADD_NEW_MAP_KALIMA_20040518

// 게임서버에서 접속서버로 보내주는 추가적인 정보들 [0xF4][0x07]
//#define GAMESERVER_INFO_EXTENDED_20040625

// 고유 정보 아이템 (apple)
//#define ADD_PROPERTY_ITEM_SYSTEM_01_20040609 

// PVP 시스템 보완 1차 (apple)
//#define ADD_PVP_SYSTEM_01_20040517	

// 몬스터 타입 BYTE -> WORD 로 확장 (b4nfter)
#define ENHANCE_MONSTER_TYPE_TO_WORD_20040618
#endif

#ifdef ADD_NEW_MAP_KALIMA_20040518
// 쿤둔 죽었을 경우 세트 아이템 드랍(apple) 
#define ADD_REWARD_ABOUT_KALIMA_BOSS_01_20040907
#endif

// 물약 가격 재수정(foguy)
#define	HP_POTION_VALUE_CHANGE_20040618

#if GAME_VERSION >= G_V_99B
// ExDB 길드 작업 재수정
#define	EX_DB_GUILD_REWORK_RETOUCH
// GuildClass 수정작업
#define MODIFY_GUILD_CLASS_20040608
#endif

// 죽었을 때 용사, 전사의 반지 않떨구도록 한다 (b4nfter)
#define USER_DIE_NOT_DROP_HERORING_20040330

// 블러드캐슬 입장시 레벨 6 아이템으로 7광장에 입장할 수 있게 한다. (b4nfter)
//#define USER_ENTER_BLOODCASTLE7_WITH6_20040330

// 상대방을 사탄, 날개를 착용하고 공격하다 자신이 체력감소로 죽을 때 상대방을 카오로 만드는 버그 (b4nfter)
#define USER_DIE_MAKE_OPPOSIT_PK_20040329

// 캐릭터 사망시 아이템 가질수 없도록 (b4nfter)
#define USER_DIE_ITEMGET_BUG_PATCH_20040322

// 죽었을 때 젠이 증가하는 버그 수정 (b4nfter) 
#define USER_DIE_ZEN_BUG_PATCH_20040319
// 죽었을 때 젠 감소하는 수치 조정 (b4nfter)
#define USER_DIE_ZEN_MODIFY_20040318

//////////////////////////////////////////////////////////////////
// 2004년 2월 5일 본섭 패치 내용
// 아이템 복사버그 패치 (b4nfter)
#define ITEMCOPY_BUGFIX_20040112	
#if GAME_VERSION >= G_V_99B
// 내친구 적용 (saemsong)
#define __FRIEND_WORK__	
#endif

#if GAME_VERSION >= G_V_S1
// 길드 뷰포트 수정 (foguy)
#define GUILD_VIEWPORT_MODIFY	
#endif

// 블러드 캐슬 데빌스퀘어 입장시 아이템 복사 버그 수정 (foguy)
#define BLOOD_DEVILUSQARE_TRADE_BUG_FIX
// 캐릭터 사망시 경험치 손실 소정 (foguy)
#define USER_DIE_EXPERIENCE_MODIFY
// 이동 명령어 스크립트 추가 (foguy)
#define	ADD_MOVE_COMMAND_SCRIPT
#if GAME_VERSION >= G_V_S1
// 파티원에게 자신이 먹은 아이템 정보를 준다 (foguy)
#define	SEND_GETITEMINFO_FOR_MYPARTY
#endif
// 로크의 깃털 이카루스에서만 떨어지게 제한
#define	FEATHEROFLOKE_ITEMDROP_CHECK
//////////////////////////////////////////////////////////////////


// 길드 포인터 참조 에러 수정
#define CHINA_GUILD_POINTER_REF_ERROR

// 카오스 조합 -> 비정상 종료 시 인벤토리 RollBack / Commit 하도록 수정
#define CHAOS_MIX_TRANSACTION_BUXFIX_20040610

// DbVersion 이 0 인 사용자들이 접속했을 때 개인상점 영역을 초기화
#define PERSONAL_SHOP_DBVER_0_FIX_200406016

// 개인상점 영역에서 물건 가격을 조정하고 사고 팔기 전 복사아이템 체크
#define PERSONAL_SHOP_CHECK_COPYITEM_200406016

// 블러드 캐슬, 데빌스퀘어 복사 버그 수정
//#define BLOOD_DEVILSQUARE_TRADE_BUG_FIX

// 카오스 캐슬 결투 및 길드전 신청응답 안되게 수정
#define	CHAOSCASTLE_DUAL_GUILDWAR_CHANGE_20040614
// 관통 스킬 하나의 시리얼에 하나의 몬스터만 맞게 수정
#define	CHECK_PENETRATION_SKILL

//  파티원 아이템 정보 전송 프토로콜 레벨 추가 
#define SEND_GETITEMINFO_FOR_MYPARTY_ADD_LEVEL

#if GAME_VERSION >= G_V_99B
#define GUILD_REWORK		// 길드 다시 작업중 수정(SaemSong)
#endif

// 없는 아이템 삭제 -> 않하도록 변경 (b4nfter)
//#define	ITEMDELETE_MODIFY_20040604

// 블러드 캐슬에서 점수 저장 시 접속 끊긴 인원들도 저장되도록 수정 (b4nfter)
//#define	BLOODCASTLE_SENDPOINT_BUGFIX_20040604

// 파티 멤버 생명력 리스트 중에 멤버 퇴장 시 퇴장한 멤버의 값으로 잘 못 보이는 것. (b4nfter)
#define PARTYMEMBER_LIFELIST_FIX_20040531


// 마검 이동 레벨 공식 클라이언트와 맞춤 (NeedLevel = ((NeedLevel/3)*2) -> NeedLevel = ((NeedLevel*2)/3);
#define MODIFY_MAGUMSA_MOVE_LEVEL_20040517

// 2차 날개 카오스 조합확률(-454%) 버그 수정 (apple)
#define MODIFY_WINGMIX_454BUG_20040512

// 거래를 이용한 아이템 복사 버그 수정(foguy)(현재 중국만 수정됨)
//#define	TRADE_ITEM_COPY_BUG_FIX_20040511


// 세트 아이템용 버퍼 클리어
#define	SETITEM_BUFFER_CLEAR

// 물약을 먹을때 이전에 채울께 남아 있으면, 그것도 채우고 다음 물약을 먹인다
#define	USE_PREV_HP_POTION

//#define FOR_ANTI_HACK						// 핵테스트(사용못함)
// 천공 1차 
#define MONSTER_SKILL						// 몬스터 스킬
//#define RENA_CHANGE
#define CHANGE_VIEWSTATE					// ViewStat BYTE에서 WORD로 확장

#define NEW_SKILL_FORSKYLAND				// 천공을 위한 새로운 스킬

#define SERVERCODE_EXPAND					// 서버 코드 확장

#if GAME_VERSION >= G_V_S1
#define GAMESERVER_DIVISION					// 서버 분할작업
#endif
// 천공 1차 끝

// 천공 2차 
// 다중 체크섬 
//#define MULTI_CHECKSUM
// 다중 체크섬 끝

#define CHANGE_MAGICATTACKPACKET			// 마법 공격패킷을 받을때, 마법 순서 번호 대신, 스킬번호를 받게 수정

#define EXP_CAL_CHANGE						// 경험치 계산 방법 변경
// 천공 추가 수정을 위한 디파인
#define NEW_FORSKYLAND3		
// 천공 추가 수정을 위한 디파인 끝

#define VER_CHATWINDOW_OPTION				// 채팅옵션 저장

#define NEW_FORSKYLAND2						// 천공 2차를 위핸...

#define APPLY_PACKETCHECKSUM				// 체크섬 체크

#define HACK_LOG
// 천공 2차 끝

#define CHANGE_CLIENTHACKCHECK_MSG			// 핵체크 관련 메시지 변경						

#define FOR_STONE_EXCHANGE					// 스톤 환전
#define FOR_LOTTO_EVENT						// 상용화 2주년 기념 복권 이벤트 관련

#if GAME_VERSION >= G_V_99B
// 스킬추가 (2003.10.21)
#define ADD_SKILL_20031022
// 스킬추가 끝

// 아이템 추가
#define ADD_ITEM
// 아이템 추가 끝

// 변신 반지 아이템 드롭 설정
#define ITEMDROP_RINGOFTRANSFORM
// 변신 반지 아이템 드롭 설정 끝

// 스킬 추가
#define	ADD_SKILL_WITH_COMBO	

// 0x1E패킷 확장 (강제 공격시 강제 공격대상)
#define EXPAND_ATTACK_PACKET_0X1E	
#endif

// 트레이드를 이용한 스킬 버그 수정
#define TRADE_SKILLBUG_FIX	

// 카오스 일반날개 아이템 생성 레벨 조정
#define	CHAOS_MIX_WING_ITEMLEVEL_FIX

// 캐릭터 실시간 통계를 위해서 한시간 간격으로 아이템 저장할때.. 실시간 정보를 기록하라고 DB서버에 알림
#define ITEMSAVE_MODIFY_FORSTATICS

// WhatsUp용 더미 포트
#define WHATSUP_DUMMY_SERVER	

// 날개 조합 변경
#define WING_MIX_MODIFY

// 창고 아이템 복사 버그 수정
#define WAREHOUSE_ITEMCOPY_BUG_FIX

// 아이템백 업그레이드
#define EVENT_ITEMBAG_UPGRADE

/////////////////////////////////////////////////////////
// 테섭에 적용 중인 것들
/////////////////////////////////////////////////////////

// 마검사 방어력 = 민첩 / 5 로 적용 되어 있지 않았음.. (apple)
// 절대 사용금지 -> 마이너스 패치.
//#define MODIFY_CALC_MAGUMSA_DEFENSE_20040511

// M: 드라이브 연결 체크, 서버종료메세지 후 프로세스 종료 (apple)
#define APPLY_SERVER_UTIL_20040504

// 데미지 반사에 의한 화살 내구력 감소. 요정 화살 감소 수정 (apple)
#define MODIFY_ARROW_DECREASE_ELF_20040503

// 로그 무한 증가 1차 Check & Modify (apple)
#define CHECK_LOG_INFINITE_20040426

// 세트 방어 미적용 버그 수정 (apple)
#define MODIFY_10_11_12_13_SET_DEFENSE_20040421

// 운영 캐릭 명령어처리 로그 (apple)
// [IP][AccountID][Name][Command]
#define ADD_LOG_GM_COMMAND_20040420

// 물약 겹치기 버그 수정 (apple)
#define ADD_HP_POTION_LEVEL1_FIX_20040420

#if GAME_VERSION >= G_V_99B
// 공지사항 수정 (apple)
// Speed : 25 Default
// Delay : 0
// Type  : 10-15
#define MODIFY_NOTICE_20040325
#endif

// 캐릭터의 최대 소유 ZEN MAX 설정 : MAX 20억 (apple)
#define MODIFY_ZEN_MAX_20040414

// 아이템 가격 40억 초과시 40억으로 고정 (apple)
// 아이템 가격 재조정 : 사는 가격 최대 30억(foguy)_밑에 디파인 사용하는거 없어서 대신 사용.
// 아이템 가격 재조정 : 사는 가격 최대 20억(apple)
#define MODIFY_ITEM_PRICE_MAXFIX

// 아이템 수리 가격 재조정 (최대 4억으로 고정(아이템 가격 재조정에 따른 수리 비용 증가를 막기 위함)
#define MODIFY_ITEM_REPAIRE_MAXMONEY

// 올미스 처리 변경 (apple)
#define MODIFY_SUCCESSBLOCKING_ALLMISS_20040408

// 명령어 처리 추가 (생왕창, 아이템인덱스, 스탯수정등..) (apple)
#define JS_ADD_TEST_COMMAND

#if GAME_VERSION >= G_V_99B
// 12, 13 아이템 추가 && 물약추가 (apple)
// CHAOS_MIX_UPGRADE 같이 들어가야 함.!
// Viewport 관련 아이템레벨 변환 함수 변경 : 기존 0~7 -> 새로 0~6
#define ITEM_12_13_20040401

// 물약 먹었을때 다른 사람한테 효과 보여주기 (apple)
//#define ADD_EFFECT_POTION_20040401

// 레벨업 했을 때 다른 사람한테 효과 보여주기
// Effect 보내는 함수, 프로토콜 여기서 포함됨 (apple)
#define ADD_EFFECT_LEVELUP_20040401
#endif

#if GAME_VERSION >= G_V_99B
// 카오스 조합 타입별로 구분 업그레드 (foguy)
// +12, +13과 같이 패치 되어야함 (apple)
#define CHAOS_MIX_UPGRADE	
#endif
// HP 생명 물약 +1 추가 (apple)
#define ADD_HP_POTION_LEVEL1_20040401

// 이벤트 관련 옵션 리로드 -> commonserver.cfg 에 데이터는 그대로 있고 읽는 경로만 ReadCommonServerInfo() 와 분리 (b4nfter)
#define EVENT_OPTION_RELOAD_20040305

// 이벤트 외의 옵션 리로드 -> commonserver.cfg 에 데이터는 그대로 있고 이벤트 외의 게임옵션 리로드 (b4nfter)
#define ETC_OPTION_RELOAD_20040308

// 사용자가 종료를 선택했을때 로그 남김 (foguy)
#define	ADD_LOG_USER_CLOSE_SET

#if GAME_VERSION >= G_V_99B
// 이동, 공격, 패킷 변경(foguy)
#define PACKET_CHANGE
#endif

// 길드워 종료 처리 시간 조정
#define CHANGE_GUILD_WAR_END_DELAYTIME	

// 게임서버 정보 -> 접속서버 군 전달 - 접속서버가 분산구조로 바뀜에 따라 추가 (b4nfter)
//	#define GAMESERVER_INFO_TO_CSS_20040317

// 세트 아이템 옵션 정보(foguy)	
// [20060821 코드 삭제]
//	#define ADD_SET_ITEM_OPTION


/////////////////////////////////////////////////////////
// 기능은 되었는데 안쓰는것
// 접속 <-> 게임서버 정보전달 TCP (b4nfter)
// #define GAMESERVER_INFO_TCP_20031203
// 부활 영웅시스템 (b4nfter)
// #define	HERO_SYSTEM_MODIFY
// 부활 영웅시스템 끝
/////////////////////////////////////////////////////////
#endif


///////////////////////////////////////////////////////////////////
//
//	◆ 마스터레벨 시스템 ◆
//
///////////////////////////////////////////////////////////////////
#ifdef MASTER_LEVEL_SYSTEM_20070912
// 마스터레벨 성장 시스템
#define MASTER_LEVEL_UP_SYSTEM_20070912				

// 마스터레벨 전용등급 이벤트맵 추가
#define ADD_DEVILSQURE_FOR_MASTER_LEVEL_20071010		// 데빌스퀘어7 추가
#define ADD_BLOODCASTLE_FOR_MASTER_LEVEL_20071010		// 블러드캐슬8 추가
#define ADD_CHAOSCASTLE_FOR_MASTER_LEVEL_20071010		// 카오스캐슬7 추가
#define ADD_ILLUSIONTEMPLE_FOR_MASTER_LEVEL_20071010	// 환영사원6 사용 (비활성화 된 레벨을 활성화)

// 명령어
#define ADD_MASTER_LEVEL_SYSTEM_COMMAND_20071122		// 마스터레벨 관련 테스트용 명령어 추가

// 마스터레벨 스킬 시스템	
#define EXPAND_SKILL_SCRIPT_FOR_MASTER_LEVEL_20071122	// skill(kor).txt 스크립트 확장
#define MASTER_LEVEL_SKILL_SYSTEM_20071122				// 마스터레벨 스킬 시스템

//해외로 빌드시 컴파일 에러가 발생하여 임시로 상위 디파인조건을 추가함 - riverstyx
#ifdef PCBANG_POINT_SYSTEM_20070206
// PC방 아이템 관련 버프시스템 수정
#define BUGFIX_BUFF_EFFECT_SYSTEM_FOR_PCBANG_ITEM_20071205

// PC방 관련해서 해외 적용 되지 않음.(20081106-grooving)
// [버그수정] 환영사원 보상경험치 풍용의 인장 제거(goni)
#define MODIFY_EVENTMAP_REWARD_BUGFIX_20080404
#endif // PCBANG_POINT_SYSTEM_20070206

// [버그수정] 레벨업을 했을 때 경험치가 추가로 클라이언트에 전송되는 문제 수정
// 기존에 있던 클라이언트 버그를 서버에서 처리함.
// 마스터레벨 시스템 관련하여 경험치 계산 부분을 INT64로 변경.
#define BUGFIX_GAIN_EXP_20071210

// [버그수정] 스킬 기본 요구에너지 값 변경 (RKFKA)
#define MODIFY_BASIC_SKILL_REQENG_20080102 

// [코드삭제] DS에 데이터 요청 두번 하는 것 수정
#define DELETE_GD_REQUEST_20080110

// 시즌 3+ 마스터레벨 스킬 추가
#define ADD_MASTER_LEVEL_SKILL_PASSIVE_20080107			// 패시브 스킬 추가
#define ADD_MASTER_LEVEL_SKILL_SYSTEM_ACTIVE_20080107	// 액티브스킬 시스템 및 액티브스킬 추가

#ifdef  ADD_SEASON_4_UPDATE_20080617
// [업데이트] 마스터레벨 4랭크 추가(goni)
#define UPDATE_MASTER_LEVEL_4RANK_20080428
#endif	// ADD_SEASON_4_UPDATE_20080617

// [테스트 메세지]
//#define TEST_MSG_MLS_ACTIVE_20080131
#endif

///////////////////////////////////////////////////////////////////
//
//	◆ PC방 이벤트 ◆
//
///////////////////////////////////////////////////////////////////
#ifdef PCBANG_REVITALIZATION_EVENT_20060830
#define ADD_ELITE_SKELETON_WORRIOR_CHANGE_RING_20060830		// 엘리트해골전사변신반지가 추가되어 있어야 한다.
#define PCBANG_COUPON_EVENT_20060124						// PC방 쿠폰이벤트를 기본으로 사용한다.
#endif

///////////////////////////////////////////////////////////////////
//
//	◆ 칸투르 ◆
//
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
#if GAME_VERSION >= G_V_S2_2
#define KANTURU_MOONSTONEPENDANT_20060804		// 문스톤 펜던트 처리 추가 (RKFKA)
#define ADD_NEW_MAP_KANTURU_BOSS_20060627		// 칸투르 보스맵 추가 (RKFKA)		
#define ADD_NEW_MAP_KANTURU_COMMON_20060523		// 칸투르 일반 맵 추가 (RKFKA)		
#define KANTURU_PROTOCOL_20060705				// 칸투르 프로토콜 추가 (RKFKA)
#endif

///////////////////////////////////////////////////////////////////
#ifdef ADD_KANTURU_20060627

//#define KANTURU_TEST_200607119					// 칸투르 테스트용 디파인 - 작업이 끝나면 모두 삭제한다. (RKFKA)
#define KANTURU_BOSSMONSTER_EXP_NONE_20060809	// 칸투르 보스몬스터는 경험치를 주지 않는다.
#define KANTURU_SPECIAL_ITEMDROP_20060808		// 칸투르 조화의보석/문스톤 드랍
#define KANTURU_MONSTER_ITEMDROP_20060807		// 칸투르 몬스터 마야손, 나이트메어 아이템 드롭 (RKFKA)
#define ADD_KANTURU_CONDITION_20060725			// 칸투르 기타 작업내용 보완 (hnine)
#define KANTURU_GM_COMMAND_20060709				// 칸투르 운영자용 명령어 추가 (RKFKA)	
#define ADD_NEW_NPC_KANTURU_20060612			// 칸투르 NPC추가 (RKFKA)
#endif
//-----------------------------------------------------------------




///////////////////////////////////////////////////////////////////
//
//	★ 크라이울프 ☆
//
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
#ifdef CRYWOLF_PRECEDENCE_PATCH_20050413
//-----------------------------------------------------------------

#ifndef CASTLE_SIEGE_COMMON_PATCH_20041018
#define CASTLE_SIEGE_COMMON_PATCH_20041018
#endif 

#ifndef DEVILSQUARE_EXTEND_20050221
#if TESTSERVER == 1
#define DEVILSQUARE_EXTEND_20050221			
#endif
#endif

#ifndef ADD_NEW_MAP_AIDA_20050617
#define ADD_NEW_MAP_AIDA_20050617
#endif

//-----------------------------------------------------------------
#endif
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
#ifdef CRYWOLF_COMMON_PATCH_20050413
//-----------------------------------------------------------------
#define ADD_NEW_MAP_CRYWOLF_FIRSTZONE_20050414		// 크라이울프 1차 지역맵 추가
#define ADD_NEW_MAP_CRYWOLF_SECONDZONE_20050414		// 크라이울프 2차 지역맵 추가

#define	MU_CRYWOLF_SERVER_SYNC_20050505				// 크라이울프 관련 서버 간 동기화 작업
#define MU_CRYWOLF_CL_PROTOCOL_20050505				// 크라이울프 - GS <-> CL 프로토콜
#define MU_CRYWOLF_DS_PROTOCOL_20050505				// 크라이울프 - GS <-> DS 프로토콜

#define MU_CRYWOLF_BENEFIT_20051215					// 크라이울프 MVP 승리 혜택
#define MU_CRYWOLF_PENALTY_20051215					// 크라이울프 MVP 패배 패널티

#define CRYWOLF_MVP_REWARD_RANK_20051215			// 크라이울프 MVP 결과에 대한 랭크 및 포상

//-----------------------------------------------------------------
#endif
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
#ifdef CRYWOLF_ONLY_PATCH_20050413
//-----------------------------------------------------------------

#define	CRYWOLF_MAIN_SCHEDULER_20050505				// 크라이울프 일정과 데이터를 관리하는 스케쥴러

#define CRYWOLF_MONSTER_WORK_20050914				// 크라이울프 MONSTER 처리
#define	CRYWOLF_NPC_WORK_20050912					// 크라이울프 NPC 처리
#define CRYWOLF_MAP_SETTING_20050915				// 크라이울프 점령 상태에 따라 맵 속성 설정

#define CRYWOLF_GM_COMMAND_20050525					// 크라이울프 운영자 명령어

#define CRYWOLF_MVP_DISABLE_USER_ITEMDROP_20051217	// 크라이울프 MVP 시에는 죽었을 때 아이템 드랍되지 않음
#define CRYWOLF_MVP_DISABLE_USER_ZENDOWN_20060116	// 크라이울프 MVP 시에는 죽었을 때 젠이 감소 하지 않음

#define CRYWOLF_MODIFY_REGEN_POS_ON_MVP_20060116	// 크라이울프 MVP 시에 죽었을 때 리젠 위치


//-----------------------------------------------------------------
#endif
///////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////
//
//	★ 공성전 ☆
//
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
#ifdef  CASTLE_SIEGE_COMMON_PATCH_20041018			// 공성전 서버와 일반 서버간에 공통되는 패치부분
//-----------------------------------------------------------------
//#define MODIFY_MARKOFLORD_OVERLAPPED_20050530		// 성주의 표식이 인벤토리 상에서 겹쳐지도록 수정
#define	ADD_NEW_MAP_CASTLE_20041115					// 공성전 맵 추가
#define	ADD_NEW_NPC_CASTLE_20041115					// 공성전 관련 NPC 추가
#define MAP_SERVER_WORK_20041030					// 맵서버 분할 작업

#define	MU_CASTLESIEGE_SERVER_SYNC_20041130			// 공성전 서버들 간에 동기화를 맞추는 일련의 작업들
#define MU_CASTLESIEGE_CL_PROTOCOL_20041122			// 뮤 공성전 - 뮤 클라이언트 관련 프로토콜, 통신 부분
#define MU_CASTLESIEGE_DS_PROTOCOL_20041105			// 뮤 공성전 - 데이터 서버 관련 프로토콜, 통신 부분
#define	MU_CASTLESIEGE_TAX_SYSTEM_20041219			// 성 경제 시스템 구현 관련
#define MU_CASTLESIEGE_CS_MARKS_20041214			// 성주의 표식 아이템 관련 작업들

#define MODIFY_CASTLE_PK_01_20050309				// 성주 길드가 성에서 PK 했을 경우에 대한 처리

#define ADD_NEW_GEM_OF_DEFEND_FOR_CS_01_20050301	// 공성에서의 수호 보석 설정, 드랍률설정 가능.
#define ADD_NEW_CASTLE_FLAG_01_20041227				// Castle 깃발 및 장식 정보
#define ADD_NEW_MERCENARY_FOR_CASTLE_01_20041214	// 공성 용병 NPC 추가
#define ADD_NEW_ITEM_FOR_CASTLE_01_20041116			// ITEM 추가
#define ADD_NEW_SKILL_FOR_CASTLE_01_20041116		// 캐릭터 스킬 추가

#define ADD_NEW_WEAPON_FOR_CASTLE_01_20041116		// 공성 무기 추가
#define ADD_NEW_VIEWPORT_SYSTEM_01_20041201			// 공성 무기 뷰포트 시스템
#define ADD_NEW_MAP_CASTLE_HUNTZONE_20041115		// 사냥터 맵 추가
#define EXPAND_INTERFACE_BYTE_TO_DWORD_20041209		// m_IfState BYTE -> DWORD 로 확장
#define EXPAND_VIEWSKILLSTATE_WORD_TO_INT_20041122	// ViewSkillState WORD -> INT 로 확장
#define EXPAND_MAX_MAGICLIST_20_TO_60_20041126		// MagicList 확장 20개 -> 60개로 확장
//-----------------------------------------------------------------
#endif //CASTLE_SIEGE_COMMON_PATCH_20041018


#define MAP_SERVER_ADD_MONSTER_20041216				// 맵서버 분할 관련 몬스터 추가 함수 변경 (서버가 가지고 있는 맵만 추가되도록)

// 인증서버에 서버코드 추가 (공성)
#define JOINSERVER_USING_SERVERCODE
// 인증서버에 서버코드 추가 끝
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
#ifdef  CASTLE_SIEGE_ONLY_PATCH_20041018			// 공성전 서버만 필요한 패치부분
//-----------------------------------------------------------------
#define	DISABLE_GETTING_EXP_FROM_GUARDTOWER_20070801	// 가드타워 파괴 시 경험치를 얻지 못하게 한다.
#define CASTLE_NPC_DONT_DROP_ITEM_20050517			// 공성전 NPC들은 아이템을 떨구지 않는다.
#define	CASTLEDEEP_EVENT_20050413					// 로랜협곡 습격 이벤트 (b4nfter)
#define	CASTLE_SPECIAL_ITEMMIX_20050425				// 성주혜택 특별 아이템 조합 (b4nfter)
#define	MU_CASTLESIEGE_START_NOTIFY_20050418		// 공성전 시작 전 N분 부터 전 서버에 공성전 알람 시작
#define	MU_CASTLESIEGE_STATE_SEC_VIEW_20050413		// 공성전 상태 남은시간 표시
//#define	CASTLE_NPC_TEST_STATE_20050118				// 공성전 NPC에 테스트용 임시수치 적용
#define CASTLE_SAVE_PCROOM_USERLIST_20050105		// PC방 이벤트 관련 - 공성전 참여자들의 PC방 정보 저장
//#define	CASTLE_TEST_SCHEDULER_20041218				// 테스트 스케쥴러를 사용한다. (모든 단계는 5분씩)
#define CASTLE_GM_COMMAND_20041222					// 공성전 운영자 명령어
//#define	CASTLE_POTION_NPC_20041222					// 공성전 맵의 물약파는 NPC 처리
#define	CASTLE_MAIN_SCHEDULER_20041111				// 공성전의 일정과 데이터를 관리하는 스케쥴러
#define	CASTLE_NPC_GATE_WORK_20041206				// 성문 처리와 관련된 작업들
#define CASTLE_NPC_GUARDIANSTATUE_WORK_20041207		// 석상 처리와 관련된 작업들
#define CASTLE_NPC_LIFESTONE_WORK_20041208			// 라이프스톤 (진지) 처리와 관련된 작업들
#define CASTLE_NPC_CROWN_WORK_20041210				// 왕관 처리와 관련된 작업들
#define CASTLE_NPC_CROWN_SWITCH_WORK_20041210		// 왕관 스위치 처리와 관련된 작업들
#define CASTLE_NPC_CANNON_TOWER_20041223			// 캐논타워 처리와 관련된 작업들
#define MU_CASTLESIEGE_JOINSIDE_VIEWPORT_20041209	// 공성전 시 공/수 양측의 소속 상태를 뷰포트에 추가하여 표시함
#define MU_CASTLESIEGE_LOG_20050107					// 공성전 별도 로그 관리
#define ADD_CASTLE_HUNTZONE_MONSTER_01_20050111		// 사냥터 몬스터. 특히 BOSS 몹 처리
#define ADD_CASTLE_HUNTZONE_NPC_01_20050111			// 사냥터 문지기 등.
#define ADD_NEW_CASTLE_HUNTZONE_REWARD_01_20050303	// 공성 사냥터에서 보상 추가.(1.보스몹에 대해)
#define ADD_NEW_CASTLE_HUNTZONE_REWARD_02_20050314	// 공성 사냥터에서 세트아이템 드랍 추가.(2.시련의땅에서만)
#define MODIFY_RANGEATTACK_CHECK_20050113			// 범위 스킬 공격방식 변경 (공성맵에서 공성전 중일 때 사람도 맞도록)
#define MODIFY_UPDATING_VIEWPORT_20050118			// 반지 버릴 경우 캐릭터를 다시 그리라는 명령을 클라이언트에게 주지 않는다.

#define MODIFY_ANS_GIVEUP_20050413					// 공성 선포 기간같이 공성포기기간이 아닐때 클라이언트로 보내주는 에러 처리 수정 (apple)
//-----------------------------------------------------------------
#endif //CASTLE_SIEGE_ONLY_PATCH_20041018
///////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////
//
//	◆ 이벤트 ◆	- Old Style...
//
///////////////////////////////////////////////////////////////////
// Blood Castle용
#define FOR_BLOODCASTLE						// 블러드 캐슬용임
#define FOR_BLOODCASTLE2					// 블러드 캐슬용 추가 작업(foguy)
#define FOR_BLOODCASTLE3					// 블러드 캐슬용 추가 작업(b4nfter - 2003.10.21 패치)
#if GAME_VERSION >= G_V_99B
#define BLOODCASTLE_EXTEND_20040314			// 블러드캐슬 7개로 확장	(수정되는 리소스 gate.txt, MonsterSetBase.txt, BloodCastle.dat)
#define BLOODCASTLE_EVENT_3RD_20040401		// 블러드캐슬 3차 이벤트 (캐슬 남은시간 저장) (b4nfter)
#define BLOODCASTLE_EVENT_4TH_20040531		// 블러드캐슬 4차 이벤트 (캐슬 남은시간 저장) (b4nfter)
#define BLOODCASTLE_EVENT_5TH_20050531		// 블러드캐슬 5차이벤트. 파티중심으로 변경 (b4nfter)
#endif

// 엘도라도의 상자이벤트
#define ELEGORADO_EVENT						
///////////////////////////////////////////////////////////////////


#if GAME_VERSION >= G_V_99B
///////////////////////////////////////////////////////////////////
//
//	◆ 기본 시스템 ◆	- Old Style...
//
///////////////////////////////////////////////////////////////////
// 결투 시스템
#define	DUEL_SYSTEM_20031028
#define	DUEL_SYSTEM_FIX_20031224	

// 2차 퀘스트
#define SECOND_QUEST

// 무리 몬스터 시스템
#define MONSTER_HERD_SYSTEM_20031120

// 다크로드 작업	(아이템 스크립트 확장도 같이 들어감)
#define	DARKLORD_WORK

// 개인상점 추가 (b4nfter)
#define PERSONAL_SHOP_20040113
#define PERSONAL_SHOP_BUG_FIX
#define ADD_SHOP_11_12	// 상점 추가
#endif

// 길드 서버 적용
#define _NEW_EXDB_

#define QUEST_BUG_FIX	// 퀘스트 버그 수정

///////////////////////////////////////////////////////////////////


#ifdef MAP_SERVER_WORK_20041030						// 맵서버 분할 작업 관련 추가 패치
//#define MAP_SERVER_ADD_MONSTER_20041216				// 맵서버 분할 관련 몬스터 추가 함수 변경 (서버가 가지고 있는 맵만 추가되도록)
#endif //MAP_SERVER_WORK_20041030


#define LOLONG(l)									((DWORD)((UINT64)(l) & 0xFFFFFFFF))
#define HILONG(l)									((DWORD)((UINT64)(l) >> 32))
#define MAKELONGLONG(a, b)							((INT64)(((DWORD)((UINT64)(a) & 0xFFFFFFFF)) | ((INT64)((DWORD)((UINT64)(b) & 0xFFFFFFFF))) << 32))

#ifdef ADD_NEW_ITEM_FOR_CASTLE_01_20041116
// D E F I N E : 공성 아이템 추가
#ifdef MODIFY_SIEGE_POTION_OVERLAP_COUNT_20060511
#define MAX_SPECIAL_POTION_OVERLAP_COUNT	250
#else
#define MAX_SPECIAL_POTION_OVERLAP_COUNT	160
#endif

// 수정 MODIFY_CASTLE_POTION_20051017
// BLESS:60 -> 120, SOUL:30 -> 60
#define CASTLE_BLESSPOTION_ACTIVETIME		120
#define CASTLE_SOULPOTION_ACTIVETIME		60


// D E F I N E : 영혼의 물약 AG 회복값
#define CASTLE_SOULPOTION_AG_REFILL_POINT		8

// D E F I N E : 영혼의 물약 저항력 증가값(%)
#define CASTLE_SOULPOTION_ADD_RESISTANCE	50


#endif

#ifdef ADD_NEW_SKILL_FOR_CASTLE_01_20041116
// D E F I N E : 공성 스킬 추가 
enum SKILL_LIST_TYPE
{
	// 기본
	SKILL_LIST_TYPE_DEFALT = 0x00,
	// 스킬 추가 
	SKILL_LIST_TYPE_ADD = 0x01,
	// 스킬 제거 
	SKILL_LIST_TYPE_DEL = 0x02,

};

enum KILLCOUNT_OPTION
{
	KILLCOUNT_RESET = 0x00,
	KILLCOUNT_INC = 0x01,
	KILLCOUNT_DEC = 0x02,
};

#endif

#ifdef ADD_CASTLE_HUNTZONE_NPC_01_20050111
// D E F I N E : 사냥터 NPC 추가

#define CASTLE_HUNTZONE_GATE_01		106

enum CASTLE_HUNTZONE_NPCTALK_RESULT
{
	CASTLE_HUNTZONE_ENTRANCE_DISABLE = 0x00,
	CASTLE_HUNTZONE_ENTRANCE_ENABLE = 0x01,
	CASTLE_HUNTZONE_ENTRANCE_ENABLE_TO_MEMBER = 0x02,
	CASTLE_HUNTZONE_ENTRANCE_ENABLE_TO_OWNER = 0x03,
};

enum CASTLE_HUNTZONE_SETTING
{
	CASTLE_HUNTZONE_SETTING_FAIL = 0x00,
	CASTLE_HUNTZONE_SETTING_SUCCESS = 0x01,

};

enum CASTLE_HUNTZONE_USAGE
{
	CASTLE_HUNTZONE_USAGE_DISABLE = 0x00,
	CASTLE_HUNTZONE_USAGE_ENABLE = 0x01,

};
#endif


///////////////////////////////////////////////////////////////////
//
//	친구 시스템
//
///////////////////////////////////////////////////////////////////////
#ifdef __FRIEND_WORK__
#define MAX_MEMO_SUBJECT	32
#define MAX_MEMO			1000
#define MAX_DATE			30

#define FRIENDSERVER_ONLINE				0	// 친구 서버 온라인 상태
#define FRIENDSERVER_OFFLINE			1	// 친구 서버 오프라인 상태
#define FRIENDSERVER_ONLINEREQUEST		2	// 친구 서버에 접속 요청 중

#endif

//////////////////////////////////////////////////////////////////////////
//
//	인증 정보
//
//////////////////////////////////////////////////////////////////////////
#ifdef UPDATE_UNIFICATIONBILL_20090203
enum
{
	BILL_TYPE_NONE = 0,				// 없음
	BILL_TYPE_PERSONAL_AMOUNT = 1,				// 개인 정액
	BILL_TYPE_PCBANG_AMOUNT = 2,				// PC방 정액
	BILL_TYPE_PCBANG_QUANTITY = 3,				// PC방 정량
	BILL_TYPE_PERSONAL_QUANTITY = 4,				// 개인 정량
	BILL_TYPE_COLLOR = 5,				// 컬러 요금제(개인)
};
#define MAX_LOGIN_COUNT			6
#else	// UPDATE_UNIFICATIONBILL_20090203
#define MAX_LOGIN_COUNT			3

#define CERTIFYTYPE_ACCOUNT		0			// 계정인증
#define CERTIFYTYPE_IP			1			// IP 인증

#define BILLTYPE_JUNGYANG		0			// 정량 
#define BILLTYPE_JUNGACK		1			// 정액 
#define BILLTYPE_JONGYANG		2			// 종량
#define BILLTYPE_TIME			3			// 시간제		
#define BILLTYPE_DATE			4			// 날짜제
#define BILLTYPE_NOCHARGE		5			// 무료
#endif	// UPDATE_UNIFICATIONBILL_20090203
//----------------------------------------------------------------------------
// 인증서버에 접속하는 프로그램의 타입
#define ST_GAMESERVER				1			// 게임서버 번호

#define DEFMAPSERVERPORT			55900		// Map Server port number
#define DEFJOINSERVERPORT			55970		// Join Server port number
#define DEFDATASERVERPORT			55960		// Game Data Server Port number
#ifdef ADD_GAMESERVER_PARAMETER_20050728
#define DEFEXDBSERVERPORT			55906		// ExDB Server Port number
#endif

//----------------------------------------------------------------------------
// 계정정보에 사용되는 정의들..
#define MAX_JOOMINNUMBERSTR			13		// 주민등록번호 스트링 크기 -를 A 크기이다.
#define MAX_QUESTIONSTR				30		// 질문 스트링 크기
#define MAX_ANSWERSTR				30		// 답변 스트링 크기
#define MAX_PHONENUMBERSTR			20		// 전화번호 스트링 크기
#define MAX_EMAILSTR				50		// e-mail 스트링 크기


//////////////////////////////////////////////////////////////////////////
//
//	서버 타입 정보
//
//////////////////////////////////////////////////////////////////////////
// Server Type
#define ST_JOINSERVER				0		// 인증 접속 서버
#define ST_GAMESERVER				1		// 게임 서버
#define MAX_CHAT					60		// 대화 최대 크기
#define MAX_GUILDNOTICE				60		// 최대 길드 공지 길이


#ifdef GAMESERVER_INFO_TO_CSS_20040317		// 접속서버분산 - 매크로선언
#define MAX_CS_COUNT				32		// 최대 접속서버의 개수
#endif

//////////////////////////////////////////////////////////////////////////
//
//	시스템 기본 정보
//
//////////////////////////////////////////////////////////////////////////
#define MAX_ROADPATH				15		// 사용자가 이동하는 PATH 최대 크기
#define MAX_PATHDIR					8		// 이동에 사용되는 방향 개수
#define MAX_IDSTRING				10		// 아이디 크기
#ifdef UPDATE_USERPASSWORD_LENGTH_20090424
#define MAX_PASSWORD_LENGTH			20
#define MAX_JOOMINNUMBER_LENGTH		20
#else	// UPDATE_USERPASSWORD_LENGTH_20090424
#define MAX_PASSWORD_LENGTH			12
#endif	// UPDATE_USERPASSWORD_LENGTH_20090424
#define DEFAULT_MONEY				0		// 초기 주어지는 돈 액수

#define MAX_LEVEL					1000		// 레벨 최대 크기

#ifdef MASTER_LEVEL_UP_SYSTEM_20070912	// 마스터레벨 최대 크기
#define MAX_MASTER_LEVEL			200
#endif

#ifdef ITEM_12_13_20040401
#define MAX_ITEMLEVEL			15		// 레벨 최대 크기
#else
#define MAX_ITEMLEVEL			15		// 레벨 최대 크기
#endif

#define MAX_PRESENTNAME				50		// 최대 경품 이름

#ifdef MODIFY_ZEN_MAX_20040414
#define MAX_ZEN					2000000000
#else
#define MAX_ZEN					2000000000
#endif

#define MAXVIEWPORTOBJECT			75		// 뷰포트 최대 OBJECT 수 
#ifdef GAMESERVER_TO_CASTLESIEGESERVER		// 공성전 전용서버 일때의 몬스터 뷰포트 변화
#define MAX_MONVIEWPORTOBJECT		75		// 몬스터의 뷰에는 최대 50 마리 까지 표시 (공성전 전용서버 일 때만)
#else
#define MAX_MONVIEWPORTOBJECT		20		// 몬스터의 뷰에는 최대 20 마리 까지 표시
#endif

#define MAXUSERCHARACTER			5		// 유저당 가질수 있는 최대 캐릭터 수

#define MAX_GUILDNAMESTRING			8		// 길드 이름 스트링 길이

#define MAX_GUILDMARKSIZE			32		// 길드 마크 버퍼 크기

#define MAX_DBEQUIPMENT				120		// (12x10) 데이터베이스 읽기&저장되는 장비데이터 크기

#ifdef PERSONAL_SHOP_20040113
#define MAX_PSHOP_TEXT				36		// 개인상점 텍스트의 최대크기

#ifdef ITEM_DBSIZE_EXTEND_20050706
#define MAX_DBINVENTORY				3792//1728	// (8x8x10)+120+(8x4x10) 데이터베이스 읽기&저장되는 인벤토리데이터 크기
#else
#define MAX_DBINVENTORY				1080	// (8x8x10)+120+(8x4x10) 데이터베이스 읽기&저장되는 인벤토리데이터 크기
#endif

#else
#define MAX_DBINVENTORY				760		// (8x8x10)+120 데이터베이스 읽기&저장되는 인벤토리데이터 크기
#endif

#ifdef ITEM_DBSIZE_EXTEND_20050706
#define MAX_ITEMDBBYTE				16		// 아이템이 DB에 저장되는 바이트 수
#define MAX_ITEMDBBYTE_V02			10		// 아이템이 DB에 저장되는 바이트 수
#else
#define MAX_ITEMDBBYTE				10		// 아이템이 DB에 저장되는 바이트 수
#endif

#define MAX_ITEMDBBYTE_V00			7		// 아이템이 DB에 저장되는 바이트 수

#ifdef ITEM_INDEX_EXTEND_20050706
#define ITEM_INDEX_NOT_EXIST		511		// 9비트 아이템 인덱스 (4비트 아이템 타입) 일 경우 존재하지 않는 갑옷류 아이템의 인덱스
#endif

#ifdef ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
#define ITEM_BUFFER_SIZE			12			// 아이템 패킷 버퍼 크기 
#else
#ifdef ITEM_INDEX_EXTEND_20050706
#define ITEM_BUFFER_SIZE			7			// 아이템 패킷 버퍼 크기 
#elif GAME_VERSION >= G_V_99B
#define ITEM_BUFFER_SIZE			5			// 아이템 패킷 버퍼 크기 
#else
#define ITEM_BUFFER_SIZE			4
#endif
#endif // ADD_ITEM_SOCKET_OPTION_EXTEND_20080422

#define MONEY_BUFFER_SIZE			4			// 젠 패킷 버퍼 크기

#ifdef ITEM_DBSIZE_EXTEND_20050706
#define MAX_WAREHOUSEDBSIZE			3840//1920
#else
#define MAX_WAREHOUSEDBSIZE			1200
#endif

#define MAX_WAREHOUSEITEMS			(8*15)

#define MAX_CHAOSBOXSIZE			8*4
#define MAX_CHAOSBOXITEMS			8*4


#define MAX_EQUIPMENT				12
#define MAX_INVENTORYMAP			8*8
#define MAX_INVENTORY				(MAX_EQUIPMENT + MAX_INVENTORYMAP)		// (8x8)+12 인벤토리 최대 개수
#define MAX_TRADEITEM				32				// (8x4) 
#define INVENTORY_EXT4_SIZE			204

#ifdef PERSONAL_SHOP_20040113		
#define MAX_PSHOPITEM				8*4		// (8x4) 개인상점창
#define MAX_PSHOPITEMMAP			8*4		// (8x4) 개인상점창 맵
									//76
#define MAX_INVENTORY_EXTEND		(MAX_INVENTORY + MAX_PSHOPITEM)		// (8x8)+12+(8*4) DB저장 시 인벤토리 최대 개수
#endif

#define MAX_DBMAGIC					(MAX_MAGIC*3)	// 데이터베이스에 저장되는 마법 데이터 크기

#ifdef ITEM_DBSIZE_EXTEND_20050706
#define ITEM_BITSHIFT				9
#else
#define ITEM_BITSHIFT				5
#endif

#ifdef ADD_NOT_SELL_EQUIPITEM_20080625
#define IS_EQUIPITEM(pos)			(pos >= EQUIPMENT_WEAPON_RIGHT && pos < MAX_EQUIPMENT) ? TRUE : FALSE
#endif // ADD_NOT_SELL_EQUIPITEM_20080625

//////////////////////////////////////////////////////////////////////////
//
//	캐릭터에 관련된 정의들
//
//////////////////////////////////////////////////////////////////////////
#define PK_MINIMUM_LEVEL			5		// 사용자끼리 죽일수 있는 최소 레벨 

#ifdef ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912	// 채대 종족 개수 확장
#define MAX_CLASSTYPE				8//6		// 최대 종족 개수 8for s12
#else
#ifdef DARKLORD_WORK
#define MAX_CLASSTYPE				5		// 최대 종족 개수
#else
#define MAX_CLASSTYPE				4		// 최대 종족 개수
#endif
#endif	// ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912

#define MAX_PREVIEWCHARSET			9		// 캐릭터 세트 최대 크기( 미리보기용 버퍼 )

#define MAX_RESISTANCE				7		// 세트 아이템으로 인해 7로 증가


#ifdef GAMESERVER_TO_CASTLESIEGESERVER		// 공성전 전용서버는 사용자 오브젝트의 개수를 늘리고 몬스터 개수를 줄인다.
#if TESTSERVER == 1
#define MAX_OBJECT					7400	// 게임서버의 최대 오브젝트(유저) 수
#define MAX_MONSTER					5800
#define MAX_CALLMONSTER				600
#define MAX_USER					1000
#else
#define MAX_OBJECT					4000	// 게임서버의 최대 오브젝트(유저) 수
#define MAX_MONSTER					1500
#define MAX_CALLMONSTER				1000
#define MAX_USER					1500
#endif	// TESTSERVER

#else

#ifdef MODIFY_ILLUSIONTEMPLE_BUGFIX_3_20070731
#define MAX_OBJECT					9000	// 게임서버의 최대 오브젝트(유저) 수
#define MAX_MONSTER					7400
#define MAX_CALLMONSTER				600
#define MAX_USER					1000
#else
#ifdef CHAOSCASTLE_SYSTEM_20040408
#define MAX_OBJECT					7400	// 게임서버의 최대 오브젝트(유저) 수
#define MAX_MONSTER					5800
#define MAX_CALLMONSTER				600
#define MAX_USER					1000
#else
#define MAX_OBJECT					5650	// 게임서버의 최대 오브젝트(유저) 수
#define MAX_MONSTER					4800
#define MAX_CALLMONSTER				600
#define MAX_USER					250
#endif	// CHAOSCASTLE_SYSTEM_20040408
#endif	// MODIFY_ILLUSIONTEMPLE_BUGFIX_3_20070731
#endif	// GAMESERVER_TO_CASTLESIEGESERVER

#define ALLOC_USEROBJECTSTART		(MAX_MONSTER+MAX_CALLMONSTER)	// 게임서버의 최대 오브젝트(유저) 수

#define OBJTYPE_CHARACTER			1		// 오브젝트 타입이 유저캐릭터이다.
#define OBJTYPE_MONSTER				2		// 오브젝트 타입이 몬스터이다.
#define OBJTYPE_NPC					3		// 오브젝트 타입이  NPC 이다.
#define OBJTYPE_ITEM				5		// 아이템이다.

//----------------------------------------------------------------------------
// Killer Type ( 죽였을
#define KT_CHAR						0		// 플레이어한테 죽었다.
#define KT_MONSTER					1		// 몬스터한테 죽엇따.
#define KT_GUILDWARCHAR				2		// 길드전에서 플레이어가 죽였다.

#ifdef DUEL_SYSTEM_20031028
#define KT_DUELCHAR					3		// 결투 중에 플레이어가 죽였다.
#endif

//////////////////////////////////////////////////////////////////////////
//
// 게임에 사용되는 정의들
//
//////////////////////////////////////////////////////////////////////////
#define MAX_LEVELUPPOINT			5		// 캐릭터당 레벨업 했을때 포인트

#ifdef ADD_GAMBLING_20090120			// 겜블링 상점개수 추가
#define MAX_SHOP						20
#else // ADD_GAMBLING_20090120
#ifdef ADD_SEASON_3_NEW_MAP_20070910	// 엘베란드 상점개수 추가
#define MAX_SHOP						18
#else
#ifdef ADD_SHOP_14_20070308
#define MAX_SHOP						15
#else
#ifdef ADD_FIRECRACKER_NPC_20070306		// 상점 개수 추가
#define MAX_SHOP						14		// 최대 상점 개수
#else	// ADD_FIRECRACKER_NPC_20070306
#ifdef ADD_SHOP_11_12
#define MAX_SHOP					13		// 최대 상점 개수
#else
#define MAX_SHOP					12		// 최대 상점 개수
#endif
#endif	// ADD_FIRECRACKER_NPC_20070306
#endif	// ADD_SHOP_14_20070308
#endif	// ADD_SEASON_3_NEW_MAP_20070910 
#endif	// ADD_GAMBLING_20090120

#define PK_LEVEL_DEFAULT			3		// PK Level 의 기본 값

#ifdef HERO_SYSTEM_MODIFY
#define PK_LEVEL_3_ITEMDROP			2		// PK Level 3 이상의 아이템 드롭율
#define PK_LEVEL_2_ITEMDROP			4		// PK Level 2 이상의 아이템 드롭율
#define PK_LEVEL_1_ITEMDROP			8		// PK Level 1 이상의 아이템 드롭율

#define PK_LEVEL_3_ITEMERASE		8		// PK Level 3 이상의 아이템 소멸율
#define PK_LEVEL_2_ITEMERASE		16		// PK Level 2 이상의 아이템 소멸율
#define PK_LEVEL_1_ITEMERASE		32		// PK Level 1 이상의 아이템 소멸율
#endif

// 퀘스트에서 사용되는 정의들
#define MAX_QUEST					200
#define MAX_DBQUEST					50
#define MAX_QUEST_SUBINFO			10
#define MAX_QUEST_CONDITION			10

#define APPLE_DROPRATE				2000	// 케릭터 레벨이 20 이하일 때 사과 드롭률 (n / 10000)

//----------------------------------------------------------------------------
#define PARTY_LENGTH				130

//----------------------------------------------------------------------------
#ifdef ADD_ITEM_FENRIR_01_20051110
#define MAX_OVERLAP_FENRIR_MIX_STUFF_01		20	// 갑옷 파편
#define MAX_OVERLAP_FENRIR_MIX_STUFF_02		20	// 여신의 가호
#define MAX_OVERLAP_FENRIR_MIX_STUFF_03		10	// 맹수의 발톱

#ifdef ADD_PCS_FULL_RECOVERY_POTION_20070508
#define MAX_OVERLAP_FULL_RECOVERY_POTION	100 // 100% 회복물약 겹치는 갯수
#endif // ADD_PCS_FULL_RECOVERY_POTION_20070508

#define MIN_FENRIR_EQUIP_LEVEL				300	// 300레벨 부터 착용 가능
#define MAX_FENRIR_DAMAGE_INC_LEVEL			5	// 5레벨 마다 스킬데미지 1% 증가

#endif // ADD_ITEM_FENRIR_01_2005

#ifdef NPROTECT_GAME_GAURD_FOR_SERVER_VERSION_25_20060123
#define MAX_USER_FOR_GAMEGUARD_AUTH		1500
#endif // NPROTECT_GAME_GAURD_FOR_SERVER_VERSION_25_20060123


#ifdef UPDATE_SEASON4_MARKET_CONDITIONS_BALANCE_20080828	// 구슬, 스크롤 아이템 드랍 개수 
#ifdef MODIFY_SPEAR_DROP_BUGFIX_20080901
#define MAX_BALLTABLE_SIZE	22
#else	// MODIFY_SPEAR_DROP_BUGFIX_20080901
#define MAX_BALLTABLE_SIZE	22
#endif	// MODIFY_SPEAR_DROP_BUGFIX_20080901
#else	// UPDATE_SEASON4_MARKET_CONDITIONS_BALANCE_20080828
#ifdef MODIFY_ITEM_DROP_FIRESCREAMSCROLL_20060830
#define MAX_BALLTABLE_SIZE	17
#else  
#ifdef MODIFY_ITEM_DROP_MAXINDEX_20060830
#define MAX_BALLTABLE_SIZE	16
#endif // MODIFY_ITEM_DROP_MAXINDEX_20060830
#endif // MODIFY_ITEM_DROP_FIRESCREAMSCROLL_20060830
#endif	// UPDATE_SEASON4_MARKET_CONDITIONS_BALANCE_20080828

#ifdef MODIFY_EXP_LOG_MONSTER_EVENT_INDEX_20060906
enum EXP_GETTING_EVENT_TYPE
{
	EVENT_TYPE_NONE = 0,
	EVENT_TYPE_PARTY = 1,
	EVENT_TYPE_DEVILSQUARE = 2,
	EVENT_TYPE_CHAOSCASTLE = 3,
	EVENT_TYPE_BLOODCASTLE = 4,
	EVENT_TYPE_CRYWOLF = 5
};
#endif // MODIFY_EXP_LOG_MONSTER_EVENT_INDEX_20060906

#ifdef HALLOWINDAY_JACK_O_LANTERN_EVENT_20061017
#define MAX_OVERLAP_JACK_O_LANTERN_POTION	3	// 할로윈 데이 이벤트 포션 겹쳐지는 갯수
#endif

#ifdef MODIFY_CHN_PLAYTIME_LIMIT_SYSTEM_01_20070509
#define PLAYTIME_LIMIT_VERIFY_ADULT		0
#define PLAYTIME_LIMIT_VERIFY_KID		1
#define PLAYTIME_LIMIT_VERIFY_ERROR		2
#endif // MODIFY_CHN_PLAYTIME_LIMIT_SYSTEM_01_20070509

#ifdef ADD_FULL_RECOVERY_POTION_20070719
#define MAX_OVERLAP_ELITE_POTION			50	// 엘리트 물약의 최대 겹쳐지는 갯수
#endif // ADD_FULL_RECOVERY_POTION_20070719

#ifdef ADD_PCS_IMPROVE_POTION_20070718
#define MAX_OVERLAP_IMPROVE_POTION			3	// 비약의 최대 겹쳐지는 갯수
#endif // ADD_PCS_IMPROVE_POTION_20070718

#ifdef ADD_EVENT_CHERRYBLOSSOM_20080312
enum _enumMAXOVERLAP
{
	MAX_OVERLAP_CHERRYBLOSSOM_ITEM_DEFAULT = 3,
	MAX_OVERLAP_CHERRYBLOSSOM_WHITE = 10,
	MAX_OVERLAP_CHERRYBLOSSOM_RED = 30,
#ifdef FOR_KOREA
	MAX_OVERLAP_CHERRYBLOSSOM_GOLD = 255,
#else	// FOR_KOREA
	MAX_OVERLAP_CHERRYBLOSSOM_GOLD = 50,
#endif	// FOR_KOREA
};
#endif // ADD_EVENT_CHERRYBLOSSOM_20080312

#ifdef UPDATE_LUCKY_COIN_EVENT_20081029	// 행운의 동전 겹치기 최대 개수
#define MAX_OVERLAP_LUCKY_COIN			255
#endif	// UPDATE_LUCKY_COIN_EVENT_20081029	


//////////////////////////////////////////////////////////////////////////
//
//	뷰포트 관련 정보
//
//////////////////////////////////////////////////////////////////////////
// 자신이 죽을때 이중에서 아이템을 떨어트리게 된다.
#define Max3(v1, v2, v3) (max((max(v1, v2)),v3))

//----------------------------------------------------------------------------
// 유저의 뷰포트 안에 있는 다른 유저들 상태 정보
#define STVP_NONE		0	// 등록이 안되어있다.
#define STVP_CREATE		1	// Create 되어야 한다.
#define STVP_PLAYING	2	// 활동 중이다.
#define STVP_DESTROY	3	// Destroy 되어야 한다.

typedef struct
{
	char  state;	// 뷰포트에서의 상태
	short number;	// 뷰포트에 등록된 오브젝트의 절대 번호
	BYTE  type;		// 등록된 오브젝트의 형태 (STVP_??????) 참고
	short index;	// 등록된 오브젝트의 몇번째 등록이 되었는지..
	int   dis;		// 거리.
} VIEWPORT_PLAYER_STRUCT;


// 내 화면에 보여지는 사용자 리스트
typedef struct
{
	char  state;		// 뷰포트에서의 상태
	short number;		// 뷰포트에 등록된 오브젝트의 절대 번호
	BYTE  type;			// 등록된 오브젝트의 형태 (STVP_??????) 참고
	short index;		// 등록된 오브젝트의 몇번째 등록이 되었는지..
	int   dis;			// 거리.
						//	short HitDamage;	// 타격 데미지 (누구한테 얼만큼 맞았다)
} VIEWPORT_STRUCT;


#ifdef PERSONAL_SHOP_20040113
// 내 화면에 보여지는 개인상점 리스트 (사람)
typedef struct
{
	bool	bUsing;		// 0:사용않함 / 1:사용함
	short	iIndex;		// 사용자객체 배열의 인덱스
} PSHOP_VIEWPORT_STRUCT;
#endif


#define MAX_HITDAMAGE	40

typedef struct
{
	short number;		// 타격을 가한 유저 번호
	int   HitDamage;	// 타격 데미지 (누구한테 얼만큼 맞았다)
	DWORD LastHitTime;	// 마지막 타격 시간..

} HITDAMAGE_STRUCT;		// 몬스터 타격 데미지에 사용하기 위해

						//////////////////////////////////////////////////////////////////////////
						//
						//	UI Type
						//
						//////////////////////////////////////////////////////////////////////////
#define I_TRADE						1		// 교환 진행중
#define I_PARTY						2		// 파티 진행중
#define I_SHOP						3
#define I_GUILD						4		// 길드 가입 인터페이스
#define I_GUILDCREATE				5		// 길드 생성 인터페이스
#define I_WAREHOUSE					6		// 창고
#define I_CHAOSBOX					7		// 카오스 박스
#define I_INVENTORY					8		// 인벤토리내
#define I_EVENTCHIP					9		// 이벤트칩
#define I_QUEST						10		// 퀘스트
#define I_SERVERDIVISION			11		// 서버분할
#define I_ETCWINDOW					12		// 서버분할
#define I_DARK_TRAINER				13		// 다크호스 트레이너

#ifdef PERSONAL_SHOP_20040113				// 개인상점 인터페이스 코드 (I_SHOP과 같이 쓰고 싶었으나 종료시 초기화할 부분이 다른 관계로 따로 씀)
#define I_PSHOP_OPEN				12		// 개인상점 - 개설한 쪽 만 사용 (방문한 쪽은 I_SHOP)
#endif

#ifdef ADD_NEW_UNION_01_20041006
#define I_UNION						14		// 연합, 라이벌 관련 인터페이스.
#endif

#ifdef ADD_NEW_WEAPON_FOR_CASTLE_01_20041116
#define I_CS_MACHINE_ATTACK			15		// 공성 무기
#define I_CS_MACHINE_DEFENSE		16		// 수성 무기
#endif

#ifdef ADD_CASTLE_HUNTZONE_NPC_01_20050111
#define I_CS_HUNTZONE_GUARD			17		// 사냥터 문지기	
#endif

#ifdef PCBANG_POINT_SYSTEM_20070206			// 상점 인덱스
#define I_PCBANG_POINT_SHOP			18		// PC방 포인트 상점
#endif

#ifdef ADD_PARTIALY_CHARGE_CASH_SHOP_20070117
#ifdef ADD_PARTIALY_CHARGE_ON
#define I_CASHSHOP_INTERFACE		19
#else
#define I_CASHSHOP_INTERFACE		18
#endif // ADD_PARTIALY_CHARGE_ON
#endif // ADD_PARTIALY_CHARGE_CASH_SHOP_20070117

#ifdef MODIFY_JEWELMIXSYSTEM_BUGFIX_20081020
enum _eInterfaceState
{
	I_JEWEL = 20,
};

#define	IS_MIXJEWEL(u, t)		(u == 1 && t == I_JEWEL) ? TRUE : FALSE

#endif // MODIFY_JEWELMIXSYSTEM_BUGFIX_20081020

#ifdef PERSONAL_SHOP_20040113
// 아이템 이동 (0x24) 시 사용되는 위치 매크로
#define ITEMMOVE_INVENTORY			0		// 이동위치 - 인벤토리
#define ITEMMOVE_TRADEWND			1		// 이동위치 - 거래창
#define ITEMMOVE_WAREHOUSE			2		// 이동위치 - 창고
#define ITEMMOVE_CHAOSBOX			3		// 이동위치 - 카오스상자
#define ITEMMOVE_PSHOPWND			4		// 이동위치 - 개인상점
#else
#define ITEMMOVE_INVENTORY			0		// 이동위치 - 인벤토리
#define ITEMMOVE_TRADEWND			1		// 이동위치 - 거래창
#define ITEMMOVE_WAREHOUSE			2		// 이동위치 - 창고
#define ITEMMOVE_CHAOSBOX			3		// 이동위치 - 카오스상자
#define ITEMMOVE_PSHOPWND			4		// 이동위치 - 개인상점
#endif

#ifdef DARKLORD_WORK
#define ITEMMOVE_DARK_TRAINER			5	// 이동 위치 - 다크로드(조련사)
#endif

#ifdef ADD_JEWEL_OF_HARMONY_SYSTEM_20060530
#define	ITEMMOVE_JEWELOFHARMONY_PURITY	6	// 이동 위치 - 조화의보석 정제 ( NPC )
#define ITEMMOVE_JEWELOFHARMONY_SMELT	7	// 이동 위치 - 제련석 ( NPC )
#define ITEMMOVE_JEWELOFHARMONY_RESTORE 8	// 이동 위치 - 환원 ( NPC )
#endif // ADD_JEWEL_OF_HARMONY_SYSTEM_20060530

#ifdef ADD_PCS_LOTTERY_SYSTEM_20070117
#define ITEMMOVE_LOTTERY_MIX	9
#endif // ADD_PCS_LOTTERY_SYSTEM_20070117

#ifdef ADD_EVENT_CHERRYBLOSSOM_20080312
#define ITEMMOVE_CHERRYBLOSSOM	10
#endif // ADD_EVENT_CHERRYBLOSSOM_20080312

#ifdef ADD_ITEM_SOCKET_OPTION_MIX_20080415
#define ITEMMOVE_SOCKET_ITEM_EXTRACT	11
#define ITEMMOVE_SOCKET_ITEM_COMPOSIT	12
#define ITEMMOVE_SOCKET_ITEM_EQUIP		13
#define ITEMMOVE_SOCKET_ITEM_REMOVE		14
#endif // ADD_ITEM_SOCKET_OPTION_MIX_20080415

#ifdef CASTLE_SPECIAL_ITEMMIX_20050425
#define	CASTLE_ITEM_MIX_MAXCOUNT		1	// 성주 조합 시 아이템 최대 조합가능 횟수
#endif

//////////////////////////////////////////////////////////////////////////
//
// 맵 관련 정보
//
//////////////////////////////////////////////////////////////////////////
#define MAX_MAPITEM					300

#ifdef ADD_NEWPVP_PKFIELD
#define MAX_MAP						116//65		// 크리스마스 맵
#else

#ifdef UPDATE_XMASEVENT_MAP_20080930
#define MAX_MAP						63		// 크리스마스 맵
#else

#ifdef ADD_RAKLION_20080408
#define MAX_MAP						59		// 빙하호수 맵
#else
#ifdef UPDATE_NEWMAP_SWAMP_OF_CALMNESS_20080108
#define MAX_MAP						57		//	마스터레벨 전용 평온의늪
#else
#ifdef ADD_CHAOSCASTLE_FOR_MASTER_LEVEL_20071010	
#define MAX_MAP						54		// 마스터레벨 전용등급 카오스캐슬
#else
#ifdef ADD_BLOODCASTLE_FOR_MASTER_LEVEL_20071010
#define MAX_MAP						53		// 마스터레벨 전용등급 블러드캐슬
#else
#ifdef ADD_SEASON_3_NEW_MAP_20070910
#define MAX_MAP						52		// 시즌 3 신규 맵
#else
#ifdef ADD_EVENT_MAP_ILLUSION_TEMPLE_20070328
#define	MAX_MAP						51		// 신규 이벤트 맵
#else
#ifdef UPDATE_BEFORE_ILLUSION_TEMPLE_MAX_MAP_20070702
#define	MAX_MAP						43		// 신규 이벤트 맵이전 최대 맵 수 재 설정
#else
#ifdef UPDATE_GM_FUNCTION_20070228
#define MAX_MAP						41		// GM 소환 지역 추가
#else
#ifdef ADD_NEW_MAP_KANTURU_BOSS_20060627
#define MAX_MAP						40		// 칸투르 보스맵 추가
#else
#ifdef ADD_NEW_MAP_KANTURU_COMMON_20060523
#define MAX_MAP						39		// 칸투르 일반 맵 추가 (2)
#else
#ifdef HIDDEN_KALIMA_20050706
#define MAX_MAP						37		// 히든 칼리마 추가
#else
#ifdef ADD_NEW_MAP_CRYWOLF_SECONDZONE_20050414
#define MAX_MAP						36		// 크라이울프 2차맵이 추가 되었다.
#else
#ifdef ADD_NEW_MAP_CRYWOLF_FIRSTZONE_20050414
#define MAX_MAP						35		// 크라이울프 1차맵이 추가 되었다.
#else
#ifdef ADD_NEW_MAP_AIDA_20050617
#define MAX_MAP						34		// 아이다 맵이 추가 되었다.
#else
#ifdef DEVILSQUARE_EXTEND_20050221			// 데빌스퀘어 맵추가
#define MAX_MAP						33		// 데빌스퀘어 맵이 확장 되었다.
#else
#ifdef ADD_NEW_MAP_CASTLE_HUNTZONE_20041115
#define MAX_MAP						32		// 성 사냥터 맵이 추가 되었다.
#else
#ifdef ADD_NEW_MAP_CASTLE_20041115
#define MAX_MAP						31		// 성 맵이 추가되었다.
#else
#ifdef ADD_NEW_MAP_KALIMA_20040518
#define MAX_MAP						30		// 신규맵 칼리마가 추가되었다.
#else
#ifdef CHAOSCASTLE_SYSTEM_20040408 
#define MAX_MAP						24		// 카오스 캐슬이 추가되었다.
#else
#ifdef BLOODCASTLE_EXTEND_20040314			// 블러드캐슬 확장으로 인해 맵이 추가되었다.
#define MAX_MAP						18
#else
#ifdef FOR_BLOODCASTLE
#define MAX_MAP						17
#else
#ifdef NEW_SKILL_FORSKYLAND
#define MAX_MAP						11
#else
#define MAX_MAP						10
#endif
#endif		// FOR_BLOODCASTLE
#endif		// BLOODCASTLE_EXTEND_20040314
#endif		// CHAOSCASTLE_SYSTEM_20040408
#endif		// ADD_NEW_MAP_KALIMA_20040518
#endif		// ADD_NEW_MAP_CASTLE_20041115
#endif		// ADD_NEW_MAP_CASTLE_HUNTZONE_20041115
#endif		// DEVILSQUARE_EXTEND_20050221
#endif		// ADD_NEW_MAP_AIDA_20050617
#endif		// ADD_NEW_MAP_CRYWOLF_FIRSTZONE_20050414
#endif		// ADD_NEW_MAP_CRYWOLF_SECONDZONE_20050414
#endif		// HIDDEN_KALIMA_20050706
#endif		// ADD_NEW_MAP_KANTURU_COMMON_20060523
#endif		// ADD_NEW_MAP_KANTURU_BOSS_20060627
#endif		// UPDATE_GM_FUNCTION_20070228
#endif		// UPDATE_BEFORE_ILLUSION_TEMPLE_MAX_MAP_20070702
#endif		// ADD_EVENT_MAP_ILLUSION_TEMPLE_20070328
#endif		// ADD_SEASON_3_NEW_MAP_20070910
#endif		// ADD_BLOODCASTLE_FOR_MASTER_LEVEL_20071010
#endif		// ADD_CHAOSCASTLE_FOR_MASTER_LEVEL_20071010
#endif		// UPDATE_NEWMAP_SWAMP_OF_CALMNESS_20080108
#endif		// ADD_RAKLION_20080408

#endif		// UPDATE_XMASEVENT_MAP_20080930
#endif		// ADD_NEWPVP_PKFIELD

enum MAP_INDEX
{
	MAP_INDEX_RORENCIA = 0,
	MAP_INDEX_DUNGEON = 1,
	MAP_INDEX_DEVIAS = 2,
	MAP_INDEX_NORIA = 3,
	MAP_INDEX_LOSTTOWER = 4,
	MAP_INDEX_RESERVED = 5,
	MAP_INDEX_BATTLESOCCER = 6,
	MAP_INDEX_ATHLANSE = 7,
	MAP_INDEX_TARKAN = 8,
	MAP_INDEX_DEVILSQUARE = 9,
	MAP_INDEX_ICARUS = 10,

	// 블러드 캐슬
	MAP_INDEX_BLOODCASTLE1 = 11,
	MAP_INDEX_BLOODCASTLE2 = 12,
	MAP_INDEX_BLOODCASTLE3 = 13,
	MAP_INDEX_BLOODCASTLE4 = 14,
	MAP_INDEX_BLOODCASTLE5 = 15,
	MAP_INDEX_BLOODCASTLE6 = 16,
#ifdef BLOODCASTLE_EXTEND_20040314
	MAP_INDEX_BLOODCASTLE7 = 17,
#endif


#ifdef CHAOSCASTLE_SYSTEM_20040408		// 카오스 캐슬 맵 인덱스
	MAP_INDEX_CHAOSCASTLE1 = 18,
	MAP_INDEX_CHAOSCASTLE2 = 19,
	MAP_INDEX_CHAOSCASTLE3 = 20,
	MAP_INDEX_CHAOSCASTLE4 = 21,
	MAP_INDEX_CHAOSCASTLE5 = 22,
	MAP_INDEX_CHAOSCASTLE6 = 23,
#endif

#ifdef ADD_NEW_MAP_KALIMA_20040518		// 칼리마 맵 인덱스
	MAP_INDEX_KALIMA1 = 24,
	MAP_INDEX_KALIMA2 = 25,
	MAP_INDEX_KALIMA3 = 26,
	MAP_INDEX_KALIMA4 = 27,
	MAP_INDEX_KALIMA5 = 28,
	MAP_INDEX_KALIMA6 = 29,
#endif

#ifdef CASTLE_SIEGE_COMMON_PATCH_20041018		// 성 맵 인덱스
	MAP_INDEX_CASTLESIEGE = 30,
#endif

#ifdef ADD_NEW_MAP_CASTLE_HUNTZONE_20041115		// 성 사냥터
	MAP_INDEX_CASTLEHUNTZONE = 31,
#endif

#ifdef DEVILSQUARE_EXTEND_20050221				// 데빌스퀘어 확장
	MAP_INDEX_DEVILSQUARE2 = 32,
#endif
#ifdef ADD_NEW_MAP_AIDA_20050617
	MAP_INDEX_AIDA = 33,		// 아이다 맵
#endif
#ifdef ADD_NEW_MAP_CRYWOLF_FIRSTZONE_20050414
	MAP_INDEX_CRYWOLF_FIRSTZONE = 34,		// 크라이울프 1차맵
#endif

#ifdef ADD_NEW_MAP_CRYWOLF_SECONDZONE_20050414
	MAP_INDEX_CRYWOLF_SECONDZONE = 35,		// 크라이울프 2차맵
#endif

#ifdef HIDDEN_KALIMA_20050706
	MAP_INDEX_KALIMA7 = 36,		// 히든 칼리마
#endif

#ifdef ADD_NEW_MAP_KANTURU_COMMON_20060523
	MAP_INDEX_KANTURU1 = 37,		// 칸투르 1차맵
	MAP_INDEX_KANTURU2 = 38,		// 칸투르 2차맵 	
#endif

#ifdef ADD_NEW_MAP_KANTURU_BOSS_20060627
	MAP_INDEX_KANTURU_BOSS = 39,		// 칸투르 보스맵	
#endif

#ifdef UPDATE_GM_FUNCTION_20070228
	MAP_INDEX_GM_MAP = 40,		// GM 소환 지역
#endif

#ifdef THIRD_CHANGEUP_SYSTEM_20070507	// 3차 전직 맵 인덱스 추가
	MAP_INDEX_3RD_CHANGEUP_QUEST = 41,		// 3차 전직 퀘스트 맵
	MAP_INDEX_3RD_CHANGEUP_BOSS_QUEST = 42,		// 3차 전직 퀘스트 보스맵
#endif

#ifdef ADD_SEASON_3_NEW_MAP_20070910
	MAP_INDEX_ILLUSION_TEMPLE1 = 45,		// 제 1 환영 사원 맵번호
	MAP_INDEX_ILLUSION_TEMPLE2 = 46,		// 제 2 환영 사원 맵번호
	MAP_INDEX_ILLUSION_TEMPLE3 = 47,		// 제 3 환영 사원 맵번호
	MAP_INDEX_ILLUSION_TEMPLE4 = 48,		// 제 4 환영 사원 맵번호
	MAP_INDEX_ILLUSION_TEMPLE5 = 49,		// 제 5 환영 사원 맵번호
	MAP_INDEX_ILLUSION_TEMPLE6 = 50,		// 제 6 환영 사원 맵번호

	MAP_INDEX_ELBELAND = 51,		// 신규캐릭터맵 '엘베란드'
#endif

#ifdef ADD_BLOODCASTLE_FOR_MASTER_LEVEL_20071010
	MAP_INDEX_BLOODCASTLE8 = 52,	// 블러드캐슬8
#endif
#ifdef ADD_CHAOSCASTLE_FOR_MASTER_LEVEL_20071010
	MAP_INDEX_CHAOSCASTLE7 = 53,	// 카오스캐슬7	
#endif
#ifdef UPDATE_NEWMAP_SWAMP_OF_CALMNESS_20080108
	MAP_INDEX_SWAMP_OF_CALMNESS = 56,	// 평온의늪
#endif
#ifdef ADD_RAKLION_20080408
	MAP_INDEX_RAKLION_FIELD = 57,	// 빙하 호수 필드
	MAP_INDEX_RAKLION_BOSS = 58,	// 빙하 호수 보스 존
#endif // ADD_RAKLION_20080408
#ifdef UPDATE_XMASEVENT_MAP_20080930
	MAP_INDEX_XMASEVENT = 62, //크리스마스 이벤트 맵
#endif // UPDATE_XMASEVENT_MAP_20080930
#ifdef ADD_NEWPVP_PKFIELD
	MAP_INDEX_VULCANUS = 63, // 불카누스폐허
	MAP_INDEX_PKFIELD = 64, // PK 필드
#endif // ADD_NEWPVP_PKFIELD
};


//////////////////////////////////////////////////////////////////////////
//
//	국가별 패킷 
//
//////////////////////////////////////////////////////////////////////////

// 0xDx 번대로 가자!!!!! ~_~
#ifdef PACKET_CHANGE
#if GAME_VERSION == G_V_99B
#define CHINESE_PACKET
#define PACKET_CHANGE_CHINA_V3
#elif GAME_VERSION == G_V_S2_2
#define JAPAN_PACKET
#elif defined(JAPAN_S4_6)
#define JAPAN_PACKET
#elif GAME_VERSION == G_V_S4_6 || GAME_VERSION == G_V_S1_512
#define KOREAN_PACKET
#endif

#ifdef KOREAN_PACKET
#define PACKET_MOVE				0xD3 
#define PACKET_POSITION			0xDF 
#define PACKET_MAGIC_ATTACK		0x10 
#define PACKET_ATTACK			0xD7
#endif

#ifdef JAPAN_PACKET
#define PACKET_MOVE				0X1D 
#define PACKET_POSITION			0XD6 
#define PACKET_MAGIC_ATTACK		0XD7 
#define PACKET_ATTACK			0XDC
#endif

#ifdef CHINESE_PACKET
#ifdef PACKET_CHANGE_CHINA_V3
#define PACKET_MOVE				0XD7
#ifdef MODIFY_PACKET_POSITION_PROTOCOL_CODE_20071126
#define PACKET_POSITION			0XD2
#else
#define PACKET_POSITION			0XD0 
#endif // MODIFY_PACKET_POSITION_PROTOCOL_CODE_20071126 
#define PACKET_MAGIC_ATTACK		0X1D 
#define PACKET_ATTACK			0XD9
#else
#define PACKET_MOVE				0XDD 
#define PACKET_POSITION			0XD3 
#define PACKET_MAGIC_ATTACK		0XD9 
#define PACKET_ATTACK			0XDE
#endif
#endif


#ifdef TAIWAN_PACKET
#define PACKET_MOVE				0XD6 
#define PACKET_POSITION			0XDF 
#ifdef MODIFY_PACKET_POSITION_PROTOCOL_CODE_20071126
#define PACKET_MAGIC_ATTACK		0XD2
#else
#define PACKET_MAGIC_ATTACK		0XD0 
#endif // MODIFY_PACKET_POSITION_PROTOCOL_CODE_20071126
#define PACKET_ATTACK			0XDD
#endif

#ifdef THAILAND_PACKET
#define PACKET_MOVE				0X11 
#define PACKET_POSITION			0XD4 
#define PACKET_MAGIC_ATTACK		0XD9 
#define PACKET_ATTACK			0XD6
#endif

#ifdef GLOBAL_PACKET
#define PACKET_MOVE				0XD4 
#define PACKET_POSITION			0X15 
#define PACKET_MAGIC_ATTACK		0XDB 
#define PACKET_ATTACK			0X11
#endif

#ifdef FOR_PHILIPPINE
#define PACKET_MOVE				0XDD 
#define PACKET_POSITION			0XDF 
#define PACKET_MAGIC_ATTACK		0X11 
#define PACKET_ATTACK			0XD6
#endif

#ifdef FOR_VIETNAM		// 베트남
#define PACKET_MOVE				0xD9 
#define PACKET_POSITION			0xDC 
#define PACKET_MAGIC_ATTACK		0x1D 
#define PACKET_ATTACK			0x15
#endif

#ifdef FOR_USA
#define PACKET_MOVE				0XD4 
#define PACKET_POSITION			0X15 
#define PACKET_MAGIC_ATTACK		0XDB 
#define PACKET_ATTACK			0X11
#endif

#else
#define PACKET_MOVE				0x10 
#define PACKET_POSITION			0x11 
#define PACKET_MAGIC_ATTACK		0x1D 
#define PACKET_ATTACK			0x15
#endif

//////////////////////////////////////////////////////////////////////////
//
//	보안
//
//////////////////////////////////////////////////////////////////////////
#define AUTH_CHECK_00			((char)0x29)
#define AUTH_CHECK_01			((char)0x23)
#define AUTH_CHECK_02			((char)0xBE)
#define AUTH_CHECK_03			((char)0x84)
#define AUTH_CHECK_04			((char)0xE1)
#define AUTH_CHECK_05			((char)0x6C)
#define AUTH_CHECK_06			((char)0xD6)
#define AUTH_CHECK_07			((char)0xAE)
#define AUTH_CHECK_08			((char)0x52)
#define AUTH_CHECK_09			((char)0x90)
#define AUTH_CHECK_10			((char)0x49)
#define AUTH_CHECK_11			((char)0xF1)
#define AUTH_CHECK_12			((char)0xF1)
#define AUTH_CHECK_13			((char)0xBB)
#define AUTH_CHECK_14			((char)0xE9)
#define AUTH_CHECK_15			((char)0xEB)
#define AUTH_CHECK_16			((char)0xB3)
#define AUTH_CHECK_17			((char)0xA6)
#define AUTH_CHECK_18			((char)0xDB)
#define AUTH_CHECK_19			((char)0x00)


//////////////////////////////////////////////////////////////////////////
//
//	조합 정보
//
//////////////////////////////////////////////////////////////////////////
enum CHAOS_TYPE
{
	CHAOS_TYPE_DEFAULT = 1,
	CHAOS_TYPE_DEVILSQUARE = 2,
	CHAOS_TYPE_UPGRADE_10 = 3,
	CHAOS_TYPE_UPGRADE_11 = 4,
#ifdef ITEM_12_13_20040401
	CHAOS_TYPE_UPGRADE_12 = 22,
	CHAOS_TYPE_UPGRADE_13 = 23,
#endif
	CHAOS_TYPE_DINORANT = 5,
	CHAOS_TYPE_FRUIT = 6,
	CHAOS_TYPE_SECOND_WING = 7,
	CHAOS_TYPE_BLOODCATLE = 8,
	CHAOS_TYPE_FIRST_WING = 11,
#ifdef ITEM_12_13_20040401
	CHAOS_TYPE_SETITEM = 12,
#endif
#ifdef DARKLORD_WORK
	CHAOS_TYPE_DARKHORSE = 13,
	CHAOS_TYPE_DARKSPIRIT = 14,
	CHAOS_TYPE_CLOAK = 24,
#endif

#ifdef ADD_NEW_ITEM_FOR_CASTLE_01_20041116
	CHAOS_TYPE_BLESS_POTION = 15,
	CHAOS_TYPE_SOUL_POTION = 16,
	CHAOS_TYPE_LIFE_STONE = 17,
#endif

#ifdef CASTLE_SPECIAL_ITEMMIX_20050425
	CHAOS_TYPE_CASTLE_ITEM = 18,			// 성주 혜택으로 특별하게 조합 가능한 아이템
#endif

#ifdef HIDDEN_TREASUREBOX_EVENT_20050804	// 숨겨진 보물상자 이벤트 - 수정조합
	CHAOS_TYPE_HT_BOX = 20,
#endif

#ifdef ADD_ITEM_FENRIR_01_20051110
	CHAOS_TYPE_FENRIR_01 = 25,			// 펜릴 조합 1단계 - 뿔피리 조각
	CHAOS_TYPE_FENRIR_02 = 26,			// 펜릴 조합 2단계 - 부러진 뿔피리
	CHAOS_TYPE_FENRIR_03 = 27,			// 펜릴 조합 3단계 - 펜릴의 뿔피리
	CHAOS_TYPE_FENRIR_04 = 28,			// 펜릴 조합 4단계 - 펜릴의 뿔피리 업그레이드
#endif

#ifdef ADD_SHIELD_POINT_01_20060403
	CHAOS_TYPE_COMPOUNDPOTION_LV1 = 30,
	CHAOS_TYPE_COMPOUNTPOTION_LV2 = 31,
	CHAOS_TYPE_COMPOUNTPOTION_LV3 = 32,
#endif

#ifdef ADD_JEWEL_OF_HARMONY_SYSTEM_20060530
	CHAOS_TYPE_JEWELOFHARMONY_PURITY = 33,	// 조화의보석 원석 정제
	CHAOS_TYPE_JEWELOFHARMONY_MIX_SMELTINGITEM = 34,	// 제련석 조합
	CHAOS_TYPE_JEWELOFHARMONY_RESTORE_ITEM = 35,	// 강화아이템 환원
#endif // ADD_JEWEL_OF_HARMONY_SYSTEM_20060530

#ifdef ADD_380ITEM_NEWOPTION_20060711
	CHAOS_TYPE_380_OPTIONITEM = 36,	// 380 아이템 조합
#endif // ADD_380ITEM_NEWOPTION_20060711

#ifdef ADD_EVENT_MAP_ILLUSION_TEMPLE_20070328	// 피의 두루마리 아이템 조합 타입
	CHAOS_TYPE_ILLUSION_TEMPLE_ITEM = 37,	// 피의 두루마리 아이템 조합
#endif

#ifdef ADD_THIRD_WING_20070525	// 날개 조합 번호
	CHAOS_TYPE_THIRD_WING_1 = 38,		// 3차 날개 조합 - 1차	
	CHAOS_TYPE_THIRD_WING_2 = 39,		// 3차 날개 조합 - 2차	
#endif	

#ifdef ADD_PCS_LOTTERY_SYSTEM_20070117
	CHAOS_TYPE_LOTTERY_MIX = 40,
	/*
	ADD_PCS_LOTTERY_SYSTEM_20070117 빌드로 임시로 처리
	#ifdef ADD_PARTIALY_CHARGE_ON
	CHAOS_TYPE_LOTTERY_MIX		= 40,
	#else
	CHAOS_TYPE_LOTTERY_MIX		= 37,
	#endif // ADD_PARTIALY_CHARGE_ON
	*/
#endif // ADD_PCS_LOTTERY_SYSTEM_20070117

#ifdef ADD_EVENT_CHERRYBLOSSOM_20080312
	CHAOS_TYPE_CHERRY_MIX = 41,
#endif // ADD_EVENT_CHERRY_20080312

#ifdef ADD_ITEM_SOCKET_OPTION_MIX_20080415
	CHAOS_TYPE_SEED_EXTRACT = 42,
	CHAOS_TYPE_SEED_COMPOSIT = 43,
	CHAOS_TYPE_SEED_EQUIP = 44,
	CHAOS_TYPE_SEED_REMOVE = 45,
#endif // ADD_ITEM_SOCKET_OPTION_MIX_20080415
};

//////////////////////////////////////////////////////////////////////////
//
//	옵션 정보
//
//////////////////////////////////////////////////////////////////////////
#ifdef EVENT_OPTION_RELOAD_20040305					// 뮤의 이벤트 옵션만 다시 읽기 위함

enum MU_EVENT_TYPE {
	MU_EVENT_ALL = 0,			// 모든 이벤트의 옵션을 읽음

	MU_EVENT_DEVILSQUARE = 1,			// 데빌스퀘어
	MU_EVENT_BLOODCASTLE = 2,			// 블러드캐슬

	MU_EVENT_ATTACKEVENTTROOP = 3,			// 지하 군단
	MU_EVENT_GOLDENTROOP = 4,			// 황금 군단
	MU_EVENT_WHITEMAGETROOP = 5,			// 백색마법사 군단

	MU_EVENT_LOVEPANGPANG = 6,			// 러브팡팡 이벤트 (몬스터에게서 하루 일정개수의 사랑의하트 (14,12) 드롭됨, 수호길드 이벤트)
	MU_EVENT_FIRECRACKER = 7,			// 폭죽 이벤트 (몬스터 죽일 때 폭죽 (14,11) 드롭됨 -> 한국은 아틀라스 이하등 특정지역만)
	MU_EVENT_MEDALION = 8,			// 메달 이벤트 (뮤월드 각 지역에 따라 은메달, 금메달 등이 나온다.)
	MU_EVENT_XMASSTAR = 9,			// 성탄의별 이벤트 (몬스터에게서 성탄의별이 드롭됨)
	MU_EVENT_HEARTOFLOVE = 10,			// 사랑의하트 이벤트 (몬스터에게서 사랑의하트가 드롭됨)

	MU_EVENT_SAY_HAPPYNEWYEAR = 11,			// NPC가 새해인사를 한다.
	MU_EVENT_SAY_MERRYXMAS = 12,			// NPC가 메리 크리스마스라고 말한다.

#ifdef CHAOSCASTLE_SYSTEM_20040408 
	MU_EVENT_CHAOSCASTLE = 13,			// 카오스캐슬
#endif

#ifdef CHRISTMAS_RIBBONBOX_EVENT_20051212
	MU_EVENT_CHRISTMAS_RIBBONBOX = 14,			// 크리스마스 리본상자 이벤트( 몬스터에게서 빨강,초록,파랑 리본상자가 드롭됨 )
#endif

#ifdef VALENTINES_DAY_BOX_EVENT_20060124
	MU_EVENT_VALENTINESDAY_CHOCOLATEBOX = 15,		// 발렌타인데이 초콜릿상자 이벤트( 몬스터에게서 분송,빨강,파랑 초콜릿상자가 드롭됨 )
#endif

#ifdef WHITEDAY_CANDY_BOX_EVENT_20060222
	MU_EVENT_WHITEDAY_CANDYBOX = 16,			// 화이트데이 사탕상자 이벤트( 몬스터에게서 연보라,주황,감청 사탕상자가 드롭됨 )
#endif

};

#endif


#ifdef ETC_OPTION_RELOAD_20040308					// 뮤의 옵션 중 이벤트 외의 것들만 리로드

enum MU_ETC_TYPE
{
	MU_ETC_ALL = 0,			// 모든 게임외의 옵션 리로드
	MU_ETC_CREATECHARACTER = 1,			// 케릭터 생성
	MU_ETC_GUILD = 2,			// 길드 생성
	MU_ETC_TRADE = 3,			// 거래
	MU_ETC_USECHAOSBOX = 4,			// 카오스박스 사용
	MU_ETC_PERSONALSHOP = 5,			// 개인상점
	MU_ETC_PKITEMDROP = 6,			// PK시 아이템 드롭여부
	MU_ETC_ITEMDROPRATE = 7,			// 아이템 드롭확률
	MU_ETC_SPEEDHACK = 8,			// 스피드핵
	MU_ETC_GAMEGUARD = 9,			// 게임가드 체크섬 체크여부
};

#endif


enum DATA_FILE_INDEX				// !!! . 이 번호가 WzVersionManager 에서 GetPrivateProfileString() 으로 읽은 뒤 연결해주는 파일 ID번호와 같아야 함
{
	FILE_ITEM = 0,		// Item(kor).txt
	FILE_ITEMLOCAL = 1,		// 국가별 Item.txt
	FILE_SKILL = 2,		// Skill(kor).txt
	FILE_SKILLLOCAL = 3,		// 국가별 skill.txt
	FILE_QUEST = 4,		// Quest(kor).txt
	FILE_QUESTLOCAL = 5,		// 국가별 Quest.txt
	FILE_CHECKSUM = 6,		// Checksum.dat
	FILE_MONSTER = 7,		// Monster.txt
	FILE_GATE = 8,		// Gate.txt
	FILE_MONSTERSETBASE = 9,		// MonsterSetBase.txt
	FILE_NPGGAUTH = 10,		// CSAuth.dat
	FILE_SHOP0 = 11,		// Shop0.txt
	FILE_SHOP1 = 12,		// Shop1.txt
	FILE_SHOP2 = 13,		// Shop2.txt
	FILE_SHOP3 = 14,		// Shop3.txt
	FILE_SHOP4 = 15,		// Shop4.txt
	FILE_SHOP5 = 16,		// Shop5.txt
	FILE_SHOP6 = 17,		// Shop6.txt
	FILE_SHOP7 = 18,		// Shop7.txt
	FILE_SHOP8 = 19,		// Shop8.txt
	FILE_SHOP9 = 20,		// Shop9.txt
	FILE_SHOP10 = 21,		// Shop10.txt
	FILE_SHOP11 = 22,		// Shop11.txt
	FILE_SHOP12 = 23,		// Shop12.txt

	FILE_MOVEREQ = 24,		// movereq(local).txt
	FILE_MOVEREQLOCAL = 25,		// 국가별 movereq.txt
	FILE_SETITEMOPTION = 26,		// itemsetoption(Kor).txt
	FILE_SETITEMOPTIONLOCAL = 27,	// (국가별) itemsetoption.txt
	FILE_SETITEMTYPE = 28,		// itemsettype(Kor).txt
	FILE_SETITEMTYPELOCAL = 29,	// (국가별) itemsettype.txt	

								// 앞으로 SHOP이나 다른 데이터르 추가할 때는 기존 요청번호가 밀리지 않도록 뒤로 들어가야 한다.
#ifdef ADD_FIRECRACKER_NPC_20070306
								FILE_SHOP13 = 30,		// Shop13.txt
#endif
#ifdef ADD_SHOP_14_20070308	
								FILE_SHOP14 = 31,		// Shop14.txt
#endif
#ifdef ADD_SEASON_3_NEW_MAP_20070910	// 엘베란드 상점목록
								FILE_SHOP15 = 32,		// Shop15.txt
								FILE_SHOP16 = 33,		// Shop16.txt
								FILE_SHOP17 = 34,		// Shop17.txt
#endif
#ifdef ADD_GAMBLING_20090120		// 겜블링 상점
								FILE_SHOP18 = 35,		// Shop18.txt
#endif // ADD_GAMBLING_20090120
};


// 메인 이벤트
#define EVENTMASK_DevilSquareEvent			0x00000001		// 데빌스퀘어
#define EVENTMASK_BloodCastleEvent			0x00000002		// 블러드캐슬

// 서브 이벤트
#define EVENTMASK_XMasEvent					0X00000100		// 성탄의별
#define EVENTMASK_FireCrackerEvent			0X00000200		// 폭죽
#define EVENTMASK_HeartOfLoveEvent			0X00000400		// 사랑의 하트
#define EVENTMASK_MedalEvent				0X00000800		// 메달이벤트
#define EVENTMASK_RingAttackEvent			0X00001000		// 반지이벤트
#define EVENTMASK_EventChipEvent			0X00002000		// 레나이벤트
#define EVENTMASK_IsEledoradoEvent			0X00004000		// 황금정예이벤트

// 기타 설정
#define EVENTMASK_UseNPGGChecksum			0X00010000	// 게임가드 사용 



///////////////////////////////////////////////////////////////////
//
//	연합 시스템 (apple)
//
///////////////////////////////////////////////////////////////////////
#ifdef ADD_NEW_GUILD_01_20040913

#define MIN_UNION_MASTER_GUILD_MEMBERCOUNT	20
#define MAX_RELATIONSHIP_COUNT				100 
#define INVALID_USER_INDEX					-1

#ifdef MODIFY_MAX_UNION_MEMBER_01_20050418

#ifdef FOR_KOREA
#define MAX_UNION_MEMBER_COUNT				3
#define MAX_TESTSERVER_UNION_MEMBER_COUNT	3
#else
#define MAX_UNION_MEMBER_COUNT				5
#define MAX_TESTSERVER_UNION_MEMBER_COUNT	5
#endif

#else

#define MAX_UNION_MEMBER_COUNT				7
#define MAX_TESTSERVER_UNION_MEMBER_COUNT	12

#endif


enum GUILD_NOTIFICATION
{
	G_NOTIFICATION_SET = 0x01,
	G_NOTIFICATION_UNION_BREAKOFF = 0x10

};

enum GUILD_OPERATION_ERRORCODE
{
	G_ERROR_NONE = 0

	// 0x10~ Common Result

};

enum GUILD_RELATION_OPERATION
{
	G_RELATION_OPERATION_JOIN = 1,
	G_RELATION_OPERATION_BREAKOFF = 2
};

enum GUILD_RELATIONSHIP
{
	G_RELATIONSHIP_NONE = 0,
	G_RELATIONSHIP_UNION = 0x01,
	G_RELATIONSHIP_RIVAL = 0x02,
	G_RELATIONSHIP_UNIONMASTER = 0x04,
	G_RELATIONSHIP_RIVALMASTER = 0x08,

};

enum GUILD_TYPE
{
	G_TYPE_NONE = -1,
	G_TYPE_COMMON = 0,
	G_TYPE_GUARD = 1		// 수호 길드.
							//	G_TYPE_MERCENARY	= 1,
							//	G_TYPE_CLAN			= 2
};

enum GUILD_STATUS
{
	G_NONE = -1,
	G_PERSON = 0,		// 일반
	G_MASTER = 128,		// 길드마스터
	G_SUB_MASTER = 64,		// 부길드마스터
	G_BATTLE_MASTER = 32		// 배틀마스터
};

enum GUILD_REQ_COMMON_RESULT
{
	// 길드가 없음
	GUILD_ANS_NOTEXIST_GUILD = 0x10,
	// 공성전으로 인하여 연합기능이 제한됩니다.
	GUILD_ANS_UNIONFAIL_BY_CASTLE = 0x10,
	// 권한 없음
	GUILD_ANS_NOTEXIST_PERMISSION = 0x11,

	// 임명 할 수 있는 계급이 없음
	GUILD_ANS_NOTEXIST_EXTRA_STATUS = 0x12,
	// 임명 할 수 있는 타입이 없음
	GUILD_ANS_NOTEXIST_EXTRA_TYPE = 0x13,

	// 관계 유 & 무 
	GUILD_ANS_EXIST_RELATIONSHIP_UNION = 0x15,
	GUILD_ANS_EXIST_RELATIONSHIP_RIVAL = 0x16,

	// 연합 유 & 무
	GUILD_ANS_EXIST_UNION = 0x17,
	GUILD_ANS_EXIST_RIVAL = 0x18,
	GUILD_ANS_NOTEXIST_UNION = 0x19,
	GUILD_ANS_NOTEXIST_RIVAL = 0x1A,

	// 연합 마스터가 아님
	GUIDL_ANS_NOT_UNION_MASTER = 0x1B,

	// 적대 길드가 아님
	GUILD_ANS_NOT_GUILD_RIVAL = 0x1C,

	// 상대방이 연합 마스터 길드의 조건을 갖추지 못함.
	GUILD_ANS_CANNOT_BE_UNION_MASTER = 0x1D,

	// 최대 길드 연합 개수 초과 함
	GUILD_ANS_EXCEED_MAX_UNION_MEMBER = 0x1E,

	// 신청이 취소되었습니다.
	GUILD_ANS_CANCLE_REQUEST = 0x20

};

enum EXDB_DATA_TRANSFER_TYPE
{
	EX_SEND_P2P = 0x01,		// 요청 서버에만
	EX_SEND_BROADCASTING = 0x00			// 브로드캐스팅
};

enum EXDB_RESULT
{
	EX_RESULT_SUCCESS = 0x01,
	EX_RESULT_FAIL = 0x00,
	EX_RESULT_FAIL_FOR_CASTLE = 0x10,	// GUILD_ANS_UNIONFAIL_BY_CASTLE 와 같음.
};
#endif // ADD_NEW_GUILD_01_20040913

//////////////////////////////////////////////////////////////////////////
//
//	스탯 열매 관련 정보
//
//////////////////////////////////////////////////////////////////////////
#ifdef ADD_MINUS_STAT_SYSTEM_USING_FRUIT_20050712

enum FRUIT_ITEM_TYPE
{
	FRUIT_ENERGY = 0,
	FRUIT_VITALITY = 1,
	FRUIT_DEXTERITY = 2,
	FRUIT_STRENGTH = 3,
	FRUIT_LEADERSHIP = 4
};

enum STAT_FRUIT_USING_RESULT
{
	STAT_PLUS_SUCCESS = 0x00,	// 스탯생성 성공
	STAT_PLUS_FAILED = 0x01, // 스탯생성 실패
	STAT_PLUS_PREVENTED = 0x02,	// 열매를 Stat Plus에 사용 불가

	STAT_MINUS_SUCCESS = 0x03,	// 스탯감소 성공
	STAT_MINUS_FAILED = 0x04,	// 스탯감소 실패
	STAT_MINUS_PREVENTED = 0x05,	// 열매를 Stat Minus에 사용 불가

#ifdef MODIFY_RESET_FRUITS_RESULT_TYPE_20070821
	STAT_MINUS_EX_SUCCESS = 0x06,	// 리셋열매 결과 코드 성공
	STAT_MINUS_EX_FAILED = 0x07, // 리셋열매 결과 코드 실패
	STAT_MINUS_EX_PREVENTED = 0x08,	// 리셋열매 사용 불가
#endif // MODIFY_RESET_FRUITS_RESULT_TYPE_20070821

	STAT_FRUIT_USING_PREVENTED_BY_ITEMEQUIPMENT = 0x10,	// 아이템을 착용해서 사용불가능

	STAT_PLUS_PREVENTED_BY_MAX = 0x21,	// 생성 최대치까지 사용 했음
	STAT_MINUS_PREVENTED_BY_MAX = 0x25,	// 감소 최대치까지 사용 했음
	STAT_MINUS_PREVENTED_BY_DEFAULT = 0x26,	// 기본값 이하로는 감소 할 수 없음
};

#endif // ADD_MINUS_STAT_SYSTEM_USING_FRUIT_20050712

#ifdef ADD_MAPMOVE_PROTOCOL_20090327
enum MAP_MOVE_RESULT
{
	MAPMOVE_SUCCESS = 0,				// 이동 성공
	MAPMOVE_FAILED,										// 이동 실패 (이동 불가능한 다른 경우)
	MAPMOVE_FAILED_TELEPORT,							// 이동 실패 (텔레포트 중)
	MAPMOVE_FAILED_PSHOP_OPEN,							// 이동 실패 (개인상점이 열려있는 경우)
	MAPMOVE_FAILED_RECALLED,							// 이동 실패 (소환되는 도중)
	MAPMOVE_FAILED_NOT_ENOUGH_EQUIP,					// 이동 실패 (해당 맵으로 이동하기 위한 장비 부족)
	MAPMOVE_FAILED_WEARING_EQUIP,						// 이동 실패 (해당 맵에 입장시 장비하지 못하는 장비 착용)
	MAPMOVE_FAILED_MURDERER,							// 이동 실패 (살인마 일 경우 맵 이동 불가)
	MAPMOVE_FAILED_NOT_ENOUGH_LEVEL,					// 이동 실패 (레벨 부족)
	MAPMOVE_FAILED_NOT_ENOUGH_ZEN,						// 이동 실패 (소유 젠 부족)
	MAPMOVE_FAILED_EVENT_END,							// 이동 실패 (해당 맵의 이벤트가 이미 종료되었음)
	MAPMOVE_FAILED_HACKTOOL_BLOCK,						// 이동 실패 (핵툴 사용자로 맵 이동이 차단되었음)
	MAPMOVE_FAILED_CHECKSUM_ERROR,						// 이동 실패 (사용자가 보낸 체크섬 값이 맞지 않는다.)
	MAPMOVE_FORCED_EVENT_END = 20,				// 강제 이동 (이벤트 종료에 의한 강제 이동)
	MAPMOVE_FORCED_GM									// 강제 이동 (GM에 의한 강제 이동)
};

#endif // ADD_MAPMOVE_PROTOCOL_20090327

#endif

