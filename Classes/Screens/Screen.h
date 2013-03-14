#ifndef CONST_SCREEN_H
#define CONST_SCREEN_H

#include "cocos2d.h"

#include "Entity.h"
#include "Options.h"

using namespace cocos2d;

class Screen : public CCScene, public CCTargetedTouchDelegate
{
	protected:
		// ===========================================================
		// Protected fields
		// ===========================================================

		bool mWasTouched;
		bool mIsRegisterAsTouchable;

	private:
		// ===========================================================
		// Constructor private function
		// ===========================================================

		// ===========================================================
		// Private fields
		// ===========================================================

		// ===========================================================
		// Private methods
		// ===========================================================

	public:
		// ===========================================================
		// Public fields
		// ===========================================================

		// ===========================================================
		// Constructors
		// ===========================================================

		Screen();

		// ===========================================================
		// Getters
		// ===========================================================

		// ===========================================================
		// Setters
		// ===========================================================

		// ===========================================================
		// Checkers
		// ===========================================================

		// ===========================================================
		// Events
		// ===========================================================

		virtual void onTouch(CCTouch* touch, CCEvent* event);

		// ===========================================================
		// Methods
		// ===========================================================

		// ===========================================================
		// Virtual methods
		// ===========================================================

		virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
		virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
		virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
		
		virtual bool containsTouchLocation(CCTouch* touch);

		virtual void setRegisterAsTouchable(bool pTouchable);

		virtual void onEnter();
		virtual void onExit();

		virtual void onEnterTransitionDidFinish();
};

#endif