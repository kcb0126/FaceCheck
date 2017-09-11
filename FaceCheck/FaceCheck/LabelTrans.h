#if !defined(AFX_LABETRANSL_H__A4EABEC5_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_)
#define AFX_LABELTRANS_H__A4EABEC5_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Label.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLabelTrans window
enum FlashType { None, Caption, Background };

class CLabelTrans : public CStatic
{
	// Construction
public:
	CLabelTrans();
	CLabelTrans& SetBkColor(COLORREF crBkgnd);
	CLabelTrans& SetTextColor(COLORREF crText);
	CLabelTrans& SetText(const CString& strText);
	CLabelTrans& SetFontBold(BOOL bBold);
	CLabelTrans& SetFontName(const CString& strFont);
	CLabelTrans& SetFontUnderline(BOOL bSet);
	CLabelTrans& SetFontItalic(BOOL bSet);
	CLabelTrans& SetFontSize(int nSize);
	CLabelTrans& SetSunken(BOOL bSet);
	CLabelTrans& SetBorder(BOOL bSet);
	CLabelTrans& FlashText(BOOL bActivate);
	CLabelTrans& FlashBackground(BOOL bActivate);
	CLabelTrans& SetLink(BOOL bLink);
	CLabelTrans& SetLinkCursor(HCURSOR hCursor);

	// Attributes
public:
protected:
	void ReconstructFont();
	COLORREF	m_crText;
	HBRUSH		m_hBrush;
	HBRUSH		m_hwndBrush;
	LOGFONT		m_lf;
	CFont		m_font;
	CString		m_strText;
	BOOL		m_bState;
	BOOL		m_bTimer;
	BOOL		m_bLink;
	FlashType	m_Type;
	HCURSOR		m_hCursor;
	// Operations
public:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLabelTrans)
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CLabelTrans();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLabel)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LABELTRANS_H__A4EABEC5_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_)
