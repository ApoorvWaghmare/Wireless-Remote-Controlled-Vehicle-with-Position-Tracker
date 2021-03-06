
// ChristopherView.h : interface of the CChristopherView class
//

#pragma once

#include <vector>

using namespace std;

class CChristopherView : public CView
{
protected: // create from serialization only
	CChristopherView();
	DECLARE_DYNCREATE(CChristopherView)

// Attributes
public:
	CChristopherDoc* GetDocument() const;

// Operations
public:
	enum { moveForward = 1, moveBackward, turnRight, turnLeft, stop };
private:
	int m_xStart = 660;
	int m_yStart = 340;
	bool m_timerOn = false;
	double m_chrisX = 0;
	double m_chrisY = 0;
	int m_currentDirection = 0;
	int m_timerLength = 100;

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CChristopherView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // debug version in ChristopherView.cpp
inline CChristopherDoc* CChristopherView::GetDocument() const
   { return reinterpret_cast<CChristopherDoc*>(m_pDocument); }
#endif

