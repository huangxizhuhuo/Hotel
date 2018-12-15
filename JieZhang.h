#if !defined(AFX_JIEZHANG_H__D45C54C8_376A_40C2_85CB_ABE009C5CB16__INCLUDED_)
#define AFX_JIEZHANG_H__D45C54C8_376A_40C2_85CB_ABE009C5CB16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JieZhang.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// JieZhang dialog

class JieZhang : public CDialog
{
// Construction
public:
	JieZhang(CWnd* pParent = NULL);   // standard constructor

	int m_nIndex;

// Dialog Data
	//{{AFX_DATA(JieZhang)
	enum { IDD = IDD_CUSTOMJZH };
	CComboBox	m_paytype;
	CListCtrl	m_listzf;
	CString	m_id;
	CString	m_name;
	CString	m_roomid;
	CString	m_shouldpay;
	CString	m_payfirst;
	CString	m_paylast;
	CString	m_beizhu;
	CString	m_small;
	COleDateTime	m_curtime;
	CString	m_intime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(JieZhang)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(JieZhang)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListzf(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnSetfocusCostofall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JIEZHANG_H__D45C54C8_376A_40C2_85CB_ABE009C5CB16__INCLUDED_)
