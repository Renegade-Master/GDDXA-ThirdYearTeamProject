#pragma once
/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef DOOR_H
#define DOOR_H

#include "Item.h"

class Door : public Item
{
protected:
	bool door;
	void DoorState();
};
#endif // !DOOR_H
