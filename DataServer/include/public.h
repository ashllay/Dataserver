﻿#ifndef __PUBLIC_H__
#define __PUBLIC_H__

enum ClassNumber
{
	CLASS_WIZARD,
	CLASS_KNIGHT,
	CLASS_ELF,
	CLASS_MAGUMSA,
	CLASS_DARKLORD, 
	CLASS_SUMMONER,
	CLASS_MONK,
	CLASS_LANCER
};

#define MAX_MAGIC	150

enum CHARACTER_AUTO_RECUPERATION_TIME
{
	CART_10_SEC = 1000 * 10,
	CART_15_SEC = 1000 * 15,
	CART_25_SEC = 1000 * 25,
};

enum HP_MP_AG_VALUE_PER_TIME
{
	VPT_HP_MP_AG_1_PER_1_SEC = 1,
	VPT_HP_MP_AG_5_PER_1_SEC = 5,
	VPT_HP_MP_AG_10_PER_1_SEC = 10
};

enum eSkillType
{
	AT_SKILL_POISON = 0x1,
	AT_SKILL_METEO = 0x2,
	AT_SKILL_THUNDER = 0x3,
	AT_SKILL_FIREBALL = 0x4,
	AT_SKILL_FLAME = 0x5,
	AT_SKILL_TELEPORT = 0x6,
	AT_SKILL_SLOW = 0x7,
	AT_SKILL_STORM = 0x8,
	AT_SKILL_EVIL = 0x9,
	AT_SKILL_HELL = 0xA,
	AT_SKILL_POWERWAVE = 0xB,
	AT_SKILL_FLASH = 0xC,
	AT_SKILL_BLAST = 0xD,
	AT_SKILL_INFERNO = 0xE,
	AT_SKILL_TARGET_TELEPORT = 0xF,
	AT_SKILL_MAGICDEFENSE = 0x10,
	AT_SKILL_ENERGYBALL = 0x11,
	AT_SKILL_BLOCKING = 0x12,
	AT_SKILL_SWORD1 = 0x13,
	AT_SKILL_SWORD2 = 0x14,
	AT_SKILL_SWORD3 = 0x15,
	AT_SKILL_SWORD4 = 0x16,
	AT_SKILL_SWORD5 = 0x17,
	AT_SKILL_CROSSBOW = 0x18,
	AT_SKILL_BOW = 0x19,
	AT_SKILL_HEALING = 0x1A,
	AT_SKILL_DEFENSE = 0x1B,
	AT_SKILL_ATTACK = 0x1C,
	AT_SKILL_CALLMON1 = 0x1E,
	AT_SKILL_CALLMON2 = 0x1F,
	AT_SKILL_CALLMON3 = 0x20,
	AT_SKILL_CALLMON4 = 0x21,
	AT_SKILL_CALLMON5 = 0x22,
	AT_SKILL_CALLMON6 = 0x23,
	AT_SKILL_CALLMON7 = 0x24,
	AT_SKILL_WHEEL = 0x29,
	AT_SKILL_BLOWOFFURY = 0x2A,
	AT_SKILL_STRIKE = 0x2B,
	AT_SKILL_KNIGHTSPEAR = 0x2F,
	AT_SKILL_KNIGHTADDLIFE = 0x30,
	AT_SKILL_KNIGHTDINORANT = 0x31,
	AT_SKILL_ELFHARDEN = 0x33,
	AT_SKILL_PENETRATION = 0x34,
	AT_SKILL_DEFENSEDOWN = 0x37,
	AT_SKILL_SWORD6 = 0x38,
	AT_SKILL_5CROSSBOW = 0x36,
	AT_SKILL_EXPPOISON = 0x26,
	AT_SKILL_EXPICE = 0x27,
	AT_SKILL_EXPHELL = 0x28,
	AT_SKILL_EXPHELL_START = 0x3A,
	AT_SKILL_IMPROVE_AG_REFILL = 0x35,
	AT_SKILL_DEVILFIRE = 0x32,
	AT_SKILL_COMBO = 0x3B,
	AT_SKILL_SPEAR = 0x3C,
	AT_SKILL_FIREBURST = 0x3D,
	AT_SKILL_DARKHORSE_ATTACK = 0x3E,
	AT_SKILL_RECALL_PARTY = 0x3F,
	AT_SKILL_ADD_CRITICALDAMAGE = 0x40,
	AT_SKILL_ELECTRICSPARK = 0x41,
	AT_SKILL_LONGSPEAR = 0x42,
	AT_SKILL_RUSH = 0x2C,
	AT_SKILL_JAVALIN = 0x2D,
	AT_SKILL_DEEPIMPACT = 0x2E,
	AT_SKILL_ONE_FLASH = 0x39,
	AT_SKILL_DEATH_CANNON = 0x49,
	AT_SKILL_SPACE_SPLIT = 0x4A,
	AT_SKILL_BRAND_OF_SKILL = 0x4B,
	AT_SKILL_STUN = 0x43,
	AT_SKILL_REMOVAL_STUN = 0x44,
	AT_SKILL_ADD_MANA = 0x45,
	AT_SKILL_INVISIBLE = 0x46,
	AT_SKILL_REMOVAL_INVISIBLE = 0x47,
	AT_SKILL_REMOVAL_MAGIC = 0x48,
	AT_SKILL_FENRIR_ATTACK = 0x4C,
	AT_SKILL_SUMMON = 0xC8,
	AT_SKILL_IMMUNE_TO_MAGIC = 0xC9,
	AT_SKILL_IMMUNE_TO_HARM = 0xCA,
};

enum eOptionType
{
	AT_IMPROVE_DAMAGE = 0x50,
	AT_IMPROVE_MAGIC = 0x51,
	AT_IMPROVE_BLOCKING = 0x52,
	AT_IMPROVE_DEFENSE = 0x53,
	AT_LUCK = 0x54,
	AT_LIFE_REGENERATION = 0x55,
	AT_IMPROVE_LIFE = 0x56,
	AT_IMPROVE_MANA = 0x57,
	AT_DECREASE_DAMAGE = 0x58,
	AT_REFLECTION_DAMAGE = 0x59,
	AT_IMPROVE_BLOCKING_PERCENT = 0x5A,
	AT_IMPROVE_GAIN_GOLD = 0x5B,
	AT_EXCELLENT_DAMAGE = 0x5C,
	AT_IMPROVE_DAMAGE_LEVEL = 0x5D,
	AT_IMPROVE_DAMAGE_PERCENT = 0x5E,
	AT_IMPROVE_MAGIC_LEVEL = 0x5F,
	AT_IMPROVE_MAGIC_PERCENT = 0x60,
	AT_IMPROVE_ATTACK_SPEED = 0x61,
	AT_IMPROVE_GAIN_LIFE = 0x62,
	AT_IMPROVE_GAIN_MANA = 0x63,
	AT_PLUS_WING_MAXLIFE = 0x64,
	AT_PLUS_WING_MAXMANA = 0x65,
	AT_PLUS_ONE_PERCENT_DAMAGE = 0x66,
	AT_IMPROVE_AG_MAX = 0x67,
	AT_DAMAGE_ABSORB = 0x68,
	AT_PLUS_WING_ADD_LEADERSHIP = 0x69,
	AT_PLUS_FENRIR_INCREASE_LAST_DAMAGE = 0x6A,
	AT_PLUS_FENRIR_DECREASE_LAST_DAMAGE = 0x6B,
	AT_5PER_IGNORE_DEFENSE = 0x6C,
	AT_5PER_ATTACK_TURNING = 0x6D,
	AT_RECOVER_100PER_LIFE = 0x6E,
	AT_RECOVER_100PER_MASIC = 0x6F,
	AT_PLUS_ILLUSION_FENRIR_OPTION = 0x70,
	AT_IMPROVE_CURSE = 0x71,
	AT_4PER_IGNORE_DEFENSE = 0x72,
	AT_4PER_RECOVER_100PER_LIFE = 0x73,
	AT_4PER_DOUBLE_DAMAGE = 0x74,
	AT_EXCELLENT_OPTION_EX_WEAPON_1EA = 0x75,
	AT_EXCELLENT_OPTION_EX_WEAPON_2EA = 0x76,
	AT_EXCELLENT_OPTION_EX_WEAPON_3EA = 0x77,
	AT_EXCELLENT_OPTION_EX_ARMOR_1EA = 0x78,
	AT_EXCELLENT_OPTION_EX_ARMOR_2EA = 0x79,
	AT_EXCELLENT_OPTION_EX_ARMOR_3EA = 0x7A,
	AT_ATTACK1 = 0x78,
	AT_ATTACK2 = 0x79,
	AT_STAND1 = 0x7A,
	AT_STAND2 = 0x7B,
	AT_MOVE1 = 0x7C,
	AT_MOVE2 = 0x7D,
	AT_DAMAGE1 = 0x7E,
	AT_DIE1 = 0x7F,
	AT_SIT1 = 0x80,
	AT_POSE1 = 0x81,
	AT_HEALING1 = 0x82,
	AT_GREETING1 = 0x83,
	AT_GOODBYE1 = 0x84,
	AT_CLAP1 = 0x85,
	AT_GESTURE1 = 0x86,
	AT_DIRECTION1 = 0x87,
	AT_UNKNOWN1 = 0x88,
	AT_CRY1 = 0x89,
	AT_CHEER1 = 0x8A,
	AT_AWKWARD1 = 0x8B,
	AT_SEE1 = 0x8C,
	AT_WIN1 = 0x8D,
	AT_SMILE1 = 0x8E,
	AT_SLEEP1 = 0x8F,
	AT_COLD1 = 0x90,
	AT_AGAIN1 = 0x91,
	AT_RESPECT1 = 0x92,
	AT_SALUTE1 = 0x93,
	AT_RUSH1 = 0x94,
	AT_SET_RING_OPTION_ADD_SKILLDAMAGE = 0x95,
	AT_SET_OPTION_IMPROVE_STRENGTH = 0xA0,
	AT_SET_OPTION_IMPROVE_DEXTERITY = 0xA1,
	AT_SET_OPTION_IMPROVE_ENERGY = 0xA2,
	AT_SET_OPTION_IMPROVE_VITALITY = 0xA3,
	AT_SET_OPTION_IMPROVE_LEADERSHIP = 0xA4,
	AT_SET_OPTION_IMPROVE_MINATTACKDAMAGE = 0xA5,
	AT_SET_OPTION_IMPROVE_MAXATTACKDAMAGE = 0xA6,
	AT_SET_OPTION_IMPROVE_MAGICDAMAGE = 0xA7,
	AT_SET_OPTION_IMPROVE_DAMAGE = 0xA8,
	AT_SET_OPTION_IMPROVE_ATTACKRATE = 0xA9,
	AT_SET_OPTION_IMPROVE_DEFENCE = 0xAA,
	AT_SET_OPTION_IMPROVE_MAXLIFE = 0xAB,
	AT_SET_OPTION_IMPROVE_MAXMANA = 0xAC,
	AT_SET_OPTION_IMPROVE_MAXAG = 0xAD,
	AT_SET_OPTION_IMPROVE_AG_VALUE = 0xAE,
	AT_SET_OPTION_IMPROVE_CRITICALDAMAGE_SUCCESS = 0xAF,
	AT_SET_OPTION_IMPROVE_CRITICALDAMAGE = 0xB0,
	AT_SET_OPTION_IMPROVE_EX_DAMAGE_SUCCESS = 0xB1,
	AT_SET_OPTION_IMPROVE_EX_DAMAGE = 0xB2,
	AT_SET_OPTION_IMPROVE_SKILLDAMAGE = 0xB3,
	AT_SET_OPTION_DOUBLE_DAMAGE = 0xB4,
	AT_SET_OPTION_DEFENCE_IGNORE = 0xB5,
	AT_SET_OPTION_IMPROVE_SHIELD_DEFENCE = 0xB6,
	AT_SET_OPTION_TWO_HAND_SWORD_IMPROVE_DAMAGE = 0xB7,
	AT_SET_OPTION_IMPROVE_ATTACKDAMAGE_WITH_STR = 0xB8,
	AT_SET_OPTION_IMPROVE_ATTACKDAMAGE_WITH_DEX = 0xB9,
	AT_SET_OPTION_IMPROVE_DEFENCE_WITH_DEX = 0xBA,
	AT_SET_OPTION_IMPROVE_DEFENCE_WITH_VIT = 0xBB,
	AT_SET_OPTION_IMPROVE_MAGICDAMAGE_WITH_ENERGY = 0xBC,
	AT_SET_OPTION_ICE_MASTERY = 0xBD,
	AT_SET_OPTION_POSION_MASTERY = 0xBE,
	AT_SET_OPTION_THUNDER_MASTERY = 0xBF,
	AT_SET_OPTION_FIRE_MASTERY = 0xC0,
	AT_SET_OPTION_EARTH_MASTERY = 0xC1,
	AT_SET_OPTION_WIND_MASTERY = 0xC2,
	AT_SET_OPTION_WATER_MASTERY = 0xC3,
	AT_SET_IMPROVE_STRENGTH = 0xC4,
	AT_SET_IMPROVE_DEXTERITY = 0xC5,
	AT_SET_IMPROVE_ENERGY = 0xC6,
	AT_SET_IMPROVE_VITALITY = 0xC7,
};

enum GUILD_STATUS
{
	G_NONE = 0xFFFFFFFF,
	G_PERSON = 0x0,
	G_MASTER = 0x80,
	G_SUB_MASTER = 0x40,
	G_BATTLE_MASTER = 0x20,
};

enum
{
	PRE_LEAGUE = 0x0,
	SEMI_LEAGUE = 0x1,
	FINAL_LEAGUE = 0x2,
	LAST_WINNER = 0x3,
};

enum __DSF_TYPE
{
	DSF_TYPE_NONE = 0x0,
	DSF_TYPE_LEAGUE = 0x1,
	DSF_TYPE_SEMIFINAL = 0x2,
	DSF_TYPE_FINAL = 0x3,
	DSF_TYPE_WINNER = 0x4,
};

#endif

