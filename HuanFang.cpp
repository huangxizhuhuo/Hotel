// HuanFang.cpp : implementation file
//

#include "stdafx.h"
#include "Hotel.h"
#include "HuanFang.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// HuanFang dialog


HuanFang::HuanFang(CWnd* pParent /*=NULL*/)
	: CDialog(HuanFang::IDD, pParent)
{
	//{{AFX_DATA_INIT(HuanFang)
	m_name = _T("");
	m_shouldpay = _T("");
	m_hadpay = _T("");
	m_zhekou = _T("");
	m_beizhu = _T("");
	m_roomtype = _T("");
	m_newcost = _T("");
	m_cost = _T("");
	m_changebeizhu = _T("");
	m_isclockroom = FALSE;
	m_intime = COleDateTime::GetCurrentTime();
	m_curtime = COleDateTime::GetCurrentTime();
	m_customerid = _T("");
	//}}AFX_DATA_INIT
}


void HuanFang::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(HuanFang)
	DDX_Control(pDX, IDC_COMBO2, m_changetotype);
	DDX_Control(pDX, IDC_COMBO3, m_changeroomid);
	DDX_Control(pDX, IDC_COMBO4, m_roomid);
	DDX_Text(pDX, IDC_EDIT11, m_name);
	DDX_Text(pDX, IDC_EDIT8, m_shouldpay);
	DDX_Text(pDX, IDC_EDIT10, m_hadpay);
	DDX_Text(pDX, IDC_EDIT12, m_zhekou);
	DDX_Text(pDX, IDC_EDIT13, m_beizhu);
	DDX_Text(pDX, IDC_EDIT5, m_roomtype);
	DDX_Text(pDX, IDC_EDIT15, m_newcost);
	DDX_Text(pDX, IDC_EDIT6, m_cost);
	DDX_Text(pDX, IDC_EDIT17, m_changebeizhu);
	DDX_Check(pDX, IDC_CHECK1, m_isclockroom);
	DDX_Text(pDX, IDC_EDIT9, m_intime);
	DDX_Text(pDX, IDC_EDIT16, m_curtime);
	DDX_Text(pDX, IDC_STATIC_LISTID, m_customerid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(HuanFang, CDialog)
	//{{AFX_MSG_MAP(HuanFang)
	ON_CBN_SELCHANGE(IDC_COMBO4, OnSelchangeRoomId)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeNewFangXing)
	ON_CBN_SELCHANGE(IDC_COMBO3, OnSelchangeNewRoomId)
	ON_BN_CLICKED(IDOK, OnChangeRoom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// HuanFang message handlers

BOOL HuanFang::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	_variant_t str;
	str="select * from 客房 where 客房状态='已住'";///所有已住房加入到旧房号ComboBox
	theApp.ADOExecute(theApp.m_pRecordset,str);

	while(!theApp.m_pRecordset->EndOfFile)
	{
		m_roomid.AddString((wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("房号"));
		theApp.m_pRecordset->MoveNext();
	}

//	theApp.m_pRecordset->MoveFirst();
	str="select * from 客房 where 客房状态='空'";////所有空房加入到新房号ComboBox
	theApp.ADOExecute(theApp.m_pRecordset,str);

	while(!theApp.m_pRecordset->EndOfFile)
	{
		m_changeroomid.AddString((wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("房号"));
		theApp.m_pRecordset->MoveNext();
	}

	str="select distinct 客房级别 from 客房";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	while(!theApp.m_pRecordset->EndOfFile)
	{
		m_changetotype.AddString((wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("客房级别"));
		theApp.m_pRecordset->MoveNext();
	}

	m_isclockroom=false;
	CString dengjiyuan=theApp.m_sCurrentUser;
	SetDlgItemText(IDC_STATIC_DENGJIYUAN,"登记员  "+dengjiyuan);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void HuanFang::OnSelchangeRoomId() 
{
	// TODO: Add your control notification handler code here

	_variant_t str;
	CString roomid;
	int i=m_roomid.GetCurSel();
	m_roomid.GetLBText(i,roomid);

	str="select * from 客房,住房 where 客房.房号='"+roomid+"'and 住房.现住房号='"+roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	CString str3=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("钟点房");

	if(str3=="Y")
	{
		m_isclockroom=true;
		UpdateData(false);
	}
	else
	{
		m_isclockroom=false;
		UpdateData(false);
	}

	_variant_t str1=theApp.m_pRecordset->GetCollect("客房级别");
	SetDlgItemText(IDC_EDIT5,(wchar_t*)(_bstr_t)str1);

	_variant_t str2=theApp.m_pRecordset->GetCollect("单价");
	SetDlgItemText(IDC_EDIT6,(wchar_t*)(_bstr_t)str2);

	

	CString str4=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("登记时间");
	SetDlgItemText(IDC_EDIT9,str4);	
	SetDlgItemText(IDC_STATIC_INTIME,"登记时间  "+str4);

	CString str5=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("客人账号");
	SetDlgItemText(IDC_STATIC_LISTID,str5);

	CString str6=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("姓名");
	SetDlgItemText(IDC_EDIT11,str6);

	CString str7=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("预付金额");
	SetDlgItemText(IDC_EDIT10,str7);

	UpdateData();
	if(m_isclockroom==false)//不是钟点房
	{
	COleDateTime curtime=COleDateTime::GetCurrentTime();	
	float dayoflive=curtime-m_intime;
	float deltaday(dayoflive-int(dayoflive));
	if(deltaday<=0.5)
		dayoflive=int(dayoflive)+0.5f;//算半天
	else
		dayoflive=int(dayoflive)+1.0f;//算一天	
	double realcost=theApp.m_pRecordset->GetCollect("实价");
	double costatlast=dayoflive*realcost;
	CString costatlaststr;
	costatlaststr.Format(_T("%.2f"),costatlast);
	SetDlgItemText(IDC_EDIT8,costatlaststr);

	CString day;
	day.Format(_T("%.1f"),dayoflive);
	CString beizhu="已住"+day+"天";
	SetDlgItemText(IDC_EDIT13,beizhu);

	}
	else
	{
	COleDateTime curtime=COleDateTime::GetCurrentTime();	
	float dayoflive=curtime-m_intime;
	float deltaday(dayoflive-int(dayoflive));
	float deltahour=deltaday*24;
	dayoflive=int(deltahour+0.5f);
	double realcost=theApp.m_pRecordset->GetCollect("实价");
	double costatlast=dayoflive*realcost;
	CString costatlaststr;
	costatlaststr.Format(_T("%.2f"),costatlast);
	SetDlgItemText(IDC_EDIT8,costatlaststr);
    
	CString day;
	day.Format(_T("%.1f"),dayoflive);
	CString beizhu="已住"+day+"小时";
	SetDlgItemText(IDC_EDIT13,beizhu);
	}

	//折扣
	float shijia=theApp.m_pRecordset->GetCollect("实价");
	float yuanjia=theApp.m_pRecordset->GetCollect("单价");
//	float zhekou=shijia/yuanjia;
	float zhekou=float(shijia)/float(yuanjia);
	CString zhekoustr;
	zhekoustr.Format(_T("%.2f"),zhekou);
	SetDlgItemText(IDC_EDIT12,zhekoustr);
	
//	double precost=theApp.m_pRecordset->GetCollect("预付金额");
//	CString str8=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("登记时间");
//	SetDlgItemText(IDC_EDIT9,(wchar_t*)(_bstr_t)str8);
//	UpdateData(FALSE);	
}

void HuanFang::OnSelchangeNewFangXing() 
{
	// TODO: Add your control notification handler code here

	_variant_t str;
	CString roomtype;
	int i=m_changetotype.GetCurSel();
	m_changetotype.GetLBText(i,roomtype);

	str="select * from 客房 where 客房.客房级别='"+roomtype+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	CString danjiastr=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("单价");
	SetDlgItemText(IDC_EDIT15,danjiastr);

	m_changeroomid.ResetContent();//删除组合框的列表框和编辑控件中的所有项 

	str="select * from 客房 where 客房.客房级别='"+roomtype+"' and 客房状态='空'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	while(!theApp.m_pRecordset->EndOfFile)
	{
		m_changeroomid.AddString((wchar_t*)(_bstr_t)(theApp.m_pRecordset->GetCollect("房号")));
		theApp.m_pRecordset->MoveNext();
	}
}

void HuanFang::OnSelchangeNewRoomId() 
{
	// TODO: Add your control notification handler code here

    _variant_t str;
	CString roomid;
	int i=m_changeroomid.GetCurSel();
	m_changeroomid.GetLBText(i,roomid);

	str="select * from 客房 where 房号='"+roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	_variant_t str1=theApp.m_pRecordset->GetCollect("客房级别");
	SetDlgItemText(IDC_COMBO2,(wchar_t*)(_bstr_t)str1);
	_variant_t str2=theApp.m_pRecordset->GetCollect("单价");
	SetDlgItemText(IDC_EDIT15,(wchar_t*)(_bstr_t)str2);
/*
	if(m_isclock)
	{
		float clockvalue=theApp.m_pRecordset->GetCollect("钟点房价");
		CString clockvaluestr;
       	clockvaluestr.Format("%.2f",clockvalue);
	    SetDlgItemText(IDC_COMBO6,clockvaluestr);
	}	
	*/
}

void HuanFang::OnChangeRoom() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	//入阶段账务表，修改原房(脏房)与今房(已住)的状态，更新住房表的现住房号，登记时间，实价以及钟点房项
    //对于换房后的实价，应是原折扣*今房价？？？？？？？？？？？？？？？？？
	_variant_t str;
	CString roomid;
	GetDlgItemText(IDC_COMBO4,roomid);
	CString intime=m_intime.Format(_T("%Y-%m-%d %H:%M:%S"));
	CString curtime=m_curtime.Format(_T("%Y-%m-%d %H:%M:%S"));
	CString newroom;
	GetDlgItemText(IDC_COMBO3,newroom);

	if(roomid==""||intime==""||curtime==""||newroom=="")
	{
		AfxMessageBox(_T("请输入完整的信息..."),MB_ICONINFORMATION);
		return;
	}

	if(MessageBox(_T("确定换房吗?"),_T("是否确定?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
	////应当判断如果时间间隔过短，不能换房，而应取消？？？？？？？？？？？

	str="insert into 阶段账务(客户账号,主客姓名,登记日期,阶段时刻,原住房,消费金额,现住房)\
		values('"+m_customerid+"','"+m_name+"','"+intime+"','"+curtime+"','"+roomid+"','"+m_shouldpay+"','"+newroom+"')";

	theApp.ADOExecute(theApp.m_pRecordset,str);

	str="update 客房 set 客房状态='脏房' where 房号='"+roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	str="update 客房 set 客房状态='已住' where 房号='"+newroom+"'";
    theApp.ADOExecute(theApp.m_pRecordset,str);

	CString isclock;
	m_isclockroom? isclock='Y': isclock='N';

	str="update 住房 set 现住房号='"+newroom+"',\
		                 登记时间='"+curtime+"',\
						 实价='"+m_newcost+"',\
						 钟点房='"+isclock+"' where 客人账号='"+m_customerid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	CDialog::OnOK();
	
}
