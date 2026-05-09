#ifndef INTERACTIVECONTEXT_H_
#define INTERACTIVECONTEXT_H_

#define INTERACTIVE_BUTTON_PREPAGE		0
#define INTERACTIVE_BUTTON_NEXTPAGE		1
#define INTERACTIVE_BUTTON_CLOSE		2

#include "../../CommonModule/ByteBuffer.h"
#include "../../CommonModule/GamePacket.h"   // brings in InteractiveDialogItem
#include <Windows.h>
#include <vector>

typedef std::vector<InteractiveDialogItem> InteractiveDialogItemList;

//	> 5 �İ�ť����ID ���ᱻ�����ű�����

#define BUFER_SIZE						1024 * 2


//	�������������� ҳ����0��ʼ ȷ����ť����������紦�� �����Լ�����
/*  '/'ת��� p������ҳ�� h���� t���� b��ť
Format: /p/h[TEXT]/t/b[ID][TEXT]/p[NEXTPAGE]
Exp:	/p/hС��/t����Ҫ��/b3ȷ��...
*/

class InteractiveContext
{
public:
	InteractiveContext();
	~InteractiveContext();

public:
	//	���ӿ�
	void AddPage();
	void AddButton(int _id, const char* _text);
	void AddHead(const char* _text);
	void AddText(const char* _text);
	//void EndPage();

public:
	//	�ڲ�����
	int GetPageCount();
	int GetCurPage();
	bool NextPage();
	bool PrevPage();
	const char* GetTitle();
	const char* GetText();
	int GetButtonSum();
	int GetButtonID(int _idx);
	const char* GetButtonText(int _idx);

public:
	void Reset();
	void Init();
	bool CheckValid();
	bool LoadFromFile(const char* lpszFileName);

private:
	bool InternalCheck();
	void InternalUpdateReadOffset(bool _forward);
	void InternalUpdateDataLength();

private:
	int m_nCurWritePage;
	int m_nCurReadpage;
	int m_nCurReadPageOffsetBegin;
	int m_nCurReadPageOffsetEnd;
	int m_nCurReadDataLength;
	int m_nPageSum;
	char m_szData[BUFER_SIZE];
	char m_szRet[BUFER_SIZE / 2];
};

struct ContextNode
{
	RECT rcLocate;
	const char *szMsg;
	DWORD dwID;
};
typedef std::list<ContextNode*> CONTEXTNODELIST;

class InteractiveContextEx
{
public:
	InteractiveContextEx();
	~InteractiveContextEx();

public:
	//	All for script
	void AddContextNode(int _x, int _y, const char* _pMsg, int _nId);
	void Clear();

	//	Not for script
	CONTEXTNODELIST& GetNodes()
	{
		return m_xNodes;
	}
	int GetButtonID(int _idx);

private:
	ByteBuffer m_xContext;
	std::list<ContextNode*> m_xNodes;
};
//////////////////////////////////////////////////////////////////////////
#endif