#include "MacroUtils.h"
#include "SocketUDP.h"

#define DEFAULT_BUFFER_LENGTH   4096

DWORD __stdcall thread_udprecv(LPVOID lpArg)
{
	CServerSocketUDP * pServerSocket = static_cast<CServerSocketUDP*>(lpArg);
	pServerSocket->RecvThread();
	return 0;
}

DWORD __stdcall thread_client_udp_recv(LPVOID lpArg)
{
	CClientSocketUDP * pServerSocket = static_cast<CClientSocketUDP*>(lpArg);
	pServerSocket->RecvThread();
	return 0;
}



CServerSocketUDP::CServerSocketUDP()
{
	m_dwRecvOfs = 0;
}

CServerSocketUDP::~CServerSocketUDP()
{
	m_RecvThread.Stop();
	WSACleanup();
}


bool CServerSocketUDP::Init(WORD wPort)
{
	WSADATA			wsa;

	if( WSAStartup(MAKEWORD(2,2), &wsa) != 0 ) {        
		return false;
    }

//	m_Socket = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, NULL);
	m_Socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);
    
	if( m_Socket == INVALID_SOCKET ) {        
		return false;
	}

	m_SockAddr.sin_port			= htons(wPort);
	m_SockAddr.sin_family		= AF_INET;
	m_SockAddr.sin_addr.s_addr	= htonl(INADDR_ANY);

	if( bind(m_Socket, (SOCKADDR *)&m_SockAddr, sizeof(m_SockAddr)) == SOCKET_ERROR ) {		
		return false;
	}
	
	m_Recvbuf = new BYTE[DEFAULT_BUFFER_LENGTH];

    if( m_Recvbuf == NULL ) {
		return false;
    }

	m_RecvThread.Bind(thread_udprecv, this);
	m_RecvThread.Start();

	return true;
}

void CServerSocketUDP::DataSend(LPBYTE lpData, INT Size, SOCKADDR_IN & Dest)
{
   	sendto(m_Socket, (char*)lpData, Size+1, 0, (SOCKADDR *)&Dest, sizeof(SOCKADDR_IN));
}

void CServerSocketUDP::RecvThread()
{
	int			ret;
    DWORD		dwSenderSize;
    SOCKADDR_IN	sender;	
	
	dwSenderSize = sizeof(sender);

	while( true )
	{		
		ret = recvfrom(m_Socket, (char*)m_Recvbuf+m_dwRecvOfs,
			DEFAULT_BUFFER_LENGTH-m_dwRecvOfs, 0, (SOCKADDR *)&sender, (int*)&dwSenderSize);

		if( ret != SOCKET_ERROR && ret != 0 )
		{
			m_dwLength  = ret;
			m_dwRecvOfs += ret;
			this->OnRecv(m_Recvbuf, ret, sender);
		}
		Sleep(1);
	}
}

// -------------------------------------------------------------------------------------------------------------
//
// -------------------------------------------------------------------------------------------------------------

CClientSocketUDP::CClientSocketUDP()
{
	m_dwRecvOfs = 0;
}

CClientSocketUDP::~CClientSocketUDP()
{
	m_RecvThread.Stop();
	WSACleanup();
}


bool CClientSocketUDP::Init(char * szIpAddress, WORD wPort)
{
	WSADATA	wsa;
	ULONG	HostAddr = inet_addr(szIpAddress);

	if( WSAStartup(MAKEWORD(2,2), &wsa) != 0 ) {        
		return false;
    }

	m_Socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);
    
	if( m_Socket == INVALID_SOCKET ) {        
		return false;
	}

	if( HostAddr == INADDR_NONE )
	{
		hostent *host = gethostbyname(szIpAddress);
		HostAddr = *reinterpret_cast<ULONG*>(host->h_addr_list[0]);
	}

	if( HostAddr == INADDR_NONE ) {
		return false;
	}

	m_SockAddr.sin_port			= htons(wPort);
	m_SockAddr.sin_family		= AF_INET;
	m_SockAddr.sin_addr.s_addr	= HostAddr;
	
	m_Recvbuf = new BYTE[DEFAULT_BUFFER_LENGTH];

    if( m_Recvbuf == NULL ) {
		return false;
    }

	m_RecvThread.Bind(thread_client_udp_recv, this);
	m_RecvThread.Start();

	return true;
}

bool CClientSocketUDP::DataSend(LPBYTE lpData, INT Size)
{
	DWORD Ret;

	ZeroMemory(&(m_PerIoSendData.Overlapped), sizeof(OVERLAPPED));
	
	memcpy(m_PerIoSendData.Buffer, lpData, Size);
	
	m_PerIoSendData.lOfs		= Size;
	m_PerIoSendData.DataBuf.buf = m_PerIoSendData.Buffer;
	m_PerIoSendData.DataBuf.len = m_PerIoSendData.lOfs;
		
	Ret = WSASendTo(m_Socket, 
					&(m_PerIoSendData.DataBuf), 
					1, 
					(LPDWORD)&Size, 
					0, 
					(SOCKADDR*)&m_SockAddr, 
					sizeof(m_SockAddr), 
					&(m_PerIoSendData.Overlapped), 
					NULL);

	if( Ret == 0 ) {
		return true;
	}
	return false;
}

void CClientSocketUDP::RecvThread()
{
	int			ret;
    DWORD		dwSenderSize;
    SOCKADDR_IN	sender;	
	
	dwSenderSize = sizeof(sender);

	while( true )
	{		
		ret = recvfrom(m_Socket, (char*)m_Recvbuf+m_dwRecvOfs,
			DEFAULT_BUFFER_LENGTH-m_dwRecvOfs, 0, (SOCKADDR *)&sender, (int*)&dwSenderSize);

		if( ret != SOCKET_ERROR && ret != 0 )
		{
			m_dwLength  = ret;
			m_dwRecvOfs += ret;
			this->OnRecv(m_Recvbuf, ret);
		}
		Sleep(1);
	}
}

