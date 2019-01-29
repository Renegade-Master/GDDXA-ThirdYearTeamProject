#pragma once
#include "Item.h"
#ifndef GUNBATTERY_H
#define GUNBATTERY_H

class gunBattery : public Item
{
private:
	//Enum class for what kind of gunBattery this object is
	enum class Capacity { SMALL, MEDIUM, LARGE };
	//Holds the type of gunBattery object for reference
	Capacity m_Capacity = Capacity::SMALL;
public:
	gunBattery(sf::Vector2i startPosition);
	//return the capacity to the gun
	virtual float getCapacity();
	virtual void update(float elapsedTime, int** m_ArrayLevel);
};
#endif 