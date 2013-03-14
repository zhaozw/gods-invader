#ifndef CONST_SMALLCLOUD_H
#define CONST_SMALLCLOUD_H

#include "cocos2d.h"

#include "Entity.h"

using namespace cocos2d;

class Cloud : public Entity
{
	protected:
		// ===========================================================
		// Protected fields
		// ===========================================================

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

		SmallCloud();
		SmallCloud(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);

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

		// ===========================================================
		// Methods
		// ===========================================================

		// ===========================================================
		// Virtual methods
		// ===========================================================

		virtual SmallCloud* deepCopy();	
};

#endif