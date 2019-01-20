/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2018/11/01	YYYY/MM/DD
*	@description
*/

#include "TextureHolder.h"

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder() {
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(std::string const& filename) {
	// Get a reference to m_Textures using m_S_Instance
	std::map<std::string,sf::Texture>& m = m_s_Instance->m_Textures;
	// auto is the equivalent of map<string, Texture>

	// Create an iterator to hold a key-value-pair (kvp)
	// and search for the required kvp
	// using the passed in file name
	std::map<std::string, sf::Texture>::iterator keyValuePair = m.find(filename);
	// auto is equivalent of map<string, Texture>::iterator


	// Did we find a match?
	if (keyValuePair != m.end()) {
		// Yes
		// Return the texture,
		// the second part of the kvp, the texture
		
		// Apply Anti-Aliasing to the Texture
		keyValuePair->second.setSmooth(true);

		return keyValuePair->second;
	}
	else {
		// File name not found
		// Create a new key value pair using the filename
		sf::Texture& texture = m[filename];
		// Load the texture from file in the usual way
		texture.loadFromFile(filename);

		// Apply Anti-Aliasing to the Texture
		texture.setSmooth(true);

		// Return the texture to the calling code
		return texture;
	}
}