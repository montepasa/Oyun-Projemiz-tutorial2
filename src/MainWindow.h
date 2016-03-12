#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <Windows.h>
#include "GL/gl.h"
#include "Image.h"
#include "AnimatedSprite.h"

// Ana Pencere için baþlýk dosyamýz
class CMainWindow
{
public:
	CMainWindow(int iWidth, int iHeight, bool bFullScreen);
	~CMainWindow();

	// 
	void Update(DWORD dwCurrentTime);
	// Oyunumuzu çizdirmemize yarayan fonksiyonumuz
	void Draw();

private:
	
	void RegisterWindowClass();
	// Context oluþtur
	void CreateContext();
	// OPENGL'Ü YÜKLE
	void InitGL();

	// Boyutlarýný yakaladýðýmýz fonksiyon
	void OnSize(GLsizei width, GLsizei height);

	// Pencerenin özelliklerini geri döndüren foksiyonumuz
    static LRESULT CALLBACK OnEvent(HWND Handle, UINT Message, WPARAM wParam, LPARAM lParam);

	void ProcessEvent(UINT Message, WPARAM wParam, LPARAM lParam);

	void UpdateAnimation();

	
	HWND	m_hWindow;

    HDC     m_hDeviceContext;
	
    HGLRC   m_hGLContext;    

	
	bool m_bFullScreen;

	// Çimler için
	TImagePtr m_pGrassImg;

	// Aðaçlar için
	TImagePtr m_pTreesImg[16];

	// Savaþçýmýzýn animasyonu için
	CAnimatedSprite* m_pKnightSprite;
	// Kaç tuþ takýmý çalýþacak
	bool m_KeysDown[4];
	// Savaþçýmýzýn son yönü
	std::string m_strLastDir;
};

#endif  // _MAINWINDOW_H_