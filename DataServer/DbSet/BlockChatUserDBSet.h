#ifndef __BLOCKCHATUSERDBSET_H__
#define __BLOCKCHATUSERDBSET_H__
#pragma once

#include "..\Include\Sprodef.h"
#include "DBConBase.h"

class CBlockChatUserDBSet : public CDBConBase
{
public:
	CBlockChatUserDBSet();
	virtual ~CBlockChatUserDBSet();

	BOOL Connect();

	BOOL DSDB_SelectBlockChatUser(char* Name, LPSDHP_ANS_BLOCK_CHAT_USER_INFO lpSendMsg);
	BOOL DSDB_AddBlockChatUser(LPSDHP_REQ_ADD_BLOCK_CHAT_USER_INFO lpRecv);
	BOOL DSDB_DelBlockChatUser(LPSDHP_REQ_DEL_BLOCK_CHAT_USER_INFO lpRecv);

public:
	CQuery m_DBQuery;
};

#endif