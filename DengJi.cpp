// DengJi.cpp : implementation file
//

#include "stdafx.h"
#include "Hotel.h"
#include "DengJi.h"
//#include "Kewuzhx.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// DengJi dialog


DengJi::DengJi(CWnd* pParent /*=NULL*/)
	: CDialog(DengJi::IDD, pParent)
{
	//{{AFX_DATA_INIT(DengJi)
	m_name = _T("");
	m_borndate = 0;
	m_home = _T("");
	m_beizhu = _T("");
	m_isvip = FALSE;
	m_realcost = _T("");
	m_id = _T("");
	m_cardnumber = _T("");
	m_time = COleDateTime::GetCurrentTime();
	m_payfirst = _T("");
	m_isclock = FALSE;
	//}}AFX_DATA_INIT
}


void DengJi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DengJi)
	DDX_Control(pDX, IDC_COMBO8, m_paytype);
	DDX_Control(pDX, IDC_COMBO7, m_zhekou);
	DDX_Control(pDX, IDC_COMBO6, m_cost);
	DDX_Control(pDX, IDC_COMBO5, m_roomtype);
	DDX_Control(pDX, IDC_COMBO4, m_roomid);
	DDX_Control(pDX, IDC_COMBO3, m_country);
	DDX_Control(pDX, IDC_COMBO2, m_sex);
	DDX_Control(pDX, IDC_COMBO1, m_cardtype);
	DDX_Text(pDX, IDC_EDIT5, m_name);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_borndate);
	DDX_Text(pDX, IDC_EDIT8, m_home);
	DDX_Text(pDX, IDC_EDIT9, m_beizhu);
	DDX_Check(pDX, IDC_CHECK1, m_isvip);
	DDX_Text(pDX, IDC_EDIT6, m_realcost);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT3, m_cardnumber);
	DDX_Text(pDX, IDC_EDIT10, m_time);
	DDX_Text(pDX, IDC_EDIT2, m_payfirst);
	DDX_Check(pDX, IDC_CHECK2, m_isclock);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DengJi, CDialog)
	//{{AFX_MSG_MAP(DengJi)
	ON_CBN_EDITCHANGE(IDC_COMBO4, OnChangeRoomId)
	ON_CBN_SETFOCUS(IDC_COMBO4, OnSetfocusRoomId)
	ON_CBN_SELENDOK(IDC_COMBO4, OnSelendokRoomId)
	ON_CBN_SELCHANGE(IDC_COMBO4, OnSelchangeRoomId)
	ON_CBN_SELCHANGE(IDC_COMBO7, OnSelchangeZheKou)
	ON_BN_CLICKED(IDC_CHECK2, OnCheckZhong)
	ON_BN_DOUBLECLICKED(IDC_CHECK2, OnDoubleclickedClock)
	ON_CBN_SELCHANGE(IDC_COMBO5, OnSelchangeRoomType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DengJi message handlers

void DengJi::OnOK() 
{
	// TODO: Add extra validation here

	CString roomid,roomtype,cost;
    GetDlgItemText(IDC_COMBO4,roomid);
    GetDlgItemText(IDC_COMBO5,roomtype);
    GetDlgItemText(IDC_COMBO6,cost);
    if(roomid==""||roomtype==""||cost=="")
	{
        AfxMessageBox(_T("��Ϣ������..."),MB_ICONINFORMATION);
        return;
	}

	if(!theApp.IsZhuan)
	{
	UpdateData();
	_variant_t str;
	CString date,sex,cardtype,country;
	GetDlgItemText(IDC_DATETIMEPICKER1,date);
	GetDlgItemText(IDC_COMBO2,sex);
    GetDlgItemText(IDC_COMBO1,cardtype);
    GetDlgItemText(IDC_COMBO3,country);
	char isvip,isclock;
	m_isvip? isvip='Y' :isvip='N';
	m_isclock? isclock='Y' :isclock='N';
	if(m_name==""||m_id=="")
	{
		AfxMessageBox(_T("��������Ϊ��!"),MB_ICONINFORMATION);
		return;
	}

	if(MessageBox(_T("ȷ���Ǽ���?"),_T("�Ƿ�ȷ��?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
	if(!theApp.isnewroom)//������ǿ���,�������ͻ���Ϣ����д���ظ�����Ϣ
	{
	str="insert into �ͻ���Ϣ(�����˺�,����,֤������,֤������,�Ա�,��������,����,IsVip,��ϸסַ,��ע)\
		values ("+m_id+",'"+m_name+"','"+cardtype+"','"+m_cardnumber+"',\
		'"+sex+"','"+date+"','"+country+"','"+isvip+"','"+m_home+"','"+m_beizhu+"')";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	}
//	theApp.m_pRecordset->Update();		
	CString roomid,roomtype,cost,zhekou,paytype;
	//m_timeΪֻ��!!!!!!!!!!!
	m_time.GetCurrentTime();
	CString time=m_time.Format(_T("%Y-%m-%d %H:%M:%S"));///???????????????????����ֱ�Ӳ���m_time
	GetDlgItemText(IDC_COMBO4,roomid);
    GetDlgItemText(IDC_COMBO5,roomtype);
    GetDlgItemText(IDC_COMBO6,cost);
	GetDlgItemText(IDC_COMBO7,zhekou);
	GetDlgItemText(IDC_COMBO8,paytype);
	str="insert into ס��(�����˺�,����,��ס����,�Ǽ�ʱ��,Ԥ�����,���ѷ�ʽ,ʵ��,�ӵ㷿)\
		values ("+m_id+",'"+m_name+"','"+roomid+"','"+time+"',\
		'"+m_payfirst+"','"+paytype+"','"+m_realcost+"','"+isclock+"')";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	m_id="";
	m_name="";
	m_cardnumber="";
	m_home="";
	m_beizhu="";
	UpdateData(false);
	str="update �ͷ� set �ͷ�״̬='��ס' where ����='"+roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	AfxMessageBox(_T("�ɹ��Ǽ�.."),MB_ICONINFORMATION);	
	}

	else////�����ת��ס
	{
	
	UpdateData();
	_variant_t str;
	CString date,sex,cardtype,country;
	GetDlgItemText(IDC_DATETIMEPICKER1,date);
	GetDlgItemText(IDC_COMBO2,sex);
    GetDlgItemText(IDC_COMBO1,cardtype);
    GetDlgItemText(IDC_COMBO3,country);
	char isvip,isclock;
	m_isvip? isvip='Y' :isvip='N';
	m_isclock? isclock='Y' :isclock='N';
	if(m_name==""||m_id=="")
	{
		AfxMessageBox(_T("��������Ϊ��!"),MB_ICONINFORMATION);
		return;
	}
	if(MessageBox(_T("ȷ���Ǽ���?"),_T("�Ƿ�ȷ��?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
	if(!theApp.isnewroom)//����Ǽӿ���,�������ͻ���Ϣ����д���ظ�����Ϣ
	{
	str="insert into �ͻ���Ϣ(�����˺�,����,֤������,֤������,�Ա�,��������,����,IsVip,��ϸסַ,��ע)\
		values ("+m_id+",'"+m_name+"','"+cardtype+"','"+m_cardnumber+"',\
		'"+sex+"','"+date+"','"+country+"','"+isvip+"','"+m_home+"','"+m_beizhu+"')";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	}		
	CString roomid,roomtype,cost,zhekou,paytype;
	//m_timeΪֻ��!!!!!!!!!!!
	m_time.GetCurrentTime();
	CString time=m_time.Format(_T("%Y-%m-%d %H:%M:%S"));///???????????????????����ֱ�Ӳ���m_time
	GetDlgItemText(IDC_COMBO4,roomid);
    GetDlgItemText(IDC_COMBO5,roomtype);
    GetDlgItemText(IDC_COMBO6,cost);
	GetDlgItemText(IDC_COMBO7,zhekou);
	GetDlgItemText(IDC_COMBO8,paytype);
	str="insert into ס��(�����˺�,����,��ס����,�Ǽ�ʱ��,Ԥ�����,���ѷ�ʽ,ʵ��,�ӵ㷿)\
		values ("+m_id+",'"+m_name+"','"+roomid+"','"+time+"',\
		'"+m_payfirst+"','"+paytype+"','"+m_realcost+"','"+isclock+"')";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	m_id="";
	m_name="";
	m_cardnumber="";
	m_home="";
	m_beizhu="";
	UpdateData(false);
	str="update �ͷ� set �ͷ�״̬='��ס' where ����='"+roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	MessageBox(_T("�ɹ�ת��ס..."),_T("�����ɹ�!"),MB_ICONINFORMATION);	
	///////��Ԥ������Ϊ��Ч
	str="update Ԥ�� set ״̬='��Ч' where ��������='"+roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	}
	CDialog::OnOK();
}

BOOL DengJi::OnInitDialog() 
{
	InitCommonControls();
	CDialog::OnInitDialog();
//	theApp.IsZhuan=false;
	
	// TODO: Add extra initialization here
	_variant_t str;
	//��ʼ�������roomid
	str="select * from �ͷ� where �ͷ�״̬='��'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	while(!theApp.m_pRecordset->EndOfFile)
	{
		m_roomid.AddString((wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("����"));
		theApp.m_pRecordset->MoveNext();
	}

	str="select distinct �ͷ����� from �ͷ�";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	//��ʼ����������roomtype
	theApp.m_pRecordset->MoveFirst();
	while(!theApp.m_pRecordset->EndOfFile)
	{
		m_roomtype.AddString((wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("�ͷ�����"));
		theApp.m_pRecordset->MoveNext();
	}
	//��ʼ�����䵥��cost
	str="select distinct ���� from �ͷ�";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	while(!theApp.m_pRecordset->EndOfFile)
	{
		m_cost.AddString((wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("����"));
		theApp.m_pRecordset->MoveNext();
	}
	//��ʼ��֤������cardtype
	m_cardtype.AddString(_T("���֤"));
	m_cardtype.AddString(_T("ѧ��֤"));
	m_cardtype.AddString(_T("����֤"));
	m_cardtype.AddString(_T("��ʻ֤"));
	m_cardtype.AddString(_T("����"));
	//��ʼ���Ա�sex
	m_sex.AddString(_T("��"));
	m_sex.AddString(_T("Ů"));
	//��ʼ������country
	m_country.AddString(_T("�л����񹲺͹�"));
	m_country.AddString(_T("����"));
	m_country.AddString(_T("����"));
	m_country.AddString(_T("Ӣ��"));
	m_country.AddString(_T("�¹�"));
	m_country.AddString(_T("�ձ�"));
	m_country.AddString(_T("����˹"));
	//��ʼ���Ż��ۿ�zhekou
	m_zhekou.AddString(_T("������"));
	m_zhekou.AddString(_T("95%100"));
	m_zhekou.AddString(_T("90%100"));
	m_zhekou.AddString(_T("85%100"));
	m_zhekou.AddString(_T("80%100"));
	m_zhekou.AddString(_T("75%100"));
	m_zhekou.AddString(_T("70%100"));
	m_zhekou.AddString(_T("65%100"));
	m_zhekou.AddString(_T("60%100"));
	m_zhekou.AddString(_T("55%100"));
	m_zhekou.AddString(_T("50%100"));
	m_zhekou.AddString(_T("���"));
	//��ʼ�����ѷ�ʽpaytype
	m_paytype.AddString(_T("�ֽ�"));
	m_paytype.AddString(_T("֧Ʊ"));
	m_paytype.AddString(_T("���ÿ�"));

//	m_intime.GetCurrentTime();
//	m_intime.Format(_T("%Y%m%d"));//???????????
	m_isclock=false;
	CString caozuoyuan=theApp.m_sCurrentUser;
	SetDlgItemText(IDC_STATIC_Operator,caozuoyuan);


	//��ʼ���ͻ��˺�
	if(theApp.isnewroom==false)
	{	
	CString IdOfCustomer;
	CTime time;
	time=CTime::GetCurrentTime();
	IdOfCustomer=time.Format("%Y%m%d%H%M%S");
	SetDlgItemText(IDC_EDIT1,IdOfCustomer);
	}




//ת��סʱ��ʼ��
	if(theApp.IsZhuan)
	{
	str="select * from Ԥ�� where Ԥ����='"+m_name+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	CString cardtype=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("֤������");
	SetDlgItemText(IDC_COMBO1,cardtype);
//	CString sex=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("֤������");
	SetDlgItemText(IDC_COMBO2,_T("��"));
	SetDlgItemText(IDC_COMBO3,_T("�л����񹲺͹�"));
	CString room=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("��������");
	SetDlgItemText(IDC_COMBO4,room);
	}
	//�ӿ���ʱ��ʼ��
	if(theApp.isnewroom)
	{
		str="select * from �ͻ���Ϣ where �����˺�='"+m_id+"'";
		theApp.ADOExecute(theApp.m_pRecordset,str);
		CString isvip=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("IsVip");
		if(isvip=="Y")
		{
			m_isvip=true;
			UpdateData(FALSE);
		}
		else
		{
			m_isvip=false;
			UpdateData(FALSE);
		}
		CString cardtype=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("֤������");
	    SetDlgItemText(IDC_COMBO1,cardtype);
		CString country=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("����");
    	
		CString sex=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("�Ա�");
	    SetDlgItemText(IDC_COMBO3,country);
		SetDlgItemText(IDC_COMBO2,sex);
		CString cardid=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("֤������");
		SetDlgItemText(IDC_EDIT3,cardid);
		CString zhuzhi=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("��ϸסַ");
		SetDlgItemText(IDC_EDIT8,zhuzhi);
		CString beizhu=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("��ע");
        SetDlgItemText(IDC_EDIT9,beizhu);
	}
	 //   CString room=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("��������");
	  //  SetDlgItemText(IDC_COMBO4,room);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}







void DengJi::OnChangeRoomId() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL DengJi::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	theApp.IsZhuan=false;
	
	return CDialog::DestroyWindow();
}

void DengJi::OnSetfocusRoomId() 
{
	// TODO: Add your control notification handler code here

	
}

void DengJi::OnSelendokRoomId() 
{
	// TODO: Add your control notification handler code here

	
}

void DengJi::OnSelchangeRoomId() 
{
	// TODO: Add your control notification handler code here

	_variant_t str;
	CString roomid;
	int i=m_roomid.GetCurSel();
	m_roomid.GetLBText(i,roomid);

	str="select * from �ͷ� where ����='"+roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	_variant_t str1=theApp.m_pRecordset->GetCollect("�ͷ�����");
	//str
	SetDlgItemText(IDC_COMBO5,(wchar_t*)(_bstr_t)str1);
	_variant_t str2=theApp.m_pRecordset->GetCollect("����");
	SetDlgItemText(IDC_COMBO6,(wchar_t*)(_bstr_t)str2);

	if(m_isclock)
	{
		float clockvalue=theApp.m_pRecordset->GetCollect("�ӵ㷿��");
		CString clockvaluestr;
       	clockvaluestr.Format(_T("%.2f"),clockvalue);
	    SetDlgItemText(IDC_COMBO6,clockvaluestr);
	}	

	
}

void DengJi::OnSelchangeZheKou() 
{
	// TODO: Add your control notification handler code here
	int i=m_zhekou.GetCurSel();
	CString zhekou;
//	m_zhekou.GetLBText(i,zhekou);
	CString cost,roomid;
	GetDlgItemText(IDC_COMBO6,cost);
	GetDlgItemText(IDC_COMBO4,roomid);
	if(cost=="")
		return;

	_variant_t str;
	str="select * from �ͷ� where ����='"+roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	if(!m_isclock)
	{
	double danjia=theApp.m_pRecordset->GetCollect("����");//������ԭ��

	CString danjia1;//�ַ���ԭ��
	double realcost;//�������ۺ��

	switch(i)
	{
		
		
	case 1:		
		realcost=danjia*0.5;
	    danjia1.Format(_T("%.2f"),realcost);//���㵽�ַ���
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 2:
    	realcost=danjia*0.55;
		danjia1.Format(_T("%.2f"),realcost);//���㵽�ַ���
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 3:
		realcost=danjia*0.6;
		danjia1.Format(_T("%.2f"),realcost);//���㵽�ַ���
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 4:
		realcost=danjia*0.65;
		danjia1.Format(_T("%.2f"),realcost);//���㵽�ַ���
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 5:

		realcost=danjia*0.7;
		danjia1.Format(_T("%.2f"),realcost);//���㵽�ַ���
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 6:

		realcost=danjia*0.75;
		danjia1.Format(_T("%.2f"),realcost);//���㵽�ַ���
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 7:

		realcost=danjia*0.8;
		danjia1.Format(_T("%.2f"),realcost);//���㵽�ַ���
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 8:
		realcost=danjia*0.85;
		danjia1.Format(_T("%.2f"),realcost);//���㵽�ַ���
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 9:
		realcost=danjia*0.9;
		danjia1.Format(_T("%.2f"),realcost);//���㵽�ַ���
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 10:
		realcost=danjia*0.95;
		danjia1.Format(_T("%.2f"),realcost);//���㵽�ַ���
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 11:
		realcost=danjia*0.00;
		danjia1.Format(_T("%.2f"),realcost);//���㵽�ַ���
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	case 12:
		realcost=danjia*1.00;
		danjia1.Format(_T("%.2f"),realcost);//���㵽�ַ���
		SetDlgItemText(IDC_EDIT6,danjia1);
		break;
	}
	}
	
}

void DengJi::OnCheckZhong() 
{
	// TODO: Add your control notification handler code here
	//UpdateData();
	m_isclock=!m_isclock;
	CString roomid;
	GetDlgItemText(IDC_COMBO4,roomid);
	if(roomid=="")
		return;
	_variant_t str;
	str="select * from �ͷ� where ����='"+roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	float clockvalue=theApp.m_pRecordset->GetCollect("�ӵ㷿��");
	CString clockvaluestr;
	clockvaluestr.Format(_T("%.2f"),clockvalue);
	SetDlgItemText(IDC_COMBO6,clockvaluestr);
    if(m_isclock==false)
	{
		float value=theApp.m_pRecordset->GetCollect("����");
		CString valuestr;
	    valuestr.Format(_T("%.1f"),value);
	    SetDlgItemText(IDC_COMBO6,valuestr);
		CString valueofclockroomstr;
		GetDlgItemText(IDC_COMBO6,valueofclockroomstr);
		SetDlgItemText(IDC_EDIT6,valueofclockroomstr);
	}
	else
	{
		CString valueofclockroom;
		GetDlgItemText(IDC_COMBO6,valueofclockroom);
		SetDlgItemText(IDC_COMBO7,_T(""));
		SetDlgItemText(IDC_EDIT6,valueofclockroom);
	}


	
	
}

void DengJi::OnDoubleclickedClock() 
{
	// TODO: Add your control notification handler code here
	
}

void DengJi::OnSelchangeRoomType() 
{
	// TODO: Add your control notification handler code here

	_variant_t str;
	CString roomtype;
	int i=m_roomtype.GetCurSel();
	m_roomtype.GetLBText(i,roomtype);


	m_roomid.ResetContent();//ɾ����Ͽ���б��ͱ༭�ؼ��е������� 

	str="select * from �ͷ� where �ͷ�.�ͷ�����='"+roomtype+"' and �ͷ�״̬='��'";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	while(!theApp.m_pRecordset->EndOfFile)
	{
		m_roomid.AddString((wchar_t*)(_bstr_t)(theApp.m_pRecordset->GetCollect("����")));
		theApp.m_pRecordset->MoveNext();
	}

	m_cost.ResetContent();
//	CString danjia=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("����");
//	SetDlgItemText(IDC_COMBO6,danjia);	
}

void DengJi::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnOK();
}
