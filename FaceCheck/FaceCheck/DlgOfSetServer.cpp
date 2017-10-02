// DlgOfSetServer.cpp : implementation file
//

#include "stdafx.h"
#include "FaceCheck.h"
#include "DlgOfSetServer.h"
#include "afxdialogex.h"


// CDlgOfSetServer dialog

IMPLEMENT_DYNAMIC(CDlgOfSetServer, CDialogEx)

CDlgOfSetServer::CDlgOfSetServer(CWnd* pParent /*=NULL*/)
: CDialogEx(CDlgOfSetServer::IDD, pParent)
, m_strAddress(_T(""))
, m_strUsername(_T(""))
, m_strPassword(_T(""))
, m_nPort(0)
, m_strDBName(_T(""))
{

	EnableAutomation();

}

CDlgOfSetServer::~CDlgOfSetServer()
{
}

void CDlgOfSetServer::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialogEx::OnFinalRelease();
}

void CDlgOfSetServer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SETSERVER_ADDRESS, m_strAddress);
	DDX_Text(pDX, IDC_EDIT_SETSERVER_USERNAME, m_strUsername);
	DDX_Text(pDX, IDC_EDIT_SETSERVER_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_SETSERVER_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_SETSERVER_DBNAME, m_strDBName);
}


BEGIN_MESSAGE_MAP(CDlgOfSetServer, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgOfSetServer, CDialogEx)
END_DISPATCH_MAP()

// Note: we add support for IID_IDlgOfSetServer to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {37215497-85B5-428C-80AA-FD75A37F22BA}
static const IID IID_IDlgOfSetServer =
{ 0x37215497, 0x85B5, 0x428C, { 0x80, 0xAA, 0xFD, 0x75, 0xA3, 0x7F, 0x22, 0xBA } };

BEGIN_INTERFACE_MAP(CDlgOfSetServer, CDialogEx)
	INTERFACE_PART(CDlgOfSetServer, IID_IDlgOfSetServer, Dispatch)
END_INTERFACE_MAP()


// CDlgOfSetServer message handlers


BOOL CDlgOfSetServer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
