#if !defined(AFX_DENGJI_H__11FFD3CC_EA00_4273_BDC9_B2D88B1ABA10__INCLUDED_)
#define AFX_DENGJI_H__11FFD3CC_EA00_4273_BDC9_B2D88B1ABA10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DengJi.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DengJi dialog

class DengJi : public CDialog
{
// Construction
public:
	DengJi(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DengJi)
	enum { IDD = IDD_CUSTOMDJ };
	CComboBox	m_paytype;
	CComboBox	m_zhekou;
	CComboBox	m_cost;
	CComboBox	m_roomtype;
	CComboBox	m_roomid;
	CComboBox	m_country;
	CComboBox	m_sex;
	CComboBox	m_cardtype;
	CString	m_name;
	CTime	m_borndate;
	CString	m_home;
	CString	m_beizhu;
	BOOL	m_isvip;
	CString	m_realcost;
	CString	m_id;
	CString	m_cardnumber;
	COleDateTime	m_time;
	CString	m_payfirst;
	BOOL	m_isclock;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DengJi)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DengJi)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeRoomId();
	afx_msg void OnSetfocusRoomId();
	afx_msg void OnSelendokRoomId();
	afx_msg void OnSelchangeRoomId();
	afx_msg void OnSelchangeZheKou();
	afx_msg void OnCheckZhong();
	afx_msg void OnDoubleclickedClock();
	afx_msg void OnSelchangeRoomType();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DENGJI_H__11FFD3CC_EA00_4273_BDC9_B2D88B1ABA10__INCLUDED_)
