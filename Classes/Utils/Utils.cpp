#ifndef CONST_UTILS
#define CONST_UTILS

#include "Utils.h"

float Utils::Pi = std::atan(1.0) * 4;

float Utils::randomf(float min, float max)
{
	return min + (float) rand() / ((float) RAND_MAX / (max - min));
}

int Utils::random(int min, int max)
{
	return min + rand() / (RAND_MAX / (max - min));
}

float Utils::coord(float pCoordinate)
{
	return pCoordinate / CCDirector::sharedDirector()->getContentScaleFactor();
}

#endif