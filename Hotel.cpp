// Hotel.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Hotel.h"
//#include "ClassXP.h"
#include "MainFrm.h"
#include "HotelDoc.h"
#include "HotelView.h"
#include "Login.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//#ifdef _DEBUG
//#pragma comment(lib, "Debug\\XPLIB.lib")
//#else // _DEBUG
//#pragma comment(lib, "Release\\XPLIB.lib")
//#endif // _DEBUG
/////////////////////////////////////////////////////////////////////////////
// CHotelApp

BEGIN_MESSAGE_MAP(CHotelApp, CWinApp)
	//{{AFX_MSG_MAP(CHotelApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHotelApp construction

CHotelApp::CHotelApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHotelApp object

CHotelApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHotelApp initialization

BOOL CHotelApp::InitInstance()
{
	InitCommonControls();
//	ClassXP();
	AfxEnableControlContainer();
	Login dlg;
	theApp.IsZhuan=false;
	
	
//	m_iLoginCount=0;//初始化登陆计数
	if(FAILED(::CoInitialize(NULL)))
	{
		AfxMessageBox(_T("ADO INIT FAILED!"));
		return false;
	}
	try
	{
		m_pConnection.CreateInstance(__uuidof(Connection));
		m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=客房管理系统.mdb","","",adConnectUnspecified);///连接数据库
	}
	catch(_com_error &e)///捕捉异常
	{
		CString errormessage;
		errormessage.Format(_T("连接数据库失败!\r\n错误信息:%s"),e.ErrorMessage());
		AfxMessageBox(errormessage);///显示错误信息
		return FALSE;
	}
	catch(...)
	{
		AfxMessageBox(_T("Unknown Error..."));
	}
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	if(dlg.DoModal()!=IDOK||IsLogin!=1)
		return FALSE;



	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	//Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	//Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CHotelDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CHotelView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	m_pMainWnd->SetWindowText(_T("酒店住宿管理系统"));

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CHotelApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CHotelApp message handlers

bool CHotelApp::ADOExecute(_RecordsetPtr &ADOSet,_variant_t &strSQL)
{
	if(m_pRecordset->State==adStateOpen)
		m_pRecordset->Close();
	try
	{
		m_pRecordset->Open(strSQL,m_pConnection.GetInterfacePtr(),adOpenStatic,adLockOptimistic,adCmdText);
		return true;
	}
	catch(_com_error &e)
	{
		CString err;
		err.Format(_T("ADO Error:%s"),(char*)e.Description());
		AfxMessageBox(err);
		return false;
	}

}



int CHotelApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class

//	if(MessageBox(m_pMainWnd->GetSafeHwnd(),"确定退出吗?","是否确定?",MB_YESNO|MB_ICONQUESTION)==IDNO)
//		return 1;
//	DeleteClassXP();
	if(adStateOpen==m_pConnection->State)
		m_pConnection->Close();
	m_pConnection.Release();

	if(adStateOpen==m_pRecordset->State)
		m_pRecordset->Close();
	m_pRecordset.Release();
	//~ClassXP();
	
	return CWinApp::ExitInstance();
}

void CHotelApp::OnAppExit() 
{
	// TODO: Add your command handler code here
	if(MessageBox(m_pMainWnd->GetSafeHwnd(),_T("确定退出吗?"),_T("是否确定?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
	exit(0);
	//CFrameWnd::OnClose();
//	AfxGetApp()->m_pMainWnd->OnClose();
	
}
