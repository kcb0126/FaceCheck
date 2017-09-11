#pragma once

// This class comes from http://greenfishblog.tistory.com/44
// CBitmapButtonPlus

class CBitmapButtonPlus : public CBitmapButton
{

	DECLARE_DYNAMIC(CBitmapButtonPlus)

public:
	CBitmapButtonPlus();
	virtual ~CBitmapButtonPlus();
	virtual void SetTransBitmap(IN COLORREF clrTrans) { m_clrTrans = clrTrans; }
	virtual void SetHoverBitmapID(IN UINT nIDBitmapResourceHover);

protected:
	COLORREF			m_clrTrans;
	BOOL				m_bMouseHover;
	TRACKMOUSEEVENT		m_stTrackMouse;
	UINT				m_nIDBitmapResourceHover;
	CBitmap				m_cBitmapHover;

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);

public:
	void OnSet();	//OnCreate() doesn't work. So I will call this manually.
};

// header
class CLayoutMgr
{
public:
	static void DrawBitmapTrans(IN OUT CDC* pDC, IN CBitmap* pcBitmap, IN int x, IN int y, IN COLORREF crMask);
};
