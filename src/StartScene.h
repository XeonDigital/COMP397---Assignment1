#pragma once
#ifndef __START_SCENE__
#define __START_SCENE__

#include "Scene.h"
#include "Label.h"
#include "RollButton.h"
#include "SlotMachine.h"

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
	
	// Game Objects
	RollButton* m_pRollButton;
	Label* m_pNameLabel;
	SlotMachine* m_pSlotMachine;

	// private data member
	glm::vec2 m_mousePosition;
	float m_currency;
	//replace bells with apples
	const std::string slotSymbols[8] = {"grapes","bananas","oranges","cherries","bars","apple","sevens","blanks" };// this is the picture name
	int slots[3] = {0,0,0}; // the number values for the game
	std::string betLine[3] = {" "," "," "};
};

#endif /* defined (__START_SCENE__) */