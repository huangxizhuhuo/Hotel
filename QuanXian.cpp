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
	m_listqx.InsertColumn(0,_T("��¼�˺�"),LVCFMT_LEFT,80);
	m_listqx.InsertColumn(1,_T("ְ��"),LVCFMT_LEFT,120);
	m_listqx.InsertColumn(2,_T("��ע"),LVCFMT_LEFT,100);
	m_listqx.InsertColumn(3,_T("�ͷ�ϵͳ"),LVCFMT_LEFT,60);
	m_listqx.InsertColumn(4,_T("��Ϣ��ѯ"),LVCFMT_LEFT,60);
	m_listqx.InsertColumn(5,_T("��������"),LVCFMT_LEFT,60);
	m_listqx.InsertColumn(6,_T("��������"),LVCFMT_LEFT,60);
	m_listqx.InsertColumn(7,_T("ϵͳ����"),LVCFMT_LEFT,60);

	_variant_t Holder;
	_variant_t strQuery;
	strQuery="select * from �û�Ȩ��";
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

		Holder=theApp.m_pRecordset->GetCollect("ְ��");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,1,str);

        Holder=theApp.m_pRecordset->GetCollect("��ע");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,2,str);

		Holder=theApp.m_pRecordset->GetCollect("�ͷ�ϵͳ");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,3,str);

		Holder=theApp.m_pRecordset->GetCollect("��Ϣ��ѯ");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,4,str);

		Holder=theApp.m_pRecordset->GetCollect("��������");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,5,str);

		Holder=theApp.m_pRecordset->GetCollect("��������");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,6,str);

		Holder=theApp.m_pRecordset->GetCollect("ϵͳ����");
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
	m_nIndex = m_listqx.GetNextSelectedItem(pos);//�õ���Ŀ����


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
		AfxMessageBox(_T("�������û���..."),MB_ICONINFORMATION);
		return;
	}
	
	m_listqx.SetFocus();
	if (m_nIndex == -1)	  //���û��ѡ��ͷ���
	{
		MessageBox(_T("��ѡ���ϱ��б���һ���ٲ���!"),_T("��ʾ"),MB_ICONINFORMATION);
		return;  
	}

	CString name;///////////��������Ա��Ϣ�����޸�
	name= m_listqx.GetItemText(m_nIndex,0);

	CString jobstr;
    jobstr=m_listqx.GetItemText(m_nIndex,1);
    if(jobstr=="��������Ա")
	{
      MessageBox(_T("��������Ա��Ϣ�����޸�..."),_T("û��Ȩ��"),MB_ICONINFORMATION);
      return;
	}


	if(MessageBox(_T("ȷ���޸���?"),_T("�Ƿ�ȷ��?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
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
	str="update �û�Ȩ�� set ��ע='"+m_beizhu+"',\
		                     ְ��='"+job+"',\
							 �ͷ�ϵͳ='"+iscustom+"',\
							 ��Ϣ��ѯ='"+isselect+"',\
							 ��������='"+istable+"',\
							 ��������='"+isfoundation+"',\
							 ϵͳ����='"+issystem+"' where UserId='"+name+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	AfxMessageBox(_T("�޸ĳɹ�..."),MB_ICONINFORMATION);
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
		AfxMessageBox(_T("�������û���..."),MB_ICONINFORMATION);
		return;
	}
	
	if(MessageBox(_T("ȷ��������?"),_T("�Ƿ�ȷ��?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
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
	str="insert into �û�Ȩ��(UserId,��ע,ְ��,�ͷ�ϵͳ,��Ϣ��ѯ,��������,��������,ϵͳ����)\
		values('"+m_id+"','"+m_beizhu+"','"+job+"','"+iscustom+"','"+isselect+"','"+istable+"','"+isfoundation+"','"+issystem+"')";

	theApp.ADOExecute(theApp.m_pRecordset,str);
	AfxMessageBox(_T("��ӳɹ�..."),MB_ICONINFORMATION);
	OnRefresh();
	
}

void QuanXian::OnShanChu() 
{
	// TODO: Add your control notification handler code here
	m_listqx.SetFocus();
	if (m_nIndex == -1)	  //���û��ѡ��ͷ���
	{
		MessageBox(_T("��ѡ���ϱ��б���һ���ٲ���!"),_T("��ʾ"),MB_ICONINFORMATION);
		return;  
	}

	CString name;
	name= m_listqx.GetItemText(m_nIndex,0);
	CString job;//////////////////��������Ա����ɾ��
    job=m_listqx.GetItemText(m_nIndex,1);
    if(job=="��������Ա")
	{
        MessageBox(_T("��������Ա����ɾ��..."),_T("û��Ȩ��"),MB_ICONINFORMATION);
        return;
	}
	if(MessageBox(_T("ȷ����?��ʹ���û�ɾ��..."),_T("�Ƿ�ȷ��?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
	_variant_t str;
	str="delete from �û�Ȩ�� where UserId='"+name+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	OnRefresh();

	
}

void QuanXian::OnClickListqx(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	POSITION pos=m_listqx.GetFirstSelectedItemPosition();
	m_nIndex = m_listqx.GetNextSelectedItem(pos);//�õ���Ŀ����
	
	*pResult = 0;
}


void QuanXian::OnRefresh()
{
	m_listqx.DeleteAllItems();///ɾ��������

	_variant_t str1="select * from �û�Ȩ��";
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

		Holder=theApp.m_pRecordset->GetCollect("ְ��");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,1,str);

        Holder=theApp.m_pRecordset->GetCollect("��ע");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,2,str);

		Holder=theApp.m_pRecordset->GetCollect("�ͷ�ϵͳ");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,3,str);

		Holder=theApp.m_pRecordset->GetCollect("��Ϣ��ѯ");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,4,str);

		Holder=theApp.m_pRecordset->GetCollect("��������");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,5,str);

		Holder=theApp.m_pRecordset->GetCollect("��������");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,6,str);

		Holder=theApp.m_pRecordset->GetCollect("ϵͳ����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listqx.SetItemText(i,7,str);

		theApp.m_pRecordset->MoveNext();
	}
}
