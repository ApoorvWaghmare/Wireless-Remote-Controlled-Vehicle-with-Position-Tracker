
// ChristopherView.cpp : implementation of the CChristopherView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Christopher.h"
#endif

#include "ChristopherDoc.h"
#include "ChristopherView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChristopherView

IMPLEMENT_DYNCREATE(CChristopherView, CView)

BEGIN_MESSAGE_MAP(CChristopherView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CChristopherView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CChristopherView construction/destruction

CChristopherView::CChristopherView()
{
	// TODO: add construction code here

}

CChristopherView::~CChristopherView()
{
}

BOOL CChristopherView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CChristopherView drawing

void CChristopherView::OnDraw(CDC* pDC)
{
	CChristopherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	HDC hdc = pDC->GetSafeHdc();

	//printing coordinates
	char xCoordinate[100];
	char yCoordinate[100];

	CString xName = CString(_T("Christopher X Coordinate = "));
	CString yName = CString(_T("Christopher Y Coordinate = "));
	
	sprintf_s(xCoordinate, "%8.3lf", m_chrisX);
	CString x(xCoordinate);

	sprintf_s(yCoordinate, "%8.3lf", m_chrisY);
	CString y(yCoordinate);

	TextOut(hdc, 1075, 20, xName, xName.GetAllocLength());
	TextOut(hdc, 1250, 20, x, x.GetAllocLength());
	TextOut(hdc, 1075, 60, yName, yName.GetAllocLength());
	TextOut(hdc, 1250, 60, y, y.GetAllocLength());

	//path tracer

	int Xv = m_xStart + (10 * m_chrisX);
	int Yv = m_yStart - (10 * m_chrisY);

	CPen line(PS_SOLID, 7, BLACK_PEN);
	pDC->SelectObject(&line);

	pDC->MoveTo(m_xStart, m_yStart);
	pDC->LineTo(Xv, Yv);

	Xv = m_xStart;
	Yv = m_yStart;
}


// CChristopherView printing


void CChristopherView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CChristopherView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CChristopherView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CChristopherView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CChristopherView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CChristopherView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CChristopherView diagnostics

#ifdef _DEBUG
void CChristopherView::AssertValid() const
{
	CView::AssertValid();
}

void CChristopherView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChristopherDoc* CChristopherView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChristopherDoc)));
	return (CChristopherDoc*)m_pDocument;
}
#endif //_DEBUG


// CChristopherView message handlers

void CChristopherView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == VK_RETURN && GetDocument()->returnConnectionStatus() == false)
	{
		GetDocument()->connectToPi();
	}

	if (GetDocument()->returnConnectionStatus() == true)
	{
		// Chris movement instructions
		if (nChar == VK_UP)
		{
			GetDocument()->sendMotionMessage(moveForward);
			m_currentDirection = moveForward;
		}
		else if (nChar == VK_DOWN)
		{
			GetDocument()->sendMotionMessage(moveBackward);
			m_currentDirection = moveBackward;
		}
		else if (nChar == VK_RIGHT)
		{
			GetDocument()->sendMotionMessage(turnRight);
			m_currentDirection = turnRight;
		}
		else if (nChar == VK_LEFT)
		{
			GetDocument()->sendMotionMessage(turnLeft);
			m_currentDirection = turnLeft;
		}
		else if (nChar == VK_SPACE)
		{
			GetDocument()->sendMotionMessage(stop);
			m_currentDirection = stop;
		}
		else if (nChar == VK_SHIFT)
		{
			//KillTimer(1);
			GetDocument()->endConnection();
		}

		if (!m_timerOn && (nChar == VK_UP || nChar == VK_DOWN || nChar == VK_RIGHT ||
		nChar == VK_LEFT))
		{
			SetTimer(1, m_timerLength, NULL);
		}
	}
	else
		return;

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CChristopherView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	GetDocument()->recieveNewCoordinates();

	m_chrisX = GetDocument()->getXCoordinate();
	m_chrisY = GetDocument()->getYCoordinate();

	Invalidate();

	GetDocument()->sendMotionMessage(m_currentDirection);

	CView::OnTimer(nIDEvent);
}