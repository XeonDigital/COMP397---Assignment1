#pragma once
#ifndef __SLOTMACHINE__
#define __SLOTMACHINE__
#include "DisplayObject.h"

class SlotMachine : public DisplayObject
{
public:
	SlotMachine();
	~SlotMachine();
	
	void draw() override;
	void update() override;
	void clean() override;

private:
	
};

#endif