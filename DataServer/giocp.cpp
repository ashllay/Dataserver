#include "stdafx.h"
#include <stdio.h>
//#include "Include\ProDef.h"
#include <winsock2.h>
#include "Protocol.h"
#include "DelayHandler.h"
#include "WzQueue.h"
#include "giocp.h"
#include "ServerPrc.h"
#include "WZIPCheck.h"

enum {
	RECV_IO,
	SEND_IO
} SOCKET_FLAG;


HANDLE			g_CompletionPort=NULL;

DWORD           g_dwThreadCount = 0;        //worker thread count 

WZQueue	WzRecvQ2;
WZQueue	WzRecvQ3;
WZQueue	WzRecvQ4;

CRITICAL_SECTION criti;

WZQueue	WzSendQ;
WZQueue	WzRecvQ;

HANDLE          g_ThreadHandles[MAX_WORKER_THREAD]; 

CRITICAL_SECTION    g_CriticalSection;      // guard access to the global context list 

LPPER_SOCKET_CONTEXT	g_pCtxtList = NULL;
LPPER_SOCKET_CONTEXT	g_pCtxtListHead = NULL;

int		IoSend(int aIndex, LPBYTE lpMsg, DWORD dwSize);
BOOL	RecvDataParse(LPPER_IO_CONTEXT	lpIOContext, int uIndex);
void	CloseClient ( LPPER_SOCKET_CONTEXT lpPerSocketContext, BOOL bGraceful ) ;

DWORD	WINAPI IocpServerWorker(LPVOID p);
DWORD	WINAPI ServerRecvWorkerThread(LPVOID p);
DWORD   WINAPI ServerWorkerThread(LPVOID CompletionPortID);
DWORD   WINAPI ServerRecvWorkerThreadSecond(LPVOID p);
DWORD   WINAPI ServerRecvWorkerThreadThird(LPVOID p);
DWORD   WINAPI ServerRecvWorkerThreadFourth(LPVOID p);

LPPER_SOCKET_CONTEXT ContextAllocate(SOCKET sd, int ClientIndex);
void CtxtListAddTo(LPPER_SOCKET_CONTEXT lpPerSocketContext);
BOOL CtxtListDeleteFrom(LPPER_SOCKET_CONTEXT lpPerSocketContext);
void CtxtListFree();

SOCKET			g_Listen = INVALID_SOCKET;
int				g_ServerPort;

int CreateGIocp(int server_port)
{
	DWORD	ThreadID;
	HANDLE	ThreadHandle;

	g_ServerPort = server_port;
	if ((ThreadHandle = CreateThread(NULL, 0, IocpServerWorker, (LPVOID)NULL,
			0, &ThreadID)) == NULL)
	{
		LogAdd("CreateThread() failed with error %d", GetLastError());
		return FALSE;
	}

	CloseHandle(ThreadHandle );
	return TRUE;
}

BOOL CreateListenSocket(void) 
{	
	SOCKADDR_IN InternetAddr;
	int			nRet;

	g_Listen = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (g_Listen == INVALID_SOCKET)
	{
		LogAdd("WSASocket() failed with error %d", WSAGetLastError());
		return FALSE;
	} 
	
	InternetAddr.sin_family			= AF_INET;
	InternetAddr.sin_addr.s_addr	= htonl(INADDR_ANY);
	InternetAddr.sin_port			= htons(g_ServerPort);
	
	nRet = bind(g_Listen, (PSOCKADDR) &InternetAddr, sizeof(InternetAddr));
	if( nRet == SOCKET_ERROR )
	{
		LogAdd("bind() failed with error %d", WSAGetLastError());
		return FALSE;
	}

	nRet = listen(g_Listen, 5);

	if (nRet == SOCKET_ERROR)
	{
		LogAdd("listen() failed with error %d", WSAGetLastError());
		return FALSE;
	} 
	return TRUE;
}

DWORD WINAPI IocpServerWorker(LPVOID p)
{
	SYSTEM_INFO SystemInfo;
	DWORD		ThreadID;
	SOCKET		Accept;
	LPPER_SOCKET_CONTEXT lpPerSocketContext = NULL;
	int			nRet;
	int			ClientIndex;
	SOCKADDR_IN cAddr;
	IN_ADDR		cInAddr;
	int			cAddrlen = sizeof( cAddr );

	DWORD RecvBytes;
	DWORD Flags=0;
		
	InitializeCriticalSection(&criti);

	GetSystemInfo(&SystemInfo);
	g_dwThreadCount = SystemInfo.dwNumberOfProcessors * 2;

	if(g_dwThreadCount > MAX_WORKER_THREAD) //webzen season 6.2 fix
	{
		g_dwThreadCount = MAX_WORKER_THREAD;
		LogAdd(" **** Worker Thread Max Count Fix 16ea ****");
	}
	
    __try  
    { 
		g_CompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
		if ( g_CompletionPort == NULL)
		{
			LogAdd("CreateIoCompletionPort failed with error: %d", GetLastError());
			__leave;
		}
		
		for(DWORD dwCPU = 0; dwCPU < g_dwThreadCount; dwCPU++)
		{
			HANDLE ThreadHandle;
			// Create a server worker thread and pass the completion port to the thread.
			
			ThreadHandle = CreateThread(NULL, 0, ServerWorkerThread, g_CompletionPort, 0, &ThreadID);
			if ( ThreadHandle == NULL)
			{
				LogAdd("CreateThread() failed with error %d", GetLastError());
				__leave;
			}
			g_ThreadHandles[dwCPU] = ThreadHandle;
		}

		HANDLE ThreadHandle; //ebp-7c
		ThreadHandle = CreateThread(NULL, 0, ServerRecvWorkerThread, (LPVOID)NULL,0, &ThreadID);
		if (ThreadHandle == NULL)
		{
			LogAdd("CreateThread() failed with error %d", GetLastError());
			__leave;
		}

		if(SetThreadPriority(ThreadHandle, THREAD_PRIORITY_HIGHEST) == FALSE) //webzen season 6.2 add-on
		{
			LogAdd("SetThreadPriority() failed with error %d", GetLastError());
		}

		ThreadHandle = CreateThread(NULL, 0, ServerRecvWorkerThreadSecond, (LPVOID)NULL, 0, &ThreadID); //webzen season6.2 add-on
		if (ThreadHandle == NULL)
		{
			LogAdd("RecvWorkerthread Second CreateThread() failed with error %d", GetLastError());
			__leave;
		}

		ThreadHandle = CreateThread(NULL, 0, ServerRecvWorkerThreadThird, (LPVOID)NULL, 0, &ThreadID); //webzen season6.2 add-on
		if (ThreadHandle == NULL)
		{
			LogAdd("RecvWorkerthread Third CreateThread() failed with error %d", GetLastError());
			__leave;
		}

		ThreadHandle = CreateThread(NULL, 0, ServerRecvWorkerThreadFourth, (LPVOID)NULL, 0, &ThreadID); //webzen season6.2 add-on
		if (ThreadHandle == NULL)
		{
			LogAdd("RecvWorkerthread Fourth CreateThread() failed with error %d", GetLastError());
			__leave;
		}
		
		if (!CreateListenSocket() )
			__leave;

		while(TRUE)		
		{
			Accept = WSAAccept(g_Listen, (LPSOCKADDR)&cAddr, &cAddrlen, NULL, 0);
			if (Accept==SOCKET_ERROR)
			{
				EnterCriticalSection(&criti);
				LogAdd("WSAAccept() failed with error %d", WSAGetLastError());
				LeaveCriticalSection(&criti);
				__leave;
			}

			int SocketData = MSG_PARTIAL;

			if(setsockopt(Accept, SOL_SOCKET, SO_RCVBUF, (char*)&SocketData, 4) == SOCKET_ERROR) //webzen season6.2 add-on
			{
				EnterCriticalSection(&criti);
				LogAdd("setsockopt() failed with error %d", WSAGetLastError());
				LeaveCriticalSection(&criti);
				__leave;
			}

			EnterCriticalSection(&criti);

			memcpy( &cInAddr, &cAddr.sin_addr.s_addr, 4 );
		
			if(g_WZIPCheck.CheckIP(inet_ntoa(cInAddr)) == FALSE) //webzen season6.2 add-on
			{
				closesocket(Accept);
				LeaveCriticalSection(&criti);
				LogAddTD("[ANTI-HACKING] Attempted to connect illegal IP : %d.%d.%d.%d ", cInAddr.S_un.S_un_b.s_b1, cInAddr.S_un.S_un_b.s_b2, cInAddr.S_un.S_un_b.s_b3, cInAddr.S_un.S_un_b.s_b4);
				continue;
			}
			
			ClientIndex = gSObjAdd(Accept, inet_ntoa(cInAddr));

			LogAddTD("UserIndex [%d] Connected IP : %d.%d.%d.%d ", ClientIndex, cInAddr.S_un.S_un_b.s_b1, cInAddr.S_un.S_un_b.s_b2, cInAddr.S_un.S_un_b.s_b3, cInAddr.S_un.S_un_b.s_b4);
			
			if( ClientIndex == -1 ) 
			{
				LogAdd("Error : Max User Index");
				closesocket(Accept);
				LeaveCriticalSection(&criti);
				continue;
			}

			LogAdd("Socket number %d connected", Accept);

			lpPerSocketContext = UpdateCompletionPort(Accept, ClientIndex, TRUE);
			if( lpPerSocketContext == FALSE )
			{ 
				LogAdd("CreateIoCompletionPort failed with error %d", GetLastError());				
				LeaveCriticalSection(&criti);
				__leave;
			}
			
			gSObj[ClientIndex].lpPerSocketContext = lpPerSocketContext;

			lpPerSocketContext->nIndex = ClientIndex;

			nRet = WSARecv(Accept, &(lpPerSocketContext->IOContext[0].wsabuf), 1, &RecvBytes, &Flags,
				&(lpPerSocketContext->IOContext[0].Overlapped), NULL);
			
			if( nRet == SOCKET_ERROR && WSAGetLastError() != ERROR_IO_PENDING )
			{
				LogAdd("WSARecv() failed with error %d", WSAGetLastError());
				//gSObj[ClientIndex].lpPerSocketContext->IOContext[0].nWaitIO = 4;
				CloseClient(lpPerSocketContext, FALSE);
				LeaveCriticalSection(&criti);
				continue;
			}
			else
			{
				//gSObj[ClientIndex].lpPerSocketContext->IOContext[0].nWaitIO = 1;
				lpPerSocketContext->dwIOCount++; //gSObj[ClientIndex].lpPerSocketContext->dwIOCount++;
			}
			LeaveCriticalSection(&criti);
		}	// while
	}	// __try
	__finally  
	{
		if( g_CompletionPort )
		{
			for (DWORD i = 0; i < g_dwThreadCount; i++) 
					PostQueuedCompletionStatus(g_CompletionPort, 0, 0, NULL); 
		}

		CtxtListFree();

		if( g_CompletionPort )
		{
			CloseHandle(g_CompletionPort);
			g_CompletionPort = NULL;
		}
		if (g_Listen != INVALID_SOCKET)  
		{ 
            closesocket(g_Listen);  
            g_Listen = INVALID_SOCKET; 
		} 
	}
	return TRUE;
}

DWORD WINAPI ServerRecvWorkerThread(LPVOID p)
{
	BYTE RecvData[MAX_BUFF_SIZE]; //0
	unsigned int nSize=0; //4
	BYTE headcode; //8
	int  uindex; //c
	int	 loopN; //10

	int  iSessionId; //14
	bool bProcessPacket; //18

	int  nCount=0; //1C

	while(TRUE)
	{
		EnterCriticalSection(&criti);

		loopN = WzRecvQ.GetCount();	

		if( loopN > MAX_NODE-1 )
		{
			loopN = MAX_NODE-1;
			LogAdd("error : Loop MAX %s %d", __FILE__, __LINE__);
		}
		LeaveCriticalSection(&criti);
		if( loopN > 0 )
		{
#ifdef DEBUG_IOCP_LOG
			DWORD dwTime = GetTickCount();
#endif
			//for( int n=0; n<loopN; n++)
			{
				if( WzRecvQ.GetFromQueue((LPBYTE)RecvData, &nSize, &headcode, &uindex, &iSessionId) == TRUE )
				{
					bProcessPacket = true;
					if(iSessionId != g_DelayHandler.GetQuerySessionId())
					{
						if(g_DelayHandler.CheckHeadCode(headcode) == false)
						{
							bProcessPacket = false;
							LogAddTD("[DelayHandler] Drop Delayed Packet -> Head : %X", headcode);
						}
						else
						{
							LogAddTD("[DelayHandler] Process Delayed Packet -> Head : %X", headcode);
						}
					}
					if(bProcessPacket != false)
					{
						ProtocolCore(headcode, RecvData, nSize, uindex);
					}
				}
			}
#ifdef DEBUG_IOCP_LOG
			LogAdd("[PacketLog] OUT [0x%02X] %u", headcode[0], GetTickCount() - TickCount);
#endif
			//LogAdd("Process End : [%d]", GetTickCount() - dwTime);
		}
		Sleep(1);
	}
	return TRUE;
}

DWORD WINAPI ServerWorkerThread(LPVOID CompletionPortID)
{
	HANDLE	CompletionPort = (HANDLE) CompletionPortID; //loc1
	DWORD	dwIoSize; //loc2
	DWORD	RecvBytes; //loc3
	DWORD	Flags; //loc4
	DWORD	dwSendNumBytes = 0; //loc5
	BOOL	bSuccess = FALSE; //loc6 
	int		nRet; //loc7
	//int     ClientIndex;

	LPPER_SOCKET_CONTEXT	lpPerSocketContext = NULL; //loc8
	LPOVERLAPPED			lpOverlapped = NULL; //loc9
	LPPER_IO_CONTEXT		lpIOContext = NULL; //loc10

	while(TRUE)
	{
		bSuccess = GetQueuedCompletionStatus(
			CompletionPort,
			&dwIoSize,
			(LPDWORD)&lpPerSocketContext,
			&lpOverlapped,
			INFINITE
		);

		if( !bSuccess )
		{
			EnterCriticalSection(&criti);
			//LogAdd( "GetQueuedCompletionStatus failed with error %d", GetLastError() ); fuck this error log too
			CloseClient(lpPerSocketContext, FALSE);
			LeaveCriticalSection(&criti);
			continue;
		}

		if(lpPerSocketContext == NULL)
		{
			LogAdd( "lpPerSocketContext is NULL" );
			return FALSE;
		}

		EnterCriticalSection(&criti);
		
		lpPerSocketContext->dwIOCount--;
		if( bSuccess == FALSE || bSuccess != FALSE && dwIoSize == 0 )
		{
			LogAdd("GetQueuedCompletionStatus dwIoSize is zero (%d)", GetLastError() );
			CloseClient(lpPerSocketContext, FALSE);
			LeaveCriticalSection(&criti);
			continue;
		}

		lpIOContext = (LPPER_IO_CONTEXT)lpOverlapped;

		if( lpIOContext->IOOperation == SEND_IO )
		{
			/*lpIOContext->nSentBytes += dwIoSize;

			if( lpIOContext->nSentBytes >= lpIOContext->nTotalBytes )
			{
				lpIOContext->nWaitIO = 0;
				if( lpIOContext->nSecondOfs > 0 )
				{
					//IoSend(lpPerSocketContext);
				}
			}
			else
			{
				//IoSend(lpPerSocketContext);
			}*/
		}
		else if( lpIOContext->IOOperation == RECV_IO )
		{
			RecvBytes = 0;

			lpIOContext->nSentBytes += dwIoSize;
			
			RecvDataParse(lpIOContext, lpPerSocketContext->nIndex);

			//lpIOContext->nWaitIO = 0;
			Flags = 0;
			ZeroMemory(&(lpIOContext->Overlapped), sizeof(OVERLAPPED));
			
			lpIOContext->wsabuf.len		= MAX_BUFF_SIZE-lpIOContext->nSentBytes;
			lpIOContext->wsabuf.buf		= lpIOContext->Buffer+lpIOContext->nSentBytes;
			lpIOContext->IOOperation	= RECV_IO;
			
			nRet = WSARecv(lpPerSocketContext->m_socket, &(lpIOContext->wsabuf), 1, &RecvBytes, &Flags,
				&(lpIOContext->Overlapped), NULL);
			if( nRet == SOCKET_ERROR && (WSAGetLastError() != ERROR_IO_PENDING) )
			{
				LogAdd("WSARecv() failed with error %d", WSAGetLastError());
				//lpIOContext->nWaitIO = 2;
				CloseClient( lpPerSocketContext, FALSE);
				LeaveCriticalSection(&criti);
				continue;
			}
			else
			{	
				lpPerSocketContext->dwIOCount++;
				//lpIOContext->nWaitIO = 1;
			}
		}
		LeaveCriticalSection(&criti);
	}
	//return TRUE;
}

BOOL RecvDataParse(LPPER_IO_CONTEXT	lpIOContext, int uIndex)
{
	if( lpIOContext->nSentBytes < 3 ) return FALSE;
	
	LPBYTE	recvbuf;
	int		lOfs=0;
	int		size=0;
	BYTE	headcode;
	
	recvbuf = (LPBYTE)lpIOContext->Buffer;

	while(1)
	{
		if( recvbuf[lOfs] == 0xC1 ) //
		{
			LPPBMSG_HEAD lphead = (LPPBMSG_HEAD)(recvbuf+lOfs);
			size				= lphead->size;
			headcode			= lphead->headcode;
		}
		else if( recvbuf[lOfs] == 0xC2 ) //
		{
			LPPWMSG_HEAD lphead	= (LPPWMSG_HEAD)(recvbuf+lOfs);
			size				= ((WORD)(lphead->sizeH)<<8);
			size			   |= (WORD)(lphead->sizeL);
			headcode			= lphead->headcode;
		}
		else  // ����� ���� �ʴٸ�..
		{
			LogAdd("error-L1 : Header error (%s %d)lOfs:%d, size:%d", __FILE__, __LINE__, lOfs, lpIOContext->nSentBytes);
			lpIOContext->nSentBytes = 0;
			return FALSE;
		}
		if( size <= 0 )
		{
			LogAdd("error : size�� %d�̴�.", size);
			return FALSE;
		}
		if( size <= lpIOContext->nSentBytes )	// �����Ͱ� ũ�⸸ŭ �����ϸ�..
		{
#ifdef DEBUG_IOCP_LOG
			LogAdd("[PacketLog][recvhead] [0x%02X]", headcode);
#endif
			if(headcode == 0x52 || headcode == 0x54 || headcode == 0x55)
			{
				WzRecvQ3.AddToQueue((LPBYTE)(recvbuf+lOfs), size, headcode, uIndex, g_DelayHandler.GetQuerySessionId());
			}
			else if(headcode == 0xF6
				|| headcode == 0xF7
				//s12
				//|| headcode == 0xE4
				//|| headcode == 0x3E
				//|| headcode == 0x4C
				//|| headcode == 0xE8
				//|| headcode == 0x4E
				//|| headcode == 0xF1
				//|| headcode == 0xF2
				//|| headcode == 0xE9
				//|| headcode == 0xEA
				//|| headcode == 0xEB
				//|| headcode == 0xEC
				//|| headcode == 0xED
				//|| headcode == 0xF3
				//|| headcode == 0x79
				//
				)
			{
				WzRecvQ2.AddToQueue((LPBYTE)(recvbuf+lOfs), size, headcode, uIndex, g_DelayHandler.GetQuerySessionId());
			}
			else if(headcode == 0x13
				|| headcode == 0x14
				//s12
				//|| headcode == 0xEE
				//|| headcode == 0xF0
				//|| headcode == 0xFC
				//|| headcode == 0xF9
				//|| headcode == 0x80
				//|| headcode >= 0x81 && headcode <= 0x89
				//|| headcode == 0xE5
				//|| headcode == 0xF8
				//|| headcode == 0xFA
				//|| headcode == 0xFB
				//|| headcode == 0xFD
				//|| headcode == 0xEF
				//
				)
			{
				WzRecvQ4.AddToQueue((LPBYTE)(recvbuf+lOfs), size, headcode, uIndex, g_DelayHandler.GetQuerySessionId());
			}
			else
			{
				WzRecvQ.AddToQueue((LPBYTE)(recvbuf+lOfs), size, headcode, uIndex, g_DelayHandler.GetQuerySessionId());
			}
			//ProtocolCore(headcode, (recvbuf+lOfs), size, uIndex);
			lOfs += size;
			lpIOContext->nSentBytes -= size;			
			if( lpIOContext->nSentBytes <= 0 ) break;
		}			
		else 
		{	// recv �����Ͱ� ���� �ϼ����� �ʾҴٸ�..
			if( lOfs > 0 )  // �ϳ��̻� �����͸� ���� �Ķ��..
			{
				if( lpIOContext->nSentBytes < 1 ) 
				{
					LogAdd("error : recvbuflen �� 1���� �۴�..");
					break;
				}
				else 
				{
					if( lpIOContext->nSentBytes < MAX_BUFF_SIZE )
					{
						memcpy(recvbuf, (recvbuf+lOfs), lpIOContext->nSentBytes); // ������ŭ �����Ѵ�.
						LogAdd("error : copy %d",lpIOContext->nSentBytes);
					}
					break;
				}
			}
			break;
		}
	}
	return 0;
}

int IoSend(int aIndex, LPBYTE lpMsg, DWORD dwSize)
{	
	EnterCriticalSection(&criti);
	DWORD SendBytes;
	LPPER_SOCKET_CONTEXT lpPerSocketContext;
	/*if( gSObj[aIndex].Connected < 1 )
	{
		LeaveCriticalSection(&criti);
		return FALSE;
	}
	lpPerSocketContext = gSObj[aIndex].lpPerSocketContext;*/
#ifdef DEBUG_IOCP_LOG
	LogAdd("[PacketLog] [0x%02X][0x%02X][0x%02X][0x%02X]", *lpMsg, lpMsg[1], lpMsg[2], lpMsg[3]);
#endif
	if( dwSize > MAX_BUFF_SIZE )
	{
		LogAdd("Error : Max msg %s %d", __FILE__, __LINE__);
		LeaveCriticalSection(&criti);
		//CloseClient( aIndex );
		return FALSE;
	}

	if( gSObj[aIndex].Connected < 1 )
	{
		LeaveCriticalSection(&criti);
		return FALSE;
	}

	lpPerSocketContext = gSObj[aIndex].lpPerSocketContext;

	if(lpPerSocketContext == NULL)
	{
		LogAdd("error : user socket context buffer free.");
		LeaveCriticalSection(&criti);
		return FALSE;
	}

	LPPER_IO_CONTEXT	lpIoCtxt = (LPPER_IO_CONTEXT)&lpPerSocketContext->IOContext[1];

	lpIoCtxt->wsabuf.buf = (char*)lpMsg;
	lpIoCtxt->wsabuf.len = dwSize;

	/*if( lpIoCtxt->nWaitIO > 0 )	// ���� �۾��� ���� �Ϸ���� �ʾҴٸ�.. ����Ʈ�� ����
	{	
		if( (lpIoCtxt->nSecondOfs+dwSize) > MAX_BUFF_SIZE-1)	// ũ�⸦ �Ѿ���.
		{
			LogAdd("error-L2 MAX BUFFER OVER");
			lpIoCtxt->nWaitIO = 0;
			CloseClient( aIndex );
			LeaveCriticalSection(&criti);
			return TRUE;
		}
		else
		{
			// �����带 �ϴ� ����..
			memcpy(lpIoCtxt->BufferSecond+lpIoCtxt->nSecondOfs, lpMsg, dwSize);
			lpIoCtxt->nSecondOfs+=dwSize;
			//LogAdd("������ ����.. %d+=%d (%s)", lpIoCtxt->nSecondOfs, dwSize, gSObj[aIndex].AccountID);
			LeaveCriticalSection(&criti);
			return TRUE;
		}
	}
	else
	{
		lpIoCtxt->nTotalBytes = 0;
		if( lpIoCtxt->nSecondOfs > 0 )
		{
			memcpy(lpIoCtxt->Buffer, lpIoCtxt->BufferSecond, lpIoCtxt->nSecondOfs);
			lpIoCtxt->nTotalBytes = lpIoCtxt->nSecondOfs;
			//LogAdd("����Ʈ�� ����.. %d", lpIoCtxt->nTotalBytes);
			lpIoCtxt->nSecondOfs = 0;
		}
		if( (lpIoCtxt->nTotalBytes+dwSize) > MAX_BUFF_SIZE-1)	// ũ�⸦ �Ѿ���.
		{
			LogAdd("error-L2 MAX BUFFER OVER");
			lpIoCtxt->nWaitIO = 0;
			CloseClient( aIndex );
			LeaveCriticalSection(&criti);
			return FALSE;
		}
		else
		{
			memcpy(lpIoCtxt->Buffer+lpIoCtxt->nTotalBytes, lpMsg, dwSize);
			lpIoCtxt->nTotalBytes += dwSize;
			//LogAdd("�޽��� ����.. %d", lpIoCtxt->nTotalBytes);
		}
	}
	// �����۾��� �Ϸ�Ǿ��ٸ�..

	lpIoCtxt->wsabuf.buf	= (char*)lpIoCtxt->Buffer;
	lpIoCtxt->wsabuf.len	= lpIoCtxt->nTotalBytes;*/
	lpIoCtxt->nTotalBytes	= dwSize;
	lpIoCtxt->nSentBytes	= 0;
	lpIoCtxt->IOOperation	= SEND_IO;

	if (WSASend(gSObj[aIndex].m_socket, &(lpIoCtxt->wsabuf), 1, &SendBytes, 0,
		&(lpIoCtxt->Overlapped), NULL) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != ERROR_IO_PENDING)
		{
			LogAdd("WSASend() failed with error %d", WSAGetLastError());			
			//lpIoCtxt->nWaitIO = 3;
			//CloseClient( aIndex );
			LeaveCriticalSection(&criti);
			return FALSE;
		}
	}
	else 
	{
		lpPerSocketContext->dwIOCount++;
	}
	//lpIoCtxt->nWaitIO = 1;
	LeaveCriticalSection(&criti);
	return TRUE;
}

LPPER_SOCKET_CONTEXT UpdateCompletionPort( SOCKET sd, int ClientIndex, BOOL bAddToList ) 
{
    LPPER_SOCKET_CONTEXT lpPerSocketContext = NULL;

	lpPerSocketContext = ContextAllocate(sd, ClientIndex);

	if(lpPerSocketContext == NULL)
	{
		return FALSE;
	}
	
    HANDLE cp = CreateIoCompletionPort((HANDLE)sd, g_CompletionPort, (DWORD)lpPerSocketContext, 0); 
    
	if (cp == NULL)
	{
        LogAdd("CreateIoCompletionPort: %d", GetLastError());
		HeapFree(GetProcessHeap(), 0, lpPerSocketContext);
        return FALSE;
	}

	if(bAddToList != FALSE)
	{
		CtxtListAddTo(lpPerSocketContext);
	}
	//gSObj[ClientIndex].lpPerSocketContext->dwIOCount = 0;
    return lpPerSocketContext; 
}

LPPER_SOCKET_CONTEXT ContextAllocate(SOCKET sd, int ClientIndex)
{ //completed
	LPPER_SOCKET_CONTEXT lpPerSocketContext;

	EnterCriticalSection(&criti);

	lpPerSocketContext = (LPPER_SOCKET_CONTEXT)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(_PER_SOCKET_CONTEXT));
	lpPerSocketContext->WzSendQ	= new WZQueue();

	if(lpPerSocketContext != NULL)
	{
		lpPerSocketContext->m_socket = sd;
		lpPerSocketContext->nIndex = ClientIndex;

		lpPerSocketContext->lpCtxtBack = NULL;
		lpPerSocketContext->lpCtxtForward = NULL;

		lpPerSocketContext->IOContext[RECV_IO].Overlapped.Internal = 0;
		lpPerSocketContext->IOContext[RECV_IO].Overlapped.InternalHigh = 0;
		lpPerSocketContext->IOContext[RECV_IO].Overlapped.Offset = 0;
		lpPerSocketContext->IOContext[RECV_IO].Overlapped.OffsetHigh = 0;
		lpPerSocketContext->IOContext[RECV_IO].Overlapped.hEvent = NULL;
		lpPerSocketContext->IOContext[RECV_IO].IOOperation = RECV_IO;
		lpPerSocketContext->IOContext[RECV_IO].pIOContextForward = NULL;
		lpPerSocketContext->IOContext[RECV_IO].nTotalBytes = 0;
		lpPerSocketContext->IOContext[RECV_IO].nSentBytes = 0;
		lpPerSocketContext->IOContext[RECV_IO].wsabuf.buf = lpPerSocketContext->IOContext[RECV_IO].Buffer;
		lpPerSocketContext->IOContext[RECV_IO].wsabuf.len = MAX_BUFF_SIZE;
		
		lpPerSocketContext->IOContext[SEND_IO].Overlapped.Internal = 0;
		lpPerSocketContext->IOContext[SEND_IO].Overlapped.InternalHigh = 0;
		lpPerSocketContext->IOContext[SEND_IO].Overlapped.Offset = 0;
		lpPerSocketContext->IOContext[SEND_IO].Overlapped.OffsetHigh = 0;
		lpPerSocketContext->IOContext[SEND_IO].Overlapped.hEvent = NULL;		
		lpPerSocketContext->IOContext[SEND_IO].IOOperation = SEND_IO;
		lpPerSocketContext->IOContext[SEND_IO].pIOContextForward = 0;
		lpPerSocketContext->IOContext[SEND_IO].nTotalBytes = 0;
		lpPerSocketContext->IOContext[SEND_IO].nSentBytes = 0;
		lpPerSocketContext->IOContext[SEND_IO].wsabuf.buf = lpPerSocketContext->IOContext[SEND_IO].Buffer;
		lpPerSocketContext->IOContext[SEND_IO].wsabuf.len = MAX_BUFF_SIZE;
	}
	else
	{
		LogAdd("HeapAlloc PER_SOCKET_CONTEXT Failed: %d", GetLastError());
	}

	LeaveCriticalSection(&criti);

	return lpPerSocketContext;
}

void CtxtListAddTo(LPPER_SOCKET_CONTEXT lpPerSocketContext)
{ //completed
	LPPER_SOCKET_CONTEXT pTemp;

	EnterCriticalSection(&criti);

	if(g_pCtxtList == NULL)
	{
		lpPerSocketContext->lpCtxtBack = NULL;
		lpPerSocketContext->lpCtxtForward = NULL;
		g_pCtxtList = lpPerSocketContext;
		g_pCtxtListHead = lpPerSocketContext;
	}
	else
	{
		pTemp = g_pCtxtList;
		g_pCtxtList = lpPerSocketContext;
		lpPerSocketContext->lpCtxtBack = pTemp;
		lpPerSocketContext->lpCtxtForward = NULL;
		pTemp->lpCtxtForward = lpPerSocketContext;
	}

	LeaveCriticalSection(&criti);
}

BOOL CtxtListDeleteFrom(LPPER_SOCKET_CONTEXT lpPerSocketContext)
{ //completed
	LPPER_SOCKET_CONTEXT	pBack; //loc1
	LPPER_SOCKET_CONTEXT	pForward; //loc2

	LPPER_IO_CONTEXT	pNextIO = NULL; //loc3
	LPPER_IO_CONTEXT	pTempIO = NULL; //loc4

	BYTE TempBuf[MAX_BUFF_SIZE];
	UINT nSize;
	BYTE headcode;
	int uindex;
	int iSessionId;

	if(lpPerSocketContext->dwIOCount > 0)
	{
		return FALSE;
	}

	EnterCriticalSection(&criti);

	if(lpPerSocketContext != NULL)
	{
		pBack = lpPerSocketContext->lpCtxtBack;
		pForward = lpPerSocketContext->lpCtxtForward;

		if(pBack == NULL && pForward == NULL)
		{
			g_pCtxtList = NULL;
			g_pCtxtListHead = NULL;
		}
		else if(pBack == NULL && pForward != NULL)
		{
			pForward->lpCtxtBack = NULL;
			g_pCtxtList = pForward;
		}
		else if(pBack != NULL && pForward == NULL)
		{
			pBack->lpCtxtForward = NULL;
			g_pCtxtList = pBack;
		}
		else if(pBack != NULL && pForward != NULL)
		{
			pBack->lpCtxtForward = pForward;
			pForward->lpCtxtBack = pBack;
		}

		while( lpPerSocketContext->WzSendQ->GetFromQueue(TempBuf, &nSize, &headcode, &uindex, &iSessionId) != 0 )
		{
			continue;
		}

		delete lpPerSocketContext->WzSendQ;

		HeapFree(GetProcessHeap(), 0, lpPerSocketContext);
		lpPerSocketContext = NULL;
	}
	else
	{
		LogAdd("CtxtListDeleteFrom: lpPerSocketContext is NULL");
	}

	LeaveCriticalSection(&criti);

	return TRUE;
}

void CtxtListFree()
{ //completed
	EnterCriticalSection(&criti);

	LPPER_SOCKET_CONTEXT pTemp1 = g_pCtxtList; //loc1
	LPPER_SOCKET_CONTEXT pTemp2; //loc2

	while(pTemp1 != 0)
	{
		pTemp2 = pTemp1->lpCtxtBack;
		pTemp1 = pTemp2;
	}
	
	LeaveCriticalSection(&criti);
}

void CloseClient ( LPPER_SOCKET_CONTEXT lpPerSocketContext, BOOL bGraceful ) 
{ 
	int index=lpPerSocketContext->nIndex;
	CloseClient(index);
}

void CloseClient ( int index ) ///LPPER_SOCKET_CONTEXT lpPerSocketContext, BOOL bGraceful ) 
{
	if( index < 0 || index > MAX_OBJECT-1 ) return;
	if( gSObj[index].Connected == 0 ) return;

	EnterCriticalSection(&criti);

	LPPER_SOCKET_CONTEXT lpPerSocketContext = gSObj[index].lpPerSocketContext;

	if(lpPerSocketContext != NULL)
	{
		index = lpPerSocketContext->nIndex;

		if(lpPerSocketContext->m_socket != INVALID_SOCKET)
		{
			closesocket(lpPerSocketContext->m_socket);
			lpPerSocketContext->m_socket = INVALID_SOCKET;
		}

		if(CtxtListDeleteFrom(lpPerSocketContext) == TRUE)
		{
			lpPerSocketContext = NULL;
			gSObj[index].lpPerSocketContext = NULL;
		}
	}
	else
	{
		LogAdd("CloseClient: lpPerSocketContext is NULL");
	}

	if(index >= 0)
	{
		LogAddTD("CloseClient(%d)", index);
		gSObjDel(index);
	}

	LeaveCriticalSection(&criti);

//	closesocket(gSObj[index].m_socket);
//
//	gSObj[index].m_socket = INVALID_SOCKET;
//	LogAddTD("error-L2:CloseClient %d (��������??)", index);

    return;
}

DWORD WINAPI ServerRecvWorkerThreadSecond(LPVOID p)
{
	BYTE RecvData[MAX_BUFF_SIZE]; //0
	unsigned int nSize=0; //4
	BYTE headcode; //8
	int  uindex; //c
	int	 loopN; //10

	int  iSessionId; //14
	bool bProcessPacket; //18

	int  nCount=0; //1C

	while(TRUE)
	{
		EnterCriticalSection(&criti);

		loopN = WzRecvQ2.GetCount();	

		if( loopN > MAX_NODE-1 )
		{
			loopN = MAX_NODE-1;
			LogAdd("error : Q2 Loop MAX %s %d", __FILE__, __LINE__);
		}
		LeaveCriticalSection(&criti);
		if( loopN > 0 )
		{
			//DWORD dwTime = GetTickCount();
			//for( int n=0; n<loopN; n++)
			{
				if( WzRecvQ2.GetFromQueue((LPBYTE)RecvData, &nSize, &headcode, &uindex, &iSessionId) == TRUE )
				{
					bProcessPacket = true;
					if(iSessionId != g_DelayHandler.GetQuerySessionId())
					{
						if(g_DelayHandler.CheckHeadCode(headcode) == false)
						{
							bProcessPacket = false;
							LogAddTD("[DelayHandler] Drop Delayed Packet -> Head : %X", headcode);
						}
						else
						{
							LogAddTD("[DelayHandler] Process Delayed Packet -> Head : %X", headcode);
						}
					}
					if(bProcessPacket != false)
					{
						ProtocolCore(headcode, RecvData, nSize, uindex);
					}
				}
			}
			//LogAdd("Process End : [%d]", GetTickCount() - dwTime);
		}
		Sleep(1);
	}
	return TRUE;
}

DWORD WINAPI ServerRecvWorkerThreadThird(LPVOID p)
{
	BYTE RecvData[MAX_BUFF_SIZE]; //0
	unsigned int nSize=0; //4
	BYTE headcode; //8
	int  uindex; //c
	int	 loopN; //10

	int  iSessionId; //14
	bool bProcessPacket; //18

	int  nCount=0; //1C

	while(TRUE)
	{
		EnterCriticalSection(&criti);

		loopN = WzRecvQ3.GetCount();	

		if( loopN > MAX_NODE-1 )
		{
			loopN = MAX_NODE-1;
			LogAdd("error : Q3 Loop MAX %s %d", __FILE__, __LINE__);
		}
		LeaveCriticalSection(&criti);
		if( loopN > 0 )
		{
			//DWORD dwTime = GetTickCount();
			//for( int n=0; n<loopN; n++)
			{
				if( WzRecvQ3.GetFromQueue((LPBYTE)RecvData, &nSize, &headcode, &uindex, &iSessionId) == TRUE )
				{
					bProcessPacket = true;
					if(iSessionId != g_DelayHandler.GetQuerySessionId())
					{
						if(g_DelayHandler.CheckHeadCode(headcode) == false)
						{
							bProcessPacket = false;
							LogAddTD("[DelayHandler] Drop Delayed Packet -> Head : %X", headcode);
						}
						else
						{
							LogAddTD("[DelayHandler] Process Delayed Packet -> Head : %X", headcode);
						}
					}
					if(bProcessPacket != false)
					{
						ProtocolCore(headcode, RecvData, nSize, uindex);
					}
				}
			}
			//LogAdd("Process End : [%d]", GetTickCount() - dwTime);
		}
		Sleep(1);
	}
	return TRUE;
}

DWORD WINAPI ServerRecvWorkerThreadFourth(LPVOID p)
{
	BYTE RecvData[MAX_BUFF_SIZE]; //0
	unsigned int nSize=0; //4
	BYTE headcode; //8
	int  uindex; //c
	int	 loopN; //10

	int  iSessionId; //14
	bool bProcessPacket; //18

	int  nCount=0; //1C

	while(TRUE)
	{
		EnterCriticalSection(&criti);
		loopN = WzRecvQ4.GetCount();	

		if( loopN > MAX_NODE-1 )
		{
			loopN = MAX_NODE-1;
			LogAdd("error : Q3 Loop MAX %s %d", __FILE__, __LINE__);
		}
		LeaveCriticalSection(&criti);

		if( loopN > 0 )
		{
			//DWORD dwTime = GetTickCount();
			//for( int n=0; n<loopN; n++)
			{
				if( WzRecvQ4.GetFromQueue((LPBYTE)RecvData, &nSize, &headcode, &uindex, &iSessionId) == TRUE )
				{
					bProcessPacket = true;
					if(iSessionId != g_DelayHandler.GetQuerySessionId())
					{
						if( !g_DelayHandler.CheckHeadCode(headcode) )
						{
							bProcessPacket = false;
							LogAddTD("[DelayHandler] Drop Delayed Packet -> Head : %X", headcode);
						}
						else LogAddTD("[DelayHandler] Process Delayed Packet -> Head : %X", headcode);
					}
					if( bProcessPacket )
					{
						ProtocolCore(headcode, RecvData, nSize, uindex);
					}
				}
			}
			//LogAdd("Process End : [%d]", GetTickCount() - dwTime);
		}
		Sleep(1);
	}
	return TRUE;
}