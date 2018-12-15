// HotelView.h : interface of the CHotelView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOTELVIEW_H__02E1079D_B3B0_4562_BA6B_156009CAFDA4__INCLUDED_)
#define AFX_HOTELVIEW_H__02E1079D_B3B0_4562_BA6B_156009CAFDA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHotelView : public CView
{
protected: // create from serialization only
	CHotelView();
	DECLARE_DYNCREATE(CHotelView)

// Attributes
public:
	CHotelDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHotelView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHotelView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHotelView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HotelView.cpp
inline CHotelDoc* CHotelView::GetDocument()
   { return (CHotelDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOTELVIEW_H__02E1079D_B3B0_4562_BA6B_156009CAFDA4__INCLUDED_)
