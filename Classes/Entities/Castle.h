#ifndef CONST_CASTLE_H
#define CONST_CASTLE_H

#include "cocos2d.h"

#include "Entity.h"

using namespace cocos2d;

class Castle : public Entity
{
	protected:

	private:

	public:
		Castle(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);
};

#endif