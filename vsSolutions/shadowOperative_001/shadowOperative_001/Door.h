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

class Door : public Item {
public:
    Door(char state, sf::Vector2i position);
	
	// We will call this function once every frame
	virtual void update(float elapsedTime, int** m_ArrayLevel) override;

	//return capacity
	virtual float getCapacity();

	sf::Sprite getDoorSprite();

	bool getDoorState();
	void doorState();
	bool getValidState();

	sf::FloatRect getPosition();

private:
    //enum class for the available State's of the Door
	enum class State { OPEN, CLOSE, STATIC };
	
	//Enum variable for current state of the door
	State m_DoorState = State::CLOSE;
	
	//Sprite for the door during the OPEN State
	sf::Sprite m_OpenDoorSprite;
	
	//Sprite for the door during the CLOSED/STATIC STATE
	sf::Sprite m_ClosedDoorSprite;
};
#endif // !DOOR_H
