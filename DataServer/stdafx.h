#ifndef __STDAFX_H__
#define __STDAFX_H__
#pragma once

#pragma warning ( disable : 4786 )
#pragma warning ( disable : 4566 )

#define VC_EXTRALEAN
#define _WIN32_WINNT 0x500

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes

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

#define DATASERVER_VERSION "0.75.00"

#include "Include\define.h"
#include "common\Logproc.h"
#include "LogToFile.h"
#include "common\winutil.h"
#include "Include\ProDef.h"

#define DB_CONNECT_DSN			"MuOnlineJoinDB"
#define DB_CONNECT_UID			"MuOnlineAdmin"
#define DB_CONNECT_PWD			"wkfwkRnfRnf"

extern char szDbConnectID[];
extern char szDbConnectPass[];
extern char szDbConnectDsn[];

#include "CQuery.h"

extern char g_szDBID_DESC[];
