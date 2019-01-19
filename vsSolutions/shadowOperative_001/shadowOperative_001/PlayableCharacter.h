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

#include <fstream>
#include <iostream>

#include <SFML/Graphics.hpp>

class PlayableCharacter {
public:
	// PlayableCharacter Direction Action
	enum class Direction { IDLE, RIGHT, LEFT };
	Direction m_Direction = Direction::IDLE;
	
	// PlayableCharacter Action Action
	enum class Action { IDLE, WALKING, JUMPING, FALLING, CROUCHING };
	Action m_Action = Action::IDLE;

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
	int m_animationFrame;
	int m_animationType;
	int m_maxAnimationFrames;
	float m_timeSinceLastFrame;

	sf::Image m_animationSheet;
	sf::Sprite m_Sprite;
	sf::Sprite m_SpriteRunningRight;
	sf::Sprite m_SpriteRunningLeft;
	sf::Sprite m_SpriteFalling;

	// Jump Controls
	float m_jumpDuration;
	int m_jumpCounter;
	
	float maxJumpDuration = 0.5f;
	int	maxJumps = 1;

	// Where is the player
	sf::Vector2f m_Position;

	// What is the gravity
	float m_Gravity;

	// Has the player just initialted a jump
	//bool m_JustJumped = false;

	// We will call this function once every frame
	virtual void update(float elapsedTime,int** m_ArrayLevel) = 0;

	// This is a pure virtual function
	virtual void handleInput() = 0;

	// How fast is the character
	float m_Speed = 100;

	// Where are the characters various body parts?
	sf::FloatRect m_Feet;
	sf::FloatRect m_Head;
	sf::FloatRect m_Right;
	sf::FloatRect m_Left;

	// A texture
	sf::Texture m_Texture;
	int animationCounter = 0;
};
#endif // !PLAYABLECHARACTER_H
