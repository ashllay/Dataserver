#pragma once

typedef struct _ST_BLOCK_CHATTING_USER
{
	_ST_BLOCK_CHATTING_USER()
	{
		bIsUsed = false;
		btSlotNum = -1;
		memset(szCharName, 0, MAX_IDSTRING + 1);
	}

	void Clear()
	{
		bIsUsed = false;
		btSlotNum = -1;
		memset(szCharName, 0, MAX_IDSTRING + 1);
	}

	bool bIsUsed;
	BYTE btSlotNum;
	char szCharName[MAX_IDSTRING + 1];
};

struct SDHP_ANS_BLOCK_CHAT_USER_INFO
{
	PWMSG_HEAD2 h;
	int nUserIndex;
	char szCharName[11];
	char btUserCnt;
	_ST_BLOCK_CHATTING_USER BlockCharList[20];
};

struct SDHP_REQ_ADD_BLOCK_CHAT_USER_INFO
{
	PBMSG_HEAD2 h;
	int nUserIndex;
	char szCharName[11];
	_ST_BLOCK_CHATTING_USER szBlockChar;
};

struct SDHP_REQ_DEL_BLOCK_CHAT_USER_INFO
{
	PBMSG_HEAD2 h;
	int nUserIndex;
	char szCharName[11];
	_ST_BLOCK_CHATTING_USER szBlockChar;
};

typedef struct SDHP_REQ_BLOCK_CHAT_USER_INFO
{
	PBMSG_HEAD h;
	int iUserIndex;
	char szCharName[MAX_IDSTRING + 1];
}; typedef SDHP_REQ_BLOCK_CHAT_USER_INFO* LPSDHP_REQ_BLOCK_CHAT_USER_INFO;

class CBlockChatUserDBSet
{
public:

	CBlockChatUserDBSet();
	virtual ~CBlockChatUserDBSet();

	int Connect();
	bool DSDB_SelectBlockChatUser(char* Name, SDHP_ANS_BLOCK_CHAT_USER_INFO* lpSendMsg);
	int DSDB_AddBlockChatUser(SDHP_REQ_ADD_BLOCK_CHAT_USER_INFO* lpRecv);
	int DSDB_DelBlockChatUser(SDHP_REQ_DEL_BLOCK_CHAT_USER_INFO* lpRecv);

private:
	CQuery m_DBQuery;
};