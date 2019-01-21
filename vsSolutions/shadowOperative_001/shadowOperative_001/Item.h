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

#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
class Item 
{
public:
	// Where is the item
	sf::FloatRect getPosition();

	// A rectangle representing the position of different parts of the sprite
	sf::FloatRect getBottem();
	sf::FloatRect getTop();
	sf::FloatRect getRight();
	sf::FloatRect getLeft();

	// Send a copy of the sprite to main
	sf::Sprite getSprite();

	/*// Make the item stand firm
	void stopFalling(float position);
	void stopRight(float position);
	void stopLeft(float position);*/

	// Where is the center of the character
	sf::Vector2f getCenter();

	void spawn(sf::Vector2i startPosition, float gravity);

protected:
	// A Sprite
	sf::Sprite m_ItemSprite;

	// Where is the item
	sf::Vector2f m_Position;

	// We will call this function once every frame
	virtual void update(float elapsedTime, int** m_ArrayLevel) = 0;

	// Where are the items sides?
	sf::FloatRect m_Bottem;
	sf::FloatRect m_Top;
	sf::FloatRect m_Right;
	sf::FloatRect m_Left;

	// A texture
	sf::Texture m_Texture;
};
#endif // !ITEM_H
