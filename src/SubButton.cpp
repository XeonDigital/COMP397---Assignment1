#include "SubButton.h"
#include "Game.h"

SubButton::SubButton()
// call super constructor
	:Button(
		"../Assets/textures/SubButton.png",
		"subButton",
		SUB_BET, glm::vec2(400.0f, 300.0f), true),
	m_isClicked(false)
{

}

SubButton::~SubButton()
{
}

bool SubButton::ButtonClick()
{
	if (m_mouseOver() && m_mouseButtonClicked)
	{
		if (!m_isClicked)
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


