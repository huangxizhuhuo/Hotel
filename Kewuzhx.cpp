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
	m_listft.InsertColumn(0,_T("����"),LVCFMT_LEFT,50);
	m_listft.InsertColumn(1,_T("�ͷ�����"),LVCFMT_LEFT,100);
	m_listft.InsertColumn(2,_T("�ͷ�״̬"),LVCFMT_LEFT,50);
	m_listft.InsertColumn(3,_T("����"),LVCFMT_LEFT,70);
	m_listft.InsertColumn(4,_T("��ס��"),LVCFMT_LEFT,80);
	m_listft.InsertColumn(5,_T("�����˺�"),LVCFMT_LEFT,130);
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
    	m_listft.InsertItem(i,str);
//		m_listft.SetItem(i,0,str,);

		Holder=theApp.m_pRecordset->GetCollect("�ͷ�����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,1,str);

        Holder=theApp.m_pRecordset->GetCollect("�ͷ�״̬");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,2,str);

        Holder=theApp.m_pRecordset->GetCollect("����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,3,str);

		theApp.m_pRecordset->MoveNext();
	}
	//Invalidate();
	m_nIndex=-1;
	ishuanyuan=false;
	SetDlgItemText(IDC_BUTTON8,_T("������ס��"));

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Kewuzhx::OnButtonDJ() 
{
	// TODO: Add your control notification handler code here
	theApp.isnewroom=false;//�ǵǼǣ������¿���
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
	m_listft.DeleteAllItems();///ɾ��������

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
    	m_listft.InsertItem(i,str);

		Holder=theApp.m_pRecordset->GetCollect("�ͷ�����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,1,str);

        Holder=theApp.m_pRecordset->GetCollect("�ͷ�״̬");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,2,str);

        Holder=theApp.m_pRecordset->GetCollect("����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,3,str);

		theApp.m_pRecordset->MoveNext();
	}
	ishuanyuan=false;///////////////////////////�ð�ťΪ������ס��
	SetDlgItemText(IDC_BUTTON8,_T("������ס��"));
//	SetRedraw(TRUE); 
//	Invalidate();
	
}

void Kewuzhx::OnRclickListFt(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

//	CListCtrl &CList=m_listft.GetListCtrl();//��ȡ��ǰ�б�ؼ���ָ��
	CMenu menu,*pSubMenu;//��������Ҫ�õ���cmenu����
	menu.LoadMenu(IDR_MENU1);//װ���Զ�����Ҽ��˵�
	pSubMenu=menu.GetSubMenu(0);///��ȡ��һ�������˵������Ե�һ���˵��������Ӳ˵�
	CPoint curPoint;//����һ������ȷ�����λ�õ�λ��
	GetCursorPos(&curPoint);//��ȡ��ǰ����λ�ã��Ա�ʹ�ò˵����Ը�����

	int istat=m_listft.GetSelectionMark();//��istat��ŵ�ǰѡ�����ǵڼ���

	theApp.fangjianhaoma=m_listft.GetItemText(istat,0);//��ȡ��ǰ���е����ݣ�0�����ǵ�0��


	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,curPoint.x,curPoint.y,this);//��ָ��λ����ʾ�����˵�



	
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
	theApp.isnewroom=true;// ���¿���
	if(ishuanyuan==false)
	{
		AfxMessageBox(_T("���ȼ�����ס����Ϣ��ѡ��Ҫ�ӿ����Ŀ���..."),MB_ICONINFORMATION);
		return;
	}
	if(m_nIndex==-1)
	{
		AfxMessageBox(_T("����ѡ���������һ������..."),MB_ICONINFORMATION);
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

void Kewuzhx::OnSearchCustomer()//������ס�ͣ���ԭ 
{
	// TODO: Add your control notification handler code here
	m_listft.DeleteAllItems();///ɾ��������
	if(ishuanyuan==false)
	{	
	_variant_t Holder;
	_variant_t strQuery;
	strQuery="select * from �ͷ�,ס�� where �ͷ�.����=ס��.��ס����";
	theApp.ADOExecute(theApp.m_pRecordset,strQuery);
    int iCount=theApp.m_pRecordset->GetRecordCount();
	if(0==iCount)
		return;
	CString str;
	theApp.m_pRecordset->MoveFirst();
//	int nItem;
	for(int i=0;i<iCount;i++)
	{
		Holder=theApp.m_pRecordset->GetCollect("����");
    	str=(Holder.vt==VT_NULL)?"":(char *)(_bstr_t)Holder;
    	m_listft.InsertItem(i,str);
//		m_listft.SetItem(i,0,str,);

		Holder=theApp.m_pRecordset->GetCollect("�ͷ�����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,1,str);

        Holder=theApp.m_pRecordset->GetCollect("�ͷ�״̬");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,2,str);

        Holder=theApp.m_pRecordset->GetCollect("����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,3,str);

		Holder=theApp.m_pRecordset->GetCollect("����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,4,str);

		Holder=theApp.m_pRecordset->GetCollect("�����˺�");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,5,str);


		theApp.m_pRecordset->MoveNext();
	}
	SetDlgItemText(IDC_BUTTON8,_T("��ԭ"));
	ishuanyuan=true;
	}
	else
	{
	_variant_t Holder;
	_variant_t strQuery;
	strQuery="select * from �ͷ�";
	theApp.ADOExecute(theApp.m_pRecordset,strQuery);
    int iCount=theApp.m_pRecordset->GetRecordCount();
	if(0==iCount)
		return;
	CString str;
	theApp.m_pRecordset->MoveFirst();
//	int nItem;
	for(int i=0;i<iCount;i++)
	{
		Holder=theApp.m_pRecordset->GetCollect("����");
    	str=(Holder.vt==VT_NULL)?"":(char *)(_bstr_t)Holder;
    	m_listft.InsertItem(i,str);
//		m_listft.SetItem(i,0,str,);

		Holder=theApp.m_pRecordset->GetCollect("�ͷ�����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,1,str);

        Holder=theApp.m_pRecordset->GetCollect("�ͷ�״̬");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,2,str);

        Holder=theApp.m_pRecordset->GetCollect("����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,3,str);

		theApp.m_pRecordset->MoveNext();
	}
	//Invalidate();
	ishuanyuan=false;
	SetDlgItemText(IDC_BUTTON8,_T("������ס��"));
	}
}

void Kewuzhx::OnClickListFangTai(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listft.GetFirstSelectedItemPosition();
	m_nIndex = m_listft.GetNextSelectedItem(pos);  // �õ���Ŀ����
	
	*pResult = 0;
}

void Kewuzhx::OnYUFu() 
{
	// TODO: Add your control notification handler code here
	if(ishuanyuan==false)
	{
		AfxMessageBox(_T("���ȼ�����ס����Ϣ��ѡ��Ҫ����Ԥ����Ŀ���..."),MB_ICONINFORMATION);
		return;
	}
	if(m_nIndex==-1)
	{
		AfxMessageBox(_T("����ѡ���������һ������..."),MB_ICONINFORMATION);
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

	m_listft.DeleteAllItems();///ɾ��������

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
    	m_listft.InsertItem(i,str);

		Holder=theApp.m_pRecordset->GetCollect("�ͷ�����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,1,str);

        Holder=theApp.m_pRecordset->GetCollect("�ͷ�״̬");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,2,str);

        Holder=theApp.m_pRecordset->GetCollect("����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listft.SetItemText(i,3,str);

		theApp.m_pRecordset->MoveNext();
	}
}

