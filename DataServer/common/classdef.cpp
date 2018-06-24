// classdef.cpp: implementation of the classdef class.
// 캐릭터 기본 정보를 다루는 클래스다.
// 캐릭터가 생성될때 이 클래스의 정보를 바탕으로 만들어진다.
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "..\\Common\\classdef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif




classdef::classdef()
{
	m_BabubBanJiCreate = 0;
}

classdef::~classdef()
{
}

void classdef::Init()
{
	/**********************************************************************************************************************
	Class * Str * Dex * Vit * Energy * Life * Mana * LevelLife * LevelMana * VitalityToLife * EnergyToMana , Leadership
	***********************************************************************************************************************/
	SetCharacter(CLASS_WIZARD, 18, 18, 15, 30, 60.0, 60.0, 1.0, 2.0, 2.0, 2.0, 0);
	SetCharacter(CLASS_KNIGHT, 28, 20, 25, 10, 110.0, 20.0, 2.0, 0.5, 3.0, 1.0, 0);
	SetCharacter(CLASS_ELF, 22, 25, 20, 15, 80.0, 30.0, 1.0, 1.5, 2.0, 1.5, 0);
	SetCharacter(CLASS_MAGUMSA, 26, 26, 26, 26, 110.0, 60.0, 1.0, 1.0, 2.0, 2.0, 0);
	SetCharacter(CLASS_DARKLORD, 26, 20, 20, 15, 90.0, 40.0, 1.5, 1.0, 2.0, 1.5, 25);
	SetCharacter(CLASS_SUMMONER, 21, 21, 18, 23, 70.0, 40.0, 1.0, 1.5, 2.0, 1.5, 0);
	SetCharacter(CLASS_MONK, 32, 27, 25, 20, 100.0, 40.0, 1.3, 1.0, 2.0, 1.3, 0);
	SetCharacter(CLASS_LANCER, 30, 30, 25, 24, 110.0, 40.0, 2.0, 1.0, 2.0, 1.0, 0);
}

//////////////////////////////////////////////////////////////////////
// 입력된 인자로 기본 캐릭터를 만든다.
//////////////////////////////////////////////////////////////////////
void classdef::SetCharacter(int Class, int Str, int Dex, int Vit, int Energy, float Life, float Mana, float LevelLife, float LevelMana, float VitalityToLife, float EnergyToMana, int Leadership)
{
	DefClass[Class].Experience = 0;
	DefClass[Class].Strength = Str;
	DefClass[Class].Dexterity = Dex;
	DefClass[Class].Vitality = Vit;
	DefClass[Class].Energy = Energy;
	DefClass[Class].Life = Life;
	DefClass[Class].MaxLife = Life;
	DefClass[Class].LevelLife = LevelLife;
	DefClass[Class].Mana = Mana;
	DefClass[Class].MaxMana = Mana;
	DefClass[Class].LevelMana = LevelMana;
	DefClass[Class].VitalityToLife = VitalityToLife;
	DefClass[Class].EnergyToMana = EnergyToMana;
	DefClass[Class].Leadership = Leadership;

	SetEquipment(Class);
	SetJumpingEquipment(Class);
}

//////////////////////////////////////////////////////////////////////
// 캐릭터 기본 장비를 장착시킨다.
//////////////////////////////////////////////////////////////////////
void classdef::SetEquipment(int Class)
{
	int n;
	int right_type;
	int def_type;

	def_type = 0;
	right_type = 0;
	for (n = 0; n < 14; ++n)
		DefClass[Class].Equipment[n].Clear();
	switch (Class)
	{
	case 1:
		def_type = ItemGetNumberMake(1, 0);
		break;
	case 2:
		def_type = ItemGetNumberMake(4, 15);
		right_type = ItemGetNumberMake(4, 0);
		break;
	case 3:
		def_type = ItemGetNumberMake(6, 0);
		right_type = ItemGetNumberMake(0, 1);
		break;
	case 4:
		def_type = ItemGetNumberMake(6, 0);
		right_type = ItemGetNumberMake(0, 1);
		break;
	case 5:
		def_type = ItemGetNumberMake(1, 0);
		break;
	case 6:
		def_type = ItemGetNumberMake(1, 0);
		break;
	case 7:
		def_type = ItemGetNumberMake(6, 0);
		right_type = ItemGetNumberMake(1, 0);
		break;
	default:
		break;
	}
	if (Class)
	{
		if (Class == 4)
		{
			this->DefClass[Class].Equipment[0].m_Level = 0;
			this->DefClass[Class].Equipment[1].m_Level = 0;
			this->DefClass[Class].Equipment[EQUIPMENT_WEAPON_RIGHT].Convert(right_type, 0, 0, 0, 0, 0, 3);
			this->DefClass[Class].Equipment[1].Convert(def_type, 0, 0, 0, 0, 0, 3);

						//DefClass[Class].Equipment[EQUIPMENT_WEAPON_RIGHT].Convert(right_type, 0, 0, 0, 0, 0, 3);
						//DefClass[Class].Equipment[EQUIPMENT_WEAPON_LEFT].Convert(def_type, 0, 0, 0, 0, 0, 3);
		}
		else if (Class != 2 && Class != 3)
		{
			if (Class == 5)
			{
				this->DefClass[Class].Equipment[0].m_Level = 0;
				//this->DefClass[5].Equipment, def_type, 0, 0, 0, 0, 0, 3);
				DefClass[Class].Equipment[EQUIPMENT_WEAPON_RIGHT].Convert(def_type, 0, 0, 0, 0, 0, 3);
			}
			else if (Class == 7)
			{
				this->DefClass[Class].Equipment[0].m_Level = 0;
				this->DefClass[Class].Equipment[1].m_Level = 0;
				//this->DefClass[7].Equipment, right_type, 0, 0, 0, 0, 0, 3);
				DefClass[Class].Equipment[EQUIPMENT_WEAPON_RIGHT].Convert(right_type, 0, 0, 0, 0, 0, 3);
				//this->DefClass[7].Equipment[1], def_type, 0, 0, 0, 0, 0, 3);
				DefClass[Class].Equipment[EQUIPMENT_WEAPON_LEFT].Convert(def_type, 0, 0, 0, 0, 0, 3);
			}
			else
			{
				this->DefClass[Class].Equipment[0].m_Level = 0;
				//this->DefClass[Class].Equipment, def_type, 0, 0, 0, 0, 0, 3);
				DefClass[Class].Equipment[EQUIPMENT_WEAPON_RIGHT].Convert(def_type, 0, 0, 0, 0, 0, 3);
			}
		}
		else
		{
			this->DefClass[Class].Equipment[0].m_Level = 0;
			this->DefClass[Class].Equipment[1].m_Level = 0;
			//this->DefClass[Class].Equipment, right_type, 0, 0, 0, 0, 0, 3);
			//&this->DefClass[Class].Equipment[1], def_type, 0, 0, 0, 0, 0, 3);
			DefClass[Class].Equipment[EQUIPMENT_WEAPON_RIGHT].Convert(right_type, 0, 0, 0, 0, 0, 3);
			DefClass[Class].Equipment[EQUIPMENT_WEAPON_LEFT].Convert(def_type, 0, 0, 0, 0, 0, 3);
		}
	}
	if (this->m_BabubBanJiCreate == 1)
	{
		def_type = ItemGetNumberMake(13, 20);
		this->DefClass[Class].Equipment[12].m_Level = 1;
		this->DefClass[Class].Equipment[12].Convert(def_type, 0, 0, 0, 0, 0, 3);
		def_type = ItemGetNumberMake(13, 20);
		this->DefClass[Class].Equipment[13].m_Level = 2;
		this->DefClass[Class].Equipment[13].Convert(def_type, 0, 0, 0, 0, 0, 3);
	}
	if (this->m_BabubBanJiCreate)
	{
		def_type = ItemGetNumberMake(14, 286);
		this->DefClass[Class].Equipment[14].m_Level = 0;
		this->DefClass[Class].Equipment[14].Convert(def_type, 0, 0, 0, 0, 0, 3);
	}
	else
	{
		def_type = ItemGetNumberMake(14, 286);
		this->DefClass[Class].Equipment[12].m_Level = 0;
		this->DefClass[Class].Equipment[12].Convert(def_type, 0, 0, 0, 0, 0, 3);
	}
}
//void classdef::SetEquipment(int Class)
//{
//	int def_type = 0;
//	int right_type = 0;
//	int n;
//
//	for (n = 0; n<MAX_EQUIPMENT + 1; n++)
//		DefClass[Class].Equipment[n].Clear();
//
//	// 종족에 따라 기본 무기를 세팅한다.
//	switch (Class)
//	{
//	case CLASS_KNIGHT: //흑기사 (작은도끼)
//		def_type = ItemGetNumberMake(1, 0);
//		break;
//	case CLASS_ELF: //요정 (활과 화살)
//		def_type = ItemGetNumberMake(4, 0);
//		right_type = ItemGetNumberMake(4, 15);
//		break;
//
//#ifdef DARKLORD_WORK
//	case CLASS_DARKLORD: //다크로드 (원형방패/짧은검)
//		def_type = ItemGetNumberMake(6, 0);
//		right_type = ItemGetNumberMake(0, 1);
//		break;
//#endif
//	case CLASS_MAGUMSA: //마검사 (원형방패/짧은검)
//
//		def_type = ItemGetNumberMake(6, 0);
//		right_type = ItemGetNumberMake(0, 1);
//		break;
//#ifdef ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912	// 소환술사 생성시 기본 아이템
//	case CLASS_SUMMONER:	// 소환술사 (작은도끼)
//		def_type = ItemGetNumberMake(1, 0);
//		break;
//#endif
//	case CLASS_MONK:
//		def_type = ItemGetNumberMake(1, 0);
//		break;
//	case CLASS_LANCER:
//		def_type = ItemGetNumberMake(6, 0);
//		right_type = ItemGetNumberMake(1, 0);
//		break;
//	}
//
//	if (Class != CLASS_WIZARD)
//	{
//#ifdef DARKLORD_WORK
//		if (Class == CLASS_DARKLORD)
//		{
//			DefClass[Class].Equipment[EQUIPMENT_WEAPON_RIGHT].m_Level = 0;
//			DefClass[Class].Equipment[EQUIPMENT_WEAPON_LEFT].m_Level = 0;
//			DefClass[Class].Equipment[EQUIPMENT_WEAPON_RIGHT].Convert(right_type, 0, 0, 0, 0, 0, 3);
//			DefClass[Class].Equipment[EQUIPMENT_WEAPON_LEFT].Convert(def_type, 0, 0, 0, 0, 0, 3);
//		}
//		else
//#endif
//			if (Class == CLASS_ELF || Class == CLASS_MAGUMSA)
//
//			{
//				DefClass[Class].Equipment[EQUIPMENT_WEAPON_RIGHT].m_Level = 0;
//				DefClass[Class].Equipment[EQUIPMENT_WEAPON_LEFT].m_Level = 0;
//				DefClass[Class].Equipment[EQUIPMENT_WEAPON_RIGHT].Convert(right_type, 0, 0, 0, 0, 0, 3);
//				DefClass[Class].Equipment[EQUIPMENT_WEAPON_LEFT].Convert(def_type, 0, 0, 0, 0, 0, 3);
//			}
//#ifdef ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912	// 소환술사 생성시 기본 아이템
//			else if (Class == CLASS_SUMMONER)
//			{
//				DefClass[Class].Equipment[EQUIPMENT_WEAPON_RIGHT].m_Level = 0;
//				DefClass[Class].Equipment[EQUIPMENT_WEAPON_RIGHT].Convert(def_type, 0, 0, 0, 0, 0, 3);
//			}
//#endif		
//			else
//			{
//				DefClass[Class].Equipment[EQUIPMENT_WEAPON_RIGHT].m_Level = 0;
//				DefClass[Class].Equipment[EQUIPMENT_WEAPON_RIGHT].Convert(def_type, 0, 0, 0, 0, 0, 3);
//			}
//	}
//
//	if (m_BabubBanJiCreate == 1)
//	{
//		// 이벤트로 용사의 반지를 추가해준다.
//		def_type = ItemGetNumberMake(13, 20);
//		DefClass[Class].Equipment[MAX_EQUIPMENT].m_Level = 1;
//		DefClass[Class].Equipment[MAX_EQUIPMENT].Convert(def_type, 0, 0, 0, 0, 0, 3);
//
//		// 이벤트로 전사의 반지를 추가해준다.
//		def_type = ItemGetNumberMake(13, 20);
//		DefClass[Class].Equipment[MAX_EQUIPMENT + 1].m_Level = 2;
//		DefClass[Class].Equipment[MAX_EQUIPMENT + 1].Convert(def_type, 0, 0, 0, 0, 0, 3);
//	}
//}

char classdef::GetCharacterClassByDBClass(char DbClass)
{
	if (DbClass <= 3)
		return 0;
	if (DbClass >= 16 && DbClass <= 19)
		return 1;
	if (DbClass >= 32 && DbClass <= 35)
		return 2;
	if (DbClass >= 48 && DbClass <= 50)
		return 3;
	if (DbClass >= 64 && DbClass <= 67)
		return 4;
	if (DbClass >= 80 && DbClass <= 83)
		return 5;
	if (DbClass >= 96 && DbClass <= 98)
		return 6;
	if (DbClass < 112 || DbClass > 114)
		return -1;
	return 7;
}

void classdef::SetJumpingEquipment(int nClass)
{
	float v2; // STF0_4
	float v3; // STF0_4
	float v4; // STF0_4
	float v5; // STF0_4
	float v6; // STF0_4
	float v7; // STF0_4
	float v8; // STF0_4
	float v9; // STF0_4
	float v10; // STF0_4
	float v11; // STF0_4
	float v12; // STF0_4
	float v13; // STF0_4
	float v14; // STF0_4
	float v15; // STF0_4
	float v16; // STF0_4
	float v17; // STF0_4
	float v18; // STF0_4
	float v19; // STF0_4
	float v20; // STF0_4
	float v21; // STF0_4
	float v22; // STF0_4
	float v23; // STF0_4
	float v24; // STF0_4
	float v25; // STF0_4
	float v26; // STF0_4
	float v27; // STF0_4
	float v28; // STF0_4
	float v29; // STF0_4
	float v30; // STF0_4
	float v31; // STF0_4
	float v32; // STF0_4
	float v33; // STF0_4

	float Dur; // [esp+D4h] [ebp-A4h]
	int n; // [esp+E0h] [ebp-98h]
	int ItemPerClass; // [esp+ECh] [ebp-8Ch]
	int Common_Type; // [esp+F8h] [ebp-80h]
	int Acce_Type; // [esp+104h] [ebp-74h]
	int Wings_Type; // [esp+110h] [ebp-68h]
	int Boots_Type; // [esp+11Ch] [ebp-5Ch]
	int Gloves_Type; // [esp+128h] [ebp-50h]
	int Pants_Type; // [esp+134h] [ebp-44h]
	int Armor_Type; // [esp+140h] [ebp-38h]
	int Helm_Type; // [esp+14Ch] [ebp-2Ch]
	int SubItem_type; // [esp+158h] [ebp-20h]
	int Weapon_type; // [esp+164h] [ebp-14h]

	Weapon_type = 0;
	SubItem_type = 0;
	Helm_Type = 0;
	Armor_Type = 0;
	Pants_Type = 0;
	Gloves_Type = 0;
	Boots_Type = 0;
	Wings_Type = 0;
	Acce_Type = ItemGetNumberMake(13, 408);
	Common_Type = ItemGetNumberMake(14, 286);
	switch (nClass)
	{
	case 0:
		Weapon_type = ItemGetNumberMake(5, 45);
		SubItem_type = ItemGetNumberMake(6, 37);
		Helm_Type = ItemGetNumberMake(7, 131);
		Armor_Type = ItemGetNumberMake(8, 131);
		Pants_Type = ItemGetNumberMake(9, 131);
		Gloves_Type = ItemGetNumberMake(10, 131);
		Boots_Type = ItemGetNumberMake(11, 131);
		Wings_Type = ItemGetNumberMake(12, 281);
		break;
	case 1:
		Weapon_type = ItemGetNumberMake(0, 48);
		SubItem_type = ItemGetNumberMake(0, 48);
		Helm_Type = ItemGetNumberMake(7, 130);
		Armor_Type = ItemGetNumberMake(8, 130);
		Pants_Type = ItemGetNumberMake(9, 130);
		Gloves_Type = ItemGetNumberMake(10, 130);
		Boots_Type = ItemGetNumberMake(11, 130);
		Wings_Type = ItemGetNumberMake(12, 280);
		break;
	case 2:
		Weapon_type = ItemGetNumberMake(4, 29);
		SubItem_type = 0;
		Helm_Type = ItemGetNumberMake(7, 132);
		Armor_Type = ItemGetNumberMake(8, 132);
		Pants_Type = ItemGetNumberMake(9, 132);
		Gloves_Type = ItemGetNumberMake(10, 132);
		Boots_Type = ItemGetNumberMake(11, 132);
		Wings_Type = ItemGetNumberMake(12, 282);
		break;
	case 3:
		Weapon_type = ItemGetNumberMake(0, 49);
		SubItem_type = ItemGetNumberMake(5, 48);
		Armor_Type = ItemGetNumberMake(8, 133);
		Pants_Type = ItemGetNumberMake(9, 133);
		Gloves_Type = ItemGetNumberMake(10, 133);
		Boots_Type = ItemGetNumberMake(11, 133);
		Wings_Type = ItemGetNumberMake(12, 280);
		break;
	case 4:
		Weapon_type = ItemGetNumberMake(2, 24);
		SubItem_type = ItemGetNumberMake(6, 38);
		Helm_Type = ItemGetNumberMake(7, 134);
		Armor_Type = ItemGetNumberMake(8, 134);
		Pants_Type = ItemGetNumberMake(9, 134);
		Gloves_Type = ItemGetNumberMake(10, 134);
		Boots_Type = ItemGetNumberMake(11, 134);
		Wings_Type = ItemGetNumberMake(12, 279);
		break;
	case 5:
		Weapon_type = ItemGetNumberMake(5, 46);
		SubItem_type = ItemGetNumberMake(5, 47);
		Helm_Type = ItemGetNumberMake(7, 135);
		Armor_Type = ItemGetNumberMake(8, 135);
		Pants_Type = ItemGetNumberMake(9, 135);
		Gloves_Type = ItemGetNumberMake(10, 135);
		Boots_Type = ItemGetNumberMake(11, 135);
		Wings_Type = ItemGetNumberMake(12, 281);
		break;
	case 6:
		Weapon_type = ItemGetNumberMake(0, 50);
		SubItem_type = ItemGetNumberMake(0, 50);
		Helm_Type = ItemGetNumberMake(7, 136);
		Armor_Type = ItemGetNumberMake(8, 136);
		Pants_Type = ItemGetNumberMake(9, 136);
		Boots_Type = ItemGetNumberMake(11, 136);
		Wings_Type = ItemGetNumberMake(12, 279);
		break;
	case 7:
		Weapon_type = ItemGetNumberMake(3, 21);
		SubItem_type = ItemGetNumberMake(6, 39);
		Helm_Type = ItemGetNumberMake(7, 137);
		Armor_Type = ItemGetNumberMake(8, 137);
		Pants_Type = ItemGetNumberMake(9, 137);
		Gloves_Type = ItemGetNumberMake(10, 137);
		Boots_Type = ItemGetNumberMake(11, 137);
		Wings_Type = ItemGetNumberMake(12, 279);
		break;
	default:
		break;

	}
	ItemPerClass = 4 * nClass;
	for (n = 0; n < 204; ++n)
	{
		JumpingEquipment[4 * nClass][n].Clear();
		JumpingEquipment[ItemPerClass + 1][n].Clear();
		JumpingEquipment[ItemPerClass + 2][n].Clear();
		JumpingEquipment[ItemPerClass + 3][n].Clear();
	}
	if (Weapon_type)
	{
		v2 = ItemGetDurability(Weapon_type, 9, 0, 0);
		this->JumpingEquipment[4 * nClass][12].Convert(Weapon_type, 1, 1, 3, 0, 0, 3);
		this->JumpingEquipment[4 * nClass][12].m_Level = 9;
		this->JumpingEquipment[4 * nClass][12].m_Durability = v2;
		v3 = ItemGetDurability(Weapon_type, 11, 0, 0);
		this->JumpingEquipment[ItemPerClass + 1][12].Convert(Weapon_type, 1, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 1][12].m_Level = 11;
		this->JumpingEquipment[ItemPerClass + 1][12].m_Durability = v3;
		v4 = ItemGetDurability(Weapon_type, 7, 0, 0);
		this->JumpingEquipment[ItemPerClass + 2][12].Convert(Weapon_type, 1, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 2][12].m_Level = 7;
		this->JumpingEquipment[ItemPerClass + 2][12].m_Durability = v4;
		v5 = ItemGetDurability(Weapon_type, 13, 1, 0);
		this->JumpingEquipment[ItemPerClass + 3][12].Convert(Weapon_type, 1, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 3][12].m_NewOption = 8;
		this->JumpingEquipment[ItemPerClass + 3][12].m_Level = 13;
		this->JumpingEquipment[ItemPerClass + 3][12].m_Durability = v5;
	}

	if (SubItem_type)
	{
		v6 = ItemGetDurability(SubItem_type, 9, 0, 0);
		this->JumpingEquipment[4 * nClass][14].Convert(SubItem_type, 1, 1, 3, 0, 0, 3);
		this->JumpingEquipment[4 * nClass][14].m_Level = 9;
		this->JumpingEquipment[4 * nClass][14].m_Durability = v6;
		v7 = ItemGetDurability(SubItem_type, 11, 0, 0);
		this->JumpingEquipment[ItemPerClass + 1][14].Convert(SubItem_type, 1, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 1][14].m_Level = 11;
		this->JumpingEquipment[ItemPerClass + 1][14].m_Durability = v7;
		v8 = ItemGetDurability(SubItem_type, 7, 0, 0);
		this->JumpingEquipment[ItemPerClass + 2][14].Convert(SubItem_type, 1, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 2][14].m_Level = 7;
		this->JumpingEquipment[ItemPerClass + 2][14].m_Durability = v8;
		Dur = ItemGetDurability(SubItem_type, 13, 1, 0);
		this->JumpingEquipment[ItemPerClass + 3][14].Convert(SubItem_type, 1, 1, 3, 0, 0, 3);
		switch (nClass)
		{
		case 0:
		case 4:
		case 7:
			this->JumpingEquipment[ItemPerClass + 3][14].m_NewOption = 2;
			break;
		case 1:
		case 5:
		case 6:
			this->JumpingEquipment[ItemPerClass + 3][14].m_NewOption = 2;
			break;
		case 3:
			this->JumpingEquipment[ItemPerClass + 3][14].m_NewOption = 8;
			break;
		default:
			break;
		}
		this->JumpingEquipment[ItemPerClass + 3][14].m_Level = 13;
		this->JumpingEquipment[ItemPerClass + 3][14].m_Durability = Dur;
	}

	if (Wings_Type)
	{
		v9 = ItemGetDurability(Wings_Type, 9, 0, 0);
		this->JumpingEquipment[4 * nClass][16].Convert(Wings_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[4 * nClass][16].m_Level = 9;
		this->JumpingEquipment[4 * nClass][16].m_Durability = v9;
		v10 = ItemGetDurability(Wings_Type, 11, 0, 0);
		this->JumpingEquipment[ItemPerClass + 1][16].Convert(Wings_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 1][16].m_Level = 11;
		this->JumpingEquipment[ItemPerClass + 1][16].m_Durability = v10;
		v11 = ItemGetDurability(Wings_Type, 7, 0, 0);
		this->JumpingEquipment[ItemPerClass + 2][16].Convert(Wings_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 2][16].m_Level = 7;
		this->JumpingEquipment[ItemPerClass + 2][16].m_Durability = v11;
		v12 = ItemGetDurability(Wings_Type, 13, 0, 0);
		this->JumpingEquipment[ItemPerClass + 3][16].Convert(Wings_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 3][16].m_Level = 13;
		this->JumpingEquipment[ItemPerClass + 3][16].m_Durability = v12;
	}
	if (Acce_Type)
	{
		v13 = ItemGetDurability(Acce_Type, 0, 1, 0);
		this->JumpingEquipment[4 * nClass][40].Convert(Acce_Type, 0, 0, 0, 0, 0, 3);
		this->JumpingEquipment[4 * nClass][40].m_NewOption = 1;
		this->JumpingEquipment[4 * nClass][40].m_NewOption |= 2u;
		this->JumpingEquipment[4 * nClass][40].m_Durability = v13;
		this->JumpingEquipment[ItemPerClass + 1][40].Convert(Acce_Type, 0, 0, 0, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 1][40].m_NewOption = 1;
		this->JumpingEquipment[ItemPerClass + 1][40].m_NewOption |= 2u;
		this->JumpingEquipment[ItemPerClass + 1][40].m_Durability = v13;
		this->JumpingEquipment[ItemPerClass + 3][40].Convert(Acce_Type, 0, 0, 0, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 3][40].m_NewOption = 1;
		this->JumpingEquipment[ItemPerClass + 3][40].m_NewOption |= 2u;
		this->JumpingEquipment[ItemPerClass + 3][40].m_Durability = v13;
	}
	if (Common_Type)
	{
		this->JumpingEquipment[4 * nClass][41].m_Level = 1;
		this->JumpingEquipment[4 * nClass][41].Convert(Common_Type, 0, 0, 0, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 1][41].m_Level = 2;
		this->JumpingEquipment[ItemPerClass + 1][41].Convert(Common_Type, 0, 0, 0, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 2][41].m_Level = 1;
		this->JumpingEquipment[ItemPerClass + 2][41].Convert(Common_Type, 0, 0, 0, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 3][41].m_Level = 2;
		this->JumpingEquipment[ItemPerClass + 3][41].Convert(Common_Type, 0, 0, 0, 0, 0, 3);
	}

	if (Armor_Type)
	{
		v14 = ItemGetDurability(Armor_Type, 9, 0, 1);
		this->JumpingEquipment[4 * nClass][44].Convert(Armor_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[4 * nClass][44].m_Level = 9;
		this->JumpingEquipment[4 * nClass][44].m_SetOption = 5;
		this->JumpingEquipment[4 * nClass][44].m_Durability = v14;
		v15 = ItemGetDurability(Armor_Type, 11, 0, 1);
		this->JumpingEquipment[ItemPerClass + 1][44].Convert(Armor_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 1][44].m_Level = 11;
		this->JumpingEquipment[ItemPerClass + 1][44].m_SetOption = 6;
		this->JumpingEquipment[ItemPerClass + 1][44].m_Durability = v15;
		v16 = ItemGetDurability(Armor_Type, 7, 0, 1);
		this->JumpingEquipment[ItemPerClass + 2][44].Convert(Armor_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 2][44].m_Level = 7;
		this->JumpingEquipment[ItemPerClass + 2][44].m_SetOption = 5;
		this->JumpingEquipment[ItemPerClass + 2][44].m_Durability = v16;
		v17 = ItemGetDurability(Armor_Type, 13, 0, 1);
		this->JumpingEquipment[ItemPerClass + 3][44].Convert(Armor_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 3][44].m_Level = 13;
		this->JumpingEquipment[ItemPerClass + 3][44].m_SetOption = 6;
		this->JumpingEquipment[ItemPerClass + 3][44].m_Durability = v17;
	}
	if (Helm_Type)
	{
		v18 = ItemGetDurability(Helm_Type, 9, 0, 1);
		this->JumpingEquipment[4 * nClass][46].Convert(Helm_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[4 * nClass][46].m_Level = 9;
		this->JumpingEquipment[4 * nClass][46].m_SetOption = 5;
		this->JumpingEquipment[4 * nClass][46].m_Durability = v18;
		v19 = ItemGetDurability(Helm_Type, 11, 0, 1);
		this->JumpingEquipment[ItemPerClass + 1][46].Convert(Helm_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 1][46].m_Level = 11;
		this->JumpingEquipment[ItemPerClass + 1][46].m_SetOption = 6;
		this->JumpingEquipment[ItemPerClass + 1][46].m_Durability = v19;
		v20 = ItemGetDurability(Helm_Type, 7, 0, 1);
		this->JumpingEquipment[ItemPerClass + 2][46].Convert(Helm_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 2][46].m_Level = 7;
		this->JumpingEquipment[ItemPerClass + 2][46].m_SetOption = 5;
		this->JumpingEquipment[ItemPerClass + 2][46].m_Durability = v20;
		v21 = ItemGetDurability(Helm_Type, 13, 0, 1);
		this->JumpingEquipment[ItemPerClass + 3][46].Convert(Helm_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 3][46].m_Level = 13;
		this->JumpingEquipment[ItemPerClass + 3][46].m_SetOption = 6;
		this->JumpingEquipment[ItemPerClass + 3][46].m_Durability = v21;
	}
	if (Pants_Type)
	{
		v22 = ItemGetDurability(Pants_Type, 9, 0, 1);
		this->JumpingEquipment[4 * nClass][48].Convert(Pants_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[4 * nClass][48].m_Level = 9;
		this->JumpingEquipment[4 * nClass][48].m_SetOption = 5;
		this->JumpingEquipment[4 * nClass][48].m_Durability = v22;
		v23 = ItemGetDurability(Pants_Type, 11, 0, 1);
		this->JumpingEquipment[ItemPerClass + 1][48].Convert(Pants_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 1][48].m_Level = 11;
		this->JumpingEquipment[ItemPerClass + 1][48].m_SetOption = 6;
		this->JumpingEquipment[ItemPerClass + 1][48].m_Durability = v23;
		v24 = ItemGetDurability(Pants_Type, 7, 0, 1);
		this->JumpingEquipment[ItemPerClass + 2][48].Convert(Pants_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 2][48].m_Level = 7;
		this->JumpingEquipment[ItemPerClass + 2][48].m_SetOption = 5;
		this->JumpingEquipment[ItemPerClass + 2][48].m_Durability = v24;
		v25 = ItemGetDurability(Pants_Type, 13, 0, 1);
		this->JumpingEquipment[ItemPerClass + 3][48].Convert(Pants_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 3][48].m_Level = 13;
		this->JumpingEquipment[ItemPerClass + 3][48].m_SetOption = 6;
		this->JumpingEquipment[ItemPerClass + 3][48].m_Durability = v25;
	}
	if (Gloves_Type)
	{
		v26 = ItemGetDurability(Gloves_Type, 9, 0, 1);
		this->JumpingEquipment[4 * nClass][62].Convert(Gloves_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[4 * nClass][62].m_Level = 9;
		this->JumpingEquipment[4 * nClass][62].m_SetOption = 5;
		this->JumpingEquipment[4 * nClass][62].m_Durability = v26;
		v27 = ItemGetDurability(Gloves_Type, 11, 0, 1);
		this->JumpingEquipment[ItemPerClass + 1][62].Convert(Gloves_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 1][62].m_Level = 11;
		this->JumpingEquipment[ItemPerClass + 1][62].m_SetOption = 6;
		this->JumpingEquipment[ItemPerClass + 1][62].m_Durability = v27;
		v28 = ItemGetDurability(Gloves_Type, 7, 0, 1);
		this->JumpingEquipment[ItemPerClass + 2][62].Convert(Gloves_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 2][62].m_Level = 7;
		this->JumpingEquipment[ItemPerClass + 2][62].m_SetOption = 5;
		this->JumpingEquipment[ItemPerClass + 2][62].m_Durability = v28;
		v29 = ItemGetDurability(Gloves_Type, 13, 0, 1);
		this->JumpingEquipment[ItemPerClass + 3][62].Convert(Gloves_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 3][62].m_Level = 13;
		this->JumpingEquipment[ItemPerClass + 3][62].m_SetOption = 6;
		this->JumpingEquipment[ItemPerClass + 3][62].m_Durability = v29;
	}

	if (Boots_Type)
	{
		v30 = ItemGetDurability(Boots_Type, 9, 0, 1);
		this->JumpingEquipment[4 * nClass][64].Convert(Boots_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[4 * nClass][64].m_Level = 9;
		this->JumpingEquipment[4 * nClass][64].m_SetOption = 5;
		this->JumpingEquipment[4 * nClass][64].m_Durability = v30;
		v31 = ItemGetDurability(Boots_Type, 11, 0, 1);
		this->JumpingEquipment[ItemPerClass + 1][64].Convert(Boots_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 1][64].m_Level = 11;
		this->JumpingEquipment[ItemPerClass + 1][64].m_SetOption = 6;
		this->JumpingEquipment[ItemPerClass + 1][64].m_Durability = v31;
		v32 = ItemGetDurability(Boots_Type, 7, 0, 1);
		this->JumpingEquipment[ItemPerClass + 2][64].Convert(Boots_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 2][64].m_Level = 7;
		this->JumpingEquipment[ItemPerClass + 2][64].m_SetOption = 5;
		this->JumpingEquipment[ItemPerClass + 2][64].m_Durability = v32;
		v33 = ItemGetDurability(Boots_Type, 13, 0, 1);
		this->JumpingEquipment[ItemPerClass + 3][64].Convert(Boots_Type, 0, 1, 3, 0, 0, 3);
		this->JumpingEquipment[ItemPerClass + 3][64].m_Level = 13;
		this->JumpingEquipment[ItemPerClass + 3][64].m_SetOption = 6;
		this->JumpingEquipment[ItemPerClass + 3][64].m_Durability = v33;
	}
}
//void classdef::SetJumpingEquipment(int nClass)
//{
//	float v2; // STF0_4
//	float v3; // STF0_4
//	float v4; // STF0_4
//	float v5; // STF0_4
//	float v6; // STF0_4
//	float v7; // STF0_4
//	float v8; // STF0_4
//	float v9; // STF0_4
//	float v10; // STF0_4
//	float v11; // STF0_4
//	float v12; // STF0_4
//	float v13; // STF0_4
//	float v14; // STF0_4
//	float v15; // STF0_4
//	float v16; // STF0_4
//	float v17; // STF0_4
//	float v18; // STF0_4
//	float v19; // STF0_4
//	float v20; // STF0_4
//	float v21; // STF0_4
//	float v22; // STF0_4
//	float v23; // STF0_4
//	float v24; // STF0_4
//	float v25; // STF0_4
//	float v26; // STF0_4
//	float v27; // STF0_4
//	float v28; // STF0_4
//	float v29; // STF0_4
//	float v30; // STF0_4
//	float v31; // STF0_4
//	float v32; // STF0_4
//	float v33; // STF0_4
//	float Dur; // [esp+D4h] [ebp-A4h]
//	int n; // [esp+E0h] [ebp-98h]
//	int ItemPerClass; // [esp+ECh] [ebp-8Ch]
//	int Common_Type; // [esp+F8h] [ebp-80h]
//	int Acce_Type; // [esp+104h] [ebp-74h]
//	int Wings_Type; // [esp+110h] [ebp-68h]
//	int Boots_Type; // [esp+11Ch] [ebp-5Ch]
//	int Gloves_Type; // [esp+128h] [ebp-50h]
//	int Pants_Type; // [esp+134h] [ebp-44h]
//	int Armor_Type; // [esp+140h] [ebp-38h]
//	int Helm_Type; // [esp+14Ch] [ebp-2Ch]
//	int SubItem_type; // [esp+158h] [ebp-20h]
//	int Weapon_type; // [esp+164h] [ebp-14h]
//
//	Weapon_type = 0;
//	SubItem_type = 0;
//	Helm_Type = 0;
//	Armor_Type = 0;
//	Pants_Type = 0;
//	Gloves_Type = 0;
//	Boots_Type = 0;
//	Wings_Type = 0;
//	Acce_Type = ItemGetNumberMake(13, 408);
//	Common_Type = ItemGetNumberMake(14, 286);
//	switch (nClass)
//	{
//	case 0:
//		Weapon_type = ItemGetNumberMake(5, 45);
//		SubItem_type = ItemGetNumberMake(6, 37);
//		Helm_Type = ItemGetNumberMake(7, 131);
//		Armor_Type = ItemGetNumberMake(8, 131);
//		Pants_Type = ItemGetNumberMake(9, 131);
//		Gloves_Type = ItemGetNumberMake(10, 131);
//		Boots_Type = ItemGetNumberMake(11, 131);
//		Wings_Type = ItemGetNumberMake(12, 281);
//		break;
//	case 1:
//		Weapon_type = ItemGetNumberMake(0, 48);
//		SubItem_type = ItemGetNumberMake(0, 48);
//		Helm_Type = ItemGetNumberMake(7, 130);
//		Armor_Type = ItemGetNumberMake(8, 130);
//		Pants_Type = ItemGetNumberMake(9, 130);
//		Gloves_Type = ItemGetNumberMake(10, 130);
//		Boots_Type = ItemGetNumberMake(11, 130);
//		Wings_Type = ItemGetNumberMake(12, 280);
//		break;
//	case 2:
//		Weapon_type = ItemGetNumberMake(4, 29);
//		SubItem_type = 0;
//		Helm_Type = ItemGetNumberMake(7, 132);
//		Armor_Type = ItemGetNumberMake(8, 132);
//		Pants_Type = ItemGetNumberMake(9, 132);
//		Gloves_Type = ItemGetNumberMake(10, 132);
//		Boots_Type = ItemGetNumberMake(11, 132);
//		Wings_Type = ItemGetNumberMake(12, 282);
//		break;
//	case 3:
//		Weapon_type = ItemGetNumberMake(0, 49);
//		SubItem_type = ItemGetNumberMake(5, 48);
//		Armor_Type = ItemGetNumberMake(8, 133);
//		Pants_Type = ItemGetNumberMake(9, 133);
//		Gloves_Type = ItemGetNumberMake(10, 133);
//		Boots_Type = ItemGetNumberMake(11, 133);
//		Wings_Type = ItemGetNumberMake(12, 280);
//		break;
//	case 4:
//		Weapon_type = ItemGetNumberMake(2, 24);
//		SubItem_type = ItemGetNumberMake(6, 38);
//		Helm_Type = ItemGetNumberMake(7, 134);
//		Armor_Type = ItemGetNumberMake(8, 134);
//		Pants_Type = ItemGetNumberMake(9, 134);
//		Gloves_Type = ItemGetNumberMake(10, 134);
//		Boots_Type = ItemGetNumberMake(11, 134);
//		Wings_Type = ItemGetNumberMake(12, 279);
//		break;
//	case 5:
//		Weapon_type = ItemGetNumberMake(5, 46);
//		SubItem_type = ItemGetNumberMake(5, 47);
//		Helm_Type = ItemGetNumberMake(7, 135);
//		Armor_Type = ItemGetNumberMake(8, 135);
//		Pants_Type = ItemGetNumberMake(9, 135);
//		Gloves_Type = ItemGetNumberMake(10, 135);
//		Boots_Type = ItemGetNumberMake(11, 135);
//		Wings_Type = ItemGetNumberMake(12, 281);
//		break;
//	case 6:
//		Weapon_type = ItemGetNumberMake(0, 50);
//		SubItem_type = ItemGetNumberMake(0, 50);
//		Helm_Type = ItemGetNumberMake(7, 136);
//		Armor_Type = ItemGetNumberMake(8, 136);
//		Pants_Type = ItemGetNumberMake(9, 136);
//		Boots_Type = ItemGetNumberMake(11, 136);
//		Wings_Type = ItemGetNumberMake(12, 279);
//		break;
//	case 7:
//		Weapon_type = ItemGetNumberMake(3, 21);
//		SubItem_type = ItemGetNumberMake(6, 39);
//		Helm_Type = ItemGetNumberMake(7, 137);
//		Armor_Type = ItemGetNumberMake(8, 137);
//		Pants_Type = ItemGetNumberMake(9, 137);
//		Gloves_Type = ItemGetNumberMake(10, 137);
//		Boots_Type = ItemGetNumberMake(11, 137);
//		Wings_Type = ItemGetNumberMake(12, 279);
//		break;
//	default:
//		break;
//	}
//	ItemPerClass = 4 * nClass;
//	for (n = 0; n < 204; ++n)
//	{
//		JumpingEquipment[4 * nClass][n].Clear();
//		JumpingEquipment[ItemPerClass + 1][n].Clear();
//		JumpingEquipment[ItemPerClass + 2][n].Clear();
//		JumpingEquipment[ItemPerClass + 3][n].Clear();
//	}
//	if (Weapon_type)
//	{
//		v2 = ItemGetDurability(Weapon_type, 9, 0, 0);
//		this->JumpingEquipment[4 * nClass][12].Convert(Weapon_type, 1, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[4 * nClass][12].m_Level = 9;
//		this->JumpingEquipment[4 * nClass][12].m_Durability = v2;
//		v3 = ItemGetDurability(Weapon_type, 11, 0, 0);
//		this->JumpingEquipment[ItemPerClass + 1][12].Convert(Weapon_type, 1, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 1][12].m_Level = 11;
//		this->JumpingEquipment[ItemPerClass + 1][12].m_Durability = v3;
//		v4 = ItemGetDurability(Weapon_type, 7, 0, 0);
//		this->JumpingEquipment[ItemPerClass + 2][12].Convert(Weapon_type, 1, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 2][12].m_Level = 7;
//		this->JumpingEquipment[ItemPerClass + 2][12].m_Durability = v4;
//		v5 = ItemGetDurability(Weapon_type, 13, 1, 0);
//		this->JumpingEquipment[ItemPerClass + 3][12].Convert(Weapon_type, 1, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 3][12].m_NewOption = 8;
//		this->JumpingEquipment[ItemPerClass + 3][12].m_Level = 13;
//		this->JumpingEquipment[ItemPerClass + 3][12].m_Durability = v5;
//	}
//	if (SubItem_type)
//	{
//		this->JumpingEquipment[4 * nClass][14].m_Durability = ItemGetDurability(SubItem_type, 9, 0, 0);
//		this->JumpingEquipment[4 * nClass][14].Convert(SubItem_type, 1, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[4 * nClass][14].m_Level = 9;
//		this->JumpingEquipment[ItemPerClass + 1][14].m_Durability = ItemGetDurability(SubItem_type, 11, 0, 0);
//		this->JumpingEquipment[ItemPerClass + 1][14].Convert(SubItem_type, 1, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 1][14].m_Level = 11;
//		this->JumpingEquipment[ItemPerClass + 2][14].m_Durability = ItemGetDurability(SubItem_type, 7, 0, 0);
//		this->JumpingEquipment[ItemPerClass + 2][14].Convert(SubItem_type, 1, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 2][14].m_Level = 7;
//		Dur = ItemGetDurability(SubItem_type, 13, 1, 0);
//		this->JumpingEquipment[ItemPerClass + 3][14].Convert(SubItem_type, 1, 1, 3, 0, 0, 3);
//		switch (nClass)
//		{
//		case 0:
//		case 4:
//		case 7:
//			this->JumpingEquipment[ItemPerClass + 3][14].m_NewOption = 2;
//			break;
//		case 1:
//		case 5:
//		case 6:
//			this->JumpingEquipment[ItemPerClass + 3][14].m_NewOption = 2;
//			break;
//		case 3:
//			this->JumpingEquipment[ItemPerClass + 3][14].m_NewOption = 8;
//			break;
//		default:
//			break;
//		}
//		this->JumpingEquipment[ItemPerClass + 3][14].m_Level = 13;
//		this->JumpingEquipment[ItemPerClass + 3][14].m_Durability = Dur;
//	}
//	if (Wings_Type)
//	{
//		this->JumpingEquipment[4 * nClass][16].m_Durability = ItemGetDurability(Wings_Type, 9, 0, 0);
//		this->JumpingEquipment[4 * nClass][16].Convert(Wings_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[4 * nClass][16].m_Level = 9;
//		this->JumpingEquipment[ItemPerClass + 1][16].m_Durability = ItemGetDurability(Wings_Type, 11, 0, 0);
//		this->JumpingEquipment[ItemPerClass + 1][16].Convert(Wings_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 1][16].m_Level = 11;
//		this->JumpingEquipment[ItemPerClass + 2][16].m_Durability = ItemGetDurability(Wings_Type, 7, 0, 0);
//		this->JumpingEquipment[ItemPerClass + 2][16].Convert(Wings_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 2][16].m_Level = 7;
//		this->JumpingEquipment[ItemPerClass + 3][16].m_Durability = ItemGetDurability(Wings_Type, 13, 0, 0);
//		this->JumpingEquipment[ItemPerClass + 3][16].Convert(Wings_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 3][16].m_Level = 13;
//	}
//	if (Acce_Type)
//	{
//		v13 = ItemGetDurability(Acce_Type, 0, 1, 0);
//		this->JumpingEquipment[4 * nClass][40].Convert(Acce_Type, 0, 0, 0, 0, 0, 3);
//		this->JumpingEquipment[4 * nClass][40].m_NewOption = 1;
//		this->JumpingEquipment[4 * nClass][40].m_NewOption |= 2u;
//		this->JumpingEquipment[4 * nClass][40].m_Durability = v13;
//		this->JumpingEquipment[ItemPerClass + 1][40].Convert(Acce_Type, 0, 0, 0, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 1][40].m_NewOption = 1;
//		this->JumpingEquipment[ItemPerClass + 1][40].m_NewOption |= 2u;
//		this->JumpingEquipment[ItemPerClass + 1][40].m_Durability = v13;
//		this->JumpingEquipment[ItemPerClass + 3][40].Convert(Acce_Type, 0, 0, 0, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 3][40].m_NewOption = 1;
//		this->JumpingEquipment[ItemPerClass + 3][40].m_NewOption |= 2u;
//		this->JumpingEquipment[ItemPerClass + 3][40].m_Durability = v13;
//	}
//	if (Common_Type)
//	{
//		this->JumpingEquipment[4 * nClass][41].m_Level = 1;
//		this->JumpingEquipment[4 * nClass][41].Convert(Common_Type, 0, 0, 0, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 1][41].m_Level = 2;
//		this->JumpingEquipment[ItemPerClass + 1][41].Convert(Common_Type, 0, 0, 0, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 2][41].m_Level = 1;
//		this->JumpingEquipment[ItemPerClass + 2][41].Convert(Common_Type, 0, 0, 0, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 3][41].m_Level = 2;
//		this->JumpingEquipment[ItemPerClass + 3][41].Convert(Common_Type, 0, 0, 0, 0, 0, 3);
//	}
//	if (Armor_Type)
//	{
//		v14 = ItemGetDurability(Armor_Type, 9, 0, 1);
//		this->JumpingEquipment[4 * nClass][44].Convert(Armor_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[4 * nClass][44].m_Level = 9;
//		this->JumpingEquipment[4 * nClass][44].m_SetOption = 5;
//		this->JumpingEquipment[4 * nClass][44].m_Durability = v14;
//		v15 = ItemGetDurability(Armor_Type, 11, 0, 1);
//		(this->JumpingEquipment[ItemPerClass + 1][44].Convert, Armor_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 1][44].m_Level = 11;
//		this->JumpingEquipment[ItemPerClass + 1][44].m_SetOption = 6;
//		this->JumpingEquipment[ItemPerClass + 1][44].m_Durability = v15;
//		v16 = ItemGetDurability(Armor_Type, 7, 0, 1);
//		this->JumpingEquipment[ItemPerClass + 2][44].Convert(Armor_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 2][44].m_Level = 7;
//		this->JumpingEquipment[ItemPerClass + 2][44].m_SetOption = 5;
//		this->JumpingEquipment[ItemPerClass + 2][44].m_Durability = v16;
//		v17 = ItemGetDurability(Armor_Type, 13, 0, 1);
//		this->JumpingEquipment[ItemPerClass + 3][44].Convert(Armor_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 3][44].m_Level = 13;
//		this->JumpingEquipment[ItemPerClass + 3][44].m_SetOption = 6;
//		this->JumpingEquipment[ItemPerClass + 3][44].m_Durability = v17;
//	}
//	if (Helm_Type)
//	{
//		v18 = ItemGetDurability(Helm_Type, 9, 0, 1);
//		this->JumpingEquipment[4 * nClass][46].Convert(Helm_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[4 * nClass][46].m_Level = 9;
//		this->JumpingEquipment[4 * nClass][46].m_SetOption = 5;
//		this->JumpingEquipment[4 * nClass][46].m_Durability = v18;
//		v19 = ItemGetDurability(Helm_Type, 11, 0, 1);
//		this->JumpingEquipment[ItemPerClass + 1][46].Convert(Helm_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 1][46].m_Level = 11;
//		this->JumpingEquipment[ItemPerClass + 1][46].m_SetOption = 6;
//		this->JumpingEquipment[ItemPerClass + 1][46].m_Durability = v19;
//		v20 = ItemGetDurability(Helm_Type, 7, 0, 1);
//		this->JumpingEquipment[ItemPerClass + 2][46].Convert(Helm_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 2][46].m_Level = 7;
//		this->JumpingEquipment[ItemPerClass + 2][46].m_SetOption = 5;
//		this->JumpingEquipment[ItemPerClass + 2][46].m_Durability = v20;
//		v21 = ItemGetDurability(Helm_Type, 13, 0, 1);
//		this->JumpingEquipment[ItemPerClass + 3][46].Convert(Helm_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 3][46].m_Level = 13;
//		this->JumpingEquipment[ItemPerClass + 3][46].m_SetOption = 6;
//		this->JumpingEquipment[ItemPerClass + 3][46].m_Durability = v21;
//	}
//	if (Pants_Type)
//	{
//		v22 = ItemGetDurability(Pants_Type, 9, 0, 1);
//		this->JumpingEquipment[4 * nClass][48].Convert(Pants_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[4 * nClass][48].m_Level = 9;
//		this->JumpingEquipment[4 * nClass][48].m_SetOption = 5;
//		this->JumpingEquipment[4 * nClass][48].m_Durability = v22;
//		v23 = ItemGetDurability(Pants_Type, 11, 0, 1);
//		this->JumpingEquipment[ItemPerClass + 1][48].Convert(Pants_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 1][48].m_Level = 11;
//		this->JumpingEquipment[ItemPerClass + 1][48].m_SetOption = 6;
//		this->JumpingEquipment[ItemPerClass + 1][48].m_Durability = v23;
//		v24 = ItemGetDurability(Pants_Type, 7, 0, 1);
//		this->JumpingEquipment[ItemPerClass + 2][48].Convert(Pants_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 2][48].m_Level = 7;
//		this->JumpingEquipment[ItemPerClass + 2][48].m_SetOption = 5;
//		this->JumpingEquipment[ItemPerClass + 2][48].m_Durability = v24;
//		v25 = ItemGetDurability(Pants_Type, 13, 0, 1);
//		this->JumpingEquipment[ItemPerClass + 3][48].Convert(Pants_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 3][48].m_Level = 13;
//		this->JumpingEquipment[ItemPerClass + 3][48].m_SetOption = 6;
//		this->JumpingEquipment[ItemPerClass + 3][48].m_Durability = v25;
//	}
//	if (Gloves_Type)
//	{
//		v26 = ItemGetDurability(Gloves_Type, 9, 0, 1);
//		this->JumpingEquipment[4 * nClass][62].Convert(Gloves_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[4 * nClass][62].m_Level = 9;
//		this->JumpingEquipment[4 * nClass][62].m_SetOption = 5;
//		this->JumpingEquipment[4 * nClass][62].m_Durability = v26;
//		v27 = ItemGetDurability(Gloves_Type, 11, 0, 1);
//		this->JumpingEquipment[ItemPerClass + 1][62].Convert(Gloves_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 1][62].m_Level = 11;
//		this->JumpingEquipment[ItemPerClass + 1][62].m_SetOption = 6;
//		this->JumpingEquipment[ItemPerClass + 1][62].m_Durability = v27;
//		v28 = ItemGetDurability(Gloves_Type, 7, 0, 1);
//		this->JumpingEquipment[ItemPerClass + 2][62].Convert(Gloves_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 2][62].m_Level = 7;
//		this->JumpingEquipment[ItemPerClass + 2][62].m_SetOption = 5;
//		this->JumpingEquipment[ItemPerClass + 2][62].m_Durability = v28;
//		v29 = ItemGetDurability(Gloves_Type, 13, 0, 1);
//		this->JumpingEquipment[ItemPerClass + 3][62].Convert(Gloves_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 3][62].m_Level = 13;
//		this->JumpingEquipment[ItemPerClass + 3][62].m_SetOption = 6;
//		this->JumpingEquipment[ItemPerClass + 3][62].m_Durability = v29;
//	}
//	if (Boots_Type)
//	{
//		this->JumpingEquipment[4 * nClass][64].m_Durability = ItemGetDurability(Boots_Type, 9, 0, 1);
//		this->JumpingEquipment[4 * nClass][64].Convert( Boots_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[4 * nClass][64].m_Level = 9;
//		this->JumpingEquipment[4 * nClass][64].m_SetOption = 5;
//		this->JumpingEquipment[ItemPerClass + 1][64].m_Durability = ItemGetDurability(Boots_Type, 11, 0, 1);
//		this->JumpingEquipment[ItemPerClass + 1][64].Convert(Boots_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 1][64].m_Level = 11;
//		this->JumpingEquipment[ItemPerClass + 1][64].m_SetOption = 6;
//		this->JumpingEquipment[ItemPerClass + 2][64].m_Durability = ItemGetDurability(Boots_Type, 7, 0, 1);
//		this->JumpingEquipment[ItemPerClass + 2][64].Convert(Boots_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 2][64].m_Level = 7;
//		this->JumpingEquipment[ItemPerClass + 2][64].m_SetOption = 5;
//		this->JumpingEquipment[ItemPerClass + 3][64].m_Durability = ItemGetDurability(Boots_Type, 13, 0, 1);
//		this->JumpingEquipment[ItemPerClass + 3][64].Convert(Boots_Type, 0, 1, 3, 0, 0, 3);
//		this->JumpingEquipment[ItemPerClass + 3][64].m_Level = 13;
//		this->JumpingEquipment[ItemPerClass + 3][64].m_SetOption = 6;
//	}
//}
// 캐릭터의 기본 능력치 총 합은?
int classdef::GetDefPoint(int char_class)
{
	if (char_class < 0 || char_class > MAX_CLASSTYPE - 1)  return 0;
	return DefClass[char_class].Strength + DefClass[char_class].Dexterity + DefClass[char_class].Vitality + DefClass[char_class].Energy + DefClass[char_class].Leadership;
}

void classdef::SetMabubBanjiOption(BOOL flag)
{
	m_BabubBanJiCreate = flag;
}
