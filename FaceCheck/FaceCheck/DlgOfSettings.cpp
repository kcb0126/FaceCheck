// DlgOfSettings.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "DlgOfSettings.h"
#include "afxdialogex.h"
#include "myGlobal.h"

// CDlgOfSettings dialog

IMPLEMENT_DYNAMIC(CDlgOfSettings, CDialogEx)

CDlgOfSettings::CDlgOfSettings(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgOfSettings::IDD, pParent)
	, m_strAddress(_T(""))
	, m_strDBName(_T(""))
	, m_strPassword(_T(""))
	, m_strPlace(_T(""))
	, m_nPort(0)
	, m_nSyncPeriod(0)
	, m_strLevel(_T(""))
	, m_strUsername(_T(""))
	, m_nFov(0)
	, m_fAutorun(FALSE)
{
	m_strLevel = _T("");
	m_strAddress = AfxGetApp()->GetProfileString(_T("Setting"), _T("Address"), _T("85.214.18.79"));
	m_nPort = AfxGetApp()->GetProfileInt(_T("Setting"), _T("Port"), 3306);
	m_strDBName = AfxGetApp()->GetProfileString(_T("Setting"), _T("DBName"), _T("facecheck_db"));
	m_strUsername = AfxGetApp()->GetProfileString(_T("Setting"), _T("UserName"), _T("facecheck_user"));
	m_strPassword = AfxGetApp()->GetProfileString(_T("Setting"), _T("Password"), _T("facecheck@123"));
	m_strPlace = AfxGetApp()->GetProfileString(_T("Setting"), _T("Place"), _T("Unknown"));
	m_nSyncPeriod = AfxGetApp()->GetProfileInt(_T("Setting"), _T("SyncPeriod"), 5);

	m_fAutorun = AfxGetApp()->GetProfileInt(_T("Setting"), _T("Autorun"), -1);
	if (m_fAutorun == -1)
	{
		SetAutorun(TRUE);
		m_fAutorun = TRUE;
	}

	m_nFov = AfxGetApp()->GetProfileInt(_T("FaceOption"), _T("FOV"), 55);
	g_strPlace = m_strPlace;
}

CDlgOfSettings::~CDlgOfSettings()
{
}

void CDlgOfSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SETTINGS_ADDRESS, m_strAddress);
	DDX_Text(pDX, IDC_EDIT_SETTINGS_DBNAME, m_strDBName);
	DDX_Text(pDX, IDC_EDIT_SETTINGS_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT1, m_strPlace);
	DDX_Text(pDX, IDC_EDIT_SETTINGS_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_SETTINGS_SYNCTIME, m_nSyncPeriod);
	DDV_MinMaxInt(pDX, m_nSyncPeriod, 1, 60);
	DDX_Text(pDX, IDC_STATIC_SETTINGS_LEVEL, m_strLevel);
	DDX_Control(pDX, IDC_SLIDER_SETTINGS_THRESHOLDLEVEL, m_slider);
	DDX_Text(pDX, IDC_EDIT_SETTINGS_USERNAME, m_strUsername);
	DDX_Control(pDX, IDC_SPIN_SETTINGS_SYNCTIME, m_spinChangePeriod);
	DDX_Text(pDX, IDC_EDIT_SETTINGS_FOV, m_nFov);
	DDV_MinMaxInt(pDX, m_nFov, 20, 80);
	DDX_Check(pDX, IDC_CHECK_SETTINGS_AUTORUN, m_fAutorun);
}


BEGIN_MESSAGE_MAP(CDlgOfSettings, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SETTINGS_THRESHOLDLEVEL, &CDlgOfSettings::OnNMCustomdrawSliderSettingsThresholdlevel)
	ON_BN_CLICKED(IDC_BUTTON_SETTINGS_APPLY, &CDlgOfSettings::OnBnClickedButtonSettingsApply)
	ON_BN_CLICKED(IDC_BUTTON_SETTINGS_DEFAULT, &CDlgOfSettings::OnBnClickedButtonSettingsDefault)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SETTINGS_SYNCTIME, &CDlgOfSettings::OnDeltaposSpinSettingsSynctime)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SETTINGS_EXPORT, &CDlgOfSettings::OnBnClickedButtonSettingsExport)
	ON_BN_CLICKED(IDC_BUTTON_SETTINGS_IMPORT, &CDlgOfSettings::OnBnClickedButtonSettingsImport)
END_MESSAGE_MAP()


// CDlgOfSettings message handlers


BOOL CDlgOfSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_slider.SetRange(1, 5);
	m_slider.SetPos(AfxGetApp()->GetProfileInt(_T("FaceOption"), _T("ThresholdLevel"), 3));
	m_strLevel = getString(m_slider.GetPos());

	m_spinChangePeriod.SetRange(2, 59);
	m_spinChangePeriod.SetPos(m_nSyncPeriod);
	m_spinChangePeriod.SetBuddy(GetDlgItem(IDC_EDIT_SETTINGS_SYNCTIME));

	SetTimer(ID_SYNC_TIMER, m_nSyncPeriod * 60 * 1000, NULL);

	UpdateData(FALSE);

	m_slider.SetPos(AfxGetApp()->GetProfileInt(_T("FaceOption"), _T("ThresholdLevel"), 3));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgOfSettings::OnNMCustomdrawSliderSettingsThresholdlevel(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here

	m_strLevel = getString(m_slider.GetPos());
	UpdateData(FALSE);

	*pResult = 0;
}


void CDlgOfSettings::OnBnClickedButtonSettingsApply()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (MessageBox(_T("Do you really want to apply value?"), _T("Question"), MB_OKCANCEL) == IDOK)
	{
		if (isDataValid() == FALSE)
			return;

		AfxGetApp()->WriteProfileString(_T("Setting"), _T("Address"), m_strAddress);
		AfxGetApp()->WriteProfileInt(_T("Setting"), _T("Port"), m_nPort);

		AfxGetApp()->WriteProfileString(_T("Setting"), _T("DBName"), m_strDBName);
		AfxGetApp()->WriteProfileString(_T("Setting"), _T("UserName"), m_strUsername);
		AfxGetApp()->WriteProfileString(_T("Setting"), _T("Password"), m_strPassword);

		AfxGetApp()->WriteProfileString(_T("Setting"), _T("Place"), m_strPlace);
		AfxGetApp()->WriteProfileInt(_T("Setting"), _T("SyncPeriod"), m_nSyncPeriod);

		AfxGetApp()->WriteProfileInt(_T("Setting"), _T("Autorun"), m_fAutorun);
		SetAutorun(m_fAutorun);

		AfxGetApp()->WriteProfileInt(_T("FaceOption"), _T("ThresholdLevel"), m_slider.GetPos());
		AfxGetApp()->WriteProfileInt(_T("FaceOption"), _T("FOV"), m_nFov);

		for (int i = 0; i < MAX_CAMERA_NUM; i++)
		{
			FaceProcessor* faceprocessor = g_pCameraContainer->m_cameraViews[i].m_pProcessor;
			if (faceprocessor != NULL)
			{
				faceprocessor->getEngineHandle()->getThresholdValue(m_slider.GetPos());
			}
		}

		personDB().getThresholdValue(m_slider.GetPos());

		g_pDBManager->close_mysql();

		g_pDBManager->connect_mysql_server(m_strAddress, m_nPort, m_strDBName, m_strUsername, m_strPassword);

		g_pDBManager->loadPersonBinaryData();

		g_pMonitorHistory->RefreshList();
		g_pPersonManageList->RefreshList();
		g_pPersonHistory->RefreshList();
		g_pUserManageList->RefreshList();
		g_pUserHistory->RefreshList();

		AfxMessageBox(L"Successfully applied", MB_ICONINFORMATION);
	}
}

BOOL CDlgOfSettings::isDataValid()
{
	if (m_strAddress.IsEmpty() == TRUE)
	{
		MessageBox(_T("Please type the Server Address."), _T("Message"));
		return FALSE;
	}

	if (m_nPort < 0 || m_nPort > LONG_MAX)
	{
		MessageBox(_T("The Server Port is out of range.Please retype the Server Port."), _T("Message"));
		return FALSE;
	}

	if (m_strDBName.IsEmpty() == TRUE)
	{
		MessageBox(_T("Please type the DBName."), _T("Message"));
		return FALSE;
	}

	if (m_strUsername.IsEmpty() == TRUE)
	{
		MessageBox(_T("Please type the UserName."), _T("Message"));
		return FALSE;
	}

	if (m_strPlace.IsEmpty() == TRUE)
	{
		MessageBox(_T("Please type the Place."), _T("Message"));
		return FALSE;
	}

	if (m_nSyncPeriod < 1)
	{
		MessageBox(_T("Please type the Place."), _T("Message"));
		return FALSE;
	}

	return TRUE;
}


void CDlgOfSettings::OnBnClickedButtonSettingsDefault()
{
	if (MessageBox(_T("Do you really want to set default value?"), _T("Question"), MB_OKCANCEL) == IDOK)
	{
		m_strAddress = _T("47.93.247.211");
		m_nPort = 3306;
		m_strDBName = _T("facecheck_db");
		m_strUsername = _T("developer");
		m_strPassword = _T("devroot");
		m_strPlace = _T("Unknown");
		m_nSyncPeriod = 5;
		m_fAutorun = TRUE;
		m_nFov = 55;
		m_slider.SetPos(3);
		UpdateData(FALSE);
	}
}

CString CDlgOfSettings::getString(int nLevel)
{
	CString str = _T("");
	switch (m_slider.GetPos())
	{
	case 1:
		str.Format(_T("Lowest"));
		break;
	case 2:
		str.Format(_T(" Low "));
		break;
	case 3:
		str.Format(_T("Normal"));
		break;
	case 4:
		str.Format(_T(" High "));
		break;
	case 5:
		str.Format(_T("Highest"));
		break;
	}

	return str;
}

void CDlgOfSettings::OnDeltaposSpinSettingsSynctime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	//m_nSyncPeriod = m_spinChangePeriod.GetPos();
	m_nSyncPeriod = pNMUpDown->iPos + pNMUpDown->iDelta;
	UpdateData(FALSE);
	*pResult = 0;
}


void CDlgOfSettings::OnTimer(UINT_PTR nIDEvent)
{
	//	if (nIDEvent == ID_SYNC_TIMER)
	//	{
	//		g_pDBManager->reloadPersonBinaryData();
	//	}
	CDialogEx::OnTimer(nIDEvent);
}


void CDlgOfSettings::OnBnClickedButtonSettingsExport()
{
	exportSettings();
}

void CDlgOfSettings::importSettings()
{
	//show FileDialog 
	CFileDialog dlg(TRUE);

	CString strTitle(_T("Open Settings"));
	dlg.m_ofn.lpstrTitle = strTitle;
	dlg.m_ofn.lpstrFilter = _T("Information Files(*.inf)\0*.inf\0Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0");
	//	dlg.m_ofn.Flags |= OFN_ALLOWMULTISELECT;

	TCHAR buffer[30000];
	ZeroMemory(buffer, sizeof(TCHAR) * 30000);
	dlg.m_ofn.lpstrFile = buffer;
	dlg.m_ofn.nMaxFile = 1;

	if (dlg.DoModal() == IDCANCEL)
		return;
	if (MessageBox(_T("Do you really want to apply value?"), _T("Question"), MB_OKCANCEL) == IDOK)
	{

		CString fileName = dlg.GetFolderPath() + "\\" + dlg.GetFileName();

		CString strSetting, strTemp;

		CStdioFile file;
		if (file.Open((LPCTSTR)fileName, CFile::modeRead | CFile::typeUnicode))
		{
			while (file.ReadString(strSetting))
			{
				//CT2CA outputString(strSetting, CP_UTF8);
				CString strKey, strValue;
				BOOL isKey = TRUE;
				for (int i = 0; i < strSetting.GetLength(); i++)
				{
					if (strSetting[i] == '=')
					{
						isKey = FALSE;
						strKey = strKey.Trim();
						continue;
					}
					if (isKey)
						strKey += strSetting[i];
					else
						strValue += strSetting[i];
				}
				strValue = strValue.Trim();
				if (strKey == _T("autorun")) m_fAutorun = bool(strValue);
				if (strKey == _T("place")) m_strPlace = strValue;
				if (strKey == _T("syncperiod")) m_nSyncPeriod = _ttoi(strValue);
				if (strKey == _T("address")) m_strAddress = strValue;
				if (strKey == _T("port")) m_nPort = _ttoi(strValue);
				if (strKey == _T("dbname")) m_strDBName = strValue;
				if (strKey == _T("username")) m_strUsername = strValue;
				if (strKey == _T("password")) m_strPassword = strValue;
				if (strKey == _T("fieldOfView")) m_nFov = _ttoi(strValue);
				if (strKey == _T("level"))
				{
					int nTemp;
					sscanf_s((const char*)strValue.GetBuffer(), "%d", &nTemp);
					m_slider.SetPos(nTemp);
				}
			}
		}
		file.Close();
	}
	UpdateData(FALSE);
	AfxMessageBox(L"Successfully imported", MB_ICONINFORMATION);

	return;
}

void CDlgOfSettings::exportSettings() {
	//show FileDialog 
	CFileDialog dlg(FALSE);
	UpdateData(TRUE);

	CString strTitle(_T("Save Settings"));
	dlg.m_ofn.lpstrTitle = strTitle;
	dlg.m_ofn.lpstrFilter = _T("Information Files(*.inf)\0*.inf\0Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0");
	//	dlg.m_ofn.Flags |= OFN_ALLOWMULTISELECT;

	TCHAR buffer[30000];
	ZeroMemory(buffer, sizeof(TCHAR) * 30000);
	dlg.m_ofn.lpstrFile = buffer;
	dlg.m_ofn.nMaxFile = 1;

	if (dlg.DoModal() == IDCANCEL)
		return;

	CString fileName = dlg.GetFolderPath() + "\\" + dlg.GetFileName();

	CString strSetting, strTemp;
	strSetting.Format(_T("autorun = %s\n"), m_fAutorun ? _T("true") : _T("false"));
	strSetting.AppendFormat(_T("place = %s\n"), m_strPlace);
	strSetting.AppendFormat(_T("syncperiod = %d\n"), m_nSyncPeriod);
	strSetting.AppendFormat(_T("address = %s\n"), m_strAddress);
	strSetting.AppendFormat(_T("port = %d\n"), m_nPort);
	strSetting.AppendFormat(_T("dbname = %s\n"), m_strDBName);
	strSetting.AppendFormat(_T("username = %s\n"), m_strUsername);
	strSetting.AppendFormat(_T("password = %s\n"), m_strPassword);
	strSetting.AppendFormat(_T("fieldOfView = %d\n"), m_nFov);
	strSetting.AppendFormat(_T("level = %d"), m_slider.GetPos());

	CStdioFile file;
	if (file.Open((LPCTSTR)fileName, CFile::modeCreate | CFile::modeWrite | CFile::typeUnicode))
	{

		file.WriteString(strSetting);
	}
	file.Close();
	AfxMessageBox(L"Successfully exported", MB_ICONINFORMATION);
}

void CDlgOfSettings::OnBnClickedButtonSettingsImport()
{
	importSettings();
}

void CDlgOfSettings::SetMyLayout()
{

}

int CDlgOfSettings::SetAutorun(BOOL bAutorun)
{
	/*HKEY hAutorun;
	if(RegOpenKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), &hAutorun) != ERROR_SUCCESS)
	return 0;

	if(bAutorun)
	{
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	TCHAR * pos = _tcsrchr(szPath, _T('\\'));
	pos[1] = 0;
	_tcscat_s(szPath, _T("HBStartup.exe /PeopleCountingClient"));
	RegSetValueEx(hAutorun, _T("PeopleCountingClient"), 0, REG_SZ, (const BYTE*)szPath, _tcslen(szPath) * sizeof(TCHAR));
	}
	else
	{
	RegDeleteValue(hAutorun, _T("PeopleCountingClient"));
	}
	RegCloseKey(hAutorun);*/
	return 1;
}
