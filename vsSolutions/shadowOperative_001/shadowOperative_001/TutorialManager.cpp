/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/12/11	YYYY/MM/DD
*	@description
*/

#include "TutorialManager.h"

TutorialManager* TutorialManager::m_s_Instance = nullptr;

//  A pointer to the Tutorial to be displayed
static sf::FileInputStream* stream;

TutorialManager::TutorialManager() {
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

std::string& TutorialManager::GetTutorial(sf::Vector2i const& position) {
	//  Uncomment this to always return something
	//std::string temp = "NULL";
	//return *(&temp);

	//  Hash the Vector2i to produce an Integer value
	int hashValue = position.x * position.y;

	// Get a reference to m_Tutorials using m_S_Instance
	std::map<int, std::string>& m = m_s_Instance->m_Tutorials;

	// Create an iterator to hold a key-value-pair (kvp)
	// and search for the required kvp
	// using the passed in file name
	std::map<int, std::string>::iterator keyValuePair = m.find(hashValue);

	// Did we find a match?
	if (keyValuePair != m.end()) {
		// Yes
		// Return the string,
		// the second part of the kvp, the tutorial text
		return keyValuePair->second;
	}
	else {
		// File name not found
		// Create a new key value pair using the filename
		std::string& t_string = m[hashValue];
		// Load the string from file in the usual way
		stream->open(std::string("tutorials\\") += std::to_string(hashValue));
		stream->read(&t_string, stream->getSize());
		stream->~FileInputStream();

		// Return the string to the calling code
		return(t_string);
	}
}