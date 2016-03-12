#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include "Texture.h"
#include <string>
#include <map>

// Tüm texture'larýmýz yönetelim.
class CTextureManager
{
public:
	// Texture'larýmýzý alýyoruz
	CTexture* GetTexture(const std::string& strTextName);
	// texture bulunursa true döndür deðilse false
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