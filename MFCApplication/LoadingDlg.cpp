// LoadingDlg.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "afxdialogex.h"
#include "LoadingDlg.h"
#include "afxinet.h"
#include "../json-3.10.5/single_include/nlohmann/json.hpp"


// LoadingDlg dialog

IMPLEMENT_DYNAMIC(LoadingDlg, CDialogEx)

LoadingDlg::LoadingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOADING, pParent)
{

}

LoadingDlg::~LoadingDlg()
{
}

void LoadingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LoadingDlg, CDialogEx)
END_MESSAGE_MAP()


BOOL LoadingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	EnableWindow(FALSE);
	

	try
	{
		CInternetSession session;
		CHttpConnection* connection = session.GetHttpConnection(CString("127.0.0.1"));
		CHttpFile* File = connection->OpenRequest(CString("GET"), CString("/play"));
		File->SendRequest();

	}
	catch (const std::exception& e)
	{
		MessageBox(CString("Request Failed"));
	}

	EndDialog(-1);

	return TRUE;
}

// LoadingDlg message handlers
