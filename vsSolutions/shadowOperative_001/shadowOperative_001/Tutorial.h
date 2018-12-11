/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <map>
#include <SFML/Graphics.hpp>

class Tutorial {
private:
	// A map container from the STL,
	// that holds related pairs of String and Texture
	std::map<std::string, sf::Texture> m_Textures;

	// A pointer of the same type as the class itself
	// the one and only instance
	static Tutorial* m_s_Instance;

public:
	Tutorial();
	static std::string& GetTutorial(sf::Vector2i const& position);
};
#endif // !TUTORIAL_H