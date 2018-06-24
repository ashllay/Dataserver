// ChildView.h : interface of the CChildView class
//
#pragma once


// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildView();

	char m_szQueueSizeText[256];
	char m_szQueueSizeText2[256];
	char m_szQueueSizeText3[256];
	char m_szQueueSizeText4[256];

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void ShowDbQueueSize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

