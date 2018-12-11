/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[]
*	@creationDate	2018/12/11	YYYY/MM/DD
*	@description
*/

#include "Tutorial.h"

Tutorial* Tutorial::m_s_Instance = nullptr;

Tutorial::Tutorial() {
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

std::string& Tutorial::GetTutorial(std::string const& filename) {
	// Get a reference to m_Tutorials using m_S_Instance
	std::map<std::string, std::string>& m = m_s_Instance->m_Tutorials;
	// auto is the equivalent of map<string, string>

	// Create an iterator to hold a key-value-pair (kvp)
	// and search for the required kvp
	// using the passed in file name
	std::map<std::string, std::string>::iterator keyValuePair = m.find(filename);
	// auto is equivalent of map<string, string>::iterator


	// Did we find a match?
	if (keyValuePair != m.end()) {
		// Yes
		// Return the string,
		// the second part of the kvp, the string
		return keyValuePair->second;
	}
	else {
		// File name not found
		// Create a new key value pair using the filename
		auto& t_string = m[filename];
		// Load the texture from file in the usual way
		stream->open(filename);
		std::string* temp = NULL;
		stream->read(t_string, stream->getSize());
		//t_string = m[*temp];
		delete temp;

		// Return the texture to the calling code
		return(t_string);
	}
	
	std::string temp = "NULL";
	return *(&temp);
}