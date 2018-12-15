// Modify.cpp : implementation file
//

#include "stdafx.h"
#include "Hotel.h"
#include "Modify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Modify dialog


Modify::Modify(CWnd* pParent /*=NULL*/)
	: CDialog(Modify::IDD, pParent)
{
	//{{AFX_DATA_INIT(Modify)
	m_inputagain = _T("");
	m_newpasswd = _T("");
	m_oldpasswd = _T("");
	//}}AFX_DATA_INIT
}


void Modify::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Modify)
	DDX_Text(pDX, IDC_InputAgain, m_inputagain);
	DDX_Text(pDX, IDC_NewPasswd, m_newpasswd);
	DDX_Text(pDX, IDC_OldPasswd, m_oldpasswd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Modify, CDialog)
	//{{AFX_MSG_MAP(Modify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Modify message handlers

void Modify::OnOK() 
{
	// TODO: Add extra validation here
//	MessageBox("");


	UpdateData();
	CString strSql;
	strSql.Format(_T("select * from 用户权限 where UserId='%s'"),theApp.m_sCurrentUser);


	theApp.ADOExecute(theApp.m_pRecordset,(_variant_t)strSql);

	CString s=(char *)(_bstr_t)theApp.m_pRecordset->GetCollect("PassWd");


	if(s!=m_oldpasswd)
	{
		MessageBox(_T("旧密码不正确.."));
		m_oldpasswd.Empty();
		m_newpasswd.Empty();
		m_inputagain.Empty();
		UpdateData(FALSE);
	}
	else
	{
		if(m_newpasswd!=m_inputagain)
		{
			MessageBox(_T("两次输入新密码不一致.."));
			m_oldpasswd.Empty();
		    m_newpasswd.Empty();
		    m_inputagain.Empty();
			UpdateData(FALSE);
		//	UpdateData(FALSE);
		}
		else
		{
			//strSql.Format("delete from 用户权限 where UserId='%s'",theApp.m_sCurrentUser);
			CString curuser=theApp.m_sCurrentUser;
			strSql.Format("update 用户权限 set PassWd='"+m_newpasswd+"' where UserId='"+curuser+"'");
			//strSql.Format("insert into 用户权限 values(\'%s\',\'%s\'",theApp.m_sCurrentUser,m_newpasswd);
			theApp.ADOExecute(theApp.m_pRecordset,(_variant_t)strSql);
			MessageBox(_T("修改密码成功!"));
		}
	}


	
	CDialog::OnOK();
}
