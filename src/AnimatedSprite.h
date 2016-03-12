#ifndef _ANIMATEDSPRITE_H_
#define _ANIMATEDSPRITE_H_

#include "Image.h"
#include "ImageList.h"
#include <string>
#include <map>
#include <list>


class CAnimatedSprite
{
public:
	// Kurucular ve Yýkýcýlar
	CAnimatedSprite();
	~CAnimatedSprite();

	// Sprite'lara animasyon ekle
	void AddAnimation(const std::string& strAnimName, 
					  const CImageList& lstAnimation);
	
	// Animasyonu yeniden yükle veya oynat
	void PlayAnimation(const std::string& strAnimName);

	// Son pozisyonu yeniden çiz
	// Son pozisyon
	void DrawSprite();
	// Bir dahaki animasyona git
	void NextFrame();

	// Yeni sprite için pozisyon belirle
	void SetPosition(int XPos, int YPos) 
	{
		m_iXPos = XPos;
		m_iYPos = YPos;
	}
	//Sprite'ý gidilecek olan pozisyona göre ayarla
	void OffsetPosition(int XOffset, int YOffset) 
	{
		m_iXPos += XOffset;
		m_iYPos += YOffset;
	}

private:
	typedef std::map<std::string, CImageList> TAnimMap;
	typedef TAnimMap::iterator TAnimMapIter;

	// Mapteki Bütün sprite animasyonlarý için
	// Oynat.
	TAnimMap m_mapAnimations;
	TAnimMapIter  m_iterCurrentAnim;

	// Sprite'larýn pozisyonu için
	int m_iXPos;
	int m_iYPos;
};

#endif  // _ANIMATEDSPRITE_H_