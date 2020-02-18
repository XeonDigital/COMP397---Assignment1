#include "StartScene.h"
#include "Game.h"
#include <ctime>
#include "GLM/gtx/string_cast.hpp"
#include <algorithm>
#include <iomanip>
#include "time.h"

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
	m_pCurrencyLabel->draw();
	m_pSlotSymbol0->draw();
	m_pSlotSymbol1->draw();
	m_pSlotSymbol2->draw();
	m_pResetButton->draw();
	m_pWinLabel->draw();
	m_BetAmountLabel->draw();
	m_pSubButton->draw();
	m_pAddButton->draw();
}

void StartScene::update()
{
	m_pRollButton->setMousePosition(m_mousePosition);
	m_pResetButton->setMousePosition(m_mousePosition);
	m_pAddButton->setMousePosition(m_mousePosition);
	m_pSubButton->setMousePosition(m_mousePosition);
	if(m_pRollButton->ButtonClick())//if the button was clicked
	{
		//used to delay the button clicks
		Uint32 frameStart = SDL_GetTicks();
		//exectues the roll function
		rollDice();
		float time = TheGame::Instance()->getDeltaTime() / 1000;
		Uint32 frameTime = SDL_GetTicks() - frameStart;
		int delayTime = 500;
		//delays the button clicks
		if (frameTime < delayTime)
		{
			const auto time = int(delayTime - frameTime);
			SDL_Delay(time);
			TheGame::Instance()->setDeltaTime(time * 0.001f);
		}
		std::cout << "-----------" << std::endl;
		std::cout << "pressed button" << std::endl;
	}
	if(m_pResetButton->ButtonClick())
	{
		m_currency = 1000;
		m_grapes = 0;
		m_bananas = 0;
		m_oranges = 0;
		m_cherries = 0;
		m_bars = 0;
		m_apples = 0;
		m_sevens = 0;
		m_blanks = 0;
		slots[0] = 7;
		slots[1] = 7;
		slots[2] = 7;
		m_betAmount = 10;
		m_pCurrencyLabel->setText("Bank: $" + std::to_string(m_currency));
		m_BetAmountLabel->setText("Bet Amount: $" + std::to_string(m_betAmount));
		m_pWinLabel->setText("");
		m_pSlotSymbol0->changeImage("blank");
		m_pSlotSymbol1->changeImage("blank");
		m_pSlotSymbol2->changeImage("blank");
		//used to delay the button clicks
		Uint32 frameStart = SDL_GetTicks();
		//exectues the roll function
		float time = TheGame::Instance()->getDeltaTime() / 1000;
		Uint32 frameTime = SDL_GetTicks() - frameStart;
		int delayTime = 500;
		//delays the button clicks
		if (frameTime < delayTime)
		{
			const auto time = int(delayTime - frameTime);
			SDL_Delay(time);
			TheGame::Instance()->setDeltaTime(time * 0.001f);
		}
		std::cout << "-----------" << std::endl;
		std::cout << "pressed reset button" << std::endl;
	}
	if (m_pAddButton->ButtonClick())
	{
		if(m_betAmount <= m_currency)
		{
			m_betAmount += 10;
		}
		m_BetAmountLabel->setText("Bet Amount: $" + std::to_string(m_betAmount));
		//used to delay the button clicks
		Uint32 frameStart = SDL_GetTicks();
		//exectues the roll function
		float time = TheGame::Instance()->getDeltaTime() / 1000;
		Uint32 frameTime = SDL_GetTicks() - frameStart;
		int delayTime = 500;
		//delays the button clicks
		if (frameTime < delayTime)
		{
			const auto time = int(delayTime - frameTime);
			SDL_Delay(time);
			TheGame::Instance()->setDeltaTime(time * 0.001f);
		}
		std::cout << "-----------" << std::endl;
		std::cout << "pressed add button" << std::endl;
	}
	if (m_pSubButton->ButtonClick())
	{
		if (m_betAmount > 10)
		{
			m_betAmount -= 10;
		}
		//used to delay the button clicks
		Uint32 frameStart = SDL_GetTicks();
		//exectues the roll function
		float time = TheGame::Instance()->getDeltaTime() / 1000;
		Uint32 frameTime = SDL_GetTicks() - frameStart;
		int delayTime = 500;
		//delays the button clicks
		if (frameTime < delayTime)
		{
			const auto time = int(delayTime - frameTime);
			SDL_Delay(time);
			TheGame::Instance()->setDeltaTime(time * 0.001f);
		}
		m_BetAmountLabel->setText("Bet Amount: $" + std::to_string(m_betAmount));
		std::cout << "-----------" << std::endl;
		std::cout << "pressed sub button" << std::endl;
	}
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
				m_pAddButton->setMouseButtonClicked(true);
				m_pResetButton->setMouseButtonClicked(true);
				m_pSubButton->setMouseButtonClicked(true);
				break;
			}

			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				m_pRollButton->setMouseButtonClicked(false);
				m_pAddButton->setMouseButtonClicked(false);
				m_pResetButton->setMouseButtonClicked(false);
				m_pSubButton->setMouseButtonClicked(false);
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
	SDL_Color black = { 0,0 , 0, 255 };
	m_pNameLabel = new Label("Slot Machine", "Dock51", 70, yellow,glm::vec2(Config::SCREEN_WIDTH * 0.5f, 40.0f));
	addChild(m_pNameLabel);
	m_currency = 1000.0f;
	m_betAmount = 10;
	m_pRollButton = new RollButton();
	m_pRollButton->setPosition(glm::vec2((m_pRollButton->getWidth() / 2), 455));
	addChild(m_pRollButton);
	m_pSlotMachine = new SlotMachine();
	m_pSlotMachine->setPosition(glm::vec2(0,0));
	addChild(m_pSlotMachine);
	m_pCurrencyLabel = new Label( "Bank: $" + std::to_string(m_currency), "Consolas", 30, black, glm::vec2(Config::SCREEN_WIDTH * 0.5f, Config::SCREEN_HEIGHT *0.85));
	addChild(m_pCurrencyLabel);
	m_pSlotSymbol0 = new Slots(35, "blank");
	m_pSlotSymbol1 = new Slots(193, "blank");
	m_pSlotSymbol2 = new Slots(350,"blank");
	m_pResetButton = new ResetButton();
	m_pResetButton->setPosition(glm::vec2((m_pRollButton->getWidth() / 2) + 500, 455));
	m_pWinLabel = new Label("", "Consolas", 30, black, glm::vec2(Config::SCREEN_WIDTH * 0.5f, Config::SCREEN_HEIGHT * 0.8));
	m_BetAmountLabel = new Label("Bet Amount: $" + std::to_string(m_betAmount), "Consolas", 30, black, glm::vec2(Config::SCREEN_WIDTH * 0.5f, Config::SCREEN_HEIGHT * 0.9));
	m_pAddButton = new AddButton();
	m_pAddButton->setPosition(glm::vec2((m_pRollButton->getWidth() / 2) + 170, 455));
	m_pSubButton = new SubButton();
	m_pSubButton->setPosition(glm::vec2((m_pRollButton->getWidth() / 2) + 330, 455));
	

}

glm::vec2 StartScene::getMousePosition()
{
	return m_mousePosition;
}
//{"grapes", "bananas", "oranges", "cherries", "bars", "apple", "sevens", "blanks" }
void StartScene::rollDice()
{
	m_grapes = 0;
	m_bananas = 0;
	m_oranges = 0;
	m_cherries = 0;
	m_bars = 0;
	m_apples = 0;
	m_sevens = 0;
	m_blanks = 0;
	slots[0] = 7;
	slots[1] = 7;
	slots[2] = 7;
	std::cout << "currency: " << m_currency << std::endl;
	if (m_currency > 0)
	{
		//gets the numbers for the desired symbol
		for (int i = 0; i <= 2; i++)
		{
			int random = rand() % 65 + 1;
			slots[i] = determineSymbols(random);
			std::cout << "Random number: " << random << std::endl;
			if(slots[i] == 0)
			{
				m_grapes += 1;
			}
			else if (slots[i] == 1)
			{
				m_bananas += 1;
			}
			else if (slots[i] == 2)
			{
				m_oranges += 1;
			}
			else if (slots[i] == 3)
			{
				m_cherries += 1;
			}
			else if (slots[i] == 4)
			{
				m_bars += 1;
			}
			else if (slots[i] == 5)
			{
				m_apples += 1;
			}
			else if (slots[i] == 6)
			{
				m_sevens += 1;
			}
			else if (slots[i] == 7)
			{
				m_blanks += 1;
			}
			
		}
		int count = 0;
		for (int slot : slots)
		{
			std::cout << "Random number slot" << count << ": " << slot << std::endl;
			count++;
		}
		displaySlots();
		calculateWinnings();
		std::cout << m_currency << std::endl;
		m_currency = m_currency - m_betAmount;
		m_pCurrencyLabel->setText("Bank $" + std::to_string(m_currency));
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

void StartScene::displaySlots()
{
	m_pSlotSymbol0->changeImage(slotSymbols[slots[0]]);
	m_pSlotSymbol1->changeImage(slotSymbols[slots[1]]);
	m_pSlotSymbol2->changeImage(slotSymbols[slots[2]]);
}
//{"grapes", "bananas", "oranges", "cherries", "bars", "apple", "sevens", "blanks" }
void StartScene::calculateWinnings()
{
	float current = m_currency;
	if (m_grapes == 3) {
		m_currency += m_betAmount * 10;
		m_pWinLabel->setText("You won $" + std::to_string(m_currency - current));
	}
	else if (m_bananas == 3) {
		m_currency += m_betAmount * 20;
		m_pWinLabel->setText("You won $" + std::to_string(m_currency - current));
	}
	else if (m_oranges == 3) {
		m_currency += m_betAmount * 30;
		m_pWinLabel->setText("You won $" + std::to_string(m_currency - current));
	}
	else if (m_cherries == 3) {
		m_currency += m_betAmount * 40;
		m_pWinLabel->setText("You won $" + std::to_string(m_currency - current));
	}
	else if (m_bars == 3) {
		m_currency += m_betAmount * 50;
		m_pWinLabel->setText("You won $" + std::to_string(m_currency - current));
	}
	else if (m_apples == 3) {
		m_currency += m_betAmount * 75;
		m_pWinLabel->setText("You won $" + std::to_string(m_currency - current));
	}
	else if (m_sevens == 3) {
		m_currency += m_betAmount * 100;
		m_pWinLabel->setText("You won $" + std::to_string(m_currency - current));
	}
	else if (m_grapes == 2) {
		m_currency += m_betAmount * 2;
		m_pWinLabel->setText("You won $" + std::to_string(m_currency - current));
	}
	else if (m_bananas == 2) {
		m_currency += m_betAmount * 2;
		m_pWinLabel->setText("You won $" + std::to_string(m_currency - current));
	}
	else if (m_oranges == 2) {
		m_currency += m_betAmount * 3;
		m_pWinLabel->setText("You won $" + std::to_string(m_currency - current));
	}
	else if (m_cherries == 2) {
		m_currency += m_betAmount * 4;
		m_pWinLabel->setText("You won $" + std::to_string(m_currency - current));
	}
	else if (m_bars == 2) {
		m_currency += m_betAmount * 5;
		m_pWinLabel->setText("You won $" + std::to_string(m_currency - current));
	}
	else if (m_apples == 2) {
		m_currency += m_betAmount * 10;
		m_pWinLabel->setText("You won $" + std::to_string(m_currency - current));
	}
	else if (m_sevens == 2) {
		m_currency += m_betAmount * 20;
		m_pWinLabel->setText("You won $" + std::to_string(m_currency - current));
	}
	else if (m_sevens == 1) {
		m_currency += m_betAmount * 5;
		m_pWinLabel->setText("You won $" + std::to_string(m_currency - current));
	}
	else {
		m_pWinLabel->setText("You didnt win");
	}
	
	std::cout << m_currency << std::endl;
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