// CellOfPersonManage.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "CellOfPersonManage.h"
#include "afxdialogex.h"


// CCellOfPersonManage dialog

IMPLEMENT_DYNAMIC(CCellOfPersonManage, CPropertyPage)

CCellOfPersonManage::CCellOfPersonManage()
	: CPropertyPage(CCellOfPersonManage::IDD)
{

}

CCellOfPersonManage::~CCellOfPersonManage()
{
}

void CCellOfPersonManage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCellOfPersonManage, CPropertyPage)
END_MESSAGE_MAP()


// CCellOfPersonManage message handlers
