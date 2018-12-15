// JiaShou.cpp : implementation file
//

#include "stdafx.h"
#include "Hotel.h"
#include "JiaShou.h"
#include ".\jiashou.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// JiaShou dialog


JiaShou::JiaShou(CWnd* pParent /*=NULL*/)
	: CDialog(JiaShou::IDD, pParent)
{
	//{{AFX_DATA_INIT(JiaShou)
	m_name = _T("");
	m_isvip = FALSE;
	m_shouldpay = _T("");
	m_hadpay = _T("");
	m_roomid = _T("");
	m_beizhu = _T("");
	m_jiashou = _T("");
	m_curtime = COleDateTime::GetCurrentTime();
	m_shuoming = _T("");
	m_operatorname = _T("");
	m_customerid = _T("");
	m_intime = _T("");
	//}}AFX_DATA_INIT
}


void JiaShou::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(JiaShou)
	DDX_Control(pDX, IDC_COMBO2, m_paytype);
	DDX_Control(pDX, IDC_COMBO3, m_type);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Check(pDX, IDC_CHECK1, m_isvip);
	DDX_Text(pDX, IDC_EDIT3, m_shouldpay);
	DDX_Text(pDX, IDC_EDIT4, m_hadpay);
	DDX_Text(pDX, IDC_EDIT6, m_roomid);
	DDX_Text(pDX, IDC_EDIT5, m_beizhu);
	DDX_Text(pDX, IDC_EDIT8, m_jiashou);
	DDX_Text(pDX, IDC_EDIT9, m_curtime);
	DDX_Text(pDX, IDC_EDIT10, m_shuoming);
	DDX_Text(pDX, IDC_EDIT11, m_operatorname);
	DDX_Text(pDX, IDC_STATIC_CUSTOMERID, m_customerid);
	DDX_Text(pDX, IDC_STATIC_INTIME, m_intime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(JiaShou, CDialog)
	//{{AFX_MSG_MAP(JiaShou)
	ON_BN_CLICKED(IDOK, OnShouKuan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// JiaShou message handlers

BOOL JiaShou::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_variant_t str;
	UpdateData();
	str="select * from 客户信息 where 客人账号='"+m_customerid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	CString vip;//输出到CHECK_VIP
	vip=(char *)(_bstr_t)theApp.m_pRecordset->GetCollect("IsVip");
	if(vip=="Y")
	{
		m_isvip=true;
		m_operatorname=theApp.m_sCurrentUser;
		UpdateData(FALSE);
	}
	else
	{
		m_isvip=false;
		m_operatorname=theApp.m_sCurrentUser;
		UpdateData(FALSE);
	}


	// TODO: Add extra initialization here
	CString curuser=theApp.m_sCurrentUser;
	SetDlgItemText(IDC_STATIC_Operator,"登记员 "+curuser);
	
//	str="select * from 住房 where 现住房号='"+m_roomid+"'";
//	theApp.ADOExecute(theApp.m_pRecordset,str);


	str="select * from 住房 where 客人账号='"+m_customerid+"' and 现住房号='"+m_roomid+"'";//只有账号和房号才能决定一次消费
	theApp.ADOExecute(theApp.m_pRecordset,str);
	double realcost=theApp.m_pRecordset->GetCollect("实价");	
	float dayoflive=m_curtime-theApp.m_pRecordset->GetCollect("登记时间");//须定义为浮点型
	CString intimestr;////输出到STATIC_INTIME
    COleDateTime intime=theApp.m_pRecordset->GetCollect("登记时间");
	intimestr=intime.Format(_T("%Y-%m-%d %H:%M:%S"));
	SetDlgItemText(IDC_STATIC_INTIME,"登记时间 "+intimestr);
	CString hadpay=(char *)(_bstr_t)theApp.m_pRecordset->GetCollect("预付金额");
	SetDlgItemText(IDC_EDIT4,hadpay);



	CString day;
	float deltaday(dayoflive-int(dayoflive));
	CString isclockroom=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("钟点房");
	if(isclockroom=="N")////==VS=
	{
	if(deltaday<=0.5)
		dayoflive=int(dayoflive)+0.5;//算半天
	else
		dayoflive=int(dayoflive)+1;//算一天

	double costatleast=dayoflive*realcost;////////////////////////
	double precost=theApp.m_pRecordset->GetCollect("预付金额");
	////查询阶段账务表，若客户换过房，则应将其中账务累加至此处的应付账款
	str="select * from 阶段账务 where 客户账号='"+m_customerid+"' and 现住房='"+m_roomid+"'";///换房前与换房后两房合计
	theApp.ADOExecute(theApp.m_pRecordset,str);
	int iCount=theApp.m_pRecordset->GetRecordCount();////////////////////
//	if(iCount==0)
//		return;
	double oldpay(0.00);
	if(!theApp.m_pRecordset->EndOfFile)///////////////////扫描纪录集
	{
		oldpay=theApp.m_pRecordset->GetCollect("消费金额");
	    costatleast+=oldpay;
		theApp.m_pRecordset->MoveNext();
	}
	double shouldpayatlast=costatleast-precost;
	CString costofall;
	costofall.Format(_T("%.2f"),costatleast);
	SetDlgItemText(IDC_EDIT3,costofall);//总价显示到应付账款	
	CString shouldpaystr;
	shouldpaystr.Format(_T("%.2f"),shouldpayatlast);
	SetDlgItemText(IDC_EDIT8,shouldpaystr);
	}

	else
	{
		float deltahour=int(deltaday*24+0.5);		
		float cost=deltahour*realcost;
		double precost=theApp.m_pRecordset->GetCollect("预付金额");
		double shouldpayatlast=cost-precost;
	    
		CString costofall;
	    costofall.Format(_T("%.2f"),cost);
		SetDlgItemText(IDC_EDIT3,costofall);//总价显示到应付账款
		
		CString shouldpaystr;
    	shouldpaystr.Format(_T("%.2f"),shouldpayatlast);
	    SetDlgItemText(IDC_EDIT8,shouldpaystr);
	}		

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void JiaShou::OnShouKuan() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(m_name==""||m_shouldpay==""||m_hadpay==""||m_roomid==""||m_jiashou==""||m_operatorname=="")
	{
		AfxMessageBox(_T("请输入完整的信息..."),MB_ICONINFORMATION);
		return;
	}
	if(MessageBox(_T("确定已收(付)款吗?"),_T("是否确定?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
	_variant_t str;
	//不另设一表记录收款信息,仅更新住房表的预付金
	CString newprepaystr;
	float hadpay =(float)_wtof(m_hadpay.GetBuffer());
	float jiashou=(float)_wtof(m_jiashou.GetBuffer());
	float newprepay=hadpay+jiashou;
	newprepaystr.Format(_T("%.2f"),newprepay);


	str="update 住房 set 预付金额='"+newprepaystr+"' where 客人账号='"+m_customerid+"' and 现住房号='"+m_roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);	

	AfxMessageBox(_T("收款成功..."),MB_ICONINFORMATION);
	CDialog::OnOK();
}

