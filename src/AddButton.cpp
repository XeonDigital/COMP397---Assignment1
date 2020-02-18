#include "AddButton.h"
#include "Game.h"

AddButton::AddButton()
// call super constructor
	:Button(
		"../Assets/textures/AddButton.png",
		"addButton",
		ADD_BET, glm::vec2(400.0f, 300.0f), true),
	m_isClicked(false)
{

}

AddButton::~AddButton()
{
}

bool AddButton::ButtonClick()
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


