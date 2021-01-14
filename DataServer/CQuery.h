#include <sql.h>
#include <sqlext.h>

class CQuery
{
public:

	enum
	{
		MAXCOL = 100,
		BLOBBATCH = 10000,
		CQUERYNULL = -100,
		CQUERYEOF = -101,
		CQUERYNOCOL = -102,
		CQUERYERROR = -103
	};

private:
	SQLHENV hEnv;							// ȯ�� �ڵ�
	SQLHDBC hDbc;							// ���� �ڵ�
	SQLRETURN ret;							// ���� ������ SQL���� �����
	char Col[MAXCOL][255];					// ���ε��� �÷� ����
	
	int	m_Type;
	char m_szConnect[128];
	char m_Id[20];
	char m_Pass[20];

	int FindCol(char *name);				// �÷��� �̸����κ��� ��ȣ�� ã���ش�.
	BOOL ReConnect();

public:
	SQLINTEGER AffectCount;					// ������� ���ڵ� ����
	SQLHSTMT hStmt;							// ��� �ڵ�. ���� ����� ���� �����Ƿ� public���� ����
	SQLSMALLINT nCol;						// �÷� ����
	SQLCHAR ColName[MAXCOL][50];			// �÷��� �̸���
	SQLINTEGER lCol[MAXCOL];				// �÷��� ����/���� ����

	void PrintDiag(bool &bReconnect);						// ���� ���� ���
	CQuery();								// ������
	~CQuery();								// �ı���:���� �ڵ��� �����Ѵ�.
	BOOL Connect(int Type, char *ConStr, char *UID=NULL, char *PWD=NULL);	// ������ �ҽ��� �����Ѵ�.
	BOOL Exec(LPCTSTR szSQL, BOOL bLog = TRUE);				// SQL���� �����Ѵ�.
	int ExecGetInt(LPCTSTR szSQL);			// SQL���� �����ϰ� ù��° �÷��� ���� ����
	int ExecGetInt(char* szSQL, int * retvalue);
	BOOL ExecGetStr(LPCTSTR szSQL, char *buf);		// SQL���� �����ϰ� ù��° �÷��� ���ڿ� ����
	SQLRETURN Fetch();						// �� �� ��������
	void Clear();							// Ŀ�� ���� �� �� ���ε�
	int GetInt(int nCol);					// ������ �÷� �б�
	int GetInt(char *sCol);					// ������ �÷� �б�
	__int64 GetInt64(char* sCol);
	__int64 GetInt64(int nCol);
	float GetFloat(int nCol);
	float GetFloat(char *sCol);
	void GetStr(int nCol, char *buf);		// ���ڿ��� �÷� �б�
	void GetStr(char *sCol, char *buf);		// ���ڿ��� �÷� �б�
	int ReadBlob(LPCTSTR szSQL, void *buf);
	void WriteBlob(LPCTSTR szSQL, void *buf, int size);
	int BindParameterBinaryOutput(int nCol, BYTE *nValue, int iSize, long *lLength);
	BOOL ReadInt64(LPCTSTR szSQL, INT64 &buf);
	void WriteInt64(LPCTSTR szSQL, INT64 *buf);
	int IsConnected();//new
};
