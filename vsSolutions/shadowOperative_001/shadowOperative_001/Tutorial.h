/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/12/11	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <assert.h>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/System/FileInputStream.hpp>

class Tutorial {
private:
	//  A pointer to the Tutorial to be displayed
	static sf::FileInputStream* stream;

	// A map container from the STL,
	// that holds related pairs of String and Texture
	std::map<std::string, std::string> m_Tutorials;

	// A pointer of the same type as the class itself
	// the one and only instance
	static Tutorial* m_s_Instance;

public:
	Tutorial();
	static std::string& GetTutorial(std::string const& filename);
};
#endif // !TUTORIAL_H