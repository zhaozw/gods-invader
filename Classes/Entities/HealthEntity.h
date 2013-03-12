#ifndef CONST_HEALTHENTITY_H
#define CONST_HEALTHENTITY_H

#include "cocos2d.h"

#include "Entity.h"

using namespace cocos2d;

class HealthEntity : public Entity
{
	protected:
		// ===========================================================
		// Protected fields
		// ===========================================================

		float mHealth;
		float mMaxHealth;

	private:
		// ===========================================================
		// Constructor private function
		// ===========================================================

		void constructor();

		// ===========================================================
		// Private fields
		// ===========================================================

		bool mIsShow;

		CCPoint mRectangleVerticles1[4];
		CCPoint mRectangleVerticles2[4];

		float R;
		float G;
		float B;

		static int const COLOR_MAX_HEALTH = 75;
		static int const COLOR_MIN_HEALTH = 45;

		static int const VERTICLES_COUNT = 4;

		static int const BAR_WITH = 22;

		static int const BAR_PADDING = 1;

		// ===========================================================
		// Private methods
		// ===========================================================

		void updateBar();

	public:
		// ===========================================================
		// Constructors
		// ===========================================================

		HealthEntity();
		HealthEntity(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);

		// ===========================================================
		// Getters
		// ===========================================================

		float getHealth();
		float getMaxHealth();

		// ===========================================================
		// Setters
		// ===========================================================

		void setHealth(const float pHealth);
		void setMaxHealth(const float pMaxHealth);

		// ===========================================================
		// Checkers
		// ===========================================================

		// ===========================================================
		// Events
		// ===========================================================

		// ===========================================================
		// Methods
		// ===========================================================

		void addHealth(float pHealth);

		void removeHealth(float pHealth);

		// ===========================================================
		// Virtual methods
		// ===========================================================

		virtual void draw();
		
};

#endif