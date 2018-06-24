#ifndef __ZZZITEM_H__
#define __ZZZITEM_H__

#include "..\\Include\\ItemDef.h"


#ifdef ADD_RANDOM_RANGE_OF_ITEMINDEX_20050808
extern int g_MaxItemIndexOfEachItemType[MAX_ITEM_TYPE];
#endif

#ifdef ADD_ITEM_SOCKET_OPTION_SYSTEM_20080415
#include "ItemSocketOptionDefine.h"
#endif // ADD_ITEM_SOCKET_OPTION_SYSTEM_20080415


class CItem
{
public:
	DWORD m_Number;
	char  m_serial;
	short m_Type;
	short m_Level;
	BYTE  m_Part;
	BYTE  m_Class;
	bool  m_TwoHand;
	BYTE  m_AttackSpeed;
	BYTE  m_WalkSpeed;
	WORD  m_DamageMin;
	WORD  m_DamageMax;
	BYTE  m_SuccessfulBlocking;
	WORD  m_Defense;
	WORD  m_MagicDefense;
	BYTE  m_Speed;

	WORD  m_DamageMinOrigin;
	WORD  m_DefenseOrigin;
	WORD  m_Magic;

//#ifdef ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912
//	WORD  m_Curse;	// 저주력
//#endif

					//BYTE  m_Durability;
	float m_Durability;
	WORD  m_DurabilitySmall;

	float m_BaseDurability;		// 내구력1에 대한 수리비용(Value에서 계산해 둔다)

	BYTE  m_SpecialNum;
	BYTE  m_Special[MAX_ITEM_SPECIAL];
	BYTE  m_SpecialValue[MAX_ITEM_SPECIAL];	// 레벨

	WORD  m_RequireStrength;
	WORD  m_RequireDexterity;
	WORD  m_RequireEnergy;
	WORD  m_RequireLevel;

#ifdef EXPAND_ITEMSCRIPT_01_20050808
	WORD  m_RequireVitality;
#endif

#ifdef DARKLORD_WORK
	WORD  m_RequireLeaderShip;
	WORD  m_Leadership;		// 추가 통솔
#endif

	BYTE  m_RequireClass[MAX_CLASSTYPE];
	BYTE  m_Resistance[MAX_RESISTANCE];

	int   m_Value;
	DWORD m_SellMoney;	// 팔때 값
	DWORD m_BuyMoney;	// 살때 값

#ifdef PERSONAL_SHOP_20040113
	int	  m_iPShopValue;	// 개인상점에서 팔때의 값 (사용자 정의)
#endif

#ifdef ITEMDELETE_MODIFY_20040604	// 아이템 속성 중 아이템이 존재하는 아이템인가 아닌가에 대한 플래그
	bool  m_bItemExist;
#endif

	// 카오스 조합을 위한 아이템 가치가 바뀌기 전의 값 계산
	int   m_OldSellMoney;	// 팔때 값
	int   m_OldBuyMoney;	// 살때 값

	BYTE  m_Option1;	// 아이템 옵션 1 세팅되었는지?
	BYTE  m_Option2;	// 아이템 옵션 2 세팅되었는지?
	BYTE  m_Option3;	// 아이템 옵션 3 세팅되었는지?

	BYTE  m_NewOption;	// 새로 추가된 옵션, 비트 체크

	float  m_DurabilityState[4];
	float  m_CurrentDurabilityState;

#ifdef DARKLORD_WORK
	BYTE	m_SkillChange;
#endif

#ifdef NEW_SKILL_FORSKYLAND
	BYTE m_QuestItem;				// 퀘스트 아이템?
#endif

	BYTE	m_SetOption;
	BYTE	m_SetAddStat;			// 세트 아이템에 붙는 추가 스탯
	BYTE	m_IsValidItem;			// 유효한 아이템인가?(능력치가 되는 아이템인가?)

	BYTE	m_SkillResistance[MAX_RESISTANCE];



#ifdef DARKLORD_WORK	// 다크스피릿, 다크호스 등의 펫(레벨및경험치를 가지는) 아이템 정보 
	BOOL	m_IsLoadPetItemInfo;	// 펫아이템 정보를 얻어 왔었나?
	int		m_PetItem_Level;
	int		m_PetItem_Exp;
#endif

#ifdef ADD_JEWEL_OF_HARMONY_SYSTEM_20060530
	// 조화의 보석 강화 옵션
	BYTE	m_JewelOfHarmonyOption;
	// 조화의 보석 옵션 : 필요 스탯 감소
	WORD	m_HJOpStrength;
	WORD	m_HJOpDexterity;
#endif // ADD_JEWEL_OF_HARMONY_SYSTEM_20060530

#ifdef ADD_380ITEM_NEWOPTION_20060711
	// 아이템 추가 옵션 ( 확장 고려 )
	BYTE	m_ItemOptionEx;	// 상위 1 bit :  380 아이템 추가 옵션
#endif // ADD_380ITEM_NEWOPTION_20060711

#ifdef ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
	BYTE	m_BonusSocketOption;
	BYTE	m_SocketOption[MAX_SOCKET_SLOT];
#endif // ADD_ITEM_SOCKET_OPTION_EXTEND_20080422

#ifdef MODIFY_SOCKET_ITEM_NEW_OPTION_20080818
	// 소켓 아이템 내구력 강화 관련 변수
	BYTE	m_ImproveDurabilityRate;
#endif // MODIFY_SOCKET_ITEM_NEW_OPTION_20080818
public:
	CItem();
	void Convert(int type, BYTE Option1, BYTE Option2, BYTE Option3, BYTE Attribute2, BYTE SetOption, BYTE DbVersion); // idb

#ifdef ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
	//void Convert(int type, BYTE Option1 = 0, BYTE Option2 = 0, BYTE Option3 = 0, BYTE Attribute2 = 0, BYTE SetOption = 0, BYTE ItemEffectEx = 0, BYTE SocketOption[] = NULL, BYTE SocketBonusOption = 255, BYTE DbVersion = 3);
#else
#ifdef ITEM_INDEX_EXTEND_20050706
#ifdef ADD_380ITEM_NEWOPTION_20060711
	void Convert(int type, BYTE Option1 = 0, BYTE Option2 = 0, BYTE Option3 = 0, BYTE Attribute2 = 0, BYTE SetOption = 0, BYTE ItemEffectEx = 0, BYTE DbVersion = 3);
#else
//	void Convert(int type, BYTE Option1 = 0, BYTE Option2 = 0, BYTE Option3 = 0, BYTE Attribute2 = 0, BYTE SetOption = 0, BYTE DbVersion = 3);
#endif  // ADD_380ITEM_NEWOPTION_20060711
#else
	void Convert(int type, BYTE Option1 = 0, BYTE Option2 = 0, BYTE Option3 = 0, BYTE Attribute2 = 0, BYTE SetOption = 0, BYTE DbVersion = 1);
#endif
#endif // ADD_ITEM_SOCKET_OPTION_EXTEND_20080422

	void Value();

	void OldValue();

	BOOL GetSize(int &w, int &h);
	void Clear();
	BOOL IsItem();

	BOOL	IsSetItem();
	int		GetAddStatType();

#ifdef DARKLORD_WORK
	void	SetPetItemInfo(int petlevel, int petexp);
	// return value : level up : TRUE, else FALSE
	int		AddPetItemExp(int petexp);
	// return value : level down : TRUE, else FALSE
	int		DecPetItemExp(int percent);
	// 펫 아이템 가격 계산
	void	PetValue();
	// 펫 아이템 레벨 감소
	int		PetItemLevelDown(int exp);
#endif


	int  ItemDamageMin();
	int  ItemDefense();

//#ifdef ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912
//	int	 ItemCurse();
//#endif

#ifdef ADD_THIRD_WING_20070525	// IsClass() 수정
	BOOL IsClass(char aClass, int ChangeUP, int ThirdChangeUp);
#ifdef NEW_SKILL_FORSKYLAND
	BOOL IsClass(char aClass, int ChangeUP);
#else
	BOOL IsClass(char aClass);
#endif
#else
#ifdef NEW_SKILL_FORSKYLAND
	BOOL IsClass(char aClass, int ChangeUP);
#else
	BOOL IsClass(char aClass);
#endif
#endif	// ADD_THIRD_WING_20070525

	char *GetName();
	int  GetLevel(void);
	void PlusSpecial(int *Value, int Special);
	void PlusSpecialPercent(int* Value, int Special, WORD Percent);

	void PlusSpecialPercentEx(int* Value, int SourceValue, int Special);
	void SetItemPlusSpecialStat(WORD* Value, int Special);
	int	 GetWeaponType();
	void PlusSpecialSetRing(BYTE* Value);

	DWORD GetNumber();


	int IsExtItem();
	int IsExtLifeAdd();
	int IsExtManaAdd();
	int IsExtDamageMinus();
	int IsExtDamageReflect();
	int IsExtDefenseSuccessfull();
	int IsExtMonsterMoney();

	int IsExtExcellentDamage();
	int IsExtAttackRate();
	int IsExtAttackRate2();
	int IsExtAttackSpeed();
	int IsExtMonsterDieLife();
	int IsExtMonsterDieMana();

	int IsWingOpGetOnePercentDamage();
	int IsWingOpGetLifeToMonster();
	int IsWingOpGetManaToMoster();

	int IsDinorantReduceAttackDamaege();

#ifdef ADD_ITEM_FENRIR_01_20051110
	int IsFenrirIncLastAttackDamage();
	int IsFenrirDecLastAttackDamage();
#endif

#ifdef ADD_ILLUSION_FENRIR_20070703
	int IsIllusionFenrirOption();
#endif

#ifdef ADD_THIRD_WING_20070525	// 3차 날개 추가옵션 값 함수선언
	int GetIgnoreDefencePer();		// 적방무시 확률을 되돌려준다.
#endif


									// 내구력 감소

#ifdef ADD_NEW_ITEM_FOR_CASTLE_01_20041116
	int SimpleDurabilityDown(int iDur);
#endif

	int DurabilityDown(int dur, int aIndex);
	int DurabilityDown2(int dur, int aIndex);

	int NormalWeaponDurabilityDown(int defence, int aIndex);
	int BowWeaponDurabilityDown(int defence, int aIndex);
	int StaffWeaponDurabilityDown(int defence, int aIndex);

	int ArmorDurabilityDown(int damagemin, int aIndex);

	int	CheckDurabilityState();		// 내구도 상태 검사

#ifdef ADD_ITEM_SOCKET_OPTION_SYSTEM_20080415
									// 소켓 슬롯이 남아있는 아이템인지 확인
	bool	IsEnableSetSocketItem();
	// 소켓 슬롯을 생성
	void	MakeSocketSlot(BYTE SlotCount);
	// 시드스피어를 소켓에 적용
	bool	SetSeedSphere(BYTE SlotIndex, BYTE SeedIndex, BYTE SphereLevel);
	// 시드스피어를 소켓에서 삭제
	bool	RemoveSeedSphere(BYTE SlotIndex);
#endif // ADD_ITEM_SOCKET_OPTION_SYSTEM_20080415

	BOOL CheckExcOption(int iMinExcOption);
};

extern BOOL OpenItemScript(char *FileName);

#ifdef AUTH_GAMESERVER
extern BOOL OpenItemScript(char* Buffer, int iSize);
extern BOOL OpenItemNameScript(char *Buffer, int iSize);
#endif


#ifdef SCRIPT_DECODE_WORK
extern BOOL OpenItemScriptDecode(char *FileName);
extern BOOL OpenItemNameScriptDecode(char *FileName);
#endif

extern BOOL OpenItemNameScript(char *FileName);
extern int  ItemGetNumberMake(int type, int index);
extern void ItemGetSize(int index, int & width, int & height);
extern void ItemByteConvert3(LPBYTE buf, CItem item[], int maxitem);
extern void ItemByteConvert7(LPBYTE buf, CItem item[], int maxitem);
extern void ItemByteConvert10(LPBYTE buf, CItem item[], int maxitem);
extern void ItemByteConvert(LPBYTE buf, CItem item);

#ifdef ITEM_DBSIZE_EXTEND_20050706
extern void ItemByteConvert16(LPBYTE buf, CItem item[], int maxitem);
#endif

#ifdef ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
extern void ItemByteConvert(LPBYTE buf, int type, BYTE Option1, BYTE Option2, BYTE Option3, BYTE level, BYTE dur, BYTE Noption, BYTE SetOption = 0, BYTE JewelOfHarmonyOption = 0, BYTE ItemEffectEx = 0, BYTE SocketOption[] = NULL, BYTE SocketBonusOption = 255);
#else

#ifdef ADD_JEWEL_OF_HARMONY_SYSTEM_20060530
#ifdef ADD_380ITEM_NEWOPTION_20060711
extern void ItemByteConvert(LPBYTE buf, int type, BYTE Option1, BYTE Option2, BYTE Option3, BYTE level, BYTE dur, BYTE Noption, BYTE SetOption = 0, BYTE JewelOfHarmonyOption = 0, BYTE ItemEffectEx = 0);
#else
extern void ItemByteConvert(LPBYTE buf, int type, BYTE Option1, BYTE Option2, BYTE Option3, BYTE level, BYTE dur, BYTE Noption, BYTE SetOption = 0, BYTE JewelOfHarmonyOption = 0);
#endif // ADD_380ITEM_NEWOPTION_20060711
#else
#ifdef ADD_380ITEM_NEWOPTION_20060711
extern void ItemByteConvert(LPBYTE buf, int type, BYTE Option1, BYTE Option2, BYTE Option3, BYTE level, BYTE dur, BYTE Noption, BYTE SetOption = 0, BYTE ItemEffectEx = 0);
#else
extern void ItemByteConvert(LPBYTE buf, int type, BYTE Option1, BYTE Option2, BYTE Option3, BYTE level, BYTE dur, BYTE Noption, BYTE SetOption = 0);
#endif // ADD_380ITEM_NEWOPTION_20060711
#endif //ADD_JEWEL_OF_HARMONY_SYSTEM_20060530

#endif // ADD_ITEM_SOCKET_OPTION_EXTEND_20080422

extern int  GetLevelItem(int type, int index, int level);
extern BOOL zzzItemLevel(int type, int index, int level);
extern int GetSerialItem(int type);
extern void BufferItemtoConvert3(LPBYTE buf, int & type, BYTE & level, BYTE & op1, BYTE & op2, BYTE & op3, BYTE & dur);

// 아이템인가?
extern BOOL IsItem(int item_num);

// 아이템이 내구력을 가지고 있는가?
extern BOOL HasItemDurability(int index);

extern int ItemGetDurability(int index, int itemLevel, int ExcellentItem, int SetItem);
extern int ItemGetAttackDurability(int index);
extern int ItemGetDefenseDurability(int index);
extern void CalRepairRate(int type, int index, ITEM_ATTRIBUTE *p);

extern inline float	GetRepairItemRate(int index);
extern inline float	GetAllRepairItemRate(int index);

extern ITEM_ATTRIBUTE *GetItemAttr(int item_num);

#ifdef DARKLORD_WORK
#define MAX_DARK_SPIRIT_LEVEL	50
#define MAX_DARK_HORSE_LEVEL	50

class CPetItemExp
{
public:
	CPetItemExp()
	{
		m_DarkSpiritExpTable[0] = 0;
		m_DarkSpiritExpTable[1] = 0;
		for (int i = 2; i < MAX_DARK_SPIRIT_LEVEL + 2; i++)
		{
			m_DarkSpiritExpTable[i] = ((10 + i)*(i)*(i)*(i) * 100);
		}

		m_DarkHorseExpTable[0] = 0;
		m_DarkHorseExpTable[1] = 0;
		for (int i = 2; i < MAX_DARK_HORSE_LEVEL + 2; i++)
		{
			m_DarkHorseExpTable[i] = ((10 + i)*(i)*(i)*(i) * 100);
		}
	}
	int		m_DarkSpiritExpTable[MAX_DARK_SPIRIT_LEVEL + 2];
	int		m_DarkHorseExpTable[MAX_DARK_SPIRIT_LEVEL + 2];
};
#endif

#endif

