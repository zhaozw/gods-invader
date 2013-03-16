#ifndef CONST_SMALLCUBIC
#define CONST_SMALLCUBIC

#include "SmallCubic.h"

SmallCubic::SmallCubic() :
	BaseCubic()
	{

	}

SmallCubic::SmallCubic(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
	BaseCubic(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
	}

void SmallCubic::reset()
{
	BaseCubic::reset();

	this->setHealth(100);

	this->animate(0.03f, 0, 20);
}

SmallCubic* SmallCubic::deepCopy()
{
	return new SmallCubic("platform/pickup-cube2-animation.png", 10, 4);
}

#endif