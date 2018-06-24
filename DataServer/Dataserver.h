
// Dataserver.h : main header file for the Dataserver application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDataserverApp:
// See Dataserver.cpp for the implementation of this class
//

class CDataserverApp : public CWinApp
{
public:
	CDataserverApp();

	WORD m_ServerPort;
	WORD m_JoinServerPort;
	WORD m_position;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataserverApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
	virtual BOOL InitApplication();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDataserverApp)
	afx_msg void Init();
	afx_msg WORD GetServerPort();
	afx_msg WORD GetServerPosition();
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

