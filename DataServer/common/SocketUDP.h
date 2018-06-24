#pragma once

#include <winsock2.h>
#include "IThread.h"

#pragma comment( lib, "ws2_32.lib" )

class CServerSocketUDP
{
public:
	CServerSocketUDP();
	virtual ~CServerSocketUDP();

	bool Init(WORD wPort);
	void DataSend(LPBYTE lpData, INT Size, SOCKADDR_IN & Dest);

	virtual void OnRecv(LPBYTE lpMsg, INT Size, SOCKADDR_IN & Sender) {};

protected:
	void RecvThread();
	friend DWORD __stdcall thread_udprecv(LPVOID lpArg);
private:
	SOCKET	m_Socket;
	LPBYTE	m_Recvbuf;
	LPBYTE  m_Sendbuf;
	int     m_dwLength;
	int		m_dwRecvOfs;
	int     m_dwSendLength;
	
	IThread	m_RecvThread;

//	PER_IO_OPERATION_DATA	m_PerIoSendData;

	SOCKADDR_IN		m_SockAddr;
};

#define DATA_BUFSIZE 2048

typedef struct {
   OVERLAPPED	Overlapped;
   WSABUF		DataBuf;
   CHAR			Buffer[DATA_BUFSIZE];
   DWORD		Bytes;
	int			lOfs; 
} PER_IO_OPERATION_DATA, * LPPER_IO_OPERATION_DATA;

class CClientSocketUDP
{
public:
	CClientSocketUDP();
	virtual ~CClientSocketUDP();

	bool Init(char * szIpAddress, WORD wPort);
	bool DataSend(LPBYTE lpData, INT Size);

	virtual void OnRecv(LPBYTE lpMsg, INT Size) {};

protected:
	void RecvThread();
	friend DWORD __stdcall thread_client_udp_recv(LPVOID lpArg);
private:
	SOCKET	m_Socket;
	LPBYTE	m_Recvbuf;
	LPBYTE  m_Sendbuf;
	int     m_dwLength;
	int		m_dwRecvOfs;
	int     m_dwSendLength;
	
	IThread	m_RecvThread;

	PER_IO_OPERATION_DATA	m_PerIoSendData;

	SOCKADDR_IN		m_SockAddr;
};
