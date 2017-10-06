// DlgOfWarning.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "DlgOfWarning.h"
#include "afxdialogex.h"

#include <mmsystem.h>

// CDlgOfWarning dialog

IMPLEMENT_DYNAMIC(CDlgOfWarning, CDialogEx)

CDlgOfWarning::CDlgOfWarning(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgOfWarning::IDD, pParent)
{

}

CDlgOfWarning::~CDlgOfWarning()
{
}

void CDlgOfWarning::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgOfWarning, CDialogEx)
	ON_WM_SIZE()
	ON_WM_DRAWITEM()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDOK, &CDlgOfWarning::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgOfWarning message handlers


BOOL CDlgOfWarning::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rect;
	GetClientRect(&rect);
	GetDlgItem(IDOK)->SetWindowPos(NULL
		, 0
		, 0
		, rect.Width()
		, rect.Height()
		, SWP_NOZORDER);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgOfWarning::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	static BOOL isJustStarted = TRUE;

	if (isJustStarted)
	{
		isJustStarted = FALSE;
		return;
	}

	CRect rect;
	GetClientRect(&rect);

	GetDlgItem(IDOK)->SetWindowPos(NULL
		, -5
		, -5
		, rect.Width() + 10
		, rect.Height() + 10
		, SWP_NOZORDER);
}


void CDlgOfWarning::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (nIDCtl == IDOK)
	{
		CDC dc;
		RECT rect;
		dc.Attach(lpDrawItemStruct->hDC);   // Get the Button DC to CDC

		COLORREF backcolor = (m_nWarningType == 0) ? RGB(255, 0, 0) : RGB(255, 255, 0);

		rect = lpDrawItemStruct->rcItem;     //Store the Button rect to our local rect.
		dc.Draw3dRect(&rect, backcolor, RGB(0, 0, 0));
		dc.FillSolidRect(&rect, backcolor);//Here you can define the required color to appear on the Button.

		UINT state = lpDrawItemStruct->itemState;  //This defines the state of the Push button either pressed or not. 
		if ((state & ODS_SELECTED))
			dc.DrawEdge(&rect, EDGE_SUNKEN, BF_RECT);
		else
			dc.DrawEdge(&rect, EDGE_RAISED, BF_RECT);

		dc.SetBkColor(backcolor);   //Setting the Text Background color
		dc.SetTextColor(RGB(0, 0, 0));     //Setting the Text Color

		TCHAR buffer[MAX_PATH];           //To store the Caption of the button.
		ZeroMemory(buffer, MAX_PATH);     //Intializing the buffer to zero
		::GetWindowText(lpDrawItemStruct->hwndItem, buffer, MAX_PATH); //Get the Caption of Button Window 

		dc.DrawText(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//Redraw the  Caption of Button Window 
		dc.Detach();  // Detach the Button DC
	}


	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void CDlgOfWarning::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
}


void CDlgOfWarning::OnBnClickedOk()
{
	ShowWindow(SW_HIDE);

	sndPlaySound(NULL, SND_ASYNC);

	m_bNowWarning = FALSE;
	//CDialogEx::OnOK();
}

void CDlgOfWarning::StartWarning()
{
	if (m_bNowWarning)
		return;

	m_bNowWarning = TRUE;

	PlaySound((LPCWSTR)MAKEINTRESOURCE(IDR_WAVE_WARNING), NULL, SND_ASYNC | SND_RESOURCE);
}