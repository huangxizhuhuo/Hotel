// DengJi.cpp : implementation file
//

#include "stdafx.h"
#include "Hotel.h"
#include "DengJi.h"
//#include "Kewuzhx.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// DengJi dialog


DengJi::DengJi(CWnd* pParent /*=NULL*/)
	: CDialog(DengJi::IDD, pParent)
{
	//{{AFX_DATA_INIT(DengJi)
	m_name = _T("");
	m_borndate = 0;
	m_home = _T("");
	m_beizhu = _T("");
	m_isvip = FALSE;
	m_realcost = _T("");
	m_id = _T("");
	m_cardnumber = _T("");
	m_time = COleDateTime::GetCurrentTime();
	m_payfirst = _T("");
	m_isclock = FALSE;
	//}}AFX_DATA_INIT
}


void DengJi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DengJi)
	DDX_Control(pDX, IDC_COMBO8, m_paytype);
	DDX_Control(pDX, IDC_COMBO7, m_zhekou);
	DDX_Control(pDX, IDC_COMBO6, m_cost);
	DDX_Control(pDX, IDC_COMBO5, m_roomtype);
	DDX_Control(pDX, IDC_COMBO4, m_roomid);
	DDX_Control(pDX, IDC_COMBO3, m_country);
	DDX_Control(pDX, IDC_COMBO2, m_sex);
	DDX_Control(pDX, IDC_COMBO1, m_cardtype);
	DDX_Text(pDX, IDC_EDIT5, m_name);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_borndate);
	DDX_Text(pDX, IDC_EDIT8, m_home);
	DDX_Text(pDX, IDC_EDIT9, m_beizhu);
	DDX_Check(pDX, IDC_CHECK1, m_isvip);
	DDX_Text(pDX, IDC_EDIT6, m_realcost);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT3, m_cardnumber);
	DDX_Text(pDX, IDC_EDIT10, m_time);
	DDX_Text(pDX, IDC_EDIT2, m_payfirst);
	DDX_Check(pDX, IDC_CHECK2, m_isclock);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DengJi, CDialog)
	//{{AFX_MSG_MAP(DengJi)
	ON_CBN_EDITCHANGE(IDC_COMBO4, OnChangeRoomId)
	ON_CBN_SETFOCUS(IDC_COMBO4, OnSetfocusRoomId)
	ON_CBN_SELENDOK(IDC_COMBO4, OnSelendokRoomId)
	ON_CBN_SELCHANGE(IDC_COMBO4, OnSelchangeRoomId)
	ON_CBN_SELCHANGE(IDC_COMBO7, OnSelchangeZheKou)
	ON_BN_CLICKED(IDC_CHECK2, OnCheckZhong)
	ON_BN_DOUBLECLICKED(IDC_CHECK2, OnDoubleclickedClock)
	ON_CBN_SELCHANGE(IDC_COMBO5, OnSelchangeRoomType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DengJi message handlers

void DengJi::OnOK() 
{
	// TODO: Add extra validation here

	CString roomid,roomtype,cost;
    GetDlgItemText(IDC_COMBO4,roomid);
    GetDlgItemText(IDC_COMBO5,roomtype);
    GetDlgItemText(IDC_COMBO6,cost);
    if(roomid==""||roomtype==""||cost=="")
	{
        AfxMessageBox(_T("信息不完整..."),MB_ICONINFORMATION);
        return;
	}

	if(!theApp.IsZhuan)
	{
	UpdateData();
	_variant_t str;
	CString date,sex,cardtype,country;
	GetDlgItemText(IDC_DATETIMEPICKER1,date);
	GetDlgItemText(IDC_COMBO2,sex);
    GetDlgItemText(IDC_COMBO1,cardtype);
    GetDlgItemText(IDC_COMBO3,country);
	char isvip,isclock;
	m_isvip? isvip='Y' :isvip='N';
	m_isclock? isclock='Y' :isclock='N';
	if(m_name==""||m_id=="")
	{
		AfxMessageBox(_T("姓名不能为空!"),MB_ICONINFORMATION);
		return;
	}

	if(MessageBox(_T("确定登记吗?"),_T("是否确定?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
	if(!theApp.isnewroom)//如果不是开房,不能往客户信息表中写入重复的信息
	{
	str="insert into 客户信息(客人账号,姓名,证件类型,证件号码,性别,出生年月,国籍,IsVip,详细住址,备注)\
		values ("+m_id+",'"+m_name+"','"+cardtype+"','"+m_cardnumber+"',\
		'"+sex+"','"+date+"','"+country+"','"+isvip+"','"+m_home+"','"+m_beizhu+"')";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	}
//	theApp.m_pRecordset->Update();		
	CString roomid,roomtype,cost,zhekou,paytype;
	//m_time为只读!!!!!!!!!!!
	m_time.GetCurrentTime();
	CString time=m_time.Format(_T("%Y-%m-%d %H:%M:%S"));///???????????????????不能直接插入m_time
	GetDlgItemText(IDC_COMBO4,roomid);
    GetDlgItemText(IDC_COMBO5,roomtype);
    GetDlgItemText(IDC_COMBO6,cost);
	GetDlgItemText(IDC_COMBO7,zhekou);
	GetDlgItemText(IDC_COMBO8,paytype);
	str="insert into 住房(客人账号,姓名,现住房号,登记时间,预付金额,付费方式,实价,钟点房)\
		values ("+m_id+",'"+m_name+"','"+roomid+"','"+time+"',\
		'"+m_payfirst+"','"+paytype+"','"+m_realcost+"','"+isclock+"')";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	m_id="";
	m_name="";
	m_cardnumber="";
	m_home="";
	m_beizhu="";
	UpdateData(false);
	str="update 客房 set 客房状态='已住' where 房号='"+roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	AfxMessageBox(_T("成功登记.."),MB_ICONINFORMATION);	
	}

	else////如果是转入住
	{
	
	UpdateData();
	_variant_t str;
	CString date,sex,cardtype,country;
	GetDlgItemText(IDC_DATETIMEPICKER1,date);
	GetDlgItemText(IDC_COMBO2,sex);
    GetDlgItemText(IDC_COMBO1,cardtype);
    GetDlgItemText(IDC_COMBO3,country);
	char isvip,isclock;
	m_isvip? isvip='Y' :isvip='N';
	m_isclock? isclock='Y' :isclock='N';
	if(m_name==""||m_id=="")
	{
		AfxMessageBox(_T("姓名不能为空!"),MB_ICONINFORMATION);
		return;
	}
	if(MessageBox(_T("确定登记吗?"),_T("是否确定?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
	if(!theApp.isnewroom)//如果是加开房,不能往客户信息表中写入重复的信息
	{
	str="insert into 客户信息(客人账号,姓名,证件类型,证件号码,性别,出生年月,国籍,IsVip,详细住址,备注)\
		values ("+m_id+",'"+m_name+"','"+cardtype+"','"+m_cardnumber+"',\
		'"+sex+"','"+date+"','"+country+"','"+isvip+"','"+m_home+"','"+m_beizhu+"')";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	}		
	CString roomid,roomtype,cost,zhekou,paytype;
	//m_time为只读!!!!!!!!!!!
	m_time.GetCurrentTime();
	CString time=m_time.Format(_T("%Y-%m-%d %H:%M:%S"));///???????????????????不能直接插入m_time
	GetDlgItemText(IDC_COMBO4,roomid);
    GetDlgItemText(IDC_COMBO5,roomtype);
    GetDlgItemText(IDC_COMBO6,cost);
	GetDlgItemText(IDC_COMBO7,zhekou);
	GetDlgItemText(IDC_COMBO8,paytype);
	str="insert into 住房(客人账号,姓名,现住房号,登记时间,预付金额,付费方式,实价,钟点房)\
		values ("+m_id+",'"+m_name+"','"+roomid+"','"+time+"',\
		'"+m_payfirst+"','"+paytype+"','"+m_realcost+"','"+isclock+"')";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	m_id="";
	m_name="";
	m_cardnumber="";
	m_home="";
	m_beizhu="";
	UpdateData(false);
	str="update 客房 set 客房状态='已住' where 房号='"+roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	MessageBox(_T("成功转入住..."),_T("操作成功!"),MB_ICONINFORMATION);	
	///////置预订表项为无效
	str="update 预订 set 状态='无效' where 保留房间='"+roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	}
	CDialog::OnOK();
}

BOOL DengJi::OnInitDialog() 
{
	InitCommonControls();
	CDialog::OnInitDialog();
//	theApp.IsZhuan=false;
	
	// TODO: Add extra initialization here
	_variant_t str;
	//初始化房间号roomid
	str="select * from 客房 where 客房状态='空'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	while(!theApp.m_pRecordset->EndOfFile)
	{
		m_roomid.AddString((wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("房号"));
		theApp.m_pRecordset->MoveNext();
	}

	str="select distinct 客房级别 from 客房";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	//初始化房间类型roomtype
	theApp.m_pRecordset->MoveFirst();
	while(!theApp.m_pRecordset->EndOfFile)
	{
		m_roomtype.AddString((wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("客房级别"));
		theApp.m_pRecordset->MoveNext();
	}
	//初始化房间单价cost
	str="select distinct 单价 from 客房";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	while(!theApp.m_pRecordset->EndOfFile)
	{
		m_cost.AddString((wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("单价"));
		theApp.m_pRecordset->MoveNext();
	}
	//初始化证件类型cardtype
	m_cardtype.AddString(_T("身份证"));
	m_cardtype.AddString(_T("学生证"));
	m_cardtype.AddString(_T("军官证"));
	m_cardtype.AddString(_T("驾驶证"));
	m_cardtype.AddString(_T("护照"));
	//初始化性别sex
	m_sex.AddString(_T("男"));
	m_sex.AddString(_T("女"));
	//初始化国籍country
	m_country.AddString(_T("中华人民共和国"));
	m_country.AddString(_T("美国"));
	m_country.AddString(_T("法国"));
	m_country.AddString(_T("英国"));
	m_country.AddString(_T("德国"));
	m_country.AddString(_T("日本"));
	m_country.AddString(_T("俄罗斯"));
	//初始化优惠折扣zhekou
	m_zhekou.AddString(_T("不打折"));
	m_zhekou.AddString(_T("95%100"));
	m_zhekou.AddString(_T("90%100"));
	m_zhekou.AddString(_T("85%100"));
	m_zhekou.AddString(_T("80%100"));
	m_zhekou.AddString(_T("75%100"));
	m_zhekou.AddString(_T("70%100"));
	m_zhekou.AddString(_T("65%100"));
	m_zhekou.AddString(_T("60%100"));
	m_zhekou.AddString(_T("55%100"));
	m_zhekou.AddString(_T("50%100"));
	m_zhekou.AddString(_T("免费"));
	//初始化付费方式paytype
	m_paytype.AddString(_T("现金"));
	m_paytype.AddString(_T("支票"));
	m_paytype.AddString(_T("信用卡"));

//	m_intime.GetCurrentTime();
//	m_intime.Format(_T("%Y%m%d"));//???????????
	m_isclock=false;
	CString caozuoyuan=theApp.m_sCurrentUser;
	SetDlgItemText(IDC_STATIC_Operator,caozuoyuan);


	//初始化客户账号
	if(theApp.isnewroom==false)
	{	
	CString IdOfCustomer;
	CTime time;
	time=CTime::GetCurrentTime();
	IdOfCustomer=time.Format("%Y%m%d%H%M%S");
	SetDlgItemText(IDC_EDIT1,IdOfCustomer);
	}




//转入住时初始化
	if(theApp.IsZhuan)
	{
	str="select * from 预订 where 预订人='"+m_name+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	CString cardtype=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("证件类型");
	SetDlgItemText(IDC_COMBO1,cardtype);
//	CString sex=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("证件类型");
	SetDlgItemText(IDC_COMBO2,_T("男"));
	SetDlgItemText(IDC_COMBO3,_T("中华人民共和国"));
	CString room=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("保留房间");
	SetDlgItemText(IDC_COMBO4,room);
	}
	//加开房时初始化
	if(theApp.isnewroom)
	{
		str="select * from 客户信息 where 客人账号='"+m_id+"'";
		theApp.ADOExecute(theApp.m_pRecordset,str);
		CString isvip=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("IsVip");
		if(isvip=="Y")
		{
			m_isvip=true;
			UpdateData(FALSE);
		}
		else
		{
			m_isvip=false;
			UpdateData(FALSE);
		}
		CString cardtype=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("证件类型");
	    SetDlgItemText(IDC_COMBO1,cardtype);
		CString country=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("国籍");
    	
		CString sex=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("性别");
	    SetDlgItemText(IDC_COMBO3,country);
		SetDlgItemText(IDC_COMBO2,sex);
		CString cardid=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("证件号码");
		SetDlgItemText(IDC_EDIT3,cardid);
		CString zhuzhi=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("详细住址");
		SetDlgItemText(IDC_EDIT8,zhuzhi);
		CString beizhu=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("备注");
        SetDlgItemText(IDC_EDIT9,beizhu);
	}
	 //   CString room=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("保留房间");
	  //  SetDlgItemText(IDC_COMBO4,room);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}







void DengJi::OnChangeRoomId() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL DengJi::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	theApp.IsZhuan=false;
	
	return CDialog::DestroyWindow();
}

void DengJi::OnSetfocusRoomId() 
{
	// TODO: Add your control notification handler code here

	
}

void DengJi::OnSelendokRoomId() 
{
	// TODO: Add your control notification handler code here

	
}

void DengJi::OnSelchangeRoomId() 
{
	// TODO: Add your control notification handler code here

	_variant_t str;
	CString roomid;
	int i=m_roomid.GetCurSel();
	m_roomid.GetLBText(i,roomid);

	str="select * from 客房 where 房号='"+roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	_variant_t str1=theApp.m_pRecordset->GetCollect("客房级别");
	//str
	SetDlgItemText(IDC_COMBO5,(wchar_t*)(_bstr_t)str1);
	_variant_t str2=theApp.m_pRecordset->GetCollect("单价");
	SetDlgItemText(IDC_COMBO6,(wchar_t*)(_bstr_t)str2);

	if(m_isclock)
	{
		float clockvalue=theApp.m_pRecordset->GetCollect("钟点房价");
		CString clockvaluestr;
       	clockvaluestr.Format(_T("%.2f"),clockvalue);
	    SetDlgItemText(IDC_COMBO6,clockvaluestr);
	}	

	
}

void DengJi::OnSelchangeZheKou() 
{
	// TODO: Add your control notification handler code here
	int i=m_zhekou.GetCurSel();
	CString zhekou;
//	m_zhekou.GetLBText(i,zhekou);
	CString cost,roomid;
	GetDlgItemText(IDC_COMBO6,cost);
	GetDlgItemText(IDC_COMBO4,roomid);
	if(cost=="")
		return;

	_variant_t str;
	str="select * from 客房 where 房号='"+roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	if(!m_isclock)
	{
	double danjia=theApp.m_pRecordset->GetCollect("单价");//浮点型原价

	CString danjia1;//字符串原价
	double realcost;//浮点型折后价

	switch(i)
	{
		
		
	case 1:		
		realcost=danjia*0.5;
	    danjia1.Format(_T("%.2f"),realcost);//浮点到字符串
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 2:
    	realcost=danjia*0.55;
		danjia1.Format(_T("%.2f"),realcost);//浮点到字符串
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 3:
		realcost=danjia*0.6;
		danjia1.Format(_T("%.2f"),realcost);//浮点到字符串
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 4:
		realcost=danjia*0.65;
		danjia1.Format(_T("%.2f"),realcost);//浮点到字符串
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 5:

		realcost=danjia*0.7;
		danjia1.Format(_T("%.2f"),realcost);//浮点到字符串
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 6:

		realcost=danjia*0.75;
		danjia1.Format(_T("%.2f"),realcost);//浮点到字符串
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 7:

		realcost=danjia*0.8;
		danjia1.Format(_T("%.2f"),realcost);//浮点到字符串
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 8:
		realcost=danjia*0.85;
		danjia1.Format(_T("%.2f"),realcost);//浮点到字符串
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 9:
		realcost=danjia*0.9;
		danjia1.Format(_T("%.2f"),realcost);//浮点到字符串
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 10:
		realcost=danjia*0.95;
		danjia1.Format(_T("%.2f"),realcost);//浮点到字符串
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 11:
		realcost=danjia*0.00;
		danjia1.Format(_T("%.2f"),realcost);//浮点到字符串
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 12:
		realcost=danjia*1.00;
		danjia1.Format(_T("%.2f"),realcost);//浮点到字符串
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	}
	}
	
}

void DengJi::OnCheckZhong() 
{
	// TODO: Add your control notification handler code here
	//UpdateData();
	m_isclock=!m_isclock;
	CString roomid;
	GetDlgItemText(IDC_COMBO4,roomid);
	if(roomid=="")
		return;
	_variant_t str;
	str="select * from 客房 where 房号='"+roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	float clockvalue=theApp.m_pRecordset->GetCollect("钟点房价");
	CString clockvaluestr;
	clockvaluestr.Format(_T("%.2f"),clockvalue);
	SetDlgItemText(IDC_COMBO6,clockvaluestr);
    if(m_isclock==false)
	{
		float value=theApp.m_pRecordset->GetCollect("单价");
		CString valuestr;
	    valuestr.Format(_T("%.1f"),value);
	    SetDlgItemText(IDC_COMBO6,valuestr);
		CString valueofclockroomstr;
		GetDlgItemText(IDC_COMBO6,valueofclockroomstr);
		SetDlgItemText(IDC_EDIT6,valueofclockroomstr);
	}
	else
	{
		CString valueofclockroom;
		GetDlgItemText(IDC_COMBO6,valueofclockroom);
		SetDlgItemText(IDC_COMBO7,_T(""));
		SetDlgItemText(IDC_EDIT6,valueofclockroom);
	}


	
	
}

void DengJi::OnDoubleclickedClock() 
{
	// TODO: Add your control notification handler code here
	
}

void DengJi::OnSelchangeRoomType() 
{
	// TODO: Add your control notification handler code here

	_variant_t str;
	CString roomtype;
	int i=m_roomtype.GetCurSel();
	m_roomtype.GetLBText(i,roomtype);


	m_roomid.ResetContent();//删除组合框的列表框和编辑控件中的所有项 

	str="select * from 客房 where 客房.客房级别='"+roomtype+"' and 客房状态='空'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	while(!theApp.m_pRecordset->EndOfFile)
	{
		m_roomid.AddString((wchar_t*)(_bstr_t)(theApp.m_pRecordset->GetCollect("房号")));
		theApp.m_pRecordset->MoveNext();
	}

	m_cost.ResetContent();
//	CString danjia=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("单价");
//	SetDlgItemText(IDC_COMBO6,danjia);	
}

void DengJi::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnOK();
}
