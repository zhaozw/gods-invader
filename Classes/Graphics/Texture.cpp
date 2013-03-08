#ifndef CONST_TEXTURE
#define CONST_TEXTURE

#include "Texture.h"

Texture::Texture(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount)
{
	this->mTexture = CCTextureCache::sharedTextureCache()->addImage(pszFileName);
			
	this->mHorizontalFramesCount = pHorizontalFramesCount;
	this->mVerticalFramesCount   = pVerticalFramesCount;
}

CCTexture2D* Texture::getTexture()
{
	return this->mTexture;
}

#endif