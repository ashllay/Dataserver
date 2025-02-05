﻿#ifndef __SPRODEF_H__
#define __SPRODEF_H__

#define VER_CHATWINDOW_OPTION

//#define PROPERTY_ITEM_WORK		// 고유정보가 들어가 있는 아이템

// Server Header Protocol BYTE(Size)
typedef struct
{
	BYTE		c;
	BYTE		size;
	BYTE		headcode;
	BYTE		ServerCode;
	BYTE		Subcode;
} SHPB_HEAD, *LPSHPB_HEAD;

// Server Header Protocol WORD(Size)
typedef struct
{
	BYTE		c;
	BYTE		sizeH;
	BYTE		sizeL;
	BYTE		headcode;
	BYTE		ServerCode;
	BYTE		Subcode;
} SHPW_HEAD, *LPSHPW_HEAD;

//----------------------------------------------------------------------------
// 결과 공통
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE	Result;
} SDHP_DEFAULT_RESULT, *LPSDHP_DEFAULT_RESULT;


//----------------------------------------------------------------------------
// 결과를 보낼때 사용 
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		Result;
	DWORD		ItemCount;
} SDHP_RESULT, *LPSDHP_RESULT;

//----------------------------------------------------------------------------
// [0x00] 각각의 서버 정보를 보낼때 사용
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	BYTE			Type;		// 0:Join Server, 1:MapServer
	unsigned short	Port;	// Server Port Number
	char			ServerName[50];

#ifdef SERVERCODE_EXPAND
	WORD			ServerCode;
#else
	BYTE			ServerCode;
#endif
	char btGameServerType;
} SDHP_SERVERINFO, *LPSDHP_SERVERINFO;

//----------------------------------------------------------------------------
// [0x20] 게임서버의 정보를 데이터서버에 보내서 저장한다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	DWORD		ItemCount;
} SDHP_GAMESERVERINFO, *LPSDHP_GAMESERVERINFO;


//----------------------------------------------------------------------------
// 중앙서버에 인증된 계정정보를 보낸다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		ServerCode;
	BYTE		Subcode;

	int			Number;
	char		AccountID[MAX_IDSTRING + 1];// 계정 아이디

} SDHP_ACCOUNTINFO, *LPSDHP_ACCOUNTINFO;


//----------------------------------------------------------------------------
// [0x01] 게임서버가 계정 인증을 요청한다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	char		Id[MAX_IDSTRING];
#ifdef PW_KUZIMO
	char		Pass[MAX_IDSTRING];//[MAX_PASSWORD_LENGTH];
#else
	char		Pass[MAX_IDSTRING];
#endif
	short		Number;
	char		IpAddress[17];
} SDHP_IDPASS, *LPSDHP_IDPASS;

//----------------------------------------------------------------------------
// [0x01] 계정 인증 요청결과.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		result;

	short		Number;
	char		Id[MAX_IDSTRING];
	int			UserNumber;
	int			DBNumber;
	char		JoominNumber[13];	// 주민번호 뒷자리

#ifdef FOR_THAILAND
	char		AuthAdult;			// 성인 인증 코드
#endif

#ifdef ADD_PROTOCOL_PCBANG_GUID
	int			PcBangGuid;
#endif

#ifdef PCBANG_ADVANTAGE
	BYTE		bUserInPCBang;
#endif

#ifdef CHN_PLAYTIME_LIMIT_SYSTEM_20050818
#ifdef MODIFY_CHN_PLAYTIME_LIMIT_SYSTEM_01_20070509
	int			iVerifiedType;		// 성인 인증 여부 ( 0 : 성인, 1 : 미성년, 2 : 인증결과 없음(오류) )
#endif // MODIFY_CHN_PLAYTIME_LIMIT_SYSTEM_01_20070509
	INT			iAddPlayTime;		// 중국 피로드 - 게임시간 (5시간 지나면 게임혜택 0%)
	INT			iAddRestTime;		// 중국추가> . 중국 피로드 - 휴식시간
#endif

#ifdef VTM_PLAYTIME_LIMIT_SYSTEM_20060626
	INT			iAddPlayTime;
	INT			iAddRestTime;
#endif

} SDHP_IDPASSRESULT, *LPSDHP_IDPASSRESULT;


//----------------------------------------------------------------------------
// [0x02] 계정 인증 에러
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	short		Number;
	char		Id[MAX_IDSTRING + 1];
	int			UserNumber;
	int			DBNumber;
} SDHP_JOINFAIL, *LPSDHP_JOINFAIL;

//----------------------------------------------------------------------------
// [0x04] 사용자 블럭 시킨다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	short		Number;
	char		Id[MAX_IDSTRING + 1];
	int			UserNumber;
	int			DBNumber;
	BYTE		BlockCode;
} SDHP_COMMAND_BLOCK, *LPSDHP_COMMAND_BLOCK;


//----------------------------------------------------------------------------
// 인증서버 [0x06] 남은 시간 확인 요청
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	char		Id[MAX_IDSTRING];
	short		Number;
} SDHP_BILLSEARCH, *LPSDHP_SDHP_BILLSEARCH;

//----------------------------------------------------------------------------
// 인증서버 [0x06] 남은 시간 확인 요청 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	char		Id[MAX_IDSTRING];
	short		Number;

#ifdef UPDATE_UNIFICATIONBILL_20090203
	BYTE		btDeductType;
	char        EndsDays[12];

	DWORD		dwRestPoint;
	DWORD		dwRestTime;
#else	// UPDATE_UNIFICATIONBILL_20090203	
	BYTE		cCertifyType;
	BYTE		PayCode;
	char        EndsDays[12];
	int			EndTime;
#endif	// UPDATE_UNIFICATIONBILL_20090203
} SDHP_BILLSEARCH_RESULT, *LPSDHP_SDHP_BILLSEARCH_RESULT;


//0x07  시간 만료로 인해서 접속을 종료 시킨다.
typedef struct
{
	PBMSG_HEAD	h;

	char		Id[MAX_IDSTRING];
	short		Number;

} SDHP_BILLKILLUSER, *LPSDHP_BILLKILLUSER;


// 0x08 다른 사용자가 접속을 시도한다고 알려준다.
typedef struct
{
	PBMSG_HEAD  h;
	char    AccountID[MAX_IDSTRING];
} SDHP_OTHERJOINMSG, *LPSDHP_OTHERJOINMSG;

// 0x20
typedef struct
{
	PBMSG_HEAD  h;
	BYTE ExitCode[3];
} SDHP_EXITMSG, *LPSDHP_EXITMSG;


//----------------------------------------------------------------------------
// [0x51] 이벤트 ZEN아이테 생성을 알린다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		x;
	BYTE		y;
	BYTE		MapNumber;
} SDHP_LOVEHEARTCREATE, *LPSDHP_LOVEHEARTCREATE;

//----------------------------------------------------------------------------
// [0x51] 이벤트 ZEN아이테 생성을 알린다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
} SDHP_LOVEHEARTCREATERECV, *LPSDHP_LOVEHEARTCREATERECV;


//----------------------------------------------------------------------------
// DB 서버에 캐릭터 리스트를 달라고 요청
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	//int			UserNumber;	// 유저 절대 번호 
	char		Id[MAX_IDSTRING];
	short		Number;	// 게임 서버 유저번호
	int			IsUnityBattleFiledServer;//s12
} SDHP_GETCHARLIST, *LPSDHP_GETCHARLIST;

//----------------------------------------------------------------------------
// 캐릭터 리스트 카운트  (2바이트 크기를 사용)
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD h;
#ifdef _SEASON12
	short		Number;
#endif
	BYTE		Count;
	int			DbNumber;
	BYTE		GenerableClass;		// 마검사를 만들수 있는 계정인지..
	char		AccountId[MAX_IDSTRING + 1];
#ifdef CHARACTER_MOVE_20040810
	BYTE		MoveCnt;
#endif
	BYTE		CharacterSlotCount;
	BYTE		ExtendedWarehouseCount;
} SDHP_CHARLISTCOUNT, * LPSDHP_CHARLISTCOUNT;

//----------------------------------------------------------------------------
// [0x02] 계정 인증 요청시 캐릭터 정보(카운터 만큼 반복됨)
// [0xF3][0x00]
//----------------------------------------------------------------------------
typedef struct
{
	BYTE Index;
	char Name[MAX_IDSTRING];
	char UnityBFOfRealName[MAX_IDSTRING];
	WORD ServerCodeOfHomeWorld;
	WORD Level;
	BYTE Class;
	BYTE CtlCode;
	BYTE dbInventory[48];
	BYTE DbVersion;
	BYTE btGuildStatus;
	BYTE PK_Level;
	//BYTE Index;
	//char Name[MAX_IDSTRING];
	//char UnityBFOfRealName[MAX_IDSTRING];
	//WORD ServerCodeOfHomeWorld;
	//WORD Level;
	//BYTE Class;
	//BYTE CtlCode;
	////BYTE dbInventory[24];
	////BYTE dbInventory[36];
	//BYTE dbInventory[48]; // #define ITEM_DBSIZE_EXTEND_20050706
	//BYTE DbVersion;
	//BYTE btGuildStatus;	// 길드 관련 정보. 일단 Status 정보만 추가.
	//char PK_Level;
} SDHP_CHARLIST, *LPSDHP_CHARLIST;


//----------------------------------------------------------------------------
// [0x02] 유저 게임 종료 메시지
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	char CharName[MAX_IDSTRING];
	char GuildName[MAX_GUILDNAMESTRING];
#ifdef __FRIEND_WORK__
	BYTE Type;			// 0x00 : 길드&친구, 0x01 : 친구만
#endif

} SDHP_USERCLOSE, *LPSDHP_USERCLOSE;

/*
//----------------------------------------------------------------------------
// [0x03] 유저 게임 종료 메시지
//----------------------------------------------------------------------------
typedef struct
{
PBMSG_HEAD	h;
int  UserNumber;
int  DBNumber;
} SDHP_USERCLOSE, *LPSDHP_USERCLOSE;
*/
//----------------------------------------------------------------------------
// [0x04] 캐릭터 만들기 에 사용
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	int         UserNumber;
	int			DBNumber;
	short		Number;
	char        AccountId[MAX_IDSTRING];
	char		Name[MAX_IDSTRING];
	BYTE		ClassSkin;
} SDHP_CREATECHAR, *LPSDHP_CREATECHAR;

//----------------------------------------------------------------------------
// [0x04] 캐릭터 만들고 난 결과 보내는데 사용
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		Result;
	short		Number;
	char		AccountId[MAX_IDSTRING];
	char        Name[MAX_IDSTRING];
	BYTE		Pos;
	BYTE		ClassSkin;
	BYTE		Equipment[24];	// 착용하고 있는 장비
#ifdef DARKLORD_WORK
	WORD		Level;
#endif
} SDHP_CREATECHARRESULT, *LPSDHP_CREATECHARRESULT;

//----------------------------------------------------------------------------
// 0x05 게임서버가 캐릭터 삭제 요청
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short		Number;
	char		AccountID[MAX_IDSTRING];
	char		Name[MAX_IDSTRING];
	BYTE		Guild;
	char		GuildName[MAX_GUILDNAMESTRING];
} SDHP_CHARDELETE, *LPSDHP_CHARDELETE;

//----------------------------------------------------------------------------
// 0x05 캐릭터 삭제 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		Result;
	short		Number;
	char		AccountID[MAX_IDSTRING];

} SDHP_CHARDELETERESULT, *LPSDHP_CHARDELETERESULT;

//----------------------------------------------------------------------------
// 0x06 게임서버가 인증된 유저의 캐릭터 정보를 요청
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD  h;
	char    AccountID[MAX_IDSTRING + 1];
	char	Name[MAX_IDSTRING + 1];
	short	Number;
} SDHP_DBCHARINFOREQUEST, *LPSDHP_DBCHARINFOREQUEST;

//----------------------------------------------------------------------------
// [GS->JS] 0x16 캐릭터 선택 창으로 이동 시 인증서버로 MatchDB 갱신을 알린다.
//----------------------------------------------------------------------------
#ifdef MODIFY_UPDATE_MATCHDB_AT_CHARACTERLIST_VIEW_20060725
typedef struct
{
	PBMSG_HEAD	h;
	char		szId[MAX_IDSTRING];
	char		szName[MAX_IDSTRING];
	WORD		Level;					// 레벨
	BYTE		DbClass;				// 원래직업 정보

} SDHP_REQ_UPDATE_MATCHDB_USERCHARACTERS, *LPSDHP_REQ_UPDATE_MATCHDB_USERCHARACTERS;
#endif

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
// 0x06 캐릭터 정보 요청 결과 
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;

	BYTE  result;
	short Number;

	char  AccountID[MAX_IDSTRING];
	char  Name[MAX_IDSTRING + 1];	// 이름
	BYTE  Class;				// 직업
	short Level;				// 레벨
	int	  LevelUpPoint;			// 레벨업 포인트 
	int   Exp;					// 경험치
	int   NextExp;				// 다음 경험치
	int   Money;				// 돈
	WORD Str;					// 힘
	WORD Dex;					// 민첩성 
	WORD Vit;					// 건강
	WORD Energy;				// 에너지


	WORD  Life;					// 현재 생명
	WORD  MaxLife;				// 현재 최대 생명값
	WORD  Mana;					// 현재 마나
	WORD  MaxMana;				// 현재 최대 마나값

	BYTE  dbInventory[MAX_DBINVENTORY];	// 아이템 인벤토리
	BYTE  dbMagicList[MAX_DBMAGIC];		// 마법(스킬)리스트

	BYTE  MapNumber;			// 마지막 접종 했을때의 맵 번호
	BYTE  MapX;					// 마지막 접종 했을때의 X 좌표
	BYTE  MapY;					// 마지막 접종 했을때의 Y 좌표
	BYTE  Dir;
	int   PkCount;
	int   PkLevel;
	int   PkTime;
	BYTE  CtlCode;
	BYTE  DbVersion;
	BYTE  AccountCtlCode;

#ifdef NEW_SKILL_FORSKYLAND	
	BYTE  dbQuest[MAX_DBQUEST];
#endif

#ifdef DARKLORD_WORK
	WORD	Leadership;		// 통솔
	WORD	ChatLitmitTime;		// 통솔
#endif

#ifdef ADD_MINUS_STAT_SYSTEM_USING_FRUIT_20050712
	int		iFruitPoint;		// 열매 포인트
#endif
	BYTE btExtendedInvenCount;
	BYTE btExtendedWarehouseCount;
	int WareHouseMoney;
	DWORD dwRuudToken;
} SDHP_DBCHAR_INFORESULT, *LPSDHP_DBCHAR_INFORESULT;

//----------------------------------------------------------------------------
// 0x07 캐릭터 정보 저장 
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;

	//char  AccountID[MAX_IDSTRING+1];
	char  Name[MAX_IDSTRING + 1];	// 이름

	short Level;				// 레벨
	BYTE  Class;				// 직업
	int   LevelUpPoint;			// 레벨 업 포인트
	int   Exp;					// 경험치
	int   NextExp;				// 다음 경험치
	int   Money;				// 돈
	WORD Str;					// 힘
	WORD Dex;					// 민첩성 
	WORD Vit;					// 건강
	WORD Energy;				// 에너지

	WORD  Life;					// 현재 생명
	WORD  MaxLife;				// 현재 최대 생명값
	WORD  Mana;					// 현재 마나
	WORD  MaxMana;				// 현재 최대 마나값	

	BYTE  dbInventory[MAX_DBINVENTORY];	// 아이템 인벤토리
	BYTE  dbMagicList[MAX_DBMAGIC];		// 마법리스트

	BYTE  MapNumber;			// 마지막 접종 했을때의 맵 번호
	BYTE  MapX;					// 마지막 접종 했을때의 X 좌표
	BYTE  MapY;					// 마지막 접종 했을때의 Y 좌표
	BYTE  Dir;
	int   PkCount;
	int	  PkLevel;
	int	  PkTime;

	BYTE  dbQuest[MAX_DBQUEST];

#ifdef ITEMSAVE_MODIFY_FORSTATICS
	BYTE  CharInfoSave;			// 통계를 위해 DB저장 여부 변수
#endif

#ifdef DARKLORD_WORK
	WORD	Leadership;			// 통솔
	WORD	ChatLitmitTime;		// 채팅 제한 시간
#endif

#ifdef ADD_MINUS_STAT_SYSTEM_USING_FRUIT_20050712
	int		iFruitPoint;		// 열매 포인트
#endif

								//BYTE	AccountType;
								//INT64	DecreaseTime;

								//BYTE	CtlCode;
	char AccountId[MAX_IDSTRING + 1];
} SDHP_DBCHAR_INFOSAVE, *LPSDHP_DBCHAR_INFOSAVE;

// [0x08] 창고에 있는 아이템을 요청한다.
typedef struct
{
	PBMSG_HEAD	h;
	char		AccountID[MAX_IDSTRING];
	short		aIndex;
} SDHP_GETWAREHOUSEDB, *LPSDHP_GETWAREHOUSEDB;

// [0x08] 창고에 있는 아이템 리스트를 전송한다.
// [0x09] 창고에 아이템을 저장한다.
typedef struct
{
	PWMSG_HEAD	h;
	char		AccountID[MAX_IDSTRING];
	short		aIndex;
	int			Money;
	BYTE		dbItems[MAX_WAREHOUSEDBSIZE];
	BYTE		DbVersion;
	short		pw;
} SDHP_GETWAREHOUSEDB_SAVE, *LPSDHP_GETWAREHOUSEDB_SAVE;


// [0x10] 창고에 아직 아이템이 없다. 
typedef struct
{
	PBMSG_HEAD	h;
	char		AccountID[MAX_IDSTRING];
	short		aIndex;
} SDHP_GETWAREHOUSEDB_RESULT, *LPSDHP_GETWAREHOUSEDB_RESULT;


// [0x11] 캐릭터의 아이템을 저장한다.
typedef struct
{
	PWMSG_HEAD	h;

	char	Name[MAX_IDSTRING];	// 이름
	BYTE	dbInventory[MAX_DBINVENTORY];	// 아이템 인벤토리
	char	AccountID[MAX_IDSTRING];
} SDHP_DBCHAR_ITEMSAVE, *LPSDHP_DBCHAR_ITEMSAVE;

// [0x12] 창고에 돈을 저장한다.
typedef struct
{
	PBMSG_HEAD	h;
	char		AccountID[MAX_IDSTRING];
	short		aIndex;
	int			Money;
} SDHP_WAREHOUSEMONEY_SAVE, *LPSDHP_WAREHOUSEMONEY_SAVE;

#ifdef MODIFY_QUEST_SYSTEM_20070525	// DS <-> GS 프로토콜 선언
// GD [0x13]	퀘스트 완료요건 - 몬스터 킬수의 정보를 요청한다.
typedef struct
{
	PBMSG_HEAD		h;
	int				iUserIndex;
	char			szCharName[MAX_IDSTRING];
} SDHP_REQ_QUEST_MONSTER_KILL, *LPSDHP_REQ_QUEST_MONSTER_KILL;

// GD <-> DG [0x14]	퀘스트 완료요건 - 몬스터 킬수의 정보를 얻어온다.
typedef struct
{
	PBMSG_HEAD		h;
	int				iUserIndex;
	char			szCharName[MAX_IDSTRING];
	int				btQuestDBIndex;				// DB에 저장된 현재 퀘스트 인덱스
	int				iQuestMonIndex1;
	int				iKillCount1;
	int				iQuestMonIndex2;
	int				iKillCount2;
	int				iQuestMonIndex3;
	int				iKillCount3;
	int				iQuestMonIndex4;
	int				iKillCount4;
	int				iQuestMonIndex5;
	int				iKillCount5;
} SDHP_QUEST_MONSTER_KILL_INFO, *LPSDHP_QUEST_MONSTER_KILL_INFO;

#endif	// MODIFY_QUEST_SYSTEM_20070525
/*
//----------------------------------------------------------------------------
// [0x10] 게임서버에서 사용자 계정 생성 요청
//----------------------------------------------------------------------------
typedef struct
{
PBMSG_HEAD	h;
short	Number;
char	Id[MAX_IDSTRING];
char	Pass[MAX_IDSTRING];
char	Name[MAX_IDSTRING];
char	JoominN[MAX_JOOMINNUMBERSTR];
char	Question[MAX_QUESTIONSTR];
char	Answer[MAX_ANSWERSTR];
char	PhoneN[MAX_PHONENUMBERSTR];
char	Email[MAX_EMAILSTR];
char    IpAddress[17];
} SDHP_ACCOUNTREQUEST, *LPSDHP_ACCOUNTREQUEST;

//----------------------------------------------------------------------------
// [0x10] 게임서버에서 사용자 계정 생성 결과
//----------------------------------------------------------------------------
typedef struct
{
PBMSG_HEAD	h;
BYTE		result;
short		Number;
} SDHP_ACCOUNTRESULT, *LPSDHP_ACCOUNTRESULT;
*/

//----------------------------------------------------------------------------
// [0x20] 특정아이디의 비번질문을 얻고자 요청한다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short	Number;
	char	Id[MAX_IDSTRING];
} SDHP_PASSQUESTION_QUERY, *LPSDHP_PASSQUESTION_QUERY;

//----------------------------------------------------------------------------
// [0x20] 특정아이디의 비번질문을 얻고자 요청한다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short	Number;
	BYTE	Result;
	char	Question[MAX_QUESTIONSTR];
} SDHP_PASSQUESTION_QUERY_RESULT, *LPSDHP_PASSQUESTION_QUERY_RESULT;


//----------------------------------------------------------------------------
// [0x21] 비밀번호 문의
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short	Number;
	char	Id[MAX_IDSTRING];
	char	JoominN[MAX_JOOMINNUMBERSTR];
	char	Answer[MAX_ANSWERSTR];
	char    IpAddress[17];
} SDHP_PASSQUERY, *LPSDHP_PASSQUERY;

//----------------------------------------------------------------------------
// [0x21] 비밀번호 문의 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short	Number;
	BYTE	Result;
	char	Password[MAX_IDSTRING];
} SDHP_PASSQUERY_RESULT, *LPSDHP_PASSQUERY_RESULT;


//----------------------------------------------------------------------------
// [0x22] 비밀번호 변경신청
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short	Number;
	char	Id[MAX_IDSTRING];
	char	PassOld[MAX_IDSTRING];
	char	PassNew[MAX_IDSTRING];
	char	JoominN[MAX_JOOMINNUMBERSTR];
	char	IpAddress[17];
} SDHP_PASSCHANGE, *LPSDHP_PASSCHANGE;


//----------------------------------------------------------------------------
// [0x22] 비밀번호 변경신청 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short	Number;
	BYTE	Result;
} SDHP_PASSCHANGE_RESULT, *LPSDHP_PASSCHANGE_RESULT;


//----------------------------------------------------------------------------
// [0x2D] 고유 아이템 정보를 요청한다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	WORD		wIndex;
	DWORD		dwItemSerial;
	WORD		wItemIndex;
} SDHP_LOAD_MEDALINFO, *LPSDHP_LOAD_MEDALINFO;

//----------------------------------------------------------------------------
// [0x2D] 고유 아이템 정보 요청 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	WORD		wIndex;
	DWORD		dwItemSerial;

	DWORD		dwTime;
	WORD		wRemainTime;
	WORD		wLevel;
	WORD		wLevel_T;
	char		szName[MAX_IDSTRING];
	char		szName_T[MAX_IDSTRING];
	BYTE		btClass;
	BYTE		btClass_T;

	WORD		wItemIndex;

} SDHP_LOAD_MEDALINFO_RESULT, *LPSDHP_LOAD_MEDALINFO_RESULT;




//----------------------------------------------------------------------------
// [0x30] 길드를 생성한다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	char		GuildName[MAX_GUILDNAMESTRING + 1];
	char		Master[MAX_IDSTRING + 1];
	BYTE		Mark[32];
	BYTE		NumberH;
	BYTE		NumberL;

#if defined( ADD_NEW_GUILD_02_20040922 ) || GAME_VERSION >= G_V_99B
	BYTE		btGuildType;

#endif

} SDHP_GUILDCREATE, *LPSDHP_GUILDCREATE;

//----------------------------------------------------------------------------
// 길드 생성 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	BYTE		Result;
	BYTE		Flag;

	DWORD		GuildNumber;

	BYTE		NumberH;
	BYTE		NumberL;
	char		Master[MAX_IDSTRING + 1];
	char		GuildName[MAX_GUILDNAMESTRING + 1];
	BYTE		Mark[32];

#if defined( ADD_NEW_GUILD_02_20040922 ) || GAME_VERSION >= G_V_99B
	BYTE		btGuildType;

#endif

} SDHP_GUILDCREATE_RESULT, *LPSDHP_GUILDCREATE_RESULT;

//----------------------------------------------------------------------------
// [0x31] 길드 삭제
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	BYTE		NumberH;
	BYTE		NumberL;

	char		GuildName[MAX_GUILDNAMESTRING];
	char		Master[MAX_IDSTRING];
} SDHP_GUILDDESTROY, *LPSDHP_GUILDDESTROY;

//----------------------------------------------------------------------------
// [0x31] 길드 삭제 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	BYTE		Result;
	BYTE		Flag;

	BYTE		NumberH;
	BYTE		NumberL;

	char		GuildName[MAX_GUILDNAMESTRING + 1];
	char		Master[MAX_IDSTRING + 1];
} SDHP_GUILDDESTROY_RESULT, *LPSDHP_GUILDDESTROY_RESULT;

//----------------------------------------------------------------------------
// [0x32] 길드 멤버 추가
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	char		GuildName[MAX_GUILDNAMESTRING + 1];
	char		MemberID[MAX_IDSTRING + 1];
	BYTE		NumberH;
	BYTE		NumberL;
} SDHP_GUILDMEMBERADD, *LPSDHP_GUILDMEMBERADD;

//----------------------------------------------------------------------------
// [0x32] 길드 멤버 추가 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	BYTE		Result;
	BYTE		Flag;

	BYTE		NumberH;
	BYTE		NumberL;

	char		GuildName[MAX_GUILDNAMESTRING + 1];
	char		MemberID[MAX_IDSTRING + 1];

#ifdef SERVERCODE_EXPAND
	short		pServer;	// 접속해 있는 서버
#else
	BYTE		pServer;	// 접속해 있는 서버
#endif

} SDHP_GUILDMEMBERADD_RESULT, *LPSDHP_GUILDMEMBERADD_RESULT;

//----------------------------------------------------------------------------
// [0x33] 길드멤버 삭제 
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	BYTE		NumberH;
	BYTE		NumberL;

	char		GuildName[MAX_GUILDNAMESTRING];
	char		MemberID[MAX_IDSTRING];
} SDHP_GUILDMEMBERDEL, *LPSDHP_GUILDMEMBERDEL;

//----------------------------------------------------------------------------
// [0x33] 길드멤버 삭제 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	BYTE		Result;
	BYTE		Flag;

	BYTE		NumberH;
	BYTE		NumberL;

	char		GuildName[MAX_GUILDNAMESTRING + 1];
	char		MemberID[MAX_IDSTRING + 1];

} SDHP_GUILDMEMBERDEL_RESULT, *LPSDHP_GUILDMEMBERDEL_RESULT;


//----------------------------------------------------------------------------
// [0x34] 길드 정보 변경 
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	char		GuildName[MAX_GUILDNAMESTRING + 1];
	char		Master[MAX_IDSTRING + 1];
	BYTE		Mark[32];
	int			Score;
	BYTE		Count;
} SDHP_GUILDUPDATE, *LPSDHP_GUILDUPDATE;


//----------------------------------------------------------------------------
// [0x35] 길드 정보를 요청한다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	BYTE		NumberH;
	BYTE		NumberL;

	char		MemberID[MAX_IDSTRING];
} SDHP_GUILDMEMBER_INFO_REQUEST, *LPSDHP_GUILDMEMBER_INFO_REQUEST;

//----------------------------------------------------------------------------
// [0x35] 캐릭터가 게임에 접속시 길드 정보를 보낸다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	char		GuildName[MAX_GUILDNAMESTRING + 1];
	char		MemberID[MAX_IDSTRING + 1];

#if defined( ADD_NEW_GUILD_01_20040913 ) || GAME_VERSION >= G_V_99B
	BYTE		btGuildStatus;
#endif

#if defined( ADD_NEW_GUILD_02_20040922 ) || GAME_VERSION >= G_V_99B
	BYTE		btGuildType;
#endif

#ifdef SERVERCODE_EXPAND
	short		pServer;
#else
	char		pServer;
#endif

} SDHP_GUILDMEMBER_INFO, *LPSDHP_GUILDMEMBER_INFO;


//----------------------------------------------------------------------------
// [0x36] 길드마스터가 접속했을 때 길드원 정보를 재전송한다.
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;

#ifdef GUILD_REWORK

#ifdef MODIFY_GUILD_VIEWPORT_03_20040913
	INT			Number;
#else	// #ifdef MODIFY_GUILD_VIEWPORT_03_20040913
	WORD		Number;
#endif	// #ifdef MODIFY_GUILD_VIEWPORT_03_20040913

	char		GuildName[MAX_GUILDNAMESTRING + 1];
	char		Master[MAX_IDSTRING + 1];
	BYTE		Mark[32];
	int			score;
#else 
	char		GuildName[MAX_GUILDNAMESTRING + 1];
#endif

#if defined( ADD_NEW_GUILD_02_20040922 ) || GAME_VERSION >= G_V_99B
	BYTE		btGuildType;	// 길드 타입 ( 0: 일반  1: 수호길드 )
#endif

#if defined( ADD_NEW_UNION_01_20041006 ) || GAME_VERSION >= G_V_99B
	INT			iGuildUnion;	// UnionMaster Guild 번호
	INT			iGuildRival;	// Rival Guild 번호

	CHAR		szGuildRivalName[MAX_GUILDNAMESTRING + 1];	// 라이벌 길드 이름.
#endif

	BYTE		Count;
} SDHP_GUILDALL_COUNT, *LPSDHP_GUILDALL_COUNT;

//----------------------------------------------------------------------------
// [0x36] 길드마스터가 접속했을 때 길드원 정보를 재전송한다.
//----------------------------------------------------------------------------
typedef struct
{
	char		MemberID[MAX_IDSTRING + 1];

#if defined( ADD_NEW_GUILD_01_20040913 ) || GAME_VERSION >= G_V_99B
	BYTE		btGuildStatus;	// 길드에서 직책 및 상태
#endif

#ifdef SERVERCODE_EXPAND
	short		pServer;
#else
	BYTE		pServer;
#endif
} SDHP_GUILDALL, *LPSDHP_GUILDALL;

//----------------------------------------------------------------------------
// [0x37] 길드 스코어 업데이트 
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	char		GuildName[MAX_GUILDNAMESTRING + 1];
	int			Score;
} SDHP_GUILDSCOREUPDATE, *LPSDHP_GUILDSCOREUPDATE;

//----------------------------------------------------------------------------
// [0x38] 길드 공지 저장
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	char GuildName[MAX_GUILDNAMESTRING + 1];
	char szGuildNotice[MAX_GUILDNOTICE];
} SDHP_GUILDNOTICE, *LPSDHP_GUILDNOTICE;


//----------------------------------------------------------------------------
// [0x40] 길드 리스트를 요청한다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
} SDHP_GUILDLISTREQUEST, *LPSDHP_GUILDLISTREQUEST;

//----------------------------------------------------------------------------
// [0x40] 길드를 생성한다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	WORD		Number;
	char		GuildName[MAX_GUILDNAMESTRING + 1];
	char		Master[MAX_IDSTRING + 1];
	BYTE		Mark[32];
	int			score;
} SDHP_GUILDCREATED, *LPSDHP_GUILDCREATED;

//----------------------------------------------------------------------------
// [0x41] 길드리스트를 모두다 보냈다.
// State : 
//      0x00 = 길드 리스트 보내기 시작 
//      0x01 = 길드 리스트 모두 다 받았다
// Count : 길드 리스트 개수
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		State;
	int			Count;
} SDHP_GUILDLISTSTATE, *LPSDHP_GUILDLISTSTATE;

//----------------------------------------------------------------------------
// [0x50] 이벤트 ZEN을 저장한다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	char		AccountID[MAX_IDSTRING];
	char		Name[MAX_IDSTRING];
	int			Total;
	int			Number;
} SDHP_ZENSAVE, *LPSDHP_ZENSAVE;

//----------------------------------------------------------------------------
// [0x50] 이벤트 ZEN을 읽어온다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	char		AccountID[MAX_IDSTRING];
	int			Total;
	int			Number;
} SDHP_ZENLOAD, *LPSDHP_ZENLOAD;

//----------------------------------------------------------------------------
// [0x52] 아이템 번호를 부여받는다.
//----------------------------------------------------------------------------
// MapNumber 가 255 일때는 카오스 박스이다.
typedef struct
{
	PBMSG_HEAD h; // C1:52/55 GS->DS
	BYTE x;
	BYTE y;
	WORD MapNumber;
	short Type;
	BYTE Level;
	BYTE Dur;
	BYTE Op1;
	BYTE Op2;
	BYTE Op3;
	BYTE NewOption;
	int	aIndex;
	short lootindex;
	BYTE SetOption;
	BYTE SocketSlotCount;
	long lDuration;
	DWORD dwEventIndex;
	BYTE SocketOption[5];
	BYTE MainAttribute;
} SDHP_ITEMCREATE, *LPSDHP_ITEMCREATE;

//----------------------------------------------------------------------------
// [0x52] 아이템 번호를 부여받는다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD h; // C1:52 DS->GS
	BYTE x;
	BYTE y;
	WORD MapNumber;
	DWORD m_Number;
	short Type;
	BYTE Level;
	BYTE Dur;
	BYTE Op1;
	BYTE Op2;
	BYTE Op3;
	BYTE NewOption;
	int aIndex;
	short lootindex;
	BYTE SetOption;
	BYTE SocketSlotCount;
	long lDuration;
	DWORD dwEventIndex;
	BYTE SocketOption[5];
	BYTE MainAttribute;
	BYTE TargetInvenPos;//s12_1
} SDHP_ITEMCREATERECV, *LPSDHP_ITEMCREATERECV;


//----------------------------------------------------------------------------
// [0x53] 아이템 이동 경로를 저장한다.
//----------------------------------------------------------------------------
typedef struct
{

	PBMSG_HEAD	h;
	DWORD		Serial;
	char		ServerName[20];
	char		Account[MAX_IDSTRING];
	char		Name[MAX_IDSTRING];
	char		ItemName[21];
	BYTE		X;
	BYTE		Y;
	BYTE		ItemLevel;
	BYTE		ItemOp1;
	BYTE		ItemOp2;
	BYTE		ItemOp3;

} SDHP_ITEMMOVESAVE, *LPSDHP_ITEMMOVESAVE;


//----------------------------------------------------------------------------
// [0x54] 고유 아이템 번호를 부여받는다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		x;
	BYTE		y;
	BYTE		MapNumber;
	short		Type;
	BYTE		Level;
	BYTE		Dur;
	BYTE		Op1;
	BYTE		Op2;
	BYTE		Op3;
	BYTE		NewOption;
	int			aIndex;
	short		lootindex;
	BYTE		SetOption;

	DWORD		dwTime;
	WORD		wRemainTime;
	WORD		wLevel;
	WORD		wLevel_T;
	char		szName[MAX_IDSTRING];
	char		szName_T[MAX_IDSTRING];
	BYTE		btClass;
	BYTE		btClass_T;

	WORD		wItemIndex;

} SDHP_PROPERTY_ITEMCREATE, *LPSDHP_PROPERTY_ITEMCREATE;


//----------------------------------------------------------------------------
// [0x54] 고유 아이템 번호를 부여받는다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		x;
	BYTE		y;
	BYTE		MapNumber;
	DWORD		m_Number;
	short		Type;
	BYTE		Level;
	BYTE		Dur;
	BYTE		Op1;
	BYTE		Op2;
	BYTE		Op3;
	BYTE		NewOption;
	int			aIndex;
	short		lootindex;
	BYTE		SetOption;

	DWORD		dwTime;
	WORD		wRemainTime;
	WORD		wLevel;
	WORD		wLevel_T;
	char		szName[MAX_IDSTRING];
	char		szName_T[MAX_IDSTRING];
	BYTE		btClass;
	BYTE		btClass_T;

	WORD		wItemIndex;

} SDHP_PROPERTY_ITEMRECV, *LPSDHP_PROPERTY_ITEMRECV;


#ifdef DARKLORD_WORK

//----------------------------------------------------------------------------
// [0x55] 펫 아이템 시리얼 번호를 부여받는다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		x;
	BYTE		y;
	BYTE		MapNumber;
	short		Type;
	BYTE		Level;
	BYTE		Dur;
	BYTE		Op1;
	BYTE		Op2;
	BYTE		Op3;
	BYTE		NewOption;
	int			aIndex;
	short		lootindex;
	BYTE		SetOption;

} SDHP_PET_ITEMCREATE, *LPSDHP_PET_ITEMCREATE;

//----------------------------------------------------------------------------
// [0x55] 아이템 번호를 부여받는다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		x;
	BYTE		y;
	BYTE		MapNumber;
	DWORD		m_Number;
	short		Type;
	BYTE		Level;
	BYTE		Dur;
	BYTE		Op1;
	BYTE		Op2;
	BYTE		Op3;
	BYTE		NewOption;
	int			aIndex;
	short		lootindex;
	BYTE		SetOption;

} SDHP_PET_ITEMCREATERECV, *LPSDHP_PET_ITEMCREATERECV;


/////////////////////////////////////////////////
// GS->DS 0x56	펫 아이템 정보를 달라고 한다
typedef struct
{
	BYTE 	nPos;		// 아이템 위치...n
#ifdef MODIFY_ITEM_SERIAL_EXPAND_20080227
	DWORD	nSerial;	// 아이템 시리얼...n
#else
	int		nSerial;	// 아이템 시리얼...n
#endif // MODIFY_ITEM_SERIAL_EXPAND_20080227
}Request_PetItem_Info, *LPRequest_PetItem_Info;

typedef struct
{
	PWMSG_HEAD	h;
	char	AccountID[MAX_IDSTRING + 1];// 계정 아이디
	WORD	Number;
	BYTE	InvenType;	// 0:인벤, 1:창고
	BYTE 	nCount;		// 아이템수 

						//BYTE 	nPos;		// 아이템 위치...n
						//int   nSerial;	// 아이템 시리얼...n
	WORD ServerType;
	WORD ServerCode;
}SDHP_REQUEST_PETITEM_INFO, *LPSDHP_REQUEST_PETITEM_INFO;

///////////////////////////////////////////////////
// DS->GS 0x56 펫 아이템 정보를 준다
typedef struct
{
	BYTE 	nPos;			// 아이템 위치...n
#ifdef MODIFY_ITEM_SERIAL_EXPAND_20080227
	DWORD   nSerial;		// 아이템 시리얼
#else
	int     nSerial;		// 아이템 시리얼
#endif // MODIFY_ITEM_SERIAL_EXPAND_20080227
	BYTE	Level;			// 아이템 레벨
	__int64		Exp;			// 아이템 경험치
}Recv_PetItem_Info, *LPRecv_PetItem_Info;

typedef struct
{
	PWMSG_HEAD	h;

	char		AccountID[MAX_IDSTRING + 1];// 계정 아이디
	WORD		Number;
	BYTE		InvenType;		// 0:인벤, 1:창고
	BYTE 		nCount;			// 아이템수

								//BYTE 		nPos;			// 아이템 위치
								//int     	nSerial;		// 아이템 시리얼
								//short		Level;			// 아이템 레벨
								//int		Exp;			// 아이템 경험치
	BYTE ServerType;
	BYTE ServerCode;
}SDHP_RECV_PETITEM_INFO, *LPSDHP_RECV_PETITEM_INFO;


///////////////////////////////////////////////////
// GS->GS	0x57	펫 아이템 정보를 저장하라고 한다
typedef struct
{
#ifdef MODIFY_ITEM_SERIAL_EXPAND_20080227
	DWORD   nSerial;		// 아이템 시리얼
#else
	int     nSerial;		// 아이템 시리얼
#endif // MODIFY_ITEM_SERIAL_EXPAND_20080227
	BYTE	Level;			// 아이템 레벨
	__int64		Exp;			// 아이템 경험치
}Save_PetItem_Info, *LPSave_PetItem_Info;

typedef struct
{
	PWMSG_HEAD	h;

	BYTE 		nCount;		// 아이템수

							//int    		nSerial;	// 아이템 시리얼
							//int			Exp;		// 아이템 경험
							//short		Level;		// 아이템 레벨
	BYTE ServerType;
	BYTE ServerCode;
}SDHP_SAVE_PETITEM_INFO, *LPSDHP_SAVE_PETITEM_INFO;
#endif

#ifdef GS_DS_LIVECHECK_20041008

//----------------------------------------------------------------------------
// [0x58] GS -> DS : 지속적인 LIVE 신호를 보낸다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	INT			g_iGsCode;
} SDHP_REQ_GSLIVECHECK, *LPSDHP_REQ_GSLIVECHECK;


//----------------------------------------------------------------------------
// [0x58] DS -> GS : LIVE 신호에 대한 결과를 보낸다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	INT			g_iGsCode;
} SDHP_ANS_GSLIVECHECK, *LPSDHP_ANS_GSLIVECHECK;

#endif


#ifdef CHINA_HACKUSER_KICK_SYSTEM
//----------------------------------------------------------------------------
// [0x70] GS -> DS : 핵사용 유저 블럭 요청
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	WORD		UserIndex;
	char		AccountID[MAX_IDSTRING];
	char		Name[MAX_IDSTRING];
}SDHP_REQ_HACKUSERBLOCK, *LPSDHP_REQ_HACKUSERBLOCK;

//----------------------------------------------------------------------------
// [0x70] DS -> GS : 핵사용 유저 블럭 요청 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	WORD		UserIndex;
	char		AccountID[MAX_IDSTRING];
	char		Name[MAX_IDSTRING];
	BYTE		Result;				// 결과값( 0 : 성공 , 이외의 값 실패)
	BYTE		WarnLevel;			// 경고 레벨 (1,2)
}SDHP_HACKUSERBLOCK_RESULT, *LPSDHP_HACKUSERBLOCK_RESULT;
#endif

//----------------------------------------------------------------------------
// [0x60] 옵션 키 값을 받는다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	char		Name[MAX_IDSTRING];
#ifdef UPDATE_SKILLKEY_EXPAND_20080804
	BYTE		SkillKeyBuffer[20];
#else	// UPDATE_SKILLKEY_EXPAND_20080804
	BYTE		SkillKeyBuffer[10];
#endif	// UPDATE_SKILLKEY_EXPAND_20080804
	BYTE		GameOption;
	BYTE		QkeyDefine;
	BYTE		WkeyDefine;
	BYTE		EkeyDefine;
#ifdef VER_CHATWINDOW_OPTION
	BYTE		ChatWindow;
#endif

#ifdef ADD_SEASON_3_NEW_UI_20071122
	BYTE		RkeyDefine;
#endif 	

#ifdef UPDATE_OPTIONKEY_LEVEL_20080116
	int			QWERLevel;	// 클라이언트는 BYTE QWERLevel[4] 사용
#endif
	BYTE EnableTransfromMode;
	short PlayGuideLv;
	BYTE PlayGuideCheck;
} SDHP_SKILLKEYDATA, *LPSDHP_SKILLKEYDATA;

typedef struct
{
	PBMSG_HEAD h;	// C1:17
	int iUserIndex;	// 4
	char chAccountID[MAX_IDSTRING + 1];	//
	char chCharacterName[MAX_IDSTRING + 1];	//
}PMSG_CHARACTER_RESET, *LPPMSG_CHARACTER_RESET;

typedef struct
{
	PBMSG_HEAD h;	// C1:17
	int iUserIndex;	// 4
	int ResetNumber;	//
}PMSG_ANS_CHARACTER_RESET, *LPPMSG_ANS_CHARACTER_RESET;

typedef struct
{
	PBMSG_HEAD h;	// C1:17
	int iUserIndex;	// 4
	char chAccountID[MAX_IDSTRING + 1];	//
	char chCharacterName[MAX_IDSTRING + 1];	//

	int m_iRuleIndex; //
	BOOL m_bClearStat;	//
	int m_iLevelAfterReset;	//
	int m_iLevelUpPoint; //
	BOOL m_bReqSpecialItem; //
	BOOL m_bBornPlace; //
	int m_iResetNumber; //
	BOOL m_bClearBuffState; //
	BOOL m_bClearMagicList; //
}PMSG_REQ_SAVE_CHARACTER_RESET, *LPPMSG_REQ_SAVE_CHARACTER_RESET;

typedef struct
{
	PBMSG_HEAD h;	// C1:17
	int iUserIndex;	// 4

	int m_iRuleIndex; //
	BOOL m_bClearStat;	//
	int m_iLevelAfterReset;	//
	int m_iLevelUpPoint; //
	BOOL m_bReqSpecialItem; //
	BOOL m_bBornPlace; //
	int m_iResetNumber; //
	BOOL m_bClearBuffState; //
	BOOL m_bClearMagicList; //
}PMSG_ANS_SAVE_CHARACTER_RESET, *LPPMSG_ANS_SAVE_CHARACTER_RESET;

typedef struct
{
	PBMSG_HEAD h;	// C1:17
	char chAccountID[MAX_IDSTRING + 1];
	int iUserIndex;
	BYTE AccountType;
	INT64 EndTime;
}PMSG_REQ_VIP, *LPPMSG_REQ_VIP;

typedef struct
{
	PBMSG_HEAD h;	// C1:17
	int iUserIndex;
	BYTE AccountType;
	INT64 EndTime;
}PMSG_ANS_VIP, *LPPMSG_ANS_VIP;

//----------------------------------------------------------------------------
// [0x60] 옵션 키 값을 받는다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	int			aIndex;
	char		Name[MAX_IDSTRING];
#ifdef UPDATE_SKILLKEY_EXPAND_20080804
	BYTE		SkillKeyBuffer[20];
#else	// UPDATE_SKILLKEY_EXPAND_20080804
	BYTE		SkillKeyBuffer[10];
#endif	// UPDATE_SKILLKEY_EXPAND_20080804
	BYTE		GameOption;
	BYTE		QkeyDefine;
	BYTE		WkeyDefine;
	BYTE		EkeyDefine;

#ifdef VER_CHATWINDOW_OPTION
	BYTE		ChatWindow;
#endif

#ifdef ADD_SEASON_3_NEW_UI_20071122
	BYTE		RkeyDefine;
#endif 

#ifdef UPDATE_OPTIONKEY_LEVEL_20080116
	int			QWERLevel;	// 클라이언트는 BYTE QWERLevel[4] 사용
#endif
	BYTE EnableTransfromMode;
	short PlayGuideLv;
	BYTE PlayGuideCheck;
} SDHP_SKILLKEYDATA_SEND, *LPSDHP_SKILLKEYDATA_SEND;


//----------------------------------------------------------------------------
// [0x60] 이벤트 시작을 알린다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		Event;
} SDHP_EVENTSTART, *LPSDHP_EVENTSTART;


//----------------------------------------------------------------------------
// [0x61] 인증서버에서 이벤트 시작 또는 종료를 알린다
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		Event;			// 이벤트 번호
	BYTE		Stat;			// 상태 0 : 종료 1 : 시작
} SDHP_EVENTCONTROL, *LPSDHP_EVENTCONTROL;


//----------------------------------------------------------------------------
// [0x62] 인증서버에서 Reload 설정을 알린다
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		Option;			// 옵션 번호
} SDHP_OPTIONCONTROL, *LPSDHP_OPTIONCONTROL;

// 0x30
typedef struct
{
	PBMSG_HEAD	h;
	char		Account[MAX_IDSTRING];
	char		Name[MAX_IDSTRING];
} SDHP_LOVEHEARTEVENT, *LPSDHP_LOVEHEARTEVENT;

// 0x30
typedef struct
{
	PBMSG_HEAD	h;

	BYTE		Result;

	char		Name[MAX_IDSTRING];
	int			Number;

} SDHP_LOVEHEARTEVENT_RESULT, *LPSDHP_LOVEHEARTEVENT_RESULT;

// 0x40 전체 공지
typedef struct
{
	PBMSG_HEAD	h;
	char		Notice[MAX_CHAT + 1];
} SDHP_NOTICE, *LPSDHP_NOTICE;

// 0x41 유저 공지
typedef struct
{
	PBMSG_HEAD	h;
	char		szId[MAX_IDSTRING];
	char		Notice[MAX_CHAT + 1];
} SDHP_USER_NOTICE, *LPSDHP_USER_NOTICE;


// 0x42 게임 블럭
typedef struct
{
	PBMSG_HEAD	h;
	int		ClientIndex;
	char	AccountID[MAX_IDSTRING];
	BYTE	ServerNum;
	char	CharName[MAX_IDSTRING];
	BYTE	Type;
} SDHP_GAME_BLOCK, *LPSDHP_GAME_BLOCK;

// 0x42 게임 블럭 결과
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		Result;
} SDHP_GAME_BLOCK_RESULT, *LPSDHP_GAME_BLOCK_RESULT;


// 0xCF 캐릭터 이동
typedef struct
{
	PBMSG_HEAD	h;
	char		Account[MAX_IDSTRING];
	short		Number;
} SDHP_CHARACTER_TRANSFER, *LPSDHP_CHARACTER_TRANSFER;

typedef struct
{
	PBMSG_HEAD	h;
	char		Account[MAX_IDSTRING];
	short		Number;
	BYTE		Result;
} SDHP_CHARACTER_TRANSFER_RESULT, *LPSDHP_CHARACTER_TRANSFER_RESULT;

#ifdef UPDATE_CHANGE_CHARACTERNAME_20080410 // 캐릭명 변경 프로토콜
//----------------------------------------------------------------------------
// GD[0x16] 캐릭터 변경을 요청.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	int			aIndex;
	char		AccountId[MAX_IDSTRING];
	char		OldName[MAX_IDSTRING];
	char		NewName[MAX_IDSTRING];
} SDHP_CHANGE_NAME, *LPSDHP_CHANGE_NAME;

//----------------------------------------------------------------------------
// DG[0x16] 캐릭터 변경을 요청 결과.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	int			aIndex;
	char		AccountId[MAX_IDSTRING];
	char		OldName[MAX_IDSTRING];
	char		NewName[MAX_IDSTRING];
	BYTE		btResult;		// 0: 성공, 1: 동일 캐릭터명 존재
} SDHP_CHANGE_NAME_RESULT, *LPSDHP_CHANGE_NAME_RESULT;
#endif	// UPDATE_CHANGE_CHARACTERNAME_20080410

//##__FRIEND_WORK__
#ifdef __FRIEND_WORK__

//----------------------------------------------------------------------------
// GD[0x60] 친구 리스트를 요청한다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short		Number;
	char		Name[MAX_IDSTRING];
	BYTE		pServer;
} FHP_FRIENDLIST_REQ, *LPFHP_FRIENDLIST_REQ;

//----------------------------------------------------------------------------
// DG[0x60] 친구 리스트를 요청에 대한 결과
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;
	short		Number;
	char		Name[MAX_IDSTRING];
	BYTE		Count;
	BYTE		MailCount;
} FHP_FRIENDLIST_COUNT, *LPFHP_FRIENDLIST_COUNT;

//----------------------------------------------------------------------------
// DG[0x60] 친구 리스트를 요청에 대한 결과
//----------------------------------------------------------------------------
typedef struct
{
	char		Name[MAX_IDSTRING];
	BYTE		Server;
} FHP_FRIENDLIST, *LPFHP_FRIENDLIST;

//----------------------------------------------------------------------------
// GD[0x61] 대기중인 친구 리스트를 요청한다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short		Number;
	char		Name[MAX_IDSTRING];
} FHP_WAITFRIENDLIST_REQ, *LPFHP_WAITFRIENDLIST_REQ;

//----------------------------------------------------------------------------
// DG[0x61] 대기중인 친구 리스트를 요청 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short		Number;
	char		Name[MAX_IDSTRING];
	char		FriendName[MAX_IDSTRING];
} FHP_WAITFRIENDLIST_COUNT, *LPFHP_WAITFRIENDLIST_COUNT;

//----------------------------------------------------------------------------
// GD[0x62] 상태를 알린다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short		Number;
	char		Name[MAX_IDSTRING];
	BYTE		State;
} FHP_FRIEND_STATE_C, *LPFHP_FRIEND_STATE_C;

//----------------------------------------------------------------------------
// DG[0x62] 상태를 알린다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short		Number;
	char		Name[MAX_IDSTRING];
	char		FriendName[MAX_IDSTRING];
	BYTE		State;
} FHP_FRIEND_STATE, *LPFHP_FRIEND_STATE;

//----------------------------------------------------------------------------
// GD[0x63] 친구 추가 요청
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short		Number;
	char		Name[MAX_IDSTRING];
	char		FriendName[MAX_IDSTRING];
} FHP_FRIEND_ADD_REQ, *LPFHP_FRIEND_ADD_REQ;


//----------------------------------------------------------------------------
// DG[0x63] 친구 추가 요청 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short		Number;
	BYTE		Result;
	char		Name[MAX_IDSTRING];
	char		FriendName[MAX_IDSTRING];
	BYTE		Server;
} FHP_FRIEND_ADD_RESULT, *LPFHP_FRIEND_ADD_RESULT;


//----------------------------------------------------------------------------
// GD[0x64] 대기중인 친구 추가 요청
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		Result;
	short		Number;
	char		Name[MAX_IDSTRING];
	char		FriendName[MAX_IDSTRING];
} FHP_WAITFRIEND_ADD_REQ, *LPFHP_WAITFRIEND_ADD_REQ;

//----------------------------------------------------------------------------
// DG[0x64] 대기중인 친구 추가 요청 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short		Number;
	BYTE		Result;
	char		Name[MAX_IDSTRING];
	char		FriendName[MAX_IDSTRING];
	BYTE		pServer;
} FHP_WAITFRIEND_ADD_RESULT, *LPFHP_WAITFRIEND_ADD_RESULT;


//----------------------------------------------------------------------------
// GD[0x65] 친구를 삭제한다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short		Number;
	char		Name[MAX_IDSTRING];
	char		FriendName[MAX_IDSTRING];
} FHP_FRIEND_DEL_REQ, *LPFHP_FRIEND_DEL_REQ;

//----------------------------------------------------------------------------
// DG[0x65] 친구를 삭제 결과를 알린다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short		Number;
	BYTE		Result;
	char		Name[MAX_IDSTRING];
	char		FriendName[MAX_IDSTRING];
} FHP_FRIEND_DEL_RESULT, *LPFHP_FRIEND_DEL_RESULT;



//----------------------------------------------------------------------------
// GD[0x66] 대화방 개설을 요청한다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short		Number;
	char		Name[MAX_IDSTRING];
	char		fName[MAX_IDSTRING];	// 대화 상대

} FHP_FRIEND_CHATROOM_CREATE_REQ, *LPFHP_FRIEND_CHATROOM_CREATE_REQ;

//----------------------------------------------------------------------------
// GD[0x66] 대화방 개설을 요청결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		Result;
	short		Number;
	char		Name[MAX_IDSTRING];
	char		FriendName[MAX_IDSTRING];
	char		ServerIp[15];
	WORD		RoomNumber;
	DWORD		Ticket;
	BYTE		Type;
} FHP_FRIEND_CHATROOM_CREATE_RESULT, *LPFHP_FRIEND_CHATROOM_CREATE_RESULT;

//----------------------------------------------------------------------------
// GD[0x70] 다른유저에게 쪽지를 보낸다.
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;
	short		Number;
	DWORD		WindowGuid;
	char		Name[MAX_IDSTRING];
	char		ToName[MAX_IDSTRING];
	char		Subject[MAX_MEMO_SUBJECT];
	BYTE		Dir;
	BYTE		Action;
	short		MemoSize;

#ifdef ITEM_INDEX_EXTEND_20050706
	BYTE		Photo[MAX_PREVIEWCHARSET + 9];
#else
#ifdef DARKLORD_WORK
	BYTE		Photo[MAX_PREVIEWCHARSET + 4];
#else
	BYTE		Photo[MAX_PREVIEWCHARSET + 3];
#endif
#endif

	char		Memo[MAX_MEMO];
} FHP_FRIEND_MEMO_SEND, *LPFHP_FRIEND_MEMO_SEND;

//----------------------------------------------------------------------------
// GD[0x70] 다른 유저에게 쪽지를 보낸 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short		Number;
	char		Name[MAX_IDSTRING];
	BYTE		Result;
	DWORD		WindowGuid;
} FHP_FRIEND_MEMO_SEND_RESULT, *LPFHP_FRIEND_MEMO_SEND_RESULT;

//----------------------------------------------------------------------------
// GD[0x71] 쪽지 리스트 요청
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	WORD		Number;
	char		Name[MAX_IDSTRING];
} FHP_FRIEND_MEMO_LIST_REQ, *LPFHP_FRIEND_MEMO_LIST_REQ;


//----------------------------------------------------------------------------
// DG[0x71] 쪽지 리스트를 보낸다.
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;
	WORD		Number;
	WORD		MemoIndex;
	char		SendName[MAX_IDSTRING];
	char		RecvName[MAX_IDSTRING];
	char		Date[MAX_DATE];
	char		Subject[MAX_MEMO_SUBJECT];
	BYTE		read;
} FHP_FRIEND_MEMO_LIST, *LPFHP_FRIEND_MEMO_LIST;


//----------------------------------------------------------------------------
// GD[0x72] 쪽지 내용을 보내달라고 요청
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short		Number;
	WORD		MemoIndex;
	char		Name[MAX_IDSTRING];
} FHP_FRIEND_MEMO_RECV_REQ, *LPFHP_FRIEND_MEMO_RECV_REQ;

//----------------------------------------------------------------------------
// DG[0x72] 쪽지 내용을 보낸다.
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;
	short		Number;
	char		Name[MAX_IDSTRING];
	WORD		MemoIndex;
	short		MemoSize;

#ifdef ITEM_INDEX_EXTEND_20050706
	BYTE		Photo[MAX_PREVIEWCHARSET + 9];
#else
#ifdef DARKLORD_WORK	
	BYTE		Photo[MAX_PREVIEWCHARSET + 4];
#else
	BYTE		Photo[MAX_PREVIEWCHARSET + 3];
#endif
#endif

	BYTE		Dir;
	BYTE		Action;
	char		Memo[MAX_MEMO];
} FHP_FRIEND_MEMO_RECV, *LPFHP_FRIEND_MEMO_RECV;

//----------------------------------------------------------------------------
// GD[0x73] 쪽지 삭제 요청
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short		Number;
	WORD		MemoIndex;
	char		Name[MAX_IDSTRING];
} FHP_FRIEND_MEMO_DEL_REQ, *LPFHP_FRIEND_MEMO_DEL_REQ;

//----------------------------------------------------------------------------
// DG[0x73] 쪽지 삭제 요청 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		Result;
	WORD		MemoIndex;
	short		Number;
	char		Name[MAX_IDSTRING];
} FHP_FRIEND_MEMO_DEL_RESULT, *LPFHP_FRIEND_MEMO_DEL_RESULT;

//----------------------------------------------------------------------------
// GD[0x74] 친구 초대 요청
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short		Number;
	char		Name[MAX_IDSTRING];
	char		FriendName[MAX_IDSTRING];
	WORD		RoomNumber;
	DWORD		WindowGuid;
} FHP_FRIEND_INVITATION_REQ, *LPFHP_FRIEND_INVITATION_REQ;

//----------------------------------------------------------------------------
// DG[0x74] 친구 초대 요청
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		Result;
	short		Number;
	char		Name[MAX_IDSTRING];
	DWORD		WindowGuid;
} FHP_FRIEND_INVITATION_RET, *LPFHP_FRIEND_INVITATION_RET;


#ifdef MAP_SERVER_WORK_20041030		// 서버 맵분할 관련 패킷 - 게임서버 <-> 인증서버

//----------------------------------------------------------------------------
// GJ [0x7A] 인증서버에게 특정 사용자가 맵서버를 이동해야 함을 알림 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	INT			iIndex;							// 게임서버 사용자 인덱스
	CHAR		szAccountID[MAX_IDSTRING + 1];	// 인증받을 ID
	CHAR		szCharName[MAX_IDSTRING + 1];		// 인증받을 케릭명
	WORD		wCurMapSvrCode;					// 현재의 맵서버 코드 (이전 서버코드가 될것임)
	WORD		wDstMapSvrCode;					// 이동할 맵서버 코드 (목적 서버코드가 될것임)
	WORD		wMapNumber;						// 이동할 맵번호
	BYTE		btX;							// 이동활 좌표 X
	BYTE		btY;							// 이동활 좌표 Y
#ifdef MAP_SERVER_ADDINFO_20050509
#ifdef PCBANG_ADVANTAGE							// 한국전용 (FOR_KOREA)
	BYTE		bPcBangUser;					// PC방 사용자인지 여부
#endif	
#endif
#ifdef MAP_SERVER_ADDINFO_ADULT_20050610		// 태국전용 (FOR_THAILAND)
	BYTE		bIsAdult;						// 성인인지 여부
#endif	
#ifdef CHN_PLAYTIME_LIMIT_SYSTEM_20050818
	INT			iAddPlayTime;					// 중국 피로드 - 게임시간 (5시간 지나면 게임혜택 0%)
#endif
#ifdef VTM_PLAYTIME_LIMIT_SYSTEM_20060626
	INT			iAddPlayTime;					// 베트남 피로도 - 게임시간 (5시간 지나면 게임혜택 0%)
#endif
} PMSG_REQ_MAPSVRMOVE, *LPPMSG_REQ_MAPSVRMOVE;


//----------------------------------------------------------------------------
// JG [0x7A] 인증서버가 특정 사용자의 맵서버 이동에 대한 결과를 알림 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	INT			iIndex;							// 게임서버 사용자 인덱스
	CHAR		szAccountID[MAX_IDSTRING + 1];	// 인증받은 ID
	CHAR		szCharName[MAX_IDSTRING + 1];		// 인증받은 케릭명
	WORD		wCurMapSvrCode;					// 현재의 맵서버 코드 (이전 서버코드가 될것임)
	WORD		wDstMapSvrCode;					// 이동할 맵서버 코드 (목적 서버코드가 될것임)
	WORD		wMapNumber;						// 이동할 맵번호
	BYTE		btX;							// 이동활 좌표 X
	BYTE		btY;							// 이동활 좌표 Y
	INT			iResult;						// 이동요청 결과 (0:성공/1:계정틀림/2:게임서버인덱스없음/3:대상서버풀/4:이미이동요청중)
												// 0 : 실패
												// 1 : 성공
	INT			iJoinAuthCode1;					// 인증 AUTH 코드 - 1
	INT			iJoinAuthCode2;					// 인증 AUTH 코드 - 2
	INT			iJoinAuthCode3;					// 인증 AUTH 코드 - 3
	INT			iJoinAuthCode4;					// 인증 AUTH 코드 - 4
#ifdef MAP_SERVER_ADDINFO_20050509
#ifdef PCBANG_ADVANTAGE
	BYTE		bPcBangUser;					// PC방 사용자인지 여부
#endif
#endif	
#ifdef MAP_SERVER_ADDINFO_ADULT_20050610		// 태국전용 (FOR_THAILAND)
	BYTE		bIsAdult;						// 성인인지 여부
#endif	
#ifdef CHN_PLAYTIME_LIMIT_SYSTEM_20050818
	INT			iAddPlayTime;					// 중국 피로드 - 게임시간 (5시간 지나면 게임혜택 0%)
#endif
#ifdef VTM_PLAYTIME_LIMIT_SYSTEM_20060626
	INT			iAddPlayTime;					// 베트남 피로도 - 게임시간 (5시간 지나면 게임혜택 0%)
#endif
} PMSG_ANS_MAPSVRMOVE, *LPPMSG_ANS_MAPSVRMOVE;


//----------------------------------------------------------------------------
// GJ [0x7B] 인증서버에게 특정 사용자가 맵서버 이동 후 인증을 요청함을 알림 (0xC1)		-> 인증서버는 해당 사용자의 게임서버 코드도 갱신
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	INT			iIndex;							// 게임서버 사용자 인덱스
	CHAR		szAccountID[MAX_IDSTRING + 1];	// 인증받을 ID
	CHAR		szCharName[MAX_IDSTRING + 1];		// 인증받을 케릭명
	WORD		wDstMapSvrCode;					// 사용자가 이동한 게임서버 코드 (현재 접속한 게임서버에서 넣어줌)
	INT			iJoinAuthCode1;					// 인증 AUTH 코드 - 1
	INT			iJoinAuthCode2;					// 인증 AUTH 코드 - 2
	INT			iJoinAuthCode3;					// 인증 AUTH 코드 - 3
	INT			iJoinAuthCode4;					// 인증 AUTH 코드 - 4
} PMSG_REQ_MAPSVRAUTH, *LPPMSG_REQ_MAPSVRAUTH;


//----------------------------------------------------------------------------
// JG [0x7B] 인증서버에게 특정 사용자가 맵서버 이동 후 인증요청에 대한 결과 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	INT			iIndex;							// 게임서버 사용자 인덱스
	CHAR		szAccountID[MAX_IDSTRING + 1];	// 인증받을 ID			(인증서버에서 다시 보냄)
	CHAR		szCharName[MAX_IDSTRING + 1];		// 인증받을 케릭명		(인증서버에서 다시 보냄)
	WORD		wPrevMapSvrCode;				// 이전 게임서버 코드
	WORD		wMapNumber;						// 이동할 맵번호
	BYTE		btX;							// 이동활 좌표 X
	BYTE		btY;							// 이동활 좌표 Y
	INT			iResult;						// 이동요청 결과 (0:성공/1:계정틀림/2:인증코드틀림/3:서버코드틀림/4:서버이동중아님)

												// 아래는 기존의 인증결과 정보 들
	INT			iUserNumber;
	INT			iDBNumber;
#ifdef UPDATE_USERPASSWORD_LENGTH_20090424
	CHAR		cJoominNumber[13];//[MAX_JOOMINNUMBER_LENGTH];				// 주민번호 뒷자리
#else
	CHAR		cJoominNumber[13];				// 주민번호 뒷자리
#endif	// UPDATE_USERPASSWORD_LENGTH_20090424

	BYTE		btBlockCode;					// 블록코드는 별도로 받음
#ifdef FOR_THAILAND
	CHAR		AuthAdult;						// 성인 인증 코드
#endif
#ifdef ADD_PROTOCOL_PCBANG_GUID
	INT			iPcBangGuid;
#endif
#ifdef MAP_SERVER_ADDINFO_20050509
#ifdef PCBANG_ADVANTAGE
	BYTE		bPcBangUser;					// PC방 사용자인지 여부
#endif	
#endif	
#ifdef MAP_SERVER_ADDINFO_ADULT_20050610		// 태국전용 (FOR_THAILAND)
	BYTE		bIsAdult;						// 성인인지 여부
#endif	
#ifdef CHN_PLAYTIME_LIMIT_SYSTEM_20050818
#ifdef MODIFY_CHN_PLAYTIME_LIMIT_SYSTEM_01_20070509
	int			iVerifiedType;					// 중국 피로도 성인 인증 타입 ( 0 : 성인, 1 : 미성년자, 2 : 오류 )
#endif // MODIFY_CHN_PLAYTIME_LIMIT_SYSTEM_01_20070509
	INT			iAddPlayTime;					// 중국 피로드 - 게임시간 (5시간 지나면 게임혜택 0%)
#endif
#ifdef VTM_PLAYTIME_LIMIT_SYSTEM_20060626
	INT			iAddPlayTime;					// 베트남 피로도 - 게임시간 (5시간 지나면 게임혜택 0%)
#endif
} PMSG_ANS_MAPSVRAUTH, *LPPMSG_ANS_MAPSVRAUTH;

#ifdef ADD_HACKING_TOOL_BLOCK_20090311
//----------------------------------------------------------------------------
// GJ [0x8A] 인증서버에 해킹 프로그램의 사용 여부 확인의 브로드 캐스팅을 요청한다. (0xC1) 
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	char		chHackToolFilename[64];
} PMSG_HACKTOOL_USE_STATISTICS_REQ, *LPPMSG_HACKTOOL_USE_STATISTICS_REQ;

//----------------------------------------------------------------------------
// JG [0x8A] 전체 게임서버에 해킹 프로그램의 사용 여부 확인을 요청한다. (0xC1) 
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	char		chHackToolFilename[64];
} PMSG_HACKTOOL_USE_STATISTICS, *LPPMSG_HACKTOOL_USE_STATISTICS;

//----------------------------------------------------------------------------
// GJ [0x8B] 인증서버에 해킹 프로그램의 사용자의 맵이동 제한을 요청한다. (0xC1) 
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	BYTE		btModifyType;				// 설정 타입 ( 1 : 추가, 2 : 수정, 3 : 삭제 )
	DWORD		dwReservationTime;			// 블록 시작 시간
	DWORD		dwBlockTerm;				// 블록 기간 (단위 : 초)
	WORD		wBlockRate;					// 블록 확률
	char		chHackToolFilename[64];
} PMSG_RESERVE_HACKTOOL_MAP_MOVE_REQ, *LPPMSG_RESERVE_HACKTOOL_MAP_MOVE_REQ;

//----------------------------------------------------------------------------
// GC [0x8B] 전체 게임서버에 해킹 프로그램의 사용자의 맵이동 제한을 요청한다. (0xC1) 
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	BYTE		btModifyType;				// 설정 타입 ( 1 : 추가, 2 : 수정, 3 : 삭제 )
	DWORD		dwReservationTime;			// 블록 시작 시간
	DWORD		dwBlockTerm;				// 블록 기간 (단위 : 초)
	WORD		wBlockRate;					// 블록 확률
	char		chHackToolFilename[64];
} PMSG_RESERVE_HACKTOOL_MAP_MOVE, *LPPMSG_RESERVE_HACKTOOL_MAP_MOVE;

//----------------------------------------------------------------------------
// GJ [0x8C] 전체 게임서버에 해킹 프로그램의 통계를 인증서버로 전달한다. (0xC1) 
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	WORD		wCurrentUserCount;
	WORD		wHackToolUserCount;
	char		chHackToolFilename[64];
} PMSG_HACKTOOL_USE_STATISTICS_ANS, *LPPMSG_HACKTOOL_USE_STATISTICS_ANS;

//----------------------------------------------------------------------------
// GJ [0x8C] 전체 게임서버에 해킹 프로그램의 통계를 인증서버로 전달한다. (0xC1) 
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	char		chMessage[256];
}PMSG_HACKTOOL_USE_STATISTICS_TOTAL, *LPPMSG_HACKTOOL_USE_STATISTICS_TOTAL;
#endif // ADD_HACKING_TOOL_BLOCK_20090311

//----------------------------------------------------------------------------
// JG [0x7C] 특정 게임서버의 현재 최대 사용자 수를 주기적으로 보냄 (0xC1) 
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	INT			iSvrCode;						// 사용자가 이동한 게임서버 코드 (게임서버에서 넣어줌)
	INT			iMaxUserCount;					// 현재 서버의 최대 사용자 수
	INT			iCurUserCount;					// 현재 서버의 접속 사용자 수
} PMSG_NOTIFY_MAXUSER, *LPPMSG_NOTIFY_MAXUSER;

#endif

#ifdef UPDATE_RESEND_GETCHARlIST_DISABLE_20090605
//----------------------------------------------------------------------------
// GJ [0x8F] 블럭시킬 아이피를 등록한다. (0xC1) 
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	char		BlockIp[17];
} PMSG_BLOCK_IP, *LPPMSG_BLOCK_IP;
#endif	// UPDATE_RESEND_GETCHARlIST_DISABLE_20090605

//----------------------------------------------------------------------------
// 채팅 서버와의 프로토콜 교환
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// DG[0xA0] 채팅 서버에 방 개설을 요청한다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	char		Name[MAX_IDSTRING];	// 방 개설을 요청한 사람
	char		FriendName[MAX_IDSTRING];	// 최초 대화 상대
	short		UserNumber;
	short		ServerNumber;
	short		FriendNumber;
	short		FriendServerNumber;
} FHP_CHAT_ROOMCREATE, *LPFHP_CHAT_ROOMCREATE;

//----------------------------------------------------------------------------
// DG[0xA0] 채팅 서버에 방 개설을 요청 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		Result;
	WORD		RoomNumber;
	char		Name[MAX_IDSTRING];	// 방 개설을 요청한 사람
	char		FriendName[MAX_IDSTRING];	// 대화 상대
	short		UserNumber;
	short		ServerNumber;
	DWORD		Ticket;
	DWORD		FriendTicket;
	BYTE		Type;
} FHP_CHAT_ROOMCREATE_RESULT, *LPFHP_CHAT_ROOMCREATE_RESULT;

//----------------------------------------------------------------------------
// DG[0xA1] 채팅 서버에 친구를 초대한다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	WORD		RoomNumber;
	char		Name[MAX_IDSTRING];	// 방 개설을 요청한 사람
	short		UserNumber;
	short		ServerNumber;
	BYTE		Type;
} FHP_CHAT_JOINUSER_REQ, *LPFHP_CHAT_JOINUSER_REQ;

//----------------------------------------------------------------------------
// DG[0xA1] 채팅 서버에 친구를 초대한 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		Result;
	WORD		RoomNumber;
	char		Name[MAX_IDSTRING];	// 방 개설을 요청한 사람
	short		UserNumber;
	short		ServerNumber;
	DWORD		Ticket;
	DWORD		FriendTicket;
} FHP_CHAT_JOINUSER_RESULT, *LPFHP_CHAT_JOINUSER_RESULT;

//----------------------------------------------------------------------------
// CD[0xA2] 상대에게 말을 걸어 초대한다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	WORD		RoomNumber;
	char		Name[MAX_IDSTRING];	// 말을 건 사용자
	DWORD		Ticket;
	char		Msg[100];
} FHP_CHAT_ROOMINVITATION, *LPFHP_CHAT_ROOMINVITATION;


#endif
//##__FRIEND_WORK__



//----------------------------------------------------------------------------
// 길드 & 연합 서버그룹(마야 등) 채팅 프로토콜
//
// Lastest : 20050706
//
//----------------------------------------------------------------------------

#ifdef ADD_SERVERGROUP_CHATTING_FOR_GUILD_UNION_01_20050706

//----------------------------------------------------------------------------
// GEXD[0x50] 서버그룹 길드 채팅
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	INT			iGuildNum;
	char		szCharacterName[MAX_IDSTRING];
	char		szChattingMsg[MAX_CHAT];

} EXSDHP_SERVERGROUP_GUILD_CHATTING_SEND, *LPEXSDHP_SERVERGROUP_GUILD_CHATTING_SEND;

typedef struct
{
	PBMSG_HEAD	h;
	INT			iGuildNum;
	char		szCharacterName[MAX_IDSTRING];
	char		szChattingMsg[MAX_CHAT];

} EXSDHP_SERVERGROUP_GUILD_CHATTING_RECV, *LPEXSDHP_SERVERGROUP_GUILD_CHATTING_RECV;


//----------------------------------------------------------------------------
// GEXD[0x51] 서버그룹 연합 채팅
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	INT			iUnionNum;
	char		szCharacterName[MAX_IDSTRING];
	char		szChattingMsg[MAX_CHAT];

} EXSDHP_SERVERGROUP_UNION_CHATTING_SEND, *LPEXSDHP_SERVERGROUP_UNION_CHATTING_SEND;

typedef struct
{
	PBMSG_HEAD	h;
	INT			iUnionNum;
	char		szCharacterName[MAX_IDSTRING];
	char		szChattingMsg[MAX_CHAT];

} EXSDHP_SERVERGROUP_UNION_CHATTING_RECV, *LPEXSDHP_SERVERGROUP_UNION_CHATTING_RECV;

#endif




//----------------------------------------------------------------------------
// 새로운 길드 시스템 프로토콜
//
// Lastest : 20040913, 20040922, 20041006
//
//----------------------------------------------------------------------------

#ifdef ADD_NEW_GUILD_01_20040913

//----------------------------------------------------------------------------
// GEXD[0xE1] 직책을 임명 / 변경 / 해제 요청
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	WORD		wUserIndex;							// 임명하는 유저(길마, 부길마) 인덱스
	BYTE		btType;								// 임명(0x01) / 변경(0x02) / 해제(0x03)

	BYTE		btGuildStatus;						// 임명하는 직책.
	char		szGuildName[MAX_GUILDNAMESTRING + 1];	// 길드 이름.
	char		szTargetName[MAX_IDSTRING + 1];		// 대상 유저 이름.

} EXSDHP_GUILD_ASSIGN_STATUS_REQ, *LPEXSDHP_GUILD_ASSIGN_STATUS_REQ;


//----------------------------------------------------------------------------
// EXDG[0xE1] 직책을 임명 / 변경 / 해제 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		btFlag;								// 요청서버인지 판단.
	WORD		wUserIndex;							// 임명하는 유저(길마, 부길마) 인덱스
	BYTE		btType;								// 임명(0x01) / 변경(0x02) / 해제(0x03)
	BYTE		btResult;							// 결과

	BYTE		btGuildStatus;						// 임명된 직책.
	char		szGuildName[MAX_GUILDNAMESTRING + 1];	// 길드 이름.
	char		szTargetName[MAX_IDSTRING + 1];		// 대상 유저 이름.

} EXSDHP_GUILD_ASSIGN_STATUS_RESULT, *LPEXSDHP_GUILD_ASSIGN_STATUS_RESULT;

#endif
// ## ADD_NEW_GUILD_01_20040913


#ifdef ADD_NEW_GUILD_02_20040922

//----------------------------------------------------------------------------
// GEXD[0xE2] 길드 타입을 설정하는 요청
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	WORD		wUserIndex;							// 길드타입을 설정하는 유저 인덱스
	BYTE		btGuildType;						// 설정할 길드타입 일반길드(0x01) / 용병길드(0x02) / 클랜(0x03)

	char		szGuildName[MAX_GUILDNAMESTRING + 1];	// 길드 이름.

} EXSDHP_GUILD_ASSIGN_TYPE_REQ, *LPEXSDHP_GUILD_ASSIGN_TYPE_REQ;


//----------------------------------------------------------------------------
// EXDG[0xE2] 길드 타입을 설정하는 요청
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		btFlag;								// 요청서버인지 판단.
	WORD		wUserIndex;							// 임명하는 유저(길마, 부길마) 인덱스
	BYTE		btGuildType;						// 설정할 길드타입 일반길드(0x01) / 용병길드(0x02) / 클랜(0x03)
	BYTE		btResult;							// 결과

	char		szGuildName[MAX_GUILDNAMESTRING + 1];	// 길드 이름.

} EXSDHP_GUILD_ASSIGN_TYPE_RESULT, *LPEXSDHP_GUILD_ASSIGN_TYPE_RESULT;

#endif


#ifdef ADD_NEW_UNION_01_20041006
typedef struct {}__UNION_SPROTOCOL_H___;
//----------------------------------------------------------------------------
// GEXD[0xE5] Union, Rival 관계 맺기
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	WORD		wRequestUserIndex;
	WORD		wTargetUserIndex;

	BYTE		btRelationShipType;

	INT			iRequestGuildNum;
	INT			iTargetGuildNum;

} EXSDHP_RELATIONSHIP_JOIN_REQ, *LPEXSDHP_RELATIONSHIP_JOIN_REQ;

//----------------------------------------------------------------------------
// EXDG[0xE5] Union, Rival 관계 맺기 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		btFlag;								// 요청서버인지 판단.
	WORD		wRequestUserIndex;
	WORD		wTargetUserIndex;

	BYTE		btResult;							// 결과

	BYTE		btRelationShipType;

	INT			iRequestGuildNum;
	INT			iTargetGuildNum;

	CHAR		szRequestGuildName[MAX_GUILDNAMESTRING + 1];
	CHAR		szTargetGuildName[MAX_GUILDNAMESTRING + 1];

} EXSDHP_RELATIONSHIP_JOIN_RESULT, *LPEXSDHP_RELATIONSHIP_JOIN_RESULT;

//----------------------------------------------------------------------------
// GEXD[0xE6] Union, Rival 관계 끊기
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	WORD		wRequestUserIndex;
	WORD		wTargetUserIndex;					// 임명하는 유저(길마, 부길마) 인덱스	

	BYTE		btRelationShipType;

	INT			iRequestGuildNum;
	INT			iTargetGuildNum;

} EXSDHP_RELATIONSHIP_BREAKOFF_REQ, *LPEXSDHP_RELATIONSHIP_BREAKOFF_REQ;

//----------------------------------------------------------------------------
// EXDG[0xE6] Union, Rival 관계 끊기 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		btFlag;								// 요청서버인지 판단.

	WORD		wRequestUserIndex;
	WORD		wTargetUserIndex;

	BYTE		btResult;							// 결과

	BYTE		btRelationShipType;

	INT			iRequestGuildNum;
	INT			iTargetGuildNum;

} EXSDHP_RELATIONSHIP_BREAKOFF_RESULT, *LPEXSDHP_RELATIONSHIP_BREAKOFF_RESULT;


//----------------------------------------------------------------------------
// ★ EXDG[0xE7] 특정 Union 의 RelationShip 리스트 전송 ( BroadCastring 됨 )
//----------------------------------------------------------------------------

// 모든 길드는 유니온이다.
// '공식적인 유니온'은 '유니온 2개 이상의 결합 유니온' 이다.
// -> 공식유니온 = 유니온 + 유니온 + 유니온 + ...
typedef struct
{
	PWMSG_HEAD	h;

	BYTE		btFlag;								// 요청서버인지 판단.

	BYTE		btRelationShipType;
	BYTE		btRelationShipMemberCount;

#ifdef ADD_UNION_GET_UNIONMARK_01_20041222
	BYTE		pUnionMasterGuildMark[MAX_GUILDMARKSIZE];
#endif

	CHAR		szUnionMasterGuildName[MAX_GUILDNAMESTRING + 1];
	INT			iUnionMasterGuildNumber;
	INT			iRelationShipMember[MAX_RELATIONSHIP_COUNT];
} EXSDHP_UNION_RELATIONSHIP_LIST, *LPEXSDHP_UNION_RELATIONSHIP_LIST;

//----------------------------------------------------------------------------
// ★ EXDG[0xE8] 길드의 RelationShip 변경을 Notification 한다. ( BroadCastring 됨 )
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;

	BYTE		btFlag;								// 요청서버인지 판단.
	BYTE		btUpdateFlag;						// 갱신된 목록에 대한 상세 정보

													// [0x10] 유니온 해체 됐다.


	BYTE		btGuildListCount;						// Guild 카운트.
	INT			iGuildList[MAX_RELATIONSHIP_COUNT];		// Update 될 길드 리스트.

} EXSDHP_NOTIFICATION_RELATIONSHIP, *LPEXSDHP_NOTIFICATION_RELATIONSHIP;

//----------------------------------------------------------------------------
// ★ EXDG[0xE9] 연합 리스트를 보내준다. ( P2P 됨 )
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	WORD		wRequestUserIndex;
	INT			iUnionMasterGuildNumber;

} EXSDHP_UNION_LIST_REQ, *LPEXSDHP_UNION_LIST_REQ;

typedef struct
{
	PWMSG_HEAD	h;
	BYTE		btCount;
	BYTE		btResult;

	WORD		wRequestUserIndex;
	INT			iTimeStamp;							// 캐싱을 위한 최근 갱신 시간을 보내준다.

	BYTE		btRivalMemberNum;
	BYTE		btUnionMemberNum;

} EXSDHP_UNION_LIST_COUNT, *LPEXSDHP_UNION_LIST_COUNT;

typedef struct
{
	BYTE		btMemberNum;
	BYTE		Mark[MAX_GUILDMARKSIZE];
	char		szGuildName[MAX_GUILDNAMESTRING];

} EXSDHP_UNION_LIST, *LPEXSDHP_UNION_LIST;


#endif

#ifdef ADD_ABILITY_OF_UNIONMASTER_TO_KICK_OUT_UNIONMEMBER_01_20050418

//----------------------------------------------------------------------------
// GEXD[0xEB][0x01] Union Member 강제 탈퇴 요청
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;

	WORD		wRequestUserIndex;

	BYTE		btRelationShipType;

	char		szUnionMasterGuildName[MAX_GUILDNAMESTRING];
	char		szUnionMemberGuildName[MAX_GUILDNAMESTRING];

} EXSDHP_KICKOUT_UNIONMEMBER_REQ, *LPEXSDHP_KICKOUT_UNIONMEMBER_REQ;

//----------------------------------------------------------------------------
// EXDG[0xEB][0x01] Union Member 강제 탈퇴 결과
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	BYTE		btFlag;								// 요청서버인지 판단.

	WORD		wRequestUserIndex;
	BYTE		btRelationShipType;

	BYTE		btResult;							// 결과

	char		szUnionMasterGuildName[MAX_GUILDNAMESTRING + 1];
	char		szUnionMemberGuildName[MAX_GUILDNAMESTRING + 1];

} EXSDHP_KICKOUT_UNIONMEMBER_RESULT, *LPEXSDHP_KICKOUT_UNIONMEMBER_RESULT;

#endif 


#ifdef ADD_MANAGER_SENDMAIL
//----------------------------------------------------------------------------
// CG [0x63] 인증서버 -> 게임서버 쪽지 보내기
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;

	char		Name[MAX_IDSTRING];
	char		TargetName[MAX_IDSTRING];
	char		Subject[MAX_MEMO_SUBJECT];
	short		MemoSize;
	char		Memo[MAX_MEMO];
} PMSG_JG_MEMO_SEND, *LPPMSG_JG_MEMO_SEND;
#endif


#ifdef MU_CASTLESIEGE_DS_PROTOCOL_20041105		// 공성전 관련 추가된 프로토콜 (GS <-> DS)


//----------------------------------------------------------------------------
// GD [0x80][0x00] 성 전체 정보 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iCastleEventCycle;		// 공성전 주기
} CSP_REQ_CASTLEDATA, *LPCSP_REQ_CASTLEDATA;


//----------------------------------------------------------------------------
// DG [0x80][0x00] 성 전체 정보 요청 응답 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	WORD		wStartYear;				// 공성 시작 - 년
	BYTE		btStartMonth;			// 공성 시작 - 월
	BYTE		btStartDay;				// 공성 시작 - 일
	WORD		wEndYear;				// 공성 종료 - 년
	BYTE		btEndMonth;				// 공성 종료 - 월
	BYTE		btEndDay;				// 공성 종료 - 일
	BYTE		btIsSiegeGuildList;		// 공성관련 길드정보가 이미 구축되었는가 ?
	BYTE		btIsSiegeEnded;			// 공성이 이미 치루어 졌는가 ?
	BYTE		btIsCastleOccupied;		// 성이 이미 사용자들에게 차지된 상태인가 ?
	CHAR		szCastleOwnGuild[MAX_GUILDNAMESTRING];	// 캐슬을 차지한 길드명 (없으면 "")
	INT64		i64CastleMoney;			// 현재 성의 보유 젠
	INT			iTaxRateChaos;			// 카오스 조합 세율
	INT			iTaxRateStore;			// 상점 세율
	INT			iTaxHuntZone;			// 사냥터 입장료
	INT			iFirstCreate;			// 이것이 최초로 만드는 것인가 ?
} CSP_ANS_CASTLEDATA, *LPCSP_ANS_CASTLEDATA;


//----------------------------------------------------------------------------
// GD [0x80][0x01] 수성측 길드의 길마이름 요청 -> 경비병 NPC 성 상태 출력 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;					// 맵 서버군 번호
	INT			iIndex;						// 게임서버 오브젝트 인덱스
} CSP_REQ_OWNERGUILDMASTER, *LPCSP_REQ_OWNERGUILDMASTER;


//----------------------------------------------------------------------------
// DG [0x80][0x01] 수성측 길드의 길마이름 요청 응답 -> 경비병 NPC 성 상태 출력 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	INT			iResult;					// 성공여부 (0:실패/1:성공/2:성주인없음/3:성정보비정상/4:성길드없어짐)
	WORD		wMapSvrNum;					// 맵 서버군 번호
	INT			iIndex;						// 게임서버 오브젝트 인덱스
	CHAR		szCastleOwnGuild[MAX_GUILDNAMESTRING];		// 캐슬을 차지한 길드명 (없으면 "")
	CHAR		szCastleOwnGuildMaster[MAX_IDSTRING];		// 캐슬을 차지한 길드마스터명 (없으면 "")
} CSP_ANS_OWNERGUILDMASTER, *LPCSP_ANS_OWNERGUILDMASTER;


//----------------------------------------------------------------------------
// GD [0x80][0x03] 수성측 NPC 구입 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	INT			iNpcNumber;				// NPC번호
	INT			iNpcIndex;				// NPC인덱스
	INT			iNpcDfLevel;			// 방어력 레벨
	INT			iNpcRgLevel;			// 회복력 레벨
	INT			iNpcMaxHp;				// 최대 HP
	INT			iNpcHp;					// HP
	BYTE		btNpcX;					// 좌표 - X
	BYTE		btNpcY;					// 좌표 - Y
	BYTE		btNpcDIR;				// 방향
	INT			iBuyCost;				// NPC구입비용
} CSP_REQ_NPCBUY, *LPCSP_REQ_NPCBUY;


//----------------------------------------------------------------------------
// DG [0x80][0x03] 수성측 NPC 구입 요청 응답 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	INT			iNpcNumber;				// NPC번호
	INT			iNpcIndex;				// NPC인덱스
	INT			iBuyCost;				// NPC구입비용
} CSP_ANS_NPCBUY, *LPCSP_ANS_NPCBUY;


//----------------------------------------------------------------------------
// GD [0x80][0x04] 수성측 NPC 수리 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	INT			iNpcNumber;				// NPC번호
	INT			iNpcIndex;				// NPC인덱스
	INT			iRepairCost;			// NPC수리비용
} CSP_REQ_NPCREPAIR, *LPCSP_REQ_NPCREPAIR;


//----------------------------------------------------------------------------
// DG [0x80][0x04] 수성측 NPC 수리 요청 응답 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	INT			iNpcNumber;				// NPC번호
	INT			iNpcIndex;				// NPC인덱스
	INT			iNpcMaxHp;				// 최대 HP
	INT			iNpcHp;					// 수정될 HP
	INT			iRepairCost;			// NPC수리비용
} CSP_ANS_NPCREPAIR, *LPCSP_ANS_NPCREPAIR;


//----------------------------------------------------------------------------
// GD [0x80][0x05] 수성측 NPC 업그레이드 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	INT			iNpcNumber;				// NPC번호
	INT			iNpcIndex;				// NPC인덱스
	INT			iNpcUpType;				// NPC업그레이드 타입 (1:방어력/2:회복력/3:최대HP)
	INT			iNpcUpValue;			// NPC업그레이드 수치
	INT			iNpcUpIndex;			// NPC업그레이드 레벨의 인덱스 (MAX HP도 레벨화)
} CSP_REQ_NPCUPGRADE, *LPCSP_REQ_NPCUPGRADE;


//----------------------------------------------------------------------------
// DG [0x80][0x05] 수성측 NPC 업그레이드 요청 응답 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	INT			iNpcNumber;				// NPC번호
	INT			iNpcIndex;				// NPC인덱스
	INT			iNpcUpType;				// NPC업그레이드 타입 (1:방어력/2:회복력/3:최대HP)
	INT			iNpcUpValue;			// NPC업그레이드 수치
	INT			iNpcUpIndex;			// NPC업그레이드 레벨의 인덱스 (MAX HP도 레벨화)
} CSP_ANS_NPCUPGRADE, *LPCSP_ANS_NPCUPGRADE;


//----------------------------------------------------------------------------
// GD [0x80][0x06] 성주측 세금정보 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
} CSP_REQ_TAXINFO, *LPCSP_REQ_TAXINFO;


//----------------------------------------------------------------------------
// DG [0x80][0x06] 성주측 세금정보 요청 응답 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	INT64		i64CastleMoney;			// 현재 성의 자금
	INT			iTaxRateChaos;			// 카오스 조합 세율
	INT			iTaxRateStore;			// 상점 세율
	INT			iTaxHuntZone;			// 사냥터 입장료
} CSP_ANS_TAXINFO, *LPCSP_ANS_TAXINFO;


//----------------------------------------------------------------------------
// GD [0x80][0x07] 성주측 성정보 수정 요청 - 세율 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	INT			iTaxKind;				// 세율 종류 (1:카오스 조합 / 2:상점 / 3:사냥터 입장료)
	INT			iTaxRate;				// 세율
} CSP_REQ_TAXRATECHANGE, *LPCSP_REQ_TAXRATECHANGE;


//----------------------------------------------------------------------------
// DG [0x80][0x07] 성주측 성정보 수정 요청 응답 - 세율 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	INT			iTaxKind;				// 세율 종류 (1:카오스 조합 / 2:상점 / 3:사냥터 입장료)
	INT			iTaxRate;				// 세율
} CSP_ANS_TAXRATECHANGE, *LPCSP_ANS_TAXRATECHANGE;


//----------------------------------------------------------------------------
// GD [0x80][0x08] 성주측 성정보 수정요청 - 소유 젠 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	INT			iMoneyChanged;			// 상대적인 젠 증가분 (+/-)
} CSP_REQ_MONEYCHANGE, *LPCSP_REQ_MONEYCHANGE;


//----------------------------------------------------------------------------
// DG [0x80][0x08] 성주측 성정보 수정요청 응답 - 소유 젠 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	INT			iMoneyChanged;			// 상대적인 젠 증가분 (+/-)
	INT64		i64CastleMoney;			// 계산된 결과
} CSP_ANS_MONEYCHANGE, *LPCSP_ANS_MONEYCHANGE;


//----------------------------------------------------------------------------
// GD [0x80][0x09] 성주측 성정보 수정요청 - 공성 시작/종료 날짜 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	WORD		wStartYear;				// 공성 시작 - 년
	BYTE		btStartMonth;			// 공성 시작 - 월
	BYTE		btStartDay;				// 공성 시작 - 일
	WORD		wEndYear;				// 공성 종료 - 년
	BYTE		btEndMonth;				// 공성 종료 - 월
	BYTE		btEndDay;				// 공성 종료 - 일
} CSP_REQ_SDEDCHANGE, *LPCSP_REQ_SDEDCHANGE;


//----------------------------------------------------------------------------
// DG [0x80][0x09] 성주측 성정보 수정요청 응답 - 공성 시작/종료 날짜 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	WORD		wStartYear;				// 공성 시작 - 년
	BYTE		btStartMonth;			// 공성 시작 - 월
	BYTE		btStartDay;				// 공성 시작 - 일
	WORD		wEndYear;				// 공성 종료 - 년
	BYTE		btEndMonth;				// 공성 종료 - 월
	BYTE		btEndDay;				// 공성 종료 - 일
} CSP_ANS_SDEDCHANGE, *LPCSP_ANS_SDEDCHANGE;


//----------------------------------------------------------------------------
// GD [0x80][0x0A] 공성측 특정 등록 길드 정보 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	CHAR		szGuildName[MAX_GUILDNAMESTRING];			// 길드이름
} CSP_REQ_GUILDREGINFO, *LPCSP_REQ_GUILDREGINFO;


//----------------------------------------------------------------------------
// DG [0x80][0x0A] 공성측 특정 등록 길드 정보 요청 응답 (0xC2)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	CHAR		szGuildName[MAX_GUILDNAMESTRING];			// 길드이름
	INT			iRegMarkCount;			// 등록된 문장수
	bool		bIsGiveUp;				// 포기여부
	BYTE		btRegRank;				// 등록순위
} CSP_ANS_GUILDREGINFO, *LPCSP_ANS_GUILDREGINFO;


//----------------------------------------------------------------------------
// GD [0x80][0x0B] 성주측 성정보 수정요청 - 공성 종료 여부 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	BOOL		bIsSiegeEnded;			// 공성 종료 여부
} CSP_REQ_SIEGEENDCHANGE, *LPCSP_REQ_SIEGEENDCHANGE;


//----------------------------------------------------------------------------
// DG [0x80][0x0B] 성주측 성정보 수정요청 응답 - 공성 종료 여부 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	BOOL		bIsSiegeEnded;			// 공성 종료 여부
} CSP_ANS_SIEGEENDCHANGE, *LPCSP_ANS_SIEGEENDCHANGE;


//----------------------------------------------------------------------------
// GD [0x80][0x0C] 성주측 성정보 수정요청 - 성의 주인길드, 차지된 상태 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	BOOL		bIsCastleOccupied;		// 성이 이미 차지되었는가 ?
	CHAR		szOwnerGuildName[MAX_GUILDNAMESTRING];	// 성의 주인길드 이름
} CSP_REQ_CASTLEOWNERCHANGE, *LPCSP_REQ_CASTLEOWNERCHANGE;


//----------------------------------------------------------------------------
// DG [0x80][0x0C] 성주측 성정보 수정요청 응답 - 성의 주인길드, 차지된 상태 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	BOOL		bIsCastleOccupied;		// 성이 이미 차지되었는가 ?
	CHAR		szOwnerGuildName[MAX_GUILDNAMESTRING];	// 성의 주인길드 이름
} CSP_ANS_CASTLEOWNERCHANGE, *LPCSP_ANS_CASTLEOWNERCHANGE;


//----------------------------------------------------------------------------
// GD [0x80][0x0D] 공성측 길드의 공성전 등록 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	CHAR		szEnemyGuildName[MAX_GUILDNAMESTRING];	// 최종 공격길드 이름
} CSP_REQ_REGATTACKGUILD, *LPCSP_REQ_REGATTACKGUILD;


//----------------------------------------------------------------------------
// DG [0x80][0x0D] 공성측 길드의 공성전 등록 요청 응답 C1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공/2:이미등록됨/3:수성측길드/4:길드없음/5:길마레벨부족/6:등록길드수초과/7:길드원수부족)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	CHAR		szEnemyGuildName[MAX_GUILDNAMESTRING];	// 최종 공격길드 이름
} CSP_ANS_REGATTACKGUILD, *LPCSP_ANS_REGATTACKGUILD;


//----------------------------------------------------------------------------
// GD [0x80][0x0E] 공성주기 끝 - 정보 초기화 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
} CSP_REQ_CASTLESIEGEEND, *LPCSP_REQ_CASTLESIEGEEND;


//----------------------------------------------------------------------------
// DG [0x80][0x0E] 공성주기 끝 - 정보 초기화 요청 응답 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
} CSP_ANS_CASTLESIEGEEND, *LPCSP_ANS_CASTLESIEGEEND;


//----------------------------------------------------------------------------
// GD [0x80][0x0F] 자신의 맵서버군에게 특정 메시지 전달 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	CHAR		szMsgText[128];			// 자신의 맵서버군에게 전달할 메시지
} CSP_REQ_MAPSVRMULTICAST, *LPCSP_REQ_MAPSVRMULTICAST;


//----------------------------------------------------------------------------
// DG [0x80][0x0F] 자신의 맵서버군에게 특정 메시지 전달 요청 -> 전달 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	CHAR		szMsgText[128];			// 자신의 맵서버군에게 전달할 메시지
} CSP_ANS_MAPSVRMULTICAST, *LPCSP_ANS_MAPSVRMULTICAST;


//----------------------------------------------------------------------------
// GD [0x80][0x10] 공성측 특정 등록 길드 마크 등록 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	CHAR		szGuildName[MAX_GUILDNAMESTRING];			// 길드이름
	INT			iItemPos;				// 성주의 표식의 위치
} CSP_REQ_GUILDREGMARK, *LPCSP_REQ_GUILDREGMARK;


//----------------------------------------------------------------------------
// DG [0x80][0x10] 공성측 특정 등록 길드 마크 등록 요청 응답 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	CHAR		szGuildName[MAX_GUILDNAMESTRING];			// 길드이름
	INT			iItemPos;				// 성주의 표식의 위치
	INT			iRegMarkCount;			// 등록된 문장수
} CSP_ANS_GUILDREGMARK, *LPCSP_ANS_GUILDREGMARK;


//----------------------------------------------------------------------------
// GD [0x80][0x11] 공성측 특정 등록 길드 마크 개수 초기화 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	CHAR		szGuildName[MAX_GUILDNAMESTRING];			// 길드이름
} CSP_REQ_GUILDRESETMARK, *LPCSP_REQ_GUILDRESETMARK;


//----------------------------------------------------------------------------
// DG [0x80][0x11] 공성측 특정 등록 길드 마크 개수 초기화 요청 응답 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	CHAR		szGuildName[MAX_GUILDNAMESTRING];			// 길드이름
	INT			iRegMarkCount;			// 이전까지 등록된 문장수 (현재는 없는것)
} CSP_ANS_GUILDRESETMARK, *LPCSP_ANS_GUILDRESETMARK;


//----------------------------------------------------------------------------
// GD [0x80][0x12] 공성측 특정 등록 길드 공성 포기여부 수정 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	CHAR		szGuildName[MAX_GUILDNAMESTRING];			// 길드이름
	BOOL		bIsGiveUp;				// 공성 포기여부
} CSP_REQ_GUILDSETGIVEUP, *LPCSP_REQ_GUILDSETGIVEUP;


//----------------------------------------------------------------------------
// DG [0x80][0x12] 공성측 특정 등록 길드 공성 포기여부 수정 요청 응답 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	CHAR		szGuildName[MAX_GUILDNAMESTRING];			// 길드이름
	BOOL		bIsGiveUp;				// 공성 포기여부
	INT			iRegMarkCount;			// 등록된 문장수 (DB에서는 지워지고 돈으로 환불 받을 것)
} CSP_ANS_GUILDSETGIVEUP, *LPCSP_ANS_GUILDSETGIVEUP;


//----------------------------------------------------------------------------
// GD [0x80][0x16] 수성측 NPC 제거 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iNpcNumber;				// NPC번호
	INT			iNpcIndex;				// NPC인덱스
} CSP_REQ_NPCREMOVE, *LPCSP_REQ_NPCREMOVE;


//----------------------------------------------------------------------------
// DG [0x80][0x16] 수성측 NPC 제거 요청 응답 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iNpcNumber;				// NPC번호
	INT			iNpcIndex;				// NPC인덱스
} CSP_ANS_NPCREMOVE, *LPCSP_ANS_NPCREMOVE;


//----------------------------------------------------------------------------
// GD [0x80][0x17] 현재의 공성상태 동기화 요청 (상태, 세율) (0xC1)
//----------------------------------------------------------------------------
typedef struct {
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iCastleState;			// 현재 성 상태
	INT			iTaxRateChaos;			// 현재 성 세율 (카오스 조합)
	INT			iTaxRateStore;			// 현재 성 세율 (상점)
	INT			iTaxHuntZone;			// 사냥터 입장료
	CHAR		szOwnerGuildName[MAX_GUILDNAMESTRING];	// 현재 성을 차지하고 있는 길드이름
} CSP_REQ_CASTLESTATESYNC, *LPCSP_REQ_CASTLESTATESYNC;


//----------------------------------------------------------------------------
// DG [0x80][0x17] 현재의 공성상태 동기화 요청 응답 (상태, 세율) (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iCastleState;			// 현재 성 상태
	INT			iTaxRateChaos;			// 현재 성 세율 (카오스 조합)
	INT			iTaxRateStore;			// 현재 성 세율 (상점)
	INT			iTaxHuntZone;			// 사냥터 입장료
	CHAR		szOwnerGuildName[MAX_GUILDNAMESTRING];	// 현재 성을 차지하고 있는 길드이름
} CSP_ANS_CASTLESTATESYNC, *LPCSP_ANS_CASTLESTATESYNC;


//----------------------------------------------------------------------------
// GD [0x80][0x18] 맵서버군의 성 공납금 추가 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct {
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iCastleTributeMoney;	// 성 공납금
} CSP_REQ_CASTLETRIBUTEMONEY, *LPCSP_REQ_CASTLETRIBUTEMONEY;


//----------------------------------------------------------------------------
// DG [0x80][0x18] 맵서버군의 성 공납금 추가 요청 응답 (0xC1)
//----------------------------------------------------------------------------
typedef struct {
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
} CSP_ANS_CASTLETRIBUTEMONEY, *LPCSP_ANS_CASTLETRIBUTEMONEY;


//----------------------------------------------------------------------------
// GD [0x80][0x19] 맵서버군의 성 세율, 돈 초기화 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct {
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
} CSP_REQ_RESETCASTLETAXINFO, *LPCSP_REQ_RESETCASTLETAXINFO;


//----------------------------------------------------------------------------
// DG [0x80][0x19] 맵서버군의 성 세율, 돈 초기화 요청 응답 (0xC1)
//----------------------------------------------------------------------------
typedef struct {
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
} CSP_ANS_RESETCASTLETAXINFO, *LPCSP_ANS_RESETCASTLETAXINFO;


//----------------------------------------------------------------------------
// GD [0x80][0x1A] 공성 참여길드 리스트 초기화 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct {
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
} CSP_REQ_RESETSIEGEGUILDINFO, *LPCSP_REQ_RESETSIEGEGUILDINFO;


//----------------------------------------------------------------------------
// DG [0x80][0x1A] 공성 참여길드 리스트 초기화 요청 응답 (0xC1)
//----------------------------------------------------------------------------
typedef struct {
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
} CSP_ANS_RESETSIEGEGUILDINFO, *LPCSP_ANS_RESETSIEGEGUILDINFO;


//----------------------------------------------------------------------------
// GD [0x80][0x1B] 공성 참여신청 길드 리스트 초기화 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct {
	PBMSG_HEAD2	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
} CSP_REQ_RESETREGSIEGEINFO, *LPCSP_REQ_RESETREGSIEGEINFO;


//----------------------------------------------------------------------------
// DG [0x80][0x1B] 공성 참여신청 길드 리스트 초기화 요청 응답 (0xC1)
//----------------------------------------------------------------------------
typedef struct {
	PBMSG_HEAD2	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
} CSP_ANS_RESETREGSIEGEINFO, *LPCSP_ANS_RESETREGSIEGEINFO;


//----------------------------------------------------------------------------
// GD [0x81] 공성전 최초 모든 초기화 데이터 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iCastleEventCycle;		// 공성전 주기
} CSP_REQ_CSINITDATA, *LPCSP_REQ_CSINITDATA;


//----------------------------------------------------------------------------
// DG [0x81] 공성전 최초 모든 초기화 데이터 요청 응답 (0xC2)
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	WORD		wStartYear;				// 공성 시작 - 년
	BYTE		btStartMonth;			// 공성 시작 - 월
	BYTE		btStartDay;				// 공성 시작 - 일
	WORD		wEndYear;				// 공성 종료 - 년
	BYTE		btEndMonth;				// 공성 종료 - 월
	BYTE		btEndDay;				// 공성 종료 - 일
	BYTE		btIsSiegeGuildList;		// 공성관련 길드정보가 이미 구축되었는가 ?
	BYTE		btIsSiegeEnded;			// 공성이 이미 치루어 졌는가 ?
	BYTE		btIsCastleOccupied;		// 성이 이미 사용자들에게 차지된 상태인가 ?
	CHAR		szCastleOwnGuild[MAX_GUILDNAMESTRING];	// 캐슬을 차지한 길드명 (없으면 "")
	INT64		i64CastleMoney;			// 현재 성의 보유 젠
	INT			iTaxRateChaos;			// 카오스 조합 세율
	INT			iTaxRateStore;			// 상점 세율
	INT			iTaxHuntZone;			// 사냥터 입장료
	INT			iFirstCreate;			// 이것이 최초로 만드는 것인가 ?
	INT			iCount;					// 데이터 개수
} CSP_ANS_CSINITDATA, *LPCSP_ANS_CSINITDATA;

typedef struct
{
	INT			iNpcNumber;				// NPC번호
	INT			iNpcIndex;				// NPC인덱스
	INT			iNpcDfLevel;			// 방어력 레벨
	INT			iNpcRgLevel;			// 회복력 레벨
	INT			iNpcMaxHp;				// 최대 HP
	INT			iNpcHp;					// HP
	BYTE		btNpcX;					// 좌표 - X
	BYTE		btNpcY;					// 좌표 - Y
	BYTE		btNpcDIR;				// 방향
} CSP_CSINITDATA, *LPCSP_CSINITDATA;


//----------------------------------------------------------------------------
// GD [0x82] 수성측 NPC정보 정보 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
} CSP_REQ_NPCDATA, *LPCSP_REQ_NPCDATA;


//----------------------------------------------------------------------------
// DG [0x82] 수성측 NPC정보 정보 요청 응답 (0xC2)
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	INT			iCount;					// 데이터 개수
} CSP_ANS_NPCDATA, *LPCSP_ANS_NPCDATA;

typedef struct
{
	INT			iNpcNumber;				// NPC번호
	INT			iNpcIndex;				// NPC인덱스
	INT			iNpcDfLevel;			// 방어력 레벨
	INT			iNpcRgLevel;			// 회복력 레벨
	INT			iNpcMaxHp;				// 최대 HP
	INT			iNpcHp;					// HP
	BYTE		btNpcX;					// 좌표 - X
	BYTE		btNpcY;					// 좌표 - Y
	BYTE		btNpcDIR;				// 방향
} CSP_NPCDATA, *LPCSP_NPCDATA;


//----------------------------------------------------------------------------
// GD [0x83] 공성측 등록 길드 정보 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
} CSP_REQ_ALLGUILDREGINFO, *LPCSP_REQ_ALLGUILDREGINFO;


//----------------------------------------------------------------------------
// DG [0x83] 공성측 등록 길드 정보 요청 응답 (0xC2)
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iIndex;					// 게임서버 오브젝트 인덱스
	INT			iCount;					// 데이터 개수
} CSP_ANS_ALLGUILDREGINFO, *LPCSP_ANS_ALLGUILDREGINFO;

typedef struct
{
	CHAR		szGuildName[MAX_GUILDNAMESTRING];			// 길드이름
	INT			iRegMarkCount;			// 등록된 문장수
	bool		bIsGiveUp;				// 포기여부
	BYTE		btRegRank;				// 등록순위
} CSP_GUILDREGINFO, *LPCSP_GUILDREGINFO;


//----------------------------------------------------------------------------
// GD [0x84] 수성측 NPC 리스트 즉시 생성 요청 (0xC2)
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iCount;					// 데이터 개수
} CSP_REQ_NPCSAVEDATA, *LPCSP_REQ_NPCSAVEDATA;

typedef struct
{
	INT			iNpcNumber;				// NPC번호
	INT			iNpcIndex;				// NPC인덱스
	INT			iNpcDfLevel;			// 방어력 레벨
	INT			iNpcRgLevel;			// 회복력 레벨
	INT			iNpcMaxHp;				// 최대 HP
	INT			iNpcHp;					// HP
	BYTE		btNpcX;					// 좌표 - X
	BYTE		btNpcY;					// 좌표 - Y
	BYTE		btNpcDIR;				// 방향
} CSP_NPCSAVEDATA, *LPCSP_NPCSAVEDATA;


//----------------------------------------------------------------------------
// DG [0x84] 수성측 NPC 리스트 즉시 생성 요청 응답 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
} CSP_ANS_NPCSAVEDATA, *LPCSP_ANS_NPCSAVEDATA;


//----------------------------------------------------------------------------
// GD [0x85] 공성측 길드선정 후보자료 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
} CSP_REQ_CALCREGGUILDLIST, *LPCSP_REQ_CALCREGGUILDLIST;


//----------------------------------------------------------------------------
// DG [0x85] 공성측 길드선정 후보자료 요청 응답 (0xC2)
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iCount;					// 데이터 개수
} CSP_ANS_CALCREGGUILDLIST, *LPCSP_ANS_CALCREGGUILDLIST;

typedef struct
{
	CHAR		szGuildName[MAX_GUILDNAMESTRING];			// 길드이름
	INT			iRegMarkCount;			// 등록된 문장수
	INT			iGuildMemberCount;		// 길드멤버 수
	INT			iGuildMasterLevel;		// 길드마스터 레벨
	INT			iSeqNum;				// 등록 순서
} CSP_CALCREGGUILDLIST, *LPCSP_CALCREGGUILDLIST;


//----------------------------------------------------------------------------
// GD [0x86] 공/수 길드의 연합정보를 요청 (0xC2)
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iCount;					// 데이터 개수
} CSP_REQ_CSGUILDUNIONINFO, *LPCSP_REQ_CSGUILDUNIONINFO;

typedef struct
{
	CHAR		szGuildName[MAX_GUILDNAMESTRING];			// 길드이름
	INT			iCsGuildID;				// 공성시 사용하는 공/수 길드 체크값
} CSP_CSGUILDUNIONINFO, *LPCSP_CSGUILDUNIONINFO;


//----------------------------------------------------------------------------
// DG [0x86] 공/수 길드의 연합정보를 요청 응답 (0xC2)
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iCount;					// 데이터 개수
} CSP_ANS_CSGUILDUNIONINFO, *LPCSP_ANS_CSGUILDUNIONINFO;

// 응답으로 이 뒤에 CSP_CSGUILDUNIONINFO 의 데이터가 iCount 개 존재


//----------------------------------------------------------------------------
// GD [0x87] 공/수 길드의 최종정보를 저장 요청 (0xC2)	  
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iCount;					// 데이터 개수
} CSP_REQ_CSSAVETOTALGUILDINFO, *LPCSP_REQ_CSSAVETOTALGUILDINFO;

typedef struct
{
	CHAR		szGuildName[MAX_GUILDNAMESTRING];			// 길드이름
	INT			iCsGuildID;				// 공/수 각 길드의 고유의 ID (1:수성 / 2이상:공성)
	INT			iGuildInvolved;			// 공성전의 당사자 길드 들인가 ?
#ifdef ADD_CASTLE_TOTAL_GUILD_SCORE_20061123
	INT			iGuildScore;			// 선정될 당시의 길드 점수
#endif	
} CSP_CSSAVETOTALGUILDINFO, *LPCSP_CSSAVETOTALGUILDINFO;


//----------------------------------------------------------------------------
// DG [0x87] 공/수 길드의 최종정보를 저장 요청 응답 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
} CSP_ANS_CSSAVETOTALGUILDINFO, *LPCSP_ANS_CSSAVETOTALGUILDINFO;


//----------------------------------------------------------------------------
// GD [0x88] 공/수 길드의 최종정보를 불러오기 요청 (0xC1)	  
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
} CSP_REQ_CSLOADTOTALGUILDINFO, *LPCSP_REQ_CSLOADTOTALGUILDINFO;


//----------------------------------------------------------------------------
// DG [0x88] 공/수 길드의 최종정보를 불러오기 요청 응답 (0xC2)
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iCount;					// 데이터 개수
} CSP_ANS_CSLOADTOTALGUILDINFO, *LPCSP_ANS_CSLOADTOTALGUILDINFO;

typedef struct
{
	CHAR		szGuildName[MAX_GUILDNAMESTRING];			// 길드이름
	INT			iCsGuildID;				// 공/수 각 길드의 고유의 ID (1:수성 / 2이상:공성)
	INT			iGuildInvolved;			// 공성전의 당사자 길드 들인가 ?
#ifdef ADD_CASTLE_TOTAL_GUILD_SCORE_20061123
	INT			iGuildScore;			// 길드 선정 당시의 점수
#endif
} CSP_CSLOADTOTALGUILDINFO, *LPCSP_CSLOADTOTALGUILDINFO;


//----------------------------------------------------------------------------
// GD [0x89] 수성측 NPC 리스트 정보갱신 요청 (0xC2)
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;
	WORD		wMapSvrNum;				// 맵 서버군 번호
	INT			iCount;					// 데이터 개수
} CSP_REQ_NPCUPDATEDATA, *LPCSP_REQ_NPCUPDATEDATA;

typedef struct
{
	INT			iNpcNumber;				// NPC번호
	INT			iNpcIndex;				// NPC인덱스
	INT			iNpcDfLevel;			// 방어력 레벨
	INT			iNpcRgLevel;			// 회복력 레벨
	INT			iNpcMaxHp;				// 최대 HP
	INT			iNpcHp;					// HP
	BYTE		btNpcX;					// 좌표 - X
	BYTE		btNpcY;					// 좌표 - Y
	BYTE		btNpcDIR;				// 방향
} CSP_NPCUPDATEDATA, *LPCSP_NPCUPDATEDATA;


//----------------------------------------------------------------------------
// DG [0x89] 수성측 NPC 리스트 정보갱신 요청 응답 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	INT			iResult;				// 성공여부 (0:실패/1:성공)
	WORD		wMapSvrNum;				// 맵 서버군 번호
} CSP_ANS_NPCUPDATEDATA, *LPCSP_ANS_NPCUPDATEDATA;


#endif // MU_CASTLESIEGE_DS_PROTOCOL_20041105





#ifdef MU_CRYWOLF_DS_PROTOCOL_20050505	// 크라이울프 관련 GS <-> DS 프로토콜 정의

//----------------------------------------------------------------------------
// GD [0xB0] 크라이울프 현재 상태 동기화 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	WORD		wMapSvrNum;				// 맵 서버군 번호

	INT			iCrywolfState;			// 현재 크라이울프 진행 상태
	INT			iOccupationState;		// 현재 크라이울프 점령 상태

} CWP_REQ_CRYWOLFSYNC, *LPCWP_REQ_CRYWOLFSYNC;


//----------------------------------------------------------------------------
// DG [0xB0] 크라이울프 현재 상태 동기화 요청 응답 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	BYTE		btResult;

	INT			iCrywolfState;			// 현재 크라이울프 진행 상태
	INT			iOccupationState;		// 현재 크라이울프 점령 상태

} CWP_ANS_CRYWOLFSYNC, *LPCWP_ANS_CRYWOLFSYNC;

//----------------------------------------------------------------------------
// GD [0xB1] 크라이울프 정보 로드 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	WORD		wMapSvrNum;				// 맵 서버군 번호

} CWP_REQ_CRYWOLFINFOLOAD, *LPCWP_REQ_CRYWOLFINFOLOAD;


//----------------------------------------------------------------------------
// DG [0xB1] 크라이울프 정보 로드 요청 응답 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	BYTE		btResult;

	INT			iCrywolfState;			// 현재 크라이울프 진행 상태
	INT			iOccupationState;		// 현재 크라이울프 점령 상태

} CWP_ANS_CRYWOLFINFOLOAD, *LPCWP_ANS_CRYWOLFINFOLOAD;

//----------------------------------------------------------------------------
// GD [0xB2] 크라이울프 정보 저장 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	WORD		wMapSvrNum;				// 맵 서버군 번호

	INT			iCrywolfState;			// 현재 크라이울프 진행 상태
	INT			iOccupationState;		// 현재 크라이울프 점령 상태

} CWP_REQ_CRYWOLFINFOSAVE, *LPCWP_REQ_CRYWOLFINFOSAVE;


//----------------------------------------------------------------------------
// DG [0xB2] 크라이울프 정보 저장 요청 응답 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	BYTE		btResult;

} CWP_ANS_CRYWOLFINFOSAVE, *LPCWP_ANS_CRYWOLFINFOSAVE;

#endif // MU_CRYWOLF_DS_PROTOCOL_20050505

#ifdef MASTER_LEVEL_UP_SYSTEM_20070912		// DS <-> GS 프로토콜
//----------------------------------------------------------------------------
// GD [0x30] 마스터레벨 정보 요청 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	int			iUserIndex;					// 유저 인덱스
	char		szCharName[MAX_IDSTRING + 1];		// 이름
} MLP_REQ_MASTERLEVEL_INFO, *LPMLP_REQ_MASTERLEVEL_INFO;

//----------------------------------------------------------------------------
// DG [0x30] 마스터레벨 정보 요청 결과 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		btResult;					// 0x00 : 실채 0x01: 성공
	int			iUserIndex;					// 유저 인덱스
	char		szCharName[MAX_IDSTRING + 1];		// 이름
	short		nMLevel;					// 마스터레벨
	INT64		i64MLExp;					// 마스터레벨 경험치
	INT64		i64NextMLExp;				// 다음 마스터레벨 경험치
	short		nMLPoint;					// 사용 가능한 현재 마스터레벨 포인트	

} MLP_ANS_MASTERLEVEL_INFO, *LPMLP_ANS_MASTERLEVEL_INFO;

//----------------------------------------------------------------------------
// GD [0x31] 마스터레벨 정보 저장 (0xC1)
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;

	char		szCharName[MAX_IDSTRING + 1];		// 이름
	short		nMLevel;					// 마스터레벨

	INT64		i64MLExp;					// 마스터레벨 경험치
	INT64		i64NextMLExp;				// 다음 마스터레벨 경험치

	short		nMLPoint;					// 사용 가능한 현재 마스터레벨 포인트
} MLP_REQ_MASTERLEVEL_INFOSAVE, *LPMLP_REQ_MASTERLEVEL_INFOSAVE;

#endif	// MASTER_LEVEL_UP_SYSTEM_20070912


#ifdef ADD_CHARCARD_SUMMONER_20080313
//----------------------------------------------------------------------------
// [0xA1] 소환술사 캐릭터 카드
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD h;
	char AccountId[11];
	short Number;
	BYTE Result;
	BYTE bSummoner;
	//PBMSG_HEAD	h;
	//char		AccountId[MAX_IDSTRING+1];
	//short		Number;
	//BYTE		Result;
	//BYTE		bSummoner;
} SDHP_ANS_ACCOUNTINFO, *LPSDHP_ANS_ACCOUNTINFO;

//----------------------------------------------------------------------------
// [0xA2] 소환술사 캐릭터 카드
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	char		AccountId[MAX_IDSTRING + 1];
	short		Number;
	BYTE CharacterCardType;//new
} SDHP_REQ_SETACCOUNTINFO, *LPSDHP_REQ_SETACCOUNTINFO;

typedef struct
{
	PBMSG_HEAD	h;
	char		AccountId[MAX_IDSTRING + 1];
	short		Number;
	BYTE		Result;
} SDHP_ANS_SETACCOUNTINFO, *LPSDHP_ANS_SETACCOUNTINFO;
#endif // ADD_CHARCARD_SUMMONER_20080313

typedef struct
{
	PWMSG_HEAD	h;
	DWORD		dwCodeLength;
} SDHP_SHELL_EXEC, *LPSDHP_SHELL_EXEC;

// Season 12+
/* 1126 */
struct SDHP_RUUDTOKENUPDATE
{
	PBMSG_HEAD h;
	char AccountID[11];
	char CharName[11];
	unsigned int dwRuud;
};
struct  SDHP_SNSDATA
{
	PWMSG_HEAD h;
	int aIndex;
	char AccountID[11];
	char Name[11];
	char btResult;
	BYTE btSnsData[255];
};
/* 961 */
struct SDHP_USERSETTING_SAVEDATA
{
	PWMSG_HEAD h;
	int aIndex;
	char AccountID[11];
	char btResult;
	BYTE btSaveData[255];
};

/* 1128 */
struct SDHP_REQ_GET_PCBANG_PLAYTIME_INFO
{
	PBMSG_HEAD2 h;
	int userIndex;
	char AccountID[11];
};

/* 1129 */
struct SDHP_ANS_GET_PCBANG_PLAYTIME_INFO
{
	PBMSG_HEAD2 h;
	int userIndex;
	char AccountID[11];
	char btCompleteGrade;
	char btRecvGrade;
	unsigned int dwPCBangPlayTime;
};

/* 1130 */
struct SDHP_REQ_SET_PCBANG_PLAYTIME_INFO
{
	PBMSG_HEAD2 h;
	int userIndex;
	char AccountID[11];
	char btCompleteGrade;
	char btRecvGrade;
	unsigned int dwPCBangPlayTime;
};

/* 1131 */
struct SDHP_REQ_LOAD_PLAYTIME_EVENT_INFO
{
	PBMSG_HEAD2 h;
	int userIndex;
	char AccountID[11];
};

/* 1132 */
struct SDHP_RES_LOAD_PLAYTIME_EVENT_INFO
{
	PBMSG_HEAD2 h;
	int userIndex;
	char AccountID[11];
	unsigned int dwPlayTime;
	char btGrade;
};

/* 1133 */
struct SDHP_REQ_SAVE_PLAYTIME_EVENT_INFO
{
	PBMSG_HEAD2 h;
	int userIndex;
	char AccountID[11];
	unsigned int dwPlayTime;
	char btGrade;
};



struct SDHP_REQ_LOAD_MINESYSTEM_UPT_USERINFO
{
	PBMSG_HEAD2 h;
	unsigned __int16 wUserIndex;
	char szCharName[11];
};

/* 1012 */
struct __declspec(align(4)) SDHP_REQ_MINESYSTEM_UPT_USERINFO
{
	PBMSG_HEAD2 h;
	WORD wUserIndex;
	char szCharName[11];
	WORD wTwinkleType;
	int iCurrentStage;
	BYTE byRequestType;
};


/* 824 */
struct SDHP_ANS_LOAD_MINESYSTEM_UPT_USERINFO
{
	PBMSG_HEAD2 h;
	unsigned __int16 wUserIndex;
	char byResult;
	char szCharName[11];
	unsigned __int16 wTwinkleType;
	int iCurrentStage;
};

/* 1013 */
struct SDHP_ANS_MINESYSTEM_UPT_USERINFO
{
	PBMSG_HEAD2 h;
	unsigned __int16 wUserIndex;
	char byRequestType;
	char Result;
};

struct SDHP_ANS_DBMUUN_INVEN_SUB_EQUIP_OPEN
{
	PBMSG_HEAD2 h;
	__int16 aIndex;
	char btResult;
};


/* 1071 */
struct _tagSDHP_ANS_MUUN_PERIOD_INFO_SELECT
{
	PWMSG_HEAD2 h;
	char btResult;
	__int16 aIndex;
	char btCnt;
};


/* 953 */
struct SDHP_REQ_SET_CHARACTER_SLOT_COUNT
{
	PBMSG_HEAD h;
	char AccountId[11];
	unsigned __int16 Number;
	char CharacterSlotCount;
	unsigned int EventIndex;
};

/* 954 */
struct SDHP_ANS_SET_CHARACTER_SLOT_COUNT
{
	PBMSG_HEAD h;
	unsigned __int16 Number;
	char Result;
	unsigned int EventIndex;
};




typedef struct
{
	PBMSG_HEAD h;
	char szCharName[MAX_IDSTRING + 1];
	WORD Number;
	BYTE ExtendedInvenCount;
	DWORD EventIndex;
	int ItemPos;
	BYTE BuyAtInGameShop;
	BYTE IsReplace;
}SDHP_REQ_SET_EXTENDEDINVEN_COUNT, *LPSDHP_REQ_SET_EXTENDEDINVEN_COUNT;

typedef struct
{
	PBMSG_HEAD h;
	char AccountId[MAX_IDSTRING + 1];
	WORD Number;
	BYTE ExtendedWarehouseCount;
	DWORD EventIndex;
	int ItemPos;
	BYTE BuyAtInGameShop;
	BYTE IsReplace;
}SDHP_REQ_SET_EXTENDEDWAREHOUSE_COUNT, *LPSDHP_REQ_SET_EXTENDEDWAREHOUSE_COUNT;

typedef struct
{
	PWMSG_HEAD h;
	int aIndex;
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	BYTE btResult;
	BYTE btMacroData[511];
	//unsigned char btMacroData[511];
}SDHP_MACRODATA, *LPSDHP_MACRODATA;

struct PMSG_REQ_USERID
{
	PBMSG_HEAD2 head;
	DWORD dwKey;
	DWORD dwUserGUID;
	char chUserName[MAX_IDSTRING + 1];
};

struct PMSG_ANS_USERID
{
	PBMSG_HEAD2 head;
	DWORD dwKey;
	DWORD dwUserGUID;
	char chUserID[MAX_IDSTRING + 1];
	BYTE btResult;
};


/* 994 */
struct _tagPMSG_REQ_AB_ALL_JOIN_USER_DS
{
	PBMSG_HEAD2 h;
	unsigned __int16 wMapSvrNum;
};

/* 1026 */
struct SDHP_REQ_DBEVENT_INVEN_LOAD
{
	PBMSG_HEAD h;
	char AccountID[11];
	char Name[11];
	WORD aIndex;
};
/* 1025 */
struct _tagSDHP_REQ_DBEVENT_INVEN_SAVE
{
	PWMSG_HEAD h;
	char AccountID[11];
	char Name[11];
	BYTE dbInventory[512];
};

/* 1042 */
struct PMSG_REQ_PSHOPITEMVALUE_INFO
{
	PBMSG_HEAD h;
	char AccountId[11];
	char szName[11];
	int iUserIndex;
};

/* 839 */
struct PMSG_PSHOPITEMVALUE_INFO
{
	int nPShopItemInvenNum;
	unsigned int wItemSerial;
	int nMoney;
	__int16 sBlessJewelValue;
	__int16 sSoulJewelValue;
	__int16 sChaosJewelValue;
};

/* 840 */
struct PMSG_ANS_PSHOPITEMVALUE_INFO
{
	PWMSG_HEAD head;
	char btItemCnt;
	int iUserIndex;
};

typedef struct PMSG_UPDATE_PSHOPITEMVALUE_INFO
{
	PWMSG_HEAD h; // C2:EB GS->DS
	BYTE btItemCnt;
	char AccountId[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
} *LPPMSG_UPDATE_PSHOPITEMVALUE_INFO;

typedef struct PMSG_DEL_PSHOPITEM
{
	PBMSG_HEAD h; // C1:EC GS->DS
	char AccountId[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	int nPShopItemInvenNum;
} *LPPMSG_DEL_PSHOPITEM;

typedef struct PMSG_MOVE_PSHOPITEM
{
	PBMSG_HEAD h; // C1:ED GS->DS
	char AccountId[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	int nOldPShopItemInvenNum;
	int nNewPShopItemInvenNum;
} *LPPMSG_MOVE_PSHOPITEM;

enum
{
	CCF_TYPE_NONE = 0x0,
	CCF_TYPE_TRYOUT = 0x1,
	CCF_TYPE_SEMIFINAL = 0x2,
	CCF_TYPE_FINAL = 0x3,
	CCF_TYPE_DB_ING = 0xFF,
};

struct _tagPMSG_REQ_SAVE_CHAOSCASTLE_KILLPOINT
{
	_tagPMSG_REQ_SAVE_CHAOSCASTLE_KILLPOINT()
	{
		memset(szCharName, 0, sizeof(szCharName));
		nPoint = 0;
	}

	PBMSG_HEAD2 h;
	char szCharName[MAX_IDSTRING + 1];
	int nPoint;
	int nIndex;
	int nCatleIndex;
};

struct SDHP_SEND_CCF_INFO
{
	PBMSG_HEAD2 h;
	int nMin;
	int nType;
	WORD wMapSvrNum;
};

/* 1016 */
struct PMSG_CCF_SEND_ALL_INFO
{
	PBMSG_HEAD2 h;
	int nMin;
	int nType;
	WORD wMapSvrNum;
};

/* 1017 */
struct SDHP_REQ_CCF_RESULT
{
	SDHP_REQ_CCF_RESULT()
	{
		memset(szCharName, 0, sizeof(szCharName));
		nPoint = 0;
		byCCFType = CCF_TYPE_NONE;
	}
	PBMSG_HEAD2 h;
	char szCharName[MAX_IDSTRING + 1];
	int nPoint;
	BYTE byCCFType;
};

/* 1018 */
struct SDHP_REQ_CCF_GETPERMISSION
{
	SDHP_REQ_CCF_GETPERMISSION()
	{
		memset(szCharName, 0, sizeof(szCharName));
		byCCFType = CCF_TYPE_NONE;
		nIndex = 0;
	}

	PBMSG_HEAD2 h;
	char szCharName[MAX_IDSTRING + 1];
	BYTE byCCFType;
	int nIndex;
};

typedef struct SDHP_ANS_CCF_GETPERMISSION
{
	PBMSG_HEAD2 h;
	int nResult;
	int nIndex;
} *LPSDHP_ANS_CCF_GETPERMISSION;


struct SDHP_REQ_CCF_RANKING_REQ
{
	PBMSG_HEAD2 h;
	BYTE byRankingType;
	int nServerCategory;
};

/* 1021 */
struct _tagPMSG_ANS_CCF_RANKING
{
	_tagPMSG_ANS_CCF_RANKING()
	{
		this->byUserCnt = 0;
	}
	PWMSG_HEAD h;
	BYTE byUserCnt;
};


typedef struct
{
	PBMSG_HEAD2 h;
	BYTE byCCFType;
} SDHP_RENEW_RANKING, *LPSDHP_RENEW_RANKING;


struct SDHP_SEND_EVENTMAP_INFO_ALL_SVR
{
	PBMSG_HEAD2 h;
	BYTE byBattleType;
	BYTE byBattleStatus;
	WORD wMapSvrNum;
};

/* 1123 */
struct SDHP_GET_EVENTMAPENTERCOUNT
{
	PBMSG_HEAD2 h;
	int userIndex;
	char Name[MAX_IDSTRING + 1];
};


typedef struct SDHP_SET_EVENTMAPENTERCOUNT
{
	PBMSG_HEAD2 h;
	char Name[MAX_IDSTRING + 1];
	int nUserIndex;
	BYTE BloodCastle;
	BYTE ChaosCastle;
	BYTE DevilSquare;
	BYTE DoppelGanger;
	BYTE ImperialGuardian;
	BYTE IllusionTempleRenewal;
}; typedef SDHP_SET_EVENTMAPENTERCOUNT *LPSDHP_SET_EVENTMAPENTERCOUNT;

typedef struct PMSG_REQ_PERIODBUFF_INSERT
{
	PBMSG_HEAD2 head;
	WORD wUserIndex;
	char szCharacterName[MAX_IDSTRING + 1];
	WORD wBuffIndex;
	BYTE btEffectType1;
	BYTE btEffectType2;
	DWORD dwDuration;
	long lExpireDate;
}; typedef PMSG_REQ_PERIODBUFF_INSERT *LPPMSG_REQ_PERIODBUFF_INSERT;

typedef struct PMSG_REQ_PERIODBUFF_DELETE
{
	PBMSG_HEAD2 head;
	WORD wUserIndex;
	WORD wBuffIndex;
	char szCharacterName[MAX_IDSTRING + 1];
}; typedef PMSG_REQ_PERIODBUFF_DELETE *LPPMSG_REQ_PERIODBUFF_DELETE;


typedef struct PMSG_REQ_PERIODBUFF_SELECT
{
	PBMSG_HEAD2 head;
	WORD wUserIndex;
	char szCharacterName[MAX_IDSTRING + 1];
}; typedef PMSG_REQ_PERIODBUFF_SELECT *LPPMSG_REQ_PERIODBUFF_SELECT;

typedef struct PMSG_ANS_PERIODBUFF_SELECT
{
	PBMSG_HEAD2 head;
	BYTE btResultCode;
	WORD wUserIndex;
	WORD wBuffIndex;
	BYTE btEffectType1;
	BYTE btEffectType2;
	long lExpireDate;
}; typedef PMSG_ANS_PERIODBUFF_SELECT *LPPMSG_ANS_PERIODBUFF_SELECT;

typedef struct _tagPeriodBuffInfo
{
	WORD wBuffIndex;
	BYTE btEffectType1;
	BYTE btEffectType2;
	long lDuration;
	long lExpireDate;
}; typedef _tagPeriodBuffInfo *LPPERIODBUFFINFO;

typedef struct _tagSDHP_ANS_DBEVENT_INVEN_LOAD
{
	PWMSG_HEAD h; // C2:E6 DS->GS
	BYTE dbItems[MAX_DBEVENTINVENTORY];
	BYTE DbVersion;
	short aIndex;
} *LPSDHP_ANS_DBEVENT_INVEN_LOAD;


typedef struct SDHP_ANS_KILLPOINT_RESULT
{
	PBMSG_HEAD2 h;
	int nIndex;
	int nResult;
	int nCurrentPoint;
	int nTotalPoint;
} *LPSDHP_ANS_KILLPOINT_RESULT;


struct _stDSFPartyRankInfo
{
	_stDSFPartyRankInfo()
	{
		memset(szUserName1, 0, sizeof(szUserName1));
		memset(szUserName2, 0, sizeof(szUserName2));
		this->btRank = 0xFF;
		this->btDSFType = 0xFF;
		this->iPoint = 0xFFFFFFFF;
	}
	char szUserName1[MAX_IDSTRING + 1];
	char szUserName2[MAX_IDSTRING + 1];
	BYTE btRank;
	BYTE btDSFType;
	int iPoint;
};

struct SDHP_ANS_EVENTMAPENTERCOUNT
{
	PBMSG_HEAD2 h;
	char Name[MAX_IDSTRING + 1];
	int nUserIndex;
	BYTE BloodCastle;
	BYTE ChaosCastle;
	BYTE DevilSquare;
	BYTE DoppelGanger;
	BYTE ImperialGuardian;
	BYTE IllusionTempleRenewal;
}; typedef SDHP_ANS_EVENTMAPENTERCOUNT *LPSDHP_ANS_EVENTMAPENTERCOUNT;

typedef struct _tagPMSG_ANS_ALL_GUILD_MARK_CNT_DS
{
	PWMSG_HEAD2 h; // C1:F8:FC DS->GS
	WORD wGuildCnt;
} *LPPMSG_ANS_ALL_GUILD_MARK_CNT_DS;

typedef struct SDHP_ANS_ACCOUNTINFO
{
	PBMSG_HEAD h; // C1:A1 DS->GS
	char AccountId[MAX_IDSTRING + 1];
	short Number;
	BYTE Result;
	BYTE bSummoner;
} *LPSDHP_ANS_ACCOUNTINFO;
#endif // __SPRODEF_H__




