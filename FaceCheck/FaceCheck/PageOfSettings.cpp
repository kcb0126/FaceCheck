// PageOfSettings.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "PageOfSettings.h"
#include "afxdialogex.h"


// CPageOfSettings dialog

IMPLEMENT_DYNAMIC(CPageOfSettings, CPropertyPage)

CPageOfSettings::CPageOfSettings()
	: CPropertyPage(CPageOfSettings::IDD)
{

}

CPageOfSettings::~CPageOfSettings()
{
}

void CPageOfSettings::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageOfSettings, CPropertyPage)
END_MESSAGE_MAP()


// CPageOfSettings message handlers
