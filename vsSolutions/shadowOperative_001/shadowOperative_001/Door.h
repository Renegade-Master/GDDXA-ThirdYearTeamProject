#pragma once
/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef DOOR_H
#define DOOR_H

#include "Item.h"

class Door : public Item
{
private:
	enum class State { OPEN, CLOSE, STATIC };
	State m_DoorState = State::CLOSE;
	sf::Sprite m_OpenDoorSprite;
	sf::Sprite m_ClosedDoorSprite;
protected:
	int door;
	
public:
	Door(char state,sf::Vector2i position);
	// We will call this function once every frame
	virtual void update(float elapsedTime, int** m_ArrayLevel);

	//return capacity
	virtual float getCapacity();
	
	sf::Sprite getDoorSprite();

	bool getDoorState();
	void doorState();
};
#endif // !DOOR_H
