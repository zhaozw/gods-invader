#ifndef CONST_CASTLEENEMY_H
#define CONST_CASTLEENEMY_H

#include "cocos2d.h"

#include "BaseEnemy.h"

using namespace cocos2d;

class CastleEnemy : public BaseEnemy
{
	protected:

	private:

	public:
		CastleEnemy(Hero* pHero, EntityManager* pBullets);
		CastleEnemy(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, Hero* pHero, EntityManager* pBullets);

		virtual CastleEnemy* deepCopy();	
};

#endif