// ChildView.cpp : implementation of the CChildView class
// Decompilation Completed -> All Same as WebZen

#include "stdafx.h"
#include "DataServer.h"
#include "ChildView.h"
#include "giocp.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView


CChildView::CChildView()
{
	
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint()
{
	RECT rect;
	CBrush bk(GetSysColor(COLOR_WINDOW));
	CPaintDC dc(this);

	GetClientRect(&rect);

	dc.SelectObject(&bk);
	dc.FillRect(&rect, &bk);

	LogTextPaint(this->m_hWnd);

	char tmpQueueSizeTxt[256] = "";
	wsprintf(tmpQueueSizeTxt, this->m_szQueueSizeText);
	strcat(tmpQueueSizeTxt, this->m_szQueueSizeText2);
	strcat(tmpQueueSizeTxt, this->m_szQueueSizeText3);
	strcat(tmpQueueSizeTxt, this->m_szQueueSizeText4);
	
	dc.TextOut(20, 50, tmpQueueSizeTxt);

	CFont fnBold;
	HFONT pOldFont = 0;
	TEXTMETRICA tm;
	LOGFONT lf;

	CString strFont;
	
	memset(&lf, 0, sizeof(lf));
	
	dc.GetTextMetrics(&tm);

	lf.lfHeight = 50;
	lf.lfWeight = 0;
	lf.lfUnderline = 0;
	strncpy(lf.lfFaceName, "Times", sizeof(lf.lfFaceName));

	fnBold.CreateFontIndirect(&lf);
	pOldFont = (HFONT)dc.SelectObject(&fnBold);

	CRect rcText;
	this->GetClientRect(&rcText);

	dc.SetBkMode(1);

	if(cAM.GetMode() == AM_ACTIVE)
	{
		dc.FillSolidRect(0, 0, rcText.right, 50, RGB(110, 250, 120));
		dc.SetTextColor( RGB(250, 250, 250) );
		dc.DrawText("ACTIVE MODE", -1, (LPRECT)rcText, 5);
	}
	else
	{
		dc.FillSolidRect(0, 0, rcText.right, 50, RGB(100, 100, 100));
		dc.SetTextColor( RGB(190, 190, 190) );
		dc.DrawText("STANDBY MODE", -1, (LPRECT)rcText, 5);
	}
}

void CChildView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch( nIDEvent )
	{
	case 1001 :
		{
			this->ShowDbQueueSize();
		}
		//LogTextPaint(m_hWnd);
		break;
	}
	CWnd ::OnTimer(nIDEvent);
}

void CChildView::ShowDbQueueSize()
{
  wsprintfA(this->m_szQueueSizeText, "[Q1 Size : %d], ", WzRecvQ.GetCount_NoLock());
  wsprintfA(this->m_szQueueSizeText2, "[Q2 Size : %d], ", WzRecvQ2.GetCount_NoLock());
  wsprintfA(this->m_szQueueSizeText3, "[Q3(serial) Size : %d] ", WzRecvQ3.GetCount_NoLock());
  wsprintfA(this->m_szQueueSizeText4, "[Q4 Size : %d] ", WzRecvQ4.GetCount_NoLock());
  this->Invalidate(FALSE);
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd ::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	memset(this->m_szQueueSizeText, 0, sizeof(this->m_szQueueSizeText));
	SetTimer(1001, 1000, NULL);
	memset(this->m_szQueueSizeText2, 0, sizeof(this->m_szQueueSizeText2));
	memset(this->m_szQueueSizeText3, 0, sizeof(this->m_szQueueSizeText3));
	memset(this->m_szQueueSizeText4, 0, sizeof(this->m_szQueueSizeText4));
	return 0;
}
