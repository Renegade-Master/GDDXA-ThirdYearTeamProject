/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description	...
*
*	@notes	1.		Measurements for Player Sprite
*						Idle
*							R	Width: 35	Height: 66	XOffset: 0
*						Run
*							R	Width: 51	Height: 70	XOffset: 35
*						Jump
*							R	Width: 56	Height: 70	XOffset: 86
*						Attack
*							R	Width: 69	Height: 75	XOffset: 142
*						Climb
*							R	Width: 42	Height: 69	XOffset: 211
*						Fall
*							R	Width: 55	Height: 56	XOffset: 253
*						Die
*							R	Width: 62	Height: 64	XOffset: 308
*/

#include "Player.h"
#include "TextureHolder.h"

/**
*	Default constructor.
*/
Player::Player() {
	this->maxJumps = 2;

	this->m_animationSheet.loadFromFile("graphics\\PlayerAnimationSheet_05.png");
	this->m_maxAnimationFrames = 10;
	this->m_Action = Action::FALLING;
	this->m_Direction = Direction::IDLE;
}

/**
*	Dev
*/
void Player::update(float elapsedTime, int** m_ArrayLevel) {
	// Set Sprite Animation Frame
	if (this->frameYOffset >= this->m_maxAnimationFrames) {
		this->frameYOffset = 0;
	}
	
	this->frameXOffset = 0;
	this->m_timeSinceLastFrame += elapsedTime;
	
	/***-------------***\
	|	HANDLE ACTIONS	|
	\***-------------***/

	// Save off some data for this Frame
	/*this->m_LastAction = this->m_Action;
	this->m_LastDirection = this->m_Direction;
	this->m_LastPosition = this->m_Position;*/

	if (this->m_Action == Action::FALLING) {
		this->frameWidth = 55;
		this->frameHeight = 56;
		this->frameXOffset = 253;

		this->m_Position.y += this->m_Gravity * 0.0167f;
	}
	else if (this->m_Action == Action::JUMPING) {
		this->frameWidth = 56;
		this->frameHeight = 70;
		this->frameXOffset = 86;

		// Update how long the jump has been going
		this->m_jumpDuration += elapsedTime;

		// Apply the Jump to the Character
		this->m_Position.y -= this->m_Gravity * 2 * 0.0167;

		// Character jump has gone on long enough
		if (this->m_jumpDuration >= this->maxJumpDuration) {
			this->m_Action = Action::FALLING;
		}
	}
	else if (this->m_Action == Action::RUNNING) {
		this->frameWidth = 51;
		this->frameHeight = 70;
		this->frameXOffset = 35;
	}
	else if (this->m_Action == Action::ATTACKING) {
		this->frameWidth = 69;
		this->frameHeight = 75;
		this->frameXOffset = 142;
	}
	else if (this->m_Action == Action::CROUCHING) {
		/*this->frameWidth = 0;
		this->frameHeight = 0;*/
	}
	else if (this->m_Action == Action::IDLE) {
		this->frameWidth = 36;
		this->frameHeight = 66;
		this->frameXOffset = 0;
	}
	
	/***---------------------***\
	|	HANDLE RIGHT DIRECTION	|
	\***---------------------***/
	
	if (this->m_Direction == Direction::RIGHT) {
		this->m_Position.x += this->m_Speed * elapsedTime;
		
		// Set the Animation Sprite
		if (this->m_timeSinceLastFrame > frameSwitchTime) {
			this->m_Texture.loadFromImage(
				m_animationSheet,
				sf::IntRect(
					this->frameXOffset,						// What type of Animation?
					this->frameYOffset * this->frameHeight, // What frame of the Animation?
					this->frameWidth,						// How wide is the Frame?
					this->frameHeight));					// How tall is the Frame?
			this->m_Sprite.setTexture(this->m_Texture);
			this->m_timeSinceLastFrame = 0.0f;
		}
	}

	/***---------------------***\
	|	HANDLE LEFT DIRECTION	|
	\***---------------------***/

	else if (this->m_Direction == Direction::LEFT) {
		this->m_Position.x -= this->m_Speed * elapsedTime;

		// Look in the right direction

		// Set the Animation Sprite
		if (this->m_timeSinceLastFrame > frameSwitchTime) {
			this->m_Texture.loadFromImage(
				m_animationSheet,
				sf::IntRect(
					this->frameXOffset + (m_animationSheet.getSize().x / 2.0f),	// What type of Animation?  Also move to Left half of SpriteSheet
					this->frameYOffset * this->frameHeight,						// What frame of the Animation?
					this->frameWidth,											// How wide is the Frame?
					this->frameHeight));										// How tall is the Frame?
			this->m_Sprite.setTexture(m_Texture);
			this->m_timeSinceLastFrame = 0.0f;
		}
	}

	/***-----------------***\
	|	HANDLE NO DIRECTION	|
	\***-----------------***/

	else {
		// Look at the Nearest Enemy
		
		// Set the Animation Sprite
		if (this->m_timeSinceLastFrame > frameSwitchTime) {
			this->m_Texture.loadFromImage(
				m_animationSheet,
				sf::IntRect(
					this->frameXOffset,							// What type of Animation?
					this->frameYOffset * this->frameHeight,		// What frame of the Animation?
					this->frameWidth,							// How wide is the Frame?
					this->frameHeight));						// How tall is the Frame?
			this->m_Sprite.setTexture(m_Texture);
			this->m_timeSinceLastFrame = 0.0f;
		}
	}

	// Increment Animation Frame
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
	this->m_Feet.height = r.height * 0.075;

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

	// Move the Sprite into position
	this->m_Sprite.setPosition(this->m_Position);

	//charge weapon
	this->chargeGun(elapsedTime);
	//targetingLaser.updateLine(this->m_Position, mousePos);
}

// A virtual function
void Player::handleInput() {
	
	/***-----------------***\
	|	HANDLE ALL STANCE	|
	\***-----------------***/

	//  Moving Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->m_Direction = Direction::LEFT;
	}
	//  Moving Right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->m_Direction = Direction::RIGHT;
	}
	// If nothing is pressed
	else {
		this->m_LastDirection = this->m_Direction;
		this->m_Direction = Direction::IDLE;
	}

	/***---------------------***\
	|	HANDLE FALLING STANCE	|
	\***---------------------***/

	if (this->m_Action == Action::FALLING) {
		//  Double Jump		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

			// Character hasn't jumped too many times
			if (this->m_jumpCounter < this->maxJumps) {
				this->m_jumpDuration = 0.0f;
				this->m_Action = Action::JUMPING;
				this->m_jumpCounter++;
			}
		}
	}

	/***---------------------***\
	|	HANDLE JUMPING STANCE	|
	\***---------------------***/

	else if (this->m_Action == Action::JUMPING) {

	}

	/***---------------------***\
	|	HANDLE RUNNING STANCE	|
	\***---------------------***/

	else if (this->m_Action == Action::RUNNING) {
		// Continue Running
		if (this->m_Direction == Direction::LEFT
			|| this->m_Direction == Direction::RIGHT) {
			
			this->m_Action = Action::RUNNING;			
		}
		// Stop Running
		else if (this->m_Direction == Direction::IDLE) {
			this->m_Action == Action::IDLE;
		}
		
		//  Running Jump
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			// Character not already jumping
			if (this->m_jumpCounter < this->maxJumps) {

				this->m_Action = Action::JUMPING;
				this->m_jumpCounter++;
			}
		}
	}

	/***---------------------***\
	|	HANDLE CROUCHING STANCE	|
	\***---------------------***/

	else if (this->m_Action == Action::CROUCHING) {

	}

	/***---------------------***\
	|	HANDLE ATTACK STANCE	|
	\***---------------------***/

	else if (this->m_Action == Action::ATTACKING) {
		//  Jumping
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			// Character not already jumping
			if (this->m_jumpCounter < this->maxJumps) {

				this->m_Action = Action::JUMPING;
				this->m_jumpCounter++;
			}
		}
	}

	/***-----------------***\
	|	HANDLE IDLE STANCE	|
	\***-----------------***/
	else if (this->m_Action == Action::IDLE) {
		//  Start Jumping
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			// Character not already jumping
			if (this->m_jumpCounter < this->maxJumps) {

				this->m_Action = Action::JUMPING;
				this->m_jumpCounter++;
			}
		}

		// Start Running
		if (this->m_Direction == Direction::LEFT
			|| this->m_Direction == Direction::RIGHT) {
			
			this->m_Action = Action::RUNNING;
		}

		// Start Crouching
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			
		}
	}
	
	/***-------------***\
	|	HANDLE SHOOTING	|
	\***-------------***/

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		shooting = true;
	}
	else {
		shooting = false;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		this->toggleTargeting();
	}
}

/**
*	Decide what level of Detection is returned based on m_Action State
*/
int Player::getDetectLevel() {
	if ((this->m_Action == Action::FALLING)
		|| (this->m_Action == Action::JUMPING)
		|| (this->m_Action == Action::ATTACKING)) {

		return detectionLevel = 3;
	}
	else if (this->m_Action == Action::IDLE) {
		return detectionLevel = 2;
	}
	else if (this->m_Action == Action::CROUCHING) {
		return detectionLevel = 1;
	}
	else {
		return detectionLevel = 0;
	}
}

/**
*
*/
bool Player::isShooting() {
	return shooting;
}

/**
*
*/
void Player::playerShot(bool shot) {
	gunChargeLevel -= shotCost;
	shooting = false;
}

/**
*
*/
void Player::chargeGun(float dtAsSeconds) {
	if (!shooting) {
		if (gunChargeLevel + gunChargeRate * dtAsSeconds <= maxGunChargeLevel) {
			/*std::cout << "\n gunChargeLevel:" << gunChargeLevel << " += gunChargeRate * dtAsSeconds = "
				<< gunChargeLevel + gunChargeRate * dtAsSeconds;*/
			gunChargeLevel += gunChargeRate * dtAsSeconds;
		}
		else {
			gunChargeLevel = maxGunChargeLevel;
		}
	}
}

/**
*
*/
float Player::getChargeLevel() {
	return gunChargeLevel;
}

/**
*
*/
float Player::getShotCost() {
	return shotCost;
}

/**
*
*/
float Player::getMaxCharge() {
	return maxGunChargeLevel;
}

/**
*
*/
void Player::toggleTargeting() {
	if (targeting) {
		targeting = false;
	}
	else {
		targeting = true;
	}
}

/**
*
*/
bool Player::isTargeting() {
	return targeting;
}

/**
*	Choose Origin Point of Laser dependant on Animation State
*	and Mouse Position
*/
void Player::updateTargeting(sf::Vector2f mousePos) {
	sf::Vector2f directPosition = this->m_Position;
	if (this->m_Direction == Direction::RIGHT) {
		if (mousePos.x < this->m_Position.x) {
			directPosition.x -= 35;
			directPosition.y -= 35;
			targetingLaser.updateLine(directPosition, mousePos);
		}
		else {
			directPosition.y -= 35;
			targetingLaser.updateLine(directPosition, mousePos);
		}
	}
	else if (this->m_Direction == Direction::LEFT) {
		if (mousePos.x < this->m_Position.x) {
			directPosition.x -= 50;
			directPosition.y -= 35;
			targetingLaser.updateLine(directPosition, mousePos);
		}
		else{
			directPosition.y -= 35;
			targetingLaser.updateLine(directPosition, mousePos);
		}
	}
	else if (this->m_Direction == Direction::IDLE) {
		if (mousePos.x < this->m_Position.x){
			directPosition.x -= 40;
			directPosition.y -= 35;
			targetingLaser.updateLine(directPosition, mousePos);
		}
		else{
			directPosition.y -= 35;
			targetingLaser.updateLine(directPosition, mousePos);
		}
	}
}

/**
*
*/
sf::ConvexShape Player::getlaser() {
	return targetingLaser.getLine();
}