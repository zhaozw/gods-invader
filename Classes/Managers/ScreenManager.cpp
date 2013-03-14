#ifndef CONST_SCREENMANAGER
#define CONST_SCREENMANAGER

#include "ScreenManager.h"

// ===========================================================
// Init
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

ScreenManager::ScreenManager()
{
	this->generate();
}

// ===========================================================
// Getters
// ===========================================================

// ===========================================================
// Setters
// ===========================================================

// ===========================================================
// Methods
// ===========================================================

void ScreenManager::set(float pAnimationTime, int pIndex)
{
	CCTransitionScene* transition = CCTransitionFade::create(pAnimationTime, this->mScreens[pIndex]);

	CCDirector::sharedDirector()->setDepthTest(true);
	CCDirector::sharedDirector()->pushScene(transition);
}

void ScreenManager::generate()
{
	this->mScreens[0] = new Level();
	this->mScreens[1] = new GameOver();
	this->mScreens[2] = new GameWon();
}

// ===========================================================
// Virtual methods
// ===========================================================

#endif