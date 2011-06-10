#include "MaarGame.h"
#include "GameCell.h"
#include "GameField.h"
#include "SDL_keysym.h"

namespace MAAR
{
	MaarGame::MaarGame()
	{
		gameState=RUNNING;
		selfCollision=true;
		gridDimensions=vec2i(180,80);

		windowDimensions=gridDimensions*10;
		if(windowDimensions.x>=1250||windowDimensions.y>=1000)
		{
			windowDimensions.x=1250;
			windowDimensions.y=(static_cast<float>(windowDimensions.x)/gridDimensions.x)*gridDimensions.y;
		}

		SetSize(windowDimensions.x,windowDimensions.y);
		updateInterval=50;
		game=new GameField(gridDimensions.x,gridDimensions.y);
		mar=new Mar(40, gridDimensions.x/2,gridDimensions.y/2, game);
		GameCell::SetContentColor(GameCell::Empty, 50,60,70);
		GameCell::SetContentColor(GameCell::Kerm, 0xff,0,0);
		GameCell::SetContentColor(GameCell::Fruit, 0x20,0xff,0);
		GameCell::SetContentColor(GameCell::Wall, 0x50,0x20,0x20);
	}

	void MaarGame::SetSize(int width, int height)
	{
		MaarGame::windowDimensions=vec2i(width, height);
		GameCell::dimensions=vec2f(static_cast<float>(MaarGame::windowDimensions.x)/gridDimensions.x,
			static_cast<float>(MaarGame::windowDimensions.y)/gridDimensions.y);

	}

	void MaarGame::Update(float dts)
	{
		if(gameState==FINISHED)
			return;

		switch(_lastPressedKey)
		{
		case SDLK_END:
			if(gameState==RUNNING)
				SetGameState(PAUSED);
			break;
		case SDLK_HOME:
			if(gameState==PAUSED)
				SetGameState(RUNNING);
		}

		if(gameState==PAUSED)
			return;

		Direction dir=DIR_Right;
		switch(_lastPressedKey)
		{
		case SDLK_LEFT:
			dir=DIR_Left;
			break;
		case SDLK_RIGHT:
			dir=DIR_Right;
			break;
		case SDLK_UP:
			dir=DIR_Up;
			break;
		case SDLK_DOWN:
			dir=DIR_Down;
			break;
		}
		mar->Cycle(dir);
	}
	void MaarGame::Draw()
	{
		game->Draw();

		if(gameState==PAUSED)
		{
			unsigned char pauseStr[16]="Paused";
//TODO: Find a font/text rendering solution to display Paused in the center of screen 
		}
		else if(gameState == FINISHED)
		{
			unsigned char gostr[16]="Game Over";
//TODO: Find a font/text rendering solution to display Game Over in the center of screen 
		}
	}
	MaarGame::~MaarGame()
	{
		delete game;
		delete mar;
	}
	Game *Game::_instance=new MaarGame();
}