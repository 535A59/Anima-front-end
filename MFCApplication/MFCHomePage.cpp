// MFCHomePage.cpp: implementation file
//

#include "pch.h"
#include "afxwin.h"
#include "MFCApplication.h"
#include "afxdialogex.h"
#include "MFCHomePage.h"
#include "MFCApplicationDlg.h"
#include "MFCRecordPage.h"
#include "MFCOCRReaderDlg.h"
#include "MFCSetting.h"
#include "PathHandle.h"

// MFCHomePage dialog

IMPLEMENT_DYNAMIC(MFCHomePage, CDialogEx)

MFCHomePage::MFCHomePage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HOME, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}



void MFCHomePage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MFCHomePage, CDialogEx)
	ON_BN_CLICKED(IDOK, &MFCHomePage::OnBnClickedSpeak)
	ON_BN_CLICKED(IDC_OCR, &MFCHomePage::OnBnClickedRecord)
	ON_BN_CLICKED(IDCANCEL, &MFCHomePage::OnBnClickedExit)
	ON_BN_CLICKED(IDC_BUTTON1, &MFCHomePage::OnBnClickedButton1)
	ON_BN_CLICKED(ID_SETTING, &MFCHomePage::OnBnClickedSetting)
END_MESSAGE_MAP()


// MFCHomePage message handlers

void MFCHomePage::OnBnClickedSpeak()
{
	// TODO:  Add the control notification handler code here
	this->ShowWindow(SW_HIDE);
	CMFCApplicationDlg dlg;
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void MFCHomePage::OnBnClickedRecord()
{
	// TODO:  Add the control notification handler code here
	this->ShowWindow(SW_HIDE);
	MFCRecordPage dlg;
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}



void MFCHomePage::OnBnClickedExit()
{

	// TODO:  Add the control notification handler code here
	CString PROGRAM_PATH = PathHandle::FilePath();
	CString pFilePath = PROGRAM_PATH;
	ShellExecute(NULL, NULL, _T("stop.bat"), NULL, pFilePath, 0);
	CDialogEx::OnOK();
}


void MFCHomePage::OnBnClickedButton1()
{
	// TODO:  Add the control notification handler code here
	this->ShowWindow(SW_HIDE);
	MFCOCRReaderDlg dlg;
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}

void MFCHomePage::OnBnClickedSetting()
{
	this->ShowWindow(SW_HIDE);
	MFCSetting dlg;
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}

void MFCHomePage::OnCancel()
{
	DestroyWindow();
}