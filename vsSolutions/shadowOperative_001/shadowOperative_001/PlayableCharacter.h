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
#include "laser.h"

class PlayableCharacter {
public:
	// PlayableCharacter Direction State
	enum class Direction { LEFT, RIGHT, IDLE };
	Direction m_Direction = Direction::IDLE;
	
	// PlayableCharacter Action State
	enum class Action { FALLING, JUMPING, RUNNING, CROUCHING, ATTACKING, IDLE };
	Action m_Action = Action::IDLE;

	// Variables to Store the last action
	Direction m_LastDirection = Direction::IDLE;
	Action m_LastAction = Action::IDLE;

	// What is the gravity
	float m_Gravity;

	// Where is the player
	sf::FloatRect getPosition();
	sf::Vector2f m_Position;
	// Where was the Player
	sf::Vector2f m_LastPosition;

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
	// Sprite Animation Variables
	int frameWidth;
	int frameHeight;
	int frameXOffset;
	int frameYOffset;
	int m_maxAnimationFrames;
	float m_timeSinceLastFrame;
	float frameSwitchTime = 0.1f;

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

	//laserTargeting
	laser targetingLaser;
};
#endif // !PLAYABLECHARACTER_H
