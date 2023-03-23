#pragma once
#include "InitDlg.h"


// InitThread

class InitThread : public CWinThread
{
	DECLARE_DYNCREATE(InitThread)

protected:
	InitThread();           // protected constructor used by dynamic creation
	virtual ~InitThread();

protected:
	InitDlg* m_pInitDlg;

public:
	virtual BOOL InitInstance();
	virtual void HideSplash();
	virtual void ShowSplash();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


