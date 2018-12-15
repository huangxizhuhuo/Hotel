// Hotel.h : main header file for the HOTEL application
//

#if !defined(AFX_HOTEL_H__466D26BE_909A_4F99_9375_26DA95F259C8__INCLUDED_)
#define AFX_HOTEL_H__466D26BE_909A_4F99_9375_26DA95F259C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHotelApp:
// See Hotel.cpp for the implementation of this class
//

class CHotelApp : public CWinApp
{
public:
	CHotelApp();
	bool ADOExecute(_RecordsetPtr &ADOSet,_variant_t &strSQL);
	CString m_sCurrentUser;//指示系统当前用户
	int m_iLoginCount;
	_RecordsetPtr m_pRecordset;//智能指针纪录集对象
	_ConnectionPtr m_pConnection;//智能指针
	int IsLogin;
	bool IsZhuan;//是否转入住
	CString fangjianhaoma;
	bool isnewroom;//是否新开房
	CString systemstr;
	CString selectstr;
	CString tablestr;
	CString customstr;
	CString foundationdatastr;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHotelApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CHotelApp)
	afx_msg void OnAppAbout();
	afx_msg void OnAppExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CHotelApp theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOTEL_H__466D26BE_909A_4F99_9375_26DA95F259C8__INCLUDED_)
