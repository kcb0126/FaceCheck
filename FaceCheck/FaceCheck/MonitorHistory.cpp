// MonitorHistory.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "MonitorHistory.h"
#include "afxdialogex.h"



CMonitorHistory* g_pMonitorHistory;

// CMonitorHistory dialog

IMPLEMENT_DYNAMIC(CMonitorHistory, CPropertyPage)

CMonitorHistory::CMonitorHistory()
	: CPropertyPage(CMonitorHistory::IDD)
{
	g_pMonitorHistory = this;
}

CMonitorHistory::~CMonitorHistory()
{
	// Don't need to delete m_pListOfMonitorHistory;
}

void CMonitorHistory::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(CMonitorHistory, CPropertyPage)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_FIRST, &CMonitorHistory::OnBnClickedButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_PREV, &CMonitorHistory::OnBnClickedButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CMonitorHistory::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_LAST, &CMonitorHistory::OnBnClickedButtonLast)
	ON_WM_ERASEBKGND()
	ON_MESSAGE(UM_ADD_HISTORY, &CMonitorHistory::OnUmAddHistory)
END_MESSAGE_MAP()


// CMonitorHistory message handlers


BOOL CMonitorHistory::OnInitDialog()
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

	m_dlgOfWarning.Create(CDlgOfWarning::IDD);
	m_dlgOfWarning.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CMonitorHistory::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);
	if (m_pListOfMonitorHistory != NULL)
	{
		m_pListOfMonitorHistory->SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height() - 100, SWP_NOZORDER);
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


int CMonitorHistory::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRuntimeClass *pObject;
	pObject = RUNTIME_CLASS(CListOfMonitorHistory);
	m_pListOfMonitorHistory = (CListOfMonitorHistory*)pObject->CreateObject();
	//	m_pListOfMonitorHistory = new CListOfMonitorHistory;
	if (!m_pListOfMonitorHistory->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 100, 100), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create ListOfMonitorHistory");
		return -1;
	}

	m_pListOfMonitorHistory->ShowWindow(SW_SHOW);
	m_pListOfMonitorHistory->UpdateWindow();

	return 0;
}

void CMonitorHistory::ShowItems(int nBeginPos, int nCount)
{
	CString strQuery;
	strQuery.Format(_T("SELECT * FROM monitor_history LIMIT %d, %d"), nBeginPos, nCount);

	MYSQL_RES* result;
	int count = 0;
	result = g_pDBManager->runQuery(CW2A(strQuery.GetBuffer()));

	if (result == NULL)
	{
		AfxMessageBox(_T("Error occured in refreshing monitor history."));
		return;
	}
	else
	{
		int nRecordCount = 0;
		m_pListOfMonitorHistory->m_cellsData.clear();
		while (MYSQL_ROW record = mysql_fetch_row(result))
		{
			nRecordCount ++;
			tagMonitorHistoryCell cellData;
			FaceData data;
			data.initialize(); // Added by Koo to prevent memoryleak
			int nIdx, nView;
			CString strComment, strCommentDate;
			CString strTime;
			CString strQuery;

			nIdx = atoi(record[0]);

			data.id = atoi(record[1]);
			data.gender = atoi(record[2]);
			data.age = atoi(record[3]);

			int nbpp, nEffWidth, nHeight;
			nbpp = atoi(record[5]);
			nEffWidth = atoi(record[6]);
			nHeight = atoi(record[7]);

			BYTE* pbyBuf = new BYTE[nEffWidth * nHeight];
			memcpy(pbyBuf, record[4], nEffWidth * nHeight);

			CxImage * img = new CxImage();
			img->CreateFromArray(pbyBuf, CUSTOMER_PHOTO_WIDTH, CUSTOMER_PHOTO_HEIGHT, nbpp, nEffWidth, FALSE);

			data.imgCamera = img;

			strTime = record[8];
			nView = atoi(record[10]);
			strComment = record[11];
			strCommentDate = record[12];

			{
				HBITMAP hBmpCamera;
				HBITMAP hBmpRegistered;
				CBitmap bmp;
				CBitmap BmpRegistered;
				
				CSingleLock _lock(&(m_secData), TRUE);
				hBmpCamera = data.imgCamera->MakeBitmap();
				cellData.hPhoto = hBmpCamera;
//				DeleteObject(hBmpCamera);

				person_info tInfo;

				if (data.id != NON_EMPLOYEE)
				{
					CxImage* photo = personDB().CreatePhoto(personDB().IsExist(data.id));
					hBmpRegistered = photo->MakeBitmap();

					photo->~CxImage();		// Added by Koo to prevent memoryleak
					free(photo);
					photo = NULL;

					cellData.hPhotoRegistered = hBmpRegistered;
//					DeleteObject(hBmpRegistered);

					tInfo = g_pDBManager->getPersonInfoWithSecurity(data.id);
				}
				else
				{
					BmpRegistered.LoadBitmap(IDB_UNREGISTERED);
					hBmpRegistered = (HBITMAP)BmpRegistered.Detach();
					cellData.hPhotoRegistered = hBmpRegistered;
					tInfo.m_nBlocked = 0;
				}

				cellData.strName = data.id == NON_EMPLOYEE ? _T("Unknown") : g_pDBManager->getPersonName(data.id);
				cellData.strAgeGender.Format(_T("%d %s"), data.age, (data.gender == 0 ? _T("Male") : _T("Female")));
				cellData.strAccessedWhen = strTime;
				cellData.strStatus = tInfo.m_nBlocked ? _T("Blocked") : _T("Not blocked");
				
				data.cleanMemory();	// Added by Koo to prevent memoryleak

			}

			m_pListOfMonitorHistory->m_cellsData.push_back(cellData);

			// Don't need clean data 'cause it was already cleaned in AddToList();
			delete[] pbyBuf;
		}
		m_pListOfMonitorHistory->m_nCount = nRecordCount;
		m_pListOfMonitorHistory->Refresh();

		if (result)
			mysql_free_result(result);
	}
}

void CMonitorHistory::ShowPage(int nPageNumber)
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

void CMonitorHistory::ShowFirst()
{
	ShowPage(1);
}

void CMonitorHistory::ShowPrev()
{
	ShowPage(m_nCurrentPageNumber - 1);
}

void CMonitorHistory::ShowNext()
{
	ShowPage(m_nCurrentPageNumber + 1);
}

void CMonitorHistory::ShowLast()
{
	ShowPage(m_nPageCount);
}

void CMonitorHistory::RefreshList()
{
	CString strQuery4Count;
	CString strQuery;

	strQuery4Count.Format(_T("SELECT COUNT(*) FROM monitor_history"));

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

void CMonitorHistory::AppendItem(tagMonitorHistoryCell cellData)
{
	m_nRecordCount++;
	int nOldPageCount = m_nPageCount;
	m_nPageCount = (m_nRecordCount + m_nPageCapacity - 1) / m_nPageCapacity;

	CString strTotalpages, strTotalrecords;
	strTotalpages.Format(_T("%d pages"), m_nPageCount);
	strTotalrecords.Format(_T("%d records"), m_nRecordCount);
	m_lblTotalpages.SetWindowText(strTotalpages);
	m_lblTotalrecords.SetWindowText(strTotalrecords);
	RedrawWindow();
	UpdateData(FALSE);

	if (m_nCurrentPageNumber == nOldPageCount)
	{
		if (nOldPageCount == m_nPageCount)
		{
			m_pListOfMonitorHistory->m_cellsData.push_back(cellData);
			m_pListOfMonitorHistory->m_nCount++;
			m_pListOfMonitorHistory->RefreshAfterAppend();
		}
		else
		{
			ShowLast();
		}
	}
}

void CMonitorHistory::OnBnClickedButtonFirst()
{
	ShowFirst();
}


void CMonitorHistory::OnBnClickedButtonPrev()
{
	ShowPrev();
}


void CMonitorHistory::OnBnClickedButtonNext()
{
	ShowNext();
}


void CMonitorHistory::OnBnClickedButtonLast()
{
	ShowLast();
}


BOOL CMonitorHistory::OnEraseBkgnd(CDC* pDC)
{
	CPropertyPage::OnEraseBkgnd(pDC);

	if (!pDC)return FALSE;

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

CString strQuery4Insert;

afx_msg LRESULT CMonitorHistory::OnUmAddHistory(WPARAM wParam, LPARAM lParam)
{
	tagFaceData* facedata = (tagFaceData*)wParam;

	int nView = (int)lParam;
	{
		CString strQuery;

		int nAge, nGender;
		//			if (facedata->bIsEmployee)
		if (facedata->id != -1)
		{
			nAge = CTime::GetCurrentTime().GetYear() - StrToInt(g_pDBManager->getPersonInfoWithSecurity(facedata->id).m_strBirthday.Left(4));
			nGender = g_pDBManager->getPersonInfoWithSecurity(facedata->id).m_nGender;

			facedata->age = nAge;
			facedata->gender = nGender;
		}
		else
		{
			nAge = facedata->age;
			nGender = facedata->gender > 50 ? 0 : 1;
		}

		CString csPhoto, csFeature;
		char* szPhoto;
		int nPhotoRealSize, nPhotoSaveSize;

		//change photo binary to string in order to save table
		nPhotoRealSize = facedata->imgCamera->GetEffWidth() * facedata->imgCamera->GetHeight();
		nPhotoSaveSize = nPhotoRealSize * 2 + 3; //+3 = '0','x',...'\0'
		szPhoto = new char[nPhotoSaveSize];
		strcpy(szPhoto, "0x");
		mysql_hex_string(szPhoto + 2, (char *)(facedata->imgCamera->GetBits()), nPhotoRealSize);
		csPhoto = szPhoto;

		g_pDBManager->m_strLastInsertedTime = CTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S"));
		g_pDBManager->m_nLastInsertedView = nView;

		strQuery.Format(_T("INSERT INTO monitor_history (id, gender, age, photo_data, photo_bpp, photo_effwidth, photo_height, time, place, view) VALUES ( %d, %d, %d, %s, %d, %d, %d, '%s','%s', %d)")
			, facedata->id
			, nGender
			, nAge
			, csPhoto
			, facedata->imgCamera->GetBpp()
			, facedata->imgCamera->GetEffWidth()
			, facedata->imgCamera->GetHeight()
			, g_pDBManager->m_strLastInsertedTime
			, g_strPlace
			, nView);

		strQuery4Insert = strQuery;

		AfxBeginThread(DoInsert, NULL);
		//			g_pDBManager->runQueryWithoutResult(CW2A(strQuery.GetBuffer()));

		if (facedata->age < AGE_LIMIT)
		{
			MessageBeep(MB_ICONERROR);

			m_dlgOfWarning.SetDlgItemText(IDOK, L"Forbidden Age!");
			m_dlgOfWarning.m_nWarningType = 0;
			m_dlgOfWarning.ShowWindow(SW_SHOW);
			m_dlgOfWarning.StartWarning();
		}
		else if (facedata->age <= 25)
		{
			m_dlgOfWarning.SetDlgItemText(IDOK, L"Check IDCard!");
			m_dlgOfWarning.m_nWarningType = 1;
			m_dlgOfWarning.ShowWindow(SW_SHOW);
			m_dlgOfWarning.StartWarning();
		}
		if (!facedata->bIsEmployee)
		{
			MessageBeep(MB_ICONERROR);

			//				g_pWarningDialog->SetDlgItemText(IDOK, L"Person/Guest\nCheck ID Card!");
			//				g_pWarningDialog->ShowWindow(SW_SHOW);
		}

		person_info tInfo = g_pDBManager->getPersonInfoWithSecurity(facedata->id);

		if (tInfo.m_nBlocked && facedata->id != -1)
		{
			MessageBeep(MB_ICONERROR);

			m_dlgOfWarning.SetDlgItemText(IDOK, L"Blocked!");
			m_dlgOfWarning.ShowWindow(SW_SHOW);
			m_dlgOfWarning.StartWarning();
		}

		tagMonitorHistoryCell cellData;
		cellData.hPhoto = facedata->imgCamera->MakeBitmap();
		if (facedata->id != NON_EMPLOYEE)
		{
			CxImage* photo = personDB().CreatePhoto(personDB().IsExist(facedata->id));
			cellData.hPhotoRegistered = photo->MakeBitmap();

			photo->~CxImage();		// Added by Koo to prevent memoryleak
			free(photo);
			photo = NULL;

			tInfo = g_pDBManager->getPersonInfoWithSecurity(facedata->id);
		}
		else
		{
			CBitmap bmpUnregistered;
			bmpUnregistered.LoadBitmap(IDB_UNREGISTERED);
			cellData.hPhotoRegistered = (HBITMAP)bmpUnregistered.Detach();;
//			cellData.hPhotoRegistered = (HBITMAP)bmpUnregistered.m_hObject;
			tInfo.m_nBlocked = 0;
		}

		cellData.strName = facedata->id == NON_EMPLOYEE ? _T("Unknown") : g_pDBManager->getPersonName(facedata->id);
		cellData.strAgeGender.Format(L"%d %s", facedata->age, (facedata->gender >= 50 || facedata->gender == 0) ? _T("Male") : _T("Female"));
		cellData.strAccessedWhen = g_pDBManager->m_strLastInsertedTime;
		cellData.strStatus = tInfo.m_nBlocked ? "blocked" : "unblocked";
		//			g_pDBManager->freeSQLResult(resultTemp);
		this->AppendItem(cellData);
	}

	return 0;
}

UINT DoInsert(void *pData)
{
	CString strQuery = strQuery4Insert;
	g_pDBManager->runQueryWithoutResult(CW2A(strQuery.GetBuffer()));

	//	MYSQL_RES* resultTemp = g_pDBManager->runQuery(CW2A(L"SELECT MAX(id) from monitor_history"));
	//	MYSQL_ROW recordTemp = g_pDBManager->fetch_row(resultTemp);
	//	int nIdx = atoi(recordTemp[0]);
	//	g_pDBManager->m_nMaxIDinMonitorHistory = nIdx;

	return 0;
}
