// SetItemOption.cpp: implementation of the CSetItemOption class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SetItemOption.h"

#ifdef AUTH_GAMESERVER
#include "..\\common\\WzMemScript.h"
#endif

#if GAME_VERSION >= G_V_99B

extern ITEM_ATTRIBUTE      ItemAttribute [MAX_ITEM];

CSetItemOption	gSetItemOption;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSetItemOption::CSetItemOption()
{

}

CSetItemOption::~CSetItemOption()
{

}


BOOL CSetItemOption::LoadTypeInfo(char* filename)
{
	if((SMDFile=fopen(filename,"r")) == NULL)	
		return FALSE;

	memset(&m_SetItemTypeInfo, -1, sizeof(m_SetItemTypeInfo));

	for( int i = 0; i < MAX_ITEM; i++ )
	{
		m_SetItemTypeInfo[i].IsLoad = FALSE;
	}
	
	SMDToken Token;
	while(true)
	{
		Token = (*GetToken)();
		if(Token == END) break;
		if(Token == NUMBER)
		{
			int Type = (int)TokenNumber;
			while(true)
			{
				Token = (*GetToken)();
				int Index = (int)TokenNumber;
				if(Token==NAME && strcmp("end",TokenString)==NULL) break;
               	SETITEM_TYPEINFO *p = &m_SetItemTypeInfo[Type*MAX_ITEM_INDEX+Index];

				Token = (*GetToken)();p->OptionIndex[0]  = (int)TokenNumber;
				Token = (*GetToken)();p->OptionIndex[1]  = (int)TokenNumber;
				Token = (*GetToken)();p->ChaosMixLevel[0]  = (int)TokenNumber;
				Token = (*GetToken)();p->ChaosMixLevel[1]  = (int)TokenNumber;

				p->IsLoad = TRUE;

#if TESTSERVER == 1
				int	ItemNum = Type*MAX_ITEM_INDEX+Index;		
				
				//"세트 속성 1(힘) 2(민첩) 3(에너지) 4(체력)"
				char szSetItemAttr[][255] = 
				{
					"없음", "힘", "민첩", "에너지", "체력"
				};

				char msg[255];
				wsprintf(msg, "SetItem Type Load : (%s), (%d,%d) (%d,%d)\n",
					     ItemAttribute[ItemNum].Name,
					     p->OptionIndex[0], p->OptionIndex[1],
					     p->ChaosMixLevel[0], p->ChaosMixLevel[1]);

				//OutputDebugString(msg);

				if( p->OptionIndex[0] != 0 )
				{
					wsprintf(msg, "[%d] A Set : %s %s, %s증가 ChaosLevel = %d\n",
							 ItemNum,
							 m_SetItemOptionInfo[p->OptionIndex[0]].Name,
							 ItemAttribute[ItemNum].Name,
							 szSetItemAttr[ItemAttribute[ItemNum].SetAttr],
							 p->ChaosMixLevel[0]);
					OutputDebugString(msg);
				}				


				if( p->OptionIndex[1] != 0 )
				{
					wsprintf(msg, "B Set : %s %s, %s증가 ChaosLevel = %d\n",
							 m_SetItemOptionInfo[p->OptionIndex[1]].Name,
							 ItemAttribute[ItemNum].Name,
							 szSetItemAttr[ItemAttribute[ItemNum].SetAttr],
							 p->ChaosMixLevel[1]);
					OutputDebugString(msg);
				}

				LogAdd("SetItem Type Load : (%s), (%d,%d) (%d,%d)",
					   ItemAttribute[ItemNum].Name,
					   p->OptionIndex[0], p->OptionIndex[1],
					   p->ChaosMixLevel[0], p->ChaosMixLevel[1]);
#endif
			}
		}
	}

	fclose(SMDFile);

	return TRUE;
}

BOOL CSetItemOption::LoadOptionInfo(char* filename)
{
	if((SMDFile=fopen(filename,"r")) == NULL)	
		return FALSE;

	memset(&m_SetItemOptionInfo, 0, sizeof(m_SetItemOptionInfo));

	for( int i = 0; i < MAX_SETITEM_OPTION; i++ )
	{
		memset(m_SetItemOptionInfo[i].SetOptionTable, -1, sizeof(m_SetItemOptionInfo[i].SetOptionTable));
		memset(m_SetItemOptionInfo[i].SetExPOptionTable, -1, sizeof(m_SetItemOptionInfo[i].SetExPOptionTable));
		memset(m_SetItemOptionInfo[i].SetFullOtionTable, -1, sizeof(m_SetItemOptionInfo[i].SetFullOtionTable));		
	}
	
	SMDToken Token;
		
	while(true)
	{
		Token = (*GetToken)();
		int Index = (int)TokenNumber;
		if(Token==NAME && strcmp("end",TokenString)==NULL) break;

        SETITEM_OPTIONINFO *p = &m_SetItemOptionInfo[Index];
		Token = (*GetToken)();strcpy(p->Name,TokenString);

		for( int i = 0; i < 6; i++ )
		{
			Token = (*GetToken)();p->SetOptionTable[i][0]  = (int)TokenNumber;
			Token = (*GetToken)();p->SetOptionTableValue[i][0]  = (int)TokenNumber;

			Token = (*GetToken)();p->SetOptionTable[i][1]  = (int)TokenNumber;
			Token = (*GetToken)();p->SetOptionTableValue[i][1]  = (int)TokenNumber;

			if( p->SetOptionTable[i][0] != -1 || p->SetOptionTable[i][1] != -1 )
			{
				p->SetOptionCount++;
			}
		}

		Token = (*GetToken)();p->SetExPOptionTable[0]  = (int)TokenNumber;
		Token = (*GetToken)();p->SetExPOptionTableValue[0]  = (int)TokenNumber;

		if( p->SetExPOptionTable[0] != -1 )
		{
			p->SetOptionCount++;
		}

		Token = (*GetToken)();p->SetExPOptionTable[1]  = (int)TokenNumber;
		Token = (*GetToken)();p->SetExPOptionTableValue[1]  = (int)TokenNumber;

		if( p->SetExPOptionTable[1] != -1 )
		{
			p->SetOptionCount++;
		}

		Token = (*GetToken)();p->SetFullOtionTable[0]  = (int)TokenNumber;
		Token = (*GetToken)();p->SetFullOtionTableValue[0]  = (int)TokenNumber;

		Token = (*GetToken)();p->SetFullOtionTable[1]  = (int)TokenNumber;
		Token = (*GetToken)();p->SetFullOtionTableValue[1]  = (int)TokenNumber;

		Token = (*GetToken)();p->SetFullOtionTable[2]  = (int)TokenNumber;
		Token = (*GetToken)();p->SetFullOtionTableValue[2]  = (int)TokenNumber;

		Token = (*GetToken)();p->SetFullOtionTable[3]  = (int)TokenNumber;
		Token = (*GetToken)();p->SetFullOtionTableValue[3]  = (int)TokenNumber;
		
		Token = (*GetToken)();p->SetFullOtionTable[4]  = (int)TokenNumber;
		Token = (*GetToken)();p->SetFullOtionTableValue[4]  = (int)TokenNumber;

		Token = (*GetToken)();p->RequireClass[0]  = (int)TokenNumber;
		Token = (*GetToken)();p->RequireClass[1]  = (int)TokenNumber;
		Token = (*GetToken)();p->RequireClass[2]  = (int)TokenNumber;
		Token = (*GetToken)();p->RequireClass[3]  = (int)TokenNumber;
		Token = (*GetToken)();p->RequireClass[4]  = (int)TokenNumber;
#ifdef UPDATE_SETOPTION_SCRIPT_ADD_CLASS_20080321 // 소환술사 추가
		Token = (*GetToken)();p->RequireClass[5]  = (int)TokenNumber;
#endif

#if GAME_VERSION >= G_V_S4_6
		(*GetToken)();
#endif

		p->IsLoad = TRUE;
#if TESTSERVER == 1	

#ifdef UPDATE_SETOPTION_SCRIPT_ADD_CLASS_20080321	// 소환술사 추가
				char msg[512];
		wsprintf(msg, "%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
				 Index,p->Name,
				 p->SetOptionTable[0][0], p->SetOptionTable[0][1],
				 p->SetOptionTable[1][0], p->SetOptionTable[1][1],
				 p->SetOptionTable[2][0], p->SetOptionTable[2][1],
				 p->SetOptionTable[3][0], p->SetOptionTable[3][1],
				 p->SetOptionTable[4][0], p->SetOptionTable[4][1],
				 p->SetOptionTable[5][0], p->SetOptionTable[5][1],
				 p->SetExPOptionTable[0], p->SetExPOptionTable[1], 
				 p->SetFullOtionTable[0], p->SetFullOtionTable[1], 
				 p->SetFullOtionTable[2], p->SetFullOtionTable[3], p->SetFullOtionTable[4],
				 p->RequireClass[0], p->RequireClass[1], 
				 p->RequireClass[2], p->RequireClass[3],
				 p->RequireClass[4], p->RequireClass[5]);
#else	// UPDATE_SETOPTION_SCRIPT_ADD_CLASS_20080321
		char msg[512];
		wsprintf(msg, "%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
				 Index,p->Name,
				 p->SetOptionTable[0][0], p->SetOptionTable[0][1],
				 p->SetOptionTable[1][0], p->SetOptionTable[1][1],
				 p->SetOptionTable[2][0], p->SetOptionTable[2][1],
				 p->SetOptionTable[3][0], p->SetOptionTable[3][1],
				 p->SetOptionTable[4][0], p->SetOptionTable[4][1],
				 p->SetOptionTable[5][0], p->SetOptionTable[5][1],
				 p->SetExPOptionTable[0], p->SetExPOptionTable[1], 
				 p->SetFullOtionTable[0], p->SetFullOtionTable[1], 
				 p->SetFullOtionTable[2], p->SetFullOtionTable[3], p->SetFullOtionTable[4],
				 p->RequireClass[0], p->RequireClass[1], 
				 p->RequireClass[2], p->RequireClass[3],
				 p->RequireClass[4]);
#endif	// UPDATE_SETOPTION_SCRIPT_ADD_CLASS_20080321

		OutputDebugString(msg);

		wsprintf(msg,"%s\tOptionCount=\t%d\n", p->Name, p->SetOptionCount);
		OutputDebugString(msg);
#endif
	}

	fclose(SMDFile);

	return TRUE;
}

#ifdef AUTH_GAMESERVER
BOOL CSetItemOption::LoadTypeInfo(char *Buffer, int iSize)
{
	CWzMemScript	WzMemScript;
	WzMemScript.SetBuffer(Buffer, iSize);

	memset(&m_SetItemTypeInfo, -1, sizeof(m_SetItemTypeInfo));

	for( int i = 0; i < MAX_ITEM; i++ )
	{
		m_SetItemTypeInfo[i].IsLoad = FALSE;
	}
	
	SMDToken Token;
	while(true)
	{
		Token = WzMemScript.GetToken();
		if(Token == END) break;
		if(Token == NUMBER)
		{
			int Type = WzMemScript.GetNumber();
			while(true)
			{
				Token = WzMemScript.GetToken();
				int Index = WzMemScript.GetNumber();
				if(Token==NAME && strcmp("end",WzMemScript.GetString())==NULL) break;
               	SETITEM_TYPEINFO *p = &m_SetItemTypeInfo[Type*MAX_ITEM_INDEX+Index];

				Token = WzMemScript.GetToken();p->OptionIndex[0]  = WzMemScript.GetNumber();
				Token = WzMemScript.GetToken();p->OptionIndex[1]  = WzMemScript.GetNumber();
				Token = WzMemScript.GetToken();p->ChaosMixLevel[0]  = WzMemScript.GetNumber();
				Token = WzMemScript.GetToken();p->ChaosMixLevel[1]  = WzMemScript.GetNumber();

				p->IsLoad = TRUE;

#if TESTSERVER == 1
				int	ItemNum = Type*MAX_ITEM_INDEX+Index;									

				char msg[255];
				wsprintf(msg, "SetItem Type Load : (%s), (%d,%d) (%d,%d)\n",
					     ItemAttribute[ItemNum].Name,
					     p->OptionIndex[0], p->OptionIndex[1],
					     p->ChaosMixLevel[0], p->ChaosMixLevel[1]);

				OutputDebugString(msg);

				if( p->OptionIndex[0] != -1 )
				{
					wsprintf(msg, "A Option : %s, ChaosLevel = %d\n",
							 m_SetItemOptionInfo[p->OptionIndex[0]].Name,
							 p->ChaosMixLevel[0]);
					OutputDebugString(msg);
				}				


				if( p->OptionIndex[1] != -1 )
				{
					wsprintf(msg, "B Option : %s, ChaosLevel = %d\n",
							 m_SetItemOptionInfo[p->OptionIndex[1]].Name,
							 p->ChaosMixLevel[1]);
					OutputDebugString(msg);
				}

				LogAdd("SetItem Type Load : (%s), (%d,%d) (%d,%d)",
					   ItemAttribute[ItemNum].Name,
					   p->OptionIndex[0], p->OptionIndex[1],
					   p->ChaosMixLevel[0], p->ChaosMixLevel[1]);
#endif
			}
		}
	}
	return TRUE;
}

BOOL CSetItemOption::LoadOptionInfo(char *Buffer, int iSize)
{
	CWzMemScript	WzMemScript;
	WzMemScript.SetBuffer(Buffer, iSize);

	memset(&m_SetItemOptionInfo, 0, sizeof(m_SetItemOptionInfo));

	for( int i = 0; i < MAX_SETITEM_OPTION; i++ )
	{
		memset(m_SetItemOptionInfo[i].SetOptionTable, -1, sizeof(m_SetItemOptionInfo[i].SetOptionTable));
		memset(m_SetItemOptionInfo[i].SetExPOptionTable, -1, sizeof(m_SetItemOptionInfo[i].SetExPOptionTable));
		memset(m_SetItemOptionInfo[i].SetFullOtionTable, -1, sizeof(m_SetItemOptionInfo[i].SetFullOtionTable));		
	}
	
	SMDToken Token;
		
	while(true)
	{
		Token = WzMemScript.GetToken();
		int Index = WzMemScript.GetNumber();
		if(Token==NAME && strcmp("end",WzMemScript.GetString())==NULL) break;

        SETITEM_OPTIONINFO *p = &m_SetItemOptionInfo[Index];
		Token = WzMemScript.GetToken();strcpy(p->Name,WzMemScript.GetString());

		for( i = 0; i < 6; i++ )
		{
			Token = WzMemScript.GetToken();p->SetOptionTable[i][0]  = WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();p->SetOptionTableValue[i][0]  = WzMemScript.GetNumber();

			Token = WzMemScript.GetToken();p->SetOptionTable[i][1]  = WzMemScript.GetNumber();
			Token = WzMemScript.GetToken();p->SetOptionTableValue[i][1]  = WzMemScript.GetNumber();

			if( p->SetOptionTable[i][0] != -1 || p->SetOptionTable[i][1] != -1 )
			{
				p->SetOptionCount++;
			}
		}

		Token = WzMemScript.GetToken();p->SetExPOptionTable[0]  = WzMemScript.GetNumber();
		Token = WzMemScript.GetToken();p->SetExPOptionTableValue[0]  = WzMemScript.GetNumber();

		if( p->SetExPOptionTable[0] != -1 )
		{
			p->SetOptionCount++;
		}

		Token = WzMemScript.GetToken();p->SetExPOptionTable[1]  = WzMemScript.GetNumber();
		Token = WzMemScript.GetToken();p->SetExPOptionTableValue[1]  = WzMemScript.GetNumber();

		if( p->SetExPOptionTable[1] != -1 )
		{
			p->SetOptionCount++;
		}

		Token = WzMemScript.GetToken();p->SetFullOtionTable[0]  = WzMemScript.GetNumber();
		Token = WzMemScript.GetToken();p->SetFullOtionTableValue[0]  = WzMemScript.GetNumber();

		Token = WzMemScript.GetToken();p->SetFullOtionTable[1]  = WzMemScript.GetNumber();
		Token = WzMemScript.GetToken();p->SetFullOtionTableValue[1]  = WzMemScript.GetNumber();

		Token = WzMemScript.GetToken();p->SetFullOtionTable[2]  = WzMemScript.GetNumber();
		Token = WzMemScript.GetToken();p->SetFullOtionTableValue[2]  = WzMemScript.GetNumber();

		Token = WzMemScript.GetToken();p->SetFullOtionTable[3]  = WzMemScript.GetNumber();
		Token = WzMemScript.GetToken();p->SetFullOtionTableValue[3]  = WzMemScript.GetNumber();

		Token = WzMemScript.GetToken();p->SetFullOtionTable[4]  = WzMemScript.GetNumber();
		Token = WzMemScript.GetToken();p->SetFullOtionTableValue[4]  = WzMemScript.GetNumber();

		Token = WzMemScript.GetToken();p->RequireClass[0]  = WzMemScript.GetNumber();
		Token = WzMemScript.GetToken();p->RequireClass[1]  = WzMemScript.GetNumber();
		Token = WzMemScript.GetToken();p->RequireClass[2]  = WzMemScript.GetNumber();
		Token = WzMemScript.GetToken();p->RequireClass[3]  = WzMemScript.GetNumber();
		Token = WzMemScript.GetToken();p->RequireClass[4]  = WzMemScript.GetNumber();
#ifdef UPDATE_SETOPTION_SCRIPT_ADD_CLASS_20080321	// 소환술사 추가
		Token = WzMemScript.GetToken();p->RequireClass[5]  = WzMemScript.GetNumber();
#endif	// UPDATE_SETOPTION_SCRIPT_ADD_CLASS_20080321

		p->IsLoad = TRUE;
#if TESTSERVER == 1	

#ifdef UPDATE_SETOPTION_SCRIPT_ADD_CLASS_20080321	// 소환술사 추가
		char msg[512];
		wsprintf(msg, "%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
				 Index,p->Name,
				 p->SetOptionTable[0][0], p->SetOptionTable[0][1],
				 p->SetOptionTable[1][0], p->SetOptionTable[1][1],
				 p->SetOptionTable[2][0], p->SetOptionTable[2][1],
				 p->SetOptionTable[3][0], p->SetOptionTable[3][1],
				 p->SetOptionTable[4][0], p->SetOptionTable[4][1],
				 p->SetOptionTable[5][0], p->SetOptionTable[5][1],
				 p->SetExPOptionTable[0], p->SetExPOptionTable[1], 
				 p->SetFullOtionTable[0], p->SetFullOtionTable[1], 
				 p->SetFullOtionTable[2], p->SetFullOtionTable[3], p->SetFullOtionTable[4],
				 p->RequireClass[0], p->RequireClass[1], 
				 p->RequireClass[2], p->RequireClass[3],
				 p->RequireClass[4], p->RequireClass[5]);
#else	// UPDATE_SETOPTION_SCRIPT_ADD_CLASS_20080321
		char msg[512];
		wsprintf(msg, "%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
				 Index,p->Name,
				 p->SetOptionTable[0][0], p->SetOptionTable[0][1],
				 p->SetOptionTable[1][0], p->SetOptionTable[1][1],
				 p->SetOptionTable[2][0], p->SetOptionTable[2][1],
				 p->SetOptionTable[3][0], p->SetOptionTable[3][1],
				 p->SetOptionTable[4][0], p->SetOptionTable[4][1],
				 p->SetOptionTable[5][0], p->SetOptionTable[5][1],
				 p->SetExPOptionTable[0], p->SetExPOptionTable[1], 
				 p->SetFullOtionTable[0], p->SetFullOtionTable[1], 
				 p->SetFullOtionTable[2], p->SetFullOtionTable[3], p->SetFullOtionTable[4],
				 p->RequireClass[0], p->RequireClass[1], 
				 p->RequireClass[2], p->RequireClass[3],
				 p->RequireClass[4]);
#endif	// UPDATE_SETOPTION_SCRIPT_ADD_CLASS_20080321

		OutputDebugString(msg);

		wsprintf(msg,"%s\tOptionCount=\t%d\n", p->Name, p->SetOptionCount);
		OutputDebugString(msg);
#endif
	}
	return TRUE;
}
#endif


BOOL CSetItemOption::IsSetItem(int itemnum)
{
	if( itemnum < 0 || itemnum > MAX_ITEM-1 ) 
	{
		LogAdd("IsSetItem Check error: (itemnum:%d)", itemnum);
		return FALSE;
	}
	
	return m_SetItemTypeInfo[itemnum].IsLoad;
}

int	CSetItemOption::GetOptionTableIndex(int itemnum, int setoption)
{
	if( itemnum < 0 || itemnum > MAX_ITEM-1 ) 
	{
		LogAdd("GetOptionTableIndex Check error: (itemnum:%d)", itemnum);
		return -1;
	}

	if( setoption != 1 &&  setoption != 2 ) 
	{	// 해당 옵션값이 아니다
		LogAdd("GetOptionTableIndex setoption Check error: (itemnum:%d)", itemnum);
		return -1;
	}

	if( !m_SetItemTypeInfo[itemnum].IsLoad )
		return -1;			// 로드된 정보가 없다
	
	return m_SetItemTypeInfo[itemnum].OptionIndex[setoption-1];
}

char* CSetItemOption::GetSetOptionName(int optionindex)
{
	if( optionindex < 0 || optionindex > MAX_SETITEM_OPTION-1 ) 
	{
		LogAdd("GetSetOptionName Check error: (itemnum:%d)", optionindex);
		return "";
	}

	if( !m_SetItemOptionInfo[optionindex].IsLoad )
		return "";			// 로드된 정보가 없다

	return m_SetItemOptionInfo[optionindex].Name;
}


char* CSetItemOption::GetSetOptionName(int itemnum, int settype)
{
	if( itemnum < 0 || itemnum > MAX_ITEM-1 ) 
	{
		LogAdd("GetSetOptionName Check error: (itemnum:%d)", itemnum);
		return "";
	}
	
	if( !m_SetItemTypeInfo[itemnum].IsLoad )
	{	// 정보가 없다
		return "";
	}

	int optionindex = m_SetItemTypeInfo[itemnum].OptionIndex[settype-1];

	if( optionindex < 0 || optionindex > MAX_SETITEM_OPTION-1 ) 
	{
		LogAdd("GetSetOptionName Check error: (itemnum:%d)", optionindex);
		return "";
	}

	if( !m_SetItemOptionInfo[optionindex].IsLoad )
		return "";			// 로드된 정보가 없다

	return m_SetItemOptionInfo[optionindex].Name;
}

int CSetItemOption::GetSetOption(int optionindex, int optablenum, int& op1, int& op2, int& opvalue1, int& opvalue2, int Class, int ChangeUp)
{
	opvalue1 = 0;
	opvalue2 = 0;

	if( optionindex < 0 || optionindex > MAX_SETITEM_OPTION-1 ) 
	{
		LogAdd("GetSetOption Check error: (itemnum:%d)", optionindex);
		return FALSE;
	}

	if( !m_SetItemOptionInfo[optionindex].IsLoad )
		return FALSE;			// 로드된 정보가 없다

	if( optablenum >= m_SetItemOptionInfo[optionindex].SetOptionCount ) 
		return FALSE;			// 옵션에 대한 로드된 정보가 없다

	BOOL isRequireClass = IsRequireClass(optionindex, Class, ChangeUp);			

	if( optablenum < 6 )
	{
		op1 = m_SetItemOptionInfo[optionindex].SetOptionTable[optablenum][0];	
		opvalue1 = m_SetItemOptionInfo[optionindex].SetOptionTableValue[optablenum][0];	

		if( op1 > AT_SET_OPTION_TWO_HAND_SWORD_IMPROVE_DAMAGE )
		{	// 양손검 장비시 데미지 15% 증가 이후 부터 클래스 적용
			if( !isRequireClass )
			{
				op1 = -1;
			}
		}

		if( op1 != -1 )	
			op1 += AT_SET_OPTION_IMPROVE_STRENGTH;

		op2 = m_SetItemOptionInfo[optionindex].SetOptionTable[optablenum][1];
		opvalue2 = m_SetItemOptionInfo[optionindex].SetOptionTableValue[optablenum][1];	

		if( op2 > AT_SET_OPTION_TWO_HAND_SWORD_IMPROVE_DAMAGE )
		{	// 양손검 장비시 데미지 15% 증가 이후 부터 클래스 적용
			if( !isRequireClass )
			{
				op2 = -1;
			}
		}

		if( op2 != -1 )	op2 += AT_SET_OPTION_IMPROVE_STRENGTH;
	}
	else
	{
		op1 = m_SetItemOptionInfo[optionindex].SetExPOptionTable[optablenum-6];
		opvalue1 = m_SetItemOptionInfo[optionindex].SetExPOptionTableValue[optablenum-6];

		if( op1 > AT_SET_OPTION_TWO_HAND_SWORD_IMPROVE_DAMAGE )
		{	// 양손검 장비시 데미지 15% 증가 이후 부터 클래스 적용
			if( !isRequireClass )
			{
				op1 = -1;
			}
		}

		if( op1 != -1 )	op1 += AT_SET_OPTION_IMPROVE_STRENGTH;
		op2 = -1;
	}
	return TRUE;
}

int CSetItemOption::GetMaxSetOptionCount(int optionindex)
{
	if( optionindex < 0 || optionindex > MAX_SETITEM_OPTION-1 ) 
	{
		LogAdd("GetMaxOptionCount Check error: (itemnum:%d)", optionindex);
		return -1;
	}

	if( !m_SetItemOptionInfo[optionindex].IsLoad )
		return -1;			// 로드된 정보가 없다

	return m_SetItemOptionInfo[optionindex].SetOptionCount;
}


int	CSetItemOption::GetGetFullSetOption(int optionindex, int& op1, int& op2, int& op3, int& op4, int& op5, 
										int& opvalue1, int& opvalue2, int& opvalue3, int& opvalue4, int& opvalue5, int Class, int ChangeUp )
{
	opvalue1 = 0;
	opvalue2 = 0;
	opvalue3 = 0;
	opvalue4 = 0;
	opvalue5 = 0;

	if( optionindex < 0 || optionindex > MAX_SETITEM_OPTION-1 ) 
	{
		LogAdd("GetMaxOptionCount Check error: (itemnum:%d)", optionindex);
		return FALSE;
	}

	if( !m_SetItemOptionInfo[optionindex].IsLoad )
		return FALSE;			// 로드된 정보가 없다

	BOOL isRequireClass = IsRequireClass(optionindex, Class, ChangeUp);			

	op1 = m_SetItemOptionInfo[optionindex].SetFullOtionTable[0];
	opvalue1 = m_SetItemOptionInfo[optionindex].SetFullOtionTableValue[0];
	if( op1 > AT_SET_OPTION_TWO_HAND_SWORD_IMPROVE_DAMAGE )
	{	// 양손검 장비시 데미지 15% 증가 이후 부터 클래스 적용
		if( !isRequireClass )
		{
			op1 = -1;
		}
	}
	if( op1 != -1 )	op1 += AT_SET_OPTION_IMPROVE_STRENGTH;

	op2 = m_SetItemOptionInfo[optionindex].SetFullOtionTable[1];
	opvalue2 = m_SetItemOptionInfo[optionindex].SetFullOtionTableValue[1];
	if( op2 > AT_SET_OPTION_TWO_HAND_SWORD_IMPROVE_DAMAGE )
	{	// // 양손검 장비시 데미지 15% 증가 이후 부터 클래스 적용
		if( !isRequireClass )
		{
			op2 = -1;
		}
	}
	if( op2 != -1 )	op2 += AT_SET_OPTION_IMPROVE_STRENGTH;

	op3 = m_SetItemOptionInfo[optionindex].SetFullOtionTable[2];
	opvalue3 = m_SetItemOptionInfo[optionindex].SetFullOtionTableValue[2];
	if( op3 > AT_SET_OPTION_TWO_HAND_SWORD_IMPROVE_DAMAGE )
	{	// 양손검 장비시 데미지 15% 증가 이후 부터 클래스 적용
		if( !isRequireClass )
		{
			op3 = -1;
		}
	}
	if( op3 != -1 )	op3 += AT_SET_OPTION_IMPROVE_STRENGTH;

	op4 = m_SetItemOptionInfo[optionindex].SetFullOtionTable[3];
	opvalue4 = m_SetItemOptionInfo[optionindex].SetFullOtionTableValue[3];
	if( op4 > AT_SET_OPTION_TWO_HAND_SWORD_IMPROVE_DAMAGE )
	{	// 양손검 장비시 데미지 15% 증가 이후 부터 클래스 적용
		if( !isRequireClass )
		{
			op4 = -1;
		}
	}
	if( op4 != -1 )	op4 += AT_SET_OPTION_IMPROVE_STRENGTH;

	op5 = m_SetItemOptionInfo[optionindex].SetFullOtionTable[4];
	opvalue5 = m_SetItemOptionInfo[optionindex].SetFullOtionTableValue[4];
	if( op5 > AT_SET_OPTION_TWO_HAND_SWORD_IMPROVE_DAMAGE )
	{	// 양손검 장비시 데미지 15% 증가 이후 부터 클래스 적용
		if( !isRequireClass )
		{
			op5 = -1;
		}
	}
	if( op5 != -1 )	op5 += AT_SET_OPTION_IMPROVE_STRENGTH;

	return TRUE;
}

BOOL CSetItemOption::IsRequireClass(int optionindex, int Class, int ChangeUp)
{
	if( optionindex < 0 || optionindex > MAX_SETITEM_OPTION-1 ) 
	{
		LogAdd("GetMaxOptionCount Check error: (itemnum:%d)", optionindex);
		return FALSE;
	}

	if( !m_SetItemOptionInfo[optionindex].IsLoad )
		return FALSE;			// 로드된 정보가 없다

	if( Class < 0 || Class > MAX_CLASSTYPE-1 ) 
	{		
		return FALSE;
	}
	
	int requireclass = m_SetItemOptionInfo[optionindex].RequireClass[Class];
	if( requireclass == 0 ) return FALSE;
	if( requireclass > 1 )
	{	// 전직전용이면
		if( requireclass != ChangeUp+1 )
			return FALSE;
	}
	return TRUE;
}

BOOL CSetItemOption::CheckMixContition(int itemnum, int mixitemlevel)
{
	if( mixitemlevel == -1 )
		return FALSE;

	if( itemnum < 0 || itemnum > MAX_ITEM-1 ) 
	{
		LogAdd("MakeSetOption Check error: (itemnum:%d)", itemnum);
		return FALSE;
	}
	
	if( !m_SetItemTypeInfo[itemnum].IsLoad )
	{	// 정보가 없다
		return FALSE;
	}

	if( m_SetItemTypeInfo[itemnum].ChaosMixLevel[0] == mixitemlevel || 
		m_SetItemTypeInfo[itemnum].ChaosMixLevel[1] == mixitemlevel )
		return TRUE;

	return FALSE;
}

int	CSetItemOption::MakeSetOption(int itemnum, int mixitemlevel)
{
	if( itemnum < 0 || itemnum > MAX_ITEM-1 ) 
	{
		LogAdd("MakeSetOption Check error: (itemnum:%d)", itemnum);
		return 0;
	}
	
	if( !m_SetItemTypeInfo[itemnum].IsLoad )
	{	// 정보가 없다
		return 0;
	}

	if( m_SetItemTypeInfo[itemnum].ChaosMixLevel[0] == m_SetItemTypeInfo[itemnum].ChaosMixLevel[1] )
	{	// 같은 조건이므로, A, B 둘중 하나를 랜덤으로 준다
		return (rand()%2)+1;
	}	

	if( m_SetItemTypeInfo[itemnum].ChaosMixLevel[0] == mixitemlevel )
	{
		return 1;
	}

	if( m_SetItemTypeInfo[itemnum].ChaosMixLevel[1] == mixitemlevel )
	{
		return 2;
	}

	return 0;
}


int	CSetItemOption::GenRandomItemNum()
{
	int		iItemIndex;
	do 
	{
#ifdef ADD_RANDOM_RANGE_OF_ITEMINDEX_20050808
		int iItemType			= rand()%MAX_ITEM_TYPE;
		int iMaxItemSubIndex	= g_MaxItemIndexOfEachItemType[iItemType] <=0 ? MAX_ITEM_INDEX : g_MaxItemIndexOfEachItemType[iItemType];
		int iItemSubIndex		= rand()%iMaxItemSubIndex; 
		
		iItemIndex				= iItemType*MAX_ITEM_INDEX + iItemSubIndex;
#else
		iItemIndex = rand()%512;
#endif
		if( IsSetItem(iItemIndex) )
		{
			return iItemIndex;
		}
	} while(1);
	return 0;
}

int CSetItemOption::GenSetOption(int itemnum)
{
	if( itemnum < 0 || itemnum > MAX_ITEM-1 ) 
	{
		LogAdd("GenSetType Check error: (itemnum:%d)", itemnum);
		return 0;
	}	

	if( !m_SetItemTypeInfo[itemnum].IsLoad )
	{	// 정보가 없다
		return 0;
	}

	int		SetOption;

	if( m_SetItemTypeInfo[itemnum].OptionIndex[0] != 0 && 
		m_SetItemTypeInfo[itemnum].OptionIndex[1] != 0 )
	{
		SetOption = (rand()%2)+1;
	}
	else if( m_SetItemTypeInfo[itemnum].OptionIndex[0] != 0 )
	{
		SetOption = 1;
	}
	else
	{
		SetOption = 2;
	}

	if( rand()%100 < 80 )
		SetOption |= 0x04;
	else
		SetOption |= 0x08;

	return SetOption;
}
#endif