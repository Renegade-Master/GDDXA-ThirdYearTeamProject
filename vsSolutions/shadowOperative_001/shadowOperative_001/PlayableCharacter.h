/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[]
*					Rory Ryan	[]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef PLAYABLECHARACTER_H
#define PLAYABLECHARACTER_H

#include <SFML/Graphics.hpp>

class PlayableCharacter {
protected:
	// Of course we will need a sprite
	sf::Sprite m_Sprite;

	// How long does a jump last
	float m_JumpDuration;

	// Is character currently jumping or falling
	bool m_IsJumping;
	bool m_IsFalling;

	// Which directions is the character currently moving in
	bool m_LeftPressed;
	bool m_RightPressed;

	// How long has this jump lasted so far
	float m_TimeThisJump;

	// Has the player just initialted a jump
	bool m_JustJumped = false;

	// Private variables and functions come next
private:
	// What is the gravity
	float m_Gravity;

	// How fast is the character
	float m_Speed = 400;

	// Where is the player
	sf::Vector2f m_Position;

	// Where are the characters various body parts?
	sf::FloatRect m_Feet;
	sf::FloatRect m_Head;
	sf::FloatRect m_Right;
	sf::FloatRect m_Left;

	// And a texture
	sf::Texture m_Texture;

	// All our public functions will come next
public:
	void spawn(sf::Vector2f startPosition, float gravity);

	// This is a pure virtual function
	bool virtual handleInput() = 0;
	// This class is now abstract and cannot be instanciated

	// Where is the player
	sf::FloatRect getPosition();

	// A rectangle representing the position of different parts of the sprite
	sf::FloatRect getFeet();
	sf::FloatRect getHead();
	sf::FloatRect getRight();
	sf::FloatRect getLeft();

	// Send a copy of the sprite to main
	sf::Sprite getSprite();

	// Make the character stand firm
	void stopFalling(float position);
	void stopRight(float position);
	void stopLeft(float position);
	void stopJump();

	// Where is the center of the character
	sf::Vector2f getCenter();

	// We will call this function once every frame
	void update(float elapsedTime);
};
#endif // !PLAYABLECHARACTER_H
