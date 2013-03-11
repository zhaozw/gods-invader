#ifndef CONST_BASEBULLET_H
#define CONST_BASEBULLET_H

#include "cocos2d.h"

#include "Entity.h"
#include "Hero.h"
#include "Options.h"
#include "Utils.h"

using namespace cocos2d;

class BaseBullet : public Entity
{
	protected:
		float mSpeed;
		float mPower;

		float mLifeTime;
		float mLifeTimeElapsed;

		bool mIsMoving;
		
		Entity* mShadow;

	private:

	public:
		float mVectorX;
		float mVectorY;
		
		BaseBullet();
		BaseBullet(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);

		float getSpeed();
		float getPower();

		void setSpeed(float pSpeed);
		void setPower(float pPower);

		void fire(float pX, float pY, float pVectorX, float pVectorY);

		void update(float pDeltaTime);

		virtual void destroy();

		/**
		 *
		 * Let's take care about object copy
		 *
		 */

		virtual BaseBullet* deepCopy();	
};

#endif