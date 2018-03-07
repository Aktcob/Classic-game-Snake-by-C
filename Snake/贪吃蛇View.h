// 贪吃蛇View.h : CMyView 类的接口
//

#include "Snake.h"
#include "Ge.h"
#include "Bean.h"

#pragma once


class CMyView : public CView
{
protected: // 仅从序列化创建
	CMyView();
	DECLARE_DYNCREATE(CMyView)

	// 属性
public:
	CMyDoc* GetDocument() const;

	// 操作
public:
	int k = 0;    //动态效果判定；
	int l = 0;
	// 重写
public:
	
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 实现
public:
	virtual ~CMyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
private:
	bool m_start;
	bool m_pause;

	// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStart();
	afx_msg void OnPause();
private:
	CSnake snake1, snake2;

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	CBean bean;


};

#ifndef _DEBUG  // 贪吃蛇View.cpp 中的调试版本
inline CMyDoc* CMyView::GetDocument() const
{
	return reinterpret_cast<CMyDoc*>(m_pDocument);
}
#endif



