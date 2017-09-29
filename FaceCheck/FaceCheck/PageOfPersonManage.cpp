// PageOfPersonManage.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "PageOfPersonManage.h"
#include "afxdialogex.h"


// CPageOfPersonManage dialog

IMPLEMENT_DYNAMIC(CPageOfPersonManage, CPropertyPage)

CPageOfPersonManage::CPageOfPersonManage()
	: CPropertyPage(CPageOfPersonManage::IDD)
{

}

CPageOfPersonManage::~CPageOfPersonManage()
{
}

void CPageOfPersonManage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageOfPersonManage, CPropertyPage)
END_MESSAGE_MAP()


// CPageOfPersonManage message handlers
