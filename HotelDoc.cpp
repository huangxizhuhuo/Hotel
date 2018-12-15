// HotelDoc.cpp : implementation of the CHotelDoc class
//

#include "stdafx.h"
#include "Hotel.h"

#include "HotelDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHotelDoc

IMPLEMENT_DYNCREATE(CHotelDoc, CDocument)

BEGIN_MESSAGE_MAP(CHotelDoc, CDocument)
	//{{AFX_MSG_MAP(CHotelDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHotelDoc construction/destruction

CHotelDoc::CHotelDoc()
{
	// TODO: add one-time construction code here

}

CHotelDoc::~CHotelDoc()
{
}

BOOL CHotelDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHotelDoc serialization

void CHotelDoc::Serialize(CArchive& ar)
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

/////////////////////////////////////////////////////////////////////////////
// CHotelDoc diagnostics

#ifdef _DEBUG
void CHotelDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHotelDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHotelDoc commands
