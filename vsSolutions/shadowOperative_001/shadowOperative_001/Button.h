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

#include <iostream>

#include <SFML\Graphics.hpp>

#include "SoundManager.h"

namespace GUI {
	namespace ButtonStyle {
		enum {
			none = 0,
			save = 1,
			cancel = 2,
			clean = 3,
		};
	};

	namespace ButtonState {
		enum {
			normal = 0,
			hovered = 1,
			clicked = 2
		};
	};

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
		void setState(sf::Uint32 newState) { m_btnstate = newState; };

		void update(sf::Event& e, sf::Time t, sf::RenderWindow& window);

		GUI::Button* getPointer();

	private:
		void init();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		//Default Color for Button Objects
		sf::Color m_bgNormal;
		//Color For Button Objects when mouse Hovers over
		sf::Color m_bgHover;
		//Color for Buttons when clicked
		sf::Color m_bgClicked;
		//Default Text Color for Button Objects
		sf::Color m_textNormal;
		//Text Color for Button When Mouse is hovering over
		sf::Color m_textHover;
		//Text Color for Button Object when clicked
		sf::Color m_textClicked;
		//Border Color for Button Objects
		sf::Color m_border;
		//Thickness applied to the border surrounding Button objects
		float m_borderThickness;
		//radius of Button Object Borders
		float m_borderRadius;
		//Size of Button Objects
		sf::Vector2f m_size;
		//Position of Button Objects
		sf::Vector2f m_position;
		//Stores the Button Type(Color)
		sf::Uint32 m_style;
		//Stores the button State(Clicked,Hovered,etc)
		sf::Uint32 m_btnstate;
		//RectangleShape(Button)
		sf::RectangleShape m_button;
		//Button Text Font
		sf::Font m_font;
		//Text Font size
		unsigned int m_fontSize;
		//Button Text
		sf::Text m_text;
		//Text styled to look like a shadow
		sf::Text m_shadow;
		//Records Time of last Click
		sf::Time m_sinceLastClick;
	};
};

#endif // !BUTTON_H
