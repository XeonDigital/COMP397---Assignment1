#pragma once
#ifndef __ADD_BUTTON__
#define __ADD_BUTTON__

#include "Button.h"

class AddButton : public Button
{
public:
	AddButton();
	~AddButton();
	bool ButtonClick() override;

private:
	bool m_isClicked;
};


#endif
