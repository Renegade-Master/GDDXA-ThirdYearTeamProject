#include "gunBattery.h"
gunBattery::gunBattery()
{
	srand(time(NULL));
	m_Capacity = static_cast<Capacity>(rand() % 3);
	if (this->m_Capacity == Capacity::SMALL) {
		m_ItemSprite = sf::Sprite(TextureHolder::GetTexture(
			"graphics/Batteries/BATTERY_SMALL"));
	}
	else if (this->m_Capacity == Capacity::MEDIUM) {
		m_ItemSprite = sf::Sprite(TextureHolder::GetTexture(
			"graphics/Batteries/BATTERY_MEDIUM"));
	}
	else if (this->m_Capacity == Capacity::LARGE) {
		m_ItemSprite = sf::Sprite(TextureHolder::GetTexture(
			"graphics/Batteries/BATTERY_LARGE"));
	}
}
float gunBattery::getCapacity()
{
	if (this->m_Capacity == Capacity::SMALL) {
		return 10.00;
	}
	else if (this->m_Capacity == Capacity::MEDIUM) {
		return 25.00;
	}
	else if (this->m_Capacity == Capacity::LARGE) {
		return 50.00;
	}
}
void gunBattery::update(float elapsedTime, int** m_ArrayLevel) {
	//No update needed
}