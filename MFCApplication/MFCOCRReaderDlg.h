#pragma once
#include "afxdialogex.h"
#include "MFCSetting.h"


// MFCOCRReaderDlg Dialog

class MFCOCRReaderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MFCOCRReaderDlg)

public:
	MFCOCRReaderDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MFCOCRReaderDlg();
	CFont m_Font;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OCR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBack();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOpenfile();
	CEdit m_text;
	afx_msg void OnBnClickedRead();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};
