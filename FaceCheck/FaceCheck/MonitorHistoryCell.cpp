// MonitorHistoryCell.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "MonitorHistoryCell.h"
#include "afxdialogex.h"


// CMonitorHistoryCell dialog

IMPLEMENT_DYNAMIC(CMonitorHistoryCell, CPropertyPage)

CMonitorHistoryCell::CMonitorHistoryCell()
	: CPropertyPage(CMonitorHistoryCell::IDD)
{

}

CMonitorHistoryCell::~CMonitorHistoryCell()
{
}

void CMonitorHistoryCell::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMonitorHistoryCell, CPropertyPage)
END_MESSAGE_MAP()


// CMonitorHistoryCell message handlers
