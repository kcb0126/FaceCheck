
// FaceCheckDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "FaceCheckDlg.h"
#include "afxdialogex.h"

#include "DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFaceCheckDlg dialog



CFaceCheckDlg::CFaceCheckDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFaceCheckDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFaceCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_POWER, m_btnPower);
	DDX_Control(pDX, IDC_STATIC_TODO, m_lblTodo);
	DDX_Control(pDX, IDC_STATIC_USERNAME, m_lblUsername);
	DDX_Control(pDX, IDC_STATIC_PASSWORD, m_lblPassword);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_edtUsername);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_edtPassword);
	DDX_Control(pDX, IDC_BUTTON1, m_btnLogin);
}

BEGIN_MESSAGE_MAP(CFaceCheckDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON1, &CFaceCheckDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CFaceCheckDlg message handlers

BOOL CFaceCheckDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRect rect;
	GetDesktopWindow()->GetWindowRect(&rect);

	m_btnPower.OnSet();
	m_btnPower.LoadBitmaps(IDB_POWER, IDB_POWERDOWN, IDB_POWER, IDB_POWER);
	m_btnPower.SetHoverBitmapID(IDB_POWERHOVER);
	m_btnPower.SizeToContent();
	m_btnPower.SetWindowPos(NULL, rect.Width() - 76, 0, 76, 85, SWP_NOZORDER);

	m_lblTodo.SetTextColor(RGB(255, 255, 255));
	m_lblTodo.SetFontSize(24);
	m_lblTodo.SetFontName(L"Times New Roman");
	m_lblTodo.SetText(L"All right reserved");
	m_lblTodo.SetRedraw();

	m_lblUsername.SetTextColor(RGB(255, 255, 255));
	m_lblUsername.SetFontSize(32);
	m_lblUsername.SetFontName(L"Times New Roman");
	m_lblUsername.SetText(L"Username:");
	m_lblUsername.Invalidate();
	int usernameX, usernameY, usernameW, usernameH;
	usernameX = rect.Width() / 2 - 500;
	usernameY = rect.Height() * 3 / 4 + 24;
	usernameW = 200;
	usernameH = 32;
	m_lblUsername.SetWindowPos(NULL, usernameX, usernameY, usernameW, usernameH, SWP_NOZORDER);
	m_lblUsername.SetRedraw();

	int usernameX_, usernameY_, usernameW_, usernameH_;
	usernameX_ = usernameX + usernameW;
	usernameY_ = usernameY - 4;
	usernameW_ = 200;
	usernameH_ = 40;
	m_edtUsername.SetWindowPos(NULL, usernameX_, usernameY_, usernameW_, usernameH_, SWP_NOZORDER);

	m_lblPassword.SetTextColor(RGB(255, 255, 255));
	m_lblPassword.SetFontSize(32);
	m_lblPassword.SetFontName(L"Times New Roman");
	m_lblPassword.SetText(L"Password:");
	m_lblPassword.Invalidate();
	int passwordX, passwordY, passwordW, passwordH;
	passwordX = usernameX_ + usernameW_;
	passwordY = usernameY;
	passwordW = usernameW;
	passwordH = usernameH;
	m_lblPassword.SetWindowPos(NULL, passwordX, passwordY, passwordW, passwordH, SWP_NOZORDER);
	m_lblPassword.SetRedraw();

	int passwordX_, passwordY_, passwordW_, passwordH_;
	passwordX_ = passwordX + passwordW;
	passwordY_ = usernameY_;
	passwordW_ = usernameW_;
	passwordH_ = usernameH_;
	m_edtPassword.SetWindowPos(NULL, passwordX_, passwordY_, passwordW_, passwordH_, SWP_NOZORDER);

	m_btnLogin.OnSet();
	m_btnLogin.LoadBitmaps(IDB_LOGIN, IDB_LOGINDOWN, IDB_LOGIN, IDB_LOGIN);
	m_btnLogin.SetHoverBitmapID(IDB_LOGINHOVER);
	m_btnLogin.SizeToContent();
	int loginX, loginY, loginW, loginH;
	loginX = passwordX_ + passwordW_ + 40;
	loginY = passwordY_;
	loginW = 120;
	loginH = passwordH_;
	m_btnLogin.SetWindowPos(NULL, loginX, loginY, loginW, loginH, SWP_NOZORDER);

	m_bmpHome.LoadBitmap(IDB_HOME);
	//	SetParent(GetDesktopWindow());

	SetWindowPos(&wndTopMost, rect.left, rect.top, rect.right, rect.bottom, SWP_NOZORDER);

	this->RedrawWindow();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFaceCheckDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFaceCheckDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFaceCheckDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CFaceCheckDlg::OnEraseBkgnd(CDC* pDC)
{
	CDialogEx::OnEraseBkgnd(pDC);

	CRect rect;
	GetClientRect(&rect);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = dc.SelectObject(&m_bmpHome);
	int bmw, bmh;
	BITMAP bmap;
	m_bmpHome.GetBitmap(&bmap);
	bmw = bmap.bmWidth;
	bmh = bmap.bmHeight;
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, bmw, bmh, SRCCOPY);
	dc.SelectObject(pOldBitmap);

	CBitmap bmpBlack;
	bmpBlack.LoadBitmap(IDB_BLACK);
	pOldBitmap = dc.SelectObject(&bmpBlack);
	pDC->StretchBlt(0, 0, rect.Width(), 85, &dc, 0, 0, 100, 100, SRCCOPY);

	CBitmap bmpTitle;
	bmpTitle.LoadBitmap(IDB_TITLE);
	pOldBitmap = dc.SelectObject(&bmpTitle);
	pDC->StretchBlt(0, 0, 200, 85, &dc, 0, 0, 200, 85, SRCCOPY);

	CBitmap bmpWhite;
	bmpWhite.LoadBitmap(IDB_WHITE);
	pOldBitmap = dc.SelectObject(&bmpWhite);
	int boxX, boxY, boxW, boxH;
	boxX = rect.Width() / 2 - 500;
	boxW = 1000;
	boxY = rect.Height() / 4 * 3;
	boxH = 80;

	BLENDFUNCTION bf;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.BlendFlags = 0;
	bf.BlendOp = AC_SRC_OVER;
	bf.SourceConstantAlpha = 96;
	pDC->AlphaBlend(boxX, boxY, boxW, boxH, &dc, 0, 0, 100, 100, bf);

	return true;
}


void CFaceCheckDlg::OnBnClickedButton1()
{
	CDlgMain dlgMain;
	dlgMain.DoModal();
}
