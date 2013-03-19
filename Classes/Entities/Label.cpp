#ifndef CONST_LABEL
#define CONST_LABEL

#include "Label.h"

// ===========================================================
// Inner Classes
// ===========================================================

// ===========================================================
// Constants
// ===========================================================

// ===========================================================
// Fields
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

Label::Label(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
	Entity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->mFadeAnimationTime = 2.5f;

		this->mIsShouldShow = false;

		this->destroy();
	}

Label::Label(const char* pszFileName) :
	Entity(pszFileName)
{
		this->mFadeAnimationTime = 2.5f;

		this->mIsShouldShow = false;

		this->destroy();
}

// ===========================================================
// Methods
// ===========================================================

void Label::show(float pFadeInPauseTime, float pDisplayTime)
{
	this->mFadeInPauseTime = pFadeInPauseTime;
	this->mDisplayTime = pDisplayTime;

	this->mFadeInPauseTimeElapsed = 0.0f;

	this->mIsShouldShow = true;
}

void Label::show(float pDisplayTime)
{
	this->show(0.0f, pDisplayTime);
}

void Label::show()
{
	this->create()->setOpacity(0.0f);

	this->mDisplayTimeElapsed = 0.0f;

	this->runAction(CCFadeTo::create(this->mFadeAnimationTime, 255.0f));
}

void Label::hide()
{
	this->runAction(CCFadeTo::create(this->mFadeAnimationTime, 0.0f));
}

// ===========================================================
// Virtual Methods
// ===========================================================

void Label::update(float pDeltaTime)
{
	Entity::update(pDeltaTime);

	this->mDisplayTimeElapsed += pDeltaTime;
	this->mFadeInPauseTimeElapsed += pDeltaTime;

	if(this->mIsShouldShow && this->mFadeInPauseTimeElapsed >= this->mFadeInPauseTime)
	{
		this->mIsShouldShow = false;

		this->show();
	}

	if(this->mDisplayTimeElapsed >= this->mDisplayTime)
	{
		this->mDisplayTimeElapsed -= this->mDisplayTime;

		this->hide();
	}
}

#endif