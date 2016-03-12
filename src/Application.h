#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <windows.h>

// The application class, which simply wraps the message queue and process
// the command line.
class CApplication
{
public:
	CApplication(HINSTANCE hInstance);
	~CApplication();

	void ParseCmdLine(LPSTR lpCmdLine);
	void Run();

private:
	static const int FRAME_TIME = 75;

	HINSTANCE m_hInstance;
	//Fullscreen baþlat
	bool m_bFullScreen;
};

#endif  // _APPLICATION_H_