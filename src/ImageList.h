#ifndef _IMAGELIST_H_
#define _IMAGELIST_H_

#include "Image.h"
#include <list>

// Wraps a list of images which is used to play animations.
class CImageList
{
public:
	// Kurucumuz
	CImageList();
	
	CImageList(const CImageList& other);
	// Yýkýcýmýz
	~CImageList();

	CImageList& operator= (const CImageList& other);
	
	void Clear();
	
	void AppendImage(TImagePtr pImage);
	
	unsigned GetImagesCount() const;

	void GoToFirstImage();

	bool GoToNextImage();
	// Image'ý geri döndür
	TImagePtr GetCurrentImage() const;

private:
	// 
	typedef std::list<TImagePtr> TImageList;
	//Image Listemiz
	TImageList m_lstImages;

	// Image'ýmizin iterasynu için 
	TImageList::iterator m_iterCurrentImg;
};

#endif  // _IMAGELIST_H_