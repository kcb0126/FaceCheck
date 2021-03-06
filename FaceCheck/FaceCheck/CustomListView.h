#pragma once

#include <vector>

// CCustomListView view

class CCustomListView : public CScrollView
{
	DECLARE_DYNCREATE(CCustomListView)

protected:
	CCustomListView();           // protected constructor used by dynamic creation
	virtual ~CCustomListView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct

	DECLARE_MESSAGE_MAP()

private:
	std::vector<CWnd*> m_cells;

private:
	void DrawContents();

public:
	void Refresh();
	void RefreshAfterAppend();

public:
	virtual int GetCellCount() { return 0; };
	virtual CWnd* GetCellAt(int nIndex) { return NULL; };
};


