#if !defined(AFX_HUANFANG_H__27E595FA_A49A_4C05_8EF9_A723B0BA721C__INCLUDED_)
#define AFX_HUANFANG_H__27E595FA_A49A_4C05_8EF9_A723B0BA721C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HuanFang.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// HuanFang dialog

class HuanFang : public CDialog
{
// Construction
public:
	HuanFang(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(HuanFang)
	enum { IDD = IDD_CUSTOMCHANGEROOM };
	CComboBox	m_changetotype;
	CComboBox	m_changeroomid;
	CComboBox	m_roomid;
	CString	m_name;
	CString	m_shouldpay;
	CString	m_hadpay;
	CString	m_zhekou;
	CString	m_beizhu;
	CString	m_roomtype;
	CString	m_newcost;
	CString	m_cost;
	CString	m_changebeizhu;
	BOOL	m_isclockroom;
	COleDateTime	m_intime;
	COleDateTime	m_curtime;
	CString	m_customerid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(HuanFang)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(HuanFang)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeRoomId();
	afx_msg void OnSelchangeNewFangXing();
	afx_msg void OnSelchangeNewRoomId();
	afx_msg void OnChangeRoom();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HUANFANG_H__27E595FA_A49A_4C05_8EF9_A723B0BA721C__INCLUDED_)
