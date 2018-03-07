// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "贪吃蛇.h"
#include<windows.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	/*
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
	| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
	TRACE0("未能创建工具栏\n");
	return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this) ||
	!m_wndStatusBar.SetIndicators(indicators,
	sizeof(indicators)/sizeof(UINT)))
	{
	TRACE0("未能创建状态栏\n");
	return -1;      // 未能创建
	}

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);*/
	
	PlaySound("e:\\大二上\\贪吃蛇\\音效\\I Still Believe In Love-Jenny Hyun.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style = WS_OVERLAPPED | WS_CAPTION //| FWS_ADDTOTITLE
		| WS_MINIMIZEBOX | WS_SYSMENU;
	cs.cx = 1200;
	cs.cy = 800;
	cs.lpszName = "双人疯狂贪吃蛇";


	return TRUE;
}


// CMainFrame 诊断

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


// CMainFrame 消息处理程序
