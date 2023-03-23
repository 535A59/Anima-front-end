// InitThread.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "InitThread.h"


// InitThread

IMPLEMENT_DYNCREATE(InitThread, CWinThread)

InitThread::InitThread()
{
}

InitThread::~InitThread()
{
}

BOOL InitThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	::AttachThreadInput(m_nThreadID, AfxGetApp()->m_nThreadID, TRUE);
	m_pInitDlg = new InitDlg;
	m_pInitDlg->Create(IDD_INIT);
	m_pInitDlg->ShowWindow(SW_SHOW);
	return TRUE;

}

void InitThread::HideSplash()
{
	m_pInitDlg->SendMessage(WM_CLOSE);
}

void InitThread::ShowSplash()
{
	m_pInitDlg->ShowWindow(SW_SHOW);
}

int InitThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	m_pInitDlg->DestroyWindow();
	if (m_pInitDlg != NULL)
	{
		delete m_pInitDlg;
	}
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(InitThread, CWinThread)
END_MESSAGE_MAP()




// InitThread message handlers
