#ifndef __MNGPROTOCOL_H__
#define __MNGPROTOCOL_H__

#include "GMProtocol.h"

#define MAX_MEMO	5000

typedef struct
{
	char AccountId[MAX_IDSTRING+1];
	char Password[MAX_IDSTRING+1];
	char Name[MAX_IDSTRING+1];
#ifdef UPDATE_USERPASSWORD_LENGTH_20090424
	char JoominNumber[MAX_JOOMINNUMBER_LENGTH+1];
#else
	char JoominNumber[14];
#endif	// UPDATE_USERPASSWORD_LENGTH_20090424
	char PhoneNumber[16];
	char Email[51];
	char Question[51];
	char Answer[51];
	int  Block;
	DWORD memb_guid;
	char Memo[MAX_MEMO+1];
} AccountInfomation, *LPAccountInfomation;


// 0x01 : 클라이언트가 접속을 요청한다.
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		CheckCode;
	char		szID[10];
	char		szPWD[10];
} PMSG_CONNECT, * LPPMSG_CONNECT;

// 접속 결과
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		Result;
	int			Level;
} PMSG_CONNECT_RESULT, *LPPMSG_CONNECT_RESULT;

// 0x02 : 계정 정보를 달라고 요청한다.
typedef struct
{
	PBMSG_HEAD	h;
	char		szID[10];
} PMSG_ACCOUNTINFO, *LPPMSG_ACCOUNTINFO;


typedef struct
{
	PWMSG_HEAD	h;
	BYTE		Result;
	AccountInfomation	AInfo;
} PMSG_ACCOUNTINFO_RESULT, *LPPMSG_ACCOUNTINFO_RESULT;


// 0x03 : 캐릭터 정보를 달라고 요청한다.
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		ServerNumber;
	char		szID[10];
} PMSG_CHARINFO, *LPPMSG_CHARINFO;

// 0x03 : 캐릭터 정보 결과
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		Result;	
} PMSG_CHARINFO_RESULT, *LPPMSG_CHARINFO_RESULT;


// 0x04 : 계정 캐릭터 정보를 달라고 요청한다.
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		ServerNumber;
	char		szID[10];
} PMSG_ACCOUNTCHARINFO, *LPPMSG_ACCOUNTCHARINFO;


// 0x04 : 계정 캐릭터 정보
typedef struct
{
	PBMSG_HEAD	h;
	
	char szGameID1[10];
	char szGameID2[10];
	char szGameID3[10];
	char szGameID4[10];
	char szGameID5[10];

} PMSG_ACCOUNTCHARINFO_RESULT, *LPPMSG_ACCOUNTCHARINFO_RESULT;


// 0x05
typedef struct
{
	PWMSG_HEAD	h;
	
	char  AccountID[MAX_IDSTRING];
	char  Name[MAX_IDSTRING];	// 이름
	BYTE  Class;				// 직업
	BYTE  Level;				// 레벨
	int	  LevelUpPoint;			// 레벨업 포인트 
	int   Exp;					// 경험치
	int   NextExp;				// 다음 경험치
	int   Money;				// 돈
	short Str;					// 힘
	short Dex;					// 민첩성 
	short Vit;					// 건강
	short Energy;				// 에너지
	short Life;					// 현재 생명
	short MaxLife;				// 현재 최대 생명값
	short Mana;					// 현재 마나
	short MaxMana;				// 현재 최대 마나값
	
	BYTE  dbInventory[MAX_DBINVENTORY];	// 아이템 인벤토리
	BYTE  dbMagicList[MAX_DBMAGIC];		// 마법(스킬)리스트
	BYTE  dbWarehouse[MAX_WAREHOUSEDBSIZE];

	int   WarehouseMoney;

	BYTE  MapNumber;			// 마지막 접종 했을때의 맵 번호
	BYTE  MapX;					// 마지막 접종 했을때의 X 좌표
	BYTE  MapY;					// 마지막 접종 했을때의 Y 좌표
	BYTE  Dir;
	int   PkCount;
	int   PkLevel;
	int   PkTime;
} PMSG_GETCHARINFO, *LPPMSG_GETCHARINFO;

// 0x05
typedef struct
{
	PWMSG_HEAD	h;
	
	char  AccountID[MAX_IDSTRING];
	char  Name[MAX_IDSTRING];	// 이름
	BYTE  Class;				// 직업
	BYTE  Level;				// 레벨
	int	  LevelUpPoint;			// 레벨업 포인트 
	int   Exp;					// 경험치
	int   NextExp;				// 다음 경험치
	int   Money;				// 돈
	short Str;					// 힘
	short Dex;					// 민첩성 
	short Vit;					// 건강
	short Energy;				// 에너지
	short Life;					// 현재 생명
	short MaxLife;				// 현재 최대 생명값
	short Mana;					// 현재 마나
	short MaxMana;				// 현재 최대 마나값
	
	BYTE  dbInventory[MAX_DBINVENTORY];	// 아이템 인벤토리
	BYTE  dbMagicList[MAX_DBMAGIC];		// 마법(스킬)리스트
	BYTE  dbWarehouse[MAX_WAREHOUSEDBSIZE];

	int   WarehouseMoney;

	BYTE  MapNumber;			// 마지막 접종 했을때의 맵 번호
	BYTE  MapX;					// 마지막 접종 했을때의 X 좌표
	BYTE  MapY;					// 마지막 접종 했을때의 Y 좌표
	BYTE  Dir;
	int   PkCount;
	int   PkLevel;
	int   PkTime;
} PMSG_SETCHARINFO, *LPPMSG_SETCHARINFO;


// 0x06 캐릭터의 위치를 수정한다.
typedef struct
{
	PBMSG_HEAD		h;
	
	char			AccountID[MAX_IDSTRING];
	char			Name[MAX_IDSTRING];

	BYTE			ServerNumber;
	BYTE			MapNumber;			// 마지막 접종 했을때의 맵 번호
	BYTE			MapX;				// 마지막 접종 했을때의 X 좌표
	BYTE			MapY;				// 마지막 접종 했을때의 Y 좌표
} PMSG_POS_CHANGE, *LPPMSG_POS_CHANGE;

// 0x22 계정 정보를 수정한다.
typedef struct
{
	PBMSG_HEAD		h;
	char			AccountID[MAX_IDSTRING];
	char			Pwd[MAX_IDSTRING];

	char			Name[MAX_IDSTRING];
#ifdef UPDATE_USERPASSWORD_LENGTH_20090424
	char			JoominNumber[MAX_JOOMINNUMBER_LENGTH+1];
#else
	char			JoominNumber[14];
#endif	// UPDATE_USERPASSWORD_LENGTH_20090424
	char			PhoneNumber[16];
	char			Email[51];
	char			Question[51];
	char			Answer[51];
	
	int				Block;
} PMSG_ACCOUNTCHANGE, *LPPMSG_ACCOUNTCHANGE;
	
// 0x22 계정 정보를 수정 결과
typedef struct
{
	PBMSG_HEAD		h;	
	BYTE			result;
	char			AccountID[MAX_IDSTRING];
} PMSG_ACCOUNTCHANGE_RESULT, *LPPMSG_ACCOUNTCHANGE_RESULT;


// 0x24 : 계정 캐릭터 정보 변경
typedef struct
{
	PBMSG_HEAD		h;
	int				server_number;
	char			szId[10];
	char			szGameID1[10];
	char			szGameID2[10];
	char			szGameID3[10];
	char			szGameID4[10];
	char			szGameID5[10];
} PMSG_ACCOUNTCHARINFOCHANGE, *LPPMSG_ACCOUNTCHARINFOCHANGE;


// 0x24 : 계정 캐릭터 정보 변경 결과 
typedef struct
{
	PBMSG_HEAD		h;
	BYTE			result;
	char			szId[MAX_IDSTRING];
} PMSG_ACCOUNTCHARINFOCHANGE_RESULT, *LPPMSG_ACCOUNTCHARINFOCHANGE__RESULT;

// 0x25 : 계정 메모를 업데이트 시킨다.
typedef struct
{
	PWMSG_HEAD		h;	
	char			szId[MAX_IDSTRING];
	char			Memo[MAX_MEMO];
} PMSG_ACCOUNTMEMO_UPDATE,  *LPPMSG_ACCOUNTMEMO_UPDATE;

typedef struct
{
	PBMSG_HEAD		h;
	BYTE			result;
	char			szId[MAX_IDSTRING];
} PMSG_ACCOUNTMEMO_ID_RESULT, *LPPMSG_ACCOUNTMEMO_ID_RESULT;

// 0x26 : 계정 메모를 삭제 한다.
typedef struct
{
	PBMSG_HEAD		h;
	char			szId[MAX_IDSTRING];
} PMSG_ACCOUNTMEMO_DELETE,  *LPPMSG_ACCOUNTMEMO_DELETE;

// 0x27 돈의 액수를 수정한다.
typedef struct
{
	PBMSG_HEAD		h;
	char			GameID[MAX_IDSTRING];
	int				server_number;
	DWORD			Money;
} PMSG_MONEY_MODIFY, *LPPMSG_MONEY_MODIFY;


#endif
