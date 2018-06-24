// MuNameCheck.h: interface for the CMuNameCheck class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUNAMECHECK_H__5779723C_3E2F_460C_92EF_C7EA097E1C54__INCLUDED_)
#define AFX_MUNAMECHECK_H__5779723C_3E2F_460C_92EF_C7EA097E1C54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if GAME_VERSION >= G_V_S2
#define MODIFY_MAX_MUNAME_20071210
#endif

#ifdef MODIFY_MAX_MUNAME_20071210
#define MAX_MUNAME	3500//2000
#else
#define MAX_MUNAME	1000
#endif
#define MAX_MUNAME_STRING	20

class CMuNameCheck  
{
	char m_szName[MAX_MUNAME][MAX_MUNAME_STRING];
	int  m_nMuNameCount;

public:
	CMuNameCheck();
	virtual ~CMuNameCheck();

	BOOL CmpString( char *cmp_name );

	BOOL NameAdd(char * sz_name);
	BOOL NameLoad(char * filename);
	BOOL ItemNameLoad(char * filename);
	BOOL MonsterNpcLoad(char * filename);
	BOOL SkillLoad(char * filename);
	BOOL SkillNameLoad(char * filename);

};

#endif // !defined(AFX_MUNAMECHECK_H__5779723C_3E2F_460C_92EF_C7EA097E1C54__INCLUDED_)
