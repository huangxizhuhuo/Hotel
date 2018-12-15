// Lock.cpp : implementation file
//

#include "stdafx.h"
#include "Hotel.h"
#include "Lock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Lock dialog


Lock::Lock(CWnd* pParent /*=NULL*/)
	: CDialog(Lock::IDD, pParent)
{
	//{{AFX_DATA_INIT(Lock)
	m_curpasswd = _T("");
	//}}AFX_DATA_INIT
}


void Lock::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Lock)
	DDX_Text(pDX, IDC_EDIT1, m_curpasswd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Lock, CDialog)
	//{{AFX_MSG_MAP(Lock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Lock message handlers

void Lock::OnOK() 
{
	// TODO: Add extra validation here

	_variant_t str;
	CString curuser=theApp.m_sCurrentUser;
	str="select PassWd from 用户权限 where UserId='"+curuser+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	CString passwd=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("PassWd");
	UpdateData(TRUE);
	if(passwd!=m_curpasswd)
	{
		
		m_curpasswd="";
		UpdateData(FALSE);
		return;
	}
	
	
	CDialog::OnOK();
}

void Lock::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
	exit(0);
	
//	CDialog::OnCancel();
}
