// PersonInfo.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "PersonInfo.h"
#include "afxdialogex.h"


// CPersonInfo dialog

IMPLEMENT_DYNAMIC(CPersonInfo, CPropertyPage)

CPersonInfo::CPersonInfo()
	: CPropertyPage(CPersonInfo::IDD)
{

}

CPersonInfo::~CPersonInfo()
{
}

void CPersonInfo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPersonInfo, CPropertyPage)
END_MESSAGE_MAP()


// CPersonInfo message handlers
