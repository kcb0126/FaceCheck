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
}


BEGIN_MESSAGE_MAP(CDlgMain, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_MONITOR, &CDlgMain::OnBnClickedBtnMonitor)
	ON_BN_CLICKED(IDC_BTN_PERSONMANAGE, &CDlgMain::OnBnClickedBtnPersonmanage)
	ON_BN_CLICKED(IDC_BTN_PERSONHISTORY, &CDlgMain::OnBnClickedBtnPersonhistory)
	ON_BN_CLICKED(IDC_BTN_USERMANGE, &CDlgMain::OnBnClickedBtnUsermange)
	ON_BN_CLICKED(IDC_BTN_USERHISTORY, &CDlgMain::OnBnClickedBtnUserhistory)
	ON_BN_CLICKED(IDC_BTN_SETTINGS, &CDlgMain::OnBnClickedBtnSettings)
END_MESSAGE_MAP()


// CDlgMain message handlers


BOOL CDlgMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect rect;
	GetDesktopWindow()->GetWindowRect(&rect);

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

	SetWindowPos(&wndTopMost, rect.left, rect.top, rect.right, rect.bottom, SWP_NOZORDER);
	this->RedrawWindow();

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
	
	CBitmap bmpDarkgray;
	bmpDarkgray.LoadBitmap(IDB_DARKGRAY);
	pOldBitmap = dc.SelectObject(&bmpDarkgray);
	pDC->StretchBlt(0, 85, rect.Width(), rect.Height() - 170, &dc, 0, 0, 100, 100, SRCCOPY);

	CBitmap bmpWhite;
	bmpWhite.LoadBitmap(IDB_WHITE);
	pOldBitmap = dc.SelectObject(&bmpWhite);
	pDC->StretchBlt(0, 85, rect.Width(), 65, &dc, 0, 0, 100, 100, SRCCOPY);

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

	switch (nTabIndex)
	{
	case TAB_MONITOR:
		m_btnMonitor.EnableWindow(false);
		break;
	case TAB_PERSONMANAGE:
		m_btnPersonmanage.EnableWindow(false);
		break;
	case TAB_PERSONHISTORY:
		m_btnPersonhistory.EnableWindow(false);
		break;
	case TAB_USERMANAGE:
		m_btnUsermanage.EnableWindow(false);
		break;
	case TAB_USERHISTORY:
		m_btnUserhistory.EnableWindow(false);
		break;
	case TAB_SETTINGS:
		m_btnSettings.EnableWindow(false);
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
