// wsJoinServer.h: interface for the CwsGameServer class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __WSJOINSERVER_H__
#define __WSJOINSERVER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "common\MyWinsockBase.h"


#define MAX_SOCKETINDEX		65536	// 소켓 인덱스 최대 개수

#define MAX_SOCKETBUFFER	100		// 소켓당 버퍼 최대 개수

#define MAX_SENDBUFSIZE 500000		// 보낼수 있는 버퍼의 최대 크기
#define MAX_RECVBUFSIZE	500000		// 받을수 있는 버퍼의 최대 크기

class CSocketBuffer
{
public:
	int		live;		// 
	char	Ip_addr[16];		// ip주소
	
	SOCKET	m_socket;	// 소켓 번호

	BYTE	m_SendBuf[MAX_SENDBUFSIZE];	//
	int		m_SendBufLen;			// 버퍼크기

	BYTE	m_RecvBuf[MAX_RECVBUFSIZE];	// 보낼 버퍼
	int		m_RecvBufLen;			// 보낼 버퍼 크기 

public:

	CSocketBuffer() 
	{
		Clear();
	};
	void Clear()
	{
		live = 0;
		memset(Ip_addr, 0, 16);
		memset(m_SendBuf, 0, MAX_SENDBUFSIZE);
		memset(m_RecvBuf, 0, MAX_RECVBUFSIZE);
		m_socket = INVALID_SOCKET;
		m_SendBufLen = 0;
		m_RecvBufLen = 0;
	};
};

class CwsJoinServer : public MyWinsockBase
{
public:
	int		m_SockIndex[MAX_SOCKETINDEX];	// 소켓당 유저 배열 인덱스
	
	CSocketBuffer	sb[MAX_SOCKETBUFFER];

	DWORD	m_WinClientMsg;

public:
	int SetSocketBuffer(int index, SOCKET socket, char * ip);
	BOOL AcceptSocket(SOCKET & clientSocket, IN_ADDR & cInAddr);
	int  DataRecv(SOCKET socket);
	BOOL FDWRITE_MsgDataSend(SOCKET socket);
	BOOL DataSend(short uindex, char *buf, int len);
	BOOL CreateServer(char *ip_addr, WORD port, DWORD WinServerMsg, DWORD WinClientMsg);
	
	CwsJoinServer();
	virtual ~CwsJoinServer();

};

#endif
