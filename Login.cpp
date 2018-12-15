// Login.cpp : implementation file
//

#include "stdafx.h"
#include "Hotel.h"
#include "Login.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Login dialog


Login::Login(CWnd* pParent /*=NULL*/)
	: CDialog(Login::IDD, pParent)
{
	//{{AFX_DATA_INIT(Login)
	m_UserId = _T("");
	m_PassWd = _T("");
	//}}AFX_DATA_INIT
}


void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Login)
	DDX_Text(pDX, IDC_UserId, m_UserId);
	DDX_Text(pDX, IDC_PassWd, m_PassWd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Login, CDialog)
	//{{AFX_MSG_MAP(Login)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Login message handlers



void Login::OnCancel() 
{
	// TODO: Add extra cleanup here
//	theApp.ExitInstance();
	
	CDialog::OnCancel();
}

void Login::OnOK() 
{
	// TODO: Add extra validation here

	_variant_t str;
	UpdateData();
	str="select * from 用户权限 where UserId='"+m_UserId+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	if(theApp.m_pRecordset->EndOfFile)
	{
		AfxMessageBox(_T("用户名不正确..."));
		m_UserId="";
		UpdateData(false);
		return;
	}
	str="select * from 用户权限 where UserId='"+m_UserId+"' and PassWd='"+m_PassWd+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	if(theApp.m_pRecordset->EndOfFile)
	{
		AfxMessageBox(_T("密码错误..."));
		m_PassWd="";
		UpdateData(false);
		return;
	}
	theApp.systemstr=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("系统管理");
	theApp.foundationdatastr=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("基础资料");
	theApp.tablestr=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("报表中心");
	theApp.selectstr=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("信息查询");
	theApp.customstr=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("客房系统");

	theApp.m_sCurrentUser=(char *)(_bstr_t)theApp.m_pRecordset->GetCollect("UserId");
//	MessageBox("用户"'"+theApp.m_sCurrentUser+"'"登录");
	theApp.IsLogin=true;
	



	
	CDialog::OnOK();
}

BOOL Login::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here


/*	LOGFONT LogFont;
	GetFont()->GetLogFont(&LogFont);
	LogFont.lfHeight+=LogFont.lfHeight/2;
	LogFont.lfWidth+=LogFont.lfWidth/2;
	m_font.CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_STATIC_LoginText)->SetFont(&m_font);*/


	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
