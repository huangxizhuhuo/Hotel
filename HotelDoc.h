// HotelDoc.h : interface of the CHotelDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOTELDOC_H__9344C727_28F5_4A0B_9D45_AD4DDC2C44DE__INCLUDED_)
#define AFX_HOTELDOC_H__9344C727_28F5_4A0B_9D45_AD4DDC2C44DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHotelDoc : public CDocument
{
protected: // create from serialization only
	CHotelDoc();
	DECLARE_DYNCREATE(CHotelDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHotelDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHotelDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHotelDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOTELDOC_H__9344C727_28F5_4A0B_9D45_AD4DDC2C44DE__INCLUDED_)
