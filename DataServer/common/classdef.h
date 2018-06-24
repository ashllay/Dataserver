// classdef.h: interface for the classdef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASSDEF_H__1B6C4ED5_0169_4A49_990F_E7FBB0E9DECF__INCLUDED_)
#define AFX_CLASSDEF_H__1B6C4ED5_0169_4A49_990F_E7FBB0E9DECF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "..\\Common\\zzzItem.h"

//----------------------------------------------------------------------------
// 종족별 기본값
//----------------------------------------------------------------------------
typedef struct
{
	int 	Experience;
	WORD	Strength;
	WORD	Dexterity;
	WORD	Vitality;
	WORD	Energy;
	float   LevelLife;
	float 	Life;
	float 	MaxLife;
	float   LevelMana;
	float 	Mana;
	float 	MaxMana;
	float   VitalityToLife;
	float 	EnergyToMana;
	CItem	Equipment[MAX_EQUIPMENT + 2];
	WORD	Leadership;		// 통솔 항목 추가
} DEFAULTCLASSTYPE, *LPDEFAULTCLASSTYPE;

class classdef
{
public:
	DEFAULTCLASSTYPE	DefClass[MAX_CLASSTYPE];
	BOOL				m_BabubBanJiCreate;
	CItem				JumpingEquipment[32][204];//s12
public:
	classdef();
	virtual ~classdef();

	void Init();


	void SetCharacter(int Class, int Str, int Dex, int Vit, int Energy,float Life, float Mana, float LevelLife, float LevelMana,float VitalityToLife, float EnergyToMana, int Leadership);
	void SetEquipment(int Class);
	int  GetDefPoint(int char_class);
	void SetMabubBanjiOption(BOOL flag);
	void SetJumpingEquipment(int nClass);//new
	char GetCharacterClassByDBClass(char DbClass);
};

#endif // !defined(AFX_CLASSDEF_H__1B6C4ED5_0169_4A49_990F_E7FBB0E9DECF__INCLUDED_)
