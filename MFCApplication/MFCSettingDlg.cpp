// MFCSettingDlg.cpp: implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "afxdialogex.h"
#include "MFCSettingDlg.h"


// MFCSettingDlg dialog

IMPLEMENT_DYNAMIC(MFCSettingDlg, CDialogEx)

MFCSettingDlg::MFCSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING, pParent)
{

}

MFCSettingDlg::~MFCSettingDlg()
{
}

void MFCSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MFCSettingDlg, CDialogEx)
END_MESSAGE_MAP()


// MFCSettingDlg message handlers
