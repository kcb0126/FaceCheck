// PageOfPersonHistory.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "PageOfPersonHistory.h"
#include "afxdialogex.h"


// CPageOfPersonHistory dialog

IMPLEMENT_DYNAMIC(CPageOfPersonHistory, CPropertyPage)

CPageOfPersonHistory::CPageOfPersonHistory()
	: CPropertyPage(CPageOfPersonHistory::IDD)
{

}

CPageOfPersonHistory::~CPageOfPersonHistory()
{
}

void CPageOfPersonHistory::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageOfPersonHistory, CPropertyPage)
END_MESSAGE_MAP()


// CPageOfPersonHistory message handlers
