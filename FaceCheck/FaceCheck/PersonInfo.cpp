// PersonInfo.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "PersonInfo.h"
#include "afxdialogex.h"
#include "ShowFace.h"
#include "FaceProcessor.h"
#include "Concentration.h"
#include "DlgOfTakePhoto.h"
#include "myGlobal.h"

CPersonInfo* g_pPersonInfo;

// CPersonInfo dialog

IMPLEMENT_DYNAMIC(CPersonInfo, CPropertyPage)

CPersonInfo::CPersonInfo()
	: CPropertyPage(CPersonInfo::IDD)
	, m_nGender(0)
	, m_nPlayerLevel(0)
	, m_nSecurityLevel(0)
	, m_dateBirthday(0)
	, m_dateBlockedWhen(0)
	, m_dateTo(0)
	, m_strFirstName(_T(""))
	, m_strLastName(_T(""))
	, m_strNickName(_T(""))
	, m_strBlockedReason(_T(""))
	, m_strBlockedPlace(_T(""))
	, m_nBlockType(0)
	, m_nBlocked(0)
{
	g_pPersonInfo = this;
}

CPersonInfo::~CPersonInfo()
{
}

void CPersonInfo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_GENDER, m_nGender);
	DDX_CBIndex(pDX, IDC_COMBO_GUESTTYPE, m_nPlayerLevel);
	DDX_CBIndex(pDX, IDC_COMBO_SAFETYTYPE, m_nSecurityLevel);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BIRTHDAY, m_dateBirthday);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_dateBlockedWhen);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_dateTo);
	DDX_Text(pDX, IDC_EDIT_FIRSTNAME, m_strFirstName);
	DDX_Text(pDX, IDC_EDIT_INFOMATION, m_strInformation);
	DDX_Text(pDX, IDC_EDIT_LASTNAME, m_strLastName);
	DDX_Text(pDX, IDC_EDIT_NICKNAME, m_strNickName);
	DDX_Text(pDX, IDC_EDIT_REASON, m_strBlockedReason);
	DDX_Text(pDX, IDC_EDIT_WHERE, m_strBlockedPlace);
	DDX_Radio(pDX, IDC_RADIO_LOCAL, m_nBlockType);
	DDX_Radio(pDX, IDC_RADIO_UNBLOCKED, m_nBlocked);
	DDX_Control(pDX, IDC_STATIC_PHOTO, m_staticPhoto);
}


BEGIN_MESSAGE_MAP(CPersonInfo, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CPersonInfo::OnBnClickedButtonOk)
	ON_STN_CLICKED(IDC_STATIC_PHOTO, &CPersonInfo::OnStnClickedStaticPhoto)
	ON_BN_CLICKED(IDC_BUTTON_FILES, &CPersonInfo::OnBnClickedButtonFiles)
	ON_EN_CHANGE(IDC_EDIT_FIRSTNAME, &CPersonInfo::OnEnChangeEditFirstname)
	ON_EN_CHANGE(IDC_EDIT_LASTNAME, &CPersonInfo::OnEnChangeEditLastname)
	ON_EN_CHANGE(IDC_EDIT_NICKNAME, &CPersonInfo::OnEnChangeEditNickname)
	ON_BN_CLICKED(IDC_BUTTON_CAMERA, &CPersonInfo::OnBnClickedButtonCamera)
END_MESSAGE_MAP()


// CPersonInfo message handlers


void CPersonInfo::OnBnClickedButtonOk()
{
	UpdateData(TRUE);

	//test if entered valid data
	if (IsDataValid() == FALSE)
		return;

	int nID = -1;
	person_info tInfo;
	int nMugCount = 0;

	int nDeltaItemCount;

	if (m_nMode == MODE_CUSTOMER_ADD)
	{
		nID = g_pDBManager->findPerson(m_strFirstName, m_strLastName);
		if (nID != -1)
		{
			if (MessageBox(_T("The name is already exist. Do you want to add photos to the existing name?"), _T("Question"), MB_YESNO | MB_ICONQUESTION) == IDYES)
				m_nMode = MODE_CUSTOMER_MUGADD;
			else
				return;
		}
	}

	switch (m_nMode)
	{
	case MODE_CUSTOMER_ADD:
		nDeltaItemCount = 1;
		GetChangedInfo(tInfo);
		nID = g_pDBManager->insertPerson(m_strFirstName, m_strLastName, m_strNickName, m_dateBirthday.Format("%Y-%m-%d"), m_nGender, m_strInformation);
		g_pDBManager->insertPersonBinaryData(nID, m_person);
		g_pDBManager->insertPersonSecurityInfo(nID, m_nPlayerLevel, m_nSecurityLevel, m_nBlocked, m_nBlockType, m_dateBlockedWhen.Format("%Y-%m-%d"), m_strBlockedPlace, m_strBlockedReason);
		g_pDBManager->insertPersonUpdateLog(nID, g_strUsername, _T("Created"), CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S"), g_strPlace, _T("Created"));
		g_pDBManager->insertUserHistory(_T("added a guest"), m_strFirstName + m_strLastName + _T(":") + m_strChanged);
		break;
	case MODE_CUSTOMER_MODIFY:
		nDeltaItemCount = 0;
		tInfo = g_pDBManager->getPersonInfoWithSecurity(m_person.m_nID);
		GetChangedInfo(tInfo);

		if (m_strChanged == _T(""))
			;// CDialogEx::OnCancel();
		else
		{
			g_pDBManager->updatePerson(m_person.m_nID, m_strFirstName, m_strLastName, m_strNickName, m_dateBirthday.Format(_T("%Y-%m-%d")), m_nGender, m_strInformation);
			g_pDBManager->insertPersonBinaryData(m_person.m_nID, m_person);
			g_pDBManager->updatePersonSecurityInfo(m_person.m_nID, m_nPlayerLevel, m_nSecurityLevel, m_nBlocked, m_nBlockType, m_dateBlockedWhen.Format(_T("%Y-%m-%d")), m_strBlockedPlace, m_strBlockedReason);
			g_pDBManager->insertPersonUpdateLog(nID, g_strUsername, _T("Modified"), CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S"), g_strPlace, m_strChanged);
			g_pDBManager->insertUserHistory(_T("modified a guest"), m_strFirstName + m_strLastName + _T(":") + m_strChanged);
		}
		break;
	case MODE_CUSTOMER_MUGADD:
		nDeltaItemCount = 0;
		g_pDBManager->insertPersonBinaryData(nID, m_person);
		g_pDBManager->insertPersonUpdateLog(nID, g_strUsername, _T("Photo added"), CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S"), g_strPlace, m_strChanged);
		g_pDBManager->insertUserHistory(_T("added photo(s)"), m_strFirstName + m_strLastName);
		break;
	default:
		MessageBox(_T("Please set Dlg mode"), _T("Message"));
	}
	//	personDB().Clear();
	g_pDBManager->reloadPersonBinaryData();
//	g_pPersonManageDialog->m_listInformation.RefreshAfterModifyList(nDeltaItemCount);

//	g_pMainCameraViewContainer->m_cameraViews[0].m_pProcessor->m_smartEngine->m_lstData.clear();

	if (m_nBlocked == 1) {
		CString input_xml;
		input_xml.Format(L"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?> \
					  		<tns:SPERRE xmlns:ns2 = \"http://www.hzd.de/authentisierung\" xmlns:tns = \"http://www.hzd.de/sperreAnlegen\"> \
								<AUTHENTISIERUNG> \
									<VERANSTALTER> \
										<KENNUNG>U2153932</KENNUNG> \
										<PASSWORT>20p28sf1paP0_Gp1</PASSWORT> \
									</VERANSTALTER> \
									<BENUTZER>000</BENUTZER> \
								</AUTHENTISIERUNG> \
								<SPERRGRUND>FREMD</SPERRGRUND> \
								<SPIELER> \
									<VORNAME>%s</VORNAME> \
									<NACHNAME>%s</NACHNAME> \
									<GEBURTSNAME>%s</GEBURTSNAME> \
									<GEBURTSDATUM>%s</GEBURTSDATUM> \
									<GEBURTSORT>Niederdolm</GEBURTSORT> \
									<ANSCHRIFT> \
										<PLZ>12345</PLZ> \
										<ORT>Gueiqoruo</ORT> \
										<STRASSE>GHgsuq Stra7e</STRASSE> \
										<HAUSNR>1</HAUSNR> \
										<LAND>000</LAND> \
									</ANSCHRIFT> \
								</SPIELER> \
								<ANLASS> \
									<KENNUNG>01</KENNUNG> \
								</ANLASS> \
							</tns:SPERRE>", m_strFirstName, m_strLastName, m_strNickName, m_dateBirthday.Format(_T("%Y-%m-%d")));

//		COasisws::curl_request("https://oasis-tst-crt.hessen.de/oasisws/rest/oasis/anlegen/sperre/4.0", input_xml);
	}

//	CDialogEx::OnOK();
}

void CPersonInfo::OnStnClickedStaticPhoto()
{
	CShowFace faceDlg(&m_person, this);

	if (faceDlg.DoModal() == IDCANCEL)
		return;

	RefreshThumbImage();
}


void CPersonInfo::OnBnClickedButtonFiles()
{
	//show FileDialog 
	CFileDialog dlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Image Files|*.bmp;*.jpg;*.png;||"),
		this);

	CString strTitle(_T("Select Photographs"));
	dlg.m_ofn.lpstrTitle = strTitle;
	dlg.m_ofn.Flags |= OFN_ALLOWMULTISELECT;

	TCHAR buffer[30000];
	ZeroMemory(buffer, sizeof(TCHAR) * 30000);
	dlg.m_ofn.lpstrFile = buffer;
	dlg.m_ofn.nMaxFile = 30000;

	if (dlg.DoModal() == IDCANCEL)
		return;


	POSITION pos = dlg.GetStartPosition();
	CArray<CString, CString >	arrayImageFilePath;
	while (pos)
		arrayImageFilePath.Add(dlg.GetNextPathName(pos));

	if (arrayImageFilePath.GetCount() <= 0)
		return;

	//find faces in the files
	FaceProcessor* faceProcessor;
	faceProcessor = new FaceProcessor;
	KipEngineHandle hFaceDetector = faceProcessor->m_smartEngine->m_hFaceDetector;
	CSingleLock _lock(&faceProcessor->m_smartEngine->m_section, TRUE);
	CxImage xSrcImage;
	int nExist = 0;

	for (int i = 0; i < (int)arrayImageFilePath.GetSize(); i++)
	{
		if (xSrcImage.Load(arrayImageFilePath[i]) == FALSE)
			continue;

		int nBitPixel = xSrcImage.GetBpp();
		if (nBitPixel < 24)
			xSrcImage.IncreaseBpp(24);
		if (nBitPixel > 24)
			xSrcImage.DecreaseBpp(24, FALSE);

		KipImageInfo pImageInfo;
		pImageInfo.width = xSrcImage.GetWidth();
		pImageInfo.height = xSrcImage.GetHeight();
		pImageInfo.format = KipImageCodeBGR24u;
		pImageInfo.step_bytes = xSrcImage.GetEffWidth();
		pImageInfo.pixel_addr = xSrcImage.GetBits();

		int nFace = KipFD_Detect(hFaceDetector, &pImageInfo);
		if (nFace <= 0)
			continue;

		KipFaceLandmark *pFaceLandmark = NULL;
		int nLandmark = KipFD_GetLandmarks(hFaceDetector, 0, &pFaceLandmark);

		RECT bound = boundLandmark(pFaceLandmark, nLandmark);

		xSrcImage.Crop(bound);
		xSrcImage.Resample(REG_IMAGE_W, REG_IMAGE_W, 1);

		KipFaceFeature pFaceFeature;
		int nSuccess = KipFD_GetFeature(hFaceDetector, &pImageInfo, 0, &pFaceFeature);

		CMugshot tMugshot;

		tMugshot.m_pdwFeature = new DWORD[DATA_DIM / 4];
		memcpy(tMugshot.m_pdwFeature, pFaceFeature.recogInfo, DATA_DIM);
		tMugshot.m_photo.m_nBpp = xSrcImage.GetBpp();
		tMugshot.m_photo.m_nHeight = xSrcImage.GetHeight();
		tMugshot.m_photo.m_nEffWidth = xSrcImage.GetEffWidth();
		tMugshot.m_photo.m_pbyBuf = new BYTE[xSrcImage.GetEffWidth() * xSrcImage.GetHeight()];
		memcpy(tMugshot.m_photo.m_pbyBuf, xSrcImage.GetBits(), xSrcImage.GetEffWidth() * xSrcImage.GetHeight());
		m_person.Add(tMugshot);

		nExist++;
	}

	_lock.Unlock();
	delete faceProcessor;

	if (nExist == 0)
	{
		MessageBox(_T("Can not find any face from the file(s)"), _T("Message"));
	}
	else
	{
		RefreshThumbImage();
		m_strChanged += _T(" Photo ");
	}
}


void CPersonInfo::OnEnChangeEditFirstname()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	CheckInput(m_strFirstName, IDC_EDIT_FIRSTNAME);
}


void CPersonInfo::OnEnChangeEditLastname()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	CheckInput(m_strLastName, IDC_EDIT_LASTNAME);
}


void CPersonInfo::OnEnChangeEditNickname()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	CheckInput(m_strNickName, IDC_EDIT_NICKNAME);
}


void CPersonInfo::OnBnClickedButtonCamera()
{
	//show TakePhotoDialog 
	CDlgOfTakePhoto dlg;

	CString strTitle(_T("Take a Photograph"));

	if (dlg.DoModal() == IDCANCEL)
		return;

	FaceProcessor* faceProcessor;
	faceProcessor = new FaceProcessor;
	KipEngineHandle hFaceDetector = faceProcessor->m_smartEngine->m_hFaceDetector;
	CSingleLock _lock(&faceProcessor->m_smartEngine->m_section, TRUE);
	CxImage xSrcImage;
	int nExist = 0;

	for (int i = 0; i < 16; i++)
	{
		//		dlg.m_pPageCamera->m_CameraViewContainer.m_cameraViews[i].getbtm
		//		if (xSrcImage.Load(arrayImageFilePath[i]) == FALSE)
		if (xSrcImage.CreateFromHBITMAP(dlg.m_pCameraViewContainer->m_cameraViews[i].m_bmpBuffer) == FALSE)
			continue;

		int nBitPixel = xSrcImage.GetBpp();
		if (nBitPixel < 24)
			xSrcImage.IncreaseBpp(24);
		if (nBitPixel > 24)
			xSrcImage.DecreaseBpp(24, FALSE);

		KipImageInfo pImageInfo;
		pImageInfo.width = xSrcImage.GetWidth();
		pImageInfo.height = xSrcImage.GetHeight();
		pImageInfo.format = KipImageCodeBGR24u;
		pImageInfo.step_bytes = xSrcImage.GetEffWidth();
		pImageInfo.pixel_addr = xSrcImage.GetBits();

		int nFace = KipFD_Detect(hFaceDetector, &pImageInfo);
		if (nFace <= 0)
			continue;

		KipFaceLandmark *pFaceLandmark = NULL;
		int nLandmark = KipFD_GetLandmarks(hFaceDetector, 0, &pFaceLandmark);

		RECT bound = boundLandmark(pFaceLandmark, nLandmark);

		xSrcImage.Crop(bound);
		xSrcImage.Resample(REG_IMAGE_W, REG_IMAGE_W, 1);

		KipFaceFeature pFaceFeature;
		int nSuccess = KipFD_GetFeature(hFaceDetector, &pImageInfo, 0, &pFaceFeature);

		CMugshot tMugshot;

		tMugshot.m_pdwFeature = new DWORD[DATA_DIM / 4];
		memcpy(tMugshot.m_pdwFeature, pFaceFeature.recogInfo, DATA_DIM);
		tMugshot.m_photo.m_nBpp = xSrcImage.GetBpp();
		tMugshot.m_photo.m_nHeight = xSrcImage.GetHeight();
		tMugshot.m_photo.m_nEffWidth = xSrcImage.GetEffWidth();
		tMugshot.m_photo.m_pbyBuf = new BYTE[xSrcImage.GetEffWidth() * xSrcImage.GetHeight()];
		memcpy(tMugshot.m_photo.m_pbyBuf, xSrcImage.GetBits(), xSrcImage.GetEffWidth() * xSrcImage.GetHeight());
		m_person.Add(tMugshot);

		nExist++;
	}

	_lock.Unlock();
	delete faceProcessor;

	if (nExist == 0)
	{
		MessageBox(_T("Can not find any face from the camera(s)"), _T("Message"));
	}
	else
	{
		RefreshThumbImage();
		m_strChanged += _T(" Photo ");
	}
}


BOOL CPersonInfo::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// init members
void CPersonInfo::InitializeMembers(void)
{
	m_person.Clear();
	m_bPhotoShow = FALSE;
	m_nGender = 0;
	m_strFirstName = _T("");
	m_strLastName = _T("");
	m_strNickName = _T("");
	m_nGender = 0;
	m_strInformation = _T("");
	m_dateBirthday = CTime::GetCurrentTime();
	m_dateBlockedWhen = CTime::GetCurrentTime();
	m_dateTo = CTime::GetCurrentTime();
	m_nSecurityLevel = 0;
	m_nPlayerLevel = 0;
	m_nBlocked = 0;
	m_nBlockType = 0;
	m_strBlockedReason = _T("");
	m_strBlockedPlace = _T("");
}

//test Person Data
BOOL CPersonInfo::IsDataValid()
{
	//test name
	if (m_strFirstName.IsEmpty())
	{
		MessageBox(_T("Please enter the Name"), _T("Message"), MB_OK | MB_ICONINFORMATION);
		return FALSE;
	}

	//if there's no photo 
	if (m_person.m_vecMugshot.size() == 0)
	{
		int nRet = MessageBox(_T("Please select photo."), _T("Message"));
		return FALSE;
	}

	return TRUE;
}

void CPersonInfo::GetChangedInfo(person_info tInfo)
{
	if (m_strFirstName != tInfo.m_strFirstname)
		m_strChanged += _T("Firstname ");
	if (m_strLastName != tInfo.m_strLastname)
		m_strChanged += _T("Lastname ");
	if (m_strNickName != tInfo.m_strNickname)
		m_strChanged += _T("Nickname ");
	if (m_dateBirthday.Format("%Y-%m-%d") != tInfo.m_strBirthday)
		m_strChanged += _T("Birthday ");
	if (m_nGender != tInfo.m_nGender)
		m_strChanged += _T("Gender ");
	if (m_strInformation != tInfo.m_strInfo)
		m_strChanged += _T("Information ");
	if (m_nPlayerLevel != tInfo.m_nPlayerLevel)
		m_strChanged += _T("PlayerLevel ");
	if (m_nSecurityLevel != tInfo.m_nSecurityLevel)
		m_strChanged += _T("SecurityLevel ");
	if (m_nBlocked != tInfo.m_nBlocked)
		m_strChanged += _T("Blocked ");
	if (m_nBlockType != tInfo.m_nBlockedType)
		m_strChanged += _T("BlockedType ");
	if (m_strBlockedReason != tInfo.m_strBlockedWhy)
		m_strChanged += _T("BlockedReason ");
	if (m_strBlockedPlace != tInfo.m_strBlockedWhere)
		m_strChanged += _T("BlockedType ");
	if (m_dateBlockedWhen.Format(_T("%Y-%m-%d")) != tInfo.m_strBlockedWhen)
		m_strChanged += _T("BlockedTime");
}

void CPersonInfo::RefreshThumbImage()
{
	if (m_person.m_vecMugshot.size() <= 0)
	{
		m_staticPhoto.SetBitmap(NULL);
		return;
	}

	HBITMAP hbmReturn = NULL;
	Bitmap image(REG_IMAGE_W, REG_IMAGE_W, PixelFormat24bppRGB);

	Rect		rc(0, 0, REG_IMAGE_W, REG_IMAGE_W);
	BitmapData	data;
	image.LockBits(&rc, ImageLockModeWrite | ImageLockModeRead, PixelFormat24bppRGB, &data);

	BYTE* pPixels = (BYTE*)data.Scan0;
	for (int h = 0; h < rc.Height; h++)
	{
		BYTE *pbyPixel = m_person.m_vecMugshot[0].m_photo.m_pbyBuf +
			(rc.Height - h - 1)*m_person.m_vecMugshot[0].m_photo.m_nEffWidth;
		pPixels = (BYTE*)data.Scan0 + data.Stride * h;
		for (int w = 0; w < rc.Width; w++)
		{
			pPixels[2] = pbyPixel[2];
			pPixels[1] = pbyPixel[1];
			pPixels[0] = pbyPixel[0];
			pPixels += 3;
			pbyPixel += 3;
		}
	}
	image.UnlockBits(&data);

	Color colorW(255, 255, 255, 255);
	image.GetHBITMAP(colorW, &hbmReturn);

	m_staticPhoto.SetBitmap(hbmReturn);
}

void CPersonInfo::CheckInput(CString &strField, int nID)
{
	char* illegalChar = "~`!@#$%^&*_+-=|\\:;\"'<>/";
	UpdateData(TRUE);
	for (int i = 0; i < strlen(illegalChar); i++)
	{
		CString szTemp;
		szTemp.Format(L"%c", illegalChar[i]);
		if (strField.Find(szTemp) != -1)
		{
			//			((CEdit*)GetDlgItem(IDC_EDIT_NAME))->Undo();
			((CEdit*)GetDlgItem(nID))->EnableToolTips();
			((CEdit*)GetDlgItem(nID))->ShowBalloonTip(L"", L"Name can't contain any of following characters:\n~ ` ! @ # $ % ^ & * _ + - = | \\ : ; \" ' < > /");
			for (int j = 0; j < strlen(illegalChar); j++)
			{
				CString strTemp;
				strTemp.Format(L"%c", illegalChar[j]);
				strField.Replace(strTemp, L"");
			}
			UpdateData(FALSE);
			((CEdit*)GetDlgItem(nID))->SendMessage(NM_KEYDOWN, VK_END);
			break;
		}
	}
	//	AfxMessageBox(L"Name can't contain any of following characters:\n~ ` ! @ # $ % ^ & * _ + - = | \\ : ; \" ' < > /");
}

void CPersonInfo::SetPersonID(int nID)
{
	this->m_nNo = nID - 1;

	//set photo image if exists
	if (m_bPhotoShow == TRUE)
	{
		((CStatic*)GetDlgItem(IDC_STATIC_PHOTO))->SetBitmap(m_imgPhoto.MakeBitmap());
	}

	m_person.m_nID = personDB()[m_nNo].m_nID;
	m_person = personDB()[m_nNo];

	person_info tInfo = g_pDBManager->getPersonInfoWithSecurity(m_person.m_nID);
	m_strFirstName = tInfo.m_strFirstname;
	m_strLastName = tInfo.m_strLastname;
	m_strNickName = tInfo.m_strNickname;
	m_nGender = tInfo.m_nGender;
	m_strInformation = tInfo.m_strInfo;
	m_nPlayerLevel = tInfo.m_nPlayerLevel;
	m_nSecurityLevel = tInfo.m_nSecurityLevel;
	m_nBlocked = tInfo.m_nBlocked;
	m_nBlockType = tInfo.m_nBlockedType;
	m_strBlockedPlace = tInfo.m_strBlockedWhere;
	m_strBlockedReason = tInfo.m_strBlockedWhy;

	int year, month, day;
	swscanf_s(tInfo.m_strBirthday.GetBuffer(), _T("%d-%d-%d"), &year, &month, &day);
	m_dateBirthday = CTime(year, month, day, 0, 0, 0);

	swscanf_s(tInfo.m_strBlockedWhen.GetBuffer(), _T("%d-%d-%d"), &year, &month, &day);
	m_dateBlockedWhen = CTime(year, month, day, 0, 0, 0);

	RefreshThumbImage();
	UpdateData(FALSE);

	m_strChanged = _T("");
}