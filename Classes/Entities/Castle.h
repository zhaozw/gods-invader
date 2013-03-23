#ifndef CONST_CASTLE_H
#define CONST_CASTLE_H

#include "cocos2d.h"

#include "Entity.h"
#include "BarEntity.h"
#include "EntityManager.h"

using namespace cocos2d;

class Cherry : public Entity
{
	public:
		Cherry() :
			Entity()
		{
		}

		Cherry(const char* pszFileName) :
			Entity(pszFileName)
		{
		}

		Entity* deepCopy()
		{
			return new Cherry("base/cherry.png");
		}
};

class Castle : public BarEntity
{
	protected:
		EntityManager* mCherries;

	private:

	public:
		Castle(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount);

		void fire(float pVectorX, float pVectorY);

		virtual void update(float pDeltaTime);

		void draw();
};

#endif