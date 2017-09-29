// PageOfUserHistory.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "PageOfUserHistory.h"
#include "afxdialogex.h"


// CPageOfUserHistory dialog

IMPLEMENT_DYNAMIC(CPageOfUserHistory, CPropertyPage)

CPageOfUserHistory::CPageOfUserHistory()
	: CPropertyPage(CPageOfUserHistory::IDD)
{

}

CPageOfUserHistory::~CPageOfUserHistory()
{
}

void CPageOfUserHistory::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageOfUserHistory, CPropertyPage)
END_MESSAGE_MAP()


// CPageOfUserHistory message handlers
