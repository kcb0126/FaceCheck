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
}


BEGIN_MESSAGE_MAP(CDlgMain, CDialogEx)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDlgMain message handlers


BOOL CDlgMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect rect;
	GetDesktopWindow()->GetWindowRect(&rect);

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
	
	return true;
}
