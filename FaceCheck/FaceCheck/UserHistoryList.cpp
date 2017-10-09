// UserHistoryList.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "UserHistoryList.h"
#include "afxdialogex.h"
#include "UserHistoryList.h"

CUserHistoryList* g_pUserHistory;

// CUserHistoryList dialog

IMPLEMENT_DYNAMIC(CUserHistoryList, CPropertyPage)

CUserHistoryList::CUserHistoryList()
	: CPropertyPage(CUserHistoryList::IDD)
{
	g_pUserHistory = this;
}

CUserHistoryList::~CUserHistoryList()
{
}

void CUserHistoryList::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_FIRST, m_btnFirst);
	DDX_Control(pDX, IDC_BUTTON_PREV, m_btnPrev);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_btnNext);
	DDX_Control(pDX, IDC_BUTTON_LAST, m_btnLast);
	DDX_Control(pDX, IDC_EDIT_PAGE, m_editPagenumber);
	DDX_Control(pDX, IDC_STATIC_TOTALRECORDS, m_lblTotalrecords);
	DDX_Control(pDX, IDC_STATIC_TOTALPAGES, m_lblTotalpages);
}


BEGIN_MESSAGE_MAP(CUserHistoryList, CPropertyPage)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_FIRST, &CUserHistoryList::OnBnClickedButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_PREV, &CUserHistoryList::OnBnClickedButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CUserHistoryList::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_LAST, &CUserHistoryList::OnBnClickedButtonLast)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BOOL CUserHistoryList::OnInitDialog()
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

// CUserHistoryList message handlers


int CUserHistoryList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRuntimeClass *pObject;
	pObject = RUNTIME_CLASS(CListOfUserHistory);
	m_pListOfUserHistory = (CListOfUserHistory*)pObject->CreateObject();
	if (!m_pListOfUserHistory->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 100, 100), this, AFX_IDW_PANE_FIRST))
	{
		TRACE0("Failed to create ListOfUserHistory");
		return -1;
	}

	m_pListOfUserHistory->ShowWindow(SW_SHOW);
	m_pListOfUserHistory->UpdateWindow();

	m_listHeader.Create(CCellOfUserHistory::IDD, this);
	m_listHeader.m_lblNo.SetText(_T("No"));
	m_listHeader.m_strUsername = _T("Username");
	m_listHeader.m_strAction = _T("Action");
	m_listHeader.m_strTime = _T("Time");
	m_listHeader.m_strContent = _T("Content");
	m_listHeader.UpdateData(FALSE);
	m_listHeader.ShowWindow(SW_SHOW);

	return 0;
}


void CUserHistoryList::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);

	if (m_listHeader.m_hWnd != NULL)
	{
		m_listHeader.SetWindowPos(NULL, 0, 0, rect.Width(), 25, SWP_NOZORDER);
	}

	if (m_pListOfUserHistory != NULL)
	{
		m_pListOfUserHistory->SetWindowPos(NULL, 0, 25, rect.Width(), rect.Height() - 125, SWP_NOZORDER);
	}

	int buttonWidth = 51, buttonHeight = 30, interval = 5;

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

void CUserHistoryList::ShowItems(int nBeginPos, int nCount)
{
	CString strQuery;
	strQuery.Format(_T("SELECT  t0.user_id, t0.taken_action, t0.action_datetime, t0.info  FROM user_history AS t0 LEFT JOIN user_list AS t1 ON t0.user_id = t1.id LIMIT %d, %d"), nBeginPos, nCount);

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
		m_pListOfUserHistory->m_cellsData.clear();
		while (MYSQL_ROW record = g_pDBManager->fetch_row(result))
		{
			nRecordCount++;
			tagUserHistoryCell cellData;
			cellData.nNo = nBeginPos + nRecordCount;
			cellData.strUsername = g_pDBManager->getUserName(atoi(record[0]));
			cellData.strAction = record[1];
			cellData.strTime = record[2];
			cellData.strContent = record[3];
			m_pListOfUserHistory->m_cellsData.push_back(cellData);
		}
		m_pListOfUserHistory->m_nCount = nRecordCount;
		m_pListOfUserHistory->Refresh();
	}
	g_pDBManager->freeSQLResult(result);
}

void CUserHistoryList::ShowPage(int nPageNumber)
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

void CUserHistoryList::ShowFirst()
{
	ShowPage(1);
}

void CUserHistoryList::ShowPrev()
{
	ShowPage(m_nCurrentPageNumber - 1);
}

void CUserHistoryList::ShowNext()
{
	ShowPage(m_nCurrentPageNumber + 1);
}

void CUserHistoryList::ShowLast()
{
	ShowPage(m_nPageCount);
}

void CUserHistoryList::RefreshList()
{
	CString strQuery4Count;
	CString strQuery;

	strQuery4Count.Format(_T("SELECT COUNT(*) FROM user_history AS t0 LEFT JOIN user_list AS t1 ON t0.user_id = t1.id"));

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

void CUserHistoryList::OnBnClickedButtonFirst()
{
	ShowFirst();
}


void CUserHistoryList::OnBnClickedButtonPrev()
{
	ShowPrev();
}


void CUserHistoryList::OnBnClickedButtonNext()
{
	ShowNext();
}


void CUserHistoryList::OnBnClickedButtonLast()
{
	ShowLast();
}


BOOL CUserHistoryList::OnEraseBkgnd(CDC* pDC)
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
