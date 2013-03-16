#ifndef CONST_SMALLCUBIC_H
#define CONST_SMALLCUBIC_H

#include "cocos2d.h"

#include "BaseCubic.h"

using namespace cocos2d;

class SmallCubic : public BaseCubic
{
	protected:
		virtual void reset();

	private:

	public:
		SmallCubic();
		SmallCubic(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);

		virtual SmallCubic* deepCopy();
};

#endif