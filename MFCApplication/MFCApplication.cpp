
// MFCApplication.cpp:  Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication.h"
#include "MFCApplicationDlg.h"
#include "MFCHomePage.h"
#include "InitDlg.h"
#include "PathHandle.h"
#include <fstream>
#include <iostream>
#include "../json-3.10.5/single_include/nlohmann/json.hpp"


using namespace std;
using namespace nlohmann;
using json = nlohmann::json;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplicationApp

BEGIN_MESSAGE_MAP(CMFCApplicationApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCApplicationApp construction

CMFCApplicationApp::CMFCApplicationApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here
	// Place all significant initialization in InitInstance
}


// The one and only CMFCApplicationApp object

CMFCApplicationApp theApp;


// CMFCApplicationApp Initialization

BOOL CMFCApplicationApp::InitInstance()
{
	AfxOleInit();
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("UCL Anima v2 Speech Synthesis"));

	// Initialise loading page
	pInitThread = (InitThread*)AfxBeginThread(
		RUNTIME_CLASS(InitThread),
		THREAD_PRIORITY_NORMAL,
		0, CREATE_SUSPENDED);

	ASSERT(pInitThread->IsKindOf(RUNTIME_CLASS(InitThread)));
	pInitThread->ResumeThread();

	// Initialise back-end program;
	CString PROGRAM_PATH = PathHandle::FilePath();
	CString pFilePath = PROGRAM_PATH;
	ShellExecute(NULL, _T("runas"), _T("setup.bat"), NULL, pFilePath, 0);
	pFilePath.Append(CString("data\\status.json"));
	
	// Initialise status check json file
	ofstream jFile(pFilePath);
	json jInit;
	jInit["ready"] = false;
	jFile << std::setw(4) << jInit;
	jFile.close();

	// Check whether back-end program has finished initialisation
	stringstream jBuffer;
	bool flag = false;
	string s;
	json j;

	while (!flag)
	{
		ifstream jFile(pFilePath);
		jBuffer << jFile.rdbuf();
		s = jBuffer.str();
		j = json::parse(s);
		flag = j["ready"];
		jFile.close();
		jBuffer.str(std::string());
		// Check initialisation status every second
		Sleep(1000);
	}

	// Initialise end
	if (((CMFCApplicationApp*)AfxGetApp())->pInitThread != NULL)
		((CMFCApplicationApp*)AfxGetApp())->pInitThread->HideSplash();

	// Go to home page
	MFCHomePage dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	


	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		
	}
	
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
