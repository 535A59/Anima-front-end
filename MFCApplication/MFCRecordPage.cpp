// MFCRecordPage.cpp: implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "afxdialogex.h"
#include "atlstr.h"
#include "afxinet.h"
#include "MFCRecordPage.h"
#include "MFCSetting.h"
#include "PathHandle.h"
#include "InitDlg.h"
#include <atlstr.h>
#include <windows.h>
#include <mmsystem.h>
#include <tchar.h>
#include <Windows.h>
#include <io.h>
#include <stdlib.h>
#include <cstdlib>
#include "../json-3.10.5/single_include/nlohmann/json.hpp"
#pragma comment(lib, "WINMM.LIB")

HWAVEIN hWaveIn;//Wave_audio data formate
WAVEFORMATEX waveform;
HWAVEOUT hWaveOut;//function to open replay device　
WAVEHDR* pWaveHdr1;
WAVEHDR* pWaveHdr2;
#define BUFFER_SIZE (44100*16*2/8*5)    // length of recorded voice
#define FRAGMENT_SIZE 1024*4              // size of buffer space
#define FRAGMENT_NUM 4                  // number of buffer space 
//static unsigned char pSaveBuffer[BUFFER_SIZE] = {0}; 
PBYTE pBuffer1;
PBYTE pBuffer2;
PBYTE pSaveBuffer;
PBYTE pNewBuffer;
int dwDataLength = FRAGMENT_SIZE;
bool bEnding;


#pragma once



// MFCRecordPage dialog

IMPLEMENT_DYNAMIC(MFCRecordPage, CDialogEx)

MFCRecordPage::MFCRecordPage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RECORD, pParent)
{

}

MFCRecordPage::~MFCRecordPage()
{
}

void MFCRecordPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_text);
}

BEGIN_MESSAGE_MAP(MFCRecordPage, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_BN_CLICKED(ID_RECORD_END, &MFCRecordPage::OnBnClickedRecordEnd)
	ON_BN_CLICKED(ID_RECORD_START, &MFCRecordPage::OnBnClickedRecordStart)
	ON_MESSAGE(MM_WIM_DATA, &MFCRecordPage::OnMM_WIM_DATA)	
	ON_MESSAGE(MM_WIM_CLOSE, &MFCRecordPage::OnMM_WIN_CLOSE)
	ON_MESSAGE(MM_WOM_OPEN, &MFCRecordPage::OnMM_WOM_OPEN)
	ON_MESSAGE(MM_WOM_DONE, &MFCRecordPage::OnMM_WOM_DONE)
	ON_MESSAGE(MM_WOM_CLOSE, &MFCRecordPage::OnMM_WOM_CLOSE)
	ON_MESSAGE(MM_WIM_OPEN, &MFCRecordPage::OnMM_WIM_OPEN)
	ON_BN_CLICKED(IDC_BACK, &MFCRecordPage::OnBnClickedBack)
	ON_EN_CHANGE(IDC_EDIT1, &MFCRecordPage::OnEnChangeEdit1)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_OPENFILE, &MFCRecordPage::OnBnClickedOpenFile)
END_MESSAGE_MAP()


// MFCRecordPage message handlers


BOOL MFCRecordPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//allocate memory for wave header 
	pWaveHdr1 = reinterpret_cast<PWAVEHDR>(malloc(sizeof(WAVEHDR)));
	pWaveHdr2 = reinterpret_cast<PWAVEHDR>(malloc(sizeof(WAVEHDR)));
	//allocate memory for save buffer   
	pSaveBuffer = reinterpret_cast<PBYTE>(malloc(1));

	CString PROGRAM_PATH = PathHandle::FilePath();	
	CFile pCFile;
	CString pFilePath = PROGRAM_PATH;
	CString name("\PhoneticPangrams.txt");
	pFilePath.Append(name);
	pCFile.Open(pFilePath, CFile::modeRead);
	char* pBuf;
	DWORD dwFileLen;
	dwFileLen = pCFile.GetLength();
	pBuf = new char[dwFileLen + 1];
	pBuf[dwFileLen] = 0;
	pCFile.Read(pBuf, dwFileLen);
	CString FileData(pBuf);

	m_Font.CreatePointFont(150,_T("Calibri"), NULL);
	m_text.SetFont(&m_Font);
	SetDlgItemText(IDC_EDIT1, FileData);

	return TRUE;
}

void MFCRecordPage::OnBnClickedRecordStart()
{
;	//allocate buffer memory   
	pBuffer1 = (PBYTE)malloc(dwDataLength);
	pBuffer2 = (PBYTE)malloc(dwDataLength);
	if (!pBuffer1 || !pBuffer2) {
		if (pBuffer1) free(pBuffer1);
		if (pBuffer2) free(pBuffer2);
		MessageBeep(MB_ICONEXCLAMATION);
		AfxMessageBox(_T("Memory erro!"));
		return;
	}
	//open waveform audo for input   
	waveform.wFormatTag = WAVE_FORMAT_PCM;
	waveform.nChannels = 2;
	waveform.nSamplesPerSec = 44100;
	waveform.nAvgBytesPerSec = 176400;
	waveform.nBlockAlign = 4;
	waveform.wBitsPerSample = 16;
	waveform.cbSize = 0;

	if (waveInOpen(&hWaveIn, WAVE_MAPPER, &waveform, (DWORD)this->m_hWnd, NULL, CALLBACK_WINDOW)) {
		free(pBuffer1);
		free(pBuffer2);
		MessageBeep(MB_ICONEXCLAMATION);
		AfxMessageBox(_T("Audio can not be open!"));
		return;
	}
	pWaveHdr1->lpData = (LPSTR)pBuffer1;
	pWaveHdr1->dwBufferLength = dwDataLength;
	pWaveHdr1->dwBytesRecorded = 0;
	pWaveHdr1->dwUser = 0;
	pWaveHdr1->dwFlags = 0;
	pWaveHdr1->dwLoops = 1;
	pWaveHdr1->lpNext = NULL;
	pWaveHdr1->reserved = 0;
	waveInPrepareHeader(hWaveIn, pWaveHdr1, sizeof(WAVEHDR));
	pWaveHdr2->lpData = (LPSTR)pBuffer2;  //
	pWaveHdr2->dwBufferLength = dwDataLength;
	pWaveHdr2->dwBytesRecorded = 0;
	pWaveHdr2->dwUser = 0;
	pWaveHdr2->dwFlags = 0;
	pWaveHdr2->dwLoops = 1;
	pWaveHdr2->lpNext = NULL;
	pWaveHdr2->reserved = 0;
	waveInPrepareHeader(hWaveIn, pWaveHdr2, sizeof(WAVEHDR));

	pSaveBuffer = (PBYTE)realloc(pSaveBuffer, 1);
	// Add the buffers   
	waveInAddBuffer(hWaveIn, pWaveHdr1, sizeof(WAVEHDR));
	waveInAddBuffer(hWaveIn, pWaveHdr2, sizeof(WAVEHDR));
	// Begin sampling   
	bEnding = FALSE;
	dwDataLength = 0;
	waveInStart(hWaveIn);
}


void MFCRecordPage::OnBnClickedRecordEnd()
{
	bEnding = TRUE;
	//Stop recording
	waveInReset(hWaveIn);

	// give name to record
	RecordName.DoModal();
	CString Name("");
	RecordName.GetName(Name);
	int flag = Name.GetLength();
	if (flag == 0)
	{
		AfxMessageBox(_T("Please name your voice profile."));
	}
	else 
	{
		//Store voice file
		CFile m_file;
		CFileException fileException;

		//Convert the voice file to .wav file	
		CString PROGRAM_PATH = PathHandle::FilePath();

		if (!(GetFileAttributes(PROGRAM_PATH) == FILE_ATTRIBUTE_DIRECTORY))
		{
			if (!CreateDirectory(PROGRAM_PATH, NULL))
			{
				AfxMessageBox(_T("Make Dir Error"));
			}
		}

		// Delete original temp folder and create a new empty temp folder
		CString m_csFileName = PROGRAM_PATH ;
		m_csFileName.Append(CString("data\\temp"));
		std::string command = "rmdir /Q /S ";
		std::string path = CT2A(m_csFileName.GetBuffer());
		int i = system(command.append(path).c_str());
		CreateDirectory(m_csFileName, NULL);

		// Store voice file into temp file
		m_csFileName.Append(_T("\\"));
		m_csFileName.Append(Name);
		m_csFileName.Append(_T(".wav"));
		m_file.Open(m_csFileName, CFile::modeCreate | CFile::modeReadWrite, &fileException);
		DWORD m_WaveHeaderSize = 38;
		DWORD m_WaveFormatSize = 18;
		m_file.SeekToBegin();
		m_file.Write("RIFF", 4);
 
		unsigned int Sec = (sizeof pSaveBuffer + m_WaveHeaderSize);
		m_file.Write(&Sec, sizeof(Sec));
		m_file.Write("WAVE", 4);
		m_file.Write("fmt ", 4);
		m_file.Write(&m_WaveFormatSize, sizeof(m_WaveFormatSize));

		m_file.Write(&waveform.wFormatTag, sizeof(waveform.wFormatTag));
		m_file.Write(&waveform.nChannels, sizeof(waveform.nChannels));
		m_file.Write(&waveform.nSamplesPerSec, sizeof(waveform.nSamplesPerSec));
		m_file.Write(&waveform.nAvgBytesPerSec, sizeof(waveform.nAvgBytesPerSec));
		m_file.Write(&waveform.nBlockAlign, sizeof(waveform.nBlockAlign));
		m_file.Write(&waveform.wBitsPerSample, sizeof(waveform.wBitsPerSample));
		m_file.Write(&waveform.cbSize, sizeof(waveform.cbSize));
		m_file.Write("data", 4);
		m_file.Write(&dwDataLength, sizeof(dwDataLength));

		m_file.Write(pSaveBuffer, dwDataLength);
		m_file.Seek(dwDataLength, CFile::begin);
		m_file.Close();
    
		// running profile generate program
		try
		{
			CInternetSession session;
			CHttpConnection* connection = session.GetHttpConnection(CString("127.0.0.1"));
			CHttpFile* File = connection->OpenRequest(CString("GET"), CString("/record"));
			File->SendRequest();

		}
			catch (const std::exception& e)
		{
			MessageBox(CString("Request Failed"));
		}

		// make the new profile as the user selected one
		Name.Append(CString(".animaprofile"));
		extern CString VoiceProfile;
		VoiceProfile = Name;

		MFCSetting dlg;
		dlg.DoModal();
	}
}



void MFCRecordPage::OnBnClickedOpenFile()
{
	// TODO: Add your control notification handler code here
	TCHAR szFilter[] = _T("wav(*.wav)|*.wav||");
	//generate file dialog   
	CFileDialog fileDlg(TRUE, _T("picture"), NULL, 0, szFilter, this);
	CWinAppEx exit;
	CString strFilePath;
	CString Name;

	// Delete original temp folder and create a new temp folder
	CString PROGRAM_PATH = PathHandle::FilePath();
	CFile pCFile;
	CString pFilePath = PROGRAM_PATH;
	pFilePath.Append(CString("data\\temp"));
	std::string command = "rmdir /Q /S ";
	std::string path = CT2A(pFilePath.GetBuffer());
	int i = system(command.append(path).c_str());
	CreateDirectory(pFilePath, NULL);
	pFilePath.Replace(CString("data\\temp"),CString("data\\temp\\"));
	//show file dialog  
	
	if (IDOK == fileDlg.DoModal())
	{
		// if click "open" botton, put the file path into strFilePath  
		strFilePath = fileDlg.GetPathName();
		Name = fileDlg.GetFileName();

	}
	else
	{
		exit.CleanState();
	}

	int ChangeName = MessageBox(_T("Do you want to change your file name?"), NULL,MB_YESNO);
	
	// Change the record name if user want
	if (ChangeName == 6)
	{
		loop:
		RecordName.DoModal();
		RecordName.GetName(Name);
		int flag = Name.GetLength();
		if (flag == 0)
		{
			AfxMessageBox(_T("Please name your voice profile."));
			goto loop;

		}
		pFilePath.Append(Name);
		pFilePath.Append(CString(".wav"));
	}
	else
	{
		pFilePath.Append(Name);
	}
	
	//Copy the user chose file to temp folder
	CopyFile(strFilePath, pFilePath, true);

	// Generate profile
	try
	{
		CInternetSession session;
		CHttpConnection* connection = session.GetHttpConnection(CString("127.0.0.1"));
		CHttpFile* File = connection->OpenRequest(CString("GET"), CString("/record"));
		File->SendRequest();

	}
	catch (const std::exception& e)
	{
		MessageBox(CString("Request Failed"));
	}


	Name.Replace(CString(".wav"), CString(".animaprofile"));
	extern CString VoiceProfile;
	VoiceProfile = Name;
}



afx_msg LRESULT MFCRecordPage::OnMM_WIM_OPEN(WPARAM wParam, LPARAM lParam)
{
	((CWnd*)(this->GetDlgItem(ID_RECORD_START)))->EnableWindow(FALSE);
	((CWnd*)(this->GetDlgItem(ID_RECORD_END)))->EnableWindow(TRUE);
	return 0;
}

afx_msg LRESULT MFCRecordPage::OnMM_WIM_DATA(WPARAM wParam, LPARAM lParam)
{
	// Reallocate save buffer memory   
	pNewBuffer = (PBYTE)realloc(pSaveBuffer, dwDataLength + ((PWAVEHDR)lParam)->dwBytesRecorded);

	if (pNewBuffer == NULL)
	{
		waveInClose(hWaveIn);
		MessageBeep(MB_ICONEXCLAMATION);
		AfxMessageBox(_T("erro memory"));
		return TRUE;
	}

	pSaveBuffer = pNewBuffer;
	CopyMemory(pSaveBuffer + dwDataLength, ((PWAVEHDR)lParam)->lpData,
		((PWAVEHDR)lParam)->dwBytesRecorded);
	dwDataLength += ((PWAVEHDR)lParam)->dwBytesRecorded;

	if (bEnding)
	{
		waveInClose(hWaveIn);
		return TRUE;
	}

	waveInAddBuffer(hWaveIn, (PWAVEHDR)lParam, sizeof(WAVEHDR));
	return 0;
}


afx_msg LRESULT MFCRecordPage::OnMM_WIN_CLOSE(WPARAM wParam, LPARAM lParam)
{
	KillTimer(1);
	if (0 == dwDataLength) {
		return TRUE;
	}
	waveInUnprepareHeader(hWaveIn, pWaveHdr1, sizeof(WAVEHDR));
	waveInUnprepareHeader(hWaveIn, pWaveHdr2, sizeof(WAVEHDR));

	free(pBuffer1);
	free(pBuffer2);

	if (dwDataLength > 0)
	{
		//enable play   
		((CWnd*)(this->GetDlgItem(ID_RECORD_START)))->EnableWindow(TRUE);
		((CWnd*)(this->GetDlgItem(ID_RECORD_END)))->EnableWindow(FALSE);
	}

	((CWnd*)(this->GetDlgItem(ID_RECORD_START)))->EnableWindow(TRUE);
	((CWnd*)(this->GetDlgItem(ID_RECORD_END)))->EnableWindow(FALSE);
	
	
	
	return 0;
}


afx_msg LRESULT MFCRecordPage::OnMM_WOM_OPEN(WPARAM wParam, LPARAM lParam)
{

	pWaveHdr1->lpData = (LPSTR)pSaveBuffer;  //???
	pWaveHdr1->dwBufferLength = dwDataLength;
	pWaveHdr1->dwBytesRecorded = 0;
	pWaveHdr1->dwUser = 0;
	pWaveHdr1->dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
	pWaveHdr1->dwLoops = 1;
	pWaveHdr1->lpNext = NULL;
	pWaveHdr1->reserved = 0;

	// Prepare and write   

	waveOutPrepareHeader(hWaveOut, pWaveHdr1, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, pWaveHdr1, sizeof(WAVEHDR));

	((CWnd*)(this->GetDlgItem(ID_RECORD_START)))->EnableWindow(TRUE);
	((CWnd*)(this->GetDlgItem(ID_RECORD_END)))->EnableWindow(FALSE);
	return 0;
}


afx_msg LRESULT MFCRecordPage::OnMM_WOM_DONE(WPARAM wParam, LPARAM lParam)
{
	waveOutUnprepareHeader(hWaveOut, pWaveHdr1, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
	return  NULL;
	return 0;
}


afx_msg LRESULT MFCRecordPage::OnMM_WOM_CLOSE(WPARAM wParam, LPARAM lParam)
{
	((CWnd*)(this->GetDlgItem(ID_RECORD_START)))->EnableWindow(TRUE);
	((CWnd*)(this->GetDlgItem(ID_RECORD_END)))->EnableWindow(FALSE);
	return 0;
}





void MFCRecordPage::OnBnClickedBack()
{
	CDialogEx::OnOK();
}




void MFCRecordPage::OnEnChangeEdit1()
{
	//TODO: If the control is a RICHEDIT control, it will 
	//not send this notification unless you override the 
	//CDialogEx::OnInitDialog() functionand call CRichEditCtrl().
	//SetEventMask() and also operate the ENM_CHANGE flag "OR" into 
	//the mask.

	// TODO:  Add the control notification handler code here
}


void MFCRecordPage::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnSysCommand(nID, lParam);
	CDialogEx::OnOK();
}


