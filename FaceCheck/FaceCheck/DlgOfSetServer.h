#pragma once


// CDlgOfSetServer dialog

class CDlgOfSetServer : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOfSetServer)

public:
	CDlgOfSetServer(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgOfSetServer();

	virtual void OnFinalRelease();

	// Dialog Data
	enum { IDD = IDD_DLG_SETSERVER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CString m_strAddress;
	CString m_strUsername;
	CString m_strPassword;
	int m_nPort;
	virtual BOOL OnInitDialog();
	CString m_strDBName;
};
