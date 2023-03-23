#pragma once
#include "afxdialogex.h"


// MFCSpeakPage Dialog

class MFCSpeakPage : public CDialogEx
{
	DECLARE_DYNAMIC(MFCSpeakPage)

public:
	MFCSpeakPage(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MFCSpeakPage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
