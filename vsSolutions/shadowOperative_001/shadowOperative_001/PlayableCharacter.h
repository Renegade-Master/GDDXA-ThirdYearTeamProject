/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef PLAYABLECHARACTER_H
#define PLAYABLECHARACTER_H

#include <SFML/Graphics.hpp>

class PlayableCharacter {
public:

	// Game States Animations
	//enum class State { IDLE, RUNNINGRIGHT, RUNNINGLEFT, JUMPING, FALLING};
	enum class Direction { NOT, RIGHT, LEFT };
	Direction m_Direction = Direction::NOT;

	//enum class State_Fall_or_Jum { idle, jump, fall,};
	enum class State { IDLE, WALKING, JUMPING, FALLING, CROUCHING };
	State m_State = State::IDLE;

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

	void spawn(sf::Vector2i startPosition, float gravity);

protected:
	// A Sprite Animations
	sf::Sprite m_Sprite;
	sf::Sprite m_SpriteRunningRight;
	sf::Sprite m_SpriteRunningLeft;
	sf::Sprite m_SpriteFalling;


	int playerjump=0;
	int	jumpallowed =2;

	// How long does a jump last
	float m_JumpDuration;

	// Is character currently jumping or falling
	//bool m_IsJumping;
	//bool m_IsFalling;

	// Which directions is the character currently moving in
	bool m_LeftPressed;
	bool m_RightPressed;

	// How long has this jump lasted so far
	float m_TimeThisJump;

	// Where is the player
	sf::Vector2f m_Position;

	// What is the gravity
	float m_Gravity;

	// Has the player just initialted a jump
	bool m_JustJumped = false;

	// We will call this function once every frame
	virtual void update(float elapsedTime,int** m_ArrayLevel) = 0;

	// This is a pure virtual function
	virtual bool handleInput() = 0;

	// How fast is the character
	float m_Speed = 500;

	// Where are the characters various body parts?
	sf::FloatRect m_Feet;
	sf::FloatRect m_Head;
	sf::FloatRect m_Right;
	sf::FloatRect m_Left;

	// A texture
	sf::Texture m_Texture;
};
#endif // !PLAYABLECHARACTER_H
