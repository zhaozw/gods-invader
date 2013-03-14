#ifndef CONST_PRELOADER_H
#define CONST_PRELOADER_H

#include "cocos2d.h"

#include "Screen.h"
#include "Level.h"

using namespace cocos2d;

class Preloader : public Screen
{
	private:
		int mNumberOfSprites;
		int mNumberOfLoadedSprites;

		Entity* mBackground;
		Entity* mBarBackground;
		Entity* mBar;

	public:
		Preloader(void);

		void loadingCallBack(CCObject *obj);

		virtual void update(float pDeltaTime);
};

#endif