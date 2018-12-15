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
	m_listkf.InsertColumn(0,_T("����"),LVCFMT_LEFT,60);
	m_listkf.InsertColumn(1,_T("����"),LVCFMT_LEFT,110);
	m_listkf.InsertColumn(2,_T("λ��"),LVCFMT_LEFT,nWidth);
	m_listkf.InsertColumn(3,_T("���"),LVCFMT_LEFT,nWidth);
	m_listkf.InsertColumn(4,_T("����"),LVCFMT_LEFT,nWidth);
	m_listkf.InsertColumn(5,_T("�ӵ㷿��"),LVCFMT_LEFT,80);
	m_listkf.InsertColumn(6,_T("����"),LVCFMT_LEFT,100);
	m_listkf.InsertColumn(7,_T("��̬"),LVCFMT_LEFT,nWidth);

	_variant_t Holder;
	_variant_t strQuery;
	strQuery="select * from �ͷ�";
	theApp.ADOExecute(theApp.m_pRecordset,strQuery);
    int iCount=theApp.m_pRecordset->GetRecordCount();
	if(0==iCount)
		return FALSE;
	CString str;
	theApp.m_pRecordset->MoveFirst();
//	int nItem;
	for(int i=0;i<iCount;i++)
	{
		Holder=theApp.m_pRecordset->GetCollect("����");
    	str=(Holder.vt==VT_NULL)?"":(char *)(_bstr_t)Holder;
    	m_listkf.InsertItem(i,str);

		Holder=theApp.m_pRecordset->GetCollect("�ͷ�����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,1,str);

        Holder=theApp.m_pRecordset->GetCollect("λ��");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,2,str);

        Holder=theApp.m_pRecordset->GetCollect("λ�ڲ��");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,3,str);


		Holder=theApp.m_pRecordset->GetCollect("����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,4,str);

        Holder=theApp.m_pRecordset->GetCollect("�ӵ㷿��");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,5,str);

        Holder=theApp.m_pRecordset->GetCollect("����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,6,str);

		Holder=theApp.m_pRecordset->GetCollect("�ͷ�״̬");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,7,str);

		theApp.m_pRecordset->MoveNext();
	}


	m_roomtype.AddString(_T("��׼���˷�"));
	m_roomtype.AddString(_T("��׼˫�˷�"));
	m_roomtype.AddString(_T("�������˷�"));
	m_roomtype.AddString(_T("��׼���˷�"));
	m_roomtype.AddString(_T("�߼��׷�"));

	m_weizhi.AddString(_T("��¥"));

	m_nIndex=-1;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Room::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	POSITION pos=m_listkf.GetFirstSelectedItemPosition();
	m_nIndex = m_listkf.GetNextSelectedItem(pos);//�õ���Ŀ����


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
		MessageBox(_T("��ȷ��������������Ϣ..."));
		return;
	}

	if(MessageBox(_T("ȷ�����ķ�����Ϣ��?"),_T("�Ƿ�ȷ��?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;



	str="update �ͷ� set \
					�ͷ�����='"+roomtype+"',\
					����='"+m_costofoneday+"',\
					λ�ڲ��='"+m_floor+"',\
					λ��='"+weizhi+"',\
					����='"+m_tezheng+"',\
					�ӵ㷿��='"+m_costofanhour+"' where ����='"+m_roomid+"'";
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
		MessageBox(_T("��ȷ��������������Ϣ..."));
		return;
	}

	if(MessageBox(_T("ȷ�������?"),_T("�Ƿ�ȷ��?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
	str="insert into �ͷ�(����,�ͷ�����,�ͷ�״̬,����,λ�ڲ��,λ��,����,�ӵ㷿��)\
		values ('"+m_roomid+"','"+roomtype+"','��','"+m_costofoneday+"',\
                 '"+m_floor+"','"+weizhi+"','"+m_tezheng+"','"+m_costofanhour+"')";
/*str="update �ͷ� set ����='"+m_roomid+"'\
					�ͷ�����='"+roomtype+"'\
					����='"+m_costofoneday+"'\
					λ�ڲ��='"+m_floor+"'\
					λ��='"+weizhi+"'\
					����='"+m_tezheng+"'\
					�ӵ㷿��='"+m_costofanhour+"'";*/
	theApp.ADOExecute(theApp.m_pRecordset,str);
	OnRefresh();
//	MessageBox("��ӳɹ�...");
	
}

void Room::OnDeleteRoom() 
{
	// TODO: Add your control notification handler code here

	
//	POSITION pos = m_listkf.GetFirstSelectedItemPosition();
//	m_nIndex = m_listkf.GetNextSelectedItem(pos);  // �õ���Ŀ����
	m_listkf.SetFocus();
	if (m_nIndex == -1)	  //���û��ѡ��ͷ���
	{
		MessageBox(_T("��ѡ���±��б���һ���ٲ���!"),_T("��ʾ"),MB_ICONINFORMATION);
		return;  
	}

	CString room=m_listkf.GetItemText(m_nIndex,0);
	CString fangtai=m_listkf.GetItemText(m_nIndex,7);
	if(fangtai=="����"||fangtai=="��ס")
	{
		MessageBox(_T("�ͷ�����ʹ�û���,����ɾ��..."),_T("����ɾ��"));
		return;
	}


	_variant_t str;

	str="delete from �ͷ� where ����='"+room+"'";
	

	if(MessageBox(_T("ȷ��ɾ����?��ɾ���ÿͷ����������Ϣ..."),_T("�Ƿ�ȷ��?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;

    theApp.ADOExecute(theApp.m_pRecordset,str);
	OnRefresh();
	
}

void Room::OnRefresh() 
{
	// TODO: Add your control notification handler code here

	m_listkf.DeleteAllItems();///ɾ��������

	_variant_t str1="select * from �ͷ�";
	theApp.ADOExecute(theApp.m_pRecordset,str1);

	_variant_t Holder;
	
	int iCount=theApp.m_pRecordset->GetRecordCount();
	if(0==iCount)
		return;
	CString str;
	theApp.m_pRecordset->MoveFirst();
	for(int i=0;i<iCount;i++)
	{
		Holder=theApp.m_pRecordset->GetCollect("����");
    	str=(Holder.vt==VT_NULL)?"":(char *)(_bstr_t)Holder;
    	m_listkf.InsertItem(i,str);

		Holder=theApp.m_pRecordset->GetCollect("�ͷ�����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,1,str);

        Holder=theApp.m_pRecordset->GetCollect("λ��");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,2,str);

        Holder=theApp.m_pRecordset->GetCollect("λ�ڲ��");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,3,str);


		Holder=theApp.m_pRecordset->GetCollect("����");
    	str=(Holder.vt==VT_NULL)?"":(char *)(_bstr_t)Holder;
    	m_listkf.SetItemText(i,4,str);

		Holder=theApp.m_pRecordset->GetCollect("�ӵ㷿��");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,5,str);

        Holder=theApp.m_pRecordset->GetCollect("����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listkf.SetItemText(i,6,str);

        Holder=theApp.m_pRecordset->GetCollect("�ͷ�״̬");
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
	m_nIndex = m_listkf.GetNextSelectedItem(pos);//�õ���Ŀ����
	
	*pResult = 0;
}
