#ifndef CONST_CASTLEENEMY
#define CONST_CASTLEENEMY

#include "CastleEnemy.h"

CastleEnemy::CastleEnemy(Hero* pHero, EntityManager* pBullets) :
 BaseEnemy(pHero, pBullets)
{
}

CastleEnemy::CastleEnemy(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, Hero* pHero, EntityManager* pBullets) :
	BaseEnemy(pszFileName, pHorizontalFramesCount, pVerticalFramesCount, pHero, pBullets)
	{
		
	}

CastleEnemy* CastleEnemy::deepCopy()
{
	return new CastleEnemy("test/garlic.png", 1, 1, this->mHero, this->mBullets);
}

#endif