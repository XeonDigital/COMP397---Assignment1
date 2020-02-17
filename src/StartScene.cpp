#include "StartScene.h"
#include "Game.h"
#include <ctime>
#include "GLM/gtx/string_cast.hpp"
#include <algorithm>
#include <iomanip>

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
{
}

void StartScene::draw()
{
	m_pSlotMachine->draw();
	m_pNameLabel->draw();
	m_pRollButton->draw();
	/*m_pOcean->draw();
	m_pStartLabel->draw();
	m_pStartButton->draw();*/
	
}

void StartScene::update()
{
	m_pRollButton->setMousePosition(m_mousePosition);
	if(m_pRollButton->ButtonClick())//if the button was clicked
	{
		m_currency = m_currency - 100;
		//do something here
		rollDice();
		float time = TheGame::Instance()->getDeltaTime() / 1000;
		while(time < 100)
		{
			time = time + TheGame::Instance()->getDeltaTime() / 1000;
		}
		std::cout << "-----------" << std::endl;
		std::cout << "pressed button" << std::endl;
	}
	
	/*m_pOcean->update();
	m_pStartButton->setMousePosition(m_mousePosition);
	m_pStartButton->ButtonClick();*/
}

void StartScene::clean()
{
	delete m_pNameLabel;
	removeAllChildren();
}

void StartScene::handleEvents()
{
	int wheel = 0;
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;
		case SDL_MOUSEMOTION:
			m_mousePosition.x = event.motion.x;
			m_mousePosition.y = event.motion.y;
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				m_pRollButton->setMouseButtonClicked(true);
				break;
			}

			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				m_pRollButton->setMouseButtonClicked(false);
				break;
			}
			break;
		case SDL_MOUSEWHEEL:
			wheel = event.wheel.y;
			break;





			
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				TheGame::Instance()->quit();
				break;
			case SDLK_1:
				TheGame::Instance()->changeSceneState(SceneState::LEVEL1_SCENE);
				break;
			case SDLK_2:
				TheGame::Instance()->changeSceneState(SceneState::END_SCENE);
				break;
			}
			break;

		default:
			break;
		}
	}
}

// this function is used for initialization
void StartScene::start()
{
	SDL_Color yellow = { 255, 255, 0, 255 };
	m_pNameLabel = new Label("Slot Machine", "Dock51", 70, yellow,glm::vec2(Config::SCREEN_WIDTH * 0.5f, 40.0f));
	addChild(m_pNameLabel);
	m_currency = 1000.0f;
	m_pRollButton = new RollButton();
	m_pRollButton->setPosition(glm::vec2(m_pRollButton->getWidth() / 2, 455));
	addChild(m_pRollButton);
	m_pSlotMachine = new SlotMachine();
	m_pSlotMachine->setPosition(glm::vec2(0,0));
	
	/*m_pOcean = new Ocean();
	addChild(m_pOcean);

	
	SDL_Color yellow = { 255, 255, 0, 255 };
	m_pStartLabel = new Label("Mail Pilot", "Dock51", 80, yellow, 
		glm::vec2(Config::SCREEN_WIDTH * 0.5f, 100.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pStartButton = new StartButton();
	m_pStartButton->setPosition(glm::vec2(Config::SCREEN_WIDTH * 0.5f, Config::SCREEN_HEIGHT * 0.5f));
	addChild(m_pStartButton);*/
}

glm::vec2 StartScene::getMousePosition()
{
	return m_mousePosition;
}

void StartScene::rollDice()
{
	//gets the numbers for the desired symbol
	for (int i = 0; i <= 2; i++)
	{
		int random = rand() % 65 + 1;
		slots[i] = determineSymbols(random);
		std::cout << "Random number: " << random << std::endl;
	}
	int count = 0;
	for (int slot : slots)
	{
		std::cout << "Random number slot" << count << ": " << slot << std::endl;
		count++;
	}
	
}

bool StartScene::checkRange(int value, int lowerBounds, int upperBounds)// to check the ranges
{
	if (value >= lowerBounds && value <= upperBounds)
	{
		return true;
	}
	return false;
}

int StartScene::determineSymbols(int value)// to determine which one 
{
	if(checkRange(value, 1, 27))// 41.5% probability
	{
		return 7;
	}
	if(checkRange(value, 28, 37))// 15.4% probability
	{
		return 0;
	}
	if(checkRange(value, 38, 46))// 13.8% probability
	{
		return 1;
	}
	if(checkRange(value, 47, 54))// 12.3 % probability
	{
		return 2;
	}
	if(checkRange(value, 55, 59))// 7.7 % probability
	{
		return 3;
	}
	if(checkRange(value, 60, 62))//  4.6% probability
	{
		return 4;
	}
	if (checkRange(value, 63, 64))//  3.1% probability
	{
		return 5;
	}
	if(checkRange(value, 65, 65))//  1.5% probability
	{
		return 6;
	}
}


//case checkRange(outCome[spin], 1, 27):  // 41.5% probability
//	betLine[spin] = "blank";
//	blanks++;
//	break;
//case checkRange(outCome[spin], 28, 37): // 15.4% probability
//	betLine[spin] = "Grapes";
//	grapes++;
//	break;
//case checkRange(outCome[spin], 38, 46): // 13.8% probability
//	betLine[spin] = "Banana";
//	bananas++;
//	break;
//case checkRange(outCome[spin], 47, 54): // 12.3% probability
//	betLine[spin] = "Orange";
//	oranges++;
//	break;
//case checkRange(outCome[spin], 55, 59): //  7.7% probability
//	betLine[spin] = "Cherry";
//	cherries++;
//	break;
//case checkRange(outCome[spin], 60, 62): //  4.6% probability
//	betLine[spin] = "Bar";
//	bars++;
//	break;
//case checkRange(outCome[spin], 63, 64): //  3.1% probability
//	betLine[spin] = "Bell";
//	bells++;
//	break;
//case checkRange(outCome[spin], 65, 65): //  1.5% probability
//	betLine[spin] = "Seven";
//	sevens++;
//	break;