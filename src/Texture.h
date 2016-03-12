#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <Windows.h>
#include "GL/gl.h"
#include <string>


class CTextureManager;

// CImage Class'� sayesinde image'lerimiz render ediyorduk 
// �imdi texturelar�m�z� imagelerimize g�re render edece�iz
class CTexture
{
	friend class CTextureManager;

public:
	// texture rengini sa�lar biz burada transparan olarak kllanaca��z
	void SetColorKey(unsigned char Red, unsigned char Green, unsigned char Blue);

	// texture geni�li�i
	unsigned int GetWidth()  const  { return m_TextData.nWidth;  }
	// Returns texture y�ksekli�i
	unsigned int GetHeight() const  { return m_TextData.nHeight; }

	//referans noktas� olu�turuyoruz veya ekliyoruz
	void AddReference();
	void ReleaseReference();

	// Texture'lar�m�z birle�tiriyoruz
	void Bind() const;

protected:
	//
	CTexture(const std::string& strFileName);
	~CTexture();

private:

	void LoadFile(const std::string& strFileName);

	struct STextureData
	{
		// texture geni�lik
		unsigned int   nWidth;
		// texture y�kseklik
		unsigned int   nHeight;
		
		unsigned char* pData;
	};
	STextureData m_TextData;

	
	mutable GLuint m_glId;

	
	int m_iRefCount;
	
	std::string m_strTextName;
};

#endif  // _TEXTURE_H_