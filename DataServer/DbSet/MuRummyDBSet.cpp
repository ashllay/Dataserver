#include "StdAfx.h"
#include "MuRummyDBSet.h"

CMuRummyDBSet::CMuRummyDBSet()
{
}

CMuRummyDBSet::~CMuRummyDBSet()
{
}

BOOL CMuRummyDBSet::Connect()
{
	//return this->CDBConBase::Connect(szDbConnectID, szDbConnectPass);
	if (m_DBQuery.Connect(3, szDbConnectDsn, szDbConnectID, szDbConnectPass))
		return 1;
	MsgBox("CMuRummyDBSet ODBC Connect Fail");
	return 0;
}

BOOL CMuRummyDBSet::DBSelectMuRummyCardInfo(char *szAccountID, char *szName, _tagMuRummyCardInfoDS *stOutMuRummyCardInfoDS, unsigned __int16 *wOutScore, BYTE *btGameType, BYTE *btSpecialCardDeckCnt)
{
	int result;
	__int16 sqlReturn;
	CString QueryStr;
	int iItemCount = 0;
	int iReturnCode = 0;

	QueryStr.Format("EXEC WZ_SetSelectMuRummy '%s', '%s'",szAccountID,szName);

	if (this->m_DBQuery.Exec(QueryStr))
	{
		sqlReturn = this->m_DBQuery.Fetch();
		if (sqlReturn == 100)
		{
			this->m_DBQuery.Clear();

			result = 0;
		}
		else
		{
			int iCnt = 0;
			while (1)
			{
				if (sqlReturn == 100 || sqlReturn == -1)
				{
					this->m_DBQuery.Clear();
					return 1;
				}
				if (iCnt >= 27)
					break;
				*wOutScore = this->m_DBQuery.GetInt("mTotalScore");
				*btGameType = this->m_DBQuery.GetInt("mGameType");
				*btSpecialCardDeckCnt = this->m_DBQuery.GetInt("mSPUseCnt");
				stOutMuRummyCardInfoDS[iCnt].btColor = this->m_DBQuery.GetInt("mColor");
				stOutMuRummyCardInfoDS[iCnt].btNumber = this->m_DBQuery.GetInt("mNumber");
				stOutMuRummyCardInfoDS[iCnt].btSlotNum = this->m_DBQuery.GetInt("mPosition");
				stOutMuRummyCardInfoDS[iCnt].btStatus = this->m_DBQuery.GetInt("mStatus");
				stOutMuRummyCardInfoDS[iCnt++].btSeq = this->m_DBQuery.GetInt("mSequence");
				sqlReturn = this->m_DBQuery.Fetch();
			}
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [MuRummy] DBSelectMuRummyCardInfo #2 [%s][%s] %s %d",szAccountID,szName, __FILE__, __LINE__);

			QueryStr.Format("EXEC WZ_SetDeleteMuRummy '%s', '%s'",szAccountID,szName);
			if (!this->m_DBQuery.Exec(QueryStr))
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [MuRummy] DBSelectMuRummyCardInfo #3 [%s][%s] %s %d",
					szAccountID,szName, __FILE__, __LINE__);
			}
			this->m_DBQuery.Clear();
			result = 0;
		}
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [MuRummy] DBSelectMuRummyCardInfo #1 [%s][%s] %s %d",
			szAccountID,szName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}



BOOL CMuRummyDBSet::DBInsertMuRummyCardInfo(char *szAccountID, char *szName, _tagMuRummyCardInfoDS *stMuRummyCardInfoDS, BYTE btGameType, BYTE btSpecialCardDeckCnt)
{
	int result;
	CString QueryStr;
	int iReturnCode;
	int iItemCount;

	iItemCount = 0;
	iReturnCode = 0;

	QueryStr.Format("EXEC WZ_SetSaveMuRummyInfo '%s', '%s', %d, %d, %d",szAccountID,szName,0,btGameType,btSpecialCardDeckCnt);
	if (this->m_DBQuery.Exec(QueryStr))
	{
		this->m_DBQuery.Clear();
		for (int i = 0; i < btSpecialCardDeckCnt + 24; ++i)
		{
			QueryStr.Format("EXEC WZ_SetInsertMuRummy '%s', '%s',%d, %d, %d, %d, %d ",szAccountID,szName,
				stMuRummyCardInfoDS[i].btNumber,
				stMuRummyCardInfoDS[i].btColor,
				stMuRummyCardInfoDS[i].btSlotNum,
				stMuRummyCardInfoDS[i].btStatus,
				stMuRummyCardInfoDS[i].btSeq);
			if (!this->m_DBQuery.Exec(QueryStr))
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [MuRummy] DBInsertMuRummyCardInfo #2 [%s][%s] %s %d",szAccountID,szName, __FILE__, __LINE__);
				return 0;
			}
			this->m_DBQuery.Clear();
		}
		this->m_DBQuery.Clear();

		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [MuRummy] DBInsertMuRummyCardInfo #1 [%s][%s] %s %d",szAccountID,szName, __FILE__, __LINE__);

		result = 0;
	}
	return result;
}



BOOL CMuRummyDBSet::DBUpdateMuRummyCardInfo(char *szAccountID, char *szName, int iSlotNum, int iStatus, int iSequence)
{
	int result;
	CString QueryStr;

	QueryStr.Format("EXEC WZ_SetUpdateMuRummy  '%s', '%s',%d, %d, %d",szAccountID,szName,iSlotNum,iStatus,iSequence);
	if (this->m_DBQuery.Exec(QueryStr))
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [MuRummy] DBUpdateMuRummyCardInfo #1 [%s][%s] %s %d",szAccountID,szName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}



BOOL CMuRummyDBSet::DBUpdateMuRummyScore(char *szAccountID, char *szName, unsigned __int16 wScore, _tagMuRummyCardUpdateDS *stCardUpdateDS, BYTE btGameType, BYTE btSpecialCardDeckCnt, BYTE btMatchType)
{
	int result;
	char btStatus;
	char btSeq;
	char btSlotNum;
	char btCheckSeq; 
	int nLoopCnt; 
	CString QueryStr;
					
	QueryStr.Format("EXEC WZ_SetSaveMuRummyInfo '%s', '%s', %d, %d, %d",
		szAccountID,szName,wScore,btGameType,btSpecialCardDeckCnt);

	if (this->m_DBQuery.Exec(QueryStr))
	{
		this->m_DBQuery.Clear();
		nLoopCnt = 0;
		btCheckSeq = 0;
		if (btMatchType == 1)
		{
			nLoopCnt = 4;
			btCheckSeq = 27;
		}
		else
		{
			nLoopCnt = 3;
			btCheckSeq = 24;
		}
		for (int i = 0; i < nLoopCnt; ++i)
		{
			btSlotNum = stCardUpdateDS[i].btSlotNum;
			btSeq = stCardUpdateDS[i].btSeq;
			btStatus = stCardUpdateDS[i].btStatus;
			if (btCheckSeq <= btSeq)
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [MuRummy] DBUpdateMuRummyScore - Card Sequence Over[%d] [%s][%s] %s %d",
					btSeq,szAccountID,szName, __FILE__, __LINE__);
				return 0;
			}
			QueryStr.Format(
				"EXEC WZ_SetUpdateMuRummy  '%s', '%s', %d, %d, %d",
				szAccountID,
				szName,
				btSlotNum,
				btStatus,
				btSeq);
			if (!this->m_DBQuery.Exec(QueryStr))
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [MuRummy] DBUpdateMuRummyScore #2 [%s][%s] %s %d",
					szAccountID,szName, __FILE__, __LINE__);
				return 0;
			}
			this->m_DBQuery.Clear();
		}
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [MuRummy] DBUpdateMuRummyScore #1 [%s][%s] %s %d",
			szAccountID,szName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


BOOL CMuRummyDBSet::DBDeleteMuRummyCardInfo(char *szAccountID, char *szName)
{
	int result;
	CString QueryStr;

	QueryStr.Format("EXEC WZ_SetDeleteMuRummy '%s', '%s'",szAccountID,szName);
	if (this->m_DBQuery.Exec(QueryStr))
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [MuRummy] DBDeleteMuRummyCardInfo #1 [%s][%s] %s %d",
			szAccountID,szName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


BOOL CMuRummyDBSet::DBUpdateMuRummyCardSlotInfo(char *szAccountID, char *szName, _tagMuRummyCardUpdateDS stCardUpdateDS)
{
	int result;
	char btStatus; 
	char btSeq;
	char btSlotNum;
	CString QueryStr;

	btSlotNum = stCardUpdateDS.btSlotNum;
	btSeq = stCardUpdateDS.btSeq;
	btStatus = stCardUpdateDS.btStatus;
	if (stCardUpdateDS.btSlotNum != 255 && btSlotNum < 10)
	{
		QueryStr.Format("EXEC WZ_SetUpdateMuRummy  '%s', '%s', %d, %d, %d",szAccountID,szName,btSlotNum,btStatus,btSeq);
		if (this->m_DBQuery.Exec(QueryStr))
		{
			this->m_DBQuery.Clear();
			result = 1;
		}
		else
		{
			this->m_DBQuery.Clear();
			LogAddTD("error-L3 : [MuRummy] DBUpdateMuRummyCardSlotInfo #1 [%s][%s] %s %d",szAccountID,szName, __FILE__, __LINE__);
			result = 0;
		}
	}
	else
	{
		LogAddTD("error-L3 : [MuRummy] btSlotNum [%d] [%s][%s] %s %d",btSlotNum,szAccountID,szName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


BOOL CMuRummyDBSet::DBUpdateMuRummyInfo(char *szAccountID, char *szName, unsigned __int16 wScore, _tagMuRummyCardUpdateDS *stCardUpdateDS, BYTE btGameType, BYTE btSpecialDeckCnt)
{
	int result;
	BYTE btStatus;
	BYTE btSeq;
	BYTE btSlotNum;
	CString QueryStr; 
	int iReturnCode;
	int iItemCount; 
	iItemCount = 0;
	iReturnCode = 0;

	QueryStr.Format("EXEC WZ_SetSaveMuRummyInfo '%s', '%s', %d, %d, %d",
		szAccountID,szName,wScore,btGameType,btSpecialDeckCnt);

	if (this->m_DBQuery.Exec(QueryStr))
	{
		this->m_DBQuery.Clear();
		for (int i = 0; i < btSpecialDeckCnt + 24; ++i)
		{
			btSlotNum = stCardUpdateDS[i].btSlotNum;
			btSeq = stCardUpdateDS[i].btSeq;
			btStatus = stCardUpdateDS[i].btStatus;
			if (btSpecialDeckCnt + 24 <= btSeq)
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [MuRummy] Card Sequence Over[%d] [%s][%s] %s %d",
					btSeq,szAccountID,szName, __FILE__, __LINE__);
				return 0;
			}
			QueryStr.Format("EXEC WZ_SetUpdateMuRummy  '%s', '%s', %d, %d, %d",
				szAccountID,szName,btSlotNum,btStatus,btSeq);

			if (!this->m_DBQuery.Exec(QueryStr))
			{
				this->m_DBQuery.Clear();
				LogAddTD("error-L3 : [MuRummy] DBUpdateMuRummyInfo #2 [%s][%s] %s %d",
					szAccountID,szName, __FILE__, __LINE__);
				return 0;
			}
			this->m_DBQuery.Clear();
		}
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [MuRummy] DBUpdateMuRummyInfo #1 [%s][%s] %s %d",
			szAccountID,szName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}


BOOL CMuRummyDBSet::DBInsertMuRummyLog(char *szAccountID, char *szName, unsigned __int16 wScore)
{
	int result;
	CString QueryStr;
					
	QueryStr.Format("EXEC WZ_SetSaveMuRummyLog  '%s', '%s', %d",
		szAccountID,szName,wScore);

	if (this->m_DBQuery.Exec(QueryStr))
	{
		this->m_DBQuery.Clear();
		result = 1;
	}
	else
	{
		this->m_DBQuery.Clear();
		LogAddTD("error-L3 : [MuRummy] DBInsertMuRummyLog #1 [%s][%s] %s %d",
			szAccountID,szName, __FILE__, __LINE__);
		result = 0;
	}
	return result;
}