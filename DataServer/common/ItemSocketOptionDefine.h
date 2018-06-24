#ifndef _SOCKETOPTIONDEFINE_
#define _SOCKETOPTIONDEFINE_

#define MAX_SEED_TYPE		6
#define MAX_SEED_COUNT		50
#define MAX_SPHERE_LEVEL	5
#define MAX_SEEDSPHERE		MAX_SEED_COUNT

#define MAX_BONUS_OPTION	6
#define MAX_SET_OPTION		2

#define MAX_SOCKET_SLOT		5

#define MAX_EQUIP_SOCKET_ITEM	7

#define MAX_SEEDSPHERE_OPTION_DATA		( MAX_EQUIP_SOCKET_ITEM * MAX_SOCKET_SLOT )
#define MAX_BONUS_OPTION_DATA			MAX_EQUIP_SOCKET_ITEM
#define MAX_SET_OPTION_DATA				MAX_SET_OPTION
#define MAX_USER_SOCKET_OPTION_DATA		( ( MAX_EQUIP_SOCKET_ITEM * MAX_SOCKET_SLOT ) + MAX_BONUS_OPTION + MAX_SET_OPTION )

// ���� ������ ������ ���� ������
#define MAX_SEED_EXTRACT_SUCCESS_RATE			90
#define MAX_SEEDSPHERE_COMPOSITE_SUCCESS_RATE	90

//#define MAX_USER_SEEDSPHERE_EQUIP	7
//#define MAX_USER_SEEDSPHERE_DATA	( MAX_USER_SEEDSPHERE_EQUIP * MAX_SOCKET_SLOT )

#define MAX_OPTION_STRING	30

#define SOCKETSLOT_NONE		0xFF
#define SOCKETSLOT_EMPTY	0xFE

enum
{
	SEED_TYPE_NONE		= 0,
	SEED_TYPE_FIRE		= 1,
	SEED_TYPE_WATER		= 2,
	SEED_TYPE_ICE		= 3,
	SEED_TYPE_WIND		= 4,
	SEED_TYPE_LIGHTNING	= 5,
	SEED_TYPE_EARTH		= 6,
	SEED_TYPE_UNIQUE	= 7,
	SEED_TYPE_MAX
};

enum
{
	SOCKET_OPTION_TYPE_NONE		= 0,
	SOCKET_OPTION_TYPE_SEED		= 1,
	SOCKET_OPTION_TYPE_BONUS	= 2,
	SOCKET_OPTION_TYPE_SET		= 3,
};

enum
{
	SEED_OPTION_TYPE_NONE		= 0,
	SEED_OPTION_TYPE_VALUE		= 1,
	SEED_OPTION_TYPE_RATE		= 2,
	SEED_OPTION_TYPE_PER_LEVEL	= 3,
	SEED_OPTION_TYPE_PER_HP		= 4,
	SEED_OPTION_TYPE_PER_MP		= 5,
};

// ���ʽ� ���� �ɼ� Ÿ�� ����
enum
{
	// �����
	BONUS_OPTION_WEAPON_ATTACK_POWER			= 0,
	BONUS_OPTION_WEAPON_ATTACK_SKILL_POWER		= 1,
	// �����̷�
#ifdef MODIFY_SOCKET_ITEM_NEW_OPTION_20080818
	BONUS_OPTION_STAFF_ATTACK_POWER				= 2,
#else
	BONUS_OPTION_STAFF_MAGIC_POWER				= 2,
#endif // MODIFY_SOCKET_ITEM_NEW_OPTION_20080818
	BONUS_OPTION_STAFF_ATTACK_SKILL_POWER		= 3,
	// ����
	BONUS_OPTION_PROTECT_BLOCK_POWER			= 4,
	BONUS_OPTION_PROTECT_MAX_HP_INC				= 5,
};

enum
{
	SET_OPTION_DOUBLE_DAMAGE_RATE_INC			= 0,
	SET_OPTION_IGNORE_ENEMY_DEFENSE				= 1,
};

// �õ彺�Ǿ� �ε����� �ɷ�ġ Ÿ�� ����
enum
{
	// �� �Ӽ� (���� ��ȭ)
	SEED_EFFECT_TYPE_FIRE_BEGIN					= 0,
	SEED_EFFECT_TYPE_ATTACK_POWER				= 0,
	SEED_EFFECT_TYPE_ATTACK_SPEED				= 1,
	SEED_EFFECT_TYPE_MAX_ATTACK_POWER			= 2,
	SEED_EFFECT_TYPE_MIN_ATTACK_POWER			= 3,
	SEED_EFFECT_TYPE_MIN_MAX_ATTACK_POWER		= 4,
#ifdef MODIFY_SOCKET_ITEM_NEW_OPTION_20080818
	SEED_EFFECT_TYPE_REDUCE_AG_RATE				= 5,				// AG�Ҹ𷮰��� (�ű�)
#else
	SEED_EFFECT_TYPE_ATTACK_SKILL_POWER			= 5,				// ��ų���ݷ»�� (�� -> ����)
	SEED_EFFECT_TYPE_ATTACK_ACCURACY			= 6,				// ���ݼ��������� (�� -> ����)
	SEED_EFFECT_TYPE_PERSONAL_ATTACK_ACCURACY	= 7,				// ���ΰ��ݼ��������� (����)
	SEED_EFFECT_TYPE_MAGIC_POWER				= 8,				// �������� (����)
#endif // MODIFY_SOCKET_ITEM_NEW_OPTION_20080818
	SEED_EFFECT_TYPE_FIRE_END					= 9,
	// �� �Ӽ� (��� ��ȭ)
	SEED_EFFECT_TYPE_WATER_BEGIN				= 10,
	SEED_EFFECT_TYPE_SUCCESS_BLOCK				= 10,
	SEED_EFFECT_TYPE_BLOCK_POWER				= 11,
	SEED_EFFECT_TYPE_SHIELD_BLOCK_POWER			= 12,
	SEED_EFFECT_TYPE_REDUCE_DAMAGE				= 13,
	SEED_EFFECT_TYPE_REFLECT_DAMAGE				= 14,
	SEED_EFFECT_TYPE_WATER_END					= 15,
	// ���� �Ӽ� (���� ��ȭ)
	SEED_EFFECT_TYPE_ICE_BEGIN					= 16,
	SEED_EFFECT_TYPE_MONSTER_KILL_REFILL_HP		= 16,
	SEED_EFFECT_TYPE_MONSTER_KILL_REFILL_MP		= 17,
#ifdef MODIFY_SOCKET_ITEM_NEW_OPTION_20080818
	SEED_EFFECT_TYPE_ATTACK_SKILL_POWER			= 18,
	SEED_EFFECT_TYPE_ATTACK_ACCURACY			= 19,
	SEED_EFFECT_TYPE_ITEM_DURABILITY_IMPROVE	= 20,				// �����۳����°�ȭ (�ű�)
#else
	SEED_EFFECT_TYPE_SD_POINT_REDUCE_RATE_INC	= 18,				// ��ų���ݷ»�� (�� -> ����)
	SEED_EFFECT_TYPE_SD_IGNORE_RATE_INC			= 19,				// ���ݼ��������� (�� -> ����)
#endif // MODIFY_SOCKET_ITEM_NEW_OPTION_20080818
	SEED_EFFECT_TYPE_ICE_END					= 20,
	// �ٶ� �Ӽ� (�� ��ȭ)
	SEED_EFFECT_TYPE_WIND_BEGIN					= 21,
	SEED_EFFECT_TYPE_REFILL_HP_INC				= 21,
	SEED_EFFECT_TYPE_MAX_HP_INC					= 22,
	SEED_EFFECT_TYPE_MAX_MP_INC					= 23,
	SEED_EFFECT_TYPE_REFILL_MP_INC				= 24,
	SEED_EFFECT_TYPE_MAX_AG_INC					= 25,
	SEED_EFFECT_TYPE_REFILL_AG_INC				= 26,
	SEED_EFFECT_TYPE_MONSTER_KILL_ZEN_INC		= 27,
	SEED_EFFECT_TYPE_WIND_END					= 28,
	// ���� �Ӽ� (���� ��ȭ)
	SEED_EFFECT_TYPE_THUNDER_BEGIN				= 29,
	SEED_EFFECT_TYPE_EXCELLENT_DAMAGE_INC		= 29,
	SEED_EFFECT_TYPE_EXCELLENT_DAMAGE_RATE_INC	= 30,
	SEED_EFFECT_TYPE_CRITICAL_DAMAGE_INC		= 31,
	SEED_EFFECT_TYPE_CRITICAL_DAMAGE_RATE_INC	= 32,
	SEED_EFFECT_TYPE_THUNDER_END				= 33,
	// �� �Ӽ� (���� ��ȭ)
	SEED_EFFECT_TYPE_EARTH_BEGIN				= 34,
	SEED_EFFECT_TYPE_STRENGTH_INC				= 34,
	SEED_EFFECT_TYPE_DEXTERITY_INC				= 35,
	SEED_EFFECT_TYPE_VITALITY_INC				= 36,
	SEED_EFFECT_TYPE_ENERGY_INC					= 37,
	SEED_EFFECT_TYPE_REQUIRE_STRENGTH_DEC		= 38,
	SEED_EFFECT_TYPE_REQUIRE_DEXTERITY_DEC		= 39,
	SEED_EFFECT_TYPE_EARTH_END					= 40,
	// ����ũ �ɼ�
	SEED_EFFECT_TYPE_UNIQUE_BEGIN				= 41,
	SEED_EFFECT_TYPE_UNIQUE_1					= 41,
	SEED_EFFECT_TYPE_UNIQUE_2					= 42,
	SEED_EFFECT_TYPE_UNIQUE_END					= 43,
	// ��Ʈ �ɼ�
	SEED_EFFECT_TYPE_SET_BEGIN					= 44,
	SEED_EFFECT_TYPE_SET_DOUBLE_DAMAGE_RATE_INC	= 44,
	SEED_EFFECT_TYPE_SET_IGNORE_ENERMY_DEFENSE	= 45,
	SEED_EFFECT_TYPE_SET_END					= 45,
};

typedef struct
{
	BYTE		m_SocketOptionIndex;
	BYTE		m_SocketOptionValueType;
	WORD		m_SocketOptionValue;
	BYTE		m_SocketOptionCount;

	void Clear()
	{
		m_SocketOptionIndex = SOCKETSLOT_NONE;
		m_SocketOptionValue = 0;
		m_SocketOptionValueType = 0;
		m_SocketOptionCount = 0;
	}
}SOCKET_OPTION_LIST, *LPSOCKET_OPTION_LIST;

#endif // _SOCKETOPTIONDEFINE_