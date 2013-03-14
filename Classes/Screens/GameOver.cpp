#ifndef CONST_GAMEOVER
#define CONST_GAMEOVER

#include "GameOver.h"

// ===========================================================
// Help classes
// ===========================================================

class PlayAgainButton : public Entity
{
	public:
		PlayAgainButton() :
			Entity("game-over/play.png")
			{
				this->setRegisterAsTouchable(true);
			}

		void onTouch(CCTouch* touch, CCEvent* event)
		{
			AppDelegate::screens->set(1.0f, 0);
		}
};

// ===========================================================
// Init
// ===========================================================

// ===========================================================
// Constructors
// ===========================================================

GameOver::GameOver()
{
	this->mBackground = new Entity("game-over/background.png");
	this->mPlayAgainButton = new PlayAgainButton();

	this->mBackground->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
	this->mPlayAgainButton->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y - Utils::coord(200));

	this->addChild(this->mBackground);
	this->addChild(this->mPlayAgainButton);
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

// ===========================================================
// Virtual methods
// ===========================================================

#endif