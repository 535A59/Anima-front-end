// InitDlg.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "afxdialogex.h"
#include "InitDlg.h"


// InitDlg dialog

IMPLEMENT_DYNAMIC(InitDlg, CDialogEx)

InitDlg::InitDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INIT, pParent)
{

}

InitDlg::~InitDlg()
{
}

void InitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(InitDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// InitDlg message handlers

void InitDlg::OnClose()
{
	DestroyWindow();
}

void InitDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnSysCommand(nID, lParam);
	DestroyWindow();
}
