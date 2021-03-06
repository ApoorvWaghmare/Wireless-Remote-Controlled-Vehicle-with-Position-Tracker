
// ChristopherDoc.h : interface of the CChristopherDoc class
//


#pragma once

#include "TCPClient.h"
#include "Coordinates.h"

class CChristopherDoc : public CDocument
{
protected: // create from serialization only
	CChristopherDoc();
	DECLARE_DYNCREATE(CChristopherDoc)

// Attributes
public:

// Operations
private:
	TCPClient m_client;
	bool m_connectionStatus = false;
	Coordinates m_chrisCoordinates;

public:
	void connectToPi();
	TCPClient getClient();
	bool returnConnectionStatus();
	void sendMotionMessage(int motionMessage);
	void recieveNewCoordinates();
	double getXCoordinate();
	double getYCoordinate();
	void endConnection();
	
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CChristopherDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
