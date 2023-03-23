#pragma once
#include "afxdialogex.h"


// MFCSettingDlg Dialog

class MFCSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MFCSettingDlg)

public:
	MFCSettingDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MFCSettingDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
