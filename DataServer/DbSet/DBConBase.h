#ifndef __DBCONBASE_H__
#define __DBCONBASE_H__
#pragma once

class CDBConBase  
{
public:
	CQuery m_DBQuery;

public:
	CDBConBase();
	virtual ~CDBConBase();

	BOOL Connect(char* szConID, char* szConPass);
};

#endif