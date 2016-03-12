#include "Application.h" 
#include "Exception.h"

int WINAPI WinMain(HINSTANCE Instance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT)
{
	try
	{
		// Oyunumuzun class'lar�n� olu�tur
		// komut sat�r�n� parse et ve oyunu ba�lat
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