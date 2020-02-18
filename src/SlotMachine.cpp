#include "SlotMachine.h"
#include "Game.h"

SlotMachine::SlotMachine()
{
	TheTextureManager::Instance()->load("../Assets/textures/slotmachine.png",
		"slotmachine", TheGame::Instance()->getRenderer());

	// measure size by querying the texture
	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("slotmachine");
	setWidth(size.x);
	setHeight(size.y);

	setPosition(glm::vec2(0.0f, -960.0f));
	setIsColliding(false);
	setType(SLOT_MACHINE);
	setVelocity(glm::vec2(0.0f, 5.0f));
}

SlotMachine::~SlotMachine()
{
}

void SlotMachine::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("slotmachine", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, false);
}

void SlotMachine::update()
{
}

void SlotMachine::clean()
{
}
