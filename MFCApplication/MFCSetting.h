#pragma once
#include "afxdialogex.h"


// MFCSetting dialog

class MFCSetting : public CDialogEx
{
	DECLARE_DYNAMIC(MFCSetting)

public:
	MFCSetting(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MFCSetting();


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeDefaultvoice();
	afx_msg void OnBnClickedFindFile();
	afx_msg void OnClose();
	CComboBox m_voice;

//	afx_msg void OnSysColorChange();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};
