// UserManageList.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "UserManageList.h"
#include "afxdialogex.h"
#include "myGlobal.h"

CUserManageList* g_pUserManageList;

// CUserManageList dialog

IMPLEMENT_DYNAMIC(CUserManageList, CPropertyPage)

CUserManageList::CUserManageList()
	: CPropertyPage(CUserManageList::IDD)
{
	g_pUserManageList = this;
}

CUserManageList::~CUserManageList()
{
	// Don't need to delete m_pListOfUserManage;
}

void CUserManageList::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_FIRST, m_btnFirst);
	DDX_Control(pDX, IDC_BUTTON_PREV, m_btnPrev);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_btnNext);
	DDX_Control(pDX, IDC_BUTTON_LAST, m_btnLast);
	DDX_Control(pDX, IDC_EDIT_PAGE, m_editPagenumber);
	DDX_Control(pDX, IDC_STATIC_TOTALRECORDS, m_lblTotalrecords);
	DDX_Control(pDX, IDC_STATIC_TOTALPAGES, m_lblTotalpages);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_btnAdd);
}


BEGIN_MESSAGE_MAP(CUserManageList, CPropertyPage)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_FIRST, &CUserManageList::OnBnClickedButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_PREV, &CUserManageList::OnBnClickedButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CUserManageList::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_LAST, &CUserManageList::OnBnClickedButtonLast)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CUserManageList::OnBnClickedButtonAdd)
END_MESSAGE_MAP()


BOOL CUserManageList::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	CRect rect;
	GetDesktopWindow()->GetWindowRect(&rect);

	m_btnFirst.OnSet();
	m_btnFirst.LoadBitmaps(IDB_PAGING_FIRST, IDB_PAGING_FIRST, IDB_PAGING_FIRST, IDB_PAGING_FIRST_DISABLED);
	m_btnFirst.SetHoverBitmapID(IDB_PAGING_FIRST_HOVER);
	m_btnFirst.SizeToContent();

	m_btnPrev.OnSet();
	m_btnPrev.LoadBitmaps(IDB_PAGING_PREV, IDB_PAGING_PREV, IDB_PAGING_PREV, IDB_PAGING_PREV_DISABLED);
	m_btnPrev.SetHoverBitmapID(IDB_PAGING_PREV_HOVER);
	m_btnPrev.SizeToContent();

	m_btnNext.OnSet();
	m_btnNext.LoadBitmaps(IDB_PAGING_NEXT, IDB_PAGING_NEXT, IDB_PAGING_NEXT, IDB_PAGING_NEXT_DISABLED);
	m_btnNext.SetHoverBitmapID(IDB_PAGING_NEXT_HOVER);
	m_btnNext.SizeToContent();

	m_btnLast.OnSet();
	m_btnLast.LoadBitmaps(IDB_PAGING_LAST, IDB_PAGING_LAST, IDB_PAGING_LAST, IDB_PAGING_LAST_DISABLED);
	m_btnLast.SetHoverBitmapID(IDB_PAGING_LAST_HOVER);
	m_btnLast.SizeToContent();

	m_lblTotalpages.SetTextColor(RGB(255, 255, 255));
	m_lblTotalpages.SetFontName(_T("Times New Roman"));
	m_lblTotalpages.SetFontSize(20);

	m_lblTotalrecords.SetTextColor(RGB(255, 255, 255));
	m_lblTotalrecords.SetFontName(_T("Times New Roman"));
	m_lblTotalrecords.SetFontSize(20);

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// CUserManageList message handlers


void CUserManageList::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);

	if (m_ListHeader.m_hWnd != NULL)
	{
		m_ListHeader.SetWindowPos(NULL, 0, 0, rect.Width(), 34, SWP_NOZORDER);
	}

	if (m_pListOfUserManage != NULL)
	{
		m_pListOfUserManage->SetWindowPos(NULL, 0, 34, rect.Width(), rect.Height() - 134, SWP_NOZORDER);
	}

	int buttonWidth = 51, buttonHeight = 30, interval = 5;

	int addX, addY;

	addX = rect.Width() - interval - buttonWidth;
	addY = rect.Height() - 80;
	if (m_btnAdd.m_hWnd != NULL)
	{
		m_btnAdd.SetWindowPos(NULL, addX, addY, buttonWidth, buttonHeight, SWP_NOZORDER);
	}

	int firstX, firstY;
	firstX = rect.Width() / 2 - 25 - 2 * buttonWidth - 2 * interval;
	firstY = rect.Height() - 80;
	if (m_btnFirst.m_hWnd != NULL)
	{
		m_btnFirst.SetWindowPos(NULL, firstX, firstY, buttonWidth, buttonHeight, SWP_NOZORDER);
	}

	int prevX, prevY;
	prevX = firstX + buttonWidth + interval;
	prevY = firstY;
	if (m_btnPrev.m_hWnd != NULL)
	{
		m_btnPrev.SetWindowPos(NULL, prevX, prevY, buttonWidth, buttonHeight, SWP_NOZORDER);
	}

	int nextX, nextY;
	nextX = rect.Width() / 2 + 25 + interval;
	nextY = firstY;
	if (m_btnNext.m_hWnd != NULL)
	{
		m_btnNext.SetWindowPos(NULL, nextX, nextY, buttonWidth, buttonHeight, SWP_NOZORDER);
	}

	int lastX, lastY;
	lastX = nextX + buttonWidth + interval;
	lastY = firstY;
	if (m_btnLast.m_hWnd != NULL)
	{
		m_btnLast.SetWindowPos(NULL, lastX, lastY, buttonWidth, buttonHeight, SWP_NOZORDER);
	}

	int pageX, pageY, pageW, pageH;
	pageX = prevX + buttonWidth + interval;
	pageY = firstY;
	pageW = 50;
	pageH = buttonHeight;
	if (m_editPagenumber.m_hWnd != NULL)
	{
		m_editPagenumber.SetWindowPos(NULL, pageX, pageY, pageW, pageH, SWP_NOZORDER);
	}

	int totalrecordsX, totalrecordsY, totalrecordsW, totalrecordsH;
	totalrecordsX = 10;
	totalrecordsY = rect.Height() - 25;
	totalrecordsW = 200;
	totalrecordsH = 30;
	if (m_lblTotalrecords.m_hWnd != NULL)
	{
		m_lblTotalrecords.SetWindowPos(NULL, totalrecordsX, totalrecordsY, totalrecordsW, totalrecordsH, SWP_NOZORDER);
	}

	int totalpagesX, totalpagesY, totalpagesW, totalpagesH;
	totalpagesX = rect.Width() - 200;
	totalpagesY = totalrecordsY;
	totalpagesW = 200;
	totalpagesH = 30;
	if (m_lblTotalpages.m_hWnd != NULL)
	{
		m_lblTotalpages.SetWindowPos(NULL, totalpagesX, totalpagesY, totalpagesW, totalpagesH, SWP_NOZORDER);
	}
}


int CUserManageList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRuntimeClass *pObject;
	pObject = RUNTIME_CLASS(CListOfUserManage);
	m_pListOfUserManage = (CListOfUserManage*)pObject->CreateObject();
	if (!m_pListOfUserManage->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 100, 100), this, AFX_IDW_PANE_FIRST))
	{
		TRACE0("Failed to create ListOfUserManage");
		return -1;
	}

	m_ListHeader.Create(CCellOfUserManage::IDD, this);
	m_ListHeader.m_lblNo.SetText(_T("No"));
	m_ListHeader.m_strUsername = _T("Username");
	m_ListHeader.m_strPrivilege = _T("Privilege");
	m_ListHeader.m_strCreator = _T("Creator");
	m_ListHeader.m_strPhoneNo = _T("Phone No.");
	m_ListHeader.m_strBlocked = _T("Status");
	m_ListHeader.m_btnEdit.ShowWindow(SW_HIDE);
	m_ListHeader.m_btnDelete.ShowWindow(SW_HIDE);
	m_ListHeader.UpdateData(FALSE);
	m_ListHeader.ShowWindow(SW_SHOW);

	m_pListOfUserManage->ShowWindow(SW_SHOW);
	m_pListOfUserManage->UpdateWindow();

	return 0;
}

void CUserManageList::ShowItems(int nBeginPos, int nCount)
{
	CString strQuery;
	strQuery.Format(_T("SELECT  * FROM user_list LIMIT %d, %d"), nBeginPos, nCount);

	MYSQL_RES* result;
	int count = 0;
	result = g_pDBManager->runQuery(CW2A(strQuery.GetBuffer()));

	if (result == NULL)
	{
		AfxMessageBox(L"Error occured in refreshing user list");
		return;
	}

	if (result->row_count > 0)
	{
		int nRecordCount = 0;
		m_pListOfUserManage->m_cellsData.clear();
		while (MYSQL_ROW record = g_pDBManager->fetch_row(result))
		{
			nRecordCount++;
			tagUserManageCell cellData;
			cellData.nNo = nBeginPos + nRecordCount;
			CString strTemp;
			strTemp = record[1];
			cellData.strUsername = strTemp;
			//strTemp = record[3];
			cellData.strPrivilege = g_pDBManager->getUserPrivText(atoi(record[3]));
			strTemp = record[4];
			cellData.strCreator = strTemp;
			strTemp = record[7];
			cellData.strPhoneNo = strTemp;
			strTemp = record[6];
			cellData.strBlocked = strTemp;

			m_pListOfUserManage->m_cellsData.push_back(cellData);
		}
		m_pListOfUserManage->m_nCount = nRecordCount;
		m_pListOfUserManage->Refresh();
	}
	g_pDBManager->freeSQLResult(result);
}

void CUserManageList::ShowPage(int nPageNumber)
{
	if (nPageNumber > m_nPageCount || nPageNumber < 1)
	{
		return;
	}
	else
	{
		m_nCurrentPageNumber = nPageNumber;
		ShowItems(m_nPageCapacity * (m_nCurrentPageNumber - 1), m_nPageCapacity);

		CString strPageNum;
		strPageNum.Format(L"%d", m_nCurrentPageNumber);
		m_editPagenumber.SetWindowText(strPageNum);

		m_btnFirst.EnableWindow(m_nCurrentPageNumber > 1);
		m_btnPrev.EnableWindow(m_nCurrentPageNumber > 1);
		m_btnNext.EnableWindow(m_nCurrentPageNumber < m_nPageCount);
		m_btnLast.EnableWindow(m_nCurrentPageNumber < m_nPageCount);
	}
}

void CUserManageList::ShowFirst()
{
	ShowPage(1);
}

void CUserManageList::ShowPrev()
{
	ShowPage(m_nCurrentPageNumber - 1);
}

void CUserManageList::ShowNext()
{
	ShowPage(m_nCurrentPageNumber + 1);
}

void CUserManageList::ShowLast()
{
	ShowPage(m_nPageCount);
}

void CUserManageList::RefreshList()
{
	CString strQuery4Count;
	CString strQuery;

	strQuery4Count.Format(_T("SELECT COUNT(*) FROM user_list"));

	MYSQL_RES* result;
	int count = 0;
	result = 0;
	result = g_pDBManager->runQuery(CW2A(strQuery4Count.GetBuffer()));

	if (result == NULL)
	{
		MessageBox(_T("Error occured in refreshing user list"), _T("Error"));
		return;
	}

	if (result->row_count > 0)
	{
		MYSQL_ROW record = g_pDBManager->fetch_row(result);
		int nCount = atoi(record[0]);
		m_nRecordCount = nCount;
		m_nPageCount = (m_nRecordCount + m_nPageCapacity - 1) / m_nPageCapacity;
		CString strTotalpages, strTotalrecords;
		strTotalpages.Format(_T("%d pages"), m_nPageCount);
		strTotalrecords.Format(_T("%d records"), m_nRecordCount);
		m_lblTotalpages.SetWindowText(strTotalpages);
		m_lblTotalrecords.SetWindowText(strTotalrecords);
		ShowLast();
	}
	g_pDBManager->freeSQLResult(result);
}

void CUserManageList::OnBnClickedButtonFirst()
{
	ShowFirst();
}


void CUserManageList::OnBnClickedButtonPrev()
{
	ShowPrev();
}


void CUserManageList::OnBnClickedButtonNext()
{
	ShowNext();
}


void CUserManageList::OnBnClickedButtonLast()
{
	ShowLast();
}


BOOL CUserManageList::OnEraseBkgnd(CDC* pDC)
{
	CPropertyPage::OnEraseBkgnd(pDC);

	CRect rect;
	GetClientRect(&rect);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap;

	CBitmap bmpLightGray;
	bmpLightGray.LoadBitmap(IDB_LIGHTGRAY);
	pOldBitmap = dc.SelectObject(&bmpLightGray);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, 100, 100, SRCCOPY);
	return TRUE;
}


void CUserManageList::OnBnClickedButtonAdd()
{
	this->EnableWindow(FALSE);
	g_pUserInfo->m_nMode = MODE_USER_ADD;
	g_pUserInfo->InitializeMembers();
	g_pUserInfo->ShowWindow(SW_SHOW);
}
