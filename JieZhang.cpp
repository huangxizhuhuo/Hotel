// JieZhang.cpp : implementation file
//

#include "stdafx.h"
#include "Hotel.h"
#include "JieZhang.h"
#include "DengJi.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// JieZhang dialog


JieZhang::JieZhang(CWnd* pParent /*=NULL*/)
	: CDialog(JieZhang::IDD, pParent)
{
	//{{AFX_DATA_INIT(JieZhang)
	m_id = _T("");
	m_name = _T("");
	m_roomid = _T("");
	m_shouldpay = _T("");
	m_payfirst = _T("");
	m_paylast = _T("");
	m_beizhu = _T("");
	m_small = _T("");
	m_curtime = COleDateTime::GetCurrentTime();
	m_intime = _T("");
	//}}AFX_DATA_INIT
}


void JieZhang::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(JieZhang)
	DDX_Control(pDX, IDC_COMBO2, m_paytype);
	DDX_Control(pDX, IDC_LISTZF, m_listzf);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT4, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_roomid);
	DDX_Text(pDX, IDC_EDIT5, m_shouldpay);
	DDX_Text(pDX, IDC_EDIT7, m_payfirst);
	DDX_Text(pDX, IDC_EDIT6, m_paylast);
	DDX_Text(pDX, IDC_EDIT8, m_beizhu);
	DDX_Text(pDX, IDC_EDIT2, m_small);
	DDX_Text(pDX, IDC_EDIT9, m_curtime);
	DDX_Text(pDX, IDC_EDIT10, m_intime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(JieZhang, CDialog)
	//{{AFX_MSG_MAP(JieZhang)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTZF, OnDblclkListzf)
	ON_EN_SETFOCUS(IDC_EDIT5, OnSetfocusCostofall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// JieZhang message handlers

BOOL JieZhang::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_paytype.AddString(_T("现金"));
	m_paytype.AddString(_T("支票"));
	m_paytype.AddString(_T("签单"));

	CString DengJiYuan=theApp.m_sCurrentUser;
	SetDlgItemText(IDC_STATIC_Operator2,DengJiYuan);

	m_listzf.SetBkColor(RGB(177,151,240));
	m_listzf.SetTextColor(RGB(0,0,0));
	m_listzf.SetTextBkColor(RGB(177,151,240));
	m_listzf.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);

	int nWidth=100;
	m_listzf.InsertColumn(0,_T("客人编号"),LVCFMT_LEFT,130);
	m_listzf.InsertColumn(1,_T("姓名"),LVCFMT_LEFT,nWidth);
	m_listzf.InsertColumn(2,_T("现住房号"),LVCFMT_LEFT,60);
	m_listzf.InsertColumn(3,_T("登记时间"),LVCFMT_LEFT,130);
	m_listzf.InsertColumn(4,_T("预付金额"),LVCFMT_LEFT,nWidth);
	m_listzf.InsertColumn(5,_T("付费方式"),LVCFMT_LEFT,nWidth);
	m_listzf.InsertColumn(6,_T("实价"),LVCFMT_LEFT,nWidth);

		
	_variant_t Holder;
	_variant_t strQuery;
	strQuery="select * from 住房";
	theApp.ADOExecute(theApp.m_pRecordset,strQuery);
    int iCount=theApp.m_pRecordset->GetRecordCount();
	if(0==iCount)
		return FALSE;
	CString str;
	theApp.m_pRecordset->MoveFirst();

	for(int i=0;i<iCount;i++)
	{
		Holder=theApp.m_pRecordset->GetCollect("客人账号");
    	str=(Holder.vt==VT_NULL)?"":(char *)(_bstr_t)Holder;
    	m_listzf.InsertItem(i,str);

		Holder=theApp.m_pRecordset->GetCollect("姓名");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listzf.SetItemText(i,1,str);

        Holder=theApp.m_pRecordset->GetCollect("现住房号");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listzf.SetItemText(i,2,str);

        Holder=theApp.m_pRecordset->GetCollect("登记时间");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listzf.SetItemText(i,3,str);

		Holder=theApp.m_pRecordset->GetCollect("预付金额");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listzf.SetItemText(i,4,str);

		Holder=theApp.m_pRecordset->GetCollect("付费方式");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listzf.SetItemText(i,5,str);

		Holder=theApp.m_pRecordset->GetCollect("实价");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listzf.SetItemText(i,6,str);


		theApp.m_pRecordset->MoveNext();
	}
	
	return TRUE;// return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}




void JieZhang::OnDblclkListzf(NMHDR* pNMHDR, LRESULT* pResult)//双击列表项事件 
{
	// TODO: Add your control notification handler code here
	POSITION pos=m_listzf.GetFirstSelectedItemPosition();
	m_nIndex = m_listzf.GetNextSelectedItem(pos);//得到项目索引


	m_id=m_listzf.GetItemText(m_nIndex,0);
	m_name=m_listzf.GetItemText(m_nIndex,1);
	m_roomid=m_listzf.GetItemText(m_nIndex,2);
	m_payfirst=m_listzf.GetItemText(m_nIndex,4);
    m_intime=m_listzf.GetItemText(m_nIndex,3);


	UpdateData(FALSE);
	
	*pResult = 0;
}

void JieZhang::OnOK() 
{
	// TODO: Add extra validation here
	_variant_t str;
	//UpdateData(FALSE);
    UpdateData();
	CString paytype,curtime;
	GetDlgItemText(IDC_COMBO2,paytype);
	curtime=m_curtime.Format(_T("%Y-%m-%d %H:%M:%S"));
	if(curtime==""||m_shouldpay=="")
	{
		AfxMessageBox(_T("输入信息不完整.."),MB_ICONINFORMATION);
		return;
	}

	if(m_paylast=="")
	{
		AfxMessageBox(_T("结账总额不能为空..."),MB_ICONINFORMATION);
		return;
	}
/*	if(m_intime>curtime)
	{
		AfxMessageBox("当前时间错误..",MB_ICONINFORMATION);
		return;
	}*/

	if(MessageBox(_T("确定结账吗?"),_T("是否确定?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;

	//添加至结账明细表相关信息

	str="insert into 结账明细(结账时间,客人账号,客人姓名,登记时间,在住房号,应付账款,已付账款,收款方式,结账收款,余零,备注)\
		values ('"+curtime+"','"+m_id+"','"+m_name+"','"+m_intime+"','"+m_roomid+"','"+m_shouldpay+"','"+m_payfirst+"','"+paytype+"','"+m_paylast+"','"+m_small+"','"+m_beizhu+"')";
	theApp.ADOExecute(theApp.m_pRecordset,str);//注意数据类型的统一(与数据库)

	//删除住房表相关信息


	str="delete from 住房 where 客人账号='"+m_id+"'and 现住房号='"+m_roomid+"'";//客人账号数据类型为文本***
	theApp.ADOExecute(theApp.m_pRecordset,str);///如果一个账号对应多个房间

	//添加至历史账务表相关信息, 该处结帐总额有待修改
	str="select * from 结账明细 where 客人账号='"+m_id+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	float payatlast=theApp.m_pRecordset->GetCollect("结账收款");
	float havepay=theApp.m_pRecordset->GetCollect("已付账款");
	float yuling=theApp.m_pRecordset->GetCollect("余零");
	float jiezhangzonge=payatlast+havepay-yuling;
	CString jiezhangstr;
	jiezhangstr.Format(_T("%.2f"),jiezhangzonge);
	str="insert into 历史账务(结账时间,客人账号,客人姓名,曾住房,结账总额,登记时间)\
         values ('"+curtime+"','"+m_id+"','"+m_name+"','"+m_roomid+"','"+jiezhangstr+"','"+m_intime+"')";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	//结账后应删除阶段账务表相关内容
	str="delete * from 阶段账务 where 客户账号='"+m_id+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);/////应处理好上面扫描阶段账务表部分

	//将客房表客房状态置为脏房

	str="update 客房 set 客房状态='脏房' where 房号='"+m_roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);


	
	CDialog::OnOK();
}
//结账的复杂性：
//1.结账要考虑当前住房账务及之前换房的消费（这里只考虑换一次房，若换2次以上，
//如何累加是个问题）
//2.折扣以第一次登记为准
//3.客人可能加开房，但结账是独立的，即每次结账仅考虑1，一个账号及一个房间（及之前换房）
//构成一笔消费，除非客人要合并账单，一起结账，这一功能未做
//4.钟点房未考虑打折问题
void JieZhang::OnSetfocusCostofall()//当触发应付账款编辑框
{
	// TODO: Add your control notification handler code here

	CString intime,leavetime;
	GetDlgItemText(IDC_EDIT10,intime);
	GetDlgItemText(IDC_EDIT9,leavetime);
	if(m_id==""||m_name==""||m_roomid==""||m_payfirst==""||intime==""||leavetime=="")
		return;
	_variant_t str;
	str="select * from 住房 where 客人账号='"+m_id+"' and 现住房号='"+m_roomid+"'";//只有账号和房号才能决定一次消费
	theApp.ADOExecute(theApp.m_pRecordset,str);
//	UpdateData();
	double realcost=theApp.m_pRecordset->GetCollect("实价");

	
	float dayoflive=m_curtime-theApp.m_pRecordset->GetCollect("登记时间");//须定义为浮点型
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
	str="select * from 阶段账务 where 客户账号='"+m_id+"' and 现住房='"+m_roomid+"'";///换房前与换房后两房合计
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
	////预付+结账收款-余零=总入款
	////换房结账的复杂性？？？？？
	CString costofall;
	costofall.Format(_T("%.2f"),costatleast);
	SetDlgItemText(IDC_EDIT5,costofall);//总价显示到应付账款

	day.Format(_T("%.1f"),dayoflive);//??????

	CString shouldpaystr;
	shouldpaystr.Format(_T("%.2f"),shouldpayatlast);
	CString shouldpayatlastptr="结账须付帐款"+shouldpaystr+"元";
	day="住店"+day+"天"+shouldpayatlastptr;

	SetDlgItemText(IDC_EDIT8,day);////天数显示到备注
	}

	else
	{
		float deltahour=int(deltaday*24+0.5);
		CString deltahourstr;
		deltahourstr.Format(_T("%.1f"),deltahour);
		
		float cost=deltahour*realcost;
	    CString costofall;
	    costofall.Format(_T("%.2f"),cost);
		SetDlgItemText(IDC_EDIT5,costofall);//总价显示到应付账款

		CString time="钟点房住店时间"+deltahourstr+"小时";
		SetDlgItemText(IDC_EDIT8,time);////时间显示到备注
	}
	
}
