#ifndef __ITEMDEF_H__
#define __ITEMDEF_H__

#define MAX_ITEM_TYPE		 32//16					// #define ITEM_INDEX_EXTEND_20050706
#if GAME_VERSION >= G_V_S1_512
#define MAX_ITEM_INDEX		 512				// #define ITEM_INDEX_EXTEND_20050706
#else
#define MAX_ITEM_INDEX     32
#endif
//#define MAX_ITEM_TYPE      16
//#define MAX_ITEM_INDEX     32
#define MAX_ITEM           (MAX_ITEM_TYPE*MAX_ITEM_INDEX)

#define MAX_ITEM_SPECIAL   8

#define ITEM_LEVEL_NORMAL  8

// 금의 타입과 인덱스
#ifdef ITEM_INDEX_EXTEND_20050706
#define GOLD_TYPE_INDEX			((14<<9)+15)	// #define ITEM_INDEX_EXTEND_20050706
#else
#define GOLD_TYPE_INDEX			((14<<5)+15)
#endif

//equipment index
#define EQUIPMENT_WEAPON_RIGHT 0
#define EQUIPMENT_WEAPON_LEFT  1
#define EQUIPMENT_HELM         2
#define EQUIPMENT_ARMOR        3
#define EQUIPMENT_PANTS        4
#define EQUIPMENT_GLOVES       5
#define EQUIPMENT_BOOTS        6
#define EQUIPMENT_WING         7
#define EQUIPMENT_HELPER       8
#define EQUIPMENT_AMULET       9
#define EQUIPMENT_RING_RIGHT   10
#define EQUIPMENT_RING_LEFT    11
#define EQUIPMENT_GOLD         12
//#define MAX_EQUIPMENT          EQUIPMENT_GOLD+1

//item index
#define ITEM_SWORD		 0   //pal,etc
#define ITEM_AXE		 (MAX_ITEM_INDEX*1)  //ran,dru
#define ITEM_MACE		 (MAX_ITEM_INDEX*2)  //ran,nec
#define ITEM_SPEAR		 (MAX_ITEM_INDEX*3)  //ama
#define ITEM_BOW		 (MAX_ITEM_INDEX*4) //ama
#define ITEM_STAFF	 	 (MAX_ITEM_INDEX*5) //soc
#define ITEM_SHIELD		 (MAX_ITEM_INDEX*6)
#define ITEM_HELM		 (MAX_ITEM_INDEX*7)
#define ITEM_ARMOR		 (MAX_ITEM_INDEX*8)
#define ITEM_PANTS		 (MAX_ITEM_INDEX*9)
#define ITEM_GLOVE		 (MAX_ITEM_INDEX*10)
#define ITEM_BOOT		 (MAX_ITEM_INDEX*11)
#define ITEM_WING		 (MAX_ITEM_INDEX*12)
#define ITEM_HELPER		 (MAX_ITEM_INDEX*13)
//#define ITEM_RING		 224
#define ITEM_POTION		 (MAX_ITEM_INDEX*14)
#define ITEM_ETC		 (MAX_ITEM_INDEX*15)

//weapon special
#define PLUS_POISON                1
#define PLUS_COLD                  2
#define PLUS_FIRE                  4
#define PLUS_ATTACK_SPEED          8  //race
#define PLUS_ATTACK_RATING         16 //race
#define PLUS_DAMAGE                32 //race
#define PLUS_MAGIC_DAMAGE          64 //race

//armor special
#define PLUS_DEXTERIRY             1
#define PLUS_DEFENSE               2
#define PLUS_MAGIC_DEFENSE         4
#define PLUS_CHANCE_TO_BLOCK       8  //shield
#define PLUS_WALK_SPEED            16 //boot

//helper special
#define PLUS_STRENGTH              1
#define PLUS_LIFE                  2
#define PLUS_LIFE_STOLEN           4
#define PLUS_MANA                  8
#define PLUS_MANA_STOLEN           16
#define PLUS_LIFE_REGENERATION     32 //helper
#define PLUS_SKILL_LEVEL           64 //helper


//Wing special	(천공 새로운 날개를 위한 옵션 : 엑설런트 옵션으로 사용된다)
#define PLUS_WING_MAXLIFE				0x01		// 최대 HP+50
#define PLUS_WING_MAXMANA				0x02		// 최대 MP+50
#define PLUS_WING_ONE_PERCENT_DAMAGE	0x04		// 3% 확률로 몬스터 방어력 무시 공격 
#define PLUS_WING_ADD_LEADERSHIP		0x08		// 통솔증가(+10+레벨*5)
//#define PLUS_WING_GETLIFE_TO_MONSTER	0x08		// 몬스터에게 받는 최대 타격 데미지에서 HP 10%획득
#define PLUS_WING_GETMANA_TO_MONSTER	0x10		// 몬스터에게 받는 최대 타격 데미지에서 MP 10%획득
#define PLUS_WING_OP1_TYPE				0x20		// OP1 타입

// Dinorant special
#define PLUS_DINORANT_PLUS_REDUCE_DAMAGE	0x01	// 5%추가 데미지 흡수
#define PLUS_DINORANT_PLUS_MAX_AG			0x02	// 최대 AG+50증가
#define PLUS_DINORANT_PLUS_ATTACKSPEED		0x04	// 공격속도 +5

// Fenrir special (펜릴 특수 옵션 : 엑설런트 옵션을 사용한다.)
#define PLUS_FENRIR_INCREASE_LAST_DAMAGE	0x01	// 최종 데미지 증가
#define PLUS_FENRIR_DECREASE_LAST_DAMAGE	0x02	// 최종 데미지 감소

// #ifdef ADD_ILLUSION_FENRIR_20070703	// 환영 펜릴 추가
#define PLUS_ILLUSION_FENRIR_OPTION			0x04	// HP 증가, MP증가, 공격력증가, 마력 증가
// #endif

//#ifdef ADD_THIRD_WING_20070525		// 3차날개 랜덤 옵션 정의: 엑설런트 옵션을 사용한다.
#define	PLUS_THIRD_WING_5PER_IGNORE_DEFENSE		0x01	// (공격이 명중한 경우) %5 확률로 적 방어력 무시
#define	PLUS_THIRD_WING_5PER_ATTACK_TURNING		0x02	// (공격당한 경우) 5% 확률로 적 공격력 50% 돌려줌
#define	PLUS_THIRD_WING_RECOVER_100PER_LIFE		0x04	// (공격당한 경우) 5% 확률로 유저 생명 100% 순간 회복
#define	PLUS_THIRD_WING_RECOVER_100PER_MASIC	0x08	// (공격당한 경우) 5% 확률로 유저 마력 100% 순간 회복

// 3차날개 옵션3 - 엑설런트 옵션을 사용한다.
#define PLUS_THIRD_WING_RAND_OPT_1				0x10
#define PLUS_THIRD_WING_RAND_OPT_2				0x20
//#endif

// 스킬
/*#define SKILL_POISON               1
#define SKILL_METEORITE            2
#define SKILL_THUNDER              3
#define SKILL_BLOCKING             4
#define SKILL_SWORD1               5
#define SKILL_SWORD2               6
#define SKILL_SWORD3               7
#define SKILL_SWORD4               8
*/

typedef struct
{
	char Name[32];

	bool HaveItemInfo;	// 아이템 정보를 가지고 있는가?

	bool TwoHand;

	BYTE Level;
	BYTE Width;
	BYTE Height;
	char Serial;
	BYTE OptionFlag;
	BYTE MondownFlag;
	BYTE AttackSpeed;
	BYTE WalkSpeed;
	BYTE DamageMin;
	BYTE DamageMax;	
	BYTE SuccessfulBlocking;
	BYTE Defense;
	BYTE MagicDefense;
	BYTE Speed;
	BYTE Durability;
	BYTE MagicDurability;
	BYTE AttackDur;
	BYTE DefenceDur;

	WORD RequireStrength;
	WORD RequireDexterity;
	WORD RequireEnergy;
	WORD RequireLevel;

	WORD Value;
	BYTE RequireClass[MAX_CLASSTYPE];
	BYTE Resistance[MAX_RESISTANCE];
	
#ifdef EXPAND_ITEMSCRIPT_01_20050808
	WORD RequireVitality;
#endif


	int	 BuyMoney;	// 판매가격

	int	 MagicPW;	// 마력

	float RepaireMoneyRate;		// 기본 수리 비용 비율
	float AllRepaireMoneyRate;	// 완전 수리 비용 비율
	
#ifdef NEW_SKILL_FORSKYLAND
	BYTE QuestItem;				// 퀘스트 아이템?
#endif

	BYTE	SetAttr;				// 세트 속성
	BYTE	ResistanceType;			// 저항력 타입(BYTE Resistance[MAX_RESISTANCE];의 절대값)

	int		ItemSlot;				// 아이템 슬롯 위치
	int		SkillType;				// 무기에 들어 가는 스킬의 타입

#ifdef DARKLORD_WORK
	int		RequireLeadership;		// 요구 통솔
#endif
	//season12
	int ItemCategory;
	char ModelPath[32];
	char ModelFile[32];
	BYTE Dump;
	BYTE Transaction;
	BYTE PersonalStore;
	BYTE StoreWarehouse;
	BYTE SellToNPC;
	BYTE Repair;
	BYTE ItemKindA;
	BYTE ItemKindB;
	BYTE ItemOverlap;
} ITEM_ATTRIBUTE;


#endif

