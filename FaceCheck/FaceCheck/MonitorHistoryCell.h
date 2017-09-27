#pragma once


// CMonitorHistoryCell dialog

class CMonitorHistoryCell : public CPropertyPage
{
	DECLARE_DYNAMIC(CMonitorHistoryCell)

public:
	CMonitorHistoryCell();
	virtual ~CMonitorHistoryCell();

// Dialog Data
	enum { IDD = IDD_CELL_MONITORHISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
