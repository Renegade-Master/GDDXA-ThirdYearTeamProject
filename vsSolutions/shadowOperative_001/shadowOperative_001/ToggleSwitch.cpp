#include "ToggleSwitch.h"

ToggleSwitch::ToggleSwitch(sf::Time time) {
	m_LastToggleEvent = time;
}
sf::Sprite ToggleSwitch::getSprite(){
	if (m_ToggleState == State::TOGGLE_OFF) {
		//changed Sprite here
	}
	else {
		//change Sprite here
	}
	return m_Sprite;
}
sf::FloatRect ToggleSwitch::getPosition() {
	return m_Sprite.getGlobalBounds();
}
sf::Vector2f ToggleSwitch::getCenter() {
	return sf::Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
	);
}
void ToggleSwitch::update() {

}
void ToggleSwitch::toggle(sf::Time elapsedTime) {
	if (m_LastToggleEvent.asSeconds() -
		elapsedTime.asSeconds() > 10) {

	}
	else {
		
	}
}