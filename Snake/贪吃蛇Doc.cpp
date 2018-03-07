// 贪吃蛇Doc.cpp : CMyDoc 类的实现
//

#include "stdafx.h"
#include "贪吃蛇.h"

#include "贪吃蛇Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyDoc

IMPLEMENT_DYNCREATE(CMyDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyDoc, CDocument)
END_MESSAGE_MAP()


// CMyDoc 构造/析构

CMyDoc::CMyDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMyDoc::~CMyDoc()
{
}

BOOL CMyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMyDoc 序列化

void CMyDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CMyDoc 诊断

#ifdef _DEBUG
void CMyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyDoc 命令
