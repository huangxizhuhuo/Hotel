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
	m_paytype.AddString(_T("�ֽ�"));
	m_paytype.AddString(_T("֧Ʊ"));
	m_paytype.AddString(_T("ǩ��"));

	CString DengJiYuan=theApp.m_sCurrentUser;
	SetDlgItemText(IDC_STATIC_Operator2,DengJiYuan);

	m_listzf.SetBkColor(RGB(177,151,240));
	m_listzf.SetTextColor(RGB(0,0,0));
	m_listzf.SetTextBkColor(RGB(177,151,240));
	m_listzf.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);

	int nWidth=100;
	m_listzf.InsertColumn(0,_T("���˱��"),LVCFMT_LEFT,130);
	m_listzf.InsertColumn(1,_T("����"),LVCFMT_LEFT,nWidth);
	m_listzf.InsertColumn(2,_T("��ס����"),LVCFMT_LEFT,60);
	m_listzf.InsertColumn(3,_T("�Ǽ�ʱ��"),LVCFMT_LEFT,130);
	m_listzf.InsertColumn(4,_T("Ԥ�����"),LVCFMT_LEFT,nWidth);
	m_listzf.InsertColumn(5,_T("���ѷ�ʽ"),LVCFMT_LEFT,nWidth);
	m_listzf.InsertColumn(6,_T("ʵ��"),LVCFMT_LEFT,nWidth);

		
	_variant_t Holder;
	_variant_t strQuery;
	strQuery="select * from ס��";
	theApp.ADOExecute(theApp.m_pRecordset,strQuery);
    int iCount=theApp.m_pRecordset->GetRecordCount();
	if(0==iCount)
		return FALSE;
	CString str;
	theApp.m_pRecordset->MoveFirst();

	for(int i=0;i<iCount;i++)
	{
		Holder=theApp.m_pRecordset->GetCollect("�����˺�");
    	str=(Holder.vt==VT_NULL)?"":(char *)(_bstr_t)Holder;
    	m_listzf.InsertItem(i,str);

		Holder=theApp.m_pRecordset->GetCollect("����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listzf.SetItemText(i,1,str);

        Holder=theApp.m_pRecordset->GetCollect("��ס����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listzf.SetItemText(i,2,str);

        Holder=theApp.m_pRecordset->GetCollect("�Ǽ�ʱ��");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listzf.SetItemText(i,3,str);

		Holder=theApp.m_pRecordset->GetCollect("Ԥ�����");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listzf.SetItemText(i,4,str);

		Holder=theApp.m_pRecordset->GetCollect("���ѷ�ʽ");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listzf.SetItemText(i,5,str);

		Holder=theApp.m_pRecordset->GetCollect("ʵ��");
		str=Holder.vt==VT_NULL?"":(char *)(_bstr_t)Holder;
		m_listzf.SetItemText(i,6,str);


		theApp.m_pRecordset->MoveNext();
	}
	
	return TRUE;// return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}




void JieZhang::OnDblclkListzf(NMHDR* pNMHDR, LRESULT* pResult)//˫���б����¼� 
{
	// TODO: Add your control notification handler code here
	POSITION pos=m_listzf.GetFirstSelectedItemPosition();
	m_nIndex = m_listzf.GetNextSelectedItem(pos);//�õ���Ŀ����


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
		AfxMessageBox(_T("������Ϣ������.."),MB_ICONINFORMATION);
		return;
	}

	if(m_paylast=="")
	{
		AfxMessageBox(_T("�����ܶ��Ϊ��..."),MB_ICONINFORMATION);
		return;
	}
/*	if(m_intime>curtime)
	{
		AfxMessageBox("��ǰʱ�����..",MB_ICONINFORMATION);
		return;
	}*/

	if(MessageBox(_T("ȷ��������?"),_T("�Ƿ�ȷ��?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;

	//�����������ϸ�������Ϣ

	str="insert into ������ϸ(����ʱ��,�����˺�,��������,�Ǽ�ʱ��,��ס����,Ӧ���˿�,�Ѹ��˿�,�տʽ,�����տ�,����,��ע)\
		values ('"+curtime+"','"+m_id+"','"+m_name+"','"+m_intime+"','"+m_roomid+"','"+m_shouldpay+"','"+m_payfirst+"','"+paytype+"','"+m_paylast+"','"+m_small+"','"+m_beizhu+"')";
	theApp.ADOExecute(theApp.m_pRecordset,str);//ע���������͵�ͳһ(�����ݿ�)

	//ɾ��ס���������Ϣ


	str="delete from ס�� where �����˺�='"+m_id+"'and ��ס����='"+m_roomid+"'";//�����˺���������Ϊ�ı�***
	theApp.ADOExecute(theApp.m_pRecordset,str);///���һ���˺Ŷ�Ӧ�������

	//�������ʷ����������Ϣ, �ô������ܶ��д��޸�
	str="select * from ������ϸ where �����˺�='"+m_id+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	float payatlast=theApp.m_pRecordset->GetCollect("�����տ�");
	float havepay=theApp.m_pRecordset->GetCollect("�Ѹ��˿�");
	float yuling=theApp.m_pRecordset->GetCollect("����");
	float jiezhangzonge=payatlast+havepay-yuling;
	CString jiezhangstr;
	jiezhangstr.Format(_T("%.2f"),jiezhangzonge);
	str="insert into ��ʷ����(����ʱ��,�����˺�,��������,��ס��,�����ܶ�,�Ǽ�ʱ��)\
         values ('"+curtime+"','"+m_id+"','"+m_name+"','"+m_roomid+"','"+jiezhangstr+"','"+m_intime+"')";
	theApp.ADOExecute(theApp.m_pRecordset,str);

	//���˺�Ӧɾ���׶�������������
	str="delete * from �׶����� where �ͻ��˺�='"+m_id+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);/////Ӧ���������ɨ��׶��������

	//���ͷ���ͷ�״̬��Ϊ�෿

	str="update �ͷ� set �ͷ�״̬='�෿' where ����='"+m_roomid+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);


	
	CDialog::OnOK();
}
//���˵ĸ����ԣ�
//1.����Ҫ���ǵ�ǰס������֮ǰ���������ѣ�����ֻ���ǻ�һ�η�������2�����ϣ�
//����ۼ��Ǹ����⣩
//2.�ۿ��Ե�һ�εǼ�Ϊ׼
//3.���˿��ܼӿ������������Ƕ����ģ���ÿ�ν��˽�����1��һ���˺ż�һ�����䣨��֮ǰ������
//����һ�����ѣ����ǿ���Ҫ�ϲ��˵���һ����ˣ���һ����δ��
//4.�ӵ㷿δ���Ǵ�������
void JieZhang::OnSetfocusCostofall()//������Ӧ���˿�༭��
{
	// TODO: Add your control notification handler code here

	CString intime,leavetime;
	GetDlgItemText(IDC_EDIT10,intime);
	GetDlgItemText(IDC_EDIT9,leavetime);
	if(m_id==""||m_name==""||m_roomid==""||m_payfirst==""||intime==""||leavetime=="")
		return;
	_variant_t str;
	str="select * from ס�� where �����˺�='"+m_id+"' and ��ס����='"+m_roomid+"'";//ֻ���˺źͷ��Ų��ܾ���һ������
	theApp.ADOExecute(theApp.m_pRecordset,str);
//	UpdateData();
	double realcost=theApp.m_pRecordset->GetCollect("ʵ��");

	
	float dayoflive=m_curtime-theApp.m_pRecordset->GetCollect("�Ǽ�ʱ��");//�붨��Ϊ������
	CString day;
	float deltaday(dayoflive-int(dayoflive));
	CString isclockroom=(wchar_t*)(_bstr_t)theApp.m_pRecordset->GetCollect("�ӵ㷿");
	if(isclockroom=="N")////==VS=
	{
	if(deltaday<=0.5)
		dayoflive=int(dayoflive)+0.5;//�����
	else
		dayoflive=int(dayoflive)+1;//��һ��

	double costatleast=dayoflive*realcost;////////////////////////
	double precost=theApp.m_pRecordset->GetCollect("Ԥ�����");
	

	////��ѯ�׶���������ͻ�����������Ӧ�����������ۼ����˴���Ӧ���˿�
	str="select * from �׶����� where �ͻ��˺�='"+m_id+"' and ��ס��='"+m_roomid+"'";///����ǰ�뻻���������ϼ�
	theApp.ADOExecute(theApp.m_pRecordset,str);
	int iCount=theApp.m_pRecordset->GetRecordCount();////////////////////
//	if(iCount==0)
//		return;
	double oldpay(0.00);
	if(!theApp.m_pRecordset->EndOfFile)///////////////////ɨ���¼��
	{
		oldpay=theApp.m_pRecordset->GetCollect("���ѽ��");
	    costatleast+=oldpay;
		theApp.m_pRecordset->MoveNext();
	}
	double shouldpayatlast=costatleast-precost;
	////Ԥ��+�����տ�-����=�����
	////�������˵ĸ����ԣ���������
	CString costofall;
	costofall.Format(_T("%.2f"),costatleast);
	SetDlgItemText(IDC_EDIT5,costofall);//�ܼ���ʾ��Ӧ���˿�

	day.Format(_T("%.1f"),dayoflive);//??????

	CString shouldpaystr;
	shouldpaystr.Format(_T("%.2f"),shouldpayatlast);
	CString shouldpayatlastptr="�����븶�ʿ�"+shouldpaystr+"Ԫ";
	day="ס��"+day+"��"+shouldpayatlastptr;

	SetDlgItemText(IDC_EDIT8,day);////������ʾ����ע
	}

	else
	{
		float deltahour=int(deltaday*24+0.5);
		CString deltahourstr;
		deltahourstr.Format(_T("%.1f"),deltahour);
		
		float cost=deltahour*realcost;
	    CString costofall;
	    costofall.Format(_T("%.2f"),cost);
		SetDlgItemText(IDC_EDIT5,costofall);//�ܼ���ʾ��Ӧ���˿�

		CString time="�ӵ㷿ס��ʱ��"+deltahourstr+"Сʱ";
		SetDlgItemText(IDC_EDIT8,time);////ʱ����ʾ����ע
	}
	
}
