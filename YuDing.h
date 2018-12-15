#if !defined(AFX_YUDING_H__D6DB088E_4636_43B6_B47A_68F5A323BFE4__INCLUDED_)
#define AFX_YUDING_H__D6DB088E_4636_43B6_B47A_68F5A323BFE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// YuDing.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// YuDing dialog

class YuDing : public CDialog
{
// Construction
public:
	YuDing(CWnd* pParent = NULL);   // standard constructor
	int m_nIndex;


// Dialog Data
	//{{AFX_DATA(YuDing)
	enum { IDD = IDD_CUSTOMYD };
	CComboBox	m_reservedroom;
	CListCtrl	m_listyd;
	CComboBox	m_roomtype;
	CComboBox	m_cardtype;
	CComboBox	m_customtype;
	CString	m_name;
	CString	m_cardnumber;
	CString	m_phonenumber;
	CString	m_number;
	CString	m_shuoming;
	COleDateTime	m_timeofmakelist;
	COleDateTime	m_preintime;
	COleDateTime	m_preleavetime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(YuDing)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(YuDing)
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnNew();
	afx_msg void OnSave();
	afx_msg void OnQuXiao();
	afx_msg void OnZuoFei();
	afx_msg void OnClickListYd(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShanChu();
	afx_msg void OnZhuanRuZhu();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YUDING_H__D6DB088E_4636_43B6_B47A_68F5A323BFE4__INCLUDED_)
