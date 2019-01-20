/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.h"

class Bullet {
private:
	// Where is the bullet?
	sf::Vector2f m_Position;

	// What each bullet looks like
	sf::RectangleShape m_BulletShape;
	sf::Sprite m_BulletSprite;

	// Is this bullet currently whizzing through the air
	bool m_InFlight = false;

	// How fast does a bullet travel?
	float m_BulletSpeed = 500;
	
	// What fraction of 1 pixel does the bullet travel, 
	// Horizontally and vertically each frame?
	// These values will be derived from m_BulletSpeed
	sf::Vector2f m_BulletDistance;

	// Where is this bullet headed to?
	sf::Vector2f m_Target;

	// Some boundaries so the bullet doesn't fly forever
	sf::Vector2f m_Max;
	sf::Vector2f m_Min;

	//How much dameage will the bullet do
	float shotPower = 10;

// Public function prototypes go here
public:
	// The constructor
	Bullet();

	// Stop the bullet
	void stop();

	// Returns the value of m_InFlight
	bool isInFlight();

	// Launch a new bullet
	void shoot(float startX, float startY,
		float xTarget, float yTarget);

	// Tell the calling code where the bullet is in the world
	sf::FloatRect getPosition();

	// Return the actual shape (for drawing)
	sf::Sprite getSprite();

	// Update the bullet each frame
	void update(float elapsedTime);

	//getX,Y
	sf::Vector2f getCenter();

	//Bullet damage
	void setShotPower(float power);
	float getShotPower();
};

#endif // BULLET_H