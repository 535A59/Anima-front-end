#pragma once
#include "afxdialogex.h"
#include "RecordNameDlg.h"
#include "MFCSetting.h"

// MFCRecordPage Dialog

class MFCRecordPage : public CDialogEx
{
	DECLARE_DYNAMIC(MFCRecordPage)

public:
	MFCRecordPage(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MFCRecordPage();
	CFont m_Font;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECORD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg 
	afx_msg void OnBnClickedRecordEnd();
	afx_msg void OnBnClickedRecordStart();

	RecordNameDlg RecordName;
protected:
//	afx_msg LRESULT OnMM_WIN_OPEN(WPARAM wParam, LPARAM lParam);
public:
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
protected:
	afx_msg LRESULT OnMM_WIM_DATA(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMM_WIN_CLOSE(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMM_WOM_OPEN(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMM_WOM_DONE(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMM_WOM_CLOSE(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMM_WIM_OPEN(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedBack();
	afx_msg void OnEnChangeEdit1();
	CEdit m_text;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBnClickedOpenFile();
};
