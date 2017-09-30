#pragma once


// CPersonInfo dialog

class CPersonInfo : public CPropertyPage
{
	DECLARE_DYNAMIC(CPersonInfo)

public:
	CPersonInfo();
	virtual ~CPersonInfo();

// Dialog Data
	enum { IDD = IDD_PERSONINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
