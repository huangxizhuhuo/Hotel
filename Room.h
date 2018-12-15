#if !defined(AFX_ROOM_H__014B1873_50AB_4D5C_94A1_E2B2273CFCDF__INCLUDED_)
#define AFX_ROOM_H__014B1873_50AB_4D5C_94A1_E2B2273CFCDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Room.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Room dialog

class Room : public CDialog
{
// Construction
public:
	Room(CWnd* pParent = NULL);   // standard constructor
	int m_nIndex;

// Dialog Data
	//{{AFX_DATA(Room)
	enum { IDD = IDD_RoomSet };
	CComboBox	m_weizhi;
	CComboBox	m_roomtype;
	CListCtrl	m_listkf;
	CString	m_roomid;
	CString	m_floor;
	CString	m_tezheng;
	CString	m_costofoneday;
	CString	m_costofanhour;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Room)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Room)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnModifyRoom();
	afx_msg void OnAddRoom();
	afx_msg void OnDeleteRoom();
	afx_msg void OnRefresh();
	afx_msg void OnQuXiao();
	afx_msg void OnGuanBi();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROOM_H__014B1873_50AB_4D5C_94A1_E2B2273CFCDF__INCLUDED_)
