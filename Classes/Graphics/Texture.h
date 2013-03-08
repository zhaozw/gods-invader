#ifndef CONST_TEXTURE_H
#define CONST_TEXTURE_H

#include "cocos2d.h"

using namespace cocos2d;

class Texture
{
	protected:
		CCTexture2D* mTexture;

	public:
		int mHorizontalFramesCount;
		int mVerticalFramesCount;

		Texture(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);

		CCTexture2D* getTexture();
};

#endif