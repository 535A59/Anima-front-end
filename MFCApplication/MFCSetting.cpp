// MFCSetting.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "afxdialogex.h"
#include "MFCSetting.h"
#include "PathHandle.h"
#include <string>
#include <Windows.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <io.h>
#include <iomanip>
using namespace std;

CString VoiceProfile;

// MFCSetting dialog

IMPLEMENT_DYNAMIC(MFCSetting, CDialogEx)

MFCSetting::MFCSetting(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING, pParent)
{

}

MFCSetting::~MFCSetting()
{
}

void MFCSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_DEFAULTVOICE, m_voice);
}


BEGIN_MESSAGE_MAP(MFCSetting, CDialogEx)
	ON_BN_CLICKED(IDOK, &MFCSetting::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_DEFAULTVOICE, &MFCSetting::OnCbnSelchangeDefaultvoice)
	ON_BN_CLICKED(IDC_FINDFILE, &MFCSetting::OnBnClickedFindFile)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()





// MFCSetting message handlers
BOOL MFCSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// generate combo box
	vector<string> fileNames;
	CString PROGRAM_PATH = PathHandle::FilePath();
	CString pFilePath = PROGRAM_PATH;
	pFilePath.Append(CString("\\data\\profiles"));
	string path = CT2A(pFilePath.GetBuffer());
	PathHandle::getFileNames(path, fileNames);
	int count = 0;
	for (string ph : fileNames) {
		m_voice.InsertString(count,CString(ph.c_str()));
		count++;
	}

	// set default value of combo box if user have chosen voice profile
	int ProfileExist = VoiceProfile.GetLength();
	if (ProfileExist != 0)
	{
		m_voice.SelectString(-1, VoiceProfile);
	}

	return TRUE;
}



void MFCSetting::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	// Send user selected voice profile to other program
	int nIndex = m_voice.GetCurSel();
	CString profile;
	m_voice.GetLBText(nIndex, profile);
	VoiceProfile = profile;
	CDialogEx::OnOK();
}


void MFCSetting::OnCbnSelchangeDefaultvoice()
{
	// TODO: Add your control notification handler code here
}


void MFCSetting::OnBnClickedFindFile()
{
	// TODO: Add your control notification handler code here
	// TODO:  Add the control notification handler code here

	//generate file dialog  
	CString PROGRAM_PATH = PathHandle::FilePath();
	TCHAR szFilter[] = _T("animaprofile(*.animaprofile)|*.animaprofile||"); 
	CFileDialog fileDlg(TRUE, _T("animaprofile"), NULL, 0, szFilter, this);
	CString strFilePath;
	CString name;

	//show file dialog  
	if (IDOK == fileDlg.DoModal())
	{
		strFilePath = fileDlg.GetPathName();
		name = fileDlg.GetFileName();
	}

	// Copy the user selected profile to profiles file
	CString pFilePath = PROGRAM_PATH;
	pFilePath.Append(CString("data\\profiles\\"));
	pFilePath.Append(name);
	CopyFile(strFilePath,pFilePath,true);

	// Reset combo box
	pFilePath = PROGRAM_PATH;
	pFilePath.Append(CString("data\\profiles\\"));
	m_voice.ResetContent();
	vector<string> fileNames;
	string path = CT2A(pFilePath.GetBuffer());
	PathHandle::getFileNames(path, fileNames);
	int count = 0;
	for (string ph : fileNames) {
		m_voice.InsertString(count, CString(ph.c_str()));
		count++;
	}
	m_voice.SelectString(-1, name);
	
}


void MFCSetting::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnSysCommand(nID, lParam);
	CDialogEx::OnOK();
}
