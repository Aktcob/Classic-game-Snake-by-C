// 贪吃蛇View.cpp : CMyView 类的实现
//

#include "stdafx.h"
#include "贪吃蛇.h"

#include "贪吃蛇Doc.h"
#include "贪吃蛇View.h"
#include "mmsystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyView

IMPLEMENT_DYNCREATE(CMyView, CView)

BEGIN_MESSAGE_MAP(CMyView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_START, &CMyView::OnStart)
	ON_COMMAND(IDM_PAUSE, &CMyView::OnPause)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CMyView 构造/析构

CMyView::CMyView()

{
	this->m_start = false;
	this->m_pause = false;

	// TODO: 在此处添加构造代码
	snake1.mm_string = _T("");
	snake1.Time = 601;
	CString m5;
	m5.Format("%d", snake1.Time / 10);
	snake1.m_string = "剩余时间：" + m5;
	//初始化得分
	snake1.m_marks = 0;
	snake1.m_string = _T("");
	snake2.m_marks = 0;
	snake2.m_string = _T("");
	CString m1;
	m1.Format("%d", snake1.m_marks);
	snake1.m_string = "玩家1的得分是：" + m1;
	CString m2;
	m2.Format("%d", snake2.m_marks);
	snake2.m_string = "玩家2的得分是：" + m2;

	//初始化蛇1
	snake1.n = 3, snake1.direction = 2;
	snake1.power = -1;
	snake1.body[0].i = 2, snake1.body[0].j = 5;
	snake1.body[1].i = 2, snake1.body[1].j = 4;
	snake1.body[2].i = 2, snake1.body[2].j = 3;



	//初始化蛇2
	snake2.n = 3, snake2.direction = 4;
	snake2.power = -1;
	snake2.body[0].i = 18, snake2.body[0].j = 25;
	snake2.body[1].i = 18, snake2.body[1].j = 26;
	snake2.body[2].i = 18, snake2.body[2].j = 27;



	//初始化豆子
	unsigned int seed = time(NULL);
	srand(seed);
	do
	{
		bean.i =5+( rand() % 10);
		bean.j =5+( rand() % 20);
		bean.s = rand() % 3;
	} while (snake1.IsBeanInSnake(bean.i, bean.j) == true && snake2.IsBeanInSnake(bean.i, bean.j) == true);




}

CMyView::~CMyView()
{
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMyView 绘制

void CMyView::OnDraw(CDC* pDC)
{
	int k = 1;    //动态效果
	CMyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//画背景
	CDC dcmemory;
	dcmemory.CreateCompatibleDC(pDC);
	CBitmap bitmap;
	bitmap.LoadBitmapA(IDB_BITMAP1);
	dcmemory.SelectObject(&bitmap);
	int i, j;
	for (i = 0; i <= 30; i++)
	{
		for (j = 0; j <= 20; j++)
		{
			pDC->StretchBlt(0 + 30 * i, 0 + 30 * j, 30, 30, &dcmemory, 0, 0, 48, 48, SRCCOPY);
		}
	}
	bitmap.Detach();

	//画蛇头1
	bitmap.LoadBitmapA(IDB_BITMAP2);
	dcmemory.SelectObject(&bitmap);
	pDC->StretchBlt(0 + 30 * snake1.body[0].j, 0 + 30 * snake1.body[0].i, 30, 30, &dcmemory, 0, 0, 48, 48, SRCCOPY);
	bitmap.Detach();
	//画蛇身1
	bitmap.LoadBitmapA(IDB_BITMAP3);
	dcmemory.SelectObject(&bitmap);
	for (i = 1; i <= snake1.n; i++)
	{
		pDC->StretchBlt(0 + 30 * snake1.body[i].j, 0 + 30 * snake1.body[i].i, 30, 30, &dcmemory, 0, 0, 48, 48, SRCCOPY);
	}

	bitmap.Detach();




	//画蛇头2
	bitmap.LoadBitmapA(IDB_BITMAP7);
	dcmemory.SelectObject(&bitmap);
	pDC->StretchBlt(0 + 30 * snake2.body[0].j, 0 + 30 * snake2.body[0].i, 30, 30, &dcmemory, 0, 0, 48, 48, SRCCOPY);
	bitmap.Detach();
	//画蛇身2
	bitmap.LoadBitmapA(IDB_BITMAP3);
	dcmemory.SelectObject(&bitmap);
	for (i = 1; i <= snake2.n; i++)
	{
		pDC->StretchBlt(0 + 30 * snake2.body[i].j, 0 + 30 * snake2.body[i].i, 30, 30, &dcmemory, 0, 0, 48, 48, SRCCOPY);
	}

	bitmap.Detach();
	//画豆子
	switch (bean.s){
	case 0:
		bitmap.LoadBitmapA(IDB_BITMAP4);
		break;
	case 1:
		bitmap.LoadBitmapA(IDB_BITMAP5);
		break;
	case 2:
		bitmap.LoadBitmapA(IDB_BITMAP6);
		break;
	}
	dcmemory.SelectObject(&bitmap);
	pDC->StretchBlt(0 + 30 * bean.j, 0 + 30 * bean.i, 30, 30, &dcmemory, 0, 0, 48, 48, SRCCOPY);
	bitmap.Detach();

	//显示得分
	pDC->TextOutA(980, 20, snake1.m_string);
	pDC->TextOutA(980, 40, snake2.m_string);
	pDC->TextOutA(980, 60, snake1.mm_string);





}


// CMyView 打印


BOOL CMyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}
// CMyView 诊断

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDoc* CMyView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));
	return (CMyDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyView 消息处理程序

void CMyView::OnStart()
{
	// TODO: 在此添加命令处理程序代码
	this->m_start = true;
	this->m_pause = false;//暂停后，可以按开始继续
	SetTimer(1, 100, NULL);
}

void CMyView::OnPause()
{
	// TODO: 在此添加命令处理程序代码
	this->m_pause = true;
}

void CMyView::OnTimer(UINT_PTR nIDEvent)
{

	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (this->m_start == true && this->m_pause == false)
	{
		CGe temp;
		CClientDC dc(this);
		CDC dcmemory;
		dcmemory.CreateCompatibleDC(&dc);
		CBitmap bitmap;
		//显示时间
		COLORREF clr = dc.SetTextColor(dc.GetBkColor());
		dc.TextOutA(980, 60, snake1.mm_string);
		snake1.Time = snake1.Time - 1;
		CString m4;
		m4.Format("%d", snake1.Time/10 );
		if (snake1.Time >= 100){
			snake1.mm_string = "剩余时间：" + m4;
		}
		else snake1.mm_string = "剩余时间：  " + m4;
		dc.SetTextColor(clr);
		dc.TextOutA(980, 60, snake1.mm_string);
	

		if (snake2.power<0){
			switch (snake1.direction)
			{
			case 1:
				temp = snake1.forwardup();
				break;
			case 2:
				temp = snake1.forwardright();
				break;
			case 3:
				temp = snake1.forwarddown();
				break;
			case 4:
				temp = snake1.forwardleft();
				break;
			}
			bitmap.LoadBitmapA(IDB_BITMAP9);        //蛇1的方向
			dcmemory.SelectObject(&bitmap);
			dc.StretchBlt(0 + 30 * temp.j, 0 + 30 * temp.i, 30, 30, &dcmemory, 0, 0, 48, 48, SRCCOPY);
			bitmap.Detach();
		}
		else snake2.power--;


		if (snake1.power < 0){
			switch (snake2.direction)
			{
			case 1:
				temp = snake2.forwardup();
				break;
			case 2:
				temp = snake2.forwardright();
				break;
			case 3:
				temp = snake2.forwarddown();
				break;
			case 4:
				temp = snake2.forwardleft();
				break;
			}                //蛇2的方向
			bitmap.LoadBitmapA(IDB_BITMAP8);
			dcmemory.SelectObject(&bitmap);
			dc.StretchBlt(0 + 30 * temp.j, 0 + 30 * temp.i, 30, 30, &dcmemory, 0, 0, 48, 48, SRCCOPY);
			bitmap.Detach();
		}
		else snake1.power--;




		if (snake1.SnakeEatBean(bean.i, bean.j) == true)
		{
			if (bean.s == 0){
				PlaySound("e:\\大二上\\贪吃蛇\\音效\\1.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				snake1.n++;
				snake1.body[snake1.n - 1].i = temp.i;
				snake1.body[snake1.n - 1].j = temp.j;
			}
			else if (bean.s == 1){
				snake1.power = 15;
				PlaySound("e:\\大二上\\贪吃蛇\\音效\\2.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else if (bean.s == 2){
				PlaySound("e:\\大二上\\贪吃蛇\\音效\\3.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				if (snake2.n >= 2){
					snake1.power += 5;

					if(snake2.m_marks>0)snake2.m_marks--;
				}

			}
			//重新生成豆子
			unsigned int seed = time(NULL);
			srand(seed);
			do
			{
				bean.i = rand() % 21;
				bean.j = rand() % 31;
				bean.s = rand() % 3;
			} while (snake1.IsBeanInSnake(bean.i, bean.j) == true && snake2.IsBeanInSnake(bean.i, bean.j) == true);
			switch (bean.s){
			case 0:
				bitmap.LoadBitmapA(IDB_BITMAP4);
				break;
			case 1:
				bitmap.LoadBitmapA(IDB_BITMAP5);
				break;
			case 2:
				bitmap.LoadBitmapA(IDB_BITMAP6);
				break;
			}
			dcmemory.SelectObject(&bitmap);
			dc.StretchBlt(0 + 30 * bean.j, 0 + 30 * bean.i, 30, 30, &dcmemory, 0, 0, 48, 48, SRCCOPY);
			bitmap.Detach();
			//显示得分
			COLORREF clr = dc.SetTextColor(dc.GetBkColor());
			dc.TextOutA(980, 60, snake1.m_string);
			snake1.m_marks += 1;
			CString m1;
			m1.Format("%d", snake1.m_marks);
			snake1.m_string = "玩家1的得分是：" + m1;
			dc.SetTextColor(clr);
			dc.TextOutA(980, 20, snake1.m_string);
			CString m2;
			m2.Format("%d", snake2.m_marks);
			snake2.m_string = "玩家2的得分是：" + m2;
			dc.SetTextColor(clr);
			dc.TextOutA(980, 40, snake2.m_string);

		}

		if (snake2.SnakeEatBean(bean.i, bean.j) == true)
		{

			if (bean.s == 0){
				PlaySound("e:\\大二上\\贪吃蛇\\音效\\1.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				snake2.n++;
				snake2.body[snake2.n - 1].i = temp.i;
				snake2.body[snake2.n - 1].j = temp.j;
			}
			else if (bean.s == 1){
				snake2.power = 15;
				PlaySound("e:\\大二上\\贪吃蛇\\音效\\2.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			else if (bean.s == 2){
				PlaySound("e:\\大二上\\贪吃蛇\\音效\\3.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				if (snake1.n >= 2){
				    snake2.power += 5;
					if (snake1.m_marks>0)snake1.m_marks--;
				}
			}
			//重新生成豆子
			unsigned int seed = time(NULL);
			srand(seed);
			do
			{
				bean.i = rand() % 21;
				bean.j = rand() % 31;
				bean.s = rand() % 3;
			} while (snake1.IsBeanInSnake(bean.i, bean.j) == true && snake2.IsBeanInSnake(bean.i, bean.j) == true);

			switch (bean.s){
			case 0:
				bitmap.LoadBitmapA(IDB_BITMAP4);
				break;
			case 1:
				bitmap.LoadBitmapA(IDB_BITMAP5);
				break;
			case 2:
				bitmap.LoadBitmapA(IDB_BITMAP6);
				break;
			}
			dcmemory.SelectObject(&bitmap);
			dc.StretchBlt(0 + 30 * bean.j, 0 + 30 * bean.i, 30, 30, &dcmemory, 0, 0, 48, 48, SRCCOPY);
			bitmap.Detach();
			//显示得分
			COLORREF clr = dc.SetTextColor(dc.GetBkColor());
			dc.TextOutA(10, 620, snake2.m_string);
			snake2.m_marks += 1;
			CString m2;
			m2.Format("%d", snake2.m_marks);
			snake2.m_string = "玩家2的得分是：" + m2;
			dc.SetTextColor(clr);
			dc.TextOutA(980, 40, snake2.m_string);
			CString m1;
			m1.Format("%d", snake1.m_marks);
			snake1.m_string = "玩家1的得分是：" + m1;
			dc.SetTextColor(clr);
			dc.TextOutA(980, 20, snake1.m_string);
		}

		if (snake1.GameLose(snake2) == true || snake2.GameLose(snake1) == true)
		{
			m_start = false;
			PlaySound("e:\\大二上\\贪吃蛇\\音效\\I Still Believe In Love-Jenny Hyun.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			if (snake1.GameLose(snake2) == true && snake2.GameLose(snake1) == true){
				MessageBox("平局");
			}
			else
			{

				if (snake1.GameLose(snake2) == true){
					MessageBox("玩家2赢了");
				}
				if (snake2.GameLose(snake1) == true){
					MessageBox("玩家1赢了!");
				}
			}
	

		}


		//画蛇
		//画蛇1头

		bitmap.Detach();
		bitmap.LoadBitmapA(IDB_BITMAP2);
		dcmemory.SelectObject(&bitmap);
		dc.StretchBlt(0 + 30 * snake1.body[0].j, 0 + 30 * snake1.body[0].i, 30, 30, &dcmemory, 0, 0, 48, 48, SRCCOPY);
		bitmap.Detach();
		//画蛇1身
		if (k % 2 == 0){
			bitmap.LoadBitmapA(IDB_BITMAP3);
		}
		else bitmap.LoadBitmapA(IDB_BITMAP10);
		k++;
		dcmemory.SelectObject(&bitmap);
		for (int i = 1; i <= snake1.n; i++)
		{
			dc.StretchBlt(0 + 30 * snake1.body[i].j, 0 + 30 * snake1.body[i].i, 30, 30, &dcmemory, 0, 0, 48, 48, SRCCOPY);
		}

		bitmap.Detach();

		//画蛇2头
		bitmap.LoadBitmapA(IDB_BITMAP7);
		dcmemory.SelectObject(&bitmap);
		dc.StretchBlt(0 + 30 * snake2.body[0].j, 0 + 30 * snake2.body[0].i, 30, 30, &dcmemory, 0, 0, 48, 48, SRCCOPY);
		bitmap.Detach();
		//画蛇2身
		if (l % 2 == 0){
			bitmap.LoadBitmapA(IDB_BITMAP10);
		}
		else bitmap.LoadBitmapA(IDB_BITMAP3);
		l++;
		dcmemory.SelectObject(&bitmap);
		for (int i = 1; i <= snake2.n; i++)
		{
			dc.StretchBlt(0 + 30 * snake2.body[i].j, 0 + 30 * snake2.body[i].i, 30, 30, &dcmemory, 0, 0, 48, 48, SRCCOPY);
		}

		bitmap.Detach();

		if (snake1.Time == 0){
			MessageBox("时间到！");
			PlaySound("e:\\大二上\\贪吃蛇\\音效\\I Still Believe In Love-Jenny Hyun.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			if (snake1.m_marks > snake2.m_marks){
				MessageBox("玩家1获胜");
			}
			if (snake2.m_marks > snake1.m_marks){
				MessageBox("玩家2获胜");
			}
			if (snake2.m_marks == snake1.m_marks){
				MessageBox("平局");
			}

	
		}

	}
	CView::OnTimer(nIDEvent);
}


void CMyView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nChar == VK_UP&&snake2.direction != 3)
	{
		snake2.direction = 1;
	}
	if (nChar == VK_RIGHT&&snake2.direction != 4)
	{
		snake2.direction = 2;
	}
	if (nChar == VK_DOWN&&snake2.direction != 1)
	{
		snake2.direction = 3;
	}
	if (nChar == VK_LEFT&&snake2.direction != 2)
	{
		snake2.direction = 4;
	}                                        //蛇1的方向



	if (nChar == 'W'&&snake1.direction != 3)
	{
		snake1.direction = 1;
	}
	if (nChar == 'D'&&snake1.direction != 4)
	{
		snake1.direction = 2;
	}
	if (nChar == 'S'&&snake1.direction != 1)
	{
		snake1.direction = 3;
	}
	if (nChar == 'A'&&snake1.direction != 2)
	{
		snake1.direction = 4;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);



}