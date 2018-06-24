// SetItemOption.h: interface for the CSetItemOption class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETITEMOPTION_H__E2F2BB72_7EB5_4280_A54C_783B6EFDA283__INCLUDED_)
#define AFX_SETITEMOPTION_H__E2F2BB72_7EB5_4280_A54C_783B6EFDA283__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if GAME_VERSION >= G_V_99B

#include "..\\Common\\LogProc.h"
#include "..\\Include\\Define.h"
#include "..\\Include\\ItemDef.h"
#include "..\\Include\\ReadScript.h"
#include "..\\common\\Winutil.h"
#include "..\\common\\zzzitem.h"


// 세트 아이템 옵션 리스트
//0		더블 데미지 확률 2%
//1		적 방어력 무시 2%
//2		양손검 장비시 데미지 15% 증가
//3		공격 성공률 증가 5%
//4		100% 데미지 반사 확률 5% 증가
//5		방패 장비시 방어력 5% 증가
//6		힘 증가 +10
//7		힘 증가 +20
//8		민첩성 증가 +10
//9		민첩성 증가 +20
//10	에너지 증가 +10
//11	에너지 증가 +20
//12	체력 증가 +10
//13	체력 증가 +20
//14	최대 생명력 증가 +40
//15	최대 생명력 증가 +80
//16	최대 마나 증가 +40
//17	최대 마나 증가 +80
//18	최대 AG 5% 증가
//19	소비 AG 10% 감소
//20	아이템 드랍 확률 5% 증가
//21	특정 캐릭터 공격력 증가 민첩성/60
//22	특정 캐릭터 공격력 증가 힘/50
//23	특정 캐릭터 마력 증가 에너지/70
//24	특정 캐릭터 방어력 증가 레벨/20
//25	특정 캐릭터 방어력 증가 3%
//26	특정 캐릭터 방어력 증가 민첩성/50
//27	특정 캐릭터 방어력 증가 체력/40
//28	특정 캐릭터 불속성 추가
//29	특정 캐릭터 얼음속성 추가
//30	특정 캐릭터 번개속성 추가
//31	특정 캐릭터 독속성 추가
//32	특정 캐릭터 물속성 추가
//33	특정 캐릭터 바람속성 추가
//34	특정 캐릭터 땅속성 추가

#define		MAX_SETITEM_OPTION	80

// 세트 아이템 타입 정보 
// (해당 옵션에 대한 인덱스 및 카오스 조합 레벨 정보를 가진다)
typedef struct 
{
	BOOL	IsLoad;

	int	OptionIndex[2];
	int	ChaosMixLevel[2];	
}SETITEM_TYPEINFO;

// 세트 아이템 옵션에 대한 상세 정보
typedef struct 
{
	BOOL	IsLoad;
	char	Name[255];						// 세트 아이템 이름
	
	int		SetOptionCount;					// 기본 세트 옵션 수
	int		SetOptionTable[6][2];			// 각각마다 옵션은 두개씩
	int		SetOptionTableValue[6][2];		// 옵션의 값
	int		SetExPOptionTable[2];			// 확장 옵션 7~8 옵션
	int		SetExPOptionTableValue[2];		// 옵션의 값
	int		SetFullOtionTable[5];			// 풀옵션 최대 4개
	int		SetFullOtionTableValue[5];		// 옵션의 값

	BYTE	RequireClass[MAX_CLASSTYPE+1];	// 요구 클래스
}SETITEM_OPTIONINFO;

class CSetItemOption  
{
	SETITEM_TYPEINFO	m_SetItemTypeInfo[MAX_ITEM];
	SETITEM_OPTIONINFO	m_SetItemOptionInfo[MAX_SETITEM_OPTION];
public:
	CSetItemOption();
	virtual ~CSetItemOption();

	BOOL	LoadTypeInfo(char* filename);
	BOOL	LoadOptionInfo(char* filename);
	
#ifdef AUTH_GAMESERVER
	BOOL	LoadTypeInfo(char *Buffer, int iSize);
	BOOL	LoadOptionInfo(char *Buffer, int iSize);
#endif

	BOOL	IsSetItem(int itemnum);

	// 해당 아이템의 세트 옵션 인덱스를 얻어 온다
	int		GetOptionTableIndex(int itemnum, int setoption);

	char*	GetSetOptionName(int optionindex);
	char*	GetSetOptionName(int itemnum, int settype);

	// 옵션을 가져 온다
	int		GetSetOption(int optionindex, int optablenum, int& op1, int& op2, int& opvalue1, int& opvalue2, int Class, int ChangeUp);
	// 옵션의 최대 수를 얻어 온다
	int		GetMaxSetOptionCount(int optionindex);

	// 풀옵션을 얻어 온다
	int		GetGetFullSetOption(int optionindex, int& op1, int& op2, int& op3, int& op4, int& op5, 
								int& opvalue1, int& opvalue2, int& opvalue3, int& opvalue4, int& opvalue5, int Class, int ChangeUp );

	int		IsRequireClass(int optionindex, int Class, int ChangeUp);	

	BOOL	CheckMixContition(int itemnum, int mixitemlevel);
	// 세트 옵션을 만든다( A세트 == 1, B세트 == 2 )
	int		MakeSetOption(int itemnum, int mixitemlevel);

	int		GenRandomItemNum();
	int		GenSetOption(int itemnum);

	SETITEM_TYPEINFO *	GetSetType(int index);

};

extern CSetItemOption	gSetItemOption;

#endif

#endif // !defined(AFX_SETITEMOPTION_H__E2F2BB72_7EB5_4280_A54C_783B6EFDA283__INCLUDED_)
