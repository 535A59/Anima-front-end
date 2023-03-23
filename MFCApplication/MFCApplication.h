
// MFCApplication.h:  main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// main sumbols
#include "InitThread.h"

// CMFCApplicationApp:
// See MFCApplication.cpp for the implemetation of this class
//

class CMFCApplicationApp : public CWinApp
{
public:
	CMFCApplicationApp();
	InitThread* pInitThread;
	InitDlg* m_pInitDlg;

// Overrides
public:
	virtual BOOL InitInstance();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplicationApp theApp;
