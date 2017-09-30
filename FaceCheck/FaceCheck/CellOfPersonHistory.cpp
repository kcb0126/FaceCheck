// CellOfPersonHistory.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "CellOfPersonHistory.h"
#include "afxdialogex.h"


// CCellOfPersonHistory dialog

IMPLEMENT_DYNAMIC(CCellOfPersonHistory, CPropertyPage)

CCellOfPersonHistory::CCellOfPersonHistory()
	: CPropertyPage(CCellOfPersonHistory::IDD)
{

}

CCellOfPersonHistory::~CCellOfPersonHistory()
{
}

void CCellOfPersonHistory::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCellOfPersonHistory, CPropertyPage)
END_MESSAGE_MAP()


// CCellOfPersonHistory message handlers
