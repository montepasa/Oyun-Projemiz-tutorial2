
#include "Image.h"
#include "Exception.h"
#include "TextureManager.h"

using namespace std;

CImage::CImage(const string& strFileName) 
  : m_pTexture(NULL), m_rectTextCoord()
{
	//texture bulunamazsa hata mesajý döndürecek fonksiyonumuz
	m_pTexture = CTextureManager::GetInstance()->GetTexture(strFileName); 
	m_pTexture->AddReference();

	//texture koordinatlarý
	m_rectTextCoord.m_Top = m_rectTextCoord.m_Left = 0;
	m_rectTextCoord.m_Bottom = m_pTexture->GetHeight();
	m_rectTextCoord.m_Right = m_pTexture->GetWidth();
}

CImage::CImage(const string& strFileName, const TRectanglei& textCoord)
  : m_pTexture(NULL), m_rectTextCoord(textCoord)
{
	//texture bulunamazsa hata mesajý döndürecek fonksiyonumuz
	m_pTexture = CTextureManager::GetInstance()->GetTexture(strFileName); 
	m_pTexture->AddReference();
}

TImagePtr CImage::CreateImage(const string& strFileName)
{
	TImagePtr imgPtr(new CImage(strFileName));
	return imgPtr;
}

TImagePtr CImage::CreateImage(const string& strFileName, const TRectanglei& textCoord)
{
	TImagePtr imgPtr(new CImage(strFileName,textCoord));
	return imgPtr;
}


CImage::~CImage()
{
	if (m_pTexture)
		m_pTexture->ReleaseReference();
}

void CImage::BlitImage(int iXOffset, int iYOffset) const
{
	if (m_pTexture)
	{
		m_pTexture->Bind();

	
		float Top	 = ((float)m_rectTextCoord.m_Top)/m_pTexture->GetHeight();
		float Bottom = ((float)m_rectTextCoord.m_Bottom)/m_pTexture->GetHeight();
		float Left   = ((float)m_rectTextCoord.m_Left)/m_pTexture->GetWidth();
		float Right  = ((float)m_rectTextCoord.m_Right)/m_pTexture->GetWidth();

		
		glBegin(GL_QUADS);
		glTexCoord2f(Left,Top);		glVertex3i(iXOffset,iYOffset,0);
		glTexCoord2f(Left,Bottom);	glVertex3i(iXOffset,iYOffset+m_rectTextCoord.GetHeight(),0);
		glTexCoord2f(Right,Bottom);	glVertex3i(iXOffset+m_rectTextCoord.GetWidth(),iYOffset+m_rectTextCoord.GetHeight(),0);
		glTexCoord2f(Right,Top);	glVertex3i(iXOffset+m_rectTextCoord.GetWidth(),iYOffset,0);
		glEnd();
	}
}


