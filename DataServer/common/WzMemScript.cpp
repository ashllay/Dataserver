// WzMemScript.cpp: implementation of the CWzMemScript class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WzMemScript.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWzMemScript::CWzMemScript()
{

}

CWzMemScript::~CWzMemScript()
{

}

int	CWzMemScript::SetBuffer(char* buffer, int buffersize)
{
	SetScriptParsingBuffer(buffer, buffersize);
	return 1;
}

int CWzMemScript::GetC()
{
	if( m_iBufferCount >= m_iBufferSize )
		return EOF;

	return m_pBuffer[m_iBufferCount++];
}

void CWzMemScript::UnGetC(int ch)
{
	if( m_iBufferCount <= 0 )
		return;
	
	m_iBufferCount--;
	m_pBuffer[m_iBufferCount] = ch;
}

void CWzMemScript::SetScriptParsingBuffer(char* buffer, int size)
{
	m_pBuffer = buffer;
	m_iBufferSize = size;
	m_iBufferCount = 0;
}

int	CWzMemScript::GetNumber()
{	
	return	(int)TokenNumber;
}

char* CWzMemScript::GetString()
{
	return	TokenString;
}

SMDToken CWzMemScript::GetToken()
{
	unsigned char ch;
	TokenString[0] = '\0';
	do
	{
		if ( (ch =(unsigned char) GetC()) == (BYTE)EOF) return END;
		if (ch=='/' && (ch =(unsigned char) GetC() )=='/')	
		{
			while( (ch = (unsigned char) GetC()) != '\n' );
		}
	} while(  isspace(ch) );
	
	char *p, TempString[100];
	switch(ch)
	{	
	case '#':
		return CurrentToken = COMMAND;
	case ';':
		return CurrentToken = SEMICOLON;
	case ',':
		return CurrentToken = COMMA;
	case '{':
		return CurrentToken = LP;
	case '}':
		return CurrentToken = RP;
	case '0':	case '1':	case '2':	case '3':	case '4':
	case '5':	case '6':	case '7':	case '8':	case '9':
	case '.':	case '-':
		UnGetC(ch);
		p = TempString;
		while ( (  (ch = GetC() ) !=(BYTE)EOF) && (ch=='.' || isdigit(ch) || ch=='-') )
			*p++ = ch;
		*p = 0;
		TokenNumber = (float)atof(TempString);
		//			sscanf(TempString," %f ",&TokenNumber);
		return CurrentToken = NUMBER;
	case '"':
		p = TokenString;
		while ( (  (ch = GetC() ) !=(BYTE)EOF) && (ch!='"'))// || isalnum(ch)) )
			*p++ = ch;
		if (ch!='"')
			UnGetC(ch);
		*p = 0;
		return CurrentToken = NAME;
	default:
		if (isalpha(ch))	
		{
			p = TokenString;
			*p++ = ch;
			while ( (  (ch = GetC() ) !=(BYTE)EOF) && (ch=='.' || ch=='_' || isalnum(ch)) )
				*p++ = ch;
			UnGetC(ch);
			*p = 0;
			return CurrentToken = NAME;
		}
		return CurrentToken = SMD_ERROR;
	}
}