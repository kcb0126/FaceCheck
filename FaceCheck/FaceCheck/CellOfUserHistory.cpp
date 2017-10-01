// CellOfUserHistory.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "CellOfUserHistory.h"
#include "afxdialogex.h"


// CCellOfUserHistory dialog

IMPLEMENT_DYNAMIC(CCellOfUserHistory, CPropertyPage)

CCellOfUserHistory::CCellOfUserHistory()
	: CPropertyPage(CCellOfUserHistory::IDD)
{

}

CCellOfUserHistory::~CCellOfUserHistory()
{
}

void CCellOfUserHistory::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCellOfUserHistory, CPropertyPage)
END_MESSAGE_MAP()


// CCellOfUserHistory message handlers
