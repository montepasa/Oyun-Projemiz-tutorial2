#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <Windows.h>
#include "GL/gl.h"
#include <string>


class CTextureManager;

// CImage Class'ý sayesinde image'lerimiz render ediyorduk 
// þimdi texturelarýmýzý imagelerimize göre render edeceðiz
class CTexture
{
	friend class CTextureManager;

public:
	// texture rengini saðlar biz burada transparan olarak kllanacaðýz
	void SetColorKey(unsigned char Red, unsigned char Green, unsigned char Blue);

	// texture geniþliði
	unsigned int GetWidth()  const  { return m_TextData.nWidth;  }
	// Returns texture yüksekliði
	unsigned int GetHeight() const  { return m_TextData.nHeight; }

	//referans noktasý oluþturuyoruz veya ekliyoruz
	void AddReference();
	void ReleaseReference();

	// Texture'larýmýz birleþtiriyoruz
	void Bind() const;

protected:
	//
	CTexture(const std::string& strFileName);
	~CTexture();

private:

	void LoadFile(const std::string& strFileName);

	struct STextureData
	{
		// texture geniþlik
		unsigned int   nWidth;
		// texture yükseklik
		unsigned int   nHeight;
		
		unsigned char* pData;
	};
	STextureData m_TextData;

	
	mutable GLuint m_glId;

	
	int m_iRefCount;
	
	std::string m_strTextName;
};

#endif  // _TEXTURE_H_