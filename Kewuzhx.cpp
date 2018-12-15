// Kewuzhx.cpp : implementation file
//

#include "stdafx.h"
#include "Hotel.h"
#include "Kewuzhx.h"
#include "DengJi.h"

#include "JieZhang.h"

#include "JiaShou.h"

#include "HuanFang.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Kewuzhx dialog


Kewuzhx::Kewuzhx(CWnd* pParent /*=NULL*/)
	: CDialog(Kewuzhx::IDD, pParent)
{
	//{{AFX_DATA_INIT(Kewuzhx)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Kewuzhx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Kewuzhx)
	DDX_Control(pDX, IDC_LISTFANGTAI, m_listft);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Kewuzhx, CDialog)
	//{{AFX_MSG_MAP(Kewuzhx)
	ON_BN_CLICKED(IDC_BUTTONDJ, OnButtonDJ)
	ON_BN_CLICKED(IDC_BUTTONJZH, OnButtonJZH)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonRefresh)
	ON_NOTIFY(NM_RCLICK, IDC_LISTFANGTAI, OnRclickListFt)
	ON_BN_CLICKED(IDC_BUTTON4, OnChangeRoom)
	ON_BN_CLICKED(IDC_BUTTON2, OnAddNew)
	ON_BN_CLICKED(IDC_BUTTON8, OnSearchCustomer)
	ON_NOTIFY(NM_CLICK, IDC_LISTFANGTAI, OnClickListFangTai)
	ON_BN_CLICKED(IDC_BUTTON6, OnYUFu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Kewuzhx message handlers

BOOL Kewuzhx::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	// TODO: Add extra initialization here
//	m_listft.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_REPORT,rect,this,1);
	m_listft.SetBkColor(RGB(177,151,240));
	m_listft.SetTextColor(RGB(0,0,0));
	m_listft.SetTextBkColor(RGB(177,151,240));
	m_listft.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
//	m_listft.SetExtendedStyle(m_listft.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	int nWidth=100;
	m_listft.InsertColumn(0,_T("房号"),LVCFMT_LEFT,50);
	m_listft.InsertColumn(1,_T("客房级别"),LVCFMT_LEFT,100);
	m_listft.InsertColumn(2,_T("客房状态"),LVCFMT_LEFT,50);
	m_listft.InsertColumn(3,_T("单价"),LVCFMT_LEFT,70);
	m_listft.InsertColumn(4,_T("在住客"),LVCFMT_LEFT,80);
	m_listft.InsertColumn(5,_T("客人账号"),LVCFMT_LEFT,130);
	_variant_t Holder;
	_variant_t strQuery;
	strQuery="select * from 客房";
	theApp.ADOExecute(theApp.m_pRecordset,strQuery);
    int iCount=theApp.m_pRecordset->GetRecordCount();
	if(0==iCount)
		return FALSE;
	CString str;
	theApp.m_pRecordset->MoveFirst();
//	int nItem;
	for(int i=0;i<iCount;i++)
	{
		Holder=theApp.m_pRecordset->GetCollect("房号");
    	str=(Holder.vt==VT_NULL)?"":(char *)(_bstr_t)Holder;
    	m_listft.InsertItem(i,str);
//		m_listft.SetItem(i,0,str,);

		Holder=theApp.m_pRecordset->GetCollect("客房级别");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,1,str);

        Holder=theApp.m_pRecordset->GetCollect("客房状态");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,2,str);

        Holder=theApp.m_pRecordset->GetCollect("单价");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,3,str);

		theApp.m_pRecordset->MoveNext();
	}
	//Invalidate();
	m_nIndex=-1;
	ishuanyuan=false;
	SetDlgItemText(IDC_BUTTON8,_T("检索在住客"));

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Kewuzhx::OnButtonDJ() 
{
	// TODO: Add your control notification handler code here
	theApp.isnewroom=false;//是登记，不是新开房
	DengJi d;
	if(d.DoModal()!=IDOK)
		return;

	
}

void Kewuzhx::OnButtonJZH() 
{
	// TODO: Add your control notification handler code here


	JieZhang d;
	d.DoModal();
//	if(d.DoModal()!=IDOK)
//		return;	
}
//int nItem=-1;
void Kewuzhx::OnButtonRefresh() 
{
	// TODO: Add your control notification handler code here
	m_listft.DeleteAllItems();///删除所有行

	_variant_t str1="select * from 客房";
	theApp.ADOExecute(theApp.m_pRecordset,str1);

	_variant_t Holder;
	
	int iCount=theApp.m_pRecordset->GetRecordCount();
	if(0==iCount)
		return;
	CString str;
	theApp.m_pRecordset->MoveFirst();
	for(int i=0;i<iCount;i++)
	{
		Holder=theApp.m_pRecordset->GetCollect("房号");
    	str=(Holder.vt==VT_NULL)?"":(char *)(_bstr_t)Holder;
    	m_listft.InsertItem(i,str);

		Holder=theApp.m_pRecordset->GetCollect("客房级别");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,1,str);

        Holder=theApp.m_pRecordset->GetCollect("客房状态");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,2,str);

        Holder=theApp.m_pRecordset->GetCollect("单价");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,3,str);

		theApp.m_pRecordset->MoveNext();
	}
	ishuanyuan=false;///////////////////////////置按钮为检索在住客
	SetDlgItemText(IDC_BUTTON8,_T("检索在住客"));
//	SetRedraw(TRUE); 
//	Invalidate();
	
}

void Kewuzhx::OnRclickListFt(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

//	CListCtrl &CList=m_listft.GetListCtrl();//获取当前列表控件的指针
	CMenu menu,*pSubMenu;//定义下面要用到的cmenu对象
	menu.LoadMenu(IDR_MENU1);//装载自定义的右键菜单
	pSubMenu=menu.GetSubMenu(0);///获取第一个弹出菜单，所以第一个菜单必须有子菜单
	CPoint curPoint;//定义一个用于确定光标位置的位置
	GetCursorPos(&curPoint);//获取当前光标的位置，以便使得菜单可以跟随光标

	int istat=m_listft.GetSelectionMark();//用istat存放当前选定的是第几项

	theApp.fangjianhaoma=m_listft.GetItemText(istat,0);//获取当前项中的数据，0代表是第0列


	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,curPoint.x,curPoint.y,this);//在指定位置显示弹出菜单



	
	*pResult = 0;
}

void Kewuzhx::OnChangeRoom() 
{
	// TODO: Add your control notification handler code here
	HuanFang dlg;
	dlg.DoModal();
	
}

void Kewuzhx::OnAddNew() 
{
	// TODO: Add your control notification handler code here
	theApp.isnewroom=true;// 是新开房
	if(ishuanyuan==false)
	{
		AfxMessageBox(_T("请先检索在住客信息并选择要加开房的客人..."),MB_ICONINFORMATION);
		return;
	}
	if(m_nIndex==-1)
	{
		AfxMessageBox(_T("请先选择左面表中一行数据..."),MB_ICONINFORMATION);
		return;
	}
	DengJi dlg;
	CString id=m_listft.GetItemText(m_nIndex,5);
	CString name=m_listft.GetItemText(m_nIndex,4);
	dlg.m_id=id;
	dlg.m_name=name;
	UpdateData(FALSE);
	dlg.DoModal();
	
}

void Kewuzhx::OnSearchCustomer()//检索在住客，还原 
{
	// TODO: Add your control notification handler code here
	m_listft.DeleteAllItems();///删除所有行
	if(ishuanyuan==false)
	{	
	_variant_t Holder;
	_variant_t strQuery;
	strQuery="select * from 客房,住房 where 客房.房号=住房.现住房号";
	theApp.ADOExecute(theApp.m_pRecordset,strQuery);
    int iCount=theApp.m_pRecordset->GetRecordCount();
	if(0==iCount)
		return;
	CString str;
	theApp.m_pRecordset->MoveFirst();
//	int nItem;
	for(int i=0;i<iCount;i++)
	{
		Holder=theApp.m_pRecordset->GetCollect("房号");
    	str=(Holder.vt==VT_NULL)?"":(char *)(_bstr_t)Holder;
    	m_listft.InsertItem(i,str);
//		m_listft.SetItem(i,0,str,);

		Holder=theApp.m_pRecordset->GetCollect("客房级别");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,1,str);

        Holder=theApp.m_pRecordset->GetCollect("客房状态");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,2,str);

        Holder=theApp.m_pRecordset->GetCollect("单价");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,3,str);

		Holder=theApp.m_pRecordset->GetCollect("姓名");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,4,str);

		Holder=theApp.m_pRecordset->GetCollect("客人账号");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,5,str);


		theApp.m_pRecordset->MoveNext();
	}
	SetDlgItemText(IDC_BUTTON8,_T("还原"));
	ishuanyuan=true;
	}
	else
	{
	_variant_t Holder;
	_variant_t strQuery;
	strQuery="select * from 客房";
	theApp.ADOExecute(theApp.m_pRecordset,strQuery);
    int iCount=theApp.m_pRecordset->GetRecordCount();
	if(0==iCount)
		return;
	CString str;
	theApp.m_pRecordset->MoveFirst();
//	int nItem;
	for(int i=0;i<iCount;i++)
	{
		Holder=theApp.m_pRecordset->GetCollect("房号");
    	str=(Holder.vt==VT_NULL)?"":(char *)(_bstr_t)Holder;
    	m_listft.InsertItem(i,str);
//		m_listft.SetItem(i,0,str,);

		Holder=theApp.m_pRecordset->GetCollect("客房级别");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,1,str);

        Holder=theApp.m_pRecordset->GetCollect("客房状态");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,2,str);

        Holder=theApp.m_pRecordset->GetCollect("单价");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,3,str);

		theApp.m_pRecordset->MoveNext();
	}
	//Invalidate();
	ishuanyuan=false;
	SetDlgItemText(IDC_BUTTON8,_T("检索在住客"));
	}
}

void Kewuzhx::OnClickListFangTai(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listft.GetFirstSelectedItemPosition();
	m_nIndex = m_listft.GetNextSelectedItem(pos);  // 得到项目索引
	
	*pResult = 0;
}

void Kewuzhx::OnYUFu() 
{
	// TODO: Add your control notification handler code here
	if(ishuanyuan==false)
	{
		AfxMessageBox(_T("请先检索在住客信息并选择要加收预付款的客人..."),MB_ICONINFORMATION);
		return;
	}
	if(m_nIndex==-1)
	{
		AfxMessageBox(_T("请先选择左面表中一行数据..."),MB_ICONINFORMATION);
		return;
	}
	JiaShou dlg;
	CString id=m_listft.GetItemText(m_nIndex,5);
	CString name=m_listft.GetItemText(m_nIndex,4);
	CString roomid=m_listft.GetItemText(m_nIndex,0);
	dlg.m_customerid=id;
	dlg.m_name=name;
	dlg.m_roomid=roomid;
	UpdateData(FALSE);
	dlg.DoModal();
	
}

void Kewuzhx::OnRefresh()
{

	m_listft.DeleteAllItems();///删除所有行

	_variant_t str1="select * from 客房";
	theApp.ADOExecute(theApp.m_pRecordset,str1);

	_variant_t Holder;
	
	int iCount=theApp.m_pRecordset->GetRecordCount();
	if(0==iCount)
		return;
	CString str;
	theApp.m_pRecordset->MoveFirst();
	for(int i=0;i<iCount;i++)
	{
		Holder=theApp.m_pRecordset->GetCollect("房号");
    	str=(Holder.vt==VT_NULL)?"":(char *)(_bstr_t)Holder;
    	m_listft.InsertItem(i,str);

		Holder=theApp.m_pRecordset->GetCollect("客房级别");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,1,str);

        Holder=theApp.m_pRecordset->GetCollect("客房状态");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,2,str);

        Holder=theApp.m_pRecordset->GetCollect("单价");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,3,str);

		theApp.m_pRecordset->MoveNext();
	}
}

