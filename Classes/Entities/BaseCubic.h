#ifndef CONST_BASECUBIC_H
#define CONST_BASECUBIC_H

#include "cocos2d.h"

#include "BarEntity.h"

using namespace cocos2d;

class BaseCubic : public BarEntity
{
	protected:
		virtual void reset();

	private:

	public:
		BaseCubic();
		BaseCubic(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);

		virtual Entity* create();
};

#endif