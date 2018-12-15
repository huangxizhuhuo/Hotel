// Room.cpp : implementation file
//

#include "stdafx.h"
#include "Hotel.h"
#include "Room.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Room dialog


Room::Room(CWnd* pParent /*=NULL*/)
	: CDialog(Room::IDD, pParent)
{
	//{{AFX_DATA_INIT(Room)
	m_roomid = _T("");
	m_floor = _T("");
	m_tezheng = _T("");
	m_costofoneday = _T("");
	m_costofanhour = _T("");
	//}}AFX_DATA_INIT
}


void Room::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Room)
	DDX_Control(pDX, IDC_COMBO2, m_weizhi);
	DDX_Control(pDX, IDC_COMBO1, m_roomtype);
	DDX_Control(pDX, IDC_LIST1, m_listkf);
	DDX_Text(pDX, IDC_EDIT1, m_roomid);
	DDX_Text(pDX, IDC_EDIT2, m_floor);
	DDX_Text(pDX, IDC_EDIT3, m_tezheng);
	DDX_Text(pDX, IDC_EDIT5, m_costofoneday);
	DDX_Text(pDX, IDC_EDIT6, m_costofanhour);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Room, CDialog)
	//{{AFX_MSG_MAP(Room)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON3, OnModifyRoom)
	ON_BN_CLICKED(IDC_BUTTON2, OnAddRoom)
	ON_BN_CLICKED(IDC_BUTTON4, OnDeleteRoom)
	ON_BN_CLICKED(IDC_BUTTON5, OnRefresh)
	ON_BN_CLICKED(IDC_BUTTON6, OnQuXiao)
	ON_BN_CLICKED(IDC_BUTTON1, OnGuanBi)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Room message handlers

BOOL Room::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here


	m_listkf.SetBkColor(RGB(177,151,240));
	m_listkf.SetTextColor(RGB(0,0,0));
	m_listkf.SetTextBkColor(RGB(177,151,240));
	m_listkf.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
//	m_listft.SetExtendedStyle(m_listft.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	int nWidth=75;
	m_listkf.InsertColumn(0,_T("房号"),LVCFMT_LEFT,60);
	m_listkf.InsertColumn(1,_T("类型"),LVCFMT_LEFT,110);
	m_listkf.InsertColumn(2,_T("位置"),LVCFMT_LEFT,nWidth);
	m_listkf.InsertColumn(3,_T("层号"),LVCFMT_LEFT,nWidth);
	m_listkf.InsertColumn(4,_T("房价"),LVCFMT_LEFT,nWidth);
	m_listkf.InsertColumn(5,_T("钟点房价"),LVCFMT_LEFT,80);
	m_listkf.InsertColumn(6,_T("特征"),LVCFMT_LEFT,100);
	m_listkf.InsertColumn(7,_T("房态"),LVCFMT_LEFT,nWidth);

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
    	m_listkf.InsertItem(i,str);

		Holder=theApp.m_pRecordset->GetCollect("客房级别");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,1,str);

        Holder=theApp.m_pRecordset->GetCollect("位置");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,2,str);

        Holder=theApp.m_pRecordset->GetCollect("位于层号");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,3,str);


		Holder=theApp.m_pRecordset->GetCollect("单价");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,4,str);

        Holder=theApp.m_pRecordset->GetCollect("钟点房价");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,5,str);

        Holder=theApp.m_pRecordset->GetCollect("特征");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,6,str);

		Holder=theApp.m_pRecordset->GetCollect("客房状态");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,7,str);

		theApp.m_pRecordset->MoveNext();
	}


	m_roomtype.AddString(_T("标准单人房"));
	m_roomtype.AddString(_T("标准双人房"));
	m_roomtype.AddString(_T("豪华单人房"));
	m_roomtype.AddString(_T("标准单人房"));
	m_roomtype.AddString(_T("高级套房"));

	m_weizhi.AddString(_T("主楼"));

	m_nIndex=-1;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Room::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	POSITION pos=m_listkf.GetFirstSelectedItemPosition();
	m_nIndex = m_listkf.GetNextSelectedItem(pos);//得到项目索引


	m_roomid=m_listkf.GetItemText(m_nIndex,0);
	CString roomtype=m_listkf.GetItemText(m_nIndex,1);
    CString	weizhi=m_listkf.GetItemText(m_nIndex,2);
	m_floor=m_listkf.GetItemText(m_nIndex,3);
	m_costofoneday=m_listkf.GetItemText(m_nIndex,4);
	m_costofanhour=m_listkf.GetItemText(m_nIndex,5);
	m_tezheng=m_listkf.GetItemText(m_nIndex,6);
	SetDlgItemText(IDC_COMBO1,roomtype);
	SetDlgItemText(IDC_COMBO2,weizhi);

	UpdateData(FALSE);
	
	*pResult = 0;
}

void Room::OnModifyRoom() 
{
	// TODO: Add your control notification handler code here
	_variant_t str;
	CString roomtype,weizhi;
	GetDlgItemText(IDC_COMBO1,roomtype);
	GetDlgItemText(IDC_COMBO2,weizhi);

	UpdateData();

	if(m_roomid==""||m_floor==""||roomtype==""||weizhi==""||m_costofoneday==""||m_costofanhour=="")
	{
		MessageBox(_T("请确保输入完整的信息..."));
		return;
	}

	if(MessageBox(_T("确定更改房间信息吗?"),_T("是否确定?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;



	str="update 客房 set \
					客房级别='"+roomtype+"',\
					单价='"+m_costofoneday+"',\
					位于层号='"+m_floor+"',\
					位置='"+weizhi+"',\
					特征='"+m_tezheng+"',\
					钟点房价='"+m_costofanhour+"' where 房号='"+m_roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	OnRefresh();
	
}

void Room::OnAddRoom() 
{
	// TODO: Add your control notification handler code here

	_variant_t str;
	CString roomtype,weizhi;
	GetDlgItemText(IDC_COMBO1,roomtype);
	GetDlgItemText(IDC_COMBO2,weizhi);

	UpdateData();



	if(m_roomid==""||m_floor==""||roomtype==""||weizhi==""||m_costofoneday==""||m_costofanhour=="")
	{
		MessageBox(_T("请确保输入完整的信息..."));
		return;
	}

	if(MessageBox(_T("确定添加吗?"),_T("是否确定?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
	str="insert into 客房(房号,客房级别,客房状态,单价,位于层号,位置,特征,钟点房价)\
		values ('"+m_roomid+"','"+roomtype+"','空','"+m_costofoneday+"',\
                 '"+m_floor+"','"+weizhi+"','"+m_tezheng+"','"+m_costofanhour+"')";
/*str="update 客房 set 房号='"+m_roomid+"'\
					客房级别='"+roomtype+"'\
					单价='"+m_costofoneday+"'\
					位于层号='"+m_floor+"'\
					位置='"+weizhi+"'\
					特征='"+m_tezheng+"'\
					钟点房价='"+m_costofanhour+"'";*/
	theApp.ADOExecute(theApp.m_pRecordset,str);
	OnRefresh();
//	MessageBox("添加成功...");
	
}

void Room::OnDeleteRoom() 
{
	// TODO: Add your control notification handler code here

	
//	POSITION pos = m_listkf.GetFirstSelectedItemPosition();
//	m_nIndex = m_listkf.GetNextSelectedItem(pos);  // 得到项目索引
	m_listkf.SetFocus();
	if (m_nIndex == -1)	  //如果没有选择就返回
	{
		MessageBox(_T("请选择下边列表中一项再操作!"),_T("提示"),MB_ICONINFORMATION);
		return;  
	}

	CString room=m_listkf.GetItemText(m_nIndex,0);
	CString fangtai=m_listkf.GetItemText(m_nIndex,7);
	if(fangtai=="保留"||fangtai=="已住")
	{
		MessageBox(_T("客房正在使用或保留,不能删除..."),_T("不能删除"));
		return;
	}


	_variant_t str;

	str="delete from 客房 where 房号='"+room+"'";
	

	if(MessageBox(_T("确定删除吗?将删除该客房所有相关信息..."),_T("是否确定?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;

    theApp.ADOExecute(theApp.m_pRecordset,str);
	OnRefresh();
	
}

void Room::OnRefresh() 
{
	// TODO: Add your control notification handler code here

	m_listkf.DeleteAllItems();///删除所有行

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
    	m_listkf.InsertItem(i,str);

		Holder=theApp.m_pRecordset->GetCollect("客房级别");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,1,str);

        Holder=theApp.m_pRecordset->GetCollect("位置");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,2,str);

        Holder=theApp.m_pRecordset->GetCollect("位于层号");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,3,str);


		Holder=theApp.m_pRecordset->GetCollect("单价");
    	str=(Holder.vt==VT_NULL)?"":(char *)(_bstr_t)Holder;
    	m_listkf.SetItemText(i,4,str);

		Holder=theApp.m_pRecordset->GetCollect("钟点房价");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,5,str);

        Holder=theApp.m_pRecordset->GetCollect("特征");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,6,str);

        Holder=theApp.m_pRecordset->GetCollect("客房状态");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,7,str);

		theApp.m_pRecordset->MoveNext();
	}	
}

void Room::OnQuXiao() 
{
	// TODO: Add your control notification handler code here

	m_roomid = _T("");
	m_floor = _T("");
	m_tezheng = _T("");
	m_costofoneday = _T("");
	m_costofanhour = _T("");
	

	SetDlgItemText(IDC_COMBO1,_T(""));
	SetDlgItemText(IDC_COMBO2,_T(""));

	UpdateData(false);
	
}

void Room::OnGuanBi() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
	
}

void Room::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos=m_listkf.GetFirstSelectedItemPosition();
	m_nIndex = m_listkf.GetNextSelectedItem(pos);//得到项目索引
	
	*pResult = 0;
}
