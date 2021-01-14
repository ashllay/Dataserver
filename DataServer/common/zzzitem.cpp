#include "StdAfx.h"
#include <math.h>
#include "..\\Common\\LogProc.h"
#include "..\\Include\\Define.h"
#include "..\\Include\\ItemDef.h"
#include "..\\Include\\ReadScript.h"
#include "..\\common\\Winutil.h"
#include "ZzzItem.h"
#include "..\\common\\SetItemOption.h"

CPetItemExp	gPetItemExp;
int g_MaxItemIndexOfEachItemType[MAX_ITEM_TYPE] = { 0, };
ITEM_ATTRIBUTE      ItemAttribute[MAX_ITEM];

CItem::CItem()
{
	Clear();
}

void CItem::Clear()
{
	this->m_Type = -1;
	this->m_Level = 0;
	this->m_Part = 0;
	this->m_Class = 0;
	this->m_TwoHand = 0;
	this->m_AttackSpeed = 0;
	this->m_DamageMin = 0;
	this->m_DamageMax = 0;
	this->m_SuccessfulBlocking = 0;
	this->m_Defense = 0;
	this->m_MagicDefense = 0;
	this->m_Durability = 0.0;
	this->m_SpecialNum = 0;
	this->m_Value = 0;
	this->m_Option1 = 0;
	this->m_Option2 = 0;
	this->m_Option3 = 0;
	this->m_NewOption = 0;
	this->m_Number = 0;
	this->m_DurabilitySmall = 0;
	this->m_iPShopValue = -1;
	this->m_CurrentDurabilityState = -1.f;
	this->m_SetOption = 0;
	this->m_QuestItem = 0;
	memset(this->m_Special, 0, MAX_ITEM_SPECIAL);
	memset(this->m_SpecialValue, 0, MAX_ITEM_SPECIAL);
	memset(this->m_Resistance, 0, MAX_RESISTANCE);
	this->m_IsLoadPetItemInfo = FALSE;
	this->m_PetItem_Level = 1;
	this->m_PetItem_Exp = 0;
	this->m_Leadership = 0;
}

//----------------------------------------------------------------------------
// 아이템이 존재하는가?
BOOL CItem::IsItem()
{
	if (m_Type < 0) return FALSE;

	return TRUE;
}

// 세트아이템인가?
BOOL CItem::IsSetItem()
{
	if (m_Type < 0) return FALSE;

	return m_SetOption & 0x03;
}

//----------------------------------------------------------------------------
// 기본속성을 기반으로 아이템을 만든다.
void CItem::Convert(int type, BYTE Option1, BYTE Option2, BYTE Option3, BYTE Attribute2, BYTE SetOption, BYTE DbVersion)
{
	int _type = type;

	int ItemLevel; //3

	if ((DbVersion) == 0)
	{
		_type = (type / MAX_ITEM_TYPE * MAX_ITEM_INDEX) + (type%MAX_ITEM_TYPE);

	}
	else if (DbVersion <= 2)
	{
		_type = (type / 32 * MAX_ITEM_INDEX) + (type % 32);
	}

	if (_type >MAX_ITEM - 1)
	{
		LogAddC(2, "error-L1 : ItemIndex error %d", _type);
	}

	ITEM_ATTRIBUTE *p = &ItemAttribute[_type];

	m_serial = ItemAttribute[_type].Serial;
	m_Type = type;

	if (DbVersion <= 2)
	{
		this->m_Type = _type;
	}

	this->m_NewOption = Attribute2;

	if (p->OptionFlag == 0)
	{
		this->m_NewOption = 0;
	}

	if (((_type >= ITEM_WING + 3) && (_type <= ITEM_WING + 6)) || (_type == ITEM_HELPER + 30))
	{
		Attribute2 = 0;
	}

	if (_type == ITEM_HELPER + 37)
	{
		Attribute2 = 0;
	}

	SetOption = SetOption & 15;

	int SOption = SetOption & 3;
	int SOptionStatValue = 0;

	if (SOption != 1 && SOption != 2)
	{
		SOption = 0;
	}

	if ((((SetOption >> 2) & 3) != 1) && (((SetOption >> 2) & 3) != 2))
	{
		SOption = 0;
	}

	if (gSetItemOption.IsSetItem(_type) != 0 && SetOption != 255 && SOption != 0)
	{
		this->m_SetOption = SetOption;
		if (this->m_SetOption != 0)
		{
			this->m_NewOption = 0;
			Attribute2 = 0;
			SOptionStatValue = (SetOption >> 2) & 3;
		}
	}
	else
	{
		this->m_SetOption = 0;
	}

	memset(this->m_SkillResistance, 0, sizeof(this->m_SkillResistance));
		if (_type == 19 || _type == 2066 || _type == 2570 || _type == 1037)
			Attribute2 = 0;
	int iChaosItem = 0;
	switch (this->m_Type)
	{
	case 0x406:
		iChaosItem = 15;
		break;
	case 0xA07:
		iChaosItem = 25;
		break;
	case 0x806:
		iChaosItem = 30;
		break;
	}
	if (ItemGetDurability(this->m_Type, 0, 0, 0))
	{
		//v22 = ItemGetDurability(this->m_Type, this->m_Level, Attribute2 & 0x7F, this->m_SetOption);
		this->m_BaseDurability = (double)ItemGetDurability(this->m_Type, this->m_Level, Attribute2 & 0x7F, this->m_SetOption);
		//m_BaseDurability = (float)ItemGetDurability(m_Type, m_Level, Attribute2 & 0x7F, m_SetOption);
	}
	else
	{
		this->m_BaseDurability = 0.0;
	}
	this->m_DurabilityState[0] = this->m_BaseDurability * 0.5;
	this->m_DurabilityState[1] = this->m_BaseDurability * 0.300000011920929;
	this->m_DurabilityState[2] = this->m_BaseDurability * 0.2000000029802322;
	this->m_Value = p->Value;
	this->m_AttackSpeed = p->AttackSpeed;
	this->m_TwoHand = p->TwoHand;
	this->m_DamageMin = p->DamageMin;
	this->m_DamageMax = p->DamageMax;
	this->m_SuccessfulBlocking = p->SuccessfulBlocking;
	this->m_Defense = p->Defense;
	this->m_MagicDefense = p->MagicDefense;
	this->m_WalkSpeed = p->WalkSpeed;
	this->m_Magic = p->MagicPW;
	//v22 = p->Durability;
	this->m_Durability = (double)p->Durability;
	this->m_serial = p->Serial;
	this->m_QuestItem = p->QuestItem;
	this->m_RequireLeaderShip = 0;

	if (this->m_Durability == 0.0)
	{
		this->m_CurrentDurabilityState = 1.0;
	}
	else if (this->m_DurabilityState[2] <= (double)this->m_Durability)
	{
		if (this->m_DurabilityState[1] <= (double)this->m_Durability)
		{
			if (this->m_DurabilityState[0] <= (double)this->m_Durability)
				this->m_CurrentDurabilityState = 0.0;
			else
				this->m_CurrentDurabilityState = 0.2;
		}
		else
		{
			this->m_CurrentDurabilityState = 0.30000001;
		}
	}
	else
	{
		this->m_CurrentDurabilityState = 0.5;
	}
	memcpy(this->m_RequireClass, p->RequireClass, 8u);
	for (int i = 0; i < 7; ++i)
		this->m_Resistance[i] = this->m_Level * p->Resistance[i];
	ItemLevel = p->Level;
	if ((Attribute2 & 0x3F) <= 0)
	{
		if (this->m_SetOption)
			ItemLevel = p->Level + 25;
	}
	else
	{
		ItemLevel = p->Level + 25;
	}
	if (p->RequireStrength)
		this->m_RequireStrength = 3 * (ItemLevel + 3 * this->m_Level) * p->RequireStrength / 100 + 20;
	else
		this->m_RequireStrength = 0;
	if (p->RequireDexterity)
		this->m_RequireDexterity = 3 * (ItemLevel + 3 * this->m_Level) * p->RequireDexterity / 100 + 20;
	else
		this->m_RequireDexterity = 0;
	if (p->RequireEnergy)
		this->m_RequireEnergy = 4 * (ItemLevel + 3 * this->m_Level) * p->RequireEnergy / 100 + 20;
	else
		this->m_RequireEnergy = 0;
	if (_type >= 0 && _type < 6144)
	{
		if (p->RequireVitality)
			this->m_RequireVitality = 3 * (ItemLevel + 3 * this->m_Level) * p->RequireVitality / 100 + 20;
		else
			this->m_RequireVitality = 0;
		if (p->RequireLeadership)
			this->m_RequireLeaderShip = 3 * (ItemLevel + 3 * this->m_Level) * p->RequireVitality / 100 + 20;
		else
			this->m_RequireLeaderShip = 0;
	}
	if (_type == 6661)
		this->m_RequireLeaderShip = 15 * LOWORD(this->m_PetItem_Level) + 185;
	if (p->RequireLevel)
	{
		if (_type == 6660)
		{
			this->m_RequireLevel = 2 * LOWORD(this->m_PetItem_Level) + 218;
		}
		else if (_type < 6147 || _type > 6150)
		{
			if (_type < 6151 || _type > 6168)
			{
				if (_type < 0 || _type >= 6144)
				{
					this->m_RequireLevel = p->RequireLevel + 4 * this->m_Level;
				}
				else if (p->RequireLevel)
				{
					this->m_RequireLevel = p->RequireLevel;
				}
			}
			else
			{
				this->m_RequireLevel = p->RequireLevel;
			}
		}
		else
		{
			this->m_RequireLevel = 5 * this->m_Level + p->RequireLevel;
		}
	}
	else
	{
		this->m_RequireLevel = 0;
	}
	if (this->m_Type == 6666)
	{
		if (ItemLevel > 2)
			this->m_RequireLevel = 50;
		else
			this->m_RequireLevel = 20;
	}
	if ((Attribute2 & 0x3F) > 0 && (signed int)this->m_RequireLevel > 0 && (_type < 0 || _type >= 6144))
		this->m_RequireLevel += 20;
	if (this->m_SetOption)
		ItemLevel = p->Level + 30;
	this->m_Leadership = 0;
	if ((signed int)this->m_DamageMax > 0)
	{
		if (this->m_SetOption && ItemLevel)
		{
			this->m_DamageMax += (unsigned int)(25 * this->m_DamageMin / p->Level) + 5;
			this->m_DamageMax += ItemLevel / 40 + 5;
		}
		else if ((Attribute2 & 0x3F) > 0)
		{
			if (iChaosItem)
			{
				this->m_DamageMax += iChaosItem;
			}
			else if (p->Level)
			{
				this->m_DamageMax += (unsigned int)(25 * this->m_DamageMin / p->Level) + 5;
			}
		}
		this->m_DamageMax += 3 * this->m_Level;
		if (this->m_Level >= 10)
		{

			/*v8 = (this->m_Level - 8) * (this->m_Level - 9);
			this->m_DamageMax += ((signed int)v8 - HIDWORD(v8)) >> 1;*/
			m_DamageMax += (m_Level - 9)*(m_Level - 9 + 1) / 2;
		}
	}
	if ((signed int)this->m_DamageMin > 0)
	{
		if (this->m_SetOption && ItemLevel)
		{
			this->m_DamageMin += (unsigned int)(25 * this->m_DamageMin / p->Level) + 5;
			this->m_DamageMin += ItemLevel / 40 + 5;
		}
		else if ((Attribute2 & 0x3F) > 0)
		{
			if (iChaosItem)
			{
				this->m_DamageMin += iChaosItem;
			}
			else if (p->Level)
			{
				this->m_DamageMin += (unsigned int)(25 * this->m_DamageMin / p->Level) + 5;
			}
		}
		this->m_DamageMin += 3 * this->m_Level;
		if (this->m_Level >= 10)
		{
			/*v9 = (this->m_Level - 8) * (this->m_Level - 9);
			this->m_DamageMin += ((signed int)v9 - HIDWORD(v9)) >> 1;*/
			m_DamageMin += (m_Level - 9)*(m_Level - 9 + 1) / 2;
		}
	}
	if ((signed int)this->m_Magic > 0)
	{
		if (this->m_SetOption && ItemLevel)
		{
			this->m_Magic += (unsigned int)(25 * this->m_Magic / p->Level) + 5;
			this->m_Magic += ItemLevel / 60 + 2;
		}
		else if ((Attribute2 & 0x3F) > 0)
		{
			if (iChaosItem)
			{
				this->m_Magic += iChaosItem;
			}
			else if (p->Level)
			{
				this->m_Magic += (unsigned int)(25 * this->m_Magic / p->Level) + 5;
			}
		}
		this->m_Magic += 3 * this->m_Level;
		if (this->m_Level >= 10)
		{
			/*v10 = (this->m_Level - 8) * (this->m_Level - 9);
			this->m_Magic += ((signed int)v10 - HIDWORD(v10)) >> 1;*/
			m_Magic += (m_Level - 9)*(m_Level - 9 + 1) / 2;
		}
	}
	if (p->SuccessfulBlocking > 0)
	{
		if (this->m_SetOption && ItemLevel)
		{
			this->m_SuccessfulBlocking += (unsigned int)(25 * this->m_SuccessfulBlocking / p->Level) + 5;
			this->m_SuccessfulBlocking += ItemLevel / 40 + 5;
		}
		else if ((Attribute2 & 0x3F) > 0 && p->Level)
		{
			this->m_SuccessfulBlocking += (unsigned int)(25 * this->m_SuccessfulBlocking / p->Level) + 5;
		}
		this->m_SuccessfulBlocking += 3 * this->m_Level;
		if (this->m_Level >= 10)
		{
			/*v11 = (this->m_Level - 8) * (this->m_Level - 9);
			this->m_SuccessfulBlocking += ((signed int)v11 - HIDWORD(v11)) >> 1;*/
			m_SuccessfulBlocking += (m_Level - 9)*(m_Level - 9 + 1) / 2;
		}
	}
	if (p->Defense > 0)
	{
		if (this->m_Type < 3072 || this->m_Type >= 3584)
		{
			if (this->m_SetOption && ItemLevel)
			{
				this->m_Defense += 12 * this->m_Defense / p->Level + p->Level / 5 + 4;
				this->m_Defense += 3 * this->m_Defense / ItemLevel + ItemLevel / 30 + 2;
			}
			else if ((Attribute2 & 0x3F) > 0 && p->Level)
			{
				this->m_Defense += 12 * this->m_Defense / p->Level + p->Level / 5 + 4;
			}
			if ((_type < 6147 || _type > 6150) && _type != 6686 && _type != 6660)
				this->m_Defense += 3 * this->m_Level;
			else
				this->m_Defense += 2 * this->m_Level;
			if (this->m_Level >= 10)
			{
				/*v12 = (this->m_Level - 8) * (this->m_Level - 9);
				this->m_Defense += ((signed int)v12 - HIDWORD(v12)) >> 1;*/
				m_Defense += (m_Level - 9)*(m_Level - 9 + 1) / 2;
			}
		}
		else
		{
			this->m_Defense += this->m_Level;
			if (this->m_SetOption && ItemLevel)
				this->m_Defense += (unsigned int)(20 * this->m_Defense / ItemLevel) + 2;
		}
	}
	if (_type == 6686)
	{
		this->m_Defense = 2 * this->m_Level + 15;
		if (this->m_Level >= 10)
		{
			/*v13 = (this->m_Level - 8) * (this->m_Level - 9);
			this->m_Defense += ((signed int)v13 - HIDWORD(v13)) >> 1;*/
			m_Defense += (m_Level - 9)*(m_Level - 9 + 1) / 2;
		}
	}
	if (p->MagicDefense > 0)
	{
		this->m_MagicDefense += 3 * this->m_Level;
		if (this->m_Level >= 10)
		{
			/*v14 = (this->m_Level - 8) * (this->m_Level - 9);
			this->m_MagicDefense += ((signed int)v14 - HIDWORD(v14)) >> 1;*/
			m_MagicDefense += (m_Level - 9)*(m_Level - 9 + 1) / 2;
		}
	}
	this->m_Level &= 0xFu;
	memset(this->m_Special, 0, 8u);
	memset(this->m_SpecialValue, 0, 8u);
	this->m_SpecialNum = 0;
	this->m_Option1 = 0;
	this->m_Option2 = 0;
	this->m_Option3 = 0;
	this->m_SkillChange = 0;
	if (Option1 && p->SkillType)
	{
		if (p->SkillType == 66)
		{
			this->m_SkillChange = 1;
			this->m_Special[this->m_SpecialNum] = 0;
			this->m_Option1 = 1;
		}
		else
		{
			this->m_Special[this->m_SpecialNum] = p->SkillType;
			this->m_Option1 = 1;
		}
	}
	if (this->m_Type == 6659)
	{
		this->m_Option1 = 1;
		this->m_Special[this->m_SpecialNum] = 49;
	}
	if (this->m_Type == 6660)
	{
		this->m_Option1 = 1;
		this->m_Special[this->m_SpecialNum] = 62;
	}
	if (this->m_Type == 6693)
	{
		this->m_Option1 = 1;
		this->m_Special[this->m_SpecialNum] = 76;
	}
	++this->m_SpecialNum;
	if (Option2)
	{
		if (_type >= 0 && _type < 6144)
		{
			this->m_Special[this->m_SpecialNum] = 84;
			this->m_Option2 = 1;
		}
		if (_type >= 6144 && _type <= 6150)
		{
			this->m_Special[this->m_SpecialNum] = 84;
			this->m_Option2 = 1;
		}
		if (_type == 6686)
		{
			this->m_Special[this->m_SpecialNum] = 84;
			this->m_Option2 = 1;
		}
		if (_type >= 6423 && _type <= 6426)
		{
			this->m_Special[this->m_SpecialNum] = 84;
			this->m_Option2 = 1;
		}
	}
	++this->m_SpecialNum;
	if (Option3)
	{
		if (_type >= 0 && _type < 2560)
		{
			this->m_Special[this->m_SpecialNum] = 80;
			this->m_Option3 = Option3;
			this->m_RequireStrength += 4 * (unsigned __int8)Option3;
		}
		if (_type >= 2560 && _type < 3072)
		{
			this->m_Special[this->m_SpecialNum] = 81;
			this->m_Option3 = Option3;
			this->m_RequireStrength += 4 * (unsigned __int8)Option3;
		}
		if (_type >= 3072 && _type < 3584)
		{
			this->m_Special[this->m_SpecialNum] = 82;
			this->m_Option3 = Option3;
			this->m_RequireStrength += 4 * (unsigned __int8)Option3;
		}
		if (_type >= 3584 && _type < 6144)
		{
			this->m_Special[this->m_SpecialNum] = 83;
			this->m_Option3 = Option3;
			this->m_RequireStrength += 4 * (unsigned __int8)Option3;
		}
		if (_type >= 6664 && _type < 6670 || _type >= 6676 && _type <= 6684)
		{
			if (_type == 6680)
			{
				this->m_Special[this->m_SpecialNum] = -84;
				this->m_Option3 = Option3;
			}
			else if (_type == 6684)
			{
				this->m_Special[this->m_SpecialNum] = -83;
				this->m_Option3 = Option3;
			}
			else
			{
				this->m_Special[this->m_SpecialNum] = 85;
				this->m_Option3 = Option3;
			}
		}
		if (_type == 6686)
		{
			this->m_Special[this->m_SpecialNum] = 80;
			this->m_Option3 = Option3;
			this->m_RequireStrength += 4 * (unsigned __int8)Option3;
		}
		switch (_type)
		{
		case 6144:
			this->m_Special[this->m_SpecialNum] = 85;
			this->m_Option3 = Option3;
			break;
		case 6145:
			this->m_Special[this->m_SpecialNum] = 81;
			this->m_Option3 = Option3;
			this->m_RequireStrength += 4 * (unsigned __int8)Option3;
			break;
		case 6146:
			this->m_Special[this->m_SpecialNum] = 80;
			this->m_Option3 = Option3;
			this->m_RequireStrength += 4 * (unsigned __int8)Option3;
			break;
		case 6147:
			this->m_Special[this->m_SpecialNum] = 80;
			this->m_Option3 = Option3;
			this->m_RequireStrength += 4 * (unsigned __int8)Option3;
			if (this->m_NewOption & 0x20)
				this->m_Special[this->m_SpecialNum] = 85;
			else
				this->m_Special[this->m_SpecialNum] = 80;
			break;
		case 6148:
			this->m_Option3 = Option3;
			this->m_RequireStrength += 4 * (unsigned __int8)Option3;
			if (this->m_NewOption & 0x20)
				this->m_Special[this->m_SpecialNum] = 81;
			else
				this->m_Special[this->m_SpecialNum] = 85;
			break;
		case 6149:
			this->m_Option3 = Option3;
			this->m_RequireStrength += 4 * (unsigned __int8)Option3;
			if (this->m_NewOption & 0x20)
				this->m_Special[this->m_SpecialNum] = 80;
			else
				this->m_Special[this->m_SpecialNum] = 85;
			break;
		case 6150:
			this->m_Option3 = Option3;
			this->m_RequireStrength += 4 * (unsigned __int8)Option3;
			if (this->m_NewOption & 0x20)
				this->m_Special[this->m_SpecialNum] = 80;
			else
				this->m_Special[this->m_SpecialNum] = 81;
			break;
		case 6423:
			this->m_Option3 = Option3;
			this->m_Special[this->m_SpecialNum] = 80;
			break;
		case 6424:
			this->m_Option3 = Option3;
			this->m_Special[this->m_SpecialNum++] = 80;
			this->m_Special[this->m_SpecialNum] = 81;
			break;
		case 6425:
			this->m_Option3 = Option3;
			this->m_Special[this->m_SpecialNum++] = 81;
			this->m_Special[this->m_SpecialNum] = 113;
			break;
		case 6426:
			this->m_Option3 = Option3;
			this->m_Special[this->m_SpecialNum] = 80;
			break;
		case 6659:
			this->m_Option3 = Option3;
			if (this->m_Option3 & 2)
				this->m_Special[this->m_SpecialNum++] = 103;
			if (this->m_Option3 & 4)
			{
				this->m_Special[this->m_SpecialNum++] = 97;
				this->m_AttackSpeed += 5;
			}
			if (this->m_Option3 & 1)
				this->m_Special[this->m_SpecialNum] = 104;
			break;
		}
		if (_type == 6686)
		{
			this->m_Option3 = Option3;
			this->m_RequireStrength += 4 * (unsigned __int8)Option3;
			this->m_Special[this->m_SpecialNum] = 80;
		}
	}
	++this->m_SpecialNum;
	if (_type >= 3072 && _type < 6144 || _type >= 6664 && _type <= 6665 || _type >= 6677 && _type <= 6680)
	{
		if ((this->m_NewOption >> 5) & 1)
			this->m_Special[this->m_SpecialNum++] = 86;
		if ((this->m_NewOption >> 4) & 1)
			this->m_Special[this->m_SpecialNum++] = 87;
		if ((this->m_NewOption >> 3) & 1)
			this->m_Special[this->m_SpecialNum++] = 88;
		if ((this->m_NewOption >> 2) & 1)
			this->m_Special[this->m_SpecialNum++] = 89;
		if ((this->m_NewOption >> 1) & 1)
			this->m_Special[this->m_SpecialNum++] = 90;
		if (this->m_NewOption & 1)
			this->m_Special[this->m_SpecialNum++] = 91;
	}
	if (_type >= 0 && _type < 3072 || _type >= 6668 && _type <= 6669 || _type >= 6681 && _type <= 6684)
	{
		if ((this->m_NewOption >> 5) & 1)
			this->m_Special[this->m_SpecialNum++] = 92;
		if ((_type < 2560 || _type >= 3072) && _type != 6668 && _type != 6681 && _type != 6683)
		{
			if ((this->m_NewOption >> 4) & 1)
				this->m_Special[this->m_SpecialNum++] = 93;
			if ((this->m_NewOption >> 3) & 1)
				this->m_Special[this->m_SpecialNum++] = 94;
		}
		else
		{
			if ((this->m_NewOption >> 4) & 1)
				this->m_Special[this->m_SpecialNum++] = 95;
			if ((this->m_NewOption >> 3) & 1)
				this->m_Special[this->m_SpecialNum++] = 96;
		}
		if ((this->m_NewOption >> 2) & 1)
		{
			this->m_Special[this->m_SpecialNum++] = 97;
			this->m_AttackSpeed += 7;
		}
		if ((this->m_NewOption >> 1) & 1)
			this->m_Special[this->m_SpecialNum++] = 98;
		if (this->m_NewOption & 1)
			this->m_Special[this->m_SpecialNum++] = 99;
	}
	if (_type >= 6147 && _type <= 6150 || _type == 6686)
	{
		if (this->m_NewOption & 1)
			this->m_Special[this->m_SpecialNum++] = 100;
		if (this->m_NewOption & 2)
			this->m_Special[this->m_SpecialNum++] = 101;
		if (this->m_NewOption & 4)
			this->m_Special[this->m_SpecialNum++] = 102;
		if (this->m_NewOption & 8)
			this->m_Special[this->m_SpecialNum++] = 105;
	}
	if (_type == 6693)
	{
		if (this->m_NewOption & 1)
		{
			this->m_Special[this->m_SpecialNum++] = 106;
		}
		else if (this->m_NewOption & 2)
		{
			this->m_Special[this->m_SpecialNum++] = 107;
		}
	}
	if (SOptionStatValue && p->SetAttr)
	{
		this->m_Special[this->m_SpecialNum] = p->SetAttr - 61;
		this->m_SetAddStat = 5 * SOptionStatValue;
		++this->m_SpecialNum;
	}
	this->m_Part = p->ItemSlot;
	Value();
	if (this->m_Type != 2055 && this->m_Type != 2063)
	{
		this->m_DamageMinOrigin = this->m_DamageMin;
		this->m_DefenseOrigin = this->m_Defense;
		m_DamageMin -= (WORD)(m_DamageMin*m_CurrentDurabilityState);
		m_DamageMax -= (WORD)(m_DamageMax*m_CurrentDurabilityState);
		m_Defense -= (WORD)(m_Defense*m_CurrentDurabilityState);
		m_SuccessfulBlocking -= (BYTE)(m_SuccessfulBlocking*m_CurrentDurabilityState);
		/*v22 = this->m_DamageMin;
		v15 = (double)v22 * this->m_CurrentDurabilityState;
		v20 = v21 | 0xC00;
		v19 = (signed int)v15;
		this->m_DamageMin -= (signed int)v15;
		v22 = this->m_DamageMax;
		v16 = (double)v22 * this->m_CurrentDurabilityState;
		v20 = v21 | 0xC00;
		v19 = (signed int)v16;
		this->m_DamageMax -= (signed int)v16;
		v22 = this->m_Defense;
		v17 = (double)v22 * this->m_CurrentDurabilityState;
		v20 = v21 | 0xC00;
		v19 = (signed int)v17;
		this->m_Defense -= (signed int)v17;
		v22 = this->m_SuccessfulBlocking;
		v18 = (double)v22 * this->m_CurrentDurabilityState;
		v20 = v21 | 0xC00;
		v19 = (signed int)v18;
		this->m_SuccessfulBlocking -= (signed int)v18;*/
		if (this->m_Durability < 1.0)
			this->m_AttackSpeed = 0;
	}
	if (this->m_Durability == 0.0)
		memset(this->m_Resistance, 0, 7u);
}
//#ifdef ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
//void CItem::Convert(int type, BYTE Option1, BYTE Option2, BYTE Option3, BYTE Attribute2, BYTE SetOption, BYTE ItemEffectEx, BYTE SocketOption[], BYTE SocketBonusOption, BYTE DbVersion)
////#else
////#ifdef ADD_380ITEM_NEWOPTION_20060711
////void CItem::Convert(int type, BYTE Option1, BYTE Option2, BYTE Option3, BYTE Attribute2, BYTE SetOption, BYTE ItemEffectEx, BYTE DbVersion)
////#else	
////void CItem::Convert(int type, BYTE Option1, BYTE Option2, BYTE Option3, BYTE Attribute2, BYTE SetOption, BYTE DbVersion)
////#endif // ADD_380ITEM_NEWOPTION_20060711
////#endif // ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
//{
//	int _type = type;
//	int ItemLevel;
//
//	if (DbVersion == 0x00)
//	{
//		_type = ((type / 16)*MAX_ITEM_INDEX) + (type % 16);
//	}
//
//#ifdef ITEM_DBSIZE_EXTEND_20050706
//#ifdef ITEM_INDEX_EXTEND_20050706
//	else if (DbVersion <= 0x02)
//	{
//		_type = ((type / 32)*MAX_ITEM_INDEX) + (type % 32);
//	}
//#endif
//#endif
//
//	if (_type > MAX_ITEM - 1)
//	{
//		LogAddC(LOGC_RED, "error-L1 : ItemIndex error %d", _type);
//	}
//
//	ITEM_ATTRIBUTE *p = &ItemAttribute[_type];
//
//	m_serial = ItemAttribute[_type].Serial;
//	m_Type = type;
//
//#ifdef ITEM_INDEX_EXTEND_20050706
//	if (DbVersion <= 0x02)
//#else
//	if (DbVersion == 0x00)
//#endif
//		m_Type = _type;
//
//	m_NewOption = Attribute2;
//	if (p->OptionFlag == 0)
//	{
//		m_NewOption = 0;
//	}
//#ifdef NEW_FORSKYLAND2
//#ifdef ADD_THIRD_WING_20070525	// 3차날개 엑설런트 처리 하지 않는다.
//	if ((_type >= ITEM_WING + 3 && _type <= ITEM_WING + 6) || (_type == ITEM_HELPER + 30)
//#ifdef ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912	// 날개는 엑설런트 처리안함
//		|| (_type == ITEM_WING + 41)	// 신규캐릭터 1차날개(재앙의 날개)
//#ifdef ADD_SUMMONER_SECOND_THIRD_WING_20071130
//		|| (_type == ITEM_WING + 42)	// 신규캐릭터 2차날개(절망의 날개)
//		|| (_type == ITEM_WING + 43)	// 신규캐릭터 3차날개(차원의 날개)
//#endif		
//#endif	// ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912		
//		|| (_type >= ITEM_WING + 36 && _type <= ITEM_WING + 40)) // 날개
//#else	
//#ifdef DARKLORD_WORK
//	if ((_type >= ITEM_WING + 3 && _type <= ITEM_WING + 6) || (_type == ITEM_HELPER + 30)) // 날개	    
//#else
//	if (_type >= ITEM_WING + 3 && _type <= ITEM_WING + 6) // 날개	    
//#endif
//#endif	// ADD_THIRD_WING_20070525
//	{
//		Attribute2 = 0;
//	}
//#endif
//
//#ifdef ADD_ITEM_FENRIR_01_20051110
//	// 펜릴의 경우 액설런트 처리 ( 아이템 착용레벨, 내구도 등) 하지 않는다.
//	if (_type == MAKE_ITEMNUM(13, 37))
//	{
//		Attribute2 = 0;
//	}
//#endif
//
//#if GAME_VERSION >= G_V_99B
//	SetOption = SetOption & 0x0f;
//
//	int	SOption = SetOption & 0x03;					// 세트 옵션 타입 (1:A타입, 2:B타입)
//	int	SOptionStatValue = 0;						// 세트 옵션 스탯 값 (1:5, 2:10)
//	if (SOption != 1 && SOption != 2)
//	{	// SetOption == 1 A Option || SetOption == 2 B Option
//		SOption = 0;
//	}
//
//	if (((SetOption >> 2) & 0x03) != 1 && ((SetOption >> 2) & 0x03) != 2)
//	{	// SetOption == 1 A Option || SetOption == 2 B Option
//		SOption = 0;
//	}
//
//	if (gSetItemOption.IsSetItem(_type) && SetOption != 0xFF && SOption)
//	{	// 세트 아이템정보가 있을때만 적용한다
//		m_SetOption = SetOption;
//
//		if (m_SetOption)
//		{	// 세트옵션일때는 엑설런트 옵션은 무시..
//			m_NewOption = 0;
//			Attribute2 = 0;
//
//			SOptionStatValue = (SetOption >> 2) & 0x03;		// 세트 옵션 스탯 값 (1:5, 2:10)
//		}
//	}
//	else
//	{
//		m_SetOption = 0;
//	}
//#endif
//
//#ifdef ADD_380ITEM_NEWOPTION_20060711
//	m_ItemOptionEx = ItemEffectEx;			// 추가옵션 정보. 380추가옵션 상위 1bit.
//#endif // ADD_380ITEM_NEWOPTION_20060711
//
//#ifndef CHARACTERDB_SERVER
//#ifdef ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
//	if (g_SocketOptionSystem.IsEnableSocketItem(this) == true)
//	{
//		if (SocketOption != NULL)
//		{
//			m_BonusSocketOption = SocketBonusOption;
//
//			for (int i = 0; i < MAX_SOCKET_SLOT; i++)
//			{
//				m_SocketOption[i] = SocketOption[i];
//			}
//		}
//
//#ifdef MODIFY_ITEM_SOCKET_OPTION_BUGFIX_02_20080630
//		if (g_SocketOptionSystem.IsSocketItem(this) == true)
//		{
//			m_ItemOptionEx = 0;
//			m_SetOption = 0;
//			Attribute2 = 0;
//			m_NewOption = 0;
//			m_JewelOfHarmonyOption = 0;
//		}
//		else
//		{
//			m_BonusSocketOption = 0;
//		}
//#else
//		// 소켓 아이템의 경우는 엑설런트, 세트, 380, 조화옵션이 붙지 않는다.
//		m_ItemOptionEx = 0;
//		m_SetOption = 0;
//		Attribute2 = 0;
//		m_NewOption = 0;
//		m_JewelOfHarmonyOption = 0;
//#endif // MODIFY_ITEM_SOCKET_OPTION_BUGFIX_02_20080630
//	}
//	else
//	{
//		m_BonusSocketOption = 0;
//		for (int i = 0; i < MAX_SOCKET_SLOT; i++)
//		{
//			m_SocketOption[i] = SOCKETSLOT_NONE;
//		}
//	}
//#endif // ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
//#endif
//
//	memset(m_SkillResistance, 0, sizeof(m_SkillResistance));
//
//	if (_type == MAKE_ITEMNUM(0, 19) ||
//		_type == MAKE_ITEMNUM(4, 18) ||
//		_type == MAKE_ITEMNUM(5, 10)
//#ifdef ADD_WEAPON_OF_ARCHANGEL_SCEPTER_20050706
//		|| _type == MAKE_ITEMNUM(2, 13)
//#endif
//		)
//
//	{	// 절대 무기의 경우 무조건 엑설런트 처리를 안한다
//		Attribute2 = 0;
//	}
//
//	int	iChaosItem = 0;
//	if (m_Type == MAKE_ITEMNUM(2, 6))		// 카오스드라곤도끼
//
//	{
//		iChaosItem = 15;
//	}
//	else if (m_Type == MAKE_ITEMNUM(5, 7))	// 카오스번개지팡이
//	{
//		iChaosItem = 25;
//	}
//	else if (m_Type == MAKE_ITEMNUM(4, 6))	// 카오스네이쳐보우
//	{
//		iChaosItem = 30;
//	}
//
//	if (ItemGetDurability(m_Type, 0, 0, 0))
//	{
//		m_BaseDurability = (float)ItemGetDurability(m_Type, m_Level, Attribute2 & 0x7F, m_SetOption);
//	}
//	else
//	{
//		m_BaseDurability = 0.f;
//	}
//	m_DurabilityState[0] = m_BaseDurability * 0.5f;
//	m_DurabilityState[1] = m_BaseDurability * 0.3f;
//	m_DurabilityState[2] = m_BaseDurability * 0.2f;
//
//
//	m_Value = p->Value;
//	m_AttackSpeed = p->AttackSpeed;
//	m_TwoHand = p->TwoHand;
//	m_DamageMin = p->DamageMin;
//	m_DamageMax = p->DamageMax;
//	m_SuccessfulBlocking = p->SuccessfulBlocking;
//	m_Defense = p->Defense;
//	m_MagicDefense = p->MagicDefense;
//	m_WalkSpeed = p->WalkSpeed;
//#ifdef ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912	// 책일경우 마력대신 저주적용
//	// 지팡이류에서 왼쪽에 장착하면 책이다..
//	if ((_type >> ITEM_BITSHIFT) == ITEM_STAFF / MAX_ITEM_INDEX
//		&& p->ItemSlot == EQUIPMENT_WEAPON_LEFT
//		)
//	{
//		m_Magic = 0;
//		// 책이면 저주력력증가
//		m_Curse = p->MagicPW;
//
//	}
//	else
//	{
//		m_Magic = p->MagicPW;
//		m_Curse = 0;
//	}
//#else	// ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912
//	m_Magic = p->MagicPW;
//#endif	// ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912
//
//#ifdef CHARACTERDB_SERVER
//	m_Durability = p->Durability;
//#endif
//
//	m_serial = p->Serial;
//
//#ifdef NEW_SKILL_FORSKYLAND
//	m_QuestItem = p->QuestItem;		// 퀘스트용 아이템가?
//#endif	
//
//#ifdef EXPAND_ITEMSCRIPT_01_20050808
//	m_RequireLeaderShip = 0;
//#endif
//
//#ifdef MODIFY_ITEMDURABILITY_BUGFIX_20080408	// 마법사의 반지, 문스톤 펜던트 제외한 모든 아이템의 경우 내구가 최대를 넘으면 최대값으로
//	if (m_BaseDurability > 10
//		&& _type != MAKE_ITEMNUM(13, 20)
//		&& (_type < MAKE_ITEMNUM(14, 0)
//			|| _type > MAKE_ITEMNUM(14, 8))
//#if GAME_VERSION >= G_V_S2_2
//		&& (_type < MAKE_ITEMNUM(14, 35)
//			|| _type > MAKE_ITEMNUM(14, 40))
//#endif
//		)
//	{
//		if (m_Durability > m_BaseDurability)
//		{
//			m_Durability = m_BaseDurability;
//		}
//	}
//#endif	// MODIFY_ITEMDURABILITY_BUGFIX_20080408
//
//#ifdef MODIFY_CALC_DURABILITY_20060523 
//	// 최대 내구도 보다 큰 경우 현재 내구도를 최대 값으로 설정
//	// 기본 내구도가 10 이상인 경우만 처리. 물약을 비롯한 예외적인 아이템이 존재함.
//	// 일반 무기류 아이템은 기본 10이 넘는다.
//	if (m_BaseDurability > 10)
//	{
//		if (m_Durability > m_BaseDurability)
//		{
//			m_Durability = m_BaseDurability;
//		}
//	}
//#endif // MODIFY_CALC_DURABILITY_20060523
//
//	// 내구도 상태설정	
//	if (m_Durability == 0.f)
//		m_CurrentDurabilityState = 1.f;
//	else if (m_Durability < m_DurabilityState[2])
//		m_CurrentDurabilityState = 0.5f;
//	else if (m_Durability < m_DurabilityState[1])
//		m_CurrentDurabilityState = 0.3f;
//	else if (m_Durability < m_DurabilityState[0])
//		m_CurrentDurabilityState = 0.2f;
//	else m_CurrentDurabilityState = 0.f;
//
//	memcpy(m_RequireClass, p->RequireClass, MAX_CLASSTYPE);
//	//memcpy(m_Resistance,   p->Resistance,   MAX_RESISTANCE);
//
//	for (int i = 0; i < MAX_RESISTANCE; i++)
//	{
//		m_Resistance[i] = p->Resistance[i] * m_Level;
//	}
//
//
//	//-------------------------------------------------------------------------
//	//
//	// ★ 아이템 사용가능 스탯 요구치 기본 설정
//	//		- 아이템 추가 옵션에 따른 요구치 증가는 아래부분에서 처리.
//	//
//	//-------------------------------------------------------------------------
//	ItemLevel = p->Level;
//
//	// 1. > 엑설런트 아이템 확인
//	if ((Attribute2 & 63) > 0)
//		ItemLevel = p->Level + 25;
//
//	// 2. > 세트 아이템 확인
//	else if (m_SetOption)
//	{
//		ItemLevel = p->Level + 25;
//	}
//
//	// 3. > 일반 / 엑설런트 / 세트 아이템 여부에 따라 요구치 설정.
//	if (p->RequireStrength)
//		m_RequireStrength = 20 + p->RequireStrength *(ItemLevel + m_Level * 3) * 3 / 100;
//	else
//		m_RequireStrength = 0;
//
//	if (p->RequireDexterity)
//		m_RequireDexterity = 20 + p->RequireDexterity*(ItemLevel + m_Level * 3) * 3 / 100;
//	else
//		m_RequireDexterity = 0;
//
//	if (p->RequireEnergy)
//		m_RequireEnergy = 20 + p->RequireEnergy   *(ItemLevel + m_Level * 3) * 4 / 100;
//	else
//		m_RequireEnergy = 0;
//
//#ifdef ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912	// 신규캐릭터 책(서)에 대한 요구에너지 계산
//	if (p->RequireEnergy)
//	{
//		if ((_type >> ITEM_BITSHIFT) == ITEM_STAFF / MAX_ITEM_INDEX
//			&& p->ItemSlot == EQUIPMENT_WEAPON_LEFT
//			)
//		{
//			m_RequireEnergy = 20 + p->RequireEnergy   *(ItemLevel + m_Level * 1) * 3 / 100;
//		}
//	}
//	else
//	{
//		m_RequireEnergy = 0;
//	}
//#endif	// ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912
//
//#ifdef EXPAND_ITEMSCRIPT_01_20050808
//	if (_type >= ITEM_SWORD && _type < ITEM_WING)
//	{
//		if (p->RequireVitality)
//			m_RequireVitality = 20 + p->RequireVitality *(ItemLevel + m_Level * 3) * 3 / 100;
//		else
//			m_RequireVitality = 0;
//
//		if (p->RequireLeadership)
//			m_RequireLeaderShip = 20 + p->RequireVitality *(ItemLevel + m_Level * 3) * 3 / 100;
//		else
//			m_RequireLeaderShip = 0;
//	}
//#endif
//
//	// 4. > 다크 스피릿 요구 통솔 예외 처리
//#ifdef EXPAND_ITEMSCRIPT_01_20050808
//	// 다크스피릿만 코드에 박혀 있다.
//#ifdef MODIFY_SETITEM_LEADERSHIP_BUGFIX
//	if (_type == MAKE_ITEMNUM(13, 5)) {
//		// gObjValidItem 에서 통솔요구치 체크 버그 수정
//		// 다크스피릿은 item(kor).txt 에 요구수치가 없음으로 공식에 따라 직접 처리한다.
//		m_RequireLeaderShip = 185 + (m_PetItem_Level * 15);
//		p->RequireLeadership = 185 + (m_PetItem_Level * 15);
//	}
//#else
//	if (_type == MAKE_ITEMNUM(13, 5))
//		m_RequireLeaderShip = 185 + (m_PetItem_Level * 15);
//#endif // MODIFY_SETITEM_LEADERSHIP_BUGFIX
//
//
//#else
//#ifdef DARKLORD_WORK
//	if (_type == MAKE_ITEMNUM(13, 5)) // 다크스피릿만 요구 통솔이 필요 하다
//		m_RequireLeaderShip = 185 + (m_PetItem_Level * 15);
//	else
//		m_RequireLeaderShip = 0;
//#endif
//#endif // EXPAND_ITEMSCRIPT_01_20050808
//
//#ifndef CHARACTERDB_SERVER
//#ifdef ADD_JEWEL_OF_HARMONY_SYSTEM_20060530
//	// 조화의 보석 강화 아이템 옵션 : 필요힘/민첩 감소
//	if (g_kJewelOfHarmonySystem.IsActive(this) == TRUE)
//	{
//		BYTE btOption = g_kJewelOfHarmonySystem.GetItemStrengthenOption(this);
//#ifdef MODIFY_STAFF_DECREASE_DEXTERITY_BUGFIX_20080729
//		int iItemType = g_kJewelOfHarmonySystem._GetItemType(this);
//
//		if (iItemType == JEWELOFHARMONY_ITEM_TYPE_WEAPON)
//		{
//			if (btOption == AT_JEWELOFHARMONY_WEAPON_DECREASE_REQUIRE_STR)
//				m_HJOpStrength = g_kJewelOfHarmonySystem.GetItemEffectValue(this, AT_JEWELOFHARMONY_WEAPON_DECREASE_REQUIRE_STR);
//			else if (btOption == AT_JEWELOFHARMONY_WEAPON_DECREASE_REQUIRE_DEX)
//				m_HJOpDexterity = g_kJewelOfHarmonySystem.GetItemEffectValue(this, AT_JEWELOFHARMONY_WEAPON_DECREASE_REQUIRE_DEX);
//		}
//		else if (iItemType == JEWELOFHARMONY_ITEM_TYPE_STAFF)
//		{
//			if (btOption == AT_JEWELOFHARMONY_STAFF_DECREASE_REQUIRE_STR)
//				m_HJOpStrength = g_kJewelOfHarmonySystem.GetItemEffectValue(this, AT_JEWELOFHARMONY_STAFF_DECREASE_REQUIRE_STR);
//			else if (btOption == AT_JEWELOFHARMONY_STAFF_DECREASE_REQUIRE_DEX)
//				m_HJOpDexterity = g_kJewelOfHarmonySystem.GetItemEffectValue(this, AT_JEWELOFHARMONY_STAFF_DECREASE_REQUIRE_DEX);
//		}
//#else
//		if (btOption == AT_JEWELOFHARMONY_WEAPON_DECREASE_REQUIRE_STR)
//			m_HJOpStrength = g_kJewelOfHarmonySystem.GetItemEffectValue(this, AT_JEWELOFHARMONY_WEAPON_DECREASE_REQUIRE_STR);
//		else if (btOption == AT_JEWELOFHARMONY_STAFF_DECREASE_REQUIRE_STR)
//			m_HJOpStrength = g_kJewelOfHarmonySystem.GetItemEffectValue(this, AT_JEWELOFHARMONY_STAFF_DECREASE_REQUIRE_STR);
//		else if (btOption == AT_JEWELOFHARMONY_WEAPON_DECREASE_REQUIRE_DEX)
//			m_HJOpDexterity = g_kJewelOfHarmonySystem.GetItemEffectValue(this, AT_JEWELOFHARMONY_WEAPON_DECREASE_REQUIRE_DEX);
//		else if (btOption == AT_JEWELOFHARMONY_STAFF_DECREASE_REQUIRE_DEX)
//			m_HJOpDexterity = g_kJewelOfHarmonySystem.GetItemEffectValue(this, AT_JEWELOFHARMONY_STAFF_DECREASE_REQUIRE_DEX);
//#endif // MODIFY_STAFF_DECREASE_DEXTERITY_BUGFIX_20080729
//	}
//#ifdef MODIFY_ITEM_SOCKET_OPTION_BUGFIX_04_20080710
//	else
//	{
//		m_HJOpStrength = 0;
//		m_HJOpDexterity = 0;
//	}
//#endif // MODIFY_ITEM_SOCKET_OPTION_BUGFIX_04_20080710
//#endif // ADD_JEWEL_OF_HARMONY_SYSTEM_20060530
//
//#ifdef MODIFY_ITEM_SOCKET_OPTION_BUGFIX_03_20080704
//	g_SocketOptionSystem.SetRequireStatOption(this);
//#endif // MODIFY_ITEM_SOCKET_OPTION_BUGFIX_03_20080704
//#endif
//	// 5. > 요구 레벨 처리
//	if (p->RequireLevel)
//	{
//
//#ifdef DARKLORD_WORK
//		// 다크호스
//		if (_type == MAKE_ITEMNUM(13, 4))
//		{
//			m_RequireLevel = 218 + m_PetItem_Level * 2;
//		}
//		else
//#endif
//#ifdef ADD_THIRD_WING_20070525	// 3차 전직날개는 날개레벨에 상관없이 400으로 설정
//			if (_type >= ITEM_WING + 36 && _type <= ITEM_WING + 40)
//			{
//				m_RequireLevel = p->RequireLevel;
//			}
//			else
//#endif
//				// 추가 날개
//				if (_type >= ITEM_WING + 3 && _type <= ITEM_WING + 6)
//				{
//					m_RequireLevel = p->RequireLevel + m_Level * 5;
//				}
//#ifdef ADD_SUMMONER_SECOND_THIRD_WING_20071130	// 절망의 날개, 차원의 날개 레벨설정
//				else if (_type == ITEM_WING + 42) // 절망의 날개
//				{
//					m_RequireLevel = p->RequireLevel + m_Level * 5;
//				}
//				else if (_type == ITEM_WING + 43) // 차원의 날개
//				{
//					m_RequireLevel = p->RequireLevel;
//				}
//#endif
//#ifdef ADD_CHECKING_LEVEL_TO_LEARN_MAGIC_20041115
//		// 구슬 아이템 쪽만..
//				else
//					if ((_type >= MAKE_ITEMNUM(12, 7)) && (_type <= MAKE_ITEMNUM(12, 24)))
//					{
//
//						m_RequireLevel = p->RequireLevel;
//					}
//#endif
//#ifdef EXPAND_ITEMSCRIPT_01_20050808
//		// 무기, 방어구
//					else
//						if (_type >= ITEM_SWORD && _type < ITEM_WING)
//						{
//							if (p->RequireLevel)
//							{
//								//m_RequireLevel = 10+p->RequireLevel + (ItemLevel+m_Level*4)*5/100;
//								//m_RequireLevel = 10+p->RequireLevel + (p->Level+m_Level*4)*5/100;
//
//								// 레벨 제한의 경우 일반/세트/액설 모두 동일
//								m_RequireLevel = p->RequireLevel;
//							}
//						}
//#endif
//		// 반지,목걸이;
//						else
//						{
//							m_RequireLevel = p->RequireLevel + m_Level * 4;
//						}
//
//	}
//	else
//		m_RequireLevel = 0;
//
//
//	if (m_Type == ITEM_HELPER + 10)//변신반지
//	{
//		if (ItemLevel <= 2)
//			m_RequireLevel = 20;
//		else
//			m_RequireLevel = 50;
//	}
//
//	if ((Attribute2 & 63) > 0)		// 엑셀런트 옵션이 하나라도 붙어 있다면
//	{
//		if (m_RequireLevel > 0)
//		{
//
//#ifdef EXPAND_ITEMSCRIPT_01_20050808
//			if (_type < ITEM_SWORD || _type >= ITEM_WING)
//			{
//				// 레벨 제한의 경우 일반/세트/액설 모두 동일
//				m_RequireLevel += 20;
//			}
//#else
//			m_RequireLevel += 20;
//#endif
//
//		}
//	}
//	//-------------------------------------------------------------------------
//
//
//
//	//-------------------------------------------------------------------------
//	//
//	// ★ 아이템 기본 수치 설정
//	//
//	//	세트 아이템의 경우 
//	//	- 요구능력치 계산 시 + 25 적용
//	//	- 수치 계산 시 + 30 적용
//	//
//	//-------------------------------------------------------------------------
//
//	if (m_SetOption)
//	{
//		ItemLevel = p->Level + 30;
//	}
//
//#ifdef DARKLORD_WORK
//	m_Leadership = 0;
//#endif
//
//	if (m_DamageMax > 0)
//	{
//		if (m_SetOption && ItemLevel)
//		{	// 세트 아이템 공격력
//			m_DamageMax += m_DamageMin * 25 / p->Level + 5;
//			m_DamageMax += ItemLevel / 40 + 5;
//		}
//		else
//			if ((Attribute2 & 63) > 0)
//			{
//				if (iChaosItem)
//				{
//					m_DamageMax += iChaosItem;
//				}
//				else if (p->Level)
//				{
//					m_DamageMax += m_DamageMin * 25 / p->Level + 5;
//				}
//			}
//
//		m_DamageMax += m_Level * 3;
//
//		if (m_Level >= 10)
//		{	// +10 이상의 공격력 +
//#ifdef ITEM_12_13_20040401
//			m_DamageMax += (m_Level - 9)*(m_Level - 9 + 1) / 2;
//#else
//			m_DamageMax += (m_Level - 10) * 2 + 1;
//#endif
//		}
//	}
//
//	if (m_DamageMin > 0)
//	{
//		if (m_SetOption && ItemLevel)
//		{
//			m_DamageMin += m_DamageMin * 25 / p->Level + 5;
//			m_DamageMin += ItemLevel / 40 + 5;
//		}
//		else
//			if ((Attribute2 & 63) > 0)
//			{
//				if (iChaosItem)
//				{
//					m_DamageMin += iChaosItem;
//				}
//				else if (p->Level)
//					m_DamageMin += m_DamageMin * 25 / p->Level + 5;
//			}
//		m_DamageMin += m_Level * 3;
//
//		if (m_Level >= 10)
//		{	// +10 이상의 공격력 +
//#ifdef ITEM_12_13_20040401
//			m_DamageMin += (m_Level - 9)*(m_Level - 9 + 1) / 2;
//#else
//			m_DamageMin += (m_Level - 10) * 2 + 1;
//#endif
//		}
//	}
//
//	if (m_Magic > 0)
//	{
//		if (m_SetOption && ItemLevel)
//		{
//			m_Magic += m_Magic * 25 / p->Level + 5;
//			m_Magic += ItemLevel / 60 + 2;
//		}
//		else
//			if ((Attribute2 & 63) > 0)
//			{
//				if (iChaosItem)
//				{
//					m_Magic += iChaosItem;
//				}
//				else if (p->Level)
//					m_Magic += m_Magic * 25 / p->Level + 5;
//			}
//
//		m_Magic += m_Level * 3;
//
//		if (m_Level >= 10)
//		{	// +10 이상의 공격력 +
//#ifdef ITEM_12_13_20040401
//			m_Magic += (m_Level - 9)*(m_Level - 9 + 1) / 2;
//#else
//			m_Magic += (m_Level - 10) * 2 + 1;
//#endif
//		}
//	}
//
//#ifdef ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912	// 책에 대한 저주력 계산
//	if (m_Curse > 0)
//	{
//		if (m_SetOption && ItemLevel)
//		{
//			m_Curse += m_Curse * 25 / p->Level + 5;
//			m_Curse += ItemLevel / 60 + 2;
//		}
//		else
//			if ((Attribute2 & 63) > 0)
//			{
//				if (iChaosItem)
//				{
//					m_Curse += iChaosItem;
//				}
//				else if (p->Level)
//					m_Curse += m_Curse * 25 / p->Level + 5;
//			}
//
//		m_Curse += m_Level * 3;
//
//		if (m_Level >= 10)
//		{	// +10 이상의 공격력 +
//#ifdef ITEM_12_13_20040401
//			m_Curse += (m_Level - 9)*(m_Level - 9 + 1) / 2;
//#else
//			m_Curse += (m_Level - 10) * 2 + 1;
//#endif
//		}
//	}
//#endif
//
//	if (p->SuccessfulBlocking > 0)
//	{
//		if (m_SetOption && ItemLevel)
//		{
//			m_SuccessfulBlocking += m_SuccessfulBlocking * 25 / p->Level + 5;
//			m_SuccessfulBlocking += ItemLevel / 40 + 5;
//		}
//		else
//			if ((Attribute2 & 63) > 0)
//			{
//				if (p->Level)
//					m_SuccessfulBlocking += m_SuccessfulBlocking * 25 / p->Level + 5;
//			}
//		m_SuccessfulBlocking += m_Level * 3;
//
//		if (m_Level >= 10)
//		{	// +10 이상의 공격력 +
//#ifdef ITEM_12_13_20040401
//			m_SuccessfulBlocking += (m_Level - 9)*(m_Level - 9 + 1) / 2;
//#else
//			m_SuccessfulBlocking += (m_Level - 10) * 2 + 1;
//#endif
//		}
//	}
//
//	if (p->Defense            > 0)
//	{
//		if (m_Type >= ITEM_SHIELD && m_Type<ITEM_SHIELD + MAX_ITEM_INDEX)
//		{
//			m_Defense += m_Level;
//
//			if (m_SetOption && ItemLevel)
//			{
//				m_Defense += (m_Defense * 20 / ItemLevel + 2);
//			}
//		}
//		else
//		{
//			if (m_SetOption && ItemLevel)
//			{
//				m_Defense += m_Defense * 12 / p->Level + 4 + p->Level / 5;
//				m_Defense += m_Defense * 3 / ItemLevel + 2 + ItemLevel / 30;
//			}
//			else
//				if ((Attribute2 & 63) > 0)
//				{
//					if (p->Level)
//						m_Defense += m_Defense * 12 / p->Level + 4 + p->Level / 5;
//				}
//
//#ifdef ADD_THIRD_WING_20070525	// 3차날개의 방어력 적용
//			// _MODIFY_ADD_THIRD_WING_20070623
//			if (_type >= MAKE_ITEMNUM(12, 36) && _type <= MAKE_ITEMNUM(12, 40))
//			{
//				m_Defense += m_Level * 4;
//
//				if (m_Level >= 10)
//				{	// 10레벨부터 추가 방여력 적용 +5 ~ +8
//					m_Defense += m_Level - 9;
//				}
//			}
//			else
//#endif	// ADD_THIRD_WING_20070525
//#ifdef DARKLORD_WORK
//				if ((_type >= ITEM_WING + 3 && _type <= ITEM_WING + 6)
//					|| _type == ITEM_HELPER + 30 || _type == ITEM_HELPER + 4) // 추가 날개&&망토&&다크호스
//#else
//				if (_type >= ITEM_WING + 3 && _type <= ITEM_WING + 6) // 추가 날개
//#endif
//				{
//					m_Defense += m_Level * 2;
//				}
//				else
//				{
//					m_Defense += m_Level * 3;
//				}
//
//			if (m_Level >= 10)
//			{	// +10 이상의 공격력 +
//#ifdef ITEM_12_13_20040401
//				m_Defense += (m_Level - 9)*(m_Level - 9 + 1) / 2;
//#else
//				m_Defense += (m_Level - 10) * 2 + 1;
//#endif
//			}
//		}
//	}
//
//#ifdef DARKLORD_WORK
//	if (_type == MAKE_ITEMNUM(13, 30))
//	{	// 망토 방어력 증가
//		m_Defense = 15 + m_Level * 2;
//#ifdef MODIFY_ACCUMULATED_BUG_SLEEVEOFLORD_01_20050531			
//		if (m_Level >= 10)
//		{
//			m_Defense += (m_Level - 9)*(m_Level - 9 + 1) / 2;
//		}
//#endif
//
//	}
//#endif
//
//#ifdef ADD_SUMMONER_SECOND_THIRD_WING_20071130	// 재앙의 날개, 절망의 날개, 차원의 날개 방어력 계산
//	if (_type == MAKE_ITEMNUM(12, 41))
//	{	// 재앙의 날개
//		m_Defense += m_Level * 3;
//		if (m_Level >= 10)
//		{
//			m_Defense += (m_Level - 9)*(m_Level - 9 + 1) / 2;
//		}
//	}
//	else if (_type == MAKE_ITEMNUM(12, 42))
//	{	// 절망의 날개
//		m_Defense += m_Level * 2;
//		if (m_Level >= 10)
//		{
//			m_Defense += (m_Level - 9)*(m_Level - 9 + 1) / 2;
//		}
//	}
//	else if (_type == MAKE_ITEMNUM(12, 43))
//	{	// 차원의 날개
//		m_Defense += m_Level * 4;
//
//		if (m_Level >= 10)
//		{	// 10레벨부터 추가 방여력 적용 +5 ~ +8
//			m_Defense += m_Level - 9;
//
//#ifndef MODIFY_SUMMONER_THIRD_WING_BUFGIX_20090109
//			m_Defense += (m_Level - 9)*(m_Level - 9 + 1) / 2;
//#endif	// MODIFY_SUMMONER_THIRD_WING_BUFGIX_20090109
//		}
//	}
//#endif	// ADD_SUMMONER_SECOND_THIRD_WING_20071130
//
//	if (p->MagicDefense       > 0)
//	{
//		m_MagicDefense += m_Level * 3;
//		if (m_Level >= 10)
//		{	// +10 이상의 공격력 +
//#ifdef ITEM_12_13_20040401
//			m_MagicDefense += (m_Level - 9)*(m_Level - 9 + 1) / 2;
//#else
//			m_MagicDefense += (m_Level - 10) * 2 + 1;
//#endif
//		}
//	}
//	//-------------------------------------------------------------------------
//
//
//
//	//if(p->RequireStrength    > 0)  m_RequireStrength    += (10+(ItemLevel+m_Level*3)*15/10)*p->RequireStrength /10;
//	//if(p->RequireDexterity   > 0)  m_RequireDexterity   += (10+(ItemLevel+m_Level*3)*15/10)*p->RequireDexterity/10;
//
//	//int EnableSpecial = m_Level>>4;
//	m_Level &= 0xf;
//
//	memset(m_Special, 0, MAX_ITEM_SPECIAL);
//	memset(m_SpecialValue, 0, MAX_ITEM_SPECIAL);
//	m_SpecialNum = 0;
//	m_Option1 = 0;
//	m_Option2 = 0;
//	m_Option3 = 0;
//
//#ifdef DARKLORD_WORK
//	m_SkillChange = FALSE;
//	//옵션1(스킬)
//	if (Option1)
//	{	// ITem.txt에 스킬값이 들어감
//		if (p->SkillType)
//		{
//			if (p->SkillType == AT_SKILL_LONGSPEAR)
//			{
//				m_SkillChange = TRUE;
//				m_Special[m_SpecialNum] = 0;
//				m_Option1 = 1;
//			}
//			else
//			{
//				m_Special[m_SpecialNum] = p->SkillType;
//				m_Option1 = 1;
//			}
//		}
//	}
//#else
//	/*
//	//
//	//
//	//	20051110 DARKLORD_WORK 의 ELSE 부분 삭제 (apple)
//	//
//	//
//	//
//	*/
//	if (Option1)
//	{	// ITem.txt에 스킬값이 들어감
//		if (p->SkillType)
//		{
//			m_Special[m_SpecialNum] = p->SkillType;
//			m_Option1 = 1;
//		}
//	}
//
//#endif // DARKLORD_WORK
//
//
//	if (m_Type == MAKE_ITEMNUM(13, 3))
//	{	// 디노란트는 무조건 옵션이 들어 간다
//		m_Option1 = 1;
//		m_Special[m_SpecialNum] = AT_SKILL_KNIGHTDINORANT;
//	}
//
//
//#ifdef DARKLORD_WORK
//	if (m_Type == MAKE_ITEMNUM(13, 4))
//	{	// 다크호스는 무조건 옵션이 들어 간다
//		m_Option1 = 1;
//		m_Special[m_SpecialNum] = AT_SKILL_DARKHORSE_ATTACK;
//	}
//#endif
//
//#ifdef ADD_ITEM_FENRIR_01_20051110
//	// 펜릴은 무조건 옵션이 들어간다.
//	// item.txt 의 SkillType에 스킬 값 들어가 있지만, Convert 함수가 예외적인 상황에 호출될 때를 대비한다.
//	if (m_Type == MAKE_ITEMNUM(13, 37))
//	{	// 펜릴은 무조건 옵션이 들어 간다
//		m_Option1 = 1;
//		m_Special[m_SpecialNum] = AT_SKILL_FENRIR_ATTACK;
//	}
//#endif
//
//	m_SpecialNum++;
//
//	//옵션2(행운)
//	if (Option2)
//	{
//		if (_type >= ITEM_SWORD && _type<ITEM_BOOT + MAX_ITEM_INDEX)
//		{
//			m_Special[m_SpecialNum] = AT_LUCK;
//			m_Option2 = 1;
//		}
//		if (_type >= ITEM_WING && _type <= ITEM_WING + 6)
//		{
//			m_Special[m_SpecialNum] = AT_LUCK;
//			m_Option2 = 1;
//		}
//#ifdef DARKLORD_WORK
//		if (_type == ITEM_HELPER + 30)
//		{	// 망토는 망토 추가
//			m_Special[m_SpecialNum] = AT_LUCK;
//			m_Option2 = 1;
//		}
//#endif
//#ifdef ADD_THIRD_WING_20070525	// 행운 옵션 처리
//		if (_type >= ITEM_WING + 36 && _type <= ITEM_WING + 40)
//		{
//			m_Special[m_SpecialNum] = AT_LUCK;
//			m_Option2 = 1;
//		}
//#endif		
//#ifdef ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912	// 신규캐릭터 날개 옵션 처리
//		if (_type >= ITEM_WING + 41 && _type <= ITEM_WING + 43)
//		{
//			m_Special[m_SpecialNum] = AT_LUCK;
//			m_Option2 = 1;
//		}
//#endif		
//	}
//	m_SpecialNum++;
//
//	//옵션3(추가포인트)
//	if (Option3)
//	{
//
//		// 세트 아이템 옵션
//		{
//			if (_type >= ITEM_SWORD && _type<ITEM_BOW + MAX_ITEM_INDEX)
//			{
//				m_Special[m_SpecialNum] = AT_IMPROVE_DAMAGE;
//				m_Option3 = Option3;
//				m_RequireStrength += Option3 * 4;
//			}
//			if (_type >= ITEM_STAFF && _type<ITEM_STAFF + MAX_ITEM_INDEX)
//			{
//#ifdef ADD_SUMMONER_SECOND_THIRD_WING_20071130	// 책(왼쪽 지팡이) 일경우 저주력 증가
//				if (p->ItemSlot == EQUIPMENT_WEAPON_LEFT)
//				{
//					m_Special[m_SpecialNum] = AT_IMPROVE_CURSE;
//				}
//				else
//				{
//					m_Special[m_SpecialNum] = AT_IMPROVE_MAGIC;
//				}
//#else
//				m_Special[m_SpecialNum] = AT_IMPROVE_MAGIC;
//#endif
//				m_Option3 = Option3;
//				m_RequireStrength += Option3 * 4;
//			}
//			if (_type >= ITEM_SHIELD && _type<ITEM_SHIELD + MAX_ITEM_INDEX)
//			{
//				m_Special[m_SpecialNum] = AT_IMPROVE_BLOCKING;
//				m_Option3 = Option3;
//				m_RequireStrength += Option3 * 4;
//			}
//			if (_type >= ITEM_HELM && _type<ITEM_BOOT + MAX_ITEM_INDEX)
//			{
//				m_Special[m_SpecialNum] = AT_IMPROVE_DEFENSE;
//				m_Option3 = Option3;
//				m_RequireStrength += Option3 * 4;
//			}
//			if ((_type >= ITEM_HELPER + 8 && _type<ITEM_HELPER + 14) ||
//				(_type >= ITEM_HELPER + 20 && _type <= ITEM_HELPER + 28)) //반지,목걸이
//			{
//				if (_type == ITEM_HELPER + 24)
//				{	// 마법의 반지
//					m_Special[m_SpecialNum] = AT_SET_OPTION_IMPROVE_MAXMANA;
//					m_Option3 = Option3;
//				}
//				else if (_type == ITEM_HELPER + 28)
//				{	// 기술의 목걸이
//					m_Special[m_SpecialNum] = AT_SET_OPTION_IMPROVE_MAXAG;
//					m_Option3 = Option3;
//				}
//				else
//				{
//					m_Special[m_SpecialNum] = AT_LIFE_REGENERATION;
//					m_Option3 = Option3;
//				}
//			}
//
//
//#ifdef DARKLORD_WORK
//			if (_type == ITEM_HELPER + 30)
//			{	// 망토는 공격력 증가.
//				m_Special[m_SpecialNum] = AT_IMPROVE_DAMAGE;
//				m_Option3 = Option3;
//				//m_RequireStrength += Option3*4;
//			}
//#endif
//
//			if (_type == ITEM_WING)
//			{
//				m_Special[m_SpecialNum] = AT_LIFE_REGENERATION;
//				m_Option3 = Option3;
//			}
//			else if (_type == ITEM_WING + 1)
//			{
//				m_Special[m_SpecialNum] = AT_IMPROVE_MAGIC;
//				m_Option3 = Option3;
//				//m_RequireStrength += Option3*4;
//			}
//			else if (_type == ITEM_WING + 2)
//			{
//				m_Special[m_SpecialNum] = AT_IMPROVE_DAMAGE;
//				m_Option3 = Option3;
//				//m_RequireStrength += Option3*4;
//			}
//			else if (_type == ITEM_WING + 3)
//			{	// 정령의 날개(요정)
//				m_Special[m_SpecialNum] = AT_IMPROVE_DAMAGE;
//				m_Option3 = Option3;
//				//m_RequireStrength += Option3*4;
//
//				if ((m_NewOption)&PLUS_WING_OP1_TYPE)
//				{
//					m_Special[m_SpecialNum] = AT_LIFE_REGENERATION;
//				}
//				else
//				{
//					m_Special[m_SpecialNum] = AT_IMPROVE_DAMAGE;
//				}
//			}
//			else if (_type == ITEM_WING + 4)
//			{	// 영혼의 날개(법사)			
//				m_Option3 = Option3;
//				//m_RequireStrength += Option3*4;
//
//				if ((m_NewOption)&PLUS_WING_OP1_TYPE)
//				{
//					m_Special[m_SpecialNum] = AT_IMPROVE_MAGIC;
//				}
//				else
//				{
//					m_Special[m_SpecialNum] = AT_LIFE_REGENERATION;
//				}
//			}
//			else if (_type == ITEM_WING + 5)
//			{	// 드라곤의 날개(기사)			
//				m_Option3 = Option3;
//				//m_RequireStrength += Option3*4;
//
//				if ((m_NewOption)&PLUS_WING_OP1_TYPE)
//				{
//					m_Special[m_SpecialNum] = AT_IMPROVE_DAMAGE;
//				}
//				else
//				{
//					m_Special[m_SpecialNum] = AT_LIFE_REGENERATION;
//				}
//			}
//			else if (_type == ITEM_WING + 6)
//			{	// 어둠의 날개(마검)			
//				m_Option3 = Option3;
//				//m_RequireStrength += Option3*4;
//
//				if ((m_NewOption)&PLUS_WING_OP1_TYPE)
//				{
//					m_Special[m_SpecialNum] = AT_IMPROVE_DAMAGE;
//				}
//				else
//				{
//					m_Special[m_SpecialNum] = AT_IMPROVE_MAGIC;
//				}
//			}
//			else if (_type == ITEM_HELPER + 3)
//			{	// 디노란트
//				m_Option3 = Option3;
//
//				if ((m_Option3)&PLUS_DINORANT_PLUS_MAX_AG)
//				{
//					m_Special[m_SpecialNum] = AT_IMPROVE_AG_MAX;	m_SpecialNum++;
//				}
//
//				if ((m_Option3)&PLUS_DINORANT_PLUS_ATTACKSPEED)
//				{
//					m_Special[m_SpecialNum] = AT_IMPROVE_ATTACK_SPEED;	m_SpecialNum++;
//					m_AttackSpeed += 5;
//				}
//
//				if ((m_Option3)&PLUS_DINORANT_PLUS_REDUCE_DAMAGE)
//				{
//					m_Special[m_SpecialNum] = AT_DAMAGE_ABSORB;
//				}
//			}
//#ifdef DARKLORD_WORK
//			if (_type == ITEM_HELPER + 30)
//			{	// 망토
//				m_Option3 = Option3;
//				//m_RequireStrength += Option3*4;
//
//#ifdef SLEEVEOFLORD_OPTION_BUG_PATCH
//				m_Special[m_SpecialNum] = AT_IMPROVE_DAMAGE;
//#else
//				if ((m_NewOption)&PLUS_WING_OP1_TYPE)
//				{
//					m_Special[m_SpecialNum] = AT_IMPROVE_DAMAGE;
//				}
//				else
//				{
//					m_Special[m_SpecialNum] = AT_LIFE_REGENERATION;
//				}
//#endif
//			}
//#endif
//#ifdef ADD_THIRD_WING_20070525	// 3차날개 추가옵션 적용
//			if (_type == ITEM_WING + 36)	// 폭풍의날개
//			{
//				m_Option3 = Option3;
//				// 기본은 생명 자동 회복
//				m_Special[m_SpecialNum] = AT_LIFE_REGENERATION;
//
//				if ((m_NewOption)&PLUS_THIRD_WING_RAND_OPT_1)
//				{	// 추가 공격력
//					m_Special[m_SpecialNum] = AT_IMPROVE_DAMAGE;
//				}
//				else if ((m_NewOption)&PLUS_THIRD_WING_RAND_OPT_2)
//				{	// 추가 방어력
//					m_Special[m_SpecialNum] = AT_IMPROVE_DEFENSE;
//				}
//			}
//			if (_type == ITEM_WING + 37)	// 시공의날개
//			{
//				m_Option3 = Option3;
//				m_Special[m_SpecialNum] = AT_LIFE_REGENERATION;
//
//				if ((m_NewOption)&PLUS_THIRD_WING_RAND_OPT_1)
//				{	// 추가 마력
//					m_Special[m_SpecialNum] = AT_IMPROVE_MAGIC;
//				}
//				else if ((m_NewOption)&PLUS_THIRD_WING_RAND_OPT_2)
//				{	// 추가 방어력
//					m_Special[m_SpecialNum] = AT_IMPROVE_DEFENSE;
//				}
//			}
//			if (_type == ITEM_WING + 38)	// 환영의날개
//			{
//				m_Option3 = Option3;
//				m_Special[m_SpecialNum] = AT_LIFE_REGENERATION;
//
//				if ((m_NewOption)&PLUS_THIRD_WING_RAND_OPT_1)
//				{	// 추가 공격력
//					m_Special[m_SpecialNum] = AT_IMPROVE_DAMAGE;
//				}
//				else if ((m_NewOption)&PLUS_THIRD_WING_RAND_OPT_2)
//				{	// 추가 방어력
//					m_Special[m_SpecialNum] = AT_IMPROVE_DEFENSE;
//				}
//			}
//			if (_type == ITEM_WING + 39)	// 파멸의날개
//			{
//				m_Option3 = Option3;
//				m_Special[m_SpecialNum] = AT_LIFE_REGENERATION;
//
//				if ((m_NewOption)&PLUS_THIRD_WING_RAND_OPT_1)
//				{	// 추가 공격력
//					m_Special[m_SpecialNum] = AT_IMPROVE_DAMAGE;
//				}
//				else if ((m_NewOption)&PLUS_THIRD_WING_RAND_OPT_2)
//				{	// 추가 마력
//					m_Special[m_SpecialNum] = AT_IMPROVE_MAGIC;
//				}
//			}
//			if (_type == ITEM_WING + 40)	// 제왕의망토
//			{
//				m_Option3 = Option3;
//				m_Special[m_SpecialNum] = AT_LIFE_REGENERATION;
//
//				if ((m_NewOption)&PLUS_THIRD_WING_RAND_OPT_1)
//				{	// 추가 공격력
//					m_Special[m_SpecialNum] = AT_IMPROVE_DAMAGE;
//				}
//				else if ((m_NewOption)&PLUS_THIRD_WING_RAND_OPT_2)
//				{	// 추가 방어력
//					m_Special[m_SpecialNum] = AT_IMPROVE_DEFENSE;
//				}
//			}
//#endif	// ADD_THIRD_WING_20070525	
//#ifdef ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912	// 신규캐릭터 재앙의 날개 3번째 옵션처리
//			else if (_type == ITEM_WING + 41)
//			{	// 재앙의 날개(소환술사)			
//				m_Special[m_SpecialNum] = AT_IMPROVE_MAGIC;
//				m_Option3 = Option3;
//				//m_RequireStrength += Option3*4;
//			}
//#endif		
//#ifdef ADD_SUMMONER_SECOND_THIRD_WING_20071130	//  절망의 날개3번째 옵션
//			else if (_type == ITEM_WING + 42)
//			{	// 절망의 날개(법사)			
//				m_Option3 = Option3;
//				//m_RequireStrength += Option3*4;
//
//				if ((m_NewOption)&PLUS_WING_OP1_TYPE)
//				{
//					m_Special[m_SpecialNum] = AT_IMPROVE_MAGIC;
//				}
//				else
//				{
//					m_Special[m_SpecialNum] = AT_IMPROVE_CURSE;
//				}
//			}
//			else if (_type == ITEM_WING + 43)	// 차원의 날개
//			{
//				m_Option3 = Option3;
//				m_Special[m_SpecialNum] = AT_LIFE_REGENERATION;
//
//				if ((m_NewOption)&PLUS_THIRD_WING_RAND_OPT_1)
//				{	// 추가 공격력
//					m_Special[m_SpecialNum] = AT_IMPROVE_MAGIC;
//				}
//				else if ((m_NewOption)&PLUS_THIRD_WING_RAND_OPT_2)
//				{	// 추가 방어력
//					m_Special[m_SpecialNum] = AT_IMPROVE_CURSE;
//				}
//			}
//#endif	// ADD_SUMMONER_SECOND_THIRD_WING_20071130			
//		}
//	}
//
//	m_SpecialNum++;
//
//	if ((_type >= ITEM_SHIELD && _type<ITEM_BOOT + MAX_ITEM_INDEX) ||//방어구
//		(_type >= ITEM_HELPER + 8 && _type <= ITEM_HELPER + 9)
//		|| (_type >= ITEM_HELPER + 21 && _type <= ITEM_HELPER + 24)
//		)//반지
//	{
//		//생명증가
//		if ((m_NewOption >> 5) & 1)
//		{
//			m_Special[m_SpecialNum] = AT_IMPROVE_LIFE; m_SpecialNum++;
//		}
//		//마나증가
//		if ((m_NewOption >> 4) & 1)
//		{
//			m_Special[m_SpecialNum] = AT_IMPROVE_MANA; m_SpecialNum++;
//		}
//		//데미지감소
//		if ((m_NewOption >> 3) & 1)
//		{
//			m_Special[m_SpecialNum] = AT_DECREASE_DAMAGE; m_SpecialNum++;
//		}
//		//데미지반사
//		if ((m_NewOption >> 2) & 1)
//		{
//			m_Special[m_SpecialNum] = AT_REFLECTION_DAMAGE; m_SpecialNum++;
//		}
//		//방어성공율
//		if ((m_NewOption >> 1) & 1)
//		{
//			m_Special[m_SpecialNum] = AT_IMPROVE_BLOCKING_PERCENT; m_SpecialNum++;
//		}
//		//획득젠증가
//		if ((m_NewOption) & 1)
//		{
//			m_Special[m_SpecialNum] = AT_IMPROVE_GAIN_GOLD; m_SpecialNum++;
//		}
//	}
//	if ((_type >= ITEM_SWORD && _type<ITEM_STAFF + MAX_ITEM_INDEX) ||//무기
//		(_type >= ITEM_HELPER + 12 && _type <= ITEM_HELPER + 13)
//		|| (_type >= ITEM_HELPER + 25 && _type <= ITEM_HELPER + 28)
//		)//목걸이
//	{
//		//마나사용량감소
//		if ((m_NewOption >> 5) & 1)
//		{
//			m_Special[m_SpecialNum] = AT_EXCELLENT_DAMAGE; m_SpecialNum++;
//		}
//		if ((_type >= ITEM_STAFF && _type<ITEM_STAFF + MAX_ITEM_INDEX) ||//지팡이
//			(_type == ITEM_HELPER + 12)
//			//얼음의목걸이,물의목걸이만 마증
//			//바람,기술의 목걸이 공증
//			|| (_type == ITEM_HELPER + 25) || (_type == ITEM_HELPER + 27)
//			)//목걸이
//		{
//			//마력증가(레벨)
//			if ((m_NewOption >> 4) & 1)
//			{
//				//		m_SpecialValue[m_SpecialNum] = CharacterAttribute->Level/20;
//				m_Special[m_SpecialNum] = AT_IMPROVE_MAGIC_LEVEL; m_SpecialNum++;
//			}
//			//마력증가(퍼센트)
//			if ((m_NewOption >> 3) & 1)
//			{
//				m_Special[m_SpecialNum] = AT_IMPROVE_MAGIC_PERCENT; m_SpecialNum++;
//			}
//		}
//		else
//		{
//			//공격력증가(레벨)
//			if ((m_NewOption >> 4) & 1)
//			{
//				//m_SpecialValue[m_SpecialNum] = CharacterAttribute->Level/20;
//				m_Special[m_SpecialNum] = AT_IMPROVE_DAMAGE_LEVEL; m_SpecialNum++;
//			}
//			//공격력증가(퍼센트)
//			if ((m_NewOption >> 3) & 1)
//			{
//				m_Special[m_SpecialNum] = AT_IMPROVE_DAMAGE_PERCENT; m_SpecialNum++;
//			}
//		}
//		//공격속도
//		if ((m_NewOption >> 2) & 1)
//		{
//			m_Special[m_SpecialNum] = AT_IMPROVE_ATTACK_SPEED; m_SpecialNum++;
//			m_AttackSpeed += 7;
//		}
//		//획득생명증가
//		if ((m_NewOption >> 1) & 1)
//		{
//			m_Special[m_SpecialNum] = AT_IMPROVE_GAIN_LIFE; m_SpecialNum++;
//		}
//		//획득마나증가
//		if ((m_NewOption) & 1)
//		{
//			m_Special[m_SpecialNum] = AT_IMPROVE_GAIN_MANA; m_SpecialNum++;
//		}
//	}
//
//#ifdef NEW_FORSKYLAND2	
//#ifdef DARKLORD_WORK
//	if ((_type >= ITEM_WING + 3 && _type <= ITEM_WING + 6) ||
//#ifdef ADD_SUMMONER_SECOND_THIRD_WING_20071130
//		_type == ITEM_WING + 42 ||	// 절망의 날개 옵션
//#endif
//		_type == ITEM_HELPER + 30) // 날개 & 망토	    
//#else
//	if (_type >= ITEM_WING + 3 && _type <= ITEM_WING + 6) // 날개	    
//#endif
//	{
//		if ((m_NewOption)&PLUS_WING_MAXLIFE)
//		{	// 최대 HP+50
//			m_Special[m_SpecialNum] = AT_PLUS_WING_MAXLIFE; m_SpecialNum++;
//		}
//
//		if ((m_NewOption)&PLUS_WING_MAXMANA)
//		{	// 최대 MP+50
//			m_Special[m_SpecialNum] = AT_PLUS_WING_MAXMANA; m_SpecialNum++;
//		}
//
//		if ((m_NewOption)&PLUS_WING_ONE_PERCENT_DAMAGE)
//		{	// 데미지 HP->MP로 손실
//			m_Special[m_SpecialNum] = AT_PLUS_ONE_PERCENT_DAMAGE; m_SpecialNum++;
//		}
//
//#ifdef DARKLORD_WORK
//		if ((m_NewOption)&PLUS_WING_ADD_LEADERSHIP)
//		{	// 통솔증가
//			m_Special[m_SpecialNum] = AT_PLUS_WING_ADD_LEADERSHIP; m_SpecialNum++;
//		}
//#endif			
//	}
//#endif
//
//
//	// 펜릴 경우 특수 옵션 추가!
//#ifdef ADD_ITEM_FENRIR_01_20051110
//
//	// 펜릴 옵션에 따른 스킬 추가
//	if (_type == ITEM_HELPER + 37)
//	{
//		if ((m_NewOption)&PLUS_FENRIR_INCREASE_LAST_DAMAGE)
//		{
//			m_Special[m_SpecialNum] = AT_PLUS_FENRIR_INCREASE_LAST_DAMAGE;
//			m_SpecialNum++;
//		}
//		else if ((m_NewOption)&PLUS_FENRIR_DECREASE_LAST_DAMAGE)
//		{
//			m_Special[m_SpecialNum] = AT_PLUS_FENRIR_DECREASE_LAST_DAMAGE;
//			m_SpecialNum++;
//		}
//#ifdef ADD_ILLUSION_FENRIR_20070703	// 환영 펜릴 옵션에 따른 스킬 추가
//		else if ((m_NewOption)&PLUS_ILLUSION_FENRIR_OPTION)
//		{
//			m_Special[m_SpecialNum] = AT_PLUS_ILLUSION_FENRIR_OPTION;
//			m_SpecialNum++;
//		}
//#endif
//	}
//
//#endif
//
//#ifdef ADD_THIRD_WING_20070525	// 3차 날개 랜덤 옵션 적용
//#ifdef ADD_SUMMONER_SECOND_THIRD_WING_20071130	// 차원의 날개 랜덤 옵션적용
//	if (_type >= ITEM_WING + 36 && _type <= ITEM_WING + 40
//		|| _type == ITEM_WING + 43)	// 차원의 날개
//#else
//	if (_type >= ITEM_WING + 36 && _type <= ITEM_WING + 40)
//#endif
//	{
//		if ((m_NewOption)&PLUS_THIRD_WING_5PER_IGNORE_DEFENSE)
//		{	// %5 확률로 적 방어력 무시
//			m_Special[m_SpecialNum] = AT_5PER_IGNORE_DEFENSE;
//			m_SpecialNum++;
//		}
//		if ((m_NewOption)&PLUS_THIRD_WING_5PER_ATTACK_TURNING)
//		{	// 5% 확률로 적 공격력 50% 돌려줌
//			m_Special[m_SpecialNum] = AT_5PER_ATTACK_TURNING;
//			m_SpecialNum++;
//		}
//		if ((m_NewOption)&PLUS_THIRD_WING_RECOVER_100PER_LIFE)
//		{	// 5% 확률로 유저 생명 100% 순간 회복
//			m_Special[m_SpecialNum] = AT_RECOVER_100PER_LIFE;
//			m_SpecialNum++;
//		}
//		if ((m_NewOption)&PLUS_THIRD_WING_RECOVER_100PER_MASIC)
//		{	// 5% 확률로 유저 마력 100% 순간 회복
//			m_Special[m_SpecialNum] = AT_RECOVER_100PER_MASIC;
//			m_SpecialNum++;
//		}
//	}
//#endif
//
//#if GAME_VERSION >= G_V_99B
//	if (SOptionStatValue)
//	{	// 세트 속성 값을 넣는다
//		if (p->SetAttr)
//		{	// 세트 속성값이 있으면 세트 속성 값은 1부터 시작 되므로 -1이 필요			
//			m_Special[m_SpecialNum] = AT_SET_IMPROVE_STRENGTH + p->SetAttr - 1;
//			m_SetAddStat = SOptionStatValue * 5;
//			m_SpecialNum++;
//		}
//	}
//#endif
//
//	//#ifdef DARKLORD_WORK	//Item.txt에 위치 값 저장됨
//	m_Part = p->ItemSlot;
//	//#else
//	/*
//	//
//	//
//	//	20051110 DARKLORD_WORK 의 ELSE 부분 삭제 (apple)
//	//
//	//
//	//
//	*/
//	//#endif // DARKLORD_WORK
//
//	Value();
//
//	if (m_Type != ITEM_BOW + 7 && m_Type != ITEM_BOW + 15)
//	{	// 화살, 석궁용화살이 아니면
//		m_DamageMinOrigin = m_DamageMin;
//		m_DefenseOrigin = m_Defense;
//		m_DamageMin -= (WORD)(m_DamageMin*m_CurrentDurabilityState);
//		m_DamageMax -= (WORD)(m_DamageMax*m_CurrentDurabilityState);
//		m_Defense -= (WORD)(m_Defense*m_CurrentDurabilityState);
//		m_SuccessfulBlocking -= (BYTE)(m_SuccessfulBlocking*m_CurrentDurabilityState);
//
//		if (m_Durability < 1.f)
//			m_AttackSpeed = 0;
//	}
//
//	if (m_Durability == 0.f)
//	{	// 내구도가 0이면 저항력도 없다
//		memset(m_Resistance, 0, MAX_RESISTANCE);
//	}
//}

int CItem::GetLevel(void)
{
	return ItemAttribute[m_Type].Level;
}

DWORD CItem::GetNumber()
{
	return m_Number;
}

//#include "..\\gameserver\\Global.h"

void CItem::Value()
{
#ifdef WORLD_TOURNAMENT_EVENT_SETTING
	m_SellMoney = 0;		// WT 이벤트 서버 아이템 가격은 0
	m_BuyMoney = 0;
	return;
#endif

	if (m_Type == -1) return;

	ITEM_ATTRIBUTE *p = &ItemAttribute[m_Type];

	if (p->BuyMoney)
	{
		m_SellMoney = p->BuyMoney;
		m_BuyMoney = p->BuyMoney;

		m_SellMoney = m_SellMoney / 3;

		if (m_SellMoney >= 1000)
			m_SellMoney = m_SellMoney / 100 * 100;
		else if (m_SellMoney >= 100)
			m_SellMoney = m_SellMoney / 10 * 10;

		if (m_BuyMoney >= 1000)
			m_BuyMoney = m_BuyMoney / 100 * 100;
		else if (m_BuyMoney >= 100)
			m_BuyMoney = m_BuyMoney / 10 * 10;

		return;
	}

	int Level = (int)sqrt((double)m_Level);


#ifdef MODIFY_ITEM_PRICE_MAXFIX
	__int64 Gold = 0;
#else
	DWORD Gold = 0;
#endif

	int Type = m_Type / MAX_ITEM_INDEX;

	int Level2 = p->Level + m_Level * 3;
	int excellent = FALSE;

	for (int i = 0; i<m_SpecialNum; i++)
	{
		switch (m_Special[i])
		{
		case AT_IMPROVE_LIFE:
		case AT_IMPROVE_MANA:
		case AT_DECREASE_DAMAGE:
		case AT_REFLECTION_DAMAGE:
		case AT_IMPROVE_BLOCKING_PERCENT:
		case AT_IMPROVE_GAIN_GOLD:
		case AT_EXCELLENT_DAMAGE:
		case AT_IMPROVE_DAMAGE_LEVEL:
		case AT_IMPROVE_DAMAGE_PERCENT:
		case AT_IMPROVE_MAGIC_LEVEL:
		case AT_IMPROVE_MAGIC_PERCENT:
		case AT_IMPROVE_ATTACK_SPEED:
		case AT_IMPROVE_GAIN_LIFE:
		case AT_IMPROVE_GAIN_MANA:
			excellent = TRUE;
			break;
		}
	}
	if (excellent)
	{
		Level2 += 25;
	}
	if (m_Type == ITEM_BOW + 15)
	{	// 화살
		int levelgold = 70;
		if (m_Level == 1)
		{
			levelgold = 1200;
		}
		else if (m_Level == 2)
		{
			levelgold = 2000;
		}
#ifdef UPDATE_ADD_ARROW_TYPE_PLUS_3_20081106
		else if (m_Level == 3)
		{
			levelgold = 2800;
		}
#endif // UPDATE_ADD_ARROW_TYPE_PLUS_3_20081106

		if (m_Durability > 0)
		{
#ifdef MODIFY_ITEM_PRICE_MAXFIX
			Gold = (__int64)(levelgold * m_Durability / p->Durability);
#else
			Gold = (DWORD)(levelgold * m_Durability / p->Durability);
#endif
		}
		//  	Gold = (int)(70 * m_Durability / p->Durability)+(80*(m_Level*2));
	}
	else if (m_Type == ITEM_BOW + 7)
	{
		if (m_Durability > 0)
		{
			int levelgold = 100;
			if (m_Level == 1)
			{
				levelgold = 1400;
			}
			else if (m_Level == 2)
			{
				levelgold = 2200;
			}
#ifdef UPDATE_ADD_ARROW_TYPE_PLUS_3_20081106
			else if (m_Level == 3)
			{
				levelgold = 3000;
			}
#endif // UPDATE_ADD_ARROW_TYPE_PLUS_3_20081106

#ifdef MODIFY_ITEM_PRICE_MAXFIX
			Gold = (__int64)(levelgold * m_Durability / p->Durability);
#else
			Gold = (DWORD)(levelgold * m_Durability / p->Durability);
#endif
		}
		//Gold = (int)(100 * m_Durability / p->Durability)+(170*(m_Level*2));
	}
#ifdef FOR_TEMP_SERVER
	//------------------------------------------>
	//grooving SEASON4 20080728 : 보석 판매 가격 1000 으로 통일(시즌4 체험 서버 임시)
	else if (m_Type == ITEM_POTION + 13)	// 축석
	{
		//Gold = 9000000;
		Gold = 1000;
	}
	else if (m_Type == ITEM_POTION + 14)	// 영석
	{
		//Gold = 6000000;
		Gold = 1000;
	}
	else if (m_Type == ITEM_WING + 15)	// 혼석
	{
		//Gold = 810000;
		Gold = 1000;
	}
	else if (m_Type == ITEM_POTION + 16)	// 생석
	{
		//Gold = 45000000;
		Gold = 1000;
	}
	else if (m_Type == ITEM_POTION + 22)	// 창석
	{
		//Gold = 36000000;
		Gold = 1000;
	}
#else
	else if (m_Type == ITEM_POTION + 13)	// 축석
	{
		Gold = 9000000;
	}
	else if (m_Type == ITEM_POTION + 14)	// 영석
	{
		Gold = 6000000;
	}
	else if (m_Type == ITEM_WING + 15)	// 혼석
	{
		Gold = 810000;
	}
	else if (m_Type == ITEM_POTION + 16)	// 생석
	{
		Gold = 45000000;
	}
	else if (m_Type == ITEM_POTION + 22)	// 창석
	{
		Gold = 36000000;
	}
#endif //FOR_TEMP_SERVER 
	//<------------------------------------------
#ifdef JEWEL_MIX_SYSTEM_20050309	// 보석 조합아이템 판매가격
	else if (m_Type == ITEM_WING + 30)	// 축석 조합
	{
		Gold = 9000000 * (m_Level + 1) * 10;
	}
	else if (m_Type == ITEM_WING + 31)	// 영석 조합
	{
		Gold = 6000000 * (m_Level + 1) * 10;
	}
#endif
	else if (m_Type == ITEM_HELPER + 15)	// 열매
	{
		Gold = 33000000;
	}
	else if (m_Type == ITEM_HELPER + 14)	// 깃털
	{
#ifdef DARKLORD_WORK
		if (m_Level == 1)
			Gold = 2500000 * 3;		// 군주의 소매

#ifdef MODIFY_PRICE_FEATHE_OF_LOCH_20041129		
		else  Gold = 180000;
#endif

#else
		Gold = 180000;
#endif
	}
#ifdef ADD_NEW_ITEM_FOR_CASTLE_01_20041116
	else if (m_Type == ITEM_POTION + 31)	// 수호 보석
	{
		Gold = 60000000;
	}
	else if (m_Type == ITEM_POTION + 7)  // 공성 물약
	{
		if (m_Level == 0)	// 축복의 물약
		{
#ifdef MODIFY_CASTLE_POTION_20051017
			Gold = 900000 * (int)m_Durability;
#else
			Gold = 2100000 * (int)m_Durability;
#endif
		}
		else if (m_Level == 1)	// 영혼의 물약
		{
#ifdef MODIFY_CASTLE_POTION_20051017
			Gold = 450000 * (int)m_Durability;
#else
			Gold = 1500000 * (int)m_Durability;
#endif
		}
	}
	else if (m_Type == ITEM_HELPER + 11) // 라이프스톤
	{
		if (m_Level == 1)	// 라이프스톤
			Gold = 2400000;
	}
	else if (m_Type == ITEM_HELPER + 7)  // 용병
	{
		if (m_Level == 0) // 활용병
			Gold = 1500000;
		else if (m_Level == 1)// 창용병
			Gold = 1200000;
	}
#endif
#ifdef ADD_ITEM_FENRIR_01_20051110
	// 펜릴 관련 아이템 가격
	else if (m_Type == ITEM_HELPER + 32)
	{
		Gold = 50 * 3 * (int)m_Durability;
	}
	else if (m_Type == ITEM_HELPER + 33)
	{
		Gold = 100 * 3 * (int)m_Durability;
	}
	else if (m_Type == ITEM_HELPER + 34)
	{
		Gold = 1000 * 3 * (int)m_Durability;
	}
	else if (m_Type == ITEM_HELPER + 35)
	{
		Gold = 10000 * 3;
	}
	else if (m_Type == ITEM_HELPER + 36)
	{
		Gold = 30000 * 3;
	}
	else if (m_Type == ITEM_HELPER + 37)
	{
		Gold = 50000 * 3;
	}
#endif

	// CODEREVIEW_SHIELD : 여기다가 상점 판매 가격 '비슷한' 형식으로 넣을것.
#ifdef ADD_SHIELD_POINT_01_20060403
	else if (m_Type == MAKE_ITEMNUM(14, 35))
	{
		Gold = (2000 * (int)m_Durability);
	}
	else if (m_Type == MAKE_ITEMNUM(14, 36))
	{
		Gold = (4000 * (int)m_Durability);
	}
	else if (m_Type == MAKE_ITEMNUM(14, 37))
	{
		Gold = (6000 * (int)m_Durability);
	}
	else if (m_Type == MAKE_ITEMNUM(14, 38))
	{
		Gold = (2500 * (int)m_Durability);
	}
	else if (m_Type == MAKE_ITEMNUM(14, 39))
	{
		Gold = (5000 * (int)m_Durability);
	}
	else if (m_Type == MAKE_ITEMNUM(14, 40))
	{
		Gold = (7500 * (int)m_Durability);
	}
#endif
	//
	else if (m_Type == ITEM_HELPER + 3)	// 디노란트
	{
		Gold = 960000;
		for (int i = 0; i < 3; i++)
		{
			if (m_Option3 & (1 << i))
			{	// 옵션 하나당 100000추가
				Gold += 300000;
			}
		}
	}
	else if (m_Type == ITEM_POTION + 17)	// 악마의 눈
	{
		switch (m_Level)
		{
#ifdef UPDATE_EVENT_MAP_MIXiTEM_VALUE_200800808	// 악마의 눈 가격
		case 1: Gold = 10000;	break;
		case 2: Gold = 50000;	break;
		case 3: Gold = 100000;	break;
		case 4: Gold = 300000;	break;
		case 5: Gold = 500000;	break;
		case 6: Gold = 800000;	break;
		case 7: Gold = 1000000;	break;
#else	// UPDATE_EVENT_MAP_MIXiTEM_VALUE_200800808			
		case 1:
			Gold = 15000;
			break;

		case 2:
			Gold = 21000;
			break;

		case 3:
			Gold = 30000;
			break;

		case 4:
			Gold = 45000;
			break;

#ifdef DEVILSQUARE_EXTEND_20050221		// 악마의 눈 판매가격
		case 5:
			Gold = 60000;
			break;

		case 6:
			Gold = 75000;
			break;
#endif
#ifdef ADD_DEVILSQURE_FOR_MASTER_LEVEL_20071010		// 악마의 눈 7 판매가격
		case 7:
			Gold = 30000 * 3;
			break;
#endif	
#endif	// UPDATE_EVENT_MAP_MIXiTEM_VALUE_200800808	
		default:
			Gold = 30000;
			break;

		}
	}
	else if (m_Type == ITEM_POTION + 18)	// 악마의 열쇠
	{
		switch (m_Level)
		{
#ifdef UPDATE_EVENT_MAP_MIXiTEM_VALUE_200800808	// 악마의 열쇠 가격
		case 1: Gold = 15000;	break;
		case 2: Gold = 75000;	break;
		case 3: Gold = 150000;	break;
		case 4: Gold = 450000;	break;
		case 5: Gold = 750000;	break;
		case 6: Gold = 1200000;	break;
		case 7: Gold = 1500000;	break;
#else	// UPDATE_EVENT_MAP_MIXiTEM_VALUE_200800808
		case 1:
			Gold = 15000;
			break;

		case 2:
			Gold = 21000;
			break;

		case 3:
			Gold = 30000;
			break;

		case 4:
			Gold = 45000;
			break;

#ifdef DEVILSQUARE_EXTEND_20050221		// 악마의 열쇠 판매가격
		case 5:
			Gold = 60000;
			break;

		case 6:
			Gold = 75000;
			break;
#endif
#ifdef ADD_DEVILSQURE_FOR_MASTER_LEVEL_20071010		// 악마의열쇠7 판매가격
		case 7:
			Gold = 30000 * 3;
			break;
#endif			
#endif	// UPDATE_EVENT_MAP_MIXiTEM_VALUE_200800808
		default:
			Gold = 30000;
			break;
		}
	}
	else if (m_Type == ITEM_POTION + 19)	// 악마의 광장 초대권
	{
		switch (m_Level)
		{
		case 1:
			Gold = 60000;
			break;

		case 2:
			Gold = 84000;
			break;

		case 3:
			Gold = 120000;
			break;

		case 4:
			Gold = 180000;
			break;

#ifdef DEVILSQUARE_EXTEND_20050221		// 악마의 광장 초대권 판매가격
		case 5:
			Gold = 240000;
			break;

		case 6:
			Gold = 300000;
			break;
#endif
#ifdef ADD_DEVILSQURE_FOR_MASTER_LEVEL_20071010		// 광장7 초대권 판매가격
		case 7:
			Gold = 60000 * 3;
			break;
#endif

		default:
			Gold = 120000;
			break;
		}
	}
	else if (m_Type == ITEM_POTION + 20)	// 사랑의 묘약
	{
		Gold = 900;
	}
	else if (m_Type == ITEM_POTION + 21)	// 레나
	{
#ifdef FOR_BLOODCASTLE3
		switch (m_Level)
		{
		case 0:						// 레나
			Gold = 3000 * 3;
			m_Durability = m_BaseDurability;
		case 1:						// 스톤
			Gold = 3000 * 3;
			m_Durability = m_BaseDurability;
			break;
#ifdef EVENT_STONE_OF_FRIENDSHIP_20040206	// 우정의돌 상점판매 - 3000젠
		case 2:						// 우정의돌
			Gold = 3000 * 3;
			m_Durability = m_BaseDurability;
			break;
#endif
#ifdef MU_CASTLESIEGE_CS_MARKS_20041214
		case 3:						// 성주의 표식
#ifdef MODIFY_ACCUMULATED_BUG_MARKOFLORD_SELL_VALUE_01_20050531
			Gold = 1300 * 3 * (int)m_Durability;
#else
			Gold = 3000 * 3;
#endif
			break;
#endif
		default:
			Gold = 3000 * 3;
			m_Durability = m_BaseDurability;
			break;
		}
#else
		Gold = 3000 * 3;
		m_Durability = m_BaseDurability;
#endif
	}
#ifdef UPDATE_LUCKY_COIN_EVENT_20081029
	else if (m_Type == ITEM_POTION + 100)	// 행운의 동전
	{
		Gold = 100 * 3 * (int)m_Durability;
	}
#endif	// UPDATE_LUCKY_COIN_EVENT_20081029	
	else  if (m_Type == ITEM_POTION + 9 && m_Level == 1)	// 술 
	{	// 사랑의 열매(올리브)
		Gold = 1000;
	}
#ifdef FOR_BLOODCASTLE
	else if (m_Type == ITEM_HELPER + 18)	// 투명망토
	{
		switch (m_Level)
		{
		case 1:
			Gold = 50000 * 3;
			break;

		case 2:
			Gold = 220000 * 3;
			break;

		case 3:
			Gold = 240000 * 3;
			break;

		case 4:
			Gold = 260000 * 3;
			break;

		case 5:
			Gold = 280000 * 3;
			break;

		case 6:
			Gold = 300000 * 3;
			break;

		case 7:
			Gold = 320000 * 3;
			break;
#ifdef ADD_BLOODCASTLE_FOR_MASTER_LEVEL_20071010	// 투명망토 +8 가격
		case 8:
			Gold = 340000 * 3;
			break;
#endif			

		default:
			Gold = 200000 * 3;
			break;
		}
	}
	else if ((m_Type == ITEM_HELPER + 16) || (m_Type == ITEM_HELPER + 17))	// 블러드본 이나 대천사의서
	{

		switch (m_Level)
		{
#ifdef UPDATE_EVENT_MAP_MIXiTEM_VALUE_200800808	// 블러드본, 대천사의서 가격
		case 1: Gold = 10000;	break;
		case 2: Gold = 50000;	break;
		case 3: Gold = 100000;	break;
		case 4: Gold = 300000;	break;
		case 5: Gold = 500000;	break;
		case 6: Gold = 800000;	break;
		case 7: Gold = 1000000;	break;
		case 8: Gold = 1200000;	break;
#else	// UPDATE_EVENT_MAP_MIXiTEM_VALUE_200800808
		case 1:
			Gold = 5000 * 3;
			break;

		case 2:
			Gold = 7000 * 3;
			break;

		case 3:
			Gold = 10000 * 3;
			break;

		case 4:
			Gold = 13000 * 3;
			break;

		case 5:
			Gold = 16000 * 3;
			break;

		case 6:
			Gold = 20000 * 3;
			break;

		case 7:
			Gold = 25000 * 3;
			break;
#ifdef ADD_BLOODCASTLE_FOR_MASTER_LEVEL_20071010	// 블러드본+8, 대천사의서+8 가격
		case 8:
			Gold = 30000 * 3;
			break;
#endif
#endif	// UPDATE_EVENT_MAP_MIXiTEM_VALUE_200800808				
		default:
			Gold = 5000 * 3;
			break;
		}
	}
#endif
#ifdef CHAOSCASTLE_SYSTEM_20040408		// 근위병 갑옷세트 판매가격
	else if (m_Type == ITEM_HELPER + 29)
	{
		Gold = 5000;
	}
#endif	
#ifdef RING_EVENT_ITEMBOX_20031124		// 반지이벤트 - 마법사의 반지 판매가격
	else if (m_Type == ITEM_HELPER + 20)
	{
		switch (m_Level)
		{
		case 0:						// 마법사의 반지
			Gold = 10000 * 3;
			break;
#ifdef MU_CHN_THANKS_RING_EVENT_20040908	// 중국 이벤트 - 영예의 반지 
		case 3:						// 영예의 반지
			Gold = 10000 * 3;
			break;
#endif
		default:
			Gold = 0 * 3;
			break;
		}
	}
#endif
#ifdef DARKLORD_WORK
	else if (m_Type == ITEM_HELPER + 31)
	{
		switch (m_Level)
		{
		case 0:						// 다크호스의 영혼
			Gold = 10000000 * 3;
			break;

		case 1:						// 다크스피릿의 영혼
			Gold = 5000000 * 3;
			break;
		}
	}
#endif
#ifdef ADD_NEW_MAP_KALIMA_20040518
	else if (m_Type == ITEM_POTION + 28)		// 잃어버린 지도
	{
		Gold = 200000 * 3;
		//#ifdef FOR_NEW_TESTSERVER
		//		Gold = 20000;
		//#else
		//		Gold = 20000 * 3;
		//#endif
	}
	else if (m_Type == ITEM_POTION + 29)		// 쿤둔의표식
	{
		Gold = 10000 * m_Durability * 3;
		//#ifdef FOR_NEW_TESTSERVER
		//		Gold = 1000 * m_Durability;
		//#else
		//		Gold = 1000 * m_Durability * 3;
		//#endif
	}
#endif
#ifdef HALLOWINDAY_JACK_O_LANTERN_EVENT_20061017
	else if (m_Type == MAKE_ITEMNUM(14, 45)
		|| m_Type == MAKE_ITEMNUM(14, 46)
		|| m_Type == MAKE_ITEMNUM(14, 47)
		|| m_Type == MAKE_ITEMNUM(14, 48)
		|| m_Type == MAKE_ITEMNUM(14, 49)
		|| m_Type == MAKE_ITEMNUM(14, 50)
		)
	{
		Gold = 50 * m_Durability * 3;
	}

#endif // HALLOWINDAY_JACK_O_LANTERN_EVENT_20061017
#ifdef HIDDEN_TREASUREBOX_EVENT_20050804
	else if (m_Type == ITEM_WING + 26)
	{
		switch (m_Level) {
		case 0:							// 신비의 구슬
			Gold = 60000;
			break;
		}
	}
#endif	
#ifdef CHRISTMAS_STAR_20061211
	else if (m_Type == MAKE_ITEMNUM(14, 51))	// 크리스마스의 별
	{
		Gold = 200000;
	}
#endif	
#ifdef PCBANG_POINT_SYSTEM_20070206		// 아이템 팔 때 가격 설정
	else if (m_Type == MAKE_ITEMNUM(14, 55) 		// 혼돈의 상자
		|| m_Type == MAKE_ITEMNUM(14, 56)
		|| m_Type == MAKE_ITEMNUM(14, 57))
	{
		//#ifdef MODIFY_PCBANGPOINTSHOP_CLOSEWINDOWS_BUGFIX_20080218	// 혼돈의상자 가격 재설정
		//		Gold = 30000000 * 3;
		//#else
		Gold = 3000 * 3;
		//#endif	// MODIFY_PCBANGPOINTSHOP_CLOSEWINDOWS_BUGFIX_20080218
	}
#endif
#ifdef ADD_EVENT_MAP_ILLUSION_TEMPLE_20070328		// 아이템 팔때 가격
	else if ((m_Type == MAKE_ITEMNUM(13, 49))		// 낡은 두루마리
		|| (m_Type == MAKE_ITEMNUM(13, 50)) 		// 환영교단의 서약
		|| (m_Type == MAKE_ITEMNUM(13, 51)))		// 피의 두루마리
	{
		switch (m_Level)
		{
#ifdef UPDATE_EVENT_MAP_MIXiTEM_VALUE_200800808	// 피의두루마리, 환경교단의 서약 가격
		case 1: Gold = 500000;	break;
		case 2: Gold = 600000;	break;
		case 3: Gold = 800000;	break;
		case 4: Gold = 1000000;	break;
		case 5: Gold = 1200000;	break;
		case 6: Gold = 1400000;	break;
#else	// UPDATE_EVENT_MAP_MIXiTEM_VALUE_200800808
		case 1:
			Gold = 3000 * 3;
#endif	// UPDATE_EVENT_MAP_MIXiTEM_VALUE_200800808
		default:
			Gold = 3000 * 3;
		}
	}
#endif
#ifdef ADD_THIRD_WING_20070525	// 콘도르의 깃털, 불꽃 가격 설정
	else if (m_Type == MAKE_ITEMNUM(13, 52)	// 콘도르의 깃털
		|| m_Type == MAKE_ITEMNUM(13, 53)) 	// 콘도르의 불꽃	
	{
		Gold = 1000000 * 3;
	}
#endif	
#ifdef MODIFY_QUEST_MONSTER_KILL_COUNT_BUGFIX_20070704	// 퀘스트 아이템 가격설정
	else if (m_Type == MAKE_ITEMNUM(14, 23)	// 제왕의서
		|| m_Type == MAKE_ITEMNUM(14, 24)		// 부러진검
		|| m_Type == MAKE_ITEMNUM(14, 25)		// 엘프의눈물
		|| m_Type == MAKE_ITEMNUM(14, 26)		// 마법사의혼
		|| m_Type == MAKE_ITEMNUM(14, 65)		// 데쓰빔나이트의불꽃
		|| m_Type == MAKE_ITEMNUM(14, 66)		// 헬마이네의뿔
		|| m_Type == MAKE_ITEMNUM(14, 67)		// 어둠의불사조의깃털
#ifdef ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912// 소환술사 퀘스트 아이템 가격
		|| m_Type == MAKE_ITEMNUM(14, 68)		// 심연의눈동자
#endif
		)
	{
		Gold = 3000 * 3;
	}
#endif	

	else if (p->Value > 0)
	{
		Gold += p->Value*p->Value * 10 / 12;
		if (m_Type >= ITEM_POTION && m_Type <= ITEM_POTION + 8)
		{
#ifdef ITEM_12_13_20040401
#ifdef FOR_CHINA
			if (m_Level >0)
			{
#ifdef MODIFY_ITEM_PRICE_MAXFIX
				Gold *= (__int64)pow(3, Level);
#else
				Gold *= (DWORD)pow(3, Level);
#endif	// MODIFY_ITEM_PRICE_MAXFIX				
			}
#else
#ifdef UPDATE_ZEN_DROP_DOWN_20080806	// 큰 치료물약, 큰 마나물약 가격 2배
			if (m_Type == ITEM_POTION + 3 || m_Type == ITEM_POTION + 6)
			{
				Gold *= 2;
			}
#endif	// UPDATE_ZEN_DROP_DOWN_20080806
			if (m_Level >0)
#ifdef MODIFY_ITEM_PRICE_MAXFIX
				Gold *= (__int64)pow((double)2, (double)Level);
#else
				Gold *= (DWORD)pow((double)2, (double)Level);
#endif	// MODIFY_ITEM_PRICE_MAXFIX
#endif	// FOR_CHINA
#endif

#ifdef HP_POTION_VALUE_CHANGE_20040618		
			Gold = Gold / 10 * 10;
#endif

#ifdef MODIFY_ITEM_PRICE_MAXFIX
			Gold *= (__int64)m_Durability;
#else
			Gold *= (DWORD)m_Durability;
#endif

#ifdef HP_POTION_VALUE_CHANGE_20040618
			m_BuyMoney = Gold;
			m_SellMoney = Gold / 3;
			m_SellMoney = m_SellMoney / 10 * 10;
			return;
#endif
		}
	}
#ifdef ADD_THIRD_WING_20070525	// 3차날개 계산 - type 12에서 3차날개 제외
#ifdef ADD_SUMMONER_SECOND_THIRD_WING_20071130	// 신규캐릭터 날개 type 12에서 제외
	else if ((Type == 12 && ((m_Type > ITEM_WING + 6) && (m_Type < ITEM_WING + 36) && (m_Type > ITEM_WING + 43)))
#else
	else if ((Type == 12 && ((m_Type > ITEM_WING + 6) && (m_Type < ITEM_WING + 36) && (m_Type > ITEM_WING + 40)))
#endif
		|| Type == 13 || Type == 15)	//12(날개,구슬) 13(사탄,반지) 15(법서)
#else	
	else if ((Type == 12 && m_Type>ITEM_WING + 6) || Type == 13 || Type == 15)//12(날개,구슬) 13(사탄,반지) 15(법서)
#endif
	{
		//int Level2 = p->Level+m_Level*3;
		Gold = 100 + Level2 * Level2*Level2;
		for (int i = 0; i<m_SpecialNum; i++)
		{
			switch (m_Special[i])
			{
			case AT_LIFE_REGENERATION:
				Gold += Gold * m_Option3;
				break;
			}
		}
	}
#ifdef ADD_FIRECRACKER_NPC_20070306	// 폭죽가격 설정
	else if (m_Type == MAKE_ITEMNUM(14, 63))	// 폭죽
	{
		Gold = 200000;
	}
#endif
#ifdef MODIFY_CHERRYBLOSSOM_SELL_MONEY_BUGFIX_20090325
	// 벚꽃 관련 아이템 가격
	else if (m_Type == MAKE_ITEMNUM(14, 85)		// 벚꽃술
		|| m_Type == MAKE_ITEMNUM(14, 86)		// 벚꽃놀이 경단
		|| m_Type == MAKE_ITEMNUM(14, 87)		// 벚꽃 꽃잎
		|| m_Type == MAKE_ITEMNUM(14, 90)		// 황금 벚꽃 가지
		)
	{
		Gold = 100 * 3 * (int)m_Durability;
	}
#endif // MODIFY_CHERRYBLOSSOM_SELL_MONEY_BUGFIX_20090325
	else
	{
		//Level2 = p->Level+m_Level*3;
		switch (m_Level)     //+무기일수록 가중치 붙음
		{
		case 5:Level2 += 4; break;
		case 6:Level2 += 10; break;
		case 7:Level2 += 25; break;
		case 8:Level2 += 45; break;
		case 9:Level2 += 65; break;
		case 10:Level2 += 95; break;
		case 11:Level2 += 135; break;
#ifdef ITEM_12_13_20040401
		case 12:Level2 += 185; break;
		case 13:Level2 += 245; break;
#endif
		}
		if (Type == 12 && m_Type <= ITEM_WING + 6)
		{
			Gold = 40000000 + ((40 + Level2)*Level2*Level2 * 11);
		}
#ifdef ADD_THIRD_WING_20070525	// 3차날개 기본가격 설정
		else if (Type == 12 && (m_Type >= ITEM_WING + 36 && m_Type <= ITEM_WING + 40))
		{
			Gold = 40000000 + ((40 + Level2) * Level2 * Level2 * 11);
		}
#endif
#ifdef ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912	// 신규캐릭터 날개 가격
		else if (Type == 12 && (m_Type >= ITEM_WING + 41 && m_Type <= ITEM_WING + 43))
		{
			Gold = 40000000 + ((40 + Level2)*Level2*Level2 * 11);
		}
#endif
		else
		{
			Gold = 100 + (40 + Level2)*Level2*Level2 / 8;
		}
		if (Type >= 0 && Type <= 6) //무기일때
		{
			if (!p->TwoHand) //한손무기일때 80%
				Gold = Gold * 80 / 100;
		}
		for (int i = 0; i<m_SpecialNum; i++)
		{
			switch (m_Special[i])
			{
			case AT_SKILL_BLOCKING:
			case AT_SKILL_SWORD1:
			case AT_SKILL_SWORD2:
			case AT_SKILL_SWORD3:
			case AT_SKILL_SWORD4:
			case AT_SKILL_SWORD5:
#ifdef ADD_SKILL_20031022
			case AT_SKILL_SWORD6:
#endif
			case AT_SKILL_CROSSBOW:
#ifdef MODIFY_ITEM_PRICE_MAXFIX
				Gold += (__int64)((double)Gold*1.5f);
#else
				Gold += (DWORD)((float)Gold*1.5f);
#endif
				break;
			case AT_IMPROVE_DAMAGE:
			case AT_IMPROVE_MAGIC:
			case AT_IMPROVE_DEFENSE:
			case AT_LIFE_REGENERATION:
#ifdef ADD_SUMMONER_SECOND_THIRD_WING_20071130
			case AT_IMPROVE_CURSE:
#endif				
				switch (m_Option3)
				{
#ifdef MODIFY_ITEM_PRICE_MAXFIX
				case 1:Gold += (__int64)((double)Gold * 6 / 10); break;
				case 2:Gold += (__int64)((double)Gold * 14 / 10); break;
				case 3:Gold += (__int64)((double)Gold * 28 / 10); break;
				case 4:Gold += (__int64)((double)Gold * 56 / 10); break;
#else
				case 1:Gold += (DWORD)((float)Gold * 6 / 10); break;
				case 2:Gold += (DWORD)((float)Gold * 14 / 10); break;
				case 3:Gold += (DWORD)((float)Gold * 28 / 10); break;
				case 4:Gold += (DWORD)((float)Gold * 56 / 10); break;
#endif
				}
				break;
			case AT_IMPROVE_BLOCKING:
				switch (m_Option3)
				{
#ifdef MODIFY_ITEM_PRICE_MAXFIX
				case 1: Gold += (__int64)((double)Gold * 6 / 10); break;
				case 2: Gold += (__int64)((double)Gold * 14 / 10); break;
				case 3: Gold += (__int64)((double)Gold * 28 / 10); break;
				case 4: Gold += (__int64)((double)Gold * 56 / 10); break;
#else
				case 1: Gold += (DWORD)((float)Gold * 6 / 10); break;
				case 2: Gold += (DWORD)((float)Gold * 14 / 10); break;
				case 3: Gold += (DWORD)((float)Gold * 28 / 10); break;
				case 4: Gold += (DWORD)((float)Gold * 56 / 10); break;
#endif
				}
				break;
			case AT_LUCK:
#ifdef MODIFY_ITEM_PRICE_MAXFIX
				Gold += (__int64)((double)Gold * 25 / 100);
#else
				Gold += (DWORD)((float)Gold * 25 / 100);
#endif
				break;
			case AT_IMPROVE_LIFE:
			case AT_IMPROVE_MANA:
			case AT_DECREASE_DAMAGE:
			case AT_REFLECTION_DAMAGE:
			case AT_IMPROVE_BLOCKING_PERCENT:
			case AT_IMPROVE_GAIN_GOLD:
			case AT_EXCELLENT_DAMAGE:
			case AT_IMPROVE_DAMAGE_LEVEL:
			case AT_IMPROVE_DAMAGE_PERCENT:
			case AT_IMPROVE_MAGIC_LEVEL:
			case AT_IMPROVE_MAGIC_PERCENT:
			case AT_IMPROVE_ATTACK_SPEED:
			case AT_IMPROVE_GAIN_LIFE:
			case AT_IMPROVE_GAIN_MANA:
				Gold += Gold;
				break;

				//  추가 날개.(2003.09.23)
			case AT_PLUS_ONE_PERCENT_DAMAGE:
			case AT_PLUS_WING_MAXLIFE:
			case AT_PLUS_WING_MAXMANA:
			case AT_IMPROVE_AG_MAX:
			case AT_DAMAGE_ABSORB:
#ifdef ADD_THIRD_WING_20070525	// 3차 날개 가격 설정 - 옵션에 따른 추가금액
			case AT_5PER_IGNORE_DEFENSE:
			case AT_5PER_ATTACK_TURNING:
			case AT_RECOVER_100PER_LIFE:
			case AT_RECOVER_100PER_MASIC:
#endif				
#ifdef MODIFY_ITEM_PRICE_MAXFIX
				Gold += (__int64)((double)Gold * 25 / 100);
#else
				Gold += (DWORD)((float)Gold * 25 / 100);
#endif
				break;
			}
		}

	}

#ifndef CHARACTERDB_SERVER
#ifdef ADD_380ITEM_NEWOPTION_20060711
	// 추가 옵션에 따른 가격 변경 : 380 추가 옵션
	if (g_kItemSystemFor380.Is380OptionItem(this) == TRUE)
	{
		// 추가옵션 중 380 추가 옵션이 있는 경우 가격 1.6배
		Gold += (__int64)((double)Gold * 16 / 100);
	}
#endif // ADD_380ITEM_NEWOPTION_20060711

#ifdef MODIFY_ITEM_SOCKET_OPTION_BUGFIX_04_20080710
	// 소켓 아이템의 판매가격 설정 부분 추가
	if (g_SocketOptionSystem.IsSocketItem(this) == true)
	{
		int iSocketSlotCount = 0;
		int iSeedSphereValue = 0;
#ifdef MODIFY_ITEM_SOCKET_OPTION_BUGFIX_05_20080715
		DWORD dwSeedSphereValue = 0;
#endif // MODIFY_ITEM_SOCKET_OPTION_BUGFIX_05_20080715

		for (int i = 0; i < MAX_SOCKET_SLOT; i++)
		{
			if (m_SocketOption[i] != SOCKETSLOT_NONE)
			{
#ifdef MODIFY_ITEM_SOCKET_OPTION_BUGFIX_05_20080715
				if (m_SocketOption[i] != SOCKETSLOT_EMPTY)
				{
					dwSeedSphereValue += g_SocketOptionSystem.GetSeedSphereValue(m_SocketOption[i]);
				}
#endif // MODIFY_ITEM_SOCKET_OPTION_BUGFIX_05_20080715
				iSocketSlotCount++;
			}
		}
		Gold += (DWORD)((float)Gold * (8 * iSocketSlotCount) / 10);
#ifdef MODIFY_ITEM_SOCKET_OPTION_BUGFIX_05_20080715
		Gold += dwSeedSphereValue;
#endif // MODIFY_ITEM_SOCKET_OPTION_BUGFIX_05_20080715
	}
#endif // MODIFY_ITEM_SOCKET_OPTION_BUGFIX_04_20080710
#endif

#ifdef MODIFY_ITEM_PRICE_MAXFIX

	if (Gold>3000000000)
	{
		Gold = 3000000000;
	}

#else
	if (Gold>1200000000)
	{
		Gold = 1200000000;
	}
#endif

#ifdef FOR_TEMP_SERVER 
	//------------------------------------------>
	//grooving SEASON4 20080728 : 보석 판매 가격 1000 으로 통일(시즌4 체험 서버 임시 나중에 삭제)
	if (m_Type == MAKE_ITEMNUM(14, 42))	// 조석
	{
		Gold = 1000;
	}
	//<------------------------------------------
#endif //FOR_TEMP_SERVER
	m_BuyMoney = (DWORD)Gold;
	m_SellMoney = (DWORD)Gold;
	m_SellMoney = m_SellMoney / 3;

#ifdef _GAMESERVER
	if (g_GlobalConfig.m_bBlessBug == true && this->m_Type == ITEM_POTION + 13)
#else
	if (this->m_Type == ITEM_POTION + 13)
#endif
	{
		this->m_SellMoney *= this->m_Durability;

		if (this->m_SellMoney > MAX_ZEN)
			this->m_SellMoney = MAX_ZEN;
	}

	if ((m_Type < ITEM_POTION || m_Type > ITEM_POTION + 8) &&
#ifdef RING_EVENT_ITEMBOX_20031124		// 반지이벤트 - 마법사의 반지 판매가격
		m_Type != ITEM_HELPER + 20 &&		// 마법사의 반지
#endif
#ifdef ADD_NEW_MAP_KALIMA_20040518
		m_Type != ITEM_POTION + 28 &&		// 잃어버린 지도
		m_Type != ITEM_POTION + 29 &&		// 쿤둔의 표식
#endif

#ifdef MODIFY_ACCUMULATED_BUG_MARKOFLORD_SELL_VALUE_01_20050531
		m_Type != ITEM_POTION + 21 &&
#endif
		m_Type != ITEM_HELPER + 15 &&		// 열매
		m_Type != ITEM_HELPER + 16 &&		// 대천사의서
		m_Type != ITEM_HELPER + 17 &&		// 블러드본
		m_Type != ITEM_HELPER + 18			// 투명망토
#ifdef ADD_NEW_ITEM_FOR_CASTLE_01_20041116
		&&m_Type != ITEM_HELPER + 11		// 라이프스톤
		&& m_Type != ITEM_HELPER + 7		// 용병
#endif
#ifdef ADD_ITEM_FENRIR_01_20051110
		&&m_Type != ITEM_HELPER + 32		// 갑옷 파편
		&& m_Type != ITEM_HELPER + 33		// 여신 파편
		&& m_Type != ITEM_HELPER + 34		// 맹수 발톱
		&& m_Type != ITEM_HELPER + 35		// 뿔피리 조각
		&& m_Type != ITEM_HELPER + 36		// 부러진 뿔피리
		&& m_Type != ITEM_HELPER + 37		// 펜릴의 뿔피리
#endif
#ifdef HALLOWINDAY_JACK_O_LANTERN_EVENT_20061017
		&& m_Type != MAKE_ITEMNUM(14, 45)
		&& m_Type != MAKE_ITEMNUM(14, 46)
		&& m_Type != MAKE_ITEMNUM(14, 47)
		&& m_Type != MAKE_ITEMNUM(14, 48)
		&& m_Type != MAKE_ITEMNUM(14, 49)
		&& m_Type != MAKE_ITEMNUM(14, 50)
#endif
#ifdef CHRISTMAS_STAR_20061211
		&& m_Type != MAKE_ITEMNUM(14, 51)	// 크리스마스의 별
#endif	
#ifdef UPDATE_LUCKY_COIN_EVENT_20081029
		&& m_Type != MAKE_ITEMNUM(14, 100)
#endif	// UPDATE_LUCKY_COIN_EVENT_20081029		
#ifdef MODIFY_SELLITEM_WITHOUT_DURABILITY_20090914
#ifdef MODIFY_CHERRYBLOSSOM_SELL_MONEY_BUGFIX_20090325
		&& m_Type != MAKE_ITEMNUM(14, 85)		// 벚꽃술
		&& m_Type != MAKE_ITEMNUM(14, 86)		// 벚꽃놀이 경단
		&& m_Type != MAKE_ITEMNUM(14, 87)		// 벚꽃 꽃잎
		&& m_Type != MAKE_ITEMNUM(14, 90)		// 황금 벚꽃 가지
#endif // MODIFY_CHERRYBLOSSOM_SELL_MONEY_BUGFIX_20090325
#else
#ifdef MODIFY_CHERRYBLOSSOM_SELL_MONEY_BUGFIX_20090325
		&& m_Type == MAKE_ITEMNUM(14, 85)		// 벚꽃술
		&& m_Type == MAKE_ITEMNUM(14, 86)		// 벚꽃놀이 경단
		&& m_Type == MAKE_ITEMNUM(14, 87)		// 벚꽃 꽃잎
		&& m_Type == MAKE_ITEMNUM(14, 90)		// 황금 벚꽃 가지
#endif // MODIFY_CHERRYBLOSSOM_SELL_MONEY_BUGFIX_20090325
#endif // MODIFY_SELLITEM_WITHOUT_DURABILITY_20090914
		)
	{
		float  persent = 1.f - m_Durability / m_BaseDurability;
		DWORD  repairGold = (DWORD)(m_SellMoney * 0.6 * persent);
		m_SellMoney -= repairGold;
	}



	//if(p->Durability > 0)
	//	m_SellMoney += m_SellMoney*m_Durability/p->Durability;
	if (m_SellMoney >= 1000)
		m_SellMoney = m_SellMoney / 100 * 100;
	else if (m_SellMoney >= 100)
		m_SellMoney = m_SellMoney / 10 * 10;

	if (m_BuyMoney >= 1000)
		m_BuyMoney = m_BuyMoney / 100 * 100;
	else if (m_BuyMoney >= 100)
		m_BuyMoney = m_BuyMoney / 10 * 10;

}

void CItem::OldValue()
{
	if (m_Type == -1) return;

	int Gold = 0;
	/*ITEM_ATTRIBUTE *p = &ItemAttribute[m_Type];
	int Level = (int)sqrt(m_Level);

	int Type = m_Type/MAX_ITEM_INDEX;

	int Level2 = p->Level+m_Level*3;
	int excellent=FALSE;*/

	if (m_Type == ITEM_POTION + 13)	// 축석
	{
		Gold = 100000;
	}
	else if (m_Type == ITEM_POTION + 14)	// 영석
	{
		Gold = 70000;
	}
	else if (m_Type == ITEM_WING + 15)	// 혼석
	{
		Gold = 40000;
	}
	else if (m_Type == ITEM_POTION + 22)	// 창석
	{
		Gold = 450000;
	}
	else if (m_Type == ITEM_POTION + 16)	// 생석
	{
		Gold = 450000;
	}
	else
	{
		//m_OldSellMoney = m_SellMoney;
		m_OldBuyMoney = m_BuyMoney;
		return;
	}

	//m_OldSellMoney = Gold;
	m_OldBuyMoney = Gold;

	//m_OldSellMoney = m_OldSellMoney/3;		

	/*if( m_Type < ITEM_POTION || m_Type > ITEM_POTION+8)
	{
	float  persent = 1.f - m_Durability/m_BaseDurability;
	int	   repairGold = (int)(m_OldSellMoney * 0.6 * persent);
	m_OldSellMoney -= repairGold;
	}
	*/

	//if(p->Durability > 0)
	//	m_OldSellMoney += m_SellMoney*m_Durability/p->Durability;

	/*
	if(m_OldSellMoney>= 1000)
	m_OldSellMoney = m_OldSellMoney/100*100;
	else if(m_OldSellMoney >= 100)
	m_OldSellMoney = m_OldSellMoney/10*10;
	*/

	if (m_OldBuyMoney >= 1000)
		m_OldBuyMoney = m_OldBuyMoney / 100 * 100;
	else if (m_OldBuyMoney >= 100)
		m_OldBuyMoney = m_OldBuyMoney / 10 * 10;
}

//----------------------------------------------------------------------------
// 아이템의 가로 세로 크기를 얻는다.
//----------------------------------------------------------------------------
BOOL CItem::GetSize(int &w, int &h)
{
//#ifdef _DEBUG
//	if (m_Type < 0 || m_Type > MAX_ITEM - 1)
//	{
//		LogAdd("error: %s %d (m_Type:%d)", __FILE__, __LINE__, m_Type);
//		return FALSE;
//	}
//#endif
//	w = ItemAttribute[m_Type].Width;
//	h = ItemAttribute[m_Type].Height;
	int result;
	if (this->m_Type >= 0 && this->m_Type <= 0x3FFF)
	{
		w = ItemAttribute[this->m_Type].Width;
		h = ItemAttribute[this->m_Type].Height;
		result = 1;
	}
	else
	{
		LogAdd("error: %s %d (m_Type:%d)", __FILE__, __LINE__, this->m_Type);
		result = 0;
	}
	return result;
	return TRUE;
	//LogAdd("Item:%d %d", w, h);
}

int CItem::ItemDamageMin()
{
	if (m_Type < 0) return 0;

	int damagemin = m_DamageMinOrigin;
	PlusSpecial(&damagemin, AT_IMPROVE_DAMAGE);
	return damagemin;
}

int CItem::ItemDefense()
{
	if (m_Type < 0) return 0;

	if (!m_IsValidItem)
		return 0;

	int Defense = m_Defense;
	PlusSpecial(&Defense, AT_IMPROVE_DEFENSE);
	return Defense;
}

//#ifdef ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912	// 저주력을 얻어옴
//int CItem::ItemCurse()
//{
//	if (m_Type < 0) return 0;
//
//	if (!m_IsValidItem)
//		return 0;
//
//	int Curse = m_Curse;
//	//PlusSpecial(&Defense,AT_IMPROVE_DEFENSE);
//	return Curse;
//}
//#endif

#ifdef ADD_THIRD_WING_20070525	// IsClass() 수정 처리
BOOL CItem::IsClass(char aClass, int ChangeUP, int ThirdChangeUp)
{
	if (aClass < 0 || aClass >= MAX_CLASSTYPE)
	{
		LogAdd("클래스 에러 : %d (%s %d)", aClass, __FILE__, __LINE__);
		return FALSE;
	}

	int requireclass = m_RequireClass[aClass];

	if (requireclass == 0) return FALSE;
	if (requireclass >= 3)	// 3차전직이상
	{
		if (requireclass != ThirdChangeUp + 2)
			return FALSE;
	}
	else if (requireclass > 1)
	{	// 전직전용이면
		if (requireclass != ChangeUP + 1)
			return FALSE;
	}

	return TRUE;
}
#else
#ifdef NEW_SKILL_FORSKYLAND
BOOL CItem::IsClass(char aClass, int ChangeUP)
{
	if (aClass < 0 || aClass >= MAX_CLASSTYPE)
	{
		LogAdd("클래스 에러 : %d (%s %d)", aClass, __FILE__, __LINE__);
		return FALSE;
	}

	int requireclass = m_RequireClass[aClass];

	if (requireclass == 0) return FALSE;
	if (requireclass > 1)
	{	// 전직전용이면
		if (requireclass != ChangeUP + 1)
			return FALSE;
	}
	return TRUE;
}
#else
// 아이템을 사용할수 있는 직업인지 
BOOL CItem::IsClass(char aClass)
{
	if (aClass < 0 || aClass >= MAX_CLASSTYPE)
	{
		LogAdd("클래스 에러 : %d (%s %d)", aClass, __FILE__, __LINE__);
		return FALSE;
	}
	if (m_RequireClass[aClass] == 0) return FALSE;
	return TRUE;
}
#endif	// NEW_SKILL_FORSKYLAND
#endif	// ADD_THIRD_WING_20070525

//----------------------------------------------------------------------------
// 아이템의 이름을 얻는다.
//----------------------------------------------------------------------------
char *CItem::GetName()
{
#ifdef _DEBUG
	if (m_Type < 0 || m_Type > MAX_ITEM - 1)
	{
		//LogAdd("error: %s %d (m_Type:%d)", __FILE__, __LINE__, m_Type);
		return NULL;
	}
#endif	
	return ItemAttribute[m_Type].Name;
	//LogAdd("Item:%d %d", w, h);
}


void CItem::PlusSpecialSetRing(BYTE* Value)
{
	if (m_Type < 0) return;

	if (!IsSetItem())		// 반지 추가 스킬 데미지 적용
		return;

	if (m_Durability == 0.f)
	{	// 내구력이 0이면  추가 옵션 적용하지 않는다
		return;
	}

	if (!m_IsValidItem)		// 장착 가능한 아이템이 아니면 적용하지 않는다
		return;

	ITEM_ATTRIBUTE *p = &ItemAttribute[m_Type];

	if (p->ResistanceType == -1)
		return;

	//BYTE iValue = m_Option3*5;
	BYTE iValue = 5;
	Value[p->ResistanceType] += iValue - (BYTE)(iValue*m_CurrentDurabilityState);
}

void CItem::PlusSpecial(int* Value, int Special)
{
	if (m_Type < 0) return;

	if (m_Durability == 0.f)
	{	// 내구력이 0이면  추가 옵션 적용하지 않는다
		return;
	}

	if (!m_IsValidItem)		// 장착 가능한 아이템이 아니면 적용하지 않는다
		return;

	for (int i = 0; i<m_SpecialNum; i++)
	{
		if (m_Special[i] == Special)
		{
			switch (Special)
			{
			case AT_IMPROVE_BLOCKING:
			{
				int iValue = m_Option3 * 5;
				(*Value) += iValue - (int)(iValue*m_CurrentDurabilityState);
			}
			break;
			case AT_LUCK:
				*Value += 4;
				break;
			case AT_IMPROVE_MAGIC:
			case AT_IMPROVE_DEFENSE:
			case AT_IMPROVE_DAMAGE:
#ifdef ADD_SUMMONER_SECOND_THIRD_WING_20071130
			case AT_IMPROVE_CURSE:
#endif	
			{
				int iValue = m_Option3 * 4;
				(*Value) += iValue - (int)(iValue*m_CurrentDurabilityState);
			}
			break;

#ifdef NEW_FORSKYLAND2
			case AT_PLUS_WING_MAXLIFE:		// 최대 HP+50증가			
			case AT_PLUS_WING_MAXMANA:		// 최대 MP+50증가
			{
				(*Value) += 50 + m_Level * 5;
			}
			break;

			case AT_IMPROVE_AG_MAX:		// 최대 AG+50증가
			{
				(*Value) += 50;
			}
			break;
#endif

#ifdef DARKLORD_WORK		// 통솔 증가(망토)
			case AT_PLUS_WING_ADD_LEADERSHIP:
			{
				(*Value) += 10 + m_Level * 5;
			}
			break;
#endif

			default:	// AT_IMPROVE_DAMAGE
						// AT_IMPROVE_MAGIC 
						// AT_IMPROVE_DEFENSE
				*Value += m_Option3 * 4;
				//(*Value)
				break;
			}
		}
	}
}

void CItem::PlusSpecialPercent(int* Value, int Special, WORD Percent)
{
	if (m_Type < 0) return;


	for (int i = 0; i<m_SpecialNum; i++)
	{
		if (m_Special[i] == Special)
		{
			*Value += *Value*Percent / 100;
		}
	}
}

// 마나증가, AG증가 % 계산을 위해 확장
void CItem::PlusSpecialPercentEx(int* Value, int SourceValue, int Special)
{
	if (m_Type < 0) return;

	if (m_Durability == 0.f)
	{	// 내구력이 0이면  추가 옵션 적용하지 않는다
		return;
	}

	if (!m_IsValidItem)		// 장착 가능한 아이템이 아니면 적용하지 않는다
		return;


	for (int i = 0; i<m_SpecialNum; i++)
	{
		if (m_Special[i] == Special)
		{
			int iValue = SourceValue * m_Option3 / 100;
			(*Value) += iValue - (int)(iValue*m_CurrentDurabilityState);
		}
	}
}


// 세트 아이템 스탯 추가
void CItem::SetItemPlusSpecialStat(WORD* Value, int Special)
{
	if (m_Type < 0) return;

	if (m_Durability == 0.f)
	{	// 내구력이 0이면  추가 옵션 적용하지 않는다
		return;
	}

	for (int i = 0; i<m_SpecialNum; i++)
	{
		if (m_Special[i] == Special)
		{
			switch (Special)
			{
			case AT_SET_IMPROVE_STRENGTH:
			case AT_SET_IMPROVE_DEXTERITY:
			case AT_SET_IMPROVE_VITALITY:
			case AT_SET_IMPROVE_ENERGY:
			{
				int iValue = m_SetAddStat;
				(*Value) += iValue - (int)(iValue*m_CurrentDurabilityState);	// 내구도 적용
			}
			break;

			default:
				*Value += m_Option3 * 3;
				break;
			}
		}
	}
}

int CItem::GetAddStatType()
{
	ITEM_ATTRIBUTE *p = &ItemAttribute[m_Type];
	return p->SetAttr;
}

int CItem::GetWeaponType()
{
	if (m_Type <= ITEM_STAFF)
	{	// 검류
		return 1;
	}
	else if (m_Type <= ITEM_SHIELD)
	{	// 지팡이류
		return 2;
	}
	return 0;
}

#ifdef DARKLORD_WORK
void CItem::SetPetItemInfo(int petlevel, int petexp)
{
	//|| m_Type == MAKE_ITEMNUM(13,5) )
	if (m_Type == MAKE_ITEMNUM(13, 4))
	{	// 다크호스
		m_PetItem_Level = petlevel;
		m_PetItem_Exp = petexp;

		if (m_PetItem_Exp < gPetItemExp.m_DarkHorseExpTable[m_PetItem_Level] ||
			m_PetItem_Exp >= gPetItemExp.m_DarkHorseExpTable[m_PetItem_Level + 1])
		{
			m_PetItem_Exp = gPetItemExp.m_DarkHorseExpTable[m_PetItem_Level];
		}

#ifdef ADD_380ITEM_NEWOPTION_20060711
		Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption, m_ItemOptionEx);
#else
		Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption,3);
#endif
		PetValue();

		m_IsLoadPetItemInfo = TRUE;
	}
	else if (m_Type == MAKE_ITEMNUM(13, 5))
	{	// 다크스피릿
		m_PetItem_Level = petlevel;
		m_PetItem_Exp = petexp;

		if (m_PetItem_Exp < gPetItemExp.m_DarkSpiritExpTable[m_PetItem_Level] ||
			m_PetItem_Exp >= gPetItemExp.m_DarkSpiritExpTable[m_PetItem_Level + 1])
		{
			m_PetItem_Exp = gPetItemExp.m_DarkSpiritExpTable[m_PetItem_Level];
		}

#ifdef ADD_380ITEM_NEWOPTION_20060711
		Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption, m_ItemOptionEx);
#else
		Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption,3);
#endif


		PetValue();

		m_IsLoadPetItemInfo = TRUE;
	}
}

int	CItem::AddPetItemExp(int petexp)
{
	if (m_Durability <= 0.f)
		return FALSE;	// 내구도가 0이때는 경험치 상승 없다

	if (!m_IsLoadPetItemInfo)
		return FALSE;	// 펫 아이템 정보를 못 얻어 왔기 때문에 경험치 변동 없다

	if (m_PetItem_Level < 1)
	{
		m_PetItem_Level = 1;
		m_PetItem_Exp = 0;


#ifdef ADD_380ITEM_NEWOPTION_20060711
		Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption, m_ItemOptionEx);
#else
		Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption,3);
#endif

		PetValue();

		return FALSE;
	}

	if (m_Type == MAKE_ITEMNUM(13, 4))
	{	// 다크호스		
		if (m_PetItem_Level >= MAX_DARK_HORSE_LEVEL)
			return FALSE;	// 최대 레벨이면 경험치 상승 없다

		BOOL	IsLevelUp = FALSE;

		int nextexp = gPetItemExp.m_DarkHorseExpTable[m_PetItem_Level + 1];
		m_PetItem_Exp += petexp;

		while (m_PetItem_Exp >= nextexp)
		{
			m_PetItem_Level++;
			nextexp = gPetItemExp.m_DarkHorseExpTable[m_PetItem_Level + 1];
			IsLevelUp = TRUE;
		}

		if (IsLevelUp)
		{
#ifdef ADD_380ITEM_NEWOPTION_20060711
			Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption, m_ItemOptionEx);
#else
			Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption,3);
#endif

			PetValue();
			return TRUE;
		}
	}
	else if (m_Type == MAKE_ITEMNUM(13, 5))
	{	// 다크스피릿
		if (m_PetItem_Level >= MAX_DARK_SPIRIT_LEVEL)
			return FALSE;	// 최대 레벨이면 경험치 상승 없다

		BOOL	IsLevelUp = FALSE;

		int nextexp = gPetItemExp.m_DarkSpiritExpTable[m_PetItem_Level + 1];
		m_PetItem_Exp += petexp;

		while (m_PetItem_Exp >= nextexp)
		{
			m_PetItem_Level++;
			nextexp = gPetItemExp.m_DarkSpiritExpTable[m_PetItem_Level + 1];
			IsLevelUp = TRUE;
			//m_PetItem_Exp = gPetItemExp.m_DarkSpiritExpTable[m_PetItem_Level+1];			
		}

		if (IsLevelUp)
		{
#ifdef ADD_380ITEM_NEWOPTION_20060711
			Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption, m_ItemOptionEx);
#else
			Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption,3);
#endif
			PetValue();
			return TRUE;
		}
	}
	return FALSE;
}

int	CItem::DecPetItemExp(int percent)
{
	if (!m_IsLoadPetItemInfo)
		return FALSE;	// 펫 아이템 정보를 못 얻어 왔기 때문에 경험치 변동 없다

	if (m_PetItem_Level < 1)
	{
		m_PetItem_Level = 1;
		m_PetItem_Exp = 0;
#ifdef ADD_380ITEM_NEWOPTION_20060711
		Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption, m_ItemOptionEx);
#else
		Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption,3);
#endif

		PetValue();
		return FALSE;
	}

	if (m_Type == MAKE_ITEMNUM(13, 4))
	{	// 다크호스		
		int decexp = gPetItemExp.m_DarkHorseExpTable[m_PetItem_Level + 1] - gPetItemExp.m_DarkHorseExpTable[m_PetItem_Level];
		decexp = decexp * percent / 100;
		m_PetItem_Exp -= decexp;

		if (m_PetItem_Exp < 0)
		{
			m_PetItem_Level = 1;
			m_PetItem_Exp = 0;
#ifdef ADD_380ITEM_NEWOPTION_20060711
			Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption, m_ItemOptionEx);
#else
			Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption,3);
#endif
			PetValue();
		}
		else
		{	// 레벨 다운
			if (m_PetItem_Exp < gPetItemExp.m_DarkHorseExpTable[m_PetItem_Level])
			{
				m_PetItem_Level--;
#ifdef ADD_380ITEM_NEWOPTION_20060711
				Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption, m_ItemOptionEx);
#else
				Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption,3);
#endif
				PetValue();
				return TRUE;
			}
		}
	}
	else if (m_Type == MAKE_ITEMNUM(13, 5))
	{	// 다크스피릿
		int decexp = gPetItemExp.m_DarkSpiritExpTable[m_PetItem_Level + 1] - gPetItemExp.m_DarkSpiritExpTable[m_PetItem_Level];
		decexp = decexp * percent / 100;
		m_PetItem_Exp -= decexp;

		if (m_PetItem_Exp < 0)
		{
			m_PetItem_Level = 1;
			m_PetItem_Exp = 0;

#ifdef ADD_380ITEM_NEWOPTION_20060711
			Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption, m_ItemOptionEx);
#else
			Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption,3);
#endif
			PetValue();
		}
		else
		{	// 레벨 다운
			if (m_PetItem_Exp < gPetItemExp.m_DarkSpiritExpTable[m_PetItem_Level])
			{
				m_PetItem_Level--;
#ifdef ADD_380ITEM_NEWOPTION_20060711
				Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption, m_ItemOptionEx);
#else
				Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption,3);
#endif
				PetValue();
				return TRUE;
			}
		}
	}
	return FALSE;
}

int	CItem::PetItemLevelDown(int exp)
{
	if (!m_IsLoadPetItemInfo)
		return FALSE;	// 펫 아이템 정보를 못 얻어 왔기 때문에 경험치 변동 없다

						// MODIFY_ACCUMULATED_BUG_DARKLORD_PET_EXP_01_20050603
						// 문제 :	Exp에 대해 1 레벨 감소만 가능.
						//			실제로 카오스캐슬, 광장, 블러드캐슬에서는 여러 펫레벨치의 경치 획득이 가능하다.
						//
#ifdef MODIFY_ACCUMULATED_BUG_DARKLORD_PET_EXP_01_20050603
	if (m_PetItem_Level < 2)
		return FALSE;

	m_PetItem_Exp -= exp;
	m_PetItem_Level--;

	// 다크 호스 
	if (m_Type == MAKE_ITEMNUM(13, 4))
	{
		int iPrevPetItemLevel = m_PetItem_Level;
		int iPrevExp = gPetItemExp.m_DarkHorseExpTable[iPrevPetItemLevel];

		while (m_PetItem_Exp <= iPrevExp)
		{
			if (iPrevPetItemLevel <= 1)
				break;

			iPrevPetItemLevel--;
			iPrevExp = gPetItemExp.m_DarkHorseExpTable[iPrevPetItemLevel];
		}

		m_PetItem_Level = iPrevPetItemLevel;
	}
	// 다크 스피릿
	else if (m_Type == MAKE_ITEMNUM(13, 5))
	{
		int iPrevPetItemLevel = m_PetItem_Level;
		int iPrevExp = gPetItemExp.m_DarkSpiritExpTable[iPrevPetItemLevel];

		while (m_PetItem_Exp <= iPrevExp)
		{
			if (iPrevPetItemLevel <= 1)
				break;

			iPrevPetItemLevel--;
			iPrevExp = gPetItemExp.m_DarkSpiritExpTable[iPrevPetItemLevel];
		}

		m_PetItem_Level = iPrevPetItemLevel;
	}
#else

	m_PetItem_Level--;
	m_PetItem_Exp -= exp;

#endif

#ifdef ADD_380ITEM_NEWOPTION_20060711
	Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption, m_ItemOptionEx);
#else
	Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption,3);
#endif
	PetValue();
	return TRUE;
}

// 펫 아이템용 가격 설정(펫 정보를 받을때, 레벨업다운시 콜)
void CItem::PetValue()
{
	if (m_Type == MAKE_ITEMNUM(13, 4))
	{	//다크 호스
		m_SellMoney = m_PetItem_Level * 2000000;
	}
	else if (m_Type == MAKE_ITEMNUM(13, 5))
	{	// 다크스피릿
		m_SellMoney = m_PetItem_Level * 1000000;
	}


	m_BuyMoney = m_SellMoney;

#ifdef BUGFIX_SELL_PRICE_OF_DARKLOAD_PETS_20050310
	m_SellMoney /= 3;
#endif

	if (m_SellMoney >= 1000)
		m_SellMoney = m_SellMoney / 100 * 100;
	else if (m_SellMoney >= 100)
		m_SellMoney = m_SellMoney / 10 * 10;

	if (m_BuyMoney >= 1000)
		m_BuyMoney = m_BuyMoney / 100 * 100;
	else if (m_BuyMoney >= 100)
		m_BuyMoney = m_BuyMoney / 10 * 10;
}
#endif

int CItem::IsExtItem()
{
#ifdef MODIFY_FENRIR_EXOPTION_BUG_20060522	
	// 펜릴인 경우 : 파괴나 수호일지라도 엑설런트 아이템이 아니다
	if (m_Type == MAKE_ITEMNUM(13, 37))
		return FALSE;
#endif

	if (m_NewOption & 0x7F) return TRUE;
	return FALSE;
}

//-----------------------------------------------------------------------------
// 생명증가 속성이 있는가?
int CItem::IsExtLifeAdd()
{
	if ((m_NewOption & 0x20) == 0x20) return 4;
	return 0;
}

// 마나증가 속성이 있는가?
int CItem::IsExtManaAdd()
{
	if ((m_NewOption & 0x10) == 0x10) return 4;
	return 0;
}

// 데미지 감소 속성이 있는가?
int CItem::IsExtDamageMinus()
{
	if ((m_NewOption & 0x08) == 0x08) return 4;
	return 0;
}

// 데미지 반사 속성이 있는가?
int CItem::IsExtDamageReflect()
{
#ifdef NEW_FORSKYLAND3
	if ((m_NewOption & 0x04) == 0x04) return 5;
#else
	if ((m_NewOption & 0x04) == 0x04) return 4;
#endif
	return 0;
}

// 방어 성공율 
int CItem::IsExtDefenseSuccessfull()
{
	if ((m_NewOption & 0x02) == 0x02) return 10;
	return 0;
}

// 몬스터 킬 했을때 얻는 돈 
int CItem::IsExtMonsterMoney()
{
#ifdef UPDATE_ZEN_DROP_DOWN_20080806	// 젠 증가 30% 로 변경
	if ((m_NewOption & 0x01) == 0x01) return 30;
#else	// UPDATE_ZEN_DROP_DOWN_20080806
	if ((m_NewOption & 0x01) == 0x01) return 40;
#endif	// UPDATE_ZEN_DROP_DOWN_20080806
	return 0;
}

// 무기 및 목걸이 확장 아이템 속성
// 엑설런트 데미지 추가확률
int CItem::IsExtExcellentDamage()
{
	// 방패면 엑설런트 데미지를 적용하지 않는다.
	if (m_Type >= ITEM_SHIELD && m_Type < ITEM_HELM) return 0;

	if ((m_NewOption & 0x20) == 0x20) return 10;
	return 0;
}

// 공격력 증가 + 레벨/20 
// 마력 증가 + 레벨/20
int CItem::IsExtAttackRate()
{
	if ((m_NewOption & 0x10) == 0x10) return 1;
	return 0;
}

// 공격력 증가 + 2%, 
// 마력 증가 + 2%
int CItem::IsExtAttackRate2()
{
	if ((m_NewOption & 0x08) == 0x08) return 2;
	//if( (m_NewOption&0x08) == 0x08 ) return 100;
	return 0;
}

// 공격 스피드 증가
int CItem::IsExtAttackSpeed()
{
	if ((m_NewOption & 0x04) == 0x04) return 7;
	return 0;
}

// 몬스터 죽였을때 얻는 생명 + 생명/8
int CItem::IsExtMonsterDieLife()
{
	if ((m_NewOption & 0x02) == 0x02) return 1;
	return 0;
}

// 몬스터 죽였을때 얻는 마나 + 마나/8
int CItem::IsExtMonsterDieMana()
{
	// 방패면 엑설런트 데미지를 적용하지 않는다.
	if (m_Type >= ITEM_SHIELD && m_Type < ITEM_HELM) return 0;

	if ((m_NewOption & 0x01) == 0x01) return 1;
	return 0;
}


// 날개 3%확률로 적의 방어력 무시 공격
int CItem::IsWingOpGetOnePercentDamage()
{
	if (m_Durability < 1.f)
		return 0;

#ifdef ADD_THIRD_WING_20070525 // 적방무시 3%는 2차날개 옵션
#ifdef ADD_SUMMONER_SECOND_THIRD_WING_20071130	// 절망의 날개 적방 무시
	if ((m_Type >= MAKE_ITEMNUM(12, 3) && m_Type <= MAKE_ITEMNUM(12, 6)) || m_Type == MAKE_ITEMNUM(13, 30)
		|| m_Type == MAKE_ITEMNUM(12, 42))
#else
	if ((m_Type >= MAKE_ITEMNUM(12, 3) && m_Type <= MAKE_ITEMNUM(12, 6)) || m_Type == MAKE_ITEMNUM(13, 30))
#endif
	{
		if ((m_NewOption & PLUS_WING_ONE_PERCENT_DAMAGE))
			return 3;
	}
#else
	if ((m_NewOption&PLUS_WING_ONE_PERCENT_DAMAGE)) return 3;
#endif	

	return 0;
}

// 날개 몬스터에게 받는 최대 타격 데미지에서 HP 10%획득
/*
int CItem::IsWingOpGetLifeToMonster()
{
if( m_Durability < 1.f )
return 0;

if( (m_NewOption&PLUS_WING_GETLIFE_TO_MONSTER)  == 0x01 ) return 10;
return 0;
}*/


// 날개 몬스터에게 받는 최대 타격 데미지에서 MP 10%획득	
int CItem::IsWingOpGetManaToMoster()
{
	if (m_Durability < 1.f)
		return 0;

#ifdef ADD_THIRD_WING_20070525	// MP 10%획득은 2차날개 옵션
#ifdef ADD_SUMMONER_SECOND_THIRD_WING_20071130
	if ((m_Type >= MAKE_ITEMNUM(12, 3) && m_Type <= MAKE_ITEMNUM(12, 6)) || m_Type == MAKE_ITEMNUM(13, 30)
		|| m_Type == MAKE_ITEMNUM(12, 42))
#else
	if ((m_Type >= MAKE_ITEMNUM(12, 3) && m_Type <= MAKE_ITEMNUM(12, 6)) || m_Type == MAKE_ITEMNUM(13, 30))
#endif
#endif
		if ((m_NewOption&PLUS_WING_GETMANA_TO_MONSTER) == 0x01) return 10;

	return 0;
}

// 디노란트 5% 데미지흡수 추가
int CItem::IsDinorantReduceAttackDamaege()
{
	if (m_Durability < 1.f)
		return 0;

	if ((m_NewOption&PLUS_DINORANT_PLUS_REDUCE_DAMAGE) == 0x01) return 5;
	return 0;
}

#ifdef ADD_ITEM_FENRIR_01_20051110
// 펜릴 최종 데미지감소, 증가 추가
int CItem::IsFenrirIncLastAttackDamage()
{
	if (m_Durability < 1.f)
		return 0;

	if ((m_NewOption&PLUS_FENRIR_INCREASE_LAST_DAMAGE) == PLUS_FENRIR_INCREASE_LAST_DAMAGE) return 10;
	return 0;

}

int CItem::IsFenrirDecLastAttackDamage()
{
	if (m_Durability < 1.f)
		return 0;

	if ((m_NewOption&PLUS_FENRIR_DECREASE_LAST_DAMAGE) == PLUS_FENRIR_DECREASE_LAST_DAMAGE) return 10;
	return 0;
}
#endif

#ifdef ADD_ILLUSION_FENRIR_20070703
int CItem::IsIllusionFenrirOption()
{
	if (m_Durability < 1.f)
		return 0;

	if ((m_NewOption&PLUS_ILLUSION_FENRIR_OPTION) == PLUS_ILLUSION_FENRIR_OPTION) return 1;
	return 0;
}
#endif

#ifdef ADD_THIRD_WING_20070525	// 3차 날개 추가옵션 값 함수선언
// 적방무시 확률을 되돌려준다.
int CItem::GetIgnoreDefencePer()
{
	// _MODIFY_ADD_THIRD_WING_20070623
	// 3차 날개에 적용한다.
#ifdef ADD_SUMMONER_SECOND_THIRD_WING_20071130
	if ((m_Type >= MAKE_ITEMNUM(12, 36) && m_Type <= MAKE_ITEMNUM(12, 40))
		|| m_Type == MAKE_ITEMNUM(12, 43))
#else
	if (m_Type >= MAKE_ITEMNUM(12, 36) && m_Type <= MAKE_ITEMNUM(12, 40))
#endif
	{
		if (m_Durability < 1.f)
			return 0;

		if ((m_NewOption & PLUS_THIRD_WING_5PER_IGNORE_DEFENSE) == PLUS_THIRD_WING_5PER_IGNORE_DEFENSE)
			return 5;
	}
	return 0;
}
#endif	// ADD_THIRD_WING_20070525

#ifdef ADD_NEW_ITEM_FOR_CASTLE_01_20041116
int CItem::SimpleDurabilityDown(int iDur)
{
	m_Durability -= 1;

	if (m_Durability < 0.f)
	{
		m_Durability = 0.f;
		return 0;
	}

	if (CheckDurabilityState())
	{	// 내구력 감소에 따른 패널티가 적용된다 
		return 2;
	}

	return (int)m_Durability;
}
#endif

int CItem::DurabilityDown(int dur, int aIndex)
{
	if (m_Durability <= 0.f)
	{
		return 0;
	}

	m_DurabilitySmall += dur;

#if defined(MASTER_LEVEL_SKILL_SYSTEM_20071122) && !defined(CHARACTERDB_SERVER)	// 패시브 1차 - 내구감소2 : 날개/목걸이/반지 내구 감소
	int iBaseDurSmall = 564;
	if (gObj[aIndex].m_MPSkillOpt.iMpsDownDur2 > 0)
	{
		iBaseDurSmall += (iBaseDurSmall * gObj[aIndex].m_MPSkillOpt.iMpsDownDur2) / 100;
	}

	if (m_DurabilitySmall > iBaseDurSmall)
#else
	if (m_DurabilitySmall > 564)
#endif
	{
		m_DurabilitySmall = 0;
		m_Durability -= 1;

		if (m_Durability < 0.f)
		{
			m_Durability = 0.f;
		}

#if TESTSERVER == 1 

		char msg[255];
		wsprintf(msg, "%s:내구도감소 %d/%d", GetName(), (int)m_Durability, (int)m_BaseDurability);
		//GCServerMsgStringSend(msg, aIndex, 1);	
		LogAddTD(msg);
#endif

		if (CheckDurabilityState())
		{	// 내구력 감소에 따른 패널티가 적용된다 
			return 2;
		}
		return 1;
	}
	return (int)m_Durability;
}

int CItem::DurabilityDown2(int dur, int aIndex)
{
	if (m_Durability <= 0.f)
	{
		return 0;
	}

	m_DurabilitySmall += dur;

#if defined(MASTER_LEVEL_SKILL_SYSTEM_20071122) && !defined(CHARACTERDB_SERVER)	// 패시브 1차 - 내구감소1 : 기본 내구 감소
	int iBaseDurSmall = 1000;
	if (gObj[aIndex].m_MPSkillOpt.iMpsDownDur1 > 0)
	{
		iBaseDurSmall += (iBaseDurSmall * gObj[aIndex].m_MPSkillOpt.iMpsDownDur1) / 100;
	}

	if (m_DurabilitySmall > iBaseDurSmall)
#else
	if (m_DurabilitySmall > 1000)
#endif
	{
		m_DurabilitySmall = 0;
		m_Durability -= 1;

		if (m_Durability < 0.f)
		{
			m_Durability = 0.f;
		}
#if TESTSERVER == 1 

		char msg[255];
		wsprintf(msg, "%s:내구도감소 %d/%d", GetName(), (int)m_Durability, (int)m_BaseDurability);
		//GCServerMsgStringSend(msg, aIndex, 1);	
		LogAddTD(msg);
#endif

		if (CheckDurabilityState())
		{	// 내구력 감소에 따른 패널티가 적용된다 
			return 2;
		}
		return 1;
	}
	return 0;
}

// 검/창/도끼/둔기 무기 아이템 내구력을 하향 조정한다.
int CItem::NormalWeaponDurabilityDown(int defence, int aIndex)
{
	if (m_Durability <= 0.f)
	{
		return 0;
	}

	int damagemin = m_DamageMinOrigin;
	int plusdamage = 0;
	PlusSpecial(&plusdamage, AT_IMPROVE_DAMAGE);

	if (damagemin == 0)
	{
		LogAdd("damagemin이 0이다");
		return 0;
	}

	int div = damagemin + (damagemin / 2) + plusdamage;

	if (div == 0)
		return 0;

	int DecreaseDur = (defence * 2) / div;

#ifdef MODIFY_SOCKET_ITEM_NEW_OPTION_20080818
	DecreaseDur -= (DecreaseDur * m_ImproveDurabilityRate) / 100;
#endif // MODIFY_SOCKET_ITEM_NEW_OPTION_20080818

	m_DurabilitySmall += DecreaseDur;
#if defined(MASTER_LEVEL_SKILL_SYSTEM_20071122) && !defined(CHARACTERDB_SERVER)	// 패시브 1차 - 내구감소1 : 기본 내구 감소
	int iBaseDurSmall = 564;
	if (gObj[aIndex].m_MPSkillOpt.iMpsDownDur1 > 0)
	{
		iBaseDurSmall += (iBaseDurSmall * gObj[aIndex].m_MPSkillOpt.iMpsDownDur1) / 100;
	}

	if (m_DurabilitySmall > iBaseDurSmall)
#else
	if (m_DurabilitySmall > 564)
#endif
	{
		m_DurabilitySmall = 0;
		m_Durability -= 1;

		if (m_Durability < 0.f)
		{
			m_Durability = 0.f;
		}

		if (CheckDurabilityState())
		{	// 내구력 감소에 따른 패널티가 적용된다 
			return 2;
		}
		return 1;
	}
	return 0;
}

// 활 무기 아이템 내구력을 하향 조정한다.
int CItem::BowWeaponDurabilityDown(int defence, int aIndex)
{
	if (m_Durability <= 0.f)
	{
		return 0;
	}

	int damagemin = m_DamageMinOrigin;
	int plusdamage = 0;
	PlusSpecial(&plusdamage, AT_IMPROVE_DAMAGE);

	int div = damagemin + (damagemin / 2) + plusdamage;

	if (div == 0)
		return 0;

	int DecreaseDur = (defence * 2) / div;

#ifdef MODIFY_SOCKET_ITEM_NEW_OPTION_20080818
	DecreaseDur -= (DecreaseDur * m_ImproveDurabilityRate) / 100;
#endif // MODIFY_SOCKET_ITEM_NEW_OPTION_20080818

	m_DurabilitySmall += DecreaseDur;
#if defined(MASTER_LEVEL_SKILL_SYSTEM_20071122) && !defined(CHARACTERDB_SERVER)	// 패시브 1차 - 내구감소1 : 활 무기
	int iBaseDurSmall = 780;
	if (gObj[aIndex].m_MPSkillOpt.iMpsDownDur1 > 0)
	{
		iBaseDurSmall += (iBaseDurSmall * gObj[aIndex].m_MPSkillOpt.iMpsDownDur1) / 100;
	}

	if (m_DurabilitySmall > iBaseDurSmall)
#else
	if (m_DurabilitySmall > 780)
#endif
	{
		m_DurabilitySmall = 0;
		m_Durability -= 1;

		if (m_Durability < 0.f)
		{
			m_Durability = 0.f;
		}
		if (CheckDurabilityState())
		{	// 내구력 감소에 따른 패널티가 적용된다 
			return 2;
		}
		return 1;
	}
	return 0;
}

// 지팡이 무기 아이템 내구력을 하향 조정한다.
int CItem::StaffWeaponDurabilityDown(int defence, int aIndex)
{
	if (m_Durability <= 0.f)
	{
		return 0;
	}

	int magic = (m_Magic / 2) + (m_Level * 2);
	int plusmagic = 0;

	PlusSpecial(&plusmagic, AT_IMPROVE_MAGIC);

	int div = magic + magic / 3 + plusmagic;
	if (div == 0)
		return 0;

	int DecreaseDur = defence / div;

#ifdef MODIFY_SOCKET_ITEM_NEW_OPTION_20080818
	DecreaseDur -= (DecreaseDur * m_ImproveDurabilityRate) / 100;
#endif // MODIFY_SOCKET_ITEM_NEW_OPTION_20080818

	m_DurabilitySmall += DecreaseDur;
#if defined(MASTER_LEVEL_SKILL_SYSTEM_20071122) && !defined(CHARACTERDB_SERVER)	// 패시브 1차 - 내구감소1 : 지팡이 무기
	int iBaseDurSmall = 1050;
	if (gObj[aIndex].m_MPSkillOpt.iMpsDownDur1 > 0)
	{
		iBaseDurSmall += (iBaseDurSmall * gObj[aIndex].m_MPSkillOpt.iMpsDownDur1) / 100;
	}

	if (m_DurabilitySmall > iBaseDurSmall)
#else
	if (m_DurabilitySmall > 1050)
#endif
	{
		m_DurabilitySmall = 0;
		m_Durability -= 1;

		if (m_Durability < 0.f)
		{
			m_Durability = 0.f;
		}

		if (CheckDurabilityState())
		{	// 내구력 감소에 따른 패널티가 적용된다 
			return 2;
		}
		return 1;
	}
	return 0;
}

// 방어구 아이템 내구력을 하향 조정한다.
int CItem::ArmorDurabilityDown(int damagemin, int aIndex)
{
	if (m_Durability <= 0.f)
	{
		return 0;
	}

	if (m_Type == -1)
	{
		return FALSE;
	}

	int def = m_DefenseOrigin;
	int plusdef = 0;

	if (def == 0)
	{
		LogAdd("def이 0이다");
		return 0;
	}

	int DecreaseDur = 0;
	if ((m_Type >= ITEM_SHIELD && m_Type < ITEM_HELM))
	{	// 방패류
		PlusSpecial(&plusdef, AT_IMPROVE_BLOCKING);
		DecreaseDur = damagemin / (def * 5 + plusdef);
	}
	else if (m_RequireClass[CLASS_WIZARD])
	{
		PlusSpecial(&plusdef, AT_IMPROVE_DEFENSE);
		DecreaseDur = damagemin / (def * 3 + plusdef);
	}
	else if (m_RequireClass[CLASS_KNIGHT])
	{
		PlusSpecial(&plusdef, AT_IMPROVE_DEFENSE);
		DecreaseDur = damagemin / (def * 3 + plusdef);
	}
	else if (m_RequireClass[CLASS_ELF])
	{
		PlusSpecial(&plusdef, AT_IMPROVE_DEFENSE);
		DecreaseDur = damagemin / (def * 2 + plusdef);
	}
	else if (m_RequireClass[CLASS_MAGUMSA])
	{
		PlusSpecial(&plusdef, AT_IMPROVE_DEFENSE);
		DecreaseDur = damagemin / (def * 7 + plusdef);
	}
#ifdef DARKLORD_WORK
	else if (m_RequireClass[CLASS_DARKLORD])
	{
		PlusSpecial(&plusdef, AT_IMPROVE_DEFENSE);
		DecreaseDur = damagemin / (def * 6 + plusdef);
	}
#endif
#ifdef MODIFY_SUMMONER_ITEM_DURABILITY_DOWN_BUGFIX_20071213
	else if (m_RequireClass[CLASS_SUMMONER])
	{
		PlusSpecial(&plusdef, AT_IMPROVE_DEFENSE);
		DecreaseDur = damagemin / (def * 3 + plusdef);
	}
#endif	

	m_DurabilitySmall += DecreaseDur;

#if defined(MASTER_LEVEL_SKILL_SYSTEM_20071122) && !defined(CHARACTERDB_SERVER)	// 패시브 1차 - 내구감소1 : 방어구 무기
	int iBaseDurSmall = 69;
	if (gObj[aIndex].m_MPSkillOpt.iMpsDownDur1 > 0)
	{
		iBaseDurSmall += (iBaseDurSmall * gObj[aIndex].m_MPSkillOpt.iMpsDownDur1) / 100;
	}

	if (m_DurabilitySmall > iBaseDurSmall)
#else
	if (m_DurabilitySmall > 69)
#endif
	{
		m_DurabilitySmall = 0;
		m_Durability -= 1;

		if (m_Durability < 0.f)
		{
			m_Durability = 0.f;
		}

		if (CheckDurabilityState())
		{	// 내구력 감소에 따른 패널티가 적용된다 
			return 2;
		}
		return 1;
	}
	return 0;
}

int	CItem::CheckDurabilityState()
{
	if (m_Durability == 0.f)
	{
		if (m_CurrentDurabilityState != 1.f)
		{
			m_CurrentDurabilityState = 1.f;

#ifdef ADD_380ITEM_NEWOPTION_20060711
			Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption, m_ItemOptionEx);
#else
			Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption,3);
#endif
			return TRUE;
		}
	}
	else if (m_Durability < m_DurabilityState[2])
	{
		if (m_CurrentDurabilityState != 0.5f)
		{
			m_CurrentDurabilityState = 0.5f;
#ifdef ADD_380ITEM_NEWOPTION_20060711
			Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption, m_ItemOptionEx);
#else
			Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption,3);
#endif
			return TRUE;
		}
	}
	else if (m_Durability < m_DurabilityState[1])
	{
		if (m_CurrentDurabilityState != 0.3f)
		{
			m_CurrentDurabilityState = 0.3f;
#ifdef ADD_380ITEM_NEWOPTION_20060711
			Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption, m_ItemOptionEx);
#else
			Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption,3);
#endif
			return TRUE;
		}
	}
	else if (m_Durability < m_DurabilityState[0])
	{
		if (m_CurrentDurabilityState != 0.2f)
		{
			m_CurrentDurabilityState = 0.2f;
#ifdef ADD_380ITEM_NEWOPTION_20060711
			Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption, m_ItemOptionEx);
#else
			Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption,3);
#endif
			return TRUE;
		}
	}
	else
	{
		if (m_CurrentDurabilityState != 0)
		{
			m_CurrentDurabilityState = 0.f;
#ifdef ADD_380ITEM_NEWOPTION_20060711
			Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption, m_ItemOptionEx);
#else
			Convert(m_Type, m_Option1, m_Option2, m_Option3, m_NewOption, m_SetOption,3);
#endif
			return TRUE;
		}
	}
	return FALSE;
}


#ifdef ADD_ITEM_SOCKET_OPTION_SYSTEM_20080415
// 소켓 슬롯이 남아있는 아이템인지 확인
bool CItem::IsEnableSetSocketItem()
{
	for (int i = 0; i < MAX_SOCKET_SLOT; i++)
	{
		if (m_SocketOption[i] == SOCKETSLOT_EMPTY)
		{
			return true;
		}
	}

	return false;
}

// 시드스피어를 소켓에 적용
bool CItem::SetSeedSphere(BYTE SlotIndex, BYTE SeedIndex, BYTE SphereLevel)
{
	BYTE SeedSphereIndex = 0;

	if (SlotIndex < 0 || SlotIndex >= MAX_SOCKET_SLOT)
	{
		return false;
	}

	// 시드스피어의 인덱스 = 시드인덱스 + ( 스피어레벨 * 50 )
	SeedSphereIndex = (SphereLevel * 50) + SeedIndex;

	if (m_SocketOption[SlotIndex] != SOCKETSLOT_NONE && m_SocketOption[SlotIndex] == SOCKETSLOT_EMPTY)
	{
		m_SocketOption[SlotIndex] = SeedSphereIndex;
		return true;
	}

	return false;
}

// 시드스피어를 소켓에서 삭제
bool CItem::RemoveSeedSphere(BYTE SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= MAX_SOCKET_SLOT)
	{
		return false;
	}

	if (m_SocketOption[SlotIndex] != SOCKETSLOT_NONE && m_SocketOption[SlotIndex] != SOCKETSLOT_EMPTY)
	{
		m_SocketOption[SlotIndex] = SOCKETSLOT_EMPTY;
		return true;
	}

	return false;
}

// 소켓 슬롯을 생성
void CItem::MakeSocketSlot(BYTE SlotCount)
{
#ifndef CHARACTERDB_SERVER
	if (g_SocketOptionSystem.IsEnableSocketItem(this) == false)
	{
		return;
	}

	for (int i = 0; i < SlotCount; i++)
	{
		m_SocketOption[i] = SOCKETSLOT_EMPTY;
	}

#ifdef MODIFY_SEASON4_UPDATE_BUGFIX_02_20080804
	m_BonusSocketOption = SOCKETSLOT_NONE;
#endif // MODIFY_SEASON4_UPDATE_BUGFIX_02_20080804
#endif
}

#endif // ADD_ITEM_SOCKET_OPTION_SYSTEM_20080415


//-----------------------------------------------------------------------------

void BufferItemtoConvert3(LPBYTE buf, int & type, BYTE& level, BYTE & op1, BYTE & op2, BYTE & op3, BYTE & dur)
{
#ifdef ITEM_INDEX_EXTEND_20050706
	type = buf[0] + ((buf[3] & 0x80) << 1) + ((buf[5] & 0xF0) << 5);
#else
	type = buf[0] + (((buf[3] & 0x80) >> 7) * 256);
#endif	
	level = (buf[1] >> 3) & 0xF;
	op1 = (buf[1] >> 7) & 0x01;
	op2 = (buf[1] >> 2) & 0x01;
	op3 = (buf[1] & 0x03);
	dur = buf[2];

	if (type == MAKE_ITEMNUM(13, 3))
	{
		op3 |= (buf[3] & 0x40) >> 4;
	}
	else
	{
		if ((buf[3] & 0x40) == 0x40)
		{
			op3 += 4;
		}
	}
}

//----------------------------------------------------------------------------
// 아이템 정보를 7바이트 정보로 바꾼다.
//----------------------------------------------------------------------------
void ItemByteConvert7(LPBYTE buf, CItem item[], int maxitem)
{
	int n = 0;
	WORD hiWord, loWord;


	// type / index, Level, Dur, Special, Number
	//   4  ,   4  ,   5,   3,    8        4Byte
	for (int index = 0; index<maxitem; index++)
	{
		buf[n] = (BYTE)item[index].m_Type;				// Type       : 4bit
		n++;

		buf[n] = 0;
		buf[n] |= item[index].m_Level << 3;		// Level	: 5bit
		buf[n] |= item[index].m_Option1 << 7;		// Option 1 : 1bit
		buf[n] |= item[index].m_Option2 << 2;		// Option 2 : 1bit
		buf[n] |= item[index].m_Option3;			// Option 3 : 2bit

		n++;
		buf[n] = (BYTE)item[index].m_Durability;			// Durability : 8bit
		n++;

		hiWord = HIWORD(item[index].m_Number);
		loWord = LOWORD(item[index].m_Number);

		buf[n] = HIBYTE(hiWord);
		n++;
		buf[n] = LOBYTE(hiWord);
		n++;
		buf[n] = HIBYTE(loWord);
		n++;
		buf[n] = LOBYTE(loWord);
		n++;
	}
}



//----------------------------------------------------------------------------
// 아이템 정보를 10 바이트 정보로 바꾼다.
//----------------------------------------------------------------------------
void ItemByteConvert10(LPBYTE buf, CItem item[], int maxitem)
{
	int n = 0;
	WORD hiWord, loWord;


	// type / index, Level, Dur, Special, Number, extension
	//   4  ,   4  ,   5,   3,    8        4Byte,   3Byte
	for (int index = 0; index<maxitem; index++)
	{
#ifdef FOR_BLOODCASTLE
		if (item[index].m_Type == MAKE_ITEMNUM(13, 19))
		{		// DB에 저장하기 전에 항상 대천사 시리즈를 확인하고 존재한다면 저장대상에서 재외함.
			if (CHECK_LIMIT(item[index].m_Level, 3))
			{
				buf[n] = 255;
				buf[n + 1] = 255;
				buf[n + 2] = 255;
				buf[n + 3] = 255;
				buf[n + 4] = 255;
				buf[n + 5] = 255;
				buf[n + 6] = 255;
				buf[n + 7] = 255;
				buf[n + 8] = 255;
				buf[n + 9] = 255;
				n += MAX_ITEMDBBYTE;
				continue;
			}
		}
#endif

		if (item[index].m_Type < 0)
		{
			buf[n] = 255;
			buf[n + 1] = 255;
			buf[n + 2] = 255;
			buf[n + 3] = 255;
			buf[n + 4] = 255;
			buf[n + 5] = 255;
			buf[n + 6] = 255;
			buf[n + 7] = 255;
			buf[n + 8] = 255;
			buf[n + 9] = 255;
			n += MAX_ITEMDBBYTE;
		}
		else
		{
			buf[n] = (BYTE)item[index].m_Type % 256;				// Type       : 4bit

			n++;

			buf[n] = 0;
			buf[n] |= item[index].m_Level << 3;		// Level	: 5bit
			buf[n] |= item[index].m_Option1 << 7;		// Option 1 : 1bit
			buf[n] |= item[index].m_Option2 << 2;		// Option 2 : 1bit
			buf[n] |= (item[index].m_Option3 & 0x03);	// Option 3 : 2bit

			n++;
			buf[n] = (BYTE)item[index].m_Durability;			// Durability : 8bit
			n++;

			hiWord = HIWORD(item[index].m_Number);
			loWord = LOWORD(item[index].m_Number);

			buf[n] = HIBYTE(hiWord);
			n++;
			buf[n] = LOBYTE(hiWord);
			n++;
			buf[n] = HIBYTE(loWord);
			n++;
			buf[n] = LOBYTE(loWord);
			n++;

			buf[n] = 0;
			if (item[index].m_Type > 255) buf[n] = 128;
			if (item[index].m_Option3 > 3) buf[n] |= 64;
			buf[n] |= item[index].m_NewOption;
			n++;
#if GAME_VERSION >= G_V_99B
			buf[n] = item[index].m_SetOption;
#endif
			n++;
			n++;
		}
	}
}


//----------------------------------------------------------------------------
// 아이템 정보를 N바이트 정보로 바꾼다. -> 클라이언트에 보내는 아이템 형식 
// (DB버전 0x03:7바이트 - 20050721)
//----------------------------------------------------------------------------
void ItemByteConvert(LPBYTE buf, CItem item)
{
	int n = 0;

#ifdef ITEM_INDEX_EXTEND_20050706
	memset(buf, 0, ITEM_BUFFER_SIZE);
#endif

#ifdef ITEM_INDEX_EXTEND_20050706
	buf[n] = (BYTE)(item.m_Type & 0x00FF);		// [0]	아이템 번호 : 1 ~ 8번째 bit까지
#else
	buf[n] = (BYTE)item.m_Type % 256;
#endif
	n++;

	buf[n] = 0;
	buf[n] |= item.m_Level << 3;					// [1]	Level		: 5bit
	buf[n] |= item.m_Option1 << 7;				// [1]	Option 1	: 1bit
	buf[n] |= item.m_Option2 << 2;				// [1]	Option 2	: 1bit
	buf[n] |= item.m_Option3 & 0x03;				// [1]	Option 3	: 2bit

	n++;
	buf[n] = (BYTE)item.m_Durability;			// [2]	Durability	: 8bit
	n++;
	buf[n] = 0;
#ifdef ITEM_INDEX_EXTEND_20050706
	buf[n] |= (BYTE)((item.m_Type & 0x0100) >> 1);	// [3]	아이템 번호 : 9번째 bit
#else
	if (item.m_Type>255)
		buf[n] = 0x80;
#endif
	if (item.m_Option3 > 3)
		buf[n] |= 0x40;							// [3]	Option 3 16옵 처리
	buf[n] |= item.m_NewOption;					// [3]	액설런트 옵션

	n++;
#if GAME_VERSION >= G_V_99B
	buf[n] = item.m_SetOption;					// [4]	세트 옵션 
#endif

#ifdef ITEM_INDEX_EXTEND_20050706
	n++;
	buf[n] |= (BYTE)((item.m_Type & 0x1E00) >> 5);	// [5]	아이템 번호 : 10 ~ 13번째 bit까지

#ifdef ADD_380ITEM_NEWOPTION_20060711
	BYTE btItemEffeftFor380 = 0;
	// 380 아이템 추가 옵션 : m_ItemOptionEx의 상위 1 bit 값
	// [5] 버퍼의 상위 5 번째 값에 설정
	btItemEffeftFor380 = (item.m_ItemOptionEx & 0x80) >> 4;   // 값이 8이됨.
	buf[n] |= btItemEffeftFor380;
#endif // ADD_380ITEM_NEWOPTION_20060711

	n++;

#ifdef ADD_JEWEL_OF_HARMONY_SYSTEM_20060530
	buf[n] = item.m_JewelOfHarmonyOption;		// [6] 조화의보석 강화 옵션 : 1바이트
												// 버퍼 모두 사용
#else
	// 예비 바이트								// [6] 예비 바이트 
#endif // ADD_JEWEL_OF_HARMONY_SYSTEM_20060530
#ifndef CHARACTERDB_SERVER
#ifdef ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
#ifdef MODIFY_ITEM_SOCKET_OPTION_BUGFIX_02_20080630
	if (g_SocketOptionSystem.IsSocketItem(&item) == true)
#else
	if (g_SocketOptionSystem.IsEnableSocketItem(&item) == true)
#endif // MODIFY_ITEM_SOCKET_OPTION_BUGFIX_02_20080630
	{
		buf[n] = item.m_BonusSocketOption;		// [6] 보너스 소켓 옵션 : 1바이트
												// 소켓 아이템 일 경우 조화의 보석 옵션을 사용하지 않는다.
	}
	// 소켓 아이템 데이터를 입력한다.			// [7] ~ [11] : 소켓 아이템 정보
	n++;
	buf[n] = item.m_SocketOption[0];
	n++;
	buf[n] = item.m_SocketOption[1];
	n++;
	buf[n] = item.m_SocketOption[2];
	n++;
	buf[n] = item.m_SocketOption[3];
	n++;
	buf[n] = item.m_SocketOption[4];
#endif // ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
#endif
#endif	
}


//----------------------------------------------------------------------------
// 아이템 정보를 N바이트 정보로 바꾼다. -> 클라이언트에 보내는 아이템 형식 
// (DB버전 0x03:7바이트 - 20050721)
//----------------------------------------------------------------------------
#ifdef ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
void ItemByteConvert(LPBYTE buf, int type, BYTE Option1, BYTE Option2, BYTE Option3, BYTE level, BYTE dur, BYTE Noption, BYTE SetOption, BYTE JewelOfHarmonyOption, BYTE ItemEffectEx, BYTE SocketOption[], BYTE SocketBonusOption)
#else

#ifdef ADD_JEWEL_OF_HARMONY_SYSTEM_20060530
#ifdef ADD_380ITEM_NEWOPTION_20060711
void ItemByteConvert(LPBYTE buf, int type, BYTE Option1, BYTE Option2, BYTE Option3, BYTE level, BYTE dur, BYTE Noption, BYTE SetOption, BYTE JewelOfHarmonyOption, BYTE ItemEffectEx)
#else
void ItemByteConvert(LPBYTE buf, int type, BYTE Option1, BYTE Option2, BYTE Option3, BYTE level, BYTE dur, BYTE Noption, BYTE SetOption, BYTE JewelOfHarmonyOption)
#endif // ADD_380ITEM_NEWOPTION_20060711
#else
#ifdef ADD_380ITEM_NEWOPTION_20060711
void ItemByteConvert(LPBYTE buf, int type, BYTE Option1, BYTE Option2, BYTE Option3, BYTE level, BYTE dur, BYTE Noption, BYTE SetOption, BYTE ItemEffectEx)
#else
void ItemByteConvert(LPBYTE buf, int type, BYTE Option1, BYTE Option2, BYTE Option3, BYTE level, BYTE dur, BYTE Noption, BYTE SetOption)
#endif // ADD_380ITEM_NEWOPTION_20060711
#endif // ADD_JEWEL_OF_HARMONY_SYSTEM_20060530
#endif // ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
{

	// 20051114 초기화코드 넣음.
#ifdef ITEM_INDEX_EXTEND_20050706
	memset(buf, 0, ITEM_BUFFER_SIZE);
#endif

	int n = 0;

#ifdef ITEM_INDEX_EXTEND_20050706
	buf[n] = (BYTE)(type & 0x00FF);			// [0]	아이템 번호 : 1 ~ 8번째 bit까지
#else
	buf[n] = (BYTE)type % 256;				// Type       : 4bit
#endif
	n++;
	buf[n] = 0;
	buf[n] |= level << 3;						// [1]	Level		: 5bit
	buf[n] |= Option1 << 7;					// [1]	Option 1	: 1bit
	buf[n] |= Option2 << 2;					// [1]	Option 2	: 1bit
	buf[n] |= Option3 & 0x03;					// [1]	Option 3	: 2bit
	n++;
	buf[n] = (BYTE)dur;						// [2]	Durability	: 8bit
	n++;
	buf[n] = 0;

#ifdef ITEM_INDEX_EXTEND_20050706
	buf[n] |= (BYTE)((type & 0x0100) >> 1);		// [3]	아이템 번호 : 9번째 bit
#else
	if (type>255)
		buf[n] = 0x80;
#endif

	if (Option3 > 3)
		buf[n] |= 64;						// [3]	Option 3 16옵 처리
	buf[n] |= Noption;						// [3]	액설런트 옵션

	n++;
#if GAME_VERSION >= G_V_99B
	buf[n] = SetOption;						// [4]	세트 옵션 
#endif

#ifdef ITEM_INDEX_EXTEND_20050706
	n++;
	buf[n] |= (BYTE)((type & 0x1E00) >> 5);		// [5]	아이템 번호 : 10 ~ 13번째 bit까지

#ifdef ADD_380ITEM_NEWOPTION_20060711
	BYTE btItemEffeftFor380 = 0;
	// 380 아이템 추가 옵션 : m_ItemOptionEx의 상위 1 bit 값
	// [5] 버퍼의 상위 5 번째 값에 설정
	btItemEffeftFor380 = (ItemEffectEx & 0x80) >> 4;   // 값이 8이됨.
	buf[n] |= btItemEffeftFor380;
#endif // ADD_380ITEM_NEWOPTION_20060711

	n++;

#ifdef ADD_JEWEL_OF_HARMONY_SYSTEM_20060530
	buf[n] = JewelOfHarmonyOption;				// [6] 조화의보석 강화 옵션 : 1바이트
												// 버퍼 모두 사용
#else
	// 예비 바이트								// [6] 예비 바이트 
#endif // ADD_JEWEL_OF_HARMONY_SYSTEM_20060530	
#endif	

#ifdef ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
	if (SocketOption != NULL)
	{
		buf[n] = SocketBonusOption;				// [6] 보너스 소켓 옵션 : 1바이트
												// 소켓 아이템일 경우 조화의 옵션 대신 보너스 소켓 옵션이 들어간다.
		n++;
		buf[n] = SocketOption[0];				// [7] 소켓 옵션 : 1바이트
		n++;
		buf[n] = SocketOption[1];				// [8] 소켓 옵션 : 1바이트
		n++;
		buf[n] = SocketOption[2];				// [9] 소켓 옵션 : 1바이트
		n++;
		buf[n] = SocketOption[3];				// [10] 소켓 옵션 : 1바이트
		n++;
		buf[n] = SocketOption[4];				// [11] 소켓 옵션 : 1바이트
	}
	else
	{
		n++;
		buf[n] = SOCKETSLOT_NONE;
		n++;
		buf[n] = SOCKETSLOT_NONE;
		n++;
		buf[n] = SOCKETSLOT_NONE;
		n++;
		buf[n] = SOCKETSLOT_NONE;
		n++;
		buf[n] = SOCKETSLOT_NONE;
	}
#endif // ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
}


#ifdef ITEM_DBSIZE_EXTEND_20050706

//----------------------------------------------------------------------------
// 아이템 정보를 16 바이트 정보로 바꾼다.
//----------------------------------------------------------------------------
void ItemByteConvert16(LPBYTE buf, CItem item[], int maxitem)
{
	unsigned __int16 hiWord;
	unsigned __int16 loWord;
	BOOL v7;
	BYTE btItemIndexEx;

	int n = 0;

	for (int index = 0; index < maxitem; ++index)
	{
		if (item[index].m_Type == 6675 && (item[index].m_Level >= 0 ? (v7 = item[index].m_Level <= 2) : (v7 = 0), v7))
		{
			buf[n] = -1;
			buf[n + 1] = -1;
			buf[n + 2] = -1;
			buf[n + 3] = -1;
			buf[n + 4] = -1;
			buf[n + 5] = -1;
			buf[n + 6] = -1;
			buf[n + 7] = -1;
			buf[n + 8] = -1;
			buf[n + 9] = -1;
			buf[n + 10] = -1;
			buf[n + 11] = -1;
			buf[n + 12] = -1;
			buf[n + 13] = -1;
			buf[n + 14] = -1;
			buf[n + 15] = -1;
			n += MAX_ITEMDBBYTE;
		}
		else if (item[index].m_Type >= 0)
		{
			memset(&buf[n], 0, 0x10u);
			buf[n] = item[index].m_Type;
			int v3 = n + 1;
			buf[v3] = 0;
			buf[v3] |= 8 * item[index].m_Level;
			buf[v3] |= item[index].m_Option1 << 7;
			buf[v3] |= 4 * item[index].m_Option2;
			buf[v3] |= item[index].m_Option3 & 3;
			buf[++v3] = item[index].m_Durability;
			++v3;
			hiWord = item[index].m_Number >> MAX_ITEMDBBYTE;
			loWord = item[index].m_Number;
			buf[v3++] = item[index].m_Number >> 24;
			buf[v3++] = hiWord;
			buf[v3++] = HIBYTE(loWord);
			buf[v3] = loWord;
			int na = v3 + 1;
			buf[na] = 0;
			btItemIndexEx = (item[index].m_Type & 0x1E00) >> 5;
			buf[na] |= (item[index].m_Type & 0x100) >> 1;
			if (item[index].m_Option3 > 3)
				buf[na] |= 0x40u;
			buf[na] |= item[index].m_NewOption;
			int v6 = na + 1;
			buf[v6++] = item[index].m_SetOption;
			buf[v6] = 0;
			buf[v6] |= btItemIndexEx;
			buf[++v6] = 0;
			buf[++v6] = -1;
			buf[++v6] = -1;
			buf[++v6] = -1;
			buf[++v6] = -1;
			buf[++v6] = -1;
			n = v6 + 1;
		}
		else
		{
			buf[n] = -1;
			buf[n + 1] = -1;
			buf[n + 2] = -1;
			buf[n + 3] = -1;
			buf[n + 4] = -1;
			buf[n + 5] = -1;
			buf[n + 6] = -1;
			buf[n + 7] = -1;
			buf[n + 8] = -1;
			buf[n + 9] = -1;
			buf[n + 10] = -1;
			buf[n + 11] = -1;
			buf[n + 12] = -1;
			buf[n + 13] = -1;
			buf[n + 14] = -1;
			buf[n + 15] = -1;
			n += MAX_ITEMDBBYTE;
		}
	}
}
//void ItemByteConvert16(LPBYTE buf, CItem item[], int maxitem)
//{
//	int n = 0;
//	WORD hiWord, loWord;
//
//	// type / index, Level, Dur, Special, Number, extension
//	//   4  ,   4  ,   5,   3,    8        4Byte,   3Byte
//	for (int index = 0; index<maxitem; index++)
//	{
//#ifdef FOR_BLOODCASTLE
//		if (item[index].m_Type == MAKE_ITEMNUM(13, 19))
//		{
//			// DB에 저장하기 전에 항상 대천사 시리즈를 확인하고 존재한다면 저장대상에서 재외함.
//			if (CHECK_LIMIT(item[index].m_Level, 3))
//			{
//				buf[n] = 255;
//				buf[n + 1] = 255;
//				buf[n + 2] = 255;
//				buf[n + 3] = 255;
//				buf[n + 4] = 255;
//				buf[n + 5] = 255;
//				buf[n + 6] = 255;
//				buf[n + 7] = 255;
//				buf[n + 8] = 255;
//				buf[n + 9] = 255;
//				buf[n + 10] = 255;
//				buf[n + 11] = 255;
//				buf[n + 12] = 255;
//				buf[n + 13] = 255;
//				buf[n + 14] = 255;
//				buf[n + 15] = 255;
//				n += MAX_ITEMDBBYTE;
//				continue;
//			}
//		}
//#endif
//
//#ifdef MODIFY_ILLUSIONTEMPLE_BUGFIX_2_20070724	// DB에 저장하기 전에 성물이 있으면 저장대상에서 재외
//		if (item[index].m_Type == MAKE_ITEMNUM(14, 64))
//		{
//			buf[n] = 255;
//			buf[n + 1] = 255;
//			buf[n + 2] = 255;
//			buf[n + 3] = 255;
//			buf[n + 4] = 255;
//			buf[n + 5] = 255;
//			buf[n + 6] = 255;
//			buf[n + 7] = 255;
//			buf[n + 8] = 255;
//			buf[n + 9] = 255;
//			buf[n + 10] = 255;
//			buf[n + 11] = 255;
//			buf[n + 12] = 255;
//			buf[n + 13] = 255;
//			buf[n + 14] = 255;
//			buf[n + 15] = 255;
//			n += MAX_ITEMDBBYTE;
//			continue;
//		}
//#endif
//
//		if (item[index].m_Type < 0)
//		{
//			buf[n] = 255;
//			buf[n + 1] = 255;
//			buf[n + 2] = 255;
//			buf[n + 3] = 255;
//			buf[n + 4] = 255;
//			buf[n + 5] = 255;
//			buf[n + 6] = 255;
//			buf[n + 7] = 255;
//			buf[n + 8] = 255;
//			buf[n + 9] = 255;
//			buf[n + 10] = 255;
//			buf[n + 11] = 255;
//			buf[n + 12] = 255;
//			buf[n + 13] = 255;
//			buf[n + 14] = 255;
//			buf[n + 15] = 255;
//			n += MAX_ITEMDBBYTE;
//		}
//		else
//		{
//#ifdef ITEM_INDEX_EXTEND_20050706
//			memset(&buf[n], 0, MAX_ITEMDBBYTE);
//#endif
//
//			buf[n] = (BYTE)item[index].m_Type % 256;	// [0]			
//														// Type       : 4bit
//
//			n++;
//
//			buf[n] = 0;								// [1]
//			buf[n] |= item[index].m_Level << 3;		// Level	: 5bit
//			buf[n] |= item[index].m_Option1 << 7;		// Option 1 : 1bit
//			buf[n] |= item[index].m_Option2 << 2;		// Option 2 : 1bit
//			buf[n] |= (item[index].m_Option3 & 0x03);	// Option 3 : 2bit
//
//			n++;
//			buf[n] = (BYTE)item[index].m_Durability;// [2] 내구도		
//													// Durability : 8bit
//			n++;
//
//			hiWord = HIWORD(item[index].m_Number);	// [3] 아이템 시리얼 
//			loWord = LOWORD(item[index].m_Number);
//
//			buf[n] = HIBYTE(hiWord);
//			n++;
//			buf[n] = LOBYTE(hiWord);				// [4] 아이템 시리얼
//			n++;
//			buf[n] = HIBYTE(loWord);				// [5] 아이템 시리얼
//			n++;
//			buf[n] = LOBYTE(loWord);				// [6] 아이템 시리얼
//			n++;
//
//			buf[n] = 0;								// [7] 아이템 번호 : 9번째 bit
//													// [7] 아이템 16옵션 처리
//													// [7] 엑설런트 아이템 옵션
//
//#ifdef ITEM_INDEX_EXTEND_20050706
//			BYTE btItemIndexEx = 0;
//			btItemIndexEx |= (BYTE)((item[index].m_Type & 0x1E00) >> 5);	// 신규 확장 4비트
//			buf[n] |= (BYTE)((item[index].m_Type & 0x0100) >> 1);			// 기존 확장 1비트
//#else
//			if (item[index].m_Type > 255) buf[n] = 128;
//#endif
//			if (item[index].m_Option3 > 3) buf[n] |= 64;
//			buf[n] |= item[index].m_NewOption;
//			n++;
//
//			buf[n] = item[index].m_SetOption;		// [8] 세트아이템 옵션
//
//			n++;
//
//#ifdef ITEM_INDEX_EXTEND_20050706
//			buf[n] = 0;								// [9] 아이템 번호 : 10 ~ 13번째 bit까지
//			buf[n] |= btItemIndexEx;
//#endif			
//
//#ifdef ADD_380ITEM_NEWOPTION_20060711
//			BYTE btItemEffeftFor380 = 0;
//			// 380 아이템 추가 옵션 : m_ItemOptionEx의 상위 1 bit 값
//			// [9] 버퍼의 상위 5 번째 값에 설정
//			btItemEffeftFor380 = (item[index].m_ItemOptionEx & 0x80) >> 4;   // 값이 8이됨.
//			buf[n] |= btItemEffeftFor380;
//#endif
//
//			n++;
//
//#ifdef ADD_JEWEL_OF_HARMONY_SYSTEM_20060530
//#ifdef MODIFY_HARMONY_OPTION_INIT_VALUE_FIX_20061019
//			if (item[index].m_JewelOfHarmonyOption == 0xFF)
//			{
//				// 조화의 보석 옵션이 0xFF(잘못된 초기값)일 경우 0x00으로 강제로 설정한다.
//				item[index].m_JewelOfHarmonyOption = 0x00;
//			}
//#endif // MODIFY_HARMONY_OPTION_INIT_VALUE_FIX_20061019
//			buf[n] = item[index].m_JewelOfHarmonyOption;	// [10] 조화보석 옵셕 : 
//															// 4 Bit : 0 ~ 15. 강화 옵션 타입
//															// 4 Bit : 0 ~ 15.  강화 옵션 레벨
//#ifndef CHARACTERDB_SERVER
//#ifdef ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
//															// 소켓 아이템인 경우 조화옵션 대신 보너스 소켓 옵션을 사용한다.
//#ifdef MODIFY_ITEM_SOCKET_OPTION_BUGFIX_02_20080630
//			if (g_SocketOptionSystem.IsSocketItem(&item[index]) == true)
//#else
//			if (g_SocketOptionSystem.IsEnableSocketItem(&item[index]) == true)
//#endif // MODIFY_ITEM_SOCKET_OPTION_BUGFIX_02_20080630
//			{
//				buf[n] = item[index].m_BonusSocketOption;	// [10] 보너스 소켓 옵션 : 소켓 아이템일 경우만
//			}
//#endif // ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
//#endif
//			n++;
//
//#ifndef ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
//			n += 5;											// 예약 바이트는 필요할때 마다 하나씩 사용하면 된다.
//#endif // ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
//#else
//			n += 6;											// 예약 바이트는 필요할때 마다 하나씩 사용하면 된다.
//#endif // ADD_JEWEL_OF_HARMONY_SYSTEM_20060530
//
//#ifdef ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
//															// 예비 바이트 전부를 사용
//															// 소켓 아이템 데이터를 입력한다.
//			buf[n] = item[index].m_SocketOption[0];			// [11] : 소켓 옵션 1번째 슬롯
//			n++;
//			buf[n] = item[index].m_SocketOption[1];			// [12] : 소켓 옵션 2번째 슬롯
//			n++;
//			buf[n] = item[index].m_SocketOption[2];			// [13] : 소켓 옵션 3번째 슬롯
//			n++;
//			buf[n] = item[index].m_SocketOption[3];			// [14] : 소켓 옵션 4번째 슬롯
//			n++;
//			buf[n] = item[index].m_SocketOption[4];			// [15] : 소켓 옵션 5번째 슬롯
//			n++;
//#endif // ADD_ITEM_SOCKET_OPTION_EXTEND_20080422
//		}
//	}
//}

#endif


//----------------------------------------------------------------------------
// type,과 index로 아이템 정보를 구한다.
// 최종적으로 실제 인덱스를 만들어 낸다...
// 아이템이 존재하는지도 알수있다.
int ItemGetNumberMake(int type, int index)
{
	int make;

	make = (type*MAX_ITEM_INDEX) + index;
	if (ItemAttribute[make].Width < 1 || ItemAttribute[make].Height < 1)
	{
		return -1;
	}
	return make;
}

//----------------------------------------------------------------------------
// 인덱스를 넣어주면 아이템의 가로와 세로 크기를 얻을수있다.
void ItemGetSize(int index, int & width, int & height)
{
	width = ItemAttribute[index].Width;
	height = ItemAttribute[index].Height;
}


BOOL HasItemDurability(int index)
{
	if (ItemAttribute[index].Durability == 0 && ItemAttribute[index].MagicDurability == 0)
	{
		return FALSE;
	}
	return TRUE;
}

int ItemGetDurability(int index, int itemLevel, int ExcellentItem, int SetItem)
{

#ifdef MU_CASTLESIEGE_CS_MARKS_20041214	
	if (index == MAKE_ITEMNUM(14, 21) && itemLevel == 3)
	{
		// 성주의 표식 (레나 +3) 은 내구력이 최소 1 임 -> 레벨 수정
		itemLevel = 0;
	}
#endif

#ifdef HIDDEN_KALIMA_20050706	// 쿤둔의 표식은 기본 내구력이 1 이다.
	if (index == MAKE_ITEMNUM(14, 29))
	{
		return 1;
	}
#endif

#ifdef UPDATE_LUCKY_COIN_EVENT_20081029	// 행운의 동전 기본 내구력은 1
	if (index == MAKE_ITEMNUM(14, 100))
	{
		return 1;
	}
#endif // UPDATE_LUCKY_COIN_EVENT_20081029

	int dur = 0;

	// 엑설런트 아이템 이면	
	if (itemLevel < 5)
	{
		dur = ItemAttribute[index].Durability + itemLevel;
	}
	else if (itemLevel >= 5)
	{
		if (itemLevel == 10)
		{
			dur = ItemAttribute[index].Durability + (itemLevel * 2) - 3;
		}
		else if (itemLevel == 11)
		{
			dur = ItemAttribute[index].Durability + (itemLevel * 2) - 1;
		}
#ifdef ITEM_12_13_20040401
		else if (itemLevel == 12)
		{
			dur = ItemAttribute[index].Durability + (itemLevel * 2) - 4 + 1 + 2 + 3;
		}
		else if (itemLevel == 13)
		{
			dur = ItemAttribute[index].Durability + (itemLevel * 2) - 4 + 1 + 2 + 3 + 4;
		}
#endif
		else
		{
			dur = ItemAttribute[index].Durability + (itemLevel * 2) - 4;
		}
	}

#ifdef ADD_EVENT_MAP_ILLUSION_TEMPLE_20070328	//피의 두루마리는 내구도 1
	if (index == MAKE_ITEMNUM(13, 51))	//피의 두루마리는 내구도 1
	{
		dur = 1;
	}
#endif

	if ((index<ITEM_WING + 3 || index>ITEM_WING + 6) &&
		index != MAKE_ITEMNUM(0, 19) &&
		index != MAKE_ITEMNUM(4, 18) &&
		index != MAKE_ITEMNUM(5, 10)
#ifdef ADD_WEAPON_OF_ARCHANGEL_SCEPTER_20050706
		&& index != MAKE_ITEMNUM(2, 13)
#endif
#ifdef MODIFY_UPGRADE_DARKLORDMANTLE_20060515
		&& index != MAKE_ITEMNUM(13, 30)	// 군주의 망토 : 엑설런트 처리 없음
#endif		
#ifdef ADD_THIRD_WING_20070525	// 3차날개는 엑설런트 처리 없음
		&& index != MAKE_ITEMNUM(12, 36)
		&& index != MAKE_ITEMNUM(12, 37)
		&& index != MAKE_ITEMNUM(12, 38)
		&& index != MAKE_ITEMNUM(12, 39)
		&& index != MAKE_ITEMNUM(12, 40)
#endif
#ifdef ADD_SUMMONER_SECOND_THIRD_WING_20071130	// 신규캐릭터 재앙의 날개, 절망의 날개, 차원의 날개는 엑설런트 처리 없음
		&& index != MAKE_ITEMNUM(12, 41)
		&& index != MAKE_ITEMNUM(12, 42)
		&& index != MAKE_ITEMNUM(12, 43)
#endif
		) // 추가 날개 및 절대 아이템은 엑설런트 처리 없음
	{

		if (SetItem)
		{
			dur += 20;
		}
		else
			if (ExcellentItem)
			{
				dur += 15;
			}
	}

#ifdef MODIFY_EXCELLENT_DROP_DURATION_BUG_20060524
	// Dur값은 BYTE형으로 255를 넘어갈 수 없다. OverFlow 방지.
	if (dur > 255)
		dur = 255;
#endif // MODIFY_EXCELLENT_DROP_DURATION_BUG_20060524

	return dur;
}

int ItemGetAttackDurability(int index)
{
	return ItemAttribute[index].AttackDur;
}

int ItemGetDefenseDurability(int index)
{
	return ItemAttribute[index].DefenceDur;
}

inline float	GetRepairItemRate(int index)
{
	return ItemAttribute[index].RepaireMoneyRate;
}

inline float	GetAllRepairItemRate(int index)
{
	return ItemAttribute[index].AllRepaireMoneyRate;
}

void CalRepairRate(int type, int index, ITEM_ATTRIBUTE *p)
{
	// 초기 설정시에는 아이템별로 다른 수리비용 비율을 가지고 있었지만 일괄적으로 적용되게 변했다
	// 나중에 또 어떻게 될지 모르기 때문에 주석만 달아 뒀다
	p->RepaireMoneyRate = 0.1f;
#ifdef MODIFY_CALREPAIRRATE_20090528
	p->AllRepaireMoneyRate = 1.4f;
#else
	p->AllRepaireMoneyRate = 0.4f;
#endif
	/*
	if(type>=0 && type<=6)
	{
	if( type == 4 )
	{	// 요정
	p->RepaireMoneyRate = 0.8f;
	p->AllRepaireMoneyRate = 0.4f;
	}
	else if( type == 5 )
	{	// 흑마법사
	p->RepaireMoneyRate = 0.8f;
	p->AllRepaireMoneyRate = 0.5f;
	}
	else
	{	// 나머지
	p->RepaireMoneyRate = 0.7f;
	p->AllRepaireMoneyRate = 0.3f;
	}
	return;
	}

	if(type>=7 && type<=11)
	{
	switch(index)
	{
	case 0:
	case 1:
	case 5:
	case 6:
	case 8:
	case 9:
	case 16:
	p->RepaireMoneyRate = 0.7f;
	p->AllRepaireMoneyRate = 0.4f;
	break;

	case 2:
	case 3:
	case 4:
	case 7:
	p->RepaireMoneyRate = 0.7f;
	p->AllRepaireMoneyRate = 0.6f;
	break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	p->RepaireMoneyRate = 0.8f;
	p->AllRepaireMoneyRate = 0.4f;
	break;
	case 15:
	p->RepaireMoneyRate = 0.9f;
	p->AllRepaireMoneyRate = 0.4f;
	break;
	}
	return;
	}
	*/
}

BOOL CItem::CheckExcOption(int iMinExcOption)
{
	int iCount = 0;

	for (int i = 0; i < 6; i++)
	{
		if (this->m_NewOption & (1 << i))
			iCount++;
	}

	return (iCount >= iMinExcOption);
}

//----------------------------------------------------------------------------
// 아이템 스크립트 데이터를 읽는다.
//----------------------------------------------------------------------------
//BOOL OpenItemScript(char *FileName)
//{
//	int loop_count;
//	if ((SMDFile = fopen(FileName, "r")) == NULL)
//		return FALSE;
//
//	memset(&ItemAttribute, 0, sizeof(ItemAttribute));
//	for (int n = 0; n<MAX_ITEM; n++)
//	{
//		ItemAttribute[n].Level = 0xFF;
//		ItemAttribute[n].RepaireMoneyRate = 0;
//		ItemAttribute[n].AllRepaireMoneyRate = 0;
//	}
//
//	SMDToken Token;
//	while (true)
//	{
//		Token = (*GetToken)();
//		if (Token == END) break;
//		if (Token == NUMBER)
//		{
//			int Type = (int)TokenNumber;
//			loop_count = 0;
//			while (true)
//			{
//				Token = (*GetToken)();
//				int Index = (int)TokenNumber;
//
//#ifdef ADD_RANDOM_RANGE_OF_ITEMINDEX_20050808
//				if (Type >= 0 && Type < MAX_ITEM_TYPE)
//				{
//					// 타입의 최대 인덱스를 기록한다.
//					if (g_MaxItemIndexOfEachItemType[Type] <= Index)
//						g_MaxItemIndexOfEachItemType[Type] = Index;
//				}
//#endif // ADD_RANDOM_RANGE_OF_ITEMINDEX_20050808
//
//				if (Token == NAME && strcmp("end", TokenString) == NULL) break;
//				ITEM_ATTRIBUTE *p = &ItemAttribute[Type*MAX_ITEM_INDEX + Index];
//
//				Token = (*GetToken)(); p->ItemSlot = (int)TokenNumber;
//				Token = (*GetToken)(); p->SkillType = (int)TokenNumber;
//
//				Token = (*GetToken)(); p->Width = (int)TokenNumber;
//				Token = (*GetToken)(); p->Height = (int)TokenNumber;
//				Token = (*GetToken)(); p->Serial = (int)TokenNumber;
//				Token = (*GetToken)(); p->OptionFlag = (int)TokenNumber;
//				Token = (*GetToken)(); p->MondownFlag = (int)TokenNumber;
//				Token = (*GetToken)(); strcpy(p->Name, TokenString);
//
//#if TESTSERVER == 1
//				char sztext[255];
//				wsprintf(sztext, "%d\t%s\n", MAKE_ITEMNUM(Type, Index), p->Name);
//				OutputDebugString(sztext);
//#endif
//
//				// ★ 무기, 지팡이류 
//				if (Type >= 0 && Type <= 5)
//				{
//
//					// 1. > 기본 정보
//					Token = (*GetToken)(); p->Level = (int)TokenNumber;
//					Token = (*GetToken)(); p->DamageMin = (int)TokenNumber;
//					Token = (*GetToken)(); p->DamageMax = (int)TokenNumber;
//					Token = (*GetToken)(); p->AttackSpeed = (int)TokenNumber;
//					Token = (*GetToken)(); p->Durability = (int)TokenNumber;
//
//
//					// 2. > 마법 정보 
//					Token = (*GetToken)(); p->MagicDurability = (int)TokenNumber;
//					Token = (*GetToken)(); p->MagicPW = (int)TokenNumber;
//
//					// 3. > 요구 레벨, 스탯 정보
//#ifdef EXPAND_ITEMSCRIPT_01_20050808 
//					Token = (*GetToken)(); p->RequireLevel = (int)TokenNumber; // 요구 레벨
//#else
//					Token = (*GetToken)();
//#endif
//					Token = (*GetToken)(); p->RequireStrength = (int)TokenNumber;	// 요구 힘
//					Token = (*GetToken)(); p->RequireDexterity = (int)TokenNumber;	// 요구 민첩
//					Token = (*GetToken)(); p->RequireEnergy = (int)TokenNumber;	// 요구 에너지
//
//#ifdef EXPAND_ITEMSCRIPT_01_20050808 
//					Token = (*GetToken)(); p->RequireVitality = (int)TokenNumber;	// 요구 레벨
//					Token = (*GetToken)(); p->RequireLeadership = (int)TokenNumber; // 요구 통솔
//#else
//					Token = (*GetToken)();
//					Token = (*GetToken)();
//#endif
//
//					// 4. > 부가 정보 세팅
//					if (p->Width >= 2) p->TwoHand = true;
//
//					// 마법 내구도와 물리 내구도는 같이 사용된다
//					p->Durability += p->MagicDurability;
//
//				}
//
//				// ★ 방패, 방어구류
//				if (Type >= 6 && Type <= 11)
//				{
//					// 1. > 기본 정보
//					Token = (*GetToken)(); p->Level = (int)TokenNumber;
//
//					if (Type == 6)
//					{
//						Token = (*GetToken)(); p->Defense = (int)TokenNumber;			// 방어
//						Token = (*GetToken)(); p->SuccessfulBlocking = (int)TokenNumber;		// 방어 성공률			
//					}
//
//					else if (Type >= 7 && Type <= 9)
//					{
//						Token = (*GetToken)(); p->Defense = (int)TokenNumber;
//						Token = (*GetToken)(); p->MagicDefense = (int)TokenNumber;
//					}
//					else if (Type == 10)
//					{
//						Token = (*GetToken)(); p->Defense = (int)TokenNumber;
//						Token = (*GetToken)(); p->AttackSpeed = (int)TokenNumber;
//					}
//					else if (Type == 11)
//					{
//						Token = (*GetToken)(); p->Defense = (int)TokenNumber;
//						Token = (*GetToken)(); p->WalkSpeed = (int)TokenNumber;
//					}
//					Token = (*GetToken)(); p->Durability = (int)TokenNumber;
//
//
//					// 2. > 요구 레벨, 스탯 정보
//
//#ifdef EXPAND_ITEMSCRIPT_01_20050808 
//					Token = (*GetToken)(); p->RequireLevel = (int)TokenNumber; // 요구 레벨
//#else
//					Token = (*GetToken)();
//#endif
//
//					Token = (*GetToken)(); p->RequireStrength = (int)TokenNumber;	// 요구 힘
//					Token = (*GetToken)(); p->RequireDexterity = (int)TokenNumber; // 요구 민첩
//
//#ifdef EXPAND_ITEMSCRIPT_01_20050808
//					Token = (*GetToken)(); p->RequireEnergy = (int)TokenNumber;	// 요구 에너지
//					Token = (*GetToken)(); p->RequireVitality = (int)TokenNumber;	// 요구 레벨
//					Token = (*GetToken)(); p->RequireLeadership = (int)TokenNumber; // 요구 통솔
//#else
//					if (Type == 6)
//					{
//						Token = (*GetToken)(); p->RequireEnergy = (int)TokenNumber;
//						Token = (*GetToken)();
//						Token = (*GetToken)();
//					}
//					else
//					{
//						Token = (*GetToken)();
//						Token = (*GetToken)();
//						Token = (*GetToken)();
//					}
//#endif
//
//				}
//
//				// ★ 헬퍼류, 목걸이, 반지, 뿔류, 깃털, 주문서 등
//				if (Type == 13)
//				{
//					Token = (*GetToken)(); p->Level = (int)TokenNumber;
//					Token = (*GetToken)(); p->Durability = (int)TokenNumber;
//					Token = (*GetToken)(); p->Resistance[0] = (int)TokenNumber;
//					Token = (*GetToken)(); p->Resistance[1] = (int)TokenNumber;
//					Token = (*GetToken)(); p->Resistance[2] = (int)TokenNumber;
//					Token = (*GetToken)(); p->Resistance[3] = (int)TokenNumber;
//
//					Token = (*GetToken)(); p->Resistance[4] = (int)TokenNumber;
//					Token = (*GetToken)(); p->Resistance[5] = (int)TokenNumber;
//					Token = (*GetToken)(); p->Resistance[6] = (int)TokenNumber;
//
//					p->ResistanceType = 0xFF;
//					for (int ResiIndex = 0; ResiIndex < 6; ResiIndex++)
//					{
//						if (p->Resistance[ResiIndex])
//							p->ResistanceType = ResiIndex;
//					}
//
//					// 목걸이, 반지의 경우 요구레벨을 아이템레벨 자체로 할당 해놨음..이런..
//					p->RequireLevel = p->Level;
//				}
//
//				// ★ 물약, 보석, 징표, 젠, 퀘스트 아이템 등
//				if (Type == 14)
//				{
//					Token = (*GetToken)(); p->Value = (int)TokenNumber;
//					Token = (*GetToken)(); p->Level = (int)TokenNumber;
//					//if( Index == 17 || Index == 18 )
//					//{	// 아이템에 내구도를 강제로 넣어준다(TESTSERVER1에서 사용된 아이템을 강제로 없애기 위해서)
//					// 악마의 눈, 열쇠
//					p->Durability = 1;
//					//}
//				}
//
//				// ★ 날개, 혼돈의보석, 스크롤, 축/영석 조합
//				if (Type == 12)
//				{
//					Token = (*GetToken)(); p->Level = (int)TokenNumber;
//					Token = (*GetToken)(); p->Defense = (int)TokenNumber;
//					Token = (*GetToken)(); p->Durability = (int)TokenNumber;
//					Token = (*GetToken)(); p->RequireLevel = (int)TokenNumber;
//					Token = (*GetToken)(); p->RequireEnergy = (int)TokenNumber;
//
//					Token = (*GetToken)(); p->RequireStrength = (int)TokenNumber;
//#ifdef NEW_FORSKYLAND2	// 구슬 요구 민첩 추가(20030731)					
//					Token = (*GetToken)(); p->RequireDexterity = (int)TokenNumber;
//#else
//					Token = (*GetToken)();
//#endif
//
//#ifdef DARKLORD_WORK // 다크 스피릿으로 인해 추가 					
//					Token = (*GetToken)(); p->RequireLeadership = (int)TokenNumber;
//#else
//					Token = (*GetToken)();
//#endif
//
//					Token = (*GetToken)(); p->BuyMoney = (int)TokenNumber;
//				}
//
//				// ★ 법서
//				if (Type == 15)
//				{
//					Token = (*GetToken)(); p->Level = (int)TokenNumber;
//
//#ifdef NEW_FORSKYLAND2	// 법서 요구 레벨 추가(20030725)(foguy)
//					Token = (*GetToken)(); p->RequireLevel = (int)TokenNumber;
//#else
//					Token = (*GetToken)();
//#endif
//
//					Token = (*GetToken)(); p->RequireEnergy = (int)TokenNumber;
//
//					Token = (*GetToken)(); p->BuyMoney = (int)TokenNumber;
//					p->DamageMin = p->Level;
//					p->DamageMax = p->Level + p->Level / 2;
//
//				}
//
//
//				// 세트 속성 추가
//				if (Type <= 11 || Type == 13)
//					Token = (*GetToken)(); p->SetAttr = (int)TokenNumber;
//
//				//사용 클래스
//				if (Type <= 13 || Type == 15)
//				{
//					Token = (*GetToken)(); p->RequireClass[0] = (int)TokenNumber;
//					Token = (*GetToken)(); p->RequireClass[1] = (int)TokenNumber;
//					Token = (*GetToken)(); p->RequireClass[2] = (int)TokenNumber;
//					Token = (*GetToken)(); p->RequireClass[3] = (int)TokenNumber;
//
//#ifdef DARKLORD_WORK	
//					// 다크로드
//					Token = (*GetToken)(); p->RequireClass[4] = (int)TokenNumber;
//#else
//					Token = (*GetToken)();
//#endif
//
//#ifdef ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912	// item 사용 클래스 추가
//					Token = (*GetToken)(); p->RequireClass[5] = (int)TokenNumber;
//#else
//					Token = (*GetToken)();
//#endif
//
//					Token = (*GetToken)(); //Rage Fighter Bypass
//				}
//
//				// 아이템 수리비용 비율을 설정한다
//				CalRepairRate(Type, Index, p);
//				p->HaveItemInfo = TRUE;
//
//				loop_count++;
//				if (loop_count > MAX_ITEM_INDEX)
//				{
//					MsgBox("Error : Item Data fail. (LoopCount:%d) Item Type:%d Index %d", loop_count, Type, Index);
//					break;
//				}
//			}
//			if (loop_count > MAX_ITEM_INDEX)
//			{
//				break;
//			}
//		}
//	}
//	fclose(SMDFile);
//	return TRUE;
//}
int OpenItemScript(char *FileName)
{
	int loop_count;
	SMDFile = fopen(FileName, "r");
	if (!SMDFile)
		return 0;

	memset(&ItemAttribute, 0, sizeof(ItemAttribute));
	for (int n = 0; n < MAX_ITEM; ++n)
	{
		ItemAttribute[n].Level = 0xFF;
		ItemAttribute[n].RepaireMoneyRate = 0.0;
		ItemAttribute[n].AllRepaireMoneyRate = 0.0;
	}

	SMDToken Token;
	while (true)
	{
		Token = Token = (*GetToken)();
		if (Token == END)
			break;
		if (Token == NUMBER)
		{
			int Type = (int)TokenNumber;
			loop_count = 0;
			while (true)
			{
				Token = (*GetToken)();
				int Index = (int)TokenNumber;

				if (Type >= 0 && Type < MAX_ITEM_TYPE && g_MaxItemIndexOfEachItemType[Type] <= Index)
					g_MaxItemIndexOfEachItemType[Type] = Index;

				if (Token == NAME && strcmp("end", TokenString) == NULL) break;
				ITEM_ATTRIBUTE *p = &ItemAttribute[Index + (Type << 9)];

				Token = (*GetToken)(); p->ItemSlot = (int)TokenNumber;
				Token = (*GetToken)(); p->SkillType = (int)TokenNumber;
				Token = (*GetToken)(); p->Width = (int)TokenNumber;
				Token = (*GetToken)();
				p->Height = (int)TokenNumber;
				Token = (*GetToken)();
				p->Serial = (int)TokenNumber;
				Token = (*GetToken)();
				p->OptionFlag = (int)TokenNumber;
				Token = (*GetToken)();
				p->MondownFlag = (int)TokenNumber;
				Token = (*GetToken)();
				strcpy(p->Name, TokenString);
				if (Type >= 0 && Type <= 5)
				{
					Token = (*GetToken)();
					p->Level = (int)TokenNumber;
					Token = (*GetToken)();
					p->DamageMin = (int)TokenNumber;
					Token = (*GetToken)();
					p->DamageMax = (int)TokenNumber;
					Token = (*GetToken)();
					p->AttackSpeed = (int)TokenNumber;
					Token = (*GetToken)();
					p->Durability = (int)TokenNumber;
					Token = (*GetToken)();
					p->MagicDurability = (int)TokenNumber;
					Token = (*GetToken)();
					p->MagicPW = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireLevel = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireStrength = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireDexterity = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireEnergy = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireVitality = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireLeadership = (int)TokenNumber;
					if (p->Width >= 2)p->TwoHand = true;
					p->Durability += p->MagicDurability;
				}
				if (Type >= 6 && Type <= 11)
				{
					Token = (*GetToken)();
					p->Level = (int)TokenNumber;
					if (Type == 6)
					{
						Token = (*GetToken)();
						p->Defense = (int)TokenNumber;
						Token = (*GetToken)();
						p->SuccessfulBlocking = (int)TokenNumber;
					}
					else if (Type < 7 || Type > 9)
					{
						if (Type == 10)
						{
							Token = (*GetToken)();
							p->Defense = (int)TokenNumber;
							Token = (*GetToken)();
							p->AttackSpeed = (int)TokenNumber;
						}
						else if (Type == 11)
						{
							Token = (*GetToken)();
							p->Defense = (int)TokenNumber;
							Token = (*GetToken)();
							p->WalkSpeed = (int)TokenNumber;
						}
					}
					else
					{
						Token = (*GetToken)();
						p->Defense = (int)TokenNumber;
						Token = (*GetToken)();
						p->MagicDefense = (int)TokenNumber;
					}
					Token = (*GetToken)();
					p->Durability = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireLevel = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireStrength = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireDexterity = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireEnergy = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireVitality = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireLeadership = (int)TokenNumber;
				}
				if (Type == 13 || Type == 16)
				{
					Token = (*GetToken)();
					p->Level = (int)TokenNumber;
					Token = (*GetToken)();
					p->Durability = (int)TokenNumber;
					Token = (*GetToken)();
					p->Resistance[0] = (int)TokenNumber;
					Token = (*GetToken)();
					p->Resistance[1] = (int)TokenNumber;
					Token = (*GetToken)();
					p->Resistance[2] = (int)TokenNumber;
					Token = (*GetToken)();
					p->Resistance[3] = (int)TokenNumber;
					Token = (*GetToken)();
					p->Resistance[4] = (int)TokenNumber;
					Token = (*GetToken)();
					p->Resistance[5] = (int)TokenNumber;
					Token = (*GetToken)();
					p->Resistance[6] = (int)TokenNumber;
					p->ResistanceType = 0xFF;
					for (int ResiIndex = 0; ResiIndex < 6; ++ResiIndex)
					{
						if (p->Resistance[ResiIndex])
							p->ResistanceType = ResiIndex;
					}
					p->RequireLevel = p->Level;
				}
				if (Type == 14)
				{
					Token = (*GetToken)();
					p->Value = (int)TokenNumber;
					Token = (*GetToken)();
					p->Level = (int)TokenNumber;
					p->Durability = 1;
					Token = (*GetToken)();
					p->ItemCategory = (int)TokenNumber;
					Token = (*GetToken)();
					strcpy(p->ModelPath, TokenString);
					Token = (*GetToken)();
					strcpy(p->ModelFile, TokenString);
					Token = (*GetToken)();
					p->Dump = (int)TokenNumber;
					Token = (*GetToken)();
					p->Transaction = (int)TokenNumber;
					Token = (*GetToken)();
					p->PersonalStore = (int)TokenNumber;
					Token = (*GetToken)();
					p->StoreWarehouse = (int)TokenNumber;
					Token = (*GetToken)();
					p->SellToNPC = (int)TokenNumber;
					Token = (*GetToken)();
					p->Repair = (int)TokenNumber;
					Token = (*GetToken)();
					p->ItemKindA = (int)TokenNumber;
					Token = (*GetToken)();
					p->ItemKindB = (int)TokenNumber;
					Token = (*GetToken)();
					p->ItemOverlap = (int)TokenNumber;
				}
				if (Type == 12)
				{
					if (Index < 200 || Index > 220)
					{
						Token = (*GetToken)();
						p->Level = (int)TokenNumber;
					}
					else
					{
						Token = (*GetToken)();
						p->RequireLevel = (int)TokenNumber;
					}
					Token = (*GetToken)();
					p->Defense = (int)TokenNumber;
					Token = (*GetToken)();
					p->Durability = (int)TokenNumber;
					if (Index < 200 || Index > 220)
					{
						Token = (*GetToken)();
						p->RequireLevel = (int)TokenNumber;
						Token = (*GetToken)();
						p->RequireEnergy = (int)TokenNumber;
					}
					else
					{
						Token = (*GetToken)();
						p->DamageMin = (int)TokenNumber;
						Token = (*GetToken)();
						p->DamageMax = (int)TokenNumber;
					}
					Token = (*GetToken)();
					p->RequireStrength = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireDexterity = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireLeadership = (int)TokenNumber;
					Token = (*GetToken)();
					p->BuyMoney = (int)TokenNumber;
				}
				if (Type == 15)
				{
					Token = (*GetToken)();
					p->Level = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireLevel = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireEnergy = (int)TokenNumber;
					Token = (*GetToken)();
					p->BuyMoney = (int)TokenNumber;
					p->DamageMin = p->Level;
					p->DamageMax = p->Level / 2 + p->Level;
				}
				if (Type <= 11 || Type == 13 || Type == 16)
					Token = (*GetToken)();
				p->SetAttr = (int)TokenNumber;
				if (Type <= 13 || Type == 15 || Type == 16)
				{
					Token = (*GetToken)();
					p->RequireClass[0] = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireClass[1] = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireClass[2] = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireClass[3] = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireClass[4] = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireClass[5] = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireClass[6] = (int)TokenNumber;
					Token = (*GetToken)();
					p->RequireClass[7] = (int)TokenNumber;
					Token = (*GetToken)();
					p->ItemCategory = (int)TokenNumber;
					Token = (*GetToken)();
					strcpy(p->ModelPath, TokenString);
					Token = (*GetToken)();
					strcpy(p->ModelFile, TokenString);
					Token = (*GetToken)();
					p->Dump = (int)TokenNumber;
					Token = (*GetToken)();
					p->Transaction = (int)TokenNumber;
					Token = (*GetToken)();
					p->PersonalStore = (int)TokenNumber;
					Token = (*GetToken)();
					p->StoreWarehouse = (int)TokenNumber;
					Token = (*GetToken)();
					p->SellToNPC = (int)TokenNumber;
					Token = (*GetToken)();
					p->Repair = (int)TokenNumber;
					Token = (*GetToken)();
					p->ItemKindA = (int)TokenNumber;
					Token = (*GetToken)();
					p->ItemKindB = (int)TokenNumber;
					Token = (*GetToken)();
					p->ItemOverlap = (int)TokenNumber;
				}
				CalRepairRate(Type, Index, p);
				p->HaveItemInfo = 1;
				if (++loop_count > MAX_ITEM_INDEX)
				{
					MsgBox("Error : Item Data fail. (LoopCount:%d) Item Type:%d Index %d", loop_count, Type, Index);
					break;
				}
			}
			if (loop_count > MAX_ITEM_INDEX)
				break;
		}
	}
	fclose(SMDFile);
	return 1;
}


//----------------------------------------------------------------------------
// 해외판을 위해서 기존에 로드한 아이템 정보에 아이템 이름만 바꾼다
//----------------------------------------------------------------------------
BOOL OpenItemNameScript(char *FileName)
{
	if ((SMDFile = fopen(FileName, "r")) == NULL)
		return FALSE;

	SMDToken Token;
	while (true)
	{
		Token = (*GetToken)();
		if (Token == END) break;
		if (Token == NUMBER)
		{
			int Type = (int)TokenNumber;
			while (true)
			{
				Token = (*GetToken)();
				int Index = (int)TokenNumber;
				if (Token == NAME && strcmp("end", TokenString) == NULL) break;
				ITEM_ATTRIBUTE *p = &ItemAttribute[Type*MAX_ITEM_INDEX + Index];
				Token = (*GetToken)(); strcpy(p->Name, TokenString);
			}
		}
	}
	fclose(SMDFile);
	return TRUE;
}

#ifdef AUTH_GAMESERVER
BOOL OpenItemScript(char* Buffer, int iSize)
{
	CWzMemScript	WzMemScript;
	WzMemScript.SetBuffer(Buffer, iSize);


	memset(&ItemAttribute, 0, sizeof(ItemAttribute));
	for (int n = 0; n<MAX_ITEM; n++)
	{
		ItemAttribute[n].Level = 0xFF;
		ItemAttribute[n].RepaireMoneyRate = 0;
		ItemAttribute[n].AllRepaireMoneyRate = 0;
	}

	int loop_count;

	SMDToken Token;
	while (true)
	{
		Token = WzMemScript.GetToken();
		if (Token == END) break;
		if (Token == NUMBER)
		{
			int Type = WzMemScript.GetNumber();
			loop_count = 0;
			while (true)
			{
				Token = WzMemScript.GetToken();
				int Index = WzMemScript.GetNumber();

#ifdef ADD_RANDOM_RANGE_OF_ITEMINDEX_20050808
				if (Type >= 0 && Type < MAX_ITEM_TYPE)
				{
					// 타입의 최대 인덱스를 기록한다.
					if (g_MaxItemIndexOfEachItemType[Type] <= Index)
						g_MaxItemIndexOfEachItemType[Type] = Index;
				}
#endif // ADD_RANDOM_RANGE_OF_ITEMINDEX_20050808

				if (Token == NAME && strcmp("end", WzMemScript.GetString()) == NULL) break;
				ITEM_ATTRIBUTE *p = &ItemAttribute[Type*MAX_ITEM_INDEX + Index];

#ifdef DARKLORD_WORK	// 아이템 슬롯 위치				
				Token = WzMemScript.GetToken(); p->ItemSlot = WzMemScript.GetNumber();
				Token = WzMemScript.GetToken(); p->SkillType = WzMemScript.GetNumber();
#endif
				Token = WzMemScript.GetToken(); p->Width = WzMemScript.GetNumber();
				Token = WzMemScript.GetToken(); p->Height = WzMemScript.GetNumber();
				Token = WzMemScript.GetToken(); p->Serial = WzMemScript.GetNumber();
				Token = WzMemScript.GetToken(); p->OptionFlag = WzMemScript.GetNumber();
				Token = WzMemScript.GetToken(); p->MondownFlag = WzMemScript.GetNumber();
				Token = WzMemScript.GetToken(); strcpy(p->Name, WzMemScript.GetString());

#if TESTSERVER == 1
				char sztext[255];
				wsprintf(sztext, "%d\t%s\n", MAKE_ITEMNUM(Type, Index), p->Name);
				OutputDebugString(sztext);
#endif

				if (Type >= 0 && Type <= 5)
				{
					Token = WzMemScript.GetToken(); p->Level = WzMemScript.GetNumber();
					Token = WzMemScript.GetToken(); p->DamageMin = WzMemScript.GetNumber();
					Token = WzMemScript.GetToken(); p->DamageMax = WzMemScript.GetNumber();
					Token = WzMemScript.GetToken(); p->AttackSpeed = WzMemScript.GetNumber();
					Token = WzMemScript.GetToken(); p->Durability = WzMemScript.GetNumber();

					// 추가(20030305)(foguy)
					Token = WzMemScript.GetToken(); p->MagicDurability = WzMemScript.GetNumber();
					Token = WzMemScript.GetToken(); p->MagicPW = WzMemScript.GetNumber();

#ifdef EXPAND_ITEMSCRIPT_01_20050808 
					Token = WzMemScript.GetToken(); p->RequireLevel = WzMemScript.GetNumber();	// 요구 레벨
#endif

					Token = WzMemScript.GetToken(); p->RequireStrength = WzMemScript.GetNumber();	// 요구 힘
					Token = WzMemScript.GetToken(); p->RequireDexterity = WzMemScript.GetNumber();	// 요구 민첩
					Token = WzMemScript.GetToken(); p->RequireEnergy = WzMemScript.GetNumber();		// 요구 에너지

#ifdef EXPAND_ITEMSCRIPT_01_20050808 
					Token = WzMemScript.GetToken(); p->RequireVitality = WzMemScript.GetNumber();	// 요구 생명
					Token = WzMemScript.GetToken(); p->RequireLeadership = WzMemScript.GetNumber();	// 요구 통솔
#endif

					if (p->Width >= 2) p->TwoHand = true;

					// 마법 내구도와 물리 내구도는 같이 사용된다
					p->Durability += p->MagicDurability;


				}
				if (Type >= 6 && Type <= 11)
				{
					Token = WzMemScript.GetToken(); p->Level = WzMemScript.GetNumber();

					if (Type == 6)
					{
						Token = WzMemScript.GetToken(); p->Defense = WzMemScript.GetNumber();
						Token = WzMemScript.GetToken(); p->SuccessfulBlocking = WzMemScript.GetNumber();
					}

					else if (Type >= 7 && Type <= 9)
					{
						Token = WzMemScript.GetToken(); p->Defense = WzMemScript.GetNumber();
						Token = WzMemScript.GetToken(); p->MagicDefense = WzMemScript.GetNumber();
					}
					else if (Type == 10)
					{
						Token = WzMemScript.GetToken(); p->Defense = WzMemScript.GetNumber();
						Token = WzMemScript.GetToken(); p->AttackSpeed = WzMemScript.GetNumber();
					}
					else if (Type == 11)
					{
						Token = WzMemScript.GetToken(); p->Defense = WzMemScript.GetNumber();
						Token = WzMemScript.GetToken(); p->WalkSpeed = WzMemScript.GetNumber();
					}
					Token = WzMemScript.GetToken(); p->Durability = WzMemScript.GetNumber();

#ifdef EXPAND_ITEMSCRIPT_01_20050808 
					Token = WzMemScript.GetToken(); p->RequireLevel = WzMemScript.GetNumber();	// 요구 레벨
#endif
					Token = WzMemScript.GetToken(); p->RequireStrength = WzMemScript.GetNumber();	// 요구 힘
					Token = WzMemScript.GetToken(); p->RequireDexterity = WzMemScript.GetNumber();	// 요구 민첩

#ifdef EXPAND_ITEMSCRIPT_01_20050808
					Token = WzMemScript.GetToken(); p->RequireEnergy = WzMemScript.GetNumber();	// 요구 에너지
					Token = WzMemScript.GetToken(); p->RequireVitality = WzMemScript.GetNumber();	// 요구 생명
					Token = WzMemScript.GetToken(); p->RequireLeadership = WzMemScript.GetNumber();  // 요구 통솔
#else
					if (Type == 6)
					{
						Token = WzMemScript.GetToken(); p->RequireEnergy = WzMemScript.GetNumber();
					}
#endif
				}
				if (Type == 13)
				{
					Token = WzMemScript.GetToken(); p->Level = WzMemScript.GetNumber();
					Token = WzMemScript.GetToken(); p->Durability = WzMemScript.GetNumber();
					Token = WzMemScript.GetToken(); p->Resistance[0] = WzMemScript.GetNumber();
					Token = WzMemScript.GetToken(); p->Resistance[1] = WzMemScript.GetNumber();
					Token = WzMemScript.GetToken(); p->Resistance[2] = WzMemScript.GetNumber();
					Token = WzMemScript.GetToken(); p->Resistance[3] = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken(); p->Resistance[4] = WzMemScript.GetNumber();
					Token = WzMemScript.GetToken(); p->Resistance[5] = WzMemScript.GetNumber();
					Token = WzMemScript.GetToken(); p->Resistance[6] = WzMemScript.GetNumber();

					p->ResistanceType = 0xFF;
					for (int ResiIndex = 0; ResiIndex < 6; ResiIndex++)
					{
						if (p->Resistance[ResiIndex])
							p->ResistanceType = ResiIndex;
					}

					p->RequireLevel = p->Level;
				}
				if (Type == 14)
				{
					Token = WzMemScript.GetToken(); p->Value = WzMemScript.GetNumber();
					Token = WzMemScript.GetToken(); p->Level = WzMemScript.GetNumber();
					//if( Index == 17 || Index == 18 )
					//{	// 아이템에 내구도를 강제로 넣어준다(TESTSERVER1에서 사용된 아이템을 강제로 없애기 위해서)
					// 악마의 눈, 열쇠
					p->Durability = 1;
					//}
				}
				if (Type == 12)
				{
					Token = WzMemScript.GetToken(); p->Level = WzMemScript.GetNumber();
					Token = WzMemScript.GetToken(); p->Defense = WzMemScript.GetNumber();
					Token = WzMemScript.GetToken(); p->Durability = WzMemScript.GetNumber();
					Token = WzMemScript.GetToken(); p->RequireLevel = WzMemScript.GetNumber();
					Token = WzMemScript.GetToken(); p->RequireEnergy = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken(); p->RequireStrength = WzMemScript.GetNumber();
#ifdef NEW_FORSKYLAND2	// 구슬 요구 민첩 추가(20030731)					
					Token = WzMemScript.GetToken(); p->RequireDexterity = WzMemScript.GetNumber();
#endif

#ifdef DARKLORD_WORK					
					Token = WzMemScript.GetToken(); p->RequireLeadership = WzMemScript.GetNumber();
#endif

					Token = WzMemScript.GetToken(); p->BuyMoney = WzMemScript.GetNumber();
				}
				if (Type == 15)
				{
					Token = WzMemScript.GetToken(); p->Level = WzMemScript.GetNumber();

#ifdef NEW_FORSKYLAND2	// 법서 요구 레벨 추가(20030725)(foguy)
					Token = WzMemScript.GetToken(); p->RequireLevel = WzMemScript.GetNumber();
#endif
					Token = WzMemScript.GetToken(); p->RequireEnergy = WzMemScript.GetNumber();

					Token = WzMemScript.GetToken(); p->BuyMoney = WzMemScript.GetNumber();
					p->DamageMin = p->Level;
					p->DamageMax = p->Level + p->Level / 2;

				}

				if (Type <= 11 || Type == 13)
					Token = WzMemScript.GetToken(); p->SetAttr = WzMemScript.GetNumber();

				//사용 클래스
				if (Type <= 13 || Type == 15)
				{
					Token = WzMemScript.GetToken(); p->RequireClass[0] = WzMemScript.GetNumber();
					Token = WzMemScript.GetToken(); p->RequireClass[1] = WzMemScript.GetNumber();
					Token = WzMemScript.GetToken(); p->RequireClass[2] = WzMemScript.GetNumber();
					Token = WzMemScript.GetToken(); p->RequireClass[3] = WzMemScript.GetNumber();
#ifdef DARKLORD_WORK	// 다크로드
					Token = WzMemScript.GetToken(); p->RequireClass[4] = WzMemScript.GetNumber();
#endif

#ifdef ADD_SEASON_3_NEW_CHARACTER_SUMMONER_20070912	// item 사용 클래스 추가
					Token = WzMemScript.GetToken(); p->RequireClass[5] = WzMemScript.GetNumber();
#endif
				}

				// 아이템 수리비용 비율을 설정한다
				CalRepairRate(Type, Index, p);
				p->HaveItemInfo = TRUE;

				loop_count++;
				if (loop_count > MAX_ITEM_INDEX)
				{
					MsgBox("Error : Item Data fail. (LoopCount:%d) Item Type:%d Index %d", loop_count, Type, Index);
					break;
				}
			}
		}
	}
	return TRUE;
}

//----------------------------------------------------------------------------
// 해외판을 위해서 기존에 로드한 아이템 정보에 아이템 이름만 바꾼다
//----------------------------------------------------------------------------
BOOL OpenItemNameScript(char *Buffer, int iSize)
{
	CWzMemScript	WzMemScript;
	WzMemScript.SetBuffer(Buffer, iSize);

	SMDToken Token;
	while (true)
	{
		Token = WzMemScript.GetToken();
		if (Token == END) break;
		if (Token == NUMBER)
		{
			int Type = WzMemScript.GetNumber();
			while (true)
			{
				Token = WzMemScript.GetToken();
				int Index = WzMemScript.GetNumber();
				if (Token == NAME && strcmp("end", WzMemScript.GetString()) == NULL) break;
				ITEM_ATTRIBUTE *p = &ItemAttribute[Type*MAX_ITEM_INDEX + Index];
				Token = WzMemScript.GetToken(); strcpy(p->Name, WzMemScript.GetString());
			}
		}
	}
	return TRUE;
}
#endif



#ifdef SCRIPT_DECODE_WORK
//----------------------------------------------------------------------------
// 아이템 스크립트 데이터를 읽는다.
//----------------------------------------------------------------------------
BOOL OpenItemScriptDecode(char *FileName)
{
	CWZScriptEncode		Encoder;
	if (!Encoder.Open(FileName))
	{
		return FALSE;
	}

	WZSMDToken Token;

	memset(&ItemAttribute, 0, sizeof(ItemAttribute));
	for (int n = 0; n<MAX_ITEM; n++)
	{
		ItemAttribute[n].Level = 0xFF;
		ItemAttribute[n].RepaireMoneyRate = 0;
		ItemAttribute[n].AllRepaireMoneyRate = 0;
	}


	while (true)
	{
		Token = Encoder.GetToken();
		if (Token == END) break;
		if (Token == T_NUMBER)
		{
			int Type = Encoder.GetNumber();
			while (true)
			{
				Token = Encoder.GetToken();
				int Index = Encoder.GetNumber();

#ifdef ADD_RANDOM_RANGE_OF_ITEMINDEX_20050808
				if (Type >= 0 && Type < MAX_ITEM_TYPE)
				{
					// 타입의 최대 인덱스를 기록한다.
					if (g_MaxItemIndexOfEachItemType[Type] <= Index)
						g_MaxItemIndexOfEachItemType[Type] = Index;
				}
#endif // ADD_RANDOM_RANGE_OF_ITEMINDEX_20050808

				if (Token == T_NAME && strcmp("end", Encoder.GetString()) == NULL) break;
				ITEM_ATTRIBUTE *p = &ItemAttribute[Type*MAX_ITEM_INDEX + Index];

				Token = Encoder.GetToken(); p->Width = Encoder.GetNumber();
				Token = Encoder.GetToken(); p->Height = Encoder.GetNumber();
				Token = Encoder.GetToken(); p->Serial = Encoder.GetNumber();
				Token = Encoder.GetToken(); p->OptionFlag = Encoder.GetNumber();
				Token = Encoder.GetToken(); p->MondownFlag = Encoder.GetNumber();
				Token = Encoder.GetToken(); strcpy(p->Name, Encoder.GetString());

				if (Type >= 0 && Type <= 5)
				{
					Token = Encoder.GetToken(); p->Level = Encoder.GetNumber();
					Token = Encoder.GetToken(); p->DamageMin = Encoder.GetNumber();
					Token = Encoder.GetToken(); p->DamageMax = Encoder.GetNumber();
					Token = Encoder.GetToken(); p->AttackSpeed = Encoder.GetNumber();
					Token = Encoder.GetToken(); p->Durability = Encoder.GetNumber();

					// 추가(20030305)(foguy)
					Token = Encoder.GetToken(); p->MagicDurability = Encoder.GetNumber();
					Token = Encoder.GetToken(); p->MagicPW = Encoder.GetNumber();

#ifdef EXPAND_ITEMSCRIPT_01_20050808 
					Token = Encoder.GetToken(); p->RequireLevel = Encoder.GetNumber();	// 요구 레벨
#endif

					Token = Encoder.GetToken(); p->RequireStrength = Encoder.GetNumber();	// 요구 힘
					Token = Encoder.GetToken(); p->RequireDexterity = Encoder.GetNumber();	// 요구 민첩
					Token = Encoder.GetToken(); p->RequireEnergy = Encoder.GetNumber();		// 요구 에너지

#ifdef EXPAND_ITEMSCRIPT_01_20050808 
					Token = Encoder.GetToken(); p->RequireVitality = Encoder.GetNumber();	// 요구 레벨
					Token = Encoder.GetToken(); p->RequireLeadership = Encoder.GetNumber();	// 요구 통솔
#endif

					if (p->Width >= 2) p->TwoHand = true;

					// 마법 내구도와 물리 내구도는 같이 사용된다
					p->Durability += p->MagicDurability;


				}
				if (Type >= 6 && Type <= 11)
				{
					Token = Encoder.GetToken(); p->Level = Encoder.GetNumber();

					if (Type == 6)
					{
						Token = Encoder.GetToken(); p->Defense = Encoder.GetNumber();
						Token = Encoder.GetToken(); p->SuccessfulBlocking = Encoder.GetNumber();
					}

					else if (Type >= 7 && Type <= 9)
					{
						Token = Encoder.GetToken(); p->Defense = Encoder.GetNumber();
						Token = Encoder.GetToken(); p->MagicDefense = Encoder.GetNumber();
					}
					else if (Type == 10)
					{
						Token = Encoder.GetToken(); p->Defense = Encoder.GetNumber();
						Token = Encoder.GetToken(); p->AttackSpeed = Encoder.GetNumber();
					}
					else if (Type == 11)
					{
						Token = Encoder.GetToken(); p->Defense = Encoder.GetNumber();
						Token = Encoder.GetToken(); p->WalkSpeed = Encoder.GetNumber();
					}
					Token = Encoder.GetToken(); p->Durability = Encoder.GetNumber();

#ifdef EXPAND_ITEMSCRIPT_01_20050808 
					Token = Encoder.GetToken(); p->RequireLevel = Encoder.GetNumber();	// 요구 레벨
#endif

					Token = Encoder.GetToken(); p->RequireStrength = Encoder.GetNumber();	// 요구 힘
					Token = Encoder.GetToken(); p->RequireDexterity = Encoder.GetNumber();	// 요구 민첩

#ifdef EXPAND_ITEMSCRIPT_01_20050808
					Token = Encoder.GetToken(); p->RequireEnergy = Encoder.GetNumber();	// 요구 에너지
					Token = Encoder.GetToken(); p->RequireVitality = Encoder.GetNumber();	// 요구 레벨
					Token = Encoder.GetToken(); p->RequireLeadership = Encoder.GetNumber();	// 요구 통솔
#else
					if (Type == 6)
					{
						Token = Encoder.GetToken(); p->RequireEnergy = Encoder.GetNumber();
					}
#endif
				}
				if (Type == 13)
				{
					Token = Encoder.GetToken(); p->Level = Encoder.GetNumber();
					Token = Encoder.GetToken(); p->Durability = Encoder.GetNumber();
					Token = Encoder.GetToken(); p->Resistance[0] = Encoder.GetNumber();
					Token = Encoder.GetToken(); p->Resistance[1] = Encoder.GetNumber();
					Token = Encoder.GetToken(); p->Resistance[2] = Encoder.GetNumber();
					Token = Encoder.GetToken(); p->Resistance[3] = Encoder.GetNumber();
					p->RequireLevel = p->Level;
				}
				if (Type == 14)
				{
					Token = Encoder.GetToken(); p->Value = Encoder.GetNumber();
					Token = Encoder.GetToken(); p->Level = Encoder.GetNumber();
					//if( Index == 17 || Index == 18 )
					//{	// 아이템에 내구도를 강제로 넣어준다(TESTSERVER1에서 사용된 아이템을 강제로 없애기 위해서)
					// 악마의 눈, 열쇠
					p->Durability = 1;
					//}
				}
				if (Type == 12)
				{
					Token = Encoder.GetToken(); p->Level = Encoder.GetNumber();
					Token = Encoder.GetToken(); p->Defense = Encoder.GetNumber();
					Token = Encoder.GetToken(); p->Durability = Encoder.GetNumber();
					Token = Encoder.GetToken(); p->RequireLevel = Encoder.GetNumber();
					Token = Encoder.GetToken(); p->RequireEnergy = Encoder.GetNumber();

					Token = Encoder.GetToken(); p->RequireStrength = Encoder.GetNumber();
#ifdef NEW_FORSKYLAND2	// 구슬 요구 민첩 추가(20030731)					
					Token = Encoder.GetToken(); p->RequireDexterity = Encoder.GetNumber();
#endif
					Token = Encoder.GetToken(); p->BuyMoney = Encoder.GetNumber();
				}
				if (Type == 15)
				{
					Token = Encoder.GetToken(); p->Level = Encoder.GetNumber();

#ifdef NEW_FORSKYLAND2	// 법서 요구 레벨 추가(20030725)(foguy)
					Token = Encoder.GetToken(); p->RequireLevel = Encoder.GetNumber();
#endif
					Token = Encoder.GetToken(); p->RequireEnergy = Encoder.GetNumber();

					Token = Encoder.GetToken(); p->BuyMoney = Encoder.GetNumber();
					p->DamageMin = p->Level;
					p->DamageMax = p->Level + p->Level / 2;

				}
				//사용 클래스
				if (Type <= 13 || Type == 15)
				{
					Token = Encoder.GetToken(); p->RequireClass[0] = Encoder.GetNumber();
					Token = Encoder.GetToken(); p->RequireClass[1] = Encoder.GetNumber();
					Token = Encoder.GetToken(); p->RequireClass[2] = Encoder.GetNumber();
					Token = Encoder.GetToken(); p->RequireClass[3] = Encoder.GetNumber();
				}

				// 아이템 수리비용 비율을 설정한다
				CalRepairRate(Type, Index, p);
				p->HaveItemInfo = TRUE;
			}
		}
	}
	return TRUE;
}


//----------------------------------------------------------------------------
// 해외판을 위해서 기존에 로드한 아이템 정보에 아이템 이름만 바꾼다
//----------------------------------------------------------------------------
BOOL OpenItemNameScriptDecode(char *FileName)
{
	CWZScriptEncode		Encoder;
	if (!Encoder.Open(FileName))
		return FALSE;

	WZSMDToken Token;
	while (true)
	{
		Token = Encoder.GetToken();
		if (Token == END) break;
		if (Token == T_NUMBER)
		{
			int Type = Encoder.GetNumber();
			while (true)
			{
				Token = Encoder.GetToken();
				int Index = Encoder.GetNumber();
				if (Token == T_NAME && strcmp("end", Encoder.GetString()) == NULL) break;
				ITEM_ATTRIBUTE *p = &ItemAttribute[Type*MAX_ITEM_INDEX + Index];
				Token = Encoder.GetToken();	strcpy(p->Name, Encoder.GetString());
			}
		}
	}
	return TRUE;
}
#endif

// 아이템의 레벨을 얻는다.
BOOL zzzItemLevel(int type, int index, int level)
{
	int item_num;
	item_num = (type*MAX_ITEM_INDEX) + index;

	if (level < 0) level = 0;

	if (ItemAttribute[item_num].Level == 0xFF) return FALSE;	// 레벨이존재하지 않다면.
	if (ItemAttribute[item_num].Level == 0) return FALSE;
	if (ItemAttribute[item_num].Level < level) return TRUE;
	return FALSE;
}

// 각 해당 아이템에 대한 몬스터 레벨 별 +레벨을 구한다.
int GetLevelItem(int type, int index, int level)
{
	int item_num;
	int itemlevel;

	if (level < 0) level = 0;
	//	level = 65;
	//item_num = (type*MAX_ITEM_INDEX)+index;
	item_num = MAKE_ITEMNUM(type, index);

	if (ItemAttribute[item_num].MondownFlag == 0)
		return -1;

	if (ItemAttribute[item_num].Level == 0xFF) return -1;	// 레벨이존재하지 않다면.
	if (ItemAttribute[item_num].Level == 0) return -1;	// 레벨이존재하지 않다면.

	if (type == 14)	// 사과및 물약시리즈는 
	{
		itemlevel = ItemAttribute[item_num].Level;

		if (index == 15) return -1;	// 금이면 리턴
		if (itemlevel >= (level - 8) && itemlevel <= level)
		{
			return 0;
		}
		return -1;
	}
	// 변신 반지일때는..
	if (type == 13 && index == 10)
	{
		if ((rand() % 10) == 0)
		{
			int callbead_level = 0;
			if (level < 0) level = 0;
			callbead_level = level / 10;
			if (callbead_level > 0) callbead_level -= 1;
			if (callbead_level > 5) callbead_level = 5;
			return callbead_level;
		}
		return -1;
	}
	if (type == 12 && index == 11)
	{
		if ((rand() % 10) == 0)
		{
			int callbead_level = 0;
			if (level < 0) level = 0;
			callbead_level = level / 10;
			if (callbead_level > 0) callbead_level -= 1;
			if (callbead_level > 6) callbead_level = 6;
			return callbead_level;
		}
		// 이번 버젼엔 소환 구슬 안나가게..
		return -1;
	}

	itemlevel = ItemAttribute[item_num].Level;

	// 몬스터의 드롭 아이템 최대 레벨을 수정시 MAX_MONSTER_ITEM_DROP_RANGE 값을 수정해 줘야 한다.
	// MAX_MONSTER_ITEM_DROP_RANGE : 현재 몬스터 레벨과 현재 아이템 드롭의 최소 몬스터 레벨간의 범위
#ifdef MODIFY_DROP_MAX_ITEM_LEVEL_6_OF_MONSTER_20050624
#define MAX_MONSTER_ITEM_DROP_RANGE   18  
	if (((itemlevel) >= (level - MAX_MONSTER_ITEM_DROP_RANGE)) && (itemlevel <= level))
	{
#else
#define MAX_MONSTER_ITEM_DROP_RANGE   15
	if (((itemlevel) >= (level - MAX_MONSTER_ITEM_DROP_RANGE)) && (itemlevel <= level))
	{
#endif
		if (type == 15) return 0;	// 마법서이면 + 레벨은 없다..

#ifndef MODIFY_DROP_PREVENT_OF_RING_N_NECKLACE_LV_5_OVER_20050623
		return (level - itemlevel) / 3;
#endif

#ifdef MODIFY_DROP_PREVENT_OF_RING_N_NECKLACE_LV_5_OVER_20050623
		itemlevel = (level - itemlevel) / 3;

		// 모든 반지와 목걸이는 레벨 4이하만 생성
		if (type == 13) {
			if (index == 8 || // 얼음의반지
				index == 9 || // 독의반지
				index == 12 || // 번개의목걸이
				index == 13 || // 불의목걸이
				index == 20 || // 마법사의반지
				index == 21 || // 불의반지
				index == 22 || // 땅의반지
				index == 23 || // 바람의반지
				index == 24 || // 마법의반지
				index == 25 || // 얼음의목걸이
				index == 26 || // 바람의목걸이 
				index == 27 || // 물의목걸이
				index == 28    // 기술의목걸이
				) {
				if (itemlevel > 4) {
					itemlevel = 4;
				}
			}
		}

		return itemlevel;
#endif

	}
	return -1;
	}

int GetSerialItem(int type)
{
	int item_num;

	item_num = type;

	if (ItemAttribute[item_num].Level == 0xFF) return -1;	// 레벨이존재하지 않다면.

	if (ItemAttribute[item_num].Serial == 0) return FALSE;
	return TRUE;
}

BOOL IsItem(int item_num)
{
	if (item_num < 0 || item_num >= MAX_ITEM)
		return FALSE;

	return ItemAttribute[item_num].HaveItemInfo;
}


ITEM_ATTRIBUTE *GetItemAttr(int item_num)
{
	if (item_num < 0 || item_num >= MAX_ITEM)
		return FALSE;

	return &ItemAttribute[item_num];
}

