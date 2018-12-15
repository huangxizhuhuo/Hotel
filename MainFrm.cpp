// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Hotel.h"

#include "MainFrm.h"
#include "Login.h"
#include "Modify.h"
#include "Kewuzhx.h"
#include "YuDing.h"
#include "DengJi.h"
#include "JieZhang.h"
#include "Lock.h"
#include "Room.h"
#include "QuanXian.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_MENULOGIN, OnLogin)
	ON_COMMAND(ID_MENUITEM32772, OnModifyPasswd)
	ON_COMMAND(ID_MENUITEM32774, OnCalc)
	ON_COMMAND(ID_MENUITEM32776, OnCustomCenter)
	ON_COMMAND(ID_MENUITEM32775, OnYuDing)
	ON_COMMAND(ID_MENUITEM32773, OnLockScreen)
	ON_COMMAND(ID_MENUITEM32796, OnMakeItDirty)
	ON_COMMAND(ID_MENUITEM32795, OnMakeItEmpty)
	ON_COMMAND(ID_MENUITEM32797, OnMakeItReserved)
	ON_COMMAND(ID_MENUITEM32789, OnRoomSet)
	ON_COMMAND(ID_MENUITEM32806, OnDengJi)
	ON_COMMAND(ID_MENUITEM32807, OnJieZhang)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_WM_CLOSE()
	ON_COMMAND(ID_MENUITEM32792, OnQuanXian)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR, 
		ID_SEPARATOR,
		ID_SEPARATOR,// status line indicator
//		ID_INDICATOR_LOGIN,////显示当前用户名
//	ID_INDICATOR_CAPS,
//	ID_INDICATOR_NUM,
//	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction
YuDing* dlg;
CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	dlg=new YuDing(this);
	
}

CMainFrame::~CMainFrame()
{
	delete dlg;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	CMenu *mmenu=GetMenu();
	mmenu->EnableMenuItem(1,MF_BYPOSITION | MF_GRAYED);

//  mmenu->EnableMenuItem(0,MF_BYPOSITION | MF_GRAYED);
	
/*	CMenu* submenu = mmenu->GetSubMenu(1);
    submenu->EnableMenuItem(ID_MENUITEM32775,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);
	submenu->EnableMenuItem(ID_MENUITEM32776,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);
	submenu->EnableMenuItem(ID_MENUITEM32806,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);
	submenu->EnableMenuItem(ID_MENUITEM32807,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);*/
	mmenu->EnableMenuItem(2,MF_BYPOSITION | MF_GRAYED);
	mmenu->EnableMenuItem(3,MF_BYPOSITION | MF_GRAYED);
	mmenu->EnableMenuItem(4,MF_BYPOSITION | MF_GRAYED);
	mmenu->EnableMenuItem(5,MF_BYPOSITION | MF_GRAYED);
//	mmenu->EnableMenuItem(6,MF_BYPOSITION | MF_GRAYED);



	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	CString user="当前用户：    "+theApp.m_sCurrentUser;
	CTime time;
	time=CTime::GetCurrentTime();
	CString daystr;
	int day=time.GetDayOfWeek();
	switch(day)
	{
	case 1:
		daystr="星期天";
		break;
	case 2:
		daystr="星期一";
		break;
	case 3:
		daystr="星期二";
		break;
	case 4:
		daystr="星期三";
		break;
	case 5:
		daystr="星期四";
		break;
	case 6:
		daystr="星期五";
		break;
	case 7:
		daystr="星期六";
		break;
	}
	CString curtime="时间：     "+time.Format("%Y-%m-%d %H:%M  ")+daystr;
	
	
	m_wndStatusBar.SetPaneInfo(1,NULL,SBPS_NORMAL,100);  
	m_wndStatusBar.SetPaneInfo(2,NULL,SBPS_NORMAL,200);
//	m_wndStatusBar.SetPaneInfo(3,NULL,SBPS_NORMAL,0);
    m_wndStatusBar.SetPaneText(1,user,TRUE);
    m_wndStatusBar.SetPaneText(2,curtime,TRUE);


	////////////////////////////////////////////////////////////////////////
	CBitmap m_bmp;
	m_bmp.Attach(::LoadImage(AfxGetResourceHandle(), _T("list_normal"),	IMAGE_BITMAP, 0, 0,LR_DEFAULTSIZE|LR_CREATEDIBSECTION));
	m_NormalList.Create(48, 48, ILC_COLOR24|ILC_MASK, 0, 0);
	m_NormalList.Add(&m_bmp,RGB(192,192,192)) ;
	m_bmp.Detach();
	m_wndToolBar.SendMessage(TB_SETIMAGELIST,0,(LPARAM)m_NormalList.m_hImageList);

	m_bmp.Attach(::LoadImage(AfxGetResourceHandle(), _T("list_hot"),IMAGE_BITMAP, 0, 0,LR_DEFAULTSIZE|LR_CREATEDIBSECTION));
	m_HotList.Create(48, 48, ILC_COLOR24|ILC_MASK, 0, 0);
	m_HotList.Add(&m_bmp,RGB(192,192,192)) ;
	m_bmp.Detach();
	m_wndToolBar.SendMessage(TB_SETHOTIMAGELIST,0,(LPARAM)m_HotList.m_hImageList);
	
	m_bmp.Attach(::LoadImage(AfxGetResourceHandle(), _T("list_disable"),IMAGE_BITMAP, 0, 0,LR_DEFAULTSIZE|LR_CREATEDIBSECTION));
	m_DisableList.Create(48, 48, ILC_COLOR24|ILC_MASK, 0, 0);
	m_DisableList.Add(&m_bmp,RGB(192,192,192)) ;
	m_bmp.Detach();
	m_wndToolBar.SendMessage(TB_SETDISABLEDIMAGELIST,0,(LPARAM)m_DisableList.m_hImageList);
/////////////////////////////////////////////////////////////////////////////////////////////

//	m_wndToolBar.SetButtonText(1,"客人登记");
	///给工具条加文本
	for(int i=0;i<m_wndToolBar.GetCount();i++)
	{
		UINT id=m_wndToolBar.GetItemID(i);
		CString s;
		if(!s.LoadString(id))
			continue;
		int j=s.Find(_T('\n'));
		if(j<0)
			continue;
		s=s.Right(s.GetLength()-j-1);
		m_wndToolBar.SetButtonText(i,s);
	}

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
//	::SetProp(GetSafeHwnd(),INSTANCEMAINWNDPROP,(HANDLE)1);

/*	TBBUTTONINFO tbinfo;
    tbinfo.cbSize = sizeof(TBBUTTONINFO);
    tbinfo.dwMask = TBIF_STATE;
    tbinfo.fsState = TBSTATE_HIDDEN         ;
    ::SendMessage(m_wndToolBar,TB_SETBUTTONINFO,(WPARAM)ID_MENUITEM32775,(LPARAM)&tbinfo);
    ::SendMessage(m_wndToolBar,TB_SETBUTTONINFO,(WPARAM)ID_MENUITEM32806,(LPARAM)&tbinfo);
	::SendMessage(m_wndToolBar,TB_SETBUTTONINFO,(WPARAM)ID_MENUITEM32807,(LPARAM)&tbinfo);
    ::SendMessage(m_wndToolBar,TB_SETBUTTONINFO,(WPARAM)ID_MENUITEM32776,(LPARAM)&tbinfo);*/
//////////////////////////////////////////////////////////////////////////////////////////
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnLogin()//重登录响应函数
{
 //   ::CoInitialize(NULL);
	Login dlg;
	if(dlg.DoModal()!=IDOK)
		return;
	CMenu *mmenu=GetMenu();
	mmenu->EnableMenuItem(1,MF_BYPOSITION | MF_GRAYED);
	mmenu->EnableMenuItem(2,MF_BYPOSITION | MF_GRAYED);
	mmenu->EnableMenuItem(3,MF_BYPOSITION | MF_GRAYED);
	mmenu->EnableMenuItem(4,MF_BYPOSITION | MF_GRAYED);
	mmenu->EnableMenuItem(5,MF_BYPOSITION | MF_GRAYED);

	_variant_t str;
	UpdateData();
	CString UserId=dlg.m_UserId;
	CString PassWd=dlg.m_PassWd;
	str="select * from 用户权限 where UserId='"+UserId+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	if(theApp.m_pRecordset->EndOfFile)
	{
		AfxMessageBox(_T("用户名不正确..."));
		UserId="";
		UpdateData(false);
		return;
	}
	str="select * from 用户权限 where UserId='"+UserId+"' and PassWd='"+PassWd+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str);
	if(theApp.m_pRecordset->EndOfFile)
	{
		AfxMessageBox(_T("密码错误..."));
		PassWd="";
		UpdateData(false);
		return;
	}
	theApp.m_sCurrentUser=(char *)(_bstr_t)theApp.m_pRecordset->GetCollect("UserId");
	CString user="当前用户为:  "+theApp.m_sCurrentUser;	
	m_wndStatusBar.SetPaneText(1,user,TRUE);
//	MessageBox("用户"'"+theApp.m_sCurrentUser+"'"登录");
	theApp.IsLogin=true;
	if(theApp.systemstr=="Y")
	{
		CMenu *mmenu=GetMenu();
        mmenu->EnableMenuItem(5,MF_BYPOSITION | MF_ENABLED);
		DrawMenuBar();
	}
	if(theApp.selectstr=="Y")
	{
		CMenu *mmenu=GetMenu();
        mmenu->EnableMenuItem(2,MF_BYPOSITION | MF_ENABLED);
		DrawMenuBar();
	}
	if(theApp.foundationdatastr=="Y")
	{
		CMenu *mmenu=GetMenu();
        mmenu->EnableMenuItem(4,MF_BYPOSITION | MF_ENABLED);
		DrawMenuBar();
	}
	if(theApp.tablestr=="Y")
	{
		CMenu *mmenu=GetMenu();
        mmenu->EnableMenuItem(3,MF_BYPOSITION | MF_ENABLED);
		DrawMenuBar();
	}
	if(theApp.customstr=="Y")
	{
		CMenu *mmenu=GetMenu();
        mmenu->EnableMenuItem(1,MF_BYPOSITION | MF_ENABLED);
		
		TBBUTTONINFO tbinfo;///结构???
        tbinfo.cbSize = sizeof(TBBUTTONINFO);
        tbinfo.dwMask = TBIF_STATE;
        tbinfo.fsState = TBSTATE_ENABLED;
		DrawMenuBar();
	}

}


void CMainFrame::OnModifyPasswd() 
{
	// TODO: Add your command handler code here
	Modify d;
	if(d.DoModal()!=IDOK)
		return;
	
}

void CMainFrame::OnCalc() 
{
	// TODO: Add your command handler code here
	WinExec("res\\Calc.exe",SW_SHOW);
	
	
}

void CMainFrame::OnCustomCenter() 
{
	// TODO: Add your command handler code here
	Kewuzhx d;
	if(d.DoModal()!=IDOK)
		return;
	
}

void CMainFrame::OnYuDing() 
{
	// TODO: Add your command handler code here
//	YuDing *dlg=new YuDing(this);
	if(dlg->GetSafeHwnd()==0)
	{
	    dlg->Create(IDD_CUSTOMYD);
	}

//	dlg->ModifyStyle(WS_CLIPCHILDREN,WS_CAPTION);


	dlg->ShowWindow(SW_SHOW);


	
}

void CMainFrame::OnLockScreen() 
{
	// TODO: Add your command handler code here
	Lock dlg;
	dlg.DoModal();
	
}

void CMainFrame::OnMakeItDirty() 
{
	// TODO: Add your command handler code here
	_variant_t str2;
	CString room=theApp.fangjianhaoma;
	str2="update 客房 set 客房状态='脏房' where 房号='"+room+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str2);
	Kewuzhx dlg;
	
	
}

void CMainFrame::OnMakeItEmpty() 
{
	// TODO: Add your command handler code here

	_variant_t str2;
	CString room=theApp.fangjianhaoma;
	str2="update 客房 set 客房状态='空' where 房号='"+room+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str2);
	Kewuzhx dlg;
		
}

void CMainFrame::OnMakeItReserved() 
{
	// TODO: Add your command handler code here

	_variant_t str2;
	CString room=theApp.fangjianhaoma;
	str2="update 客房 set 客房状态='保留' where 房号='"+room+"'";
	theApp.ADOExecute(theApp.m_pRecordset,str2);
	Kewuzhx dlg;
	
}

void CMainFrame::OnRoomSet() 
{
	// TODO: Add your command handler code here
	Room dlg;
	dlg.DoModal();
	
}

void CMainFrame::OnDengJi() 
{
	// TODO: Add your command handler code here
	DengJi dlg;
	dlg.DoModal();
	
}

void CMainFrame::OnJieZhang() 
{
	// TODO: Add your command handler code here
	JieZhang dlg;
	dlg.DoModal();
	
}

void CMainFrame::OnAppExit() 
{
	// TODO: Add your command handler code here
	if(MessageBox(_T("确定退出吗?"),_T("是否确定?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;
//	exit(0);
	CFrameWnd::OnClose();
//	AfxGetApp()->ExitInstance();
	
}





void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	if(MessageBox(_T("确定退出吗?"),_T("是否确定?"),MB_YESNO|MB_ICONQUESTION)==IDNO)
		return;	
	CFrameWnd::OnClose();
}

void CMainFrame::OnQuanXian() 
{
	// TODO: Add your command handler code here
	QuanXian dlg;
	dlg.DoModal();
	
}

void CMainFrame::OnDestroy() 
{

//	::RemoveProp(GetSafeHwnd(),INSTANCEMAINWNDPROP);	
//	CWnd::OnDestroy();
	CFrameWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
