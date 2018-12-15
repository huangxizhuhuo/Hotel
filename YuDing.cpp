// YuDing.cpp : implementation file
//

#include "stdafx.h"
#include "Hotel.h"
#include "YuDing.h"

#include "DengJi.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// YuDing dialog


YuDing::YuDing(CWnd* pParent /*=NULL*/)
	: CDialog(YuDing::IDD, pParent)
{
	//{{AFX_DATA_INIT(YuDing)
	m_name = _T("");
	m_cardnumber = _T("");
	m_phonenumber = _T("");
	m_number = _T("");
	m_shuoming = _T("");
	m_timeofmakelist = COleDateTime::GetCurrentTime();
	m_preintime = COleDateTime::GetCurrentTime();
	m_preleavetime = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void YuDing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(YuDing)
	DDX_Control(pDX, IDC_COMBO4, m_reservedroom);
	DDX_Control(pDX, IDC_LIST1, m_listyd);
	DDX_Control(pDX, IDC_COMBO3, m_roomtype);
	DDX_Control(pDX, IDC_COMBO2, m_cardtype);
	DDX_Control(pDX, IDC_COMBO1, m_customtype);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_cardnumber);
	DDX_Text(pDX, IDC_EDIT3, m_phonenumber);
	DDX_Text(pDX, IDC_EDIT5, m_number);
	DDX_Text(pDX, IDC_EDIT6, m_shuoming);
	DDX_Text(pDX, IDC_EDIT7, m_timeofmakelist);
	DDX_Text(pDX, IDC_EDIT8, m_preintime);
	DDX_Text(pDX, IDC_EDIT9, m_preleavetime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(YuDing, CDialog)
	//{{AFX_MSG_MAP(YuDing)
	ON_BN_CLICKED(IDC_BUTTON7, OnClose)
	ON_BN_CLICKED(IDC_BUTTON4, OnNew)
	ON_BN_CLICKED(IDC_BUTTON5, OnSave)
	ON_BN_CLICKED(IDC_BUTTON6, OnQuXiao)
	ON_BN_CLICKED(IDC_BUTTON1, OnZuoFei)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickListYd)
	ON_BN_CLICKED(IDC_BUTTON3, OnShanChu)
	ON_BN_CLICKED(IDC_BUTTON2, OnZhuanRuZhu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// YuDing message handlers

void YuDing::OnClose() 
{
	// TODO: Add your control notification handler code here
	theApp.IsZhuan=false;
	DestroyWindow();

//	delete this;

	
}

BOOL YuDing::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_nIndex=-1;//初始化!!!!!!!!!!!!!
	CString DengJiYuan=theApp.m_sCurrentUser;
	SetDlgItemText(IDC_STATIC_Operator1,DengJiYuan);
	
	// TODO: Add extra initialization here

	m_customtype.AddString(_T("散客"));
	m_customtype.AddString(_T("团队"));
	m_customtype.AddString(_T("内部"));

	//初始化证件类型cardtype
	m_cardtype.AddString(_T("身份证"));
	m_cardtype.AddString(_T("学生证"));
	m_cardtype.AddString(_T("军官证"));
	m_cardtype.AddString(_T("驾驶证"));
	m_cardtype.AddString(_T("护照"));

	m_roomtype.AddString(_T("标准单人房"));
	m_roomtype.AddString(_T("标准双人房"));
	m_roomtype.AddString(_T("豪华单人房"));
	m_roomtype.AddString(_T("豪华双人房"));
	m_roomtype.AddString(_T("高级套房"));

	_variant_t str1;
	//初始化房间号roomid
	str1="select * from 客房 where 客房状态='空'";
	theApp.ADOExecute(theApp.m_pRecordset,str1);

	while(!theApp.m_pRecordset->EndOfFile)
	{
		m_reservedroom.AddString((wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("房号"));
		theApp.m_pRecordset->MoveNext();
	}

	m_listyd.SetBkColor(RGB(177,151,240));
	m_listyd.SetTextColor(RGB(0,0,0));
	m_listyd.SetTextBkColor(RGB(177,151,240));
	m_listyd.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);

	int nWidth=80;
	m_listyd.InsertColumn(0,_T("制单时间"),LVCFMT_LEFT,120);
	m_listyd.InsertColumn(1,_T("预订人"),LVCFMT_LEFT,60);
	m_listyd.InsertColumn(2,_T("证件类型"),LVCFMT_LEFT,80);
	m_listyd.InsertColumn(3,_T("证件号码"),LVCFMT_LEFT,80);
	m_listyd.InsertColumn(4,_T("预订入店时间"),LVCFMT_LEFT,120);
	m_listyd.InsertColumn(5,_T("联系电话"),LVCFMT_LEFT,nWidth);
	m_listyd.InsertColumn(6,_T("预订房型"),LVCFMT_LEFT,nWidth);
	m_listyd.InsertColumn(7,_T("数量"),LVCFMT_LEFT,60);
	m_listyd.InsertColumn(8,_T("保留房间"),LVCFMT_LEFT,80);
		
	_variant_t Holder;
	_variant_t strQuery;
	strQuery="select * from 预订 where 状态='有效'";//仅显示有效的订单!!!!!
	theApp.ADOExecute(theApp.m_pRecordset,strQuery);
    int iCount=theApp.m_pRecordset->GetRecordCount();
	if(0==iCount)
		return FALSE;
	CString str;
	theApp.m_pRecordset->MoveFirst();

	for(int i=0;i<iCount;i++)
//	if(theApp.m_pRecordset!=EndOfFile)
	{
		Holder=theApp.m_pRecordset->GetCollect("制单时间");
    	str=(Holder.vt==VT_NULL)?"":(char *)(_bstr_t)Holder;
    	m_listyd.InsertItem(i,str);

		Holder=theApp.m_pRecordset->GetCollect("预订人");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listyd.SetItemText(i,1,str);

    	Holder=theApp.m_pRecordset->GetCollect("证件类型");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listyd.SetItemText(i,2,str);

		Holder=theApp.m_pRecordset->GetCollect("证件号码");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listyd.SetItemText(i,3,str);

        Holder=theApp.m_pRecordset->GetCollect("预订入店时间");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listyd.SetItemText(i,4,str);

        Holder=theApp.m_pRecordset->GetCollect("联系电话");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listyd.SetItemText(i,5,str);

		Holder=theApp.m_pRecordset->GetCollect("预订房型");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listyd.SetItemText(i,6,str);

		Holder=theApp.m_pRecordset->GetCollect("数量");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listyd.SetItemText(i,7,str);

		Holder=theApp.m_pRecordset->GetCollect("保留房间");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listyd.SetItemText(i,8,str);


		theApp.m_pRecordset->MoveNext();
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void YuDing::OnNew() 
{
	// TODO: Add your control notification handler code here

//	m_customtype="散客";
//	m_cardtype="身份证";
//	m_roomtype="标准单人间";
//	CTime curtime;
//	CTime time=curtime.GetCurrentTime();

	SetDlgItemText(IDC_COMBO1,_T("散客"));
	SetDlgItemText(IDC_COMBO2,_T("身份证"));
	SetDlgItemText(IDC_COMBO3,_T("标准单人房"));
	m_timeofmakelist.GetCurrentTime();
	m_timeofmakelist.Format(_T("%Y-%m-%d %H:%M:%S"));
	CString roomtype;
	GetDlgItemText(IDC_COMBO3,roomtype);

//	CTime now=CTime::GetCurrentTime(); 
//	CString strNowTime;
//  strNowTime=now.Format(_T("%Y年%m月%d日%H时%M分%S秒"));	
	m_number="1";
	UpdateData(FALSE);
	
}

void YuDing::OnSave() 
{
	// TODO: Add your control notification handler code here

	_variant_t str;

	CString timeofmakelist,customtype,cardtype,roomtype,preintime,preleavetime,reservedroom;
//	GetDlgItemText(IDC_DATETIMEPICKER1,timeofmakelist);
	GetDlgItemText(IDC_COMBO1,customtype);
	GetDlgItemText(IDC_COMBO2,cardtype);
	GetDlgItemText(IDC_COMBO3,roomtype);
//  GetDlgItemText(IDC_DATETIMEPICKER2,preintime);
//	GetDlgItemText(IDC_DATETIMEPICKER3,preleavetime);
	GetDlgItemText(IDC_COMBO4,reservedroom);
	UpdateData();

	if(m_name==""||m_cardnumber=="")
	{
		AfxMessageBox(_T("预订人或证件号不能为空..."),MB_ICONINFORMATION);
		return;
	}

	if(m_preintime>m_preleavetime)
	{
		AfxMessageBox(_T("时间错误.."),MB_ICONINFORMATION);
		return;
	}

	if(MessageBox(_T("确定保存吗?"),_T("是否确定?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
	timeofmakelist=m_timeofmakelist.Format(_T("%Y-%m-%d %H:%M:%S"));
	preleavetime=m_preleavetime.Format(_T("%Y-%m-%d %H:%M:%S"));
	preintime=m_preintime.Format(_T("%Y-%m-%d %H:%M:%S"));

	str="insert into 预订(制单时间,预订人,客人类型,证件类型,证件号码,预订入店时间,预订离店时间,联系电话,预订房型,数量,保留房间)\
		values ('"+timeofmakelist+"','"+m_name+"','"+customtype+"','"+cardtype+"','"+m_cardnumber+"','"+preintime+"',\
		'"+preleavetime+"','"+m_phonenumber+"','"+roomtype+"','"+m_number+"','"+reservedroom+"')";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	str="update 客房 set 客房状态='保留' where 房号='"+reservedroom+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	AfxMessageBox(_T("成功预订.."),MB_ICONINFORMATION);


	//清空数据
	m_name = _T("");
	m_cardnumber = _T("");
	m_phonenumber = _T("");
	m_number = _T("");
	m_timeofmakelist=COleDateTime::GetCurrentTime();
	m_preintime=COleDateTime::GetCurrentTime();
	m_preleavetime=COleDateTime::GetCurrentTime();
	m_shuoming = _T("");
	UpdateData(FALSE);
}

void YuDing::OnQuXiao() 
{
	// TODO: Add your control notification handler code here

	m_name = _T("");
	m_cardnumber = _T("");
	m_phonenumber = _T("");
	m_number = _T("");
	m_timeofmakelist = COleDateTime::GetCurrentTime();
	m_preintime = COleDateTime::GetCurrentTime();
	m_preleavetime = COleDateTime::GetCurrentTime();
	m_shuoming = _T("");
	UpdateData(FALSE);

	SetDlgItemText(IDC_COMBO1,_T(""));
	SetDlgItemText(IDC_COMBO2,_T(""));
	SetDlgItemText(IDC_COMBO3,_T(""));
	
}

void YuDing::OnZuoFei() 
{
	// TODO: Add your control notification handler code here

	m_listyd.SetFocus();
	if (m_nIndex == -1)	  //如果没有选择就返回
	{
		MessageBox(_T("请选择左边列表中一项再操作!"),_T("提示"),MB_ICONINFORMATION);
		return;  
	}

	CString name;
	name= m_listyd.GetItemText(m_nIndex,1);
	if(MessageBox(_T("确定吗?将使该预订单作废..."),_T("是否确定?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
	
	_variant_t str;
	str="update 预订 set 状态='无效' where 预订人='"+name+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	//同时应将房态从保留置为空!!!!!!!!!!!!!!!!!!!!!!
	CString reservedroom;
	GetDlgItemText(IDC_COMBO4,reservedroom);
	str="update 客房 set 客房状态='空' where 房号='"+reservedroom+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	
}



void YuDing::OnClickListYd(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	
	POSITION pos = m_listyd.GetFirstSelectedItemPosition();
	m_nIndex = m_listyd.GetNextSelectedItem(pos);  // 得到项目索引
	
	*pResult = 0;
}

void YuDing::OnShanChu() 
{
	// TODO: Add your control notification handler code here

	m_listyd.SetFocus();
	if (m_nIndex == -1)	  //如果没有选择就返回
	{
		MessageBox(_T("请选择左边列表中一项再操作!"),_T("提示"),MB_ICONINFORMATION);
		return;  
	}

	CString name;
	name= m_listyd.GetItemText(m_nIndex,1);
	if(MessageBox(_T("确定吗?将使该预订单永久删除..."),_T("是否确定?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
	
	_variant_t str;
	str="delete from 预订 where 预订人='"+name+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	//同时应将房态从保留置为空!!!!!!!!!!!!!!!!!!!!!!
	CString reservedroom;
	GetDlgItemText(IDC_COMBO4,reservedroom);
	str="update 客房 set 客房状态='空' where 房号='"+reservedroom+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	
}

void YuDing::OnZhuanRuZhu() 
{
	// TODO: Add your control notification handler code here
	theApp.IsZhuan=true;

	m_listyd.SetFocus();
	if (m_nIndex == -1)	  //如果没有选择就返回
	{
		MessageBox(_T("请选择左边列表中一项再操作!"),_T("提示"),MB_ICONINFORMATION);
		return;  
	}
	CString roomid=m_listyd.GetItemText(m_nIndex,8);

	//置保留房间为空!!!!!!!!!!!!!!!!!!!!!!!!!!转入住登记如果点了取消
	if(MessageBox(_T("确定预订客户将转入住吗?点击确定将改变该保留房态"),_T("是否确定?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
	///置保留房为空
	_variant_t str;
	str="update 客房 set 客房状态='空' where 房号='"+roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	DengJi dlg;
	CString name,cardnumber;
	name= m_listyd.GetItemText(m_nIndex,1);
	cardnumber=m_listyd.GetItemText(m_nIndex,3);
	dlg.m_name=name;
	dlg.m_cardnumber=cardnumber;	
	UpdateData(FALSE);
	dlg.DoModal();
	
}
