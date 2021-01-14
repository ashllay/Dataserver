#include "stdafx.h"
#include "Dataserver.h"
#include "MainFrm.h"
#include "ServerPrc.h"
#include "WZIPCheck.h"
#include "BadSyntaxChk.h"
#include "MapServerManager_DS.h"

char szVersion[] = DATASERVER_VERSION;

CActiveMng cAM;

char szKorSkillTextFileName[256];
char szKorItemTextFileName[256];
char szSkillTextFileName[256];
char szItemTextFileName[256];

int gLanguage;
int gNewAccountCreate;

DWORD gItemCount = 0;

CWZScriptEncode CWZSEncode;

CwsJoinServer wsjServer;

CMuNameCheck gMuName;

COptionDbSet gOptionDbSet;
CItemExtDbSet gItemExtDbSet;
CQuery GuildMemberQry;
CWarehouseDBSet CWhDBSet;
CZenEvenDb CZenEvenDBSet;
CCharPreviewDBSet gCharPreDBSet;
LuckyItemDBSet g_LuckyItemDBSet;
CMonsterKillInfoDbSet g_MonsterKillInfoDbSet;
CBlockChatUserDBSet g_BlockChatUserDBSet;
LabyrinthDBSet g_LabyrinthDBSet;
CRestoreItemDBSet g_CRestoreItemDBSet;
CPlayTimeEventDBSet g_PlayTimeEventDBSet;
CPCBangRenewalDBSet g_PCBangRenewalDBSet;
CMuunSystemDBSet g_CMuunSystemDBSet;
CMineSystemDBSet g_MineSystemDBSet;
CHuntingRecordDBSet g_HuntingRecordDBSet;
CPentagramDBSet g_PentagramDBSet;
CPentagramLogDBSet g_PentagramLogDBSet;
CArcaBattleDBSet gCArcaBattleDBSet;
CPeriodBuffDBSet g_PeriodBuffDBSet;
CMuRummyDBSet g_CMuRummyDBSet;
CBombHuntDBSet g_BombHuntDBSet;
CPShopSystemDBSet g_PShopSystemDBSet;
CSPServerDBSet g_SPServerDBSet;
IllusionTempleLeagueDBSet g_ITLDBset;
EventMapEnterCount g_EventMapEnterCount;
CRuudLogDbSet g_RuudLogDBSet;
CGremoryCaseDBSet g_CGremoryCaseDBSet;
CDevilSquareFinalDBSet g_DSFDBset;
ChaosCastleFinalDBSet g_CCFDbSet;

BOOL gbIsJumpingServer;

CQuestExpDBSet g_QuestExpDBSet;
CPeriodItemExDBSet PeriodItemExDBSet;
CMasterLevelSystemDBSet MasterLevelSystemDBSet;
CQuestMonKillDBSet QuestMonKillDBSet;
CCrywolfDBSet CrywolfDBSet;
CCastleDBSet CastleDBSet;
CPetDBSet PetDBSet;
CCharDBSet gCharDbSet;
CAccountCharDBSet gACDbSet;

CGSDBSet gGSDbSet;
CDirPath gDirPath;
classdef DCInfo;

char szDbConnectID[52];
char szDbConnectPass[52];
char szDbConnectDsn[52];

#define WM_ASYNCSELECTMSG_CLIENT		(WM_USER+1001)

#define WM_ASYNCSELECTMSG_SERVERACCEPT	(WM_USER+1002)

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ASYNCSELECTMSG_SERVERACCEPT, OnAsyncSelectServerAccept)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CDataserverApp* DataApp = (CDataserverApp*)AfxGetApp(); //0x08

	char szText[256]; //0x108
	WZSMDToken iTokenType; //0x10C

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		return -1;
	}

	//
	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
	//	| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	//{
	//	return -1;      // fail to create
	//}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
			sizeof(indicators) / sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	LogInit(LOG_PRINT);

	gDirPath.SetFirstPath("..\\data\\");

	if (CWZSEncode.Open(".\\dataserver.ini.dat") == FALSE)
	{
		AfxMessageBox("file 'dataserver.ini.dat' is not exist in local folder.", 16, 0);
	}

	CWZSEncode.GetToken();	gNewAccountCreate = CWZSEncode.GetNumber();
	CWZSEncode.GetToken();	//DataApp->m_ServerPort = CWZSEncode.GetNumber();
	CWZSEncode.GetToken();	strcpy(szDbConnectID, CWZSEncode.GetString());
	CWZSEncode.GetToken();	strcpy(szDbConnectPass, CWZSEncode.GetString());
	CWZSEncode.GetToken();	DCInfo.SetMabubBanjiOption(CWZSEncode.GetNumber());

	iTokenType = CWZSEncode.GetToken();
	if (iTokenType == T_END)
		strcpy(szDbConnectDsn, "MuOnline");
	else strcpy(szDbConnectDsn, CWZSEncode.GetString());

	if (iTokenType != 2)
	{
		gbIsJumpingServer = CWZSEncode.GetNumber();//season12
	}
		
	if (strcmp(szDbConnectDsn, "") == 0)
	{
		strcpy(szDbConnectDsn, "MuOnline");
	}

	LogAddTD("szDbConnectDsn %s ", __FILE__, __LINE__);

	CWZSEncode.Close();

	gCharDbSet.SetSP_WZ_CreateCharacterGetVersion(GetPrivateProfileInt("DataServerInfo", "CreateCharacterSP_Ver", 1, "..\\data\\dataserver.ini"));

	gLanguage = GetPrivateProfileInt("GameServerInfo", "Language", 0, gDirPath.GetNewPath("commonserver.cfg"));

	strcpy(szKorItemTextFileName, gDirPath.GetNewPath("lang\\kor\\item(kor).txt"));
	strcpy(szKorSkillTextFileName, gDirPath.GetNewPath("lang\\kor\\skill(kor).txt"));

	wsprintf(szText, "Data Server Port:%d App ver : %s %s", DataApp->GetServerPort(), szVersion, __DATE__);

	switch (gLanguage)
	{
	case 0:
	{
		strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\kor\\item(kor).txt"));
		strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\kor\\skill(kor).txt"));
		strcat(szText, "(Kor)");
	}
	break;
	case 1:
	{
		strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\eng\\item(eng).txt"));
		strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\eng\\skill(eng).txt"));
		strcat(szText, "(Eng)");
	}
	break;
	case 2:
	{
		strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\jpn\\item(jpn).txt"));
		strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\jpn\\skill(jpn).txt"));
		strcat(szText, "(Jpn)");
	}
	break;
	case 3:
	{
		strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\chs\\item(chs).txt"));
		strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\chs\\skill(chs).txt"));
		strcat(szText, "(Chs)");
	}
	break;
	case 4:
	{
		strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\tai\\item(tai).txt"));
		strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\tai\\skill(tai).txt"));
		strcat(szText, "(Tai)");
	}
	break;
	case 5:
	{
		strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\tha\\item(tha).txt"));
		strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\tha\\skill(tha).txt"));
		strcat(szText, "(Tha)");
	}
	break;
	case 6:
	{
		strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\phi\\item(phi).txt"));
		strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\phi\\skill(phi).txt"));
		strcat(szText, "(Phi)");
	}
	break;
	case 7:
	{
		strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\vtm\\item(vtm).txt"));
		strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\vtm\\skill(vtm).txt"));
		strcat(szText, "(Vtm)");
	}
	break;
	}
	if (OpenItemScript(szKorItemTextFileName) == FALSE)
	{
		MsgBox("Item FIle Not Found. (파일이 존재하지 않습니다.) %s", szKorItemTextFileName);
	}

	if (gLanguage == 0)
	{
		if (gMuName.NameLoad(szItemTextFileName) == FALSE)
		{
			MsgBox("Item File Not Found.");
		}
	}
	else if (gMuName.NameLoad(szKorItemTextFileName) == FALSE)
	{
		MsgBox("Item File Not Found.");
	}

	if (gMuName.NameLoad("..\\data\\Monster.txt") == FALSE)
	{
		MsgBox("Monster File Not Found.");
	}

	if (gLanguage == 0)
	{
		if (gMuName.NameLoad(szSkillTextFileName) == FALSE)
		{
			MsgBox("Skill File Not Found.");
		}
	}
	else if (gMuName.NameLoad(szKorSkillTextFileName) == FALSE)
	{
		MsgBox("Skill File Not Found.");
	}

	DCInfo.Init();

	if (cBadStrChk.Load("..\\data\\badsyntax.txt") == FALSE)
	{
		MsgBox("badstring load error");
	}

#ifdef MAP_SERVER_WORK_20041030
	if (g_MapServerManager.LoadMapData(gDirPath.GetNewPath("MapServerInfo.dat")) == FALSE)
	{
		MsgBox("Map Server Data load error");
	}
#endif

	CRect mWin;

	mWin.top = 0;
	mWin.bottom = GetSystemMetrics(SM_CYFULLSCREEN);

	if (DataApp->GetServerPosition() <= 1)
	{
		mWin.left = 0;
		mWin.right = GetSystemMetrics(SM_CXFULLSCREEN) / 2;
	}
	else
	{
		mWin.left = GetSystemMetrics(SM_CXFULLSCREEN) / 2;
		mWin.right = GetSystemMetrics(SM_CXFULLSCREEN);
	}

	this->CWnd::MoveWindow((LPRECT)mWin);

	this->CWnd::SetWindowText(szText);

	this->CWnd::SetTimer(1001, 1000, NULL);
	this->CWnd::SetTimer(1000, 100000, NULL);

	if (this->ServerCreate() == FALSE)
	{
		return -1;
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0, 0, 0, 0);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

//----------------------------------------------------------------------------
// 서버의 접속 메시지를 처리
//----------------------------------------------------------------------------
LONG CMainFrame::OnAsyncSelectServerAccept(WPARAM wParam, LPARAM lParam)
{
	switch ((WORD)lParam & 0xFFFF)
	{
	case FD_ACCEPT:
		AcceptClient();
		break;
	case FD_CLOSE:
		closesocket(wParam);
		LogAdd("port check close");
		break;
	}
	return TRUE;
}

//----------------------------------------------------------------------------
// Join 서버에 사용자가 접속해 왔을때
//----------------------------------------------------------------------------
// type : 
// CLINETACCEPTTYPE : 클라이언트가(유저) 접속했을때 
// SERVERACCEPTTYPE : 서버가 접속했을때 
int CMainFrame::AcceptClient()
{
	LogAdd("port check accept");

	SOCKET		clientSocket;
	IN_ADDR		clientAddr;

	wsjServer.AcceptSocket(clientSocket, clientAddr);

	return TRUE;
}

void CMainFrame::OnTimer(UINT nIDEvent)
{
	switch (nIDEvent)
	{
	case 1001:
		this->Invalidate(TRUE);
		break;
	case 1000:
		LogDateChange();
		break;
	}
	this->CWnd::OnTimer(nIDEvent);
}

BOOL CMainFrame::ServerCreate()
{
	CDataserverApp* DataApp = (CDataserverApp*)AfxGetApp();

	gSObjInit();

	//DbSet
	if (!gGSDbSet.Connect())
	{
		return FALSE;
	}

	if (!gACDbSet.Connect())
	{
		return FALSE;
	}

	if (!gCharDbSet.Connect())
	{
		return FALSE;
	}

	if (!gCharPreDBSet.Conenect())
	{
		return FALSE;
	}

	CZenEvenDBSet.Connect();

	if (!CWhDBSet.Connect())
	{
		return FALSE;
	}

	if (!gItemExtDbSet.Connect())
	{
		return FALSE;
	}

	if (!gOptionDbSet.Connect())
	{
		return FALSE;
	}

	if (!gGSDbSet.CheckMuDBIdentification())
	{
		MsgBox("☆ Unknow MuDB Id.");
	}
	else
	{
		CString szTitle;
		CString szNewTitle;

		this->GetWindowText(szTitle);

		szNewTitle.Format("%s - ☆ %s", szTitle, g_szDBID_DESC);

		this->SetWindowText(szNewTitle);
	}

	gItemCount = gGSDbSet.GetCount();

	//DbSet New
#ifdef DARKLORD_WORK
	if (!PetDBSet.Connect())
	{
		return FALSE;
	}
#endif

#ifdef MU_CASTLESIEGE_DS_PROTOCOL_20041105
	if (!CastleDBSet.Connect())
	{
		return FALSE;
	}
#endif

#ifdef MU_CRYWOLF_DS_PROTOCOL_20050505
	if (!CrywolfDBSet.Connect())
	{
		return FALSE;
	}
#endif

	if (!QuestMonKillDBSet.Connect())
	{
		return FALSE;
	}

#ifdef MASTER_LEVEL_UP_SYSTEM_20070912
	if (!MasterLevelSystemDBSet.Connect())
	{
		return FALSE;
	}
#endif

	if (!g_QuestExpDBSet.Connect())
	{
		return FALSE;
	}

	if (!PeriodItemExDBSet.Connect())
	{
		return FALSE;
	}

	if (!g_LuckyItemDBSet.Connect())
	{
		return FALSE;
	}
	//season12+
	if (!g_MonsterKillInfoDbSet.Connect())
	{
		return FALSE;
	}
	if (!g_BlockChatUserDBSet.Connect())
	{
		return FALSE;
	}
	if (!g_LabyrinthDBSet.Connect())
	{
		return FALSE;
	}
	if (!g_CRestoreItemDBSet.Connect())
	{
		return FALSE;
	}
	if (!g_PlayTimeEventDBSet.Connect())
	{
		return FALSE;
	}
	if (!g_PCBangRenewalDBSet.Connect())
	{
		return FALSE;
	}
	if (!g_CMuunSystemDBSet.Connect())
	{
		return FALSE;
	}
	if (!g_MineSystemDBSet.Connect())
	{
		return FALSE;
	}
	if (!g_HuntingRecordDBSet.Connect())
	{
		return FALSE;
	}
	if (!g_PentagramDBSet.Connect())
	{
		return FALSE;
	}
	if (!g_PentagramLogDBSet.Connect())
	{
		return FALSE;
	}
	if (!gCArcaBattleDBSet.Connect())
	{
		return FALSE;
	}
	if (!g_PeriodBuffDBSet.Connect())
	{
		return FALSE;
	}
	if (!g_CMuRummyDBSet.Connect())
	{
		return FALSE;
	}
	if (!g_BombHuntDBSet.Connect())
	{
		return FALSE;
	}
	if (!g_PShopSystemDBSet.Connect())
	{
		return FALSE;
	}
	if (!g_SPServerDBSet.Connect())
	{
		return FALSE;
	}
	if (!g_ITLDBset.Connect())
	{
		return FALSE;
	}
	if (!g_EventMapEnterCount.Connect())
	{
		return FALSE;
	}
	if (!g_RuudLogDBSet.Connect())
	{
		return FALSE;
	}
	if (!g_CGremoryCaseDBSet.Connect())
	{
		return FALSE;
	}
	if (!g_DSFDBset.Connect())
	{
		return FALSE;
	}
	if (!g_CCFDbSet.Connect())
	{
		return FALSE;
	}
	/*CMonsterKillInfoDbSet g_MonsterKillInfoDbSet;
	CBlockChatUserDBSet g_BlockChatUserDBSet;
	LabyrinthDBSet g_LabyrinthDBSet;
	CRestoreItemDBSet g_CRestoreItemDBSet;
	CPlayTimeEventDBSet g_PlayTimeEventDBSet;
	CPCBangRenewalDBSet g_PCBangRenewalDBSet;
	CMuunSystemDBSet g_CMuunSystemDBSet;
	CMineSystemDBSet g_MineSystemDBSet;
	CHuntingRecordDBSet g_HuntingRecordDBSet;
	CPentagramDBSet g_PentagramDBSet;
	CPentagramLogDBSet g_PentagramLogDBSet;
	CArcaBattleDBSet gCArcaBattleDBSet;
	CPeriodBuffDBSet g_PeriodBuffDBSet;
	CMuRummyDBSet g_CMuRummyDBSet;
	CBombHuntDBSet g_BombHuntDBSet;
	CPShopSystemDBSet g_PShopSystemDBSet;
	CSPServerDBSet g_SPServerDBSet;
	IllusionTempleLeagueDBSet g_ITLDBset;
	EventMapEnterCount g_EventMapEnterCount;
	CRuudLogDbSet g_RuudLogDBSet;
	CGremoryCaseDBSet g_CGremoryCaseDBSet;
	CDevilSquareFinalDBSet g_DSFDBset;
	ChaosCastleFinalDBSet g_CCFDbSet;*/
	if (strcmp(szVersion, "4.1") == 0)
	{
		MsgBox("4.0 버젼에선 VER_CHATWINDOW_OPTION 이 추가될시 문제가 발생합니다");
	}

	cAM.StartThread();

	g_WZIPCheck.Init();

	LogAdd("DataServer Run");

	CreateGIocp(DataApp->GetServerPort());

	wsjServer.MyWinsockBase::CreateSocket(this->m_hWnd);
	wsjServer.CreateServer(NULL, DataApp->GetServerPort() + 1, 2026, 0);
	return TRUE;
}

void CMainFrame::OnClose()
{
	int n, count = 0;

	for (n = 0; n < MAX_SERVEROBJECT; n++)
	{
		if (gSObj[n].Connected != 0)
		{
			LogAdd(" %s GameServer Conneting... ", &gSObj[n].ServerCode);
			count++;
		}
	}

	char szTemp[256] = "Server Close?";

	if (count > 0)
	{
		wsprintf(szTemp, "%d Gameserver's are connected. Forced termination may result in data loss.", count);
		AfxMessageBox(szTemp, 16, 0);
	}

	if (AfxMessageBox("Are you sure you want to close the connection?", 36, 0) == 7)
	{
		return;
	}

	for (n = 0; n < MAX_SERVEROBJECT; n++)
	{
		gSObjDel(n);
	}

	this->CFrameWnd::OnClose();
}

DWORD WINAPI GuildLoadThread(LPVOID p)
{
	return 1;
}

void CMainFrame::DisplayStatusBar(char *szString)
{
	this->m_wndStatusBar.SetWindowText(szString);
}