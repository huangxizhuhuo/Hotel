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

	m_nIndex=-1;//��ʼ��!!!!!!!!!!!!!
	CString DengJiYuan=theApp.m_sCurrentUser;
	SetDlgItemText(IDC_STATIC_Operator1,DengJiYuan);
	
	// TODO: Add extra initialization here

	m_customtype.AddString(_T("ɢ��"));
	m_customtype.AddString(_T("�Ŷ�"));
	m_customtype.AddString(_T("�ڲ�"));

	//��ʼ��֤������cardtype
	m_cardtype.AddString(_T("���֤"));
	m_cardtype.AddString(_T("ѧ��֤"));
	m_cardtype.AddString(_T("����֤"));
	m_cardtype.AddString(_T("��ʻ֤"));
	m_cardtype.AddString(_T("����"));

	m_roomtype.AddString(_T("��׼���˷�"));
	m_roomtype.AddString(_T("��׼˫�˷�"));
	m_roomtype.AddString(_T("�������˷�"));
	m_roomtype.AddString(_T("����˫�˷�"));
	m_roomtype.AddString(_T("�߼��׷�"));

	_variant_t str1;
	//��ʼ�������roomid
	str1="select * from �ͷ� where �ͷ�״̬='��'";
	theApp.ADOExecute(theApp.m_pRecordset,str1);

	while(!theApp.m_pRecordset->EndOfFile)
	{
		m_reservedroom.AddString((wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("����"));
		theApp.m_pRecordset->MoveNext();
	}

	m_listyd.SetBkColor(RGB(177,151,240));
	m_listyd.SetTextColor(RGB(0,0,0));
	m_listyd.SetTextBkColor(RGB(177,151,240));
	m_listyd.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);

	int nWidth=80;
	m_listyd.InsertColumn(0,_T("�Ƶ�ʱ��"),LVCFMT_LEFT,120);
	m_listyd.InsertColumn(1,_T("Ԥ����"),LVCFMT_LEFT,60);
	m_listyd.InsertColumn(2,_T("֤������"),LVCFMT_LEFT,80);
	m_listyd.InsertColumn(3,_T("֤������"),LVCFMT_LEFT,80);
	m_listyd.InsertColumn(4,_T("Ԥ�����ʱ��"),LVCFMT_LEFT,120);
	m_listyd.InsertColumn(5,_T("��ϵ�绰"),LVCFMT_LEFT,nWidth);
	m_listyd.InsertColumn(6,_T("Ԥ������"),LVCFMT_LEFT,nWidth);
	m_listyd.InsertColumn(7,_T("����"),LVCFMT_LEFT,60);
	m_listyd.InsertColumn(8,_T("��������"),LVCFMT_LEFT,80);
		
	_variant_t Holder;
	_variant_t strQuery;
	strQuery="select * from Ԥ�� where ״̬='��Ч'";//����ʾ��Ч�Ķ���!!!!!
	theApp.ADOExecute(theApp.m_pRecordset,strQuery);
    int iCount=theApp.m_pRecordset->GetRecordCount();
	if(0==iCount)
		return FALSE;
	CString str;
	theApp.m_pRecordset->MoveFirst();

	for(int i=0;i<iCount;i++)
//	if(theApp.m_pRecordset!=EndOfFile)
	{
		Holder=theApp.m_pRecordset->GetCollect("�Ƶ�ʱ��");
    	str=(Holder.vt==VT_NULL)?"":(char *)(_bstr_t)Holder;
    	m_listyd.InsertItem(i,str);

		Holder=theApp.m_pRecordset->GetCollect("Ԥ����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listyd.SetItemText(i,1,str);

    	Holder=theApp.m_pRecordset->GetCollect("֤������");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listyd.SetItemText(i,2,str);

		Holder=theApp.m_pRecordset->GetCollect("֤������");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listyd.SetItemText(i,3,str);

        Holder=theApp.m_pRecordset->GetCollect("Ԥ�����ʱ��");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listyd.SetItemText(i,4,str);

        Holder=theApp.m_pRecordset->GetCollect("��ϵ�绰");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listyd.SetItemText(i,5,str);

		Holder=theApp.m_pRecordset->GetCollect("Ԥ������");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listyd.SetItemText(i,6,str);

		Holder=theApp.m_pRecordset->GetCollect("����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listyd.SetItemText(i,7,str);

		Holder=theApp.m_pRecordset->GetCollect("��������");
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

//	m_customtype="ɢ��";
//	m_cardtype="���֤";
//	m_roomtype="��׼���˼�";
//	CTime curtime;
//	CTime time=curtime.GetCurrentTime();

	SetDlgItemText(IDC_COMBO1,_T("ɢ��"));
	SetDlgItemText(IDC_COMBO2,_T("���֤"));
	SetDlgItemText(IDC_COMBO3,_T("��׼���˷�"));
	m_timeofmakelist.GetCurrentTime();
	m_timeofmakelist.Format(_T("%Y-%m-%d %H:%M:%S"));
	CString roomtype;
	GetDlgItemText(IDC_COMBO3,roomtype);

//	CTime now=CTime::GetCurrentTime(); 
//	CString strNowTime;
//  strNowTime=now.Format(_T("%Y��%m��%d��%Hʱ%M��%S��"));	
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
		AfxMessageBox(_T("Ԥ���˻�֤���Ų���Ϊ��..."),MB_ICONINFORMATION);
		return;
	}

	if(m_preintime>m_preleavetime)
	{
		AfxMessageBox(_T("ʱ�����.."),MB_ICONINFORMATION);
		return;
	}

	if(MessageBox(_T("ȷ��������?"),_T("�Ƿ�ȷ��?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
	timeofmakelist=m_timeofmakelist.Format(_T("%Y-%m-%d %H:%M:%S"));
	preleavetime=m_preleavetime.Format(_T("%Y-%m-%d %H:%M:%S"));
	preintime=m_preintime.Format(_T("%Y-%m-%d %H:%M:%S"));

	str="insert into Ԥ��(�Ƶ�ʱ��,Ԥ����,��������,֤������,֤������,Ԥ�����ʱ��,Ԥ�����ʱ��,��ϵ�绰,Ԥ������,����,��������)\
		values ('"+timeofmakelist+"','"+m_name+"','"+customtype+"','"+cardtype+"','"+m_cardnumber+"','"+preintime+"',\
		'"+preleavetime+"','"+m_phonenumber+"','"+roomtype+"','"+m_number+"','"+reservedroom+"')";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	str="update �ͷ� set �ͷ�״̬='����' where ����='"+reservedroom+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	AfxMessageBox(_T("�ɹ�Ԥ��.."),MB_ICONINFORMATION);


	//�������
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
	if (m_nIndex == -1)	  //���û��ѡ��ͷ���
	{
		MessageBox(_T("��ѡ������б���һ���ٲ���!"),_T("��ʾ"),MB_ICONINFORMATION);
		return;  
	}

	CString name;
	name= m_listyd.GetItemText(m_nIndex,1);
	if(MessageBox(_T("ȷ����?��ʹ��Ԥ��������..."),_T("�Ƿ�ȷ��?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
	
	_variant_t str;
	str="update Ԥ�� set ״̬='��Ч' where Ԥ����='"+name+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	//ͬʱӦ����̬�ӱ�����Ϊ��!!!!!!!!!!!!!!!!!!!!!!
	CString reservedroom;
	GetDlgItemText(IDC_COMBO4,reservedroom);
	str="update �ͷ� set �ͷ�״̬='��' where ����='"+reservedroom+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	
}



void YuDing::OnClickListYd(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	
	POSITION pos = m_listyd.GetFirstSelectedItemPosition();
	m_nIndex = m_listyd.GetNextSelectedItem(pos);  // �õ���Ŀ����
	
	*pResult = 0;
}

void YuDing::OnShanChu() 
{
	// TODO: Add your control notification handler code here

	m_listyd.SetFocus();
	if (m_nIndex == -1)	  //���û��ѡ��ͷ���
	{
		MessageBox(_T("��ѡ������б���һ���ٲ���!"),_T("��ʾ"),MB_ICONINFORMATION);
		return;  
	}

	CString name;
	name= m_listyd.GetItemText(m_nIndex,1);
	if(MessageBox(_T("ȷ����?��ʹ��Ԥ��������ɾ��..."),_T("�Ƿ�ȷ��?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
	
	_variant_t str;
	str="delete from Ԥ�� where Ԥ����='"+name+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	//ͬʱӦ����̬�ӱ�����Ϊ��!!!!!!!!!!!!!!!!!!!!!!
	CString reservedroom;
	GetDlgItemText(IDC_COMBO4,reservedroom);
	str="update �ͷ� set �ͷ�״̬='��' where ����='"+reservedroom+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	
}

void YuDing::OnZhuanRuZhu() 
{
	// TODO: Add your control notification handler code here
	theApp.IsZhuan=true;

	m_listyd.SetFocus();
	if (m_nIndex == -1)	  //���û��ѡ��ͷ���
	{
		MessageBox(_T("��ѡ������б���һ���ٲ���!"),_T("��ʾ"),MB_ICONINFORMATION);
		return;  
	}
	CString roomid=m_listyd.GetItemText(m_nIndex,8);

	//�ñ�������Ϊ��!!!!!!!!!!!!!!!!!!!!!!!!!!ת��ס�Ǽ��������ȡ��
	if(MessageBox(_T("ȷ��Ԥ���ͻ���ת��ס��?���ȷ�����ı�ñ�����̬"),_T("�Ƿ�ȷ��?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
	///�ñ�����Ϊ��
	_variant_t str;
	str="update �ͷ� set �ͷ�״̬='��' where ����='"+roomid+"'";
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
