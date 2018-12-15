#if !defined(AFX_KEWUZHX_H__07F65E07_8E3E_4A46_BA51_D8B63F5991F8__INCLUDED_)
#define AFX_KEWUZHX_H__07F65E07_8E3E_4A46_BA51_D8B63F5991F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Kewuzhx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Kewuzhx dialog

class Kewuzhx : public CDialog
{
// Construction
public:
	Kewuzhx(CWnd* pParent = NULL);   // standard constructor
//	bool isnewroom;
	bool ishuanyuan;
	int m_nIndex;
	void OnRefresh();

// Dialog Data
	//{{AFX_DATA(Kewuzhx)
	enum { IDD = IDD_CUSTOMCENTER };
	CListCtrl	m_listft;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Kewuzhx)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Kewuzhx)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonDJ();
	afx_msg void OnButtonJZH();
	afx_msg void OnButtonRefresh();
	afx_msg void OnRclickListFt(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeRoom();
	afx_msg void OnAddNew();
	afx_msg void OnSearchCustomer();
	afx_msg void OnClickListFangTai(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnYUFu();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEWUZHX_H__07F65E07_8E3E_4A46_BA51_D8B63F5991F8__INCLUDED_)
