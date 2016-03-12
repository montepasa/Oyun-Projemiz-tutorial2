#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "Texture.h"
#include "Rectangle.h"
#include "SmartPtr.h"

class CImage;

typedef CSmartPtr<CImage> TImagePtr;

class CImage
{
public:
	// �zel lokasyonla ba�lat
	void BlitImage(int iXOffset=0, int iYOffset=0) const;
	// Texture'�m�z� image nesnesiyle d�nd�r�yoruz 
	CTexture* GetTexture() const  { return m_pTexture; }

	//Resmimizi �zel bir pointer kullanarak yerle�tiriyoruz
	static TImagePtr CreateImage(const std::string& strFileName);
	static TImagePtr CreateImage(const std::string& strFileName, 
								 const TRectanglei& textCoord);

	~CImage();

protected:
	// Olu�turdu�umuz image'leri sakl�yoruz
	CImage(const std::string& strFileName);
	CImage(const std::string& strFileName, const TRectanglei& textCoord);

private:
	// Image'lerimizi tutan texturelar�m�z� pointer ile g�steriyoruz
	CTexture*   m_pTexture;
	// texture koordinatlar�n� veriyoruz
	TRectanglei  m_rectTextCoord;
};

#endif  // _IMAGE_H_