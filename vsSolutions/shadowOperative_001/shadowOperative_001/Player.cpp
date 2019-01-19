/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description	...
*
*	@notes	1.		Measurements for Player Sprite
*						Idle
*							L	Width: 35	Height: 66	XOffset: 0
*							R	Width: 35	Height: 66	XOffset: 35
*						Run
*							L	Width: 50	Height: 66	XOffset: 71
*							R	Width: 50	Height: 66	XOffset: 121
*						Jump
*							L	Width: 52	Height: 64	XOffset: 171
*							R	Width: 52	Height: 64	XOffset: 223
*						Attack
*							L	Width: 68	Height: 66	XOffset: 275
*							R	Width: 68	Height: 66	XOffset: 343
*/

#include "Player.h"
#include "TextureHolder.h"

/**
*	Default constructor.
*/
Player::Player() {
	this->maxJumps = 2;

	this->m_animationSheet.loadFromFile("graphics\\PlayerAnimationSheet.png");
	this->m_maxAnimationFrames = 10;
}

void Player::update(float elapsedTime, int** m_ArrayLevel) {
	// Set Sprite Animation Frame
	if (this->frameYOffset > m_maxAnimationFrames) {
		this->frameYOffset = 0;
	}

	this->m_timeSinceLastFrame += elapsedTime;
	
	/***-------------***\
	|	HANDLE ACTIONS	|
	\***-------------***/

	if (this->m_Action == Action::IDLE) {
		this->frameWidth = 35;
		this->frameHeight = 66;
		this->frameXOffset = 0;
	}
	else if (this->m_Action == Action::RUNNING) {
		this->frameWidth = 50;
		this->frameHeight = 66;
		this->frameXOffset = 71;
	}
	else if (this->m_Action == Action::JUMPING) {
		this->frameWidth = 52;
		this->frameHeight = 64;
		this->frameXOffset = 171;

		// Update how long the jump has been going
		this->m_jumpDuration += elapsedTime;

		// Add the jump time to the timer
		this->m_Position.y -= this->m_Gravity * 2 * elapsedTime;

		// Character jump has gone on long enough
		if (this->m_jumpDuration >= this->maxJumpDuration) {
			this->m_Action = Action::FALLING;
		}
	}
	else if (this->m_Action == Action::ATTACKING) {
		this->frameWidth = 68;
		this->frameHeight = 66;
		this->frameXOffset = 275;
	}
	else if (this->m_Action == Action::FALLING) {
		/*this->frameWidth = 0;
		this->frameHeight = 0;*/

		this->m_Position.y += this->m_Gravity * elapsedTime;
	}
	else if (this->m_Action == Action::CROUCHING) {
		/*this->frameWidth = 0;
		this->frameHeight = 0;*/
	}
	
	/***-----------------***\
	|	HANDLE DIRECTIONS	|
	\***-----------------***/
	
	if (this->m_Direction == Direction::LEFT) {
		this->m_Position.x -= this->m_Speed * elapsedTime;

		//Changes the the sprite to running left
		/*this->m_Sprite = sf::Sprite(TextureHolder::GetTexture(
			"graphics/RunLeft__001.png"));*/
		// Set the Animation Sprite
		if (this->m_timeSinceLastFrame > frameSwitchTime) {
			this->m_Texture.loadFromImage(
				m_animationSheet,
				sf::IntRect(
					this->frameXOffset,
					this->frameYOffset * this->frameHeight,
					this->frameWidth,
					this->frameHeight));
			this->m_Sprite.setTexture(m_Texture);
			this->m_timeSinceLastFrame = 0.0f;
		}
	}
	else if (this->m_Direction == Direction::RIGHT) {
		this->m_Position.x += this->m_Speed * elapsedTime;
		
		this->frameXOffset += this->frameWidth;

		//Changes the the sprite to runnning right
		/*this->m_Sprite = sf::Sprite(TextureHolder::GetTexture(
			"graphics/RunRight__001.png"));*/
		// Set the Animation Sprite
		if (this->m_timeSinceLastFrame > frameSwitchTime) {
			this->m_Texture.loadFromImage(
				m_animationSheet,
				sf::IntRect(
					this->frameXOffset,
					this->frameYOffset * this->frameHeight,
					this->frameWidth,
					this->frameHeight));
			this->m_Sprite.setTexture(m_Texture);
			this->m_timeSinceLastFrame = 0.0f;
		}
	}
	else if (m_Direction == Direction::IDLE) {
		// Look at the Nearest Enemy

		//this->frameXOffset += this->frameWidth;

		// Set the Animation Sprite
		if (this->m_timeSinceLastFrame > frameSwitchTime) {
			this->m_Texture.loadFromImage(
				m_animationSheet, 
				sf::IntRect(
					this->frameXOffset, 
					this->frameYOffset * this->frameHeight, 
					this->frameWidth, 
					this->frameHeight));
			this->m_Sprite.setTexture(m_Texture);
			this->m_timeSinceLastFrame = 0.0f;
		}
	}
	else if (this->m_Action == Action::FALLING) {
		// Set Player Sprite to Falling
		this->m_Sprite = sf::Sprite(TextureHolder::GetTexture(
			"graphics/Glide_000.png"));
	}
	
	this->frameYOffset++;

	/***-------------***\
	|	RESIZE HITBOX	|
	\***-------------***/

	// Update the rect for all body parts
	sf::FloatRect r = this->getPosition();
	
	// Feet
	this->m_Feet.left = m_Position.x;
	this->m_Feet.top = m_Position.y + (r.height * 0.9);
	this->m_Feet.width = r.width;
	this->m_Feet.height = r.height * 0.1;

	// Head
	this->m_Head.left = m_Position.x;
	this->m_Head.top = m_Position.y;
	this->m_Head.width = r.width;
	this->m_Head.height = r.height * 0.1;

	// Right
	this->m_Right.left = m_Position.x + (r.width * 0.9);
	this->m_Right.top = m_Position.y + (r.height * 0.1);
	this->m_Right.width = r.width * 0.1;
	this->m_Right.height = r.height * 0.8;

	// Left
	this->m_Left.left = m_Position.x;
	this->m_Left.top = m_Position.y + (r.height * 0.1);
	this->m_Left.width = r.width * 0.1;
	this->m_Left.height = r.height * 0.8;

	// Move the sprite into position
	this->m_Sprite.setPosition(this->m_Position);

}

// A virtual function
void Player::handleInput() {
	//  Jumping
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		// Character not already jumping
		if (this->m_jumpCounter < this->maxJumps) {

			this->m_Action = Action::JUMPING;
			this->m_jumpCounter++;
		}
	}

	//  Moving Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		//this->m_Action = Action::RUNNING;
		this->m_Direction = Direction::LEFT;
	}
	//  Moving Right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		//this->m_Action = Action::RUNNING;
		this->m_Direction = Direction::RIGHT;
	}
	
	// If nothing is pressed
	else {
		//this->m_Action = Action::IDLE;
		this->m_Direction = Direction::IDLE;
	}	
}

int Player::getDetectLevel()
{
	return detectionLevel;
}