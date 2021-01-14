﻿#ifndef __SPRODEF_H__
#define __SPRODEF_H__

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

typedef struct
{
	PBMSG_HEAD	h;
	BYTE	Result;
} SDHP_DEFAULT_RESULT, *LPSDHP_DEFAULT_RESULT;

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
	WORD		Number;	// 게임 서버 유저번호
	int			IsUnityBattleFiledServer;//s12
} SDHP_GETCHARLIST, *LPSDHP_GETCHARLIST;
//struct SDHP_GETCHARLIST_RECV 
//{
//	PBMSG_HEAD header;    // C1:01    
//	char Account[10];  
//	WORD Index;  
//	int IsUnityBattleFiledServer;
//};


//----------------------------------------------------------------------------
// 캐릭터 리스트 카운트  (2바이트 크기를 사용)
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD header;    // C1:01   
	WORD Index;
	BYTE Count;
	int DbNumber;
	BYTE GenerableClass;
	char AccountId[11];
	BYTE MoveCnt;
	BYTE CharacterSlotCount;
	BYTE ExtendedWarehouseCount;
	//	short		Number;
	//	BYTE		Count;
	//	int			DbNumber;
	//	BYTE		GenerableClass;		// 마검사를 만들수 있는 계정인지..
	//	char		AccountId[MAX_IDSTRING+1];
	//#ifdef CHARACTER_MOVE_20040810
	//	BYTE		MoveCnt;
	//#endif
	//	BYTE		CharacterSlotCount;
	//	BYTE		ExtendedWarehouseCount;
} SDHP_CHARLISTCOUNT, *LPSDHP_CHARLISTCOUNT;

struct SDHP_CHARLISTCOUNT_SEND 
{
	PWMSG_HEAD header;    // C1:01  
	WORD Index;  
	BYTE Count;  
	int DbNumber;  
	BYTE GenerableClass;  
	char AccountId[11]; 
	BYTE MoveCnt;  
	BYTE CharacterSlotCount;  
	BYTE ExtendedWarehouseCount;
};

//----------------------------------------------------------------------------
// [0x02] 계정 인증 요청시 캐릭터 정보(카운터 만큼 반복됨)
// [0xF3][0x00]
//----------------------------------------------------------------------------
typedef struct
{
	BYTE Index;
	char Name[10];
	char UnityBFOfRealName[10];
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
	PBMSG_HEAD h;
	char x;
	char y;
	unsigned __int16 MapNumber;
	__int16 Type;
	char Level;
	char Dur;
	char Op1;
	char Op2;
	char Op3;
	char NewOption;
	int aIndex;
	__int16 lootindex;
	char SetOption;
	char SocketSlotCount;
	int lDuration;
	unsigned int dwEventIndex;
	char SocketOption[5];
	char MainAttribute;
	/*PBMSG_HEAD	h;
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
	BYTE		SocketSlotCount;
	long		lDuration;
	DWORD		dwEventIndex;
	BYTE		SocketOption[5];
	BYTE		MainAttribute;*/
} SDHP_ITEMCREATE, *LPSDHP_ITEMCREATE;

//----------------------------------------------------------------------------
// [0x52] 아이템 번호를 부여받는다.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD h;
	char x;
	char y;
	char MapNumber;
	unsigned int m_Number;
	__int16 Type;
	char Level;
	char Dur;
	char Op1;
	char Op2;
	char Op3;
	char NewOption;
	int aIndex;
	__int16 lootindex;
	char SetOption;
	char SocketSlotCount;
	int lDuration;
	unsigned int dwEventIndex;
	char SocketOption[5];
	char MainAttribute;
	/*PBMSG_HEAD	h;
	BYTE x;
	BYTE y;
	BYTE MapNumber;
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
	BYTE		SocketOption[5];
	BYTE		MainAttribute;*/
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
	BYTE		ChatWindow;

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

	BYTE		ChatWindow;

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
	char		Notice[61];
} SDHP_NOTICE, *LPSDHP_NOTICE;

// 0x41 유저 공지
typedef struct
{
	PBMSG_HEAD	h;
	char		szId[10];
	char		Notice[61];
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


typedef struct CSP_REQ_CASTLEDATA
{
	PBMSG_HEAD2 h; // C1:80:00 GS->DS
	WORD wMapSvrNum;
	int iCastleEventCycle;
} *LPCSP_REQ_CASTLEDATA;

typedef struct CSP_ANS_CASTLEDATA
{
	PBMSG_HEAD2 h; // C1:80:00 DS->GS
	int iResult;
	WORD wMapSvrNum;
	WORD wStartYear;
	BYTE btStartMonth;
	BYTE btStartDay;
	WORD wEndYear;
	BYTE btEndMonth;
	BYTE btEndDay;
	BYTE btIsSiegeGuildList;
	BYTE btIsSiegeEnded;
	BYTE btIsCastleOccupied;
	char szCastleOwnGuild[MAX_GUILDNAMESTRING];
	__int64 i64CastleMoney;
	int iTaxRateChaos;
	int iTaxRateStore;
	int iTaxHuntZone;
	int iFirstCreate;
} *LPCSP_ANS_CASTLEDATA;

typedef struct CSP_REQ_OWNERGUILDMASTER
{
	PBMSG_HEAD2 h; // C1:80:01 GS->DS
	WORD wMapSvrNum;
	int iIndex;
} *LPCSP_REQ_OWNERGUILDMASTER;

typedef struct CSP_ANS_OWNERGUILDMASTER
{
	PBMSG_HEAD2 h; // C1:80:01 DS->GS
	int iResult;
	WORD wMapSvrNum;
	int iIndex;
	char szCastleOwnGuild[MAX_GUILDNAMESTRING];
	char szCastleOwnGuildMaster[MAX_IDSTRING];
} *LPCSP_ANS_OWNERGUILDMASTER;

typedef struct CSP_REQ_NPCBUY
{
	PBMSG_HEAD2 h; // C1:80:03 GS->DS
	WORD wMapSvrNum;
	int iIndex;
	int iNpcNumber;
	int iNpcIndex;
	int iNpcDfLevel;
	int iNpcRgLevel;
	int iNpcMaxHp;
	int iNpcHp;
	BYTE btNpcX;
	BYTE btNpcY;
	BYTE btNpcDIR;
	int iBuyCost;
} *LPCSP_REQ_NPCBUY;

typedef struct CSP_ANS_NPCBUY
{
	PBMSG_HEAD2 h; // C1:80:03 DS->GS
	int iResult;
	WORD wMapSvrNum;
	int iIndex;
	int iNpcNumber;
	int iNpcIndex;
	int iBuyCost;
} *LPCSP_ANS_NPCBUY;

typedef struct CSP_REQ_NPCREPAIR
{
	PBMSG_HEAD2 h; // C1:80:04 GS->DS
	WORD wMapSvrNum;
	int iIndex;
	int iNpcNumber;
	int iNpcIndex;
	int iRepairCost;
} *LPCSP_REQ_NPCREPAIR;

typedef struct CSP_ANS_NPCREPAIR
{
	PBMSG_HEAD2 h; // C1:80:04 DS->GS
	int iResult;
	WORD wMapSvrNum;
	int iIndex;
	int iNpcNumber;
	int iNpcIndex;
	int iNpcMaxHp;
	int iNpcHp;
	int iRepairCost;
} *LPCSP_ANS_NPCREPAIR;

typedef struct CSP_REQ_NPCUPGRADE
{
	PBMSG_HEAD2 h; // C1:80:05 GS->DS
	WORD wMapSvrNum;
	int iIndex;
	int iNpcNumber;
	int iNpcIndex;
	int iNpcUpType;
	int iNpcUpValue;
	int iNpcUpIndex;
} *LPCSP_REQ_NPCUPGRADE;

typedef struct CSP_ANS_NPCUPGRADE
{
	PBMSG_HEAD2 h; // C1:80:05 DS->GS
	int iResult;
	WORD wMapSvrNum;
	int iIndex;
	int iNpcNumber;
	int iNpcIndex;
	int iNpcUpType;
	int iNpcUpValue;
	int iNpcUpIndex;
} *LPCSP_ANS_NPCUPGRADE;

typedef struct CSP_REQ_TAXINFO
{
	PBMSG_HEAD2 h; // C1:80:06 GS->DS
	WORD wMapSvrNum;
	int iIndex;
} *LPCSP_REQ_TAXINFO;

typedef struct CSP_ANS_TAXINFO
{
	PBMSG_HEAD2 h; // C1:80:06 DS->GS
	int iResult;
	WORD wMapSvrNum;
	int iIndex;
	__int64 i64CastleMoney;
	int iTaxRateChaos;
	int iTaxRateStore;
	int iTaxHuntZone;
} *LPCSP_ANS_TAXINFO;

typedef struct CSP_REQ_TAXRATECHANGE
{
	PBMSG_HEAD2 h; // C1:80:07 GS->DS
	WORD wMapSvrNum;
	int iIndex;
	int iTaxKind;
	int iTaxRate;
} *LPCSP_REQ_TAXRATECHANGE;

typedef struct CSP_ANS_TAXRATECHANGE
{
	PBMSG_HEAD2 h; // C1:80:07 DS->GS
	int iResult;
	WORD wMapSvrNum;
	int iIndex;
	int iTaxKind;
	int iTaxRate;
} *LPCSP_ANS_TAXRATECHANGE;


typedef struct CSP_REQ_MONEYCHANGE
{
	PBMSG_HEAD2 h; // C1:80:08 GS->DS
	WORD wMapSvrNum;
	int iIndex;
	int iMoneyChanged;
} *LPCSP_REQ_MONEYCHANGE;

typedef struct CSP_ANS_MONEYCHANGE
{
	PBMSG_HEAD2 h; // C1:80:08 DS->GS
	int iResult;
	WORD wMapSvrNum;
	int iIndex;
	int iMoneyChanged;
	__int64 i64CastleMoney;
} *LPCSP_ANS_MONEYCHANGE;

typedef struct CSP_REQ_SDEDCHANGE
{
	PBMSG_HEAD2 h; // C1:80:09 GS->DS
	WORD wMapSvrNum;
	int iIndex;
	WORD wStartYear;
	BYTE btStartMonth;
	BYTE btStartDay;
	WORD wEndYear;
	BYTE btEndMonth;
	BYTE btEndDay;
} *LPCSP_REQ_SDEDCHANGE;

typedef struct CSP_ANS_SDEDCHANGE
{
	PBMSG_HEAD2 h; // C1:80:09 DS->GS
	int iResult;
	WORD wMapSvrNum;
	int iIndex;
	WORD wStartYear;
	BYTE btStartMonth;
	BYTE btStartDay;
	WORD wEndYear;
	BYTE btEndMonth;
	BYTE btEndDay;
} *LPCSP_ANS_SDEDCHANGE;

typedef struct CSP_REQ_GUILDREGINFO
{
	PBMSG_HEAD2 h; // C1:80:0A GS->DS
	WORD wMapSvrNum;
	int iIndex;
	char szGuildName[MAX_GUILDNAMESTRING];
} *LPCSP_REQ_GUILDREGINFO;

typedef struct CSP_ANS_GUILDREGINFO
{
	PBMSG_HEAD2 h; // C1:80:0A DS->GS
	int iResult;
	WORD wMapSvrNum;
	int iIndex;
	char szGuildName[MAX_GUILDNAMESTRING];
	int iRegMarkCount;
	bool bIsGiveUp;
	BYTE btRegRank;
} *LPCSP_ANS_GUILDREGINFO;

typedef struct CSP_REQ_SIEGEENDCHANGE
{
	PBMSG_HEAD2 h; // C1:80:0B GS->DS
	WORD wMapSvrNum;
	BOOL bIsSiegeEnded;
} *LPCSP_REQ_SIEGEENDCHANGE;

typedef struct CSP_ANS_SIEGEENDCHANGE
{
	PBMSG_HEAD2 h; // C1:80:0B DS->GS
	int iResult;
	WORD wMapSvrNum;
	BOOL bIsSiegeEnded;
} *LPCSP_ANS_SIEGEENDCHANGE;

typedef struct CSP_REQ_CASTLEOWNERCHANGE
{
	PBMSG_HEAD2 h; // C1:80:0C GS->DS
	WORD wMapSvrNum;
	BOOL bIsCastleOccupied;
	char szOwnerGuildName[MAX_GUILDNAMESTRING];
} *LPCSP_REQ_CASTLEOWNERCHANGE;

typedef struct CSP_ANS_CASTLEOWNERCHANGE
{
	PBMSG_HEAD2 h; // C1:80:0C DS->GS
	int iResult;
	WORD wMapSvrNum;
	BOOL bIsCastleOccupied;
	char szOwnerGuildName[MAX_GUILDNAMESTRING];
} *LPCSP_ANS_CASTLEOWNERCHANGE;

typedef struct CSP_REQ_REGATTACKGUILD
{
	PBMSG_HEAD2 h; // C1:80:0D GS->DS
	WORD wMapSvrNum;
	int iIndex;
	char szEnemyGuildName[MAX_GUILDNAMESTRING];
} *LPCSP_REQ_REGATTACKGUILD;

typedef struct CSP_ANS_REGATTACKGUILD
{
	PBMSG_HEAD2 h; // C1:80:0D DS->GS
	int iResult;
	WORD wMapSvrNum;
	int iIndex;
	char szEnemyGuildName[MAX_GUILDNAMESTRING];
} *LPCSP_ANS_REGATTACKGUILD;

typedef struct CSP_REQ_CASTLESIEGEEND
{
	PBMSG_HEAD2 h; // C1:80:0E GS->DS
	WORD wMapSvrNum;
} *LPCSP_REQ_CASTLESIEGEEND;

typedef struct CSP_ANS_CASTLESIEGEEND
{
	PBMSG_HEAD2 h; // C1:80:0E DS->GS
	int iResult;
	WORD wMapSvrNum;
} *LPCSP_ANS_CASTLESIEGEEND;

typedef struct CSP_REQ_MAPSVRMULTICAST
{
	PBMSG_HEAD2 h; // C1:80:0F GS->DS
	WORD wMapSvrNum;
	char szMsgText[128];
} *LPCSP_REQ_MAPSVRMULTICAST;

typedef struct CSP_ANS_MAPSVRMULTICAST
{
	PBMSG_HEAD2 h; // C1:80:0F DS->GS
	WORD wMapSvrNum;
	char szMsgText[128];
} *LPCSP_ANS_MAPSVRMULTICAST;

typedef struct CSP_REQ_GUILDREGMARK
{
	PBMSG_HEAD2 h; // C1:80:10 GS->DS
	WORD wMapSvrNum;
	int iIndex;
	char szGuildName[MAX_GUILDNAMESTRING];
	int iItemPos;
} *LPCSP_REQ_GUILDREGMARK;

typedef struct CSP_ANS_GUILDREGMARK
{
	PBMSG_HEAD2	h; // C1:80:10 DS->GS
	int iResult;
	WORD wMapSvrNum;
	int iIndex;
	char szGuildName[MAX_GUILDNAMESTRING];
	int iItemPos;
	int iRegMarkCount;
} *LPCSP_ANS_GUILDREGMARK;

typedef struct CSP_REQ_GUILDRESETMARK
{
	PBMSG_HEAD2 h; // C1:80:11 GS->DS
	WORD wMapSvrNum;
	int iIndex;
	char szGuildName[MAX_GUILDNAMESTRING];
} *LPCSP_REQ_GUILDRESETMARK;

typedef struct CSP_ANS_GUILDRESETMARK
{
	PBMSG_HEAD2 h; // C1:80:11 DS->GS
	int iResult;
	WORD wMapSvrNum;
	int iIndex;
	char szGuildName[MAX_GUILDNAMESTRING];
	int iRegMarkCount;
} *LPCSP_ANS_GUILDRESETMARK;

typedef struct CSP_REQ_GUILDSETGIVEUP
{
	PBMSG_HEAD2 h; // C1:80:12 GS->DS
	WORD wMapSvrNum;
	int iIndex;
	char szGuildName[MAX_GUILDNAMESTRING];
	BOOL bIsGiveUp;
} *LPCSP_REQ_GUILDSETGIVEUP;

typedef struct CSP_ANS_GUILDSETGIVEUP
{
	PBMSG_HEAD2 h; // C1:80:12 DS->GS
	int iResult;
	WORD wMapSvrNum;
	int iIndex;
	char szGuildName[MAX_GUILDNAMESTRING];
	BOOL bIsGiveUp;
	int iRegMarkCount;
} *LPCSP_ANS_GUILDSETGIVEUP;

typedef struct CSP_REQ_NPCREMOVE
{
	PBMSG_HEAD2 h; // C1:80:16 GS->DS
	WORD wMapSvrNum;
	int iNpcNumber;
	int iNpcIndex;
} *LPCSP_REQ_NPCREMOVE;

typedef struct CSP_ANS_NPCREMOVE
{
	PBMSG_HEAD2 h; // C1:80:16 DS->GS
	int iResult;
	WORD wMapSvrNum;
	int iNpcNumber;
	int iNpcIndex;
} *LPCSP_ANS_NPCREMOVE;

typedef struct CSP_REQ_CASTLESTATESYNC
{
	PBMSG_HEAD2 h; // C1:80:17 GS->DS
	WORD wMapSvrNum;
	int iCastleState;
	int iTaxRateChaos;
	int iTaxRateStore;
	int iTaxHuntZone;
	char szOwnerGuildName[MAX_GUILDNAMESTRING];
} *LPCSP_REQ_CASTLESTATESYNC;

typedef struct CSP_ANS_CASTLESTATESYNC
{
	PBMSG_HEAD2 h; // C1:80:17 DS->GS
	WORD wMapSvrNum;
	int iCastleState;
	int iTaxRateChaos;
	int iTaxRateStore;
	int iTaxHuntZone;
	char szOwnerGuildName[MAX_GUILDNAMESTRING];
} *LPCSP_ANS_CASTLESTATESYNC;

typedef struct CSP_REQ_CASTLETRIBUTEMONEY
{
	PBMSG_HEAD2 h; // C1:80:18 GS->DS
	WORD wMapSvrNum;
	int iCastleTributeMoney;
} *LPCSP_REQ_CASTLETRIBUTEMONEY;

typedef struct CSP_ANS_CASTLETRIBUTEMONEY
{
	PBMSG_HEAD2 h; // C1:80:18 DS->GS
	int iResult;
	WORD wMapSvrNum;
} *LPCSP_ANS_CASTLETRIBUTEMONEY;

typedef struct CSP_REQ_RESETCASTLETAXINFO
{
	PBMSG_HEAD2 h; // C1:80:19 GS->DS
	WORD wMapSvrNum;
} *LPCSP_REQ_RESETCASTLETAXINFO;

typedef struct CSP_ANS_RESETCASTLETAXINFO
{
	PBMSG_HEAD2 h; // C1:80:19 DS->GS
	int iResult;
	WORD wMapSvrNum;
} *LPCSP_ANS_RESETCASTLETAXINFO;

typedef struct CSP_REQ_RESETSIEGEGUILDINFO
{
	PBMSG_HEAD2 h; // C1:80:1A GS->DS
	WORD wMapSvrNum;
} *LPCSP_REQ_RESETSIEGEGUILDINFO;

typedef struct CSP_ANS_RESETSIEGEGUILDINFO
{
	PBMSG_HEAD2 h; // C1:80:1A DS->GS
	int iResult;
	WORD wMapSvrNum;
} *LPCSP_ANS_RESETSIEGEGUILDINFO;

typedef struct CSP_REQ_RESETREGSIEGEINFO
{
	PBMSG_HEAD2 h; // C1:80:1B GS->DS
	WORD wMapSvrNum;
} *LPCSP_REQ_RESETREGSIEGEINFO;

typedef struct CSP_ANS_RESETREGSIEGEINFO
{
	PBMSG_HEAD2 h; // C1:80:1B DS->GS
	int iResult;
	WORD wMapSvrNum;
} *LPCSP_ANS_RESETREGSIEGEINFO;

typedef struct CSP_REQ_CSINITDATA
{
	PBMSG_HEAD h; // C1:81 GS->DS
	WORD wMapSvrNum;
	int iCastleEventCycle;
} *LPCSP_REQ_CSINITDATA;

typedef struct CSP_ANS_CSINITDATA
{
	PWMSG_HEAD h; // C2:81 DS->GS
	int iResult;
	WORD wMapSvrNum;
	WORD wStartYear;
	BYTE btStartMonth;
	BYTE btStartDay;
	WORD wEndYear;
	BYTE btEndMonth;
	BYTE btEndDay;
	BYTE btIsSiegeGuildList;
	BYTE btIsSiegeEnded;
	BYTE btIsCastleOccupied;
	BYTE szCastleOwnGuild[MAX_GUILDNAMESTRING];
	__int64 i64CastleMoney;
	int iTaxRateChaos;
	int iTaxRateStore;
	int iTaxHuntZone;
	int iFirstCreate;
	int iCount;
} *LPCSP_ANS_CSINITDATA;

typedef struct CSP_CSINITDATA
{
	int iNpcNumber;
	int iNpcIndex;
	int iNpcDfLevel;
	int iNpcRgLevel;
	int iNpcMaxHp;
	int iNpcHp;
	BYTE btNpcX;
	BYTE btNpcY;
	BYTE btNpcDIR;
} *LPCSP_CSINITDATA;

typedef struct CSP_REQ_NPCDATA
{
	PBMSG_HEAD h; // C1:82 GS->DS
	WORD wMapSvrNum;
	int iIndex;
} *LPCSP_REQ_NPCDATA;

typedef struct CSP_ANS_NPCDATA
{
	PWMSG_HEAD h; // C2:82 DS->GS
	int iResult;
	WORD wMapSvrNum;
	int iIndex;
	int iCount;
} *LPCSP_ANS_NPCDATA;

typedef struct CSP_NPCDATA
{
	int iNpcNumber;
	int iNpcIndex;
	int iNpcDfLevel;
	int iNpcRgLevel;
	int iNpcMaxHp;
	int iNpcHp;
	BYTE btNpcX;
	BYTE btNpcY;
	BYTE btNpcDIR;
} *LPCSP_NPCDATA;

typedef struct CSP_REQ_ALLGUILDREGINFO
{
	PBMSG_HEAD h; // C1:83 GS->DS
	WORD wMapSvrNum;
	int iIndex;
} *LPCSP_REQ_ALLGUILDREGINFO;

typedef struct CSP_ANS_ALLGUILDREGINFO
{
	PWMSG_HEAD h; // C2:83 DS->GS
	int iResult;
	WORD wMapSvrNum;
	int iIndex;
	int iCount;
} *LPCSP_ANS_ALLGUILDREGINFO;

typedef struct CSP_GUILDREGINFO
{
	char szGuildName[MAX_GUILDNAMESTRING];
	int iRegMarkCount;
	bool bIsGiveUp;
	BYTE btRegRank;
} *LPCSP_GUILDREGINFO;

typedef struct CSP_REQ_NPCSAVEDATA
{
	PWMSG_HEAD h; // C2:84 GS->DS
	WORD wMapSvrNum;
	int iCount;
} *LPCSP_REQ_NPCSAVEDATA;

typedef struct CSP_NPCSAVEDATA
{
	int	iNpcNumber;
	int	iNpcIndex;
	int	iNpcDfLevel;
	int	iNpcRgLevel;
	int	iNpcMaxHp;
	int	iNpcHp;
	BYTE btNpcX;
	BYTE btNpcY;
	BYTE btNpcDIR;
} *LPCSP_NPCSAVEDATA;

typedef struct CSP_ANS_NPCSAVEDATA
{
	PBMSG_HEAD h; // C1:84 DS->GS
	int iResult;
	WORD wMapSvrNum;
} *LPCSP_ANS_NPCSAVEDATA;

typedef struct CSP_REQ_CALCREGGUILDLIST
{
	PBMSG_HEAD h; // C1:85 GS->DS
	WORD wMapSvrNum;
} *LPCSP_REQ_CALCREGGUILDLIST;

typedef struct CSP_ANS_CALCREGGUILDLIST
{
	PWMSG_HEAD h; // C2:85 DS->GS
	int iResult;
	WORD wMapSvrNum;
	int iCount;
} *LPCSP_ANS_CALCREGGUILDLIST;

typedef struct CSP_CALCREGGUILDLIST
{
	char szGuildName[MAX_GUILDNAMESTRING];
	int iRegMarkCount;
	int iGuildMemberCount;
	int iGuildMasterLevel;
	int iSeqNum;
} *LPCSP_CALCREGGUILDLIST;

typedef struct CSP_REQ_CSGUILDUNIONINFO
{
	PWMSG_HEAD h; // C2:86 GS->DS
	WORD wMapSvrNum;
	int iCount;
} *LPCSP_REQ_CSGUILDUNIONINFO;

typedef struct CSP_CSGUILDUNIONINFO
{
	char szGuildName[MAX_GUILDNAMESTRING];
	int iCsGuildID;
} *LPCSP_CSGUILDUNIONINFO;

typedef struct CSP_ANS_CSGUILDUNIONINFO
{
	PWMSG_HEAD h; // C2:86 DS->GS
	int iResult;
	WORD wMapSvrNum;
	int iCount;
} *LPCSP_ANS_CSGUILDUNIONINFO;

typedef struct CSP_REQ_CSSAVETOTALGUILDINFO
{
	PWMSG_HEAD h; // C2:87 GS->DS
	WORD wMapSvrNum;
	int iCount;
} *LPCSP_REQ_CSSAVETOTALGUILDINFO;

typedef struct CSP_CSSAVETOTALGUILDINFO
{
	char szGuildName[MAX_GUILDNAMESTRING];
	int iCsGuildID;
	int iGuildInvolved;
	int iGuildScore;
} *LPCSP_CSSAVETOTALGUILDINFO;

typedef struct CSP_ANS_CSSAVETOTALGUILDINFO
{
	PBMSG_HEAD h; // C1:87 DS->GS
	int iResult;
	WORD wMapSvrNum;
} *LPCSP_ANS_CSSAVETOTALGUILDINFO;

typedef struct CSP_REQ_CSLOADTOTALGUILDINFO
{
	PBMSG_HEAD h; // C1:88 GS->DS
	WORD wMapSvrNum;
} *LPCSP_REQ_CSLOADTOTALGUILDINFO;

typedef struct CSP_ANS_CSLOADTOTALGUILDINFO
{
	PWMSG_HEAD h; // C2:88 DS->GS
	int iResult;
	WORD wMapSvrNum;
	int iCount;
} *LPCSP_ANS_CSLOADTOTALGUILDINFO;

typedef struct CSP_CSLOADTOTALGUILDINFO
{
	char szGuildName[MAX_GUILDNAMESTRING];
	int iCsGuildID;
	int iGuildInvolved;
	int iGuildScore;
} *LPCSP_CSLOADTOTALGUILDINFO;

typedef struct CSP_REQ_NPCUPDATEDATA
{
	PWMSG_HEAD h; // C2:89 GS->DS
	WORD wMapSvrNum;
	int iCount;
} *LPCSP_REQ_NPCUPDATEDATA;

typedef struct CSP_NPCUPDATEDATA
{
	int iNpcNumber;
	int iNpcIndex;
	int iNpcDfLevel;
	int iNpcRgLevel;
	int iNpcMaxHp;
	int iNpcHp;
	BYTE btNpcX;
	BYTE btNpcY;
	BYTE btNpcDIR;
} *LPCSP_NPCUPDATEDATA;

typedef struct CSP_ANS_NPCUPDATEDATA
{
	PBMSG_HEAD h; // C1:89 DS->GS
	int iResult;
	WORD wMapSvrNum;
} *LPCSP_ANS_NPCUPDATEDATA;

typedef struct CWP_REQ_CRYWOLFSYNC
{
	PBMSG_HEAD h; // C1:B0 GS->DS
	WORD wMapSvrNum;
	int iCrywolfState;
	int iOccupationState;
} *LPCWP_REQ_CRYWOLFSYNC;

typedef struct CWP_ANS_CRYWOLFSYNC
{
	PBMSG_HEAD h; // C1:B0 DS->GS
	BYTE btResult;
	int iCrywolfState;
	int iOccupationState;
} *LPCWP_ANS_CRYWOLFSYNC;

typedef struct CWP_REQ_CRYWOLFINFOLOAD
{
	PBMSG_HEAD h; // C1:B1 GS->DS
	WORD wMapSvrNum;
} *LPCWP_REQ_CRYWOLFINFOLOAD;

typedef struct CWP_ANS_CRYWOLFINFOLOAD
{
	PBMSG_HEAD h; // C1:B1 DS->GS
	BYTE btResult;
	int iCrywolfState;
	int iOccupationState;
} *LPCWP_ANS_CRYWOLFINFOLOAD;

typedef struct CWP_REQ_CRYWOLFINFOSAVE
{
	PBMSG_HEAD h; // C1:B2 GS->DS
	WORD wMapSvrNum;
	int iCrywolfState;
	int iOccupationState;
} *LPCWP_REQ_CRYWOLFINFOSAVE;

typedef struct CWP_ANS_CRYWOLFINFOSAVE
{
	PBMSG_HEAD h; // C1:B2 DS->GS
	BYTE btResult;
} *LPCWP_ANS_CRYWOLFINFOSAVE;

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

/* 1108 */
struct _tagSDHP_REQ_EVENT_MONSTER_KILL_INFO
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char AccountID[11];
	char CharName[11];
};
struct _tagSDHP_ANS_EVENT_MONSTER_KILL_INFO
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	__int16 MonsterIndex1;
	unsigned __int16 MonsterLevel1;
	int KillCount1;
	__int16 MonsterIndex2;
	unsigned __int16 MonsterLevel2;
	int KillCount2;
	__int16 MonsterIndex3;
	unsigned __int16 MonsterLevel3;
	int KillCount3;
	__int16 MonsterIndex4;
	unsigned __int16 MonsterLevel4;
	int KillCount4;
	__int16 MonsterIndex5;
	unsigned __int16 MonsterLevel5;
	int KillCount5;
	__int64 DamageScore;
	char btResult;
};

/* 676 */
struct _tagSDHP_REQ_EVENT_MONSTER_KILL_INFO_SAVE
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char AccountID[11];
	char CharName[11];
	__int16 MonsterIndex1;
	unsigned __int16 MonsterLevel1;
	int KillCount1;
	__int16 MonsterIndex2;
	unsigned __int16 MonsterLevel2;
	int KillCount2;
	__int16 MonsterIndex3;
	unsigned __int16 MonsterLevel3;
	int KillCount3;
	__int16 MonsterIndex4;
	unsigned __int16 MonsterLevel4;
	int KillCount4;
	__int16 MonsterIndex5;
	unsigned __int16 MonsterLevel5;
	int KillCount5;
	__int64 DamageScore;
};

typedef struct _ST_BLOCK_CHATTING_USER
{
	_ST_BLOCK_CHATTING_USER()
	{
		bIsUsed = false;
		btSlotNum = 0;
		memset(szCharName, 0, sizeof(szCharName));
	}

	bool bIsUsed;
	BYTE btSlotNum;
	char szCharName[MAX_IDSTRING + 1];
};

typedef struct SDHP_REQ_BLOCK_CHAT_USER_INFO
{
	PBMSG_HEAD h; // C1:6E:00 GS->DS
	int iUserIndex;
	char szCharName[MAX_IDSTRING + 1];
} *LPSDHP_REQ_BLOCK_CHAT_USER_INFO;

typedef struct SDHP_ANS_BLOCK_CHAT_USER_INFO
{
	PWMSG_HEAD2 h; // C2:6E:00 DS->GS
	int nUserIndex;
	char szCharName[MAX_IDSTRING + 1];
	BYTE btUserCnt;
	_ST_BLOCK_CHATTING_USER BlockCharList[20];
} *LPSDHP_ANS_BLOCK_CHAT_USER_INFO;

typedef struct SDHP_REQ_ADD_BLOCK_CHAT_USER_INFO
{
	PBMSG_HEAD2 h; // C1:6E:01 GS->DS
	int nUserIndex;
	char szCharName[MAX_IDSTRING + 1];
	_ST_BLOCK_CHATTING_USER szBlockChar;
} *LPSDHP_REQ_ADD_BLOCK_CHAT_USER_INFO;

typedef struct SDHP_REQ_DEL_BLOCK_CHAT_USER_INFO
{
	PBMSG_HEAD2 h; // C1:6E:02 GS->DS
	int nUserIndex;
	char szCharName[MAX_IDSTRING + 1];
	_ST_BLOCK_CHATTING_USER szBlockChar;
} *LPSDHP_REQ_DEL_BLOCK_CHAT_USER_INFO;

struct _SDHP_REQ_RESTORE_ITEM_LIST_SAVE
{
	PWMSG_HEAD2 h;
	int userIndex;
	char AccountID[11];
	char Name[11];
	char dbRestoreItemData[150];
};

/* 1110 */
struct _SDHP_REQ_RESTORE_ITEM_LIST
{
	PWMSG_HEAD2 h;
	int userIndex;
	char AccountID[11];
	char Name[11];
};

/* 6306 */
struct SDHP_REQ_LABYRINTH_INFO
{
	PWMSG_HEAD2 h;
	char szAccountID[11];
	char szName[11];
	int nUserIndex;
};

/* 6307 */
struct SDHP_REQ_LABYRINTH_MISSION_DELETE
{
	PWMSG_HEAD2 h;
	char szAccountID[11];
	char szName[11];
	int nUserIndex;
};

/* 703 */
struct _SDHP_ANS_RESTORE_ITEM_LIST
{
	PWMSG_HEAD2 h;
	int userIndex;
	char result;
	char dbRestoreItemData[150];
	char dbVersion;
};

/* 6304 */
struct SDHP_REQ_LABYRINTH_INFO_UPDATE
{
	PWMSG_HEAD2 h;
	char szAccountID[11];
	char szName[11];
	int nUserIndex;
	char btDimensionLevel;
	unsigned __int16 wConfigNum;
	char btCurrentZone;
	char btVisitedCnt;
	char btVisitedList[200];
	__int64 nEntireExp;
	__int64 nEntireMonKillCnt;
};

/* 6305 */
struct  SDHP_REQ_LABYRINTH_MISSION_UPDATE
{
	PWMSG_HEAD2 h;
	char szAccountID[11];
	char szName[11];
	int nUserIndex;
	char btZoneNumber;
	char btMissionType;
	int nMissionValue;
	int nAcquisionValue;
	char btMissionState;
	char btIsMainMission;
	char btMainMissionOrder;
	int nRewardItemType;
	int nRewardItemIndex;
	int nRewardValue;
	char btRewardCheckState;
};


/* 6309 */
struct  SDHP_ANS_LABYRINTH_INFO
{
	PWMSG_HEAD2 h;
	int nUserIndex;
	char btResult;
	char btDimensionLevel;
	unsigned __int16 wConfigNum;
	char btCurrentZone;
	int nLeftTime;
	char btVisitedCnt;
	BYTE btVisitedList[200];
	char btClearState;
	char btMissionCount;
};

/* 6310 */
struct MISSION_INFO
{
	char btZoneNumber;
	char btMissionType;
	int nMissionValue;
	int nAcquisionValue;
	char btMissionState;
	char btIsMainMission;
	char btMainMissionOrder;
	int nRewardItemType;
	int nRewardItemIndex;
	int nRewardValue;
	char btRewardCheckState;
};

/* 6311 */
struct SDHP_REQ_LABYRINTH_INFO_SAVE
{
	PWMSG_HEAD2 h;
	char szAccountID[11];
	char szName[11];
	int nUserIndex;
	char btDimensionLevel;
	unsigned __int16 wConfigNum;
	char btCurrentZone;
	char btVisitedCnt;
	char btVisitedList[200];
	__int64 nEntireExp;
	__int64 nEntireMonKillCnt;
	int nClearCnt;
	char btClearState;
	char btMissionCount;
};

/* 6312 */
struct SDHP_REQ_LABYRINTH_REWARD_COMPLETE
{
	PWMSG_HEAD2 h;
	char szAccountID[11];
	char szName[11];
	int nUserIndex;
	char btIsMainMission;
	char btRewardCheckState;
};

/* 6313 */
struct SDHP_REQ_LABYRINTH_CLEAR_LOG_SET_SAVE
{
	PWMSG_HEAD2 h;
	char szAccountID[11];
	char szName[11];
	int nUserIndex;
	int nDimensionLevel;
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

/* 1109 */
struct SDHP_ANS_EVENT_MONSTER_KILL_INFO_SAVE
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char btResult;
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
/* 1065 */
struct _tagSDHP_REQ_DBMUUN_INVEN_SAVE
{
	PWMSG_HEAD h;
	char AccountID[11];
	char Name[11];
	BYTE dbInventory[1632];
};

/* 1066 */
struct SDHP_REQ_DBMUUN_INVEN_LOAD
{
	PBMSG_HEAD h;
	char AccountID[11];
	char Name[11];
	__int16 aIndex;
};

/* 1067 */
struct _tagSDHP_ANS_DBMUUN_INVEN_LOAD
{
	_tagSDHP_ANS_DBMUUN_INVEN_LOAD()
	{
		memset(this->dbItems, 0xFF, 1632);
		this->DbVersion = 0;
		this->SubEquip = 0;
		this->aIndex = 0;
	}
	PWMSG_HEAD h;
	BYTE dbItems[1632];
	char DbVersion;
	char SubEquip;
	short aIndex;
};
/* 1068 */
struct SDHP_REQ_DBMUUN_INVEN_SUB_EQUIP_OPEN
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Name[11];
	short aIndex;
};

/* 1070 */
struct _tagSDHP_REQ_MUUN_PERIOD_INFO_SELECT
{
	PBMSG_HEAD2 h;
	char Name[11];
	WORD aIndex;
};
/* 1072 */
struct _tagSDHP_REQ_MUUN_PERIOD_INFO_INSERT
{
	PBMSG_HEAD2 h;
	__int16 aIndex;
	char Name[11];
	unsigned __int16 wItemType;
	unsigned int dwSerial;
	unsigned int dwItemDuration;
	int lItemExpireDate;
};

/* 1073 */
struct _tagSDHP_REQ_MUUN_PERIOD_INFO_UPDATE
{
	PBMSG_HEAD2 h;
	char Name[11];
	__int16 aIndex;
	unsigned __int16 wItemType;
	DWORD dwSerial;
	BYTE btUsedInfo;
};
/* 666 */
struct _stMuunConditionInfoList
{
	_stMuunConditionInfoList()
	{
		this->btConditionType = -1;
		this->btSlotIndex = -1;
		this->wValue = 0;
	}
	BYTE btConditionType;
	BYTE btSlotIndex;
	WORD wValue;
};

struct _tagSDHP_REQ_MUUN_CONDITION_INFO_SAVE
{
	PBMSG_HEAD2 h;
	char Name[11];
	_stMuunConditionInfoList MuunConditionInfoList[2];
};
/* 1075 */
struct _tagSDHP_REQ_MUUN_CONDITION_INFO_LOAD
{
	PBMSG_HEAD2 h;
	char Name[11];
	short aIndex;
};

/* 1077 */
struct _tagSDHP_REQ_MUUN_CONDITION_INFO_DEL
{
	PBMSG_HEAD2 h;
	char Name[11];
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

/* 1076 */
struct _tagSDHP_ANS_MUUN_CONDITION_INFO_LOAD
{
	PBMSG_HEAD2 h;
	short aIndex;
	_stMuunConditionInfoList MuunConditionInfoList[2];
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

/* 1134 */
struct SDHP_REQ_HUNTING_RECORD_INFO
{
	PBMSG_HEAD2 h;
	char AccountId[11];
	char szName[11];
	int iUserIndex;
	char btMapIndex;
	char btCallType;
	char btAnotherUser;
};

/* 1135 */
struct SDHP_REQ_HUNTING_RECORD_INFO_USER_OPEN
{
	PBMSG_HEAD2 h;
	char AccountId[11];
	char szName[11];
	int iUserIndex;
};

/* 1136 */
struct SDHP_REQ_HUNTING_RECORD_INFO_CURRENT
{
	PBMSG_HEAD2 h;
	char AccountId[11];
	char szName[11];
	int iUserIndex;
	char btMapIndex;
	int iYear;
	char btMonth;
	char btDay;
	char btCallType;
};

/* 1137 */
struct SDHP_REQ_DELETE_HUNTING_RECORD_INFO
{
	PBMSG_HEAD2 h;
	char AccountId[11];
	char szName[11];
	int iUserIndex;
	char btMapIndex;
	int iYear;
	char btMonth;
	char btDay;
};

/* 764 */
struct SDHP_REQ_HUNTING_RECORD_INFO_USER_OPEN_SAVE
{
	PBMSG_HEAD2 h;
	char AccountId[11];
	char szName[11];
	int iUserIndex;
	char btOpen;
};
/* 762 */
struct SDHP_REQ_HUNTING_RECORD_INFO_SAVE
{
	PWMSG_HEAD2 h;
	char btListCnt;
	char AccountId[11];
	char szName[11];
};

/* 761 */
struct SDHP_ANS_HUNTING_RECORD_COUNT
{
	PWMSG_HEAD2 head;
	char btResult;
	char btListCnt;
	char btMapIndex;
	char btCallType;
	char btAnotherUser;
	int iUserIndex;
};

/* 760 */
struct HUNTING_RECORD_INFO
{
	char btMapIndex;
	int iYear;
	char btMonth;
	char btDay;
	int iCurrentLevel;
	int iHuntingAccrueSecond;
	__int64 i64NormalAccrueDamage;
	__int64 i64PentagramAccrueDamage;
	int iHealAccrueValue;
	int iMonsterKillCount;
	__int64 i64AccrueExp;
	int iClass;
	int iMaxNormalDamage;
	int iMinNormalDamage;
	int iMaxPentagramDamage;
	int iMinPentagramDamage;
	int iGetNormalAccrueDamage;
	int iGetPentagramAccrueDamage;
};

/* 763 */
struct SDHP_ANS_HUNTING_RECORD_INFO_USER_OPEN
{
	PBMSG_HEAD2 h;
	char btResult;
	int iUserIndex;
	char btOpen;
};

/* 765 */
struct SDHP_ANS_HUNTING_RECORD_INFO_CURRENT
{
	PWMSG_HEAD2 h;
	int iUserIndex;
	char btCallType;
	char btListCnt;
	char btMapIndex;
	int iYear;
	char btMonth;
	char btDay;
	int iCurrentLevel;
	int iHuntingAccrueSecond;
	__int64 i64NormalAccrueDamage;
	__int64 i64PentagramAccrueDamage;
	int iHealAccrueValue;
	int iMonsterKillCount;
	__int64 i64AccrueExp;
	int iClass;
	int iMaxNormalDamage;
	int iMinNormalDamage;
	int iMaxPentagramDamage;
	int iMinPentagramDamage;
	int iGetNormalAccrueDamage;
	int iGetPentagramAccrueDamage;
};
/* 796 */
struct _PMSG_QUESTEXP_INFO
{
	PWMSG_HEAD h;
	char btQuestCnt;
	char szCharName[11];
};
typedef _PMSG_QUESTEXP_INFO *LPPMSG_QUESTEXP_INFO;
/*  227 */
#pragma pack(1)
typedef struct _QUESTEXP_INFO
{
	_QUESTEXP_INFO::_QUESTEXP_INFO();

	DWORD dwQuestIndexID;
	WORD wProgState;
	BYTE btAskIndex[5];
	BYTE btAskValue[5];
	BYTE btAskState[5];
	long lStartDate;
	long lEndDate;
}_QUESTEXP_INFO, *LP_QUESTEXP_INFO;
#pragma pack()

/* 798 */
struct __unaligned PMSG_ANS_QUESTEXP_INFO
{
	PWMSG_HEAD head;
char btQuestCnt;
int iUserIndex;
};

/* 956 */
struct SDHP_ANS_SET_EXTENDEDINVEN_COUNT
{
	PBMSG_HEAD h;
	WORD Number;
	char Result;
	BYTE ExtendedInvenCount;
	DWORD EventIndex;
	int ItemPos;
	BYTE BuyAtInGameShop;
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
	unsigned char btResult;
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
struct SDHP_ANS_SET_EXTENDEDWAREHOUSE_COUNT
{
	PBMSG_HEAD h;
	WORD Number;
	BYTE Result;
	BYTE ExtendedWarehouseCount;
	DWORD EventIndex;
	int ItemPos;
	BYTE BuyAtInGameShop;
	//BYTE IsReplace;
};


/* 805 */
struct PMSG_ANS_PENTAGRAMJEWEL
{
	PWMSG_HEAD head;
	BYTE btJewelCnt;
	int iUserIndex;
	int iAnsType;
};

/* 804 */
struct PENTAGRAMJEWEL_INFO
{
	BYTE btJewelPos;
	BYTE btJewelIndex;
	BYTE btMainAttribute;
	BYTE btItemType;
	WORD wItemIndex;
	BYTE btLevel;
	BYTE btRank1OptionNum;
	BYTE btRank1Level;
	BYTE btRank2OptionNum;
	BYTE btRank2Level;
	BYTE btRank3OptionNum;
	BYTE btRank3Level;
	BYTE btRank4OptionNum;
	BYTE btRank4Level;
	BYTE btRank5OptionNum;
	BYTE btRank5Level;
};

/* 806 */
struct PMSG_PENTAGRAMJEWEL_INFO
{
	PWMSG_HEAD h;
	BYTE btJewelCnt;
	BYTE btJewelPos;
	int iUserGuid;
	char AccountId[11];
	char szName[11];
};

/* 807 */
struct PMSG_DEL_PENTAGRAMJEWEL
{
	PWMSG_HEAD h;
	int iUserGuid;
	char AccountId[11];
	char szName[11];
	BYTE btJewelPos;
	BYTE btJewelIndex;
};

/* 808 */
struct PMSG_INSERT_PENTAGRAMJEWEL
{
	PBMSG_HEAD h;
	int iUserGuid;
	BYTE AccountId[11];
	BYTE szName[11];
	BYTE btJewelPos;
	BYTE btJewelIndex;
	BYTE btItemType;
	WORD iItemIndex;
	BYTE btMainAttribute;
	BYTE btLevel;
	BYTE btRank1OptionNum;
	BYTE btRank1Level;
	BYTE btRank2OptionNum;
	BYTE btRank2Level;
	BYTE btRank3OptionNum;
	BYTE btRank3Level;
	BYTE btRank4OptionNum;
	BYTE btRank4Level;
	BYTE btRank5OptionNum;
	BYTE btRank5Level;
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
/* 1028 */
struct _tagPMSG_REQ_MURUMMY_SELECT_DS
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Name[11];
	WORD aIndex;
};
/* 831 */
struct _tagMuRummyCardInfoDS
{
	_tagMuRummyCardInfoDS()
	{
		this->btColor = -1;
		this->btNumber = -1;
		this->btSlotNum = -1;
		this->btSeq = -1;
		this->btStatus = -1;
	}
	BYTE btColor;
	BYTE btNumber;
	BYTE btSlotNum;
	BYTE btSeq;
	BYTE btStatus;
};

/* 832 */
struct _tagMuRummyCardUpdateDS
{
	_tagMuRummyCardUpdateDS()
	{
		this->btSlotNum = -1;
		this->btSeq = -1;
		this->btStatus = -1;
	}

	BYTE btSlotNum;
	BYTE btSeq;
	BYTE btStatus;
};

/* 1029 */
struct _tagPMSG_ANS_MURUMMY_SELECT_DS
{
	PBMSG_HEAD2 h;
	WORD aIndex;
	WORD wScore;
	BYTE btResult;
	BYTE btGameType;
	BYTE btSpecialCardDeckCnt;
	_tagMuRummyCardInfoDS stMuRummyCardInfoDS[27];
};

/* 1030 */
struct _tagPMSG_REQ_MURUMMY_INSERT_DS
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Name[11];
	WORD aIndex;
	BYTE btGameType;
	BYTE btSpecialCardDeckCnt;
	_tagMuRummyCardInfoDS stMuRummyCardInfoDS[27];
};

/* 1031 */
struct _tagPMSG_REQ_MURUMMY_SCORE_UPDATE_DS
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Name[11];
	WORD wScore;
	BYTE btGameType;
	BYTE btSpecialCardDeckCnt;
	BYTE btMatchType;
	_tagMuRummyCardUpdateDS stCardUpdateDS[4];
};

/* 1032 */
struct _tagPMSG_REQ_MURUMMY_UPDATE_DS
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Name[11];
	BYTE btSlotNum;
	BYTE btStatus;
	BYTE btSequence;
};

/* 1033 */
struct _tagPMSG_REQ_MURUMMY_DELETE_DS
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Name[11];
};

/* 1034 */
struct _tagPMSG_REQ_MURUMMY_SLOTUPDATE_DS
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Name[11];
	_tagMuRummyCardUpdateDS stCardUpdateDS;
};

/* 1035 */
struct _tagPMSG_REQ_MURUMMY_INFO_UPDATE_DS
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Name[11];
	WORD wScore;
	BYTE btGameType;
	BYTE btSpecialCardCnt;
	_tagMuRummyCardUpdateDS stMuRummyCardUpdateDS[27];
};

/* 1036 */
struct _tagPMSG_REQ_MURUMMY_LOG_INSERT_DS
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Name[11];
	WORD wScore;
};

/* 1037 */
struct _tagPMSG_REQ_BOMB_HUNT_SELECT_DS
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Name[11];
	unsigned __int16 aIndex;
};

/* 1038 */
struct _tagPMSG_ANS_BOMB_HUNT_SELECT_DS
{
	PBMSG_HEAD2 h;
	unsigned __int16 aIndex;
	char btResult;
	unsigned __int16 wScore;
	char btGameState;
	char szTileState[49];
};

/* 1039 */
struct _tagPMSG_REQ_BOMB_HUNT_INSERT_DS
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Name[11];
	unsigned __int16 aIndex;
	unsigned __int16 wScore;
	char btGameState;
	char szTileState[49];
};

/* 1040 */
struct _tagPMSG_REQ_BOMB_HUNT_DELETE_DS
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Name[11];
	unsigned __int16 aIndex;
};

/* 1041 */
struct _tagPMSG_REQ_BOMB_HUNT_LOG_INSERT_DS
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Name[11];
	unsigned __int16 wScore;
	char btClear;
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

/* 841 */
struct PMSG_UPDATE_PSHOPITEMVALUE_INFO
{
	PWMSG_HEAD h;
	char btItemCnt;
	char AccountId[11];
	char szName[11];
};

/* 842 */
struct PMSG_DEL_PSHOPITEM
{
	PBMSG_HEAD h;
	char AccountId[11];
	char szName[11];
	int nPShopItemInvenNum;
};

/* 843 */
struct PMSG_MOVE_PSHOPITEM
{
	PBMSG_HEAD h;
	char AccountId[11];
	char szName[11];
	int nOldPShopItemInvenNum;
	int nNewPShopItemInvenNum;
};

/* 1112 */
struct PMSG_NOTICE
{
	PBMSG_HEAD h;
	char type;
	char btCount;
	unsigned __int16 wDelay;
	unsigned int dwColor;
	char btSpeed;
	char Notice[256];
};

/* 1113 */
struct _tagCHAOS_CASTLE_NOTICE
{
	PBMSG_HEAD2 h;
	char btState;
	PMSG_NOTICE pNotice;
};

/* 1114 */
struct _tagREQCHAOS_CASTLE_USER_GS
{
	PBMSG_HEAD2 h;
	int userIndex;
	char AccountID[11];
	char Name[11];
	bool bPCBangFree;
	char btEnterLevel;
};

/* 1116 */
struct _tagANSCHAOS_CASTLE_USER_GS
{
	PBMSG_HEAD2 h;
	int serverIndex;
	int userIndex;
	char AccountID[11];
	char Name[11];
	bool bPCBangFree;
	char btEnterLevel;
	char btCount;
	unsigned __int16 wRemainTime;
};


/* 1118 */
struct _tagREQGETSPECIALIZEDSERVERINFO
{
	PBMSG_HEAD2 h;
	int userIndex;
	char btJoinResult;
	char AccountID[11];
};

/* 1119 */
struct _tagANSGETSPECIALIZEDSERVERINFO
{
	PBMSG_HEAD2 h;
	int userIndex;
	char btJoinResult;
	char AccountID[11];
	unsigned int dwPlayTime_Normal;
	unsigned int dwPlayTime_PCRoom;
	unsigned int dwCloseDateTime;
};


/* 1120 */
struct _tagREQSETSPECIALIZEDSERVERINFO
{
	PBMSG_HEAD2 h;
	int userIndex;
	char AccountID[11];
	unsigned int dwPlayTime_Normal;
	unsigned int dwPlayTime_PCRoom;
	unsigned int dwCloseDateTime;
};

/* 1121 */
struct _tagREQSETRUUDTOKENLOG
{
	PBMSG_HEAD2 h;
	int userIndex;
	char AccountID[11];
	char Name[11];
	unsigned int dwRuudTotal;
	unsigned int dwRuudValue;
	char byFlag;
};

/* 811 */
struct _tagPMSG_REQ_JEWEL_UPGRADE_INFO_INSERT_DS
{
	PBMSG_HEAD h;
	char AccountID[11];
	char Name[11];
	__int16 iJewelType;
	__int16 iJewelIndex;
	__int16 iUpgradeType;
	__int16 iSuccess;
};

/* 1043 */
struct SDHP_REQ_SAVE_ITL_GUILDPOINT
{
	PBMSG_HEAD2 h;
	char GuildName[MAX_GUILDNAMESTRING + 1];
	int nType;
	char byWin;
	char byLose;
	char byOccupiedCnt;
	char byEnterCnt;
};

/* 1044 */
struct SDHP_REQ_SAVE_ITL_GUILDCOUNT
{
	PBMSG_HEAD2 h;
	char GuildName[MAX_GUILDNAMESTRING + 1];
	char byCount;
};

/* 1045 */
struct SDHP_REQ_SAVE_ITL_USERPOINT
{
	PBMSG_HEAD2 h;
	char UserName[11];
	char GName[MAX_GUILDNAMESTRING + 1];
	int nOccupiedCount;
	int nKillP;
	int nInvalidationCount;
	int Type;
	int EnterCount;
	int Win;
};

/* 1046 */
struct _tagPMSG_REQ_ITL_GUILDCOUNTREQ
{
	PBMSG_HEAD2 h;
	char GuildName[MAX_GUILDNAMESTRING + 1];
	int nUserIndex;
	unsigned __int16 wMapSverNum;
};

/* 1047 */
struct _tagPMSG_ANS_ITL_GUILDCOUNTANS
{
	PBMSG_HEAD2 h;
	int nUserIndex;
	char byCount;
};

/* 1048 */
struct _tagPMSG_ANS_ITL_RANKING
{
	PWMSG_HEAD2 h;
	char byGuildCnt;
};

/* 1049 */
struct _tagPMSG_ANS_ITL_GUILDCNT
{
	PWMSG_HEAD2 h;
	char byGuildCnt;
};

/* 1050 */
struct _tagPMSG_REQ_LEAGUERANK_RENEW
{
	PBMSG_HEAD2 h;
	char byITLType;
};

/* 1051 */
struct _tagPMSG_REQ_GUILDRANK_GET
{
	PBMSG_HEAD2 h;
};

/* 1052 */
struct PMSG_REQ_ITL_TOURNAMENT
{
	PBMSG_HEAD2 h;
	char byITLType;
};

/* 1053 */
struct PMSG_REQ_ITL_RENEW_REWARD
{
	PBMSG_HEAD2 h;
	unsigned __int16 wMapSvrNum;
};

/* 1054 */
struct PMSG_REQ_ITL_GET_REWARDLIST
{
	PBMSG_HEAD2 h;
	unsigned __int16 wMapSvrNum;
};

/* 1055 */
struct PMSG_REQ_ITL_REWARDRECEIVED
{
	PBMSG_HEAD2 h;
	char szCharName[11];
};

/* 1056 */
struct _tagPMSG_ANS_ITL_REWARDLIST
{
	PWMSG_HEAD2 h;
	char byCnt;
};

/* 1078 */
struct _tagPMSG_REQ_ITL_USERCOUNTREQ
{
	PBMSG_HEAD2 h;
	char UserName[MAX_GUILDNAMESTRING + 1];
	int nUserIndex;
};

/* 1057 */
struct _tagSDHP_REQ_GREMORY_CASE_INSERT
{
	PBMSG_HEAD2 h;
	__int16 aIndex;
	char AccountID[11];
	char Name[11];
	char btGCType;
	char btGiveType;
	char btItemType;
	unsigned __int16 wItemIndex;
	char btLevel;
	char btDur;
	char btSkill;
	char btLuck;
	char btOpt;
	char btSetOpt;
	unsigned __int16 wNewOpt;
	char btBonusSocketOpt;
	char btSocketOpt[5];
	unsigned int dwReceiptExpireDuration;
	unsigned int dwItemDuration;
	int lRecvDate;
	int lRecvExpireDate;
	int lItemExpireDate;
};

/* 1058 */
struct _tagSDHP_ANS_GREMORY_CASE_INSERT
{
	PBMSG_HEAD2 h;
	__int16 aIndex;
	char btResult;
	char btGCType;
	char btGiveType;
	char btItemType;
	unsigned __int16 wItemIndex;
	char btLevel;
	char btDur;
	char btSkill;
	char btLuck;
	char btOpt;
	char btSetOpt;
	unsigned __int16 wNewOpt;
	char btBonusSocketOpt;
	char btSocketOpt[5];
	unsigned int dwSerial;
	int lRecvDate;
	int lRecvExpireDate;
	int lItemExpireDate;
};

/* 1059 */
struct _tagSDHP_REQ_GC_UPDATE
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Name[11];
	__int16 aIndex;
	char btGCType;
	char btItemType;
	unsigned __int16 wItemIndex;
	char btLevel;
	unsigned int dwSerial;
	int lRecvDate;
	BYTE btUsedInfo;
};

/* 1060 */
struct _tagSDHP_ANS_GC_UPDATE
{
	PBMSG_HEAD2 h;
	__int16 aIndex;
	char btResult;
	char btItemType;
	unsigned __int16 wItemIndex;
	char btLevel;
	unsigned int dwSerial;
	int lRecvDate;
};

/* 1063 */
struct _tagSDHP_REQ_GC_UPDATE_INSERT
{
	PBMSG_HEAD2 h;
	__int16 aIndex;
	char btUpdate_GCType;
	char btUpdate_ItemType;
	unsigned __int16 wUpdate_ItemIndex;
	char btUpdate_Level;
	unsigned int dwUpdate_Serial;
	int lUpdate_RecvDate;
	char btUpdate_UsedInfo;
	char AccountID[11];
	char Name[11];
	char btGCType;
	char btGiveType;
	char btItemType;
	unsigned __int16 wItemIndex;
	char btLevel;
	char btDur;
	char btSkill;
	char btLuck;
	char btOpt;
	char btSetOpt;
	unsigned __int16 wNewOpt;
	char btBonusSocketOpt;
	char btSocketOpt[5];
	unsigned int dwReceiptDuration;
	unsigned int dwItemDuration;
	int lRecvDate;
	int lRecvExpireDate;
	int lItemExpireDate;
};

/* 1061 */
struct _tagSDHP_REQ_GREMORY_CASE_SELECT
{
	PBMSG_HEAD2 h;
	char AccountID[11];
	char Name[11];
	__int16 aIndex;
	char btGCType;
};

/* 816 */
struct _stCancelGuildNames
{
	char szGuildNames[MAX_GUILDNAMESTRING + 1];
};
/* 814 */
struct _stABWinGuildInfoDS
{
	char szGuildName[MAX_GUILDNAMESTRING + 1];
	DWORD dwGuild;
	WORD wOccupyObelisk;
	WORD wObeliskGroup;
};

/* 968 */
struct _tagPMSG_REQ_AB_GUILD_JOIN_SELECT_DS
{
	PBMSG_HEAD2 h;
	char szGuildMaster[11];
	unsigned __int16 wNumber;
};

/* 969 */
struct _tagPMSG_REQ_ARCA_BATTLE_GUILD_JOIN_DS
{
	PBMSG_HEAD2 h;
	char szGuildMaster[11];
	char szGuildName[MAX_GUILDNAMESTRING + 1];
	unsigned int dwGuild;
	unsigned __int16 wNumber;
};

/* 970 */
struct _tagPMSG_ANS_ARCA_BATTLE_GUILD_JOIN_DS
{
	PBMSG_HEAD2 h;
	char btResult;
	unsigned __int16 wNumber;
};

/* 971 */
struct _tagPMSG_REQ_ARCA_BATTLE_GUILD_MEMBER_JOIN_DS
{
	PBMSG_HEAD2 h;
	char szCharName[11];
	char szGuildName[MAX_GUILDNAMESTRING + 1];
	unsigned int dwGuild;
	unsigned __int16 wNumber;
};

/* 972 */
struct _tagPMSG_ANS_ARCA_BATTLE_GUILD_MEMBER_JOIN_DS
{
	PBMSG_HEAD2 h;
	char btResult;
	unsigned __int16 wNumber;
};

/* 973 */
struct _tagPMSG_REQ_AB_WIN_GUILD_INFO_INSERT_DS
{
	PBMSG_HEAD2 h;
	char btGuildCnt;
	unsigned __int16 wMapSvrNum;
	_stABWinGuildInfoDS m_stABWinGuildInfoDS[5];
};

/* 974 */
struct _tagPMSG_ANS_AB_WIN_GUILD_INFO_DS
{
	PBMSG_HEAD2 h;
	char btGuildCnt;
	_stABWinGuildInfoDS m_stABWinGuildInfoDS[5];
};

/* 975 */
struct _tagPMSG_REQ_AB_WIN_GUILD_INFO_DS
{
	PBMSG_HEAD2 h;
	unsigned __int16 wNumber;
};

/* 976 */
struct _tagPMSG_REQ_ARCA_BATTLE_ENTER_DS
{
	PBMSG_HEAD2 h;
	char szCharName[11];
	char btEnterSeq;
	unsigned __int16 wNumber;
};

/* 977 */
struct _tagPMSG_ANS_ARCA_BATTLE_ENTER_DS
{
	PBMSG_HEAD2 h;
	char btResult;
	char btEnterSeq;
	unsigned __int16 wNumber;
};

/* 978 */
struct _tagPMSG_REQ_ARCA_BATTLE_GROUP_NUM_DS
{
	PBMSG_HEAD2 h;
	char szCharName[11];
	unsigned __int16 wNumber;
};

/* 979 */
struct _tagPMSG_ANS_ARCA_BATTLE_GROUP_NUM_DS
{
	PBMSG_HEAD2 h;
	unsigned __int16 wGroupNum;
	unsigned __int16 wNumber;
};

/* 980 */
struct _tagPMSG_REQ_ARCA_BATTLE_INFO_DS
{
	PBMSG_HEAD2 h;
};

/* 981 */
struct _tagPMSG_REQ_AB_PROC_INSERT_DS
{
	PBMSG_HEAD2 h;
	unsigned __int16 wMapSvrNum;
	char btProcState;
};

/* 982 */
struct _tagPMSG_REQ_ARCA_BATTLE_PROC_STATE_DS
{
	PBMSG_HEAD2 h;
};

/* 983 */
struct _tagPMSG_ANS_ARCA_BATTLE_PROC_STATE_DS
{
	PBMSG_HEAD2 h;
	char btProcState;
};

/* 984 */
struct _tagPMSG_REQ_AB_JOIN_MEMBER_UNDER_DS
{
	PBMSG_HEAD2 h;
	unsigned __int16 wMapSvrNum;
};

/* 815 */
struct _stGuildUnderMember
{
	char btGuildMemberCnt;
	char szGuildNames[MAX_GUILDNAMESTRING + 1];
};

/* 985 */
struct _tagPMSG_ANS_AB_JOIN_MEMBER_UNDER_DS
{
	PBMSG_HEAD2 h;
	char btGuildCnt;
	_stGuildUnderMember GuildMemberCnt[6];
};

/* 986 */
struct _tagPMSG_REQ_AB_JOIN_CANCEL_DS
{
	PBMSG_HEAD2 h;
	char btMinGuildMemNum;
	unsigned __int16 wMapSvrNum;
};

/* 987 */
struct _tagPMSG_ANS_AB_JOIN_CANCEL_DS
{
	PBMSG_HEAD2 h;
	char btGuildCnt;
	_stCancelGuildNames CancelGuildNames[6];
};

/* 988 */
struct _tagPMSG_REQ_AB_REG_MEMBER_CNT_DS
{
	PBMSG_HEAD2 h;
	unsigned __int16 wNumber;
	unsigned int dwGuild;
};

/* 989 */
struct _tagPMSG_ANS_AB_REG_MEMBER_CNT_DS
{
	PBMSG_HEAD2 h;
	unsigned __int16 wNumber;
	char btRegMemCnt;
};

/* 990 */
struct _tagPMSG_REQ_REMOVE_ALL_GUILD_BUFF_DS
{
	PBMSG_HEAD2 h;
	unsigned __int16 wMapSvrNum;
};

/* 991 */
struct _tagPMSG_REQ_REMOVE_GUILD_BUFF_DS
{
	PBMSG_HEAD2 h;
	unsigned __int16 wMapSvrNum;
	char szGuildName[MAX_GUILDNAMESTRING + 1];
};

/* 1024 */
struct _tagPMSG_REQ_SAVE_CHAOSCASTLE_KILLPOINT
{
	PBMSG_HEAD2 h;
	char szCharName[11];
	int nPoint;
	int nIndex;
	int nCatleIndex;
};

/* 1015 */
struct SDHP_SEND_CCF_INFO
{
	PBMSG_HEAD2 h;
	int nMin;
	int nType;
	unsigned __int16 wMapSvrNum;
};

/* 1016 */
struct PMSG_CCF_SEND_ALL_INFO
{
	PBMSG_HEAD2 h;
	int nMin;
	int nType;
	unsigned __int16 wMapSvrNum;
};

/* 1017 */
struct SDHP_REQ_CCF_RESULT
{
	PBMSG_HEAD2 h;
	char szCharName[11];
	int nPoint;
	char byCCFType;
};

/* 1018 */
struct SDHP_REQ_CCF_GETPERMISSION
{
	PBMSG_HEAD2 h;
	char szCharName[11];
	char byCCFType;
	int nIndex;
};

/* 1019 */
struct SDHP_ANS_CCF_GETPERMISSION
{
	PBMSG_HEAD2 h;
	int nResult;
	int nIndex;
};

/* 1020 */
struct SDHP_REQ_CCF_RANKING_REQ
{
	PBMSG_HEAD2 h;
	char byRankingType;
	int nServerCategory;
};

/* 1021 */
struct _tagPMSG_ANS_CCF_RANKING
{
	PWMSG_HEAD h;
	char byUserCnt;
};
/* 1022 */
struct SDHP_RENEW_RANKING
{
	PBMSG_HEAD2 h;
	char byCCFType;
};

/* 1081 */
struct PMSG_UBF_REGISTER_ACCOUNT_USER
{
	PBMSG_HEAD2 h;
	char btDummy;
	char szAccountID[11];
	char szName[11];
	char szBattleFieldName[11];
	int iUserIndex;
	__int16 ServerCode;
	char btRegisterState;
	char btRegisterMonth;
	char btRegisterDay;
};

/* 1082 */
struct PMSG_UBF_REGISTER_ACCOUNT_USER_RESULT
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char btResult;
	unsigned __int16 nLeftSec;
};

/* 1083 */
struct PMSG_UBF_ACCOUNT_USER_COPY
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char szAccountID[11];
	char btDumy1;
	char szName[11];
	char btDumy2;
	__int16 ServerCode;
	char btPromotionMode;
};

/* 1084 */
struct PMSG_UBF_ACCOUNT_USER_COPY_RESULT
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char btResult;
	char btSubResult;
};

/* 1085 */
struct PMSG_REQ_UBF_SET_RECEIVED_REWARD
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	int iServerCode;
	char szName[11];
	char btReceivedReward;
};

/* 1086 */
struct PMSG_ANS_UBF_SET_RECEIVED_REWARD
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char btReturn;
	char btSubReturn;
};

/* 1088 */
struct PMSG_UBF_REQ_CANCEL_REGISTER_USER
{
	PBMSG_HEAD2 h;
	char btDummy;
	char szAccountID[11];
	char szName[11];
	int iUserIndex;
	__int16 ServerCode;
	char btCanceled;
};

/* 1089 */
struct PMSG_UBF_ANS_CANCEL_REGISTER_USER
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char btCanceledResult;
	char btDeletedResult;
};

/* 1090 */
struct PMSG_REQ_GET_UBF_REAL_NAME
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char szUBFName[11];
};

/* 1091 */
struct PMSG_REQ_UBF_SET_REWARD_INFORMATION
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char btServerKind;
	char szAccountID[11];
	char szName[11];
	__int16 ServerCode;
	char btContentsType;
	char btSubContentsType;
	int iItemCode;
	char btItemCount;
	char btTookState;
};

/* 1092 */
struct PMSG_ANS_UBF_SET_REWARD_INFORMATION
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char btReturn;
	char btContentsType;
	char btSubContentsType;
	int iItemCode;
	char btItemCount;
};

/* 1093 */
struct PMSG_REQ_DSF_CAN_PARTY_ENTER
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char szAccountID1[11];
	char szUserName1[11];
	char szAccountID2[11];
	char szUserName2[11];
	char btDSFType;
	int iEnterYear;
	char btEnterMonth;
	char btEnterDay;
};

/* 1094 */
struct PMSG_ANS_DSF_CAN_PARTY_ENTER
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char btCount;
	char btResult;
};

/* 1095 */
struct PMSG_REQ_SAVE_DSF_USERPOINT
{
	PBMSG_HEAD2 h;
	char UserName[11];
	char GName[MAX_GUILDNAMESTRING + 1];
	int nPoint;
	int Type;
	int nEnterCount;
	int nWin;
};

/* 1096 */
struct PMSG_REQ_SAVE_DSF_PARTYPOINT
{
	PBMSG_HEAD2 h;
	char szAccountID1[11];
	char szUserName1[11];
	int nUser1Level;
	char szAccountID2[11];
	char szUserName2[11];
	int nUser2Level;
	int nDSFType;
	int nPoint;
	char btEnterCnt;
	int nEnterYear;
	char btEnterMonth;
	char btEnterDay;
};

/* 1097 */
struct PMSG_REQ_DSF_PARTYRANKRENEW
{
	PBMSG_HEAD2 h;
	char btDSFType;
	int nEnterYear;
	char btEnterMonth;
	char btEnterDay;
};

/* 1098 */
struct PMSG_ANS_DSF_PARTYRANKRENEW
{
	PBMSG_HEAD2 h;
	char btResult;
};

/* 1099 */
struct PMSG_REQ_DSF_TODAY_PARTYRANK
{
	PBMSG_HEAD2 h;
	int iUserIndex;
	char btDSFType;
	int nEnterYear;
	char btEnterMonth;
	char btEnterDay;
};

/* 1100 */
struct PMSG_ANS_DSF_TODAY_PARTYRANK
{
	PWMSG_HEAD2 h;
	int iUserIndex;
	char btPartyCnt;
};

/* 1101 */
struct PMSG_REQ_DSF_GO_FINAL_PARTY
{
	PBMSG_HEAD2 h;
	char btDSFType;
	int nEnterYear;
	char btEnterMonth;
	char btEnterDay;
};

/* 1102 */
struct PMSG_ANS_DSF_GO_FINAL_PARTY
{
	PWMSG_HEAD2 h;
	char btPartyCnt;
	char btDSFType;
};

/* 1103 */
struct PMSG_REQ_SAVE_DSF_REWARD_USER
{
	PBMSG_HEAD2 h;
	char szAccountID[11];
	char szUserName[11];
	int iClass;
	char btDSFType;
	int nRewardYear;
	char btRewardMonth;
	char btRewardStartDay;
	char btRewardEndDay;
};

/* 1104 */
struct PMSG_REQ_GET_DSF_REWARD
{
	PBMSG_HEAD2 h;
	char szAccountID[11];
	char szUserName[11];
	int nServerCode;
	int nUserIndex;
	int nRewardYear;
	char btRewardMonth;
	char btRewardDay;
};

/* 1105 */
struct PMSG_ANS_GET_DSF_REWARD
{
	PBMSG_HEAD2 h;
	int nUserIndex;
	char btResult;
};

/* 1106 */
struct _tagPMSG_ANS_DSF_REWARDLIST
{
	PWMSG_HEAD2 h;
	char byCnt;
};

/* 1107 */
struct _stDSFRewardList
{
	char byRank;
	char szCharName[11];
	char szGuildName[MAX_GUILDNAMESTRING + 1];
	char byEnterCount;
	char byPoint;
	char byGotReward;
};

/* 1122 */
struct SDHP_SEND_EVENTMAP_INFO_ALL_SVR
{
	PBMSG_HEAD2 h;
	char byBattleType;
	char byBattleStatus;
	unsigned __int16 wMapSvrNum;
};

/* 1123 */
struct SDHP_GET_EVENTMAPENTERCOUNT
{
	PBMSG_HEAD2 h;
	int userIndex;
	char Name[11];
};

/* 1124 */
struct SDHP_SET_EVENTMAPENTERCOUNT
{
	PBMSG_HEAD2 h;
	char Name[11];
	int userIndex;
	char BloodCastle;
	char ChaosCastle;
	char DevilSquare;
	char DoppelGanger;
	char ImperialGuardian;
	char IllusionTempleRenewal;
};

/* 1004 */
struct _tagPMSG_ANS_ARCA_BATTLE_MARK_CNT_DS
{
	PBMSG_HEAD2 h;
	char btResult;
	unsigned __int16 wNumber;
	unsigned int dwMarkCnt;
};
/* 999 */
struct PMSG_REQ_PERIODBUFF_INSERT
{
	PBMSG_HEAD2 head;
	WORD wUserIndex;
	char szCharacterName[11];
	WORD wBuffIndex;
	char btEffectType1;
	char btEffectType2;
	DWORD dwDuration;
	int lExpireDate;
};

/* 1000 */
struct PMSG_REQ_PERIODBUFF_DELETE
{
	PBMSG_HEAD2 head;
	unsigned __int16 wUserIndex;
	unsigned __int16 wBuffIndex;
	char szCharacterName[11];
};


/* 1001 */
struct PMSG_REQ_PERIODBUFF_SELECT
{
	PBMSG_HEAD2 head;
	unsigned __int16 wUserIndex;
	char szCharacterName[11];
};

/* 1002 */
struct PMSG_ANS_PERIODBUFF_SELECT
{
	PBMSG_HEAD2 head;
	char btResultCode;
	unsigned __int16 wUserIndex;
	unsigned __int16 wBuffIndex;
	char btEffectType1;
	char btEffectType2;
	int lExpireDate;
};
/* 822 */
struct _tagPeriodBuffInfo
{
	unsigned __int16 wBuffIndex;
	char btEffectType1;
	char btEffectType2;
	int lDuration;
	int lExpireDate;
};

/* 1003 */
struct _tagPMSG_REQ_ARCA_BATTLE_MARK_CNT_DS
{
	PBMSG_HEAD2 h;
	unsigned __int16 wNumber;
	unsigned int dwGuildNum;
};

/* 1027 */
struct _tagSDHP_ANS_DBEVENT_INVEN_LOAD
{
	PWMSG_HEAD h;
	char dbItems[512];
	char DbVersion;
	__int16 aIndex;
};

/* 995 */
struct _tagPMSG_ANS_AB_ALL_JOIN_USER_DS
{
	PWMSG_HEAD h;
	char btUserCnt;
};

/* 1117 */
struct _tagANSCHAOS_CASTLE_USER_DS
{
	PBMSG_HEAD2 h;
	int userIndex;
	char AccountID[11];
	char Name[11];
	bool bPCBangFree;
	char btEnterLevel;
	char btCount;
	unsigned __int16 wRemainTime;
};

/* 1023 */
struct SDHP_ANS_KILLPOINT_RESULT
{
	PBMSG_HEAD2 h;
	int nIndex;
	int nResult;
	int nCurrentPoint;
	int nTotalPoint;
};

typedef struct PMSG_REQ_UBF_ACCOUNT_USERINFO
{
	PBMSG_HEAD2 h; // C1:FA:01 GS->DS
	int iUserIndex;
	char szAccountID[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	int iServerCode;
	BOOL IsUnityBattleFieldServer;
	BYTE btObserverMode;
} *LPPMSG_REQ_UBF_ACCOUNT_USERINFO;

typedef struct PMSG_ANS_UBF_ACCOUNT_USERINFO
{
	PBMSG_HEAD2 h; // C1:FA:01 DS->GS
	int iUserIndex;
	BYTE btResult;
	BYTE btRegisterState;
	BYTE btRegisterMonth;
	BYTE btRegisterDay;
	BYTE btObserverMode;
} *LPPMSG_ANS_UBF_ACCOUNT_USERINFO;

typedef struct PMSG_REQ_UBF_GET_REWARD
{
	PBMSG_HEAD2 h; // C1:FA:06 GS->DS
	int iUserIndex;
	int iServerCode;
	BYTE btServerKind;
	BYTE btContentsType;
	char szName[MAX_IDSTRING + 1];
} *LPPMSG_REQ_UBF_GET_REWARD;

typedef struct PMSG_ANS_UBF_GET_REWARD
{
	PBMSG_HEAD2 h; // C1:FA:06 DS->GS
	int iUserIndex;
	BYTE btResult;
	BYTE btContentsType;
	BYTE btArrayCCF_Reward[4];
	BYTE btArrayDSF_Reward[4];
	BYTE btArrayCCN_Reward[2];
	BYTE btArrayDSN_Reward[14];
} *LPPMSG_ANS_UBF_GET_REWARD;

typedef struct PMSG_REQ_GET_UBF_REAL_NAME
{
	PBMSG_HEAD2 h; // C1:FA:08 GS->DS
	int iUserIndex;
	char szUBFName[MAX_IDSTRING + 1];
} *LPPMSG_REQ_GET_UBF_REAL_NAME;

typedef struct PMSG_ANS_GET_UBF_REAL_NAME
{
	PBMSG_HEAD2 h; // C1:FA:08 DS->GS
	int iUserIndex;
	char szUBFName[MAX_IDSTRING + 1];
	char szRealName[MAX_IDSTRING + 1];
	int iServerCode;
	BYTE btRetrun;
} *LPPMSG_ANS_GET_UBF_REAL_NAME;


/* 671 */
struct _stDSFPartyRankInfo
{
	char szUserName1[11];
	char szUserName2[11];
	char btRank;
	char btDSFType;
	int iPoint;
};

/* 1125 */
struct SDHP_ANS_EVENTMAPENTERCOUNT
{
	PBMSG_HEAD2 h;
	char Name[11];
	int nUserIndex;
	char BloodCastle;
	char ChaosCastle;
	char DevilSquare;
	char DoppelGanger;
	char ImperialGuardian;
	char IllusionTempleRenewal;
};


/* 672 */
struct _stDSFGoFinalPartyInfo
{
	char szUserName1[11];
	char szUserName2[11];
	unsigned __int16 wServerCode1;
	unsigned __int16 wServerCode2;
	char btRank;
	char btDSFType;
	int iPoint;
	int nEnterYear;
	char btEnterMonth;
	char btEnterDay;
};

typedef struct _stArcaBattleMarkTopRank
{
	_stArcaBattleMarkTopRank()
	{
		btRank = 0;
		dwMarkCnt = 0;
		memset(szGuildNames, 0, sizeof(szGuildNames));
	}

	BYTE btRank;
	char szGuildNames[MAX_GUILDNAMESTRING + 1];
	BYTE dwMarkCnt;
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

/* 819 */
struct _stABJoinUserInfoDS
{
	char szGuildName[MAX_GUILDNAMESTRING + 1];
	unsigned int dwGuild;
	char szUserName[11];
};


/* 992 */
struct _tagPMSG_ANS_REMOVE_GUILD_BUFF_DS
{
	PBMSG_HEAD2 h;
	char szGuildName[MAX_GUILDNAMESTRING + 1];
};

/* 1006 */
struct _tagPMSG_ANS_ARCA_BATTLE_MARK_REG_DS
{
	PBMSG_HEAD2 h;
	unsigned __int16 wNumber;
	char btResult;
};

/* 1007 */
struct _tagPMSG_REQ_ARCA_BATTLE_MARK_RANK_DS
{
	PBMSG_HEAD2 h;
	unsigned __int16 wNumber;
	unsigned int dwGuildNum;
};

/* 1005 */
struct _tagPMSG_REQ_ARCA_BATTLE_MARK_REG_DS
{
	PBMSG_HEAD2 h;
	unsigned __int16 wNumber;
	char szGuildMaster[11];
	char szGuildName[MAX_GUILDNAMESTRING + 1];
	unsigned int dwMarkCnt;
	unsigned int dwGuildNum;
};

/* 1008 */
struct _tagPMSG_ANS_ARCA_BATTLE_MARK_RANK_DS
{
	PBMSG_HEAD2 h;
	unsigned __int16 wNumber;
	char btRank;
	unsigned int dwMarkCnt;
	char btGuildCnt;
	_stArcaBattleMarkTopRank ArcaBattleMarkTopRank[6];
};

/* 1009 */
struct _tagPMSG_REQ_ARCA_BATTLE_MARK_REG_DEL_DS
{
	PBMSG_HEAD2 h;
	unsigned __int16 wNumber;
	unsigned int dwGuildNum;
};

/* 1010 */
struct _tagPMSG_REQ_ARCA_BATTLE_IS_TOP_RANK
{
	PBMSG_HEAD2 h;
	unsigned __int16 wNumber;
	unsigned int dwGuildNum;
};

typedef struct _tagPMSG_REQ_AB_MARK_REG_UPDATE_DS
{
	PBMSG_HEAD2 h; // C1:F8:57 GS->DS
	DWORD dwGuildNum;
	DWORD dwMarkCnt;
} *LPPMSG_REQ_AB_MARK_REG_UPDATE_DS;

/* 997 */
struct _tagPMSG_ANS_AE_PLAY_DS
{
	PBMSG_HEAD2 h;
	char btPlay;
};

/* 998 */
struct PMSG_REQ_PENTAGRAMJEWEL
{
	PBMSG_HEAD h;
	int iUserIndex;
	BYTE btJewelPos;
	int iUserGuid;
	char AccountId[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
};

/* 996 */
struct _tagPMSG_REQ_AE_PLAY_DS
{
	PBMSG_HEAD2 h;
	unsigned __int16 wMapSvrNum;
	char btPlay;
};

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

/* 1079 */
struct _tagPMSG_ANS_ITL_USERCOUNTANS
{
	PBMSG_HEAD2 h;
	int nUserIndex;
	char byCount;
};

/* 836 */
struct _stITLRewardList
{
	char byRank;
	char szCharName[11];
	char szGuildName[MAX_GUILDNAMESTRING + 1];
	char byEnterCount;
	char byPoint;
	char byGotReward;
};

/* 834 */
struct _stITLRankingInfo
{
	char szGuildName[MAX_GUILDNAMESTRING + 1];
	char byRank;
	char byITLType;
	char byWin;
	char byLose;
};

/* 1062 */
struct _tagSDHP_ANS_GREMORY_CASE_SELECT
{
	PWMSG_HEAD2 h;
	char btResult;
	__int16 aIndex;
	char btCnt;
};

/* 1064 */
struct _tagSDHP_ANS_GC_UPDATE_INSERT
{
	PBMSG_HEAD2 h;
	__int16 aIndex;
	char btUpdate_GCType;
	char btUpdate_ItemType;
	unsigned __int16 wUpdate_ItemIndex;
	char btUpdate_Level;
	unsigned int dwUpdate_Serial;
	int lUpdate_RecvDate;
	char btUpdate_UsedInfo;
	char btGCType;
	char btGiveType;
	char btItemType;
	unsigned __int16 wItemIndex;
	char btLevel;
	char btDur;
	char btSkill;
	char btLuck;
	char btOpt;
	char btSetOpt;
	unsigned __int16 wNewOpt;
	char btBonusSocketOpt;
	char btSocketOpt[5];
	unsigned int dwSerial;
	int lRecvDate;
	int lRecvExpireDate;
	int lItemExpireDate;
};

/* 993 */
struct _tagPMSG_ANS_ALL_GUILD_MARK_CNT_DS
{
	PWMSG_HEAD2 h;
	unsigned __int16 wGuildCnt;
};
/* 1115 */
struct _tagREQCHAOS_CASTLE_USER_DS
{
	PBMSG_HEAD2 h;
	int serverIndex;
	int userIndex;
	char AccountID[11];
	char Name[11];
	bool bPCBangFree;
	char btEnterLevel;
};

/* 699 */
struct _stGremoryCaseList
{
	char btGCType;
	char btGiveType;
	char btItemType;
	unsigned __int16 wItemIndex;
	char btLevel;
	char btDur;
	char btSkill;
	char btLuck;
	char btOpt;
	char btSetOpt;
	unsigned __int16 wNewOpt;
	char btBonusSocketOpt;
	char btSocketOpt[5];
	unsigned int dwSerial;
	int lRecvDate;
	int lRecvExpireDate;
	int lItemExpireDate;
};

/* 6308 */
struct SDHP_REQ_LABYRINTH_END_UPDATE
{
	PWMSG_HEAD2 h;
	char szAccountID[11];
	char szName[11];
	int nUserIndex;
	int nClearCnt;
	char btClearState;
};

/* 950 */
struct SDHP_ANS_ACCOUNTINFO
{
	PBMSG_HEAD h;
	char AccountId[11];
	__int16 Number;
	BYTE Result;
	BYTE bSummoner;
};
#endif // __SPRODEF_H__




