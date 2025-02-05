
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif
#include "targetver.h"

#pragma warning ( disable : 4786 )
#pragma warning ( disable :4566)

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT

#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars

#define DATASERVER_VERSION				"0.75.00"//"0.73.00"

#include "Include\define.h"
#include "common\Logproc.h"
#include "LogToFile.h"
#include "common\winutil.h"
#include "Include\ProDef.h"
#include "common\ItemSocketOptionDefine.h"

#define DB_CONNECT_DSN			"MuOnlineJoinDB"
#define DB_CONNECT_UID			"MuOnlineAdmin"
#define DB_CONNECT_PWD			"wkfwkRnfRnf"

extern char szDbConnectID[];
extern char szDbConnectPass[];
extern char szDbConnectDsn[];

#include "CQuery.h"

extern char g_szDBID_DESC[];

//#define DEBUG_IOCP_LOG
#define _SEASON12