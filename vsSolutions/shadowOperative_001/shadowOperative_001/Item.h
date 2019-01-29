/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef ITEM_H
#define ITEM_H

#include "Constants.h"
#include "TextureHolder.h"

class Item {
public:
	// Where is the item
	sf::FloatRect getPosition();

	// Send a copy of the sprite to main thread
	sf::Sprite getSprite();

	// Where is the center of the item
	sf::Vector2f getCenter();

	void spawn();

	//Default Constructor
	Item();
	~Item();

	// We will call this function once every frame
	virtual void update(float elapsedTime, int** m_ArrayLevel) = 0;

	//return capacity
	virtual float getCapacity() = 0;

protected:
	// A Sprite
	sf::Sprite m_ItemSprite;

	// Where is the item
	sf::Vector2f m_Position;

	// A texture
	sf::Texture m_Texture;
};

#endif // !ITEM_H
