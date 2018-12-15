#if !defined(AFX_JIASHOU_H__AEFC45FE_A374_40D5_87F9_5E484EC63450__INCLUDED_)
#define AFX_JIASHOU_H__AEFC45FE_A374_40D5_87F9_5E484EC63450__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JiaShou.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// JiaShou dialog

class JiaShou : public CDialog
{
// Construction
public:
	JiaShou(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(JiaShou)
	enum { IDD = IDD_JIASHOU };
	CComboBox	m_paytype;
	CComboBox	m_type;
	CString	m_name;
	BOOL	m_isvip;
	CString	m_shouldpay;
	CString	m_hadpay;
	CString	m_roomid;
	CString	m_beizhu;
	CString	m_jiashou;
	COleDateTime	m_curtime;
	CString	m_shuoming;
	CString	m_operatorname;
	CString	m_customerid;
	CString	m_intime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(JiaShou)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(JiaShou)
	virtual BOOL OnInitDialog();
	afx_msg void OnShouKuan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JIASHOU_H__AEFC45FE_A374_40D5_87F9_5E484EC63450__INCLUDED_)
