#pragma once

#include "CameraViewContainer.h"
// CDlgOfTakePhoto dialog

class CDlgOfTakePhoto : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOfTakePhoto)

public:
	CDlgOfTakePhoto(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgOfTakePhoto();


	void InitializeMembers();

	// Dialog Data
	enum { IDD = IDD_DLG_TAKEPHOTO };


public:
	CCameraViewContainer* m_pCameraViewContainer;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	void SetMyLayout();
};
