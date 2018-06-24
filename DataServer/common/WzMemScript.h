// WzMemScript.h: interface for the CWzMemScript class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WZMEMSCRIPT_H__0BFA7E3B_1FBE_467B_A975_6F8BA4B42F7B__INCLUDED_)
#define AFX_WZMEMSCRIPT_H__0BFA7E3B_1FBE_467B_A975_6F8BA4B42F7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "..\\include\\ReadScript.h"

class CWzMemScript  
{
	char*	m_pBuffer;	

	int		m_iBufferSize;
	int		m_iBufferCount;

	HANDLE	m_hFile;

	char*	m_Token;

	float    TokenNumber;
	char     TokenString[100];
	SMDToken CurrentToken;
public:
	CWzMemScript();
	virtual ~CWzMemScript();

	int			SetBuffer(char* buffer, int buffersize);

	void		SetScriptParsingBuffer(char* buffer, int size);

	SMDToken	GetToken();
	SMDToken	TokenType(){return CurrentToken;}
	int			GetNumber();
	char*		GetString();	
protected:
	int			GetC();
	void		UnGetC(int ch);	
};

#endif // !defined(AFX_WZMEMSCRIPT_H__0BFA7E3B_1FBE_467B_A975_6F8BA4B42F7B__INCLUDED_)
