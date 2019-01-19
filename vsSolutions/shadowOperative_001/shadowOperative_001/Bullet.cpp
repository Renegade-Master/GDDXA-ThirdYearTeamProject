/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "Bullet.h"

// The constructor
Bullet::Bullet() {
	//std::cout << "\nBullet initialised";
	m_BulletSprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/Bullet_000.png"));
	m_BulletSprite.setPosition(this->m_Position);
	//m_BulletShape.setSize(sf::Vector2f(10, 10));
	m_InFlight = false;
}


void Bullet::shoot(float startX, float startY,
	float targetX, float targetY) {
	// Keep track of the bullet
	m_InFlight = true;
	m_Position.x = startX;
	m_Position.y = startY;

	// Calculate the gradient of the flight path
	float gradient = (startX - targetX) / (startY - targetY);

	// Any gradient less than zero needs to be negative
	if (gradient < 0) {
		gradient *= -1;
	}

	// Calculate the ratio between x and t
	float ratioXY = m_BulletSpeed / (1 + gradient);

	// Set the "speed" horizontally and vertically
	m_BulletDistance.y = ratioXY;
	m_BulletDistance.x = ratioXY * gradient;

	// Point the bullet in the right direction
	if (targetX < startX) {
		m_BulletDistance.x *= -1;
	}

	if (targetY < startY) {
		m_BulletDistance.y *= -1;
	}

	// Finally, assign the results to the
	// member variables
	m_Target.x = targetX;
	m_Target.y = targetY;

	// Set a max range of 1000 pixels
	float range = 1000;
	m_Min.x = startX - range;
	m_Max.x = startX + range;
	m_Min.y = startY - range;
	m_Max.y = startY + range;

	// Position the bullet ready to be drawn
	m_BulletSprite.setPosition(startX,startY);
	m_BulletShape.setPosition(startX, startY);
}

void Bullet::stop() {
	m_InFlight = false;
}

bool Bullet::isInFlight() {
	return m_InFlight;
}
sf::Vector2f Bullet::getCenter()
{
	return m_Position;
}
sf::FloatRect Bullet::getPosition() {
	return m_BulletSprite.getGlobalBounds();
	//return m_BulletShape.getGlobalBounds();
}

sf::Sprite Bullet::getSprite() {
	return m_BulletSprite;
}
sf::RectangleShape Bullet::getShape()
{
	std::cout << "\ncalling bulletShape";
	return m_BulletShape;
}
void Bullet::update(float elapsedTime) {
	/*std::cout << "\nelapsed Time:" << elapsedTime;
	std::cout << "\n Starting position recalculated";
	std::cout << "\n Bullet positin is now: x," << m_Position.x << " , y:" << m_Position.y;
	std::cout << "\n BulletShape positin is now: x," << m_BulletShape.getPosition().x << " , y:" << m_BulletShape.getPosition().y;*/
	// Update the bullet position variables
	/*std::cout<<"\n m_BulletDistance.x ="<< m_BulletDistance.x;
	std::cout << "\n m_BulletDistance.y =" << m_BulletDistance.y;*/
	m_Position.x += m_BulletDistance.x * elapsedTime;
	m_Position.y += m_BulletDistance.y * elapsedTime;
	/*std::cout << "\n position recalculated";
	std::cout << "\n Bullet positin is now: x," << m_Position.x << " , y:" << m_Position.y;
	std::cout << "\n BulletShape positin is now: x," << m_BulletShape.getPosition().x << " , y:" << m_BulletShape.getPosition().y;*/
	// Move the bullet
	m_BulletSprite.setPosition(m_Position);
	m_BulletShape.setPosition(m_Position);

	// Has the bullet gone out of range?
	if (m_Position.x < m_Min.x || m_Position.x > m_Max.x ||
		m_Position.y < m_Min.y || m_Position.y > m_Max.y) {
		m_InFlight = false;
	}
	//has the bullet collided with a wall
	
	/*std::cout << "\n position final calculation";
	std::cout << "\n Bullet positin is now: x," << m_Position.x << " , y:" << m_Position.y;
	std::cout << "\n BulletShape positin is now: x," << m_BulletShape.getPosition().x << " , y:" << m_BulletShape.getPosition().y;*/
}