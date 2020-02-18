#include "Slots.h"
#include "Game.h"

Slots::Slots(float x, std::string image)
{
	//loads all the textures
	TheTextureManager::Instance()->load("../Assets/textures/SlotSymbols/blank.png",
		"blank", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/SlotSymbols/apple.png",
		"apple", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/SlotSymbols/banana.png",
		"banana", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/SlotSymbols/bar.png",
		"bar", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/SlotSymbols/cherry.png" ,
		"cherry", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/SlotSymbols/grapes.png" ,
		"grapes", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/SlotSymbols/lemon.png" ,
		"lemon", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/SlotSymbols/orange.png" ,
		"orange", TheGame::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/textures/SlotSymbols/seven.png",
		"seven", TheGame::Instance()->getRenderer());
	//sets the texture
	id = image;
	// measure size by querying the texture
	glm::vec2 size = TheTextureManager::Instance()->getTextureSize(id);
	setWidth(size.x);
	setHeight(size.y);

	setPosition(glm::vec2(x,165));
	setIsColliding(false);
	setType(SLOT);
	setVelocity(glm::vec2(0.0f, 5.0f));
}

Slots::~Slots()
{
	
}

void Slots::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw(id , xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, false);
}

void Slots::update()
{
}

void Slots::clean()
{
}

void Slots::changeImage(std::string value)
{
	id = value;
	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("blank");
	setWidth(size.x);
	setHeight(size.y);
}
