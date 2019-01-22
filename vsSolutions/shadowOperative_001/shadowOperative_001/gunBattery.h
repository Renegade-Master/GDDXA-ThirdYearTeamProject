#pragma once
#include "Item.h"
#ifndef GUNBATTERY_H
#define GUNBATTERY_H

class gunBattery : public Item
{
private:
	//How much energy this will return to the Gun
	enum class Capacity { SMALL, MEDIUM, LARGE };
	Capacity m_Capacity = Capacity::SMALL;
public:
	gunBattery(sf::Vector2i startPosition);
	//return the capacity to the gun
	float getCapacity();
	virtual void update(float elapsedTime, int** m_ArrayLevel);
};
#endif 