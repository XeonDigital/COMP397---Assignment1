#pragma once
#ifndef __SUB_BUTTON__
#define __SUB_BUTTON__

#include "Button.h"

class SubButton : public Button
{
public:
	SubButton();
	~SubButton();
	bool ButtonClick() override;

private:
	bool m_isClicked;
};


#endif
