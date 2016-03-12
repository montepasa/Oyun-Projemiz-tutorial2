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
	// Özel lokasyonla baþlat
	void BlitImage(int iXOffset=0, int iYOffset=0) const;
	// Texture'ýmýzý image nesnesiyle döndürüyoruz 
	CTexture* GetTexture() const  { return m_pTexture; }

	//Resmimizi özel bir pointer kullanarak yerleþtiriyoruz
	static TImagePtr CreateImage(const std::string& strFileName);
	static TImagePtr CreateImage(const std::string& strFileName, 
								 const TRectanglei& textCoord);

	~CImage();

protected:
	// Oluþturduðumuz image'leri saklýyoruz
	CImage(const std::string& strFileName);
	CImage(const std::string& strFileName, const TRectanglei& textCoord);

private:
	// Image'lerimizi tutan texturelarýmýzý pointer ile gösteriyoruz
	CTexture*   m_pTexture;
	// texture koordinatlarýný veriyoruz
	TRectanglei  m_rectTextCoord;
};

#endif  // _IMAGE_H_