// GSDBSet.h: interface for the CGSDBSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GSDBSET_H__22255CC2_C2B4_44DB_A166_C1F57E107D79__INCLUDED_)
#define AFX_GSDBSET_H__22255CC2_C2B4_44DB_A166_C1F57E107D79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

class CGSDBSet  
{
public:
	CQuery	m_Query;

	
	CGSDBSet();
	virtual ~CGSDBSet();
	
	BOOL	Connect();

	DWORD	GetCount();
	BOOL	SetCount(int count);
	BOOL	CreateZen();
	BOOL	CreateItem(DWORD& sirial_number);
	BOOL	CreatePropertyItemInfo(DWORD serial, SDHP_PROPERTY_ITEMCREATE* lpMsg);
	int		GetPropertyItemInfo(DWORD serial, SDHP_LOAD_MEDALINFO_RESULT* lpMsg);
	int		GetItemSerial(DWORD& sirial_number, int MakeSeiralCount);
	int		CheckMuDBIdentification();
};

#endif // !defined(AFX_GSDBSET_H__22255CC2_C2B4_44DB_A166_C1F57E107D79__INCLUDED_)
