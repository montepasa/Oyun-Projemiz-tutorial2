
#include "TextureManager.h"
#include "Exception.h"
#include <IL/IL.h>

using namespace std;

CTextureManager::CTextureManager() : m_Textures()
{
	ilInit();

	ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
	ilEnable(IL_ORIGIN_SET);
}

CTextureManager::~CTextureManager()
{
	TTextureMap::iterator iter = m_Textures.begin();
	for (iter; iter != m_Textures.end(); iter++)
	{
		if (iter->second)
			delete iter->second;
	}
}

CTextureManager* CTextureManager::GetInstance()
{
	static CTextureManager Instance;
	return &Instance;
}

CTexture* CTextureManager::GetTexture(const string& strTextName)
{
	TTextureMap::const_iterator iter = m_Textures.find(strTextName);
	if (iter != m_Textures.end())
		return iter->second;

	CTexture* pNewText = NULL;
	try
	{
		pNewText = new CTexture(strTextName);
	}
	catch (CException& e)
	{
		delete pNewText;
		throw e;
	}

	m_Textures[strTextName] = pNewText;
	return pNewText;
}

bool CTextureManager::ReleaseTexture(const std::string& strTextName)
{
	bool bFound = false;
	TTextureMap::iterator iter = m_Textures.find(strTextName);
	if (iter != m_Textures.end())
	{
		bFound = true;
		if (iter->second)
			delete iter->second;
		m_Textures.erase(iter);
	}

	return bFound;
}
