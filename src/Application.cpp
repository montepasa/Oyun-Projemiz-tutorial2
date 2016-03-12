#include "Application.h"
#include "MainWindow.h"
#include <string>

#pragma warning(disable:4996)

CApplication::CApplication(HINSTANCE hInstance)
  : m_hInstance(hInstance), m_bFullScreen(false)
{
}

CApplication::~CApplication()
{
}

void CApplication::ParseCmdLine(LPSTR lpCmdLine)
{
	LPSTR lpArgument = strtok(lpCmdLine," ");
	while (lpArgument)
	{
		if (stricmp(lpArgument,"-fullscreen") == 0)
			m_bFullScreen = true;
		lpArgument = strtok(NULL," ");
	}
}

void CApplication::Run()
{
	// Create the main window first
	CMainWindow mainWindow(800,600,m_bFullScreen);

    MSG Message;
    Message.message = ~WM_QUIT;
	DWORD dwNextDeadLine = GetTickCount() + FRAME_TIME;
	DWORD dwSleep = FRAME_TIME;
	bool bUpdate = false;

    while (Message.message != WM_QUIT)
    {
		
		DWORD dwResult = MsgWaitForMultipleObjectsEx(0,NULL,dwSleep,QS_ALLEVENTS,0);
		if (dwResult != WAIT_TIMEOUT)
		{
		
			while (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
			{
			
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}

		
			if (GetTickCount() >= dwNextDeadLine)
				bUpdate = true;
			else
				bUpdate = false;
		}
		else
	
			bUpdate = true;

	
		if (bUpdate)
		{
			DWORD dwCurrentTime = GetTickCount();
		
			mainWindow.Update(dwCurrentTime);
		
			mainWindow.Draw();

			dwNextDeadLine = dwNextDeadLine + FRAME_TIME;
		}

		dwSleep =  dwNextDeadLine - GetCurrentTime();
	
		if (dwSleep>FRAME_TIME)
		{
			dwSleep = FRAME_TIME;
			dwNextDeadLine = GetCurrentTime() + FRAME_TIME;
		}
	}
}