#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <Windows.h>
#include "GL/gl.h"
#include "Image.h"
#include "AnimatedSprite.h"

// Ana Pencere i�in ba�l�k dosyam�z
class CMainWindow
{
public:
	CMainWindow(int iWidth, int iHeight, bool bFullScreen);
	~CMainWindow();

	// 
	void Update(DWORD dwCurrentTime);
	// Oyunumuzu �izdirmemize yarayan fonksiyonumuz
	void Draw();

private:
	
	void RegisterWindowClass();
	// Context olu�tur
	void CreateContext();
	// OPENGL'� Y�KLE
	void InitGL();

	// Boyutlar�n� yakalad���m�z fonksiyon
	void OnSize(GLsizei width, GLsizei height);

	// Pencerenin �zelliklerini geri d�nd�ren foksiyonumuz
    static LRESULT CALLBACK OnEvent(HWND Handle, UINT Message, WPARAM wParam, LPARAM lParam);

	void ProcessEvent(UINT Message, WPARAM wParam, LPARAM lParam);

	void UpdateAnimation();

	
	HWND	m_hWindow;

    HDC     m_hDeviceContext;
	
    HGLRC   m_hGLContext;    

	
	bool m_bFullScreen;

	// �imler i�in
	TImagePtr m_pGrassImg;

	// A�a�lar i�in
	TImagePtr m_pTreesImg[16];

	// Sava���m�z�n animasyonu i�in
	CAnimatedSprite* m_pKnightSprite;
	// Ka� tu� tak�m� �al��acak
	bool m_KeysDown[4];
	// Sava���m�z�n son y�n�
	std::string m_strLastDir;
};

#endif  // _MAINWINDOW_H_