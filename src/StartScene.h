#pragma once
#ifndef __START_SCENE__
#define __START_SCENE__

#include "Scene.h"
#include "Label.h"
#include "RollButton.h"
#include "SlotMachine.h"
#include "Slots.h"
#include "ResetButton.h"
#include "AddButton.h"
#include "SubButton.h"

class StartScene : public Scene
{
public:
	// constructor
	StartScene();
	// destructor
	~StartScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	// getters
	glm::vec2 getMousePosition();

private:
	//methods
	void Spin();
	void rollDice();
	bool checkRange(int value, int lowerBounds, int upperBounds);
	int determineSymbols(int value);
	void displaySlots();
	void calculateWinnings();
	
	// Game Objects
	RollButton* m_pRollButton;
	ResetButton* m_pResetButton;
	AddButton* m_pAddButton;
	SubButton* m_pSubButton;
	Label* m_pNameLabel;
	Label* m_pWinLabel;
	Label* m_BetAmountLabel;
	SlotMachine* m_pSlotMachine;
	Label* m_pCurrencyLabel;
	Slots* m_pSlotSymbol0;
	Slots* m_pSlotSymbol1;
	Slots* m_pSlotSymbol2;


	
	// private data member
	glm::vec2 m_mousePosition;
	float m_currency;
	float m_betAmount;
	//counting how many is in the roll
	int m_grapes = 0;
	int m_bananas = 0;
	int m_oranges = 0;
	int m_cherries = 0;
	int m_bars = 0;
	int m_apples = 0;
	int m_sevens = 0;
	int m_blanks = 0;
	
	//replace bells with apples
	const std::string slotSymbols[8] = {"grapes","banana","orange","cherry","bar","apple","seven","blank" };// this is the picture name
	int slots[3] = {0,0,0}; // the number values for the game
	std::string betLine[3] = {" "," "," "};
};

#endif /* defined (__START_SCENE__) */