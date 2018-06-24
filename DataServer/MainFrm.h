
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#include "ActiveMng.h"
#include "common\WZScriptEncode.h"
#include "wsJoinServer.h"
#include "common\MuNameCheck.h"
#include "DBSet\GSDBSet.h"
#include "DbSet\CharDBSet.h"
#include "DbSet\AccountCharDBSet.h"
#include "DbSet\CastleDBSet.h"
#include "DbSet\CharPreviewDBSet.h"
#include "DbSet\CrywolfDBSet.h"
#include "DbSet\ItemExtDbSet.h"
#include "DbSet\MasterLevelSystemDBSet.h"
#include "DbSet\PeriodItemExDBSet.h"
#include "DbSet\PetDBSet.h"
#include "DbSet\QuestExpDBSet.h"
#include "DbSet\QuestMonKillDBSet.h"
#include "DbSet\WarehouseDBSet.h"
#include "DbSet\ZenEvenDb.h"
#include "DbSet\OptionDbSet.h"
#include "DirPath.h"
#include "common\classdef.h"
#include "ChildView.h"
//season 12+
#include "DbSet\EvolutionMonsterKillInfoDBSet.h"
#include "DbSet\BlockChatUserDBSet.h"
#include "DbSet\LabyrinthDBSet.h"
#include "DbSet\RestoreItemDBSet.h"
#include "DbSet\PlayTimeEventDBSet.h"
#include "DbSet\PCBangRenewalDBSet.h"
#include "DbSet\MuunSystemDbSet.h"
#include "DbSet\MineSystemDBSet.h"
#include "DbSet\HuntingRecordDBSet.h"
#include "DbSet\PentagramDBSet.h"
#include "DbSet\ArcaBattleDBSet.h"
#include "DbSet\MuRummyDBSet.h"
#include "DbSet\BombHuntDBSet.h"
#include "DbSet\PShopSystemDBSet.h"
#include "DbSet\SPServerDBSet.h"
#include "DbSet\IllusionTempleLeagueDBSet.h"
#include "DbSet\EventMapEnterCount.h"
#include "DbSet\RuudLogDbSet.h"
#include "DbSet\GremoryCaseDBSet.h"
#include "DbSet\DevilSquareFinalDBSet.h"
#include "DbSet\ChaosCastleFinalDBSet.h"

extern CMonsterKillInfoDbSet g_MonsterKillInfoDbSet;
extern CBlockChatUserDBSet g_BlockChatUserDBSet;
extern LabyrinthDBSet g_LabyrinthDBSet;
extern CRestoreItemDBSet g_CRestoreItemDBSet;
extern CPlayTimeEventDBSet g_PlayTimeEventDBSet;
extern CPCBangRenewalDBSet g_PCBangRenewalDBSet;
extern CMuunSystemDBSet g_CMuunSystemDBSet;
extern CMineSystemDBSet g_MineSystemDBSet;
extern CHuntingRecordDBSet g_HuntingRecordDBSet;
extern CPentagramDBSet g_PentagramDBSet;
extern CPentagramLogDBSet g_PentagramLogDBSet;
extern CArcaBattleDBSet gCArcaBattleDBSet;
extern CPeriodBuffDBSet g_PeriodBuffDBSet;
extern CMuRummyDBSet g_CMuRummyDBSet;
extern CBombHuntDBSet g_BombHuntDBSet;
extern CPShopSystemDBSet g_PShopSystemDBSet;
extern CSPServerDBSet g_SPServerDBSet;
extern IllusionTempleLeagueDBSet g_ITLDBset;
extern EventMapEnterCount g_EventMapEnterCount;
extern CRuudLogDbSet g_RuudLogDBSet;
extern CGremoryCaseDBSet g_CGremoryCaseDBSet;
extern CDevilSquareFinalDBSet g_DSFDBset;
extern ChaosCastleFinalDBSet g_CCFDbSet;
extern int gbIsJumpingServer;

extern char szVersion[];

extern CActiveMng cAM;

extern char szKorSkillTextFileName[];
extern char szKorItemTextFileName[];
extern char szSkillTextFileName[];
extern char szItemTextFileName[];

extern int gLanguage;
extern int gNewAccountCreate;

extern DWORD gItemCount;

extern CWZScriptEncode CWZSEncode;

extern CwsJoinServer wsjServer;

extern CMuNameCheck gMuName;

extern COptionDbSet gOptionDbSet;
extern CItemExtDbSet gItemExtDbSet;
extern CQuery GuildMemberQry;
extern CWarehouseDBSet CWhDBSet;
extern CZenEvenDb CZenEvenDBSet;
extern CCharPreviewDBSet gCharPreDBSet;
extern LuckyItemDBSet g_LuckyItemDBSet;
extern CQuestExpDBSet g_QuestExpDBSet;
extern CPeriodItemExDBSet PeriodItemExDBSet;
#ifdef MASTER_LEVEL_UP_SYSTEM_20070912
extern CMasterLevelSystemDBSet MasterLevelSystemDBSet;
#endif
extern CQuestMonKillDBSet QuestMonKillDBSet;
#ifdef MU_CRYWOLF_DS_PROTOCOL_20050505
extern CCrywolfDBSet CrywolfDBSet;
#endif
#ifdef MU_CASTLESIEGE_DS_PROTOCOL_20041105
extern CCastleDBSet CastleDBSet;
#endif
#ifdef DARKLORD_WORK
extern CPetDBSet PetDBSet;
#endif
extern CCharDBSet gCharDbSet;
extern CAccountCharDBSet gACDbSet;

extern CGSDBSet gGSDbSet;
extern CDirPath gDirPath;
extern classdef DCInfo;

//extern char szDbConnectID[];
//extern char szDbConnectPass[];
//extern char szDbConnectDsn[];

class CMainFrame : public CFrameWnd
{

public: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CChildView  m_wndView;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg void DisplayStatusBar(char* szString);
	afx_msg BOOL ServerCreate();
	afx_msg int AcceptClient();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg LONG OnAsyncSelectServerAccept(WPARAM wParam, LPARAM lParam);
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


