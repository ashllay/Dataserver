#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"

class CBlockChatUserDBSet : public CDBConBase
{
public:

	CBlockChatUserDBSet();
	virtual ~CBlockChatUserDBSet();

	int Connect(); // idb
	bool DSDB_SelectBlockChatUser(char *Name, SDHP_ANS_BLOCK_CHAT_USER_INFO *lpSendMsg); // idb
	int DSDB_AddBlockChatUser(SDHP_REQ_ADD_BLOCK_CHAT_USER_INFO *lpRecv); // idb
	int DSDB_DelBlockChatUser(SDHP_REQ_DEL_BLOCK_CHAT_USER_INFO *lpRecv); // idb
};