#ifndef CONST_SCREEN
#define CONST_SCREEN

#include "Screen.h"

Screen::Screen()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	this->scheduleUpdate();
}

/**
 *
 * Checing for touch detector
 *
 */

bool Screen::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if(!this->mIsRegisterAsTouchable || !this->isVisible())
	{
		return false;
	}

	if(containsTouchLocation(touch))
	{
		this->mWasTouched = true;

		return true;
	}

	return true;
}

void Screen::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	if(!containsTouchLocation(touch))
	{
		this->mWasTouched = false;
	}
}

void Screen::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if(this->mWasTouched)
	{
		this->onTouch(touch, event);
	}

	this->mWasTouched = false;
}

bool Screen::containsTouchLocation(CCTouch* touch)
{
	return CCRectMake(-Options::CAMERA_WIDTH / 2, -Options::CAMERA_HEIGHT / 2, Options::CAMERA_WIDTH, Options::CAMERA_HEIGHT).containsPoint(convertTouchToNodeSpaceAR(touch));
}

void Screen::setRegisterAsTouchable(bool pTouchable)
{
	this->mIsRegisterAsTouchable = pTouchable;
}

void Screen::onTouch(CCTouch* touch, CCEvent* event)
{
}

#endif