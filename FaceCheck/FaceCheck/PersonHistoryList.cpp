// PersonHistoryList.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "PersonHistoryList.h"
#include "afxdialogex.h"


// CPersonHistoryList dialog

IMPLEMENT_DYNAMIC(CPersonHistoryList, CPropertyPage)

CPersonHistoryList::CPersonHistoryList()
	: CPropertyPage(CPersonHistoryList::IDD)
{

}

CPersonHistoryList::~CPersonHistoryList()
{
}

void CPersonHistoryList::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(CPersonHistoryList, CPropertyPage)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_FIRST, &CPersonHistoryList::OnBnClickedButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_PREV, &CPersonHistoryList::OnBnClickedButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CPersonHistoryList::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_LAST, &CPersonHistoryList::OnBnClickedButtonLast)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CPersonHistoryList message handlers


void CPersonHistoryList::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);
	if (m_pListOfPersonHistory != NULL)
	{
		m_pListOfPersonHistory->SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height() - 100, SWP_NOZORDER);
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


int CPersonHistoryList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRuntimeClass *pObject;
	pObject = RUNTIME_CLASS(CListOfPersonHistory);
	m_pListOfPersonHistory = (CListOfPersonHistory*)pObject->CreateObject();
	if (!m_pListOfPersonHistory->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 100, 100), this, AFX_IDW_PANE_FIRST))
	{
		TRACE0("Failed to create ListOfPersonHistory");
		return -1;
	}

	m_pListOfPersonHistory->ShowWindow(SW_SHOW);
	m_pListOfPersonHistory->UpdateWindow();

	return 0;
}

BOOL CPersonHistoryList::OnInitDialog()
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

void CPersonHistoryList::ShowItems(int nBeginPos, int nCount)
{
	CString strQuery;
	strQuery.Format(_T("SELECT * FROM monitor_history JOIN person_list ON monitor_history.id = person_list.id LIMIT %d, %d"), nBeginPos, nCount);

	MYSQL_RES* result;
	result = g_pDBManager->runQuery(CW2A(strQuery.GetBuffer()));

	if (result == NULL)
	{
		AfxMessageBox(L"Error occured in refreshing person list");
		return;
	}

	if (result->row_count > 0)
	{
		int nRecordCount = 0;
		m_pListOfPersonHistory->m_cellsData.clear();
		while (MYSQL_ROW record = g_pDBManager->fetch_row(result))
		{
			nRecordCount++;
			tagPersonHistoryCell cellData;
			cellData.nNo = nBeginPos + nRecordCount;
			int nbpp, nEffWidth, nHeight;
			nbpp = atoi(record[5]);
			nEffWidth = atoi(record[6]);
			nHeight = atoi(record[7]);

			BYTE* pbyBuf = new BYTE[nEffWidth * nHeight];
			memcpy(pbyBuf, record[4], nEffWidth * nHeight);

			CxImage * img = new CxImage();

			img->CreateFromArray(pbyBuf, CUSTOMER_PHOTO_WIDTH, CUSTOMER_PHOTO_HEIGHT, nbpp, nEffWidth, FALSE);

			delete[] pbyBuf;

			HBITMAP hBmpRegistered = img->MakeBitmap();
			cellData.hPhoto = hBmpRegistered;

//			DeleteObject(hBmpRegistered);
			//delete img;
			img->~CxImage();
			free(img);
			img = NULL;

			CString strTemp;
			cellData.strName = g_pDBManager->getPersonName(atoi(record[1]));
			cellData.strGender = (atoi(record[2]) == 0 ? _T("Male") : _T("Female"));
			strTemp = record[3];
			cellData.strAge = strTemp;
			strTemp = record[8];
			cellData.strTime = strTemp;
			strTemp = record[9];
			cellData.strPlace = strTemp;
			strTemp = record[10];
			cellData.strView = strTemp;
			strTemp = record[11];
			cellData.strComment = strTemp;

			m_pListOfPersonHistory->m_cellsData.push_back(cellData);
		}
		m_pListOfPersonHistory->m_nCount = nRecordCount;
		m_pListOfPersonHistory->Refresh();
	}
	g_pDBManager->freeSQLResult(result);
}

void CPersonHistoryList::ShowPage(int nPageNumber)
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

void CPersonHistoryList::ShowFirst()
{
	ShowPage(1);
}

void CPersonHistoryList::ShowPrev()
{
	ShowPage(m_nCurrentPageNumber - 1);
}

void CPersonHistoryList::ShowNext()
{
	ShowPage(m_nCurrentPageNumber + 1);
}

void CPersonHistoryList::ShowLast()
{
	ShowPage(m_nPageCount);
}

void CPersonHistoryList::RefreshList()
{
	CString strQuery4Count;
	CString strQuery;

	strQuery4Count.Format(_T("SELECT COUNT(*) FROM monitor_history JOIN person_list ON monitor_history.id = person_list.id"));

	MYSQL_RES* result;
	int count = 0;
	result = 0;
	result = g_pDBManager->runQuery(CW2A(strQuery4Count.GetBuffer()));

	if (result == NULL)
	{
		MessageBox(_T("Error occured in refreshing person list"), _T("Error"));
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


void CPersonHistoryList::OnBnClickedButtonFirst()
{
	ShowFirst();
}


void CPersonHistoryList::OnBnClickedButtonPrev()
{
	ShowPrev();
}


void CPersonHistoryList::OnBnClickedButtonNext()
{
	ShowNext();
}


void CPersonHistoryList::OnBnClickedButtonLast()
{
	ShowLast();
}


BOOL CPersonHistoryList::OnEraseBkgnd(CDC* pDC)
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
