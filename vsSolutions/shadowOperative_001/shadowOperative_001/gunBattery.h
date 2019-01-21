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
	gunBattery();
	//return the capacity to the gun
	float getCapacity();
};
#endif 