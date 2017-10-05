// ShowFace.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "ShowFace.h"
#include "afxdialogex.h"


// CShowFace dialog

IMPLEMENT_DYNAMIC(CShowFace, CDialogEx)

CShowFace::CShowFace(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShowFace::IDD, pParent)
{

}

CShowFace::CShowFace(CPerson* pPerson, CWnd* pParent/* = NULL*/)
	: CDialogEx(CShowFace::IDD, pParent)
{
	m_pPerson = pPerson;
}

CShowFace::~CShowFace()
{
}

void CShowFace::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SHOWFACE_FACES, m_listReg);
}


BEGIN_MESSAGE_MAP(CShowFace, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SHOWFACE_DELETE, &CShowFace::OnBnClickedButtonShowfaceDelete)
	ON_WM_GETMINMAXINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_SHOWFACE_OK, &CShowFace::OnBnClickedButtonShowfaceOk)
END_MESSAGE_MAP()


// CShowFace message handlers
BOOL CShowFace::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	RECT rt;
	GetClientRect(&rt);

	//if( m_nID == NON_EMPLOYEE )
	//	return TRUE;

	CString str;
	str.Format(_T("Show Face - %s"), m_pPerson->m_strName);
	SetWindowText(str);

	m_imgListReg.Create(REG_IMAGE_W, REG_IMAGE_W, ILC_COLOR24, 0, 1);
	m_listReg.SetImageList(&m_imgListReg, LVSIL_NORMAL);

	m_listReg.SetExtendedStyle(m_listReg.GetExtendedStyle() | LVS_EX_BORDERSELECT);
	m_listReg.SetOutlineColor(RGB(255, 255, 255));

	m_listReg.SetRedraw(FALSE);

	for (UINT i = 0; i < m_pPerson->m_vecMugshot.size(); i++)
		AddPeople2List(i);

	CenterWindow();

	m_listReg.SetRedraw(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CShowFace::RedrawFaceList()
{
	m_listReg.SetRedraw(FALSE);
	m_listReg.DeleteAllItems();

	for (int i = m_imgListReg.GetImageCount() - 1; i >= 0; i--)
		m_imgListReg.Remove(i);

	for (UINT i = 0; i < m_pPerson->m_vecMugshot.size(); i++)
		AddPeople2List(i);

	m_listReg.SetRedraw(TRUE);
}

void CShowFace::OnBnClickedButtonShowfaceDelete()
{
	int nSelectedCount = m_listReg.GetSelectedCount();
	if (nSelectedCount <= 0)
	{
		MessageBox(_T("Select Photo"), _T("Message"));
		return;
	}

	if (MessageBox(_T("Are you sure you want to delete?"), _T("Warning"), MB_YESNO | MB_ICONWARNING) != IDYES)
		return;

	///////Get Selected Pos////////////
	POSITION pos = m_listReg.GetFirstSelectedItemPosition();
	int* list_index = new int[nSelectedCount];
	int i = 0;

	while (pos)
	{
		list_index[i] = m_listReg.GetNextSelectedItem(pos);
		i++;
	}
	//////////////////////////////////////

	int nData;
	for (int i = nSelectedCount - 1; i >= 0; i--)
	{
		nData = m_listReg.GetItemData(list_index[i]);
		if (nData == -1)
		{
			m_pPerson->m_vecMugshot.erase(m_pPerson->m_vecMugshot.begin() + list_index[i]);
		}
		else
		{
			m_pPerson->m_vecMugshot.erase(m_pPerson->m_vecMugshot.begin() + list_index[i]);
			personDB().DeleteMugshot(m_pPerson->m_nID, nData);
			g_pDBManager->deletePersonBinaryData(m_pPerson->m_nID, nData);
		}
	}

	//if (personDB()[m_nID].m_vecMugshot.size() == 0)
	//{
	//	MessageBox(_T("The person is removed because there are no pictures!"), _T("Information"));
	//	UINT nID = personDB()[m_nID].m_nID;
	//	personDB().Delete(nID);
	//}

	RedrawFaceList();
}

HBITMAP CShowFace::GetFaceThumbImage(CPerson* pPerson, int nIndex)
{
	if (pPerson->m_vecMugshot.size() <= 0)
		return NULL;

	HBITMAP hbmReturn = NULL;
	Bitmap image(REG_IMAGE_W, REG_IMAGE_W, PixelFormat24bppRGB);

	Rect		rc(0, 0, REG_IMAGE_W, REG_IMAGE_W);
	BitmapData	data;
	image.LockBits(&rc, ImageLockModeWrite | ImageLockModeRead, PixelFormat24bppRGB, &data);

	BYTE* pPixels = (BYTE*)data.Scan0;
	for (int h = 0; h < rc.Height; h++)
	{
		BYTE *pbyPixel = pPerson->m_vecMugshot[nIndex].m_photo.m_pbyBuf +
			(rc.Height - h - 1) * pPerson->m_vecMugshot[nIndex].m_photo.m_nEffWidth;
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

	return hbmReturn;
}

void CShowFace::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 500;
	lpMMI->ptMinTrackSize.y = 300;
	lpMMI->ptMaxPosition.x = 0;
	lpMMI->ptMaxPosition.y = 0;
	lpMMI->ptMaxSize.x = GetSystemMetrics(SM_CXFULLSCREEN);
	lpMMI->ptMaxSize.y = GetSystemMetrics(SM_CYFULLSCREEN) + GetSystemMetrics(SM_CYCAPTION);

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

void CShowFace::AddPeople2List(int nIndex)
{
	CBitmap bmp;

	HBITMAP  hbmReturn = GetFaceThumbImage(m_pPerson, nIndex);

	if (hbmReturn != NULL)
	{
		bmp.Attach(hbmReturn);

		m_imgListReg.Add(&bmp, (CBitmap*)NULL);

		bmp.Detach();
		DeleteObject(hbmReturn);

		m_listReg.InsertItem(nIndex, _T(""), nIndex);
		m_listReg.SetItemData(nIndex, m_pPerson->m_vecMugshot[nIndex].m_nIDX);
	}
}

void CShowFace::OnDestroy()
{
	CDialogEx::OnOK();
}


void CShowFace::OnBnClickedButtonShowfaceOk()
{
	CDialogEx::OnOK();
}
