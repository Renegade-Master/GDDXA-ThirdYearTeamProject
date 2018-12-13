/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/12/11	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef TUTORIALMANAGER_H
#define TUTORIALMANAGER_H

#include <assert.h>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/System/FileInputStream.hpp>

class TutorialManager {
private:
	// A map container from the STL,
	// that holds related pairs of Integers and Strings
	std::map<int, std::string> m_Tutorials;

	// A pointer of the same type as the class itself
	// the one and only instance
	static TutorialManager* m_s_Instance;

public:
	TutorialManager();
	static std::string& GetTutorial(sf::Vector2i const& position);
};
#endif // !TUTORIALMANAGER_H