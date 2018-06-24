#pragma once

class CWzMD5
{
public:
	CWzMD5();
	~CWzMD5();

	//
	//	MD5_EncodeString
	//
	PCHAR EncodeString(const char * szWord, int iKeyIndex);
	PBYTE RawEncodeString(const char * szWord, int iKeyIndex);
	DWORD MakeKey(const char * szHash);
};
