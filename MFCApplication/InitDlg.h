#pragma once
#include "afxdialogex.h"


// InitDlg dialog

class InitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(InitDlg)

public:
	InitDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~InitDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnClose();


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};
