// HotelView.cpp : implementation of the CHotelView class
//

#include "stdafx.h"
#include "Hotel.h"

#include "HotelDoc.h"
#include "HotelView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHotelView

IMPLEMENT_DYNCREATE(CHotelView, CView)

BEGIN_MESSAGE_MAP(CHotelView, CView)
	//{{AFX_MSG_MAP(CHotelView)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHotelView construction/destruction

CHotelView::CHotelView()
{
	// TODO: add construction code here

}

CHotelView::~CHotelView()
{
}

BOOL CHotelView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHotelView drawing

void CHotelView::OnDraw(CDC* pDC)
{
	CHotelDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CHotelView diagnostics

#ifdef _DEBUG
void CHotelView::AssertValid() const
{
	CView::AssertValid();
}

void CHotelView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHotelDoc* CHotelView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHotelDoc)));
	return (CHotelDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHotelView message handlers

void CHotelView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	HBITMAP   hBmp;
    CString   path="res\\¾Æµê×¡ËÞ.bmp";
    int   x,y;
    x=1024;
    y=700;
    hBmp=(HBITMAP)LoadImage(AfxGetInstanceHandle(),path,IMAGE_BITMAP,x,y,LR_LOADFROMFILE);
    CDC   tmpdc;
    tmpdc.CreateCompatibleDC(&dc);
    CBitmap   bmp;
    CBitmap   *pOldBmp=tmpdc.SelectObject(bmp.FromHandle(hBmp));
    dc.BitBlt(0,0,x,y,&tmpdc,0,0,SRCCOPY);
    tmpdc.SelectObject(pOldBmp);

	
	// TODO: Add your message handler code here
	
	// Do not call CView::OnPaint() for painting messages
}
