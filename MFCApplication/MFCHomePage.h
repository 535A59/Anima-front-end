#pragma once
#include "afxdialogex.h"


// MFCHomePage Dialog

class MFCHomePage : public CDialogEx
{
	DECLARE_DYNAMIC(MFCHomePage)

public:
	MFCHomePage(CWnd* pParent = nullptr);   // standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCancel();
	afx_msg void OnBnClickedSpeak();
	afx_msg void OnBnClickedRecord();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedSetting();
};

