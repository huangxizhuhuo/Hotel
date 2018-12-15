#if !defined(AFX_MODIFY_H__46938765_A100_4266_8242_AA941CF971CF__INCLUDED_)
#define AFX_MODIFY_H__46938765_A100_4266_8242_AA941CF971CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Modify.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Modify dialog

class Modify : public CDialog
{
// Construction
public:
	Modify(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Modify)
	enum { IDD = IDD_ModifyPasswd };
	CString	m_inputagain;
	CString	m_newpasswd;
	CString	m_oldpasswd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Modify)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Modify)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFY_H__46938765_A100_4266_8242_AA941CF971CF__INCLUDED_)
