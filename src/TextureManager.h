#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include "Texture.h"
#include <string>
#include <map>

// T�m texture'lar�m�z y�netelim.
class CTextureManager
{
public:
	// Texture'lar�m�z� al�yoruz
	CTexture* GetTexture(const std::string& strTextName);
	// texture bulunursa true d�nd�r de�ilse false
	bool ReleaseTexture(const std::string& strTextName);

	// singleton nesnemiz
	static CTextureManager* GetInstance();

protected:
	
	CTextureManager();
	~CTextureManager();

private:
	typedef std::map<std::string,CTexture*> TTextureMap;

	TTextureMap m_Textures;
};

#endif  // _TEXTUREMANAGER_H_