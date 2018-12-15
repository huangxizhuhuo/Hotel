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
	CString m_sCurrentUser;//ָʾϵͳ��ǰ�û�
	int m_iLoginCount;
	_RecordsetPtr m_pRecordset;//����ָ���¼������
	_ConnectionPtr m_pConnection;//����ָ��
	int IsLogin;
	bool IsZhuan;//�Ƿ�ת��ס
	CString fangjianhaoma;
	bool isnewroom;//�Ƿ��¿���
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
