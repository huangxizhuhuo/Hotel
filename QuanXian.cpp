// QuanXian.cpp : implementation file
//

#include "stdafx.h"
#include "Hotel.h"
#include "QuanXian.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// QuanXian dialog


QuanXian::QuanXian(CWnd* pParent /*=NULL*/)
	: CDialog(QuanXian::IDD, pParent)
{
	//{{AFX_DATA_INIT(QuanXian)
	m_id = _T("");
	m_beizhu = _T("");
	m_iscustom = FALSE;
	m_isselect = FALSE;
	m_istable = FALSE;
	m_isfoundation = FALSE;
	m_issystem = FALSE;
	//}}AFX_DATA_INIT
}


void QuanXian::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(QuanXian)
	DDX_Control(pDX, IDC_COMBO1, m_job);
	DDX_Control(pDX, IDC_LIST1, m_listqx);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT3, m_beizhu);
	DDX_Check(pDX, IDC_CHECK1, m_iscustom);
	DDX_Check(pDX, IDC_CHECK2, m_isselect);
	DDX_Check(pDX, IDC_CHECK3, m_istable);
	DDX_Check(pDX, IDC_CHECK4, m_isfoundation);
	DDX_Check(pDX, IDC_CHECK5, m_issystem);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(QuanXian, CDialog)
	//{{AFX_MSG_MAP(QuanXian)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkListqx)
	ON_BN_CLICKED(IDC_BUTTON1, OnAddId)
	ON_BN_CLICKED(IDC_BUTTON3, OnQuXiao)
	ON_BN_CLICKED(IDC_BUTTON2, OnBaoCun)
	ON_BN_CLICKED(IDC_BUTTON4, OnShanChu)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickListqx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// QuanXian message handlers

BOOL QuanXian::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_listqx.SetBkColor(RGB(177,151,240));
	m_listqx.SetTextColor(RGB(0,0,0));
	m_listqx.SetTextBkColor(RGB(177,151,240));
	m_listqx.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
//	m_listft.SetExtendedStyle(m_listft.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	int nWidth=100;
	m_listqx.InsertColumn(0,_T("登录账号"),LVCFMT_LEFT,80);
	m_listqx.InsertColumn(1,_T("职务"),LVCFMT_LEFT,120);
	m_listqx.InsertColumn(2,_T("备注"),LVCFMT_LEFT,100);
	m_listqx.InsertColumn(3,_T("客房系统"),LVCFMT_LEFT,60);
	m_listqx.InsertColumn(4,_T("信息查询"),LVCFMT_LEFT,60);
	m_listqx.InsertColumn(5,_T("报表中心"),LVCFMT_LEFT,60);
	m_listqx.InsertColumn(6,_T("基础资料"),LVCFMT_LEFT,60);
	m_listqx.InsertColumn(7,_T("系统管理"),LVCFMT_LEFT,60);

	_variant_t Holder;
	_variant_t strQuery;
	strQuery="select * from 用户权限";
	theApp.ADOExecute(theApp.m_pRecordset,strQuery);
    int iCount=theApp.m_pRecordset->GetRecordCount();
	if(0==iCount)
		return FALSE;
	CString str;
	theApp.m_pRecordset->MoveFirst();
//	int nItem;
	for(int i=0;i<iCount;i++)
	{
		Holder=theApp.m_pRecordset->GetCollect("UserId");
    	str=(Holder.vt==VT_NULL)?"":(char *)(_bstr_t)Holder;
    	m_listqx.InsertItem(i,str);
//		m_listft.SetItem(i,0,str,);

		Holder=theApp.m_pRecordset->GetCollect("职务");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,1,str);

        Holder=theApp.m_pRecordset->GetCollect("备注");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,2,str);

		Holder=theApp.m_pRecordset->GetCollect("客房系统");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,3,str);

		Holder=theApp.m_pRecordset->GetCollect("信息查询");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,4,str);

		Holder=theApp.m_pRecordset->GetCollect("报表中心");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,5,str);

		Holder=theApp.m_pRecordset->GetCollect("基础资料");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,6,str);

		Holder=theApp.m_pRecordset->GetCollect("系统管理");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,7,str);

		theApp.m_pRecordset->MoveNext();
	}
	m_nIndex=-1;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void QuanXian::OnDblclkListqx(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	POSITION pos=m_listqx.GetFirstSelectedItemPosition();
	m_nIndex = m_listqx.GetNextSelectedItem(pos);//得到项目索引


	m_id=m_listqx.GetItemText(m_nIndex,0);
	CString job=m_listqx.GetItemText(m_nIndex,1);
	SetDlgItemText(IDC_COMBO1,job);
	m_beizhu=m_listqx.GetItemText(m_nIndex,2);
	CString iscustom=m_listqx.GetItemText(m_nIndex,3);
	if(iscustom=="Y")
	{
		m_iscustom=true;
	}
	else
	{
		m_iscustom=false;
	}
    CString isselect=m_listqx.GetItemText(m_nIndex,4);
	if(isselect=="Y")
	{
		m_isselect=true;
	}
	else
	{
		m_isselect=false;
	}
	CString istable=m_listqx.GetItemText(m_nIndex,5);
	if(istable=="Y")
	{
		m_istable=true;
	}
	else
	{
		m_istable=false;
	}
	CString isfoundation=m_listqx.GetItemText(m_nIndex,6);
	if(isfoundation=="Y")
	{
		m_isfoundation=true;
	}
	else
	{
		m_isfoundation=false;
	}
	CString issystem=m_listqx.GetItemText(m_nIndex,7);
	if(issystem=="Y")
	{
		m_issystem=true;
	}
	else
	{
		m_issystem=false;
	}


	UpdateData(FALSE);
	
	*pResult = 0;
}

void QuanXian::OnAddId() 
{
	// TODO: Add your control notification handler code here

	UpdateData();
	if(m_id=="")
	{
		AfxMessageBox(_T("请输入用户名..."),MB_ICONINFORMATION);
		return;
	}
	
	m_listqx.SetFocus();
	if (m_nIndex == -1)	  //如果没有选择就返回
	{
		MessageBox(_T("请选择上边列表中一项再操作!"),_T("提示"),MB_ICONINFORMATION);
		return;  
	}

	CString name;///////////超级管理员信息不可修改
	name= m_listqx.GetItemText(m_nIndex,0);

	CString jobstr;
    jobstr=m_listqx.GetItemText(m_nIndex,1);
    if(jobstr=="超级管理员")
	{
      MessageBox(_T("超级管理员信息不可修改..."),_T("没有权限"),MB_ICONINFORMATION);
      return;
	}


	if(MessageBox(_T("确定修改吗?"),_T("是否确定?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;

	_variant_t str;
	CString iscustom,isselect,istable,isfoundation,issystem;
	m_iscustom?iscustom="Y":iscustom="N";
	m_isselect?isselect="Y":isselect="N";
	m_istable?istable="Y":istable="N";
	m_isfoundation?isfoundation="Y":isfoundation="N";
	m_issystem?issystem="Y":issystem="N";
	CString job;
	GetDlgItemText(IDC_COMBO1,job);
	str="update 用户权限 set 备注='"+m_beizhu+"',\
		                     职务='"+job+"',\
							 客房系统='"+iscustom+"',\
							 信息查询='"+isselect+"',\
							 报表中心='"+istable+"',\
							 基础资料='"+isfoundation+"',\
							 系统管理='"+issystem+"' where UserId='"+name+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	AfxMessageBox(_T("修改成功..."),MB_ICONINFORMATION);
	OnRefresh();

	
}

void QuanXian::OnQuXiao() 
{
	// TODO: Add your control notification handler code here
	m_id = _T("");
	m_beizhu = _T("");
	SetDlgItemText(IDC_COMBO1,_T(""));
	m_iscustom = FALSE;
	m_isselect = FALSE;
	m_istable = FALSE;
	m_isfoundation = FALSE;
	m_issystem = FALSE;
	UpdateData(false);
	
}

void QuanXian::OnBaoCun() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(m_id=="")
	{
		AfxMessageBox(_T("请输入用户名..."),MB_ICONINFORMATION);
		return;
	}
	
	if(MessageBox(_T("确定保存吗?"),_T("是否确定?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;

	_variant_t str;
	CString iscustom,isselect,istable,isfoundation,issystem;
	m_iscustom?iscustom="Y":iscustom="N";
	m_isselect?isselect="Y":isselect="N";
	m_istable?istable="Y":istable="N";
	m_isfoundation?isfoundation="Y":isfoundation="N";
	m_issystem?issystem="Y":issystem="N";
	CString job;
	GetDlgItemText(IDC_COMBO1,job);
	str="insert into 用户权限(UserId,备注,职务,客房系统,信息查询,报表中心,基础资料,系统管理)\
		values('"+m_id+"','"+m_beizhu+"','"+job+"','"+iscustom+"','"+isselect+"','"+istable+"','"+isfoundation+"','"+issystem+"')";

	theApp.ADOExecute(theApp.m_pRecordset,str);
	AfxMessageBox(_T("添加成功..."),MB_ICONINFORMATION);
	OnRefresh();
	
}

void QuanXian::OnShanChu() 
{
	// TODO: Add your control notification handler code here
	m_listqx.SetFocus();
	if (m_nIndex == -1)	  //如果没有选择就返回
	{
		MessageBox(_T("请选择上边列表中一项再操作!"),_T("提示"),MB_ICONINFORMATION);
		return;  
	}

	CString name;
	name= m_listqx.GetItemText(m_nIndex,0);
	CString job;//////////////////超级管理员不可删除
    job=m_listqx.GetItemText(m_nIndex,1);
    if(job=="超级管理员")
	{
        MessageBox(_T("超级管理员不可删除..."),_T("没有权限"),MB_ICONINFORMATION);
        return;
	}
	if(MessageBox(_T("确定吗?将使该用户删除..."),_T("是否确定?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
	_variant_t str;
	str="delete from 用户权限 where UserId='"+name+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	OnRefresh();

	
}

void QuanXian::OnClickListqx(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	POSITION pos=m_listqx.GetFirstSelectedItemPosition();
	m_nIndex = m_listqx.GetNextSelectedItem(pos);//得到项目索引
	
	*pResult = 0;
}


void QuanXian::OnRefresh()
{
	m_listqx.DeleteAllItems();///删除所有行

	_variant_t str1="select * from 用户权限";
	theApp.ADOExecute(theApp.m_pRecordset,str1);

	_variant_t Holder;
	
	int iCount=theApp.m_pRecordset->GetRecordCount();
	if(0==iCount)
		return;
	CString str;
	theApp.m_pRecordset->MoveFirst();
		for(int i=0;i<iCount;i++)
	{
		Holder=theApp.m_pRecordset->GetCollect("UserId");
    	str=(Holder.vt==VT_NULL)?"":(char *)(_bstr_t)Holder;
    	m_listqx.InsertItem(i,str);
//		m_listft.SetItem(i,0,str,);

		Holder=theApp.m_pRecordset->GetCollect("职务");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,1,str);

        Holder=theApp.m_pRecordset->GetCollect("备注");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,2,str);

		Holder=theApp.m_pRecordset->GetCollect("客房系统");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,3,str);

		Holder=theApp.m_pRecordset->GetCollect("信息查询");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,4,str);

		Holder=theApp.m_pRecordset->GetCollect("报表中心");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,5,str);

		Holder=theApp.m_pRecordset->GetCollect("基础资料");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,6,str);

		Holder=theApp.m_pRecordset->GetCollect("系统管理");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,7,str);

		theApp.m_pRecordset->MoveNext();
	}
}
