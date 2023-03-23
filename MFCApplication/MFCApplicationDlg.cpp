// MFCApplicationDlg.cpp: implementation file

#include "pch.h"
#include "framework.h"
#include "MFCApplication.h"
#include "MFCApplicationDlg.h"
#include "afxdialogex.h"
#include "afxinet.h"
#include "MFCSetting.h"
#include "PathHandle.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <io.h>
#include <iomanip>
#include <Windows.h>
#include <Mmsystem.h>
#include "../json-3.10.5/single_include/nlohmann/json.hpp"


using namespace std;
using namespace nlohmann;
using json = nlohmann::json;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplicationDlg dialog


CMFCApplicationDlg::CMFCApplicationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSPEAKPAGE, pParent)
	, VB_TEXT(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TM, VB_TEXT);
	DDX_Control(pDX, IDC_EDIT_TM, m_text);
}

BEGIN_MESSAGE_MAP(CMFCApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SPEAK, &CMFCApplicationDlg::OnBnClickedSpeak)
	ON_EN_CHANGE(IDC_EDIT_TM, &CMFCApplicationDlg::OnEnChangeEditTm)
	ON_BN_CLICKED(IDC_BACK, &CMFCApplicationDlg::OnBnClickedBack)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFCApplicationDlg::OnCbnSelchangeCombo1)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()



// CMFCApplicationDlg message handlers


BOOL CMFCApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_Font.CreatePointFont(150, _T("Calibri"), NULL);
	m_text.SetFont(&m_Font);
	// TODO: Add extra initialization her

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplicationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplicationDlg::OnBnClickedSpeak()
{
	// TODO: Add the control notification handler code here
	CString m_text;
	CString PROGRAM_PATH = PathHandle ::FilePath();
	extern CString VoiceProfile;
	GetDlgItem(IDC_EDIT_TM)->GetWindowText(m_text);
	int textLen = m_text.GetLength();
	int profileExist = VoiceProfile.GetLength();
	if (profileExist == 0)
	{
		AfxMessageBox(_T("Please record or choose your voice"));
		MFCSetting dlg;
		dlg.DoModal();
	}
	if (textLen == 0)
	{
		AfxMessageBox(_T("Please enter text in the textbox"));
	}
	



	if (textLen != 0 && profileExist != 0)
	{
		// Initialise user selected profile
		CString profilePath;
		CString profile;
		profile = VoiceProfile;

		// modify the data.json to transfer data to back end

		CString pFilePath = PROGRAM_PATH;
		pFilePath.Append(CString("data\\data.json"));

		ofstream file(pFilePath);
		profilePath.Append(CString("data/profiles/"));
		profilePath.Append(profile);


		json j;
		j["lang"] = "en";
		string temp = CT2A(m_text.GetBuffer());
		const char* content = temp.c_str();
		j["text"] = content;
		temp = CT2A(profilePath.GetBuffer());
		const char* CCprofile = temp.c_str();
		j["profile"] = CCprofile;
		file << std::setw(4) << j;
		file.close();

		// Disable all buttons when back end generate sound
		CWnd* speakButton = GetDlgItem(IDC_SPEAK);
		CWnd* backButton = GetDlgItem(IDC_BACK);
		if (speakButton) 
		{
			speakButton->EnableWindow(FALSE);
			backButton->EnableWindow(FALSE);
			speakButton->SetWindowText(_T("Loading..."));
		}


		// Running back end by flask 
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

		// Play generated sound
		pFilePath.Replace(CString("\\data.json"), CString("\\output\\out.wav"));
		PlaySound(pFilePath, NULL, SND_FILENAME);

		// Enable all buttons
		if (speakButton) 
		{
			speakButton->EnableWindow(TRUE);
			backButton->EnableWindow(TRUE);
			speakButton->SetWindowText(_T("Speak"));
		}
	}
}



void CMFCApplicationDlg::OnEnChangeEditTm()
{

	//TODO: If the control is a RICHEDIT control, it will 
	//not send this notification unless you override the 
	//CDialogEx::OnInitDialog() functionand call CRichEditCtrl().
	//SetEventMask() and also operate the ENM_CHANGE flag "OR" into 
	//the mask.

	// TODO:  Add the control notification handler code here
}


void CMFCApplicationDlg::OnBnClickedBack()
{
	// TODO: Add the control notification handler code here
	CDialogEx::OnOK();
	return;
}

void CMFCApplicationDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add the control notification handler code here
	

}


void CMFCApplicationDlg::OnClose()
{
	DestroyWindow();
}

void CMFCApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnSysCommand(nID, lParam);
	CDialogEx::OnOK();
}
