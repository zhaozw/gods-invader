#ifndef CONST_SCREENMANAGER
#define CONST_SCREENMANAGER

#include "ScreenManager.h"

// ===========================================================
// Init
// ===========================================================

ScreenManager::constructor()
{
	this->generate();
}

// ===========================================================
// Constructors
// ===========================================================

ScreenManager::ScreenManager()
{
	this->constructor();
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

ScreenManager::set(float pAnimationTime, int pIndex)
{
	CCTransitionScene* transition = CCTransitionFade::create(pAnimationTime, this->mScreens[pIndex]);

	CCDirector::sharedDirector()->setDepthTest(true);
	CCDirector::sharedDirector()->pushScene(transition);
}

ScreenManager::generate()
{
	this->mScreens[0] = new Level();
	this->mScreens[1] = new GameOver();
	this->mScreens[2] = new GameWon();
}

// ===========================================================
// Virtual methods
// ===========================================================

#endif