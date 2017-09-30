// PersonHistoryList.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "PersonHistoryList.h"
#include "afxdialogex.h"


// CPersonHistoryList dialog

IMPLEMENT_DYNAMIC(CPersonHistoryList, CPropertyPage)

CPersonHistoryList::CPersonHistoryList()
	: CPropertyPage(CPersonHistoryList::IDD)
{

}

CPersonHistoryList::~CPersonHistoryList()
{
}

void CPersonHistoryList::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPersonHistoryList, CPropertyPage)
END_MESSAGE_MAP()


// CPersonHistoryList message handlers
