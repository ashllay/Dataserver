#pragma once
//#include "Include\ProDef.h"
#include "..\Include\Sprodef.h"

#include "DBConBase.h"


class CDevilSquareFinalDBSet : public CDBConBase
{
public:

	CDevilSquareFinalDBSet();
	virtual ~CDevilSquareFinalDBSet();

	int Connect();
	void ReqCanPartyEnter(char *AccountID1, char *UserName1, char *AccountID2, char *UserName2, char btDSFType, int iEnterYear, char btEnterMonth, char btEnterDay, int *nEnterCount, int *nResult); // idb
	void UpdateDSFUserPoint(char *UserName, char *Gname, int DSFtype, int nPoint, int nEnterCount, int nWin); // idb
	void SaveDSFPartyPoint(char *szAccountID1, char *szUserName1, int nUser1Level, char *szAccountID2, char *szUserName2, int nUser2Level, int nType, int nPoint, char btEnterCount, int nEnterYear, char btEnterMonth, char btEnterDay); // idb
	void RenewDSFPartyRank(char btDSFType, int nYear, int nMonth, int nDay); // idb
	int TodayDSFPartyRank(_stDSFPartyRankInfo *DSFRank, char *btCount, char btDSFType, int nYear, int nMonth, int nDay); // idb
	int DSFGoFinalParty(_stDSFGoFinalPartyInfo *DSFRank, char *btCount, char btDSFType, int nYear, int nMonth, int nDay); // idb
	void InsertRewardUser(char *szAccountID, char *szUserName, int iClass, int nDSFType, int nRewardYear, char btRewardMonth, char btRewardStartDay, char btRewardEndDay); // idb
	int GetReward(char *szAccountID, char *szUserName, int nServerCode, int nRewardYear, char btRewardMonth, char btRewardDay); // idb

};