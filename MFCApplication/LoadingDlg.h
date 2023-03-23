#pragma once
#include "afxdialogex.h"


// LoadingDlg dialog

class LoadingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LoadingDlg)

public:
	LoadingDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~LoadingDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOADING };
#endif

protected:
	LoadingDlg* m_pLoading;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();


	DECLARE_MESSAGE_MAP()
};
