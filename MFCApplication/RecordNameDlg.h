#pragma once
#include "afxdialogex.h"


// RecordNameDlg Dialog

class RecordNameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RecordNameDlg)

public:
	RecordNameDlg(CWnd* pParent = nullptr);   // standard constructor

	virtual ~RecordNameDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECORDNAME };
#endif

private:
	CString m_RecordName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeRecordname();
	void GetName(CString& Name);
};
