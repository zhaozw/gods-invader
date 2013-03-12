#ifndef CONST_HEALTHENTITY
#define CONST_HEALTHENTITY

#include "HealthEntity.h"

// ===========================================================
// Init
// ===========================================================

void HealthEntity::constructor()
{
	this->mHealth = 0;
	this->mMaxHealth = 0;

	this->mIsShow = false;
}

// ===========================================================
// Constructors
// ===========================================================

HealthEntity::HealthEntity()
{
	this->constructor();
}

HealthEntity::HealthEntity(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
	Entity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
	{
		this->constructor();
	}

// ===========================================================
// Getters
// ===========================================================

float HealthEntity::getHealth()
{
	return this->mHealth;
}

float HealthEntity::getMaxHealth()
{
	return this->mMaxHealth;
}

// ===========================================================
// Setters
// ===========================================================

void HealthEntity::setHealth(float pHealth)
{
	// If mMaxHealth is not defined we must to define it as full mHealth
	if(this->mMaxHealth == 0)
	{
		this->mMaxHealth = pHealth;
	}

	this->mHealth = pHealth;
}

void HealthEntity::setMaxHealth(float pMaxHealth)
{
	this->mMaxHealth = pMaxHealth;
}

// ===========================================================
// Methods
// ===========================================================

void HealthEntity::addHealth(float pHealth)
{
	this->mHealth += pHealth;

	this->updateBar();
}

void HealthEntity::removeHealth(float pHealth)
{
	this->mHealth -= pHealth;

	// We must call some "die" method if health are not enought
	if(this->mHealth <= 0)
	{
		// TODO: Call "die" method
	}

	this->updateBar();
}

void HealthEntity::updateBar()
{
	// Setting up colors for health bar
	this->R = this->mHealth < COLOR_MAX_HEALTH ? 1 : 0;
	this->G = this->mHealth > COLOR_MIN_HEALTH ? 1 : 0;
	this->B = 0;

	// Is we must to show health bar?
	if(this->mHealth < this->mMaxHealth)
	{
		this->mIsShow = true;
	}
	else
	{
		this->mIsShow = false;
	}

	// Calculate new coordinates
	float x1;
	float x2;

	float y1;
	float y2;

	// Setting up black rectangle

	x1 = (this->getWidth() - BAR_WITH) / 2;
	x2 = this->getWidth() - x1;

	y1 = -12;
	y2 = -16;

	this->mRectangleVerticles1[0] = ccp(x1, y1);
	this->mRectangleVerticles1[1] = ccp(x2, y1);
	this->mRectangleVerticles1[2] = ccp(x2, y2);
	this->mRectangleVerticles1[3] = ccp(x1, y2);

	// Setting up health rectangle

	x1 = (this->getWidth() - BAR_WITH) / 2 + BAR_PADDING;
	x2 = (this->getWidth() - x1) * (this->getHealth() / this->getMaxHealth()) - BAR_PADDING;

	y1 = -13;
	y2 = -15;

	/**float full = (this->getWidth() - 5);

	if(this->getScaleX() > 0)
	{
		x1 = 5;
		x2 = full * (this->getHealth() / this->getMaxHealth());
	}
	else
	{
		x1 = 5;
		x2 = full * (this->getHealth() / this->getMaxHealth());

		x1 += full - x2;
		x2 += full - x2;
	}**/

	this->mRectangleVerticles2[0] = ccp(x1, y1);
	this->mRectangleVerticles2[1] = ccp(x2, y1);
	this->mRectangleVerticles2[2] = ccp(x2, y2);
	this->mRectangleVerticles2[3] = ccp(x1, y2);
}

// ===========================================================
// Virtual methods
// ===========================================================

void HealthEntity::draw()
{
	Entity::draw();

	if(this->mIsShow)
	{
		ccDrawSolidPoly(this->mRectangleVerticles1, VERTICLES_COUNT, ccc4f(0, 0, 0, 1));
		ccDrawSolidPoly(this->mRectangleVerticles2, VERTICLES_COUNT, ccc4f(this->R, this->G, this->B, 1));
	}
}

#endif