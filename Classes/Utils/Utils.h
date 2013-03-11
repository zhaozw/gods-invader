#ifndef CONST_UTILS_H
#define CONST_UTILS_H

#include "cocos2d.h"

#include <stdlib.h>
#include <cmath>

using namespace cocos2d;

class Utils
{
	public:
		static float randomf(float min, float max);
		static int random(int min, int max);
		static float coord(float pCoordinate);
		static float distance(float dX0, float dY0, float dX1, float dY1);

		static float Pi;
};

#endif