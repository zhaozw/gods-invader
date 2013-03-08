#ifndef CONST_LEVEL_H
#define CONST_LEVEL_H

#include "cocos2d.h"

#include "Screen.h"
#include "Options.h"

using namespace cocos2d;

class Level : public Screen
{
	private:

	public:
		Level(void);

		virtual void update(float pDeltaTime);
};

#endif