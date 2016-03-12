#include "Texture.h"
#include "TextureManager.h"
#include "Exception.h"
#include <string>
#include <IL/il.h>

using namespace std;

CTexture::CTexture(const std::string& strFileName) 
 : m_TextData(), m_glId(0), m_iRefCount(0), 
   m_strTextName(strFileName)
{
	m_TextData.nHeight = m_TextData.nWidth = 0;
	m_TextData.pData = NULL;

	LoadFile(m_strTextName);
}

CTexture::~CTexture()
{
	if (m_TextData.pData)
	{
		delete[] m_TextData.pData;
		m_TextData.pData = NULL;
	}
}

void CTexture::LoadFile(const std::string& strFileName)
{
	ILuint imgId;
	ilGenImages(1,&imgId);
	ilBindImage(imgId);

	if (!ilLoadImage(strFileName.c_str()))
	{
		string strError = "Failed to load file: " + strFileName;
		throw CException(strError);
	}

	m_TextData.nWidth	= ilGetInteger(IL_IMAGE_WIDTH);
	m_TextData.nHeight	= ilGetInteger(IL_IMAGE_HEIGHT);

	unsigned int size = m_TextData.nWidth * m_TextData.nHeight * 4;
	m_TextData.pData = new unsigned char[size];
	ilCopyPixels(0, 0, 0, m_TextData.nWidth, m_TextData.nHeight,
		1, IL_RGBA, IL_UNSIGNED_BYTE, m_TextData.pData);
	ilDeleteImage(imgId);
}

void CTexture::AddReference()
{
	m_iRefCount++;
}

void CTexture::ReleaseReference()
{
	m_iRefCount--;
	if (m_iRefCount == 0)
		CTextureManager::GetInstance()->ReleaseTexture(m_strTextName);
}

void CTexture::Bind() const
{
	if(!m_glId)
	{
		glGenTextures(1,&m_glId);
		glBindTexture(GL_TEXTURE_2D,m_glId);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);			
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glTexImage2D(GL_TEXTURE_2D, 0, 4, m_TextData.nWidth, m_TextData.nHeight,
				0,GL_RGBA,GL_UNSIGNED_BYTE,m_TextData.pData);
	}

	glBindTexture(GL_TEXTURE_2D,m_glId);
}

void CTexture::SetColorKey(unsigned char Red, 
						   unsigned char Green, 
						   unsigned char Blue)
{
	if (m_glId)
	{
		glDeleteTextures(1,&m_glId);
		m_glId = 0;
	}

	unsigned long Count = m_TextData.nWidth * m_TextData.nHeight * 4;
	for (unsigned long i = 0; i<Count; i+=4)
	{
		if ( (m_TextData.pData[i]==Red) && (m_TextData.pData[i+1]==Green) 
			  && (m_TextData.pData[i+2]==Blue) )
			m_TextData.pData[i+3] = 0;
		else
			m_TextData.pData[i+3] = 255;

	}
}
