#ifndef CONST_UTILS_H
#define CONST_UTILS_H

#include "cocos2d.h"

#include <stdlib.h>

using namespace cocos2d;

class Utils
{
	public:
		static float randomf(float min, float max);
		static int random(int min, int max);
		static float coord(float pCoordinate);
};

#endif