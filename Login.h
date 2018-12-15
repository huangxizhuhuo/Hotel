#if !defined(AFX_LOGIN_H__EBA4C7E6_1EEB_4963_B498_524682D6C670__INCLUDED_)
#define AFX_LOGIN_H__EBA4C7E6_1EEB_4963_B498_524682D6C670__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Login.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Login dialog

class Login : public CDialog
{
// Construction
public:
	Login(CWnd* pParent = NULL);   // standard constructor
	CFont m_font;

// Dialog Data
	//{{AFX_DATA(Login)
	enum { IDD = IDD_Login };
	CString	m_UserId;
	CString	m_PassWd;
//	afx_msg BOOL OnLogin();
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Login)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Login)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGIN_H__EBA4C7E6_1EEB_4963_B498_524682D6C670__INCLUDED_)
