#include "ResetButton.h"

ResetButton::ResetButton()// call super constructor
	:Button(
		"../Assets/textures/ResetButton.png",
		"ResetButton",
		RESET_BUTTON, glm::vec2(400.0f, 300.0f), true),
		m_isClicked(false)
{
}

ResetButton::~ResetButton()
{
}

bool ResetButton::ButtonClick()
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
