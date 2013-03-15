#ifndef CONST_PICKUP_H
#define CONST_PICKUP_H

#include "cocos2d.h"

#include "Entity.h"
#include "Utils.h"

using namespace cocos2d;

class Pickup : public Entity
{
	protected:
		// ===========================================================
		// Protected fields
		// ===========================================================

	private:
		// ===========================================================
		// Constructor private function
		// ===========================================================

		void constructor();

		// ===========================================================
		// Private fields
		// ===========================================================

		float mVectorX;
		float mVectorY;
		
		float mCenterX;
		float mCenterY;

		float mPaddingY;

		float mAnimationTime;
		float mAnimationTimeElapsed;

		bool mIsAnimationReverse;

		bool mIsFollow;

		Entity* mFollowEntity;

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

		Pickup();
		Pickup(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);

		// ===========================================================
		// Getters
		// ===========================================================

		// ===========================================================
		// Setters
		// ===========================================================

		void setFollowEntity(Entity* pEntity);

		// ===========================================================
		// Checkers
		// ===========================================================

		bool isFollow();

		// ===========================================================
		// Events
		// ===========================================================

		// ===========================================================
		// Methods
		// ===========================================================

		void reset();

		// ===========================================================
		// Virtual methods
		// ===========================================================

		virtual Entity* create();

		virtual void update(float pDeltaTime);

		virtual Pickup* deepCopy();	
};

#endif