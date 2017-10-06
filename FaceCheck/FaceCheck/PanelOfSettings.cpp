// PanelOfSettings.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "PanelOfSettings.h"
#include "afxdialogex.h"


// CPanelOfSettings dialog

IMPLEMENT_DYNAMIC(CPanelOfSettings, CPropertyPage)

CPanelOfSettings::CPanelOfSettings()
	: CPropertyPage(CPanelOfSettings::IDD)
{

}

CPanelOfSettings::~CPanelOfSettings()
{
}

void CPanelOfSettings::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPanelOfSettings, CPropertyPage)
END_MESSAGE_MAP()


// CPanelOfSettings message handlers
