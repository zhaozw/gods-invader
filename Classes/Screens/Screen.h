#ifndef CONST_SCREEN_H
#define CONST_SCREEN_H

#include "cocos2d.h"

#include "Entity.h"
#include "Options.h"

using namespace cocos2d;

class Screen : public CCScene, public CCTargetedTouchDelegate
{
	protected:
		bool mWasTouched;
		bool mIsRegisterAsTouchable;

	public:
		Screen();

	/**
	 *
	 * Checing for touch detector
	 *
	 */

	bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	void ccTouchMoved(CCTouch* touch, CCEvent* event);
	void ccTouchEnded(CCTouch* touch, CCEvent* event);
		
	bool containsTouchLocation(CCTouch* touch);

	void setRegisterAsTouchable(bool pTouchable);

	virtual void onTouch(CCTouch* touch, CCEvent* event);
};

#endif