/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2019/01/29	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef GUNBATTERY_H
#define GUNBATTERY_H

#include "Item.h"

class gunBattery : public Item {
public:
	gunBattery(sf::Vector2i startPosition);
	//return the capacity to the gun
	virtual float getCapacity();
	virtual void update(float elapsedTime, int** m_ArrayLevel);

private:
	//How much energy this will return to the Gun
	enum class Capacity { SMALL, MEDIUM, LARGE };
	Capacity m_Capacity = Capacity::SMALL;
};

#endif	//	!GUNBATTERY_H