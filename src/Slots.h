#pragma once
#ifndef __SLOTS__
#define __SLOTS__
#include "DisplayObject.h"

class Slots : public DisplayObject
{
public:
	Slots(float x, std::string image);
	~Slots();
	void draw() override;
	void update() override;
	void clean() override;
	void changeImage(std::string image);
private:
	const std::string defaultImage = "blank";
	std::string id;
};

#endif