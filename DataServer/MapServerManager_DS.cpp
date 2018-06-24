// MapServerManager_DS.cpp: implementation of the CMapServerManager class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#ifdef MAP_SERVER_WORK_20041030
#include "Dataserver.h"
#include "MapServerManager_DS.h"
#include "Include\ReadScript.h"
#include "common\winutil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

_MAPSVR_DATA::_MAPSVR_DATA()
{
	this->Clear(1);
}

_MAPSVR_DATA::~_MAPSVR_DATA()
{

}

void _MAPSVR_DATA::Clear(int iInitSetVal)
{
	this->m_bIN_USE = FALSE;
	this->m_btMAPSVR_GROUP = -1;
	this->m_sSVR_CODE = -1;

	memset(this->m_cIPADDR, 0, sizeof(this->m_cIPADDR));

	this->m_wPORT = 0;

	for ( int iMAP_COUNT =0;iMAP_COUNT<MAX_MAP;iMAP_COUNT++)
	{
		switch ( iInitSetVal )
		{
			case -1:
				this->m_sMAP_MOVE[iMAP_COUNT] = -2;
				break;
			case 0:
				this->m_sMAP_MOVE[iMAP_COUNT] = -1;
				break;
			default:
				this->m_sMAP_MOVE[iMAP_COUNT] = -3;
		}
	}
}

CMapServerManager::CMapServerManager()
{
	srand(time(NULL)); 
	this->m_bMapDataLoadOk = FALSE;
	this->m_lpThisMapSvrData = NULL;

	InitializeCriticalSection(&this->m_critSVRCODE_MAP);
}

CMapServerManager::~CMapServerManager()
{
	DeleteCriticalSection(&this->m_critSVRCODE_MAP);
}

BOOL CMapServerManager::LoadMapData(char* lpszFileName)
{
	if ( (lpszFileName == NULL) || ( strcmp(lpszFileName, "")== 0 ) ) 
	{
		MsgBox("[MapServerMng] file load error - File Name Error");
		return FALSE;
	}

	EnterCriticalSection(&this->m_critSVRCODE_MAP);

	this->m_bMapDataLoadOk = FALSE;

	for ( int iGROUP_COUNT=0;iGROUP_COUNT<20;iGROUP_COUNT++)
	{
		this->m_iMAPSVR_GROUP_COUNT[iGROUP_COUNT] = 0;

		for ( int iSUB_GROUP_COUNT=0;iSUB_GROUP_COUNT<20;iSUB_GROUP_COUNT++)
		{
			this->m_MAPSVR_DATA[iGROUP_COUNT][iSUB_GROUP_COUNT].Clear(1);
		}
	}

	this->m_mapSVRCODE_MAP.clear();

	SMDFile = fopen(lpszFileName, "r");

	if ( SMDFile == NULL )
	{
		MsgBox("[MapServerMng] file load error - fopen() : %s",	lpszFileName);
		return FALSE;
	}

	int type = -1;

	SMDToken Token;

	while ( true )
	{
		Token = GetToken();

		if ( Token == END )	break;

		type = TokenNumber;

		while ( true )
		{
			if ( type == 0 )
			{
				short sSVR_CODE = -1;
				short sMAPSVR_GROUP = -1;
				int iInitSetVal = 1;
				char szIpAddr[16]={0};
				WORD wPortNum = 0;
				
				Token = GetToken();

				if (strcmp("end", TokenString) == 0) break;

				sSVR_CODE = TokenNumber;

				Token = GetToken();
				sMAPSVR_GROUP = TokenNumber;

				Token = GetToken();
				iInitSetVal = TokenNumber;

				Token = GetToken();
				memcpy(szIpAddr, &TokenString[1], 16);
				szIpAddr[15] =0;

				Token = GetToken();
				wPortNum = TokenNumber;
				Token = GetToken();//season12

				if ( sSVR_CODE < 0 )
				{
					MsgBox("[MapServerMng] file load error - sSVR_CODE < 0 (SVR:%d) - 1",
						sSVR_CODE);
					return FALSE;
				}

				if ( iInitSetVal != -1 && iInitSetVal != 0 && iInitSetVal != 1 )
				{
					MsgBox("[MapServerMng] file load error - iInitSetting Value:%d (SVR:%d) - 1",
						iInitSetVal, sSVR_CODE);
					return FALSE;
				}

				if ( !strcmp(szIpAddr, ""))
				{
					MsgBox("[MapServerMng] file load error - No IpAddress (SVR:%d)",
						sSVR_CODE);
					return FALSE;
				}

				if ( CHECK_LIMIT(sMAPSVR_GROUP, 20) == FALSE )
				{
					MsgBox("[MapServerMng] file load error - Map Server Group Index (IDX:%d)",
						sMAPSVR_GROUP);
					return FALSE;
				}

				if ( this->m_iMAPSVR_GROUP_COUNT[sMAPSVR_GROUP] >= 20 )
				{
					MsgBox("[MapServerMng] file load error - No Space to Save SvrInfo (SVR:%d)",
						sSVR_CODE);
					return FALSE;
				}

				_MAPSVR_DATA * lpMapSvrData = NULL;

				lpMapSvrData= &this->m_MAPSVR_DATA[sMAPSVR_GROUP][this->m_iMAPSVR_GROUP_COUNT[sMAPSVR_GROUP]];

				lpMapSvrData->Clear(iInitSetVal);
				lpMapSvrData->m_bIN_USE = TRUE;
				lpMapSvrData->m_sSVR_CODE = sSVR_CODE;
				lpMapSvrData->m_btMAPSVR_GROUP = sMAPSVR_GROUP;
				lpMapSvrData->m_wPORT = wPortNum;

				memcpy(lpMapSvrData->m_cIPADDR, szIpAddr, 16);
				lpMapSvrData->m_cIPADDR[15] = 0;
				
				//#fix-me
				this->m_mapSVRCODE_MAP.insert(std::pair<int,_MAPSVR_DATA *>(sSVR_CODE, lpMapSvrData));

				this->m_iMAPSVR_GROUP_COUNT[sMAPSVR_GROUP]++;
			}
			else if ( type == 1 )
			{
				short sSVR_CODE = -1;
				BYTE btNotMoveOption = 0;
				WORD wMapNum = 0;
				short sDEST_SVR_CODE = -1;
				
				_MAPSVR_DATA * lpMapSvrData = NULL;

				Token = GetToken();

				if ( strcmp("end", TokenString) == 0) break;

				sSVR_CODE = TokenNumber;

				Token = GetToken();
				btNotMoveOption = TokenNumber;

				Token = GetToken();
				wMapNum = TokenNumber;

				Token = GetToken();
				sDEST_SVR_CODE = TokenNumber;

				if ( sSVR_CODE < 0 )
				{
					MsgBox("[MapServerMng] file load error - sSVR_CODE < 0 (SVR:%d) - 2",
						sSVR_CODE);
					return FALSE;
				}

				if ( sDEST_SVR_CODE < -2 )
				{
					MsgBox("[MapServerMng] file load error - sDEST_SVR_CODE < -1 (SVR:%d, DEST_SVR:%d) - 2",
						sSVR_CODE, sDEST_SVR_CODE);
					return FALSE;
				}

				std::map<int, _MAPSVR_DATA*>::iterator it = this->m_mapSVRCODE_MAP.find(sSVR_CODE);

				if ( it == this->m_mapSVRCODE_MAP.end() )
				{
					MsgBox("[MapServerMng] file load error - sSVR_CODE wasn't registered (SVR:%d)",
						sSVR_CODE);
					return FALSE;
				}

				lpMapSvrData = it->second;

				if ( lpMapSvrData == NULL )
				{
					MsgBox("[MapServerMng] file load error - lpMapSvrData == NULL (SVR:%d)",
						sSVR_CODE);
					return FALSE;
				}

				if ( lpMapSvrData->m_bIN_USE == FALSE )
				{
					MsgBox("[MapServerMng] file load error - lpMapSvrData->m_bIN_USE == FALSE (SVR:%d)",
						sSVR_CODE);
					return FALSE;
				}

				if ( lpMapSvrData->m_sSVR_CODE != sSVR_CODE )
				{
					MsgBox("[MapServerMng] file load error - lpMapSvrData->m_sSVR_CODE != sSVR_CODE (SVR:%d)",
						sSVR_CODE);
					return FALSE;
				}

				if ( btNotMoveOption != 0 && btNotMoveOption != 1 )
				{
					MsgBox("[MapServerMng] file load error - lpMapSvrData->m_sSVR_CODE != sSVR_CODE (SVR:%d, OPT:%d)",
						sSVR_CODE, btNotMoveOption);
					return FALSE;
				}

				if ( CHECK_LIMIT(wMapNum, MAX_MAP) == FALSE )
				{
					MsgBox("[MapServerMng] file load error - Map Number is out of bound (SVR:%d, MAP:%d)",
						sSVR_CODE, wMapNum);
					return FALSE;
				}

				switch ( btNotMoveOption )
				{
					case 0:
						lpMapSvrData->m_sMAP_MOVE[wMapNum] = sDEST_SVR_CODE;
						break;
					case 1:
						lpMapSvrData->m_sMAP_MOVE[wMapNum] = -3;
						break;
					default:
						MsgBox("[MapServerMng] file load error - lpMapSvrData->m_sSVR_CODE != sSVR_CODE (SVR:%d, OPT:%d)",
							sSVR_CODE, btNotMoveOption);
						break;
				}
			}
		}
	}

	fclose(SMDFile);

	this->m_bMapDataLoadOk = TRUE;
	LeaveCriticalSection(&this->m_critSVRCODE_MAP);	
	return TRUE;
}

BOOL CMapServerManager::GetSvrCodeData(WORD wServerCode, char* lpszIpAddress, WORD * lpwPort)
{
	if ( !lpszIpAddress || !lpwPort )
	{
		return FALSE;
	}

	_MAPSVR_DATA * lpMapSvrData = NULL;

	EnterCriticalSection(&this->m_critSVRCODE_MAP);

	std::map<int, _MAPSVR_DATA *>::iterator it = this->m_mapSVRCODE_MAP.find(wServerCode);

	if ( it != this->m_mapSVRCODE_MAP.end() )
	{
		lpMapSvrData = it->second;
	}

	LeaveCriticalSection(&this->m_critSVRCODE_MAP);

	if ( lpMapSvrData == NULL )
	{
		return FALSE;
	}

	strcpy(lpszIpAddress, lpMapSvrData->m_cIPADDR);
	*lpwPort = lpMapSvrData->m_wPORT;

	return TRUE;
}

int CMapServerManager::GetMapSvrGroup(WORD wServerCode)
{
	_MAPSVR_DATA* lpMapSvrData = NULL;

	EnterCriticalSection(&this->m_critSVRCODE_MAP);

	std::map<int, _MAPSVR_DATA*>::iterator it = this->m_mapSVRCODE_MAP.find(wServerCode);

	if ( it != this->m_mapSVRCODE_MAP.end() )
	{
		lpMapSvrData = it->second;
	}

	LeaveCriticalSection(&this->m_critSVRCODE_MAP);

	if(lpMapSvrData != NULL)
	{
		return lpMapSvrData->m_btMAPSVR_GROUP;
	}

	return -1;
}

CMapServerManager	g_MapServerManager;
#endif