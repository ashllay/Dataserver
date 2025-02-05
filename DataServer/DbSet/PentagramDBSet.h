// PentagramDBSet.h: interface for the CPentagramDBSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PENTAGRAMDBSET_H__01C748D6_E836_4267_AF43_66BD9D34C7DC__INCLUDED_)
#define AFX_PENTAGRAMDBSET_H__01C748D6_E836_4267_AF43_66BD9D34C7DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBConBase.h"

#define MAX_PENTAGRAMJEWEL_INFO 250

struct PMSG_REQ_PENTAGRAMJEWEL
{
	PBMSG_HEAD h;
	int iUserIndex;
	BYTE btJewelPos;
	int iUserGuid;
	char AccountId[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
};

struct PMSG_INSERT_PENTAGRAMJEWEL
{
	PBMSG_HEAD h;
	int iUserGuid;
	BYTE AccountId[MAX_IDSTRING + 1];
	BYTE szName[MAX_IDSTRING + 1];
	BYTE btJewelPos;
	BYTE btJewelIndex;
	BYTE btItemType;
	int iItemIndex;
	BYTE btMainAttribute;
	BYTE btLevel;
	BYTE btRank1OptionNum;
	BYTE btRank1Level;
	BYTE btRank2OptionNum;
	BYTE btRank2Level;
	BYTE btRank3OptionNum;
	BYTE btRank3Level;
	BYTE btRank4OptionNum;
	BYTE btRank4Level;
	BYTE btRank5OptionNum;
	BYTE btRank5Level;
};

struct _tagPMSG_REQ_JEWEL_UPGRADE_INFO_INSERT_DS
{
	PBMSG_HEAD h;
	char AccountID[MAX_IDSTRING + 1];
	char Name[MAX_IDSTRING + 1];
	short iJewelType;
	short iJewelIndex;
	short iUpgradeType;
	short iSuccess;
};

struct PENTAGRAMJEWEL_INFO
{
	BYTE btJewelPos;
	BYTE btJewelIndex;
	BYTE btMainAttribute;
	BYTE btItemType;
	WORD wItemIndex;
	BYTE btLevel;
	BYTE btRank1OptionNum;
	BYTE btRank1Level;
	BYTE btRank2OptionNum;
	BYTE btRank2Level;
	BYTE btRank3OptionNum;
	BYTE btRank3Level;
	BYTE btRank4OptionNum;
	BYTE btRank4Level;
	BYTE btRank5OptionNum;
	BYTE btRank5Level;
};

struct __declspec(align(4)) PMSG_PENTAGRAMJEWEL_INFO
{
	PWMSG_HEAD h;
	BYTE btJewelCnt;
	BYTE btJewelPos;
	int iUserGuid;
	char AccountId[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	PENTAGRAMJEWEL_INFO PentaGramInfo[MAX_PENTAGRAMJEWEL_INFO];
};

struct PMSG_ANS_PENTAGRAMJEWEL
{
	PWMSG_HEAD head;
	char btJewelCnt;
	int iUserIndex;
	int iAnsType;
};

struct PMSG_DEL_PENTAGRAMJEWEL
{
	PBMSG_HEAD h;
	int iUserGuid;
	char AccountId[MAX_IDSTRING + 1];
	char szName[MAX_IDSTRING + 1];
	BYTE btJewelPos;
	BYTE btJewelIndex;
};

class CPentagramDBSet : public CDBConBase
{
public:

	CPentagramDBSet();
	virtual ~CPentagramDBSet();

	BOOL Connect();
	int DelPentagramJewel(PMSG_DEL_PENTAGRAMJEWEL* lpMsg);
	int InsertPentagramJewel(PMSG_INSERT_PENTAGRAMJEWEL* lpMsg);
	int SetPentagramJewel(PMSG_PENTAGRAMJEWEL_INFO* src);
	int GetPentagramJewel(int UserGuid, char* Id, char* Char, PENTAGRAMJEWEL_INFO PentaGramInfo[250], PMSG_ANS_PENTAGRAMJEWEL* lpMsg, int JewelPos);
};

class CPentagramLogDBSet : public CDBConBase
{
public:
	CPentagramLogDBSet();
	virtual ~CPentagramLogDBSet();
	int Connect();
	int InsertJewelUpgradeInfo(_tagPMSG_REQ_JEWEL_UPGRADE_INFO_INSERT_DS* lpMsg);
};

#endif // !defined(AFX_PENTAGRAMDBSET_H__01C748D6_E836_4267_AF43_66BD9D34C7DC__INCLUDED_)
