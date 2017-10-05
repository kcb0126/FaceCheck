#pragma once
#include "PersonDB.h"
#include "afxcmn.h"

// CShowFace dialog

#define UM_FACE_ITEM_CHANGE   WM_USER + 254

class CShowFace : public CDialogEx
{
	DECLARE_DYNAMIC(CShowFace)

public:
	CShowFace(CWnd* pParent = NULL);   // standard constructor
	CShowFace(CPerson* pPerson, CWnd* pParent = NULL);

	virtual ~CShowFace();

// Dialog Data
	enum { IDD = IDD_SHOW_SAME_FACE };

public:
	void		AddPeople2List(int nIndex);
	HBITMAP		GetFaceThumbImage(CPerson* pPerson, int nIndex);
	void		RedrawFaceList();

public:
	CPerson*		m_pPerson;
	CListCtrl		m_listReg;
	CImageList		m_imgListReg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonShowfaceDelete();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonShowfaceOk();
};
