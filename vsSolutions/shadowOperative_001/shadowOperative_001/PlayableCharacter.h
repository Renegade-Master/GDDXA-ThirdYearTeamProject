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
#include <list>

#include "Laser.h"
#include "SoundManager.h"

class PlayableCharacter {
public:
	// PlayableCharacter Direction State
	enum class Direction { LEFT, RIGHT, IDLE };
	//Holds Current Direction State for this Character
	Direction m_Direction = Direction::IDLE;
	
	// PlayableCharacter Action State
	enum class Action { FALLING, JUMPING, RUNNING, CROUCHING, ATTACKING, IDLE };
	//Holds Current Action State for this character
	Action m_Action = Action::IDLE;

	// Variables to Store the last Direction State
	Direction m_LastDirection = Direction::IDLE;
	//Variable Holds the last Action State
	Action m_LastAction = Action::IDLE;

	// What is the gravity
	float m_Gravity;

	// Returns the current Position
	sf::FloatRect getPosition();
	//Holds the current location coordinates X*Y
	sf::Vector2f m_Position;
	// Where was the Player
	sf::Vector2f m_LastPosition;

	// A rectangle representing the position of different parts of the sprite
	//Rectangle represents player feet HitBox
	sf::FloatRect getFeet();
	//Rectangle represents player Head HitBox
	sf::FloatRect getHead();
	//Rectangle represents player Right side HitBox
	sf::FloatRect getRight();
	//Rectangle represents player Left side HitBox
	sf::FloatRect getLeft();

	// Send a copy of the sprite to main
	sf::Sprite getSprite();

	// Make the character stand firm
	//Stop the character Falling
	void stopFalling(float position);
	//Stop the character moving Right
	void stopRight(float position);
	//Stop the character moving Left
	void stopLeft(float position);
	//Stop the character Jumping
	void stopJump();

	// Jump Controls
	float m_jumpDuration = 0.0f;
	//How many times have we jumped so far
	int m_jumpCounter = 0;
	//How long can the characters jump last
	float maxJumpDuration = 0.5f;
	//Maximum nuber of jumps allowed
	int	maxJumps = 1;

	// Where is the center of the character
	sf::Vector2f getCenter();
	//Spawn function of the playableCharacter class
	void spawn(sf::Vector2i startPosition, float gravity);

	//return Direction enum state
	PlayableCharacter::Direction getDir();
	//Virtual function for targeting laser toggle
	virtual void toggleTargeting(SoundManager& m_SM) = 0;
	//Is this character currently shooting
	bool shooting = false;
	//virtual function for returning the targeting state
	virtual bool isTargeting() = 0;
	//Laser(targeting beam) object points to this location
	sf::Vector2f target;
	//Laser object
	laser targetingLaser;

	//	Every subclass of this class must overload this function
	virtual sf::String getClassName() = 0;

protected:
	// Sprite Animation Variables
	//Width of animation Sprite
	int frameWidth = 0;
	//Height of animation Sprite
	int frameHeight = 0;
	//animation Sprite offset,X-axis
	int frameXOffset = 0;
	//animation Sprite offset,Y-axis
	int frameYOffset = 0;
	//Maximum number of animation frames
	int m_maxAnimationFrames = 0;
	//Time passed since animation frame update
	float m_timeSinceLastFrame = 0.0f;
	//Time between frame updates
	float frameSwitchTime = 0.1f;
	//Image containing animation sheet(Sprite Sheet)
	sf::Image m_animationSheet;
	//Sprite for this character
	sf::Sprite m_Sprite;

	// We will call this function once every frame
	virtual void update(float elapsedTime,int** m_ArrayLevel) = 0;

	// This is a pure virtual function
	virtual void handleInput() = 0;

	// How fast is the character
	float m_Speed = 100;

	// Where are the characters various body parts?
	//Contains the boundaries of the character Feet
	sf::FloatRect m_Feet;
	//Contains the boundaries of the character Head
	sf::FloatRect m_Head;
	//Contains the boundaries of the character Right side
	sf::FloatRect m_Right;
	//Contains the boundaries of the character Left side
	sf::FloatRect m_Left;

	// A texture
	sf::Texture m_Texture;

	//	Overload the '<Direction>++' operator
	friend PlayableCharacter::Direction& operator++(PlayableCharacter::Direction& mv, int);
};

#endif // !PLAYABLECHARACTER_H
