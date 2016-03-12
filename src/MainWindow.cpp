#include "MainWindow.h"
#include "Exception.h"
#include "Image.h"
#include "AnimFileLoader.h"
#include "TextureManager.h"

using namespace std;


#define WINDOW_CLASSNAME    "Knight Antalya"  // Pencere adý

CMainWindow::CMainWindow(int iWidth, int iHeight, bool bFullScreen) 
  :  m_hWindow(NULL), m_hDeviceContext(NULL), m_hGLContext(NULL), 
     m_bFullScreen(bFullScreen)
{
	RegisterWindowClass();

	RECT WindowRect;
	WindowRect.top = WindowRect.left = 0;
	WindowRect.right = iWidth;
	WindowRect.bottom = iHeight;

	// Pencere geniþlik stili
	DWORD dwExStyle = 0;	
	// Pencere stili
	DWORD dwStyle = 0;		

	if (m_bFullScreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		
		dmScreenSettings.dmPelsWidth	= iWidth;			
		dmScreenSettings.dmPelsHeight	= iHeight;		
		dmScreenSettings.dmBitsPerPel	= 32;		
		dmScreenSettings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

	
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)
				!= DISP_CHANGE_SUCCESSFUL)
		{
			throw CException("Tam ekran yapýlamaz");
		}

		dwExStyle = WS_EX_APPWINDOW;	
		dwStyle = WS_POPUP;		
	
		ShowCursor(FALSE);
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;	
	}

	// Adjust the window to the true requested size
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		
	// Now create the main window
    m_hWindow = CreateWindowEx(dwExStyle,TEXT(WINDOW_CLASSNAME), 
							 TEXT("Knigt Antalya"), 
							 WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle,
							 0, 0, WindowRect.right-WindowRect.left, 
							 WindowRect.bottom-WindowRect.top, 
							 NULL, NULL, 
							 GetModuleHandle(NULL), 
							 this);
	if (m_hWindow==NULL)
		throw CException("Oyun açýlamýyor");

	CreateContext();
	InitGL();
	ShowWindow(m_hWindow,SW_SHOW);

	OnSize(iWidth,iHeight);

	// Yeþillik alaný yükle, fakat ayný zamanda rengini de ayarla
	m_pGrassImg = CImage::CreateImage("GrassIso.bmp");
	m_pGrassImg->GetTexture()->SetColorKey(0,128,128);

	// Aðaçlarýmýzý yükle
	for (int i=0; i<16; i++)
	{
		TRectanglei imgRect(i/4*128,(i/4+1)*128,(i%4)*128,(i%4+1)*128);
		m_pTreesImg[i] = CImage::CreateImage("Trees.bmp",imgRect);
	}
	CTextureManager::GetInstance()->GetTexture("Trees.bmp")
		->SetColorKey(191, 123, 199);

	// savaþçýmýzý hazýrla
	m_pKnightSprite = new CAnimatedSprite;
	CAnimFileLoader fileLoader1("KnightWalk.bmp", 8, 96, 96);
	CTextureManager::GetInstance()->GetTexture("KnightWalk.bmp")
		->SetColorKey(111, 79, 51);
	m_pKnightSprite->AddAnimation("WalkE",
			fileLoader1.GetAnimation(0,7));
	m_pKnightSprite->AddAnimation("WalkSE",
			fileLoader1.GetAnimation(8,15));
	m_pKnightSprite->AddAnimation("WalkS",
			fileLoader1.GetAnimation(16,23));
	m_pKnightSprite->AddAnimation("WalkSW",
			fileLoader1.GetAnimation(24,31));
	m_pKnightSprite->AddAnimation("WalkW",
			fileLoader1.GetAnimation(32,39));
	m_pKnightSprite->AddAnimation("WalkNW",
			fileLoader1.GetAnimation(40,47));
	m_pKnightSprite->AddAnimation("WalkN",
			fileLoader1.GetAnimation(48,55));
	m_pKnightSprite->AddAnimation("WalkNE",
			fileLoader1.GetAnimation(56,63));

	// Oyunu Pause'ye al
	CAnimFileLoader fileLoader2("KnightPause.bmp", 8, 96, 96);
	CTextureManager::GetInstance()->GetTexture("KnightPause.bmp")
		->SetColorKey(111, 79, 51);
	m_pKnightSprite->AddAnimation("PauseE",
			fileLoader2.GetAnimation(0,7));
	m_pKnightSprite->AddAnimation("PauseSE",
			fileLoader2.GetAnimation(8,15));
	m_pKnightSprite->AddAnimation("PauseS",
			fileLoader2.GetAnimation(16,23));
	m_pKnightSprite->AddAnimation("PauseSW",
			fileLoader2.GetAnimation(24,31));
	m_pKnightSprite->AddAnimation("PauseW",
			fileLoader2.GetAnimation(32,39));
	m_pKnightSprite->AddAnimation("PauseNW",
			fileLoader2.GetAnimation(40,47));
	m_pKnightSprite->AddAnimation("PauseN",
			fileLoader2.GetAnimation(48,55));
	m_pKnightSprite->AddAnimation("PauseNE",
			fileLoader2.GetAnimation(56,63));
	m_pKnightSprite->PlayAnimation("PauseE");

	for (int i=0; i<4; i++)
		m_KeysDown[i] = false;
	// Doðuya yönel
	m_strLastDir = "E";
	m_pKnightSprite->SetPosition(350,250);
}

CMainWindow::~CMainWindow()
{
	if (m_bFullScreen)
	{
		// Tam ekrandan çýkmak için bu fonksiyonu kuruyoruz
		ChangeDisplaySettings(NULL,0);
		ShowCursor(TRUE);	
	}

	if (m_hGLContext)
	{
		wglMakeCurrent(NULL,NULL);
		wglDeleteContext(m_hGLContext);
		m_hGLContext = NULL;
	}
	if (m_hDeviceContext)
	{
		ReleaseDC(m_hWindow,m_hDeviceContext);
		m_hDeviceContext = NULL;
	}

    DestroyWindow(m_hWindow);
    UnregisterClass(TEXT(WINDOW_CLASSNAME), GetModuleHandle(NULL));
}

LRESULT CMainWindow::OnEvent(HWND Handle, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (Message == WM_NCCREATE)
	{
		CREATESTRUCT* pCreateStruct = reinterpret_cast<CREATESTRUCT*>(lParam);

        SetWindowLongPtr(Handle, GWLP_USERDATA, 
						 reinterpret_cast<long>(pCreateStruct->lpCreateParams));
	}

    CMainWindow* pWindow = reinterpret_cast<CMainWindow*>
		(GetWindowLongPtr(Handle, GWLP_USERDATA));
	if (pWindow)
		pWindow->ProcessEvent(Message,wParam,lParam);

    return DefWindowProc(Handle, Message, wParam, lParam);
}

void CMainWindow::ProcessEvent(UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
    case WM_CLOSE :
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		OnSize(LOWORD(lParam),HIWORD(lParam));
		break;
    case WM_KEYDOWN :
		switch (wParam)
		{
		case VK_UP:
			m_KeysDown[0] = true;
			break;
		case VK_DOWN:
			m_KeysDown[1] = true;
			break;
		case VK_LEFT:
			m_KeysDown[2] = true;
			break;
		case VK_RIGHT:
			m_KeysDown[3] = true;
			break;
		}
		UpdateAnimation();
        break;
    case WM_KEYUP :
 		switch (wParam)
		{
		case VK_UP:
			m_KeysDown[0] = false;
			break;
		case VK_DOWN:
			m_KeysDown[1] = false;
			break;
		case VK_LEFT:
			m_KeysDown[2] = false;
			break;
		case VK_RIGHT:
			m_KeysDown[3] = false;
			break;
		}
		UpdateAnimation();
		break;
    }
}

void CMainWindow::RegisterWindowClass()
{
    WNDCLASS WindowClass;
    WindowClass.style         = 0;
    WindowClass.lpfnWndProc   = &CMainWindow::OnEvent;
    WindowClass.cbClsExtra    = 0;
    WindowClass.cbWndExtra    = 0;
    WindowClass.hInstance     = GetModuleHandle(NULL);
    WindowClass.hIcon         = NULL;
    WindowClass.hCursor       = 0;
    WindowClass.hbrBackground = 0;
    WindowClass.lpszMenuName  = NULL;
    WindowClass.lpszClassName = WINDOW_CLASSNAME;

    RegisterClass(&WindowClass);
}

void CMainWindow::CreateContext()
{
	
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;	// Oyununuza versiyon girin
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |	// Pencere oluþtur
				  PFD_SUPPORT_OPENGL |	// OPENGL'yi desteklemeli
				  PFD_DOUBLEBUFFER;		
	pfd.iPixelType = PFD_TYPE_RGBA;		// RGBA formatýnda kullan 
	pfd.cColorBits = 32;				// 32 bit renk

	if (!(m_hDeviceContext=GetDC(m_hWindow)))	
		throw CException("Unable to create rendering context");

	int PixelFormat;
	
	if (!(PixelFormat=ChoosePixelFormat(m_hDeviceContext,&pfd)))				
		throw CException("Unable to create rendering context");
	
	if(!SetPixelFormat(m_hDeviceContext,PixelFormat,&pfd))			
		throw CException("Unable to create rendering context");
	
	if (!(m_hGLContext=wglCreateContext(m_hDeviceContext)))	
		throw CException("Unable to create rendering context");

	if(!wglMakeCurrent(m_hDeviceContext,m_hGLContext))
		throw CException("Unable to create rendering context");						
}

void CMainWindow::InitGL()
{
	glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
}

void CMainWindow::OnSize(GLsizei width, GLsizei height)
{
    glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,width,height,0.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
}

void CMainWindow::Update(DWORD dwCurrentTime)
{
	int xOffset = 0;
	int yOffset = 0;
	if (m_KeysDown[0])
		yOffset -= 5;
	if (m_KeysDown[1])
		yOffset += 5;
	if (m_KeysDown[2])
		xOffset -= 5;
	if (m_KeysDown[3])
		xOffset += 5;
	m_pKnightSprite->OffsetPosition(xOffset, yOffset);
}

void CMainWindow::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	int xPos=0, yPos=0;
	for (int i=0; i<8; i++)
	{
		for (int j=0; j<6; j++)
		{
			xPos = i * 256/2 - 128;
			if (i%2)
				yPos = (j * 128) - 128/2;
			else
				yPos = (j * 128);

			m_pGrassImg->BlitImage(xPos, yPos);
		}
	}

	m_pTreesImg[0]->BlitImage(15,25);
	m_pTreesImg[1]->BlitImage(695,55);
	m_pTreesImg[2]->BlitImage(15,25);
	m_pTreesImg[3]->BlitImage(300,400);
	m_pTreesImg[4]->BlitImage(125,75);
	m_pTreesImg[5]->BlitImage(350,250);
	m_pTreesImg[6]->BlitImage(400,350);
	m_pTreesImg[7]->BlitImage(350,105);
	m_pTreesImg[8]->BlitImage(530,76);
	m_pTreesImg[9]->BlitImage(125,450);
	m_pTreesImg[10]->BlitImage(425,390);
	m_pTreesImg[11]->BlitImage(25,125);
	m_pTreesImg[12]->BlitImage(550,365);
	m_pTreesImg[13]->BlitImage(680,250);
	m_pTreesImg[14]->BlitImage(245,325);
	m_pTreesImg[15]->BlitImage(300,245);

	m_pKnightSprite->DrawSprite();
	m_pKnightSprite->NextFrame();
	SwapBuffers(m_hDeviceContext);
}

void CMainWindow::UpdateAnimation()
{
	bool keyPressed = false;
	for (int i=0; i<4; i++)
	{
		if (m_KeysDown[i])
		{
			keyPressed = true;
			break;
		}
	}

	string strAnim;
	if (!keyPressed)
		strAnim = "Pause" + m_strLastDir;
	if (keyPressed)
	{
		string vertDir;
		string horizDir;
		if (m_KeysDown[0])
			vertDir = "N";
		else if (m_KeysDown[1])
			vertDir = "S";
		if (m_KeysDown[2])
			horizDir = "W";
		else if (m_KeysDown[3])
			horizDir = "E";
		m_strLastDir = vertDir + horizDir;
		strAnim = "Walk" + m_strLastDir;
	}
	m_pKnightSprite->PlayAnimation(strAnim);
}