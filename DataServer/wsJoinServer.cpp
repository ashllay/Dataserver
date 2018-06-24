// wsGameServer.cpp: implementation of the CwsJoinServer class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Include\ProDef.h"
#include "Protocol.h"
#include "wsJoinServer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CwsJoinServer::CwsJoinServer()
{

	int n;

	for( n=0; n<MAX_SOCKETINDEX; n++) m_SockIndex[n] = -1;
}

CwsJoinServer::~CwsJoinServer()
{

}

BOOL CwsJoinServer::CreateServer(char *ip_addr, WORD port, DWORD WinServerMsg, DWORD WinClientMsg)
{
	sockaddr_in	addr;
	int			nResult;

#ifdef _DEBUG
	if( m_hWnd == NULL ) { LogAdd("윈도우 핸들 에러"); return FALSE; }
#endif
	memset(&addr, 0, sizeof(sockaddr_in));
	
	addr.sin_family			= PF_INET;
    addr.sin_addr.s_addr	= htonl( INADDR_ANY );
	addr.sin_port			= htons( port );
 
	nResult = bind(m_socket, (LPSOCKADDR)&addr, sizeof(addr) );
    if( nResult == SOCKET_ERROR ) 
	{
		LogAdd("Server bind error %d", WSAGetLastError());
		closesocket(m_socket);
		return FALSE;
    }

	nResult = listen( m_socket, 8 );
    if( nResult == SOCKET_ERROR) {
		closesocket(m_socket);
		LogAdd("Server listen error %d", WSAGetLastError());
		return FALSE;
    }

	nResult = WSAAsyncSelect( m_socket, m_hWnd, WinServerMsg, FD_READ|FD_WRITE|FD_ACCEPT|FD_CLOSE);
    if( nResult == SOCKET_ERROR) {
		closesocket(m_socket);
		LogAdd("Server WSAAsyncSelect error %d", WSAGetLastError());
        return FALSE;
    }
	//cLogProc.Add("서버 소켓 CREATE");

	m_WinClientMsg = WinClientMsg;
	return TRUE;
}

BOOL CwsJoinServer::AcceptSocket(SOCKET & clientSocket, IN_ADDR	& cInAddr)
{
	SOCKET		cSocket;
	SOCKADDR_IN cAddr;
	int			Len;
	//int			nResult;
	
	Len = sizeof(SOCKADDR_IN);
	cSocket = accept( m_socket, (LPSOCKADDR)&cAddr, &Len);
	if( cSocket != INVALID_SOCKET )
	{
		memcpy( &cInAddr, &cAddr.sin_addr.s_addr, 4 );
		//LogAdd("사용자가 접속요청(Accept) Address:%s, port %d socket number:%d", inet_ntoa(clientIn), ntohs(clientAddr.sin_port) , clientSocket);
		/*nResult = WSAAsyncSelect( cSocket, m_hWnd, m_WinClientMsg, FD_READ|FD_WRITE|FD_CLOSE );
		if( nResult == SOCKET_ERROR) {
			closesocket(cSocket);
			//LogAdd("Server WSAAsyncSelect error %d", WSAGetLastError());
			return FALSE;
		}*/
	}
	clientSocket = cSocket;
	return TRUE;
}


#include "giocp.h"


BOOL CwsJoinServer::DataSend(short uindex, char *buf, int len)
{
	return IoSend(uindex, (LPBYTE)buf, len);

	int nResult;
	int nDx=0;
	int nLeft;
	
	SOCKET socket = sb[uindex].m_socket;
	
	nLeft = len;
	LPBYTE sendbuf;
	int *  sendbuflen;
				
	sendbuf		= sb[uindex].m_SendBuf;
	sendbuflen	= &sb[uindex].m_SendBufLen;
				
	if( ((*sendbuflen)+len) > MAX_SENDBUFSIZE ) {
		LogAdd("복사할 양이 버퍼보다 더 크다.");
		(*sendbuflen) = 0;
		Close(socket);
		return FALSE;
	}
	
	memcpy(sendbuf+(*sendbuflen), buf, len);
	(*sendbuflen) += len;
	while( 1 )
	{
		nResult = send(socket, (char*)sendbuf+nDx, (*sendbuflen)-nDx, 0);
		if( nResult == SOCKET_ERROR )
		{ //line:30
			if( WSAGetLastError() != WSAEWOULDBLOCK )
			{
				//MessageBox(m_hWnd, "Send Error", "socket error", MB_OK);
				//cLogProc.Add("send() 에러 %d 로 인해 접속 종료시킴", WSAGetLastError());
				/*if( FreeSocketBuffer(socket)== 1 )
				{
					//cLogProc.Add("사용자를 찾지 못했다. Socket(%d)", socket);
				}*/
				LogAdd("error : %d (%s %d)", WSAGetLastError(), __FILE__, __LINE__);
				Close(socket);
				return FALSE;
			}
			else
			{//line:42
				
				if( ( (*sendbuflen)+nLeft) > MAX_SENDBUFSIZE ) 
				{
					//cLogProc.Add("(%d) 버퍼가 꽉차서 더이상 저장할수 없다.. 사용자 접속 종료 시킨다. %d, %d", uindex, ((*sendbuflen)+nLeft) , MAX_SENDBUF);
					//FreeSocketBuffer(socket);
					LogAdd("error : (%d) 버퍼가 꽉차서 더이상 저장할수 없다.. 사용자 접속 종료 시킨다. %d", uindex, ((*sendbuflen)+nLeft));
					Close(socket);
					return FALSE;
				}
				memcpy(sendbuf, sendbuf+nDx, (*sendbuflen)-nDx);
				//cLogProc.Add("User(%d) senbuf에 복사 ofs:%d  len:%d", uindex, (*sendbuflen), nLeft);
				//memcpy((sendbuf+(*sendbuflen)), buf, nLeft);
				//(*sendbuflen) += nLeft;
				//LogAdd("Copy %d", nLeft);
				//cLogProc.Add("send() WSAEWOULDBLOCK : %d", WSAGetLastError());
				LogAdd("Copy : nLeft:%d len:%d, nDx:%d", nLeft, (*sendbuflen), nDx);
				return TRUE;
				break;
			}
		}
		else {
			if( nResult == 0 ) {
				//cLogProc.Add("send()  result is zero", WSAGetLastError());
				break;
			}
#ifdef _DEBUG_PROTOCOL
			LogAddHeadHex(5, buf, len);
#endif
		}
		nDx += nResult;
		nLeft -= nResult;
		if( nLeft <= 0 ) break;
	}	
	(*sendbuflen) -= nDx;
	LogAdd("Send ok:%d", nDx);
	return TRUE;
}

BOOL CwsJoinServer::FDWRITE_MsgDataSend(SOCKET socket)
{
	int nResult;
	int nDx;
	
	short	uindex		= m_SockIndex[socket];
	LPBYTE	sendbuf		= sb[uindex].m_SendBuf;
	int *	sendbuflen  = &sb[uindex].m_SendBufLen;
	int		nLeft		= (*sendbuflen);

	LogAdd("FD_WRITE %d", (*sendbuflen));

	nDx = 0;
	
	//cLogProc.Add("fd_write 메시지 접수 User(%d) socket(%d)", uindex, socket);
	while( (*sendbuflen) > 0 ) 
	{
		nResult = send(socket, (char*)sendbuf+nDx, (*sendbuflen)-nDx, 0);
		//cLogProc.Add("fd_write %d byte 메시지 보냄 ", nResult);		
		if( nResult == SOCKET_ERROR )
		{
			if( WSAGetLastError() != WSAEWOULDBLOCK )
			{
				//cLogProc.Add("FD_WRITE send() 에러 %d", WSAGetLastError());
				
				//--FreeSocketBuffer(socket);
				Close(socket);
				return FALSE;
			}
			else 
			{
				//cLogProc.Add("FD_WRITE send() WSAEWOULDBLOCK : %d", WSAGetLastError());
				break;
			}
		}
		else {
			if( nResult <= 0 ) {
				//cLogProc.Add("send() result is zero %d", WSAGetLastError());			
				
				/*if( FreeSocketBuffer(socket) == 1 )
				{
					//cLogProc.Add("사용자를 찾지 못했다.");
				}
				*/				
				Close(socket);
				return FALSE;
			}			
#ifdef _DEBUG_PROTOCOL
			LogAddHeadHex(3, (char*)sendbuf, (*sendbuflen)-nDx);
#endif
		}
		nDx += nResult;
		(*sendbuflen) -= nResult;		
	}
	return TRUE;
}

int CwsJoinServer::DataRecv(SOCKET socket)
{
	int		nResult;
	short 	uindex;
	LPBYTE	recvbuf;
	int *	recvbuflen;

	uindex = m_SockIndex[socket];

#ifdef _DEBUG
	if( uindex < 0 ) { LogAdd("사용자 인덱스가 잘못되었습니다."); return 1; }
#endif
	
	recvbuf = sb[uindex].m_RecvBuf;
	recvbuflen = &sb[uindex].m_RecvBufLen;

	nResult = recv( socket, (char*)recvbuf+(*recvbuflen), MAX_RECVBUFSIZE-(*recvbuflen), 0);
	
	if( nResult == 0 ) //접속이 끊겼씀.
	{
		LogAdd("Recv result is zero (%d)", WSAGetLastError());
		return 1;
	}
	if( nResult == SOCKET_ERROR )
	{
		if( WSAGetLastError() == WSAEWOULDBLOCK )
		{
			return 1;
		}
		else {
			//cLogProc.Add("recv() 받기 에러 %d", WSAGetLastError());
		}
		return 1;
	}

#ifdef _DEBUG_PROTOCOL
	LogAddHeadHex(6, (char*)recvbuf+(*recvbuflen), nResult);
#endif
	
	(*recvbuflen) += nResult;

	if( (*recvbuflen) < 3 ) {
		return 3;	
	}

	int lOfs=0;
	int size=0;
	BYTE headcode;
	while(1)
	{
		if( recvbuf[lOfs] == 0xC1 ) //
		{
			LPPBMSG_HEAD lphead=(LPPBMSG_HEAD)(recvbuf+lOfs);
			size = lphead->size;
			headcode = lphead->headcode;
		}
		else if( recvbuf[lOfs] == 0xC2 ) //
		{
			LPPWMSG_HEAD lphead=(LPPWMSG_HEAD)(recvbuf+lOfs);
			size = ((WORD)(lphead->sizeH)<<8);
			size |= (WORD)(lphead->sizeL);
			headcode = lphead->headcode;
		}
		else  // 헤더가 맞지 않다면..
		{
			LogAdd("헤더가 올바르지 않다.(%s %d)lOfs:%d, size:%d", __FILE__, __LINE__, lOfs, (*recvbuflen));
			(*recvbuflen) = 0;
			Close(this->m_socket);
			return FALSE;
		}

		if( size <= 0 )
		{
			//cLogProc.Add("size가 %d이다.", lphead->size);
			return FALSE;
		}
		if( size <= (*recvbuflen) )	// 데이터가 크기만큼 존재하면..
		{
			ProtocolCore(headcode, (recvbuf+lOfs), size, (short)uindex);
			lOfs += size;
			(*recvbuflen) -= size;			
			if( (*recvbuflen) <= 0 ) break;
		}			
		else {	// recv 데이터가 아직 완성되지 않았다면..
			if( lOfs > 0 )  // 하나이상 데이터를 보낸 후라면..
			{
				if( (*recvbuflen) < 1 ) 
				{
					//cLogProc.Add("(*recvbuflen) 이 1보다 작다..");
					break;
				}
				else {
					memcpy(recvbuf, (recvbuf+lOfs), (*recvbuflen)); // 남은만큼 복사한다.
					LogAdd("Copy : %d %d", lOfs, (*recvbuflen));
					break;
				}
			}
			break;
		}
	}
	return 0;
}

int CwsJoinServer::SetSocketBuffer(int index, SOCKET socket, char *ip)
{
	sb[index].Clear();
	sb[index].live = 1;	
	sb[index].m_socket = socket;
	strcpy(sb[index].Ip_addr, ip);
	return TRUE;
}
