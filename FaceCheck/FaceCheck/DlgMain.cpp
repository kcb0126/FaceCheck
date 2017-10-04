// DlgMain.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "DlgMain.h"
#include "afxdialogex.h"


// CDlgMain dialog

IMPLEMENT_DYNAMIC(CDlgMain, CDialogEx)

CDlgMain::CDlgMain(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMain::IDD, pParent)
{

}

CDlgMain::~CDlgMain()
{
}

void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_MONITOR, m_btnMonitor);
	DDX_Control(pDX, IDC_BTN_PERSONMANAGE, m_btnPersonmanage);
	DDX_Control(pDX, IDC_BTN_PERSONHISTORY, m_btnPersonhistory);
	DDX_Control(pDX, IDC_BTN_USERMANGE, m_btnUsermanage);
	DDX_Control(pDX, IDC_BTN_USERHISTORY, m_btnUserhistory);
	DDX_Control(pDX, IDC_BTN_SETTINGS, m_btnSettings);
	DDX_Control(pDX, IDC_BTN_POWER, m_btnPower);
	DDX_Control(pDX, IDC_BTN_PREFERENCES, m_btnPreferences);
}


BEGIN_MESSAGE_MAP(CDlgMain, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_MONITOR, &CDlgMain::OnBnClickedBtnMonitor)
	ON_BN_CLICKED(IDC_BTN_PERSONMANAGE, &CDlgMain::OnBnClickedBtnPersonmanage)
	ON_BN_CLICKED(IDC_BTN_PERSONHISTORY, &CDlgMain::OnBnClickedBtnPersonhistory)
	ON_BN_CLICKED(IDC_BTN_USERMANGE, &CDlgMain::OnBnClickedBtnUsermange)
	ON_BN_CLICKED(IDC_BTN_USERHISTORY, &CDlgMain::OnBnClickedBtnUserhistory)
	ON_BN_CLICKED(IDC_BTN_SETTINGS, &CDlgMain::OnBnClickedBtnSettings)
	ON_BN_CLICKED(IDC_BTN_POWER, &CDlgMain::OnBnClickedBtnPower)
END_MESSAGE_MAP()


// CDlgMain message handlers


BOOL CDlgMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect rect;
	GetDesktopWindow()->GetWindowRect(&rect);
	SetWindowPos(&wndTopMost, rect.left, rect.top, rect.right, rect.bottom, SWP_NOZORDER);

	m_btnPower.OnSet();
	m_btnPower.LoadBitmaps(IDB_POWER, IDB_POWERDOWN, IDB_POWER, IDB_POWER);
	m_btnPower.SetHoverBitmapID(IDB_POWERHOVER);
	m_btnPower.SizeToContent();
	m_btnPower.SetWindowPos(NULL, rect.Width() - 76, 0, 76, 85, SWP_NOZORDER);

	m_btnPreferences.OnSet();
	m_btnPreferences.LoadBitmaps(IDB_PREFERENCES, IDB_PREFERENCESDOWN, IDB_PREFERENCES, IDB_PREFERENCES);
	m_btnPreferences.SetHoverBitmapID(IDB_PREFERENCESHOVER);
	m_btnPreferences.SizeToContent();
	m_btnPreferences.SetWindowPos(NULL, rect.Width() - 152, 0, 76, 85, SWP_NOZORDER);

	m_btnMonitor.OnSet();
	m_btnMonitor.LoadBitmaps(IDB_MONITOR, IDB_MONITOR_HOVER, IDB_MONITOR, IDB_MONITOR_DISABLED);
	m_btnMonitor.SetHoverBitmapID(IDB_MONITOR_HOVER);
	m_btnMonitor.SizeToContent();
	int monitorX, monitorY, monitorW, monitorH;
	monitorX = 0;
	monitorY = 85;
	monitorW = 200;
	monitorH = 63;
	m_btnMonitor.SetWindowPos(NULL, monitorX, monitorY, monitorW, monitorH, SWP_NOZORDER);

	m_btnPersonmanage.OnSet();
	m_btnPersonmanage.LoadBitmaps(IDB_PERSONMANAGE, IDB_PERSONMANAGE_HOVER, IDB_PERSONMANAGE, IDB_PERSONMANAGE_DISABLED);
	m_btnPersonmanage.SetHoverBitmapID(IDB_PERSONMANAGE_HOVER);
	m_btnPersonmanage.SizeToContent();
	int personmanageX, personmanageY, personmanageW, personmanageH;
	personmanageX = monitorX + monitorW + 2;
	personmanageY = monitorY;
	personmanageW = monitorW;
	personmanageH = monitorH;
	m_btnPersonmanage.SetWindowPos(NULL, personmanageX, personmanageY, personmanageW, personmanageH, SWP_NOZORDER);

	m_btnPersonhistory.OnSet();
	m_btnPersonhistory.LoadBitmaps(IDB_PERSONHISTORY, IDB_PERSONHISTORY_HOVER, IDB_PERSONHISTORY, IDB_PERSONHISTORY_DISABLED);
	m_btnPersonhistory.SetHoverBitmapID(IDB_PERSONHISTORY_HOVER);
	m_btnPersonhistory.SizeToContent();
	int personhistoryX, personhistoryY, personhistoryW, personhistoryH;
	personhistoryX = personmanageX + personmanageW + 2;
	personhistoryY = personmanageY;
	personhistoryW = personmanageW;
	personhistoryH = personmanageH;
	m_btnPersonhistory.SetWindowPos(NULL, personhistoryX, personhistoryY, personhistoryW, personhistoryH, SWP_NOZORDER);

	m_btnUsermanage.OnSet();
	m_btnUsermanage.LoadBitmaps(IDB_USERMANAGE, IDB_USERMANAGE_HOVER, IDB_USERMANAGE, IDB_USERMANAGE_DISABLED);
	m_btnUsermanage.SetHoverBitmapID(IDB_USERMANAGE_HOVER);
	m_btnUsermanage .SizeToContent();
	int usermanageX, usermanageY, usermanageW, usermanageH;
	usermanageX = personhistoryX + personhistoryW + 2;
	usermanageY = personhistoryY;
	usermanageW = personhistoryW;
	usermanageH = personhistoryH;
	m_btnUsermanage.SetWindowPos(NULL, usermanageX, usermanageY, usermanageW, usermanageH, SWP_NOZORDER);

	m_btnUserhistory.OnSet();
	m_btnUserhistory.LoadBitmaps(IDB_USERHISTORY, IDB_USERHISTORY_HOVER, IDB_USERHISTORY, IDB_USERHISTORY_DISABLED);
	m_btnUserhistory.SetHoverBitmapID(IDB_USERHISTORY_HOVER);
	m_btnUserhistory.SizeToContent();
	int userhistoryX, userhistoryY, userhistoryW, userhistoryH;
	userhistoryX = usermanageX + usermanageW + 2;
	userhistoryY = usermanageY;
	userhistoryW = usermanageW;
	userhistoryH = usermanageH;
	m_btnUserhistory.SetWindowPos(NULL, userhistoryX, userhistoryY, userhistoryW, userhistoryH, SWP_NOZORDER);

	m_btnSettings.OnSet();
	m_btnSettings.LoadBitmaps(IDB_SETTINGS, IDB_SETTINGS_HOVER, IDB_SETTINGS, IDB_SETTINGS_DISABLED);
	m_btnSettings.SetHoverBitmapID(IDB_SETTINGS_HOVER);
	m_btnSettings.SizeToContent();
	int settingsX, settingsY, settingsW, settingsH;
	settingsX = userhistoryX + userhistoryW + 2;
	settingsY = userhistoryY;
	settingsW = userhistoryW;
	settingsH = userhistoryH;
	m_btnSettings.SetWindowPos(NULL, settingsX, settingsY, settingsW, settingsH, SWP_NOZORDER);

	int pageMonitorX, pageMonitorY, pageMonitorW, pageMonitorH;
	pageMonitorX = monitorX;
	pageMonitorY = monitorY + monitorH + 5;
	pageMonitorW = rect.Width() - pageMonitorX * 2;
	pageMonitorH = rect.Height() - pageMonitorY - 90;
	m_pageMonitor.Create(CPageOfMonitor::IDD, this);
	m_pageMonitor.SetWindowPos(NULL, pageMonitorX, pageMonitorY, pageMonitorW, pageMonitorH, SWP_NOZORDER);
	m_pageMonitor.ShowWindow(SW_HIDE);

	int pagePersonManageX, pagePersonManageY, pagePersonManageW, pagePersonManageH;
	pagePersonManageX = pageMonitorX;
	pagePersonManageY = pageMonitorY;
	pagePersonManageW = pageMonitorW;
	pagePersonManageH = pageMonitorH;
	m_pagePersonManage.Create(CPageOfPersonManage::IDD, this);
	m_pagePersonManage.SetWindowPos(NULL, pagePersonManageX, pagePersonManageY, pagePersonManageW, pagePersonManageH, SWP_NOZORDER);
	m_pagePersonManage.ShowWindow(SW_HIDE);

	int pagePersonHistoryX, pagePersonHistoryY, pagePersonHistoryW, pagePersonHistoryH;
	pagePersonHistoryX = pageMonitorX;
	pagePersonHistoryY = pageMonitorY;
	pagePersonHistoryW = pageMonitorW;
	pagePersonHistoryH = pageMonitorH;
	m_pagePersonHistory.Create(CPageOfPersonHistory::IDD, this);
	m_pagePersonHistory.SetWindowPos(NULL, pagePersonHistoryX, pagePersonHistoryY, pagePersonHistoryW, pagePersonHistoryH, SWP_NOZORDER);
	m_pagePersonHistory.ShowWindow(SW_HIDE);

	int pageUserManageX, pageUserManageY, pageUserManageW, pageUserManageH;
	pageUserManageX = pageMonitorX;
	pageUserManageY = pageMonitorY;
	pageUserManageW = pageMonitorW;
	pageUserManageH = pageMonitorH;
	m_pageUserManage.Create(CPageOfUserManage::IDD, this);
	m_pageUserManage.SetWindowPos(NULL, pageUserManageX, pageUserManageY, pageUserManageW, pageUserManageH, SWP_NOZORDER);
	m_pageUserManage.ShowWindow(SW_HIDE);

	int pageUserHistoryX, pageUserHistoryY, pageUserHistoryW, pageUserHistoryH;
	pageUserHistoryX = pageMonitorX;
	pageUserHistoryY = pageMonitorY;
	pageUserHistoryW = pageMonitorW;
	pageUserHistoryH = pageMonitorH;
	m_pageUserHistory.Create(CPageOfUserHistory::IDD, this);
	m_pageUserHistory.SetWindowPos(NULL, pageUserHistoryX, pageUserHistoryY, pageUserHistoryW, pageUserHistoryH, SWP_NOZORDER);
	m_pageUserHistory.ShowWindow(SW_HIDE);

	int pageSettingsX, pageSettingsY, pageSettingsW, pageSettingsH;
	pageSettingsX = pageMonitorX;
	pageSettingsY = pageMonitorY;
	pageSettingsW = pageMonitorW;
	pageSettingsH = pageMonitorH;
	m_pageSettings.Create(CPageOfSettings::IDD, this);
	m_pageSettings.SetWindowPos(NULL, pageSettingsX, pageSettingsY, pageSettingsW, pageSettingsH, SWP_NOZORDER);
	m_pageSettings.ShowWindow(SW_HIDE);

	this->RedrawWindow();

	SetTab(TAB_MONITOR);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDlgMain::OnEraseBkgnd(CDC* pDC)
{
	CDialogEx::OnEraseBkgnd(pDC);

	CRect rect;
	GetClientRect(&rect);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap;

	CBitmap bmpBlack;
	bmpBlack.LoadBitmap(IDB_BLACK);
	pOldBitmap = dc.SelectObject(&bmpBlack);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, 100, 100, SRCCOPY);
	
	CBitmap bmpTitle;
	bmpTitle.LoadBitmap(IDB_TITLE);
	pOldBitmap = dc.SelectObject(&bmpTitle);
	pDC->StretchBlt(0, 0, 200, 85, &dc, 0, 0, 200, 80, SRCCOPY);

	CBitmap bmpDarkgray;
	bmpDarkgray.LoadBitmap(IDB_DARKGRAY);
	pOldBitmap = dc.SelectObject(&bmpDarkgray);
	pDC->StretchBlt(0, 85, rect.Width(), rect.Height() - 170, &dc, 0, 0, 100, 100, SRCCOPY);

	CBitmap bmpWhite;
	bmpWhite.LoadBitmap(IDB_WHITE);
	pOldBitmap = dc.SelectObject(&bmpWhite);
	pDC->StretchBlt(0, 85, rect.Width(), 65, &dc, 0, 0, 100, 100, SRCCOPY);

	CBitmap bmpBottom;
	bmpBottom.LoadBitmap(IDB_BOTTOM);	
	pOldBitmap = dc.SelectObject(&bmpBottom);
	pDC->StretchBlt(rect.Width() / 2 - 400, rect.Height() - 85, 800, 85, &dc, 0, 0, 800, 85, SRCCOPY);

	CRect rcSettings;
	m_btnSettings.GetWindowRect(&rcSettings);
	
	pOldBitmap = dc.SelectObject(&bmpDarkgray);
	int restbarX, restbarY, restbarW, restbarH;
	restbarX = rcSettings.right + 2;
	restbarY = rcSettings.top;
	restbarW = rect.right - rcSettings.right;
	restbarH = rcSettings.Height();
	pDC->StretchBlt(restbarX, restbarY, restbarW, restbarH, &dc, 0, 0, 100, 100, SRCCOPY);

	return true;
}

void CDlgMain::SetTab(int nTabIndex)
{
	m_btnMonitor.EnableWindow(true);
	m_btnPersonmanage.EnableWindow(true);
	m_btnPersonhistory.EnableWindow(true);
	m_btnUsermanage.EnableWindow(true);
	m_btnUserhistory.EnableWindow(true);
	m_btnSettings.EnableWindow(true);

	m_pageMonitor.ShowWindow(SW_HIDE);
	m_pagePersonManage.ShowWindow(SW_HIDE);
	m_pagePersonHistory.ShowWindow(SW_HIDE);
	m_pageUserManage.ShowWindow(SW_HIDE);
	m_pageUserHistory.ShowWindow(SW_HIDE);
	m_pageSettings.ShowWindow(SW_HIDE);

	switch (nTabIndex)
	{
	case TAB_MONITOR:
		m_btnMonitor.EnableWindow(false);
		m_pageMonitor.ShowWindow(SW_SHOW);
		break;
	case TAB_PERSONMANAGE:
		m_btnPersonmanage.EnableWindow(false);
		m_pagePersonManage.ShowWindow(SW_SHOW);
		break;
	case TAB_PERSONHISTORY:
		m_btnPersonhistory.EnableWindow(false);
		m_pagePersonHistory.ShowWindow(SW_SHOW);
		break;
	case TAB_USERMANAGE:
		m_btnUsermanage.EnableWindow(false);
		m_pageUserManage.ShowWindow(SW_SHOW);
		break;
	case TAB_USERHISTORY:
		m_btnUserhistory.EnableWindow(false);
		m_pageUserHistory.ShowWindow(SW_SHOW);
		break;
	case TAB_SETTINGS:
		m_btnSettings.EnableWindow(false);
		m_pageSettings.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}

}

void CDlgMain::OnBnClickedBtnMonitor()
{
	SetTab(TAB_MONITOR);
}


void CDlgMain::OnBnClickedBtnPersonmanage()
{
	SetTab(TAB_PERSONMANAGE);
}


void CDlgMain::OnBnClickedBtnPersonhistory()
{
	SetTab(TAB_PERSONHISTORY);
}


void CDlgMain::OnBnClickedBtnUsermange()
{
	SetTab(TAB_USERMANAGE);
}


void CDlgMain::OnBnClickedBtnUserhistory()
{
	SetTab(TAB_USERHISTORY);
}


void CDlgMain::OnBnClickedBtnSettings()
{
	SetTab(TAB_SETTINGS);
}


void CDlgMain::OnBnClickedBtnPower()
{
	CDialogEx::OnOK();
}
