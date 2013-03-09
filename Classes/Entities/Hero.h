#ifndef CONST_HERO_H
#define CONST_HERO_H

#include "cocos2d.h"

#include "Entity.h"

using namespace cocos2d;

class Hero : public Entity
{
	protected:
		int mSpeed;

	private:

	public:
		Hero(const char* pszFileName);

		float getSpeed();

		void setSpeed(float pSpeed);	
};

#endif