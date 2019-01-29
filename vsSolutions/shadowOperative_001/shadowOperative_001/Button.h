/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2019/01/15	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML\Graphics.hpp>

#include "SoundManager.h"

//	Keep Button related code inside GUI namespace
namespace GUI {

	//	Preset appearances for the Button
	namespace ButtonStyle {
		enum {
			none = 0,
			save = 1,
			cancel = 2,
			clean = 3,
		};
	};

	//	Button states for attaching events to
	namespace ButtonState {
		enum {
			normal = 0,
			hovered = 1,
			clicked = 2
		};
	};

	//	Button class.  Implements Drawable interface 
	class Button : public sf::Drawable {
	public:
		Button();
		Button(std::string s, sf::Font& font, sf::Vector2f position, sf::Uint32 Style);

		~Button();

		void setColourTextNormal(sf::Color text) { m_textNormal = text; };
		void setColourTextHover(sf::Color text) { m_textHover = text; };
		void setColourTextClicked(sf::Color text) { m_textClicked = text; };
		void setColourNormal(sf::Color bgNormal) { m_bgNormal = bgNormal; };
		void setColourHover(sf::Color bgHover) { m_bgHover = bgHover; };
		void setColourClicked(sf::Color bgClicked) { m_bgClicked = bgClicked; };
		void setBorderColour(sf::Color border) { m_border = border; };
		void setBorderThickness(float t) { m_borderThickness = t; };
		void setBorderRadius(float r) { m_borderRadius = r; };
		void setPosition(sf::Vector2f position) { m_position = position; };
		void setSize(unsigned int size);

		void setText(std::string s);
		void setStyle(sf::Uint32 Style);
		void setFont(sf::Font& font);

		sf::Vector2f getPosition() { return m_position; };
		sf::Vector2f getDimensions() { return sf::Vector2f(m_button.getGlobalBounds().width, m_button.getGlobalBounds().height); };
		sf::Uint32 getState() { return m_btnstate; };

		//	Set the state of this button externally
		void setState(sf::Uint32 newState) { this->m_btnstate = newState; };

		//	Update the button with the mouse position, time, and the active window
		void update(sf::Event& e, sf::Time t, sf::RenderWindow& window);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		//	Colours for defining different states
		sf::Color m_bgNormal;
		sf::Color m_bgHover;
		sf::Color m_bgClicked;
		sf::Color m_textNormal;
		sf::Color m_textHover;
		sf::Color m_textClicked;
		sf::Color m_border;

		//	Outline properties of the Button
		float m_borderThickness;
		float m_borderRadius;
		sf::RectangleShape m_button;
		sf::Vector2f m_size;
		sf::Vector2f m_position;
		sf::Uint32 m_style;
		sf::Uint32 m_btnstate;

		//	Appearance of Text on the Button
		sf::Font m_font;
		unsigned int m_fontSize;
		sf::Text m_text;
		sf::Text m_shadow;

		//	Time since last click to prevent multiple presses
		sf::Time m_sinceLastClick;
	};
};

#endif // !BUTTON_H
