#if !defined(AFX_LOCK_H__6F25EFC9_13C3_42BB_BB50_BA55F5AE965B__INCLUDED_)
#define AFX_LOCK_H__6F25EFC9_13C3_42BB_BB50_BA55F5AE965B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Lock.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Lock dialog

class Lock : public CDialog
{
// Construction
public:
	Lock(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Lock)
	enum { IDD = IDD_Lock };
	CString	m_curpasswd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Lock)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Lock)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCK_H__6F25EFC9_13C3_42BB_BB50_BA55F5AE965B__INCLUDED_)
