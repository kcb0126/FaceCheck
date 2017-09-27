#pragma once
#include "CustomListView.h"
class CMonitorHistory :
	public CCustomListView
{
public:
	CMonitorHistory();
	~CMonitorHistory();

public:
	virtual int getCellCount();
	virtual CWnd* getCellAt(int nIndex);
};

