// RecordNameDlg.cpp: implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "afxdialogex.h"
#include "RecordNameDlg.h"





// RecordNameDlg dialog

IMPLEMENT_DYNAMIC(RecordNameDlg, CDialogEx)

RecordNameDlg::RecordNameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RECORDNAME, pParent)
{

}

RecordNameDlg::~RecordNameDlg()
{
}

void RecordNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(RecordNameDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &RecordNameDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_RECORDNAME, &RecordNameDlg::OnEnChangeRecordname)
END_MESSAGE_MAP()


// RecordNameDlg message handlers


void RecordNameDlg::OnBnClickedOk()
{
	// TODO:  Add the control notification handler code here

	GetDlgItem(IDC_RECORDNAME)->GetWindowText(m_RecordName);
	CDialogEx::OnOK();
}

void RecordNameDlg::GetName(CString& Name)
{
	Name = m_RecordName;
}

void RecordNameDlg::OnEnChangeRecordname()
{
	//TODO: If the control is a RICHEDIT control, it will 
	//not send this notification unless you override the 
	//CDialogEx::OnInitDialog() functionand call CRichEditCtrl().
	//SetEventMask() and also operate the ENM_CHANGE flag "OR" into 
	//the mask.

	// TODO:  Add the control notification handler code here
}

