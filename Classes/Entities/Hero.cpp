#ifndef CONST_HERO
#define CONST_HERO

#include "Hero.h"

Hero::Hero(const char* pszFileName) :
	Entity(pszFileName)
	{
		this->setSpeed(200); // I should remove this
		this->setScale(0.7);
	}

float Hero::getSpeed()
{
	return this->mSpeed;
}

void Hero::setSpeed(float pSpeed)
{
	this->mSpeed = pSpeed;
}

#endif