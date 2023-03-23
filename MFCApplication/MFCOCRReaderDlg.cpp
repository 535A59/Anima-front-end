// MFCOCRReaderDlg.cpp: realise file
//

#include "pch.h"
#include "MFCApplication.h"
#include "afxdialogex.h"
#include "MFCOCRReaderDlg.h"
#include "afxinet.h"
#include "MFCSetting.h"
#include "PathHandle.h"
#include <string>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <fstream>
#include <io.h>
#include <Windows.h>
#include <Mmsystem.h>
#include "../json-3.10.5/single_include/nlohmann/json.hpp"
using namespace tesseract;
using namespace std;
using namespace nlohmann;
using json = nlohmann::json;


// MFCOCRReaderDlg Dialog

IMPLEMENT_DYNAMIC(MFCOCRReaderDlg, CDialogEx)

MFCOCRReaderDlg::MFCOCRReaderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OCR, pParent)
{

}

MFCOCRReaderDlg::~MFCOCRReaderDlg()
{
}

void MFCOCRReaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_text);
}


BEGIN_MESSAGE_MAP(MFCOCRReaderDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BACK, &MFCOCRReaderDlg::OnBnClickedBack)
	ON_EN_CHANGE(IDC_EDIT1, &MFCOCRReaderDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_OPENFILE, &MFCOCRReaderDlg::OnBnClickedOpenfile)
	ON_BN_CLICKED(IDC_READ, &MFCOCRReaderDlg::OnBnClickedRead)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// MFCOCRReaderDlg message handlers
BOOL MFCOCRReaderDlg::OnInitDialog()
{
	// Initialise letter style
	CDialogEx::OnInitDialog();
	
	m_Font.CreatePointFont(150, _T("Calibri"), NULL);
	m_text.SetFont(&m_Font);

	return TRUE;

}



void MFCOCRReaderDlg::OnBnClickedBack()
{
	// TODO:  Add the control notification handler code here
	CDialogEx:OnOK();
	
}


void MFCOCRReaderDlg::OnEnChangeEdit1()
{
	//TODO: If the control is a RICHEDIT control, it will 
	//not send this notification unless you override the 
	//CDialogEx::OnInitDialog() functionand call CRichEditCtrl().
	//SetEventMask() and also operate the ENM_CHANGE flag "OR" into 
	//the mask.

	// TODO:  Add the control notification handler code here
}


void MFCOCRReaderDlg::OnBnClickedOpenfile()
{
	// TODO:  Add the control notification handler code here
	//setting filter 
	TCHAR szFilter[] = _T("png(*.png)|*.png|jpg(*.jpg)|*.jpg||");
	//generate file dialog   
	CFileDialog fileDlg(TRUE, _T("picture"), NULL, 0, szFilter, this);
	CString strFilePath;

	//show file dialog  
	if (IDOK == fileDlg.DoModal())
	{
		// if click "open" botton, put the file path into strFilePath  
		strFilePath = fileDlg.GetPathName();
	}


	CString text;
	CString PROGRAM_PATH = PathHandle::FilePath();
	CString pFilePath = PROGRAM_PATH;
	pFilePath.Append(CString("tessdata"));


	//Defind OCR api parameter type
	TessBaseAPI* myTessApi;
	myTessApi = new TessBaseAPI();


	//generate OCR api
	if (myTessApi->Init(CT2A(pFilePath.GetBuffer()), "eng"))
	{
		MessageBox(_T("Could not initialize tesseract.\n"));
		exit(1);
	}


	//Get text from picture
	string temp = CT2A(strFilePath.GetBuffer());
	Pix* image = pixRead(temp.c_str());
	myTessApi->SetImage(image);
	text = myTessApi->GetUTF8Text();

	//showing the letter into edit control box
	text.Replace(CString("\n"), CString("\r\n"));
	SetDlgItemText(IDC_EDIT1, text);
}




void MFCOCRReaderDlg::OnBnClickedRead()
{
	// TODO:  Add the control notification handler code here

	// Get the text selected by mouse
	CWinAppEx exit;
	int start, end;
	m_text.GetSel(start, end);
	CString selectedText;
	m_text.GetWindowText(selectedText);
	selectedText = selectedText .Right(selectedText.GetLength() - start);
	selectedText.Truncate(end - start);


	//Send those text to the json file
	selectedText.Replace(CString("\r\n"), CString(" "));
	CString profilePath;
	CString profile;
	extern CString VoiceProfile;
	int profileExist = VoiceProfile.GetLength();
	if (profileExist == 0)
	{
		AfxMessageBox(_T("Please record or choose your voice"));
		exit.CleanState();
	}
	int textExist = selectedText.GetLength();
	if (textExist == 0)
	{
		AfxMessageBox(_T("Please select some text"));
		exit.CleanState();

	}

	// open json file
	profile = VoiceProfile;
	CString PROGRAM_PATH = PathHandle::FilePath();
	CString pFilePath = PROGRAM_PATH;
	pFilePath.Append(CString("data\\data.json"));

	ofstream file(pFilePath);
	profilePath.Append(CString("data/profiles/"));
	profilePath.Append(profile);


	// write into data.json
	json j;
	j["lang"] = "en";
	string temp = CT2A(selectedText.GetBuffer());
	const char* content = temp.c_str();
	j["text"] = content;
	temp = CT2A(profilePath.GetBuffer());
	const char* CCprofile = temp.c_str();
	j["profile"] = CCprofile;
	file << std::setw(4) << j;
	file.close();


	//disable buttons during the loading
	CWnd* readButton = GetDlgItem(IDC_READ);
	CWnd* backButton = GetDlgItem(IDC_BACK);
	CWnd* fileButton = GetDlgItem(IDC_OPENFILE);
	if (readButton) {
		readButton->EnableWindow(FALSE);
		backButton->EnableWindow(FALSE);
		fileButton->EnableWindow(FALSE);
		readButton->SetWindowText(_T("Loading..."));
	}

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

	//play sound
	pFilePath.Replace(CString("\\data.json"), CString("\\output\\out.wav"));
	PlaySound(pFilePath, NULL, SND_FILENAME);

	//enable buttons
	if (readButton) {
		readButton->EnableWindow(TRUE);
		backButton->EnableWindow(TRUE);
		fileButton->EnableWindow(TRUE);
		readButton->SetWindowText(_T("Speak"));
	}
}


void MFCOCRReaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnSysCommand(nID, lParam);
	CDialogEx::OnOK();
}
