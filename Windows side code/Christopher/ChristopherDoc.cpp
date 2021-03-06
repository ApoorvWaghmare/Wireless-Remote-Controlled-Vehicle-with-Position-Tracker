
// ChristopherDoc.cpp : implementation of the CChristopherDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Christopher.h"
#endif

#include "ChristopherDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChristopherDoc

IMPLEMENT_DYNCREATE(CChristopherDoc, CDocument)

BEGIN_MESSAGE_MAP(CChristopherDoc, CDocument)
END_MESSAGE_MAP()


// CChristopherDoc construction/destruction

CChristopherDoc::CChristopherDoc()
{
}

CChristopherDoc::~CChristopherDoc()
{
}

BOOL CChristopherDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CChristopherDoc serialization

void CChristopherDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CChristopherDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CChristopherDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CChristopherDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CChristopherDoc diagnostics

#ifdef _DEBUG
void CChristopherDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CChristopherDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// My functions

TCPClient CChristopherDoc::getClient()
{
	return m_client;
}

void CChristopherDoc::connectToPi()
{
	TCPClient::TCPConnectionStatus update = m_client.connectToPi();
	if (update == TCPClient::WSA_DATA_STARTUP_FAIL)
		AfxMessageBox(_T("WSA data stratUp fail"));
	else if (update == TCPClient::GET_ADD_INFO_FAIL)
		AfxMessageBox(_T("Get address info fail"));
	else if (update == TCPClient::SOCKET_FAIL)
		AfxMessageBox(_T("Socket fail"));
	else if (update == TCPClient::SERVER_CONNECTION_FAIL)
		AfxMessageBox(_T("Server connection fail"));
	else if (update == TCPClient::INITIAL_DATA_SEND_FAIL)
		AfxMessageBox(_T("Initial data sent fail"));
	else if (update == TCPClient::CONNECTION_SUCCESSFUL)
	{
		AfxMessageBox(_T("Connection with Chris successful"));
		m_connectionStatus = true;
	}
}

void CChristopherDoc::endConnection()
{
	if (m_connectionStatus == true)
	{
		m_client.endConnection();
		AfxMessageBox(_T("Connection with Chris ended"));
	}
}

bool CChristopherDoc::returnConnectionStatus()
{
	return m_connectionStatus;
}

void CChristopherDoc::sendMotionMessage(int motionMessage)
{
	if (m_connectionStatus == true)
	{
		m_client.sendData(motionMessage);
	}
	else
		return;
}

void CChristopherDoc::recieveNewCoordinates()
{
	double xCoordinate = m_client.recieveData();
	m_chrisCoordinates.setCurrentX(xCoordinate);

	double yCoordinate = m_client.recieveData();
	m_chrisCoordinates.setCurrentY(yCoordinate);
}

double CChristopherDoc::getXCoordinate()
{
	return m_chrisCoordinates.getCurrentXCoordinate();
}

double CChristopherDoc::getYCoordinate()
{
	return m_chrisCoordinates.getCurrentYCoordinate();
}

// CChristopherDoc commands
