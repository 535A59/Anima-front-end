// MFCSpeakPage.cpp: implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "afxdialogex.h"
#include "MFCSpeakPage.h"


// MFCSpeakPage dialog

IMPLEMENT_DYNAMIC(MFCSpeakPage, CDialogEx)

MFCSpeakPage::MFCSpeakPage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION_DIALOG, pParent)
{

}

MFCSpeakPage::~MFCSpeakPage()
{
}

void MFCSpeakPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MFCSpeakPage, CDialogEx)
END_MESSAGE_MAP()


// MFCSpeakPage message handlers
