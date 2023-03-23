
// MFCApplicationDlg.h: header file
//


#pragma once
#include "afxdialogex.h"
#include "MFCSetting.h"

// CMFCApplicationDlg Dialog
class CMFCApplicationDlg : public CDialogEx
{
// Construction
public:
	CMFCApplicationDlg(CWnd* pParent = nullptr);	// standard constructor
	CFont m_Font;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSpeak();
	afx_msg void OnEnChangeEditTm();
	CString VB_TEXT;
	CEdit m_text;
	afx_msg void OnBnClickedBack();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnClose();
	CComboBox m_select_voice;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};
