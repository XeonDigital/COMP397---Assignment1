#include "RollButton.h"
#include "Game.h"

RollButton::RollButton()
	// call super constructor
	:Button(
		"../Assets/textures/StartButton.png",
		"startButton",
		START_BUTTON, glm::vec2(400.0f, 300.0f),true),
		m_isClicked(false)
{
	
}

RollButton::~RollButton()
{
}

bool RollButton::ButtonClick()
{
	if (m_mouseOver() && m_mouseButtonClicked)
	{
		if(!m_isClicked)
		{
			//do something here
			m_isClicked = true;
		}
		return true;
	}
	else
	{
		m_isClicked = false;
	}

	return false;
}


