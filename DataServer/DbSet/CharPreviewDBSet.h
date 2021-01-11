#ifndef __CHARPREVIEWDBSET_H__
#define __CHARPREVIEWDBSET_H__
#pragma once

class CCharPreviewDBSet
{
public:
	CCharPreviewDBSet();
	virtual ~CCharPreviewDBSet();

	BOOL Conenect();

	BOOL GetChar(char* Name, char* AccountId, int& _level, int& _class, LPBYTE Inventory, BYTE& _ctlcode, BYTE& _dbverstion, BYTE& _pkLevel, BYTE& _btGuildStatus);
	BOOL GetRealNameAndServerCode(char* szUBFName, char* szRealName, int* ServerCode, BOOL IsUBFServer);

public:
	CQuery m_DBQuery;
};

#endif