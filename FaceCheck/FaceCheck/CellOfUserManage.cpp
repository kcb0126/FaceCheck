// CellOfUserManage.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "CellOfUserManage.h"
#include "afxdialogex.h"


// CCellOfUserManage dialog

IMPLEMENT_DYNAMIC(CCellOfUserManage, CPropertyPage)

CCellOfUserManage::CCellOfUserManage()
	: CPropertyPage(CCellOfUserManage::IDD)
{

}

CCellOfUserManage::~CCellOfUserManage()
{
}

void CCellOfUserManage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCellOfUserManage, CPropertyPage)
END_MESSAGE_MAP()


// CCellOfUserManage message handlers
