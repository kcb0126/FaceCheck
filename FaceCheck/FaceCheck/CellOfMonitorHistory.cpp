// CellOfMonitorHistory.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "CellOfMonitorHistory.h"
#include "afxdialogex.h"


// CCellOfMonitorHistory dialog

IMPLEMENT_DYNAMIC(CCellOfMonitorHistory, CPropertyPage)

CCellOfMonitorHistory::CCellOfMonitorHistory()
	: CPropertyPage(CCellOfMonitorHistory::IDD)
{

}

CCellOfMonitorHistory::~CCellOfMonitorHistory()
{
}

void CCellOfMonitorHistory::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCellOfMonitorHistory, CPropertyPage)
END_MESSAGE_MAP()


// CCellOfMonitorHistory message handlers
