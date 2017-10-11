// CellOfMonitorHistory.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "CellOfMonitorHistory.h"
#include "afxdialogex.h"
#include "PersonInfo.h"
#include "DlgOfAddComment.h"

// CCellOfMonitorHistory dialog

IMPLEMENT_DYNAMIC(CCellOfMonitorHistory, CPropertyPage)

CCellOfMonitorHistory::CCellOfMonitorHistory()
	: CPropertyPage(CCellOfMonitorHistory::IDD)
	, m_strName(_T(""))
	, m_strAgeNGender(_T(""))
	, m_strAccessedwhen(_T(""))
	, m_strStatus(_T(""))
{

}

CCellOfMonitorHistory::~CCellOfMonitorHistory()
{
}

void CCellOfMonitorHistory::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PHOTO, m_staticPhoto);
	DDX_Control(pDX, IDC_STATIC_PHOTO_REGISTERED, m_staticPhotoRegistered);
	DDX_Text(pDX, IDC_STATIC_NAME, m_strName);
	DDX_Text(pDX, IDC_STATIC_AGEGENDER, m_strAgeNGender);
	DDX_Text(pDX, IDC_STATIC_ACCESSEDWHEN, m_strAccessedwhen);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_strStatus);
	DDX_Control(pDX, IDC_STATIC_NAME, m_lblName);
	DDX_Control(pDX, IDC_STATIC_AGEGENDER, m_lblAgeGender);
	DDX_Control(pDX, IDC_STATIC_ACCESSED, m_lblAccessed);
	DDX_Control(pDX, IDC_STATIC_ACCESSEDWHEN, m_lblAccessedWhen);
	DDX_Control(pDX, IDC_STATIC_STATUSLABEL, m_lblStatus1);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_lblStatus);
}


BEGIN_MESSAGE_MAP(CCellOfMonitorHistory, CPropertyPage)
	ON_WM_ERASEBKGND()
	ON_STN_CLICKED(IDC_STATIC_PHOTO, &CCellOfMonitorHistory::OnStnClickedStaticPhoto)
END_MESSAGE_MAP()


// CCellOfMonitorHistory message handlers


BOOL CCellOfMonitorHistory::OnEraseBkgnd(CDC* pDC)
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


BOOL CCellOfMonitorHistory::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_lblName.SetTextColor(RGB(255, 255, 255));
	m_lblAgeGender.SetTextColor(RGB(255, 255, 255));
	m_lblAccessed.SetTextColor(RGB(255, 255, 255));
	m_lblAccessedWhen.SetTextColor(RGB(255, 255, 255));
	m_lblStatus1.SetTextColor(RGB(255, 255, 255));
	m_lblStatus.SetTextColor(RGB(255, 255, 255));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CCellOfMonitorHistory::OnStnClickedStaticPhoto()
{	
	int nPersonID = g_pDBManager->getPersonIdFromIdx(m_nIDX);

	if (nPersonID != NON_EMPLOYEE)
		{
			//dlgMan.m_nMode = MODE_CUSTOMER_MODIFY;
			//int nIndex = personDB().IsExist(g_pDBManager->getPersonIdFromIdx(m_listHistory.GetItemData(pNMItemActivate->iItem)));
			//dlgMan.m_strNo.Format(_T("%d"), nIndex + 1);
			CDlgOfAddComment dlgComment(nPersonID);
			dlgComment.DoModal();
		}
		else
		{
			CPersonInfo dlgMan;
			dlgMan.m_nMode = MODE_CUSTOMER_ADD;

			FaceProcessor* faceProcessor;
			faceProcessor = new FaceProcessor;
			KipEngineHandle hFaceDetector = faceProcessor->m_smartEngine->m_hFaceDetector;
			CSingleLock _lock(&faceProcessor->m_smartEngine->m_section, TRUE);

			CxImage imgPhoto;
			imgPhoto = g_pDBManager->getHistoryImage(m_nIDX);
			KipImageInfo pImageInfo;
			pImageInfo.width = imgPhoto.GetWidth();
			pImageInfo.height = imgPhoto.GetHeight();
			pImageInfo.format = KipImageCodeBGR24u;
			pImageInfo.step_bytes = imgPhoto.GetEffWidth();
			pImageInfo.pixel_addr = imgPhoto.GetBits();

			int nFace = KipFD_Detect(hFaceDetector, &pImageInfo);
			if (nFace <= 0)
				return;

			KipFaceFeature pFaceFeature;
			int nSuccess = KipFD_GetFeature(hFaceDetector, &pImageInfo, 0, &pFaceFeature);

			CMugshot tMugshot;
			tMugshot.m_pdwFeature = new DWORD[DATA_DIM / 4];
			memcpy(tMugshot.m_pdwFeature, pFaceFeature.recogInfo, DATA_DIM);
			tMugshot.m_photo.m_nBpp = imgPhoto.GetBpp();
			tMugshot.m_photo.m_nHeight = imgPhoto.GetHeight();
			tMugshot.m_photo.m_nEffWidth = imgPhoto.GetEffWidth();
			tMugshot.m_photo.m_pbyBuf = new BYTE[imgPhoto.GetEffWidth() * imgPhoto.GetHeight()];
			memcpy(tMugshot.m_photo.m_pbyBuf, imgPhoto.GetBits(), imgPhoto.GetEffWidth() * imgPhoto.GetHeight());

			dlgMan.m_imgPhoto = imgPhoto;
			dlgMan.m_person.Add(tMugshot);
			dlgMan.m_person.m_nID = NON_EMPLOYEE;
			dlgMan.m_bPhotoShow = TRUE;

			_lock.Unlock();
			delete faceProcessor;

			if (dlgMan.DoModal() == IDCANCEL)
				return;

		}
}
