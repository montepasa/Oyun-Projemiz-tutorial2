#include "Application.h" 
#include "Exception.h"

int WINAPI WinMain(HINSTANCE Instance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT)
{
	try
	{
		// Oyunumuzun class'larýný oluþtur
		// komut satýrýný parse et ve oyunu baþlat
		CApplication theApp(Instance);
		theApp.ParseCmdLine(lpCmdLine);
		theApp.Run();
	}
	catch(CException& e)
	{
		MessageBox(NULL,e.what(),"Error",MB_OK|MB_ICONEXCLAMATION);
	}

	return 0;
}