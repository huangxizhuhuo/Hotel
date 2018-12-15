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
	str="select * from �ͷ� where �ͷ�״̬='��ס'";///������ס�����뵽�ɷ���ComboBox
	theApp.ADOExecute(theApp.m_pRecordset,str);

	while(!theApp.m_pRecordset->EndOfFile)
	{
		m_roomid.AddString((wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("����"));
		theApp.m_pRecordset->MoveNext();
	}

//	theApp.m_pRecordset->MoveFirst();
	str="select * from �ͷ� where �ͷ�״̬='��'";////���пշ����뵽�·���ComboBox
	theApp.ADOExecute(theApp.m_pRecordset,str);

	while(!theApp.m_pRecordset->EndOfFile)
	{
		m_changeroomid.AddString((wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("����"));
		theApp.m_pRecordset->MoveNext();
	}

	str="select distinct �ͷ����� from �ͷ�";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	while(!theApp.m_pRecordset->EndOfFile)
	{
		m_changetotype.AddString((wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("�ͷ�����"));
		theApp.m_pRecordset->MoveNext();
	}

	m_isclockroom=false;
	CString dengjiyuan=theApp.m_sCurrentUser;
	SetDlgItemText(IDC_STATIC_DENGJIYUAN,"�Ǽ�Ա  "+dengjiyuan);

	
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

	str="select * from �ͷ�,ס�� where �ͷ�.����='"+roomid+"'and ס��.��ס����='"+roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	CString str3=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("�ӵ㷿");

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

	_variant_t str1=theApp.m_pRecordset->GetCollect("�ͷ�����");
	SetDlgItemText(IDC_EDIT5,(wchar_t*)(_bstr_t)str1);

	_variant_t str2=theApp.m_pRecordset->GetCollect("����");
	SetDlgItemText(IDC_EDIT6,(wchar_t*)(_bstr_t)str2);

	

	CString str4=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("�Ǽ�ʱ��");
	SetDlgItemText(IDC_EDIT9,str4);	
	SetDlgItemText(IDC_STATIC_INTIME,"�Ǽ�ʱ��  "+str4);

	CString str5=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("�����˺�");
	SetDlgItemText(IDC_STATIC_LISTID,str5);

	CString str6=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("����");
	SetDlgItemText(IDC_EDIT11,str6);

	CString str7=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("Ԥ�����");
	SetDlgItemText(IDC_EDIT10,str7);

	UpdateData();
	if(m_isclockroom==false)//�����ӵ㷿
	{
	COleDateTime curtime=COleDateTime::GetCurrentTime();	
	float dayoflive=curtime-m_intime;
	float deltaday(dayoflive-int(dayoflive));
	if(deltaday<=0.5)
		dayoflive=int(dayoflive)+0.5f;//�����
	else
		dayoflive=int(dayoflive)+1.0f;//��һ��	
	double realcost=theApp.m_pRecordset->GetCollect("ʵ��");
	double costatlast=dayoflive*realcost;
	CString costatlaststr;
	costatlaststr.Format(_T("%.2f"),costatlast);
	SetDlgItemText(IDC_EDIT8,costatlaststr);

	CString day;
	day.Format(_T("%.1f"),dayoflive);
	CString beizhu="��ס"+day+"��";
	SetDlgItemText(IDC_EDIT13,beizhu);

	}
	else
	{
	COleDateTime curtime=COleDateTime::GetCurrentTime();	
	float dayoflive=curtime-m_intime;
	float deltaday(dayoflive-int(dayoflive));
	float deltahour=deltaday*24;
	dayoflive=int(deltahour+0.5f);
	double realcost=theApp.m_pRecordset->GetCollect("ʵ��");
	double costatlast=dayoflive*realcost;
	CString costatlaststr;
	costatlaststr.Format(_T("%.2f"),costatlast);
	SetDlgItemText(IDC_EDIT8,costatlaststr);
    
	CString day;
	day.Format(_T("%.1f"),dayoflive);
	CString beizhu="��ס"+day+"Сʱ";
	SetDlgItemText(IDC_EDIT13,beizhu);
	}

	//�ۿ�
	float shijia=theApp.m_pRecordset->GetCollect("ʵ��");
	float yuanjia=theApp.m_pRecordset->GetCollect("����");
//	float zhekou=shijia/yuanjia;
	float zhekou=float(shijia)/float(yuanjia);
	CString zhekoustr;
	zhekoustr.Format(_T("%.2f"),zhekou);
	SetDlgItemText(IDC_EDIT12,zhekoustr);
	
//	double precost=theApp.m_pRecordset->GetCollect("Ԥ�����");
//	CString str8=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("�Ǽ�ʱ��");
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

	str="select * from �ͷ� where �ͷ�.�ͷ�����='"+roomtype+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	CString danjiastr=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("����");
	SetDlgItemText(IDC_EDIT15,danjiastr);

	m_changeroomid.ResetContent();//ɾ����Ͽ���б��ͱ༭�ؼ��е������� 

	str="select * from �ͷ� where �ͷ�.�ͷ�����='"+roomtype+"' and �ͷ�״̬='��'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	while(!theApp.m_pRecordset->EndOfFile)
	{
		m_changeroomid.AddString((wchar_t*)(_bstr_t)(theApp.m_pRecordset->GetCollect("����")));
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

	str="select * from �ͷ� where ����='"+roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	_variant_t str1=theApp.m_pRecordset->GetCollect("�ͷ�����");
	SetDlgItemText(IDC_COMBO2,(wchar_t*)(_bstr_t)str1);
	_variant_t str2=theApp.m_pRecordset->GetCollect("����");
	SetDlgItemText(IDC_EDIT15,(wchar_t*)(_bstr_t)str2);
/*
	if(m_isclock)
	{
		float clockvalue=theApp.m_pRecordset->GetCollect("�ӵ㷿��");
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
	//��׶�������޸�ԭ��(�෿)���(��ס)��״̬������ס�������ס���ţ��Ǽ�ʱ�䣬ʵ���Լ��ӵ㷿��
    //���ڻ������ʵ�ۣ�Ӧ��ԭ�ۿ�*�񷿼ۣ���������������������������������
	_variant_t str;
	CString roomid;
	GetDlgItemText(IDC_COMBO4,roomid);
	CString intime=m_intime.Format(_T("%Y-%m-%d %H:%M:%S"));
	CString curtime=m_curtime.Format(_T("%Y-%m-%d %H:%M:%S"));
	CString newroom;
	GetDlgItemText(IDC_COMBO3,newroom);

	if(roomid==""||intime==""||curtime==""||newroom=="")
	{
		AfxMessageBox(_T("��������������Ϣ..."),MB_ICONINFORMATION);
		return;
	}

	if(MessageBox(_T("ȷ��������?"),_T("�Ƿ�ȷ��?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
	////Ӧ���ж����ʱ�������̣����ܻ�������Ӧȡ������������������������

	str="insert into �׶�����(�ͻ��˺�,��������,�Ǽ�����,�׶�ʱ��,ԭס��,���ѽ��,��ס��)\
		values('"+m_customerid+"','"+m_name+"','"+intime+"','"+curtime+"','"+roomid+"','"+m_shouldpay+"','"+newroom+"')";

	theApp.ADOExecute(theApp.m_pRecordset,str);

	str="update �ͷ� set �ͷ�״̬='�෿' where ����='"+roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	str="update �ͷ� set �ͷ�״̬='��ס' where ����='"+newroom+"'";
    theApp.ADOExecute(theApp.m_pRecordset,str);

	CString isclock;
	m_isclockroom? isclock='Y': isclock='N';

	str="update ס�� set ��ס����='"+newroom+"',\
		                 �Ǽ�ʱ��='"+curtime+"',\
						 ʵ��='"+m_newcost+"',\
						 �ӵ㷿='"+isclock+"' where �����˺�='"+m_customerid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	CDialog::OnOK();
	
}
