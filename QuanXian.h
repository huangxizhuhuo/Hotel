#if !defined(AFX_QUANXIAN_H__05D4663C_5CF7_4F4A_A09C_67EF86F5BF3C__INCLUDED_)
#define AFX_QUANXIAN_H__05D4663C_5CF7_4F4A_A09C_67EF86F5BF3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QuanXian.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// QuanXian dialog

class QuanXian : public CDialog
{
// Construction
public:
	QuanXian(CWnd* pParent = NULL);   // standard constructor
	void OnRefresh();

// Dialog Data
	//{{AFX_DATA(QuanXian)
	enum { IDD = IDD_QUANXIAN };
	CComboBox	m_job;
	CListCtrl	m_listqx;
	CString	m_id;
	CString	m_beizhu;
	BOOL	m_iscustom;
	BOOL	m_isselect;
	BOOL	m_istable;
	BOOL	m_isfoundation;
	BOOL	m_issystem;
	int m_nIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(QuanXian)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(QuanXian)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListqx(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAddId();
	afx_msg void OnQuXiao();
	afx_msg void OnBaoCun();
	afx_msg void OnShanChu();
	afx_msg void OnClickListqx(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUANXIAN_H__05D4663C_5CF7_4F4A_A09C_67EF86F5BF3C__INCLUDED_)
